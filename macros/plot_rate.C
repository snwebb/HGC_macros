
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <iomanip>  
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TGraphErrors.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TGaxis.h>
#include <TLatex.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TLorentzVector.h>
#include <TObject.h>
#include "Helpers.C"

#include <algorithm>

using namespace std;



vector<TH1F*> histo_ET_max_Mjj(TString filename, float mjj, float PU=200.){

  TChain * tree = new TChain("jets");
  tree->Add(filename);
  tree->SetBranchStatus("*",0);
 
  TH1F* h_SingleJet=new TH1F("h_SingleJet","h_SingleJet",1000,0,1000);
  TH1F* h_DoubleJet=new TH1F("h_DoubleJet","h_DoubleJet",1000,0,1000);
  TH1F* h_DoubleJet_pm=new TH1F("h_DoubleJet_pm","h_DoubleJet_pm",1000,0,1000);
  TH1F* h_DoubleJet_pm_mjj=new TH1F("h_DoubleJet_pm_mjj","h_DoubleJet_pm_mjj",1000,0,1000);
  

  vector<float>* _jets_raw_Luca_pt;
  vector<float>* _jets_PU_subtr_cone_C3D;
  vector<float>* _jets_eta;
  vector<float>* _jets_phi;

  tree->SetBranchAddress("jets_raw_Luca_pt", &_jets_raw_Luca_pt);
  tree->SetBranchAddress("jets_PU_subtr_cone_C3D", &_jets_PU_subtr_cone_C3D);
  tree->SetBranchAddress("jets_eta", &_jets_eta);
  tree->SetBranchAddress("jets_phi", &_jets_phi);


  Long64_t nentries = tree->GetEntries();
  cout<<nentries<<" events"<<endl;

  for (int i=0;i<nentries;i++) {

    if(i%1000==0)
      cout<<"i="<<i<<endl;
    
    _jets_raw_Luca_pt = 0;
    _jets_PU_subtr_cone_C3D = 0;
    _jets_eta = 0;
    _jets_phi = 0;

    tree->GetEntry(i);

    float pt_max1 = 0.;
    float pt_max2 = 0.;    
    TLorentzVector jet_max_plus;
    jet_max_plus.SetPtEtaPhiM(0,0,0,0);
    TLorentzVector jet_max_minus;
    jet_max_minus.SetPtEtaPhiM(0,0,0,0);

    TLorentzVector jet_max1;
    jet_max1.SetPtEtaPhiM(0,0,0,0);
    TLorentzVector jet_max2;
    jet_max2.SetPtEtaPhiM(0,0,0,0);
    
    for(unsigned int ijet=0; ijet<(*_jets_raw_Luca_pt).size(); ijet++){
            
      TLorentzVector jet;
      float pt = (4.4374 -0.948102 * log(max((*_jets_raw_Luca_pt)[ijet]-PU/200.*2*(*_jets_PU_subtr_cone_C3D)[ijet],20.)) + .0686934* pow(log(max((*_jets_raw_Luca_pt)[ijet]-PU/200.*2*(*_jets_PU_subtr_cone_C3D)[ijet],20.)),2) ) * max((*_jets_raw_Luca_pt)[ijet]-PU/200.*2*(*_jets_PU_subtr_cone_C3D)[ijet],0.);
      jet.SetPtEtaPhiM(pt, (*_jets_eta)[ijet], (*_jets_phi)[ijet], 0);

      if(pt>pt_max1){
	pt_max2 = pt_max1;
	pt_max1 = pt;
	jet_max2 = jet_max1;
	jet_max1 = jet;
      }
      else if(pt>pt_max2){
	pt_max2 = pt;
	jet_max2 = jet;
      }

      if((*_jets_eta)[ijet]>0 && jet.Pt()>jet_max_plus.Pt())
	jet_max_plus = jet;
      if((*_jets_eta)[ijet]<0 && jet.Pt()>jet_max_minus.Pt())
	jet_max_minus = jet;    

    }

    h_SingleJet->Fill(pt_max1);
    h_DoubleJet->Fill(pt_max2);
    h_DoubleJet_pm->Fill(min(jet_max_plus.Pt(),jet_max_minus.Pt()));    
    //if(jet_max1.Eta()*jet_max2.Eta()<0)
    //  h_DoubleJet_pm->Fill(pt_max2);    

    if((jet_max_plus+jet_max_minus).M()>mjj)
      h_DoubleJet_pm_mjj->Fill(min(jet_max_plus.Pt(),jet_max_minus.Pt()));
      //if((jet_max1+jet_max2).M()>mjj)
      //h_DoubleJet_pm_mjj->Fill(pt_max2);

  }

  /*h_SingleJet->Scale(1./nentries);
  h_DoubleJet->Scale(1./nentries);
  h_DoubleJet_pm->Scale(1./nentries);
  h_DoubleJet_pm_mjj->Scale(1./nentries);*/

  vector<TH1F*> histos;
  histos.push_back(h_SingleJet);
  histos.push_back(h_DoubleJet);
  histos.push_back(h_DoubleJet_pm);
  histos.push_back(h_DoubleJet_pm_mjj);
  

  return histos;

}








vector<TH1F*> histo_ET_max_Mjj_GEO(TString filename, float mjj, float PU=200.){

  TChain * tree = new TChain("jets");
  tree->Add(filename);
  tree->SetBranchStatus("*",0);
 
  TH1F* h_SingleJet=new TH1F("h_SingleJet","h_SingleJet",1000,0,1000);
  TH1F* h_DoubleJet=new TH1F("h_DoubleJet","h_DoubleJet",1000,0,1000);
  TH1F* h_DoubleJet_pm=new TH1F("h_DoubleJet_pm","h_DoubleJet_pm",1000,0,1000);
  TH1F* h_DoubleJet_pm_mjj=new TH1F("h_DoubleJet_pm_mjj","h_DoubleJet_pm_mjj",1000,0,1000);
  

  vector<float>* _jets_raw_Luca_pt;
  vector<float>* _jets_PU_subtr_cone_GEO_C3D;
  vector<float>* _jets_eta;
  vector<float>* _jets_phi;

  tree->SetBranchAddress("jets_raw_Luca_pt", &_jets_raw_Luca_pt);
  tree->SetBranchAddress("jets_PU_subtr_cone_GEO_C3D", &_jets_PU_subtr_cone_GEO_C3D);
  tree->SetBranchAddress("jets_eta", &_jets_eta);
  tree->SetBranchAddress("jets_phi", &_jets_phi);


  Long64_t nentries = tree->GetEntries();
  cout<<nentries<<" events"<<endl;

  for (int i=0;i<nentries;i++) {

    if(i%1000==0)
      cout<<"i="<<i<<endl;
    
    _jets_raw_Luca_pt = 0;
    _jets_PU_subtr_cone_GEO_C3D = 0;
    _jets_eta = 0;
    _jets_phi = 0;

    tree->GetEntry(i);

    float pt_max1 = 0.;
    float pt_max2 = 0.;    
    TLorentzVector jet_max_plus;
    jet_max_plus.SetPtEtaPhiM(0,0,0,0);
    TLorentzVector jet_max_minus;
    jet_max_minus.SetPtEtaPhiM(0,0,0,0);

    TLorentzVector jet_max1;
    jet_max1.SetPtEtaPhiM(0,0,0,0);
    TLorentzVector jet_max2;
    jet_max2.SetPtEtaPhiM(0,0,0,0);
    
    for(unsigned int ijet=0; ijet<(*_jets_raw_Luca_pt).size(); ijet++){
            
      TLorentzVector jet;
      float pt = 1.06*(4.4374 -0.948102 * log(max((*_jets_raw_Luca_pt)[ijet]-PU/200.*2*(*_jets_PU_subtr_cone_GEO_C3D)[ijet],0.)) + .0686934* pow(log(max((*_jets_raw_Luca_pt)[ijet]-PU/200.*2*(*_jets_PU_subtr_cone_GEO_C3D)[ijet],0.)),2) ) * max((*_jets_raw_Luca_pt)[ijet]-PU/200.*2*(*_jets_PU_subtr_cone_GEO_C3D)[ijet],0.);
      jet.SetPtEtaPhiM(pt, (*_jets_eta)[ijet], (*_jets_phi)[ijet], 0);

      if(pt>pt_max1){
	pt_max2 = pt_max1;
	pt_max1 = pt;
	jet_max2 = jet_max1;
	jet_max1 = jet;
      }
      else if(pt>pt_max2){
	pt_max2 = pt;
	jet_max2 = jet;
      }

      if((*_jets_eta)[ijet]>0 && jet.Pt()>jet_max_plus.Pt())
	jet_max_plus = jet;
      if((*_jets_eta)[ijet]<0 && jet.Pt()>jet_max_minus.Pt())
	jet_max_minus = jet;    

    }

    h_SingleJet->Fill(pt_max1);
    h_DoubleJet->Fill(pt_max2);
    h_DoubleJet_pm->Fill(min(jet_max_plus.Pt(),jet_max_minus.Pt()));    
    //if(jet_max1.Eta()*jet_max2.Eta()<0)
    //  h_DoubleJet_pm->Fill(pt_max2);    

    if((jet_max_plus+jet_max_minus).M()>mjj)
      h_DoubleJet_pm_mjj->Fill(min(jet_max_plus.Pt(),jet_max_minus.Pt()));
      //if((jet_max1+jet_max2).M()>mjj)
      //h_DoubleJet_pm_mjj->Fill(pt_max2);

  }

  /*h_SingleJet->Scale(1./nentries);
  h_DoubleJet->Scale(1./nentries);
  h_DoubleJet_pm->Scale(1./nentries);
  h_DoubleJet_pm_mjj->Scale(1./nentries);*/

  vector<TH1F*> histos;
  histos.push_back(h_SingleJet);
  histos.push_back(h_DoubleJet);
  histos.push_back(h_DoubleJet_pm);
  histos.push_back(h_DoubleJet_pm_mjj);
  

  return histos;

}





vector<TH1F*> histo_ET_max_Mjj_GEO_recal(TString filename, float mjj, float PU=200.){

  TChain * tree = new TChain("HGCalTriggerNtupleJet");
  tree->Add(filename);
  tree->SetBranchStatus("*",0);
 
  TH1F* h_SingleJet=new TH1F("h_SingleJet","h_SingleJet",1000,0,1000);
  TH1F* h_DoubleJet=new TH1F("h_DoubleJet","h_DoubleJet",1000,0,1000);
  TH1F* h_DoubleJet_pm=new TH1F("h_DoubleJet_pm","h_DoubleJet_pm",1000,0,1000);
  TH1F* h_DoubleJet_pm_mjj=new TH1F("h_DoubleJet_pm_mjj","h_DoubleJet_pm_mjj",1000,0,1000);
  

  vector<float>* _jets_pt;
  vector<float>* _jets_PU_subtr_cone_GEO_C3D;
  vector<float>* _jets_eta;
  vector<float>* _jets_phi;

  tree->SetBranchAddress("jets_pt", &_jets_pt);
  tree->SetBranchAddress("jets_PU_subtr_cone_GEO_C3D", &_jets_PU_subtr_cone_GEO_C3D);
  tree->SetBranchAddress("jets_eta", &_jets_eta);
  tree->SetBranchAddress("jets_phi", &_jets_phi);


  Long64_t nentries = tree->GetEntries();
  cout<<nentries<<" events"<<endl;

  for (int i=0;i<nentries;i++) {

    if(i%1000==0)
      cout<<"i="<<i<<endl;
    
    _jets_pt = 0;
    _jets_PU_subtr_cone_GEO_C3D = 0;
    _jets_eta = 0;
    _jets_phi = 0;

    tree->GetEntry(i);

    float pt_max1 = 0.;
    float pt_max2 = 0.;    
    TLorentzVector jet_max_plus;
    jet_max_plus.SetPtEtaPhiM(0,0,0,0);
    TLorentzVector jet_max_minus;
    jet_max_minus.SetPtEtaPhiM(0,0,0,0);

    TLorentzVector jet_max1;
    jet_max1.SetPtEtaPhiM(0,0,0,0);
    TLorentzVector jet_max2;
    jet_max2.SetPtEtaPhiM(0,0,0,0);
    
    for(unsigned int ijet=0; ijet<(*_jets_pt).size(); ijet++){
            
      TLorentzVector jet;
      float pt = 1.1*1.04*(4.16098 -1.00815e+00 * log(max((*_jets_pt)[ijet]-PU/200.*3*(*_jets_PU_subtr_cone_GEO_C3D)[ijet],0.)) + 7.59202e-02* pow(log(max((*_jets_pt)[ijet]-PU/200.*3*(*_jets_PU_subtr_cone_GEO_C3D)[ijet],0.)),2) ) * max((*_jets_pt)[ijet]-PU/200.*3*(*_jets_PU_subtr_cone_GEO_C3D)[ijet],0.);
      jet.SetPtEtaPhiM(pt, (*_jets_eta)[ijet], (*_jets_phi)[ijet], 0);

      if(pt>pt_max1){
	pt_max2 = pt_max1;
	pt_max1 = pt;
	jet_max2 = jet_max1;
	jet_max1 = jet;
      }
      else if(pt>pt_max2){
	pt_max2 = pt;
	jet_max2 = jet;
      }

      if((*_jets_eta)[ijet]>0 && jet.Pt()>jet_max_plus.Pt())
	jet_max_plus = jet;
      if((*_jets_eta)[ijet]<0 && jet.Pt()>jet_max_minus.Pt())
	jet_max_minus = jet;    

    }

    h_SingleJet->Fill(pt_max1);
    h_DoubleJet->Fill(pt_max2);
    h_DoubleJet_pm->Fill(min(jet_max_plus.Pt(),jet_max_minus.Pt()));    
    //if(jet_max1.Eta()*jet_max2.Eta()<0)
    //  h_DoubleJet_pm->Fill(pt_max2);    

    if((jet_max_plus+jet_max_minus).M()>mjj)
      h_DoubleJet_pm_mjj->Fill(min(jet_max_plus.Pt(),jet_max_minus.Pt()));
      //if((jet_max1+jet_max2).M()>mjj)
      //h_DoubleJet_pm_mjj->Fill(pt_max2);

  }

  /*h_SingleJet->Scale(1./nentries);
  h_DoubleJet->Scale(1./nentries);
  h_DoubleJet_pm->Scale(1./nentries);
  h_DoubleJet_pm_mjj->Scale(1./nentries);*/

  vector<TH1F*> histos;
  histos.push_back(h_SingleJet);
  histos.push_back(h_DoubleJet);
  histos.push_back(h_DoubleJet_pm);
  histos.push_back(h_DoubleJet_pm_mjj);
  

  return histos;

}







