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
#include "TLatex.h"


pair<vector<float>,map<pair<int,int>,float> > prod_Ei_Eij(TString filename){

  TChain * tree = new TChain("HGCalTriggerNtuple");
  tree->Add(filename);
  int nentries = tree->GetEntries();

  vector<float>* _gen_pt;
  vector<float>* _gen_eta;  
  vector<int>* _gen_cl3d;

  vector<vector<unsigned int> >* _cl3d_clusters_id;
  vector<float>* _cl_MIPpt;
  vector<int>* _cl_layer;
  vector<unsigned int>* _cl_id;
  
  tree->SetBranchAddress("gen_pt",     &_gen_pt);
  tree->SetBranchAddress("gen_eta",    &_gen_eta);
  tree->SetBranchAddress("gen_cl3d",    &_gen_cl3d);
  
  tree->SetBranchAddress("cl3d_clusters_id",     &_cl3d_clusters_id);
  tree->SetBranchAddress("cl_mipPt",     &_cl_MIPpt);
  tree->SetBranchAddress("cl_layer",     &_cl_layer);
  tree->SetBranchAddress("cl_id",     &_cl_id);

  cout<<"n="<<nentries<<endl;

  vector<float> Ei(38);
  map<pair<int,int>,float> EiEj;
  int nc3ds = 0;

  for(int i=0;i<nentries;i++){

    if(i%1000==0)
      cout<<"i="<<i<<endl;

    _gen_pt = 0;
    _gen_eta = 0;
    _gen_cl3d = 0;

    _cl3d_clusters_id = 0;
    _cl_MIPpt = 0;
    _cl_layer = 0;
    _cl_id = 0;

    tree->GetEntry(i);
    
    map<unsigned int, unsigned int> cl_map; //First ID, Second index
     
    for(unsigned int i_cl = 0; i_cl < (*_cl_id).size(); i_cl++)
      cl_map[(*_cl_id)[i_cl]] = i_cl;
    
    for(unsigned int i_gen=0; i_gen<(*_gen_pt).size(); i_gen++){

      int i_c3d = (*_gen_cl3d)[i_gen];

      if(i_c3d<0) continue;
      if(abs((*_gen_eta)[i_gen])<1.5 || abs((*_gen_eta)[i_gen])>2.9) continue;

      vector<float> cl3d_layer_MIPpt(53);

      for(auto & i_c2d : (*_cl3d_clusters_id)[i_c3d]){
	cl3d_layer_MIPpt[(*_cl_layer)[cl_map[i_c2d]]] += (*_cl_MIPpt)[cl_map[i_c2d]];
      }

      for(unsigned int i=0; i<38; i++){
	int i_layer = -1;
	if(i<14) i_layer = 2*i+1;
	else i_layer = i+15;
	  
	Ei[i]+=cl3d_layer_MIPpt[i_layer]*(*_gen_pt)[i_gen];
	  
	for(unsigned int j=0; j<38; j++){
	  int j_layer = -1;
	  if(j<14) j_layer = 2*j+1;
	  else j_layer = j+15;
	    
	  pair<int,int> key=make_pair(i,j);
	  EiEj[key]+=cl3d_layer_MIPpt[i_layer]*cl3d_layer_MIPpt[j_layer];

	}
	
      }
      
      nc3ds++;

   
    }


  }
  

  cout<<"nc3ds="<<nc3ds<<endl;

  for(int i=0; i<38; i++)
    Ei[i]/=nc3ds;
  for (std::map<pair<int,int>,float>::iterator it=EiEj.begin(); it!=EiEj.end(); ++it)
    it->second/=nc3ds;

  pair<vector<float>,map<pair<int,int>,float> > Ei_EiEj = make_pair(Ei,EiEj);
  
  return Ei_EiEj;


}










vector<float> prod_weight_calib_matrix_ele(TString filename){

  pair<vector<float>,map<pair<int,int>,float> > Ei_EiEj = prod_Ei_Eij(filename);
  
  vector<float> Ei = Ei_EiEj.first;
  map<pair<int,int>,float> EiEj = Ei_EiEj.second;


  TMatrixD V(14,1);
  TMatrixD M(14,14);

  for(unsigned int i=0;i<14;i++){
    V(i,0) = Ei[i];  
    for(unsigned int j=0;j<14;j++){
      pair<int,int> key = make_pair(i,j);
      M(i,j) = EiEj[key];
    }
  }

  cout<<"V"<<endl;
  V.Print();
  cout<<"M"<<endl;
  M.Print();

  M.Invert();
  TMatrixD weights = M*V;

  std::ofstream out("weights_calib.txt");

  vector<float> w(38);
  out<<"{";
  for(unsigned int i=0;i<38;i++){
    if(i<14){
      w[i] = weights(i,0);
      out<<w[i]<<",";
    }
    else if(i<38){
      w[i] = 0.;
      out<<"0.,";
    }
    else{
      w[i] = 0.;
      out<<"0.}"<<endl;
    }
  }
 


  return w;

}
				 







pair<vector<float>,map<pair<int,int>,float> > prod_Ei_Eij_pi_ele(TString filename, vector<float> weights_ele){

  TChain * tree = new TChain("HGCalTriggerNtuple");
  tree->Add(filename);
  int nentries = tree->GetEntries();

  vector<float>* _gen_pt;
  vector<float>* _gen_eta;  
  vector<int>* _gen_cl3d;

  vector<vector<unsigned int> >* _cl3d_clusters_id;
  vector<float>* _cl_MIPpt;
  vector<int>* _cl_layer;
  vector<unsigned int>* _cl_id;
  
  tree->SetBranchAddress("gen_pt",     &_gen_pt);
  tree->SetBranchAddress("gen_eta",    &_gen_eta);
  tree->SetBranchAddress("gen_cl3d",    &_gen_cl3d);
  
  tree->SetBranchAddress("cl3d_clusters_id",     &_cl3d_clusters_id);
  tree->SetBranchAddress("cl_mipPt",     &_cl_MIPpt);
  tree->SetBranchAddress("cl_layer",     &_cl_layer);
  tree->SetBranchAddress("cl_id",     &_cl_id);

  cout<<"n="<<nentries<<endl;

  vector<float> Ei(38);
  map<pair<int,int>,float> EiEj;
  int nc3ds = 0;

  for(int i=0;i<nentries;i++){

    if(i%1000==0)
      cout<<"i="<<i<<endl;

    _gen_pt = 0;
    _gen_eta = 0;
    _gen_cl3d = 0;

    _cl3d_clusters_id = 0;
    _cl_MIPpt = 0;
    _cl_layer = 0;
    _cl_id = 0;

    tree->GetEntry(i);
    
    map<unsigned int, unsigned int> cl_map; //First ID, Second index
     
    for(unsigned int i_cl = 0; i_cl < (*_cl_id).size(); i_cl++)
      cl_map[(*_cl_id)[i_cl]] = i_cl;
    
    for(unsigned int i_gen=0; i_gen<(*_gen_pt).size(); i_gen++){

      int i_c3d = (*_gen_cl3d)[i_gen];

      if(i_c3d<0) continue;
      if(abs((*_gen_eta)[i_gen])<1.5 || abs((*_gen_eta)[i_gen])>2.9) continue;

      vector<float> cl3d_layer_MIPpt(53);

      for(auto & i_c2d : (*_cl3d_clusters_id)[i_c3d]){
	cl3d_layer_MIPpt[(*_cl_layer)[cl_map[i_c2d]]] += (*_cl_MIPpt)[cl_map[i_c2d]];
      }

      float pT_cal_ele = 0;

      for(unsigned int i=0; i<38; i++){    
	  int i_layer = -1;
	  if(i<14) i_layer = 2*i+1;
	  else i_layer = i+15;	  
	  pT_cal_ele+=weights_ele[i]*cl3d_layer_MIPpt[i_layer];

      }


      for(unsigned int i=0; i<38; i++){
	int i_layer = -1;
	if(i<14) i_layer = 2*i+1;
	else i_layer = i+15;
	  
	Ei[i]+=cl3d_layer_MIPpt[i_layer]*((*_gen_pt)[i_gen]-pT_cal_ele);
	  
	for(unsigned int j=0; j<38; j++){
	  int j_layer = -1;
	  if(j<14) j_layer = 2*j+1;
	  else j_layer = j+15;
	    
	  pair<int,int> key=make_pair(i,j);
	  EiEj[key]+=cl3d_layer_MIPpt[i_layer]*cl3d_layer_MIPpt[j_layer];

	}
	
      }
      
      nc3ds++;

   
    }


  }
  

  cout<<"nc3ds="<<nc3ds<<endl;

  for(int i=0; i<38; i++)
    Ei[i]/=nc3ds;
  for (std::map<pair<int,int>,float>::iterator it=EiEj.begin(); it!=EiEj.end(); ++it)
    it->second/=nc3ds;

  pair<vector<float>,map<pair<int,int>,float> > Ei_EiEj = make_pair(Ei,EiEj);
  
  return Ei_EiEj;


}










