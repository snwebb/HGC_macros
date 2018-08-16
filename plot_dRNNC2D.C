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

  TH1F* h_NN_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_core_1*.root","jets","Sum$(cl_calib_Luca_pt>0 && cl_cl3d>=0)","1",60,0,6000);
  TH1F* h_GEO_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_jet_ntuples/ntuple_calibr_jet_1*.root","HGCalTriggerNtuple","Sum$(cl_calib_Luca_pt>0 && cl_cl3d>=0)","1",60,0,6000);
  TH1F* h_GEO_PU200_new = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR_new/jet_ntuples_merged/ntuple_jet_merged_1*.root","HGCalTriggerNtupleJet","cl_n","1",60,0,6000);
  TH1F* h_dRNNC2D_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1*.root","HGCalTriggerNtupleJet","cl_n","1",60,0,6000);


  vector<TH1F*> histo;
  histo.push_back(h_NN_PU200);
  histo.push_back(h_GEO_PU200);
  histo.push_back(h_GEO_PU200_new);
  histo.push_back(h_dRNNC2D_PU200);


  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO 3cm");
  leg_entry.push_back("GEO 3cm new");
  leg_entry.push_back("NN + GEO 6cm");


  TLegend* leg=new TLegend(0.5,0.6,0.8,0.85);
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

  
  TLatex *texl = new TLatex(10.,0.151,"CMS Simulation #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/nC2D_dRNNC2D.pdf");  


}






void plot_HGClayer_C2D(){

  TH1F* h_NN_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_core_1.root","jets","cl_HGClayer","cl_calib_Luca_pt>0 && cl_cl3d>=0",80,0,80);
  TH1F* h_GEO_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_jet_ntuples/ntuple_calibr_jet_1.root","HGCalTriggerNtuple","cl_HGClayer","cl_calib_Luca_pt>0 && cl_cl3d>=0",80,0,80);
  TH1F* h_GEO_PU200_new = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR_new/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","cl_HGClayer","1",80,0,80);
  TH1F* h_dRNNC2D_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","cl_HGClayer","1",80,0,80);


  vector<TH1F*> histo;
  histo.push_back(h_NN_PU200);
  histo.push_back(h_GEO_PU200);
  histo.push_back(h_GEO_PU200_new);
  histo.push_back(h_dRNNC2D_PU200);


  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO 3cm");
  leg_entry.push_back("GEO 3cm new");
  leg_entry.push_back("NN + GEO 6cm");


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
  TGaxis::SetMaxDigits(4);

  histo = sort_histo(histo);

  histo[0]->GetXaxis()->SetTitle("Layer(C2D)");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.,1.02*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/HGClayer_C2D_dRNNC2D.pdf");  


}







