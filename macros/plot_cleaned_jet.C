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
#include "Helpers_ROC.C"


using namespace std;







void plot_profile_L1jet_response_pt_PU200_PUS_clean(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";


  TH2F* h_PU0_raw_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU200_PUS_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);

  TH2F* h_PU200_clean_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_clean_pt[VBF_parton_genjet]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_clean_pt[VBF_parton_genjet]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU200_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);

  TH2F* h_PU200_clean_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(jets_clean_pt[VBF_parton_genjet]) + 1.02929e-01* pow(log(jets_clean_pt[VBF_parton_genjet]),2) ) * jets_clean_pt[VBF_parton_genjet]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_clean_pt[VBF_parton_genjet]>0",25,0,500,97,0.06,2);

  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw_dRNNC2D);
  histo.push_back(h_PU200_PUS_dRNNC2D);
  histo.push_back(h_PU200_clean_dRNNC2D);
  histo.push_back(h_PU0_cal_dRNNC2D);
  histo.push_back(h_PU200_cal_dRNNC2D);
  histo.push_back(h_PU200_clean_cal_dRNNC2D);

  
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0");
  leg_entry.push_back("PU=200 + PUS");
  leg_entry.push_back("PU=200 + clean");
  leg_entry.push_back("PU=0 + JEC");
  leg_entry.push_back("PU=200 + PUS + JEC");
  leg_entry.push_back("PU=200 + clean + JEC");

 

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


  c->SaveAs("plots/profile_L1jet_response_pt_PU200_PUS_clean.pdf");  


}









void plot_profile_L1jet_response_eta_PU200_PUS_clean(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";


  TH2F* h_PU0_raw_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);

  TH2F* h_PU200_PUS_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",13,1.6,2.9,97,0.06,2);

  TH2F* h_PU200_clean_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","jets_clean_pt[VBF_parton_genjet]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_clean_pt[VBF_parton_genjet]>0",13,1.6,2.9,97,0.06,2);

  TH2F* h_PU0_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);

  TH2F* h_PU200_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",13,1.6,2.9,97,0.06,2);

  TH2F* h_PU200_clean_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","1.06*(4.98004e+00 -1.23767e+00 * log(jets_clean_pt[VBF_parton_genjet]) + 1.02929e-01* pow(log(jets_clean_pt[VBF_parton_genjet]),2) ) * jets_clean_pt[VBF_parton_genjet]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_clean_pt[VBF_parton_genjet]>0",13,1.6,2.9,97,0.06,2);

  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw_dRNNC2D);
  histo.push_back(h_PU200_PUS_dRNNC2D);
  histo.push_back(h_PU200_clean_dRNNC2D);
  histo.push_back(h_PU0_cal_dRNNC2D);
  histo.push_back(h_PU200_cal_dRNNC2D);
  histo.push_back(h_PU200_clean_cal_dRNNC2D);

  
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0");
  leg_entry.push_back("PU=200 + PUS");
  leg_entry.push_back("PU=200 + clean");
  leg_entry.push_back("PU=0 + JEC");
  leg_entry.push_back("PU=200 + PUS + JEC");
  leg_entry.push_back("PU=200 + clean + JEC");

 

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
  prof[0]->GetYaxis()->SetRangeUser(0,1.2);
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


  c->SaveAs("plots/profile_L1jet_response_eta_PU200_PUS_clean.pdf");  


}









void plot_profile_L1jet_resolution_clean_PU200(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  TH2F* h_PU0_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",18,0,360,970,0.06,2);
 
  TH2F* h_PU200_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",18,0,360,970,0.06,2);
 
  TH2F* h_PU200_clean_fix_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged_clean_fix_frac/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(jets_clean_pt[VBF_parton_genjet]) + 1.02929e-01* pow(log(jets_clean_pt[VBF_parton_genjet]),2) ) * jets_clean_pt[VBF_parton_genjet]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_clean_pt[VBF_parton_genjet]>0",18,0,360,970,0.06,2);


  TH2F* h_PU200_clean_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(jets_clean_pt[VBF_parton_genjet]) + 1.02929e-01* pow(log(jets_clean_pt[VBF_parton_genjet]),2) ) * jets_clean_pt[VBF_parton_genjet]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_clean_pt[VBF_parton_genjet]>0",18,0,360,970,0.06,2);


  vector<TH2F*> histo;
  histo.push_back(h_PU0_cal_dRNNC2D );
  histo.push_back(h_PU200_cal_dRNNC2D );
  histo.push_back(h_PU200_clean_fix_cal_dRNNC2D );
  histo.push_back(h_PU200_clean_cal_dRNNC2D );

  vector<TString> leg_entry;
  leg_entry.push_back("PU=0");
  leg_entry.push_back("PU=200 + PUS");
  leg_entry.push_back("PU=200 + clean fix frac.");
  leg_entry.push_back("PU=200 + clean #eta-dep. frac.");

 
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


  c->SaveAs("plots/profile_L1jet_resolution_pt_clean_PU200.pdf");  


}