vector<float> prod_weight_calib_matrix_pi_ele(TString filename,vector<float> weights_ele){

  pair<vector<float>,map<pair<int,int>,float> > Ei_EiEj = prod_Ei_Eij_pi_ele(filename,weights_ele);
  
  vector<float> Ei = Ei_EiEj.first;
  map<pair<int,int>,float> EiEj = Ei_EiEj.second;


  TMatrixD V(24,1);
  TMatrixD M(24,24);

  for(unsigned int i=14;i<38;i++){
    V(i-14,0) = Ei[i];  
    for(unsigned int j=14;j<38;j++){
      pair<int,int> key = make_pair(i,j);
      M(i-14,j-14) = EiEj[key];
    }
  }

  cout<<"V"<<endl;
  V.Print();
  cout<<"M"<<endl;
  M.Print();

  M.Invert();
  TMatrixD weights = M*V;

  std::ofstream out("weights_calib.txt");


  vector<float> w(38);
  out<<"{";
  for(unsigned int i=0;i<38;i++){
    if(i<14){
      w[i]=weights_ele[i];
      out<<w[i]<<",";
    }
    else if(i<37){
      w[i] = weights(i-14,0);
      out<<w[i]<<",";
    }
    else{
      w[i] = weights(i-14,0);
      out<<w[i]<<"}";
    } 
  }
 


  return w;

}
				 





vector<float> prod_weight_calib_matrix_pi(TString filename){

  pair<vector<float>,map<pair<int,int>,float> > Ei_EiEj = prod_Ei_Eij(filename);
  
  vector<float> Ei = Ei_EiEj.first;
  map<pair<int,int>,float> EiEj = Ei_EiEj.second;


  TMatrixD V(38,1);
  TMatrixD M(38,38);

  for(unsigned int i=0;i<38;i++){
    V(i,0) = Ei[i];  
    for(unsigned int j=0;j<38;j++){
      pair<int,int> key = make_pair(i,j);
      M(i,j) = EiEj[key];
    }
  }

  cout<<"V"<<endl;
  V.Print();
  cout<<"M"<<endl;
  M.Print();

  M.Invert();
  TMatrixD weights = M*V;

  std::ofstream out("weights_calib.txt");


  vector<float> w(38);
  out<<"{";
  for(unsigned int i=0;i<38;i++){
    w[i] = weights(i,0);
    if(i<27)
      out<<w[i]<<",";
    else
      out<<"0.}"<<endl;
  }
 


  return w;

}
				 








TH1F* TH1_C3D_calib_pt(TString filename, vector<float> weights){

  TH1F* h = new TH1F("h","h",100,0,50);


  TChain * tree = new TChain("HGCalTriggerNtuple");
  tree->Add(filename);
  int nentries = tree->GetEntries();

  vector<int>* _gen_cl3d;
  vector<float>* _gen_eta;

  vector<vector<unsigned int> >* _cl3d_clusters_id;
  vector<float>* _cl_MIPpt;
  vector<int>* _cl_layer;
  vector<unsigned int>* _cl_id;
  
  tree->SetBranchAddress("gen_eta",    &_gen_eta);
  tree->SetBranchAddress("gen_cl3d",    &_gen_cl3d);
  
  tree->SetBranchAddress("cl3d_clusters_id",     &_cl3d_clusters_id);
  tree->SetBranchAddress("cl_mipPt",     &_cl_MIPpt);
  tree->SetBranchAddress("cl_layer",     &_cl_layer);
  tree->SetBranchAddress("cl_id",     &_cl_id);

  cout<<"n="<<nentries<<endl;


  for(int i=0;i<nentries;i++){

    if(i%1000==0)
      cout<<"i="<<i<<endl;
     
    _gen_eta = 0;
    _gen_cl3d = 0;

    _cl3d_clusters_id = 0;
    _cl_MIPpt = 0;
    _cl_layer = 0;
    _cl_id = 0;
    
    tree->GetEntry(i);

    map<unsigned int, unsigned int> cl_map; //First ID, Second index
     
    for(unsigned int i_cl = 0; i_cl < (*_cl_id).size(); i_cl++)
      cl_map[(*_cl_id)[i_cl]] = i_cl;

    for(unsigned int i_gen=0; i_gen<(*_gen_eta).size(); i_gen++){
    
      int i_c3d = (*_gen_cl3d)[i_gen];

      if(i_c3d<0) continue;
      if(abs((*_gen_eta)[i_gen])<1.5 || abs((*_gen_eta)[i_gen])>2.9) continue;

      vector<float> cl3d_layer_MIPpt(53);
      
      for(auto & i_c2d : (*_cl3d_clusters_id)[i_c3d]){      
	cl3d_layer_MIPpt[(*_cl_layer)[cl_map[i_c2d]]] += (*_cl_MIPpt)[cl_map[i_c2d]];
      }
      
      float pT_cal = 0;

      for(unsigned int i=0; i<38; i++){    
	  int i_layer = -1;
	  if(i<14) i_layer = 2*i+1;
	  else i_layer = i+15;	  
	  pT_cal+=weights[i]*cl3d_layer_MIPpt[i_layer];

	}
         
	h->Fill(pT_cal);

    }
    
  }

  return h;


}




void plot_ele(){

  TString filename = "test_ele.root";
  
  TH1F* h_default = single_plot(filename,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]","gen_cl3d>=0",100,0.,50.);
  TH1F* h_ele = single_plot(filename,"HGCalTriggerNtuple","cl3d_pt_new_ele[gen_cl3d]","gen_cl3d>=0",100,0.,50.);
  TH1F* h_pi = single_plot(filename,"HGCalTriggerNtuple","cl3d_pt_new_pi[gen_cl3d]","gen_cl3d>=0",100,0.,50.);
  TH1F* h_pi_ele_EE = single_plot(filename,"HGCalTriggerNtuple","cl3d_pt_new_ele_EE_pi_FHBH[gen_cl3d]","gen_cl3d>=0",100,0.,50.);
  TH1F* h_ele_cl_max = single_plot(filename,"HGCalTriggerNtuple","cl3d_max_pt_ele[gen_cl3d_max]","gen_cl3d_max>=0",100,0.,50.);
  TH1F* h_pi_cl_max = single_plot(filename,"HGCalTriggerNtuple","cl3d_max_pt_pi[gen_cl3d_max]","gen_cl3d_max>=0",100,0.,50.);


  vector<TH1F*> histo;
  histo.push_back(h_default);
  histo.push_back(h_ele);
  histo.push_back(h_pi);
  histo.push_back(h_pi_ele_EE);
  histo.push_back(h_ele_cl_max);
  histo.push_back(h_pi_cl_max);

  vector<TString> leg_entry;
  leg_entry.push_back("Default calibr.");
  leg_entry.push_back("New ele calibr.");
  leg_entry.push_back("New #pi calibr.");
  leg_entry.push_back("New ele EE + #pi FH-BH calibr.");
  leg_entry.push_back("Full clust. ele calibr.");
  leg_entry.push_back("Full clust. #pi calibr.");


  TLegend* leg=new TLegend(0.3,0.65,0.5,0.85);
  leg->SetHeader("Electron gun p_{T}=25 GeV PU=0");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  
 for(unsigned int i=0;i<histo.size();i++){
    TH1F* h = histo[i];
    h->Scale(1/h->Integral());
    h->SetLineWidth(2);
    h->SetLineColor(i+1);
    if(i>3)
      h->SetLineColor(i+2);      
    leg->AddEntry(h,leg_entry[i]);
  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  //c->SetLogy();

  //histo = sort_histo(histo);

  histo[0]->GetXaxis()->SetTitle("p_{T}(C3D) [GeV]");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,2*histo[0]->GetMaximum());
  //histo[0]->SetMaximum(2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(-0.99,1.02*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV, PU=0");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/C3D_ele_recalibr.pdf");  




}






