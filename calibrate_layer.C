#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TLorentzVector.h>
#include <TMath.h>
#include <iostream>
#include "Helpers.C"
#include <unordered_map>

float triggerCellLsbBeforeCompression = 100./1024.;
int triggerCellTruncationBits = 0;
float adcSaturationBH_MIP = 1024.;
int adcNbitsBH = 12;
float fCperMIP = 2.57;
float thickCorr = 1.092;

vector<float> dEdX_weights_nominal = {0.0,   // there is no layer zero
				      8.603e-3, // Gev
				      8.0675e-3, 
				      8.0675e-3, 
				       8.0675e-3, 
				       8.0675e-3, 
				       8.0675e-3, 
				       8.0675e-3, 
				       8.0675e-3, 
				       8.0675e-3, 
				       8.9515e-3, 
				       10.135e-3, 
				       10.135e-3, 
				       10.135e-3, 
				       10.135e-3, 
				       10.135e-3, 
				       10.135e-3, 
				       10.135e-3, 
				       10.135e-3, 
				       10.135e-3, 
				       11.682e-3, 
				       13.654e-3, 
				       13.654e-3, 
				       13.654e-3, 
				       13.654e-3, 
				       13.654e-3, 
				       13.654e-3, 
				       13.654e-3, 
				       38.2005e-3, 
				       55.0265e-3, 
				       49.871e-3, 
				       49.871e-3, 
				       49.871e-3, 
				       49.871e-3, 
				       49.871e-3, 
				       49.871e-3, 
				       49.871e-3, 
				       49.871e-3, 
				       49.871e-3, 
				       49.871e-3, 
				       62.005e-3, 
				       83.1675e-3, 
				       92.196e-3, 
				       92.196e-3, 
				       92.196e-3, 
				       92.196e-3, 
				       92.196e-3, 
				       92.196e-3, 
				       92.196e-3, 
				       92.196e-3, 
				       92.196e-3, 
				       92.196e-3, 
				       46.098e-3};


vector<float> dEdX_weights_Luca_TrgLayer = {0.0,                               
				   0.0183664,
				   0.,
				   0.0305622,
				   0.,
				   0.0162589,
				   0.,
				   0.0143918,
				   0.,
				   0.0134475,
				   0.,
				   0.0185754,
				   0.,
				   0.0204934,
				   0.,
				   0.016901,
				   0.,
				   0.0207958,
				   0.,
				   0.0167985,
				   0.,
				   0.0238385,
				   0.,
				   0.0301146,
				   0.,
				   0.0274622,
				   0.,
				   0.0468671,
				   0.,
				   0.078819,
				   0.0555831,
				   0.0609312,
				   0.0610768,
				   0.0657626,
				   0.0465653,
				   0.0629383,
				   0.0610061,
				   0.0517326,
				   0.0492882,
				   0.0699336,
				   0.0673457,
				   0.119896,
				   0.125327,
				   0.143235,
				   0.153295,
				   0.104777,
				   0.109345,
				   0.161386,
				   0.174656,
				   0.108053,
				   0.121674,
				   0.1171,
				   0.328053};
				   




float calibrateInMipT(int hwPt, float eta, int subdet){

  float LSB_silicon_fC = triggerCellLsbBeforeCompression*(pow(2,triggerCellTruncationBits));
  float LSB_scintillator_MIP = adcSaturationBH_MIP/(pow(2,adcNbitsBH));

  // Convert ADC to charge in fC (in EE+FH) or in MIPs (in BH)
  float amplitude = hwPt * (subdet==5 ? LSB_scintillator_MIP :  LSB_silicon_fC);

  /* convert the charge amplitude in MIP: */
  float trgCellMipP = amplitude;
  if( subdet!=5 && fCperMIP > 0 ){
    trgCellMipP /= fCperMIP; 
  }

  /* compute the transverse-mip */
  float trgCellMipPt = trgCellMipP/cosh( eta ); 
  
  /* setting pT [mip] */
  return trgCellMipPt;

}



