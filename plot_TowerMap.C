#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <THStack.h>
#include <iostream>
#include <TLegend.h>
#include <TLatex.h>
#include <TProfile.h>
#include <TStyle.h>
#include <TLine.h>
#include <TGaxis.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include "Helpers.C"
#include <vector>

using namespace std;




void plot_nC2D(){

  TH1F* h_dRNNC2D_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1*.root","HGCalTriggerNtupleJet","cl_n","1",130,0,13000);
  TH1F* h_GEO_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/jet_ntuples_merged/ntuple_jet_merged_1*.root","HGCalTriggerNtuple","cl_n","1",130,0,13000);
  TH1F* h_TowerMap3cm_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_3cm/jet_ntuples_merged/ntuple_jet_merged_1*.root","HGCalTriggerNtupleJet","cl_n","1",130,0,13000);
  TH1F* h_TowerMap6cm_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_1*.root","HGCalTriggerNtupleJet","cl_n","1",130,0,13000);


  vector<TH1F*> histo;
  histo.push_back(h_dRNNC2D_VBF_PU200);
  histo.push_back(h_GEO_VBF_PU200);
  histo.push_back(h_TowerMap3cm_VBF_PU200);
  histo.push_back(h_TowerMap6cm_VBF_PU200);

  vector<TString> leg_entry;
  leg_entry.push_back("NN + GEO 6cm");
  leg_entry.push_back("GEO 3cm");
  leg_entry.push_back("Pseudo-clustering + GEO 3cm");
  leg_entry.push_back("Pseudo-clustering + GEO 6cm");

  TLegend* leg=new TLegend(0.2,0.6,0.5,0.85);
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
  TGaxis::SetMaxDigits(4);

  histo[0]->GetXaxis()->SetTitle("#C2D");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,0.15);
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(10.,0.151,"CMS Simulation VBF H#rightarrow inv. #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/nC2D_TowerMap.pdf");  


}





void plot_eta_C2D(){

  int nbins = 100;
  float min = 1.5;
  float max = 3.0;

  TH1F* h_NN_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_1.root","HGCalTriggerNtuple","abs(cl_eta)","1",nbins,min,max);
  TH1F* h_GEO_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtuple","abs(cl_eta)","1",nbins,min,max);
  TH1F* h_TowerMap3cm_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_3cm/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","abs(cl_eta)","1",nbins,min,max);
  TH1F* h_TowerMap6cm_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_3.root","HGCalTriggerNtupleJet","abs(cl_eta)","1",nbins,min,max);


  vector<TH1F*> histo;
  histo.push_back(h_NN_VBF_PU200);
  histo.push_back(h_GEO_VBF_PU200);
  histo.push_back(h_TowerMap3cm_VBF_PU200);
  histo.push_back(h_TowerMap6cm_VBF_PU200);

  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO 3cm");
  leg_entry.push_back("Pseudo-clustering + GEO 3cm");
  leg_entry.push_back("Pseudo-clustering + GEO 6cm");

  TLegend* leg=new TLegend(0.2,0.6,0.5,0.85);
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
  TGaxis::SetMaxDigits(4);

  histo[0]->GetXaxis()->SetTitle("#eta(C2D)");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,1.7*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.51,1.01*histo[0]->GetMaximum(),"CMS Simulation VBF H#rightarrow inv. #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/eta_C2D_TowerMap.pdf");  


}







void plot_MIPpT_C2D(){

  int nbins = 100;
  float min = 0;
  float max = 400;

  TH1F* h_dRNNC2D_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","cl_mipPt","1",nbins,min,max);
  TH1F* h_GEO_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_1.root","HGCalTriggerNtuple","cl_MIPpt","1",nbins,min,max);
  TH1F* h_TowerMap3cm_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_3cm/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","cl_mipPt","1",nbins,min,max);
  TH1F* h_TowerMap6cm_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_3.root","HGCalTriggerNtupleJet","cl_mipPt","1",nbins,min,max);


  vector<TH1F*> histo;
  histo.push_back(h_dRNNC2D_VBF_PU200);
  histo.push_back(h_GEO_VBF_PU200);
  histo.push_back(h_TowerMap3cm_VBF_PU200);
  histo.push_back(h_TowerMap6cm_VBF_PU200);

  vector<TString> leg_entry;
  leg_entry.push_back("NN + GEO 6cm");
  leg_entry.push_back("GEO 3cm");
  leg_entry.push_back("Pseudo-clustering + GEO 3cm");
  leg_entry.push_back("Pseudo-clustering + GEO 6cm");

  TLegend* leg=new TLegend(0.3,0.6,0.5,0.85);
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
  TGaxis::SetMaxDigits(4);

  histo[0]->GetXaxis()->SetTitle("MIP_{T}(C2D)");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(2e-5,2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.51,1.01*histo[0]->GetMaximum(),"CMS Simulation VBF H#rightarrow inv. #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");



  gPad->SetTicks();


  c->SaveAs("plots/mipPt_C2D_TowerMap.pdf");  


}






void plot_ncells_C2D(){

  int nbins = 40;
  float min = 0;
  float max = 40;

  TH1F* h_dRNNC2D_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","cl_cells_n","1",nbins,min,max);
  TH1F* h_GEO_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_1.root","HGCalTriggerNtuple","cl_ncells","1",nbins,min,max);
  TH1F* h_TowerMap3cm_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_3cm/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","cl_cells_n","1",nbins,min,max);
  TH1F* h_TowerMap6cm_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_3.root","HGCalTriggerNtupleJet","cl_cells_n","1",nbins,min,max);


  vector<TH1F*> histo;
  histo.push_back(h_dRNNC2D_VBF_PU200);
  histo.push_back(h_GEO_VBF_PU200);
  histo.push_back(h_TowerMap3cm_VBF_PU200);
  histo.push_back(h_TowerMap6cm_VBF_PU200);

  vector<TString> leg_entry;
  leg_entry.push_back("NN + GEO 6 cm");
  leg_entry.push_back("GEO 3cm");
  leg_entry.push_back("Pseudo-clustering + GEO 3cm");
  leg_entry.push_back("Pseudo-clustering + GEO 6cm");

  TLegend* leg=new TLegend(0.4,0.6,0.8,0.85);
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
  TGaxis::SetMaxDigits(4);

  histo[0]->GetXaxis()->SetTitle("#TC per C2D");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(2e-5,2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(0.02,1.01*histo[0]->GetMaximum(),"CMS Simulation VBF H#rightarrow inv. #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");



  gPad->SetTicks();


  c->SaveAs("plots/ncells_C2D_TowerMap.pdf");  


}







void plot_eta_mipPt_C2D(){

  TH2F* h_VBF_NN = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_1.root","HGCalTriggerNtuple","abs(cl_eta)","cl_MIPpt","",15,1.5,3.,10000,0,1000);
  TH2F* h_VBF_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_1.root","HGCalTriggerNtuple","abs(cl_eta)","cl_MIPpt","",15,1.5,3.,10000,0,1000);
  TH2F* h_VBF_TowerMap_3cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_3cm/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","abs(cl_eta)","cl_mipPt","",15,1.5,3.,10000,0,1000);
  TH2F* h_VBF_TowerMap_6cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_3.root","HGCalTriggerNtupleJet","abs(cl_eta)","cl_mipPt","",15,1.5,3.,10000,0,1000);


  vector<TH2F*> histo;
  histo.push_back(h_VBF_NN);
  histo.push_back(h_VBF_GEO);
  histo.push_back(h_VBF_TowerMap_3cm);
  histo.push_back(h_VBF_TowerMap_6cm);

  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO");
  leg_entry.push_back("Pseudo-clust. + GEO 3cm");
  leg_entry.push_back("Pseudo-clust. + GEO 6cm");

  TLegend* leg=new TLegend(0.3,0.5,0.5,0.8);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  for(unsigned int i=0;i<histo.size();i++){

    TH2F* h = histo[i];
    h->SetMarkerSize(1.5);
    h->SetMarkerColor(i+1);
    h->SetLineColor(i+1);
    h->SetFillColor(i+1);
    h->SetLineWidth(2);
    h->SetStats(0);
    h->SetBarWidth(0.075);
    h->SetBarOffset(-0.3+i*0.2);
    TH2F* h_leg = (TH2F*)h->Clone();
    h_leg->SetFillColor(0);
    leg->AddEntry(h_leg,leg_entry[i]);

  }

  TCanvas* c=new TCanvas("c","c",1050,1000);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);


  TH2F* h_dummy = new TH2F("","",15,1.5,3.,1000,0,1000); 
  h_dummy->GetXaxis()->SetTitle("|#eta(C2D)|");
  h_dummy->GetYaxis()->SetTitle("MIP_{T}(C2D)");
  h_dummy->GetYaxis()->SetTitleOffset(1.7);
  h_dummy->GetYaxis()->SetRangeUser(0,100.);
  h_dummy->SetStats(0);
  h_dummy->SetTitle("");
  h_dummy->Draw("candlex(00000301)");
  for(unsigned int i=0;i<histo.size();i++)
    histo[i]->Draw("candlex(00000301)same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.51,100.5,"CMS Simulation VBF H#rightarrow inv. #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/eta_mipPt_C2D_TowerMap.pdf");  


}






void plot_eta_pt_C2D(){

  TH2F* h_VBF_NN = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_1.root","HGCalTriggerNtuple","abs(cl_eta)","cl_calib_Luca_pt","",15,1.5,3.,10000,0,100);
  TH2F* h_VBF_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_1.root","HGCalTriggerNtuple","abs(cl_eta)","cl_calib_Luca_pt","",15,1.5,3.,10000,0,100);
  TH2F* h_VBF_TowerMap_3cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_3cm/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","abs(cl_eta)","cl_pt","",15,1.5,3.,10000,0,100);
  TH2F* h_VBF_TowerMap_6cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_3.root","HGCalTriggerNtupleJet","abs(cl_eta)","cl_pt","",15,1.5,3.,10000,0,100);


  vector<TH2F*> histo;
  histo.push_back(h_VBF_NN);
  histo.push_back(h_VBF_GEO);
  histo.push_back(h_VBF_TowerMap_3cm);
  histo.push_back(h_VBF_TowerMap_6cm);

  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO");
  leg_entry.push_back("Pseudo-clust. + GEO 3cm");
  leg_entry.push_back("Pseudo-clust. + GEO 6cm");

  TLegend* leg=new TLegend(0.3,0.5,0.5,0.8);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  for(unsigned int i=0;i<histo.size();i++){

    TH2F* h = histo[i];
    h->SetMarkerSize(1.5);
    h->SetMarkerColor(i+1);
    h->SetLineColor(i+1);
    h->SetFillColor(i+1);
    h->SetLineWidth(2);
    h->SetStats(0);
    h->SetBarWidth(0.075);
    h->SetBarOffset(-0.3+i*0.2);
    TH2F* h_leg = (TH2F*)h->Clone();
    h_leg->SetFillColor(0);
    leg->AddEntry(h_leg,leg_entry[i]);

  }

  TCanvas* c=new TCanvas("c","c",1050,1000);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);


  TH2F* h_dummy = new TH2F("","",15,1.5,3.,1000,0,1000); 
  h_dummy->GetXaxis()->SetTitle("|#eta(C2D)|");
  h_dummy->GetYaxis()->SetTitle("p_{T}(C2D) [GeV]");
  h_dummy->GetYaxis()->SetTitleOffset(1.7);
  h_dummy->GetYaxis()->SetRangeUser(0,2.);
  h_dummy->SetStats(0);
  h_dummy->SetTitle("");
  h_dummy->Draw("candlex(00000301)");
  for(unsigned int i=0;i<histo.size();i++)
    histo[i]->Draw("candlex(00000301)same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.51,100.5,"CMS Simulation VBF H#rightarrow inv. #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/eta_pt_C2D_TowerMap.pdf");  


}









void plot_layer_mipPt_C2D(){

  TH2F* h_VBF_NN = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_1.root","HGCalTriggerNtuple","abs(cl_eta)","cl_HGClayer","",55,0,55,10000,0,1000);
  TH2F* h_VBF_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_1.root","HGCalTriggerNtuple","abs(cl_eta)","cl_MIPpt","",55,0,55,10000,0,1000);
  TH2F* h_VBF_TowerMap_3cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_3cm/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","abs(cl_eta)","cl_mipPt","",55,0,55,10000,0,1000);
  TH2F* h_VBF_TowerMap_6cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_3.root","HGCalTriggerNtupleJet","abs(cl_eta)","cl_mipPt","",55,0,55,10000,0,1000);


  vector<TH2F*> histo;
  histo.push_back(h_VBF_NN);
  histo.push_back(h_VBF_GEO);
  histo.push_back(h_VBF_TowerMap_3cm);
  histo.push_back(h_VBF_TowerMap_6cm);

  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO");
  leg_entry.push_back("Pseudo-clust. + GEO 3cm");
  leg_entry.push_back("Pseudo-clust. + GEO 6cm");

  TLegend* leg=new TLegend(0.3,0.5,0.5,0.8);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  for(unsigned int i=0;i<histo.size();i++){

    TH2F* h = histo[i];
    h->SetMarkerSize(1.5);
    h->SetMarkerColor(i+1);
    h->SetLineColor(i+1);
    h->SetFillColor(i+1);
    h->SetLineWidth(2);
    h->SetStats(0);
    h->SetBarWidth(0.075);
    h->SetBarOffset(-0.3+i*0.2);
    TH2F* h_leg = (TH2F*)h->Clone();
    h_leg->SetFillColor(0);
    leg->AddEntry(h_leg,leg_entry[i]);

  }

  TCanvas* c=new TCanvas("c","c",1050,1000);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);


  TH2F* h_dummy = new TH2F("","",55,0,55,1000,0,1000); 
  h_dummy->GetXaxis()->SetTitle("Layer");
  h_dummy->GetYaxis()->SetTitle("MIP_{T}(C2D)");
  h_dummy->GetYaxis()->SetTitleOffset(1.7);
  h_dummy->GetYaxis()->SetRangeUser(0,100.);
  h_dummy->SetStats(0);
  h_dummy->SetTitle("");
  h_dummy->Draw("candlex(00000301)");
  for(unsigned int i=0;i<histo.size();i++)
    histo[i]->Draw("candlex(00000301)same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.51,100.5,"CMS Simulation VBF H#rightarrow inv. #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/HGClayer_mipPt_C2D_TowerMap.pdf");  


}







void plot_nC3D(){

  TH1F* h_NN_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_1*.root","HGCalTriggerNtuple","cl3d_n","1",150,0,3000);
  TH1F* h_GEO_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/jet_ntuples_merged/ntuple_jet_merged_1*.root","HGCalTriggerNtuple","cl3d_n","1",150,0,3000);
  TH1F* h_TowerMap3cm_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_3cm/jet_ntuples_merged/ntuple_jet_merged_1*.root","HGCalTriggerNtupleJet","cl3d_n","1",150,0,3000);
  TH1F* h_TowerMap6cm_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_1*.root","HGCalTriggerNtupleJet","cl3d_n","1",150,0,3000);


  vector<TH1F*> histo;
  histo.push_back(h_NN_VBF_PU200);
  histo.push_back(h_GEO_VBF_PU200);
  histo.push_back(h_TowerMap3cm_VBF_PU200);
  histo.push_back(h_TowerMap6cm_VBF_PU200);

  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO 3cm");
  leg_entry.push_back("Pseudo-clustering + GEO 3cm");
  leg_entry.push_back("Pseudo-clustering + GEO 6cm");

  TLegend* leg=new TLegend(0.35,0.6,0.8,0.85);
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
  TGaxis::SetMaxDigits(4);

  histo[0]->GetXaxis()->SetTitle("#C3D");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,0.15);
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(10.,0.151,"CMS Simulation VBF H#rightarrow inv. #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/nC3D_TowerMap.pdf");  


}








