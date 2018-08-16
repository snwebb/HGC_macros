#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TH1D.h>
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




void plot_profile_L1jet_response_pt_PU0_tau(){

  TString cut_VBF = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";
  TString cut_tau = "gentau_jets>=0 && abs(gentau_vis_eta)>1.6 && abs(gentau_vis_eta)<2.9 && gentau_vis_pt>20 && gentau_decayMode>=0 && gentau_decayMode<=5";

  TH2F* h_VBF_raw_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut_VBF+"&& jets_pt[VBF_parton_jets]>0",50,0,250,97,0.06,2);
  TH2F* h_VBF_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut_VBF+"&& jets_pt[VBF_parton_jets]>0",50,0,250,97,0.06,2);


  TH2F* h_tau_raw_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","gentau_vis_pt","jets_pt[gentau_jets]/gentau_vis_pt",cut_tau+"&& jets_pt[gentau_jets]>0",50,0,250,97,0.06,2);
  TH2F* h_tau_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","gentau_vis_pt","1.1/(0.93-1/(0.2*max(jets_pt[gentau_jets],20)+1e-3*pow(max(jets_pt[gentau_jets],20),2))) * jets_pt[gentau_jets]/gentau_vis_pt",cut_tau+"&& jets_pt[gentau_jets]>0",50,0,250,97,0.06,2);


  vector<TH2F*> histo;
  histo.push_back(h_VBF_raw_dRNNC2D);
  histo.push_back(h_VBF_cal_dRNNC2D);
  histo.push_back(h_tau_raw_dRNNC2D);
  histo.push_back(h_tau_cal_dRNNC2D);
  
  vector<TString> leg_entry;
  leg_entry.push_back("VBF jet");
  leg_entry.push_back("VBF jet + JEC");
  leg_entry.push_back("#tau_{h}");
  leg_entry.push_back("#tau_{h} + TEC");


  TLegend* leg=new TLegend(0.6,0.15,0.8,0.5);
  leg->SetHeader("#splitline{p_T(gen.)>20 GeV}{1.6<|#eta(gen.)|<2.9}");
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

  prof[0]->GetXaxis()->SetTitle("p_{T}(gen.) [GeV]");
  prof[0]->GetYaxis()->SetTitle("p_{T}(L1)/p_{T}(gen.)");
  prof[0]->GetYaxis()->SetTitleOffset(1.7);
  prof[0]->GetYaxis()->SetRangeUser(0,1.2);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(2.,1.21,"CMS Simulation Preliminary, #sqrt{s}=14 TeV PU=0");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(0,1,500,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_response_pt_PU0_tau.pdf");  


}