void plot_pi(){

  TString filename = "test_pi.root";
  
  
  TH1F* h_default = single_plot(filename,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]","gen_cl3d>=0",100,0.,50.);
  TH1F* h_pi = single_plot(filename,"HGCalTriggerNtuple","cl3d_pt_new_pi[gen_cl3d]","gen_cl3d>=0",100,0.,50.);
  TH1F* h_pi_ele_EE = single_plot(filename,"HGCalTriggerNtuple","cl3d_pt_new_ele_EE_pi_FHBH[gen_cl3d]","gen_cl3d>=0",100,0.,50.);
  TH1F* h_pi_cl_max = single_plot(filename,"HGCalTriggerNtuple","cl3d_max_pt_pi[gen_cl3d_max]","gen_cl3d_max>=0",100,0.,50.);

  //TH1F* h_ele = TH1_C3D_calib_pt(filename,w_ele);
  //TH1F* h_pi = TH1_C3D_calib_pt(filename,w_pi);
  //TH1F* h_pi_ele = TH1_C3D_calib_pt(filename,w_pi_ele);
  //TH1F* h_pi_ele_EE = TH1_C3D_calib_pt(filename,w_pi_ele_EE);

  vector<TH1F*> histo;
  histo.push_back(h_default);
  //histo.push_back(h_ele);
  histo.push_back(h_pi);
  histo.push_back(h_pi_ele_EE);
  //histo.push_back(h_ele_cl_max);
  histo.push_back(h_pi_cl_max);

  vector<TString> leg_entry;
  leg_entry.push_back("Default calibr.");
  //leg_entry.push_back("New ele calibr.");
  leg_entry.push_back("New #pi calibr.");
  leg_entry.push_back("New ele EE + #pi FH-BH calibr.");
  //leg_entry.push_back("Full clust. ele calibr.");
  leg_entry.push_back("Full clust. #pi calibr.");


  TLegend* leg=new TLegend(0.3,0.65,0.5,0.85);
  leg->SetHeader("Pion gun p_{T}=25 GeV PU=0");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  
 for(unsigned int i=0;i<histo.size();i++){
    TH1F* h = histo[i];
    h->Scale(1/h->Integral());
    h->SetLineWidth(2);
    h->SetLineColor(i+1);
    if(i>3)
      h->SetLineColor(i+2);      
    leg->AddEntry(h,leg_entry[i]);
  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  //c->SetLogy();

  histo = sort_histo(histo);

  histo[0]->GetXaxis()->SetTitle("p_{T}(C3D) [GeV]");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,2*histo[0]->GetMaximum());
  //histo[0]->SetMaximum(2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(-0.99,1.02*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV, PU=0");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/C3D_pi_recalibr.pdf");  




}








pair<vector<float>,map<pair<int,int>,float> > prod_Ei_Eij_cl_max(TString filename){

  TChain * tree = new TChain("HGCalTriggerNtuple");
  tree->Add(filename);
  int nentries = tree->GetEntries();

  vector<float>* _gen_pt;
  vector<float>* _gen_eta;  

  vector<float>* _cl_max_MIPpt;
  vector<int>* _cl_max_layer;
  vector<float>* _cl_max_eta;
  
  tree->SetBranchAddress("gen_pt",     &_gen_pt);
  tree->SetBranchAddress("gen_eta",    &_gen_eta);
  
  tree->SetBranchAddress("cl_max_mipPt",     &_cl_max_MIPpt);
  tree->SetBranchAddress("cl_max_layer",     &_cl_max_layer);
  tree->SetBranchAddress("cl_max_eta",     &_cl_max_eta);

  cout<<"n="<<nentries<<endl;

  vector<float> Ei(38);
  map<pair<int,int>,float> EiEj;
  int nc3ds = 0;

  for(int i=0;i<nentries;i++){

    if(i%1000==0)
      cout<<"i="<<i<<endl;

    _gen_pt = 0;
    _gen_eta = 0;

    _cl_max_MIPpt = 0;
    _cl_max_layer = 0;
    _cl_max_eta = 0;

    tree->GetEntry(i);
    
    for(unsigned int i_gen=0; i_gen<(*_gen_pt).size(); i_gen++){
     
      if(abs((*_gen_eta)[i_gen])<1.5 || abs((*_gen_eta)[i_gen])>2.9) continue;

      vector<float> cl3d_layer_MIPpt(53);

      for(unsigned int i_cl_max = 0; i_cl_max<(*_cl_max_MIPpt).size(); i_cl_max++){
	if((*_cl_max_eta)[i_cl_max]*(*_gen_eta)[i_gen]<0) continue;
	cl3d_layer_MIPpt[(*_cl_max_layer)[i_cl_max]] += (*_cl_max_MIPpt)[i_cl_max];
      }	


      for(unsigned int i=0; i<38; i++){
	int i_layer = -1;
	if(i<14) i_layer = 2*i+1;
	else i_layer = i+15;
	  
	Ei[i]+=cl3d_layer_MIPpt[i_layer]*(*_gen_pt)[i_gen];
	  
	for(unsigned int j=0; j<38; j++){
	  int j_layer = -1;
	  if(j<14) j_layer = 2*j+1;
	  else j_layer = j+15;
	    
	  pair<int,int> key=make_pair(i,j);
	  EiEj[key]+=cl3d_layer_MIPpt[i_layer]*cl3d_layer_MIPpt[j_layer];

	}
	
      }
      
      nc3ds++;

   
    }


  }
  

  cout<<"nc3ds="<<nc3ds<<endl;

  for(int i=0; i<38; i++)
    Ei[i]/=nc3ds;
  for (std::map<pair<int,int>,float>::iterator it=EiEj.begin(); it!=EiEj.end(); ++it)
    it->second/=nc3ds;

  pair<vector<float>,map<pair<int,int>,float> > Ei_EiEj = make_pair(Ei,EiEj);
  
  return Ei_EiEj;


}










vector<float> prod_weight_calib_matrix_cl_max_ele(TString filename){

  pair<vector<float>,map<pair<int,int>,float> > Ei_EiEj = prod_Ei_Eij_cl_max(filename);
  
  vector<float> Ei = Ei_EiEj.first;
  map<pair<int,int>,float> EiEj = Ei_EiEj.second;


  TMatrixD V(14,1);
  TMatrixD M(14,14);

  for(unsigned int i=0;i<14;i++){
    V(i,0) = Ei[i];  
    for(unsigned int j=0;j<14;j++){
      pair<int,int> key = make_pair(i,j);
      M(i,j) = EiEj[key];
    }
  }

  cout<<"V"<<endl;
  V.Print();
  cout<<"M"<<endl;
  M.Print();

  M.Invert();
  TMatrixD weights = M*V;

  std::ofstream out("weights_calib.txt");

  vector<float> w(38);
  out<<"{";
  for(unsigned int i=0;i<38;i++){
    if(i<14){
      w[i] = weights(i,0);
      out<<w[i]<<",";
    }
    else if(i<38){
      w[i] = 0.;
      out<<"0.,";
    }
    else{
      w[i] = 0.;
      out<<"0.}"<<endl;
    }
  }
 


  return w;

}
				 













vector<float> prod_weight_calib_matrix_cl_max_pi(TString filename){

  pair<vector<float>,map<pair<int,int>,float> > Ei_EiEj = prod_Ei_Eij_cl_max(filename);
  
  vector<float> Ei = Ei_EiEj.first;
  map<pair<int,int>,float> EiEj = Ei_EiEj.second;


  TMatrixD V(38,1);
  TMatrixD M(38,38);

  for(unsigned int i=0;i<38;i++){
    V(i,0) = Ei[i];  
    for(unsigned int j=0;j<38;j++){
      pair<int,int> key = make_pair(i,j);
      M(i,j) = EiEj[key];
    }
  }

  cout<<"V"<<endl;
  V.Print();
  cout<<"M"<<endl;
  M.Print();

  M.Invert();
  TMatrixD weights = M*V;

  std::ofstream out("weights_calib.txt");


  vector<float> w(38);
  out<<"{";
  for(unsigned int i=0;i<38;i++){
    w[i] = weights(i,0);
    if(i<27)
      out<<w[i]<<",";
    else
      out<<"0.}"<<endl;
  }
 


  return w;

}
				 










