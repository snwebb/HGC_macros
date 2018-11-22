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





void plot_profile_L1jet_response_pt_PU0_C2D_recal(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

 TH2F* h_PU0_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_core_*.root","jets","genjet_pt[VBF_parton_genjet]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

 TH2F* h_PU0_raw_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_raw_GEO_recal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR_JetPU0cal/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);


  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw);
  histo.push_back(h_PU0_raw_GEO);
  histo.push_back(h_PU0_raw_GEO_recal);
 
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 NN");
  leg_entry.push_back("PU=0 GEO");
  leg_entry.push_back("PU=0 GEO recalibr. C2D");

  TLegend* leg=new TLegend(0.4,0.15,0.7,0.5);
  leg->SetHeader("#splitline{p_T(gen. jet)>20 GeV}{1.6<|#eta(gen.jet)|<2.9}");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  
  vector<TGraphErrors*> graph;

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
  prof[0]->GetYaxis()->SetRangeUser(-0.2,1.2);
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



  c->SaveAs("plots/profile_L1jet_response_pt_C2D_recal_PU0.pdf");  


}








void plot_profile_L1jet_response_pt_PU0_C2D_recal_cal(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

 TH2F* h_PU0_cal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_cal_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","1.06*(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_cal_GEO_recal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR_JetPU0cal/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.1*1.04*(4.16098 -1.00815e+00 * log(max(jets_pt[VBF_parton_jets],20)) + 7.59202e-02* pow(log(max(jets_pt[VBF_parton_jets],20)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);



  vector<TH2F*> histo;
  histo.push_back(h_PU0_cal);
  histo.push_back(h_PU0_cal_GEO);
  histo.push_back(h_PU0_cal_GEO_recal);

 
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 NN");
  leg_entry.push_back("PU=0 GEO");
  leg_entry.push_back("PU=0 GEO recalibr. C2D");


  TLegend* leg=new TLegend(0.4,0.15,0.7,0.5);
  leg->SetHeader("#splitline{p_T(gen. jet)>20 GeV}{1.6<|#eta(gen.jet)|<2.9}");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  
  vector<TGraphErrors*> graph;

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



  c->SaveAs("plots/profile_L1jet_response_pt_C2D_recal_PU0_cal.pdf");  


}







void plot_profile_L1jet_response_pt_PU0_C2D_recal_cal2(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";


 TH2F* h_PU0_cal2 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","(4.4374 -0.948102 * log(jets_raw_Luca_pt[VBF_parton_jets]) + .0686934* pow(log(jets_raw_Luca_pt[VBF_parton_jets]),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_cal_GEO2 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","1.06*(4.4374 -0.948102 * log(jets_raw_Luca_pt[VBF_parton_jets]) + .0686934* pow(log(jets_raw_Luca_pt[VBF_parton_jets]),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_cal_GEO_recal2 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR_JetPU0cal/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.1*1.04*(4.16098 -1.00815e+00 * log(jets_pt[VBF_parton_jets]) + 7.59202e-02* pow(log(jets_pt[VBF_parton_jets]),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);



  vector<TH2F*> histo;
  histo.push_back(h_PU0_cal2);
  histo.push_back(h_PU0_cal_GEO2);
  histo.push_back(h_PU0_cal_GEO_recal2);
 
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 NN");
  leg_entry.push_back("PU=0 GEO");
  leg_entry.push_back("PU=0 GEO recalibr. C2D");

  TLegend* leg=new TLegend(0.4,0.15,0.7,0.5);
  leg->SetHeader("#splitline{p_T(gen. jet)>20 GeV}{1.6<|#eta(gen.jet)|<2.9}");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  
  vector<TGraphErrors*> graph;

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



  c->SaveAs("plots/profile_L1jet_response_pt_C2D_recal_PU0_cal2.pdf");  


}











void plot_profile_L1jet_response_eta_PU0_C2D_recal_cal2(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";


 TH2F* h_PU0_cal2 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","abs(genjet_eta[VBF_parton_genjet])","(4.4374 -0.948102 * log(jets_raw_Luca_pt[VBF_parton_jets]) + .0686934* pow(log(jets_raw_Luca_pt[VBF_parton_jets]),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);

  TH2F* h_PU0_cal_GEO2 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","abs(genjet_eta[VBF_parton_genjet])","1.06*(4.4374 -0.948102 * log(jets_raw_Luca_pt[VBF_parton_jets]) + .0686934* pow(log(jets_raw_Luca_pt[VBF_parton_jets]),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);

  TH2F* h_PU0_cal_GEO_recal2 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR_JetPU0cal/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","1.1*1.04*(4.16098 -1.00815e+00 * log(jets_pt[VBF_parton_jets]) + 7.59202e-02* pow(log(jets_pt[VBF_parton_jets]),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);



  vector<TH2F*> histo;
  histo.push_back(h_PU0_cal2);
  histo.push_back(h_PU0_cal_GEO2);
  histo.push_back(h_PU0_cal_GEO_recal2);
 
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 NN");
  leg_entry.push_back("PU=0 GEO");
  leg_entry.push_back("PU=0 GEO recalibr. C2D");

  TLegend* leg=new TLegend(0.4,0.15,0.7,0.5);
  leg->SetHeader("#splitline{p_T(gen. jet)>20 GeV}{1.6<|#eta(gen.jet)|<2.9}");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  
  vector<TGraphErrors*> graph;

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
  prof[0]->GetYaxis()->SetRangeUser(0.5,1.2);
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



  c->SaveAs("plots/profile_L1jet_response_eta_C2D_recal_PU0_cal2.pdf");  


}










void plot_profile_L1jet_resolution_pt_PU0_C2D_recal_cal(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

 TH2F* h_PU0_cal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",18,0,360,97,0.06,2);

  TH2F* h_PU0_cal_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","1.06*(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",18,0,360,97,0.06,2);

  TH2F* h_PU0_cal_GEO_recal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR_JetPU0cal/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.1*1.04*(4.16098 -1.00815e+00 * log(max(jets_pt[VBF_parton_jets],20)) + 7.59202e-02* pow(log(max(jets_pt[VBF_parton_jets],20)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",18,0,360,97,0.06,2);

 TH2F* h_PU0_cal2 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","(4.4374 -0.948102 * log(jets_raw_Luca_pt[VBF_parton_jets]) + .0686934* pow(log(jets_raw_Luca_pt[VBF_parton_jets]),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",18,0,360,97,0.06,2);

  TH2F* h_PU0_cal_GEO2 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","1.06*(4.4374 -0.948102 * log(jets_raw_Luca_pt[VBF_parton_jets]) + .0686934* pow(log(jets_raw_Luca_pt[VBF_parton_jets]),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",18,0,360,97,0.06,2);

  TH2F* h_PU0_cal_GEO_recal2 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR_JetPU0cal/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.1*1.04*(4.16098 -1.00815e+00 * log(jets_pt[VBF_parton_jets]) + 7.59202e-02* pow(log(jets_pt[VBF_parton_jets]),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",18,0,360,97,0.06,2);


  vector<TH2F*> histo;
  histo.push_back(h_PU0_cal);
  histo.push_back(h_PU0_cal_GEO);
  histo.push_back(h_PU0_cal_GEO_recal);
  histo.push_back(h_PU0_cal2);
  histo.push_back(h_PU0_cal_GEO2);
  histo.push_back(h_PU0_cal_GEO_recal2);
 
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 NN");
  leg_entry.push_back("PU=0 GEO");
  leg_entry.push_back("PU=0 GEO recalibr. C2D");
  leg_entry.push_back("PU=0 NN 2");
  leg_entry.push_back("PU=0 GEO 2");
  leg_entry.push_back("PU=0 GEO recalibr. C2D 2");


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
      cout<<"bin "<<j<<endl;
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


  c->SaveAs("plots/profile_L1jet_resolution_C2D_recal_pt_PU0.pdf");  


}







void plot_profile_L1jet_response_pt_PU200_C2D_recal(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  TH2F* h_PU0_raw_GEO_recal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR_JetPU0cal/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_cal_GEO_recal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR_JetPU0cal/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.1*1.04*(4.16098 -1.00815e+00 * log(jets_pt[VBF_parton_jets]) + 7.59202e-02* pow(log(jets_pt[VBF_parton_jets]),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU200_raw_GEO_recal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR_JetPU0cal/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

 TH2F* h_PU200_PUS_GEO_recal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR_JetPU0cal/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","max(jets_pt[VBF_parton_jets]-3*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);


 TH2F* h_PU200_PUS_cal_GEO_recal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR_JetPU0cal/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.1*1.04*(4.16098 -1.00815e+00 * log(max(jets_pt[VBF_parton_jets]-3*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 7.59202e-02* pow(log(max(jets_pt[VBF_parton_jets]-3*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-3*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);



 vector<TH2F*> histo;
 histo.push_back(h_PU0_raw_GEO_recal);
 histo.push_back(h_PU0_cal_GEO_recal);
 histo.push_back(h_PU200_raw_GEO_recal);
 histo.push_back(h_PU200_PUS_GEO_recal);
 histo.push_back(h_PU200_PUS_cal_GEO_recal);

  vector<TString> leg_entry;
  leg_entry.push_back("PU=0");
  leg_entry.push_back("PU=0 + jet calibr.");
  leg_entry.push_back("PU=200");
  leg_entry.push_back("PU=200 + PUS");
  leg_entry.push_back("PU=200 + PUS + jet calibr.");

 

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


  c->SaveAs("plots/profile_L1jet_response_pt_PU200_GEO_C2D_recal.pdf");  


}








void plot_profile_L1jet_response_eta_PU200_C2D_recal(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  TH2F* h_PU0_raw_GEO_recal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR_JetPU0cal/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);

  TH2F* h_PU0_cal_GEO_recal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR_JetPU0cal/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","1.1*1.04*(4.16098 -1.00815e+00 * log(jets_pt[VBF_parton_jets]) + 7.59202e-02* pow(log(jets_pt[VBF_parton_jets]),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);

  TH2F* h_PU200_raw_GEO_recal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR_JetPU0cal/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);

 TH2F* h_PU200_PUS_GEO_recal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR_JetPU0cal/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","max(jets_pt[VBF_parton_jets]-3*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);

 TH2F* h_PU200_PUS_cal_GEO_recal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR_JetPU0cal/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","1.1*1.04*(4.16098 -1.00815e+00 * log(max(jets_pt[VBF_parton_jets]-3*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 7.59202e-02* pow(log(max(jets_pt[VBF_parton_jets]-3*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-3*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);


 vector<TH2F*> histo;
 histo.push_back(h_PU0_raw_GEO_recal);
 histo.push_back(h_PU0_cal_GEO_recal);
 histo.push_back(h_PU200_raw_GEO_recal);
 histo.push_back(h_PU200_PUS_GEO_recal);
 histo.push_back(h_PU200_PUS_cal_GEO_recal);

  vector<TString> leg_entry;
  leg_entry.push_back("PU=0");
  leg_entry.push_back("PU=0 + jet calibr.");
  leg_entry.push_back("PU=200");
  leg_entry.push_back("PU=200 + PUS");
  leg_entry.push_back("PU=200 + PUS + jet calibr.");


 

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


  c->SaveAs("plots/profile_L1jet_response_eta_PU200_GEO_C2D_recal.pdf");  


}







void plot_profile_L1jet_resolution_pt_C2D_recal_PU200(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";


  //TH2F* h_PU0_cal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","(4.4374 -0.948102 * log(jets_raw_Luca_pt[VBF_parton_jets]) + .0686934* pow(log(jets_raw_Luca_pt[VBF_parton_jets]),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",18,0,360,97,0.06,2);

  //TH2F* h_PU0_cal_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","1.06*(4.4374 -0.948102 * log(jets_raw_Luca_pt[VBF_parton_jets]) + .0686934* pow(log(jets_raw_Luca_pt[VBF_parton_jets]),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",18,0,360,97,0.06,2);

  TH2F* h_PU0_cal_GEO_recal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR_JetPU0cal/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.1*1.04*(4.16098 -1.00815e+00 * log(jets_pt[VBF_parton_jets]) + 7.59202e-02* pow(log(jets_pt[VBF_parton_jets]),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",18,0,360,97,0.06,2);



  TH2F* h_PU200_PUS_cal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets]-jets_PU_subtr_cone_C3D[VBF_parton_jets],0)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets]-jets_PU_subtr_cone_C3D[VBF_parton_jets],0)),2) ) * max(jets_raw_Luca_pt[VBF_parton_jets]-jets_PU_subtr_cone_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+" && (jets_raw_Luca_pt[VBF_parton_jets]-jets_PU_subtr_cone_C3D[VBF_parton_jets])>0",18,0,360,100,0,2);

 TH2F* h_PU200_PUS_cal_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","1.06*(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) )* max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets]>0",18,0,360,97,0.06,2);


 TH2F* h_PU200_PUS_cal_GEO_recal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR_JetPU0cal/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.1*1.04*(4.16098 -1.00815e+00 * log(max(jets_pt[VBF_parton_jets]-3*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 7.59202e-02* pow(log(max(jets_pt[VBF_parton_jets]-3*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-3*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",18,0,360,97,0.06,2);


  vector<TH2F*> histo;
  //histo.push_back(h_PU0_cal);
  //histo.push_back(h_PU0_cal_GEO);
  histo.push_back(h_PU0_cal_GEO_recal);
  histo.push_back(h_PU200_PUS_cal);
  histo.push_back(h_PU200_PUS_cal_GEO);
  histo.push_back(h_PU200_PUS_cal_GEO_recal);

  vector<TString> leg_entry;
  //leg_entry.push_back("PU=0 NN");
  //leg_entry.push_back("PU=0 GEO");
  leg_entry.push_back("PU=0 GEO recalibr. C2D");
  leg_entry.push_back("PU=200 NN");
  leg_entry.push_back("PU=200 GEO");
  leg_entry.push_back("PU=200 GEO recalibr. C2D");


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


  c->SaveAs("plots/profile_L1jet_resolution_pt_C2D_recal_PU200.pdf");  






}





void plot_layer_jets_energy_fraction(){


  TH1F* h_GEO_fraction4 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR_new/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","layer_jets_energy_fraction[4]","",100,0,1);

  TH1F* h_GEO_recal_fraction4 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR_JetPU0cal/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","layer_jets_energy_fraction[4]","",100,0,1);

  TH1F* h_GEO_fraction10 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR_new/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","layer_jets_energy_fraction[10]","",100,0,1);

  TH1F* h_GEO_recal_fraction10 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR_JetPU0cal/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","layer_jets_energy_fraction[10]","",100,0,1);

  TH1F* h_GEO_fraction16 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR_new/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","layer_jets_energy_fraction[16]","",100,0,1);

  TH1F* h_GEO_recal_fraction16 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR_JetPU0cal/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","layer_jets_energy_fraction[16]","",100,0,1);

  TH1F* h_GEO_fraction28 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR_new/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","layer_jets_energy_fraction[28]","",100,0,1);

  TH1F* h_GEO_recal_fraction28 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR_JetPU0cal/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","layer_jets_energy_fraction[28]","",100,0,1);

  TH1F* h_GEO_fraction40 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR_new/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","layer_jets_energy_fraction[40]","",100,0,1);

  TH1F* h_GEO_recal_fraction40 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR_JetPU0cal/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","layer_jets_energy_fraction[40]","",100,0,1);

  vector<TH1F*> histo;
  histo.push_back(h_GEO_fraction4);
  histo.push_back(h_GEO_recal_fraction4);
  histo.push_back(h_GEO_fraction10);
  histo.push_back(h_GEO_recal_fraction10);
  histo.push_back(h_GEO_fraction16);
  histo.push_back(h_GEO_recal_fraction16);
  histo.push_back(h_GEO_fraction28);
  histo.push_back(h_GEO_recal_fraction28);
  histo.push_back(h_GEO_fraction40);
  histo.push_back(h_GEO_recal_fraction40);

  vector<TString> leg_entry;
  leg_entry.push_back("Old cal. layer 4");
  leg_entry.push_back("New cal. layer 4");
  leg_entry.push_back("Old cal. layer 10");
  leg_entry.push_back("New cal. layer 10");
  leg_entry.push_back("Old cal. layer 16");
  leg_entry.push_back("New cal. layer 16");
  leg_entry.push_back("Old cal. layer 28");
  leg_entry.push_back("New cal. layer 28");
  leg_entry.push_back("Old cal. layer 40");
  leg_entry.push_back("New cal. layer 40");

  TLegend* leg=new TLegend(0.5,0.4,0.8,0.85);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);

  for(unsigned int i=0;i<histo.size();i++){
    TH1F* h = histo[i];
    h->Scale(1/h->Integral());
    h->SetLineWidth(2);
    h->SetLineColor(i+1);
    if(i>3)
      h->SetLineColor(i+2);      
    if(i>7)
      h->SetLineColor(i+3);  
    leg->AddEntry(h,leg_entry[i]);
  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  TGaxis::SetMaxDigits(4);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  pad1->SetGridx();         // Vertical grid
  pad1->SetGridy();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd(); 


  //histo[0]->GetXaxis()->SetTitle("Energy fraction before layer");
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


  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetLeftMargin(0.15);
  pad2->SetBottomMargin(0.25);
  pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();

  vector<TH1F*> ratios;
  
  for(unsigned int i=0;i<histo.size()/2;i++){

    TH1F* ratio = (TH1F*)histo[2*i+1]->Clone();
    ratio->Divide(histo[2*i]);
    ratios.push_back(ratio);

  }
  
  ratios[0]->SetTitle("");
  ratios[0]->SetStats(0);

  ratios[0]->Draw();
  for(unsigned int i=0;i<ratios.size();i++)
    ratios[i]->Draw("same");
  
  ratios[0]->GetYaxis()->SetLabelSize(0.);
  ratios[0]->GetYaxis()->SetRangeUser(0.,2.);

  TGaxis *axis2 = new TGaxis( 0, 0.1, 0, 1.99, 0.1, 1.99, 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();  


 // Y axis ratio plot settings
  ratios[0]->GetYaxis()->SetTitle("New/Old");
  ratios[0]->GetYaxis()->SetNdivisions(505);
  ratios[0]->GetYaxis()->SetTitleSize(20);
  ratios[0]->GetYaxis()->SetTitleFont(43);
  ratios[0]->GetYaxis()->SetTitleOffset(1.5);
  ratios[0]->GetYaxis()->CenterTitle();

  // X axis ratio plot settings
  ratios[0]->GetXaxis()->SetTitleSize(17);
  ratios[0]->GetXaxis()->SetTitleFont(43);
  ratios[0]->GetXaxis()->SetTitleOffset(4.);
  ratios[0]->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  ratios[0]->GetXaxis()->SetLabelSize(15);
  ratios[0]->GetXaxis()->SetTitle("Energy fraction before layer");
  
  TLine *line = new TLine(ratios[0]->GetXaxis()->GetXmin(), 1, ratios[0]->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");


  c->SaveAs("plots/layer_jets_energy_fraction_JetPU0cal.pdf");  




}