vector<TH1F*> histo_ET_max_Mjj_dRNNC2D(TString filename, float mjj, float PU=200.){

  TChain * tree = new TChain("HGCalTriggerNtupleJet");
  tree->Add(filename);
  tree->SetBranchStatus("*",0);
 
  TH1F* h_SingleJet=new TH1F("h_SingleJet","h_SingleJet",1000,0,1000);
  TH1F* h_DoubleJet=new TH1F("h_DoubleJet","h_DoubleJet",1000,0,1000);
  TH1F* h_DoubleJet_pm=new TH1F("h_DoubleJet_pm","h_DoubleJet_pm",1000,0,1000);
  TH1F* h_DoubleJet_pm_mjj=new TH1F("h_DoubleJet_pm_mjj","h_DoubleJet_pm_mjj",1000,0,1000);
  

  vector<float>* _jets_pt;
  vector<float>* _jets_PU_subtr_cone_GEO_C3D;
  vector<float>* _jets_eta;
  vector<float>* _jets_phi;

  tree->SetBranchAddress("jets_pt", &_jets_pt);
  tree->SetBranchAddress("jets_PU_subtr_cone_GEO_C3D", &_jets_PU_subtr_cone_GEO_C3D);
  tree->SetBranchAddress("jets_eta", &_jets_eta);
  tree->SetBranchAddress("jets_phi", &_jets_phi);


  Long64_t nentries = tree->GetEntries();
  cout<<nentries<<" events"<<endl;

  for (int i=0;i<nentries;i++) {

    if(i%1000==0)
      cout<<"i="<<i<<endl;
    
    _jets_pt = 0;
    _jets_PU_subtr_cone_GEO_C3D = 0;
    _jets_eta = 0;
    _jets_phi = 0;

    tree->GetEntry(i);

    float pt_max1 = 0.;
    float pt_max2 = 0.;    
    TLorentzVector jet_max_plus;
    jet_max_plus.SetPtEtaPhiM(0,0,0,0);
    TLorentzVector jet_max_minus;
    jet_max_minus.SetPtEtaPhiM(0,0,0,0);

    TLorentzVector jet_max1;
    jet_max1.SetPtEtaPhiM(0,0,0,0);
    TLorentzVector jet_max2;
    jet_max2.SetPtEtaPhiM(0,0,0,0);
    
    for(unsigned int ijet=0; ijet<(*_jets_pt).size(); ijet++){
            
      TLorentzVector jet;
      float pt = 1.06*(4.98004e+00 -1.23767e+00 * log(max((*_jets_pt)[ijet]-PU/200.*2*(*_jets_PU_subtr_cone_GEO_C3D)[ijet],0.)) + 1.02929e-01* pow(log(max((*_jets_pt)[ijet]-PU/200.*2*(*_jets_PU_subtr_cone_GEO_C3D)[ijet],0.)),2) ) * max((*_jets_pt)[ijet]-PU/200.*2*(*_jets_PU_subtr_cone_GEO_C3D)[ijet],0.);
      jet.SetPtEtaPhiM(pt, (*_jets_eta)[ijet], (*_jets_phi)[ijet], 0);

      if(pt>pt_max1){
	pt_max2 = pt_max1;
	pt_max1 = pt;
	jet_max2 = jet_max1;
	jet_max1 = jet;
      }
      else if(pt>pt_max2){
	pt_max2 = pt;
	jet_max2 = jet;
      }

      if((*_jets_eta)[ijet]>0 && jet.Pt()>jet_max_plus.Pt())
	jet_max_plus = jet;
      if((*_jets_eta)[ijet]<0 && jet.Pt()>jet_max_minus.Pt())
	jet_max_minus = jet;    

    }

    h_SingleJet->Fill(pt_max1);
    h_DoubleJet->Fill(pt_max2);
    h_DoubleJet_pm->Fill(min(jet_max_plus.Pt(),jet_max_minus.Pt()));    
    //if(jet_max1.Eta()*jet_max2.Eta()<0)
    //  h_DoubleJet_pm->Fill(pt_max2);    

    if((jet_max_plus+jet_max_minus).M()>mjj)
      h_DoubleJet_pm_mjj->Fill(min(jet_max_plus.Pt(),jet_max_minus.Pt()));
      //if((jet_max1+jet_max2).M()>mjj)
      //h_DoubleJet_pm_mjj->Fill(pt_max2);

  }


  vector<TH1F*> histos;
  histos.push_back(h_SingleJet);
  histos.push_back(h_DoubleJet);
  histos.push_back(h_DoubleJet_pm);
  histos.push_back(h_DoubleJet_pm_mjj);
  

  return histos;

}







vector<TH1F*> histo_ET_max_Mjj_dRNNC2D_clean(TString filename, float mjj, float PU=200.){

  TChain * tree = new TChain("HGCalTriggerNtupleJet");
  tree->Add(filename);
  tree->SetBranchStatus("*",0);
 
  TH1F* h_SingleJet=new TH1F("h_SingleJet","h_SingleJet",1000,0,1000);
  TH1F* h_DoubleJet=new TH1F("h_DoubleJet","h_DoubleJet",1000,0,1000);
  TH1F* h_DoubleJet_pm=new TH1F("h_DoubleJet_pm","h_DoubleJet_pm",1000,0,1000);
  TH1F* h_DoubleJet_pm_mjj=new TH1F("h_DoubleJet_pm_mjj","h_DoubleJet_pm_mjj",1000,0,1000);
  

  vector<float>* _jets_clean_pt;
  vector<float>* _jets_clean_eta;
  vector<float>* _jets_clean_phi;

  tree->SetBranchAddress("jets_clean_pt", &_jets_clean_pt);
  tree->SetBranchAddress("jets_clean_eta", &_jets_clean_eta);
  tree->SetBranchAddress("jets_clean_phi", &_jets_clean_phi);


  Long64_t nentries = tree->GetEntries();
  cout<<nentries<<" events"<<endl;

  for (int i=0;i<nentries;i++) {

    if(i%1000==0)
      cout<<"i="<<i<<endl;
    
    _jets_clean_pt = 0;
    _jets_clean_eta = 0;
    _jets_clean_phi = 0;

    tree->GetEntry(i);

    float pt_max1 = 0.;
    float pt_max2 = 0.;    
    TLorentzVector jet_max_plus;
    jet_max_plus.SetPtEtaPhiM(0,0,0,0);
    TLorentzVector jet_max_minus;
    jet_max_minus.SetPtEtaPhiM(0,0,0,0);

    TLorentzVector jet_max1;
    jet_max1.SetPtEtaPhiM(0,0,0,0);
    TLorentzVector jet_max2;
    jet_max2.SetPtEtaPhiM(0,0,0,0);
    
    for(unsigned int ijet=0; ijet<(*_jets_clean_pt).size(); ijet++){
            
      TLorentzVector jet;
      float pt = 1.06*(4.98004e+00 -1.23767e+00 * log((*_jets_clean_pt)[ijet]) + 1.02929e-01* pow(log((*_jets_clean_pt)[ijet]),2) ) * (*_jets_clean_pt)[ijet];
      jet.SetPtEtaPhiM(pt, (*_jets_clean_eta)[ijet], (*_jets_clean_phi)[ijet], 0);

      if(pt>pt_max1){
	pt_max2 = pt_max1;
	pt_max1 = pt;
	jet_max2 = jet_max1;
	jet_max1 = jet;
      }
      else if(pt>pt_max2){
	pt_max2 = pt;
	jet_max2 = jet;
      }

      if((*_jets_clean_eta)[ijet]>0 && jet.Pt()>jet_max_plus.Pt())
	jet_max_plus = jet;
      if((*_jets_clean_eta)[ijet]<0 && jet.Pt()>jet_max_minus.Pt())
	jet_max_minus = jet;    

    }

    h_SingleJet->Fill(pt_max1);
    h_DoubleJet->Fill(pt_max2);
    h_DoubleJet_pm->Fill(min(jet_max_plus.Pt(),jet_max_minus.Pt()));    
    //if(jet_max1.Eta()*jet_max2.Eta()<0)
    //  h_DoubleJet_pm->Fill(pt_max2);    

    if((jet_max_plus+jet_max_minus).M()>mjj)
      h_DoubleJet_pm_mjj->Fill(min(jet_max_plus.Pt(),jet_max_minus.Pt()));
      //if((jet_max1+jet_max2).M()>mjj)
      //h_DoubleJet_pm_mjj->Fill(pt_max2);

  }


  vector<TH1F*> histos;
  histos.push_back(h_SingleJet);
  histos.push_back(h_DoubleJet);
  histos.push_back(h_DoubleJet_pm);
  histos.push_back(h_DoubleJet_pm_mjj);
  

  return histos;

}







vector<TH1F*> histo_ET_max_Mjj_TowerMap_6cm(TString filename, float mjj, float PU=200.){

  TChain * tree = new TChain("HGCalTriggerNtupleJet");
  tree->Add(filename);
  tree->SetBranchStatus("*",0);
 
  TH1F* h_SingleJet=new TH1F("h_SingleJet","h_SingleJet",1000,0,1000);
  TH1F* h_DoubleJet=new TH1F("h_DoubleJet","h_DoubleJet",1000,0,1000);
  TH1F* h_DoubleJet_pm=new TH1F("h_DoubleJet_pm","h_DoubleJet_pm",1000,0,1000);
  TH1F* h_DoubleJet_pm_mjj=new TH1F("h_DoubleJet_pm_mjj","h_DoubleJet_pm_mjj",1000,0,1000);
  

  vector<float>* _jets_pt;
  vector<float>* _jets_PU_subtr_cone_GEO_C3D;
  vector<float>* _jets_eta;
  vector<float>* _jets_phi;

  tree->SetBranchAddress("jets_pt", &_jets_pt);
  tree->SetBranchAddress("jets_PU_subtr_cone_GEO_C3D", &_jets_PU_subtr_cone_GEO_C3D);
  tree->SetBranchAddress("jets_eta", &_jets_eta);
  tree->SetBranchAddress("jets_phi", &_jets_phi);


  Long64_t nentries = tree->GetEntries();
  cout<<nentries<<" events"<<endl;

  for (int i=0;i<nentries;i++) {

    if(i%1000==0)
      cout<<"i="<<i<<endl;
    
    _jets_pt = 0;
    _jets_PU_subtr_cone_GEO_C3D = 0;
    _jets_eta = 0;
    _jets_phi = 0;

    tree->GetEntry(i);

    float pt_max1 = 0.;
    float pt_max2 = 0.;    
    TLorentzVector jet_max_plus;
    jet_max_plus.SetPtEtaPhiM(0,0,0,0);
    TLorentzVector jet_max_minus;
    jet_max_minus.SetPtEtaPhiM(0,0,0,0);

    TLorentzVector jet_max1;
    jet_max1.SetPtEtaPhiM(0,0,0,0);
    TLorentzVector jet_max2;
    jet_max2.SetPtEtaPhiM(0,0,0,0);
    
    for(unsigned int ijet=0; ijet<(*_jets_pt).size(); ijet++){
            
      TLorentzVector jet;
      float pt = 1.06*(4.17719 -1.03290 * log(max((*_jets_pt)[ijet]-PU/200.*4*(*_jets_PU_subtr_cone_GEO_C3D)[ijet],0.)) + 0.0872075* pow(log(max((*_jets_pt)[ijet]-PU/200.*4*(*_jets_PU_subtr_cone_GEO_C3D)[ijet],0.)),2) ) * max((*_jets_pt)[ijet]-PU/200.*4*(*_jets_PU_subtr_cone_GEO_C3D)[ijet],0.);
      jet.SetPtEtaPhiM(pt, (*_jets_eta)[ijet], (*_jets_phi)[ijet], 0);

      if(pt>pt_max1){
	pt_max2 = pt_max1;
	pt_max1 = pt;
	jet_max2 = jet_max1;
	jet_max1 = jet;
      }
      else if(pt>pt_max2){
	pt_max2 = pt;
	jet_max2 = jet;
      }

      if((*_jets_eta)[ijet]>0 && jet.Pt()>jet_max_plus.Pt())
	jet_max_plus = jet;
      if((*_jets_eta)[ijet]<0 && jet.Pt()>jet_max_minus.Pt())
	jet_max_minus = jet;    

    }

    h_SingleJet->Fill(pt_max1);
    h_DoubleJet->Fill(pt_max2);
    h_DoubleJet_pm->Fill(min(jet_max_plus.Pt(),jet_max_minus.Pt()));    
    //if(jet_max1.Eta()*jet_max2.Eta()<0)
    //  h_DoubleJet_pm->Fill(pt_max2);    

    if((jet_max_plus+jet_max_minus).M()>mjj)
      h_DoubleJet_pm_mjj->Fill(min(jet_max_plus.Pt(),jet_max_minus.Pt()));
      //if((jet_max1+jet_max2).M()>mjj)
      //h_DoubleJet_pm_mjj->Fill(pt_max2);

  }


  vector<TH1F*> histos;
  histos.push_back(h_SingleJet);
  histos.push_back(h_DoubleJet);
  histos.push_back(h_DoubleJet_pm);
  histos.push_back(h_DoubleJet_pm_mjj);
  

  return histos;

}