void plot_eta_C3D(){

  int nbins = 100;
  float min = 1.5;
  float max = 3.0;

  TH1F* h_NN_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_1.root","HGCalTriggerNtuple","abs(cl3d_eta)","1",nbins,min,max);
  TH1F* h_GEO_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtuple","abs(cl3d_eta)","1",nbins,min,max);
  TH1F* h_TowerMap3cm_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_3cm/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","abs(cl3d_eta)","1",nbins,min,max);
  TH1F* h_TowerMap6cm_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_3.root","HGCalTriggerNtupleJet","abs(cl3d_eta)","1",nbins,min,max);


  vector<TH1F*> histo;
  histo.push_back(h_NN_VBF_PU200);
  histo.push_back(h_GEO_VBF_PU200);
  histo.push_back(h_TowerMap3cm_VBF_PU200);
  histo.push_back(h_TowerMap6cm_VBF_PU200);

  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO 3cm");
  leg_entry.push_back("Pseudo-clustering + GEO 3cm");
  leg_entry.push_back("Pseudo-clustering + GEO 6cm");

  TLegend* leg=new TLegend(0.2,0.6,0.5,0.85);
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
  TGaxis::SetMaxDigits(4);

  histo[0]->GetXaxis()->SetTitle("#eta(C3D)");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,1.7*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.51,1.01*histo[0]->GetMaximum(),"CMS Simulation VBF H#rightarrow inv. #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/eta_C3D_TowerMap.pdf");  


}







void plot_nclu_C3D(){

  int nbins = 50;
  float min = 0;
  float max = 50;

  TH1F* h_NN_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_1.root","HGCalTriggerNtuple","cl3d_nclu","1",nbins,min,max);
  TH1F* h_GEO_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtuple","cl3d_nclu","1",nbins,min,max);
  TH1F* h_TowerMap3cm_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_3cm/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","cl3d_clusters_n","1",nbins,min,max);
  TH1F* h_TowerMap6cm_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_3.root","HGCalTriggerNtupleJet","cl3d_clusters_n","1",nbins,min,max);


  vector<TH1F*> histo;
  histo.push_back(h_NN_VBF_PU200);
  histo.push_back(h_GEO_VBF_PU200);
  histo.push_back(h_TowerMap3cm_VBF_PU200);
  histo.push_back(h_TowerMap6cm_VBF_PU200);

  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO 3cm");
  leg_entry.push_back("Pseudo-clust. + GEO 3cm");
  leg_entry.push_back("Pseudo-clust. + GEO 6cm");

  TLegend* leg=new TLegend(0.4,0.6,0.7,0.85);
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
  TGaxis::SetMaxDigits(4);

  histo[0]->GetXaxis()->SetTitle("#C2D per C3D");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,1.7*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.51,1.01*histo[0]->GetMaximum(),"CMS Simulation VBF H#rightarrow inv. #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/nclu_C3D_TowerMap.pdf");  


}





void plot_eta_pt_C3D(){

  TH2F* h_VBF_NN = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_1.root","HGCalTriggerNtuple","abs(cl3d_eta)","cl3d_calib_Luca_pt","",15,1.5,3.,10000,0,100);
  TH2F* h_VBF_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_1.root","HGCalTriggerNtuple","abs(cl3d_eta)","cl3d_calib_Luca_pt","",15,1.5,3.,10000,0,100);
  TH2F* h_VBF_TowerMap_3cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_3cm/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","abs(cl3d_eta)","cl3d_pt","",15,1.5,3.,10000,0,100);
  TH2F* h_VBF_TowerMap_6cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_3.root","HGCalTriggerNtupleJet","abs(cl3d_eta)","cl3d_pt","",15,1.5,3.,10000,0,100);


  vector<TH2F*> histo;
  histo.push_back(h_VBF_NN);
  histo.push_back(h_VBF_GEO);
  histo.push_back(h_VBF_TowerMap_3cm);
  histo.push_back(h_VBF_TowerMap_6cm);

  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO");
  leg_entry.push_back("Pseudo-clust. + GEO 3cm");
  leg_entry.push_back("Pseudo-clust. + GEO 6cm");

  TLegend* leg=new TLegend(0.3,0.5,0.5,0.8);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  for(unsigned int i=0;i<histo.size();i++){

    TH2F* h = histo[i];
    h->SetMarkerSize(1.5);
    h->SetMarkerColor(i+1);
    h->SetLineColor(i+1);
    h->SetFillColor(i+1);
    h->SetLineWidth(2);
    h->SetStats(0);
    h->SetBarWidth(0.075);
    h->SetBarOffset(-0.3+i*0.2);
    TH2F* h_leg = (TH2F*)h->Clone();
    h_leg->SetFillColor(0);
    leg->AddEntry(h_leg,leg_entry[i]);

  }

  TCanvas* c=new TCanvas("c","c",1050,1000);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);


  TH2F* h_dummy = new TH2F("","",15,1.5,3.,1000,0,1000); 
  h_dummy->GetXaxis()->SetTitle("|#eta(C3D)|");
  h_dummy->GetYaxis()->SetTitle("p_{T}(C3D) [GeV]");
  h_dummy->GetYaxis()->SetTitleOffset(1.7);
  h_dummy->GetYaxis()->SetRangeUser(0,6.);
  h_dummy->SetStats(0);
  h_dummy->SetTitle("");
  h_dummy->Draw("candlex(00000301)");
  for(unsigned int i=0;i<histo.size();i++)
    histo[i]->Draw("candlex(00000301)same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.51,6.01,"CMS Simulation VBF H#rightarrow inv. #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/eta_pt_C3D_TowerMap.pdf");  


}





