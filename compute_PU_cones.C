#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TLorentzVector.h>
#include <TMath.h>
#include <iostream>
#include "Helpers.C"
#include <unordered_map>


void create_cones(TString filein,  TString treename, TString fileout){

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

  vector<float> *_tc_pt;
  vector<float> *_tc_eta;
  vector<float> *_tc_phi;
  vector<float> *_tc_energy;

  vector<float> *_cl3d_pt;
  vector<float> *_cl3d_eta;
  vector<float> *_cl3d_phi;
  vector<float> *_cl3d_energy;

  tree->SetBranchAddress("cl3d_pt",     &_cl3d_pt);
  tree->SetBranchAddress("cl3d_eta",    &_cl3d_eta);
  tree->SetBranchAddress("cl3d_phi",    &_cl3d_phi);
  tree->SetBranchAddress("cl3d_energy", &_cl3d_energy);

  tree->SetBranchAddress("tc_pt",     &_tc_pt);
  tree->SetBranchAddress("tc_eta",    &_tc_eta);
  tree->SetBranchAddress("tc_phi",    &_tc_phi);
  tree->SetBranchAddress("tc_energy", &_tc_energy);

  TTree* tree_new=tree->GetTree()->CloneTree(0);

  //New branches
  vector<float> _cone_eta;
  vector<float> _cone_phi;
  vector<vector<int> > _cone_cl3d;
  vector<int> _cone_ncl3d;
  vector<vector<int> > _cone_tc;
  vector<int> _cone_ntc;

  tree_new->Branch("cone_eta", &_cone_eta);
  tree_new->Branch("cone_phi", &_cone_phi);
  tree_new->Branch("cone_cl3d", &_cone_cl3d);
  tree_new->Branch("cone_ncl3d", &_cone_ncl3d);
  tree_new->Branch("cone_tc", &_cone_tc);
  tree_new->Branch("cone_ntc", &_cone_ntc);

  //eta = 1.5 + ieta*0.1 ieta=0..15
  //phi = -3.1 + iphi*0.4 ieta=0..14 if ieta%2==0
  //phi = -2.9 + iphi*0.4 ieta=0..14 if ieta%2==1
  
  for(int i=0;i<nentries;i++){

    if(i%10000==0)
      cout<<"i="<<i<<endl;
   
    _tc_pt = 0;
    _tc_eta = 0;
    _tc_phi = 0;
    _tc_energy = 0;

    _cl3d_pt = 0;
    _cl3d_eta = 0;
    _cl3d_phi = 0;
    _cl3d_energy = 0;
    
    _cone_eta.clear();
    _cone_phi.clear();
    _cone_cl3d.clear();
    _cone_ncl3d.clear();
    _cone_tc.clear();
    _cone_ntc.clear();

    tree->GetEntry(i);
    
    for(int ieta=0; ieta<16; ieta++){

      float eta_cone = 1.5+0.1*ieta;      

      for(int iphi=0; iphi<15; iphi++){

	float phi_cone = -3.1+0.4*iphi;
	if(ieta%2==1) phi_cone+=0.2;

	_cone_eta.emplace_back(eta_cone);
	_cone_phi.emplace_back(phi_cone);

	_cone_eta.emplace_back(-eta_cone);
	_cone_phi.emplace_back(phi_cone);
	

	TLorentzVector cone_center_plus;
	cone_center_plus.SetPtEtaPhiE(100,eta_cone,phi_cone,100);
	TLorentzVector cone_center_minus;
	cone_center_minus.SetPtEtaPhiE(100,-eta_cone,phi_cone,100);

	vector<int> cone_c3d_plus;
	vector<int> cone_c3d_minus;

	for(unsigned int i_c3d=0; i_c3d<(*_cl3d_pt).size(); i_c3d++){
	  
	  TLorentzVector C3d;
	  C3d.SetPtEtaPhiE((*_cl3d_pt)[i_c3d],(*_cl3d_eta)[i_c3d],(*_cl3d_phi)[i_c3d],(*_cl3d_energy)[i_c3d]);

	  if(C3d.DeltaR(cone_center_plus)<0.2)
	    cone_c3d_plus.emplace_back(i_c3d);
	  if(C3d.DeltaR(cone_center_minus)<0.2)
	    cone_c3d_minus.emplace_back(i_c3d);

	}

	_cone_cl3d.emplace_back(cone_c3d_plus);
	_cone_cl3d.emplace_back(cone_c3d_minus);
	_cone_ncl3d.emplace_back(cone_c3d_plus.size());
	_cone_ncl3d.emplace_back(cone_c3d_minus.size());

	vector<int> cone_tc_plus;
	vector<int> cone_tc_minus;

	for(unsigned int i_tc=0; i_tc<(*_tc_pt).size(); i_tc++){
	  
	  TLorentzVector tc;
	  tc.SetPtEtaPhiE((*_tc_pt)[i_tc],(*_tc_eta)[i_tc],(*_tc_phi)[i_tc],(*_tc_energy)[i_tc]);

	  if(tc.DeltaR(cone_center_plus)<0.2)
	    cone_tc_plus.emplace_back(i_tc);
	  if(tc.DeltaR(cone_center_minus)<0.2)
	    cone_tc_minus.emplace_back(i_tc);

	}

	_cone_tc.emplace_back(cone_tc_plus);
	_cone_tc.emplace_back(cone_tc_minus);
	_cone_ntc.emplace_back(cone_tc_plus.size());
	_cone_ntc.emplace_back(cone_tc_minus.size());


      }

    }
   
    
    tree_new->Fill();
 
  }


  tree_new->Write();
  f_new->Close();

}