vector<TH1F*> histo_ET_max_Mjj_dRNNC2D_layer_fraction5(TString filename, float mjj, float PU=200.){

  TChain * tree = new TChain("HGCalTriggerNtupleJet");
  tree->Add(filename);
  tree->SetBranchStatus("*",0);
 
  TH1F* h_SingleJet=new TH1F("h_SingleJet","h_SingleJet",1000,0,1000);
  TH1F* h_SingleJet_fraction_95=new TH1F("h_SingleJet_fraction","h_SingleJet_fraction",1000,0,1000);
  TH1F* h_SingleJet_fraction_0p2=new TH1F("h_SingleJet_fraction_0p2","h_SingleJet_fraction_0p2",1000,0,1000);

  TH1F* h_DoubleJet_pm_mjj=new TH1F("h_DoubleJet_pm_mjj","h_DoubleJet_pm_mjj",1000,0,1000);
  TH1F* h_DoubleJet_pm_mjj_fraction_95=new TH1F("h_DoubleJet_pm_mjj_fraction_95","h_DoubleJet_pm_mjj_fraction_95",1000,0,1000);
  TH1F* h_DoubleJet_pm_mjj_fraction_0p2=new TH1F("h_DoubleJet_pm_mjj_fraction_0p2","h_DoubleJet_pm_mjj_fraction_0p2",1000,0,1000);
  

  vector<float>* _jets_pt;
  vector<float>* _jets_PU_subtr_cone_GEO_C3D;
  vector<float>* _jets_eta;
  vector<float>* _jets_phi;
  vector<vector<float> >* _layer_jets_energy_fraction;

  tree->SetBranchAddress("jets_pt", &_jets_pt);
  tree->SetBranchAddress("jets_PU_subtr_cone_GEO_C3D", &_jets_PU_subtr_cone_GEO_C3D);
  tree->SetBranchAddress("jets_eta", &_jets_eta);
  tree->SetBranchAddress("jets_phi", &_jets_phi);
  tree->SetBranchAddress("layer_jets_energy_fraction", &_layer_jets_energy_fraction);
  


  Long64_t nentries = tree->GetEntries();
  cout<<nentries<<" events"<<endl;

  for (int i=0;i<100000;i++) {
  //for(int i=113620; i<113650;i++) {

    if(i%1000==0)
      cout<<"i="<<i<<endl;
    
    _jets_pt = 0;
    _jets_PU_subtr_cone_GEO_C3D = 0;
    _jets_eta = 0;
    _jets_phi = 0;
    _layer_jets_energy_fraction = 0;

    tree->GetEntry(i);

    float pt_max = 0.;
    TLorentzVector jet_max_plus;
    jet_max_plus.SetPtEtaPhiM(0,0,0,0);
    TLorentzVector jet_max_minus;
    jet_max_minus.SetPtEtaPhiM(0,0,0,0);

    
    for(unsigned int ijet=0; ijet<(*_jets_pt).size(); ijet++){
            
      float pt_raw = (*_jets_pt)[ijet];
      float PUS = (*_jets_PU_subtr_cone_GEO_C3D)[ijet];

      TLorentzVector jet;
      float pt = 1.06*(4.98004e+00 -1.23767e+00 * log(max(pt_raw-PU/200.*2*PUS,0.)) + 1.02929e-01* pow(log(max(pt_raw-PU/200.*2*PUS,0.)),2) ) * max(pt_raw-PU/200.*2*PUS,0.);
      jet.SetPtEtaPhiM(pt, (*_jets_eta)[ijet], (*_jets_phi)[ijet], 0);

      if(pt>pt_max){
	pt_max = pt;
      }

      if((*_jets_eta)[ijet]>0 && jet.Pt()>jet_max_plus.Pt())
	jet_max_plus = jet;
      if((*_jets_eta)[ijet]<0 && jet.Pt()>jet_max_minus.Pt())
	jet_max_minus = jet;    

    }

    h_SingleJet->Fill(pt_max);
    if((jet_max_plus+jet_max_minus).M()>mjj)
      h_DoubleJet_pm_mjj->Fill(min(jet_max_plus.Pt(),jet_max_minus.Pt()));

    pt_max = 0.;
    jet_max_plus.SetPtEtaPhiM(0,0,0,0);
    jet_max_minus.SetPtEtaPhiM(0,0,0,0);

    for(unsigned int ijet=0; ijet<(*_jets_pt).size(); ijet++){
            
      float pt_raw = (*_jets_pt)[ijet];
      float PUS = (*_jets_PU_subtr_cone_GEO_C3D)[ijet];
      float layer_fraction5 = (*_layer_jets_energy_fraction)[5][ijet];

      TLorentzVector jet;
      float pt = 1.06*(4.98004e+00 -1.23767e+00 * log(max(pt_raw-PU/200.*2*PUS,0.)) + 1.02929e-01* pow(log(max(pt_raw-PU/200.*2*PUS,0.)),2) ) * max(pt_raw-PU/200.*2*PUS,0.);

      if(!(layer_fraction5<(1.38718e+01/(pt_raw+2.85485e+01)+7.04647e-02) || pt>60)) continue;      

      jet.SetPtEtaPhiM(pt, (*_jets_eta)[ijet], (*_jets_phi)[ijet], 0);

      if(pt>pt_max){
	pt_max = pt;
      }

      if((*_jets_eta)[ijet]>0 && jet.Pt()>jet_max_plus.Pt())
	jet_max_plus = jet;
      if((*_jets_eta)[ijet]<0 && jet.Pt()>jet_max_minus.Pt())
	jet_max_minus = jet;    

    }


    h_SingleJet_fraction_95->Fill(pt_max);
    if((jet_max_plus+jet_max_minus).M()>mjj)
      h_DoubleJet_pm_mjj_fraction_95->Fill(min(jet_max_plus.Pt(),jet_max_minus.Pt()));


    pt_max = 0.;
    jet_max_plus.SetPtEtaPhiM(0,0,0,0);
    jet_max_minus.SetPtEtaPhiM(0,0,0,0);

    for(unsigned int ijet=0; ijet<(*_jets_pt).size(); ijet++){
            
      float pt_raw = (*_jets_pt)[ijet];
      float PUS = (*_jets_PU_subtr_cone_GEO_C3D)[ijet];
      float layer_fraction5 = (*_layer_jets_energy_fraction)[5][ijet];

      TLorentzVector jet;
      float pt = 1.06*(4.98004e+00 -1.23767e+00 * log(max(pt_raw-PU/200.*2*PUS,0.)) + 1.02929e-01* pow(log(max(pt_raw-PU/200.*2*PUS,0.)),2) ) * max(pt_raw-PU/200.*2*PUS,0.);

      if(!(layer_fraction5<0.2 || pt>60)) continue;      

      jet.SetPtEtaPhiM(pt, (*_jets_eta)[ijet], (*_jets_phi)[ijet], 0);

      if(pt>pt_max){
	pt_max = pt;
      }

      if((*_jets_eta)[ijet]>0 && jet.Pt()>jet_max_plus.Pt())
	jet_max_plus = jet;
      if((*_jets_eta)[ijet]<0 && jet.Pt()>jet_max_minus.Pt())
	jet_max_minus = jet;    

    }


    h_SingleJet_fraction_0p2->Fill(pt_max);
    if((jet_max_plus+jet_max_minus).M()>mjj)
      h_DoubleJet_pm_mjj_fraction_0p2->Fill(min(jet_max_plus.Pt(),jet_max_minus.Pt()));


  }


  vector<TH1F*> histos;
  histos.push_back(h_SingleJet);
  histos.push_back(h_SingleJet_fraction_95);
  histos.push_back(h_SingleJet_fraction_0p2);
  histos.push_back(h_DoubleJet_pm_mjj);
  histos.push_back(h_DoubleJet_pm_mjj_fraction_95);
  histos.push_back(h_DoubleJet_pm_mjj_fraction_0p2);
  

  return histos;

}





vector<TH1F*> histo_ET_max_Mjj_dRNNC2D_Fisher(TString filename, float mjj, float PU=200.){

  TChain * tree = new TChain("HGCalTriggerNtupleJet");
  tree->Add(filename);
  tree->SetBranchStatus("*",0);
 
  TH1F* h_SingleJet=new TH1F("h_SingleJet","h_SingleJet",1000,0,1000);
  TH1F* h_SingleJet_fraction_0p2=new TH1F("h_SingleJet_fraction_0p2","h_SingleJet_fraction_0p2",1000,0,1000);
  TH1F* h_SingleJet_Fisher=new TH1F("h_SingleJet_Fisher","h_SingleJet_Fisher",1000,0,1000);

  TH1F* h_DoubleJet_pm_mjj=new TH1F("h_DoubleJet_pm_mjj","h_DoubleJet_pm_mjj",1000,0,1000);
  TH1F* h_DoubleJet_pm_mjj_fraction_0p2=new TH1F("h_DoubleJet_pm_mjj_fraction_0p2","h_DoubleJet_pm_mjj_fraction_0p2",1000,0,1000);
  TH1F* h_DoubleJet_pm_mjj_Fisher=new TH1F("h_DoubleJet_pm_mjj_Fisher","h_DoubleJet_pm_mjj_Fisher",1000,0,1000);
  

  vector<float>* _jets_pt;
  vector<float>* _jets_PU_subtr_cone_GEO_C3D;
  vector<float>* _jets_eta;
  vector<float>* _jets_phi;
  vector<vector<float> >* _layer_jets_energy_fraction;
  vector<float>* _jets_Fisher_VBF;


  tree->SetBranchAddress("jets_pt", &_jets_pt);
  tree->SetBranchAddress("jets_PU_subtr_cone_GEO_C3D", &_jets_PU_subtr_cone_GEO_C3D);
  tree->SetBranchAddress("jets_eta", &_jets_eta);
  tree->SetBranchAddress("jets_phi", &_jets_phi);
  tree->SetBranchAddress("layer_jets_energy_fraction", &_layer_jets_energy_fraction);
  tree->SetBranchAddress("jets_Fisher_VBF", &_jets_Fisher_VBF);
  


  Long64_t nentries = tree->GetEntries();
  cout<<nentries<<" events"<<endl;

  for (int i=0;i<100000;i++) {
  //for(int i=113620; i<113650;i++) {

    if(i%1000==0)
      cout<<"i="<<i<<endl;
    
    _jets_pt = 0;
    _jets_PU_subtr_cone_GEO_C3D = 0;
    _jets_eta = 0;
    _jets_phi = 0;
    _layer_jets_energy_fraction = 0;
    _jets_Fisher_VBF = 0;

    tree->GetEntry(i);

    float pt_max = 0.;
    TLorentzVector jet_max_plus;
    jet_max_plus.SetPtEtaPhiM(0,0,0,0);
    TLorentzVector jet_max_minus;
    jet_max_minus.SetPtEtaPhiM(0,0,0,0);

    
    for(unsigned int ijet=0; ijet<(*_jets_pt).size(); ijet++){
            
      float pt_raw = (*_jets_pt)[ijet];
      float PUS = (*_jets_PU_subtr_cone_GEO_C3D)[ijet];

      TLorentzVector jet;
      float pt = 1.06*(4.98004e+00 -1.23767e+00 * log(max(pt_raw-PU/200.*2*PUS,0.)) + 1.02929e-01* pow(log(max(pt_raw-PU/200.*2*PUS,0.)),2) ) * max(pt_raw-PU/200.*2*PUS,0.);
      jet.SetPtEtaPhiM(pt, (*_jets_eta)[ijet], (*_jets_phi)[ijet], 0);

      if(pt>pt_max){
	pt_max = pt;
      }

      if((*_jets_eta)[ijet]>0 && jet.Pt()>jet_max_plus.Pt())
	jet_max_plus = jet;
      if((*_jets_eta)[ijet]<0 && jet.Pt()>jet_max_minus.Pt())
	jet_max_minus = jet;    

    }

    h_SingleJet->Fill(pt_max);
    if((jet_max_plus+jet_max_minus).M()>mjj)
      h_DoubleJet_pm_mjj->Fill(min(jet_max_plus.Pt(),jet_max_minus.Pt()));


    pt_max = 0.;
    jet_max_plus.SetPtEtaPhiM(0,0,0,0);
    jet_max_minus.SetPtEtaPhiM(0,0,0,0);

    for(unsigned int ijet=0; ijet<(*_jets_pt).size(); ijet++){
            
      float pt_raw = (*_jets_pt)[ijet];
      float PUS = (*_jets_PU_subtr_cone_GEO_C3D)[ijet];
      float layer_fraction5 = (*_layer_jets_energy_fraction)[5][ijet];

      TLorentzVector jet;
      float pt = 1.06*(4.98004e+00 -1.23767e+00 * log(max(pt_raw-PU/200.*2*PUS,0.)) + 1.02929e-01* pow(log(max(pt_raw-PU/200.*2*PUS,0.)),2) ) * max(pt_raw-PU/200.*2*PUS,0.);

      if(!(layer_fraction5<0.2 || pt>60)) continue;      

      jet.SetPtEtaPhiM(pt, (*_jets_eta)[ijet], (*_jets_phi)[ijet], 0);

      if(pt>pt_max){
	pt_max = pt;
      }

      if((*_jets_eta)[ijet]>0 && jet.Pt()>jet_max_plus.Pt())
	jet_max_plus = jet;
      if((*_jets_eta)[ijet]<0 && jet.Pt()>jet_max_minus.Pt())
	jet_max_minus = jet;    

    }


    h_SingleJet_fraction_0p2->Fill(pt_max);
    if((jet_max_plus+jet_max_minus).M()>mjj)
      h_DoubleJet_pm_mjj_fraction_0p2->Fill(min(jet_max_plus.Pt(),jet_max_minus.Pt()));



    pt_max = 0.;
    jet_max_plus.SetPtEtaPhiM(0,0,0,0);
    jet_max_minus.SetPtEtaPhiM(0,0,0,0);

    for(unsigned int ijet=0; ijet<(*_jets_pt).size(); ijet++){
            
      float pt_raw = (*_jets_pt)[ijet];
      float PUS = (*_jets_PU_subtr_cone_GEO_C3D)[ijet];
      float Fisher = (*_jets_Fisher_VBF)[ijet];

      TLorentzVector jet;
      float pt = 1.06*(4.98004e+00 -1.23767e+00 * log(max(pt_raw-PU/200.*2*PUS,0.)) + 1.02929e-01* pow(log(max(pt_raw-PU/200.*2*PUS,0.)),2) ) * max(pt_raw-PU/200.*2*PUS,0.);

      if(!(Fisher>0.5 || pt>60)) continue;      

      jet.SetPtEtaPhiM(pt, (*_jets_eta)[ijet], (*_jets_phi)[ijet], 0);

      if(pt>pt_max){
	pt_max = pt;
      }

      if((*_jets_eta)[ijet]>0 && jet.Pt()>jet_max_plus.Pt())
	jet_max_plus = jet;
      if((*_jets_eta)[ijet]<0 && jet.Pt()>jet_max_minus.Pt())
	jet_max_minus = jet;    

    }


    h_SingleJet_Fisher->Fill(pt_max);
    if((jet_max_plus+jet_max_minus).M()>mjj)
      h_DoubleJet_pm_mjj_Fisher->Fill(min(jet_max_plus.Pt(),jet_max_minus.Pt()));


  }


  vector<TH1F*> histos;
  histos.push_back(h_SingleJet);
  histos.push_back(h_SingleJet_fraction_0p2);
  histos.push_back(h_SingleJet_Fisher);
  histos.push_back(h_DoubleJet_pm_mjj);
  histos.push_back(h_DoubleJet_pm_mjj_fraction_0p2);
  histos.push_back(h_DoubleJet_pm_mjj_Fisher);
  

  return histos;

}








