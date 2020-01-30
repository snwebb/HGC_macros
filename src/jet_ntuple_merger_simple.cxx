#include "jet_ntuple_merger_simple.h"
#include <time.h>
#include "interrupts.h"
jet_ntuple_merger_simple::jet_ntuple_merger_simple(){

}


void jet_ntuple_merger_simple::add_jet(TString filein,  TString treename, TString filein_jet, TString treename_jet, TString fileout,  TString treenameout){

  catchSignals();
  
  TFile* f_new = new TFile(fileout, "RECREATE");

  TChain * tree = new TChain(treename);
  std::cout << treename << std::endl;
  std::cout << filein << std::endl;
  tree->Add(filein);
  Long64_t nentries = tree->GetEntries();
  std::cout<<"nentries="<<nentries<<std::endl;

  //  TChain * tree_reference = new TChain("Fp8Threshold2p0Ref2dRef3dGenmatchGenclustersntuple/HGCalTriggerNtuple");
  //  tree_reference->Add(filein);
  //  tree->AddFriend(tree_reference);

  TChain * tree_jet = new TChain(treename_jet);
  tree_jet->Add(filein_jet);
  Long64_t nentries2 = tree_jet->GetEntries();
  if(nentries!=nentries2){
    std::cout<<"Inconsistent number of entries in two input files"<<std::endl;
    //return;
  }

  //options
  bool add_genjet_info = false;

  
  int _cl3d_n;
  float _dijet_mass;
  float _dijet_mass_VBF;

  std::vector<float> *_cl3d_pt;
  std::vector<float> *_cl3d_eta;
  std::vector<float> *_cl3d_phi;
  std::vector<float> *_cl3d_energy;
  std::vector<unsigned int> *_cl3d_id;

  std::vector<float> *_jets_pt;
  std::vector<float> *_jets_eta;
  std::vector<float> *_jets_phi;
  std::vector<float> *_jets_energy;

  std::vector<unsigned int> *_jets_n_cl;
  std::vector<unsigned int> *_jets_n_tcs;
  std::vector<float> *_jets_firstfrac;
  std::vector<float> *_jets_coreenergyratio;
  std::vector<float> *_jets_riso;
  std::vector<float> *_jets_hoe;
  std::vector<float> *_jets_maxlayer;
  std::vector<float> *_jets_firstlayer;
  std::vector<float> *_jets_coreshowerlength_sum;

  std::vector<float> *_jets_srrsum;
  std::vector<float> *_jets_srrjet;
  std::vector<float> *_jets_srr_best;
  std::vector<float> *_jets_srr_paul;
  std::vector<float> *_jets_srr_max_sum;
  std::vector<float> *_jets_srr_max_paul;

  std::vector<float> *_jets_sppsum;
  std::vector<float> *_jets_sppjet;
  std::vector<float> *_jets_spp_best;
  std::vector<float> *_jets_spp_paul;
  std::vector<float> *_jets_spp_max_sum;
  std::vector<float> *_jets_spp_max_paul;

  std::vector<float> *_jets_szzjet;

  std::vector<float> * _jets_meanz_mean;   
  std::vector<float> * _jets_meanz_max;
  std::vector<float> * _jets_layer10_mean;
  std::vector<float> * _jets_layer10_max;
  std::vector<float> * _jets_layer50_mean;
  std::vector<float> * _jets_layer50_max;
  std::vector<float> * _jets_layer90_mean;
  std::vector<float> * _jets_layer90_max;
  std::vector<float> * _jets_ntc67_mean;
  std::vector<float> * _jets_ntc67_max;
  std::vector<float> * _jets_ntc90_mean;
  std::vector<float> * _jets_ntc90_max;

  std::vector<std::vector<int> > *_gen_daughters;
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

  TBranch        *b_gen_daughters;   //!

  tree->SetBranchAddress("cl3d_n",   &_cl3d_n);
  tree->SetBranchAddress("cl3d_pt",     &_cl3d_pt);
  tree->SetBranchAddress("cl3d_eta",    &_cl3d_eta);
  tree->SetBranchAddress("cl3d_phi",    &_cl3d_phi);
  tree->SetBranchAddress("cl3d_energy", &_cl3d_energy);
  tree->SetBranchAddress("cl3d_id",     &_cl3d_id);
  tree->SetBranchAddress("gen_pdgid",     &_gen_id);
  tree->SetBranchAddress("gen_status", &_gen_status);
  tree->SetBranchAddress("gen_pt",     &_gen_pt);
  tree->SetBranchAddress("gen_eta",    &_gen_eta);
  tree->SetBranchAddress("gen_phi",    &_gen_phi);
  tree->SetBranchAddress("gen_energy", &_gen_energy);
  tree->SetBranchAddress("gen_daughters", &_gen_daughters, &b_gen_daughters);


  tree->SetBranchAddress("genjet_pt",     &_genjet_pt);
  tree->SetBranchAddress("genjet_eta",    &_genjet_eta);
  tree->SetBranchAddress("genjet_phi",    &_genjet_phi);
  tree->SetBranchAddress("genjet_energy", &_genjet_energy);


  tree->SetBranchStatus ("*",0);
  tree->SetBranchStatus("cl3d_n"   ,1);
  tree->SetBranchStatus("cl3d_pt"  ,1);
  tree->SetBranchStatus("cl3d_eta" ,1);
  tree->SetBranchStatus("cl3d_phi"    ,1);
  tree->SetBranchStatus("cl3d_energy" ,1);
  tree->SetBranchStatus("cl3d_id"     ,1);

  tree->SetBranchStatus("gen_pdgid",1);
  tree->SetBranchStatus("gen_status",1);
  tree->SetBranchStatus("gen_pt"   ,1);
  tree->SetBranchStatus("gen_eta"  ,1);
  tree->SetBranchStatus("gen_phi"  ,1);
  tree->SetBranchStatus("gen_energy",1);
  tree->SetBranchStatus("gen_daughters",1);

  tree->SetBranchStatus("genjet_pt"     ,1);
  tree->SetBranchStatus("genjet_eta"    ,1);
  tree->SetBranchStatus("genjet_phi"    ,1);
  tree->SetBranchStatus("genjet_energy" ,1);


  tree_jet->SetBranchAddress("jets_pt",     &_jets_pt);
  tree_jet->SetBranchAddress("jets_eta",    &_jets_eta);
  tree_jet->SetBranchAddress("jets_phi",    &_jets_phi);
  tree_jet->SetBranchAddress("jets_energy", &_jets_energy);
  tree_jet->SetBranchAddress("jets_n_cl", &_jets_n_cl);
  tree_jet->SetBranchAddress("jets_n_tcs", &_jets_n_tcs);

  tree_jet->SetBranchAddress("jets_srrsum", &_jets_srrsum);
  tree_jet->SetBranchAddress("jets_srrjet", &_jets_srrjet);
  tree_jet->SetBranchAddress("jets_srr_best", &_jets_srr_best);
  tree_jet->SetBranchAddress("jets_srr_paul", &_jets_srr_paul);
  tree_jet->SetBranchAddress("jets_srr_max_sum", &_jets_srr_max_sum);
  tree_jet->SetBranchAddress("jets_srr_max_paul", &_jets_srr_max_paul);

  tree_jet->SetBranchAddress("jets_sppsum", &_jets_sppsum);
  tree_jet->SetBranchAddress("jets_sppjet", &_jets_sppjet);
  tree_jet->SetBranchAddress("jets_spp_best", &_jets_spp_best);
  tree_jet->SetBranchAddress("jets_spp_paul", &_jets_spp_paul);
  tree_jet->SetBranchAddress("jets_spp_max_sum", &_jets_spp_max_sum);
  tree_jet->SetBranchAddress("jets_spp_max_paul", &_jets_spp_max_paul);

  tree_jet->SetBranchAddress("jets_szzjet", &_jets_szzjet);

  tree_jet->SetBranchAddress("jets_firstfrac", &_jets_firstfrac);
  tree_jet->SetBranchAddress("jets_coreenergyratio", &_jets_coreenergyratio);
  tree_jet->SetBranchAddress("jets_riso", &_jets_riso);
  tree_jet->SetBranchAddress("jets_hoe", &_jets_hoe);
  tree_jet->SetBranchAddress("jets_maxlayer", &_jets_maxlayer);
  tree_jet->SetBranchAddress("jets_firstlayer", &_jets_firstlayer);
  tree_jet->SetBranchAddress("jets_coreshowerlength_sum", &_jets_coreshowerlength_sum);


  tree_jet->SetBranchAddress("jets_meanz_mean" , &_jets_meanz_mean);   
  tree_jet->SetBranchAddress("jets_meanz_max" , &_jets_meanz_max);	 
  tree_jet->SetBranchAddress("jets_layer10_mean" , &_jets_layer10_mean); 
  tree_jet->SetBranchAddress("jets_layer10_max" , &_jets_layer10_max);  
  tree_jet->SetBranchAddress("jets_layer50_mean" , &_jets_layer50_mean); 
  tree_jet->SetBranchAddress("jets_layer50_max" , &_jets_layer50_max);  
  tree_jet->SetBranchAddress("jets_layer90_mean" , &_jets_layer90_mean); 
  tree_jet->SetBranchAddress("jets_layer90_max" , &_jets_layer90_max);  
  tree_jet->SetBranchAddress("jets_ntc67_mean" , &_jets_ntc67_mean);   
  tree_jet->SetBranchAddress("jets_ntc67_max" , &_jets_ntc67_max);	 
  tree_jet->SetBranchAddress("jets_ntc90_mean" , &_jets_ntc90_mean);   
  tree_jet->SetBranchAddress("jets_ntc90_max" , &_jets_ntc90_max);	     


    
  f_new->cd();
  TTree* tree_new = new TTree(treenameout,treenameout);


  tree_new->AddFriend(treename,filein);

  //New branches
  std::vector<std::vector<int> > _cl_cells;

  std::vector<float> _jets_PU_subtr_cone_C3D;
  std::vector<float> _jets_PU_subtr_cone_tc;
  std::vector<float> _jets_PU_subtr_cone_GEO_C3D;

  bool _isVBF;
  bool _isHGG = false;
  std::vector<int> _VBF_parton_gen;
  std::vector<int> _VBF_parton_genjet;
  std::vector<int> _VBF_parton_jets;

  std::vector<int> _Pion_gen;
  std::vector<int> _Pion_genjet;
  std::vector<int> _Pion_jets;

  std::vector<int> _Tau_gen;
  std::vector<int> _Tau_genjet;
  std::vector<int> _Tau_jets;

  std::vector<int> _Photon_gen;
  // std::vector<int> _Photon_genjet;
  // std::vector<int> _Photon_jets;
  std::vector<int> _Higgs_gen;

  std::vector<bool> _Tau_overlap;
  std::vector<bool> _Photon_overlap;

  std::vector<int> _num_seeds_in_jet;

  tree_new->Branch("jets_PU_subtr_cone_C3D", &_jets_PU_subtr_cone_C3D);
  tree_new->Branch("jets_PU_subtr_cone_tc", &_jets_PU_subtr_cone_tc);
  tree_new->Branch("jets_PU_subtr_cone_GEO_C3D", &_jets_PU_subtr_cone_GEO_C3D);

  if ( add_genjet_info ){
    tree_new->Branch("genjet_pt", &_genjet_pt);
    tree_new->Branch("genjet_eta", &_genjet_eta);
    tree_new->Branch("genjet_phi", &_genjet_phi);
    tree_new->Branch("genjet_energy", &_genjet_energy);
  }




  tree_new->Branch("isVBF", &_isVBF, "isVBF/O");
  tree_new->Branch("VBF_parton_gen", &_VBF_parton_gen);
  tree_new->Branch("VBF_parton_genjet", &_VBF_parton_genjet);
  tree_new->Branch("VBF_parton_jets", &_VBF_parton_jets);

  tree_new->Branch("Pion_genjet", &_Pion_genjet);
  tree_new->Branch("Pion_jets", &_Pion_jets);

  //  tree_new->Branch("Tau_genjet", &_Tau_genjet);
  //  tree_new->Branch("Tau_jets", &_Tau_jets);
  tree_new->Branch("Tau_overlap", &_Tau_overlap);
  tree_new->Branch("Photon_overlap", &_Photon_overlap);

  // tree_new->Branch("Photon_genjet", &_Photon_genjet);
    // tree_new->Branch("Photon_jets", &_Photon_jets);
    // tree_new->Branch("Photon_gen", &_Photon_gen);
  // tree_new->Branch("Photon_overlap", &_Photon_overlap);

  tree_new->Branch("jets_pt", &_jets_pt);
  tree_new->Branch("jets_eta", &_jets_eta);
  tree_new->Branch("jets_phi", &_jets_phi);
  tree_new->Branch("jets_energy", &_jets_energy);
  tree_new->Branch("jets_n_cl", &_jets_n_cl);
  tree_new->Branch("jets_n_tcs", &_jets_n_tcs);

  tree_new->Branch("jets_srrsum", &_jets_srrsum);
  tree_new->Branch("jets_srrjet", &_jets_srrjet);
  tree_new->Branch("jets_srr_best", &_jets_srr_best);
  tree_new->Branch("jets_srr_paul", &_jets_srr_paul);

  tree_new->Branch("jets_sppsum", &_jets_sppsum);
  tree_new->Branch("jets_sppjet", &_jets_sppjet);
  tree_new->Branch("jets_spp_best", &_jets_spp_best);
  tree_new->Branch("jets_spp_paul", &_jets_spp_paul);

  tree_new->Branch("jets_szzjet", &_jets_szzjet);
  tree_new->Branch("jets_srr_max_sum", &_jets_srr_max_sum);
  tree_new->Branch("jets_srr_max_paul", &_jets_srr_max_paul);
  tree_new->Branch("jets_spp_max_sum", &_jets_spp_max_sum);
  tree_new->Branch("jets_spp_max_paul", &_jets_spp_max_paul);


  tree_new->Branch("jets_firstfrac", &_jets_firstfrac);
  tree_new->Branch("jets_coreenergyratio", &_jets_coreenergyratio);
  tree_new->Branch("jets_riso", &_jets_riso);
  tree_new->Branch("jets_hoe", &_jets_hoe);

  tree_new->Branch("jets_maxlayer", &_jets_maxlayer);
  tree_new->Branch("jets_firstlayer", &_jets_firstlayer);
  tree_new->Branch("jets_coreshowerlength_sum", &_jets_coreshowerlength_sum);

  tree_new->Branch("dijet_mass", &_dijet_mass);
  tree_new->Branch("dijet_mass_VBF", &_dijet_mass_VBF);



  tree_new->Branch("jets_meanz_mean" , &_jets_meanz_mean);   
  tree_new->Branch("jets_meanz_max" , &_jets_meanz_max);	 
  tree_new->Branch("jets_layer10_mean" , &_jets_layer10_mean); 
  tree_new->Branch("jets_layer10_max" , &_jets_layer10_max);  
  tree_new->Branch("jets_layer50_mean" , &_jets_layer50_mean); 
  tree_new->Branch("jets_layer50_max" , &_jets_layer50_max);  
  tree_new->Branch("jets_layer90_mean" , &_jets_layer90_mean); 
  tree_new->Branch("jets_layer90_max" , &_jets_layer90_max);  
  tree_new->Branch("jets_ntc67_mean" , &_jets_ntc67_mean);   
  tree_new->Branch("jets_ntc67_max" , &_jets_ntc67_max);	 
  tree_new->Branch("jets_ntc90_mean" , &_jets_ntc90_mean);   
  tree_new->Branch("jets_ntc90_max" , &_jets_ntc90_max);	     



  bool include_num_seeds_jet = false;
  if ( include_num_seeds_jet )
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

    _cl3d_n = 0;
    _dijet_mass = 0;
    _dijet_mass_VBF = 0;

    _cl3d_pt = 0;
    _cl3d_eta = 0;
    _cl3d_phi = 0;
    _cl3d_energy = 0;
    _cl3d_id = 0;

    _jets_pt = 0;
    _jets_eta = 0;
    _jets_phi = 0;
    _jets_energy = 0;  
    _jets_n_cl = 0;  
    _jets_n_tcs = 0;  
    _jets_srrsum = 0;  
    _jets_srrjet = 0;  
    _jets_srr_best = 0;  
    _jets_srr_paul = 0;  

    _jets_sppsum = 0;  
    _jets_sppjet = 0;  
    _jets_spp_best = 0;  
    _jets_spp_paul = 0;  

    _jets_szzjet = 0;
    _jets_srr_max_sum = 0;
    _jets_srr_max_paul = 0;
    _jets_spp_max_sum = 0;
    _jets_spp_max_paul = 0;

    _jets_firstfrac = 0;  
    _jets_coreenergyratio = 0;  
    _jets_riso = 0;  
    _jets_hoe = 0;  

    _jets_maxlayer = 0;  
    _jets_firstlayer = 0;  
    _jets_coreshowerlength_sum = 0;   
    
    _jets_meanz_mean = 0;   
    _jets_meanz_max = 0;
    _jets_layer10_mean = 0;
    _jets_layer10_max = 0;
    _jets_layer50_mean = 0;
    _jets_layer50_max = 0;
    _jets_layer90_mean = 0;
    _jets_layer90_max = 0;
    _jets_ntc67_mean = 0;
    _jets_ntc67_max = 0;
    _jets_ntc90_mean = 0;
    _jets_ntc90_max = 0;

    _gen_id = 0;
    _gen_status = 0;
    _gen_pt = 0;
    _gen_eta = 0;
    _gen_phi = 0;
    _gen_energy = 0;
    _gen_daughters = 0;

    _genjet_pt = 0;
    _genjet_eta = 0;
    _genjet_phi = 0;
    _genjet_energy = 0;
    
    //New Branches
 
    _jets_PU_subtr_cone_C3D.clear();   
    _jets_PU_subtr_cone_tc.clear();   
    _jets_PU_subtr_cone_GEO_C3D.clear(); 

    _VBF_parton_gen.clear();
    _VBF_parton_genjet.clear();
    _VBF_parton_jets.clear();

    _Pion_gen.clear();
    _Pion_genjet.clear();
    _Pion_jets.clear();

    _Tau_gen.clear();
    _Tau_genjet.clear();
    _Tau_jets.clear();
    _Tau_overlap.clear();

    _Photon_gen.clear();
    // _Photon_genjet.clear();
    // _Photon_jets.clear();
    _Photon_overlap.clear();

    if (include_num_seeds_jet) _num_seeds_in_jet.clear();

    _Higgs_gen.clear();

    tree->GetEntry(i);
    tree_jet->GetEntry(i);


    //Find gen particles

    _isVBF = true;

    for(unsigned int i_gen=0; i_gen<(*_gen_id).size(); i_gen++){
      if(abs((*_gen_id)[i_gen])==21 && (*_gen_status)[i_gen]==21) //Gluon splitting in initial partons
	_isVBF = false;
      if(abs((*_gen_id)[i_gen])<6 && (*_gen_status)[i_gen]==23)
	_VBF_parton_gen.emplace_back(i_gen);
      if(abs((*_gen_id)[i_gen])==211 && (*_gen_status)[i_gen]==1)
	_Pion_gen.emplace_back(i_gen);
      if(abs((*_gen_id)[i_gen])==15 && (*_gen_status)[i_gen]==23)
	_Tau_gen.emplace_back(i_gen);
      if(abs((*_gen_id)[i_gen])==25 && (*_gen_status)[i_gen]==62){
      	_Higgs_gen.emplace_back(i_gen);
      }
    }

    //Photon
    for(unsigned int i_Higgs=0; i_Higgs<_Higgs_gen.size(); i_Higgs++){      
     for(unsigned int i_daught=0; i_daught<(*_gen_daughters)[_Higgs_gen[i_Higgs]].size(); i_daught++){
    	int id = (*_gen_daughters)[_Higgs_gen[i_Higgs]].at(i_daught);
    	if(abs((*_gen_id)[id])==22 && (*_gen_status)[id]==1){
	  _isHGG = true;
	  _Photon_gen.emplace_back(id);
	}
      }
    }
    ///If we need to get photon gen jets  
    /*
      for(unsigned int i_Photon=0; i_Photon<_Photon_gen.size(); i_Photon++){
      
      TLorentzVector Photon;
      int i_gen = _Photon_gen[i_Photon];
      Photon.SetPtEtaPhiE((*_gen_pt)[i_gen], (*_gen_eta)[i_gen], (*_gen_phi)[i_gen], (*_gen_energy)[i_gen]);     

      float dR_min = -1.;
      int i_Photon_genjet = -1;

      if ( (*_genjet_pt).size()  < 2 ) continue;

      for(unsigned int i_genjet=0; i_genjet<(*_genjet_pt).size(); i_genjet++){
    	TLorentzVector genjet;
    	genjet.SetPtEtaPhiE((*_genjet_pt)[i_genjet],(*_genjet_eta)[i_genjet],(*_genjet_phi)[i_genjet],(*_genjet_energy)[i_genjet]);
    	float dR = genjet.DeltaR(Photon);
    	if((dR_min<0 && dR<0.5) || dR<dR_min){
    	  dR_min = dR;
    	  i_Photon_genjet = i_genjet;
    	}
      }

      _Photon_genjet.emplace_back(i_Photon_genjet);
      TLorentzVector Photon_genjet;
      Photon_genjet.SetPtEtaPhiE((*_genjet_pt)[i_Photon_genjet],(*_genjet_eta)[i_Photon_genjet],(*_genjet_phi)[i_Photon_genjet],(*_genjet_energy)[i_Photon_genjet]);
      
      dR_min = -1.;
      int i_Photon_jet = -1;
      
      for(unsigned int i_jet=0; i_jet<(*_jets_pt).size(); i_jet++){
    	TLorentzVector jet;
    	jet.SetPtEtaPhiE((*_jets_pt)[i_jet],(*_jets_eta)[i_jet],(*_jets_phi)[i_jet],(*_jets_energy)[i_jet]);	
    	float dR = jet.DeltaR(Photon_genjet);
    	if((dR_min<0 && dR<0.5) || dR<dR_min){
    	//	if((dR_min<0 && dR<1.5) || dR<dR_min){
    	  dR_min = dR;
    	  i_Photon_jet = i_jet;
    	}
      }            					     

      _Photon_jets.emplace_back(i_Photon_jet);

    }
    */

    //Determine photon overlap

    for(unsigned int i_jet=0; i_jet<(*_jets_pt).size(); i_jet++){

      TLorentzVector jet;
      TLorentzVector photon;
      jet.SetPtEtaPhiE((*_jets_pt)[i_jet], (*_jets_eta)[i_jet], (*_jets_phi)[i_jet], (*_jets_energy)[i_jet]);     
      bool overlap = false;
      
      for(unsigned int phot=0; phot<_Photon_gen.size(); phot++){
      	int i_gen = _Photon_gen[phot];
	photon.SetPtEtaPhiE((*_gen_pt)[i_gen], (*_gen_eta)[i_gen], (*_gen_phi)[i_gen], (*_gen_energy)[i_gen]);     
      	if ( jet.DeltaR( photon ) < 0.1 ){
	  overlap = true;
	  break;
	}
      }

      _Photon_overlap.emplace_back(overlap);
    }


    if ( (*_jets_pt).size() > 1 ){
      if ( (_isHGG && (!_Photon_overlap[0] && !_Photon_overlap[1])) || !_isHGG ){
	_dijet_mass = std::sqrt(2*std::sqrt(std::pow((*_jets_pt)[0],2)*std::pow(std::cosh((*_jets_eta)[0]),2))*    	  std::sqrt(std::pow((*_jets_pt)[1],2)*std::pow(std::cosh((*_jets_eta)[1]),2)) -    2*(*_jets_pt)[0]*(*_jets_pt)[1]*(std::cos((*_jets_phi)[0] -  (*_jets_phi)[1]) + std::sinh((*_jets_eta)[0])*std::sinh((*_jets_eta)[1])));
      }
    }
    
    
    for(unsigned i_jet=0; i_jet < (*_jets_pt).size(); i_jet++){
      
      int i_bin = prof_cone_tc->FindBin(fabs((*_jets_eta)[i_jet]));
      _jets_PU_subtr_cone_C3D.emplace_back(prof_cone_C3D->GetBinContent(i_bin));      
      _jets_PU_subtr_cone_tc.emplace_back(prof_cone_tc->GetBinContent(i_bin));
      _jets_PU_subtr_cone_GEO_C3D.emplace_back(prof_cone_GEO_C3D->GetBinContent(i_bin));        
      
    }


    //Tau
    for(unsigned int i_Tau=0; i_Tau<_Tau_gen.size(); i_Tau++){

      TLorentzVector Tau;
      int i_gen = _Tau_gen[i_Tau];
      Tau.SetPtEtaPhiE((*_gen_pt)[i_gen], (*_gen_eta)[i_gen], (*_gen_phi)[i_gen], (*_gen_energy)[i_gen]);     

      float dR_min = -1.;
      int i_Tau_genjet = -1;

      if ( (*_genjet_pt).size()  < 2 ) continue;

      for(unsigned int i_genjet=0; i_genjet<(*_genjet_pt).size(); i_genjet++){
	TLorentzVector genjet;
	genjet.SetPtEtaPhiE((*_genjet_pt)[i_genjet],(*_genjet_eta)[i_genjet],(*_genjet_phi)[i_genjet],(*_genjet_energy)[i_genjet]);
	float dR = genjet.DeltaR(Tau);
	if((dR_min<0 && dR<0.5) || dR<dR_min){
	  dR_min = dR;
	  i_Tau_genjet = i_genjet;
	}
      }

      _Tau_genjet.emplace_back(i_Tau_genjet);
      TLorentzVector Tau_genjet;
      Tau_genjet.SetPtEtaPhiE((*_genjet_pt)[i_Tau_genjet],(*_genjet_eta)[i_Tau_genjet],(*_genjet_phi)[i_Tau_genjet],(*_genjet_energy)[i_Tau_genjet]);
      
      dR_min = -1.;
      int i_Tau_jet = -1;
      
      for(unsigned int i_jet=0; i_jet<(*_jets_pt).size(); i_jet++){
	TLorentzVector jet;
	jet.SetPtEtaPhiE((*_jets_pt)[i_jet],(*_jets_eta)[i_jet],(*_jets_phi)[i_jet],(*_jets_energy)[i_jet]);	
	float dR = jet.DeltaR(Tau_genjet);
	if((dR_min<0 && dR<0.5) || dR<dR_min){
	//	if((dR_min<0 && dR<1.5) || dR<dR_min){
	  dR_min = dR;
	  i_Tau_jet = i_jet;
	}
      }            					     

      _Tau_jets.emplace_back(i_Tau_jet);


    }



    //Find VBF jets
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
	//Continue if jet overlaps with truth photon
	if ( _Photon_overlap.size() > 0){
	  if ( _Photon_overlap[i_jet] ) continue;
	}
	TLorentzVector jet;
	jet.SetPtEtaPhiE((*_jets_pt)[i_jet],(*_jets_eta)[i_jet],(*_jets_phi)[i_jet],(*_jets_energy)[i_jet]);	
	float dR = jet.DeltaR(VBF_genjet);

	//	float dPT= (std::abs(jet.Pt()-VBF_genjet.Pt()))/VBF_genjet.Pt();

	  if((dR_min<0 && dR<0.5) || dR<dR_min){
	    
	    //	    if ( dPT-(60/VBF_genjet.Pt()) < 0.4 ){
	      dR_min = dR;
	      i_VBF_jet = i_jet;
	      //	    }
	    
	  }
      }

      _VBF_parton_jets.emplace_back(i_VBF_jet);


      //Find if Tau overlaps with VBF jet
      bool overlap = false;
      for (unsigned tau=0;tau<_Tau_jets.size();tau++){
	overlap = false;
	TLorentzVector vbfjet;
	TLorentzVector taujet;
	taujet.SetPtEtaPhiE((*_jets_pt)[tau],(*_jets_eta)[tau],(*_jets_phi)[tau],(*_jets_energy)[tau]);	
	vbfjet.SetPtEtaPhiE((*_jets_pt)[i_VBF_jet],(*_jets_eta)[i_VBF_jet],(*_jets_phi)[i_VBF_jet],(*_jets_energy)[i_VBF_jet]);	
	if ( vbfjet.DeltaR( taujet ) < 0.4 ){
	  overlap = true;
	}
      }

      _Tau_overlap.emplace_back(overlap);
    
      /*
      //Find if Photon overlaps with VBF jet
      overlap = false;
      //      for (unsigned photon=0;photon<_Photon_jets.size();photon++){
      //      for (unsigned photon=0;photon<_Photon_genjet.size();photon++){
      for(unsigned int photon=0; photon<_Photon_gen.size(); photon++){


	overlap = false;
	TLorentzVector vbfjet;
	TLorentzVector photonjet;
	//	photonjet.SetPtEtaPhiE((*_jets_pt)[photon],(*_jets_eta)[photon],(*_jets_phi)[photon],(*_jets_energy)[photon]);
	//	photonjet.SetPtEtaPhiE((*_genjet_pt)[photon],(*_genjet_eta)[photon],(*_genjet_phi)[photon],(*_genjet_energy)[photon]);
	int i_gen = _Photon_gen[photon];
	photonjet.SetPtEtaPhiE((*_gen_pt)[i_gen], (*_gen_eta)[i_gen], (*_gen_phi)[i_gen], (*_gen_energy)[i_gen]);     
	vbfjet.SetPtEtaPhiE((*_jets_pt)[i_VBF_jet],(*_jets_eta)[i_VBF_jet],(*_jets_phi)[i_VBF_jet],(*_jets_energy)[i_VBF_jet]);	
	if ( vbfjet.DeltaR( photonjet ) < 0.4 ){
	  overlap = true;
	}
      }

      _Photon_overlap.emplace_back(overlap);

      */      
    }
    
    //Pion
    for(unsigned int i_Pion=0; i_Pion<_Pion_gen.size(); i_Pion++){

      TLorentzVector Pion;
      int i_gen = _Pion_gen[i_Pion];
      Pion.SetPtEtaPhiE((*_gen_pt)[i_gen], (*_gen_eta)[i_gen], (*_gen_phi)[i_gen], (*_gen_energy)[i_gen]);     

      float dR_min = -1.;
      int i_Pion_genjet = -1;

      if ( (*_genjet_pt).size()  < 2 ) continue;

      for(unsigned int i_genjet=0; i_genjet<(*_genjet_pt).size(); i_genjet++){
	TLorentzVector genjet;
	genjet.SetPtEtaPhiE((*_genjet_pt)[i_genjet],(*_genjet_eta)[i_genjet],(*_genjet_phi)[i_genjet],(*_genjet_energy)[i_genjet]);
	float dR = genjet.DeltaR(Pion);
	if((dR_min<0 && dR<0.5) || dR<dR_min){
	  dR_min = dR;
	  i_Pion_genjet = i_genjet;
	}
      }

      _Pion_genjet.emplace_back(i_Pion_genjet);
      TLorentzVector Pion_genjet;
      Pion_genjet.SetPtEtaPhiE((*_genjet_pt)[i_Pion_genjet],(*_genjet_eta)[i_Pion_genjet],(*_genjet_phi)[i_Pion_genjet],(*_genjet_energy)[i_Pion_genjet]);
      
      dR_min = -1.;
      int i_Pion_jet = -1;
      
      for(unsigned int i_jet=0; i_jet<(*_jets_pt).size(); i_jet++){
	TLorentzVector jet;
	jet.SetPtEtaPhiE((*_jets_pt)[i_jet],(*_jets_eta)[i_jet],(*_jets_phi)[i_jet],(*_jets_energy)[i_jet]);	
	float dR = jet.DeltaR(Pion_genjet);
	if((dR_min<0 && dR<0.5) || dR<dR_min){
	  dR_min = dR;
	  i_Pion_jet = i_jet;
	}
      }            					     

      _Pion_jets.emplace_back(i_Pion_jet);

    }

  
    if ( _VBF_parton_jets.size() > 1 ){
      if ( _VBF_parton_jets[0] > 0 && _VBF_parton_jets[1] > 0 ){
	_dijet_mass_VBF = std::sqrt(2*std::sqrt(std::pow((*_jets_pt)[_VBF_parton_jets[0]],2)*std::pow(std::cosh((*_jets_eta)[_VBF_parton_jets[0]]),2))*    	  std::sqrt(std::pow((*_jets_pt)[_VBF_parton_jets[1]],2)*std::pow(std::cosh((*_jets_eta)[_VBF_parton_jets[1]]),2)) -    2*(*_jets_pt)[_VBF_parton_jets[0]]*(*_jets_pt)[_VBF_parton_jets[1]]*(std::cos((*_jets_phi)[_VBF_parton_jets[0]] -  (*_jets_phi)[_VBF_parton_jets[1]]) + std::sinh((*_jets_eta)[_VBF_parton_jets[0]])*std::sinh((*_jets_eta)[_VBF_parton_jets[1]])));
      }
    }

    
    //Find number of seeds in a jet
    
    if ( include_num_seeds_jet ){
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
    }
    
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
  TString treename_out="HGCalTriggerNtupleJet";
  TString fileout="test_jet.root";

  add_jet( filein, treename, filein_jet, treename_jet, fileout, treename_out);


}