void plot_eta_nclu_C3D(){

  TH2F* h_VBF_NN = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_1.root","HGCalTriggerNtuple","abs(cl3d_eta)","cl3d_nclu","",15,1.5,3.,100,0,100);
  TH2F* h_VBF_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_1.root","HGCalTriggerNtuple","abs(cl3d_eta)","cl3d_nclu","",15,1.5,3.,100,0,100);
  TH2F* h_VBF_TowerMap_3cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_3cm/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","abs(cl3d_eta)","cl3d_clusters_n","",15,1.5,3.,100,0,100);
  TH2F* h_VBF_TowerMap_6cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_3.root","HGCalTriggerNtupleJet","abs(cl3d_eta)","cl3d_clusters_n","",15,1.5,3.,100,0,100);


  vector<TH2F*> histo;
  histo.push_back(h_VBF_NN);
  histo.push_back(h_VBF_GEO);
  histo.push_back(h_VBF_TowerMap_3cm);
  histo.push_back(h_VBF_TowerMap_6cm);

  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO");
  leg_entry.push_back("Pseudo-clust. + GEO 3cm");
  leg_entry.push_back("Pseudo-clust. + GEO 6cm");

  TLegend* leg=new TLegend(0.3,0.5,0.5,0.8);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  for(unsigned int i=0;i<histo.size();i++){

    TH2F* h = histo[i];
    h->SetMarkerSize(1.5);
    h->SetMarkerColor(i+1);
    h->SetLineColor(i+1);
    h->SetFillColor(i+1);
    h->SetLineWidth(2);
    h->SetStats(0);
    h->SetBarWidth(0.075);
    h->SetBarOffset(-0.3+i*0.2);
    TH2F* h_leg = (TH2F*)h->Clone();
    h_leg->SetFillColor(0);
    leg->AddEntry(h_leg,leg_entry[i]);

  }

  TCanvas* c=new TCanvas("c","c",1050,1000);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);


  TH2F* h_dummy = new TH2F("","",15,1.5,3.,1000,0,1000); 
  h_dummy->GetXaxis()->SetTitle("|#eta(C3D)|");
  h_dummy->GetYaxis()->SetTitle("#C2D per C3D");
  h_dummy->GetYaxis()->SetTitleOffset(1.7);
  h_dummy->GetYaxis()->SetRangeUser(0,20.);
  h_dummy->SetStats(0);
  h_dummy->SetTitle("");
  h_dummy->Draw("candlex(00000301)");
  for(unsigned int i=0;i<histo.size();i++)
    histo[i]->Draw("candlex(00000301)same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.51,20.1,"CMS Simulation VBF H#rightarrow inv. #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/eta_nclu_C3D_TowerMap.pdf");  


}







void plot_showerlength_C3D(){

  int nbins = 30;
  float min = 0;
  float max = 60;

  TH1F* h_NN_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_1.root","HGCalTriggerNtuple","cl3d_showerlength","1",nbins,min,max);
  TH1F* h_GEO_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtuple","cl3d_showerlength","1",nbins,min,max);
  TH1F* h_TowerMap3cm_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_3cm/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","cl3d_showerlength","1",nbins,min,max);
  TH1F* h_TowerMap6cm_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_3.root","HGCalTriggerNtupleJet","cl3d_showerlength","1",nbins,min,max);


  vector<TH1F*> histo;
  histo.push_back(h_NN_VBF_PU200);
  histo.push_back(h_GEO_VBF_PU200);
  histo.push_back(h_TowerMap3cm_VBF_PU200);
  histo.push_back(h_TowerMap6cm_VBF_PU200);

  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO 3cm");
  leg_entry.push_back("Pseudo-clust. + GEO 3cm");
  leg_entry.push_back("Pseudo-clust. + GEO 6cm");

  TLegend* leg=new TLegend(0.4,0.6,0.7,0.85);
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
  TGaxis::SetMaxDigits(4);

  histo[0]->GetXaxis()->SetTitle("Shower length");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,1.7*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.51,1.01*histo[0]->GetMaximum(),"CMS Simulation VBF H#rightarrow inv. #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/showerlength_C3D_TowerMap.pdf");  


}








void plot_firstlayer_C3D(){

  int nbins = 30;
  float min = 0;
  float max = 60;

  TH1F* h_NN_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_1.root","HGCalTriggerNtuple","cl3d_firstlayer","1",nbins,min,max);
  TH1F* h_GEO_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtuple","cl3d_firstlayer","1",nbins,min,max);
  TH1F* h_TowerMap3cm_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_3cm/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","cl3d_firstlayer","1",nbins,min,max);
  TH1F* h_TowerMap6cm_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_3.root","HGCalTriggerNtupleJet","cl3d_firstlayer","1",nbins,min,max);


  vector<TH1F*> histo;
  histo.push_back(h_NN_VBF_PU200);
  histo.push_back(h_GEO_VBF_PU200);
  histo.push_back(h_TowerMap3cm_VBF_PU200);
  histo.push_back(h_TowerMap6cm_VBF_PU200);

  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO 3cm");
  leg_entry.push_back("Pseudo-clust. + GEO 3cm");
  leg_entry.push_back("Pseudo-clust. + GEO 6cm");

  TLegend* leg=new TLegend(0.4,0.7,0.7,0.85);
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
  TGaxis::SetMaxDigits(4);

  histo[0]->GetXaxis()->SetTitle("First layer");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(2e-5,4*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.51,1.2*histo[0]->GetMaximum(),"CMS Simulation VBF H#rightarrow inv. #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/firstlayer_C3D_TowerMap.pdf");  


}









void plot_njets(){

  TH1F* h_NN_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_1*.root","HGCalTriggerNtuple","jets_n","1",150,0,300);
  TH1F* h_GEO_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/jet_ntuples_merged/ntuple_jet_merged_1*.root","HGCalTriggerNtuple","jets_n","1",150,0,300);
  TH1F* h_TowerMap3cm_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_3cm/jet_ntuples_merged/ntuple_jet_merged_1*.root","HGCalTriggerNtupleJet","jets_n","1",150,0,300);
  TH1F* h_TowerMap6cm_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_1*.root","HGCalTriggerNtupleJet","jets_n","1",150,0,300);


  vector<TH1F*> histo;
  histo.push_back(h_NN_VBF_PU200);
  histo.push_back(h_GEO_VBF_PU200);
  histo.push_back(h_TowerMap3cm_VBF_PU200);
  histo.push_back(h_TowerMap6cm_VBF_PU200);

  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO 3cm");
  leg_entry.push_back("Pseudo-clust. + GEO 3cm");
  leg_entry.push_back("Pseudo-clust. + GEO 6cm");

  TLegend* leg=new TLegend(0.2,0.6,0.6,0.85);
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
  TGaxis::SetMaxDigits(4);

  histo = sort_histo(histo);

  histo[0]->GetXaxis()->SetTitle("#L1 Jets");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(1.51,1.01*histo[0]->GetMaximum(),"CMS Simulation VBF H#rightarrow inv. #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/njets_TowerMap.pdf");  


}










