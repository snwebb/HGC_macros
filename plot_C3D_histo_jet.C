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









void plot_profile_L1jet_response_pt_PU0_C3D_histo(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";


  TH2F* h_PU0_raw_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  TH2F* h_PU0_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);


  TH2F* h_PU0_raw_histo = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  TH2F* h_PU0_cal_histo = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.36*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);


  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw_dRNNC2D);
  histo.push_back(h_PU0_raw_histo);
  histo.push_back(h_PU0_cal_dRNNC2D);
  histo.push_back(h_PU0_cal_histo);

  
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 cone");
  leg_entry.push_back("PU=0 histo");
  leg_entry.push_back("PU=0 cone + JEC");
  leg_entry.push_back("PU=0 histo + JEC");

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


  c->SaveAs("plots/profile_L1jet_response_pt_PU0_histo.pdf");  


}










void plot_L1jet_response_pt_PU0_C3D_histo(){


  TString filename_dRNNC2D = "/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root";
  TString filename_histo = "/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root";


  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";


  TH1F* h_PU0_cal_dRNNC2D_1 = single_plot(filename_dRNNC2D,"HGCalTriggerNtupleJet","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& genjet_pt[VBF_parton_genjet]>40 && genjet_pt[VBF_parton_genjet]<60",125,0.,2.5);
  TH1F* h_PU0_cal_dRNNC2D_2 = single_plot(filename_dRNNC2D,"HGCalTriggerNtupleJet","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& genjet_pt[VBF_parton_genjet]>90 && genjet_pt[VBF_parton_genjet]<110",125,0.,2.5);
  TH1F* h_PU0_cal_dRNNC2D_3 = single_plot(filename_dRNNC2D,"HGCalTriggerNtupleJet","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& genjet_pt[VBF_parton_genjet]>190 && genjet_pt[VBF_parton_genjet]<210",125,0.,2.5);

  TH1F* h_PU0_cal_histo_1 = single_plot(filename_histo,"HGCalTriggerNtupleJet","1.36*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& genjet_pt[VBF_parton_genjet]>40 && genjet_pt[VBF_parton_genjet]<60",125,0.,2.5);
  TH1F* h_PU0_cal_histo_2 = single_plot(filename_histo,"HGCalTriggerNtupleJet","1.36*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& genjet_pt[VBF_parton_genjet]>90 && genjet_pt[VBF_parton_genjet]<110",125,0.,2.5);
  TH1F* h_PU0_cal_histo_3 = single_plot(filename_histo,"HGCalTriggerNtupleJet","1.36*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& genjet_pt[VBF_parton_genjet]>190 && genjet_pt[VBF_parton_genjet]<210",125,0.,2.5);

  vector<TH1F*> histo;
  histo.push_back(h_PU0_cal_dRNNC2D_1);
  histo.push_back(h_PU0_cal_dRNNC2D_2);
  histo.push_back(h_PU0_cal_dRNNC2D_3);
  histo.push_back(h_PU0_cal_histo_1);
  histo.push_back(h_PU0_cal_histo_2);
  histo.push_back(h_PU0_cal_histo_3);

   vector<TString> leg_entry;
   leg_entry.push_back("cone 40<p_{T}(gen)<60 GeV");
   leg_entry.push_back("cone 90<p_{T}(gen)<110 GeV");
   leg_entry.push_back("cone 190<p_{T}(gen)<210 GeV");
   leg_entry.push_back("histo 40<p_{T}(gen)<60 GeV");
   leg_entry.push_back("histo 90<p_{T}(gen)<110 GeV");
   leg_entry.push_back("histo 190<p_{T}(gen)<210 GeV");


   TLegend* leg=new TLegend(0.5,0.35,0.75,0.85);
   leg->SetHeader("#splitline{p_T(gen. jet)>20 GeV}{1.6<|#eta(gen.jet)|<2.9}");
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
   
   histo[0]->GetXaxis()->SetTitle("p_{T}(L1)/p_{T}(gen)");
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
   
   
   c->SaveAs("plots/L1jet_response_pt_PU0_C3D_histo.pdf");  




}









void plot_L1jet_nC3D_PU0_C3D_histo(){


  TString filename_dRNNC2D = "/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root";
  TString filename_histo = "/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root";


  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";


  TH1F* h_PU0_cal_dRNNC2D_1 = single_plot(filename_dRNNC2D,"HGCalTriggerNtupleJet","jets_ncl3d[VBF_parton_jets]",cut+"&& genjet_pt[VBF_parton_genjet]>40 && genjet_pt[VBF_parton_genjet]<60",50,0.,50.);
  TH1F* h_PU0_cal_dRNNC2D_2 = single_plot(filename_dRNNC2D,"HGCalTriggerNtupleJet","jets_ncl3d[VBF_parton_jets]",cut+"&& genjet_pt[VBF_parton_genjet]>90 && genjet_pt[VBF_parton_genjet]<110",50,0.,50.);
  TH1F* h_PU0_cal_dRNNC2D_3 = single_plot(filename_dRNNC2D,"HGCalTriggerNtupleJet","jets_ncl3d[VBF_parton_jets]",cut+"&& genjet_pt[VBF_parton_genjet]>190 && genjet_pt[VBF_parton_genjet]<210",50,0.,50.);


  TH1F* h_PU0_cal_histo_1 = single_plot(filename_histo,"HGCalTriggerNtupleJet","jets_ncl3d[VBF_parton_jets]",cut+"&& genjet_pt[VBF_parton_genjet]>40 && genjet_pt[VBF_parton_genjet]<60",50,0.,50.);
  TH1F* h_PU0_cal_histo_2 = single_plot(filename_histo,"HGCalTriggerNtupleJet","jets_ncl3d[VBF_parton_jets]",cut+"&& genjet_pt[VBF_parton_genjet]>90 && genjet_pt[VBF_parton_genjet]<110",50,0.,50.);
  TH1F* h_PU0_cal_histo_3 = single_plot(filename_histo,"HGCalTriggerNtupleJet","jets_ncl3d[VBF_parton_jets]",cut+"&& genjet_pt[VBF_parton_genjet]>190 && genjet_pt[VBF_parton_genjet]<210",50,0.,50.);


  vector<TH1F*> histo;
  histo.push_back(h_PU0_cal_dRNNC2D_1);
  histo.push_back(h_PU0_cal_dRNNC2D_2);
  histo.push_back(h_PU0_cal_dRNNC2D_3);
  histo.push_back(h_PU0_cal_histo_1);
  histo.push_back(h_PU0_cal_histo_2);
  histo.push_back(h_PU0_cal_histo_3);

   vector<TString> leg_entry;
   leg_entry.push_back("cone 40<p_{T}(gen)<60 GeV");
   leg_entry.push_back("cone 90<p_{T}(gen)<110 GeV");
   leg_entry.push_back("cone 190<p_{T}(gen)<210 GeV");
   leg_entry.push_back("histo 40<p_{T}(gen)<60 GeV");
   leg_entry.push_back("histo 90<p_{T}(gen)<110 GeV");
   leg_entry.push_back("histo 190<p_{T}(gen)<210 GeV");


   TLegend* leg=new TLegend(0.4,0.35,0.75,0.85);
   leg->SetHeader("#splitline{p_{T}(gen. jet)>20 GeV}{1.6<|#eta(gen.jet)|<2.9}");
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
   
   histo[0]->GetXaxis()->SetTitle("#C3D per jet");
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
   
   
   c->SaveAs("plots/L1jet_nC3D_PU0_C3D_histo.pdf");  




}