void plot_rate_SingleJet(vector<TString> filename, vector<TString> var, vector<TString> leg_entry, float norm, bool save=false, TString plotname=""){

   vector<TGraphErrors*> graph;

   for(unsigned int i=0;i<filename.size();i++){

     TGraphErrors* gr=new TGraphErrors();
     TH1F* h = single_plot(filename[i],"jets","Max$("+var[i]+")","",1000,0,1000);
     int nentries = h->GetEntries();

     int lim = h->GetNbinsX() + 1;
     int n = 0;
     
     cout<<leg_entry[i]<<endl;
     
     for(unsigned int E=0; E<251; E+=1){
       
       int bin = h->FindBin(E);
       double error=0;
       float frac = h->IntegralAndError(bin,lim,error)/nentries;
       gr->SetPoint(n,E,frac*norm);
       gr->SetPointError(n,0,error*norm/nentries);
       cout<<leg_entry[i]<<" ET>"<<E<<endl;
       cout<<frac*norm<<" kHz"<<endl;
       n++;
       
     }
     
     gr->SetLineWidth(2);
     gr->SetLineColor(i+1);
     gr->SetMarkerColor(i+1);
     gr->SetFillColor(i+1);
     if(i>3){
       gr->SetLineColor(i+2);
       gr->SetMarkerColor(i+2);
       gr->SetFillColor(i+2);
     }
     
     graph.push_back(gr);
     
   }

   
   
  graph[0]->GetXaxis()->SetTitle("Threshold [GeV]");
  graph[0]->GetXaxis()->SetLimits(0,200);
  graph[0]->GetYaxis()->SetTitle("SingleJet rate [kHz]");
  graph[0]->GetYaxis()->SetTitleSize(20);
  graph[0]->GetYaxis()->SetTitleOffset(1.5);
  graph[0]->GetYaxis()->SetTitleFont(43);
  graph[0]->GetYaxis()->SetRangeUser(1,4e4);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetLogy();
  c->SetTicks();
  c->SetGrid();

  graph[0]->Draw("AL3");
  for(unsigned int i=1; i<graph.size(); i++)
    graph[i]->Draw("sameL3");

  TLatex *texl = new TLatex(1,5e4,"CMS Simulation Preliminary, #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same"); 

  TLegend* leg=new TLegend(0.4,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  for(unsigned int i=0;i<graph.size();i++){
    TGraphErrors* gr = (TGraphErrors*)graph[i]->Clone();
    gr->SetFillColor(0);
    leg->AddEntry(gr,leg_entry[i]);	
  }	
  leg->Draw("same");





  if(save){
    c->SaveAs("plots/"+plotname+".pdf");
  }

  return;

}







void plot_rate_SingleJet(vector<TString> filename, vector<TString> treename, vector<TString> var, vector<TString> leg_entry, float norm, bool save=false, TString plotname=""){

   vector<TGraphErrors*> graph;

   for(unsigned int i=0;i<filename.size();i++){

     TGraphErrors* gr=new TGraphErrors();
     TH1F* h = single_plot(filename[i],treename[i],"Max$("+var[i]+")","",1000,0,1000);
     int nentries = h->GetEntries();

     int lim = h->GetNbinsX() + 1;
     int n = 0;
     
     cout<<leg_entry[i]<<endl;
     
     for(unsigned int E=0; E<251; E+=1){
       
       int bin = h->FindBin(E);
       double error=0;
       float frac = h->IntegralAndError(bin,lim,error)/nentries;
       gr->SetPoint(n,E,frac*norm);
       //gr->SetPointError(n,0,error*norm/nentries);
       cout<<leg_entry[i]<<" ET>"<<E<<endl;
       cout<<frac*norm<<" kHz"<<endl;
       n++;
       
     }
     
     gr->SetLineWidth(2);
     //gr->SetMarkerStyle(21);
     //gr->SetMarkerSize(0.7);
     gr->SetLineColor(i+1);
     gr->SetMarkerColor(i+1);
     gr->SetFillColor(i+1);
     if(i>3){
       gr->SetLineColor(i+2);
       gr->SetMarkerColor(i+2);
       gr->SetFillColor(i+2);
     }

     
     graph.push_back(gr);
     
   }

   
   
  graph[0]->GetXaxis()->SetTitle("Threshold [GeV]");
  graph[0]->GetXaxis()->SetLimits(0,200);
  graph[0]->GetYaxis()->SetTitle("SingleJet rate [kHz]");
  graph[0]->GetYaxis()->SetTitleSize(20);
  graph[0]->GetYaxis()->SetTitleOffset(1.5);
  graph[0]->GetYaxis()->SetTitleFont(43);
  graph[0]->GetYaxis()->SetRangeUser(1,4e4);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetLogy();
  c->SetTicks();
  c->SetGrid();

  graph[0]->Draw("AL3");
  for(unsigned int i=1; i<graph.size(); i++)
    graph[i]->Draw("sameL3");


  TLatex *texl = new TLatex(1,5e4,"CMS Simulation Preliminary, #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same"); 

  TLegend* leg=new TLegend(0.4,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  for(unsigned int i=0;i<graph.size();i++){
    TGraphErrors* gr = (TGraphErrors*)graph[i]->Clone();
    gr->SetFillColor(0);
    leg->AddEntry(gr,leg_entry[i]);	
  }	
  leg->Draw("same");





  if(save){
    c->SaveAs("plots/"+plotname+".pdf");
  }

  return;

}




void plot_rate_jets(TString filename, int mjj_cut, float norm, bool save=false, TString plotname="", int PU=200){

   
  vector<TH1F*> histos = histo_ET_max_Mjj(filename,float(mjj_cut),float(PU));
  
  int nentries = histos[0]->GetEntries();

  vector<TString> leg_entry;
  leg_entry.push_back("Single jet");
  leg_entry.push_back("Double jet");
  leg_entry.push_back("Double jet #eta_{1}#eta_{2}<0");
  leg_entry.push_back(Form("#splitline{Double jet #eta_{1}#eta_{2}<0}{+ M_{12}>%i GeV}",mjj_cut));
   
   vector<TGraphErrors*> graph;


   for(unsigned int i=0; i<histos.size(); i++){
          
     TH1F* h = histos[i];     
     TGraphErrors* gr=new TGraphErrors();
     int lim = h->GetNbinsX() + 1;
     int n = 0;
          
     for(unsigned int E=0; E<201; E+=5){
       
       int bin = h->FindBin(E);
       double error=0;
       float frac = h->IntegralAndError(bin,lim,error)/nentries;
       gr->SetPoint(n,E,frac*norm);
       gr->SetPointError(n,0,error*norm/nentries);
       cout<<leg_entry[i]<<" ET>"<<E<<endl;
       cout<<frac*norm<<" kHz"<<endl;
       n++;
       
     }
     
     gr->SetLineWidth(2);
     gr->SetLineColor(i+1);
     //gr->SetMarkerStyle(21);
     //gr->SetMarkerSize(0.7);
     gr->SetMarkerColor(i+1);
     gr->SetFillColor(i+1);
     //gr->SetFillColor(0);
     
     graph.push_back(gr);
     
   }

   
   
  graph[0]->GetXaxis()->SetTitle("E_{T} threshold [GeV]");
  graph[0]->GetXaxis()->SetLimits(0,200);
  graph[0]->GetYaxis()->SetTitle("Rate [kHz]");
  graph[0]->GetYaxis()->SetTitleSize(20);
  graph[0]->GetYaxis()->SetTitleOffset(1.5);
  graph[0]->GetYaxis()->SetTitleFont(43);
  graph[0]->GetYaxis()->SetRangeUser(1.,5e4);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetLogy();
  c->SetTicks();
  c->SetGrid();

  graph[0]->Draw("AL3");
  for(unsigned int i=1; i<graph.size(); i++)
    graph[i]->Draw("sameL3");

  TLatex *texl = new TLatex(1,6e4,Form("CMS Simulation Preliminary, #sqrt{s}=14 TeV, PU=%i",PU));
  texl->SetTextSize(0.03);
  texl->Draw("same"); 

  TLegend* leg=new TLegend(0.6,0.5,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  for(unsigned int i=0;i<graph.size();i++){
    TGraphErrors* gr = (TGraphErrors*)graph[i]->Clone();
    gr->SetFillColor(0);
    leg->AddEntry(gr,leg_entry[i]);	
  }
  leg->Draw("same");





  if(save){
    c->SaveAs("plots/"+plotname+".pdf");
  }

  return;

}






void plot_rate_jets_GEO(TString filename, int mjj_cut, float norm, bool save=false, TString plotname="", int PU=200){

   
  vector<TH1F*> histos = histo_ET_max_Mjj_GEO(filename,float(mjj_cut),float(PU));
  
  int nentries = histos[0]->GetEntries();

  vector<TString> leg_entry;
  leg_entry.push_back("Single jet");
  leg_entry.push_back("Double jet");
  leg_entry.push_back("Double jet #eta_{1}#eta_{2}<0");
  leg_entry.push_back(Form("#splitline{Double jet #eta_{1}#eta_{2}<0}{+ M_{12}>%i GeV}",mjj_cut));
   
   vector<TGraphErrors*> graph;


   for(unsigned int i=0; i<histos.size(); i++){
          
     TH1F* h = histos[i];     
     TGraphErrors* gr=new TGraphErrors();
     int lim = h->GetNbinsX() + 1;
     int n = 0;
          
     for(unsigned int E=0; E<201; E+=5){
       
       int bin = h->FindBin(E);
       double error=0;
       float frac = h->IntegralAndError(bin,lim,error)/nentries;
       gr->SetPoint(n,E,frac*norm);
       gr->SetPointError(n,0,error*norm/nentries);
       cout<<leg_entry[i]<<" ET>"<<E<<endl;
       cout<<frac*norm<<" kHz"<<endl;
       n++;
       
     }
     
     gr->SetLineWidth(2);
     gr->SetLineColor(i+1);
     //gr->SetMarkerStyle(21);
     //gr->SetMarkerSize(0.7);
     gr->SetMarkerColor(i+1);
     gr->SetFillColor(i+1);
     //gr->SetFillColor(0);
     
     graph.push_back(gr);
     
   }

   
   
  graph[0]->GetXaxis()->SetTitle("E_{T} threshold [GeV]");
  graph[0]->GetXaxis()->SetLimits(0,200);
  graph[0]->GetYaxis()->SetTitle("Rate [kHz]");
  graph[0]->GetYaxis()->SetTitleSize(20);
  graph[0]->GetYaxis()->SetTitleOffset(1.5);
  graph[0]->GetYaxis()->SetTitleFont(43);
  graph[0]->GetYaxis()->SetRangeUser(1.,5e4);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetLogy();
  c->SetTicks();
  c->SetGrid();

  graph[0]->Draw("AL3");
  for(unsigned int i=1; i<graph.size(); i++)
    graph[i]->Draw("sameL3");

  TLatex *texl = new TLatex(1,6e4,Form("CMS Simulation Preliminary, #sqrt{s}=14 TeV, PU=%i",PU));
  texl->SetTextSize(0.03);
  texl->Draw("same"); 

  TLegend* leg=new TLegend(0.6,0.5,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  for(unsigned int i=0;i<graph.size();i++){
    TGraphErrors* gr = (TGraphErrors*)graph[i]->Clone();
    gr->SetFillColor(0);
    leg->AddEntry(gr,leg_entry[i]);	
  }
  leg->Draw("same");





  if(save){
    c->SaveAs("plots/"+plotname+".pdf");
  }

  return;

}





void plot_rate_jets_GEO_recal(TString filename, int mjj_cut, float norm, bool save=false, TString plotname="", int PU=200){

   
  vector<TH1F*> histos = histo_ET_max_Mjj_GEO_recal(filename,float(mjj_cut),float(PU));
  
  int nentries = histos[0]->GetEntries();

  vector<TString> leg_entry;
  leg_entry.push_back("Single jet");
  leg_entry.push_back("Double jet");
  leg_entry.push_back("Double jet #eta_{1}#eta_{2}<0");
  leg_entry.push_back(Form("#splitline{Double jet #eta_{1}#eta_{2}<0}{+ M_{12}>%i GeV}",mjj_cut));
   
   vector<TGraphErrors*> graph;


   for(unsigned int i=0; i<histos.size(); i++){
          
     TH1F* h = histos[i];     
     TGraphErrors* gr=new TGraphErrors();
     int lim = h->GetNbinsX() + 1;
     int n = 0;
          
     for(unsigned int E=0; E<201; E+=5){
       
       int bin = h->FindBin(E);
       double error=0;
       float frac = h->IntegralAndError(bin,lim,error)/nentries;
       gr->SetPoint(n,E,frac*norm);
       gr->SetPointError(n,0,error*norm/nentries);
       cout<<leg_entry[i]<<" ET>"<<E<<endl;
       cout<<frac*norm<<" kHz"<<endl;
       n++;
       
     }
     
     gr->SetLineWidth(2);
     gr->SetLineColor(i+1);
     //gr->SetMarkerStyle(21);
     //gr->SetMarkerSize(0.7);
     gr->SetMarkerColor(i+1);
     gr->SetFillColor(i+1);
     //gr->SetFillColor(0);
     
     graph.push_back(gr);
     
   }

   
   
  graph[0]->GetXaxis()->SetTitle("E_{T} threshold [GeV]");
  graph[0]->GetXaxis()->SetLimits(0,200);
  graph[0]->GetYaxis()->SetTitle("Rate [kHz]");
  graph[0]->GetYaxis()->SetTitleSize(20);
  graph[0]->GetYaxis()->SetTitleOffset(1.5);
  graph[0]->GetYaxis()->SetTitleFont(43);
  graph[0]->GetYaxis()->SetRangeUser(1.,5e4);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetLogy();
  c->SetTicks();
  c->SetGrid();

  graph[0]->Draw("AL3");
  for(unsigned int i=1; i<graph.size(); i++)
    graph[i]->Draw("sameL3");

  TLatex *texl = new TLatex(1,6e4,Form("CMS Simulation Preliminary, #sqrt{s}=14 TeV, PU=%i",PU));
  texl->SetTextSize(0.03);
  texl->Draw("same"); 

  TLegend* leg=new TLegend(0.6,0.5,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  for(unsigned int i=0;i<graph.size();i++){
    TGraphErrors* gr = (TGraphErrors*)graph[i]->Clone();
    gr->SetFillColor(0);
    leg->AddEntry(gr,leg_entry[i]);	
  }
  leg->Draw("same");





  if(save){
    c->SaveAs("plots/"+plotname+".pdf");
  }

  return;

}





void plot_rate_jets_dRNNC2D(TString filename, int mjj_cut, float norm, bool save=false, TString plotname="", int PU=200){

   
  vector<TH1F*> histos = histo_ET_max_Mjj_dRNNC2D(filename,float(mjj_cut),float(PU));
  
  int nentries = histos[0]->GetEntries();

  vector<TString> leg_entry;
  leg_entry.push_back("Single jet");
  leg_entry.push_back("Double jet");
  leg_entry.push_back("Double jet #eta_{1}#eta_{2}<0");
  leg_entry.push_back(Form("#splitline{Double jet #eta_{1}#eta_{2}<0}{+ M_{12}>%i GeV}",mjj_cut));
   
   vector<TGraphErrors*> graph;


   for(unsigned int i=0; i<histos.size(); i++){
          
     TH1F* h = histos[i];     
     TGraphErrors* gr=new TGraphErrors();
     int lim = h->GetNbinsX() + 1;
     int n = 0;
          
     for(unsigned int E=0; E<201; E+=1){
       
       int bin = h->FindBin(E);
       double error=0;
       float frac = h->IntegralAndError(bin,lim,error)/nentries;
       gr->SetPoint(n,E,frac*norm);
       gr->SetPointError(n,0,error*norm/nentries);
       cout<<leg_entry[i]<<" ET>"<<E<<endl;
       cout<<frac*norm<<" kHz"<<endl;
       n++;
       
     }
     
     gr->SetLineWidth(2);
     gr->SetLineColor(i+1);
     //gr->SetMarkerStyle(21);
     //gr->SetMarkerSize(0.7);
     gr->SetMarkerColor(i+1);
     gr->SetFillColor(i+1);
     //gr->SetFillColor(0);
     
     graph.push_back(gr);
     
   }

   
   
  graph[0]->GetXaxis()->SetTitle("E_{T} threshold [GeV]");
  graph[0]->GetXaxis()->SetLimits(0,200);
  graph[0]->GetYaxis()->SetTitle("Rate [kHz]");
  graph[0]->GetYaxis()->SetTitleSize(20);
  graph[0]->GetYaxis()->SetTitleOffset(1.5);
  graph[0]->GetYaxis()->SetTitleFont(43);
  graph[0]->GetYaxis()->SetRangeUser(1.,5e4);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetLogy();
  c->SetTicks();
  c->SetGrid();

  graph[0]->Draw("AL3");
  for(unsigned int i=1; i<graph.size(); i++)
    graph[i]->Draw("sameL3");

  TLatex *texl = new TLatex(1,6e4,Form("CMS Simulation Preliminary, #sqrt{s}=14 TeV, PU=%i",PU));
  texl->SetTextSize(0.03);
  texl->Draw("same"); 

  TLegend* leg=new TLegend(0.6,0.5,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  for(unsigned int i=0;i<graph.size();i++){
    TGraphErrors* gr = (TGraphErrors*)graph[i]->Clone();
    gr->SetFillColor(0);
    leg->AddEntry(gr,leg_entry[i]);	
  }
  leg->Draw("same");





  if(save){
    c->SaveAs("plots/"+plotname+".pdf");
  }

  return;

}




void plot_rate_jets_TowerMap_6cm(TString filename, int mjj_cut, float norm, bool save=false, TString plotname="", int PU=200){

   
  vector<TH1F*> histos = histo_ET_max_Mjj_TowerMap_6cm(filename,float(mjj_cut),float(PU));
  
  int nentries = histos[0]->GetEntries();

  vector<TString> leg_entry;
  leg_entry.push_back("Single jet");
  leg_entry.push_back("Double jet");
  leg_entry.push_back("Double jet #eta_{1}#eta_{2}<0");
  leg_entry.push_back(Form("#splitline{Double jet #eta_{1}#eta_{2}<0}{+ M_{12}>%i GeV}",mjj_cut));
   
   vector<TGraphErrors*> graph;


   for(unsigned int i=0; i<histos.size(); i++){
          
     TH1F* h = histos[i];     
     TGraphErrors* gr=new TGraphErrors();
     int lim = h->GetNbinsX() + 1;
     int n = 0;
          
     for(unsigned int E=0; E<201; E+=1){
       
       int bin = h->FindBin(E);
       double error=0;
       float frac = h->IntegralAndError(bin,lim,error)/nentries;
       gr->SetPoint(n,E,frac*norm);
       gr->SetPointError(n,0,error*norm/nentries);
       cout<<leg_entry[i]<<" ET>"<<E<<endl;
       cout<<frac*norm<<" kHz"<<endl;
       n++;
       
     }
     
     gr->SetLineWidth(2);
     gr->SetLineColor(i+1);
     //gr->SetMarkerStyle(21);
     //gr->SetMarkerSize(0.7);
     gr->SetMarkerColor(i+1);
     gr->SetFillColor(i+1);
     //gr->SetFillColor(0);
     
     graph.push_back(gr);
     
   }

   
   
  graph[0]->GetXaxis()->SetTitle("E_{T} threshold [GeV]");
  graph[0]->GetXaxis()->SetLimits(0,200);
  graph[0]->GetYaxis()->SetTitle("Rate [kHz]");
  graph[0]->GetYaxis()->SetTitleSize(20);
  graph[0]->GetYaxis()->SetTitleOffset(1.5);
  graph[0]->GetYaxis()->SetTitleFont(43);
  graph[0]->GetYaxis()->SetRangeUser(1.,5e4);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetLogy();
  c->SetTicks();
  c->SetGrid();

  graph[0]->Draw("AL3");
  for(unsigned int i=1; i<graph.size(); i++)
    graph[i]->Draw("sameL3");

  TLatex *texl = new TLatex(1,6e4,Form("CMS Simulation Preliminary, #sqrt{s}=14 TeV, PU=%i",PU));
  texl->SetTextSize(0.03);
  texl->Draw("same"); 

  TLegend* leg=new TLegend(0.6,0.5,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  for(unsigned int i=0;i<graph.size();i++){
    TGraphErrors* gr = (TGraphErrors*)graph[i]->Clone();
    gr->SetFillColor(0);
    leg->AddEntry(gr,leg_entry[i]);	
  }
  leg->Draw("same");





  if(save){
    c->SaveAs("plots/"+plotname+".pdf");
  }

  return;

}





void plot_rate_jets_dRNNC2D_layer_fraction5(TString filename, int mjj_cut, float norm, bool save=false, TString plotname="", int PU=200){

   
  vector<TH1F*> histos = histo_ET_max_Mjj_dRNNC2D_layer_fraction5(filename,float(mjj_cut),float(PU));
  
  int nentries = histos[0]->GetEntries();

  vector<TString> leg_entry;
  leg_entry.push_back("Single jet");
  leg_entry.push_back("+ 95% eff. cut");
  leg_entry.push_back("+ 0.2 cut");
  leg_entry.push_back(Form("#splitline{Double jet #eta_{1}#eta_{2}<0}{+ M_{12}>%i GeV}",mjj_cut));
  leg_entry.push_back("+ 95% eff. cut");
  leg_entry.push_back("+ 0.2 cut");
   
   vector<TGraphErrors*> graph;



   for(unsigned int i=0; i<histos.size(); i++){
          
     TH1F* h = histos[i];     
     TGraphErrors* gr=new TGraphErrors();
     int lim = h->GetNbinsX() + 1;
     int n = 0;
          
     for(unsigned int E=0; E<201; E+=1){
       
       int bin = h->FindBin(E);
       double error=0;
       float frac = 0.;
       frac = h->IntegralAndError(bin,lim,error)/nentries;      
       gr->SetPoint(n,E,frac*norm);
       gr->SetPointError(n,0,error*norm/nentries);
       cout<<leg_entry[i]<<" ET>"<<E<<endl;
       cout<<frac*norm<<" kHz"<<endl;
       n++;
       
     }
     
     gr->SetLineWidth(2);
     gr->SetLineColor(i+1);
     gr->SetMarkerColor(i+1);
     gr->SetFillColor(i+1);

     if(i>3){
       gr->SetLineColor(i+2);
       gr->SetMarkerColor(i+2);
       gr->SetFillColor(i+2);
     }
     
     graph.push_back(gr);
     
   }

   
   
  graph[0]->GetXaxis()->SetTitle("E_{T} threshold [GeV]");
  graph[0]->GetXaxis()->SetLimits(0,200);
  graph[0]->GetYaxis()->SetTitle("Rate [kHz]");
  graph[0]->GetYaxis()->SetTitleSize(20);
  graph[0]->GetYaxis()->SetTitleOffset(1.5);
  graph[0]->GetYaxis()->SetTitleFont(43);
  graph[0]->GetYaxis()->SetRangeUser(1.,5e4);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetLogy();
  c->SetTicks();
  c->SetGrid();

  graph[0]->Draw("AL3");
  for(unsigned int i=1; i<graph.size(); i++)
    graph[i]->Draw("sameL3");

  TLatex *texl = new TLatex(1,6e4,Form("CMS Simulation Preliminary, #sqrt{s}=14 TeV, PU=%i",PU));
  texl->SetTextSize(0.03);
  texl->Draw("same"); 

  TLegend* leg=new TLegend(0.6,0.4,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  for(unsigned int i=0;i<graph.size();i++){
    TGraphErrors* gr = (TGraphErrors*)graph[i]->Clone();
    gr->SetFillColor(0);
    leg->AddEntry(gr,leg_entry[i]);	
  }
  leg->Draw("same");





  if(save){
    c->SaveAs("plots/"+plotname+".pdf");
  }

  return;

}





void plot_rate_jets_dRNNC2D_Fisher(TString filename, int mjj_cut, float norm, bool save=false, TString plotname="", int PU=200){

   
  vector<TH1F*> histos = histo_ET_max_Mjj_dRNNC2D_Fisher(filename,float(mjj_cut),float(PU));
  
  int nentries = histos[0]->GetEntries();

  vector<TString> leg_entry;
  leg_entry.push_back("Single jet");
  leg_entry.push_back("+ fraction layer#5<0.2");
  leg_entry.push_back("+ Fisher discr.>0.5");
  leg_entry.push_back(Form("#splitline{Double jet #eta_{1}#eta_{2}<0}{+ M_{12}>%i GeV}",mjj_cut));
  leg_entry.push_back("+ fraction layer#5<0.2");
  leg_entry.push_back("+ Fisher discr.>0.5");
   
   vector<TGraphErrors*> graph;



   for(unsigned int i=0; i<histos.size(); i++){
          
     TH1F* h = histos[i];     
     TGraphErrors* gr=new TGraphErrors();
     int lim = h->GetNbinsX() + 1;
     int n = 0;
          
     for(unsigned int E=0; E<201; E+=1){
       
       int bin = h->FindBin(E);
       double error=0;
       float frac = 0.;
       frac = h->IntegralAndError(bin,lim,error)/nentries;      
       gr->SetPoint(n,E,frac*norm);
       gr->SetPointError(n,0,error*norm/nentries);
       cout<<leg_entry[i]<<" ET>"<<E<<endl;
       cout<<frac*norm<<" kHz"<<endl;
       n++;
       
     }
     
     gr->SetLineWidth(2);
     gr->SetLineColor(i+1);
     gr->SetMarkerColor(i+1);
     gr->SetFillColor(i+1);

     if(i>3){
       gr->SetLineColor(i+2);
       gr->SetMarkerColor(i+2);
       gr->SetFillColor(i+2);
     }
     
     graph.push_back(gr);
     
   }

   
   
  graph[0]->GetXaxis()->SetTitle("E_{T} threshold [GeV]");
  graph[0]->GetXaxis()->SetLimits(0,200);
  graph[0]->GetYaxis()->SetTitle("Rate [kHz]");
  graph[0]->GetYaxis()->SetTitleSize(20);
  graph[0]->GetYaxis()->SetTitleOffset(1.5);
  graph[0]->GetYaxis()->SetTitleFont(43);
  graph[0]->GetYaxis()->SetRangeUser(1.,5e4);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetLogy();
  c->SetTicks();
  c->SetGrid();

  graph[0]->Draw("AL3");
  for(unsigned int i=1; i<graph.size(); i++)
    graph[i]->Draw("sameL3");

  TLatex *texl = new TLatex(1,6e4,Form("CMS Simulation Preliminary, #sqrt{s}=14 TeV, PU=%i",PU));
  texl->SetTextSize(0.03);
  texl->Draw("same"); 

  TLegend* leg=new TLegend(0.6,0.4,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  for(unsigned int i=0;i<graph.size();i++){
    TGraphErrors* gr = (TGraphErrors*)graph[i]->Clone();
    gr->SetFillColor(0);
    leg->AddEntry(gr,leg_entry[i]);	
  }
  leg->Draw("same");





  if(save){
    c->SaveAs("plots/"+plotname+".pdf");
  }

  return;

}







vector<TH1F*> histo_ET_max_Mjj_core_cut(TString filename, float mjj, float core_cut){

  TChain * tree = new TChain("jets");
  tree->Add(filename);
  tree->SetBranchStatus("*",0);
 
  TH1F* h_SingleJet=new TH1F("h_SingleJet","h_SingleJet",1000,0,1000);
  TH1F* h_DoubleJet=new TH1F("h_DoubleJet","h_DoubleJet",1000,0,1000);
  TH1F* h_DoubleJet_pm=new TH1F("h_DoubleJet_pm","h_DoubleJet_pm",1000,0,1000);
  TH1F* h_DoubleJet_pm_mjj=new TH1F("h_DoubleJet_pm_mjj","h_DoubleJet_pm_mjj",1000,0,1000);
  

  vector<float>* _jets_raw_Luca_pt;
  vector<float>* _jets_0p1_core_ok_pt;
  vector<float>* _jets_PU_subtr_cone_C3D;
  vector<float>* _jets_eta;
  vector<float>* _jets_phi;

  tree->SetBranchAddress("jets_raw_Luca_pt", &_jets_raw_Luca_pt);
  tree->SetBranchAddress("jets_0p1_core_ok_pt", &_jets_0p1_core_ok_pt);
  tree->SetBranchAddress("jets_PU_subtr_cone_C3D", &_jets_PU_subtr_cone_C3D);
  tree->SetBranchAddress("jets_eta", &_jets_eta);
  tree->SetBranchAddress("jets_phi", &_jets_phi);


  Long64_t nentries = tree->GetEntries();
  cout<<nentries<<" events"<<endl;

  for (int i=0;i<nentries;i++) {

    if(i%10000==0)
      cout<<"i="<<i<<endl;
    
    _jets_raw_Luca_pt = 0;
    _jets_0p1_core_ok_pt = 0;
    _jets_PU_subtr_cone_C3D = 0;
    _jets_eta = 0;
    _jets_phi = 0;

    tree->GetEntry(i);

    float pt_max1 = 0.;
    float pt_max2 = 0.;    
    TLorentzVector jet_max_plus;
    jet_max_plus.SetPtEtaPhiM(0,0,0,0);
    TLorentzVector jet_max_minus;
    jet_max_minus.SetPtEtaPhiM(0,0,0,0);
    
    for(unsigned int ijet=0; ijet<(*_jets_raw_Luca_pt).size(); ijet++){

      if((*_jets_0p1_core_ok_pt)[ijet]/((*_jets_raw_Luca_pt)[ijet]-2*(*_jets_PU_subtr_cone_C3D)[ijet])<core_cut) continue;
            
      TLorentzVector jet;
      float pt = (4.4374 -0.948102 * log(max((*_jets_raw_Luca_pt)[ijet]-2*(*_jets_PU_subtr_cone_C3D)[ijet],float(20))) + .0686934* pow(log(max((*_jets_raw_Luca_pt)[ijet]-2*(*_jets_PU_subtr_cone_C3D)[ijet],float(20))),2) ) * max((*_jets_raw_Luca_pt)[ijet]-2*(*_jets_PU_subtr_cone_C3D)[ijet],float(0));
      jet.SetPtEtaPhiM(pt, (*_jets_eta)[ijet], (*_jets_phi)[ijet], 0);

      if(pt>pt_max1){
	pt_max2 = pt_max1;
	pt_max1 = pt;
      }
      else if(pt>pt_max2)
	pt_max2 = pt;

      if((*_jets_eta)[ijet]>0 && jet.Pt()>jet_max_plus.Pt())
	jet_max_plus = jet;
      if((*_jets_eta)[ijet]<0 && jet.Pt()>jet_max_minus.Pt())
	jet_max_minus = jet;    

    }

    h_SingleJet->Fill(pt_max1);
    h_DoubleJet->Fill(pt_max2);
    h_DoubleJet_pm->Fill(min(jet_max_plus.Pt(),jet_max_minus.Pt()));    

    if((jet_max_plus+jet_max_minus).M()>mjj)
      h_DoubleJet_pm_mjj->Fill(min(jet_max_plus.Pt(),jet_max_minus.Pt()));

  }

  h_SingleJet->Scale(1./nentries);
  h_DoubleJet->Scale(1./nentries);
  h_DoubleJet_pm->Scale(1./nentries);
  h_DoubleJet_pm_mjj->Scale(1./nentries);

  vector<TH1F*> histos;
  histos.push_back(h_SingleJet);
  histos.push_back(h_DoubleJet);
  histos.push_back(h_DoubleJet_pm);
  histos.push_back(h_DoubleJet_pm_mjj);
  

  return histos;

}






void plot_rate_jets_core_cut(TString filename, TString var, int mjj_cut, float core_cut, float norm, bool save=false, TString plotname=""){

   
  vector<TH1F*> histos = histo_ET_max_Mjj_core_cut(filename,float(mjj_cut),core_cut);
  
   vector<TString> leg_entry;
   leg_entry.push_back("Single jet");
   leg_entry.push_back("Double jet");
   leg_entry.push_back("Double jet #eta_{1}#eta_{2}<0");
   leg_entry.push_back(Form("Double jet #eta_{1}#eta_{2}<0 + M_{12}>%i",mjj_cut));
   
   vector<TGraphErrors*> graph;


   for(unsigned int i=0; i<histos.size(); i++){
          
     TH1F* h = histos[i];
     TGraphErrors* gr=new TGraphErrors();
     int lim = h->GetNbinsX() + 1;
     int n = 0;
          
     for(unsigned int E=0; E<251; E+=5){
       
       int bin = h->FindBin(E);
       float frac = h->Integral(bin,lim);
       gr->SetPoint(n,E,frac*norm);
       cout<<leg_entry[i]<<" ET>"<<E<<endl;
       cout<<frac*norm<<" kHz"<<endl;
       n++;
       
     }
     
     gr->SetLineWidth(2);
     gr->SetLineColor(i+1);
     gr->SetMarkerStyle(21);
     gr->SetMarkerSize(0.7);
     gr->SetMarkerColor(i+1);
     gr->SetFillColor(0);
     
     graph.push_back(gr);
     
   }

   
   
  graph[0]->GetXaxis()->SetTitle("E_{T} threshold [GeV]");
  graph[0]->GetXaxis()->SetLimits(0,250);
  graph[0]->GetYaxis()->SetTitle("Rate [kHz]");
  graph[0]->GetYaxis()->SetTitleSize(20);
  graph[0]->GetYaxis()->SetTitleOffset(1.5);
  graph[0]->GetYaxis()->SetTitleFont(43);
  graph[0]->GetYaxis()->SetRangeUser(1.5e-2,1.5e6);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetLogy();
  c->SetTicks();
  c->SetGrid();

  graph[0]->Draw("APL");
  for(unsigned int i=1; i<graph.size(); i++)
    graph[i]->Draw("samePL");

  TLatex *texl = new TLatex(1,1.6e6,"CMS Simulation Preliminary, #sqrt{s}=14 TeV, PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same"); 

  TLegend* leg=new TLegend(0.55,0.6,0.75,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  for(unsigned int i=0;i<graph.size();i++)
     leg->AddEntry(graph[i],leg_entry[i]);	
  leg->Draw("same");





  if(save){
    c->SaveAs("plots/"+plotname+".pdf");
  }

  return;

}







void plot_Mjj350(){

  TString filename="/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_*";

  float norm = 11.2456*2808;

  plot_rate_jets(filename, 350, norm, true, "rate_jets_Mjj350_PU200",200);


}






void plot_Mjj350_core_cut(){

  TString filename="/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_*";
  TString var="(4.4374 -0.948102 * log(max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_C3D,20)) + .0686934* pow(log(max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_C3D,20)),2) ) * max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_C3D,0)";

  float norm = 11.2456*2808;

  plot_rate_jets_core_cut(filename, var, 350, 0.5, norm, true, "rate_jets_Mjj350_core0p5");


}






void plot_Mjj350_PU140(){

  TString filename="/vols/cms/tstreble/HGC_ntuples/SingleNu_PU140/calibr_jet_ntuples/ntuple_calibr_jet_*";

  float norm = 11.2456*2808;

  plot_rate_jets(filename, 350, norm, true, "rate_jets_Mjj350_PU140",140);


}







void plot_Mjj500_PU200(){

  TString filename="/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_*";

  float norm = 11.2456*2808;

  plot_rate_jets(filename, 500, norm, true, "rate_jets_Mjj500_PU200",200);


}






void plot_Mjj500_PU140(){

  TString filename="/vols/cms/tstreble/HGC_ntuples/SingleNu_PU140/calibr_jet_ntuples/ntuple_calibr_jet_*";

  float norm = 11.2456*2808;

  plot_rate_jets(filename,  500, norm, true, "rate_jets_Mjj500_PU140",140);


}




void plot_SingleJet_PU140_200(){

  vector<TString> filename;
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_*");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_*");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU140/calibr_jet_ntuples/ntuple_calibr_jet_*");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU140/calibr_jet_ntuples/ntuple_calibr_jet_*");

  vector<TString> var;
  var.push_back("(4.4374 -0.948102 * log(max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_C3D,20)) + .0686934* pow(log(max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_C3D,20)),2) ) * max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_C3D,0)");
  var.push_back("(4.4374 -0.948102 * log(max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_C3D,20)) + .0686934* pow(log(max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_C3D,20)),2) ) * max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_C3D,0)*(abs(jets_eta)<2.7)");
  var.push_back("(4.4374 -0.948102 * log(max(jets_raw_Luca_pt-140./200.*2*jets_PU_subtr_cone_C3D,20)) + .0686934* pow(log(max(jets_raw_Luca_pt-140./200.*2*jets_PU_subtr_cone_C3D,20)),2) ) * max(jets_raw_Luca_pt-140./200.*2*jets_PU_subtr_cone_C3D,0)");
  var.push_back("(4.4374 -0.948102 * log(max(jets_raw_Luca_pt-140./200.*2*jets_PU_subtr_cone_C3D,20)) + .0686934* pow(log(max(jets_raw_Luca_pt-140./200.*2*jets_PU_subtr_cone_C3D,20)),2) ) * max(jets_raw_Luca_pt-140./200.*2*jets_PU_subtr_cone_C3D,0)*(abs(jets_eta)<2.7)");


  vector<TString> leg_entry;
  leg_entry.push_back("PU200");
  leg_entry.push_back("PU200 |#eta|<2.7");
  leg_entry.push_back("PU140");
  leg_entry.push_back("PU140 |#eta|<2.7");


  float norm = 11.2456*2808;

  plot_rate_SingleJet(filename, var, leg_entry, norm, true, "rate_SingleJet_PU140_200");

}






void plot_SingleJet_PU200_GEO(){

  vector<TString> filename;
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_*");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_jet_ntuples/ntuple_calibr_jet_*");


  vector<TString> var;
  var.push_back("(4.4374 -0.948102 * log(max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_C3D,20)) + .0686934* pow(log(max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_C3D,20)),2) ) * max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_C3D,0)");
  var.push_back("1.06*(4.4374 -0.948102 * log(max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_GEO_C3D,20)) + .0686934* pow(log(max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_GEO_C3D,20)),2) ) * max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_GEO_C3D,0)");


  vector<TString> leg_entry;
  leg_entry.push_back("PU200 NN");
  leg_entry.push_back("PU200 GEO");

  float norm = 11.2456*2808;

  plot_rate_SingleJet(filename, var, leg_entry, norm, true, "rate_SingleJet_PU200_GEO");

}






void plot_Mjj500_PU200_GEO(){

  TString filename="/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_jet_ntuples/ntuple_calibr_jet_*";

  float norm = 11.2456*2808;

  plot_rate_jets_GEO(filename, 500, norm, true, "rate_jets_Mjj500_PU200_GEO",200);


}






void plot_SingleJet_PU200_GEO_recal(){

  vector<TString> filename;
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_*");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_jet_ntuples/ntuple_calibr_jet_*");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR_new/jet_ntuples_merged/ntuple_jet_merged_*");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR_JetPU0cal/jet_ntuples_merged/ntuple_jet_merged_*");

  vector<TString> treename;
  treename.push_back("jets");
  treename.push_back("jets");
  treename.push_back("HGCalTriggerNtupleJet");
  treename.push_back("HGCalTriggerNtupleJet");

  vector<TString> var;
  var.push_back("(4.4374 -0.948102 * log(max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_C3D,0)) + .0686934* pow(log(max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_C3D,0)),2) ) * max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_C3D,0)");
  var.push_back("1.06*(4.4374 -0.948102 * log(max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_GEO_C3D,0)) + .0686934* pow(log(max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_GEO_C3D,0)");
  var.push_back("1.06*(4.4374 -0.948102 * log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)) + .0686934* pow(log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)");
  var.push_back("1.1*1.04*(4.16098 -1.00815e+00 * log(max(jets_pt-3*jets_PU_subtr_cone_GEO_C3D,0)) + 7.59202e-02* pow(log(max(jets_pt-3*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-3*jets_PU_subtr_cone_GEO_C3D,0)");
  //var.push_back("1.06*(4.4374 -0.948102 * log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)) + .0686934* pow(log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)");


  vector<TString> leg_entry;
  leg_entry.push_back("PU200 NN");
  leg_entry.push_back("PU200 GEO");
  leg_entry.push_back("PU200 GEO new");
  leg_entry.push_back("PU200 GEO recalibr. C2D");

  float norm = 11.2456*2808;

  plot_rate_SingleJet(filename, treename, var, leg_entry, norm, true, "rate_SingleJet_PU200_GEO_C2D_recalibr");

}







void plot_Mjj500_PU200_GEO_recal(){

  TString filename="/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR_JetPU0cal/jet_ntuples_merged/ntuple_jet_merged_*";

  float norm = 11.2456*2808;

  plot_rate_jets_GEO_recal(filename, 500, norm, true, "rate_jets_Mjj500_PU200_GEO_recal",200);


}






void plot_SingleJet_PU200_dRNNC2D(){

  vector<TString> filename;
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_*");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_jet_ntuples/ntuple_calibr_jet_*");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR_new/jet_ntuples_merged/ntuple_jet_merged_*");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*");

  vector<TString> treename;
  treename.push_back("jets");
  treename.push_back("jets");
  treename.push_back("HGCalTriggerNtupleJet");
  treename.push_back("HGCalTriggerNtupleJet");

  vector<TString> var;
  var.push_back("(4.4374 -0.948102 * log(max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_C3D,0)) + .0686934* pow(log(max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_C3D,0)),2) ) * max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_C3D,0)");
  var.push_back("1.06*(4.4374 -0.948102 * log(max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_GEO_C3D,0)) + .0686934* pow(log(max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_GEO_C3D,0)");
  var.push_back("1.06*(4.4374 -0.948102 * log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)) + .0686934* pow(log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)");
  var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)) + 1.02929e-01* pow(log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)");


  vector<TString> leg_entry;
  leg_entry.push_back("PU200 NN");
  leg_entry.push_back("PU200 GEO");
  leg_entry.push_back("PU200 GEO new");
  leg_entry.push_back("PU200 NN + GEO");

  float norm = 11.2456*2808;

  plot_rate_SingleJet(filename, treename, var, leg_entry, norm, true, "rate_SingleJet_PU200_dRNNC2D");

}








void plot_SingleJet_PU200_dRNNC2D_eta2p7(){

  vector<TString> filename;
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_*");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_jet_ntuples/ntuple_calibr_jet_*");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR_new/jet_ntuples_merged/ntuple_jet_merged_*");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*");

  vector<TString> treename;
  treename.push_back("jets");
  treename.push_back("jets");
  treename.push_back("HGCalTriggerNtupleJet");
  treename.push_back("HGCalTriggerNtupleJet");

  vector<TString> var;
  var.push_back("(4.4374 -0.948102 * log(max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_C3D,0)) + .0686934* pow(log(max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_C3D,0)),2) ) * max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_C3D,0) * (abs(jets_eta)<2.7)");
  var.push_back("1.06*(4.4374 -0.948102 * log(max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_GEO_C3D,0)) + .0686934* pow(log(max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_GEO_C3D,0) * (abs(jets_eta)<2.7)");
  var.push_back("1.06*(4.4374 -0.948102 * log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)) + .0686934* pow(log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0) * (abs(jets_eta)<2.7)");
  var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)) + 1.02929e-01* pow(log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0) * (abs(jets_eta)<2.7)");


  vector<TString> leg_entry;
  leg_entry.push_back("PU200 NN");
  leg_entry.push_back("PU200 GEO");
  leg_entry.push_back("PU200 GEO new");
  leg_entry.push_back("PU200 NN + GEO");

  float norm = 11.2456*2808;

  plot_rate_SingleJet(filename, treename, var, leg_entry, norm, true, "rate_SingleJet_PU200_dRNNC2D_eta2p7");

}