void plot_jets_pt(){

  TH1F* h_NN_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_core_1*.root","jets","jets_raw_Luca_pt","1",40,0,200);
  TH1F* h_GEO_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_1*.root","HGCalTriggerNtuple","jets_raw_Luca_pt","1",40,0,200);
  TH1F* h_TowerMap3cm_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_3cm/jet_ntuples_merged/ntuple_jet_merged_1*.root","HGCalTriggerNtupleJet","jets_pt","1",40,0,200);
  TH1F* h_TowerMap6cm_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_1*.root","HGCalTriggerNtupleJet","jets_pt","1",40,0,200);


  vector<TH1F*> histo;
  histo.push_back(h_NN_VBF_PU200);
  histo.push_back(h_GEO_VBF_PU200);
  histo.push_back(h_TowerMap3cm_VBF_PU200);
  histo.push_back(h_TowerMap6cm_VBF_PU200);

  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO 3cm");
  leg_entry.push_back("Pseudo-clust. + GEO 3cm");
  leg_entry.push_back("Pseudo-clust. + GEO 6cm");

  TLegend* leg=new TLegend(0.4,0.6,0.8,0.85);
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
  c->SetLogy();
  TGaxis::SetMaxDigits(4);

  histo = sort_histo(histo);

  histo[0]->GetXaxis()->SetTitle("p_{T}(L1 jet)[GeV]");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(2e-6,2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(1.51,1.2*histo[0]->GetMaximum(),"CMS Simulation VBF H#rightarrow inv. #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/jets_pt_TowerMap.pdf");  


}








void plot_jets_pt_VBF(){

  TH1F* h_NN_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_core_1*.root","jets","jets_raw_Luca_pt[VBF_parton_jets]","VBF_parton_jets>-1",20,0,200);
  TH1F* h_GEO_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_1*.root","HGCalTriggerNtuple","jets_raw_Luca_pt[VBF_parton_jets]","VBF_parton_jets>-1",20,0,200);
  TH1F* h_TowerMap3cm_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_3cm/jet_ntuples_merged/ntuple_jet_merged_1*.root","HGCalTriggerNtupleJet","jets_pt[VBF_parton_jets]","VBF_parton_jets>-1",20,0,200);
  TH1F* h_TowerMap6cm_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_1*.root","HGCalTriggerNtupleJet","jets_pt[VBF_parton_jets]","VBF_parton_jets>-1",20,0,200);


  vector<TH1F*> histo;
  histo.push_back(h_NN_VBF_PU200);
  histo.push_back(h_GEO_VBF_PU200);
  histo.push_back(h_TowerMap3cm_VBF_PU200);
  histo.push_back(h_TowerMap6cm_VBF_PU200);

  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO 3cm");
  leg_entry.push_back("Pseudo-clust. + GEO 3cm");
  leg_entry.push_back("Pseudo-clust. + GEO 6cm");

  TLegend* leg=new TLegend(0.5,0.6,0.8,0.85);
  leg->SetHeader("VBF jets gen.-matched");
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
  c->SetLogy();
  TGaxis::SetMaxDigits(4);

  histo = sort_histo(histo);

  histo[0]->GetXaxis()->SetTitle("p_{T}(L1 jet)[GeV]");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(2e-4,4*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(1.51,1.2*histo[0]->GetMaximum(),"CMS Simulation VBF H#rightarrow inv. #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/jets_pt_VBF_TowerMap.pdf");  


}







void plot_eta_jets(){

  int nbins = 100;
  float min = 1.5;
  float max = 3.0;

  TH1F* h_NN_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_1.root","HGCalTriggerNtuple","abs(jets_eta)","1",nbins,min,max);
  TH1F* h_GEO_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtuple","abs(jets_eta)","1",nbins,min,max);
  TH1F* h_TowerMap3cm_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_3cm/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","abs(jets_eta)","1",nbins,min,max);
  TH1F* h_TowerMap6cm_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_3.root","HGCalTriggerNtupleJet","abs(jets_eta)","1",nbins,min,max);


  vector<TH1F*> histo;
  histo.push_back(h_NN_VBF_PU200);
  histo.push_back(h_GEO_VBF_PU200);
  histo.push_back(h_TowerMap3cm_VBF_PU200);
  histo.push_back(h_TowerMap6cm_VBF_PU200);

  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO 3cm");
  leg_entry.push_back("Pseudo-clust. + GEO 3cm");
  leg_entry.push_back("Pseudo-clust. + GEO 6cm");

  TLegend* leg=new TLegend(0.2,0.6,0.5,0.85);
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
  TGaxis::SetMaxDigits(4);

  histo[0]->GetXaxis()->SetTitle("#eta(L1 jet)");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,1.7*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.51,1.01*histo[0]->GetMaximum(),"CMS Simulation VBF H#rightarrow inv. #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/eta_jets_TowerMap.pdf");  


}










void plot_eta_jets_pt20(){

  int nbins = 100;
  float min = 1.5;
  float max = 3.0;

  TH1F* h_NN_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_1.root","HGCalTriggerNtuple","abs(jets_eta)","jets_raw_Luca_pt>20",nbins,min,max);
  TH1F* h_GEO_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_1*.root","HGCalTriggerNtuple","abs(jets_eta)","jets_raw_Luca_pt>20",nbins,min,max);
  TH1F* h_TowerMap3cm_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_3cm/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","abs(jets_eta)","jets_pt>20",nbins,min,max);
  TH1F* h_TowerMap6cm_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_3.root","HGCalTriggerNtupleJet","abs(jets_eta)","jets_pt>20",nbins,min,max);


  vector<TH1F*> histo;
  histo.push_back(h_NN_VBF_PU200);
  histo.push_back(h_GEO_VBF_PU200);
  histo.push_back(h_TowerMap3cm_VBF_PU200);
  histo.push_back(h_TowerMap6cm_VBF_PU200);

  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO 3cm");
  leg_entry.push_back("Pseudo-clust. + GEO 3cm");
  leg_entry.push_back("Pseudo-clust. + GEO 6cm");

  TLegend* leg=new TLegend(0.2,0.6,0.5,0.85);
  leg->SetHeader("Jet p_{T}(uncalib.)>20 GeV");
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
  TGaxis::SetMaxDigits(4);

  histo[0]->GetXaxis()->SetTitle("#eta(L1 jet)");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,1.7*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.51,1.01*histo[0]->GetMaximum(),"CMS Simulation VBF H#rightarrow inv. #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/eta_jets_pt20_TowerMap.pdf");  


}









void plot_profile_L1jet_response_pt_PU0_TowerMap(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  TH2F* h_PU0_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_core_*.root","jets","genjet_pt[VBF_parton_genjet]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_raw_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_raw_TowerMap_3cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_TowerMap_GEO_3cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_raw_TowerMap_6cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);


  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw);
  histo.push_back(h_PU0_raw_GEO);
  histo.push_back(h_PU0_raw_TowerMap_3cm );
  histo.push_back(h_PU0_raw_TowerMap_6cm );

  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 NN");
  leg_entry.push_back("PU=0 GEO");
  leg_entry.push_back("Pseudo-clust. + GEO 3cm");
  leg_entry.push_back("Pseudo-clust. + GEO 6cm");


  TLegend* leg=new TLegend(0.4,0.15,0.7,0.5);
  leg->SetHeader("#splitline{p_T(gen. jet)>20 GeV}{1.6<|#eta(gen.jet)|<2.9}");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  
  vector<TProfile*> prof;

  for(unsigned int i=0;i<histo.size();i++){
    TProfile* p = (TProfile*)histo[i]->ProfileX()->Clone();
    prof.push_back(p);
    prof[i]->SetLineColor(i+1);
    if(i>3)
      prof[i]->SetLineColor(i+2);
    prof[i]->SetLineWidth(2);
    leg->AddEntry(prof[i],leg_entry[i]);

  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  prof[0]->GetXaxis()->SetTitle("p_{T}(gen. jet) [GeV]");
  prof[0]->GetYaxis()->SetTitle("p_{T}(L1)/p_{T}(gen. jet)");
  prof[0]->GetYaxis()->SetTitleOffset(1.7);
  prof[0]->GetYaxis()->SetRangeUser(-0.1,1.2);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(2.,1.21,"CMS Simulation Preliminary, VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(0,1,500,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_response_pt_PU0_TowerMap.pdf");  


}