void plot_turnons_L1SingleTau_dRNNC2D(int L1pt){

  TString cut = "gentau_jets>=0 && abs(gentau_vis_eta)>1.6 && abs(gentau_vis_eta)<2.9 && gentau_vis_pt>0 && gentau_decayMode>=0 && gentau_decayMode<=5";
  TString cut_Phase1 = "abs(tauEta)>1.6 && abs(tauEta)<3.0 && tau_genindex==5";

  double x[22]={0,10,20,25,30,33,35,37,39,40,41,43,45,47,50,55,60,65,75,80,90,100};
  int nbins=21;

  double x2[13]={0,20,25,30,35,38,40,42,45,50,60,80,100};
  int nbins2=12;

  TH1F* h_PU0_denom_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","gentau_vis_pt",cut,nbins,x);
  TH1F* h_PU0_cal_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","gentau_vis_pt",cut+Form("&& 1.1/(0.93-1/(0.2*max(jets_pt[gentau_jets],20)+1e-3*pow(max(jets_pt[gentau_jets],20),2))) * (jets_pt[gentau_jets]) >%i",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU0_cal_dRNNC2D = new TGraphAsymmErrors();
  gr_PU0_cal_dRNNC2D->Divide(h_PU0_cal_dRNNC2D,h_PU0_denom_dRNNC2D);


  TH1F* h_PU200_denom_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","gentau_vis_pt",cut,nbins,x);
  TH1F* h_PU200_cal_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","gentau_vis_pt",cut+Form("&& 1.1/(0.93-1/(0.2*max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20)+1e-3*pow(max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20),2))) * (jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets]) >%i",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D->Divide(h_PU200_cal_dRNNC2D,h_PU200_denom_dRNNC2D);




  /*TH1F* h_Phase1_denom = single_plot("/vols/cms/tstreble/TauHLT/TagAndProbeTrees/TagAndProbe_MuTau_Hale/NTuple_DYJets_RunIIFall17MiniAOD-RECOSIMstep_94X_mc2017_realistic_v10-v1_14_01_2018_PU_forFitv3.root","TagAndProbe","tauPt",cut_Phase1,nbins2,x2);
  TH1F* h_Phase1 = single_plot("/vols/cms/tstreble/TauHLT/TagAndProbeTrees/TagAndProbe_MuTau_Hale/NTuple_DYJets_RunIIFall17MiniAOD-RECOSIMstep_94X_mc2017_realistic_v10-v1_14_01_2018_PU_forFitv3.root","TagAndProbe","tauPt",cut_Phase1+Form("&& l1tPt >%i",L1pt),nbins2,x2);
  TGraphAsymmErrors* gr_Phase1 = new TGraphAsymmErrors();
  gr_Phase1->Divide(h_Phase1,h_Phase1_denom);*/


  vector<TGraphAsymmErrors*> turnons;
  //turnons.push_back(gr_Phase1);
  turnons.push_back(gr_PU0_cal_dRNNC2D);
  turnons.push_back(gr_PU200_cal_dRNNC2D);

  vector<TString> leg_entry;
  //leg_entry.push_back("Phase 1 <PU>=32");
  leg_entry.push_back("PU=0");
  leg_entry.push_back("PU=200");


  TLegend* leg=new TLegend(0.5,0.2,0.8,0.55);
  leg->SetHeader(Form("#splitline{p_{T}(L1 Tau)>%i GeV}{1.6<|#eta(gen.#tau_{h})|<2.9}",L1pt));
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

  turnons[0]->GetXaxis()->SetTitle("p_{T}(gen. #tau_{h}) [GeV]");
  turnons[0]->GetXaxis()->SetLimits(0,100);
  turnons[0]->GetYaxis()->SetTitle("Efficiency");
  turnons[0]->GetYaxis()->SetTitleOffset(1.7);
  turnons[0]->GetYaxis()->SetRangeUser(0.,1.);
  turnons[0]->SetTitle("");
  turnons[0]->Draw();
  for(unsigned int i=1;i<turnons.size();i++)
    turnons[i]->Draw("same");
  leg->Draw("same");
  gPad->SetGrid();
  
  TLine* line = new TLine(0,0.95,100,0.95);
  line->Draw("same");


  TLatex *texl = new TLatex(1.57,1.01,"CMS Simulation, H#rightarrow#tau#tau #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");
  gPad->SetTicks();


  c->SaveAs(Form("plots/turnons_L1SingleTau%i_dRNNC2D.pdf",L1pt));  


}








