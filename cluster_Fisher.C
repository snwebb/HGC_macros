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





pair<vector<float>,map<pair<int,int>,float> > prod_Ei_Eij_VBF(TString filename, float pt_cut){

  TChain * tree = new TChain("HGCalTriggerNtupleJet");
  tree->Add(filename);
  int nentries = tree->GetEntries();

  vector<int>* _VBF_parton_jets;
  vector<int>* _VBF_parton_genjet;

  vector<float>* _genjet_pt;
  vector<float>* _genjet_eta;  


  vector<vector<int> >* _jets_cl3d;
  vector<vector<unsigned int> >* _cl3d_clusters;
  vector<float>* _cl_MIPpt;
  vector<int>* _cl_HGClayer;


  tree->SetBranchAddress("VBF_parton_jets",        &_VBF_parton_jets);
  tree->SetBranchAddress("VBF_parton_genjet",      &_VBF_parton_genjet);
  
  tree->SetBranchAddress("genjet_pt",        &_genjet_pt);
  tree->SetBranchAddress("genjet_eta",       &_genjet_eta);

  tree->SetBranchAddress("jets_cl3d",        &_jets_cl3d);

  tree->SetBranchAddress("cl3d_clusters",       &_cl3d_clusters);
  tree->SetBranchAddress("cl_mipPt",            &_cl_MIPpt);
  tree->SetBranchAddress("cl_HGClayer",         &_cl_HGClayer);
  

  cout<<"n="<<nentries<<endl;

  vector<float> Ei(26);
  map<pair<int,int>,float> EiEj;
  int nc3ds = 0;

  for(int i=0;i<nentries;i++){

    if(i%1000==0)
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

    for(unsigned int i_VBF=0; i_VBF<(*_VBF_parton_jets).size(); i_VBF++){

      int i_gen = (*_VBF_parton_genjet)[i_VBF];
      int i_jet = (*_VBF_parton_jets)[i_VBF];

      if(i_jet<0 || i_gen<0) continue;
      if(abs((*_genjet_eta)[i_gen])<1.5 || abs((*_genjet_eta)[i_gen])>2.9 || (*_genjet_pt)[i_gen]<pt_cut) continue;

      for(auto & i_c3d : (*_jets_cl3d)[i_jet]){

	vector<float> cl3d_layer_MIPpt(53);
	float cl3d_MIPpt = 0;

	for(auto & i_c2d : (*_cl3d_clusters)[i_c3d]){      
	  cl3d_layer_MIPpt[(*_cl_HGClayer)[i_c2d]] += (*_cl_MIPpt)[i_c2d];
	  cl3d_MIPpt += (*_cl_MIPpt)[i_c2d];
	}

	for(unsigned int i=0; i<26; i++){
	  int i_layer = -1;
	  if(i<14) i_layer = 2*i+1;
	  else i_layer = i+15;
	  
	  Ei[i]+=cl3d_layer_MIPpt[i_layer]/cl3d_MIPpt;
	  
	  for(unsigned int j=0; j<26; j++){
	    int j_layer = -1;
	    if(j<14) j_layer = 2*j+1;
	    else j_layer = j+15;
	    
	    pair<int,int> key=make_pair(i,j);
	    EiEj[key]+=cl3d_layer_MIPpt[i_layer]*cl3d_layer_MIPpt[j_layer]/pow(cl3d_MIPpt,2);

	  }
	  
	}
      
       nc3ds++;

      }
    
    }


  }
  

  cout<<"nc3ds="<<nc3ds<<endl;

  for(int i=0; i<26; i++)
    Ei[i]/=nc3ds;
  for (std::map<pair<int,int>,float>::iterator it=EiEj.begin(); it!=EiEj.end(); ++it)
    it->second/=nc3ds;

  pair<vector<float>,map<pair<int,int>,float> > Ei_EiEj = make_pair(Ei,EiEj);

  return Ei_EiEj;


}