void plot_Mjj500_PU200_dRNNC2D(){

  TString filename="/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*";

  float norm = 11.2456*2808;

  plot_rate_jets_dRNNC2D(filename, 500, norm, true, "rate_jets_Mjj500_PU200_dRNNC2D",200);


}






void plot_Mjj500_PU140_dRNNC2D(){

  TString filename="/vols/cms/tstreble/HGC_ntuples/SingleNu_PU140_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*";

  float norm = 11.2456*2808;

  plot_rate_jets_dRNNC2D(filename, 500, norm, true, "rate_jets_Mjj500_PU140_dRNNC2D",140);


}





void plot_Mjj500_PU200_dRNNC2D_clean(){

  TString filename="/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*";

  float norm = 11.2456*2808;

  plot_rate_jets_dRNNC2D(filename, 500, norm, true, "rate_jets_Mjj500_PU200_dRNNC2D_clean",200);


}






void plot_Mjj500_PU200_dRNNC2D_clean_fix_frac(){

  TString filename="/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged_clean_fix_frac/ntuple_jet_merged_*";

  float norm = 11.2456*2808;

  plot_rate_jets_dRNNC2D(filename, 500, norm, true, "rate_jets_Mjj500_PU200_dRNNC2D_clean_fix_frac",200);


}