void plot_ele2(){

  TString filename = "test_ele.root";
  
  TH1F* h_default = single_plot(filename,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]","gen_cl3d>=0",100,0.,50.);
  TH1F* h_ele = single_plot(filename,"HGCalTriggerNtuple","cl3d_pt_new_ele[gen_cl3d]","gen_cl3d>=0",100,0.,50.);
  TH1F* h_ele_cl_max = single_plot(filename,"HGCalTriggerNtuple","cl3d_max_pt_ele[gen_cl3d_max]","gen_cl3d_max>=0",100,0.,50.);
  TH1F* h_ele_cl2_max = single_plot(filename,"HGCalTriggerNtuple","cl3d_max_cl2_pt_ele[gen_cl3d_max]","gen_cl3d_max>=0",100,0.,50.);
  TH1F* h_ele_EE_max = single_plot(filename,"HGCalTriggerNtuple","cl3d_EE_max_pt_ele[gen_cl3d]","gen_cl3d>=0",100,0.,50.);
  TH1F* h_ele_EH_max = single_plot(filename,"HGCalTriggerNtuple","cl3d_EH_max_pt_ele[gen_cl3d]","gen_cl3d>=0",100,0.,50.);
  

  vector<TH1F*> histo;
  histo.push_back(h_default);
  histo.push_back(h_ele);
  histo.push_back(h_ele_cl_max);
  histo.push_back(h_ele_cl2_max);
  histo.push_back(h_ele_EE_max);  
  histo.push_back(h_ele_EH_max);

  vector<TString> leg_entry;
  leg_entry.push_back("Default calibr.");
  leg_entry.push_back("New ele calibr.");
  leg_entry.push_back("Full TC clust. ele calibr.");
  leg_entry.push_back("Full C2D clust. ele calibr.");
  leg_entry.push_back("Full C2D EH clust. ele calibr.");
  leg_entry.push_back("Full C2D EE clust. ele calibr.");

  TLegend* leg=new TLegend(0.2,0.65,0.5,0.85);
  leg->SetHeader("Electron gun p_{T}=25 GeV PU=0");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  
 for(unsigned int i=0;i<histo.size();i++){
    TH1F* h = histo[i];
    h->Scale(1/h->Integral());
    h->SetLineWidth(2);
    h->SetLineColor(i+1);
    if(i>3)
      h->SetLineColor(i+2);      
    leg->AddEntry(h,leg_entry[i]);
  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  //c->SetLogy();

  //histo = sort_histo(histo);

  histo[0]->GetXaxis()->SetTitle("p_{T}(C3D) [GeV]");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,2.5*histo[0]->GetMaximum());
  //histo[0]->SetMaximum(2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(-0.99,1.02*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV, PU=0");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/C3D_ele_recalibr2.pdf");  




}







void plot_ele2_rescaled(){

  TString filename = "test_ele.root";
  
  TH1F* h_default0 = single_plot(filename,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]","gen_cl3d>=0",100,0.,50.);
  TH1F* h_ele0 = single_plot(filename,"HGCalTriggerNtuple","cl3d_pt_new_ele[gen_cl3d]","gen_cl3d>=0",100,0.,50.);
  TH1F* h_ele_cl_max0 = single_plot(filename,"HGCalTriggerNtuple","cl3d_max_pt_ele[gen_cl3d_max]","gen_cl3d_max>=0",100,0.,50.);
  TH1F* h_ele_cl2_max0 = single_plot(filename,"HGCalTriggerNtuple","cl3d_max_cl2_pt_ele[gen_cl3d_max]","gen_cl3d_max>=0",100,0.,50.);
  TH1F* h_ele_EE_max0 = single_plot(filename,"HGCalTriggerNtuple","cl3d_EE_max_pt_ele[gen_cl3d]","gen_cl3d>=0",100,0.,50.);
  TH1F* h_ele_EH_max0 = single_plot(filename,"HGCalTriggerNtuple","cl3d_EH_max_pt_ele[gen_cl3d]","gen_cl3d>=0",100,0.,50.);


  TH1F* h_default = single_plot(filename,"HGCalTriggerNtuple",Form("%f*cl3d_pt[gen_cl3d]",25./h_default0->GetMean()),"gen_cl3d>=0",100,0.,50.);
  TH1F* h_ele = single_plot(filename,"HGCalTriggerNtuple",Form("%f*cl3d_pt_new_ele[gen_cl3d]",25./h_ele0->GetMean()),"gen_cl3d>=0",100,0.,50.);
  TH1F* h_ele_cl_max = single_plot(filename,"HGCalTriggerNtuple",Form("%f*cl3d_max_pt_ele[gen_cl3d_max]",25./h_ele_cl_max0->GetMean()),"gen_cl3d_max>=0",100,0.,50.);
  TH1F* h_ele_cl2_max = single_plot(filename,"HGCalTriggerNtuple",Form("%f*cl3d_max_cl2_pt_ele[gen_cl3d_max]",25./h_ele_cl2_max0->GetMean()),"gen_cl3d_max>=0",100,0.,50.);
  TH1F* h_ele_EE_max = single_plot(filename,"HGCalTriggerNtuple",Form("%f*cl3d_EE_max_pt_ele[gen_cl3d]",25./h_ele_EE_max0->GetMean()),"gen_cl3d>=0",100,0.,50.);
  TH1F* h_ele_EH_max = single_plot(filename,"HGCalTriggerNtuple",Form("%f*cl3d_EH_max_pt_ele[gen_cl3d]",25./h_ele_EE_max0->GetMean()),"gen_cl3d>=0",100,0.,50.);
  

  vector<TH1F*> histo;
  histo.push_back(h_default);
  histo.push_back(h_ele);
  histo.push_back(h_ele_cl_max);
  histo.push_back(h_ele_cl2_max);
  histo.push_back(h_ele_EE_max);  
  histo.push_back(h_ele_EH_max);

  vector<TString> leg_entry;
  leg_entry.push_back("Default calibr.");
  leg_entry.push_back("New ele calibr.");
  leg_entry.push_back("Full TC clust. ele calibr.");
  leg_entry.push_back("Full C2D clust. ele calibr.");
  leg_entry.push_back("Full C2D EH clust. ele calibr.");
  leg_entry.push_back("Full C2D EE clust. ele calibr.");

  TLegend* leg=new TLegend(0.2,0.65,0.5,0.85);
  leg->SetHeader("Electron gun p_{T}=25 GeV PU=0");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  
 for(unsigned int i=0;i<histo.size();i++){
    TH1F* h = histo[i];
    h->Scale(1/h->Integral());
    h->SetLineWidth(2);
    h->SetLineColor(i+1);
    if(i>3)
      h->SetLineColor(i+2);      
    leg->AddEntry(h,leg_entry[i]);
  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  //c->SetLogy();

  //histo = sort_histo(histo);

  histo[0]->GetXaxis()->SetTitle("p_{T}(C3D) [GeV]");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,3*histo[0]->GetMaximum());
  //histo[0]->SetMaximum(2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(-0.99,1.02*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV, PU=0");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/C3D_ele_recalibr2_rescaled.pdf");  




}








void plot_pi2(){

  TString filename = "test_pi.root";
  
  
  TH1F* h_default = single_plot(filename,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]","gen_cl3d>=0",100,0.,50.);
  TH1F* h_pi = single_plot(filename,"HGCalTriggerNtuple","cl3d_pt_new_pi[gen_cl3d]","gen_cl3d>=0",100,0.,50.);
  //TH1F* h_pi_ele_EE = single_plot(filename,"HGCalTriggerNtuple","cl3d_pt_new_ele_EE_pi_FHBH[gen_cl3d]","gen_cl3d>=0",100,0.,50.);
  TH1F* h_pi_cl_max = single_plot(filename,"HGCalTriggerNtuple","cl3d_max_pt_pi[gen_cl3d_max]","gen_cl3d_max>=0",100,0.,50.);
  TH1F* h_pi_cl2_max = single_plot(filename,"HGCalTriggerNtuple","cl3d_max_cl2_pt_pi[gen_cl3d_max]","gen_cl3d_max>=0 && abs(gen_eta)>1.5 && abs(gen_eta)<2.9",100,0.,50.);
  TH1F* h_pi_EE_max = single_plot(filename,"HGCalTriggerNtuple","cl3d_EE_max_pt_pi[gen_cl3d]","gen_cl3d>=0",100,0.,50.);
  TH1F* h_pi_EH_max = single_plot(filename,"HGCalTriggerNtuple","cl3d_EH_max_pt_pi[gen_cl3d]","gen_cl3d>=0",100,0.,50.);

  vector<TH1F*> histo;
  histo.push_back(h_default);
  histo.push_back(h_pi);
  //histo.push_back(h_pi_ele_EE);
  histo.push_back(h_pi_cl_max);
  histo.push_back(h_pi_cl2_max);
  histo.push_back(h_pi_EE_max);
  histo.push_back(h_pi_EH_max);

  vector<TString> leg_entry;
  leg_entry.push_back("Default calibr.");
  leg_entry.push_back("New #pi calibr.");
  //leg_entry.push_back("New ele EE + #pi FH-BH calibr.");
  leg_entry.push_back("Full TC clust. #pi calibr.");
  leg_entry.push_back("Full C2D clust. #pi calibr.");
  leg_entry.push_back("Full C2D EH clust. #pi calibr.");
  leg_entry.push_back("Full C2D EE clust. #pi calibr.");

  TLegend* leg=new TLegend(0.3,0.65,0.5,0.85);
  leg->SetHeader("Pion gun p_{T}=25 GeV PU=0");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  
 for(unsigned int i=0;i<histo.size();i++){
    TH1F* h = histo[i];
    h->Scale(1/h->Integral());
    h->SetLineWidth(2);
    h->SetLineColor(i+1);
    if(i>3)
      h->SetLineColor(i+2);      
    leg->AddEntry(h,leg_entry[i]);
  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  //c->SetLogy();

  histo = sort_histo(histo);

  histo[0]->GetXaxis()->SetTitle("p_{T}(C3D) [GeV]");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,2*histo[0]->GetMaximum());
  //histo[0]->SetMaximum(2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(-0.99,1.02*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV, PU=0");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/C3D_pi_recalibr2.pdf");  




}









