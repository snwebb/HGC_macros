#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TLorentzVector.h>
#include <TMath.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <TMatrixD.h>
#include "Helpers.C"
#include "TH1F.h"

using namespace std;

void write_jets(TString filename, TString treename,
		TString fileout){


  std::ofstream out(fileout);

  TChain * tree = new TChain(treename);
  tree->Add(filename);
  int nentries = tree->GetEntries();

  TChain * tree2 = new TChain("jets");
  tree2->Add(filename);
  int nentries2 = tree2->GetEntries();
  
  vector<int>* _VBF_parton_jets;
  vector<int>* _VBF_parton_genjet;

  vector<float>* _genjet_pt;
  vector<float>* _genjet_eta;
  
  vector<vector<int> >* _jets_cl3d;
  vector<vector<unsigned int> >* _cl3d_clusters;
  vector<float>* _cl_MIPpt;
  vector<int>* _cl_HGClayer;

  
  tree->SetBranchAddress("VBF_parton_jets",   &_VBF_parton_jets);
  tree->SetBranchAddress("VBF_parton_genjet", &_VBF_parton_genjet);

  tree->SetBranchAddress("genjet_pt",         &_genjet_pt);
  tree->SetBranchAddress("genjet_eta",        &_genjet_eta);

  if(treename=="jets" || treename=="HGCalTriggerNtupleJet")
    tree->SetBranchAddress("jets_cl3d",         &_jets_cl3d);
  else
    tree2->SetBranchAddress("jets_cl3d",         &_jets_cl3d);
  tree->SetBranchAddress("cl3d_clusters",     &_cl3d_clusters);
  if(treename=="HGCalTriggerNtupleJet")
    tree->SetBranchAddress("cl_mipPt",          &_cl_MIPpt);
  else
    tree->SetBranchAddress("cl_MIPpt",          &_cl_MIPpt);
  tree->SetBranchAddress("cl_HGClayer",       &_cl_HGClayer);

  cout<<"n="<<nentries<<endl;
  nentries = 1;

  for(int i=0;i<nentries;i++){

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    _VBF_parton_jets = 0;
    _VBF_parton_genjet = 0;
    
    _genjet_pt = 0;
    _genjet_eta = 0;
    
    _jets_cl3d = 0;
    _cl3d_clusters = 0;
    _cl_MIPpt = 0;
    _cl_HGClayer = 0;
    
    tree->GetEntry(i);
    if(treename!="jets")
      tree2->GetEntry(i);

    for(unsigned int i_VBF=0; i_VBF<(*_VBF_parton_jets).size(); i_VBF++){

      int i_gen = (*_VBF_parton_genjet)[i_VBF];
      int i_jet = (*_VBF_parton_jets)[i_VBF];

      if(i_jet<0 || i_gen<0) continue;
      if(abs((*_genjet_eta)[i_gen])<1.5 || abs((*_genjet_eta)[i_gen])>2.9) continue;

      out<<(*_genjet_pt)[i_gen]<<" ";
      out<<(*_genjet_eta)[i_gen]<<" ";
      
      vector<float> jet_layer_MIPpt(53);

      for(auto & i_c3d : (*_jets_cl3d)[i_jet]){
	for(auto & i_c2d : (*_cl3d_clusters)[i_c3d]){      
	  //cout<<"layer="<<(*_cl_HGClayer)[i_c2d]<<" MIPpt="<<(*_cl_MIPpt)[i_c2d]<<endl;
	  jet_layer_MIPpt[(*_cl_HGClayer)[i_c2d]] += (*_cl_MIPpt)[i_c2d];
	}
      }

      
  
      for(unsigned int i_layer=0; i_layer<14; i_layer++)
	out<<jet_layer_MIPpt[2*i_layer+1]<<" ";
      for(unsigned int i_layer=29; i_layer<53; i_layer++)
	out<<jet_layer_MIPpt[i_layer]<<" ";
      out<<endl;


    }


  }
  

  return;

}






void write_all(){

  //write_jets("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","jets_GEO_PU0.txt");
  write_jets("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR_JetPU0cal/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","test.txt");


}







