#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TLorentzVector.h>
#include <TMath.h>
#include <TProfile.h>
#include <iostream>
#include <TBranch.h>
#include "Helpers.C"




void fix_core(TString filein, TString fileout){


  TFile* f_new = TFile::Open(fileout);
  if(f_new!=0){
    cout<<fileout<<" already exists, please delete it before converting again"<<endl;
    return;
  }  
  f_new = TFile::Open(fileout,"RECREATE");

  TChain * tree = new TChain("jets");
  tree->Add(filein);
  Long64_t nentries = tree->GetEntries();
  cout<<"nentries="<<nentries<<endl;

  vector<float>* _jets_0p1_core_Luca_pt;
  tree->SetBranchAddress("jets_0p1_core_Luca_pt",        &_jets_0p1_core_Luca_pt);
  

  TTree* tree_new=tree->GetTree()->CloneTree(0);

  vector<float> _jets_0p1_core_ok_pt;
  vector<float> _jets_0p1_core_ok_energy;

  tree_new->Branch("jets_0p1_core_ok_pt",      &_jets_0p1_core_ok_pt);
  tree_new->Branch("jets_0p1_core_ok_energy",  &_jets_0p1_core_ok_energy);

  for(int i=0;i<nentries;i++){

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    _jets_0p1_core_Luca_pt = 0;

    _jets_0p1_core_ok_pt.clear();
    _jets_0p1_core_ok_energy.clear();

    tree->GetEntry(i);

    for(unsigned int ijet=0;ijet<(*_jets_0p1_core_Luca_pt).size();ijet++){
      if(ijet%2==0)
	_jets_0p1_core_ok_pt.push_back((*_jets_0p1_core_Luca_pt)[ijet]);
      else
	_jets_0p1_core_ok_energy.push_back((*_jets_0p1_core_Luca_pt)[ijet]);
    }

    tree_new->Fill();

  }


  tree_new->AddFriend("HGCalTriggerNtuple",filein);
  tree_new->Write();

  /*TChain * tree2 = new TChain("HGCalTriggerNtuple");
  tree2->Add(filein);  
  long nentries2 = tree2->GetEntries();
  TTree* t2 = tree2->CloneTree();
  t2->AddFriend(tree_new);
  t2->Write();*/

  f_new->Close();
  
  return;

}