void plot_profile_L1jet_response_pt_PU0_TowerMap_cal(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  TH2F* h_PU0_cal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_cal_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","1.06*(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_cal_TowerMap_3cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_TowerMap_GEO_3cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","0.90 * (4.26744 -0.948533 * log(max(jets_pt[VBF_parton_jets],20)) + .0743854* pow(log(max(jets_pt[VBF_parton_jets],20)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);    

  TH2F* h_PU0_cal_TowerMap_6cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","0.90 * (4.26744 -0.948533 * log(max(jets_pt[VBF_parton_jets],20)) + .0743854* pow(log(max(jets_pt[VBF_parton_jets],20)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);    


  vector<TH2F*> histo;
  histo.push_back(h_PU0_cal);
  histo.push_back(h_PU0_cal_GEO);
  histo.push_back(h_PU0_cal_TowerMap_3cm );
  histo.push_back(h_PU0_cal_TowerMap_6cm );

  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 NN");
  leg_entry.push_back("PU=0 GEO");
  leg_entry.push_back("Pseudo-clust. + GEO 3cm");
  leg_entry.push_back("Pseudo-clust. + GEO 6cm");

  TLegend* leg=new TLegend(0.4,0.15,0.7,0.5);
  leg->SetHeader("#splitline{p_T(gen. jet)>20 GeV}{1.6<|#eta(gen.jet)|<2.9}");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  
  vector<TProfile*> prof;

  for(unsigned int i=0;i<histo.size();i++){
    TProfile* p = (TProfile*)histo[i]->ProfileX()->Clone();
    prof.push_back(p);
    prof[i]->SetLineColor(i+1);
    if(i>3)
      prof[i]->SetLineColor(i+2);
    prof[i]->SetLineWidth(2);
    leg->AddEntry(prof[i],leg_entry[i]);

  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  prof[0]->GetXaxis()->SetTitle("p_{T}(gen. jet) [GeV]");
  prof[0]->GetYaxis()->SetTitle("p_{T}(L1)/p_{T}(gen. jet)");
  prof[0]->GetYaxis()->SetTitleOffset(1.7);
  prof[0]->GetYaxis()->SetRangeUser(0.5,1.2);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(2.,1.21,"CMS Simulation Preliminary, VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(0,1,500,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_response_pt_PU0_TowerMap_cal.pdf");  


}










void plot_profile_L1jet_response_eta_PU0_TowerMap_cal(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  TH2F* h_PU0_cal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","abs(genjet_eta[VBF_parton_genjet])","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);

  TH2F* h_PU0_cal_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","abs(genjet_eta[VBF_parton_genjet])","1.06*(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);

  TH2F* h_PU0_cal_TowerMap_3cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_TowerMap_GEO_3cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","0.90 * (4.26744 -0.948533 * log(max(jets_pt[VBF_parton_jets],20)) + .0743854* pow(log(max(jets_pt[VBF_parton_jets],20)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);  
  

  TH2F* h_PU0_cal_TowerMap_6cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","0.90 * (4.26744 -0.948533 * log(max(jets_pt[VBF_parton_jets],20)) + .0743854* pow(log(max(jets_pt[VBF_parton_jets],20)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);    


  vector<TH2F*> histo;
  histo.push_back(h_PU0_cal);
  histo.push_back(h_PU0_cal_GEO);
  histo.push_back(h_PU0_cal_TowerMap_3cm );
  histo.push_back(h_PU0_cal_TowerMap_6cm );

  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 NN");
  leg_entry.push_back("PU=0 GEO");
  leg_entry.push_back("Pseudo-clust. + GEO 3cm");
  leg_entry.push_back("Pseudo-clust. + GEO 6cm");

  TLegend* leg=new TLegend(0.4,0.15,0.7,0.5);
  leg->SetHeader("#splitline{p_T(gen. jet)>20 GeV}{1.6<|#eta(gen.jet)|<2.9}");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  
  vector<TProfile*> prof;

  for(unsigned int i=0;i<histo.size();i++){
    TProfile* p = (TProfile*)histo[i]->ProfileX()->Clone();
    prof.push_back(p);
    prof[i]->SetLineColor(i+1);
    if(i>3)
      prof[i]->SetLineColor(i+2);
    prof[i]->SetLineWidth(2);
    leg->AddEntry(prof[i],leg_entry[i]);

  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  prof[0]->GetXaxis()->SetTitle("|#eta(gen. jet)|");
  prof[0]->GetYaxis()->SetTitle("|#eta(gen. jet)|");
  prof[0]->GetYaxis()->SetTitleOffset(1.7);
  prof[0]->GetYaxis()->SetRangeUser(0.5,1.2);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(1.62,1.21,"CMS Simulation Preliminary, VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(1.6,1,2.9,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_response_eta_PU0_TowerMap_cal.pdf");  


}






void plot_profile_L1jet_resolution_TowerMap_PU0(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  TH2F* h_PU0_cal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",18,0,360,970,0.06,2);

  TH2F* h_PU0_cal_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","1.06*(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",18,0,360,970,0.06,2);

  TH2F* h_PU0_cal_TowerMap_3cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_TowerMap_GEO_3cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","0.90 * (4.26744 -0.948533 * log(max(jets_pt[VBF_parton_jets],20)) + .0743854* pow(log(max(jets_pt[VBF_parton_jets],20)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",18,0,360,970,0.06,2);    

  TH2F* h_PU0_cal_TowerMap_6cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","0.90 * (4.26744 -0.948533 * log(max(jets_pt[VBF_parton_jets],20)) + .0743854* pow(log(max(jets_pt[VBF_parton_jets],20)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",18,0,360,970,0.06,2);    


  vector<TH2F*> histo;
  histo.push_back(h_PU0_cal);
  histo.push_back(h_PU0_cal_GEO);
  histo.push_back(h_PU0_cal_TowerMap_3cm );
  histo.push_back(h_PU0_cal_TowerMap_6cm );

  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 NN");
  leg_entry.push_back("PU=0 GEO");
  leg_entry.push_back("Pseudo-clust. + GEO 3cm");
  leg_entry.push_back("Pseudo-clust. + GEO 6cm");
 

  TLegend* leg=new TLegend(0.4,0.5,0.7,0.85);
  leg->SetHeader("#splitline{p_T(gen. jet)>20 GeV}{1.6<|#eta(gen.jet)|<2.9}");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  
  vector<TGraphErrors*> graph;

  for(unsigned int i=0;i<histo.size();i++){

    TGraphErrors* gr = new TGraphErrors();

    /*TProfile* p = (TProfile*)histo[i]->ProfileX()->Clone();
    p->BuildOptions(0,0,"s");
    for(unsigned int j=1;j<=p->GetNbinsX();j++){
      float x = p->GetBinCenter(j);
      float y = p->GetBinError(j)/p->GetBinContent(j);
      if(y>1 || p->GetBinContent(j)==0) continue;
      gr->SetPoint(j-1,x,y);
      }*/

    for(unsigned int j=1;j<=histo[i]->GetNbinsX();j++){
      TH1D* proj = histo[i]->ProjectionY("",j,j);
      //cout<<"bin "<<j<<endl;
      Double_t xq[4] = {0.25,0.5,0.75,1};
      Double_t yq[4];
      proj->GetQuantiles(4,yq,xq);
      gr->SetPoint(j-1,histo[i]->GetXaxis()->GetBinCenter(j),(yq[2]-yq[0])/yq[1]);
    }

   for(unsigned int j=0;j<gr->GetN();j++){
      double x,y;
      gr->GetPoint(j,x,y);
      if(y==0) gr->RemovePoint(j);
    }

    graph.push_back(gr);
    graph[i]->SetLineColor(i+1);    
    if(i>3)
      graph[i]->SetLineColor(i+2);
    graph[i]->SetLineWidth(2);
    graph[i]->SetFillColor(0);
    leg->AddEntry(graph[i],leg_entry[i]);

  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  graph[0]->GetXaxis()->SetTitle("p_{T}(gen) [GeV]");
  graph[0]->GetYaxis()->SetTitle("IQR / Median");
  graph[0]->GetYaxis()->SetTitleOffset(1.7);
  graph[0]->GetYaxis()->SetRangeUser(0,1.);
  graph[0]->SetTitle("");
  graph[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    graph[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.01,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV PU=0");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_resolution_pt_TowerMap_PU0.pdf");  


}










void plot_profile_L1jet_response_pt_PU200_TowerMap(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  TH2F* h_PU0_raw_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_raw_TowerMap_3cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_TowerMap_GEO_3cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);  
 
  TH2F* h_PU0_raw_TowerMap_6cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);  

   TH2F* h_PU200_raw_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU200_raw_TowerMap_3cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_3cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU200_raw_TowerMap_6cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);


  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw_dRNNC2D);
  histo.push_back(h_PU0_raw_TowerMap_3cm );
  histo.push_back(h_PU0_raw_TowerMap_6cm );
  histo.push_back(h_PU200_raw_dRNNC2D);
  histo.push_back(h_PU200_raw_TowerMap_3cm );
  histo.push_back(h_PU200_raw_TowerMap_6cm );

  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 NN+GEO");
  leg_entry.push_back("PU=0 Pseudo-clust. + GEO 3cm");
  leg_entry.push_back("PU=0 Pseudo-clust. + GEO 6cm");
  leg_entry.push_back("PU=200 NN+GEO");
  leg_entry.push_back("PU=200 Pseudo-clust. + GEO 3cm");
  leg_entry.push_back("PU=200 Pseudo-clust. + GEO 6cm");

  TLegend* leg=new TLegend(0.3,0.15,0.7,0.5);
  leg->SetHeader("#splitline{p_T(gen. jet)>20 GeV}{1.6<|#eta(gen.jet)|<2.9}");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  
  vector<TProfile*> prof;

  for(unsigned int i=0;i<histo.size();i++){
    TProfile* p = (TProfile*)histo[i]->ProfileX()->Clone();
    prof.push_back(p);
    prof[i]->SetLineColor(i+1);
    if(i>3)
      prof[i]->SetLineColor(i+2);
    prof[i]->SetLineWidth(2);
    leg->AddEntry(prof[i],leg_entry[i]);

  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  prof[0]->GetXaxis()->SetTitle("p_{T}(gen. jet) [GeV]");
  prof[0]->GetYaxis()->SetTitle("p_{T}(L1)/p_{T}(gen. jet)");
  prof[0]->GetYaxis()->SetTitleOffset(1.7);
  prof[0]->GetYaxis()->SetRangeUser(-0.1,1.2);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(2.,1.21,"CMS Simulation Preliminary, VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(0,1,500,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_response_pt_PU200_TowerMap.pdf");  


}










void plot_profile_L1jet_response_eta_PU200_TowerMap(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  TH2F* h_PU0_raw_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);

  TH2F* h_PU0_raw_TowerMap_3cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_TowerMap_GEO_3cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);   

   TH2F* h_PU0_raw_TowerMap_6cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);  
 

   TH2F* h_PU200_raw_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);

  TH2F* h_PU200_raw_TowerMap_3cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_3cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);

  TH2F* h_PU200_raw_TowerMap_6cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);


  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw_dRNNC2D);
  histo.push_back(h_PU0_raw_TowerMap_3cm );
  histo.push_back(h_PU0_raw_TowerMap_6cm );
  histo.push_back(h_PU200_raw_dRNNC2D);
  histo.push_back(h_PU200_raw_TowerMap_3cm );
  histo.push_back(h_PU200_raw_TowerMap_6cm );

  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 NN+GEO");
  leg_entry.push_back("PU=0 Pseudo-clust. + GEO 3cm");
  leg_entry.push_back("PU=0 Pseudo-clust. + GEO 6cm");
  leg_entry.push_back("PU=200 NN+GEO");
  leg_entry.push_back("PU=200 Pseudo-clust. + GEO 3cm");
  leg_entry.push_back("PU=200 Pseudo-clust. + GEO 6cm");


  TLegend* leg=new TLegend(0.3,0.15,0.7,0.5);
  leg->SetHeader("#splitline{p_T(gen. jet)>20 GeV}{1.6<|#eta(gen.jet)|<2.9}");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  
  vector<TProfile*> prof;

  for(unsigned int i=0;i<histo.size();i++){
    TProfile* p = (TProfile*)histo[i]->ProfileX()->Clone();
    prof.push_back(p);
    prof[i]->SetLineColor(i+1);
    if(i>3)
      prof[i]->SetLineColor(i+2);
    prof[i]->SetLineWidth(2);
    leg->AddEntry(prof[i],leg_entry[i]);

  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  prof[0]->GetXaxis()->SetTitle("|#eta(gen. jet)|");
  prof[0]->GetYaxis()->SetTitle("p_{T}(L1)/p_{T}(gen. jet)");
  prof[0]->GetYaxis()->SetTitleOffset(1.7);
  prof[0]->GetYaxis()->SetRangeUser(-0.7,1.5);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(1.61,1.51,"CMS Simulation Preliminary, VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(1.6,1,2.9,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_response_eta_PU200_TowerMap.pdf");  


}






void plot_profile_L1jet_response_pt_PUS_PU200_TowerMap(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  TH2F* h_PU0_raw_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_raw_TowerMap_6cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);  
 
  TH2F* h_PU200_PUS_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);


  TH2F* h_PU200_PUS_TowerMap_6cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","max(jets_pt[VBF_parton_jets]-4*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-4*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);

  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw_dRNNC2D);
  histo.push_back(h_PU0_raw_TowerMap_6cm );
  histo.push_back(h_PU200_PUS_dRNNC2D);
  histo.push_back(h_PU200_PUS_TowerMap_6cm );

  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 NN+GEO");
  leg_entry.push_back("PU=0 Pseudo-clust. + GEO 6cm");
  leg_entry.push_back("PU=200 NN+GEO + PUS");
  leg_entry.push_back("PU=200 Pseudo-clust. + GEO 6cm + PUS");


  TLegend* leg=new TLegend(0.3,0.15,0.7,0.5);
  leg->SetHeader("#splitline{p_T(gen. jet)>20 GeV}{1.6<|#eta(gen.jet)|<2.9}");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  
  vector<TProfile*> prof;

  for(unsigned int i=0;i<histo.size();i++){
    TProfile* p = (TProfile*)histo[i]->ProfileX()->Clone();
    prof.push_back(p);
    prof[i]->SetLineColor(i+1);
    if(i>3)
      prof[i]->SetLineColor(i+2);
    prof[i]->SetLineWidth(2);
    leg->AddEntry(prof[i],leg_entry[i]);

  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  prof[0]->GetXaxis()->SetTitle("p_{T}(gen. jet) [GeV]");
  prof[0]->GetYaxis()->SetTitle("p_{T}(L1)/p_{T}(gen. jet)");
  prof[0]->GetYaxis()->SetTitleOffset(1.7);
  prof[0]->GetYaxis()->SetRangeUser(-0.1,1.2);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(2.,1.21,"CMS Simulation Preliminary, VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(0,1,500,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_response_pt_PUS_PU200_TowerMap.pdf");  


}







void plot_profile_L1jet_response_eta_PUS_PU200_TowerMap(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  TH2F* h_PU0_raw_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);  

   TH2F* h_PU0_raw_TowerMap_6cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);  
 

   TH2F* h_PU200_PUS_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",13,1.6,2.9,97,0.06,2);

  TH2F* h_PU200_PUS_TowerMap_6cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","max(jets_pt[VBF_parton_jets]-4*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-4*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",13,1.6,2.9,97,0.06,2);

  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw_dRNNC2D);
  histo.push_back(h_PU0_raw_TowerMap_6cm );
  histo.push_back(h_PU200_PUS_dRNNC2D);
  histo.push_back(h_PU200_PUS_TowerMap_6cm );

  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 NN+GEO");
  leg_entry.push_back("PU=0 Pseudo-clust. + GEO 6cm");
  leg_entry.push_back("PU=200 NN+GEO + PUS");
  leg_entry.push_back("PU=200 Pseudo-clust. + GEO 6cm + PUS");



  TLegend* leg=new TLegend(0.3,0.15,0.7,0.5);
  leg->SetHeader("#splitline{p_T(gen. jet)>20 GeV}{1.6<|#eta(gen.jet)|<2.9}");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  
  vector<TProfile*> prof;

  for(unsigned int i=0;i<histo.size();i++){
    TProfile* p = (TProfile*)histo[i]->ProfileX()->Clone();
    prof.push_back(p);
    prof[i]->SetLineColor(i+1);
    if(i>3)
      prof[i]->SetLineColor(i+2);
    prof[i]->SetLineWidth(2);
    leg->AddEntry(prof[i],leg_entry[i]);

  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  prof[0]->GetXaxis()->SetTitle("|#eta(gen. jet)|");
  prof[0]->GetYaxis()->SetTitle("p_{T}(L1)/p_{T}(gen. jet)");
  prof[0]->GetYaxis()->SetTitleOffset(1.7);
  prof[0]->GetYaxis()->SetRangeUser(-0.7,1.5);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(1.61,1.51,"CMS Simulation Preliminary, VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(1.6,1,2.9,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_response_eta_PUS_PU200_TowerMap.pdf");  


}







void plot_profile_L1jet_response_pt_cal_PU0_TowerMap(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  TH2F* h_PU0_raw_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_raw_TowerMap_6cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);  
 
  TH2F* h_PU0_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_cal_TowerMap_6cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.17719 -1.03290 * log(max(jets_pt[VBF_parton_jets],0)) + 0.0872075* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);



  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw_dRNNC2D);
  histo.push_back(h_PU0_raw_TowerMap_6cm );
  histo.push_back(h_PU0_cal_dRNNC2D);
  histo.push_back(h_PU0_cal_TowerMap_6cm );

  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 NN+GEO");
  leg_entry.push_back("PU=0 Pseudo-clust. + GEO 6cm");
  leg_entry.push_back("PU=0 NN+GEO + JEC");
  leg_entry.push_back("PU=0 Pseudo-clust. + GEO 6cm + JEC");


  TLegend* leg=new TLegend(0.3,0.15,0.7,0.5);
  leg->SetHeader("#splitline{p_T(gen. jet)>20 GeV}{1.6<|#eta(gen.jet)|<2.9}");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  
  vector<TProfile*> prof;

  for(unsigned int i=0;i<histo.size();i++){
    TProfile* p = (TProfile*)histo[i]->ProfileX()->Clone();
    prof.push_back(p);
    prof[i]->SetLineColor(i+1);
    if(i>3)
      prof[i]->SetLineColor(i+2);
    prof[i]->SetLineWidth(2);
    leg->AddEntry(prof[i],leg_entry[i]);

  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  prof[0]->GetXaxis()->SetTitle("p_{T}(gen. jet) [GeV]");
  prof[0]->GetYaxis()->SetTitle("p_{T}(L1)/p_{T}(gen. jet)");
  prof[0]->GetYaxis()->SetTitleOffset(1.7);
  prof[0]->GetYaxis()->SetRangeUser(-0.1,1.2);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(2.,1.21,"CMS Simulation Preliminary, VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(0,1,500,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_response_pt_cal_PU0_TowerMap.pdf");  


}








void plot_profile_L1jet_response_pt_cal_PU200_TowerMap(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  //TH2F* h_PU0_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  //TH2F* h_PU0_cal_TowerMap_6cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.17719 -1.03290 * log(max(jets_pt[VBF_parton_jets],0)) + 0.0872075* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU200_raw_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU200_raw_TowerMap_6cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

 
  TH2F* h_PU200_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);


  TH2F* h_PU200_cal_TowerMap_6cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.17719 -1.03290 * log(max(jets_pt[VBF_parton_jets]-4*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 0.0872075* pow(log(max(jets_pt[VBF_parton_jets]-4*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-4*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-4*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);

  vector<TH2F*> histo;
  histo.push_back(h_PU200_raw_dRNNC2D);
  histo.push_back(h_PU200_raw_TowerMap_6cm );
  histo.push_back(h_PU200_cal_dRNNC2D);
  histo.push_back(h_PU200_cal_TowerMap_6cm );

  vector<TString> leg_entry;
  leg_entry.push_back("PU=200 NN+GEO");
  leg_entry.push_back("PU=200 Pseudo-clust. + GEO 6cm");
  leg_entry.push_back("PU=200 NN+GEO + PUS + JEC");
  leg_entry.push_back("#splitline{PU=200 Pseudo-clust. + GEO 6cm}{+ PUS + JEC}");


  TLegend* leg=new TLegend(0.3,0.15,0.7,0.5);
  leg->SetHeader("#splitline{p_T(gen. jet)>20 GeV}{1.6<|#eta(gen.jet)|<2.9}");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  
  vector<TProfile*> prof;

  for(unsigned int i=0;i<histo.size();i++){
    TProfile* p = (TProfile*)histo[i]->ProfileX()->Clone();
    prof.push_back(p);
    prof[i]->SetLineColor(i+1);
    if(i>3)
      prof[i]->SetLineColor(i+2);
    prof[i]->SetLineWidth(2);
    leg->AddEntry(prof[i],leg_entry[i]);

  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  prof[0]->GetXaxis()->SetTitle("p_{T}(gen. jet) [GeV]");
  prof[0]->GetYaxis()->SetTitle("p_{T}(L1)/p_{T}(gen. jet)");
  prof[0]->GetYaxis()->SetTitleOffset(1.7);
  prof[0]->GetYaxis()->SetRangeUser(-0.1,1.2);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(2.,1.21,"CMS Simulation Preliminary, VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(0,1,500,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_response_pt_cal_PU200_TowerMap.pdf");  


}









void plot_profile_L1jet_response_eta_cal_PU200_TowerMap(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";


  TH2F* h_PU200_raw_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);

  TH2F* h_PU200_raw_TowerMap_6cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);

 
  TH2F* h_PU200_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",13,1.6,2.9,97,0.06,2);


  TH2F* h_PU200_cal_TowerMap_6cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","1.06*(4.17719 -1.03290 * log(max(jets_pt[VBF_parton_jets]-4*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 0.0872075* pow(log(max(jets_pt[VBF_parton_jets]-4*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-4*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-4*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",13,1.6,2.9,97,0.06,2);

  vector<TH2F*> histo;
  histo.push_back(h_PU200_raw_dRNNC2D);
  histo.push_back(h_PU200_raw_TowerMap_6cm );
  histo.push_back(h_PU200_cal_dRNNC2D);
  histo.push_back(h_PU200_cal_TowerMap_6cm );

  vector<TString> leg_entry;
  leg_entry.push_back("PU=200 NN+GEO");
  leg_entry.push_back("PU=200 Pseudo-clust. + GEO 6cm");
  leg_entry.push_back("PU=200 NN+GEO + PUS + JEC");
  leg_entry.push_back("#splitline{PU=200 Pseudo-clust. + GEO 6cm}{+ PUS + JEC}");


  TLegend* leg=new TLegend(0.3,0.15,0.7,0.5);
  leg->SetHeader("#splitline{p_T(gen. jet)>20 GeV}{1.6<|#eta(gen.jet)|<2.9}");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  
  vector<TProfile*> prof;

  for(unsigned int i=0;i<histo.size();i++){
    TProfile* p = (TProfile*)histo[i]->ProfileX()->Clone();
    prof.push_back(p);
    prof[i]->SetLineColor(i+1);
    if(i>3)
      prof[i]->SetLineColor(i+2);
    prof[i]->SetLineWidth(2);
    leg->AddEntry(prof[i],leg_entry[i]);

  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  prof[0]->GetXaxis()->SetTitle("|#eta(gen. jet)|");
  prof[0]->GetYaxis()->SetTitle("p_{T}(L1)/p_{T}(gen. jet)");
  prof[0]->GetYaxis()->SetTitleOffset(1.7);
  prof[0]->GetYaxis()->SetRangeUser(-0.1,1.2);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(1.61,1.21,"CMS Simulation Preliminary, VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(1.6,1,2.9,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_response_eta_cal_PU200_TowerMap.pdf");  


}







void plot_profile_L1jet_resolution_TowerMap_PU200(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  TH2F* h_PU0_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_cal_TowerMap_6cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.17719 -1.03290 * log(max(jets_pt[VBF_parton_jets],0)) + 0.0872075* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

 
  TH2F* h_PU200_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);


  TH2F* h_PU200_cal_TowerMap_6cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.17719 -1.03290 * log(max(jets_pt[VBF_parton_jets]-4*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 0.0872075* pow(log(max(jets_pt[VBF_parton_jets]-4*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-4*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-4*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);


  vector<TH2F*> histo;
  histo.push_back(h_PU0_cal_dRNNC2D);
  histo.push_back(h_PU0_cal_TowerMap_6cm );
  histo.push_back(h_PU200_cal_dRNNC2D);
  histo.push_back(h_PU200_cal_TowerMap_6cm );

  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 NN + GEO + JEC");
  leg_entry.push_back("PU=0 Pseudo-clust. + GEO 6cm + JEC");
  leg_entry.push_back("PU=200 NN + GEO + JEC");
  leg_entry.push_back("PU=200 Pseudo-clust. + GEO 6cm + JEC");

  TLegend* leg=new TLegend(0.25,0.4,0.7,0.85);
  leg->SetHeader("#splitline{p_T(gen. jet)>20 GeV}{1.6<|#eta(gen.jet)|<2.9}");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  
  vector<TGraphErrors*> graph;

  for(unsigned int i=0;i<histo.size();i++){

    TGraphErrors* gr = new TGraphErrors();

    /*TProfile* p = (TProfile*)histo[i]->ProfileX()->Clone();
    p->BuildOptions(0,0,"s");
    for(unsigned int j=1;j<=p->GetNbinsX();j++){
      float x = p->GetBinCenter(j);
      float y = p->GetBinError(j)/p->GetBinContent(j);
      if(y>1 || p->GetBinContent(j)==0) continue;
      gr->SetPoint(j-1,x,y);
      }*/

    for(unsigned int j=1;j<=histo[i]->GetNbinsX();j++){
      TH1D* proj = histo[i]->ProjectionY("",j,j);
      //cout<<"bin "<<j<<endl;
      Double_t xq[4] = {0.25,0.5,0.75,1};
      Double_t yq[4];
      proj->GetQuantiles(4,yq,xq);
      gr->SetPoint(j-1,histo[i]->GetXaxis()->GetBinCenter(j),(yq[2]-yq[0])/yq[1]);
    }

   for(unsigned int j=0;j<gr->GetN();j++){
      double x,y;
      gr->GetPoint(j,x,y);
      if(y==0) gr->RemovePoint(j);
    }

    graph.push_back(gr);
    graph[i]->SetLineColor(i+1);    
    if(i>3)
      graph[i]->SetLineColor(i+2);
    graph[i]->SetLineWidth(2);
    graph[i]->SetFillColor(0);
    leg->AddEntry(graph[i],leg_entry[i]);

  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  graph[0]->GetXaxis()->SetTitle("p_{T}(gen) [GeV]");
  graph[0]->GetYaxis()->SetTitle("IQR / Median");
  graph[0]->GetYaxis()->SetTitleOffset(1.7);
  graph[0]->GetYaxis()->SetRangeUser(0,0.8);
  graph[0]->SetTitle("");
  graph[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    graph[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,0.81,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV PU=0");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_resolution_pt_TowerMap_PU200.pdf");  


}





void plot_profile_L1jet_resolution_TowerMap_PU200_eta1p6_2p4(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.4 && genjet_pt[VBF_parton_genjet]>20";

  TH2F* h_PU0_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_cal_TowerMap_6cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.17719 -1.03290 * log(max(jets_pt[VBF_parton_jets],0)) + 0.0872075* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

 
  TH2F* h_PU200_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);


  TH2F* h_PU200_cal_TowerMap_6cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.17719 -1.03290 * log(max(jets_pt[VBF_parton_jets]-4*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 0.0872075* pow(log(max(jets_pt[VBF_parton_jets]-4*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-4*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-4*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);


  vector<TH2F*> histo;
  histo.push_back(h_PU0_cal_dRNNC2D);
  histo.push_back(h_PU0_cal_TowerMap_6cm );
  histo.push_back(h_PU200_cal_dRNNC2D);
  histo.push_back(h_PU200_cal_TowerMap_6cm );

  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 NN + GEO + JEC");
  leg_entry.push_back("PU=0 Pseudo-clust. + GEO 6cm + JEC");
  leg_entry.push_back("PU=200 NN + GEO + JEC");
  leg_entry.push_back("PU=200 Pseudo-clust. + GEO 6cm + JEC");

  TLegend* leg=new TLegend(0.25,0.4,0.7,0.85);
  leg->SetHeader("#splitline{p_T(gen. jet)>20 GeV}{1.6<|#eta(gen.jet)|<2.4}");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  
  vector<TGraphErrors*> graph;

  for(unsigned int i=0;i<histo.size();i++){

    TGraphErrors* gr = new TGraphErrors();

    /*TProfile* p = (TProfile*)histo[i]->ProfileX()->Clone();
    p->BuildOptions(0,0,"s");
    for(unsigned int j=1;j<=p->GetNbinsX();j++){
      float x = p->GetBinCenter(j);
      float y = p->GetBinError(j)/p->GetBinContent(j);
      if(y>1 || p->GetBinContent(j)==0) continue;
      gr->SetPoint(j-1,x,y);
      }*/

    for(unsigned int j=1;j<=histo[i]->GetNbinsX();j++){
      TH1D* proj = histo[i]->ProjectionY("",j,j);
      //cout<<"bin "<<j<<endl;
      Double_t xq[4] = {0.25,0.5,0.75,1};
      Double_t yq[4];
      proj->GetQuantiles(4,yq,xq);
      gr->SetPoint(j-1,histo[i]->GetXaxis()->GetBinCenter(j),(yq[2]-yq[0])/yq[1]);
    }

   for(unsigned int j=0;j<gr->GetN();j++){
      double x,y;
      gr->GetPoint(j,x,y);
      if(y==0) gr->RemovePoint(j);
    }

    graph.push_back(gr);
    graph[i]->SetLineColor(i+1);    
    if(i>3)
      graph[i]->SetLineColor(i+2);
    graph[i]->SetLineWidth(2);
    graph[i]->SetFillColor(0);
    leg->AddEntry(graph[i],leg_entry[i]);

  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  graph[0]->GetXaxis()->SetTitle("p_{T}(gen) [GeV]");
  graph[0]->GetYaxis()->SetTitle("IQR / Median");
  graph[0]->GetYaxis()->SetTitleOffset(1.7);
  graph[0]->GetYaxis()->SetRangeUser(0,0.8);
  graph[0]->SetTitle("");
  graph[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    graph[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,0.81,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV PU=0");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_resolution_pt_TowerMap_PU200_eta1p6_2p4.pdf");  


}






void plot_profile_L1jet_resolution_TowerMap_PU200_eta2p4_2p9(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>2.4 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  TH2F* h_PU0_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_cal_TowerMap_6cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.17719 -1.03290 * log(max(jets_pt[VBF_parton_jets],0)) + 0.0872075* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

 
  TH2F* h_PU200_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);


  TH2F* h_PU200_cal_TowerMap_6cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.17719 -1.03290 * log(max(jets_pt[VBF_parton_jets]-4*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 0.0872075* pow(log(max(jets_pt[VBF_parton_jets]-4*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-4*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-4*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);


  vector<TH2F*> histo;
  histo.push_back(h_PU0_cal_dRNNC2D);
  histo.push_back(h_PU0_cal_TowerMap_6cm );
  histo.push_back(h_PU200_cal_dRNNC2D);
  histo.push_back(h_PU200_cal_TowerMap_6cm );

  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 NN + GEO + JEC");
  leg_entry.push_back("PU=0 Pseudo-clust. + GEO 6cm + JEC");
  leg_entry.push_back("PU=200 NN + GEO + JEC");
  leg_entry.push_back("PU=200 Pseudo-clust. + GEO 6cm + JEC");

  TLegend* leg=new TLegend(0.25,0.4,0.7,0.85);
  leg->SetHeader("#splitline{p_T(gen. jet)>20 GeV}{2.4<|#eta(gen.jet)|<2.9}");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  
  vector<TGraphErrors*> graph;

  for(unsigned int i=0;i<histo.size();i++){

    TGraphErrors* gr = new TGraphErrors();

    /*TProfile* p = (TProfile*)histo[i]->ProfileX()->Clone();
    p->BuildOptions(0,0,"s");
    for(unsigned int j=1;j<=p->GetNbinsX();j++){
      float x = p->GetBinCenter(j);
      float y = p->GetBinError(j)/p->GetBinContent(j);
      if(y>1 || p->GetBinContent(j)==0) continue;
      gr->SetPoint(j-1,x,y);
      }*/

    for(unsigned int j=1;j<=histo[i]->GetNbinsX();j++){
      TH1D* proj = histo[i]->ProjectionY("",j,j);
      //cout<<"bin "<<j<<endl;
      Double_t xq[4] = {0.25,0.5,0.75,1};
      Double_t yq[4];
      proj->GetQuantiles(4,yq,xq);
      gr->SetPoint(j-1,histo[i]->GetXaxis()->GetBinCenter(j),(yq[2]-yq[0])/yq[1]);
    }

   for(unsigned int j=0;j<gr->GetN();j++){
      double x,y;
      gr->GetPoint(j,x,y);
      if(y==0) gr->RemovePoint(j);
    }

    graph.push_back(gr);
    graph[i]->SetLineColor(i+1);    
    if(i>3)
      graph[i]->SetLineColor(i+2);
    graph[i]->SetLineWidth(2);
    graph[i]->SetFillColor(0);
    leg->AddEntry(graph[i],leg_entry[i]);

  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  graph[0]->GetXaxis()->SetTitle("p_{T}(gen) [GeV]");
  graph[0]->GetYaxis()->SetTitle("IQR / Median");
  graph[0]->GetYaxis()->SetTitleOffset(1.7);
  graph[0]->GetYaxis()->SetRangeUser(0,0.8);
  graph[0]->SetTitle("");
  graph[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    graph[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,0.81,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV PU=0");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_resolution_pt_TowerMap_PU200_eta2p4_2p9.pdf");  


}







void plot_profile_L1jet_resolution_eta_TowerMap_PU200(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  TH2F* h_PU0_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);

  TH2F* h_PU0_cal_TowerMap_6cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","1.06*(4.17719 -1.03290 * log(max(jets_pt[VBF_parton_jets],0)) + 0.0872075* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);

 
  TH2F* h_PU200_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",13,1.6,2.9,97,0.06,2);


  TH2F* h_PU200_cal_TowerMap_6cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","1.06*(4.17719 -1.03290 * log(max(jets_pt[VBF_parton_jets]-4*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 0.0872075* pow(log(max(jets_pt[VBF_parton_jets]-4*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-4*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-4*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",13,1.6,2.9,97,0.06,2);


  vector<TH2F*> histo;
  histo.push_back(h_PU0_cal_dRNNC2D);
  histo.push_back(h_PU0_cal_TowerMap_6cm );
  histo.push_back(h_PU200_cal_dRNNC2D);
  histo.push_back(h_PU200_cal_TowerMap_6cm );

  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 NN + GEO + JEC");
  leg_entry.push_back("PU=0 Pseudo-clust. + GEO 6cm + JEC");
  leg_entry.push_back("PU=200 NN + GEO + JEC");
  leg_entry.push_back("PU=200 Pseudo-clust. + GEO 6cm + JEC");

  TLegend* leg=new TLegend(0.25,0.4,0.7,0.85);
  leg->SetHeader("#splitline{p_T(gen. jet)>20 GeV}{1.6<|#eta(gen.jet)|<2.9}");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  
  vector<TGraphErrors*> graph;

  for(unsigned int i=0;i<histo.size();i++){

    TGraphErrors* gr = new TGraphErrors();

    /*TProfile* p = (TProfile*)histo[i]->ProfileX()->Clone();
    p->BuildOptions(0,0,"s");
    for(unsigned int j=1;j<=p->GetNbinsX();j++){
      float x = p->GetBinCenter(j);
      float y = p->GetBinError(j)/p->GetBinContent(j);
      if(y>1 || p->GetBinContent(j)==0) continue;
      gr->SetPoint(j-1,x,y);
      }*/

    for(unsigned int j=1;j<=histo[i]->GetNbinsX();j++){
      TH1D* proj = histo[i]->ProjectionY("",j,j);
      //cout<<"bin "<<j<<endl;
      Double_t xq[4] = {0.25,0.5,0.75,1};
      Double_t yq[4];
      proj->GetQuantiles(4,yq,xq);
      gr->SetPoint(j-1,histo[i]->GetXaxis()->GetBinCenter(j),(yq[2]-yq[0])/yq[1]);
    }

   for(unsigned int j=0;j<gr->GetN();j++){
      double x,y;
      gr->GetPoint(j,x,y);
      if(y==0) gr->RemovePoint(j);
    }

    graph.push_back(gr);
    graph[i]->SetLineColor(i+1);    
    if(i>3)
      graph[i]->SetLineColor(i+2);
    graph[i]->SetLineWidth(2);
    graph[i]->SetFillColor(0);
    leg->AddEntry(graph[i],leg_entry[i]);

  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  graph[0]->GetXaxis()->SetTitle("|#eta(gen)|");
  graph[0]->GetYaxis()->SetTitle("IQR / Median");
  graph[0]->GetYaxis()->SetTitleOffset(1.7);
  graph[0]->GetYaxis()->SetRangeUser(0,1.0);
  graph[0]->SetTitle("");
  graph[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    graph[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.01,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV PU=0");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_resolution_eta_TowerMap_PU200.pdf");  


}





void plot_turnons_L1SingleJet_TowerMap_PU0(int L1pt){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";


  double x[16]={0,25,35,40,45,50,55,60,65,75,80,90,100,120,150,300};
  int nbins=15;


  TH1F* h_PU0_denom_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU0_cal_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]) >%i",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU0_cal_dRNNC2D = new TGraphAsymmErrors();
  gr_PU0_cal_dRNNC2D->Divide(h_PU0_cal_dRNNC2D,h_PU0_denom_dRNNC2D);


  TH1F* h_PU0_denom_TowerMap = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU0_cal_TowerMap = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.17719 -1.03290 * log(max(jets_pt[VBF_parton_jets],0)) + 0.0872075* pow(log(max(jets_pt[VBF_parton_jets],0)),2)) * jets_pt[VBF_parton_jets]) >%i",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU0_cal_TowerMap = new TGraphAsymmErrors();
  gr_PU0_cal_TowerMap->Divide(h_PU0_cal_TowerMap,h_PU0_denom_TowerMap);


  vector<TGraphAsymmErrors*> turnons;
  turnons.push_back(gr_PU0_cal_dRNNC2D);
  turnons.push_back(gr_PU0_cal_TowerMap);
 
  vector<TString> leg_entry;
  leg_entry.push_back("NN + GEO");
  leg_entry.push_back("Pseudo-clust. + GEO 6cm");

  TLegend* leg=new TLegend(0.45,0.12,0.85,0.55);
  leg->SetHeader(Form("#splitline{L1_SingleJet%i}{1.6<|#eta(gen.jet)|<2.9}",L1pt));
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  
  vector<TProfile*> prof;

  for(unsigned int i=0;i<turnons.size();i++){
    turnons[i]->SetLineColor(i+1);
    if(i>3)
      turnons[i]->SetLineColor(i+2);
    turnons[i]->SetLineWidth(2);
    turnons[i]->SetFillColor(0);
    leg->AddEntry(turnons[i],leg_entry[i]);

  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  turnons[0]->GetXaxis()->SetTitle("p_{T}(gen. jet) [GeV]");
  //turnons[0]->GetXaxis()->SetLimits(0,300);
  turnons[0]->GetXaxis()->SetLimits(0,150);
  turnons[0]->GetYaxis()->SetTitle("Efficiency");
  turnons[0]->GetYaxis()->SetTitleOffset(1.7);
  turnons[0]->GetYaxis()->SetRangeUser(0.,1.);
  turnons[0]->SetTitle("");
  turnons[0]->Draw();
  for(unsigned int i=1;i<turnons.size();i++)
    turnons[i]->Draw("same");
  leg->Draw("same");
  gPad->SetGrid();
  
  TLine* line = new TLine(0,0.95,150,0.95);
  line->Draw("same");

  //TLine* line2 = new TLine(50,0.,50,1.);
  //line2->Draw("same");

  TLatex *texl = new TLatex(1.57,1.01,"CMS Simulation VBF H#rightarrowinv. PU=0 #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");
  gPad->SetTicks();


  c->SaveAs(Form("plots/turnons_L1SingleJet%i_TowerMap_PU0.pdf",L1pt));  


}







void plot_turnons_L1SingleJet_TowerMap_PU200(int L1pt){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";


  double x[16]={0,25,35,40,45,50,55,60,65,75,80,90,100,120,150,300};
  int nbins=15;


  TH1F* h_PU200_denom_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_cal_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D->Divide(h_PU200_cal_dRNNC2D,h_PU200_denom_dRNNC2D);


  TH1F* h_PU200_denom_TowerMap = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_cal_TowerMap = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.17719 -1.03290 * log(max(jets_pt[VBF_parton_jets]-4*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 0.0872075* pow(log(max(jets_pt[VBF_parton_jets]-4*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2)) * max(jets_pt[VBF_parton_jets]-4*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_TowerMap = new TGraphAsymmErrors();
  gr_PU200_cal_TowerMap->Divide(h_PU200_cal_TowerMap,h_PU200_denom_TowerMap);


  vector<TGraphAsymmErrors*> turnons;
  turnons.push_back(gr_PU200_cal_dRNNC2D);
  turnons.push_back(gr_PU200_cal_TowerMap);
 
  vector<TString> leg_entry;
  leg_entry.push_back("NN + GEO");
  leg_entry.push_back("Pseudo-clust. + GEO 6cm");

  TLegend* leg=new TLegend(0.45,0.12,0.85,0.55);
  leg->SetHeader(Form("#splitline{L1_SingleJet%i}{1.6<|#eta(gen.jet)|<2.9}",L1pt));
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  
  vector<TProfile*> prof;

  for(unsigned int i=0;i<turnons.size();i++){
    turnons[i]->SetLineColor(i+1);
    if(i>3)
      turnons[i]->SetLineColor(i+2);
    turnons[i]->SetLineWidth(2);
    turnons[i]->SetFillColor(0);
    leg->AddEntry(turnons[i],leg_entry[i]);

  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  turnons[0]->GetXaxis()->SetTitle("p_{T}(gen. jet) [GeV]");
  //turnons[0]->GetXaxis()->SetLimits(0,300);
  turnons[0]->GetXaxis()->SetLimits(0,150);
  turnons[0]->GetYaxis()->SetTitle("Efficiency");
  turnons[0]->GetYaxis()->SetTitleOffset(1.7);
  turnons[0]->GetYaxis()->SetRangeUser(0.,1.);
  turnons[0]->SetTitle("");
  turnons[0]->Draw();
  for(unsigned int i=1;i<turnons.size();i++)
    turnons[i]->Draw("same");
  leg->Draw("same");
  gPad->SetGrid();
  
  TLine* line = new TLine(0,0.95,150,0.95);
  line->Draw("same");

  //TLine* line2 = new TLine(50,0.,50,1.);
  //line2->Draw("same");

  TLatex *texl = new TLatex(1.57,1.01,"CMS Simulation VBF H#rightarrowinv. PU=200 #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");
  gPad->SetTicks();


  c->SaveAs(Form("plots/turnons_L1SingleJet%i_TowerMap_PU200.pdf",L1pt));  


}








void plot_turnons_L1SingleJet_TowerMap_PU200(int L1pt_1, int L1pt_2){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";


  //double x[16]={0,25,35,40,45,50,55,60,65,75,80,90,100,120,150,300};
  //int nbins=15;
  double x[18]={0,40,60,70,80,90,100,110,120,130,140,160,180,200,250,300,400,500};
  int nbins=17;

  TH1F* h_PU200_denom_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_cal_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i",L1pt_1),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D->Divide(h_PU200_cal_dRNNC2D,h_PU200_denom_dRNNC2D);


  TH1F* h_PU200_denom_TowerMap = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_cal_TowerMap = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.17719 -1.03290 * log(max(jets_pt[VBF_parton_jets]-4*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 0.0872075* pow(log(max(jets_pt[VBF_parton_jets]-4*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2)) * max(jets_pt[VBF_parton_jets]-4*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i",L1pt_2),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_TowerMap = new TGraphAsymmErrors();
  gr_PU200_cal_TowerMap->Divide(h_PU200_cal_TowerMap,h_PU200_denom_TowerMap);


  vector<TGraphAsymmErrors*> turnons;
  turnons.push_back(gr_PU200_cal_dRNNC2D);
  turnons.push_back(gr_PU200_cal_TowerMap);
 
  vector<TString> leg_entry;
  leg_entry.push_back(Form("NN + GEO SingleJet%i",L1pt_1));
  leg_entry.push_back(Form("#splitline{Pseudo-clust. + GEO 6cm}{SingleJet%i}",L1pt_2));

  TLegend* leg=new TLegend(0.45,0.12,0.85,0.55);
  leg->SetHeader("1.6<|#eta(gen.jet)|<2.9");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  
  vector<TProfile*> prof;

  for(unsigned int i=0;i<turnons.size();i++){
    turnons[i]->SetLineColor(i+1);
    if(i>3)
      turnons[i]->SetLineColor(i+2);
    turnons[i]->SetLineWidth(2);
    turnons[i]->SetFillColor(0);
    leg->AddEntry(turnons[i],leg_entry[i]);

  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  turnons[0]->GetXaxis()->SetTitle("p_{T}(gen. jet) [GeV]");
  turnons[0]->GetXaxis()->SetLimits(0,300);
  //turnons[0]->GetXaxis()->SetLimits(0,150);
  turnons[0]->GetYaxis()->SetTitle("Efficiency");
  turnons[0]->GetYaxis()->SetTitleOffset(1.7);
  turnons[0]->GetYaxis()->SetRangeUser(0.,1.);
  turnons[0]->SetTitle("");
  turnons[0]->Draw();
  for(unsigned int i=1;i<turnons.size();i++)
    turnons[i]->Draw("same");
  leg->Draw("same");
  gPad->SetGrid();
  
  //TLine* line = new TLine(0,0.95,150,0.95);
  TLine* line = new TLine(0,0.95,300,0.95);
  line->Draw("same");


  TLatex *texl = new TLatex(1.57,1.01,"CMS Simulation VBF H#rightarrowinv. PU=200 #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");
  gPad->SetTicks();


  c->SaveAs(Form("plots/turnons_L1SingleJet%i_%i_TowerMap_PU200.pdf",L1pt_1,L1pt_2));  


}