void write_jets_ZB(TString filename, TString treename, float pt_cut,
		   TString fileout, int nevents, int skipevents){


  std::ofstream out(fileout);

  TChain * tree = new TChain(treename);
  tree->Add(filename);
  int nentries = tree->GetEntries();

  TChain * tree2 = new TChain("jets");
  tree2->Add(filename);
  int nentries2 = tree2->GetEntries();
  
  vector<float>* _jets_raw_Luca_pt;
  vector<float>* _jets_raw_eta;

  vector<vector<int> >* _jets_cl3d;
  vector<vector<unsigned int> >* _cl3d_clusters;
  vector<float>* _cl_MIPpt;
  vector<int>* _cl_HGClayer;


  if(treename=="jets"){
    tree->SetBranchAddress("jets_cl3d",         &_jets_cl3d);
    tree->SetBranchAddress("jets_raw_Luca_pt",  &_jets_raw_Luca_pt);
    tree->SetBranchAddress("jets_raw_eta",      &_jets_raw_eta);
  }
  else{
    tree2->SetBranchAddress("jets_cl3d",        &_jets_cl3d);
    tree2->SetBranchAddress("jets_raw_Luca_pt",  &_jets_raw_Luca_pt);
    tree2->SetBranchAddress("jets_raw_eta",      &_jets_raw_eta);
  }

  tree->SetBranchAddress("cl3d_clusters",       &_cl3d_clusters);
  tree->SetBranchAddress("cl_MIPpt",            &_cl_MIPpt);
  tree->SetBranchAddress("cl_HGClayer",         &_cl_HGClayer);

  cout<<"n="<<nentries<<endl;
  
  //for(int i=0;i<nentries;i++){
  for(int i=skipevents;i<min(nentries,skipevents+nevents);i++){

    if(i%1000==0)
      cout<<"i="<<i<<endl;
    
    _jets_cl3d = 0;
    _jets_raw_Luca_pt = 0;
    _jets_raw_eta = 0;
    _cl3d_clusters = 0;
    _cl_MIPpt = 0;
    _cl_HGClayer = 0;
    
    tree->GetEntry(i);
    if(treename!="jets")
      tree2->GetEntry(i);

    for(unsigned int i_jet=0; i_jet<(*_jets_raw_Luca_pt).size(); i_jet++){

      if(abs((*_jets_raw_eta)[i_jet])<1.5 || abs((*_jets_raw_eta)[i_jet])>2.9 || (*_jets_raw_Luca_pt)[i_jet]<pt_cut) continue;

      out<<(*_jets_raw_Luca_pt)[i_jet]<<" ";
      out<<(*_jets_raw_eta)[i_jet]<<" ";

      vector<float> jet_layer_MIPpt(53);

      for(auto & i_c3d : (*_jets_cl3d)[i_jet]){
	for(auto & i_c2d : (*_cl3d_clusters)[i_c3d]){      
	  //cout<<"layer="<<(*_cl_HGClayer)[i_c2d]<<" MIPpt="<<(*_cl_MIPpt)[i_c2d]<<endl;
	  jet_layer_MIPpt[(*_cl_HGClayer)[i_c2d]] += (*_cl_MIPpt)[i_c2d];
	}
      }

      
  
      for(unsigned int i_layer=0; i_layer<14; i_layer++)
	out<<jet_layer_MIPpt[2*i_layer+1]<<" ";
      for(unsigned int i_layer=29; i_layer<53; i_layer++)
	out<<jet_layer_MIPpt[i_layer]<<" ";
      out<<endl;


    }


  }
  

  return;

}







void write_all_ZB(){

  //write_jets_ZB("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_*.root","jets",50,"jets_ZB_NN_PU200_ptcut50_1.txt",25000,0);
  /*write_jets_ZB("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_*.root","jets",50,"jets_ZB_NN_PU200_ptcut50_2.txt",25000,25000);
    write_jets_ZB("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_*.root","jets",50,"jets_ZB_NN_PU200_ptcut50_3.txt",25000,50000);*/

  //write_jets_ZB("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_*.root","jets",80,"jets_ZB_NN_PU200_ptcut80_1.txt",25000,0);
  /*write_jets_ZB("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_*.root","jets",80,"jets_ZB_NN_PU200_ptcut80_2.txt",25000,25000); 
    write_jets_ZB("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_*.root","jets",80,"jets_ZB_NN_PU200_ptcut80_3.txt",25000,50000);*/
  

  //write_jets_ZB("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_jet_ntuples/ntuple_calibr_jet_*.root","HGCalTriggerNtuple",50,"jets_ZB_GEO_PU200_ptcut50_1.txt",25000,0);  
  //write_jets_ZB("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_jet_ntuples/ntuple_calibr_jet_*.root","HGCalTriggerNtuple",50,"jets_ZB_GEO_PU200_ptcut50_2.txt",25000,25000);  
  //write_jets_ZB("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_jet_ntuples/ntuple_calibr_jet_*.root","HGCalTriggerNtuple",50,"jets_ZB_GEO_PU200_ptcut50_3.txt",25000,50000);
  

  //write_jets_ZB("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_jet_ntuples/ntuple_calibr_jet_*.root","HGCalTriggerNtuple",80,"jets_ZB_GEO_PU200_ptcut80_1.txt",25000,0);
  //write_jets_ZB("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_jet_ntuples/ntuple_calibr_jet_*.root","HGCalTriggerNtuple",80,"jets_ZB_GEO_PU200_ptcut80_2.txt",25000,25000);
  write_jets_ZB("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_jet_ntuples/ntuple_calibr_jet_*.root","HGCalTriggerNtuple",80,"jets_ZB_GEO_PU200_ptcut80_3.txt",25000,50000);


}