void plot_ncells_C2D(){

  TH1F* h_NN_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_core_1.root","jets","cl_ncells","cl_calib_Luca_pt>0 && cl_cl3d>=0",20,0,20);
  TH1F* h_GEO_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_jet_ntuples/ntuple_calibr_jet_1.root","HGCalTriggerNtuple","cl_ncells","cl_calib_Luca_pt>0 && cl_cl3d>=0",20,0,20);
  TH1F* h_GEO_PU200_new = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR_new/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","cl_cells_n","1",20,0,20);
  TH1F* h_dRNNC2D_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","cl_cells_n","1",20,0,20);


  vector<TH1F*> histo;
  histo.push_back(h_NN_PU200);
  histo.push_back(h_GEO_PU200);
  histo.push_back(h_GEO_PU200_new);
  histo.push_back(h_dRNNC2D_PU200);


  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO 3cm");
  leg_entry.push_back("GEO 3cm new");
  leg_entry.push_back("NN + GEO 6cm");


  TLegend* leg=new TLegend(0.6,0.6,0.8,0.85);
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

  histo[0]->GetXaxis()->SetTitle("#TC per C2D");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(2e-5,3*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.,1.2*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/ncells_C2D_dRNNC2D.pdf");  


}





void plot_eta_mipPt_C2D(){

  TH2F* h_NN_PU200 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_core_1.root","jets","abs(cl_eta)","cl_MIPpt","cl_calib_Luca_pt>0 && cl_cl3d>=0",15,1.5,3.0,10000,0,1000);
  //TH2F* h_GEO_PU200 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_jet_ntuples/ntuple_calibr_jet_1.root","HGCalTriggerNtuple","abs(cl_eta)","cl_MIPpt","cl_calib_Luca_pt>0 && cl_cl3d>=0",15,1.5,3.0,10000,0,1000);
  //TH2F* h_GEO_PU200_new = single_plot2D("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR_new/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","abs(cl_eta)","cl_mipPt","1",15,1.5,3.0,10000,0,1000);
  TH2F* h_dRNNC2D_PU200 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","abs(cl_eta)","cl_mipPt","1",15,1.5,3.0,10000,0,1000);

  vector<TH2F*> histo;
  histo.push_back(h_NN_PU200);
  //histo.push_back(h_GEO_PU200);
  //histo.push_back(h_GEO_PU200_new);
  histo.push_back(h_dRNNC2D_PU200);

  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  //leg_entry.push_back("GEO 3cm");
  //leg_entry.push_back("GEO 3cm new");
  leg_entry.push_back("NN + GEO");


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

  
  TLatex *texl = new TLatex(1.51,100.5,"CMS Simulation #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/eta_mipPt_C2D_dRNNC2D.pdf");  


}





void plot_eta_ncells_C2D(){

  TH2F* h_NN_PU200 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_core_1.root","jets","abs(cl_eta)","cl_ncells","cl_calib_Luca_pt>0 && cl_cl3d>=0",15,1.5,3.0,1000,0,1000);
  //TH2F* h_GEO_PU200 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_jet_ntuples/ntuple_calibr_jet_1.root","HGCalTriggerNtuple","abs(cl_eta)","cl_MIPpt","cl_calib_Luca_pt>0 && cl_cl3d>=0",15,1.5,3.0,10000,0,1000);
  //TH2F* h_GEO_PU200_new = single_plot2D("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR_new/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","abs(cl_eta)","cl_mipPt","1",15,1.5,3.0,10000,0,1000);
  TH2F* h_dRNNC2D_PU200 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","abs(cl_eta)","cl_cells_n","1",15,1.5,3.0,1000,0,1000);

  vector<TH2F*> histo;
  histo.push_back(h_NN_PU200);
  //histo.push_back(h_GEO_PU200);
  //histo.push_back(h_GEO_PU200_new);
  histo.push_back(h_dRNNC2D_PU200);

  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  //leg_entry.push_back("GEO 3cm");
  //leg_entry.push_back("GEO 3cm new");
  leg_entry.push_back("NN + GEO");


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
  h_dummy->GetYaxis()->SetTitle("#TC per C2D");
  h_dummy->GetYaxis()->SetTitleOffset(1.7);
  h_dummy->GetYaxis()->SetRangeUser(0,30.);
  h_dummy->SetStats(0);
  h_dummy->SetTitle("");
  h_dummy->Draw("candlex(00000301)");
  for(unsigned int i=0;i<histo.size();i++)
    histo[i]->Draw("candlex(00000301)same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.51,31,"CMS Simulation #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/eta_ncells_C2D_dRNNC2D.pdf");  


}







void plot_eta_C2D(){

  TH1F* h_NN_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_core_1.root","jets","abs(cl_eta)","cl_calib_Luca_pt>0 && cl_cl3d>=0",60,1.5,3.0);
  TH1F* h_GEO_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_jet_ntuples/ntuple_calibr_jet_1.root","HGCalTriggerNtuple","abs(cl_eta)","cl_calib_Luca_pt>0 && cl_cl3d>=0",60,1.5,3.0);
  TH1F* h_GEO_PU200_new = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR_new/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","abs(cl_eta)","1",60,1.5,3.0);
  TH1F* h_dRNNC2D_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","abs(cl_eta)","1",60,1.5,3.0);


  vector<TH1F*> histo;
  histo.push_back(h_NN_PU200);
  histo.push_back(h_GEO_PU200);
  histo.push_back(h_GEO_PU200_new);
  histo.push_back(h_dRNNC2D_PU200);


  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO 3cm");
  leg_entry.push_back("GEO 3cm new");
  leg_entry.push_back("NN + GEO 6cm");


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
  TGaxis::SetMaxDigits(4);

  histo = sort_histo(histo);

  histo[0]->GetXaxis()->SetTitle("|#eta(C2D)|");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.51,1.02*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/eta_C2D_dRNNC2D.pdf");  


}






void plot_nC3D(){

  TH1F* h_NN_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_core_1*.root","jets","cl3d_n","1",100,0,2000);
  TH1F* h_GEO_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_jet_ntuples/ntuple_calibr_jet_1*.root","HGCalTriggerNtuple","cl3d_n","1",100,0,2000);
  TH1F* h_GEO_PU200_new = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR_new/jet_ntuples_merged/ntuple_jet_merged_1*.root","HGCalTriggerNtupleJet","cl3d_n","1",100,0,2000);
  TH1F* h_dRNNC2D_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1*.root","HGCalTriggerNtupleJet","cl3d_n","1",100,0,2000);


  vector<TH1F*> histo;
  histo.push_back(h_NN_PU200);
  histo.push_back(h_GEO_PU200);
  histo.push_back(h_GEO_PU200_new);
  histo.push_back(h_dRNNC2D_PU200);


  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO 3cm");
  leg_entry.push_back("GEO 3cm new");
  leg_entry.push_back("NN + GEO 6cm");


  TLegend* leg=new TLegend(0.5,0.6,0.8,0.85);
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
  histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(10.,1.01*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/nC3D_dRNNC2D.pdf");  


}






void plot_pt_C3D(){

  TH1F* h_NN_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_core_1.root","jets","cl3d_calib_Luca_pt","1",40,0,20);
  TH1F* h_GEO_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_jet_ntuples/ntuple_calibr_jet_1.root","HGCalTriggerNtuple","cl3d_calib_Luca_pt","1",40,0,20);
  TH1F* h_GEO_PU200_new = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR_new/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","cl3d_pt","1",40,0,20);
  TH1F* h_dRNNC2D_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","cl3d_pt","1",40,0,20);


  vector<TH1F*> histo;
  histo.push_back(h_NN_PU200);
  histo.push_back(h_GEO_PU200);
  histo.push_back(h_GEO_PU200_new);
  histo.push_back(h_dRNNC2D_PU200);


  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO 3cm");
  leg_entry.push_back("GEO 3cm new");
  leg_entry.push_back("NN + GEO 6cm");


  TLegend* leg=new TLegend(0.5,0.6,0.8,0.85);
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

  histo[0]->GetXaxis()->SetTitle("p_{T}(C3D) [GeV]");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(2e-5,1.2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.,1.01*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/pt_C3D_dRNNC2D.pdf");  


}













void plot_njets(){

  TH1F* h_NN_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_core_1*.root","jets","jets_n","1",200,100,300);
  TH1F* h_GEO_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_jet_ntuples/ntuple_calibr_jet_1*.root","HGCalTriggerNtuple","jets_n","1",200,100,300);
  TH1F* h_GEO_PU200_new = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR_new/jet_ntuples_merged/ntuple_jet_merged_1*.root","HGCalTriggerNtupleJet","jets_n","1",200,100,300);
  TH1F* h_dRNNC2D_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1*.root","HGCalTriggerNtupleJet","jets_n","1",200,100,300);


  vector<TH1F*> histo;
  histo.push_back(h_NN_PU200);
  histo.push_back(h_GEO_PU200);
  histo.push_back(h_GEO_PU200_new);
  histo.push_back(h_dRNNC2D_PU200);


  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO 3cm");
  leg_entry.push_back("GEO 3cm new");
  leg_entry.push_back("NN + GEO 6cm");


  TLegend* leg=new TLegend(0.25,0.6,0.5,0.85);
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

  histo[0]->GetXaxis()->SetTitle("#L1 jet");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(102.,1.01*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/njets_dRNNC2D.pdf");  


}










void plot_jets_pt(){

  TH1F* h_NN_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_core_1*.root","jets","jets_raw_Luca_pt","1",50,0,50);
  TH1F* h_GEO_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_jet_ntuples/ntuple_calibr_jet_1*.root","HGCalTriggerNtuple","jets_raw_Luca_pt","1",50,0,50);
  TH1F* h_GEO_PU200_new = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR_new/jet_ntuples_merged/ntuple_jet_merged_1*.root","HGCalTriggerNtupleJet","jets_pt","1",50,0,50);
  TH1F* h_dRNNC2D_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1*.root","HGCalTriggerNtupleJet","jets_pt","1",50,0,50);


  vector<TH1F*> histo;
  histo.push_back(h_NN_PU200);
  histo.push_back(h_GEO_PU200);
  histo.push_back(h_GEO_PU200_new);
  histo.push_back(h_dRNNC2D_PU200);


  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO 3cm");
  leg_entry.push_back("GEO 3cm new");
  leg_entry.push_back("NN + GEO 6cm");


  TLegend* leg=new TLegend(0.5,0.6,0.8,0.85);
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
  c->SetLogy();

  histo[0]->GetXaxis()->SetTitle("p_{T}(jet) [GeV]");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  //histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
  histo[0]->GetYaxis()->SetRangeUser(1e-5,2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(2.,1.2*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/jets_pt_dRNNC2D.pdf");  


}








void plot_eta_C3D(){

  TH1F* h_NN_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_core_1.root","jets","abs(cl3d_eta)","1",60,1.5,3.0);
  TH1F* h_GEO_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_jet_ntuples/ntuple_calibr_jet_1.root","HGCalTriggerNtuple","abs(cl3d_eta)","1",60,1.5,3.0);
  TH1F* h_GEO_PU200_new = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR_new/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","abs(cl3d_eta)","1",60,1.5,3.0);
  TH1F* h_dRNNC2D_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","abs(cl3d_eta)","1",60,1.5,3.0);


  vector<TH1F*> histo;
  histo.push_back(h_NN_PU200);
  histo.push_back(h_GEO_PU200);
  histo.push_back(h_GEO_PU200_new);
  histo.push_back(h_dRNNC2D_PU200);


  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO 3cm");
  leg_entry.push_back("GEO 3cm new");
  leg_entry.push_back("NN + GEO 6cm");


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
  TGaxis::SetMaxDigits(4);

  histo = sort_histo(histo);

  histo[0]->GetXaxis()->SetTitle("|#eta(C3D)|");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.51,1.02*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/eta_C3D_dRNNC2D.pdf");  


}







void plot_nclu_C3D(){

 int nbins = 50;
  float min = 0;
  float max = 50;

  TH1F* h_NN_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_core_1.root","jets","cl3d_nclu","1",nbins,min,max);
  TH1F* h_GEO_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_jet_ntuples/ntuple_calibr_jet_1.root","HGCalTriggerNtuple","cl3d_nclu","1",nbins,min,max);
  TH1F* h_GEO_PU200_new = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR_new/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","cl3d_clusters_n","1",nbins,min,max);
  TH1F* h_dRNNC2D_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","cl3d_clusters_n","1",nbins,min,max);


  vector<TH1F*> histo;
  histo.push_back(h_NN_PU200);
  histo.push_back(h_GEO_PU200);
  histo.push_back(h_GEO_PU200_new);
  histo.push_back(h_dRNNC2D_PU200);


  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO 3cm");
  leg_entry.push_back("GEO 3cm new");
  leg_entry.push_back("NN + GEO 6cm");


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
  TGaxis::SetMaxDigits(4);
  c->SetLogy();
  histo = sort_histo(histo);

  histo[0]->GetXaxis()->SetTitle("#C2D per C3D");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(2e-5,2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(0.02,1.2*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/nclu_C3D_dRNNC2D.pdf");  


}







void plot_eta_pt_C3D(){

  TH2F* h_NN_PU200 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_core_1.root","jets","abs(cl3d_eta)","cl3d_pt","1",15,1.5,3.0,10000,0,100);
  TH2F* h_GEO_PU200 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_jet_ntuples/ntuple_calibr_jet_1.root","HGCalTriggerNtuple","abs(cl3d_eta)","cl3d_pt","1",15,1.5,3.0,10000,0,100);
  TH2F* h_GEO_PU200_new = single_plot2D("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR_new/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","abs(cl3d_eta)","cl3d_pt","1",15,1.5,3.0,10000,0,100);
  TH2F* h_dRNNC2D_PU200 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","abs(cl3d_eta)","cl3d_pt","1",15,1.5,3.0,10000,0,100);

  vector<TH2F*> histo;
  histo.push_back(h_NN_PU200);
  histo.push_back(h_GEO_PU200);
  histo.push_back(h_GEO_PU200_new);
  histo.push_back(h_dRNNC2D_PU200);

  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO 3cm");
  leg_entry.push_back("GEO 3cm new");
  leg_entry.push_back("NN + GEO 6cm");


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
  h_dummy->GetYaxis()->SetRangeUser(0,5.);
  h_dummy->SetStats(0);
  h_dummy->SetTitle("");
  h_dummy->Draw("candlex(00000301)");
  for(unsigned int i=0;i<histo.size();i++)
    histo[i]->Draw("candlex(00000301)same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.51,100.5,"CMS Simulation #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/eta_pt_C3D_dRNNC2D.pdf");  


}












void plot_showerlength_C3D(){

 int nbins = 30;
  float min = 0;
  float max = 60;

  TH1F* h_NN_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_core_1.root","jets","cl3d_showerlength","1",nbins,min,max);
  TH1F* h_GEO_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_jet_ntuples/ntuple_calibr_jet_1.root","HGCalTriggerNtuple","cl3d_showerlength","1",nbins,min,max);
  TH1F* h_GEO_PU200_new = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR_new/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","cl3d_showerlength","1",nbins,min,max);
  TH1F* h_dRNNC2D_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","cl3d_showerlength","1",nbins,min,max);


  vector<TH1F*> histo;
  histo.push_back(h_NN_PU200);
  histo.push_back(h_GEO_PU200);
  histo.push_back(h_GEO_PU200_new);
  histo.push_back(h_dRNNC2D_PU200);


  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO 3cm");
  leg_entry.push_back("GEO 3cm new");
  leg_entry.push_back("NN + GEO 6cm");


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
  TGaxis::SetMaxDigits(4);
  histo = sort_histo(histo);

  histo[0]->GetXaxis()->SetTitle("Shower length");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(0.1,1.02*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/showerlength_C3D_dRNNC2D.pdf");  


}







void plot_firstlayer_C3D(){

  int nbins = 30;
  float min = 0;
  float max = 60;

  TH1F* h_NN_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_core_1.root","jets","cl3d_firstlayer","1",nbins,min,max);
  TH1F* h_GEO_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_jet_ntuples/ntuple_calibr_jet_1.root","HGCalTriggerNtuple","cl3d_firstlayer","1",nbins,min,max);
  TH1F* h_GEO_PU200_new = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR_new/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","cl3d_firstlayer","1",nbins,min,max);
  TH1F* h_dRNNC2D_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","cl3d_firstlayer","1",nbins,min,max);


  vector<TH1F*> histo;
  histo.push_back(h_NN_PU200);
  histo.push_back(h_GEO_PU200);
  histo.push_back(h_GEO_PU200_new);
  histo.push_back(h_dRNNC2D_PU200);


  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO 3cm");
  leg_entry.push_back("GEO 3cm new");
  leg_entry.push_back("NN + GEO 6cm");


  TLegend* leg=new TLegend(0.5,0.7,0.8,0.85);
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

  histo[0]->GetXaxis()->SetTitle("First layer");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(2e-4,2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(0.1,1.2*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/firstlayer_C3D_dRNNC2D.pdf");  


}









void plot_njets20(){

  int nbins = 15;
  float min = 0;
  float max = 15;

  TH1F* h_NN_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_core_1*.root","jets","Sum$(jets_raw_Luca_pt>20)","1",15,0,15);
  TH1F* h_GEO_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_jet_ntuples/ntuple_calibr_jet_1*.root","HGCalTriggerNtuple","Sum$(jets_raw_Luca_pt>20)","1",15,0,15);
  TH1F* h_GEO_PU200_new = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR_new/jet_ntuples_merged/ntuple_jet_merged_1*.root","HGCalTriggerNtupleJet","Sum$(jets_pt>20)","1",15,0,15);
  TH1F* h_dRNNC2D_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1*.root","HGCalTriggerNtupleJet","Sum$(jets_pt>20)","1",15,0,15);


  vector<TH1F*> histo;
  histo.push_back(h_NN_PU200);
  histo.push_back(h_GEO_PU200);
  histo.push_back(h_GEO_PU200_new);
  histo.push_back(h_dRNNC2D_PU200);


  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO 3cm");
  leg_entry.push_back("GEO 3cm new");
  leg_entry.push_back("NN + GEO 6cm");


  TLegend* leg=new TLegend(0.25,0.6,0.5,0.85);
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
  histo=sort_histo(histo);

  histo[0]->GetXaxis()->SetTitle("#L1 jet(p_T(uncal.)>20 GeV)");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(102.,1.01*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/njets20_dRNNC2D.pdf");  


}






void plot_pt_jet(){

  TH1F* h_NN_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_core_1.root","jets","jets_raw_Luca_pt","1",40,0,40);
  TH1F* h_GEO_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_jet_ntuples/ntuple_calibr_jet_1.root","HGCalTriggerNtuple","jets_raw_Luca_pt","1",40,0,40);
  TH1F* h_GEO_PU200_new = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR_new/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","jets_pt","1",40,0,40);
  TH1F* h_dRNNC2D_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","jets_pt","1",40,0,40);

  vector<TH1F*> histo;
  histo.push_back(h_NN_PU200);
  histo.push_back(h_GEO_PU200);
  histo.push_back(h_GEO_PU200_new);
  histo.push_back(h_dRNNC2D_PU200);


  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO 3cm");
  leg_entry.push_back("GEO 3cm new");
  leg_entry.push_back("NN + GEO 6cm");


  TLegend* leg=new TLegend(0.5,0.6,0.8,0.85);
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

  histo[0]->GetXaxis()->SetTitle("p_{T}(L1 jet) [GeV]");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(2e-5,2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.,1.01*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/pt_jet_dRNNC2D.pdf");  


}









void plot_eta_jet(){

  int nbins=60;
  float min=1.5;
  float max=3.0;

  TH1F* h_NN_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_core_1.root","jets","abs(jets_eta)","1",nbins,min,max);
  TH1F* h_GEO_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_jet_ntuples/ntuple_calibr_jet_1.root","HGCalTriggerNtuple","abs(jets_eta)","1",nbins,min,max);
  TH1F* h_GEO_PU200_new = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR_new/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","abs(jets_eta)","1",nbins,min,max);
  TH1F* h_dRNNC2D_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","abs(jets_eta)","1",nbins,min,max);

  vector<TH1F*> histo;
  histo.push_back(h_NN_PU200);
  histo.push_back(h_GEO_PU200);
  histo.push_back(h_GEO_PU200_new);
  histo.push_back(h_dRNNC2D_PU200);


  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO 3cm");
  leg_entry.push_back("GEO 3cm new");
  leg_entry.push_back("NN + GEO 6cm");


  TLegend* leg=new TLegend(0.5,0.6,0.8,0.85);
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

  histo[0]->GetXaxis()->SetTitle("|#eta(L1 jet)|");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.52,1.01*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/eta_jet_dRNNC2D.pdf");  


}











void plot_eta_jet20(){

  int nbins=60;
  float min=1.5;
  float max=3.0;

  TH1F* h_NN_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_core_1.root","jets","abs(jets_eta)","jets_raw_Luca_pt>20",nbins,min,max);
  TH1F* h_GEO_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_jet_ntuples/ntuple_calibr_jet_1.root","HGCalTriggerNtuple","abs(jets_eta)","jets_raw_Luca_pt>20",nbins,min,max);
  TH1F* h_GEO_PU200_new = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR_new/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","abs(jets_eta)","jets_pt>20",nbins,min,max);
  TH1F* h_dRNNC2D_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","abs(jets_eta)","jets_pt>20",nbins,min,max);

  vector<TH1F*> histo;
  histo.push_back(h_NN_PU200);
  histo.push_back(h_GEO_PU200);
  histo.push_back(h_GEO_PU200_new);
  histo.push_back(h_dRNNC2D_PU200);


  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO 3cm");
  leg_entry.push_back("GEO 3cm new");
  leg_entry.push_back("NN + GEO 6cm");


  TLegend* leg=new TLegend(0.5,0.6,0.8,0.85);
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

  histo[0]->GetXaxis()->SetTitle("|#eta(L1 jet p_{T}>20 GeV)|");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.52,1.01*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/eta_jet20_dRNNC2D.pdf");  


}











void plot_profile_L1jet_response_pt_PU0_dRNNC2D(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";


  TH2F* h_PU0_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  TH2F* h_PU0_cal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],0)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],0)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);


  TH2F* h_PU0_raw_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  TH2F* h_PU0_cal_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","1.06* (4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],0)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],0)),2) )* jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_raw_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  TH2F* h_PU0_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);


  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw);
  histo.push_back(h_PU0_raw_GEO);
  histo.push_back(h_PU0_raw_dRNNC2D);
  histo.push_back(h_PU0_cal);
  histo.push_back(h_PU0_cal_GEO);
  histo.push_back(h_PU0_cal_dRNNC2D);

  
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 NN");
  leg_entry.push_back("PU=0 GEO");
  leg_entry.push_back("PU=0 NN + GEO");
  leg_entry.push_back("PU=0 + jet calibr. NN");
  leg_entry.push_back("PU=0 + jet calibr. GEO");
  leg_entry.push_back("PU=0 + jet calibr. NN + GEO");

 

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
  prof[0]->GetYaxis()->SetRangeUser(0,1.2);
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


  c->SaveAs("plots/profile_L1jet_response_pt_PU0_dRNNC2D.pdf");  


}









void plot_profile_L1jet_response_eta_PU0_dRNNC2D(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";


  TH2F* h_PU0_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","abs(genjet_eta[VBF_parton_genjet])","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);
  TH2F* h_PU0_cal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","abs(genjet_eta[VBF_parton_genjet])","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],0)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],0)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);


  TH2F* h_PU0_raw_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","abs(genjet_eta[VBF_parton_genjet])","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);
  TH2F* h_PU0_cal_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","abs(genjet_eta[VBF_parton_genjet])","1.06* (4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],0)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],0)),2) )* jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);

  TH2F* h_PU0_raw_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);
  TH2F* h_PU0_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);


  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw);
  histo.push_back(h_PU0_raw_GEO);
  histo.push_back(h_PU0_raw_dRNNC2D);
  histo.push_back(h_PU0_cal);
  histo.push_back(h_PU0_cal_GEO);
  histo.push_back(h_PU0_cal_dRNNC2D);

  
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 NN");
  leg_entry.push_back("PU=0 GEO");
  leg_entry.push_back("PU=0 NN + GEO");
  leg_entry.push_back("PU=0 + jet calibr. NN");
  leg_entry.push_back("PU=0 + jet calibr. GEO");
  leg_entry.push_back("PU=0 + jet calibr. NN + GEO");

 

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
  prof[0]->GetYaxis()->SetTitle("p_{T}(L1)/p_{T}(gen. jet)");
  prof[0]->GetYaxis()->SetTitleOffset(1.7);
  prof[0]->GetYaxis()->SetRangeUser(-0.4,1.2);
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


  c->SaveAs("plots/profile_L1jet_response_eta_PU0_dRNNC2D.pdf");  


}
















