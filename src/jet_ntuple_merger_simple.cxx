#include "jet_ntuple_merger_simple.h"
#include <time.h>
#include "interrupts.h"
jet_ntuple_merger_simple::jet_ntuple_merger_simple(){

}

int jet_ntuple_merger_simple::HGC_layer(const uint32_t subdet, const uint32_t layer) {

  int hgclayer = -1;
  if(subdet==3) hgclayer=layer;//EE
  else if(subdet==4) hgclayer=layer+28;//FH
  else if(subdet==5) hgclayer=layer+40;//BH

  return hgclayer;

}


//Compute energy-weighted mean of any variable X in the cluster

float jet_ntuple_merger_simple::meanX(const std::vector<std::pair<float,float> >& energy_X_tc) {

  float Etot = 0;
  float X_sum = 0;

  for(const auto& energy_X : energy_X_tc){

    X_sum += energy_X.first*energy_X.second;
    Etot += energy_X.first;

  }

  float X_mean = 0;
  if(Etot>0) X_mean = X_sum/Etot;
  return X_mean;

}




//Compute energy-weighted RMS of any variable X in the cluster

float jet_ntuple_merger_simple::sigmaXX(const std::vector<std::pair<float,float> >& energy_X_tc, const float X_cluster) {

  float Etot = 0;
  float deltaX2_sum = 0;

  for(const auto& energy_X : energy_X_tc){

    deltaX2_sum += energy_X.first * pow(energy_X.second - X_cluster,2);
    Etot += energy_X.first;

  }

  float X_MSE = 0;
  if (Etot>0) X_MSE=deltaX2_sum/Etot;
  float X_RMS=sqrt(X_MSE);
  return X_RMS;

}


//Compute energy-weighted RMS of any variable X in the cluster
//Extra care needed because of deltaPhi

float jet_ntuple_merger_simple::sigmaPhiPhi(const std::vector<std::pair<float,float> >& energy_phi_tc, const float phi_cluster) {

  float Etot = 0;
  float deltaphi2_sum = 0;

  for(const auto& energy_phi : energy_phi_tc){

    deltaphi2_sum += energy_phi.first * pow(helper.deltaPhi(energy_phi.second,phi_cluster),2);
    Etot += energy_phi.first;

  }

  float phi_MSE = 0;
  if (Etot>0) phi_MSE=deltaphi2_sum/Etot;
  float Spp=sqrt(phi_MSE);
  return Spp;

}