pair<vector<float>,map<pair<int,int>,float> > prod_Ei_Eij_VBF(TString filename, float pt_cut){

  TChain * tree = new TChain("HGCalTriggerNtupleJet");
  tree->Add(filename);
  int nentries = tree->GetEntries();

  vector<int>* _VBF_parton_jets;
  vector<int>* _VBF_parton_genjet;

  vector<float>* _genjet_pt;
  vector<float>* _genjet_eta;  


  vector<vector<int> >* _jets_cl3d;
  vector<float>* _jets_mipPt;
  vector<vector<unsigned int> >* _cl3d_clusters;
  vector<float>* _cl_MIPpt;
  vector<int>* _cl_HGClayer;


  tree->SetBranchAddress("VBF_parton_jets",        &_VBF_parton_jets);
  tree->SetBranchAddress("VBF_parton_genjet",      &_VBF_parton_genjet);
  
  tree->SetBranchAddress("genjet_pt",        &_genjet_pt);
  tree->SetBranchAddress("genjet_eta",       &_genjet_eta);

  tree->SetBranchAddress("jets_cl3d",        &_jets_cl3d);
  tree->SetBranchAddress("jets_mipPt",        &_jets_mipPt);

  tree->SetBranchAddress("cl3d_clusters",       &_cl3d_clusters);
  tree->SetBranchAddress("cl_mipPt",            &_cl_MIPpt);
  tree->SetBranchAddress("cl_HGClayer",         &_cl_HGClayer);
  

  cout<<"n="<<nentries<<endl;

  vector<float> Ei(38);
  map<pair<int,int>,float> EiEj;
  int njets = 0;

  for(int i=0;i<nentries;i++){

    if(i%1000==0)
      cout<<"i="<<i<<endl;
    
    _VBF_parton_jets = 0;
    _VBF_parton_genjet = 0;

    _genjet_pt = 0;
    _genjet_eta = 0; 

    _jets_cl3d = 0;    
    _jets_mipPt = 0;

    _cl3d_clusters = 0;
    _cl_MIPpt = 0;
    _cl_HGClayer = 0;

    
    tree->GetEntry(i);

    for(unsigned int i_VBF=0; i_VBF<(*_VBF_parton_jets).size(); i_VBF++){

      int i_gen = (*_VBF_parton_genjet)[i_VBF];
      int i_jet = (*_VBF_parton_jets)[i_VBF];

      if(i_jet<0 || i_gen<0) continue;
      if(abs((*_genjet_eta)[i_gen])<1.5 || abs((*_genjet_eta)[i_gen])>2.9 || (*_genjet_pt)[i_gen]<pt_cut) continue;

      vector<float> jet_layer_MIPpt(53);

      for(auto & i_c3d : (*_jets_cl3d)[i_jet]){
	for(auto & i_c2d : (*_cl3d_clusters)[i_c3d]){      
	  //cout<<"layer="<<(*_cl_HGClayer)[i_c2d]<<" MIPpt="<<(*_cl_MIPpt)[i_c2d]<<endl;
	  jet_layer_MIPpt[(*_cl_HGClayer)[i_c2d]] += (*_cl_MIPpt)[i_c2d];
	}
	}
      
      for(unsigned int i=0; i<38; i++){
	int i_layer = -1;
	if(i<14) i_layer = 2*i+1;
	else i_layer = i+15;
	
	Ei[i]+=jet_layer_MIPpt[i_layer]/(*_jets_mipPt)[i_jet];

	for(unsigned int j=0; j<38; j++){
	  int j_layer = -1;
	  if(j<14) j_layer = 2*j+1;
	  else j_layer = j+15;
	  
	  pair<int,int> key=make_pair(i,j);
	  EiEj[key]+=jet_layer_MIPpt[i_layer]*jet_layer_MIPpt[j_layer]/pow((*_jets_mipPt)[i_jet],2);

	}

      }
    
      njets++;

    }


  }
  

  cout<<"njets="<<njets<<endl;

  for(int i=0; i<38; i++)
    Ei[i]/=njets;
  for (std::map<pair<int,int>,float>::iterator it=EiEj.begin(); it!=EiEj.end(); ++it)
    it->second/=njets;

  pair<vector<float>,map<pair<int,int>,float> > Ei_EiEj = make_pair(Ei,EiEj);

  return Ei_EiEj;


}