void plot_Mjj500_PU200_TowerMap_6cm(){

  TString filename="/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_TowerMap_C2D_dR_6cm/jet_ntuples_merged/ntuple_jet_merged_*";

  float norm = 11.2456*2808;

  plot_rate_jets_TowerMap_6cm(filename, 500, norm, true, "rate_jets_Mjj500_PU200_TowerMap_6cm",200);


}







void plot_SingleJet_PU200_dRNNC2D_er(){

  vector<TString> filename;
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_*");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_*");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_*");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*");

  vector<TString> treename;
  treename.push_back("jets");
  treename.push_back("jets");
  treename.push_back("jets");
  treename.push_back("HGCalTriggerNtupleJet");
  treename.push_back("HGCalTriggerNtupleJet");
  treename.push_back("HGCalTriggerNtupleJet");

  vector<TString> var;
  var.push_back("(4.4374 -0.948102 * log(max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_C3D,20)) + .0686934* pow(log(max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_C3D,20)),2) ) * max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_C3D,0)");
  var.push_back("(4.4374 -0.948102 * log(max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_C3D,20)) + .0686934* pow(log(max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_C3D,20)),2) ) * max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_C3D,0)*(abs(jets_eta)<2.7)");
 var.push_back("(4.4374 -0.948102 * log(max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_C3D,20)) + .0686934* pow(log(max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_C3D,20)),2) ) * max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_C3D,0)*(abs(jets_eta)>2.7)");

  var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)) + 1.02929e-01* pow(log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)");
  var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)) + 1.02929e-01* pow(log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)*(abs(jets_eta)<2.7)");
 var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)) + 1.02929e-01* pow(log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)*(abs(jets_eta)>2.7)");


  vector<TString> leg_entry;
  leg_entry.push_back("PU200 NN");
  leg_entry.push_back("PU200 NN |#eta|<2.7");
  leg_entry.push_back("PU200 NN |#eta|>2.7");
  leg_entry.push_back("PU200 NN + GEO");
  leg_entry.push_back("PU200 NN + GEO |#eta|<2.7");
  leg_entry.push_back("PU200 NN + GEO |#eta|>2.7");

  float norm = 11.2456*2808;

  plot_rate_SingleJet(filename, treename, var, leg_entry, norm, true, "rate_SingleJet_PU200_dRNNC2D_er");

}