void plot_profile_L1jet_response_pt_PU200_tau(){

  TString cut_tau = "gentau_jets>=0 && abs(gentau_vis_eta)>1.6 && abs(gentau_vis_eta)<2.9 && gentau_vis_pt>20 && gentau_decayMode>=0 && gentau_decayMode<=5";


  TH2F* h_tau_PU0_raw_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","gentau_vis_pt","jets_pt[gentau_jets]/gentau_vis_pt",cut_tau+"&& jets_pt[gentau_jets]>0",30,0,150,97,0.06,2);
  TH2F* h_tau_PU0_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","gentau_vis_pt","1.1/(0.93-1/(0.2*max(jets_pt[gentau_jets],20)+1e-3*pow(max(jets_pt[gentau_jets],20),2))) * jets_pt[gentau_jets]/gentau_vis_pt",cut_tau+"&& jets_pt[gentau_jets]>0",30,0,150,97,0.06,2);


  TH2F* h_tau_PU200_PUS_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","gentau_vis_pt","max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],0)/gentau_vis_pt",cut_tau+"&& (jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets])>0",30,0,150,97,0.06,2);
 TH2F* h_tau_PU200_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","gentau_vis_pt","1.1/(0.93-1/(0.2*max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20)+1e-3*pow(max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20),2))) * max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],0)/gentau_vis_pt",cut_tau+"&& (jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets])>0",30,0,150,97,0.06,2);

  vector<TH2F*> histo;
  histo.push_back(h_tau_PU0_raw_dRNNC2D);
  histo.push_back(h_tau_PU0_cal_dRNNC2D);
  histo.push_back(h_tau_PU200_PUS_dRNNC2D);
  histo.push_back(h_tau_PU200_cal_dRNNC2D);
  
  
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0");
  leg_entry.push_back("PU=0 + #tau_{h} calibr.");  
  leg_entry.push_back("PU=200 PUS");
  leg_entry.push_back("PU=200 PUS +  #tau_{h} calibr.");


  TLegend* leg=new TLegend(0.4,0.15,0.8,0.5);
  leg->SetHeader("#splitline{p_{T}(gen. #tau_{h})>20 GeV}{1.6<|#eta(gen. #tau_{h})|<2.9}");
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

  prof[0]->GetXaxis()->SetTitle("p_{T}(gen. #tau_{h}) [GeV]");
  prof[0]->GetYaxis()->SetTitle("p_{T}(L1)/p_{T}(gen. #tau_{h})");
  prof[0]->GetYaxis()->SetTitleOffset(1.7);
  prof[0]->GetYaxis()->SetRangeUser(0,1.2);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(2.,1.21,"CMS Simulation Preliminary, H#rightarrow#tau#tau #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(0,1,150,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_response_pt_PU200_tau.pdf");  


}







void plot_profile_L1jet_response_eta_PU200_tau(){

  TString cut_tau = "gentau_jets>=0 && abs(gentau_vis_eta)>1.6 && abs(gentau_vis_eta)<2.9 && gentau_vis_pt>20 && gentau_decayMode>=0 && gentau_decayMode<=5";


  TH2F* h_tau_PU0_raw_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(gentau_vis_eta)","jets_pt[gentau_jets]/gentau_vis_pt",cut_tau+"&& jets_pt[gentau_jets]>0",13,1.6,2.9,97,0.06,2);
  TH2F* h_tau_PU0_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(gentau_vis_eta)","1.1/(0.93-1/(0.2*max(jets_pt[gentau_jets],20)+1e-3*pow(max(jets_pt[gentau_jets],20),2))) * jets_pt[gentau_jets]/gentau_vis_pt",cut_tau+"&& jets_pt[gentau_jets]>0",13,1.6,2.9,97,0.06,2);


  TH2F* h_tau_PU200_PUS_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(gentau_vis_eta)","max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],0)/gentau_vis_pt",cut_tau+"&& (jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets])>0",13,1.6,2.9,97,0.06,2);
  TH2F* h_tau_PU200_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(gentau_vis_eta)","1.1/(0.93-1/(0.2*max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20)+1e-3*pow(max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20),2))) * max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],0)/gentau_vis_pt",cut_tau+"&& (jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets])>0",13,1.6,2.9,97,0.06,2);

  vector<TH2F*> histo;
  histo.push_back(h_tau_PU0_raw_dRNNC2D);
  histo.push_back(h_tau_PU0_cal_dRNNC2D);
  histo.push_back(h_tau_PU200_PUS_dRNNC2D);
  histo.push_back(h_tau_PU200_cal_dRNNC2D);
  
  
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0");
  leg_entry.push_back("PU=0 +  #tau_{h} calibr.");  
  leg_entry.push_back("PU=200 PUS");
  leg_entry.push_back("PU=200 PUS +  #tau_{h} calibr.");


  TLegend* leg=new TLegend(0.4,0.15,0.8,0.5);
  leg->SetHeader("#splitline{p_{T}(gen. #tau_{h})>20 GeV}{1.6<|#eta(gen. #tau_{h})|<2.9}");
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

  prof[0]->GetXaxis()->SetTitle("|#eta(gen. #tau_{h})|");
  prof[0]->GetYaxis()->SetTitle("p_{T}(L1)/p_{T}(gen. #tau_{h})");
  prof[0]->GetYaxis()->SetTitleOffset(1.7);
  prof[0]->GetYaxis()->SetRangeUser(-1,1.2);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(1.61,1.21,"CMS Simulation Preliminary, H#rightarrow#tau#tau #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(1.6,1,2.9,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_response_eta_PU200_tau.pdf");  


}






