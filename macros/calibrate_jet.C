#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TLorentzVector.h>
#include <TMath.h>
#include <iostream>
#include "Helpers.C"



void calibrate_jet(TString filein,
		   TString fileout){

  TFile* f_new = TFile::Open(fileout);
  if(f_new!=0){
    cout<<fileout<<" already exists, please delete it before converting again"<<endl;
    return;
  }  
  f_new = TFile::Open(fileout,"RECREATE");

  TChain * tree = new TChain("HGCalTriggerNtuple");
  tree->Add(filein);
  Long64_t nentries = tree->GetEntries();
  cout<<"nentries="<<nentries<<endl;


  TTree* tree_new2 = new TChain("jets");
  TChain * tree_jet = new TChain("jets");
  tree_jet->Add(filein);
  Long64_t nentries2 = tree_jet->GetEntries();
  if(nentries!=nentries2){
    cout<<"Inconsistent number of entries in two input files"<<endl;
    return;
  }



  vector<float>* _jets_raw_eta;
  vector<float>* _jets_raw_phi;
  vector<float>* _jets_raw_Luca_pt;
  vector<float>* _jets_raw_Luca_energy;
  vector<float>* _jets_PU_subtr_cone_C3D;

  tree_jet->SetBranchAddress("jets_raw_eta",           &_jets_raw_eta);
  tree_jet->SetBranchAddress("jets_raw_phi",           &_jets_raw_phi);
  tree_jet->SetBranchAddress("jets_raw_Luca_pt",       &_jets_raw_Luca_pt);
  tree_jet->SetBranchAddress("jets_raw_Luca_energy",   &_jets_raw_Luca_energy);
  tree_jet->SetBranchAddress("jets_PU_subtr_cone_C3D", &_jets_PU_subtr_cone_C3D);
  
  //New branches
  vector<float> _jets_raw_PUS_pt;
  vector<float> _jets_raw_PUS_energy;
  vector<float> _jets_calib_pt;
  vector<float> _jets_calib_energy;

  tree_new2->Branch("jets_raw_PUS_pt",     &_jets_raw_PUS_pt);
  tree_new2->Branch("jets_raw_PUS_energy", &_jets_raw_PUS_energy);
  tree_new2->Branch("jets_calib_pt",       &_jets_calib_pt);
  tree_new2->Branch("jets_calib_energy",   &_jets_calib_energy);


  for(int i=0;i<nentries;i++){
    cout<<"i="<<i<<endl;

    _jets_raw_eta = 0;
    _jets_raw_phi = 0;
    _jets_raw_Luca_pt = 0;
    _jets_raw_Luca_energy = 0;
    _jets_PU_subtr_cone_C3D = 0;

    _jets_raw_PUS_pt.clear();
    _jets_raw_PUS_energy.clear();
    _jets_calib_pt.clear();
    _jets_calib_energy.clear();

    tree->GetEntry(i);
    tree_jet->GetEntry(i);

    for(unsigned int i_jet=0;i_jet<(*_jets_raw_eta).size();i_jet++){

      TLorentzVector jet_PUS;
      float pt_PUS = max((*_jets_raw_Luca_pt)[i_jet]-(*_jets_PU_subtr_cone_C3D)[i_jet],0);
      jet_PUS.SetPtEtaPhiM(pt_PUS,(*_jets_raw_eta)[i_jet],(*_jets_raw_phi)[i_jet],0);
 
      float SF = 4.4374 -0.948102 *TMath::Log(TMath::Max(pt_PUS,20.)) + 0.0686934* TMath::Log(TMath::Max(pt_PUS,20.)) * TMath::Log(TMath::Max(pt_PUS,20.));
      TLorentzVector jet_calib = SF*jet_PUS;

      _jets_raw_PUS_pt.emplace_back(jet_PUS.Pt());
      _jets_raw_PUS_energy.emplace_back(jet_PUS.E());
      _jets_calib_pt.emplace_back(jet_calib.Pt());
      _jets_calib_energy(jet_calib.E());

    }


}