void plot_Mjj500_PU200_dRNNC2D_layer_fraction5(){

  TString filename="/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*";


  float norm = 11.2456*2808;

  plot_rate_jets_dRNNC2D_layer_fraction5(filename, 500, norm, true, "rate_jets_Mjj500_PU200_dRNNC2D_layer_fraction5",200);


}






void plot_Mjj500_PU200_dRNNC2D_Fisher(){

  TString filename="/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*";


  float norm = 11.2456*2808;

  plot_rate_jets_dRNNC2D_Fisher(filename, 500, norm, true, "rate_jets_Mjj500_PU200_dRNNC2D_Fisher",200);


}









void plot_SingleTau_PU200_dRNNC2D(){

  vector<TString> filename;
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*");


  vector<TString> treename;
  treename.push_back("HGCalTriggerNtupleJet");
  treename.push_back("HGCalTriggerNtupleJet");
  treename.push_back("HGCalTriggerNtupleJet");
  treename.push_back("HGCalTriggerNtupleJet");

  vector<TString> var;
  var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)) + 1.02929e-01* pow(log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)");
  var.push_back("1.1/(0.93-1/(0.2*max(jets_pt-1.5*jets_PU_subtr_cone_GEO_C3D,20)+1e-3*pow(max(jets_pt-1.5*jets_PU_subtr_cone_GEO_C3D,20),2))) * (jets_pt-1.5*jets_PU_subtr_cone_GEO_C3D)");
  var.push_back("1.1/(0.93-1/(0.2*max(jets_pt-1.5*jets_PU_subtr_cone_GEO_C3D,20)+1e-3*pow(max(jets_pt-1.5*jets_PU_subtr_cone_GEO_C3D,20),2))) * (jets_pt-1.5*jets_PU_subtr_cone_GEO_C3D)*(layer_jets_energy_fraction[5]<0.2 || 1.1/(0.93-1/(0.2*max(jets_pt-1.5*jets_PU_subtr_cone_GEO_C3D,20)+1e-3*pow(max(jets_pt-1.5*jets_PU_subtr_cone_GEO_C3D,20),2))) * (jets_pt-1.5*jets_PU_subtr_cone_GEO_C3D)>45)");
  var.push_back("1.1/(0.93-1/(0.2*max(jets_pt-1.5*jets_PU_subtr_cone_GEO_C3D,20)+1e-3*pow(max(jets_pt-1.5*jets_PU_subtr_cone_GEO_C3D,20),2))) * (jets_pt-1.5*jets_PU_subtr_cone_GEO_C3D)*(jets_Fisher_VBF>0.5 || 1.1/(0.93-1/(0.2*max(jets_pt-1.5*jets_PU_subtr_cone_GEO_C3D,20)+1e-3*pow(max(jets_pt-1.5*jets_PU_subtr_cone_GEO_C3D,20),2))) * (jets_pt-1.5*jets_PU_subtr_cone_GEO_C3D)>45)");
  

  vector<TString> leg_entry;
  leg_entry.push_back("SingleJet");
  leg_entry.push_back("SingleTau");
  leg_entry.push_back("SingleTau + f layer#5<0.2");
  leg_entry.push_back("SingleTau + Fischer discr.>0.5");

  float norm = 11.2456*2808;

  plot_rate_SingleJet(filename, treename, var, leg_entry, norm, true, "rate_SingleTau_PU200_dRNNC2D");

}










void plot_SingleJet_PU200_dRNNC2D_clean(){

  vector<TString> filename;
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged_clean_fix_frac/ntuple_jet_merged_*");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*");

  vector<TString> treename;
  treename.push_back("HGCalTriggerNtupleJet");
  treename.push_back("HGCalTriggerNtupleJet");
  treename.push_back("HGCalTriggerNtupleJet");

  vector<TString> var;
  var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)) + 1.02929e-01* pow(log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)");
  var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_clean_pt,0)) + 1.02929e-01* pow(log(max(jets_clean_pt,0)),2) ) * max(jets_clean_pt,0)");
  var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_clean_pt,0)) + 1.02929e-01* pow(log(max(jets_clean_pt,0)),2) ) * max(jets_clean_pt,0)");


  vector<TString> leg_entry;
  leg_entry.push_back("PUS");
  leg_entry.push_back("Clean fix frac.");
  leg_entry.push_back("Clean #eta-dep. frac.");

  float norm = 11.2456*2808;

  plot_rate_SingleJet(filename, treename, var, leg_entry, norm, true, "rate_SingleJet_PU200_dRNNC2D_clean");

}









void plot_SingleJet_PU140_PU200_dRNNC2D(){

  vector<TString> filename;
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU140_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*");
  //filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*");
  //filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU140_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*");

  vector<TString> treename;
  treename.push_back("HGCalTriggerNtupleJet");
  treename.push_back("HGCalTriggerNtupleJet");
  //treename.push_back("HGCalTriggerNtupleJet");
  //treename.push_back("HGCalTriggerNtupleJet");

  vector<TString> var;
  var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)) + 1.02929e-01* pow(log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)");
  var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt-140./200.*2*jets_PU_subtr_cone_GEO_C3D,0)) + 1.02929e-01* pow(log(max(jets_pt-140./200.*2*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-140./200.*2*jets_PU_subtr_cone_GEO_C3D,0)");
  

  vector<TString> leg_entry;
  leg_entry.push_back("PU=200");
  leg_entry.push_back("PU=140");
  //leg_entry.push_back("PU=200, |#eta|<2.7");
  //leg_entry.push_back("PU=140, |#eta|<2.7");

  float norm = 11.2456*2808;

  plot_rate_SingleJet(filename, treename, var, leg_entry, norm, true, "rate_SingleJet_PU140_PU200_dRNNC2D");

}




void plot_SingleTau_PU140_PU200_dRNNC2D(){

  vector<TString> filename;
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU140_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*");


  vector<TString> treename;
  treename.push_back("HGCalTriggerNtupleJet");
  treename.push_back("HGCalTriggerNtupleJet");

  vector<TString> var;
  var.push_back("1.1/(0.93-1/(0.2*max(jets_pt-1.5*jets_PU_subtr_cone_GEO_C3D,20)+1e-3*pow(max(jets_pt-1.5*jets_PU_subtr_cone_GEO_C3D,20),2))) * (jets_pt-1.5*jets_PU_subtr_cone_GEO_C3D)");
  var.push_back("1.1/(0.93-1/(0.2*max(jets_pt-140./200.*1.5*jets_PU_subtr_cone_GEO_C3D,20)+1e-3*pow(max(jets_pt-140./200.*1.5*jets_PU_subtr_cone_GEO_C3D,20),2))) * (jets_pt-140./200.*1.5*jets_PU_subtr_cone_GEO_C3D)");

  

  vector<TString> leg_entry;
  leg_entry.push_back("PU=200");
  leg_entry.push_back("PU=140");

  float norm = 11.2456*2808;

  plot_rate_SingleJet(filename, treename, var, leg_entry, norm, true, "rate_SingleTau_PU140_PU200_dRNNC2D");

}










void plot_SingleJet_PU200_dRC3D_0p03_recal(){

  vector<TString> filename;
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRC3D_0p03_recal/jet_ntuples_merged/ntuple_jet_merged_1*.root");

  vector<TString> treename;
  treename.push_back("HGCalTriggerNtupleJet");
  treename.push_back("HGCalTriggerNtupleJet");

  vector<TString> var;
  var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)) + 1.02929e-01* pow(log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)");
  var.push_back("max(min(1.06/(-4.82362e-01 + 4.58856e-01 * log(max(jets_pt-4.5*jets_PU_subtr_cone_GEO_C3D,0)) -2.58405e-02 * pow(log(max(jets_pt-4.5*jets_PU_subtr_cone_GEO_C3D,0)),2) ),2),0)*max(jets_pt-4.5*jets_PU_subtr_cone_GEO_C3D,0)");


  vector<TString> leg_entry;
  leg_entry.push_back("dR=0.01 default C3D cal.");
  leg_entry.push_back("dR=0.03 C3D recal.");


  float norm = 11.2456*2808;

  plot_rate_SingleJet(filename, treename, var, leg_entry, norm, true, "rate_SingleJet_PU200_dRC3D_0p03_recal");

}