void plot_pi2_rescaled(){

  TString filename = "test_pi.root";
  
  
  TH1F* h_default0 = single_plot(filename,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]","gen_cl3d>=0",100,0.,50.);
  TH1F* h_pi0 = single_plot(filename,"HGCalTriggerNtuple","cl3d_pt_new_pi[gen_cl3d]","gen_cl3d>=0",100,0.,50.);
  //TH1F* h_pi_ele_EE0 = single_plot(filename,"HGCalTriggerNtuple","cl3d_pt_new_ele_EE_pi_FHBH[gen_cl3d]","gen_cl3d>=0",100,0.,50.);
  TH1F* h_pi_cl_max0 = single_plot(filename,"HGCalTriggerNtuple","cl3d_max_pt_pi[gen_cl3d_max]","gen_cl3d_max>=0",100,0.,50.);
  TH1F* h_pi_cl2_max0 = single_plot(filename,"HGCalTriggerNtuple","cl3d_max_cl2_pt_pi[gen_cl3d_max]","gen_cl3d_max>=0 && abs(gen_eta)>1.5 && abs(gen_eta)<2.9",100,0.,50.);
  TH1F* h_pi_EE_max0 = single_plot(filename,"HGCalTriggerNtuple","cl3d_EE_max_pt_pi[gen_cl3d]","gen_cl3d>=0",100,0.,50.);
  TH1F* h_pi_EH_max0 = single_plot(filename,"HGCalTriggerNtuple","cl3d_EH_max_pt_pi[gen_cl3d]","gen_cl3d>=0",100,0.,50.);

  TH1F* h_default = single_plot(filename,"HGCalTriggerNtuple",Form("%f*cl3d_pt[gen_cl3d]",25./ h_default0->GetMean()),"gen_cl3d>=0",100,0.,50.);
  TH1F* h_pi = single_plot(filename,"HGCalTriggerNtuple",Form("%f*cl3d_pt_new_pi[gen_cl3d]",25./h_pi0->GetMean()),"gen_cl3d>=0",100,0.,50.);
  //TH1F* h_pi_ele_EE = single_plot(filename,"HGCalTriggerNtuple",Form("%f*cl3d_pt_new_ele_EE_pi_FHBH[gen_cl3d]",25./h_pi_ele_EE0->GetMean()),"gen_cl3d>=0",100,0.,50.);
  TH1F* h_pi_cl_max = single_plot(filename,"HGCalTriggerNtuple",Form("%f*cl3d_max_pt_pi[gen_cl3d_max]",25./h_pi_cl_max0->GetMean()),"gen_cl3d_max>=0",100,0.,50.);
  TH1F* h_pi_cl2_max = single_plot(filename,"HGCalTriggerNtuple",Form("%f*cl3d_max_cl2_pt_pi[gen_cl3d_max]",25./h_pi_cl2_max0->GetMean()),"gen_cl3d_max>=0 && abs(gen_eta)>1.5 && abs(gen_eta)<2.9",100,0.,50.);
  TH1F* h_pi_EE_max = single_plot(filename,"HGCalTriggerNtuple",Form("%f*cl3d_EE_max_pt_pi[gen_cl3d]",25./h_pi_EE_max0->GetMean()),"gen_cl3d>=0",100,0.,50.);
  TH1F* h_pi_EH_max = single_plot(filename,"HGCalTriggerNtuple",Form("%f*cl3d_EH_max_pt_pi[gen_cl3d]",25./h_pi_EH_max0->GetMean()),"gen_cl3d>=0",100,0.,50.);


  vector<TH1F*> histo;
  histo.push_back(h_default);
  histo.push_back(h_pi);
  //histo.push_back(h_pi_ele_EE);
  histo.push_back(h_pi_cl_max);
  histo.push_back(h_pi_cl2_max);
  histo.push_back(h_pi_EE_max);
  histo.push_back(h_pi_EH_max);

  vector<TString> leg_entry;
  leg_entry.push_back("Default calibr.");
  leg_entry.push_back("New #pi calibr.");
  //leg_entry.push_back("New ele EE + #pi FH-BH calibr.");
  leg_entry.push_back("Full TC clust. #pi calibr.");
  leg_entry.push_back("Full C2D clust. #pi calibr.");
  leg_entry.push_back("Full C2D EH clust. #pi calibr.");
  leg_entry.push_back("Full C2D EE clust. #pi calibr.");

  TLegend* leg=new TLegend(0.3,0.65,0.5,0.85);
  leg->SetHeader("Pion gun p_{T}=25 GeV PU=0");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  
 for(unsigned int i=0;i<histo.size();i++){
    TH1F* h = histo[i];
    h->Scale(1/h->Integral());
    h->SetLineWidth(2);
    h->SetLineColor(i+1);
    if(i>3)
      h->SetLineColor(i+2);      
    leg->AddEntry(h,leg_entry[i]);
  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  //c->SetLogy();

  histo = sort_histo(histo);

  histo[0]->GetXaxis()->SetTitle("p_{T}(C3D) [GeV]");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,2*histo[0]->GetMaximum());
  //histo[0]->SetMaximum(2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(-0.99,1.02*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV, PU=0");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/C3D_pi_recalibr2_rescaled.pdf");  




}








pair<vector<float>,map<pair<int,int>,float> > prod_Ei_Eij_max_EE(TString filename){

  TChain * tree = new TChain("HGCalTriggerNtuple");
  tree->Add(filename);
  int nentries = tree->GetEntries();

  vector<float>* _gen_pt;
  vector<float>* _gen_eta;  
  vector<int>* _gen_cl3d;

  vector<vector<unsigned int> >* _cl3d_clusters_id;
  vector<float>* _cl_MIPpt;
  vector<int>* _cl_layer;
  vector<unsigned int>* _cl_id;
  
  tree->SetBranchAddress("gen_pt",     &_gen_pt);
  tree->SetBranchAddress("gen_eta",    &_gen_eta);
  tree->SetBranchAddress("gen_cl3d",    &_gen_cl3d);
  
  tree->SetBranchAddress("cl3d_EE_max_clusters_id",     &_cl3d_clusters_id);
  tree->SetBranchAddress("cl_EE_max_mipPt",     &_cl_MIPpt);
  tree->SetBranchAddress("cl_EE_max_layer",     &_cl_layer);

  cout<<"n="<<nentries<<endl;

  vector<float> Ei(38);
  map<pair<int,int>,float> EiEj;
  int nc3ds = 0;

  for(int i=0;i<nentries;i++){

    if(i%1000==0)
      cout<<"i="<<i<<endl;

    _gen_pt = 0;
    _gen_eta = 0;
    _gen_cl3d = 0;

    _cl3d_clusters_id = 0;
    _cl_MIPpt = 0;
    _cl_layer = 0;

    tree->GetEntry(i);

    
    for(unsigned int i_gen=0; i_gen<(*_gen_pt).size(); i_gen++){

      int i_c3d = (*_gen_cl3d)[i_gen];

      if(i_c3d<0) continue;
      if(abs((*_gen_eta)[i_gen])<1.5 || abs((*_gen_eta)[i_gen])>2.9) continue;

      vector<float> cl3d_layer_MIPpt(53);

      for(auto & i_c2d : (*_cl3d_clusters_id)[i_c3d]){
	cl3d_layer_MIPpt[(*_cl_layer)[i_c2d]] += (*_cl_MIPpt)[i_c2d];
      }

      for(unsigned int i=0; i<38; i++){
	int i_layer = -1;
	if(i<14) i_layer = 2*i+1;
	else i_layer = i+15;
	  
	Ei[i]+=cl3d_layer_MIPpt[i_layer]*(*_gen_pt)[i_gen];
	  
	for(unsigned int j=0; j<38; j++){
	  int j_layer = -1;
	  if(j<14) j_layer = 2*j+1;
	  else j_layer = j+15;
	    
	  pair<int,int> key=make_pair(i,j);
	  EiEj[key]+=cl3d_layer_MIPpt[i_layer]*cl3d_layer_MIPpt[j_layer];

	}
	
      }
      
      nc3ds++;

   
    }


  }
  

  cout<<"nc3ds="<<nc3ds<<endl;

  for(int i=0; i<38; i++)
    Ei[i]/=nc3ds;
  for (std::map<pair<int,int>,float>::iterator it=EiEj.begin(); it!=EiEj.end(); ++it)
    it->second/=nc3ds;

  pair<vector<float>,map<pair<int,int>,float> > Ei_EiEj = make_pair(Ei,EiEj);
  
  return Ei_EiEj;


}










