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
#include <TGraphAsymmErrors.h>
#include "Helpers.C"
#include <vector>

using namespace std;



void plot_profile_L1jet_response_pt_PU0(){

  TH2F* h = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]","VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20 && jets_raw_Luca_pt[VBF_parton_jets]>0",100,0,1000,100,0,2);

  h->Scale(1/h->Integral());
  h->SetStats(0);
  h->SetTitle("");
  
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  //c->SetLogz();
  h->GetXaxis()->SetTitle("p_{T}(gen. jet) [GeV]");
  h->GetYaxis()->SetTitle("p_{T}(L1)/p_{T}(gen. jet)");
  h->GetYaxis()->SetTitleOffset(1.7);
  //h->GetZaxis()->SetRangeUser(1e-9,1);
  h->Draw("colz");

  TProfile prof = *(h->ProfileX());
  prof.SetStats(0);
  prof.SetTitle("");
  //prof.BuildOptions(0,0,"s");
  prof.SetLineColor(kGreen);
  prof.SetLineWidth(2);
  prof.Draw("same");

  TH2F* h2 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]","VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20 && jets_raw_Luca_pt[VBF_parton_jets]>0",100,0,1000,100,0,2);

  TProfile prof2 = *(h2->ProfileX());
  prof2.SetStats(0);
  //prof.BuildOptions(0,0,"s");
  prof2.SetLineColor(kRed);
  prof2.SetLineWidth(2);
  prof2.Draw("same");

  TLatex *texl = new TLatex(2,2.02,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV PU=0");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  c->SaveAs("plots/profile_L1jet_response_pt_PU0.pdf");  


}








void plot_profile_L1jet_response_pt_PU200(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";


  TH2F* h_PU0_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+" && jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,100,0,2);
  TH2F* h_PU0_cal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+" && jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,100,0,2);

  TH2F* h_PU200_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+" && jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,100,0,2);
  TH2F* h_PU200_PUS_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","max(jets_raw_Luca_pt[VBF_parton_jets]-jets_PU_subtr_cone_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+" && (jets_raw_Luca_pt[VBF_parton_jets]-jets_PU_subtr_cone_C3D[VBF_parton_jets])>0",25,0,500,100,0,2);
  TH2F* h_PU200_PUS_cal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets]-jets_PU_subtr_cone_C3D[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets]-jets_PU_subtr_cone_C3D[VBF_parton_jets],20)),2) ) * max(jets_raw_Luca_pt[VBF_parton_jets]-jets_PU_subtr_cone_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+" && (jets_raw_Luca_pt[VBF_parton_jets]-jets_PU_subtr_cone_C3D[VBF_parton_jets])>0",25,0,500,100,0,2);

  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw);
  histo.push_back(h_PU0_cal);
  histo.push_back(h_PU200_raw);
  histo.push_back(h_PU200_PUS_raw);
  histo.push_back(h_PU200_PUS_cal);
  
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
  prof[0]->GetYaxis()->SetRangeUser(0,1.2);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(2.,1.21,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(0,1,500,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_response_pt_PU200.pdf");  


}








void plot_profile_L1jet_response_pt_PU200_eta2p1(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.1 && genjet_pt[VBF_parton_genjet]>20";


  TH2F* h_PU0_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut,25,0,500,100,0,2);
  TH2F* h_PU0_cal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut,25,0,500,100,0,2);

  TH2F* h_PU200_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut,25,0,500,100,0,2);
  TH2F* h_PU200_PUS_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","max(jets_raw_Luca_pt[VBF_parton_jets]-jets_PU_subtr_cone_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut,25,0,500,100,0,2);
  TH2F* h_PU200_PUS_cal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets]-jets_PU_subtr_cone_C3D[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets]-jets_PU_subtr_cone_C3D[VBF_parton_jets],20)),2) ) * max(jets_raw_Luca_pt[VBF_parton_jets]-jets_PU_subtr_cone_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut,25,0,500,100,0,2);

  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw);
  histo.push_back(h_PU0_cal);
  histo.push_back(h_PU200_raw);
  histo.push_back(h_PU200_PUS_raw);
  histo.push_back(h_PU200_PUS_cal);
  
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0");
  leg_entry.push_back("PU=0 + jet calibr.");
  leg_entry.push_back("PU=200");
  leg_entry.push_back("PU=200 + PUS");
  leg_entry.push_back("PU=200 + PUS + jet calibr.");

  TLegend* leg=new TLegend(0.4,0.15,0.7,0.5);
  leg->SetHeader("#splitline{p_T(gen. jet)>20 GeV}{1.6<|#eta(gen.jet)|<2.1}");
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

  TLatex *texl = new TLatex(2.,1.21,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(0,1,500,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_response_pt_PU200_eta2p1.pdf");  


}







void plot_profile_L1jet_response_pt_PU200_eta2p1_pt0(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.1 && genjet_pt[VBF_parton_genjet]>20";


  TH2F* h_PU0_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  TH2F* h_PU0_cal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU200_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  TH2F* h_PU200_PUS_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);
  TH2F* h_PU200_PUS_cal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)),2) ) * max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);

  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw);
  histo.push_back(h_PU0_cal);
  histo.push_back(h_PU200_raw);
  histo.push_back(h_PU200_PUS_raw);
  histo.push_back(h_PU200_PUS_cal);
  
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0");
  leg_entry.push_back("PU=0 + jet calibr.");
  leg_entry.push_back("PU=200");
  leg_entry.push_back("PU=200 + PUS");
  leg_entry.push_back("PU=200 + PUS + jet calibr.");

  TLegend* leg=new TLegend(0.4,0.15,0.7,0.5);
  leg->SetHeader("#splitline{p_T(gen. jet)>20 GeV}{1.6<|#eta(gen.jet)|<2.1}");
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

  TLatex *texl = new TLatex(2.,1.21,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(0,1,500,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_response_pt_PU200_eta2p1_pT0.pdf");  


}











void plot_profile_L1jet_response_pt_PU200_pt0(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";


  TH2F* h_PU0_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  TH2F* h_PU0_cal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU200_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  //TH2F* h_PU200_PUS0_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","max(jets_raw_Luca_pt[VBF_parton_jets]-jets_PU_subtr_cone_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_raw_Luca_pt[VBF_parton_jets]-jets_PU_subtr_cone_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);
  TH2F* h_PU200_PUS_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);
  TH2F* h_PU200_PUS_cal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)),2) ) * max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);

  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw);
  histo.push_back(h_PU0_cal);
  histo.push_back(h_PU200_raw);
  //histo.push_back(h_PU200_PUS0_raw);
  histo.push_back(h_PU200_PUS_raw);
  histo.push_back(h_PU200_PUS_cal);
  
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0");
  leg_entry.push_back("PU=0 + jet calibr.");
  leg_entry.push_back("PU=200");
  //leg_entry.push_back("PU=200 + PUS");
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


  c->SaveAs("plots/profile_L1jet_response_pt_PU200_pT0.pdf");  


}