pair<vector<float>,map<pair<int,int>,float> > prod_Ei_Eij_ZB(TString filename, float pt_cut){

  TChain * tree = new TChain("HGCalTriggerNtupleJet");
  tree->Add(filename);
  int nentries = tree->GetEntries();

  vector<float>* _jets_pt;

  vector<vector<int> >* _jets_cl3d;
  vector<float>* _jets_mipPt;
  vector<vector<unsigned int> >* _cl3d_clusters;
  vector<float>* _cl_MIPpt;
  vector<int>* _cl_HGClayer;

  
  tree->SetBranchAddress("jets_pt",        &_jets_pt);
  tree->SetBranchAddress("jets_cl3d",      &_jets_cl3d);
  tree->SetBranchAddress("jets_mipPt",     &_jets_mipPt);

  tree->SetBranchAddress("cl3d_clusters",       &_cl3d_clusters);
  tree->SetBranchAddress("cl_mipPt",            &_cl_MIPpt);
  tree->SetBranchAddress("cl_HGClayer",         &_cl_HGClayer);

  cout<<"n="<<nentries<<endl;

  vector<float> Ei(38);
  map<pair<int,int>,float> EiEj;
  int njets = 0;
  
  for(int i=0;i<nentries;i++){

    if(i%1000==0)
      cout<<"i="<<i<<endl;    

    _jets_pt = 0;
    _jets_mipPt = 0;

    _jets_cl3d = 0;    
    _cl3d_clusters = 0;
    _cl_MIPpt = 0;
    _cl_HGClayer = 0;
    
    tree->GetEntry(i);

    for(unsigned int i_jet=0; i_jet<(*_jets_pt).size(); i_jet++){

      if((*_jets_pt)[i_jet]<pt_cut) continue;

      vector<float> jet_layer_MIPpt(53);

      for(auto & i_c3d : (*_jets_cl3d)[i_jet]){
	for(auto & i_c2d : (*_cl3d_clusters)[i_c3d]){      
	  //cout<<"layer="<<(*_cl_HGClayer)[i_c2d]<<" MIPpt="<<(*_cl_MIPpt)[i_c2d]<<endl;
	  jet_layer_MIPpt[(*_cl_HGClayer)[i_c2d]] += (*_cl_MIPpt)[i_c2d];
	}
      }
      
      for(unsigned int i=0; i<38; i++){
	int i_layer = -1;
	if(i<14) i_layer = 2*i+1;
	else i_layer = i+15;
	
	Ei[i]+=jet_layer_MIPpt[i_layer]/(*_jets_mipPt)[i_jet];

	for(unsigned int j=0; j<38; j++){
	  int j_layer = -1;
	  if(j<14) j_layer = 2*j+1;
	  else j_layer = j+15;
	  
	  pair<int,int> key=make_pair(i,j);
	  EiEj[key]+=jet_layer_MIPpt[i_layer]*jet_layer_MIPpt[j_layer]/pow((*_jets_mipPt)[i_jet],2);
	}

      }
    
      njets++;

    }


  }
  

  cout<<"njets="<<njets<<endl;

  for(int i=0; i<38; i++)
    Ei[i]/=njets;
  for (std::map<pair<int,int>,float>::iterator it=EiEj.begin(); it!=EiEj.end(); ++it)
    it->second/=njets;


  pair<vector<float>,map<pair<int,int>,float> > Ei_EiEj = make_pair(Ei,EiEj);

  return Ei_EiEj;


}