float jet_ntuple_merger_simple::calibrateInMipT(int hwPt, float eta, int subdet){

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



float jet_ntuple_merger_simple::calibrateMipTinGeV(float MIPpt, int HGClayer, TString calib_version){

  std::vector<float> dEdX_weights;
  if(calib_version == "nominal")
    dEdX_weights = dEdX_weights_nominal;
  else if(calib_version == "Luca_TrgLayer")
    dEdX_weights = dEdX_weights_Luca_TrgLayer;
  /* weight the amplitude by the absorber coefficient in GeV/mip */
  double trgCellEt = MIPpt * dEdX_weights.at(HGClayer);


  if(calib_version=="nominal" && HGClayer<=40) trgCellEt/=thickCorr;  
  
  return trgCellEt;

}







void jet_ntuple_merger_simple::add_jet(TString filein,  TString treename, TString filein_jet, TString treename_jet, TString fileout){

  catchSignals();
  
  TFile* f_new = new TFile(fileout, "RECREATE");

  TChain * tree = new TChain(treename);
  tree->Add(filein);
  Long64_t nentries = tree->GetEntries();
  std::cout<<"nentries="<<nentries<<std::endl;

  TChain * tree_jet = new TChain(treename_jet);
  tree_jet->Add(filein_jet);
  Long64_t nentries2 = tree_jet->GetEntries();
  if(nentries!=nentries2){
    std::cout<<"Inconsistent number of entries in two input files"<<std::endl;
    //return;
  }

  
  int _tc_n;
  //  int _cl_n;
  int _cl3d_n;



  std::vector<float> *_tc_eta;
  std::vector<float> *_tc_pt;
  std::vector<float> *_tc_phi;
  std::vector<float> *_tc_energy;
  std::vector<float> *_tc_z;
  std::vector<int> *_tc_layer;
  std::vector<int> *_tc_subdet;
  std::vector<unsigned int> *_tc_id;

  std::vector<float> *_cl3d_pt;
  std::vector<float> *_cl3d_eta;
  std::vector<float> *_cl3d_phi;
  std::vector<float> *_cl3d_energy;
  std::vector<unsigned int> *_cl3d_id;
  std::vector<int> *_cl3d_firstlayer;

  std::vector<float> *_jets_pt;
  std::vector<float> *_jets_eta;
  std::vector<float> *_jets_phi;
  std::vector<float> *_jets_energy;

  std::vector<std::vector<float> > *_jets_C3d_pt;
  std::vector<std::vector<float> > *_jets_C3d_eta;
  std::vector<std::vector<float> > *_jets_C3d_phi;
  std::vector<std::vector<float> > *_jets_C3d_energy;

  std::vector<std::vector<unsigned int> > *_cl3d_clusters_id;

  std::vector<int> *_gen_id;
  std::vector<int> *_gen_status;
  std::vector<float> *_gen_pt;
  std::vector<float> *_gen_eta;
  std::vector<float> *_gen_phi;
  std::vector<float> *_gen_energy;
  
  std::vector<float> *_genjet_pt;
  std::vector<float> *_genjet_eta;
  std::vector<float> *_genjet_phi;
  std::vector<float> *_genjet_energy;

  std::vector<float> *_gentau_vis_pt;
  std::vector<float> *_gentau_vis_eta;
  std::vector<float> *_gentau_vis_phi;
  std::vector<float> *_gentau_vis_energy;
      
  tree->SetBranchAddress("tc_n",     &_tc_n);
  tree->SetBranchAddress("cl3d_n",   &_cl3d_n);
  
  tree->SetBranchAddress("tc_eta",    &_tc_eta);
  tree->SetBranchAddress("tc_pt",    &_tc_pt);
  tree->SetBranchAddress("tc_phi",    &_tc_phi);
  tree->SetBranchAddress("tc_energy", &_tc_energy);
  tree->SetBranchAddress("tc_z",      &_tc_z);
  tree->SetBranchAddress("tc_layer",  &_tc_layer);
  tree->SetBranchAddress("tc_subdet", &_tc_subdet);
  tree->SetBranchAddress("tc_id",     &_tc_id);

  tree->SetBranchAddress("cl3d_pt",     &_cl3d_pt);
  tree->SetBranchAddress("cl3d_eta",    &_cl3d_eta);
  tree->SetBranchAddress("cl3d_phi",    &_cl3d_phi);
  tree->SetBranchAddress("cl3d_energy", &_cl3d_energy);
  tree->SetBranchAddress("cl3d_id",     &_cl3d_id);
  tree->SetBranchAddress("cl3d_firstlayer",    &_cl3d_firstlayer);

  tree->SetBranchAddress("cl3d_clusters_id",   &_cl3d_clusters_id);
  tree->SetBranchAddress("gen_pdgid",     &_gen_id);
  tree->SetBranchAddress("gen_status", &_gen_status);
  tree->SetBranchAddress("gen_pt",     &_gen_pt);
  tree->SetBranchAddress("gen_eta",    &_gen_eta);
  tree->SetBranchAddress("gen_phi",    &_gen_phi);
  tree->SetBranchAddress("gen_energy", &_gen_energy);
      
  tree->SetBranchAddress("genjet_pt",     &_genjet_pt);
  tree->SetBranchAddress("genjet_eta",    &_genjet_eta);
  tree->SetBranchAddress("genjet_phi",    &_genjet_phi);
  tree->SetBranchAddress("genjet_energy", &_genjet_energy);

  tree->SetBranchAddress("gentau_vis_pt",     &_gentau_vis_pt);
  tree->SetBranchAddress("gentau_vis_eta",    &_gentau_vis_eta);
  tree->SetBranchAddress("gentau_vis_phi",    &_gentau_vis_phi);
  tree->SetBranchAddress("gentau_vis_energy", &_gentau_vis_energy);


  tree->SetBranchStatus ("*",0);
  tree->SetBranchStatus("tc_n"     ,1);

  tree->SetBranchStatus("cl3d_n"   ,1);
  tree->SetBranchStatus("tc_eta"   ,1);
  tree->SetBranchStatus("tc_pt"   ,1);
  tree->SetBranchStatus("tc_phi"   ,1);
  tree->SetBranchStatus("tc_energy",1);
  tree->SetBranchStatus("tc_z"     ,1);
  tree->SetBranchStatus("tc_layer" ,1);
  tree->SetBranchStatus("tc_subdet",1);
  tree->SetBranchStatus("tc_id"    ,1);
  tree->SetBranchStatus("cl3d_pt"  ,1);
  tree->SetBranchStatus("cl3d_eta" ,1);


  tree->SetBranchStatus("cl3d_phi"    ,1);
  tree->SetBranchStatus("cl3d_energy" ,1);
  tree->SetBranchStatus("cl3d_id"     ,1);
  tree->SetBranchStatus("cl3d_firstlayer",1);
  tree->SetBranchStatus("cl3d_clusters_id",1);

  tree->SetBranchStatus("gen_pdgid",1);
  tree->SetBranchStatus("gen_status",1);
  tree->SetBranchStatus("gen_pt"   ,1);
  tree->SetBranchStatus("gen_eta"  ,1);
  tree->SetBranchStatus("gen_phi"  ,1);
  tree->SetBranchStatus("gen_energy",1);

  tree->SetBranchStatus("genjet_pt"     ,1);
  tree->SetBranchStatus("genjet_eta"    ,1);
  tree->SetBranchStatus("genjet_phi"    ,1);
  tree->SetBranchStatus("genjet_energy" ,1);

  tree->SetBranchStatus("gentau_vis_pt"    ,1);
  tree->SetBranchStatus("gentau_vis_eta"   ,1);
  tree->SetBranchStatus("gentau_vis_phi"   ,1);
  tree->SetBranchStatus("gentau_vis_energy",1);


  tree_jet->SetBranchAddress("jets_pt",     &_jets_pt);
  tree_jet->SetBranchAddress("jets_eta",    &_jets_eta);
  tree_jet->SetBranchAddress("jets_phi",    &_jets_phi);
  tree_jet->SetBranchAddress("jets_energy", &_jets_energy);

  tree_jet->SetBranchAddress("jets_C3d_pt",     &_jets_C3d_pt);
  tree_jet->SetBranchAddress("jets_C3d_eta",    &_jets_C3d_eta);
  tree_jet->SetBranchAddress("jets_C3d_phi",    &_jets_C3d_phi);
  tree_jet->SetBranchAddress("jets_C3d_energy", &_jets_C3d_energy);
    

  f_new->cd();
  TTree* tree_new = new TTree("HGCalTriggerNtupleJet","HGCalTriggerNtupleJet");
  tree_new->AddFriend(treename,filein);
  TString filejet_friend = "/vols/cms/snwebb/HGC_ntuples/" + filein_jet(29,filein_jet.Length());
  
  //New branches
  std::vector<int> _tc_HGClayer;//need
  std::vector<int> _cl_HGClayer;//need

  std::vector<int> _tc_cl;
  std::vector<int> _tc_cl3d;
  std::vector<int> _cl_cl3d;  
  std::vector<int> _tc_jet; //index of jet in which tc included
  std::vector<int> _cl_jet; //index of jet in which cl included
  std::vector<int> _cl3d_jet; //index of jet in which cl3d included

  std::vector<std::vector<int> > _cl_cells;
  std::vector<std::vector<int> > _cl3d_clusters;

  int _jets_n;
  std::vector<int> _jets_ncl3d;
  std::vector<std::vector<int> > _jets_cl3d; // list of cl3d included in jet
  std::vector<std::vector<unsigned int> > _jets_cl3d_id;

  std::vector<float> _jets_mipPt;
  std::vector<float> _jets_seetot;
  std::vector<float> _jets_spptot;
  std::vector<float> _jets_srrtot;
  std::vector<float> _jets_firstlayer_avg;
  std::vector<std::vector<float> > _layer_jets_energy_fraction; //layer_jets_energy_fraction[i][j] = fraction of jet j energy included up to layer i
  std::vector<float> _jets_Fisher_VBF;

  std::vector<float> _jets_PU_subtr_cone_C3D;
  std::vector<float> _jets_PU_subtr_cone_tc;
  std::vector<float> _jets_PU_subtr_cone_GEO_C3D;

  bool _isVBF;
  std::vector<int> _VBF_parton_gen;
  std::vector<int> _VBF_parton_genjet;
  std::vector<int> _VBF_parton_jets;

  std::vector<int> _gentau_jets;

  std::vector<float> _jets_clean_pt;
  std::vector<float> _jets_clean_eta;
  std::vector<float> _jets_clean_phi;
  std::vector<float> _jets_clean_energy;

  std::vector<int> _num_seeds_in_jet;

  tree_new->Branch("tc_HGClayer",     &_tc_HGClayer);    //need
  tree_new->Branch("cl_HGClayer",     &_cl_HGClayer);    //need

  tree_new->Branch("jets_mipPt", &_jets_mipPt);
  tree_new->Branch("jets_seetot", &_jets_seetot);
  tree_new->Branch("jets_spptot", &_jets_spptot);
  tree_new->Branch("jets_srrtot", &_jets_srrtot);
  tree_new->Branch("jets_firstlayer_avg", &_jets_firstlayer_avg);
  tree_new->Branch("layer_jets_energy_fraction", &_layer_jets_energy_fraction);
  tree_new->Branch("jets_Fisher_VBF", &_jets_Fisher_VBF);

  tree_new->Branch("jets_PU_subtr_cone_C3D", &_jets_PU_subtr_cone_C3D);
  tree_new->Branch("jets_PU_subtr_cone_tc", &_jets_PU_subtr_cone_tc);
  tree_new->Branch("jets_PU_subtr_cone_GEO_C3D", &_jets_PU_subtr_cone_GEO_C3D);

  tree_new->Branch("isVBF", &_isVBF, "isVBF/O");
  tree_new->Branch("VBF_parton_gen", &_VBF_parton_gen);
  tree_new->Branch("VBF_parton_genjet", &_VBF_parton_genjet);
  tree_new->Branch("VBF_parton_jets", &_VBF_parton_jets);

  tree_new->Branch("gentau_jets", &_gentau_jets);

  tree_new->Branch("jets_pt", &_jets_pt);
  tree_new->Branch("jets_eta", &_jets_eta);
  tree_new->Branch("jets_phi", &_jets_phi);
  tree_new->Branch("jets_energy", &_jets_energy);

  tree_new->Branch("num_seeds_in_jet", &_num_seeds_in_jet);
  
  TFile* f_PU_cone_eta = TFile::Open("PU_cone_vs_eta_20190121-3.root");
  TProfile* prof_cone_tc = (TProfile*)f_PU_cone_eta->Get("prof_cone_tc");
  TProfile* prof_cone_C3D = (TProfile*)f_PU_cone_eta->Get("prof_cone_C3D");
  prof_cone_tc->SetDirectory(0);
  prof_cone_C3D->SetDirectory(0);
  f_PU_cone_eta->Close();

  TFile* f_PU_cone_eta_GEO = TFile::Open("PU_cone_vs_eta_C2D_dR.root");
  TProfile* prof_cone_GEO_C3D = (TProfile*)f_PU_cone_eta_GEO->Get("prof_cone_C3D");
  prof_cone_GEO_C3D->SetDirectory(0);
  f_PU_cone_eta_GEO->Close();

  int N = std::min(nentries,nentries2);
  for(int i=0;i<N;i++){

    if(i%10==0)
      std::cout<<"i="<<i<<std::endl;

    _tc_n = 0;
    _cl3d_n = 0;
    _tc_eta = 0;
    _tc_pt = 0;
    _tc_phi = 0;
    _tc_energy = 0;
    _tc_z = 0;
    _tc_layer = 0;
    _tc_subdet = 0;
    _tc_id = 0;

    _cl3d_pt = 0;
    _cl3d_eta = 0;
    _cl3d_phi = 0;
    _cl3d_energy = 0;
    _cl3d_id = 0;
    _cl3d_firstlayer = 0;
    _cl3d_clusters_id = 0;

    _jets_pt = 0;
    _jets_eta = 0;
    _jets_phi = 0;
    _jets_energy = 0;  
    
    _jets_C3d_pt = 0;
    _jets_C3d_eta = 0;
    _jets_C3d_phi = 0;
    _jets_C3d_energy = 0; 

    _gen_id = 0;
    _gen_status = 0;
    _gen_pt = 0;
    _gen_eta = 0;
    _gen_phi = 0;
    _gen_energy = 0;
    
    _genjet_pt = 0;
    _genjet_eta = 0;
    _genjet_phi = 0;
    _genjet_energy = 0;

    _gentau_vis_pt = 0;
    _gentau_vis_eta = 0;
    _gentau_vis_phi = 0;
    _gentau_vis_energy = 0;
    
    _jets_n = 0;

    //New Branches
 
    _tc_HGClayer.clear();
    _cl_HGClayer.clear();

    _tc_cl.clear();
    _tc_cl3d.clear();
    _cl_cl3d.clear();  

    _tc_jet.clear();
    _cl_jet.clear();
    _cl3d_jet.clear();
    _cl3d_clusters.clear();

    _jets_ncl3d.clear();
    _jets_cl3d.clear();
    _jets_cl3d_id.clear();

    _jets_mipPt.clear();
    _jets_seetot.clear();
    _jets_spptot.clear();
    _jets_srrtot.clear();
    _jets_firstlayer_avg.clear();
    _layer_jets_energy_fraction.clear();
    _jets_Fisher_VBF.clear();

    _jets_PU_subtr_cone_C3D.clear();   
    _jets_PU_subtr_cone_tc.clear();   
    _jets_PU_subtr_cone_GEO_C3D.clear(); 

    _VBF_parton_gen.clear();
    _VBF_parton_genjet.clear();
    _VBF_parton_jets.clear();

    _gentau_jets.clear();
    _num_seeds_in_jet.clear();

    tree->GetEntry(i);
    tree_jet->GetEntry(i);

    _jets_n = (*_jets_pt).size();   
    
    std::map<unsigned int, unsigned int> tc_map; //First ID, Second index
    std::map<unsigned int, unsigned int> cl_map; //First ID, Second index
    std::map<unsigned int, unsigned int> cl3d_map; //First ID, Second index

    for(int i_tc=0; i_tc<_tc_n; i_tc++){      

      int HGClayer = HGC_layer( (*_tc_subdet)[i_tc], (*_tc_layer)[i_tc] );
      _tc_HGClayer.emplace_back(HGClayer);          
      tc_map[(*_tc_id)[i_tc]] = i_tc;

    }

    for(unsigned int i_c3d=0; i_c3d<(*_cl3d_clusters_id).size(); i_c3d++){

      cl3d_map[(*_cl3d_id)[i_c3d]] = i_c3d;

    }    

    _cl3d_clusters.resize((*_cl3d_clusters_id).size());
    for(unsigned int i_cl3d=0; i_cl3d<(*_cl3d_clusters_id).size(); i_cl3d++){
      for(unsigned int i_cl=0; i_cl<(*_cl3d_clusters_id)[i_cl3d].size(); i_cl++){
	_cl3d_clusters[i_cl3d].push_back(cl_map[(*_cl3d_clusters_id)[i_cl3d][i_cl]]);
      }
    }

    _jets_cl3d_id.resize(_jets_n);
    _jets_cl3d.resize(_jets_n);
    //Clusters shower-shape variables

    for(unsigned int i_cl3d=0; i_cl3d<(_cl3d_clusters).size();i_cl3d++){

      std::vector<std::pair<float,float> > energy_r_tc;
      std::vector<std::pair<float,float> > energy_z_tc;
      
    }

    //Jet shower-shape variables
    _layer_jets_energy_fraction.resize(53);

    for(int i_jet=0; i_jet<_jets_n; i_jet++){

      std::vector<std::pair<float,float> > energy_eta_c3d;
      std::vector<std::pair<float,float> > energy_phi_c3d;
      std::vector<std::pair<float,float> > energy_r_c3d;
      std::vector<std::pair<float,float> > energy_firstlayer_c3d;

      std::map<int, float> layer_mipPt;
      float tot_mipPt = 0.;    
    
      float jet_See_tot = sigmaXX(energy_eta_c3d,(*_jets_eta)[i_jet]);
      float jet_Spp_tot = sigmaXX(energy_phi_c3d,(*_jets_phi)[i_jet]);
      float jet_Srr_tot = sigmaXX(energy_r_c3d,1/abs(TMath::ASinH((*_jets_eta)[i_jet])));
      float jet_firstlayer_avg = meanX(energy_firstlayer_c3d);

      _jets_mipPt.push_back(tot_mipPt);
      _jets_seetot.push_back(jet_See_tot);
      _jets_spptot.push_back(jet_Spp_tot);
      _jets_srrtot.push_back(jet_Srr_tot);   
      _jets_firstlayer_avg.push_back(jet_firstlayer_avg);

      _layer_jets_energy_fraction[0].push_back({0});

      for(unsigned int i_layer=1;i_layer<53;i_layer++){

	float fraction = _layer_jets_energy_fraction[i_layer-1].back() + layer_mipPt[i_layer]/tot_mipPt;
	_layer_jets_energy_fraction[i_layer].push_back(fraction);
      }
      
      int i_bin = prof_cone_tc->FindBin(fabs((*_jets_eta)[i_jet]));
      _jets_PU_subtr_cone_C3D.emplace_back(prof_cone_C3D->GetBinContent(i_bin));      
      _jets_PU_subtr_cone_tc.emplace_back(prof_cone_tc->GetBinContent(i_bin));
      _jets_PU_subtr_cone_GEO_C3D.emplace_back(prof_cone_GEO_C3D->GetBinContent(i_bin));        

      float Fisher = 0;

      for(unsigned int k=0; k<38; k++){
	int k_layer = -1;
	if(k<14) k_layer = 2*k+1;
	else k_layer = k+15;	
	Fisher+=weights_Fisher[k]*layer_mipPt[k_layer]/tot_mipPt;
      }

      _jets_Fisher_VBF.push_back(Fisher);      


    }

    _isVBF = true;

    for(unsigned int i_gen=0; i_gen<(*_gen_id).size(); i_gen++){
      if(abs((*_gen_id)[i_gen])==21 && (*_gen_status)[i_gen]==21) //Gluon splitting in initial partons
	_isVBF = false;
      if(abs((*_gen_id)[i_gen])<6 && (*_gen_status)[i_gen]==23)
	_VBF_parton_gen.emplace_back(i_gen);
    }

    for(unsigned int i_VBF=0; i_VBF<_VBF_parton_gen.size(); i_VBF++){

      TLorentzVector VBF_parton;
      int i_gen = _VBF_parton_gen[i_VBF];
      VBF_parton.SetPtEtaPhiE((*_gen_pt)[i_gen], (*_gen_eta)[i_gen], (*_gen_phi)[i_gen], (*_gen_energy)[i_gen]);     

      float dR_min = -1.;
      int i_VBF_genjet = -1;
      
      for(unsigned int i_genjet=0; i_genjet<(*_genjet_pt).size(); i_genjet++){
	TLorentzVector genjet;
	genjet.SetPtEtaPhiE((*_genjet_pt)[i_genjet],(*_genjet_eta)[i_genjet],(*_genjet_phi)[i_genjet],(*_genjet_energy)[i_genjet]);
	float dR = genjet.DeltaR(VBF_parton);
	if((dR_min<0 && dR<0.5) || dR<dR_min){
	  dR_min = dR;
	  i_VBF_genjet = i_genjet;
	}
      }

      _VBF_parton_genjet.emplace_back(i_VBF_genjet);
      TLorentzVector VBF_genjet;
      VBF_genjet.SetPtEtaPhiE((*_genjet_pt)[i_VBF_genjet],(*_genjet_eta)[i_VBF_genjet],(*_genjet_phi)[i_VBF_genjet],(*_genjet_energy)[i_VBF_genjet]);
      
      dR_min = -1.;
      int i_VBF_jet = -1;
      
      for(unsigned int i_jet=0; i_jet<(*_jets_pt).size(); i_jet++){
	TLorentzVector jet;
	jet.SetPtEtaPhiE((*_jets_pt)[i_jet],(*_jets_eta)[i_jet],(*_jets_phi)[i_jet],(*_jets_energy)[i_jet]);	
	float dR = jet.DeltaR(VBF_genjet);
	if((dR_min<0 && dR<0.5) || dR<dR_min){
	  dR_min = dR;
	  i_VBF_jet = i_jet;
	}
      }            					     

      _VBF_parton_jets.emplace_back(i_VBF_jet);
      
    }


    //Find number of seeds in a jet
    
    for(unsigned int i_jet=0; i_jet<(*_jets_pt).size(); i_jet++){
      int num_seeds = 0;
      
      TLorentzVector jet;
      jet.SetPtEtaPhiE((*_jets_pt)[i_jet],(*_jets_eta)[i_jet],(*_jets_phi)[i_jet],(*_jets_energy)[i_jet]);	
            
      for(unsigned int i_cl3d=0; i_cl3d<(*_cl3d_pt).size(); i_cl3d++){
	TLorentzVector cl3d;
	cl3d.SetPtEtaPhiE((*_cl3d_pt)[i_cl3d], (*_cl3d_eta)[i_cl3d], (*_cl3d_phi)[i_cl3d], (*_cl3d_energy)[i_cl3d]);     
	
	float dR = jet.DeltaR(cl3d);
	if( dR<0.2 ){
	  num_seeds++;
	}
      }            					     
     
      _num_seeds_in_jet.emplace_back(num_seeds);
      
    }


    for(unsigned int i_gen=0; i_gen<(*_gentau_vis_pt).size(); i_gen++){

      TLorentzVector gentau;
      gentau.SetPtEtaPhiE((*_gentau_vis_pt)[i_gen], (*_gentau_vis_eta)[i_gen], (*_gentau_vis_phi)[i_gen], (*_gentau_vis_energy)[i_gen]);     

      float dR_min = -1.;
      int i_gentau_jet = -1;
      
      for(unsigned int i_jet=0; i_jet<(*_jets_pt).size(); i_jet++){
	TLorentzVector jet;
	jet.SetPtEtaPhiE((*_jets_pt)[i_jet],(*_jets_eta)[i_jet],(*_jets_phi)[i_jet],(*_jets_energy)[i_jet]);	
	float dR = jet.DeltaR(gentau);
	if((dR_min<0 && dR<0.3) || dR<dR_min){
	  dR_min = dR;
	  i_gentau_jet = i_jet;
	}
      }            					     
      _gentau_jets.emplace_back(i_gentau_jet);
      
    }
  
    delete _cl3d_clusters_id;
    _cl3d_clusters_id = 0;

    delete _jets_C3d_pt;        
    delete _jets_C3d_eta;        
    delete _jets_C3d_phi;        
    delete _jets_C3d_energy;        
    _jets_C3d_pt = 0  ;        
    _jets_C3d_eta = 0 ;        
    _jets_C3d_phi = 0 ;        
    _jets_C3d_energy = 0 ;        
    
    tree_new->Fill();

    if ( continueJob == false ) break;
  }

  f_new->cd();
  tree_new->Write();
  f_new->Close();
  f_new->Delete();

  return;


}


void jet_ntuple_merger_simple::test(){

  TString filein="root://cms-xrd-global.cern.ch//store/user/tstreble/VBF_HToInvisible_M125_14TeV_powheg_pythia8/VBF_Hinv_93X_PU0_dRC2D_JetPU0cal_18_01_08/180108_163440/0000/ntuple_12.root";
  TString treename="hgcalTriggerNtuplizer/HGCalTriggerNtuple";
  TString filein_jet="/data_CMS/cms/strebler/HGC/VBF_Hinv_PU0_C2D_dR_JetPU0cal/jet_ntuples/ntuple_jet_12.root";
  TString treename_jet="jets";
  TString fileout="test_jet.root";

  add_jet( filein, treename, filein_jet, treename_jet, fileout);


}