void plot_profile_L1jet_resolution_clean_PU200_eta2p1(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.1 && genjet_pt[VBF_parton_genjet]>20";

  TH2F* h_PU0_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",18,0,360,970,0.06,2);
 
  TH2F* h_PU200_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",18,0,360,970,0.06,2);
 
  TH2F* h_PU200_clean_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(jets_clean_pt[VBF_parton_genjet]) + 1.02929e-01* pow(log(jets_clean_pt[VBF_parton_genjet]),2) ) * jets_clean_pt[VBF_parton_genjet]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_clean_pt[VBF_parton_genjet]>0",18,0,360,970,0.06,2);


  vector<TH2F*> histo;
  histo.push_back(h_PU0_cal_dRNNC2D );
  histo.push_back(h_PU200_cal_dRNNC2D );
  histo.push_back(h_PU200_clean_cal_dRNNC2D );

  vector<TString> leg_entry;
  leg_entry.push_back("PU=0");
  leg_entry.push_back("PU=200 + PUS");
  leg_entry.push_back("PU=200 + clean");

 
  TLegend* leg=new TLegend(0.4,0.5,0.7,0.85);
  leg->SetHeader("#splitline{p_T(gen. jet)>20 GeV}{1.6<|#eta(gen.jet)|<2.1}");
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


  c->SaveAs("plots/profile_L1jet_resolution_pt_clean_PU200_eta2p1.pdf");  


}










void plot_turnons_L1SingleJet_dRNNC2D_PU200(int L1pt){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  double x[18]={0,40,60,70,80,90,100,110,120,130,140,160,180,200,250,300,400,500};
  int nbins=17;

  //double x[16]={0,25,35,40,45,50,55,60,65,75,80,90,100,120,150,300};
  //int nbins=15;


  TH1F* h_PU200_denom_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_cal_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D->Divide(h_PU200_cal_dRNNC2D,h_PU200_denom_dRNNC2D);


  TH1F* h_PU200_clean_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_clean_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_clean_pt[VBF_parton_jets],0)),2) ) * max(jets_clean_pt[VBF_parton_jets],0)) >%i",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU200_clean_dRNNC2D = new TGraphAsymmErrors();
  gr_PU200_clean_dRNNC2D->Divide(h_PU200_clean_dRNNC2D,h_PU200_denom_dRNNC2D);

  vector<TGraphAsymmErrors*> turnons;
  turnons.push_back(gr_PU200_cal_dRNNC2D);
  turnons.push_back(gr_PU200_clean_dRNNC2D);


  vector<TString> leg_entry;
  leg_entry.push_back("PUS");
  leg_entry.push_back("Clean");


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


  c->SaveAs(Form("plots/turnons_L1SingleJet%i_dRNNC2D_clean_PU200.pdf",L1pt));  


}










void plot_turnons_L1SingleJet_dRNNC2D_PU200_eta2p1(int L1pt){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.1 && genjet_pt[VBF_parton_genjet]>20";

  double x[18]={0,40,60,70,80,90,100,110,120,130,140,160,180,200,250,300,400,500};
  int nbins=17;

  //double x[16]={0,25,35,40,45,50,55,60,65,75,80,90,100,120,150,300};
  //int nbins=15;


  TH1F* h_PU200_denom_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_cal_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D->Divide(h_PU200_cal_dRNNC2D,h_PU200_denom_dRNNC2D);


  TH1F* h_PU200_clean_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_clean_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_clean_pt[VBF_parton_jets],0)),2) ) * max(jets_clean_pt[VBF_parton_jets],0)) >%i",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU200_clean_dRNNC2D = new TGraphAsymmErrors();
  gr_PU200_clean_dRNNC2D->Divide(h_PU200_clean_dRNNC2D,h_PU200_denom_dRNNC2D);

  vector<TGraphAsymmErrors*> turnons;
  turnons.push_back(gr_PU200_cal_dRNNC2D);
  turnons.push_back(gr_PU200_clean_dRNNC2D);


  vector<TString> leg_entry;
  leg_entry.push_back("PUS");
  leg_entry.push_back("Clean");


  TLegend* leg=new TLegend(0.5,0.12,0.85,0.55);
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


  c->SaveAs(Form("plots/turnons_L1SingleJet%i_dRNNC2D_clean_PU200_eta2p1.pdf",L1pt));  


}