vector<float> prod_weight_Fisher(TString filename_sig,TString filename_bkg){

  pair<vector<float>,map<pair<int,int>,float> > Ei_EiEj_sig = prod_Ei_Eij_VBF(filename_sig,20);
  pair<vector<float>,map<pair<int,int>,float> > Ei_EiEj_bkg = prod_Ei_Eij_ZB(filename_bkg,20);
  
  vector<float> Ei_sig = Ei_EiEj_sig.first;
  vector<float> Ei_bkg = Ei_EiEj_bkg.first;
  map<pair<int,int>,float> EiEj_sig = Ei_EiEj_sig.second;
  map<pair<int,int>,float> EiEj_bkg = Ei_EiEj_bkg.second;

  TMatrixD mu_sig(38,1);
  TMatrixD mu_bkg(38,1);
  TMatrixD sigma_sig(38,38);
  TMatrixD sigma_bkg(38,38);

  for(unsigned int i=0;i<38;i++){
    mu_sig(i,0) = Ei_sig[i];
    mu_bkg(i,0) = Ei_bkg[i];
    for(unsigned int j=0;j<38;j++){
      pair<int,int> key = make_pair(i,j);
      sigma_sig(i,j) = EiEj_sig[key]-Ei_sig[i]*Ei_sig[j];
      sigma_bkg(i,j) = EiEj_bkg[key]-Ei_bkg[i]*Ei_bkg[j];
    }
  }

  cout<<"mu_sig"<<endl;
  mu_sig.Print();
  cout<<"mu_bkg"<<endl;
  mu_bkg.Print();
  cout<<"sigma_sig"<<endl;
  sigma_sig.Print();
  cout<<"sigma_bkg"<<endl;
  sigma_bkg.Print();

  TMatrixD mu_diff = mu_sig - mu_bkg;
  TMatrixD sigma_sum = sigma_sig + sigma_bkg;
  sigma_sum.Invert();
  TMatrixD weights = sigma_sum*mu_diff;


  std::ofstream out("weights_Fisher.txt");


  vector<float> w(38);
  out<<"{";
  for(unsigned int i=0;i<38;i++){
    w[i] = weights(i,0);
    if(i<37)
      out<<w[i]<<",";
    else
      out<<w[i]<<"}"<<endl;
  }
 


  return w;

}
				 





TH1F* TH1_Fisher_VBF(TString filename, float pt_cut, vector<float> weights){

  TH1F* h = new TH1F("h","h",1000,-10,10);


  TChain * tree = new TChain("HGCalTriggerNtupleJet");
  tree->Add(filename);
  int nentries = tree->GetEntries();

  vector<int>* _VBF_parton_jets;
  vector<int>* _VBF_parton_genjet;

  vector<float>* _genjet_pt;
  vector<float>* _genjet_eta;  


  vector<vector<int> >* _jets_cl3d;
  vector<float>* _jets_mipPt;
  vector<vector<unsigned int> >* _cl3d_clusters;
  vector<float>* _cl_MIPpt;
  vector<int>* _cl_HGClayer;

  tree->SetBranchAddress("VBF_parton_jets",        &_VBF_parton_jets);
  tree->SetBranchAddress("VBF_parton_genjet",      &_VBF_parton_genjet);
  
  tree->SetBranchAddress("genjet_pt",        &_genjet_pt);
  tree->SetBranchAddress("genjet_eta",       &_genjet_eta);

  tree->SetBranchAddress("jets_cl3d",        &_jets_cl3d);
  tree->SetBranchAddress("jets_mipPt",        &_jets_mipPt);

  tree->SetBranchAddress("cl3d_clusters",       &_cl3d_clusters);
  tree->SetBranchAddress("cl_mipPt",            &_cl_MIPpt);
  tree->SetBranchAddress("cl_HGClayer",         &_cl_HGClayer);

  cout<<"n="<<nentries<<endl;

  int njets = 0;

  for(int i=0;i<nentries;i++){

    if(i%1000==0)
      cout<<"i="<<i<<endl;
    
    _VBF_parton_jets = 0;
    _VBF_parton_genjet = 0;

    _genjet_pt = 0;
    _genjet_eta = 0; 

    _jets_cl3d = 0;    
    _jets_mipPt = 0;

    _cl3d_clusters = 0;
    _cl_MIPpt = 0;
    _cl_HGClayer = 0;
    
    tree->GetEntry(i);

    for(unsigned int i_VBF=0; i_VBF<(*_VBF_parton_jets).size(); i_VBF++){

      int i_gen = (*_VBF_parton_genjet)[i_VBF];
      int i_jet = (*_VBF_parton_jets)[i_VBF];

      if(i_jet<0 || i_gen<0) continue;
      if(abs((*_genjet_eta)[i_gen])<1.5 || abs((*_genjet_eta)[i_gen])>2.9 || (*_genjet_pt)[i_gen]<pt_cut) continue;

      vector<float> jet_layer_MIPpt(53);

      for(auto & i_c3d : (*_jets_cl3d)[i_jet]){
	for(auto & i_c2d : (*_cl3d_clusters)[i_c3d]){      
	  //cout<<"layer="<<(*_cl_HGClayer)[i_c2d]<<" MIPpt="<<(*_cl_MIPpt)[i_c2d]<<endl;
	  jet_layer_MIPpt[(*_cl_HGClayer)[i_c2d]] += (*_cl_MIPpt)[i_c2d];
	}
      }
      
      float Fisher = 0;

      for(unsigned int i=0; i<38; i++){
	int i_layer = -1;
	if(i<14) i_layer = 2*i+1;
	else i_layer = i+15;
	
	Fisher+=weights[i]*jet_layer_MIPpt[i_layer]/(*_jets_mipPt)[i_jet];

      }
    
      //cout<<"Fisher="<<Fisher<<endl;
      h->Fill(Fisher);

      njets++;

    }


  }
  

  cout<<"njets="<<njets<<endl;

  return h;


}