void plot_profile_L1jet_response_pt_PU200_pt0_TC(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";


  TH2F* h_PU0_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  TH2F* h_PU0_cal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU200_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  TH2F* h_PU200_PUS0_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","max(jets_raw_Luca_pt[VBF_parton_jets]-jets_PU_subtr_cone_tc[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_raw_Luca_pt[VBF_parton_jets]-jets_PU_subtr_cone_tc[VBF_parton_jets])>0",25,0,500,97,0.06,2);
  TH2F* h_PU200_PUS_cal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets]-jets_PU_subtr_cone_tc[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets]-jets_PU_subtr_cone_tc[VBF_parton_jets],20)),2) ) * max(jets_raw_Luca_pt[VBF_parton_jets]-jets_PU_subtr_cone_tc[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_raw_Luca_pt[VBF_parton_jets]-jets_PU_subtr_cone_tc[VBF_parton_jets])>0",25,0,500,97,0.06,2);

  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw);
  histo.push_back(h_PU0_cal);
  histo.push_back(h_PU200_raw);
  histo.push_back(h_PU200_PUS0_raw);
  //histo.push_back(h_PU200_PUS_raw);
  histo.push_back(h_PU200_PUS_cal);
  
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0");
  leg_entry.push_back("PU=0 + jet calibr.");
  leg_entry.push_back("PU=200");
  leg_entry.push_back("PU=200 + PUS");
  //leg_entry.push_back("PU=200 + 2*PUS");
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
  prof[0]->GetYaxis()->SetRangeUser(0,1.2);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(2.,1.21,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(0,1,500,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_response_pt_PU200_pT0_TC.pdf");  


}






void plot_profile_L1jet_response_eta_PU200_pt0(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";


  TH2F* h_PU0_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","abs(genjet_eta[VBF_parton_genjet])","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",15,1.55,2.95,97,0.06,2);
  TH2F* h_PU0_cal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","abs(genjet_eta[VBF_parton_genjet])","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",15,1.55,2.95,97,0.06,2);

  TH2F* h_PU200_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","abs(genjet_eta[VBF_parton_genjet])","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",15,1.55,2.95,97,0.06,2);
  //TH2F* h_PU200_PUS0_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","abs(genjet_eta[VBF_parton_genjet])","max(jets_raw_Luca_pt[VBF_parton_jets]-jets_PU_subtr_cone_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_raw_Luca_pt[VBF_parton_jets]-jets_PU_subtr_cone_C3D[VBF_parton_jets])>0",15,1.55,2.95,97,0.06,2);
 TH2F* h_PU200_PUS_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","abs(genjet_eta[VBF_parton_genjet])","max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets])>0",15,1.55,2.95,97,0.06,2);
  TH2F* h_PU200_PUS_cal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","abs(genjet_eta[VBF_parton_genjet])","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)),2) ) * max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets])>0",15,1.55,2.95,97,0.06,2);

  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw);
  histo.push_back(h_PU0_cal);
  histo.push_back(h_PU200_raw);
  //histo.push_back(h_PU200_PUS0_raw);
  histo.push_back(h_PU200_PUS_raw);
  histo.push_back(h_PU200_PUS_cal);
  
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0");
  leg_entry.push_back("PU=0 + jet calibr.");
  leg_entry.push_back("PU=200");
  //leg_entry.push_back("PU=200 + PUS");
  leg_entry.push_back("PU=200 + PUS");
  leg_entry.push_back("PU=200 + PUS + jet calibr.");

  TLegend* leg=new TLegend(0.4,0.12,0.7,0.48);
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
  prof[0]->GetYaxis()->SetRangeUser(-0.2,1.2);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(1.57,1.21,"CMS Simulation Preliminary, VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(1.55,1,2.95,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_response_eta_PU200_pT0.pdf");  


}