void plot_profile_L1jet_resolution_dRNNC2D_PU0(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  TH2F* h_PU0_cal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],0)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],0)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",18,0,360,970,0.06,2);

  TH2F* h_PU0_cal_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","1.06*(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],0)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],0)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",18,0,360,970,0.06,2);


  TH2F* h_PU0_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",18,0,360,970,0.06,2);
 


  vector<TH2F*> histo;
  histo.push_back(h_PU0_cal);
  histo.push_back(h_PU0_cal_GEO);
  histo.push_back(h_PU0_cal_dRNNC2D );

  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 NN");
  leg_entry.push_back("PU=0 GEO");
  leg_entry.push_back("PU=0 NN + GEO");

 

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


  c->SaveAs("plots/profile_L1jet_resolution_pt_dRNNC2D_PU0.pdf");  


}







void plot_turnons_L1SingleJet_dRNNC2D_PU200(int L1pt){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  double x[18]={0,40,60,70,80,90,100,110,120,130,140,160,180,200,250,300,400,500};
  int nbins=17;

  //double x[16]={0,25,35,40,45,50,55,60,65,75,80,90,100,120,150,300};
  //int nbins=15;

  /*TH1F* h_PU0_denom = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU0_cal = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]",cut+Form("&& ( (4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets] )>%i",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU0_cal = new TGraphAsymmErrors();
  gr_PU0_cal->Divide(h_PU0_cal,h_PU0_denom);


  TH1F* h_PU0_denom_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU0_cal_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]) >%i",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU0_cal_dRNNC2D = new TGraphAsymmErrors();
  gr_PU0_cal_dRNNC2D->Divide(h_PU0_cal_dRNNC2D,h_PU0_denom_dRNNC2D);*/


  TH1F* h_PU200_denom = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_cal = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]",cut+Form("&& ((4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)),2) ) * max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0))>%i",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal = new TGraphAsymmErrors();
  gr_PU200_cal->Divide(h_PU200_cal,h_PU200_denom);

  TH1F* h_PU200_denom_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_cal_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D->Divide(h_PU200_cal_dRNNC2D,h_PU200_denom_dRNNC2D);

  vector<TGraphAsymmErrors*> turnons;
  /*turnons.push_back(gr_PU0_cal);
    turnons.push_back(gr_PU0_cal_dRNNC2D);*/
  turnons.push_back(gr_PU200_cal);
  turnons.push_back(gr_PU200_cal_dRNNC2D);

  vector<TString> leg_entry;
  /*leg_entry.push_back("PU=0 NN");
    leg_entry.push_back("PU=0 NN + GEO");*/
  leg_entry.push_back("NN");
  leg_entry.push_back("NN + GEO");


  TLegend* leg=new TLegend(0.5,0.12,0.85,0.55);
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
  
  TLine* line = new TLine(0,0.95,300,0.95);
  line->Draw("same");

  //TLine* line2 = new TLine(50,0.,50,1.);
  //line2->Draw("same");

  TLatex *texl = new TLatex(1.57,1.01,"CMS Simulation VBF H#rightarrowinv. PU=200 #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");
  gPad->SetTicks();


  c->SaveAs(Form("plots/turnons_L1SingleJet%i_dRNNC2D_PU200.pdf",L1pt));  


}







