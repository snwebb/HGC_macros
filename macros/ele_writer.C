#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TLorentzVector.h>
#include <TMath.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include "Helpers.C"


using namespace std;

void write_ele(TString filename, TString treename,
		TString fileout){


  std::ofstream out(fileout);

  TChain * tree = new TChain(treename);
  tree->Add(filename);
  int nentries = tree->GetEntries();


  vector<int> *_genele_C3D;

  vector<float>* _gen_pt;
  vector<float>* _gen_eta;

  vector<vector<unsigned int> >* _cl3d_clusters;
  vector<float>* _cl_MIPpt;
  vector<int>* _cl_HGClayer;

  
  tree->SetBranchAddress("genele_C3D",   &_genele_C3D);

  tree->SetBranchAddress("gen_pt",         &_gen_pt);
  tree->SetBranchAddress("gen_eta",        &_gen_eta);

  tree->SetBranchAddress("cl3d_clusters",     &_cl3d_clusters);
  tree->SetBranchAddress("cl_mipPt",          &_cl_MIPpt);
  tree->SetBranchAddress("cl_HGClayer",       &_cl_HGClayer);

  cout<<"n="<<nentries<<endl;

  for(int i=0;i<nentries;i++){

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    _genele_C3D = 0;
    
    _gen_pt = 0;
    _gen_eta = 0;
    
    _cl3d_clusters = 0;
    _cl_MIPpt = 0;
    _cl_HGClayer = 0;
    
    tree->GetEntry(i);

    for(unsigned int i_gen=0; i_gen<(*_genele_C3D).size(); i_gen++){

      int i_c3d = (*_genele_C3D)[i_gen];

      if(i_c3d<0) continue;
      if(abs((*_gen_eta)[i_gen])<1.5 || abs((*_gen_eta)[i_gen])>2.9) continue;

      out<<(*_gen_pt)[i_gen]<<" ";
      out<<(*_gen_eta)[i_gen]<<" ";

      vector<float> c3d_layer_MIPpt(53);

      for(auto & i_c2d : (*_cl3d_clusters)[i_c3d]){      
	c3d_layer_MIPpt[(*_cl_HGClayer)[i_c2d]] += (*_cl_MIPpt)[i_c2d];	
      }
      
  
      for(unsigned int i_layer=0; i_layer<14; i_layer++)
	out<<c3d_layer_MIPpt[2*i_layer+1]<<" ";
      for(unsigned int i_layer=29; i_layer<53; i_layer++)
	out<<c3d_layer_MIPpt[i_layer]<<" ";
      out<<endl;


    }


  }
  

  return;

}




void write_all(){

 
  write_ele("/vols/cms/tstreble/HGC_ntuples/SingleEle_PU200_C2D_dR/ele_ntuples/ntuple_ele_*.root","HGCalTriggerNtupleEle","test_ele_PU200.txt");


}