void plot_profile_L1jet_response_eta_PU200_pt0_TC(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";


  TH2F* h_PU0_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","abs(genjet_eta[VBF_parton_genjet])","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",15,1.55,2.95,97,0.06,2);
  TH2F* h_PU0_cal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","abs(genjet_eta[VBF_parton_genjet])","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",15,1.55,2.95,97,0.06,2);

  TH2F* h_PU200_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","abs(genjet_eta[VBF_parton_genjet])","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",15,1.55,2.95,97,0.06,2);
  TH2F* h_PU200_PUS0_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","abs(genjet_eta[VBF_parton_genjet])","max(jets_raw_Luca_pt[VBF_parton_jets]-jets_PU_subtr_cone_tc[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_raw_Luca_pt[VBF_parton_jets]-jets_PU_subtr_cone_tc[VBF_parton_jets])>0",15,1.55,2.95,97,0.06,2);
  TH2F* h_PU200_PUS_cal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","abs(genjet_eta[VBF_parton_genjet])","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets]-jets_PU_subtr_cone_tc[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets]-jets_PU_subtr_cone_tc[VBF_parton_jets],20)),2) ) * max(jets_raw_Luca_pt[VBF_parton_jets]-jets_PU_subtr_cone_tc[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_raw_Luca_pt[VBF_parton_jets]-jets_PU_subtr_cone_tc[VBF_parton_jets])>0",15,1.55,2.95,97,0.06,2);

  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw);
  histo.push_back(h_PU0_cal);
  histo.push_back(h_PU200_raw);
  histo.push_back(h_PU200_PUS0_raw);
  //histo.push_back(h_PU200_PUS_raw);
  histo.push_back(h_PU200_PUS_cal);
  
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0");
  leg_entry.push_back("PU=0 + jet calibr.");
  leg_entry.push_back("PU=200");
  leg_entry.push_back("PU=200 + PUS");
  //leg_entry.push_back("PU=200 + 2*PUS");
  leg_entry.push_back("PU=200 + PUS + jet calibr.");

  TLegend* leg=new TLegend(0.4,0.12,0.7,0.48);
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
  prof[0]->GetYaxis()->SetRangeUser(-0.2,1.2);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(1.57,1.21,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(1.55,1,2.95,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_response_eta_PU200_pT0_TC.pdf");  


}







void plot_turnons_L1SingleJet(int L1pt){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  double x[21]={0,20,40,60,80,100,110,120,130,140,150,160,170,180,190,200,220,250,300,400,500};
  int nbins=20;



  TH1F* h_PU0_denom = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  //TH1F* h_PU0_raw = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]",cut+Form("&& jets_raw_Luca_pt[VBF_parton_jets]>%i",L1pt),nbins,x);
  //TGraphAsymmErrors* gr_PU0_raw = new TGraphAsymmErrors();
  //gr_PU0_raw->Divide(h_PU0_raw,h_PU0_denom);
  TH1F* h_PU0_cal = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]",cut+Form("&& (4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]>%i",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU0_cal = new TGraphAsymmErrors();
  gr_PU0_cal->Divide(h_PU0_cal,h_PU0_denom);

  TH1F* h_PU200_denom = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  /*TH1F* h_PU200_raw = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]",cut+Form("&& jets_raw_Luca_pt[VBF_parton_jets]>%i",L1pt),16,x);
  TGraphAsymmErrors* gr_PU200_raw = new TGraphAsymmErrors();
  gr_PU200_raw->Divide(h_PU200_raw,h_PU200_denom);
  TH1F* h_PU200_PUS = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]",cut+Form("&& max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)>%i",L1pt),16,x);
  TGraphAsymmErrors* gr_PU200_PUS = new TGraphAsymmErrors();
  gr_PU200_PUS->Divide(h_PU200_PUS,h_PU200_denom);*/
  TH1F* h_PU200_PUS_cal = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]",cut+Form("&& (4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)),2) ) * max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)>%i",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU200_PUS_cal = new TGraphAsymmErrors();
  gr_PU200_PUS_cal->Divide(h_PU200_PUS_cal,h_PU200_denom);
  


  vector<TGraphAsymmErrors*> turnons;
  //turnons.push_back(gr_PU0_raw);
  turnons.push_back(gr_PU0_cal);
  //turnons.push_back(gr_PU200_raw);
  //turnons.push_back(gr_PU200_PUS);
  turnons.push_back(gr_PU200_PUS_cal);
  
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0");
  //leg_entry.push_back("PU=0 + jet calibr.");
  leg_entry.push_back("PU=200");
  //leg_entry.push_back("PU=200 + PUS");
  //leg_entry.push_back("#splitline{PU=200 + PUS}{+ jet calibr.}");

  TLegend* leg=new TLegend(0.5,0.12,0.8,0.55);
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

  TLatex *texl = new TLatex(1.57,1.01,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");
  gPad->SetTicks();


  c->SaveAs(Form("plots/turnons_L1SingleJet%i.pdf",L1pt));  


}




void plot_turnons_L1SingleJet_eta2p1(int L1pt){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.1 && genjet_pt[VBF_parton_genjet]>20";

  double x[17]={0,50,80,100,120,130,140,150,160,170,180,200,220,260,300,400,500};

  TH1F* h_PU0_denom = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]",cut,16,x);
  TH1F* h_PU0_raw = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]",cut+Form("&& jets_raw_Luca_pt[VBF_parton_jets]>%i",L1pt),16,x);
  TGraphAsymmErrors* gr_PU0_raw = new TGraphAsymmErrors();
  gr_PU0_raw->Divide(h_PU0_raw,h_PU0_denom);
  TH1F* h_PU0_cal = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]",cut+Form("&& (4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]>%i",L1pt),16,x);
  TGraphAsymmErrors* gr_PU0_cal = new TGraphAsymmErrors();
  gr_PU0_cal->Divide(h_PU0_cal,h_PU0_denom);

  TH1F* h_PU200_denom = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]",cut,16,x);
  TH1F* h_PU200_raw = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]",cut+Form("&& jets_raw_Luca_pt[VBF_parton_jets]>%i",L1pt),16,x);
  TGraphAsymmErrors* gr_PU200_raw = new TGraphAsymmErrors();
  gr_PU200_raw->Divide(h_PU200_raw,h_PU200_denom);
  TH1F* h_PU200_PUS = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]",cut+Form("&& max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)>%i",L1pt),16,x);
  TGraphAsymmErrors* gr_PU200_PUS = new TGraphAsymmErrors();
  gr_PU200_PUS->Divide(h_PU200_PUS,h_PU200_denom);
  TH1F* h_PU200_PUS_cal = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]",cut+Form("&& (4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)),2) ) * max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)>%i",L1pt),16,x);
  TGraphAsymmErrors* gr_PU200_PUS_cal = new TGraphAsymmErrors();
  gr_PU200_PUS_cal->Divide(h_PU200_PUS_cal,h_PU200_denom);
  


  vector<TGraphAsymmErrors*> turnons;
  turnons.push_back(gr_PU0_raw);
  turnons.push_back(gr_PU0_cal);
  turnons.push_back(gr_PU200_raw);
  turnons.push_back(gr_PU200_PUS);
  turnons.push_back(gr_PU200_PUS_cal);
  
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0");
  leg_entry.push_back("PU=0 + jet calibr.");
  leg_entry.push_back("PU=200");
  leg_entry.push_back("PU=200 + PUS");
  leg_entry.push_back("#splitline{PU=200 + PUS}{+ jet calibr.}");

  TLegend* leg=new TLegend(0.5,0.12,0.8,0.55);
  leg->SetHeader(Form("#splitline{L1_SingleJet%i}{1.6<|#eta(gen.jet)|<2.1}",L1pt));
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
  turnons[0]->GetXaxis()->SetLimits(0,500);
  turnons[0]->GetYaxis()->SetTitle("Efficiency");
  turnons[0]->GetYaxis()->SetTitleOffset(1.7);
  turnons[0]->GetYaxis()->SetRangeUser(0.,1.);
  turnons[0]->SetTitle("");
  turnons[0]->Draw();
  for(unsigned int i=1;i<turnons.size();i++)
    turnons[i]->Draw("same");
  leg->Draw("same");
  gPad->SetGrid();
  
  TLine* line = new TLine(0,0.95,500,0.95);
  line->Draw("same");

  TLatex *texl = new TLatex(1.57,1.01,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");
  gPad->SetTicks();


  c->SaveAs(Form("plots/turnons_L1SingleJet%i_eta2p1.pdf",L1pt));  


}