void plot_turnons_L1SingleJet_dRNNC2D_PU200_eta2p7(int L1pt){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  double x[18]={0,40,60,70,80,90,100,110,120,130,140,160,180,200,250,300,400,500};
  int nbins=17;

  //double x[16]={0,25,35,40,45,50,55,60,65,75,80,90,100,120,150,300};
  //int nbins=15;

  TH1F* h_PU200_denom_dRNNC2D_loweta = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut + "&& abs(genjet_eta)<2.7",nbins,x);
  TH1F* h_PU200_cal_dRNNC2D_loweta = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i",L1pt) + "&& abs(genjet_eta)<2.7",nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D_loweta = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D_loweta->Divide(h_PU200_cal_dRNNC2D_loweta,h_PU200_denom_dRNNC2D_loweta);

  TH1F* h_PU200_denom_dRNNC2D_higheta = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut + "&& abs(genjet_eta)>2.7",nbins,x);
  TH1F* h_PU200_cal_dRNNC2D_higheta = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i",L1pt) + "&& abs(genjet_eta)>2.7",nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D_higheta = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D_higheta->Divide(h_PU200_cal_dRNNC2D_higheta,h_PU200_denom_dRNNC2D_higheta);

  vector<TGraphAsymmErrors*> turnons;
  turnons.push_back(gr_PU200_cal_dRNNC2D_loweta);
  turnons.push_back(gr_PU200_cal_dRNNC2D_higheta);

  vector<TString> leg_entry;
  leg_entry.push_back("NN + GEO |#eta|<2.7");
  leg_entry.push_back("NN + GEO |#eta|>2.7");


  TLegend* leg=new TLegend(0.5,0.12,0.85,0.55);
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
  
  TLine* line = new TLine(0,0.95,300,0.95);
  line->Draw("same");

  //TLine* line2 = new TLine(50,0.,50,1.);
  //line2->Draw("same");

  TLatex *texl = new TLatex(1.57,1.01,"CMS Simulation VBF H#rightarrowinv. PU=200 #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");
  gPad->SetTicks();


  c->SaveAs(Form("plots/turnons_L1SingleJet%i_dRNNC2D_PU200_eta2p7.pdf",L1pt));  


}






