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



void plot_ele_cone(){

  TString filename = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_C3D_cone.root";

  TH1F* h_C3D = single_plot(filename,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]","gen_cl3d>=0",120,0.,60.);
  TH1F* h_SC_C3D_0p1 = single_plot(filename,"HGCalTriggerNtuple","gen_SC_C3D_0p1_pt","",120,0.,60.);
  TH1F* h_SC_C3D_0p3 = single_plot(filename,"HGCalTriggerNtuple","gen_SC_C3D_0p3_pt","",120,0.,60.);

   vector<TH1F*> histo;
   histo.push_back(h_C3D);
   histo.push_back(h_SC_C3D_0p1);
   histo.push_back(h_SC_C3D_0p3);

   vector<TString> leg_entry;
   leg_entry.push_back("Highest-p_{T} C3D #DeltaR=0.3");
   leg_entry.push_back("Gen. SC #DeltaR=0.1");
   leg_entry.push_back("Gen. SC #DeltaR=0.3.");

   TLegend* leg=new TLegend(0.45,0.65,0.75,0.85);
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
   
   histo = sort_histo(histo);
   
   histo[0]->GetXaxis()->SetTitle("p_{T}(C3D) [GeV]");
   histo[0]->GetYaxis()->SetTitle("a. u.");
   histo[0]->GetYaxis()->SetTitleOffset(1.7);
   histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
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
   
   
   c->SaveAs("plots/C3D_ele_SC.pdf");  




}








void plot_pi_cone(){

  TString filename = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_C3D_cone.root";

  TH1F* h_C3D = single_plot(filename,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]","gen_cl3d>=0",120,0.,60.);
  TH1F* h_SC_C3D_0p1 = single_plot(filename,"HGCalTriggerNtuple","gen_SC_C3D_0p1_pt","",120,0.,60.);
  TH1F* h_SC_C3D_0p3 = single_plot(filename,"HGCalTriggerNtuple","gen_SC_C3D_0p3_pt","",120,0.,60.);

   vector<TH1F*> histo;
   histo.push_back(h_C3D);
   histo.push_back(h_SC_C3D_0p1);
   histo.push_back(h_SC_C3D_0p3);

   vector<TString> leg_entry;
   leg_entry.push_back("Highest-p_{T} C3D #DeltaR=0.3");
   leg_entry.push_back("Gen. SC #DeltaR=0.1");
   leg_entry.push_back("Gen. SC #DeltaR=0.3.");

   TLegend* leg=new TLegend(0.45,0.65,0.75,0.85);
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
   histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
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
   
   
   c->SaveAs("plots/C3D_pi_SC.pdf");  




}









void plot_ele_cone_rescaled(){

  TString filename = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_C3D_cone.root";

  TH1F* h_C3D_0 = single_plot(filename,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]","gen_cl3d>=0",120,0.,60.);
  TH1F* h_SC_C3D_0p1_0 = single_plot(filename,"HGCalTriggerNtuple","gen_SC_C3D_0p1_pt","",120,0.,60.);
  TH1F* h_SC_C3D_0p3_0 = single_plot(filename,"HGCalTriggerNtuple","gen_SC_C3D_0p3_pt","",120,0.,60.);

  TH1F* h_C3D = single_plot(filename,"HGCalTriggerNtuple",Form("%f*cl3d_pt[gen_cl3d]",25./h_C3D_0->GetBinCenter(h_C3D_0->GetMaximumBin())),"gen_cl3d>=0",120,0.,60.);
  TH1F* h_SC_C3D_0p1 = single_plot(filename,"HGCalTriggerNtuple",Form("%f*gen_SC_C3D_0p1_pt",25./h_SC_C3D_0p1_0->GetBinCenter(h_SC_C3D_0p1_0->GetMaximumBin())),"",120,0.,60.);
  TH1F* h_SC_C3D_0p3 = single_plot(filename,"HGCalTriggerNtuple",Form("%f*gen_SC_C3D_0p3_pt",25./h_SC_C3D_0p3_0->GetBinCenter(h_SC_C3D_0p3_0->GetMaximumBin())),"",120,0.,60.);

   vector<TH1F*> histo;
   histo.push_back(h_C3D);
   histo.push_back(h_SC_C3D_0p1);
   histo.push_back(h_SC_C3D_0p3);

   vector<TString> leg_entry;
   leg_entry.push_back("Highest-p_{T} C3D #DeltaR=0.3");
   leg_entry.push_back("Gen. SC #DeltaR=0.1");
   leg_entry.push_back("Gen. SC #DeltaR=0.3.");

   TLegend* leg=new TLegend(0.47,0.65,0.75,0.85);
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
   
   histo = sort_histo(histo);
   
   histo[0]->GetXaxis()->SetTitle("p_{T}(C3D) [GeV]");
   histo[0]->GetYaxis()->SetTitle("a. u.");
   histo[0]->GetYaxis()->SetTitleOffset(1.7);
   histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
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
   
   
   c->SaveAs("plots/C3D_ele_SC_rescaled.pdf");  




}








void plot_pi_cone_rescaled(){

  TString filename = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_C3D_cone.root";

  TH1F* h_C3D_0 = single_plot(filename,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]","gen_cl3d>=0",120,0.,60.);
  TH1F* h_SC_C3D_0p1_0 = single_plot(filename,"HGCalTriggerNtuple","gen_SC_C3D_0p1_pt","gen_SC_C3D_0p1_pt>0",120,0.,60.);
  TH1F* h_SC_C3D_0p3_0 = single_plot(filename,"HGCalTriggerNtuple","gen_SC_C3D_0p3_pt","gen_SC_C3D_0p3_pt>0",120,0.,60.);

  TH1F* h_C3D = single_plot(filename,"HGCalTriggerNtuple",Form("%f*cl3d_pt[gen_cl3d]",25./h_C3D_0->GetBinCenter(h_C3D_0->GetMaximumBin())),"gen_cl3d>=0",120,0.,60.);
  TH1F* h_SC_C3D_0p1 = single_plot(filename,"HGCalTriggerNtuple",Form("%f*gen_SC_C3D_0p1_pt",25./h_SC_C3D_0p1_0->GetBinCenter(h_SC_C3D_0p1_0->GetMaximumBin())),"",120,0.,60.);
  TH1F* h_SC_C3D_0p3 = single_plot(filename,"HGCalTriggerNtuple",Form("%f*gen_SC_C3D_0p3_pt",25./h_SC_C3D_0p3_0->GetBinCenter(h_SC_C3D_0p3_0->GetMaximumBin())),"",120,0.,60.);


   vector<TH1F*> histo;
   histo.push_back(h_C3D);
   histo.push_back(h_SC_C3D_0p1);
   histo.push_back(h_SC_C3D_0p3);

   vector<TString> leg_entry;
   leg_entry.push_back("Highest-p_{T} C3D #DeltaR=0.3");
   leg_entry.push_back("Gen. SC #DeltaR=0.1");
   leg_entry.push_back("Gen. SC #DeltaR=0.3.");

   TLegend* leg=new TLegend(0.52,0.65,0.75,0.85);
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
   histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
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
   
   
   c->SaveAs("plots/C3D_pi_SC_rescaled.pdf");  




}