void plot_turnons_L1SingleJet_eta2p9(int L1pt){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>2.1 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  double x[17]={0,50,80,100,120,130,140,150,160,170,180,200,220,260,300,400,500};

  TH1F* h_PU0_denom = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]",cut,16,x);
  TH1F* h_PU0_raw = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]",cut+Form("&& jets_raw_Luca_pt[VBF_parton_jets]>%i",L1pt),16,x);
  TGraphAsymmErrors* gr_PU0_raw = new TGraphAsymmErrors();
  gr_PU0_raw->Divide(h_PU0_raw,h_PU0_denom);
  TH1F* h_PU0_cal = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]",cut+Form("&& (4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]>%i",L1pt),16,x);
  TGraphAsymmErrors* gr_PU0_cal = new TGraphAsymmErrors();
  gr_PU0_cal->Divide(h_PU0_cal,h_PU0_denom);

  TH1F* h_PU200_denom = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]",cut,16,x);
  TH1F* h_PU200_raw = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]",cut+Form("&& jets_raw_Luca_pt[VBF_parton_jets]>%i",L1pt),16,x);
  TGraphAsymmErrors* gr_PU200_raw = new TGraphAsymmErrors();
  gr_PU200_raw->Divide(h_PU200_raw,h_PU200_denom);
  TH1F* h_PU200_PUS = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]",cut+Form("&& max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)>%i",L1pt),16,x);
  TGraphAsymmErrors* gr_PU200_PUS = new TGraphAsymmErrors();
  gr_PU200_PUS->Divide(h_PU200_PUS,h_PU200_denom);
  TH1F* h_PU200_PUS_cal = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]",cut+Form("&& (4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)),2) ) * max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)>%i",L1pt),16,x);
  TGraphAsymmErrors* gr_PU200_PUS_cal = new TGraphAsymmErrors();
  gr_PU200_PUS_cal->Divide(h_PU200_PUS_cal,h_PU200_denom);
  


  vector<TGraphAsymmErrors*> turnons;
  turnons.push_back(gr_PU0_raw);
  turnons.push_back(gr_PU0_cal);
  turnons.push_back(gr_PU200_raw);
  turnons.push_back(gr_PU200_PUS);
  turnons.push_back(gr_PU200_PUS_cal);
  
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0");
  leg_entry.push_back("PU=0 + jet calibr.");
  leg_entry.push_back("PU=200");
  leg_entry.push_back("PU=200 + PUS");
  leg_entry.push_back("#splitline{PU=200 + PUS}{+ jet calibr.}");

  TLegend* leg=new TLegend(0.5,0.12,0.8,0.55);
  leg->SetHeader(Form("#splitline{L1_SingleJet%i}{2.1<|#eta(gen.jet)|<2.9}",L1pt));
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
  turnons[0]->GetXaxis()->SetLimits(0,500);
  turnons[0]->GetYaxis()->SetTitle("Efficiency");
  turnons[0]->GetYaxis()->SetTitleOffset(1.7);
  turnons[0]->GetYaxis()->SetRangeUser(0.,1.);
  turnons[0]->SetTitle("");
  turnons[0]->Draw();
  for(unsigned int i=1;i<turnons.size();i++)
    turnons[i]->Draw("same");
  leg->Draw("same");
  gPad->SetGrid();
  
  TLine* line = new TLine(0,0.95,500,0.95);
  line->Draw("same");

  TLatex *texl = new TLatex(1.57,1.01,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");
  gPad->SetTicks();


  c->SaveAs(Form("plots/turnons_L1SingleJet%i_eta2p9.pdf",L1pt));  


}


