TH1F* TH1_Fisher_ZB(TString filename, float pt_cut, vector<float> weights){

  TH1F* g = new TH1F("g","g",1000,-10,10);

  TChain * tree = new TChain("HGCalTriggerNtupleJet");
  tree->Add(filename);
  int nentries = tree->GetEntries();

  vector<float>* _jets_pt;

  vector<vector<int> >* _jets_cl3d;
  vector<float>* _jets_mipPt;
  vector<vector<unsigned int> >* _cl3d_clusters;
  vector<float>* _cl_MIPpt;
  vector<int>* _cl_HGClayer;

  
  tree->SetBranchAddress("jets_pt",        &_jets_pt);
  tree->SetBranchAddress("jets_cl3d",      &_jets_cl3d);
  tree->SetBranchAddress("jets_mipPt",     &_jets_mipPt);

  tree->SetBranchAddress("cl3d_clusters",       &_cl3d_clusters);
  tree->SetBranchAddress("cl_mipPt",            &_cl_MIPpt);
  tree->SetBranchAddress("cl_HGClayer",         &_cl_HGClayer);

  cout<<"n="<<nentries<<endl;

  int njets = 0;
  
  for(int i=0;i<nentries;i++){

    if(i%1000==0)
      cout<<"i="<<i<<endl;    

    _jets_pt = 0;
    _jets_mipPt = 0;

    _jets_cl3d = 0;    
    _cl3d_clusters = 0;
    _cl_MIPpt = 0;
    _cl_HGClayer = 0;
    
    tree->GetEntry(i);

    for(unsigned int i_jet=0; i_jet<(*_jets_pt).size(); i_jet++){

      if((*_jets_pt)[i_jet]<pt_cut) continue;

      vector<float> jet_layer_MIPpt(53);

      for(auto & i_c3d : (*_jets_cl3d)[i_jet]){
	for(auto & i_c2d : (*_cl3d_clusters)[i_c3d]){      
	  //cout<<"layer="<<(*_cl_HGClayer)[i_c2d]<<" MIPpt="<<(*_cl_MIPpt)[i_c2d]<<endl;
	  jet_layer_MIPpt[(*_cl_HGClayer)[i_c2d]] += (*_cl_MIPpt)[i_c2d];
	}
      }

      float Fisher=0;
      
      for(unsigned int i=0; i<38; i++){
	int i_layer = -1;
	if(i<14) i_layer = 2*i+1;
	else i_layer = i+15;
	
	Fisher+=weights[i]*jet_layer_MIPpt[i_layer]/(*_jets_mipPt)[i_jet];


      }

      g->Fill(Fisher);
    
      njets++;

    }


  }
  

  cout<<"njets="<<njets<<endl;

  return g;


}