void plot_profile_L1jet_response_pt_PU200_PUS_dRNNC2D(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";


  TH2F* h_PU0_raw_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU200_raw_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU200_PUS_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU200_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);


  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw_dRNNC2D);
  histo.push_back(h_PU0_cal_dRNNC2D);
  histo.push_back(h_PU200_raw_dRNNC2D);
  histo.push_back(h_PU200_PUS_dRNNC2D);
  histo.push_back(h_PU200_cal_dRNNC2D);
  
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0");
  leg_entry.push_back("PU=0 + jet calibr.");
  leg_entry.push_back("PU=200");
  leg_entry.push_back("PU=200 + PUS");
  leg_entry.push_back("PU=200 + PUS + jet calibr.");

 

  TLegend* leg=new TLegend(0.4,0.15,0.7,0.5);
  leg->SetHeader("#splitline{p_{T}(gen. jet)>20 GeV}{1.6<|#eta(gen.jet)|<2.9}");
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
  prof[0]->GetYaxis()->SetRangeUser(0,1.2);
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


  c->SaveAs("plots/profile_L1jet_response_pt_PU200_PUS_dRNNC2D.pdf");  


}










void plot_layer_jets_energy_fraction_pt(){


  TH2F* h_VBF_layer4 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","jets_pt[VBF_parton_jets]","layer_jets_energy_fraction[4][VBF_parton_jets]","VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20",15,0,150,10000,0,1);
  TH2F* h_tau_layer4 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","jets_pt[gentau_jets]","layer_jets_energy_fraction[4][gentau_jets]","gentau_jets>=0 && abs(gentau_vis_eta)>1.6 && abs(gentau_vis_eta)<2.9 && gentau_vis_pt>20 && gentau_decayMode>=0 && gentau_decayMode<=5",15,0,150,10000,0,1);
  TH2F* h_ZB_layer4 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","jets_pt","layer_jets_energy_fraction[4]","1",15,0,150,10000,0,1);

  TH2F* h_VBF_layer10 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","jets_pt[VBF_parton_jets]","layer_jets_energy_fraction[10][VBF_parton_jets]","VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20",15,0,150,10000,0,1);
  TH2F* h_tau_layer10 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","jets_pt[gentau_jets]","layer_jets_energy_fraction[10][gentau_jets]","gentau_jets>=0 && abs(gentau_vis_eta)>1.6 && abs(gentau_vis_eta)<2.9 && gentau_vis_pt>20 && gentau_decayMode>=0 && gentau_decayMode<=5",15,0,150,10000,0,1);
  TH2F* h_ZB_layer10 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","jets_pt","layer_jets_energy_fraction[10]","1",15,0,150,10000,0,1);

  vector<TH2F*> histo;
  histo.push_back(h_VBF_layer4);
  histo.push_back(h_tau_layer4);
  histo.push_back(h_ZB_layer4);
  histo.push_back(h_VBF_layer10);
  histo.push_back(h_tau_layer10);
  histo.push_back(h_ZB_layer10);

  vector<TString> leg_entry;
  leg_entry.push_back("VBF PU=200 layer 4");
  leg_entry.push_back("#tau_{h} PU=200 layer 4");
  leg_entry.push_back("ZB PU=200 layer 4");
  leg_entry.push_back("VBF PU=200 layer 10");
  leg_entry.push_back("#tau_{h} PU=200 layer 10");
  leg_entry.push_back("ZB PU=200 layer 10");


  TLegend* leg=new TLegend(0.5,0.5,0.8,0.8);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  for(unsigned int i=0;i<histo.size();i++){

    TH2F* h = histo[i];
    h->SetMarkerSize(1.5);
    h->SetMarkerColor(i+1);
    h->SetLineColor(i+1);
    h->SetFillColor(i+1);
    if(i>3){
      h->SetMarkerColor(i+2);
      h->SetLineColor(i+2);
      h->SetFillColor(i+2);
    }
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


  TH2F* h_dummy = new TH2F("","",16,0,160.,1000,0,1); 
  h_dummy->GetXaxis()->SetTitle("p_{T} [GeV]");
  h_dummy->GetYaxis()->SetTitle("Energy fraction");
  h_dummy->GetYaxis()->SetTitleOffset(1.7);
  h_dummy->GetYaxis()->SetRangeUser(0,1.);
  h_dummy->SetStats(0);
  h_dummy->SetTitle("");
  h_dummy->Draw("candlex(00000301)");
  for(unsigned int i=0;i<histo.size();i++)
    histo[i]->Draw("candlex(00000301)same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(2.,1.02,"CMS Simulation #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/layer_jets_energy_fraction_pt_dRNNC2D.pdf");  


}







void plot_profile_L1jet_resolution_dRNNC2D_PU200(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  TH2F* h_PU0_cal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],0)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],0)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",18,0,360,970,0.06,2);

  TH2F* h_PU200_cal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)),2) ) * max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets])>0",18,0,360,970,0.06,2);


  TH2F* h_PU0_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",18,0,360,970,0.06,2);
 
  TH2F* h_PU200_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",18,0,360,970,0.06,2);
 


  vector<TH2F*> histo;
  histo.push_back(h_PU0_cal);
  histo.push_back(h_PU200_cal);
  histo.push_back(h_PU0_cal_dRNNC2D );
  histo.push_back(h_PU200_cal_dRNNC2D );

  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 NN");
  leg_entry.push_back("PU=200 NN");
  leg_entry.push_back("PU=0 NN + GEO");
  leg_entry.push_back("PU=200 NN + GEO");

 
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

  TLatex *texl = new TLatex(0.01,1.02,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_resolution_pt_dRNNC2D_PU200.pdf");  


}