void plot_profile_L1jet_response_pt_PU0_etabins(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  TH2F* h_PU0_raw_eta0 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<1.8",25,0,500,97,0.06,2);
  TH2F* h_PU0_raw_eta1 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0 && abs(genjet_eta[VBF_parton_genjet])>1.8 && abs(genjet_eta[VBF_parton_genjet])<2.0",25,0,500,97,0.06,2);
  TH2F* h_PU0_raw_eta2 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0 && abs(genjet_eta[VBF_parton_genjet])>2.0 && abs(genjet_eta[VBF_parton_genjet])<2.2",25,0,500,97,0.06,2);
  TH2F* h_PU0_raw_eta3 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0 && abs(genjet_eta[VBF_parton_genjet])>2.2 && abs(genjet_eta[VBF_parton_genjet])<2.4",25,0,500,97,0.06,2);
  TH2F* h_PU0_raw_eta4 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0 && abs(genjet_eta[VBF_parton_genjet])>2.4 && abs(genjet_eta[VBF_parton_genjet])<2.6",25,0,500,97,0.06,2);
  TH2F* h_PU0_raw_eta5 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0 && abs(genjet_eta[VBF_parton_genjet])>2.6 && abs(genjet_eta[VBF_parton_genjet])<2.8",25,0,500,97,0.06,2);

  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw_eta0);
  histo.push_back(h_PU0_raw_eta1);
  histo.push_back(h_PU0_raw_eta2);
  histo.push_back(h_PU0_raw_eta3);
  histo.push_back(h_PU0_raw_eta4);
  histo.push_back(h_PU0_raw_eta5);
  
  vector<TString> leg_entry;
  leg_entry.push_back("1.6<|#eta|<1.8");
  leg_entry.push_back("1.8<|#eta|<2.0");
  leg_entry.push_back("2.0<|#eta|<2.2");
  leg_entry.push_back("2.2<|#eta|<1.4");
  leg_entry.push_back("2.4<|#eta|<2.6");
  leg_entry.push_back("2.6<|#eta|<2.8");


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

  TLatex *texl = new TLatex(2.,1.21,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(0,1,500,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_response_pt_PU0_etabins.pdf");  


}











void plot_profile_L1jet_response_pt_PU200_ncl3Dbins(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  TH2F* h_PU200_PUS_bin0 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets]>0 && cl3d_n<600",25,0,500,97,0.06,2);
  TH2F* h_PU200_PUS_bin1 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets]>0 && cl3d_n>600 && cl3d_n<700",25,0,500,97,0.06,2);
  TH2F* h_PU200_PUS_bin2 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets]>0 && cl3d_n>700 && cl3d_n<800",25,0,500,97,0.06,2);
  TH2F* h_PU200_PUS_bin3 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets]>0 && cl3d_n>800 && cl3d_n<900",25,0,500,97,0.06,2);
  TH2F* h_PU200_PUS_bin4 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets]>0 && cl3d_n>900",25,0,500,97,0.06,2);
 

  vector<TH2F*> histo;
  histo.push_back(h_PU200_PUS_bin0);
  histo.push_back(h_PU200_PUS_bin1);
  histo.push_back(h_PU200_PUS_bin2);
  histo.push_back(h_PU200_PUS_bin3);
  histo.push_back(h_PU200_PUS_bin4);

  
  vector<TString> leg_entry;
  leg_entry.push_back("#C3D<600");
  leg_entry.push_back("600<#C3D<700");
  leg_entry.push_back("700<#C3D<800");
  leg_entry.push_back("800<#C3D<900");
  leg_entry.push_back("900<#C3D");


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

  TLatex *texl = new TLatex(2.,1.21,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(0,1,500,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_response_pt_PU0_ncl3Dbins.pdf");  


}




void plot_turnons_L1SingleJet_PU140(int L1pt){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  double x[17]={0,50,80,100,120,130,140,150,160,170,180,200,220,260,300,400,500};

  TH1F* h_PU0_denom = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]",cut,16,x);
  TH1F* h_PU0_raw = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]",cut+Form("&& jets_raw_Luca_pt[VBF_parton_jets]>%i",L1pt),16,x);
  TGraphAsymmErrors* gr_PU0_raw = new TGraphAsymmErrors();
  gr_PU0_raw->Divide(h_PU0_raw,h_PU0_denom);
  TH1F* h_PU0_cal = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]",cut+Form("&& (4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]>%i",L1pt),16,x);
  TGraphAsymmErrors* gr_PU0_cal = new TGraphAsymmErrors();
  gr_PU0_cal->Divide(h_PU0_cal,h_PU0_denom);

  TH1F* h_PU140_denom = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU140/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]",cut,16,x);
  TH1F* h_PU140_raw = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU140/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]",cut+Form("&& jets_raw_Luca_pt[VBF_parton_jets]>%i",L1pt),16,x);
  TGraphAsymmErrors* gr_PU140_raw = new TGraphAsymmErrors();
  gr_PU140_raw->Divide(h_PU140_raw,h_PU140_denom);
  TH1F* h_PU140_PUS = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU140/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]",cut+Form("&& max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)>%i",L1pt),16,x);
  TGraphAsymmErrors* gr_PU140_PUS = new TGraphAsymmErrors();
  gr_PU140_PUS->Divide(h_PU140_PUS,h_PU140_denom);
  TH1F* h_PU140_PUS_cal = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU140/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]",cut+Form("&& (4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)),2) ) * max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)>%i",L1pt),16,x);
  TGraphAsymmErrors* gr_PU140_PUS_cal = new TGraphAsymmErrors();
  gr_PU140_PUS_cal->Divide(h_PU140_PUS_cal,h_PU140_denom);
  


  vector<TGraphAsymmErrors*> turnons;
  turnons.push_back(gr_PU0_raw);
  turnons.push_back(gr_PU0_cal);
  turnons.push_back(gr_PU140_raw);
  turnons.push_back(gr_PU140_PUS);
  turnons.push_back(gr_PU140_PUS_cal);
  
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0");
  leg_entry.push_back("PU=0 + jet calibr.");
  leg_entry.push_back("PU=140");
  leg_entry.push_back("PU=140 + PUS");
  leg_entry.push_back("#splitline{PU=140 + PUS}{+ jet calibr.}");

  TLegend* leg=new TLegend(0.5,0.12,0.8,0.55);
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
  turnons[0]->GetXaxis()->SetLimits(0,500);
  turnons[0]->GetYaxis()->SetTitle("Efficiency");
  turnons[0]->GetYaxis()->SetTitleOffset(1.7);
  turnons[0]->GetYaxis()->SetRangeUser(0.,1.);
  turnons[0]->SetTitle("");
  turnons[0]->Draw();
  for(unsigned int i=1;i<turnons.size();i++)
    turnons[i]->Draw("same");
  leg->Draw("same");
  gPad->SetGrid();
  
  TLine* line = new TLine(0,0.95,500,0.95);
  line->Draw("same");

  TLatex *texl = new TLatex(1.57,1.01,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");
  gPad->SetTicks();


  c->SaveAs(Form("plots/turnons_L1SingleJet%i_PU140.pdf",L1pt));  


}







void plot_profile_L1jet_response_pt_PU0_GEO(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";


  TH2F* h_PU0_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  TH2F* h_PU0_cal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);


  TH2F* h_PU0_raw_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  TH2F* h_PU0_cal_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","1.06*(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);


  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw);
  histo.push_back(h_PU0_raw_GEO);
  histo.push_back(h_PU0_cal);
  histo.push_back(h_PU0_cal_GEO);
  
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 NN");
  leg_entry.push_back("PU=0 GEO");
  leg_entry.push_back("PU=0 + jet calibr. NN");
  leg_entry.push_back("PU=0 + jet calibr. GEO");
 

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


  c->SaveAs("plots/profile_L1jet_response_pt_PU0_C2D_dR.pdf");  


}









void plot_profile_L1jet_response_eta_PU0_GEO(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

 TH2F* h_PU0_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","abs(genjet_eta[VBF_parton_genjet])","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",15,1.55,2.95,97,0.06,2);
  TH2F* h_PU0_cal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","abs(genjet_eta[VBF_parton_genjet])","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",15,1.55,2.95,97,0.06,2);


  TH2F* h_PU0_raw_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","abs(genjet_eta[VBF_parton_genjet])","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",15,1.55,2.95,97,0.06,2);
  TH2F* h_PU0_cal_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","abs(genjet_eta[VBF_parton_genjet])","1.06*(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",15,1.55,2.95,97,0.06,2);


 vector<TH2F*> histo;
  histo.push_back(h_PU0_raw);
  histo.push_back(h_PU0_raw_GEO);
  histo.push_back(h_PU0_cal);
  histo.push_back(h_PU0_cal_GEO);
  
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 NN");
  leg_entry.push_back("PU=0 GEO");
  leg_entry.push_back("PU=0 + jet calibr. NN");
  leg_entry.push_back("PU=0 + jet calibr. GEO");


  TLegend* leg=new TLegend(0.4,0.12,0.7,0.48);
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
  prof[0]->GetYaxis()->SetRangeUser(-0.2,1.2);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(1.57,1.21,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(1.55,1,2.95,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_response_eta_PU0_C2D_dR.pdf");  



}









void plot_profile_L1jet_response_pt_PU200_GEO(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";


  TH2F* h_PU0_raw_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  //TH2F* h_PU0_cal_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","1.06*(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  
  TH2F* h_PU0_cal_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","1.06*(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],0)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],0)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU200_raw_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);


 TH2F* h_PU200_PUS_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);

 //TH2F* h_PU200_PUS_cal_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","1.06*(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],20)),2) )* max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets]>0",25,0,500,97,0.06,2);

 TH2F* h_PU200_PUS_cal_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","1.06*(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) )* max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets]>0",25,0,500,97,0.06,2);


 vector<TH2F*> histo;
 histo.push_back(h_PU0_raw_GEO);
 histo.push_back(h_PU0_cal_GEO);
 histo.push_back(h_PU200_raw_GEO);
 histo.push_back(h_PU200_PUS_GEO);
 histo.push_back(h_PU200_PUS_cal_GEO);

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


  c->SaveAs("plots/profile_L1jet_response_pt_PU200_GEO.pdf");  


}