pair<vector<float>,map<pair<int,int>,float> > prod_Ei_Eij_ZB(TString filename, float pt_cut){

  TChain * tree = new TChain("HGCalTriggerNtupleJet");
  tree->Add(filename);
  int nentries = tree->GetEntries();

  vector<float>* _jets_pt;

  vector<vector<int> >* _jets_cl3d;
  vector<vector<unsigned int> >* _cl3d_clusters;
  vector<float>* _cl_MIPpt;
  vector<int>* _cl_HGClayer;

  
  tree->SetBranchAddress("jets_pt",        &_jets_pt);
  tree->SetBranchAddress("jets_cl3d",      &_jets_cl3d);

  tree->SetBranchAddress("cl3d_clusters",       &_cl3d_clusters);
  tree->SetBranchAddress("cl_mipPt",            &_cl_MIPpt);
  tree->SetBranchAddress("cl_HGClayer",         &_cl_HGClayer);

  cout<<"n="<<nentries<<endl;

  vector<float> Ei(26);
  map<pair<int,int>,float> EiEj;
  int nc3ds = 0;
  
  for(int i=0;i<nentries;i++){

    if(i%1000==0)
      cout<<"i="<<i<<endl;    

    _jets_pt = 0;

    _jets_cl3d = 0;    
    _cl3d_clusters = 0;
    _cl_MIPpt = 0;
    _cl_HGClayer = 0;
    
    tree->GetEntry(i);

    for(unsigned int i_jet=0; i_jet<(*_jets_pt).size(); i_jet++){

      if((*_jets_pt)[i_jet]<pt_cut) continue;

      for(auto & i_c3d : (*_jets_cl3d)[i_jet]){

	vector<float> c3d_layer_MIPpt(53);
	float cl3d_MIPpt = 0;

	for(auto & i_c2d : (*_cl3d_clusters)[i_c3d]){      
	  c3d_layer_MIPpt[(*_cl_HGClayer)[i_c2d]] += (*_cl_MIPpt)[i_c2d];
	  cl3d_MIPpt += (*_cl_MIPpt)[i_c2d];
	}      
      
	for(unsigned int i=0; i<26; i++){
	  int i_layer = -1;
	  if(i<14) i_layer = 2*i+1;
	  else i_layer = i+15;
	
	  Ei[i]+=c3d_layer_MIPpt[i_layer]/cl3d_MIPpt;

	  for(unsigned int j=0; j<26; j++){
	    int j_layer = -1;
	    if(j<14) j_layer = 2*j+1;
	    else j_layer = j+15;
	  
	    pair<int,int> key=make_pair(i,j);
	    EiEj[key]+=c3d_layer_MIPpt[i_layer]*c3d_layer_MIPpt[j_layer]/pow(cl3d_MIPpt,2);
	  }
	  
	}
	
	nc3ds++;

      }

    }


  }
  

  cout<<"nc3ds="<<nc3ds<<endl;

  for(int i=0; i<26; i++)
    Ei[i]/=nc3ds;
  for (std::map<pair<int,int>,float>::iterator it=EiEj.begin(); it!=EiEj.end(); ++it)
    it->second/=nc3ds;


  pair<vector<float>,map<pair<int,int>,float> > Ei_EiEj = make_pair(Ei,EiEj);

  return Ei_EiEj;


}