vector<float> prod_weight_calib_matrix_ele_max_EE(TString filename){

  pair<vector<float>,map<pair<int,int>,float> > Ei_EiEj = prod_Ei_Eij_max_EE(filename);
  
  vector<float> Ei = Ei_EiEj.first;
  map<pair<int,int>,float> EiEj = Ei_EiEj.second;


  TMatrixD V(14,1);
  TMatrixD M(14,14);

  for(unsigned int i=0;i<14;i++){
    V(i,0) = Ei[i];  
    for(unsigned int j=0;j<14;j++){
      pair<int,int> key = make_pair(i,j);
      M(i,j) = EiEj[key];
    }
  }

  cout<<"V"<<endl;
  V.Print();
  cout<<"M"<<endl;
  M.Print();

  M.Invert();
  TMatrixD weights = M*V;

  std::ofstream out("weights_calib.txt");

  vector<float> w(38);
  out<<"{";
  for(unsigned int i=0;i<38;i++){
    if(i<14){
      w[i] = weights(i,0);
      out<<w[i]<<",";
    }
    else if(i<38){
      w[i] = 0.;
      out<<"0.,";
    }
    else{
      w[i] = 0.;
      out<<"0.}"<<endl;
    }
  }
 


  return w;

}
				 





vector<float> prod_weight_calib_matrix_pi_max_EE(TString filename){

  pair<vector<float>,map<pair<int,int>,float> > Ei_EiEj = prod_Ei_Eij_max_EE(filename);
  
  vector<float> Ei = Ei_EiEj.first;
  map<pair<int,int>,float> EiEj = Ei_EiEj.second;


  TMatrixD V(38,1);
  TMatrixD M(38,38);

  for(unsigned int i=0;i<38;i++){
    V(i,0) = Ei[i];  
    for(unsigned int j=0;j<38;j++){
      pair<int,int> key = make_pair(i,j);
      M(i,j) = EiEj[key];
    }
  }

  cout<<"V"<<endl;
  V.Print();
  cout<<"M"<<endl;
  M.Print();

  M.Invert();
  TMatrixD weights = M*V;

  std::ofstream out("weights_calib.txt");


  vector<float> w(38);
  out<<"{";
  for(unsigned int i=0;i<38;i++){
    w[i] = weights(i,0);
    if(i<27)
      out<<w[i]<<",";
    else
      out<<"0.}"<<endl;
  }
 


  return w;

}
				 







pair<vector<float>,map<pair<int,int>,float> > prod_Ei_Eij_max_EH(TString filename){

  TChain * tree = new TChain("HGCalTriggerNtuple");
  tree->Add(filename);
  int nentries = tree->GetEntries();

  vector<float>* _gen_pt;
  vector<float>* _gen_eta;  
  vector<int>* _gen_cl3d;

  vector<vector<unsigned int> >* _cl3d_clusters_id;
  vector<float>* _cl_MIPpt;
  vector<int>* _cl_layer;
  vector<unsigned int>* _cl_id;
  
  tree->SetBranchAddress("gen_pt",     &_gen_pt);
  tree->SetBranchAddress("gen_eta",    &_gen_eta);
  tree->SetBranchAddress("gen_cl3d",    &_gen_cl3d);
  
  tree->SetBranchAddress("cl3d_EH_max_clusters_id",     &_cl3d_clusters_id);
  tree->SetBranchAddress("cl_EH_max_mipPt",     &_cl_MIPpt);
  tree->SetBranchAddress("cl_EH_max_layer",     &_cl_layer);

  cout<<"n="<<nentries<<endl;

  vector<float> Ei(38);
  map<pair<int,int>,float> EiEj;
  int nc3ds = 0;

  for(int i=0;i<nentries;i++){

    if(i%1000==0)
      cout<<"i="<<i<<endl;

    _gen_pt = 0;
    _gen_eta = 0;
    _gen_cl3d = 0;

    _cl3d_clusters_id = 0;
    _cl_MIPpt = 0;
    _cl_layer = 0;

    tree->GetEntry(i);

    
    for(unsigned int i_gen=0; i_gen<(*_gen_pt).size(); i_gen++){

      int i_c3d = (*_gen_cl3d)[i_gen];

      if(i_c3d<0) continue;
      if(abs((*_gen_eta)[i_gen])<1.5 || abs((*_gen_eta)[i_gen])>2.9) continue;

      vector<float> cl3d_layer_MIPpt(53);

      for(auto & i_c2d : (*_cl3d_clusters_id)[i_c3d]){
	cl3d_layer_MIPpt[(*_cl_layer)[i_c2d]] += (*_cl_MIPpt)[i_c2d];
      }

      for(unsigned int i=0; i<38; i++){
	int i_layer = -1;
	if(i<14) i_layer = 2*i+1;
	else i_layer = i+15;
	  
	Ei[i]+=cl3d_layer_MIPpt[i_layer]*(*_gen_pt)[i_gen];
	  
	for(unsigned int j=0; j<38; j++){
	  int j_layer = -1;
	  if(j<14) j_layer = 2*j+1;
	  else j_layer = j+15;
	    
	  pair<int,int> key=make_pair(i,j);
	  EiEj[key]+=cl3d_layer_MIPpt[i_layer]*cl3d_layer_MIPpt[j_layer];

	}
	
      }
      
      nc3ds++;

   
    }


  }
  

  cout<<"nc3ds="<<nc3ds<<endl;

  for(int i=0; i<38; i++)
    Ei[i]/=nc3ds;
  for (std::map<pair<int,int>,float>::iterator it=EiEj.begin(); it!=EiEj.end(); ++it)
    it->second/=nc3ds;

  pair<vector<float>,map<pair<int,int>,float> > Ei_EiEj = make_pair(Ei,EiEj);
  
  return Ei_EiEj;


}










vector<float> prod_weight_calib_matrix_ele_max_EH(TString filename){

  pair<vector<float>,map<pair<int,int>,float> > Ei_EiEj = prod_Ei_Eij_max_EH(filename);
  
  vector<float> Ei = Ei_EiEj.first;
  map<pair<int,int>,float> EiEj = Ei_EiEj.second;


  TMatrixD V(14,1);
  TMatrixD M(14,14);

  for(unsigned int i=0;i<14;i++){
    V(i,0) = Ei[i];  
    for(unsigned int j=0;j<14;j++){
      pair<int,int> key = make_pair(i,j);
      M(i,j) = EiEj[key];
    }
  }

  cout<<"V"<<endl;
  V.Print();
  cout<<"M"<<endl;
  M.Print();

  M.Invert();
  TMatrixD weights = M*V;

  std::ofstream out("weights_calib.txt");

  vector<float> w(38);
  out<<"{";
  for(unsigned int i=0;i<38;i++){
    if(i<14){
      w[i] = weights(i,0);
      out<<w[i]<<",";
    }
    else if(i<38){
      w[i] = 0.;
      out<<"0.,";
    }
    else{
      w[i] = 0.;
      out<<"0.}"<<endl;
    }
  }
 


  return w;

}
				 





vector<float> prod_weight_calib_matrix_pi_max_EH(TString filename){

  pair<vector<float>,map<pair<int,int>,float> > Ei_EiEj = prod_Ei_Eij_max_EH(filename);
  
  vector<float> Ei = Ei_EiEj.first;
  map<pair<int,int>,float> EiEj = Ei_EiEj.second;


  TMatrixD V(38,1);
  TMatrixD M(38,38);

  for(unsigned int i=0;i<38;i++){
    V(i,0) = Ei[i];  
    for(unsigned int j=0;j<38;j++){
      pair<int,int> key = make_pair(i,j);
      M(i,j) = EiEj[key];
    }
  }

  cout<<"V"<<endl;
  V.Print();
  cout<<"M"<<endl;
  M.Print();

  M.Invert();
  TMatrixD weights = M*V;

  std::ofstream out("weights_calib.txt");


  vector<float> w(38);
  out<<"{";
  for(unsigned int i=0;i<38;i++){
    w[i] = weights(i,0);
    if(i<27)
      out<<w[i]<<",";
    else
      out<<"0.}"<<endl;
  }
 


  return w;

}
				 