void plot_profile_L1jet_response_eta_PU200_GEO(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";
 
 TH2F* h_PU0_raw_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","abs(genjet_eta[VBF_parton_genjet])","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",15,1.55,2.95,97,0.06,2);

 TH2F* h_PU0_cal_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","abs(genjet_eta[VBF_parton_genjet])","1.06*(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",15,1.55,2.95,97,0.06,2);

 TH2F* h_PU200_raw_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","abs(genjet_eta[VBF_parton_genjet])","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",15,1.55,2.95,97,0.06,2);

 TH2F* h_PU200_PUS_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","abs(genjet_eta[VBF_parton_genjet])","max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets]>0",15,1.55,2.95,97,0.06,2);

 TH2F* h_PU200_PUS_cal_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","abs(genjet_eta[VBF_parton_genjet])","1.06*(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],20)),2) )* max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets]>0",15,1.55,2.95,97,0.06,2);

 vector<TH2F*> histo;
 histo.push_back(h_PU0_raw_GEO);
 histo.push_back(h_PU0_cal_GEO);
 histo.push_back(h_PU200_raw_GEO);
 histo.push_back(h_PU200_PUS_GEO);
 histo.push_back(h_PU200_PUS_cal_GEO);

  vector<TString> leg_entry;
  leg_entry.push_back("PU=0");
  leg_entry.push_back("PU=0 + jet calibr.");
  leg_entry.push_back("PU=200");
  leg_entry.push_back("PU=200 + PUS");
  leg_entry.push_back("PU=200 + PUS + jet calibr.");



  TLegend* leg=new TLegend(0.4,0.12,0.7,0.48);
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

  TLatex *texl = new TLatex(1.57,1.21,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(1.55,1,2.95,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_response_eta_PU200_GEO.pdf");  



}











void plot_turnons_L1SingleJet_GEO(int L1pt){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  //double x[17]={0,50,80,100,120,130,140,150,160,170,180,200,220,260,300,400,500};
  double x[18]={0,40,60,70,80,90,100,110,120,130,140,160,180,200,250,300,400,500};
  int nbins=17;

  TH1F* h_PU0_denom = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU0_cal = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]",cut+Form("&& (4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]>%i",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU0_cal = new TGraphAsymmErrors();
  gr_PU0_cal->Divide(h_PU0_cal,h_PU0_denom);

  TH1F* h_PU200_denom = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_PUS_cal = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]",cut+Form("&& (4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)),2) ) * max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)>%i",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU200_PUS_cal = new TGraphAsymmErrors();
  gr_PU200_PUS_cal->Divide(h_PU200_PUS_cal,h_PU200_denom);


  TH1F* h_PU0_denom_GEO = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU0_cal_GEO = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]",cut+Form("&& 1.06*(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]>%i",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU0_cal_GEO = new TGraphAsymmErrors();
  gr_PU0_cal_GEO->Divide(h_PU0_cal_GEO,h_PU0_denom_GEO);

  TH1F* h_PU200_denom_GEO = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_PUS_cal_GEO = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]",cut+Form("&& 1.06*(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)),2) ) * max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)>%i",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU200_PUS_cal_GEO = new TGraphAsymmErrors();
  gr_PU200_PUS_cal_GEO->Divide(h_PU200_PUS_cal_GEO,h_PU200_denom_GEO);
  


  vector<TGraphAsymmErrors*> turnons;
  turnons.push_back(gr_PU0_cal);
  turnons.push_back(gr_PU200_PUS_cal);
  turnons.push_back(gr_PU0_cal_GEO);
  turnons.push_back(gr_PU200_PUS_cal_GEO);
  
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 NN");
  leg_entry.push_back("PU=200 NN");
  leg_entry.push_back("PU=0 GEO");
  leg_entry.push_back("PU=200 GEO");


  TLegend* leg=new TLegend(0.5,0.12,0.8,0.55);
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
  turnons[0]->GetXaxis()->SetLimits(0,500);
  turnons[0]->GetYaxis()->SetTitle("Efficiency");
  turnons[0]->GetYaxis()->SetTitleOffset(1.7);
  turnons[0]->GetYaxis()->SetRangeUser(0.,1.);
  turnons[0]->SetTitle("");
  turnons[0]->Draw();
  for(unsigned int i=1;i<turnons.size();i++)
    turnons[i]->Draw("same");
  leg->Draw("same");
  gPad->SetGrid();
  
  TLine* line = new TLine(0,0.95,500,0.95);
  line->Draw("same");

  TLatex *texl = new TLatex(1.57,1.01,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");
  gPad->SetTicks();


  c->SaveAs(Form("plots/turnons_L1SingleJet%i_GEO.pdf",L1pt));  


}