void plot_L1jet_pt_bins_PU200_clean(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  TH1F* h_PU0_cal_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets],0)",cut+"&& genjet_pt[VBF_parton_genjet]>50 && genjet_pt[VBF_parton_genjet]<60",60,0,300);


  TH1F* h_PU200_cal_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)",cut+"&& genjet_pt[VBF_parton_genjet]>50 && genjet_pt[VBF_parton_genjet]<60",60,0,300);

  TH1F* h_PU200_clean_fix_cal_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged_clean_fix_frac/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","1.06*(4.98004e+00 -1.23767e+00 * log(jets_clean_pt[VBF_parton_genjet]) + 1.02929e-01* pow(log(jets_clean_pt[VBF_parton_genjet]),2) ) * jets_clean_pt[VBF_parton_genjet]",cut+"&& genjet_pt[VBF_parton_genjet]>50 && genjet_pt[VBF_parton_genjet]<60",60,0,300);

  TH1F* h_PU200_clean_cal_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","1.06*(4.98004e+00 -1.23767e+00 * log(jets_clean_pt[VBF_parton_genjet]) + 1.02929e-01* pow(log(jets_clean_pt[VBF_parton_genjet]),2) ) * jets_clean_pt[VBF_parton_genjet]",cut+"&& genjet_pt[VBF_parton_genjet]>50 && genjet_pt[VBF_parton_genjet]<60",60,0,300);



  vector<TH1F*> histo;
  histo.push_back(h_PU0_cal_dRNNC2D);
  histo.push_back(h_PU200_cal_dRNNC2D);
  histo.push_back(h_PU200_clean_fix_cal_dRNNC2D);
  histo.push_back(h_PU200_clean_cal_dRNNC2D);

  
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 PUS");
  leg_entry.push_back("PU=200 PUS");
  leg_entry.push_back("PU=200 clean fix frac.");
  leg_entry.push_back("PU=200 clean #eta-dep. frac.");
 

  TLegend* leg=new TLegend(0.4,0.2,0.7,0.6);
  leg->SetHeader("#splitline{50<p_T(gen. jet)<60 GeV}{1.6<|#eta(gen.jet)|<2.9}");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  

  for(unsigned int i=0;i<histo.size();i++){
    histo[i]->SetLineColor(i+1);
    if(i>3)
      histo[i]->SetLineColor(i+2);
    histo[i]->SetLineWidth(2);
    leg->AddEntry(histo[i],leg_entry[i]);
    histo[i]->Scale(1/histo[i]->Integral());
  }

  histo = sort_histo(histo);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  histo[0]->SetMaximum(1.2*histo[0]->GetMaximum());
  histo[0]->GetXaxis()->SetTitle("p_{T}(L1 jet) [GeV]");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(2.,1.02*histo[0]->GetMaximum(),"CMS Simulation Preliminary, VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/L1jet_pt_bins_PU200_clean.pdf");  


}










void plot_profile_L1jet_PUS_eta_PU200(){

  TString VBF_cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";
  TString ZB_cut = "cl3d_jet>=0 && jets_pt[cl3d_jet]>20";


  TH2F* h_VBF_PU200_PUS_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(jets_eta[VBF_parton_jets])","2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets]",VBF_cut,13,1.6,2.9,10000,0.,30.);

  TH2F* h_VBF_PU200_clean_fix_frac_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged_clean_fix_frac/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(jets_eta[VBF_parton_jets])","jets_pt[VBF_parton_jets]-jets_clean_pt[VBF_parton_jets]",VBF_cut,13,1.6,2.9,10000,0.,30.);

  TH2F* h_VBF_PU200_clean_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(jets_eta[VBF_parton_jets])","jets_pt[VBF_parton_jets]-jets_clean_pt[VBF_parton_jets]",VBF_cut,13,1.6,2.9,10000,0.,30.);

  TH2F* h_ZB_PU200_clean_fix_frac_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged_clean_fix_frac/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(jets_eta)","jets_pt-jets_clean_pt",ZB_cut,13,1.6,2.9,10000,0.,30.);

  TH2F* h_ZB_PU200_clean_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(jets_eta)","jets_pt-jets_clean_pt",ZB_cut,13,1.6,2.9,10000,0.,30.);


  vector<TH2F*> histo;
  histo.push_back(h_VBF_PU200_PUS_dRNNC2D);
  histo.push_back(h_VBF_PU200_clean_fix_frac_dRNNC2D);
  histo.push_back(h_VBF_PU200_clean_dRNNC2D);
  histo.push_back(h_ZB_PU200_clean_fix_frac_dRNNC2D);
  histo.push_back(h_ZB_PU200_clean_dRNNC2D);

  
  vector<TString> leg_entry;
  leg_entry.push_back("PUS VBF=ZB");
  leg_entry.push_back("Clean fix frac. VBF PU=200");
  leg_entry.push_back("Clean #eta-dep. frac. VBF  PU=200");
  leg_entry.push_back("Clean fix frac. ZB PU=200");
  leg_entry.push_back("Clean #eta-dep. frac. ZB  PU=200");


  TLegend* leg=new TLegend(0.2,0.6,0.6,0.8);
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

  prof[0]->GetXaxis()->SetTitle("|#eta(L1 jet)|");
  prof[0]->GetYaxis()->SetTitle("PUS [GeV]");
  prof[0]->GetYaxis()->SetTitleOffset(1.7);
  prof[0]->GetYaxis()->SetRangeUser(0,30.);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(1.61,30.1,"CMS Simulation Preliminary, #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_PUS_eta_PU200.pdf");  


}