vector<float> prod_weight_Fisher_clusters(TString filename_sig,TString filename_bkg){

  pair<vector<float>,map<pair<int,int>,float> > Ei_EiEj_sig = prod_Ei_Eij_VBF(filename_sig,20);
  pair<vector<float>,map<pair<int,int>,float> > Ei_EiEj_bkg = prod_Ei_Eij_ZB(filename_bkg,20);
  
  vector<float> Ei_sig = Ei_EiEj_sig.first;
  vector<float> Ei_bkg = Ei_EiEj_bkg.first;
  map<pair<int,int>,float> EiEj_sig = Ei_EiEj_sig.second;
  map<pair<int,int>,float> EiEj_bkg = Ei_EiEj_bkg.second;

  TMatrixD mu_sig(26,1);
  TMatrixD mu_bkg(26,1);
  TMatrixD sigma_sig(26,26);
  TMatrixD sigma_bkg(26,26);

  for(unsigned int i=0;i<26;i++){
    mu_sig(i,0) = Ei_sig[i];
    mu_bkg(i,0) = Ei_bkg[i];
    for(unsigned int j=0;j<26;j++){
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


  vector<float> w(26);
  out<<"{";
  for(unsigned int i=0;i<26;i++){
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
  vector<vector<unsigned int> >* _cl3d_clusters;
  vector<float>* _cl_MIPpt;
  vector<int>* _cl_HGClayer;

  tree->SetBranchAddress("VBF_parton_jets",        &_VBF_parton_jets);
  tree->SetBranchAddress("VBF_parton_genjet",      &_VBF_parton_genjet);
  
  tree->SetBranchAddress("genjet_pt",        &_genjet_pt);
  tree->SetBranchAddress("genjet_eta",       &_genjet_eta);

  tree->SetBranchAddress("jets_cl3d",        &_jets_cl3d);

  tree->SetBranchAddress("cl3d_clusters",       &_cl3d_clusters);
  tree->SetBranchAddress("cl_mipPt",            &_cl_MIPpt);
  tree->SetBranchAddress("cl_HGClayer",         &_cl_HGClayer);

  cout<<"n="<<nentries<<endl;


  for(int i=0;i<nentries;i++){

    if(i%1000==0)
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

    for(unsigned int i_VBF=0; i_VBF<(*_VBF_parton_jets).size(); i_VBF++){

      int i_gen = (*_VBF_parton_genjet)[i_VBF];
      int i_jet = (*_VBF_parton_jets)[i_VBF];

      if(i_jet<0 || i_gen<0) continue;
      if(abs((*_genjet_eta)[i_gen])<1.5 || abs((*_genjet_eta)[i_gen])>2.9 || (*_genjet_pt)[i_gen]<pt_cut) continue;

      for(auto & i_c3d : (*_jets_cl3d)[i_jet]){

	vector<float> cl3d_layer_MIPpt(53);
	float cl3d_MIPpt = 0;

	for(auto & i_c2d : (*_cl3d_clusters)[i_c3d]){      
	  cl3d_layer_MIPpt[(*_cl_HGClayer)[i_c2d]] += (*_cl_MIPpt)[i_c2d];
	  cl3d_MIPpt += (*_cl_MIPpt)[i_c2d];
	}
      
      
	float Fisher = 0;

	for(unsigned int i=0; i<26; i++){
	  int i_layer = -1;
	  if(i<14) i_layer = 2*i+1;
	  else i_layer = i+15;
	  
	  Fisher+=weights[i]*cl3d_layer_MIPpt[i_layer]/cl3d_MIPpt;

	}
    
	//cout<<"Fisher="<<Fisher<<endl;
	h->Fill(Fisher);

      }

    }


  }
  


  return h;


}







TH1F* TH1_Fisher_ZB(TString filename, float pt_cut, vector<float> weights){

  TH1F* g = new TH1F("g","g",1000,-10,10);

  TChain * tree = new TChain("HGCalTriggerNtupleJet");
  tree->Add(filename);
  int nentries = tree->GetEntries();

  vector<float>* _jets_pt;

  vector<vector<int> >* _jets_cl3d;
  vector<vector<unsigned int> >* _cl3d_clusters;
  vector<float>* _cl_MIPpt;
  vector<int>* _cl_HGClayer;

  
  tree->SetBranchAddress("jets_pt",        &_jets_pt);
  tree->SetBranchAddress("jets_cl3d",      &_jets_cl3d);

  tree->SetBranchAddress("cl3d_clusters",       &_cl3d_clusters);
  tree->SetBranchAddress("cl_mipPt",            &_cl_MIPpt);
  tree->SetBranchAddress("cl_HGClayer",         &_cl_HGClayer);

  cout<<"n="<<nentries<<endl;

  
  for(int i=0;i<nentries;i++){

    if(i%1000==0)
      cout<<"i="<<i<<endl;    

    _jets_pt = 0;

    _jets_cl3d = 0;    
    _cl3d_clusters = 0;
    _cl_MIPpt = 0;
    _cl_HGClayer = 0;
    
    tree->GetEntry(i);

    for(unsigned int i_jet=0; i_jet<(*_jets_pt).size(); i_jet++){

      if((*_jets_pt)[i_jet]<pt_cut) continue;

      for(auto & i_c3d : (*_jets_cl3d)[i_jet]){

	vector<float> cl3d_layer_MIPpt(53);
	float cl3d_MIPpt = 0;

	for(auto & i_c2d : (*_cl3d_clusters)[i_c3d]){      
	  cl3d_layer_MIPpt[(*_cl_HGClayer)[i_c2d]] += (*_cl_MIPpt)[i_c2d];
	  cl3d_MIPpt += (*_cl_MIPpt)[i_c2d];
	}      

	float Fisher=0;
	
	for(unsigned int i=0; i<26; i++){
	  int i_layer = -1;
	  if(i<14) i_layer = 2*i+1;
	  else i_layer = i+15;
	  
	  Fisher+=weights[i]*cl3d_layer_MIPpt[i_layer]/cl3d_MIPpt;
	  
	  
	}

	g->Fill(Fisher);
    
      }

    }


  }
  


  return g;


}