void plot_turnons_L1SingleJet_NN_GEO(int L1pt_NN, int L1pt_GEO){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  //double x[17]={0,50,80,100,120,130,140,150,160,170,180,200,220,260,300,400,500};
  double x[18]={0,40,60,70,80,90,100,110,120,130,140,160,180,200,250,300,400,500};
  int nbins=17;

  TH1F* h_PU0_denom = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU0_cal = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]",cut+Form("&& (4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]>%i",L1pt_NN),nbins,x);
  TGraphAsymmErrors* gr_PU0_cal = new TGraphAsymmErrors();
  gr_PU0_cal->Divide(h_PU0_cal,h_PU0_denom);

  TH1F* h_PU200_denom = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_PUS_cal = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]",cut+Form("&& (4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)),2) ) * max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)>%i",L1pt_NN),nbins,x);
  TGraphAsymmErrors* gr_PU200_PUS_cal = new TGraphAsymmErrors();
  gr_PU200_PUS_cal->Divide(h_PU200_PUS_cal,h_PU200_denom);


  TH1F* h_PU0_denom_GEO = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU0_cal_GEO = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]",cut+Form("&& 1.06*(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]>%i",L1pt_GEO),nbins,x);
  TGraphAsymmErrors* gr_PU0_cal_GEO = new TGraphAsymmErrors();
  gr_PU0_cal_GEO->Divide(h_PU0_cal_GEO,h_PU0_denom_GEO);

  TH1F* h_PU200_denom_GEO = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_PUS_cal_GEO = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]",cut+Form("&& 1.06*(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)),2) ) * max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)>%i",L1pt_GEO),nbins,x);
  TGraphAsymmErrors* gr_PU200_PUS_cal_GEO = new TGraphAsymmErrors();
  gr_PU200_PUS_cal_GEO->Divide(h_PU200_PUS_cal_GEO,h_PU200_denom_GEO);
  


  vector<TGraphAsymmErrors*> turnons;
  turnons.push_back(gr_PU0_cal);
  turnons.push_back(gr_PU200_PUS_cal);
  turnons.push_back(gr_PU0_cal_GEO);
  turnons.push_back(gr_PU200_PUS_cal_GEO);
  
  vector<TString> leg_entry;
  leg_entry.push_back(Form("PU=0 NN L1_SingleJet%i",L1pt_NN));
  leg_entry.push_back(Form("PU=200 NN L1_SingleJet%i",L1pt_NN));
  leg_entry.push_back(Form("PU=0 GEO L1_SingleJet%i",L1pt_GEO));
  leg_entry.push_back(Form("PU=200 GEO L1_SingleJet%i",L1pt_GEO));


  TLegend* leg=new TLegend(0.35,0.12,0.85,0.55);
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
  turnons[0]->GetXaxis()->SetLimits(0,500);
  turnons[0]->GetYaxis()->SetTitle("Efficiency");
  turnons[0]->GetYaxis()->SetTitleOffset(1.7);
  turnons[0]->GetYaxis()->SetRangeUser(0.,1.);
  turnons[0]->SetTitle("");
  turnons[0]->Draw();
  for(unsigned int i=1;i<turnons.size();i++)
    turnons[i]->Draw("same");
  leg->Draw("same");
  gPad->SetGrid();
  
  TLine* line = new TLine(0,0.95,500,0.95);
  line->Draw("same");

  TLatex *texl = new TLatex(1.57,1.01,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");
  gPad->SetTicks();


  c->SaveAs(Form("plots/turnons_L1SingleJet%i_NN_L1SingleJet%i_GEO.pdf",L1pt_NN,L1pt_GEO));  


}






void plot_profile_L1jet_response_pt_PU200_GEO_JetCalPU200(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  TH2F* h_PU200_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_core_*.root","jets","genjet_pt[VBF_parton_genjet]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);


  TH2F* h_PU200_raw_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU200_raw_GEO_JetCalPU0 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR_JetPU0cal/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU200_raw_GEO_TowerMap_3cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_3cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU200_raw_GEO_TowerMap_6cm = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_TowerMap_GEO_6cm/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  vector<TH2F*> histo;
  histo.push_back(h_PU200_raw);
  histo.push_back(h_PU200_raw_GEO);
  histo.push_back(h_PU200_raw_GEO_JetCalPU0);
  histo.push_back(h_PU200_raw_GEO_TowerMap_3cm);
  histo.push_back(h_PU200_raw_GEO_TowerMap_6cm);

  vector<TString> leg_entry;
  leg_entry.push_back("PU=200 NN");
  leg_entry.push_back("PU=200 GEO");
  leg_entry.push_back("PU=200 GEO + jet calibr. PU0");
  leg_entry.push_back("PU=200 GEO TowerMap 3cm");
  leg_entry.push_back("PU=200 GEO TowerMap 6cm");

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


  c->SaveAs("plots/profile_L1jet_response_pt_PU200_GEO_JetCalPU200.pdf");  


}







void plot_profile_L1jet_response_pt_PU0_GEO_JetCalPU0(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  TH2F* h_PU0_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_core_*.root","jets","genjet_pt[VBF_parton_genjet]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_raw_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_raw_GEO_JetCalPU0 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR_JetPU0cal/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);


  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw);
  histo.push_back(h_PU0_raw_GEO);
  histo.push_back(h_PU0_raw_GEO_JetCalPU0);

  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 NN");
  leg_entry.push_back("PU=0 GEO");
  leg_entry.push_back("PU=0 GEO + jet calibr. PU0");


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


  c->SaveAs("plots/profile_L1jet_response_pt_PU0_GEO_JetCalPU0.pdf");  


}











void plot_turnons_L1SingleJet_GEO_C2D_recal_PU0(int L1pt){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  double x[18]={0,40,60,70,80,90,100,110,120,130,140,160,180,200,250,300,400,500};
  int nbins=17;

  TH1F* h_PU0_denom = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU0_cal = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]",cut+Form("&& (4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]>%i",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU0_cal = new TGraphAsymmErrors();
  gr_PU0_cal->Divide(h_PU0_cal,h_PU0_denom);


  TH1F* h_PU0_denom_GEO = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU0_cal_GEO = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]",cut+Form("&& 1.06*(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]>%i",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU0_cal_GEO = new TGraphAsymmErrors();
  gr_PU0_cal_GEO->Divide(h_PU0_cal_GEO,h_PU0_denom_GEO);



  TH1F* h_PU0_denom_GEO_recal = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR_JetPU0cal/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU0_cal_GEO_recal = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR_JetPU0cal/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.1*1.04*(4.16098 -1.00815e+00 * log(jets_pt[VBF_parton_jets]) + 7.59202e-02* pow(log(jets_pt[VBF_parton_jets]),2) ) * jets_pt[VBF_parton_jets] ) >%i",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU0_cal_GEO_recal = new TGraphAsymmErrors();
  gr_PU0_cal_GEO_recal->Divide(h_PU0_cal_GEO_recal,h_PU0_denom_GEO_recal);


  vector<TGraphAsymmErrors*> turnons;
  turnons.push_back(gr_PU0_cal);
  turnons.push_back(gr_PU0_cal_GEO);
  turnons.push_back(gr_PU0_cal_GEO_recal);
  
  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO");
  leg_entry.push_back("GEO recalibr. C2D");


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
  turnons[0]->GetXaxis()->SetLimits(0,250);
  turnons[0]->GetYaxis()->SetTitle("Efficiency");
  turnons[0]->GetYaxis()->SetTitleOffset(1.7);
  turnons[0]->GetYaxis()->SetRangeUser(0.,1.);
  turnons[0]->SetTitle("");
  turnons[0]->Draw();
  for(unsigned int i=1;i<turnons.size();i++)
    turnons[i]->Draw("same");
  leg->Draw("same");
  gPad->SetGrid();
  
  TLine* line = new TLine(0,0.95,250,0.95);
  line->Draw("same");

  TLatex *texl = new TLatex(1.57,1.01,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV PU=0");
  texl->SetTextSize(0.03);
  texl->Draw("same");
  gPad->SetTicks();


  c->SaveAs(Form("plots/turnons_L1SingleJet%i_GEO_PU0.pdf",L1pt));  


}