void plot_SingleJet_PU0_dRC3D_histo(){

  vector<TString> filename;
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C3D_polarHisto_dR0p03/jet_ntuples_merged/ntuple_jet_merged_*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRC3D_polarHisto_thresh_20MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRC3D_polarHisto_thresh_50MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root");

  vector<TString> treename;
  treename.push_back("HGCalTriggerNtupleJet");
  treename.push_back("HGCalTriggerNtupleJet");
  treename.push_back("HGCalTriggerNtupleJet");
  treename.push_back("HGCalTriggerNtupleJet");
  treename.push_back("HGCalTriggerNtupleJet");

  vector<TString> var;
  var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)) + 1.02929e-01* pow(log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)");
  var.push_back("1.17*(4.98004e+00 -1.23767e+00 * log(max(jets_pt-1.1*jets_PU_subtr_cone_GEO_C3D,0)) + 1.07929e-01* pow(log(max(jets_pt-1.1*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-1.1*jets_PU_subtr_cone_GEO_C3D,0)");
    var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)) + 1.02929e-01* pow(log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)");
  var.push_back("1.10*(4.98004e+00 -1.23767e+00 * log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)) + 1.01929e-01* pow(log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)");
  var.push_back("1.20*(4.98004e+00 -1.25767e+00 * log(max(jets_pt-1.5*jets_PU_subtr_cone_GEO_C3D,0)) + 1.02929e-01* pow(log(max(jets_pt-1.5*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-1.5*jets_PU_subtr_cone_GEO_C3D,0)");
  

  vector<TString> leg_entry;
  leg_entry.push_back("Cone dr=0.01");
  leg_entry.push_back("Histo dr=0.01 Max. finding");
  leg_entry.push_back("Histo dr=0.03 Max. finding");
  leg_entry.push_back("Histo dr=0.01 20 MIPT-thresh.");
  leg_entry.push_back("Histo dr=0.01 50 MIPT-thresh.");



  float norm = 11.2456*2808;

  plot_rate_SingleJet(filename, treename, var, leg_entry, norm, true, "rate_SingleJet_PU200_dRC3D_histo");

}







void plot_SingleJet_PU200_dRC3D_histo(){

  vector<TString> filename;
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C3D_polarHisto_dR0p03/jet_ntuples_merged/ntuple_jet_merged_*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRC3D_polarHisto_thresh_20MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRC3D_polarHisto_thresh_50MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root");

  vector<TString> treename;
  treename.push_back("HGCalTriggerNtupleJet");
  treename.push_back("HGCalTriggerNtupleJet");
  treename.push_back("HGCalTriggerNtupleJet");
  treename.push_back("HGCalTriggerNtupleJet");
  treename.push_back("HGCalTriggerNtupleJet");

  vector<TString> var;
  var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)) + 1.02929e-01* pow(log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)");
  var.push_back("1.17*(4.98004e+00 -1.23767e+00 * log(max(jets_pt-1.1*jets_PU_subtr_cone_GEO_C3D,0)) + 1.07929e-01* pow(log(max(jets_pt-1.1*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-1.1*jets_PU_subtr_cone_GEO_C3D,0)");
    var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)) + 1.02929e-01* pow(log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)");
  var.push_back("1.10*(4.98004e+00 -1.23767e+00 * log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)) + 1.01929e-01* pow(log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)");
  var.push_back("1.20*(4.98004e+00 -1.25767e+00 * log(max(jets_pt-1.5*jets_PU_subtr_cone_GEO_C3D,0)) + 1.02929e-01* pow(log(max(jets_pt-1.5*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-1.5*jets_PU_subtr_cone_GEO_C3D,0)");
  

  vector<TString> leg_entry;
  leg_entry.push_back("Cone dr=0.01");
  leg_entry.push_back("Histo dr=0.01 Max. finding");
  leg_entry.push_back("Histo dr=0.03 Max. finding");
  leg_entry.push_back("Histo dr=0.01 20 MIPT-thresh.");
  leg_entry.push_back("Histo dr=0.01 50 MIPT-thresh.");



  float norm = 11.2456*2808;

  plot_rate_SingleJet(filename, treename, var, leg_entry, norm, true, "rate_SingleJet_PU200_dRC3D_histo");

}










void plot_SingleJet_PU200_test(){

  vector<TString> filename;
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1*.root");


  vector<TString> treename;
  treename.push_back("HGCalTriggerNtupleJet");
  treename.push_back("HGCalTriggerNtupleJet");
  treename.push_back("HGCalTriggerNtupleJet");

  vector<TString> var;
  var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt-1*jets_PU_subtr_cone_GEO_C3D,0)) + 1.02929e-01* pow(log(max(jets_pt-1*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-1*jets_PU_subtr_cone_GEO_C3D,0)");
  var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)) + 1.02929e-01* pow(log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)");
  var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt-3*jets_PU_subtr_cone_GEO_C3D,0)) + 1.02929e-01* pow(log(max(jets_pt-3*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-3*jets_PU_subtr_cone_GEO_C3D,0)");



  vector<TString> leg_entry;
  leg_entry.push_back("cone PUS -50%");
  leg_entry.push_back("cone PUS nominal");
  leg_entry.push_back("cone PUS +50%");


  float norm = 11.2456*2808;

  plot_rate_SingleJet(filename, treename, var, leg_entry, norm, true, "rate_SingleJet_PU200_test");

}










void plot_SingleJet_PU200_dRC3D_histo_TC(){

  vector<TString> filename;
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root");
 //  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C3D_polarHisto_dR0p03/jet_ntuples_merged/ntuple_jet_merged_*.root");
 //  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRC3D_polarHisto_thresh_20MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root");
 // filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C3D_polarHisto_dR0p03_TC/jet_ntuples_merged/ntuple_jet_merged_*.root");
 //  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRC3D_polarHisto_thresh_20MIPT_TC/jet_ntuples_merged/ntuple_jet_merged_*.root");

  vector<TString> treename;
  treename.push_back("HGCalTriggerNtupleJet");
  // treename.push_back("HGCalTriggerNtupleJet");
  // treename.push_back("HGCalTriggerNtupleJet");
  // treename.push_back("HGCalTriggerNtupleJet");
  // treename.push_back("HGCalTriggerNtupleJet");

  vector<TString> var;
  var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)) + 1.02929e-01* pow(log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)");
  //   var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)) + 1.02929e-01* pow(log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)");
  // var.push_back("1.10*(4.98004e+00 -1.23767e+00 * log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)) + 1.01929e-01* pow(log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)");
  // var.push_back("0.84*(5.09004e+00 -1.22767e+00 * log(max(jets_pt-2.6*jets_PU_subtr_cone_GEO_C3D,0)) + 1.02929e-01* pow(log(max(jets_pt-2.6*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-2.6*jets_PU_subtr_cone_GEO_C3D,0)");
  // var.push_back("0.98*(4.98004e+00 -1.23767e+00 * log(max(jets_pt-2.6*jets_PU_subtr_cone_GEO_C3D,0)) + 1.00929e-01* pow(log(max(jets_pt-2.6*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-2.6*jets_PU_subtr_cone_GEO_C3D,0)");  

  vector<TString> leg_entry;
  leg_entry.push_back("C2D + Cone dr=0.01");
  // leg_entry.push_back("C2D + Histo dr=0.03 Max. finding");
  // leg_entry.push_back("C2D + Histo dr=0.01 20 MIPT-thresh.");
  // leg_entry.push_back("TC + Histo dr=0.03 Max. finding");
  // leg_entry.push_back("TC + Histo dr=0.01 20 MIPT-thresh."); 


  float norm = 11.2456*2808;

  plot_rate_SingleJet(filename, treename, var, leg_entry, norm, true, "rate_SingleJet_PU200_dRC3D_histo_TC");

}









void plot_SingleJet_PU200_dRC3D_histo_TC_er2p4(){

  vector<TString> filename;
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C3D_polarHisto_dR0p03/jet_ntuples_merged/ntuple_jet_merged_*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRC3D_polarHisto_thresh_20MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root");
 filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C3D_polarHisto_dR0p03_TC/jet_ntuples_merged/ntuple_jet_merged_*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRC3D_polarHisto_thresh_20MIPT_TC/jet_ntuples_merged/ntuple_jet_merged_*.root");

  vector<TString> treename;
  treename.push_back("HGCalTriggerNtupleJet");
  treename.push_back("HGCalTriggerNtupleJet");
  treename.push_back("HGCalTriggerNtupleJet");
  treename.push_back("HGCalTriggerNtupleJet");
  treename.push_back("HGCalTriggerNtupleJet");

  vector<TString> var;
  var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)) + 1.02929e-01* pow(log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0) * (abs(jets_eta)<2.4)");
    var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)) + 1.02929e-01* pow(log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0) * (abs(jets_eta)<2.4)");
  var.push_back("1.10*(4.98004e+00 -1.23767e+00 * log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)) + 1.01929e-01* pow(log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0) * (abs(jets_eta)<2.4)");
  var.push_back("0.84*(5.09004e+00 -1.22767e+00 * log(max(jets_pt-2.6*jets_PU_subtr_cone_GEO_C3D,0)) + 1.02929e-01* pow(log(max(jets_pt-2.6*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-2.6*jets_PU_subtr_cone_GEO_C3D,0) * (abs(jets_eta)<2.4)");
  var.push_back("0.98*(4.98004e+00 -1.23767e+00 * log(max(jets_pt-2.6*jets_PU_subtr_cone_GEO_C3D,0)) + 1.00929e-01* pow(log(max(jets_pt-2.6*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-2.6*jets_PU_subtr_cone_GEO_C3D,0) * (abs(jets_eta)<2.4)");  

  vector<TString> leg_entry;
  leg_entry.push_back("C2D + Cone dr=0.01");
  leg_entry.push_back("C2D + Histo dr=0.03 Max. finding");
  leg_entry.push_back("C2D + Histo dr=0.01 20 MIPT-thresh.");
  leg_entry.push_back("TC + Histo dr=0.03 Max. finding");
  leg_entry.push_back("TC + Histo dr=0.01 20 MIPT-thresh."); 


  float norm = 11.2456*2808;

  plot_rate_SingleJet(filename, treename, var, leg_entry, norm, true, "rate_SingleJet_PU200_dRC3D_histo_TC_er2p4");

}








void plot_SingleJet_PU200_dRC3D_histo_TC_eta2p4_2p8(){

  vector<TString> filename;
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C3D_polarHisto_dR0p03/jet_ntuples_merged/ntuple_jet_merged_*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRC3D_polarHisto_thresh_20MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root");
 filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C3D_polarHisto_dR0p03_TC/jet_ntuples_merged/ntuple_jet_merged_*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRC3D_polarHisto_thresh_20MIPT_TC/jet_ntuples_merged/ntuple_jet_merged_*.root");

  vector<TString> treename;
  treename.push_back("HGCalTriggerNtupleJet");
  treename.push_back("HGCalTriggerNtupleJet");
  treename.push_back("HGCalTriggerNtupleJet");
  treename.push_back("HGCalTriggerNtupleJet");
  treename.push_back("HGCalTriggerNtupleJet");

  vector<TString> var;
  var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)) + 1.02929e-01* pow(log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0) * (abs(jets_eta)>2.4 && abs(jets_eta)<2.8)");
    var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)) + 1.02929e-01* pow(log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0) * (abs(jets_eta)>2.4 && abs(jets_eta)<2.8)");
  var.push_back("1.10*(4.98004e+00 -1.23767e+00 * log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)) + 1.01929e-01* pow(log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0) * (abs(jets_eta)>2.4 && abs(jets_eta)<2.8)");
  var.push_back("0.84*(5.09004e+00 -1.22767e+00 * log(max(jets_pt-2.6*jets_PU_subtr_cone_GEO_C3D,0)) + 1.02929e-01* pow(log(max(jets_pt-2.6*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-2.6*jets_PU_subtr_cone_GEO_C3D,0) * (abs(jets_eta)>2.4 && abs(jets_eta)<2.8)");
  var.push_back("0.98*(4.98004e+00 -1.23767e+00 * log(max(jets_pt-2.6*jets_PU_subtr_cone_GEO_C3D,0)) + 1.00929e-01* pow(log(max(jets_pt-2.6*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-2.6*jets_PU_subtr_cone_GEO_C3D,0) * (abs(jets_eta)>2.4 && abs(jets_eta)<2.8)");  

  vector<TString> leg_entry;
  leg_entry.push_back("C2D + Cone dr=0.01");
  leg_entry.push_back("C2D + Histo dr=0.03 Max. finding");
  leg_entry.push_back("C2D + Histo dr=0.01 20 MIPT-thresh.");
  leg_entry.push_back("TC + Histo dr=0.03 Max. finding");
  leg_entry.push_back("TC + Histo dr=0.01 20 MIPT-thresh."); 


  float norm = 11.2456*2808;

  plot_rate_SingleJet(filename, treename, var, leg_entry, norm, true, "rate_SingleJet_PU200_dRC3D_histo_TC_eta2p4_2p8");

}






//NEW

void plot_SingleJet_PU0_histo(){

  vector<TString> filename;
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C3D_polarHisto_crossRefinedMax/jet_ntuples_merged/ntuple_jet_merged_*.root");


  vector<TString> treename;
  treename.push_back("HGCalTriggerNtupleJet");

  vector<TString> var;
  var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)) + 1.02929e-01* pow(log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)");

  vector<TString> leg_entry;
  leg_entry.push_back("Cone dr=0.01 Max. finding cross refined");

  float norm = 11.2456*2808;

  plot_rate_SingleJet(filename, treename, var, leg_entry, norm, true, "rate_SingleJet_PU0_histo");

}