void plot_turnons_L1SingleJet_NN_dRNNC2D_PU200(int L1pt_NN, int L1pt_dRNNC2D){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  double x[18]={0,40,60,70,80,90,100,110,120,130,140,160,180,200,250,300,400,500};
  int nbins=17;

  //double x[15]={0,25,35,40,45,50,55,60,65,75,80,90,100,120,150};
  //int nbins=14;


  TH1F* h_PU200_denom = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_cal = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]",cut+Form("&& ((4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)),2) ) * max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0))>%i",L1pt_NN),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal = new TGraphAsymmErrors();
  gr_PU200_cal->Divide(h_PU200_cal,h_PU200_denom);


  TH1F* h_PU200_denom_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_cal_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i",L1pt_dRNNC2D),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D->Divide(h_PU200_cal_dRNNC2D,h_PU200_denom_dRNNC2D);





  vector<TGraphAsymmErrors*> turnons;
  turnons.push_back(gr_PU200_cal);
  turnons.push_back(gr_PU200_cal_dRNNC2D);

  vector<TString> leg_entry;
  leg_entry.push_back(Form("NN SingleJet%i",L1pt_NN));
  leg_entry.push_back(Form("NN + GEO SingleJet%i",L1pt_dRNNC2D));

  TLegend* leg=new TLegend(0.5,0.12,0.85,0.55);
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
  
  TLine* line = new TLine(0,0.95,300,0.95);
  line->Draw("same");

  //TLine* line2 = new TLine(50,0.,50,1.);
  //line2->Draw("same");

  TLatex *texl = new TLatex(1.57,1.01,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV PU200");
  texl->SetTextSize(0.03);
  texl->Draw("same");
  gPad->SetTicks();


  c->SaveAs(Form("plots/turnons_L1SingleJet%i_NN_SingleJet%i_dRNNC2D_PU200.pdf",L1pt_NN,L1pt_dRNNC2D));  


}