void plot_ele_nC3D_nC2D(){

  TString filename_cone = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_C3D_cone.root";
  TString filename_histo_0p01 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_C3D_polarHisto.root";
  TString filename_histo_0p03 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_C3D_polarHisto_dR0p03.root";

  TH1F* h_cone = single_plot(filename_cone,"HGCalTriggerNtuple","cl3d_clusters_n","",60,0.,60.);
  TH1F* h_histo_0p01 = single_plot(filename_histo_0p01,"HGCalTriggerNtuple","cl3d_clusters_n","",60,0.,60.);
  TH1F* h_histo_0p03 = single_plot(filename_histo_0p03,"HGCalTriggerNtuple","cl3d_clusters_n","",60,0.,60.);
  TH1F* h_cone_gen = single_plot(filename_cone,"HGCalTriggerNtuple","cl3d_clusters_n[gen_cl3d]","gen_cl3d>=0",60,0.,60.);
  TH1F* h_histo_0p01_gen = single_plot(filename_histo_0p01,"HGCalTriggerNtuple","cl3d_clusters_n[gen_cl3d]","gen_cl3d>=0",60,0.,60.);
  TH1F* h_histo_0p03_gen = single_plot(filename_histo_0p03,"HGCalTriggerNtuple","cl3d_clusters_n[gen_cl3d]","gen_cl3d>=0",60,0.,60.);

   vector<TH1F*> histo;
   histo.push_back(h_cone);
   histo.push_back(h_histo_0p01);
   histo.push_back(h_histo_0p03);
   histo.push_back(h_cone_gen);
   histo.push_back(h_histo_0p01_gen);
   histo.push_back(h_histo_0p03_gen);

   vector<TString> leg_entry;
   leg_entry.push_back("Cone dR=0.01 incl.");
   leg_entry.push_back("Histo dR=0.01 incl.");
   leg_entry.push_back("Histo dR=0.03 incl.");
   leg_entry.push_back("Cone dR=0.01 gen.");
   leg_entry.push_back("Histo dR=0.01 gen.");
   leg_entry.push_back("Histo dR=0.03 gen.");

   TLegend* leg=new TLegend(0.45,0.6,0.75,0.85);
   leg->SetHeader("Electron gun p_{T}=25 GeV PU=0");
   leg->SetFillColor(0);
   leg->SetBorderSize(0);
   leg->SetTextSize(0.03);
  
   for(unsigned int i=0;i<histo.size();i++){
     TH1F* h = histo[i];
     //h->Scale(1/h->Integral());
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
   
   histo[0]->GetXaxis()->SetTitle("#C2D per C3D");
   histo[0]->GetYaxis()->SetTitle("#C3D");
   histo[0]->GetYaxis()->SetTitleOffset(1.7);
   histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
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
   
   
   c->SaveAs("plots/C3D_ele_C3D_nC2D.pdf");  




}





void plot_pi_nC3D_nC2D(){

  TString filename_cone = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_C3D_cone.root";
  TString filename_histo_0p01 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_C3D_polarHisto.root";
  TString filename_histo_0p03 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_C3D_polarHisto_dR0p03.root";


  TH1F* h_cone = single_plot(filename_cone,"HGCalTriggerNtuple","cl3d_clusters_n","",60,0.,60.);
  TH1F* h_histo_0p01 = single_plot(filename_histo_0p01,"HGCalTriggerNtuple","cl3d_clusters_n","",60,0.,60.);
  TH1F* h_histo_0p03 = single_plot(filename_histo_0p03,"HGCalTriggerNtuple","cl3d_clusters_n","",60,0.,60.);
  TH1F* h_cone_gen = single_plot(filename_cone,"HGCalTriggerNtuple","cl3d_clusters_n[gen_cl3d]","gen_cl3d>=0",60,0.,60.);
  TH1F* h_histo_0p01_gen = single_plot(filename_histo_0p01,"HGCalTriggerNtuple","cl3d_clusters_n[gen_cl3d]","gen_cl3d>=0",60,0.,60.);
  TH1F* h_histo_0p03_gen = single_plot(filename_histo_0p03,"HGCalTriggerNtuple","cl3d_clusters_n[gen_cl3d]","gen_cl3d>=0",60,0.,60.);

   vector<TH1F*> histo;
   histo.push_back(h_cone);
   histo.push_back(h_histo_0p01);
   histo.push_back(h_histo_0p03);
   histo.push_back(h_cone_gen);
   histo.push_back(h_histo_0p01_gen);
   histo.push_back(h_histo_0p03_gen);

   vector<TString> leg_entry;
   leg_entry.push_back("Cone dR=0.01 incl.");
   leg_entry.push_back("Histo dR=0.01 incl.");
   leg_entry.push_back("Histo dR=0.03 incl.");
   leg_entry.push_back("Cone dR=0.01 gen.");
   leg_entry.push_back("Histo dR=0.01 gen.");
   leg_entry.push_back("Histo dR=0.03 gen.");


   TLegend* leg=new TLegend(0.45,0.6,0.75,0.85);
   leg->SetHeader("Pion gun p_{T}=25 GeV PU=0");
   leg->SetFillColor(0);
   leg->SetBorderSize(0);
   leg->SetTextSize(0.03);
  
   for(unsigned int i=0;i<histo.size();i++){
     TH1F* h = histo[i];
     //h->Scale(1/h->Integral());
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
   
   histo[0]->GetXaxis()->SetTitle("#C2D per C3D");
   histo[0]->GetYaxis()->SetTitle("#C3D");
   histo[0]->GetYaxis()->SetTitleOffset(1.7);
   //histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
   histo[0]->SetMaximum(2*histo[0]->GetMaximum());
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
   
   
   c->SaveAs("plots/C3D_pi_C3D_nC2D.pdf");  




}







void plot_ele_nC3D_nC2D_PU200(){

  TString filename_cone = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_PU200_C3D_cone.root";
  TString filename_histo_0p01 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_PU200_C3D_polarHisto.root";
  TString filename_histo_0p03 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_PU200_C3D_polarHisto_dR0p03.root";

 TH1F* h_cone = single_plot(filename_cone,"HGCalTriggerNtuple","cl3d_clusters_n","",60,0.,60.);
  TH1F* h_histo_0p01 = single_plot(filename_histo_0p01,"HGCalTriggerNtuple","cl3d_clusters_n","",60,0.,60.);
  TH1F* h_histo_0p03 = single_plot(filename_histo_0p03,"HGCalTriggerNtuple","cl3d_clusters_n","",60,0.,60.);
  TH1F* h_cone_gen = single_plot(filename_cone,"HGCalTriggerNtuple","cl3d_clusters_n[gen_cl3d]","gen_cl3d>=0",60,0.,60.);
  TH1F* h_histo_0p01_gen = single_plot(filename_histo_0p01,"HGCalTriggerNtuple","cl3d_clusters_n[gen_cl3d]","gen_cl3d>=0",60,0.,60.);
  TH1F* h_histo_0p03_gen = single_plot(filename_histo_0p03,"HGCalTriggerNtuple","cl3d_clusters_n[gen_cl3d]","gen_cl3d>=0",60,0.,60.);

   vector<TH1F*> histo;
   histo.push_back(h_cone);
   histo.push_back(h_histo_0p01);
   histo.push_back(h_histo_0p03);
   histo.push_back(h_cone_gen);
   histo.push_back(h_histo_0p01_gen);
   histo.push_back(h_histo_0p03_gen);

   vector<TString> leg_entry;
   leg_entry.push_back("Cone dR=0.01 incl.");
   leg_entry.push_back("Histo dR=0.01 incl.");
   leg_entry.push_back("Histo dR=0.03 incl.");
   leg_entry.push_back("Cone dR=0.01 gen. (x1000)");
   leg_entry.push_back("Histo dR=0.01 gen. (x1000)");
   leg_entry.push_back("Histo dR=0.03 gen. (x1000)");


   TLegend* leg=new TLegend(0.45,0.6,0.75,0.85);
   leg->SetHeader("Electron gun p_{T}=25 GeV PU=200");
   leg->SetFillColor(0);
   leg->SetBorderSize(0);
   leg->SetTextSize(0.03);
  
   for(unsigned int i=0;i<histo.size();i++){
     TH1F* h = histo[i];
     //h->Scale(1/h->Integral());
     if(i>2)
       h->Scale(1000);
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
   
   histo[0]->GetXaxis()->SetTitle("#C2D per C3D");
   histo[0]->GetYaxis()->SetTitle("#C3D");
   histo[0]->GetYaxis()->SetTitleOffset(1.7);
   histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
   //histo[0]->SetMaximum(2*histo[0]->GetMaximum());
   histo[0]->SetStats(0);
   histo[0]->SetTitle("");
   histo[0]->Draw();
   
   for(unsigned int i=1;i<histo.size();i++)
     histo[i]->Draw("same");
   leg->Draw("same");
   
   
   TLatex *texl = new TLatex(0.01,1.02*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV, PU=200");
   texl->SetTextSize(0.03);
   texl->Draw("same");
   
   gPad->SetTicks();
   
   
   c->SaveAs("plots/C3D_ele_C3D_nC2D_PU200.pdf");  




}





void plot_pi_nC3D_nC2D_PU200(){

  TString filename_cone = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_PU200_C3D_cone.root";
  TString filename_histo_0p01 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_PU200_C3D_polarHisto.root";
  TString filename_histo_0p03 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_PU200_C3D_polarHisto_dR0p03.root";

 TH1F* h_cone = single_plot(filename_cone,"HGCalTriggerNtuple","cl3d_clusters_n","",60,0.,60.);
  TH1F* h_histo_0p01 = single_plot(filename_histo_0p01,"HGCalTriggerNtuple","cl3d_clusters_n","",60,0.,60.);
  TH1F* h_histo_0p03 = single_plot(filename_histo_0p03,"HGCalTriggerNtuple","cl3d_clusters_n","",60,0.,60.);
  TH1F* h_cone_gen = single_plot(filename_cone,"HGCalTriggerNtuple","cl3d_clusters_n[gen_cl3d]","gen_cl3d>=0",60,0.,60.);
  TH1F* h_histo_0p01_gen = single_plot(filename_histo_0p01,"HGCalTriggerNtuple","cl3d_clusters_n[gen_cl3d]","gen_cl3d>=0",60,0.,60.);
  TH1F* h_histo_0p03_gen = single_plot(filename_histo_0p03,"HGCalTriggerNtuple","cl3d_clusters_n[gen_cl3d]","gen_cl3d>=0",60,0.,60.);

   vector<TH1F*> histo;
   histo.push_back(h_cone);
   histo.push_back(h_histo_0p01);
   histo.push_back(h_histo_0p03);
   histo.push_back(h_cone_gen);
   histo.push_back(h_histo_0p01_gen);
   histo.push_back(h_histo_0p03_gen);

   vector<TString> leg_entry;
   leg_entry.push_back("Cone dR=0.01 incl.");
   leg_entry.push_back("Histo dR=0.01 incl.");
   leg_entry.push_back("Histo dR=0.03 incl.");
   leg_entry.push_back("Cone dR=0.01 gen. (x1000)");
   leg_entry.push_back("Histo dR=0.01 gen. (x1000)");
   leg_entry.push_back("Histo dR=0.03 gen. (x1000)");


   TLegend* leg=new TLegend(0.45,0.6,0.75,0.85);
   leg->SetHeader("Pion gun p_{T}=25 GeV PU=200");
   leg->SetFillColor(0);
   leg->SetBorderSize(0);
   leg->SetTextSize(0.03);
  
   for(unsigned int i=0;i<histo.size();i++){
     TH1F* h = histo[i];
     //h->Scale(1/h->Integral());
     if(i>2)
       h->Scale(1000);
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
   
   histo[0]->GetXaxis()->SetTitle("#C2D per C3D");
   histo[0]->GetYaxis()->SetTitle("#C3D");
   histo[0]->GetYaxis()->SetTitleOffset(1.7);
   histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
   //histo[0]->SetMaximum(2*histo[0]->GetMaximum());
   histo[0]->SetStats(0);
   histo[0]->SetTitle("");
   histo[0]->Draw();
   
   for(unsigned int i=1;i<histo.size();i++)
     histo[i]->Draw("same");
   leg->Draw("same");
   
   
   TLatex *texl = new TLatex(0.01,1.02*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV, PU=200");
   texl->SetTextSize(0.03);
   texl->Draw("same");
   
   gPad->SetTicks();
   
   
   c->SaveAs("plots/C3D_pi_C3D_nC2D_PU200.pdf");  




}






void plot_ele_SC_nC3D(){

  TString filename_cone = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_C3D_cone.root";
  TString filename_histo_0p01 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_C3D_polarHisto.root";
  TString filename_histo_0p03 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_C3D_polarHisto_dR0p03.root";


  TH1F* h_cone_SC_C3D_0p1 = single_plot(filename_cone,"HGCalTriggerNtuple","gen_SC_C3D_0p1_n_cl3d","",10,0.,10.);
  TH1F* h_histo_0p01_SC_C3D_0p1 = single_plot(filename_histo_0p01,"HGCalTriggerNtuple","gen_SC_C3D_0p1_n_cl3d","",10,0.,10.);
  TH1F* h_histo_0p03_SC_C3D_0p1 = single_plot(filename_histo_0p03,"HGCalTriggerNtuple","gen_SC_C3D_0p1_n_cl3d","",10,0.,10.);
  TH1F* h_cone_SC_C3D_0p3 = single_plot(filename_cone,"HGCalTriggerNtuple","gen_SC_C3D_0p3_n_cl3d","",10,0.,10.);
  TH1F* h_histo_0p01_SC_C3D_0p3 = single_plot(filename_histo_0p01,"HGCalTriggerNtuple","gen_SC_C3D_0p3_n_cl3d","",10,0.,10.);
  TH1F* h_histo_0p03_SC_C3D_0p3 = single_plot(filename_histo_0p03,"HGCalTriggerNtuple","gen_SC_C3D_0p3_n_cl3d","",10,0.,10.);


   vector<TH1F*> histo;
   histo.push_back(h_cone_SC_C3D_0p1);
   histo.push_back(h_histo_0p01_SC_C3D_0p1);
   histo.push_back(h_histo_0p03_SC_C3D_0p1);
   histo.push_back(h_cone_SC_C3D_0p3);
   histo.push_back(h_histo_0p01_SC_C3D_0p3);
   histo.push_back(h_histo_0p03_SC_C3D_0p3);


   vector<TString> leg_entry;
   leg_entry.push_back("Gen. SC #DeltaR=0.1 cone dR=0.01");
   leg_entry.push_back("Gen. SC #DeltaR=0.1 histo dR=0.01");
   leg_entry.push_back("Gen. SC #DeltaR=0.1 histo dR=0.03");
   leg_entry.push_back("Gen. SC #DeltaR=0.3. cone dR=0.01");
   leg_entry.push_back("Gen. SC #DeltaR=0.3. histo dR=0.01");
   leg_entry.push_back("Gen. SC #DeltaR=0.3. histo dR=0.03");


   TLegend* leg=new TLegend(0.35,0.6,0.75,0.85);
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
   
   histo = sort_histo(histo);
   
   histo[0]->GetXaxis()->SetTitle("#C3D per SC");
   histo[0]->GetYaxis()->SetTitle("a. u.");
   histo[0]->GetYaxis()->SetTitleOffset(1.7);
   histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
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
   
   
   c->SaveAs("plots/C3D_ele_SC_nC3D.pdf");  




}









void plot_pi_SC_nC3D(){

  TString filename_cone = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_C3D_cone.root";
  TString filename_histo_0p01 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_C3D_polarHisto.root";
  TString filename_histo_0p03 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_C3D_polarHisto_dR0p03.root";


  TH1F* h_cone_SC_C3D_0p1 = single_plot(filename_cone,"HGCalTriggerNtuple","gen_SC_C3D_0p1_n_cl3d","",10,0.,10.);
  TH1F* h_histo_0p01_SC_C3D_0p1 = single_plot(filename_histo_0p01,"HGCalTriggerNtuple","gen_SC_C3D_0p1_n_cl3d","",10,0.,10.);
  TH1F* h_histo_0p03_SC_C3D_0p1 = single_plot(filename_histo_0p03,"HGCalTriggerNtuple","gen_SC_C3D_0p1_n_cl3d","",10,0.,10.);
  TH1F* h_cone_SC_C3D_0p3 = single_plot(filename_cone,"HGCalTriggerNtuple","gen_SC_C3D_0p3_n_cl3d","",10,0.,10.);
  TH1F* h_histo_0p01_SC_C3D_0p3 = single_plot(filename_histo_0p01,"HGCalTriggerNtuple","gen_SC_C3D_0p3_n_cl3d","",10,0.,10.);
  TH1F* h_histo_0p03_SC_C3D_0p3 = single_plot(filename_histo_0p03,"HGCalTriggerNtuple","gen_SC_C3D_0p3_n_cl3d","",10,0.,10.);


   vector<TH1F*> histo;
   histo.push_back(h_cone_SC_C3D_0p1);
   histo.push_back(h_histo_0p01_SC_C3D_0p1);
   histo.push_back(h_histo_0p03_SC_C3D_0p1);
   histo.push_back(h_cone_SC_C3D_0p3);
   histo.push_back(h_histo_0p01_SC_C3D_0p3);
   histo.push_back(h_histo_0p03_SC_C3D_0p3);


   vector<TString> leg_entry;
   leg_entry.push_back("Gen. SC #DeltaR=0.1 cone dR=0.01");
   leg_entry.push_back("Gen. SC #DeltaR=0.1 histo dR=0.01");
   leg_entry.push_back("Gen. SC #DeltaR=0.1 histo dR=0.03");
   leg_entry.push_back("Gen. SC #DeltaR=0.3. cone dR=0.01");
   leg_entry.push_back("Gen. SC #DeltaR=0.3. histo dR=0.01");
   leg_entry.push_back("Gen. SC #DeltaR=0.3. histo dR=0.03");


   TLegend* leg=new TLegend(0.35,0.6,0.75,0.85);
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
   
   histo[0]->GetXaxis()->SetTitle("#C3D per SC");
   histo[0]->GetYaxis()->SetTitle("a. u.");
   histo[0]->GetYaxis()->SetTitleOffset(1.7);
   histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
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
   
   
   c->SaveAs("plots/C3D_pi_SC_nC3D.pdf");  




}









void plot_ele_SC_nC3D_PU200(){

  TString filename_cone = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_PU200_C3D_cone.root";
  TString filename_histo_0p01 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_PU200_C3D_polarHisto.root";
  TString filename_histo_0p03 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_PU200_C3D_polarHisto_dR0p03.root";

  TH1F* h_cone_SC_C3D_0p1 = single_plot(filename_cone,"HGCalTriggerNtuple","gen_SC_C3D_0p1_n_cl3d","",30,0.,30.);
  TH1F* h_histo_0p01_SC_C3D_0p1 = single_plot(filename_histo_0p01,"HGCalTriggerNtuple","gen_SC_C3D_0p1_n_cl3d","",30,0.,30.);
  TH1F* h_histo_0p03_SC_C3D_0p1 = single_plot(filename_histo_0p03,"HGCalTriggerNtuple","gen_SC_C3D_0p1_n_cl3d","",30,0.,30.);

  TH1F* h_cone_SC_C3D_0p3 = single_plot(filename_cone,"HGCalTriggerNtuple","gen_SC_C3D_0p3_n_cl3d","",30,0.,30.);
  TH1F* h_histo_0p01_SC_C3D_0p3 = single_plot(filename_histo_0p01,"HGCalTriggerNtuple","gen_SC_C3D_0p3_n_cl3d","",30,0.,30.);
  TH1F* h_histo_0p03_SC_C3D_0p3 = single_plot(filename_histo_0p03,"HGCalTriggerNtuple","gen_SC_C3D_0p3_n_cl3d","",30,0.,30.);

   vector<TH1F*> histo;
   histo.push_back(h_cone_SC_C3D_0p1);
   histo.push_back(h_histo_0p01_SC_C3D_0p1);
   histo.push_back(h_histo_0p03_SC_C3D_0p1);
   histo.push_back(h_cone_SC_C3D_0p3);
   histo.push_back(h_histo_0p01_SC_C3D_0p3);
   histo.push_back(h_histo_0p03_SC_C3D_0p3);

   vector<TString> leg_entry;
   leg_entry.push_back("Gen. SC #DeltaR=0.1 cone dR=0.01");
   leg_entry.push_back("Gen. SC #DeltaR=0.1 histo dR=0.01");
   leg_entry.push_back("Gen. SC #DeltaR=0.1 histo dR=0.03");
   leg_entry.push_back("Gen. SC #DeltaR=0.3. cone dR=0.01");
   leg_entry.push_back("Gen. SC #DeltaR=0.3. histo dR=0.01");
   leg_entry.push_back("Gen. SC #DeltaR=0.3. histo dR=0.03");

   TLegend* leg=new TLegend(0.35,0.6,0.75,0.85);
   leg->SetHeader("Electron gun p_{T}=25 GeV PU=200");
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
   
   histo[0]->GetXaxis()->SetTitle("#C3D per SC");
   histo[0]->GetYaxis()->SetTitle("a. u.");
   histo[0]->GetYaxis()->SetTitleOffset(1.7);
   histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
   //histo[0]->SetMaximum(2*histo[0]->GetMaximum());
   histo[0]->SetStats(0);
   histo[0]->SetTitle("");
   histo[0]->Draw();
   
   for(unsigned int i=1;i<histo.size();i++)
     histo[i]->Draw("same");
   leg->Draw("same");
   
   
   TLatex *texl = new TLatex(0.01,1.02*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV, PU=200");
   texl->SetTextSize(0.03);
   texl->Draw("same");
   
   gPad->SetTicks();
   
   
   c->SaveAs("plots/C3D_ele_SC_nC3D_PU200.pdf");  




}









void plot_pi_SC_nC3D_PU200(){

  TString filename_cone = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_PU200_C3D_cone.root";
  TString filename_histo_0p01 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_PU200_C3D_polarHisto.root";
  TString filename_histo_0p03 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_PU200_C3D_polarHisto_dR0p03.root";

  TH1F* h_cone_SC_C3D_0p1 = single_plot(filename_cone,"HGCalTriggerNtuple","gen_SC_C3D_0p1_n_cl3d","",30,0.,30.);
  TH1F* h_histo_0p01_SC_C3D_0p1 = single_plot(filename_histo_0p01,"HGCalTriggerNtuple","gen_SC_C3D_0p1_n_cl3d","",30,0.,30.);
  TH1F* h_histo_0p03_SC_C3D_0p1 = single_plot(filename_histo_0p03,"HGCalTriggerNtuple","gen_SC_C3D_0p1_n_cl3d","",30,0.,30.);

  TH1F* h_cone_SC_C3D_0p3 = single_plot(filename_cone,"HGCalTriggerNtuple","gen_SC_C3D_0p3_n_cl3d","",30,0.,30.);
  TH1F* h_histo_0p01_SC_C3D_0p3 = single_plot(filename_histo_0p01,"HGCalTriggerNtuple","gen_SC_C3D_0p3_n_cl3d","",30,0.,30.);
  TH1F* h_histo_0p03_SC_C3D_0p3 = single_plot(filename_histo_0p03,"HGCalTriggerNtuple","gen_SC_C3D_0p3_n_cl3d","",30,0.,30.);

   vector<TH1F*> histo;
   histo.push_back(h_cone_SC_C3D_0p1);
   histo.push_back(h_histo_0p01_SC_C3D_0p1);
   histo.push_back(h_histo_0p03_SC_C3D_0p1);
   histo.push_back(h_cone_SC_C3D_0p3);
   histo.push_back(h_histo_0p01_SC_C3D_0p3);
   histo.push_back(h_histo_0p03_SC_C3D_0p3);

   vector<TString> leg_entry;
   leg_entry.push_back("Gen. SC #DeltaR=0.1 cone dR=0.01");
   leg_entry.push_back("Gen. SC #DeltaR=0.1 histo dR=0.01");
   leg_entry.push_back("Gen. SC #DeltaR=0.1 histo dR=0.03");
   leg_entry.push_back("Gen. SC #DeltaR=0.3. cone dR=0.01");
   leg_entry.push_back("Gen. SC #DeltaR=0.3. histo dR=0.01");
   leg_entry.push_back("Gen. SC #DeltaR=0.3. histo dR=0.03");

   TLegend* leg=new TLegend(0.35,0.6,0.75,0.85);
   leg->SetHeader("Pion gun p_{T}=25 GeV PU=200");
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
   
   histo[0]->GetXaxis()->SetTitle("#C3D per SC");
   histo[0]->GetYaxis()->SetTitle("a. u.");
   histo[0]->GetYaxis()->SetTitleOffset(1.7);
   histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
   //histo[0]->SetMaximum(2*histo[0]->GetMaximum());
   histo[0]->SetStats(0);
   histo[0]->SetTitle("");
   histo[0]->Draw();
   
   for(unsigned int i=1;i<histo.size();i++)
     histo[i]->Draw("same");
   leg->Draw("same");
   
   
   TLatex *texl = new TLatex(0.01,1.02*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV, PU=200");
   texl->SetTextSize(0.03);
   texl->Draw("same");
   
   gPad->SetTicks();
   
   
   c->SaveAs("plots/C3D_pi_SC_nC3D_PU200.pdf");  




}










void plot_delta_eta_C3D(){

  TString filename_ele_cone = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_C3D_cone.root";
  TString filename_ele_histo = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_C3D_polarHisto.root";
  TString filename_pi_cone = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_C3D_cone.root";
  TString filename_pi_histo = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_C3D_polarHisto.root";

  TH1F* h_ele_cone = single_plot(filename_ele_cone,"HGCalTriggerNtuple","cl3d_eta[gen_cl3d]-gen_eta","gen_cl3d>=0",100,-0.2,0.2);
  TH1F* h_ele_histo = single_plot(filename_ele_histo,"HGCalTriggerNtuple","cl3d_eta[gen_cl3d]-gen_eta","gen_cl3d>=0",100,-0.2,0.2);
  TH1F* h_pi_cone = single_plot(filename_pi_cone,"HGCalTriggerNtuple","cl3d_eta[gen_cl3d]-gen_eta","gen_cl3d>=0",100,-0.2,0.2);
  TH1F* h_pi_histo = single_plot(filename_pi_histo,"HGCalTriggerNtuple","cl3d_eta[gen_cl3d]-gen_eta","gen_cl3d>=0",100,-0.2,0.2);


   vector<TH1F*> histo;
   histo.push_back(h_ele_cone);
   histo.push_back(h_ele_histo);
   histo.push_back(h_pi_cone);
   histo.push_back(h_pi_histo);
 

   vector<TString> leg_entry;
   leg_entry.push_back("Electron cone");
   leg_entry.push_back("Electron histo");
   leg_entry.push_back("Pion cone");
   leg_entry.push_back("Pion histo");

   TLegend* leg=new TLegend(0.2,0.65,0.45,0.85);
   leg->SetHeader("Particle gun p_{T}=25 GeV PU=0");
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
   
   histo[0]->GetXaxis()->SetTitle("#eta(C3D)-#eta(gen)");
   histo[0]->GetYaxis()->SetTitle("a. u.");
   histo[0]->GetYaxis()->SetTitleOffset(1.7);
   histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
   //histo[0]->SetMaximum(2*histo[0]->GetMaximum());
   histo[0]->SetStats(0);
   histo[0]->SetTitle("");
   histo[0]->Draw();
   
   for(unsigned int i=1;i<histo.size();i++)
     histo[i]->Draw("same");
   leg->Draw("same");
   
   
   TLatex *texl = new TLatex(-0.19,1.02*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV, PU=0");
   texl->SetTextSize(0.03);
   texl->Draw("same");
   
   gPad->SetTicks();
   
   
   c->SaveAs("plots/C3D_delta_eta.pdf");  




}







void plot_delta_phi_C3D(){

  TString filename_ele_cone = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_C3D_cone.root";
  TString filename_ele_histo = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_C3D_polarHisto.root";
  TString filename_pi_cone = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_C3D_cone.root";
  TString filename_pi_histo = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_C3D_polarHisto.root";

  TH1F* h_ele_cone = single_plot(filename_ele_cone,"HGCalTriggerNtuple","TMath::ACos(cos(cl3d_phi[gen_cl3d]-gen_phi))*TMath::Sign(1,sin(cl3d_phi[gen_cl3d]-gen_phi))","gen_cl3d>=0",100,-0.2,0.2);
  TH1F* h_ele_histo = single_plot(filename_ele_histo,"HGCalTriggerNtuple","TMath::ACos(cos(cl3d_phi[gen_cl3d]-gen_phi))*TMath::Sign(1,sin(cl3d_phi[gen_cl3d]-gen_phi))","gen_cl3d>=0",100,-0.2,0.2);
  TH1F* h_pi_cone = single_plot(filename_pi_cone,"HGCalTriggerNtuple","TMath::ACos(cos(cl3d_phi[gen_cl3d]-gen_phi))*TMath::Sign(1,sin(cl3d_phi[gen_cl3d]-gen_phi))","gen_cl3d>=0",100,-0.2,0.2);
  TH1F* h_pi_histo = single_plot(filename_pi_histo,"HGCalTriggerNtuple","TMath::ACos(cos(cl3d_phi[gen_cl3d]-gen_phi))*TMath::Sign(1,sin(cl3d_phi[gen_cl3d]-gen_phi))","gen_cl3d>=0",100,-0.2,0.2);


   vector<TH1F*> histo;
   histo.push_back(h_ele_cone);
   histo.push_back(h_ele_histo);
   histo.push_back(h_pi_cone);
   histo.push_back(h_pi_histo);
 

   vector<TString> leg_entry;
   leg_entry.push_back("Electron cone");
   leg_entry.push_back("Electron histo");
   leg_entry.push_back("Pion cone");
   leg_entry.push_back("Pion histo");

   TLegend* leg=new TLegend(0.2,0.65,0.4,0.85);
   leg->SetHeader("Particle gun p_{T}=25 GeV PU=0");
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
   
   histo[0]->GetXaxis()->SetTitle("#Delta#phi(C3D-gen)");
   histo[0]->GetYaxis()->SetTitle("a. u.");
   histo[0]->GetYaxis()->SetTitleOffset(1.7);
   histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
   //histo[0]->SetMaximum(2*histo[0]->GetMaximum());
   histo[0]->SetStats(0);
   histo[0]->SetTitle("");
   histo[0]->Draw();
   
   for(unsigned int i=1;i<histo.size();i++)
     histo[i]->Draw("same");
   leg->Draw("same");
   
   
   TLatex *texl = new TLatex(-0.19,1.02*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV, PU=0");
   texl->SetTextSize(0.03);
   texl->Draw("same");
   
   gPad->SetTicks();
   
   
   c->SaveAs("plots/C3D_delta_phi.pdf");  




}







void plot_delta_eta_C3D_PU200(){

  TString filename_ele_cone = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_PU200_C3D_cone.root";
  TString filename_ele_histo = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_PU200_C3D_polarHisto.root";
  TString filename_pi_cone = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_PU200_C3D_cone.root";
  TString filename_pi_histo = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_PU200_C3D_polarHisto.root";

  TH1F* h_ele_cone = single_plot(filename_ele_cone,"HGCalTriggerNtuple","cl3d_eta[gen_cl3d]-gen_eta","gen_cl3d>=0",100,-0.2,0.2);
  TH1F* h_ele_histo = single_plot(filename_ele_histo,"HGCalTriggerNtuple","cl3d_eta[gen_cl3d]-gen_eta","gen_cl3d>=0",100,-0.2,0.2);
  TH1F* h_pi_cone = single_plot(filename_pi_cone,"HGCalTriggerNtuple","cl3d_eta[gen_cl3d]-gen_eta","gen_cl3d>=0",100,-0.2,0.2);
  TH1F* h_pi_histo = single_plot(filename_pi_histo,"HGCalTriggerNtuple","cl3d_eta[gen_cl3d]-gen_eta","gen_cl3d>=0",100,-0.2,0.2);


   vector<TH1F*> histo;
   histo.push_back(h_ele_cone);
   histo.push_back(h_ele_histo);
   histo.push_back(h_pi_cone);
   histo.push_back(h_pi_histo);
 

   vector<TString> leg_entry;
   leg_entry.push_back("Electron cone");
   leg_entry.push_back("Electron histo");
   leg_entry.push_back("Pion cone");
   leg_entry.push_back("Pion histo");

   TLegend* leg=new TLegend(0.2,0.65,0.45,0.85);
   leg->SetHeader("Particle gun p_{T}=25 GeV PU=200");
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
   
   histo[0]->GetXaxis()->SetTitle("#eta(C3D)-#eta(gen)");
   histo[0]->GetYaxis()->SetTitle("a. u.");
   histo[0]->GetYaxis()->SetTitleOffset(1.7);
   histo[0]->GetYaxis()->SetRangeUser(0,1.3*histo[0]->GetMaximum());
   //histo[0]->SetMaximum(2*histo[0]->GetMaximum());
   histo[0]->SetStats(0);
   histo[0]->SetTitle("");
   histo[0]->Draw();
   
   for(unsigned int i=1;i<histo.size();i++)
     histo[i]->Draw("same");
   leg->Draw("same");
   
   
   TLatex *texl = new TLatex(-0.19,1.02*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV, PU=200");
   texl->SetTextSize(0.03);
   texl->Draw("same");
   
   gPad->SetTicks();
   
   
   c->SaveAs("plots/C3D_delta_eta_PU200.pdf");  




}






void plot_delta_phi_C3D_PU200(){

  TString filename_ele_cone = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_PU200_C3D_cone.root";
  TString filename_ele_histo = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_PU200_C3D_polarHisto.root";
  TString filename_pi_cone = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_PU200_C3D_cone.root";
  TString filename_pi_histo = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_PU200_C3D_polarHisto.root";

  TH1F* h_ele_cone = single_plot(filename_ele_cone,"HGCalTriggerNtuple","TMath::ACos(cos(cl3d_phi[gen_cl3d]-gen_phi))*TMath::Sign(1,sin(cl3d_phi[gen_cl3d]-gen_phi))","gen_cl3d>=0",100,-0.2,0.2);
  TH1F* h_ele_histo = single_plot(filename_ele_histo,"HGCalTriggerNtuple","TMath::ACos(cos(cl3d_phi[gen_cl3d]-gen_phi))*TMath::Sign(1,sin(cl3d_phi[gen_cl3d]-gen_phi))","gen_cl3d>=0",100,-0.2,0.2);
  TH1F* h_pi_cone = single_plot(filename_pi_cone,"HGCalTriggerNtuple","TMath::ACos(cos(cl3d_phi[gen_cl3d]-gen_phi))*TMath::Sign(1,sin(cl3d_phi[gen_cl3d]-gen_phi))","gen_cl3d>=0",100,-0.2,0.2);
  TH1F* h_pi_histo = single_plot(filename_pi_histo,"HGCalTriggerNtuple","TMath::ACos(cos(cl3d_phi[gen_cl3d]-gen_phi))*TMath::Sign(1,sin(cl3d_phi[gen_cl3d]-gen_phi))","gen_cl3d>=0",100,-0.2,0.2);


   vector<TH1F*> histo;
   histo.push_back(h_ele_cone);
   histo.push_back(h_ele_histo);
   histo.push_back(h_pi_cone);
   histo.push_back(h_pi_histo);
 

   vector<TString> leg_entry;
   leg_entry.push_back("Electron cone");
   leg_entry.push_back("Electron histo");
   leg_entry.push_back("Pion cone");
   leg_entry.push_back("Pion histo");

   TLegend* leg=new TLegend(0.2,0.65,0.4,0.85);
   leg->SetHeader("Particle gun p_{T}=25 GeV PU=200");
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
   
   histo[0]->GetXaxis()->SetTitle("#Delta#phi(C3D-gen)");
   histo[0]->GetYaxis()->SetTitle("a. u.");
   histo[0]->GetYaxis()->SetTitleOffset(1.7);
   histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
   //histo[0]->SetMaximum(2*histo[0]->GetMaximum());
   histo[0]->SetStats(0);
   histo[0]->SetTitle("");
   histo[0]->Draw();
   
   for(unsigned int i=1;i<histo.size();i++)
     histo[i]->Draw("same");
   leg->Draw("same");
   
   
   TLatex *texl = new TLatex(-0.19,1.02*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV, PU=200");
   texl->SetTextSize(0.03);
   texl->Draw("same");
   
   gPad->SetTicks();
   
   
   c->SaveAs("plots/C3D_delta_phi_PU200.pdf");  




}







void plot_delta_phi_charge_C3D(){

  TString filename_ele_cone = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_C3D_cone.root";
  TString filename_pi_cone = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_C3D_cone.root";

  TH1F* h_ele_plus = single_plot(filename_ele_cone,"HGCalTriggerNtuple","TMath::ACos(cos(cl3d_phi[gen_cl3d]-gen_phi))*TMath::Sign(1,sin(cl3d_phi[gen_cl3d]-gen_phi))","gen_cl3d>=0 && gen_pdgid==-11",100,-0.2,0.2);
  TH1F* h_ele_minus = single_plot(filename_ele_cone,"HGCalTriggerNtuple","TMath::ACos(cos(cl3d_phi[gen_cl3d]-gen_phi))*TMath::Sign(1,sin(cl3d_phi[gen_cl3d]-gen_phi))","gen_cl3d>=0 && gen_pdgid==11",100,-0.2,0.2);
  TH1F* h_pi_plus = single_plot(filename_pi_cone,"HGCalTriggerNtuple","TMath::ACos(cos(cl3d_phi[gen_cl3d]-gen_phi))*TMath::Sign(1,sin(cl3d_phi[gen_cl3d]-gen_phi))","gen_cl3d>=0 && gen_pdgid==211",100,-0.2,0.2);
  TH1F* h_pi_minus = single_plot(filename_pi_cone,"HGCalTriggerNtuple","TMath::ACos(cos(cl3d_phi[gen_cl3d]-gen_phi))*TMath::Sign(1,sin(cl3d_phi[gen_cl3d]-gen_phi))","gen_cl3d>=0 && gen_pdgid==-211",100,-0.2,0.2);


   vector<TH1F*> histo;
   histo.push_back(h_ele_plus);
   histo.push_back(h_ele_minus);
   histo.push_back(h_pi_plus);
   histo.push_back(h_pi_minus);
 

   vector<TString> leg_entry;
   leg_entry.push_back("e^{+} cone");
   leg_entry.push_back("e^{-} cone");
   leg_entry.push_back("#pi^{+} cone");
   leg_entry.push_back("#pi^{-} cone");

   TLegend* leg=new TLegend(0.2,0.65,0.4,0.85);
   leg->SetHeader("Particle gun p_{T}=25 GeV PU=0");
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
   
   histo[0]->GetXaxis()->SetTitle("#Delta#phi(C3D-gen)");
   histo[0]->GetYaxis()->SetTitle("a. u.");
   histo[0]->GetYaxis()->SetTitleOffset(1.7);
   histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
   //histo[0]->SetMaximum(2*histo[0]->GetMaximum());
   histo[0]->SetStats(0);
   histo[0]->SetTitle("");
   histo[0]->Draw();
   
   for(unsigned int i=1;i<histo.size();i++)
     histo[i]->Draw("same");
   leg->Draw("same");
   
   
   TLatex *texl = new TLatex(-0.19,1.02*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV, PU=0");
   texl->SetTextSize(0.03);
   texl->Draw("same");
   
   gPad->SetTicks();
   
   
   c->SaveAs("plots/C3D_delta_phi_charge.pdf");  




}








void plot_ele_histo(){

  TString filename_cone = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_C3D_cone.root";
  TString filename_histo_0p01 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_C3D_polarHisto.root";
  TString filename_histo_0p03 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_C3D_polarHisto_dR0p03.root";


  TH1F* h_C3D = single_plot(filename_cone,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]","gen_cl3d>=0",100,0.,50.);
  TH1F* h_C3D_histo_0p01 = single_plot(filename_histo_0p01,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]","gen_cl3d>=0",100,0.,50.);
  TH1F* h_C3D_histo_0p03 = single_plot(filename_histo_0p03,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]","gen_cl3d>=0",100,0.,50.);


   vector<TH1F*> histo;
   histo.push_back(h_C3D);
   histo.push_back(h_C3D_histo_0p01);
   histo.push_back(h_C3D_histo_0p03);

   vector<TString> leg_entry;
   leg_entry.push_back("cone dR=0.01");
   leg_entry.push_back("histo dR=0.01");
   leg_entry.push_back("histo dR=0.03");

   TLegend* leg=new TLegend(0.55,0.35,0.75,0.85);
   leg->SetHeader("#splitline{Electron gun p_{T}=25 GeV}{PU=0 Highest-p_{T} C3D}");
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
   histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
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
   
   
   c->SaveAs("plots/C3D_ele_histo.pdf");  




}








void plot_ele_SC_histo(){

  TString filename_cone = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_C3D_cone.root";
  TString filename_histo_0p01 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_C3D_polarHisto.root";
  TString filename_histo_0p03 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_C3D_polarHisto_dR0p03.root";


  TH1F* h_SC_C3D_0p3 = single_plot(filename_cone,"HGCalTriggerNtuple","gen_SC_C3D_0p3_pt","",100,0.,50.);
  TH1F* h_SC_C3D_0p3_histo_0p01 = single_plot(filename_histo_0p01,"HGCalTriggerNtuple","gen_SC_C3D_0p3_pt","",100,0.,50.);
  TH1F* h_SC_C3D_0p3_histo_0p03 = single_plot(filename_histo_0p03,"HGCalTriggerNtuple","gen_SC_C3D_0p3_pt","",100,0.,50.);

   vector<TH1F*> histo;
   histo.push_back(h_SC_C3D_0p3);
   histo.push_back(h_SC_C3D_0p3_histo_0p01);
   histo.push_back(h_SC_C3D_0p3_histo_0p03);

   vector<TString> leg_entry;
   leg_entry.push_back("cone dR=0.01");
   leg_entry.push_back("histo dR=0.01");
   leg_entry.push_back("histo dR=0.03");

   TLegend* leg=new TLegend(0.55,0.35,0.75,0.85);
   leg->SetHeader("#splitline{Electron gun p_{T}=25 GeV}{PU=0 Gen. SC #DeltaR=0.3.}");
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
   histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
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
   
   
   c->SaveAs("plots/C3D_ele_SC_histo.pdf");  




}









void plot_pi_histo(){

  TString filename_cone = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_C3D_cone.root";
  TString filename_histo_0p01 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_C3D_polarHisto.root";
  TString filename_histo_0p03 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_C3D_polarHisto_dR0p03.root";

  TH1F* h_C3D = single_plot(filename_cone,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]","gen_cl3d>=0",120,0.,60.);
  TH1F* h_C3D_histo_0p01 = single_plot(filename_histo_0p01,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]","gen_cl3d>=0",120,0.,60.);
  TH1F* h_C3D_histo_0p03 = single_plot(filename_histo_0p03,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]","gen_cl3d>=0",120,0.,60.);


   vector<TH1F*> histo;
   histo.push_back(h_C3D);
   histo.push_back(h_C3D_histo_0p01);
   histo.push_back(h_C3D_histo_0p03);

   vector<TString> leg_entry;
   leg_entry.push_back("cone dR=0.01");
   leg_entry.push_back("histo dR=0.01");
   leg_entry.push_back("histo dR=0.03");

   TLegend* leg=new TLegend(0.55,0.35,0.75,0.85);
   leg->SetHeader("#splitline{Pion gun p_{T}=25 GeV}{PU=0 Highest-p_{T} C3D}");
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
   histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
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
   
   
   c->SaveAs("plots/C3D_pi_histo.pdf");  




}






void plot_pi_SC_histo(){

  TString filename_cone = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_C3D_cone.root";
  TString filename_histo_0p01 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_C3D_polarHisto.root";
  TString filename_histo_0p03 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_C3D_polarHisto_dR0p03.root";


  TH1F* h_SC_C3D_0p3 = single_plot(filename_cone,"HGCalTriggerNtuple","gen_SC_C3D_0p3_pt","",120,0.,60.);
  TH1F* h_SC_C3D_0p3_histo_0p01 = single_plot(filename_histo_0p01,"HGCalTriggerNtuple","gen_SC_C3D_0p3_pt","",120,0.,60.);
  TH1F* h_SC_C3D_0p3_histo_0p03 = single_plot(filename_histo_0p03,"HGCalTriggerNtuple","gen_SC_C3D_0p3_pt","",120,0.,60.);

   vector<TH1F*> histo;
   histo.push_back(h_SC_C3D_0p3);
   histo.push_back(h_SC_C3D_0p3_histo_0p01);
   histo.push_back(h_SC_C3D_0p3_histo_0p03);

   vector<TString> leg_entry;
   leg_entry.push_back("cone dR=0.01");
   leg_entry.push_back("histo dR=0.01");
   leg_entry.push_back("histo dR=0.03");

   TLegend* leg=new TLegend(0.55,0.35,0.75,0.85);
   leg->SetHeader("#splitline{Pion gun p_{T}=25 GeV}{PU=0 Gen. SC #DeltaR=0.3.}");
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
   histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
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
   
   
   c->SaveAs("plots/C3D_pi_SC_histo.pdf");  




}







void plot_ele_histo_PU200(){

  TString filename_cone = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_PU200_C3D_cone.root";
  TString filename_histo_0p01 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_PU200_C3D_polarHisto.root";
  TString filename_histo_0p03 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_PU200_C3D_polarHisto_dR0p03.root";


  TH1F* h_C3D = single_plot(filename_cone,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]","gen_cl3d>=0",100,0.,50.);
  TH1F* h_C3D_histo_0p01 = single_plot(filename_histo_0p01,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]","gen_cl3d>=0",100,0.,50.);
  TH1F* h_C3D_histo_0p03 = single_plot(filename_histo_0p03,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]","gen_cl3d>=0",100,0.,50.);


   vector<TH1F*> histo;
   histo.push_back(h_C3D);
   histo.push_back(h_C3D_histo_0p01);
   histo.push_back(h_C3D_histo_0p03);

   vector<TString> leg_entry;
   leg_entry.push_back("cone dR=0.01");
   leg_entry.push_back("histo dR=0.01");
   leg_entry.push_back("histo dR=0.03");

   TLegend* leg=new TLegend(0.55,0.5,0.75,0.85);
   leg->SetHeader("#splitline{Electron gun p_{T}=25 GeV}{PU=200 Highest-p_{T} C3D}");
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
   histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
   //histo[0]->SetMaximum(2*histo[0]->GetMaximum());
   histo[0]->SetStats(0);
   histo[0]->SetTitle("");
   histo[0]->Draw();
   
   for(unsigned int i=1;i<histo.size();i++)
     histo[i]->Draw("same");
   leg->Draw("same");
   
   
   TLatex *texl = new TLatex(0.01,1.02*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV, PU=200");
   texl->SetTextSize(0.03);
   texl->Draw("same");
   
   gPad->SetTicks();
   
   
   c->SaveAs("plots/C3D_ele_PU200_histo.pdf");  




}








void plot_ele_SC_histo_PU200(){

  TString filename_cone = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_PU200_C3D_cone.root";
  TString filename_histo_0p01 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_PU200_C3D_polarHisto.root";
  TString filename_histo_0p03 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_PU200_C3D_polarHisto_dR0p03.root";


  TH1F* h_SC_C3D_0p3 = single_plot(filename_cone,"HGCalTriggerNtuple","gen_SC_C3D_0p3_pt","",100,0.,100.);
  TH1F* h_SC_C3D_0p3_histo_0p01 = single_plot(filename_histo_0p01,"HGCalTriggerNtuple","gen_SC_C3D_0p3_pt","",100,0.,100.);
  TH1F* h_SC_C3D_0p3_histo_0p03 = single_plot(filename_histo_0p03,"HGCalTriggerNtuple","gen_SC_C3D_0p3_pt","",100,0.,100.);

   vector<TH1F*> histo;
   histo.push_back(h_SC_C3D_0p3);
   histo.push_back(h_SC_C3D_0p3_histo_0p01);
   histo.push_back(h_SC_C3D_0p3_histo_0p03);

   vector<TString> leg_entry;
   leg_entry.push_back("cone dR=0.01");
   leg_entry.push_back("histo dR=0.01");
   leg_entry.push_back("histo dR=0.03");

   TLegend* leg=new TLegend(0.55,0.35,0.75,0.85);
   leg->SetHeader("#splitline{Electron gun p_{T}=25 GeV}{PU=200 Gen. SC #DeltaR=0.3.}");
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
   histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
   //histo[0]->SetMaximum(2*histo[0]->GetMaximum());
   histo[0]->SetStats(0);
   histo[0]->SetTitle("");
   histo[0]->Draw();
   
   for(unsigned int i=1;i<histo.size();i++)
     histo[i]->Draw("same");
   leg->Draw("same");
   
   
   TLatex *texl = new TLatex(0.01,1.02*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV, PU=200");
   texl->SetTextSize(0.03);
   texl->Draw("same");
   
   gPad->SetTicks();
   
   
   c->SaveAs("plots/C3D_ele_SC_histo_PU200.pdf");  




}









void plot_pi_histo_PU200(){

  TString filename_cone = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_PU200_C3D_cone.root";
  TString filename_histo_0p01 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_PU200_C3D_polarHisto.root";
  TString filename_histo_0p03 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_PU200_C3D_polarHisto_dR0p03.root";

  TH1F* h_C3D = single_plot(filename_cone,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]","gen_cl3d>=0",60,0.,60.);
  TH1F* h_C3D_histo_0p01 = single_plot(filename_histo_0p01,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]","gen_cl3d>=0",60,0.,60.);
  TH1F* h_C3D_histo_0p03 = single_plot(filename_histo_0p03,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]","gen_cl3d>=0",60,0.,60.);


   vector<TH1F*> histo;
   histo.push_back(h_C3D);
   histo.push_back(h_C3D_histo_0p01);
   histo.push_back(h_C3D_histo_0p03);

   vector<TString> leg_entry;
   leg_entry.push_back("cone dR=0.01");
   leg_entry.push_back("histo dR=0.01");
   leg_entry.push_back("histo dR=0.03");

   TLegend* leg=new TLegend(0.55,0.35,0.75,0.85);
   leg->SetHeader("#splitline{Pion gun p_{T}=25 GeV}{PU=200 Highest-p_{T} C3D}");
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
   
   
   TLatex *texl = new TLatex(0.01,1.02*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV, PU=200");
   texl->SetTextSize(0.03);
   texl->Draw("same");
   
   gPad->SetTicks();
   
   
   c->SaveAs("plots/C3D_pi_histo_PU200.pdf");  




}






void plot_pi_SC_histo_PU200(){

  TString filename_cone = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_PU200_C3D_cone.root";
  TString filename_histo_0p01 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_PU200_C3D_polarHisto.root";
  TString filename_histo_0p03 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_PU200_C3D_polarHisto_dR0p03.root";


  TH1F* h_SC_C3D_0p3 = single_plot(filename_cone,"HGCalTriggerNtuple","gen_SC_C3D_0p3_pt","",60,0.,60.);
  TH1F* h_SC_C3D_0p3_histo_0p01 = single_plot(filename_histo_0p01,"HGCalTriggerNtuple","gen_SC_C3D_0p3_pt","",60,0.,60.);
  TH1F* h_SC_C3D_0p3_histo_0p03 = single_plot(filename_histo_0p03,"HGCalTriggerNtuple","gen_SC_C3D_0p3_pt","",60,0.,60.);

   vector<TH1F*> histo;
   histo.push_back(h_SC_C3D_0p3);
   histo.push_back(h_SC_C3D_0p3_histo_0p01);
   histo.push_back(h_SC_C3D_0p3_histo_0p03);

   vector<TString> leg_entry;
   leg_entry.push_back("cone dR=0.01");
   leg_entry.push_back("histo dR=0.01");
   leg_entry.push_back("histo dR=0.03");

   TLegend* leg=new TLegend(0.5,0.6,0.75,0.85);
   leg->SetHeader("#splitline{Pion gun p_{T}=25 GeV}{PU=200 Gen. SC #DeltaR=0.3.}");
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
   
   
   TLatex *texl = new TLatex(0.01,1.02*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV, PU=200");
   texl->SetTextSize(0.03);
   texl->Draw("same");
   
   gPad->SetTicks();
   
   
   c->SaveAs("plots/C3D_pi_SC_histo_PU200.pdf");  




}










void plot_ele_histo_rescaled(){

  TString filename_cone = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_C3D_cone.root";
  TString filename_histo = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_C3D_polarHisto.root";

 TH1F* h_C3D_0 = single_plot(filename_cone,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]","gen_cl3d>=0",120,0.,60.);
  TH1F* h_SC_C3D_0p3_0 = single_plot(filename_cone,"HGCalTriggerNtuple","gen_SC_C3D_0p3_pt","",120,0.,60.);
  TH1F* h_C3D_histo_0 = single_plot(filename_histo,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]","gen_cl3d>=0",120,0.,60.);
  TH1F* h_SC_C3D_0p3_histo_0 = single_plot(filename_histo,"HGCalTriggerNtuple","gen_SC_C3D_0p3_pt","",120,0.,60.);

  TH1F* h_C3D = single_plot(filename_cone,"HGCalTriggerNtuple",Form("%f*cl3d_pt[gen_cl3d]",25./h_C3D_0->GetBinCenter(h_C3D_0->GetMaximumBin())),"gen_cl3d>=0",120,0.,60.);
  TH1F* h_SC_C3D_0p3 = single_plot(filename_cone,"HGCalTriggerNtuple",Form("%f*gen_SC_C3D_0p3_pt",25./h_SC_C3D_0p3_0->GetBinCenter(h_SC_C3D_0p3_0->GetMaximumBin())),"",120,0.,60.);
  TH1F* h_C3D_histo = single_plot(filename_histo,"HGCalTriggerNtuple",Form("%f*cl3d_pt[gen_cl3d]",25./h_C3D_histo_0->GetBinCenter(h_C3D_histo_0->GetMaximumBin())),"gen_cl3d>=0",120,0.,60.);
  TH1F* h_SC_C3D_0p3_histo = single_plot(filename_histo,"HGCalTriggerNtuple",Form("%f*gen_SC_C3D_0p3_pt",25./h_SC_C3D_0p3_histo_0->GetBinCenter(h_SC_C3D_0p3_histo_0->GetMaximumBin())),"",120,0.,60.);


   vector<TH1F*> histo;
   histo.push_back(h_C3D);
   histo.push_back(h_SC_C3D_0p3);
   histo.push_back(h_C3D_histo);
   histo.push_back(h_SC_C3D_0p3_histo);

   vector<TString> leg_entry;
   leg_entry.push_back("Highest-p_{T} C3D cone");
   leg_entry.push_back("Gen. SC #DeltaR=0.3. cone");
   leg_entry.push_back("Highest-p_{T} C3D histo");
   leg_entry.push_back("Gen. SC #DeltaR=0.3. histo");

   TLegend* leg=new TLegend(0.47,0.65,0.75,0.85);
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
   
   histo = sort_histo(histo);
   
   histo[0]->GetXaxis()->SetTitle("p_{T}(C3D) [GeV]");
   histo[0]->GetYaxis()->SetTitle("a. u.");
   histo[0]->GetYaxis()->SetTitleOffset(1.7);
   histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
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
   
   
   c->SaveAs("plots/C3D_ele_SC_histo_rescaled.pdf");  




}









void plot_pi_histo_rescaled(){

  TString filename_cone = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_C3D_cone.root";
  TString filename_histo = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_C3D_polarHisto.root";

 TH1F* h_C3D_0 = single_plot(filename_cone,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]","gen_cl3d>=0",120,0.,60.);
  TH1F* h_SC_C3D_0p3_0 = single_plot(filename_cone,"HGCalTriggerNtuple","gen_SC_C3D_0p3_pt","",120,0.,60.);
  TH1F* h_C3D_histo_0 = single_plot(filename_histo,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]","gen_cl3d>=0",120,0.,60.);
  TH1F* h_SC_C3D_0p3_histo_0 = single_plot(filename_histo,"HGCalTriggerNtuple","gen_SC_C3D_0p3_pt","",120,0.,60.);

  TH1F* h_C3D = single_plot(filename_cone,"HGCalTriggerNtuple",Form("%f*cl3d_pt[gen_cl3d]",25./h_C3D_0->GetMean()),"gen_cl3d>=0",120,0.,60.);
  TH1F* h_SC_C3D_0p3 = single_plot(filename_cone,"HGCalTriggerNtuple",Form("%f*gen_SC_C3D_0p3_pt",25./h_SC_C3D_0p3_0->GetMean()),"",120,0.,60.);
							     TH1F* h_C3D_histo = single_plot(filename_histo,"HGCalTriggerNtuple",Form("%f*cl3d_pt[gen_cl3d]",25./h_C3D_histo_0->GetMean()),"gen_cl3d>=0",120,0.,60.);
											     TH1F* h_SC_C3D_0p3_histo = single_plot(filename_histo,"HGCalTriggerNtuple",Form("%f*gen_SC_C3D_0p3_pt",25./h_SC_C3D_0p3_histo_0->GetMean()),"",120,0.,60.);


   vector<TH1F*> histo;
   histo.push_back(h_C3D);
   histo.push_back(h_SC_C3D_0p3);
   histo.push_back(h_C3D_histo);
   histo.push_back(h_SC_C3D_0p3_histo);

   vector<TString> leg_entry;
   leg_entry.push_back("Highest-p_{T} C3D cone");
   leg_entry.push_back("Gen. SC #DeltaR=0.3. cone");
   leg_entry.push_back("Highest-p_{T} C3D histo");
   leg_entry.push_back("Gen. SC #DeltaR=0.3. histo");

   TLegend* leg=new TLegend(0.45,0.65,0.75,0.85);
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
   histo[0]->GetYaxis()->SetRangeUser(0,1.5*histo[0]->GetMaximum());
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
   
   
   c->SaveAs("plots/C3D_pi_SC_histo_rescaled.pdf");  




}












void plot_ratio(){

  TString filename_ele_cone = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_C3D_cone.root";
  TString filename_ele_histo_0p01 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_C3D_polarHisto.root";
  TString filename_ele_histo_0p03 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_C3D_polarHisto_dR0p03.root";
 
  TString filename_pi_cone = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_C3D_cone.root";
  TString filename_pi_histo_0p01 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_C3D_polarHisto.root";
  TString filename_pi_histo_0p03 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_C3D_polarHisto_dR0p03.root";


  TH1F* h_ele_cone = single_plot(filename_ele_cone,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]/gen_SC_C3D_0p3_pt","gen_cl3d>=0",100,0.,1.01);
  TH1F* h_ele_histo_0p01 = single_plot(filename_ele_histo_0p01,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]/gen_SC_C3D_0p3_pt","gen_cl3d>=0",100,0.,1.01);
  TH1F* h_ele_histo_0p03 = single_plot(filename_ele_histo_0p03,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]/gen_SC_C3D_0p3_pt","gen_cl3d>=0",100,0.,1.01);

  TH1F* h_pi_cone = single_plot(filename_pi_cone,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]/gen_SC_C3D_0p3_pt","gen_cl3d>=0",100,0.,1.01);
  TH1F* h_pi_histo_0p01 = single_plot(filename_pi_histo_0p01 ,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]/gen_SC_C3D_0p3_pt","gen_cl3d>=0",100,0.,1.01);
  TH1F* h_pi_histo_0p03 = single_plot(filename_pi_histo_0p03 ,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]/gen_SC_C3D_0p3_pt","gen_cl3d>=0",100,0.,1.01);


   vector<TH1F*> histo;
   histo.push_back(h_ele_cone);
   histo.push_back(h_ele_histo_0p01);
   histo.push_back(h_ele_histo_0p03);
   histo.push_back(h_pi_cone);
   histo.push_back(h_pi_histo_0p01);
   histo.push_back(h_pi_histo_0p03);

   vector<TString> leg_entry;
   leg_entry.push_back("Electron cone dR=0.01");
   leg_entry.push_back("Electron histo dR=0.01");
   leg_entry.push_back("Electron histo dR=0.03");
   leg_entry.push_back("Pion cone dR=0.01");
   leg_entry.push_back("Pion histo dR=0.01");
   leg_entry.push_back("Pion histo dR=0.03");
 

   TLegend* leg=new TLegend(0.2,0.65,0.55,0.85);
   leg->SetHeader("Particle gun p_{T}=25 GeV PU=0");
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
   
   histo[0]->GetXaxis()->SetTitle("p_{T}(lead. C3D)/p_{T}(supercluster #DeltaR=0.3)");
   histo[0]->GetYaxis()->SetTitle("a. u.");
   histo[0]->GetYaxis()->SetTitleOffset(1.7);
   histo[0]->GetYaxis()->SetRangeUser(1e-4,2*histo[0]->GetMaximum());
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
   
   
   c->SaveAs("plots/C3D_ratio_histo.pdf");  




}











void plot_ratio_PU200(){

  TString filename_ele_cone = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_PU200_C3D_cone.root";
  TString filename_ele_histo_0p01 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_PU200_C3D_polarHisto.root";
  TString filename_ele_histo_0p03 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_PU200_C3D_polarHisto_dR0p03.root";

  TString filename_pi_cone = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_PU200_C3D_cone.root";
  TString filename_pi_histo_0p01 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_PU200_C3D_polarHisto.root";
  TString filename_pi_histo_0p03 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_PU200_C3D_polarHisto_dR0p03.root";


  TH1F* h_ele_cone = single_plot(filename_ele_cone,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]/gen_SC_C3D_0p3_pt","gen_cl3d>=0",50,0.,1.01);
  TH1F* h_ele_histo_0p01 = single_plot(filename_ele_histo_0p01,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]/gen_SC_C3D_0p3_pt","gen_cl3d>=0",50,0.,1.01);
  TH1F* h_ele_histo_0p03 = single_plot(filename_ele_histo_0p03,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]/gen_SC_C3D_0p3_pt","gen_cl3d>=0",50,0.,1.01);

  TH1F* h_pi_cone = single_plot(filename_pi_cone,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]/gen_SC_C3D_0p3_pt","gen_cl3d>=0",50,0.,1.01);
  TH1F* h_pi_histo_0p01 = single_plot(filename_pi_histo_0p01 ,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]/gen_SC_C3D_0p3_pt","gen_cl3d>=0",50,0.,1.01);
  TH1F* h_pi_histo_0p03 = single_plot(filename_pi_histo_0p03 ,"HGCalTriggerNtuple","cl3d_pt[gen_cl3d]/gen_SC_C3D_0p3_pt","gen_cl3d>=0",50,0.,1.01);

  vector<TH1F*> histo;
   histo.push_back(h_ele_cone);
   histo.push_back(h_ele_histo_0p01);
   histo.push_back(h_ele_histo_0p03);
   histo.push_back(h_pi_cone);
   histo.push_back(h_pi_histo_0p01);
   histo.push_back(h_pi_histo_0p03);

   vector<TString> leg_entry;
   leg_entry.push_back("Electron cone dR=0.01");
   leg_entry.push_back("Electron histo dR=0.01");
   leg_entry.push_back("Electron histo dR=0.03");
   leg_entry.push_back("Pion cone dR=0.01");
   leg_entry.push_back("Pion histo dR=0.01");
   leg_entry.push_back("Pion histo dR=0.03");

 

   TLegend* leg=new TLegend(0.2,0.65,0.55,0.85);
   leg->SetHeader("Particle gun p_{T}=25 GeV PU=200");
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
   
   histo[0]->GetXaxis()->SetTitle("p_{T}(lead. C3D)/p_{T}(supercluster #DeltaR=0.3)");
   histo[0]->GetYaxis()->SetTitle("a. u.");
   histo[0]->GetYaxis()->SetTitleOffset(1.7);
   histo[0]->GetYaxis()->SetRangeUser(0,1.7*histo[0]->GetMaximum());
   //histo[0]->SetMaximum(2*histo[0]->GetMaximum());
   histo[0]->SetStats(0);
   histo[0]->SetTitle("");
   histo[0]->Draw();
   
   for(unsigned int i=1;i<histo.size();i++)
     histo[i]->Draw("same");
   leg->Draw("same");
   
   
   TLatex *texl = new TLatex(0.01,1.02*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV, PU=200");
   texl->SetTextSize(0.03);
   texl->Draw("same");
   
   gPad->SetTicks();
   
   
   c->SaveAs("plots/C3D_ratio_histo_PU200.pdf");  




}













void plot_nC3D_PU200(){

  TString filename_ele_cone = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_PU200_C3D_cone.root";
  TString filename_ele_histo_0p01 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_PU200_C3D_polarHisto.root";
  TString filename_ele_histo_0p03 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_PU200_C3D_polarHisto_dR0p03.root";
  TString filename_pi_cone = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_PU200_C3D_cone.root";
  TString filename_pi_histo_0p01 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_PU200_C3D_polarHisto.root";
  TString filename_pi_histo_0p03 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_PU200_C3D_polarHisto_dR0p03.root";


  TH1F* h_ele_cone = single_plot(filename_ele_cone,"HGCalTriggerNtuple","cl3d_n","1",200,0.,2000.);
  TH1F* h_ele_histo_0p01 = single_plot(filename_ele_histo_0p01,"HGCalTriggerNtuple","cl3d_n","1",200,0.,2000.);
  TH1F* h_ele_histo_0p03 = single_plot(filename_ele_histo_0p03,"HGCalTriggerNtuple","cl3d_n","1",200,0.,2000.);

  TH1F* h_pi_cone = single_plot(filename_pi_cone,"HGCalTriggerNtuple","cl3d_n","1",200,0.,2000.);
  TH1F* h_pi_histo_0p01 = single_plot(filename_pi_histo_0p01,"HGCalTriggerNtuple","cl3d_n","1",200,0.,2000.);
  TH1F* h_pi_histo_0p03 = single_plot(filename_pi_histo_0p03,"HGCalTriggerNtuple","cl3d_n","1",200,0.,2000.);


   vector<TH1F*> histo;
   histo.push_back(h_ele_cone);
   histo.push_back(h_ele_histo_0p01);
   histo.push_back(h_ele_histo_0p03);
   histo.push_back(h_pi_cone);
   histo.push_back(h_pi_histo_0p01);
   histo.push_back(h_pi_histo_0p03);
   

   vector<TString> leg_entry;
   leg_entry.push_back("Electron cone dR=0.01");
   leg_entry.push_back("Electron histo dR=0.01");
   leg_entry.push_back("Electron histo dR=0.03");
   leg_entry.push_back("Pion cone dR=0.01");
   leg_entry.push_back("Pion histo dR=0.01");
   leg_entry.push_back("Pion histo dR=0.03");
 

   TLegend* leg=new TLegend(0.2,0.65,0.55,0.85);
   leg->SetHeader("Particle gun p_{T}=25 GeV PU=200");
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
   histo[0]->GetYaxis()->SetRangeUser(0,1.7*histo[0]->GetMaximum());
   //histo[0]->SetMaximum(2*histo[0]->GetMaximum());
   histo[0]->SetStats(0);
   histo[0]->SetTitle("");
   histo[0]->Draw();
   
   for(unsigned int i=1;i<histo.size();i++)
     histo[i]->Draw("same");
   leg->Draw("same");
   
   
   TLatex *texl = new TLatex(0.01,1.02*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV, PU=200");
   texl->SetTextSize(0.03);
   texl->Draw("same");
   
   gPad->SetTicks();
   
   
   c->SaveAs("plots/C3D_n_PU200.pdf");  




}








void drawHisto(TString filename, int nevent, int eta_side){


  TH2F* h = single_plot2D(filename,"hgcalTriggerNtuplizer/HGCalTriggerNtuple","1/abs(sinh(cl_eta))","cl_phi",Form("cl_mipPt*(cl_eta*%i>0 && event==%i)",eta_side,nevent),6,0.09,0.52,216,-3.14159,3.14159);
  TH2F* h2 = new TH2F("h2","h2",6,0.09,0.52,216,-3.14159,3.14159);
  TH2F* h3 = new TH2F("h3","h3",6,0.09,0.52,216,-3.14159,3.14159);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  
  h->GetXaxis()->SetTitle("r/z");
  h->GetYaxis()->SetTitle("#phi");
  h->GetYaxis()->SetTitleOffset(1.7);
  h->SetStats(0);
  h->SetTitle("");
  h->Draw("colz");


  vector<unsigned> binSums = {13,                                           // 0
				   11, 11, 11,                                   // 1 - 3
				   9, 9, 9,                                      // 4 - 6
				   7, 7, 7, 7, 7, 7,                             // 7 - 12
				   5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,  //13 - 27
				   3, 3, 3, 3, 3, 3, 3, 3                        //28 - 35
  };

  float kROverZMin_ = 0.09;
  float kROverZMax_ = 0.52;
  int nBinsRHisto_ = h->GetXaxis()->GetNbins();
  int nBinsPhiHisto_ = h->GetYaxis()->GetNbins();

  for(int bin_R = 0; bin_R<nBinsRHisto_; bin_R++){

    int nBinsSide = (binSums[bin_R]-1)/2;

    for(int bin_phi = 0; bin_phi<nBinsPhiHisto_; bin_phi++){

      float content = h->GetBinContent(bin_R,bin_phi);

      for(int bin_phi2=1; bin_phi2<=nBinsSide; bin_phi2++ ){

	int binToSumLeft = bin_phi - bin_phi2;
	if( binToSumLeft<0 ) binToSumLeft += nBinsPhiHisto_;
	int binToSumRight = bin_phi + bin_phi2;
	if( binToSumRight>=int(nBinsPhiHisto_) ) binToSumRight -= nBinsPhiHisto_;
	
	content += h->GetBinContent(bin_R,binToSumLeft) / pow(2,bin_phi2); // quadratic kernel
	content += h->GetBinContent(bin_R,binToSumRight) / pow(2,bin_phi2); // quadratic kernel
	
      }
      
      float R1 = kROverZMin_ + bin_R*(kROverZMax_-kROverZMin_);
      float R2 = R1 + (kROverZMax_-kROverZMin_);
      double area = 0.5 * (pow(R2,2)-pow(R1,2)) * (1+0.5*(1-pow(0.5,nBinsSide))); // Takes into account different area of bins in different R-rings + sum of quadratic weights used
      h2->SetBinContent(bin_R,bin_phi,content/area);

    }
    
  }


  for(int bin_R = 0; bin_R<int(nBinsRHisto_); bin_R++){

    float weight = (bin_R==0 || bin_R==int(nBinsRHisto_)-1) ? 1.5 : 2.;
    
    for(int bin_phi = 0; bin_phi<int(nBinsPhiHisto_); bin_phi++){
      
      float content = h2->GetBinContent(bin_R,bin_phi);
      float contentDown = h2->GetBinContent(bin_R-1,bin_phi); //Non-allocated elements in maps return default 0 value
      float contentUp = h2->GetBinContent(bin_R+1,bin_phi);
      
      h3->SetBinContent(bin_R,bin_phi,(content + 0.5*contentDown + 0.5*contentUp)/weight);

    }

  }


  TCanvas* c2=new TCanvas("c2","c2",650,600);
  c2->SetLeftMargin(0.15);
  c2->SetRightMargin(0.15);
  
  h3->GetXaxis()->SetTitle("r/z");
  h3->GetYaxis()->SetTitle("#phi");
  h3->GetYaxis()->SetTitleOffset(1.7);
  h3->SetStats(0);
  h3->SetTitle("");
  h3->Draw("colz");


  
  
}








void plot_ele_incl_histo_PU200(){

  TString filename_cone = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_PU200_C3D_cone.root";
  TString filename_histo_0p01 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_PU200_C3D_polarHisto.root";
  TString filename_histo_0p03 = "/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_ele_PU200_C3D_polarHisto_dR0p03.root";


  TH1F* h_C3D = single_plot(filename_cone,"HGCalTriggerNtuple","cl3d_pt","1",100,0.,50.);
  TH1F* h_C3D_histo_0p01 = single_plot(filename_histo_0p01,"HGCalTriggerNtuple","cl3d_pt","1",100,0.,50.);
  TH1F* h_C3D_histo_0p03 = single_plot(filename_histo_0p03,"HGCalTriggerNtuple","cl3d_pt","1",100,0.,50.);


   vector<TH1F*> histo;
   histo.push_back(h_C3D);
   histo.push_back(h_C3D_histo_0p01);
   histo.push_back(h_C3D_histo_0p03);

   vector<TString> leg_entry;
   leg_entry.push_back("cone dR=0.01");
   leg_entry.push_back("histo dR=0.01");
   leg_entry.push_back("histo dR=0.03");

   TLegend* leg=new TLegend(0.55,0.5,0.75,0.85);
   leg->SetHeader("#splitline{Electron gun p_{T}=25 GeV}{PU=200 C3D inclusive}");
   leg->SetFillColor(0);
   leg->SetBorderSize(0);
   leg->SetTextSize(0.03);
  
   for(unsigned int i=0;i<histo.size();i++){
     TH1F* h = histo[i];
     //h->Scale(1/h->Integral());
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
   
   histo[0]->GetXaxis()->SetTitle("p_{T}(C3D) [GeV]");
   histo[0]->GetYaxis()->SetTitle("#C3D");
   histo[0]->GetYaxis()->SetTitleOffset(1.7);
   //histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
   histo[0]->SetMaximum(2*histo[0]->GetMaximum());
   histo[0]->SetStats(0);
   histo[0]->SetTitle("");
   histo[0]->Draw();
   
   for(unsigned int i=1;i<histo.size();i++)
     histo[i]->Draw("same");
   leg->Draw("same");
   
   
   TLatex *texl = new TLatex(0.01,1.02*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV, PU=200");
   texl->SetTextSize(0.03);
   texl->Draw("same");
   
   gPad->SetTicks();
   
   
   c->SaveAs("plots/C3D_ele_incl_PU200_histo.pdf");  




}