void plot_pi3(){

  TString filename = "test_pi.root";
  TString filename2 = "test_pi_0p03.root";
  
  
  TH1F* h_default = single_plot(filename,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]","gen_cl3d>=0",100,0.,50.);
  TH1F* h_default_0p03 = single_plot(filename2,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]","gen_cl3d>=0",100,0.,50.);
  TH1F* h_pi = single_plot(filename,"HGCalTriggerNtuple","cl3d_pt_new_pi[gen_cl3d]","gen_cl3d>=0",100,0.,50.);
  TH1F* h_pi2 = single_plot(filename2,"HGCalTriggerNtuple","cl3d_pt_new_pi[gen_cl3d]","gen_cl3d>=0",100,0.,50.);
  TH1F* h_pi_0p03 = single_plot(filename2,"HGCalTriggerNtuple","cl3d_pt_new_pi_0p03[gen_cl3d]","gen_cl3d>=0",100,0.,50.);


  vector<TH1F*> histo;
  histo.push_back(h_default);
  histo.push_back(h_default_0p03);
  histo.push_back(h_pi);
  histo.push_back(h_pi2);
  histo.push_back(h_pi_0p03);



  vector<TString> leg_entry;
  leg_entry.push_back("dR=0.01, default calibr.");
  leg_entry.push_back("dR=0.03, default calibr.");
  leg_entry.push_back("dR=0.01, dR=0.01 recalibr.");
  leg_entry.push_back("dR=0.03, dR=0.01 recalibr.");
  leg_entry.push_back("dR=0.03, dR=0.03 recalibr.");


  TLegend* leg=new TLegend(0.3,0.65,0.5,0.85);
  leg->SetHeader("Pion gun p_{T}=25 GeV PU=0");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  
 for(unsigned int i=0;i<histo.size();i++){
    TH1F* h = histo[i];
    h->Scale(1/h->Integral());
    h->SetLineWidth(2);
    h->SetLineColor(i+1);
    if(i>3)
      h->SetLineColor(i+2);      
    leg->AddEntry(h,leg_entry[i]);
  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  //c->SetLogy();

  histo = sort_histo(histo);

  histo[0]->GetXaxis()->SetTitle("p_{T}(C3D) [GeV]");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,2*histo[0]->GetMaximum());
  //histo[0]->SetMaximum(2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(-0.99,1.02*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV, PU=0");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/C3D_pi_recalibr3.pdf");  




}









void plot_pi3_rescaled(){

  TString filename = "test_pi.root";
  TString filename2 = "test_pi_0p03.root";
  
  TH1F* h_default_0 = single_plot(filename,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]","gen_cl3d>=0",100,0.,50.);
  TH1F* h_default_0p03_0 = single_plot(filename2,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]","gen_cl3d>=0",100,0.,50.);
  TH1F* h_pi_0 = single_plot(filename,"HGCalTriggerNtuple","cl3d_pt_new_pi[gen_cl3d]","gen_cl3d>=0",100,0.,50.);
  TH1F* h_pi2_0 = single_plot(filename2,"HGCalTriggerNtuple","cl3d_pt_new_pi[gen_cl3d]","gen_cl3d>=0",100,0.,50.);
  TH1F* h_pi_0p03_0 = single_plot(filename2,"HGCalTriggerNtuple","cl3d_pt_new_pi_0p03[gen_cl3d]","gen_cl3d>=0",100,0.,50.);

  TH1F* h_default = single_plot(filename,"HGCalTriggerNtuple",Form("%f*cl3d_pt[gen_cl3d]",25./ h_default_0->GetMean()),"gen_cl3d>=0",100,0.,50.);
  TH1F* h_default_0p03 = single_plot(filename2,"HGCalTriggerNtuple",Form("%f*cl3d_pt[gen_cl3d]",25./ h_default_0p03_0->GetMean()),"gen_cl3d>=0",100,0.,50.);
  TH1F* h_pi = single_plot(filename,"HGCalTriggerNtuple",Form("%f*cl3d_pt_new_pi[gen_cl3d]",25./ h_pi_0->GetMean()),"gen_cl3d>=0",100,0.,50.);
  TH1F* h_pi2 = single_plot(filename2,"HGCalTriggerNtuple",Form("%f*cl3d_pt_new_pi[gen_cl3d]",25./ h_pi2_0->GetMean()),"gen_cl3d>=0",100,0.,50.);
  TH1F* h_pi_0p03 = single_plot(filename2,"HGCalTriggerNtuple",Form("%f*cl3d_pt_new_pi_0p03[gen_cl3d][gen_cl3d]",25./ h_pi_0p03_0->GetMean()),"gen_cl3d>=0",100,0.,50.);

  cout<<25./ h_pi_0p03_0->GetMean()<<endl;


  vector<TH1F*> histo;
  histo.push_back(h_default);
  histo.push_back(h_default_0p03);
  histo.push_back(h_pi);
  histo.push_back(h_pi2);
  histo.push_back(h_pi_0p03);



  vector<TString> leg_entry;
  leg_entry.push_back("dR=0.01, default calibr.");
  leg_entry.push_back("dR=0.03, default calibr.");
  leg_entry.push_back("dR=0.01, dR=0.01 recalibr.");
  leg_entry.push_back("dR=0.03, dR=0.01 recalibr.");
  leg_entry.push_back("dR=0.03, dR=0.03 recalibr.");


  TLegend* leg=new TLegend(0.3,0.65,0.5,0.85);
  leg->SetHeader("Pion gun p_{T}=25 GeV PU=0");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  
 for(unsigned int i=0;i<histo.size();i++){
    TH1F* h = histo[i];
    h->Scale(1/h->Integral());
    h->SetLineWidth(2);
    h->SetLineColor(i+1);
    if(i>3)
      h->SetLineColor(i+2);      
    leg->AddEntry(h,leg_entry[i]);
  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  //c->SetLogy();

  histo = sort_histo(histo);

  histo[0]->GetXaxis()->SetTitle("p_{T}(C3D) [GeV]");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,2*histo[0]->GetMaximum());
  //histo[0]->SetMaximum(2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(-0.99,1.02*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV, PU=0");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/C3D_pi_recalibr3_rescaled.pdf");  




}










void plot_pi_default_nC3D(){

  TString filename = "test_pi.root";
  TString filename2 = "test_pi_0p03.root";
  
  
  TH1F* h_1 = single_plot(filename,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d[0]]","gen_cl3d[0]>=0 && Sum$(cl3d_eta*gen_eta[0]>0)==1",50,0.,50.);
  TH1F* h_2 = single_plot(filename,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d[0]]","gen_cl3d[0]>=0 && Sum$(cl3d_eta*gen_eta[0]>0)==2",50,0.,50.);
  TH1F* h_3 = single_plot(filename,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d[0]]","gen_cl3d[0]>=0 && Sum$(cl3d_eta*gen_eta[0]>0)==3",50,0.,50.);
  TH1F* h_4 = single_plot(filename,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d[0]]","gen_cl3d[0]>=0 && Sum$(cl3d_eta*gen_eta[0]>0)==4",50,0.,50.);
  TH1F* h_5 = single_plot(filename,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d[0]]","gen_cl3d[0]>=0 && Sum$(cl3d_eta*gen_eta[0]>0)==5",50,0.,50.);
  TH1F* h_6 = single_plot(filename,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d[0]]","gen_cl3d[0]>=0 && Sum$(cl3d_eta*gen_eta[0]>0)==6",50,0.,50.);


  vector<TH1F*> histo;
  histo.push_back(h_1);
  histo.push_back(h_2);
  histo.push_back(h_3);
  histo.push_back(h_4);
  histo.push_back(h_5);
  histo.push_back(h_6);

  vector<TString> leg_entry;
  leg_entry.push_back("#C3D = 1");
  leg_entry.push_back("#C3D = 2");
  leg_entry.push_back("#C3D = 3");
  leg_entry.push_back("#C3D = 4");
  leg_entry.push_back("#C3D = 5");
  leg_entry.push_back("#C3D = 6");


  TLegend* leg=new TLegend(0.4,0.5,0.5,0.85);
  leg->SetHeader("#splitline{Pion gun p_{T}=25 GeV PU=0}{dR=0.01, default calibr.}");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  
 for(unsigned int i=0;i<histo.size();i++){
    TH1F* h = histo[i];
    cout<<h->Integral()<<endl;
    h->Scale(1/h->Integral());
    h->SetLineWidth(2);
    h->SetLineColor(i+1);
    if(i>3)
      h->SetLineColor(i+2);      
    leg->AddEntry(h,leg_entry[i]);    
  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  //c->SetLogy();

  histo = sort_histo(histo);

  histo[0]->GetXaxis()->SetTitle("p_{T}(C3D) [GeV]");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,2*histo[0]->GetMaximum());
  //histo[0]->SetMaximum(2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(-0.99,1.02*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV, PU=0");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/C3D_pi_default_nC3D.pdf");  




}