void plot_turnons_L1SingleJet_NN_dRNNC2D_PU200_low(int L1pt_NN, int L1pt_dRNNC2D){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  double x[15]={0,25,35,40,45,50,55,60,65,75,80,90,100,120,150};
  int nbins=14;


  TH1F* h_PU200_denom = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_cal = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]",cut+Form("&& ((4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)),2) ) * max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0))>%i",L1pt_NN),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal = new TGraphAsymmErrors();
  gr_PU200_cal->Divide(h_PU200_cal,h_PU200_denom);


  TH1F* h_PU200_denom_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_cal_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i",L1pt_dRNNC2D),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D->Divide(h_PU200_cal_dRNNC2D,h_PU200_denom_dRNNC2D);





  vector<TGraphAsymmErrors*> turnons;
  turnons.push_back(gr_PU200_cal);
  turnons.push_back(gr_PU200_cal_dRNNC2D);

  vector<TString> leg_entry;
  leg_entry.push_back(Form("NN SingleJet%i",L1pt_NN));
  leg_entry.push_back(Form("NN + GEO SingleJet%i",L1pt_dRNNC2D));

  TLegend* leg=new TLegend(0.5,0.12,0.85,0.55);
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

  TLatex *texl = new TLatex(1.57,1.01,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV PU200");
  texl->SetTextSize(0.03);
  texl->Draw("same");
  gPad->SetTicks();


  c->SaveAs(Form("plots/turnons_L1SingleJet%i_NN_SingleJet%i_dRNNC2D_PU200.pdf",L1pt_NN,L1pt_dRNNC2D));  


}










