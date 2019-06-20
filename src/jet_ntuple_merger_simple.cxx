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

  
  int _cl3d_n;

  std::vector<float> *_cl3d_pt;
  std::vector<float> *_cl3d_eta;
  std::vector<float> *_cl3d_phi;
  std::vector<float> *_cl3d_energy;
  std::vector<unsigned int> *_cl3d_id;

  std::vector<float> *_jets_pt;
  std::vector<float> *_jets_eta;
  std::vector<float> *_jets_phi;
  std::vector<float> *_jets_energy;

  // std::vector<std::vector<float> > *_jets_C3d_pt;
  // std::vector<std::vector<float> > *_jets_C3d_eta;
  // std::vector<std::vector<float> > *_jets_C3d_phi;
  // std::vector<std::vector<float> > *_jets_C3d_energy;

  std::vector<std::vector<unsigned int> > *_cl3d_clusters_id;

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

  //  TBranch        *b_gen_daughters;   //!

  //  tree->SetBranchAddress("tc_n",     &_tc_n);
  tree->SetBranchAddress("cl3d_n",   &_cl3d_n);
  
  // tree->SetBranchAddress("tc_eta",    &_tc_eta);
  // tree->SetBranchAddress("tc_pt",    &_tc_pt);
  // tree->SetBranchAddress("tc_phi",    &_tc_phi);
  // tree->SetBranchAddress("tc_energy", &_tc_energy);
  // tree->SetBranchAddress("tc_z",      &_tc_z);
  // tree->SetBranchAddress("tc_layer",  &_tc_layer);
  // tree->SetBranchAddress("tc_subdet", &_tc_subdet);
  //  tree->SetBranchAddress("tc_id",     &_tc_id);

  tree->SetBranchAddress("cl3d_pt",     &_cl3d_pt);
  tree->SetBranchAddress("cl3d_eta",    &_cl3d_eta);
  tree->SetBranchAddress("cl3d_phi",    &_cl3d_phi);
  tree->SetBranchAddress("cl3d_energy", &_cl3d_energy);
  tree->SetBranchAddress("cl3d_id",     &_cl3d_id);
  tree->SetBranchAddress("cl3d_clusters_id",   &_cl3d_clusters_id);
  tree->SetBranchAddress("gen_pdgid",     &_gen_id);
  tree->SetBranchAddress("gen_status", &_gen_status);
  tree->SetBranchAddress("gen_pt",     &_gen_pt);
  tree->SetBranchAddress("gen_eta",    &_gen_eta);
  tree->SetBranchAddress("gen_phi",    &_gen_phi);
  tree->SetBranchAddress("gen_energy", &_gen_energy);
  //  tree->SetBranchAddress("gen_daughters", &_gen_daughters, &b_gen_daughters);



  tree->SetBranchAddress("genjet_pt",     &_genjet_pt);
  tree->SetBranchAddress("genjet_eta",    &_genjet_eta);
  tree->SetBranchAddress("genjet_phi",    &_genjet_phi);
  tree->SetBranchAddress("genjet_energy", &_genjet_energy);


  tree->SetBranchStatus ("*",0);
  //  tree->SetBranchStatus("tc_n"     ,1);

  tree->SetBranchStatus("cl3d_n"   ,1);
  // tree->SetBranchStatus("tc_eta"   ,1);
  // tree->SetBranchStatus("tc_pt"   ,1);
  // tree->SetBranchStatus("tc_phi"   ,1);
  // tree->SetBranchStatus("tc_energy",1);
  // tree->SetBranchStatus("tc_z"     ,1);
  // tree->SetBranchStatus("tc_layer" ,1);
  // tree->SetBranchStatus("tc_subdet",1);
  //tree->SetBranchStatus("tc_id"    ,1);
  tree->SetBranchStatus("cl3d_pt"  ,1);
  tree->SetBranchStatus("cl3d_eta" ,1);
  tree->SetBranchStatus("cl3d_phi"    ,1);
  tree->SetBranchStatus("cl3d_energy" ,1);
  tree->SetBranchStatus("cl3d_id"     ,1);
  tree->SetBranchStatus("cl3d_clusters_id",1);

  tree->SetBranchStatus("gen_pdgid",1);
  tree->SetBranchStatus("gen_status",1);
  tree->SetBranchStatus("gen_pt"   ,1);
  tree->SetBranchStatus("gen_eta"  ,1);
  tree->SetBranchStatus("gen_phi"  ,1);
  tree->SetBranchStatus("gen_energy",1);
  //   tree->SetBranchStatus("gen_daughters",1);

  tree->SetBranchStatus("genjet_pt"     ,1);
  tree->SetBranchStatus("genjet_eta"    ,1);
  tree->SetBranchStatus("genjet_phi"    ,1);
  tree->SetBranchStatus("genjet_energy" ,1);


  tree_jet->SetBranchAddress("jets_pt",     &_jets_pt);
  tree_jet->SetBranchAddress("jets_eta",    &_jets_eta);
  tree_jet->SetBranchAddress("jets_phi",    &_jets_phi);
  tree_jet->SetBranchAddress("jets_energy", &_jets_energy);
    

  // tree->SetBranchStatus ("*",1);

  f_new->cd();
  TTree* tree_new = new TTree(treenameout,treenameout);


  tree_new->AddFriend(treename,filein);
  //  tree_new->AddFriend(tree_reference,filein);
  //  TString filejet_friend = "/vols/cms/snwebb/HGC_ntuples/" + filein_jet(29,filein_jet.Length());
  
  //New branches
  // std::vector<int> _tc_HGClayer;//need
  // std::vector<int> _cl_HGClayer;//need

  // std::vector<int> _tc_cl;
  // std::vector<int> _tc_cl3d;
  std::vector<int> _cl_cl3d;  
  // std::vector<int> _tc_jet; //index of jet in which tc included
  // std::vector<int> _cl_jet; //index of jet in which cl included
  // std::vector<int> _cl3d_jet; //index of jet in which cl3d included

  std::vector<std::vector<int> > _cl_cells;
  //  std::vector<std::vector<int> > _cl3d_clusters;

  int _jets_n;
  std::vector<int> _jets_ncl3d;
  std::vector<std::vector<int> > _jets_cl3d; // list of cl3d included in jet
  std::vector<std::vector<unsigned int> > _jets_cl3d_id;

  std::vector<float> _jets_PU_subtr_cone_C3D;
  std::vector<float> _jets_PU_subtr_cone_tc;
  std::vector<float> _jets_PU_subtr_cone_GEO_C3D;

  bool _isVBF;
  std::vector<int> _VBF_parton_gen;
  std::vector<int> _VBF_parton_genjet;
  std::vector<int> _VBF_parton_jets;

  std::vector<int> _Pion_gen;
  std::vector<int> _Pion_genjet;
  std::vector<int> _Pion_jets;

  std::vector<int> _Tau_gen;
  std::vector<int> _Tau_genjet;
  std::vector<int> _Tau_jets;

  // std::vector<int> _Photon_gen;
  // std::vector<int> _Photon_genjet;
  // std::vector<int> _Photon_jets;

  // std::vector<int> _Higgs_gen;

  std::vector<bool> _Tau_overlap;
  //  std::vector<bool> _Photon_overlap;

  //  std::vector<int> _num_seeds_in_jet;

  tree_new->Branch("jets_PU_subtr_cone_C3D", &_jets_PU_subtr_cone_C3D);
  tree_new->Branch("jets_PU_subtr_cone_tc", &_jets_PU_subtr_cone_tc);
  tree_new->Branch("jets_PU_subtr_cone_GEO_C3D", &_jets_PU_subtr_cone_GEO_C3D);

  tree_new->Branch("isVBF", &_isVBF, "isVBF/O");
  tree_new->Branch("VBF_parton_gen", &_VBF_parton_gen);
  tree_new->Branch("VBF_parton_genjet", &_VBF_parton_genjet);
  tree_new->Branch("VBF_parton_jets", &_VBF_parton_jets);

  tree_new->Branch("Pion_genjet", &_Pion_genjet);
  tree_new->Branch("Pion_jets", &_Pion_jets);

  //  tree_new->Branch("Tau_genjet", &_Tau_genjet);
  //  tree_new->Branch("Tau_jets", &_Tau_jets);
  tree_new->Branch("Tau_overlap", &_Tau_overlap);
  //  tree_new->Branch("Photon_overlap", &_Photon_overlap);

  // tree_new->Branch("Photon_genjet", &_Photon_genjet);
  // tree_new->Branch("Photon_jets", &_Photon_jets);
  // tree_new->Branch("Photon_overlap", &_Photon_overlap);

  tree_new->Branch("jets_pt", &_jets_pt);
  tree_new->Branch("jets_eta", &_jets_eta);
  tree_new->Branch("jets_phi", &_jets_phi);
  tree_new->Branch("jets_energy", &_jets_energy);

  //  tree_new->Branch("num_seeds_in_jet", &_num_seeds_in_jet);
  
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

    //    _tc_n = 0;
    _cl3d_n = 0;
    // _tc_eta = 0;
    // _tc_pt = 0;
    // _tc_phi = 0;
    // _tc_energy = 0;
    // _tc_z = 0;
    // _tc_layer = 0;
    // _tc_subdet = 0;
    //    _tc_id = 0;

    _cl3d_pt = 0;
    _cl3d_eta = 0;
    _cl3d_phi = 0;
    _cl3d_energy = 0;
    _cl3d_id = 0;
    // _cl3d_firstlayer = 0;
    _cl3d_clusters_id = 0;

    _jets_pt = 0;
    _jets_eta = 0;
    _jets_phi = 0;
    _jets_energy = 0;  
    
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
    
    _jets_n = 0;

    //New Branches
 
    // _tc_cl.clear();
    // _tc_cl3d.clear();
    _cl_cl3d.clear();  

    _jets_ncl3d.clear();
    _jets_cl3d.clear();
    _jets_cl3d_id.clear();

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

    // _Photon_gen.clear();
    // _Photon_genjet.clear();
    // _Photon_jets.clear();
    // _Photon_overlap.clear();

    //    _num_seeds_in_jet.clear();

    //    _Higgs_gen.clear();

    tree->GetEntry(i);
    tree_jet->GetEntry(i);

    _jets_n = (*_jets_pt).size();   
    
    //    std::map<unsigned int, unsigned int> tc_map; //First ID, Second index
    std::map<unsigned int, unsigned int> cl_map; //First ID, Second index
    std::map<unsigned int, unsigned int> cl3d_map; //First ID, Second index
   
    // for(int i_tc=0; i_tc<_tc_n; i_tc++){      
   
    //   tc_map[(*_tc_id)[i_tc]] = i_tc;
   
    // }
   
    for(unsigned int i_c3d=0; i_c3d<(*_cl3d_clusters_id).size(); i_c3d++){

      cl3d_map[(*_cl3d_id)[i_c3d]] = i_c3d;

    }    


    _jets_cl3d_id.resize(_jets_n);
    _jets_cl3d.resize(_jets_n);



    for(int i_jet=0; i_jet<_jets_n; i_jet++){
      
      int i_bin = prof_cone_tc->FindBin(fabs((*_jets_eta)[i_jet]));
      _jets_PU_subtr_cone_C3D.emplace_back(prof_cone_C3D->GetBinContent(i_bin));      
      _jets_PU_subtr_cone_tc.emplace_back(prof_cone_tc->GetBinContent(i_bin));
      _jets_PU_subtr_cone_GEO_C3D.emplace_back(prof_cone_GEO_C3D->GetBinContent(i_bin));        

    }

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
      // if(abs((*_gen_id)[i_gen])==15 && (*_gen_status)[i_gen]==62)
      // 	_Higgs_gen.emplace_back(i_gen);

    }



    //Photon
    //Find the higgs
    // std::cout << "find the higgs "<< std::endl;
    // std::cout << _Higgs_gen.size() << std::endl;
    // for(unsigned int i_Higgs=0; i_Higgs<_Higgs_gen.size(); i_Higgs++){
    //   for(unsigned int i_daught=0; i_daught<_gen_daughters[i_Higgs].size(); i_daught++){
	
    // 	int id = (*_gen_daughters)[i_Higgs].at(i_daught);
    // 	if(abs((*_gen_id)[id])==22 && (*_gen_status)[id]==1)
    // 	  _Photon_gen.emplace_back(id);

    //   }
    // }

    // for(unsigned int i_Photon=0; i_Photon<_Photon_gen.size(); i_Photon++){

    //   TLorentzVector Photon;
    //   int i_gen = _Photon_gen[i_Photon];
    //   Photon.SetPtEtaPhiE((*_gen_pt)[i_gen], (*_gen_eta)[i_gen], (*_gen_phi)[i_gen], (*_gen_energy)[i_gen]);     

    //   float dR_min = -1.;
    //   int i_Photon_genjet = -1;

    //   if ( (*_genjet_pt).size()  < 2 ) continue;

    //   for(unsigned int i_genjet=0; i_genjet<(*_genjet_pt).size(); i_genjet++){
    // 	TLorentzVector genjet;
    // 	genjet.SetPtEtaPhiE((*_genjet_pt)[i_genjet],(*_genjet_eta)[i_genjet],(*_genjet_phi)[i_genjet],(*_genjet_energy)[i_genjet]);
    // 	float dR = genjet.DeltaR(Photon);
    // 	if((dR_min<0 && dR<0.5) || dR<dR_min){
    // 	  dR_min = dR;
    // 	  i_Photon_genjet = i_genjet;
    // 	}
    //   }

    //   _Photon_genjet.emplace_back(i_Photon_genjet);
    //   TLorentzVector Photon_genjet;
    //   Photon_genjet.SetPtEtaPhiE((*_genjet_pt)[i_Photon_genjet],(*_genjet_eta)[i_Photon_genjet],(*_genjet_phi)[i_Photon_genjet],(*_genjet_energy)[i_Photon_genjet]);
      
    //   dR_min = -1.;
    //   int i_Photon_jet = -1;
      
    //   for(unsigned int i_jet=0; i_jet<(*_jets_pt).size(); i_jet++){
    // 	TLorentzVector jet;
    // 	jet.SetPtEtaPhiE((*_jets_pt)[i_jet],(*_jets_eta)[i_jet],(*_jets_phi)[i_jet],(*_jets_energy)[i_jet]);	
    // 	float dR = jet.DeltaR(Photon_genjet);
    // 	if((dR_min<0 && dR<0.5) || dR<dR_min){
    // 	//	if((dR_min<0 && dR<1.5) || dR<dR_min){
    // 	  dR_min = dR;
    // 	  i_Photon_jet = i_jet;
    // 	}
    //   }            					     

    //   _Photon_jets.emplace_back(i_Photon_jet);


    // }




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









    //VBF
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



    //Find number of seeds in a jet
    /*
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
    */

    delete _cl3d_clusters_id;
    _cl3d_clusters_id = 0;

    // delete _jets_C3d_pt;        
    // delete _jets_C3d_eta;        
    // delete _jets_C3d_phi;        
    // delete _jets_C3d_energy;        
    // _jets_C3d_pt = 0  ;        
    // _jets_C3d_eta = 0 ;        
    // _jets_C3d_phi = 0 ;        
    // _jets_C3d_energy = 0 ;        
    
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