void plot_jets_nc3d(){

  TH1F* h_VBF_PU0 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","jets_ncl3d[VBF_parton_jets]","VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20",50,0,50);
  TH1F* h_tau_PU0 = single_plot("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","jets_ncl3d[gentau_jets]","gentau_jets>=0 && abs(gentau_vis_eta)>1.6 && abs(gentau_vis_eta)<2.9 && gentau_vis_pt>20 && gentau_decayMode>=0 && gentau_decayMode<=5",50,0,50);

  TH1F* h_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","jets_ncl3d[VBF_parton_jets]","VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20",50,0,50);
  TH1F* h_tau_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","jets_ncl3d[gentau_jets]","gentau_jets>=0 && abs(gentau_vis_eta)>1.6 && abs(gentau_vis_eta)<2.9 && gentau_vis_pt>20 && gentau_decayMode>=0 && gentau_decayMode<=5",50,0,50);
  TH1F* h_ZB_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","jets_ncl3d","jets_pt>20",50,0,50);


  vector<TH1F*> histo;
  histo.push_back(h_VBF_PU0);
  histo.push_back(h_tau_PU0);
  histo.push_back(h_VBF_PU200);
  histo.push_back(h_tau_PU200);
  histo.push_back(h_ZB_PU200);


  vector<TString> leg_entry;
  leg_entry.push_back("VBF PU=0");
  leg_entry.push_back("#tau_{h} PU=0");
  leg_entry.push_back("VBF PU=200");
  leg_entry.push_back("#tau_{h} PU=200");
  leg_entry.push_back("PU PU=200");


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

  histo[0]->GetXaxis()->SetTitle("#C3D per jet");
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

  
  TLatex *texl = new TLatex(2.,1.2*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/jets_nC3D_tau.pdf");  


}








void plot_jets_srrtot(){

  TH1F* h_VBF_PU0 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","jets_srrtot[VBF_parton_jets]","VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20",100,0,0.05);
  TH1F* h_tau_PU0 = single_plot("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","jets_srrtot[gentau_jets]","gentau_jets>=0 && abs(gentau_vis_eta)>1.6 && abs(gentau_vis_eta)<2.9 && gentau_vis_pt>20 && gentau_decayMode>=0 && gentau_decayMode<=5",100,0,0.05);

  TH1F* h_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","jets_srrtot[VBF_parton_jets]"," VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20",100,0,0.05);
  TH1F* h_tau_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","jets_srrtot[gentau_jets]","gentau_jets>=0 && abs(gentau_vis_eta)>1.6 && abs(gentau_vis_eta)<2.9 && gentau_vis_pt>20 && gentau_decayMode>=0 && gentau_decayMode<=5",100,0,0.05);
  TH1F* h_ZB_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","jets_srrtot","jets_pt>20",100,0,0.05);


  vector<TH1F*> histo;
  histo.push_back(h_VBF_PU0);
  histo.push_back(h_tau_PU0);
  histo.push_back(h_VBF_PU200);
  histo.push_back(h_tau_PU200);
  histo.push_back(h_ZB_PU200);


  vector<TString> leg_entry;
  leg_entry.push_back("VBF PU=0");
  leg_entry.push_back("#tau_{h} PU=0");
  leg_entry.push_back("VBF PU=200");
  leg_entry.push_back("#tau_{h} PU=200");
  leg_entry.push_back("PU PU=200");


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

  histo = sort_histo(histo);

  histo[0]->GetXaxis()->SetTitle("#sigma_{rr}(jet)");
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

  
  TLatex *texl = new TLatex(0.002,1.2*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();

  c->SaveAs("plots/jets_sigmarr_tau.pdf");  


}










void plot_profile_L1jet_clean_response_pt_tau(){

  TString cut_tau = "gentau_jets>=0 && abs(gentau_vis_eta)>1.6 && abs(gentau_vis_eta)<2.9 && gentau_vis_pt>20 && gentau_decayMode>=0 && gentau_decayMode<=5";

  TH2F* h_tau_PU0_raw_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","gentau_vis_pt","jets_pt[gentau_jets]/gentau_vis_pt",cut_tau+"&& jets_pt[gentau_jets]>0",30,0,150,97,0.06,2);

  TH2F* h_tau_PU0_clean_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","gentau_vis_pt","jets_clean_pt[gentau_jets]/gentau_vis_pt",cut_tau+"&& jets_clean_pt[gentau_jets]>0",30,0,150,97,0.06,2);

  TH2F* h_tau_PU200_raw_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","gentau_vis_pt","jets_pt[gentau_jets]/gentau_vis_pt",cut_tau+"&& jets_pt[gentau_jets]>0",30,0,150,97,0.06,2);

  TH2F* h_tau_PU200_PUS_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","gentau_vis_pt","max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],0)/gentau_vis_pt",cut_tau+"&& (jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets])>0",30,0,150,97,0.06,2);

  TH2F* h_tau_PU200_clean_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","gentau_vis_pt","jets_clean_pt[gentau_jets]/gentau_vis_pt",cut_tau+"&& jets_clean_pt[gentau_jets]>0",30,0,150,97,0.06,2);

  TH2F* h_tau_PU200_clean_PUS_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","gentau_vis_pt","max(jets_clean_pt[gentau_jets]-0.6*jets_PU_subtr_cone_GEO_C3D[gentau_jets],0)/gentau_vis_pt",cut_tau+"&& (jets_clean_pt[gentau_jets]-0.6*jets_PU_subtr_cone_GEO_C3D[gentau_jets])>0",30,0,150,97,0.06,2);



  vector<TH2F*> histo;
  histo.push_back(h_tau_PU0_raw_dRNNC2D);
  histo.push_back(h_tau_PU0_clean_dRNNC2D);
  histo.push_back(h_tau_PU200_raw_dRNNC2D);
  histo.push_back(h_tau_PU200_PUS_dRNNC2D);
  histo.push_back(h_tau_PU200_clean_dRNNC2D);
  histo.push_back(h_tau_PU200_clean_PUS_dRNNC2D);
  
  vector<TString> leg_entry;
  leg_entry.push_back("#tau_{h} PU0");
  leg_entry.push_back("#tau_{h} clean PU0");
  leg_entry.push_back("#tau_{h} PU200");
  leg_entry.push_back("#tau_{h} PUS PU200");
  leg_entry.push_back("#tau_{h} clean PU200");
  leg_entry.push_back("#tau_{h} clean + PUS PU200");
  

  TLegend* leg=new TLegend(0.6,0.15,0.8,0.5);
  leg->SetHeader("#splitline{p_T(gen.)>20 GeV}{1.6<|#eta(gen.)|<2.9}");
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

  prof[0]->GetXaxis()->SetTitle("p_{T}(gen.) [GeV]");
  prof[0]->GetYaxis()->SetTitle("p_{T}(L1)/p_{T}(gen.)");
  prof[0]->GetYaxis()->SetTitleOffset(1.7);
  prof[0]->GetYaxis()->SetRangeUser(0,1.2);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(2.,1.21,"CMS Simulation Preliminary, #sqrt{s}=14 TeV PU=0");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(0,1,500,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_clean_response_pt_tau.pdf");  


}