void plot_turnons_L1SingleJet_GEO_C2D_recal_PU200(int L1pt){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  double x[18]={0,40,60,70,80,90,100,110,120,130,140,160,180,200,250,300,400,500};
  int nbins=17;

  TH1F* h_PU200_denom = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_PUS_cal = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]",cut+Form("&& (4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)),2) ) * max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)>%i",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU200_PUS_cal = new TGraphAsymmErrors();
  gr_PU200_PUS_cal->Divide(h_PU200_PUS_cal,h_PU200_denom);


  TH1F* h_PU200_denom_GEO = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_PUS_cal_GEO = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]",cut+Form("&& 1.06*(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)),2) ) * max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)>%i",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU200_PUS_cal_GEO = new TGraphAsymmErrors();
  gr_PU200_PUS_cal_GEO->Divide(h_PU200_PUS_cal_GEO,h_PU200_denom_GEO);


  TH1F* h_PU200_denom_GEO_recal = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR_JetPU0cal/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_PUS_cal_GEO_recal = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR_JetPU0cal/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.1*1.04*(4.16098 -1.00815e+00 * log(max(jets_pt[VBF_parton_jets]-3*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)) + 7.59202e-02* pow(log(max(jets_pt[VBF_parton_jets]-3*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-3*jets_PU_subtr_cone_C3D[VBF_parton_jets],0) ) >%i",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU200_PUS_cal_GEO_recal = new TGraphAsymmErrors();
  gr_PU200_PUS_cal_GEO_recal->Divide(h_PU200_PUS_cal_GEO_recal,h_PU200_denom_GEO_recal);





  vector<TGraphAsymmErrors*> turnons;
  turnons.push_back(gr_PU200_PUS_cal);
  turnons.push_back(gr_PU200_PUS_cal_GEO);
  turnons.push_back(gr_PU200_PUS_cal_GEO_recal);
  
  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO");
  leg_entry.push_back("GEO recalibr. C2D");


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
  turnons[0]->GetXaxis()->SetLimits(0,250);
  turnons[0]->GetYaxis()->SetTitle("Efficiency");
  turnons[0]->GetYaxis()->SetTitleOffset(1.7);
  turnons[0]->GetYaxis()->SetRangeUser(0.,1.);
  turnons[0]->SetTitle("");
  turnons[0]->Draw();
  for(unsigned int i=1;i<turnons.size();i++)
    turnons[i]->Draw("same");
  leg->Draw("same");
  gPad->SetGrid();
  
  TLine* line = new TLine(0,0.95,250,0.95);
  line->Draw("same");

  TLatex *texl = new TLatex(1.57,1.01,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");
  gPad->SetTicks();


  c->SaveAs(Form("plots/turnons_L1SingleJet%i_GEO_PU200.pdf",L1pt));  


}






void plot_turnons_L1SingleJet_GEO_C2D_recal_PU200_var(int L1pt_NN, int L1pt_GEO, int L1pt_GEO_recal){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  double x[18]={0,40,60,70,80,90,100,110,120,130,140,160,180,200,250,300,400,500};
  int nbins=17;

  TH1F* h_PU200_denom = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_PUS_cal = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]",cut+Form("&& ((4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)),2) ) * max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0))>%i",L1pt_NN),nbins,x);
  TGraphAsymmErrors* gr_PU200_PUS_cal = new TGraphAsymmErrors();
  gr_PU200_PUS_cal->Divide(h_PU200_PUS_cal,h_PU200_denom);


  TH1F* h_PU200_denom_GEO = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_PUS_cal_GEO = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)),2) ) * max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0))>%i",L1pt_GEO),nbins,x);
  TGraphAsymmErrors* gr_PU200_PUS_cal_GEO = new TGraphAsymmErrors();
  gr_PU200_PUS_cal_GEO->Divide(h_PU200_PUS_cal_GEO,h_PU200_denom_GEO);


  TH1F* h_PU200_denom_GEO_recal = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR_JetPU0cal/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_PUS_cal_GEO_recal = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR_JetPU0cal/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.1*1.04*(4.16098 -1.00815e+00 * log(max(jets_pt[VBF_parton_jets]-3*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)) + 7.59202e-02* pow(log(max(jets_pt[VBF_parton_jets]-3*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-3*jets_PU_subtr_cone_C3D[VBF_parton_jets],0) ) >%i",L1pt_GEO_recal),nbins,x);
  TGraphAsymmErrors* gr_PU200_PUS_cal_GEO_recal = new TGraphAsymmErrors();
  gr_PU200_PUS_cal_GEO_recal->Divide(h_PU200_PUS_cal_GEO_recal,h_PU200_denom_GEO_recal);





  vector<TGraphAsymmErrors*> turnons;
  turnons.push_back(gr_PU200_PUS_cal);
  turnons.push_back(gr_PU200_PUS_cal_GEO);
  turnons.push_back(gr_PU200_PUS_cal_GEO_recal);
  
  vector<TString> leg_entry;
  leg_entry.push_back(Form("NN L1_SingleJet%i",L1pt_NN));
  leg_entry.push_back(Form("GEO L1_SingleJet%i",L1pt_GEO));
  leg_entry.push_back(Form("GEO recal. L1_SingleJet%i",L1pt_GEO_recal));


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
  turnons[0]->GetXaxis()->SetLimits(0,250);
  turnons[0]->GetYaxis()->SetTitle("Efficiency");
  turnons[0]->GetYaxis()->SetTitleOffset(1.7);
  turnons[0]->GetYaxis()->SetRangeUser(0.,1.);
  turnons[0]->SetTitle("");
  turnons[0]->Draw();
  for(unsigned int i=1;i<turnons.size();i++)
    turnons[i]->Draw("same");
  leg->Draw("same");
  gPad->SetGrid();
  
  TLine* line = new TLine(0,0.95,250,0.95);
  line->Draw("same");

  TLatex *texl = new TLatex(1.57,1.01,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");
  gPad->SetTicks();

  c->SaveAs(Form("plots/turnons_L1SingleJet%i_NN_L1SingleJet%i_GEO_L1SingleJet%i_GEO_recal.pdf",L1pt_NN,L1pt_GEO,L1pt_GEO_recal));  



}


