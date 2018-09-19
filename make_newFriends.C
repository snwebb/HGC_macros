#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <iostream>

using namespace std;

void make_newFriends(TString dir, int nfiles){

  for(unsigned int i=1;i<nfiles+1;i++){
    
    cout<<i<<endl;
    TString filename_1 = dir+Form("jet_ntuples_merged/ntuple_jet_merged_%i.root",i);
    TString filename_2 = dir+Form("ntuples/ntuple_%i.root",i);
    TString filename_3 = dir+Form("jet_ntuples/ntuple_jet_%i.root",i);

    TFile* f = new TFile(filename_1,"UPDATE");
    
    TTree* tree = (TTree*)f->Get("HGCalTriggerNtupleJet");
    if(tree){
      tree->SetName("temp");
      for(unsigned int j=0;j<tree->GetListOfFriends()->GetSize();j++){
	if(TString(tree->GetListOfFriends()->At(j)->GetName())=="hgcalTriggerNtuplizer/HGCalTriggerNtuple"){      
	  tree->GetListOfFriends()->Remove(tree->GetListOfFriends()->At(j));
	  tree->AddFriend("hgcalTriggerNtuplizer/HGCalTriggerNtuple",filename_2);      
	}
	else if(TString(tree->GetListOfFriends()->At(j)->GetName())=="jets"){      
	  tree->GetListOfFriends()->Remove(tree->GetListOfFriends()->At(j));
	  tree->AddFriend("jets",filename_3); 
	  }
      }
      gDirectory->Delete("HGCalTriggerNtupleJet;*");
      tree->SetName("HGCalTriggerNtupleJet");
      tree->Write();
    }

    f->Close();

  }

}



void test(){

  TString dir = "/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRC3D_polarHisto_thresh_20MIPT_TC/";
  make_newFriends(dir,49);

}