float calibrateMipTinGeV(float MIPpt, int HGClayer, TString calib_version){

  vector<float> dEdX_weights;
  if(calib_version == "nominal")
    dEdX_weights = dEdX_weights_nominal;
  else if(calib_version == "Luca_TrgLayer")
    dEdX_weights = dEdX_weights_Luca_TrgLayer;

  /* weight the amplitude by the absorber coefficient in GeV/mip */
  double trgCellEt = MIPpt * dEdX_weights.at(HGClayer);
  if(calib_version=="nominal" && HGClayer<=40) trgCellEt/=thickCorr;  
  
  return trgCellEt;

}



void calibrate_layer(TString filein,  TString treename, //TString calib_version,
		     TString fileout, bool JB_version=false, bool add_jet=false, bool add_cone=false){


  TFile* f_new = TFile::Open(fileout);
  if(f_new!=0){
    cout<<fileout<<" already exists, please delete it before converting again"<<endl;
    return;
  }  
  f_new = TFile::Open(fileout,"RECREATE");

  TChain * tree = new TChain(treename);
  tree->Add(filein);
  Long64_t nentries = tree->GetEntries();
  cout<<"nentries="<<nentries<<endl;



  TTree* tree_new2 = new TChain("jets");
  TChain * tree_jet = new TChain("jets");
  if(add_jet){
    
    tree_jet->Add(filein);
    Long64_t nentries2 = tree_jet->GetEntries();
    if(nentries!=nentries2){
      cout<<"Inconsistent number of entries in two input files"<<endl;
      return;
    }



  }

  vector<int> *_tc_data;
  vector<int> *_tc_subdet;
  vector<float> *_tc_eta;
  vector<float> *_tc_phi;
  vector<int> *_tc_HGClayer;

  vector<unsigned int> *_tc_id;
  vector<unsigned int> *_cl_id;
  vector<vector<unsigned int> > *_cl_cells;
  vector<vector<unsigned int> > *_cl3d_clusters;
  vector<vector<int> > *_jets_cl3d;
  vector<vector<int> > *_cone_cl3d;
  vector<vector<int> > *_cone_tc;

  vector<float> *_cl_eta;
  vector<float> *_cl_phi;
  vector<float> *_cl3d_eta;
  vector<float> *_cl3d_phi;

  tree->SetBranchAddress("tc_data",       &_tc_data);
  tree->SetBranchAddress("tc_subdet",     &_tc_subdet);  
  tree->SetBranchAddress("tc_eta",        &_tc_eta);
  tree->SetBranchAddress("tc_phi",        &_tc_phi);
  tree->SetBranchAddress("tc_HGClayer",   &_tc_HGClayer);

  if(JB_version){
    tree->SetBranchAddress("tc_id",       &_tc_id);
    tree->SetBranchAddress("cl_id",       &_cl_id);
  }

  tree->SetBranchAddress("cl_cells",      &_cl_cells);
  tree->SetBranchAddress("cl3d_clusters", &_cl3d_clusters);
  if(add_jet)
    tree_jet->SetBranchAddress("jets_cl3d",  &_jets_cl3d);
  if(add_cone){
    tree->SetBranchAddress("cone_cl3d",   &_cone_cl3d);
    tree->SetBranchAddress("cone_tc",     &_cone_tc);
  }

  tree->SetBranchAddress("cl_eta",        &_cl_eta);
  tree->SetBranchAddress("cl_phi",        &_cl_phi);
  tree->SetBranchAddress("cl3d_eta",      &_cl3d_eta);
  tree->SetBranchAddress("cl3d_phi",      &_cl3d_phi);

  TTree* tree_new=tree->GetTree()->CloneTree(0);
  if(add_jet){
    tree_new2=tree_jet->GetTree()->CloneTree(0);
    tree_new->AddFriend(tree_new2);
  }

  //New branches
  vector<float> _tc_MIPpt;
  vector<float> _tc_calib_pt;
  vector<float> _tc_calib_Luca_pt;
  vector<float> _cl_MIPpt;
  vector<float> _cl_calib_pt;
  vector<float> _cl_calib_Luca_pt;
  vector<float> _cl3d_MIPpt;
  vector<float> _cl3d_calib_pt; 
  vector<float> _cl3d_calib_Luca_pt; 
  vector<float> _jets_MIPpt;
  vector<float> _jets_raw_pt;
  vector<float> _jets_raw_eta;
  vector<float> _jets_raw_phi;
  vector<float> _jets_raw_energy; 
  vector<float> _jets_raw_Luca_pt;
  vector<float> _jets_raw_Luca_energy;
  vector<float> _cone_MIPpt;
  vector<float> _cone_calib_pt;
  vector<float> _cone_calib_Luca_pt;
  vector<float> _cone_tc_MIPpt;
  vector<float> _cone_tc_calib_pt;
  vector<float> _cone_tc_calib_Luca_pt;
  
  tree_new->Branch("tc_MIPpt",      &_tc_MIPpt);
  tree_new->Branch("tc_calib_pt",   &_tc_calib_pt);
  tree_new->Branch("tc_calib_Luca_pt",   &_tc_calib_Luca_pt);
  tree_new->Branch("cl_MIPpt",      &_cl_MIPpt);
  tree_new->Branch("cl_calib_pt",   &_cl_calib_pt);
  tree_new->Branch("cl_calib_Luca_pt",   &_cl_calib_Luca_pt);
  tree_new->Branch("cl3d_MIPpt",    &_cl3d_MIPpt);
  tree_new->Branch("cl3d_calib_pt", &_cl3d_calib_pt);
  tree_new->Branch("cl3d_calib_Luca_pt", &_cl3d_calib_Luca_pt);
  if(add_jet){
    tree_new2->Branch("jets_MIPpt",   &_jets_MIPpt);
    tree_new2->Branch("jets_raw_pt",  &_jets_raw_pt);
    tree_new2->Branch("jets_raw_eta", &_jets_raw_eta);
    tree_new2->Branch("jets_raw_phi",  &_jets_raw_phi);
    tree_new2->Branch("jets_raw_energy",  &_jets_raw_energy);
    tree_new2->Branch("jets_raw_Luca_pt",  &_jets_raw_Luca_pt);
    tree_new2->Branch("jets_raw_Luca_energy",  &_jets_raw_Luca_energy);
  }
  if(add_cone){
    tree_new->Branch("cone_MIPpt",    &_cone_MIPpt);
    tree_new->Branch("cone_calib_pt", &_cone_calib_pt);
    tree_new->Branch("cone_calib_Luca_pt", &_cone_calib_Luca_pt);
    tree_new->Branch("cone_tc_MIPpt",    &_cone_tc_MIPpt);
    tree_new->Branch("cone_tc_calib_pt", &_cone_tc_calib_pt);
    tree_new->Branch("cone_tc_calib_Luca_pt", &_cone_tc_calib_Luca_pt);
  }


  for(int i=0;i<nentries;i++){
    //for(int i=4;i<5;i++){

    if(i%10000==0)
      cout<<"i="<<i<<endl;
   
    _tc_data = 0;
    _tc_subdet = 0;
    _tc_eta = 0;
    _tc_phi = 0;
    _tc_HGClayer = 0;
    
    _tc_id = 0;
    _cl_id = 0;
    _cl_cells = 0;
    _cl3d_clusters = 0;
    _jets_cl3d = 0;
    _cone_cl3d = 0;
    _cone_tc = 0;

    _cl_eta = 0;
    _cl_phi = 0;
    _cl3d_eta = 0;
    _cl3d_phi = 0;

    _tc_MIPpt.clear();
    _tc_calib_pt.clear();
    _tc_calib_Luca_pt.clear();
    _cl_MIPpt.clear();
    _cl_calib_pt.clear();
    _cl_calib_Luca_pt.clear();
    _cl3d_MIPpt.clear();
    _cl3d_calib_pt.clear();
    _cl3d_calib_Luca_pt.clear();
    _jets_MIPpt.clear();
    _jets_raw_pt.clear();
    _jets_raw_eta.clear();
    _jets_raw_phi.clear();
    _jets_raw_energy.clear();    
    _jets_raw_Luca_pt.clear();
    _jets_raw_Luca_energy.clear();    

    _cone_MIPpt.clear();
    _cone_calib_pt.clear();
    _cone_calib_Luca_pt.clear();
    _cone_tc_MIPpt.clear();
    _cone_tc_calib_pt.clear();
    _cone_tc_calib_Luca_pt.clear();

    tree->GetEntry(i);
    if(add_jet)
      tree_jet->GetEntry(i);

    map<unsigned int, unsigned int> tc_map; //First ID, Second index
    map<unsigned int, unsigned int> cl_map; //First ID, Second index

    for(unsigned int i_tc=0; i_tc<(*_tc_data).size(); i_tc++){
      
      int hwPt = (*_tc_data)[i_tc];
      int subdet = (*_tc_subdet)[i_tc];
      float eta = (*_tc_eta)[i_tc];
      int HGClayer = (*_tc_HGClayer)[i_tc];

      float MIPpt = calibrateInMipT(hwPt, eta, subdet);
      float calib_pt = calibrateMipTinGeV(MIPpt,HGClayer,"nominal");
      float calib_Luca_pt = calibrateMipTinGeV(MIPpt,HGClayer,"Luca_TrgLayer"); 
      _tc_MIPpt.emplace_back(MIPpt);
      _tc_calib_pt.emplace_back(calib_pt);
      _tc_calib_Luca_pt.emplace_back(calib_Luca_pt);

      if(JB_version)
	tc_map[(*_tc_id)[i_tc]] = i_tc;
      else
	tc_map[i_tc] = i_tc;

    }


    for(unsigned int i_cl=0; i_cl<(*_cl_cells).size(); i_cl++){    
      
      float MIPpt = 0;
      float calib_pt = 0;
      float calib_Luca_pt = 0;

      for(unsigned int i_tc=0; i_tc<(*_cl_cells)[i_cl].size(); i_tc++){
	int tc_index = tc_map[(*_cl_cells)[i_cl][i_tc]];
	MIPpt += _tc_MIPpt[tc_index];
	calib_pt += _tc_calib_pt[tc_index];
	calib_Luca_pt += _tc_calib_Luca_pt[tc_index];
      }

      _cl_MIPpt.emplace_back(MIPpt);
      _cl_calib_pt.emplace_back(calib_pt);      
      _cl_calib_Luca_pt.emplace_back(calib_Luca_pt);      

      if(JB_version)
	cl_map[(*_cl_id)[i_cl]] = i_cl;
      else
	cl_map[i_cl] = i_cl;

    }

    
    for(unsigned int i_c3d=0; i_c3d<(*_cl3d_clusters).size(); i_c3d++){

      float MIPpt = 0;
      float calib_pt = 0;
      float calib_Luca_pt = 0;

      for(unsigned int i_cl=0; i_cl<(*_cl3d_clusters)[i_c3d].size(); i_cl++){
	int cl_index = cl_map[(*_cl3d_clusters)[i_c3d][i_cl]];
	MIPpt += _cl_MIPpt[cl_index];
	calib_pt += _cl_calib_pt[cl_index];
	calib_Luca_pt += _cl_calib_Luca_pt[cl_index];
      }

      _cl3d_MIPpt.emplace_back(MIPpt);
      _cl3d_calib_pt.emplace_back(calib_pt); 
      _cl3d_calib_Luca_pt.emplace_back(calib_Luca_pt); 

    }
    


    if(add_jet){
     
      for(unsigned int i_jet=0; i_jet<(*_jets_cl3d).size(); i_jet++){

	TLorentzVector jet_calib;
	TLorentzVector jet_calib_Luca;
	float MIPpt = 0;

	for(unsigned int i_c3d=0; i_c3d<(*_jets_cl3d)[i_jet].size(); i_c3d++){
	  int cl3d_index = (*_jets_cl3d)[i_jet][i_c3d];
	  TLorentzVector C3D;
	  C3D.SetPtEtaPhiM(_cl3d_calib_pt[cl3d_index],(*_cl3d_eta)[cl3d_index],(*_cl3d_phi)[cl3d_index],0);
	  TLorentzVector C3D_Luca;
	  C3D_Luca.SetPtEtaPhiM(_cl3d_calib_Luca_pt[cl3d_index],(*_cl3d_eta)[cl3d_index],(*_cl3d_phi)[cl3d_index],0);	  
	  jet_calib += C3D;
	  jet_calib_Luca += C3D_Luca;
	  MIPpt += _cl3d_MIPpt[cl3d_index];
	}

	_jets_MIPpt.emplace_back(MIPpt);
	_jets_raw_pt.emplace_back(jet_calib.Pt());
	_jets_raw_eta.emplace_back(jet_calib.Eta());
	_jets_raw_phi.emplace_back(jet_calib.Phi());
	_jets_raw_energy.emplace_back(jet_calib.E());
	_jets_raw_Luca_pt.emplace_back(jet_calib_Luca.Pt());
	_jets_raw_Luca_energy.emplace_back(jet_calib_Luca.E());
	
      }

    }



    if(add_cone){
     
      for(unsigned int i_cone=0; i_cone<(*_cone_cl3d).size(); i_cone++){

	TLorentzVector cone_calib;
	TLorentzVector cone_calib_Luca;
	float MIPpt = 0;

	for(unsigned int i_c3d=0; i_c3d<(*_cone_cl3d)[i_cone].size(); i_c3d++){
	  int cl3d_index = (*_cone_cl3d)[i_cone][i_c3d];
	  TLorentzVector C3D;
	  C3D.SetPtEtaPhiM(_cl3d_calib_pt[cl3d_index],(*_cl3d_eta)[cl3d_index],(*_cl3d_phi)[cl3d_index],0);
	  TLorentzVector C3D_Luca;
	  C3D_Luca.SetPtEtaPhiM(_cl3d_calib_Luca_pt[cl3d_index],(*_cl3d_eta)[cl3d_index],(*_cl3d_phi)[cl3d_index],0);
	  cone_calib += C3D;
	  cone_calib_Luca += C3D_Luca;
	  MIPpt += _cl3d_MIPpt[cl3d_index];
	}

	_cone_MIPpt.emplace_back(MIPpt);
	_cone_calib_pt.emplace_back(cone_calib.Pt());
	_cone_calib_Luca_pt.emplace_back(cone_calib_Luca.Pt());


	TLorentzVector cone_tc_calib;
	TLorentzVector cone_tc_calib_Luca;
	float MIPpt_tc = 0;

	for(unsigned int i_tc=0; i_tc<(*_cone_tc)[i_cone].size(); i_tc++){
	  int tc_index = (*_cone_tc)[i_cone][i_tc];
	  TLorentzVector tc;
	  tc.SetPtEtaPhiM(_tc_calib_pt[tc_index],(*_tc_eta)[tc_index],(*_tc_phi)[tc_index],0);
	  TLorentzVector tc_Luca;
	  tc_Luca.SetPtEtaPhiM(_tc_calib_Luca_pt[tc_index],(*_tc_eta)[tc_index],(*_tc_phi)[tc_index],0);
	  cone_tc_calib += tc;
	  cone_tc_calib_Luca += tc_Luca;
	  MIPpt_tc += _tc_MIPpt[tc_index];
	}

	_cone_tc_MIPpt.emplace_back(MIPpt_tc);
	_cone_tc_calib_pt.emplace_back(cone_tc_calib.Pt());
	_cone_tc_calib_Luca_pt.emplace_back(cone_tc_calib_Luca.Pt());
	
      }

    }

    tree_new->Fill();
    if(add_jet)
      tree_new2->Fill();


  }

  tree_new->Write();
  if(add_jet)
    tree_new2->Write();
  f_new->Close();


}
