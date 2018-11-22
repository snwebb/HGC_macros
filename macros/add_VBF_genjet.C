#include <TProfile.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TLorentzVector.h>
#include <TMath.h>
#include <iostream>
#include "Helpers.C"
#include <unordered_map>




void add_VBF_genjet(TString filein,  TString treename, TString fileout){

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
  TTree* tree_new=tree->GetTree()->CloneTree(0);

  TChain * tree_jet = new TChain("jets");
  tree_jet->Add(filein);
  Long64_t nentries2 = tree_jet->GetEntries();
  if(nentries!=nentries2){
    cout<<"Inconsistent number of entries in two input files"<<endl;
    return;
  }
  TTree* tree_new2=tree_jet->GetTree()->CloneTree(0);
  tree_new->AddFriend(tree_new2);

  vector<int> *_gen_id;
  vector<int> *_gen_status;
  vector<float> *_gen_pt;
  vector<float> *_gen_eta;
  vector<float> *_gen_phi;
  vector<float> *_gen_energy;
  
  vector<float> *_genjet_pt;
  vector<float> *_genjet_eta;
  vector<float> *_genjet_phi;
  vector<float> *_genjet_energy;

  vector<float> *_jets_pt;
  vector<float> *_jets_eta;
  vector<float> *_jets_phi;
  vector<float> *_jets_energy;

  tree->SetBranchAddress("gen_id",     &_gen_id);
  tree->SetBranchAddress("gen_status", &_gen_status);
  tree->SetBranchAddress("gen_pt",     &_gen_pt);
  tree->SetBranchAddress("gen_eta",    &_gen_eta);
  tree->SetBranchAddress("gen_phi",    &_gen_phi);
  tree->SetBranchAddress("gen_energy", &_gen_energy);
      
  tree->SetBranchAddress("genjet_pt",     &_genjet_pt);
  tree->SetBranchAddress("genjet_eta",    &_genjet_eta);
  tree->SetBranchAddress("genjet_phi",    &_genjet_phi);
  tree->SetBranchAddress("genjet_energy", &_genjet_energy);
      
  tree_jet->SetBranchAddress("jets_pt",     &_jets_pt);
  tree_jet->SetBranchAddress("jets_eta",    &_jets_eta);
  tree_jet->SetBranchAddress("jets_phi",    &_jets_phi);
  tree_jet->SetBranchAddress("jets_energy", &_jets_energy);

  //New branches
  bool _isVBF;
  vector<int> _VBF_parton_gen;
  vector<int> _VBF_parton_genjet;
  vector<int> _VBF_parton_jets;

  vector<float> _jets_PU_subtr_cone_C3D;
  vector<float> _jets_PU_subtr_cone_C3D_pTgt0;
  vector<float> _jets_PU_subtr_cone_tc;
  vector<float> _jets_PU_subtr_cone_tc_pTgt0;

  tree_new->Branch("isVBF", &_isVBF, "isVBF/O");
  tree_new->Branch("VBF_parton_gen", &_VBF_parton_gen);
  tree_new->Branch("VBF_parton_genjet", &_VBF_parton_genjet);
  tree_new->Branch("VBF_parton_jets", &_VBF_parton_jets);

  tree_new2->Branch("jets_PU_subtr_cone_C3D", &_jets_PU_subtr_cone_C3D);
  tree_new2->Branch("jets_PU_subtr_cone_C3D_pTgt0", &_jets_PU_subtr_cone_C3D_pTgt0);
  tree_new2->Branch("jets_PU_subtr_cone_tc", &_jets_PU_subtr_cone_tc);
  tree_new2->Branch("jets_PU_subtr_cone_tc_pTgt0", &_jets_PU_subtr_cone_tc_pTgt0); 

  TFile* f_PU_cone_eta = TFile::Open("PU_cone_vs_eta.root");
  TProfile* prof_cone_tc = (TProfile*)f_PU_cone_eta->Get("prof_cone_tc");
  TProfile* prof_cone_tc_pTgt0 = (TProfile*)f_PU_cone_eta->Get("prof_cone_tc_pTgt0");
  TProfile* prof_cone_C3D = (TProfile*)f_PU_cone_eta->Get("prof_cone_C3D");
  TProfile* prof_cone_C3D_pTgt0 = (TProfile*)f_PU_cone_eta->Get("prof_cone_C3D_pTgt0");
  prof_cone_tc->SetDirectory(0);
  prof_cone_tc_pTgt0->SetDirectory(0);
  prof_cone_C3D->SetDirectory(0);
  prof_cone_C3D_pTgt0->SetDirectory(0);
  f_PU_cone_eta->Close();

  
  for(int i=0;i<nentries;i++){

    if(i%10000==0)
      cout<<"i="<<i<<endl;
  
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
    
    _jets_pt = 0;
    _jets_eta = 0;
    _jets_phi = 0;
    _jets_energy = 0;
  
    _VBF_parton_gen.clear();
    _VBF_parton_genjet.clear();
    _VBF_parton_jets.clear();

    _jets_PU_subtr_cone_C3D.clear();
    _jets_PU_subtr_cone_C3D_pTgt0.clear();
    _jets_PU_subtr_cone_tc.clear();
    _jets_PU_subtr_cone_tc_pTgt0.clear();

    tree->GetEntry(i);
    tree_jet->GetEntry(i);

    _isVBF = true;

    for(unsigned int i_gen=0; i_gen<(*_gen_id).size(); i_gen++){
      if(abs((*_gen_id)[i_gen])==21 && (*_gen_status)[i_gen]==21) //Gluon splitting in initial partons
	_isVBF = false;
      if(abs((*_gen_id)[i_gen])<6 && (*_gen_status)[i_gen]==23)
	_VBF_parton_gen.emplace_back(i_gen);
    }

    if(_VBF_parton_gen.size()!=2 && _isVBF){
      cout<<"Not 2 VBF partons, please look in details at event "<<i<<endl;
      return;
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
	//float dR = jet.DeltaR(VBF_parton);
	float dR = jet.DeltaR(VBF_genjet);
	if((dR_min<0 && dR<0.5) || dR<dR_min){
	  dR_min = dR;
	  i_VBF_jet = i_jet;
	}
      }            					     

      _VBF_parton_jets.emplace_back(i_VBF_jet);

    }

    for(unsigned int i_jet=0; i_jet<(*_jets_pt).size(); i_jet++){
      
      int i_bin = prof_cone_tc->FindBin(fabs((*_jets_eta)[i_jet]));
      _jets_PU_subtr_cone_C3D.emplace_back(prof_cone_C3D->GetBinContent(i_bin));
      _jets_PU_subtr_cone_C3D_pTgt0.emplace_back(prof_cone_C3D_pTgt0->GetBinContent(i_bin));
      _jets_PU_subtr_cone_tc.emplace_back(prof_cone_tc->GetBinContent(i_bin));
      _jets_PU_subtr_cone_tc_pTgt0.emplace_back(prof_cone_tc_pTgt0->GetBinContent(i_bin));      
      
    }
    
    tree_new->Fill();
    tree_new2->Fill();

  }

  f_new->cd();
  tree_new->Write();
  tree_new2->Write();
  f_new->Close();
  return;

}