void plot_nC3D(){

  TString filename = "test_pi.root";
  TString filename2 = "test_pi_0p03.root";
  
  
  TH1F* h_default = single_plot(filename,"HGCalTriggerNtuple","Sum$(cl3d_eta>0)","",10,0.,10.);
  h_default->Add( single_plot(filename,"HGCalTriggerNtuple","Sum$(cl3d_eta<0)","",10,0.,10.));

  TH1F* h_default_0p03 = single_plot(filename2,"HGCalTriggerNtuple","Sum$(cl3d_eta>0)","",10,0.,10.);
  h_default_0p03->Add( single_plot(filename2,"HGCalTriggerNtuple","Sum$(cl3d_eta<0)","",10,0.,10.));



  vector<TH1F*> histo;
  histo.push_back(h_default);
  histo.push_back(h_default_0p03);



  vector<TString> leg_entry;
  leg_entry.push_back("dR=0.01");
  leg_entry.push_back("dR=0.03");


  TLegend* leg=new TLegend(0.3,0.65,0.5,0.85);
  leg->SetHeader("Pion gun p_{T}=25 GeV PU=0");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  
 for(unsigned int i=0;i<histo.size();i++){
    TH1F* h = histo[i];
    h->Scale(1/h->Integral());
    h->SetLineWidth(2);
    h->SetLineColor(i+1);
    if(i>3)
      h->SetLineColor(i+2);      
    leg->AddEntry(h,leg_entry[i]);
  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  //c->SetLogy();

  histo = sort_histo(histo);

  histo[0]->GetXaxis()->SetTitle("#C3D");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,2*histo[0]->GetMaximum());
  //histo[0]->SetMaximum(2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(0.01,1.02*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV, PU=0");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/nC3D_0p03.pdf");  




}












void plot_C3D_ratio(){

  TString filename = "test_pi.root";
  TString filename2 = "test_pi_0p03.root";
  
   TH1F* h_default = single_plot(filename,"HGCalTriggerNtuple","Max$(cl3d_pt*(cl3d_eta*gen_eta[0]>0 && cl3d_pt!=cl3d_pt[gen_cl3d[0]]))/cl3d_pt[gen_cl3d[0]]","gen_cl3d[0]>=0",100,0.,1.);
  TH1F* h_default_0p03 = single_plot(filename2,"HGCalTriggerNtuple","Max$(cl3d_pt*(cl3d_eta*gen_eta[0]>0 && cl3d_pt!=cl3d_pt[gen_cl3d[0]]))/cl3d_pt[gen_cl3d[0]]","gen_cl3d[0]>=0",100,0.,1.);
  TH1F* h_pi = single_plot(filename,"HGCalTriggerNtuple","Max$(cl3d_pt_new_pi*(cl3d_eta*gen_eta[0]>0 && cl3d_pt_new_pi!=cl3d_pt_new_pi[gen_cl3d[0]]))/cl3d_pt_new_pi[gen_cl3d[0]]","gen_cl3d[0]>=0",100,0.,1.);
  TH1F* h_pi2 = single_plot(filename2,"HGCalTriggerNtuple","Max$(cl3d_pt_new_pi*(cl3d_eta*gen_eta[0]>0 && cl3d_pt_new_pi!=cl3d_pt_new_pi[gen_cl3d[0]]))/cl3d_pt_new_pi[gen_cl3d[0]]","gen_cl3d[0]>=0",100,0.,1.);
  TH1F* h_pi_0p03 = single_plot(filename2,"HGCalTriggerNtuple","Max$(cl3d_pt_new_pi_0p03*(cl3d_eta*gen_eta[0]>0 && cl3d_pt_new_pi_0p03!=cl3d_pt_new_pi_0p03[gen_cl3d[0]]))/cl3d_pt_new_pi_0p03[gen_cl3d[0]]","gen_cl3d[0]>=0",100,0.,1.);

  vector<TH1F*> histo;
  histo.push_back(h_default);
  histo.push_back(h_default_0p03);
  histo.push_back(h_pi);
  histo.push_back(h_pi2);
  histo.push_back(h_pi_0p03);



  vector<TString> leg_entry;
  leg_entry.push_back("dR=0.01, default calibr.");
  leg_entry.push_back("dR=0.03, default calibr.");
  leg_entry.push_back("dR=0.01, dR=0.01 recalibr.");
  leg_entry.push_back("dR=0.03, dR=0.01 recalibr.");
  leg_entry.push_back("dR=0.03, dR=0.03 recalibr.");


  TLegend* leg=new TLegend(0.3,0.65,0.5,0.85);
  leg->SetHeader("Pion gun p_{T}=25 GeV PU=0");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  
 for(unsigned int i=0;i<histo.size();i++){
    TH1F* h = histo[i];
    h->Scale(1/h->Integral());
    h->SetLineWidth(2);
    h->SetLineColor(i+1);
    if(i>3)
      h->SetLineColor(i+2);      
    leg->AddEntry(h,leg_entry[i]);
  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  c->SetLogy();

  histo = sort_histo(histo);

  histo[0]->GetXaxis()->SetTitle("Ratio sublead./lead. C3D");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  //histo[0]->GetYaxis()->SetRangeUser(0,2*histo[0]->GetMaximum());
  histo[0]->SetMaximum(2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(0.01,1.2*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV, PU=0");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/C3D_ratio.pdf");  




}









void plot_C3D_ratio2(){

  TString filename = "test_pi.root";
  TString filename2 = "test_pi_0p03.root";
  
   TH1F* h_default = single_plot(filename,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d[0]]/Sum$(cl3d_pt*(cl3d_eta*gen_eta[0]>0))","gen_cl3d[0]>=0",101,0.,1.01);
  TH1F* h_default_0p03 = single_plot(filename2,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d[0]]/Sum$(cl3d_pt*(cl3d_eta*gen_eta[0]>0))","gen_cl3d[0]>=0",101,0.,1.01);
  TH1F* h_pi = single_plot(filename,"HGCalTriggerNtuple","cl3d_pt_new_pi[gen_cl3d[0]]/Sum$(cl3d_pt_new_pi*(cl3d_eta*gen_eta[0]>0))","gen_cl3d[0]>=0",101,0.,1.01);
  TH1F* h_pi2 = single_plot(filename2,"HGCalTriggerNtuple","cl3d_pt_new_pi[gen_cl3d[0]]/Sum$(cl3d_pt_new_pi*(cl3d_eta*gen_eta[0]>0))","gen_cl3d[0]>=0",101,0.,1.01);
  TH1F* h_pi_0p03 = single_plot(filename2,"HGCalTriggerNtuple","cl3d_pt_new_pi_0p03[gen_cl3d[0]]/Sum$(cl3d_pt_new_pi_0p03*(cl3d_eta*gen_eta[0]>0))","gen_cl3d[0]>=0",101,0.,1.01);

  vector<TH1F*> histo;
  histo.push_back(h_default);
  histo.push_back(h_default_0p03);
  histo.push_back(h_pi);
  histo.push_back(h_pi2);
  histo.push_back(h_pi_0p03);



  vector<TString> leg_entry;
  leg_entry.push_back("dR=0.01, default calibr.");
  leg_entry.push_back("dR=0.03, default calibr.");
  leg_entry.push_back("dR=0.01, dR=0.01 recalibr.");
  leg_entry.push_back("dR=0.03, dR=0.01 recalibr.");
  leg_entry.push_back("dR=0.03, dR=0.03 recalibr.");


  TLegend* leg=new TLegend(0.2,0.65,0.5,0.85);
  leg->SetHeader("Pion gun p_{T}=25 GeV PU=0");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  
 for(unsigned int i=0;i<histo.size();i++){
    TH1F* h = histo[i];
    h->Scale(1/h->Integral());
    h->SetLineWidth(2);
    h->SetLineColor(i+1);
    if(i>3)
      h->SetLineColor(i+2);      
    leg->AddEntry(h,leg_entry[i]);
  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  c->SetLogy();

  histo = sort_histo(histo);

  histo[0]->GetXaxis()->SetTitle("Ratio lead./sum C3D");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  //histo[0]->GetYaxis()->SetRangeUser(0,2*histo[0]->GetMaximum());
  histo[0]->SetMaximum(2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(0.01,1.2*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV, PU=0");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/C3D_ratio2.pdf");  




}