void plot_profile_L1jet_clean_response_eta_tau(){

  TString cut_tau = "gentau_jets>=0 && abs(gentau_vis_eta)>1.6 && abs(gentau_vis_eta)<2.9 && gentau_vis_pt>20 && gentau_decayMode>=0 && gentau_decayMode<=5";


  TH2F* h_tau_PU0_raw_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(gentau_vis_eta)","jets_pt[gentau_jets]/gentau_vis_pt",cut_tau+"&& jets_pt[gentau_jets]>0",13,1.6,2.9,97,0.06,2);

  TH2F* h_tau_PU0_clean_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(gentau_vis_eta)","jets_clean_pt[gentau_jets]/gentau_vis_pt",cut_tau+"&& jets_clean_pt[gentau_jets]>0",13,1.6,2.9,97,0.06,2);

  TH2F* h_tau_PU200_raw_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(gentau_vis_eta)","jets_pt[gentau_jets]/gentau_vis_pt",cut_tau+"&& jets_pt[gentau_jets]>0",13,1.6,2.9,97,0.06,2);

  TH2F* h_tau_PU200_PUS_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(gentau_vis_eta)","max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],0)/gentau_vis_pt",cut_tau+"&& (jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets])>0",13,1.6,2.9,97,0.06,2);

  TH2F* h_tau_PU200_clean_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(gentau_vis_eta)","jets_clean_pt[gentau_jets]/gentau_vis_pt",cut_tau+"&& jets_clean_pt[gentau_jets]>0",13,1.6,2.9,97,0.06,2);

  TH2F* h_tau_PU200_clean_PUS_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(gentau_vis_eta)","max(jets_clean_pt[gentau_jets]-0.6*jets_PU_subtr_cone_GEO_C3D[gentau_jets],0)/gentau_vis_pt",cut_tau+"&& (jets_clean_pt[gentau_jets]-0.6*jets_PU_subtr_cone_GEO_C3D[gentau_jets])>0",13,1.6,2.9,97,0.06,2);

 vector<TH2F*> histo;
  histo.push_back(h_tau_PU0_raw_dRNNC2D);
  histo.push_back(h_tau_PU0_clean_dRNNC2D);
  histo.push_back(h_tau_PU200_raw_dRNNC2D);
  histo.push_back(h_tau_PU200_PUS_dRNNC2D);
  histo.push_back(h_tau_PU200_clean_dRNNC2D);
  histo.push_back(h_tau_PU200_clean_PUS_dRNNC2D);
  
  vector<TString> leg_entry;
  leg_entry.push_back("#tau_{h} PU0");
  leg_entry.push_back("#tau_{h} clean PU0");
  leg_entry.push_back("#tau_{h} PU200");
  leg_entry.push_back("#tau_{h} PUS PU200");
  leg_entry.push_back("#tau_{h} clean PU200");
  leg_entry.push_back("#tau_{h} clean + PUS PU200");



  TLegend* leg=new TLegend(0.4,0.15,0.8,0.5);
  leg->SetHeader("#splitline{p_T(gen.)>20 GeV}{1.6<|#eta(gen.)|<2.9}");
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

  prof[0]->GetXaxis()->SetTitle("|#eta(gen.)|");
  prof[0]->GetYaxis()->SetTitle("p_{T}(L1)/p_{T}(gen.)");
  prof[0]->GetYaxis()->SetTitleOffset(1.7);
  prof[0]->GetYaxis()->SetRangeUser(-1,1.2);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(1.61,1.21,"CMS Simulation Preliminary, H#rightarrow#tau#tau #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(1.6,1,2.9,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_clean_response_eta_tau.pdf");  


}