void plot_profile_L1jet_response_eta_PU200_PUS_dRNNC2D(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";


  TH2F* h_PU0_raw_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);

  TH2F* h_PU200_PUS_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",13,1.6,2.9,97,0.06,2);

  TH2F* h_PU0_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);

  TH2F* h_PU200_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",13,1.6,2.9,97,0.06,2);


  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw_dRNNC2D);
  histo.push_back(h_PU0_cal_dRNNC2D);
  histo.push_back(h_PU200_PUS_dRNNC2D);
  histo.push_back(h_PU200_cal_dRNNC2D);
  
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0");
  leg_entry.push_back("PU=0 + jet calibr.");
  leg_entry.push_back("PU=200 + PUS");
  leg_entry.push_back("PU=200 + PUS + jet calibr.");

 

  TLegend* leg=new TLegend(0.4,0.15,0.7,0.5);
  leg->SetHeader("#splitline{p_{T}(gen. jet)>20 GeV}{1.6<|#eta(gen.jet)|<2.9}");
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
  prof[0]->GetYaxis()->SetRangeUser(-1,1.2);
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


  c->SaveAs("plots/profile_L1jet_response_eta_PU200_PUS_dRNNC2D.pdf");  


}








void plot_eta_leadjet(){

  int nbins=60;
  float min=1.5;
  float max=3.0;

  TH1F* h_dRNNC2D_PU200_noJEC = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","abs(jets_eta)","jets_pt==Max$(jets_pt)",nbins,min,max);
  TH1F* h_dRNNC2D_PU200_JECPUS = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","abs(jets_eta)","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)) + 1.02929e-01* pow(log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)==Max$(1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)) + 1.02929e-01* pow(log(max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0)),2) ) * max(jets_pt-2*jets_PU_subtr_cone_GEO_C3D,0))",nbins,min,max);

  vector<TH1F*> histo;
  histo.push_back(h_dRNNC2D_PU200_noJEC);
  histo.push_back(h_dRNNC2D_PU200_JECPUS);

  vector<TString> leg_entry;
  leg_entry.push_back("NN + GEO no PUS, no jet calibr.");
  leg_entry.push_back("NN + GEO PUS + jet calibr.");


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

  histo[0]->GetXaxis()->SetTitle("|#eta(leading L1 jet)|");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.52,1.01*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/eta_lead_jet_dRNNC2D.pdf");  


}







void plot_turnons_L1SingleJet_dRNNC2D_PU0_PU200(int L1pt){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  double x[21]={0,20,40,60,80,100,110,120,130,140,150,160,170,180,190,200,220,250,300,400,500};
  int nbins=20;

  //double x[16]={0,25,35,40,45,50,55,60,65,75,80,90,100,120,150,300};
  //int nbins=15;


  TH1F* h_PU0_denom_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU0_cal_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]) >%i",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU0_cal_dRNNC2D = new TGraphAsymmErrors();
  gr_PU0_cal_dRNNC2D->Divide(h_PU0_cal_dRNNC2D,h_PU0_denom_dRNNC2D);


  TH1F* h_PU200_denom_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_cal_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D->Divide(h_PU200_cal_dRNNC2D,h_PU200_denom_dRNNC2D);

  vector<TGraphAsymmErrors*> turnons;
  turnons.push_back(gr_PU0_cal_dRNNC2D);
  turnons.push_back(gr_PU200_cal_dRNNC2D);

  vector<TString> leg_entry;
  leg_entry.push_back("PU=0");
  leg_entry.push_back("PU=200");


  TLegend* leg=new TLegend(0.5,0.2,0.8,0.55);
  leg->SetHeader(Form("#splitline{p_{T}(L1 jet)>%i GeV}{1.6<|#eta(gen.jet)|<2.9}",L1pt));
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
  turnons[0]->GetXaxis()->SetLimits(0,400);
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
  
  TLine* line = new TLine(0,0.95,400,0.95);
  line->Draw("same");

  //TLine* line2 = new TLine(50,0.,50,1.);
  //line2->Draw("same");

  TLatex *texl = new TLatex(1.57,1.01,"CMS Simulation Preliminary VBF H#rightarrowinv., #sqrt{s}=14 TeV, PU=200");
  texl->SetTextSize(0.028);
  texl->Draw("same");
  gPad->SetTicks();


  c->SaveAs(Form("plots/turnons_L1SingleJet%i_dRNNC2D_PU0_PU200.pdf",L1pt));  


}




