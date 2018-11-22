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






void plot_profile_L1jet_response_pt_master(std::vector<TH2F*> &histo, std::vector<TString> &leg_entry, std::string plotname ){

  
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
  prof[0]->GetYaxis()->SetRangeUser(-0.5,1.2);
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

  c->SaveAs( ("plots/profile_L1jet_response_pt_" + plotname+ ".pdf" ).c_str() );  

}


//NEW

void plot_profile_L1jet_response_pt_PU0_C3D_histo_refined(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  std::vector<TH2F*> histo;
  histo.push_back( single_plot2D("/vols/cms/snwebb/HGC_ntuples/VBF_Hinv_PU0_C3D_polarHisto_refinedMax/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2));
  histo.push_back( single_plot2D("/vols/cms/snwebb/HGC_ntuples/VBF_Hinv_PU0_C3D_polarHisto_refinedMax/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2));

  std::vector<TString> leg_entry;
  leg_entry.push_back("PU=0 cone");
  leg_entry.push_back("PU=0 cone + JEC");

  plot_profile_L1jet_response_pt_master ( histo, leg_entry, "PU0_test" );


}



void plot_profile_L1jet_response_pt_PU0_C3D_histo_refined_OLD(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";
  std::cout << __LINE__ << std::endl;

  TH2F* h_PU0_raw_refined = single_plot2D("/vols/cms/snwebb/HGC_ntuples/VBF_Hinv_PU0_C3D_polarHisto_refinedMax/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  TH2F* h_PU0_cal_refined = single_plot2D("/vols/cms/snwebb/HGC_ntuples/VBF_Hinv_PU0_C3D_polarHisto_refinedMax/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  std::cout << __LINE__ << std::endl;
  TH2F* h_PU0_raw_refined_tc = single_plot2D("/vols/cms/snwebb/HGC_ntuples/VBF_Hinv_PU0_C3D_polarHisto_refinedMax_TC/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  TH2F* h_PU0_cal_refined_tc = single_plot2D("/vols/cms/snwebb/HGC_ntuples/VBF_Hinv_PU0_C3D_polarHisto_refinedMax_TC/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","0.84*(5.09004e+00 -1.22767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  std::cout << __LINE__ << std::endl;

  TH2F* h_PU0_raw_crossrefined = single_plot2D("/vols/cms/snwebb/HGC_ntuples/VBF_Hinv_PU0_C3D_polarHisto_crossRefinedMax/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  TH2F* h_PU0_cal_crossrefined = single_plot2D("/vols/cms/snwebb/HGC_ntuples/VBF_Hinv_PU0_C3D_polarHisto_crossRefinedMax/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  std::cout << __LINE__ << std::endl;

  TH2F* h_PU0_raw_crossrefined_tc = single_plot2D("/vols/cms/snwebb/HGC_ntuples/VBF_Hinv_PU0_C3D_polarHisto_crossRefinedMax_TC/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  TH2F* h_PU0_cal_crossrefined_tc = single_plot2D("/vols/cms/snwebb/HGC_ntuples/VBF_Hinv_PU0_C3D_polarHisto_crossRefinedMax_TC/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","0.84*(5.09004e+00 -1.22767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);





  // TH2F* h_PU0_raw_histo_old = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_old/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  // TH2F* h_PU0_cal_histo_old = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_old/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.36*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  //  std::cout << __LINE__ << std::endl;

  // TH2F* h_PU0_raw_histo = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  // TH2F* h_PU0_cal_histo = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.17*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.07929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
 


  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw_refined);
  histo.push_back(h_PU0_cal_refined);
  histo.push_back(h_PU0_raw_refined_tc);
  histo.push_back(h_PU0_cal_refined_tc);
  histo.push_back(h_PU0_raw_crossrefined);
  histo.push_back(h_PU0_cal_crossrefined);
  histo.push_back(h_PU0_raw_crossrefined_tc);
  histo.push_back(h_PU0_cal_crossrefined_tc);


  //    std::cout << __LINE__ << std::endl;
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 cone");
  leg_entry.push_back("PU=0 cone + JEC");
  leg_entry.push_back("TC PU=0 cone");
  leg_entry.push_back("TC PU=0 cone + JEC");


  leg_entry.push_back("PU=0 cone cross");
  leg_entry.push_back("PU=0 cone + JEC cross");
  leg_entry.push_back("TC PU=0 cone cross");
  leg_entry.push_back("TC PU=0 cone + JEC cross");

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
  prof[0]->GetYaxis()->SetRangeUser(-0.5,1.2);
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


  c->SaveAs("plots/profile_L1jet_response_pt_PU0_refinedmax.pdf");  


}







void plot_profile_L1jet_response_pt_PU0_C3D_histo(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";


  TH2F* h_PU0_raw_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  TH2F* h_PU0_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);


  TH2F* h_PU0_raw_histo_old = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_old/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  TH2F* h_PU0_cal_histo_old = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_old/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.36*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);


  TH2F* h_PU0_raw_histo = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  TH2F* h_PU0_cal_histo = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.17*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.07929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
 


  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw_dRNNC2D);
  histo.push_back(h_PU0_raw_histo_old);
  histo.push_back(h_PU0_raw_histo);
  histo.push_back(h_PU0_cal_dRNNC2D);
  histo.push_back(h_PU0_cal_histo_old);
  histo.push_back(h_PU0_cal_histo);


  
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 cone");
  leg_entry.push_back("PU=0 histo old");
  leg_entry.push_back("PU=0 histo new");
  leg_entry.push_back("PU=0 cone + JEC");
  leg_entry.push_back("PU=0 histo + JEC");
  leg_entry.push_back("PU=0 histo new + JEC");

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
  prof[0]->GetYaxis()->SetRangeUser(-0.5,1.2);
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









void plot_profile_L1jet_response_eta_PU0_C3D_histo(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";


  TH2F* h_PU0_raw_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);
  TH2F* h_PU0_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);


  TH2F* h_PU0_raw_histo_old = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_old/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);
  TH2F* h_PU0_cal_histo_old = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_old/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","1.36*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);


  TH2F* h_PU0_raw_histo = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);
  TH2F* h_PU0_cal_histo = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","1.17*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.07929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);
 


  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw_dRNNC2D);
  histo.push_back(h_PU0_raw_histo_old);
  histo.push_back(h_PU0_raw_histo);
  histo.push_back(h_PU0_cal_dRNNC2D);
  histo.push_back(h_PU0_cal_histo_old);
  histo.push_back(h_PU0_cal_histo);


  
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 cone");
  leg_entry.push_back("PU=0 histo old");
  leg_entry.push_back("PU=0 histo new");
  leg_entry.push_back("PU=0 cone + JEC");
  leg_entry.push_back("PU=0 histo + JEC");
  leg_entry.push_back("PU=0 histo new + JEC");

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
  prof[0]->GetYaxis()->SetRangeUser(-0.6,1.2);
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


  c->SaveAs("plots/profile_L1jet_response_eta_PU0_histo.pdf");  


}








void plot_profile_L1jet_response_pt_PU0_C3D_histo_etaLower2p3(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.3 && genjet_pt[VBF_parton_genjet]>20";


  TH2F* h_PU0_raw_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  TH2F* h_PU0_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);


  TH2F* h_PU0_raw_histo_old = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_old/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  TH2F* h_PU0_cal_histo_old = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_old/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.36*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);


  TH2F* h_PU0_raw_histo = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  TH2F* h_PU0_cal_histo = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.17*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.07929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
 


  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw_dRNNC2D);
  histo.push_back(h_PU0_raw_histo_old);
  histo.push_back(h_PU0_raw_histo);
  histo.push_back(h_PU0_cal_dRNNC2D);
  histo.push_back(h_PU0_cal_histo_old);
  histo.push_back(h_PU0_cal_histo);


  
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 cone");
  leg_entry.push_back("PU=0 histo old");
  leg_entry.push_back("PU=0 histo new");
  leg_entry.push_back("PU=0 cone + JEC");
  leg_entry.push_back("PU=0 histo + JEC");
  leg_entry.push_back("PU=0 histo new + JEC");

  TLegend* leg=new TLegend(0.4,0.15,0.7,0.5);
  leg->SetHeader("#splitline{p_T(gen. jet)>20 GeV}{1.6<|#eta(gen.jet)|<2.3}");
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
  prof[0]->GetYaxis()->SetRangeUser(-0.5,1.2);
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


  c->SaveAs("plots/profile_L1jet_response_pt_PU0_histo_etaLower2p3.pdf");  


}








void plot_profile_L1jet_response_pt_PU0_C3D_histo_etaLarger2p5(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>2.5 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";


  TH2F* h_PU0_raw_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  TH2F* h_PU0_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);


  TH2F* h_PU0_raw_histo_old = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_old/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  TH2F* h_PU0_cal_histo_old = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_old/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.36*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);


  TH2F* h_PU0_raw_histo = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  TH2F* h_PU0_cal_histo = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.17*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.07929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
 


  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw_dRNNC2D);
  histo.push_back(h_PU0_raw_histo_old);
  histo.push_back(h_PU0_raw_histo);
  histo.push_back(h_PU0_cal_dRNNC2D);
  histo.push_back(h_PU0_cal_histo_old);
  histo.push_back(h_PU0_cal_histo);


  
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 cone");
  leg_entry.push_back("PU=0 histo old");
  leg_entry.push_back("PU=0 histo new");
  leg_entry.push_back("PU=0 cone + JEC");
  leg_entry.push_back("PU=0 histo + JEC");
  leg_entry.push_back("PU=0 histo new + JEC");

  TLegend* leg=new TLegend(0.4,0.15,0.7,0.5);
  leg->SetHeader("#splitline{p_T(gen. jet)>20 GeV}{2.5<|#eta(gen.jet)|<2.9}");
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
  prof[0]->GetYaxis()->SetRangeUser(-0.5,1.2);
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


  c->SaveAs("plots/profile_L1jet_response_pt_PU0_histo_etaLarger2p5.pdf");  


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
   histo[0]->GetYaxis()->SetRangeUser(0.,2*histo[0]->GetMaximum());
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











void plot_L1jet_response_pt_PU0_C3D_histo_pt200(){


  TString filename_dRNNC2D = "/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root";
  TString filename_histo = "/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root";
  TString filename_histo_0p03 = "/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C3D_polarHisto_dR0p03/jet_ntuples_merged/ntuple_jet_merged_*.rootet_merged_*.root";
  TString filename_histo_thresh_20MIPT = "/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_thresh_20MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root";
  TString filename_histo_thresh_50MIPT = "/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_thresh_50MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root";


  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  TH1F* h_PU0_cal_dRNNC2D= single_plot(filename_dRNNC2D,"HGCalTriggerNtupleJet","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& genjet_pt[VBF_parton_genjet]>190 && genjet_pt[VBF_parton_genjet]<210",125,0.,2.5);

  TH1F* h_PU0_cal_histo = single_plot(filename_histo,"HGCalTriggerNtupleJet","1.17*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.07929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& genjet_pt[VBF_parton_genjet]>190 && genjet_pt[VBF_parton_genjet]<210",125,0.,2.5);

  TH1F* h_PU0_cal_histo_0p03 = single_plot(filename_histo_0p03,"HGCalTriggerNtupleJet","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& genjet_pt[VBF_parton_genjet]>190 && genjet_pt[VBF_parton_genjet]<210",125,0.,2.5);

    TH1F* h_PU0_cal_histo_thresh_20MIPT = single_plot(filename_histo_thresh_20MIPT,"HGCalTriggerNtupleJet","1.10*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.01929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& genjet_pt[VBF_parton_genjet]>190 && genjet_pt[VBF_parton_genjet]<210",125,0.,2.5);

    TH1F* h_PU0_cal_histo_thresh_50MIPT = single_plot(filename_histo_thresh_50MIPT,"HGCalTriggerNtupleJet","1.20*(4.98004e+00 -1.25767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& genjet_pt[VBF_parton_genjet]>190 && genjet_pt[VBF_parton_genjet]<210",125,0.,2.5);


  vector<TH1F*> histo;
  histo.push_back(h_PU0_cal_dRNNC2D);
  histo.push_back(h_PU0_cal_histo);
  histo.push_back(h_PU0_cal_histo_0p03);
  histo.push_back(h_PU0_cal_histo_thresh_20MIPT);
  histo.push_back(h_PU0_cal_histo_thresh_50MIPT);

   vector<TString> leg_entry;
  leg_entry.push_back("Cone dr=0.01");
  leg_entry.push_back("#splitline{Histo dr=0.01}{Max. finding}");
  leg_entry.push_back("#splitline{Histo dr=0.03}{Max. finding}");
  leg_entry.push_back("#splitline{Histo dr=0.01}{20 MIPT-thresh.}");
  leg_entry.push_back("#splitline{Histo dr=0.01}{50 MIPT-thresh.}");


   TLegend* leg=new TLegend(0.5,0.35,0.75,0.85);
   leg->SetHeader("#splitline{190<p_{T}(gen. jet)<210 GeV}{1.6<|#eta(gen.jet)|<2.9}");
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
   histo[0]->GetYaxis()->SetRangeUser(0.,2*histo[0]->GetMaximum());
   //histo[0]->SetMaximum(2*histo[0]->GetMaximum());
   histo[0]->SetStats(0);
   histo[0]->SetTitle("");
   histo[0]->Draw();
   
   for(unsigned int i=1;i<histo.size();i++)
     histo[i]->Draw("same");
   leg->Draw("same");
   
   
   TLatex *texl = new TLatex(0.01,1.02*histo[0]->GetMaximum(),"CMS Simulation Preliminary, VBF H#rightarrowinv. #sqrt{s}=14 TeV, PU=0");
   texl->SetTextSize(0.03);
   texl->Draw("same");
   
   gPad->SetTicks();
   
   
   c->SaveAs("plots/L1jet_response_pt_PU0_C3D_histo_pt200.pdf");  




}









void plot_L1jet_nC3D_PU0_C3D_histo(){


  TString filename_dRNNC2D = "/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root";
  TString filename_histo = "/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root";
  TString filename_histo_0p03 = "/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C3D_polarHisto_dR0p03/jet_ntuples_merged/ntuple_jet_merged_*.root";
  TString filename_histo_thresh_20MIPT = "/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_thresh_20MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root";
  TString filename_histo_thresh_50MIPT = "/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_thresh_50MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root";

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";


  TH1F* h_PU0_dRNNC2D = single_plot(filename_dRNNC2D,"HGCalTriggerNtupleJet","jets_ncl3d[VBF_parton_jets]",cut+"&& genjet_pt[VBF_parton_genjet]>190 && genjet_pt[VBF_parton_genjet]<210",50,0.,50.);
  TH1F* h_PU0_histo = single_plot(filename_histo,"HGCalTriggerNtupleJet","jets_ncl3d[VBF_parton_jets]",cut+"&& genjet_pt[VBF_parton_genjet]>190 && genjet_pt[VBF_parton_genjet]<210",50,0.,50.);
    TH1F* h_PU0_histo_0p03 = single_plot(filename_histo_0p03,"HGCalTriggerNtupleJet","jets_ncl3d[VBF_parton_jets]",cut+"&& genjet_pt[VBF_parton_genjet]>190 && genjet_pt[VBF_parton_genjet]<210",50,0.,50.);
  TH1F* h_PU0_histo_thresh_20MIPT = single_plot(filename_histo_thresh_20MIPT,"HGCalTriggerNtupleJet","jets_ncl3d[VBF_parton_jets]",cut+"&& genjet_pt[VBF_parton_genjet]>190 && genjet_pt[VBF_parton_genjet]<210",50,0.,50.);
   TH1F* h_PU0_histo_thresh_50MIPT = single_plot(filename_histo_thresh_50MIPT,"HGCalTriggerNtupleJet","jets_ncl3d[VBF_parton_jets]",cut+"&& genjet_pt[VBF_parton_genjet]>190 && genjet_pt[VBF_parton_genjet]<210",50,0.,50.);
  

  vector<TH1F*> histo;
  histo.push_back(h_PU0_dRNNC2D);
  histo.push_back(h_PU0_histo);
  histo.push_back(h_PU0_histo_0p03);
   histo.push_back(h_PU0_histo_thresh_20MIPT);
   histo.push_back(h_PU0_histo_thresh_50MIPT);

  vector<TString> leg_entry;
  leg_entry.push_back("Cone dr=0.01");
  leg_entry.push_back("#splitline{Histo dr=0.01}{Max. finding}");
  leg_entry.push_back("#splitline{Histo dr=0.03}{Max. finding}");
  leg_entry.push_back("#splitline{Histo dr=0.01}{20 MIPT-thresh.}");
  leg_entry.push_back("#splitline{Histo dr=0.01}{50 MIPT-thresh.}");


   TLegend* leg=new TLegend(0.4,0.35,0.75,0.85);
   leg->SetHeader("#splitline{190<p_{T}(gen. jet)<210 GeV}{1.6<|#eta(gen.jet)|<2.9}");
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
   

   TLatex *texl = new TLatex(0.01,1.02*histo[0]->GetMaximum(),"CMS Simulation Preliminary, VBF H#rightarrowinv. #sqrt{s}=14 TeV, PU=0");
   texl->SetTextSize(0.03);
   texl->Draw("same");
   
   gPad->SetTicks();
   
   
   c->SaveAs("plots/L1jet_nC3D_PU0_C3D_histo.pdf");  




}
















void plot_C3D_pt_PU0_C3D_histo(){


  TString filename_dRNNC2D = "/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1*.root";
  TString filename_histo = "/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_1*.root";
  TString filename_histo_0p03 = "/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C3D_polarHisto_dR0p03/jet_ntuples_merged/ntuple_jet_merged_1*.root";
  TString filename_histo_thresh_20MIPT = "/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_thresh_20MIPT/jet_ntuples_merged/ntuple_jet_merged_1*.root";
  TString filename_histo_thresh_50MIPT = "/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_thresh_50MIPT/jet_ntuples_merged/ntuple_jet_merged_1*.root";



  TH1F* h_PU0_dRNNC2D = single_plot(filename_dRNNC2D,"HGCalTriggerNtupleJet","cl3d_pt","1",100,0.,50.);
  TH1F* h_PU0_histo = single_plot(filename_histo,"HGCalTriggerNtupleJet","cl3d_pt","1",100,0.,50.);
  TH1F* h_PU0_histo_0p03 = single_plot(filename_histo_0p03,"HGCalTriggerNtupleJet","cl3d_pt","1",100,0.,50.);
  TH1F* h_PU0_histo_thresh_20MIPT = single_plot(filename_histo_thresh_20MIPT,"HGCalTriggerNtupleJet","cl3d_pt","1",100,0.,50.);
  TH1F* h_PU0_histo_thresh_50MIPT = single_plot(filename_histo_thresh_50MIPT,"HGCalTriggerNtupleJet","cl3d_pt","1",100,0.,50.);


  TH1F* h_PU0_dRNNC2D_norm = single_plot(filename_dRNNC2D,"HGCalTriggerNtupleJet","1","1",3,0.,3.);
  TH1F* h_PU0_histo_norm = single_plot(filename_histo,"HGCalTriggerNtupleJet","1","1",3,0.,3.);
  TH1F* h_PU0_histo_0p03_norm = single_plot(filename_histo_0p03,"HGCalTriggerNtupleJet","1","1",3,0.,3.);
  TH1F* h_PU0_histo_thresh_20MIPT_norm = single_plot(filename_histo_thresh_20MIPT,"HGCalTriggerNtupleJet","1","1",3,0.,3.);
  TH1F* h_PU0_histo_thresh_50MIPT_norm = single_plot(filename_histo_thresh_50MIPT,"HGCalTriggerNtupleJet","1","1",3,0.,3.);
  

  vector<TH1F*> histo;
  histo.push_back(h_PU0_dRNNC2D);
  histo.push_back(h_PU0_histo);
  histo.push_back(h_PU0_histo_0p03);
  histo.push_back(h_PU0_histo_thresh_20MIPT);
  histo.push_back(h_PU0_histo_thresh_50MIPT);


  vector<TH1F*> histo_norm;
  histo_norm.push_back(h_PU0_dRNNC2D_norm);
  histo_norm.push_back(h_PU0_histo_norm);
  histo_norm.push_back(h_PU0_histo_0p03_norm);
  histo_norm.push_back(h_PU0_histo_thresh_20MIPT_norm);
  histo_norm.push_back(h_PU0_histo_thresh_50MIPT_norm);

  vector<TString> leg_entry;
  leg_entry.push_back("Cone dr=0.01");
  leg_entry.push_back("#splitline{Histo dr=0.01}{Max. finding}");
  leg_entry.push_back("#splitline{Histo dr=0.03}{Max. finding}");
  leg_entry.push_back("#splitline{Histo dr=0.01}{20 MIPT-thresh.}");
  leg_entry.push_back("#splitline{Histo dr=0.01}{50 MIPT-thresh.}");


   TLegend* leg=new TLegend(0.4,0.35,0.75,0.85);
   leg->SetFillColor(0);
   leg->SetBorderSize(0);
   leg->SetTextSize(0.03);
  
   for(unsigned int i=0;i<histo.size();i++){
     TH1F* h = histo[i];
     TH1F* h_norm = histo_norm[i];    
     h->Scale(1/h_norm->Integral());
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
   histo[0]->GetYaxis()->SetTitle("C3D per event");
   histo[0]->GetYaxis()->SetTitleOffset(1.7);
   //histo[0]->GetYaxis()->SetRangeUser(0,2*histo[0]->GetMaximum());
   histo[0]->SetMaximum(2*histo[0]->GetMaximum());
   histo[0]->SetStats(0);
   histo[0]->SetTitle("");
   histo[0]->Draw();
   
   for(unsigned int i=1;i<histo.size();i++)
     histo[i]->Draw("same");
   leg->Draw("same");
   

   TLatex *texl = new TLatex(0.01,1.2*histo[0]->GetMaximum(),"CMS Simulation Preliminary, VBF H#rightarrowinv. #sqrt{s}=14 TeV, PU=0");
   texl->SetTextSize(0.03);
   texl->Draw("same");
   
   gPad->SetTicks();
   
   
   c->SaveAs("plots/C3D_pt_PU0_C3D_histo.pdf");  




}












void plot_profile_L1jet_response_pt_PU200_PUS_C3D_histo(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";


  TH2F* h_PU0_raw_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

    TH2F* h_PU200_PUS_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_raw_histo_old = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_old/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

    TH2F* h_PU200_PUS_histo_old = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto_old/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","max(jets_pt[VBF_parton_jets]-0.7*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-0.7*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);
 
  TH2F* h_PU0_raw_histo = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU200_PUS_histo = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","max(jets_pt[VBF_parton_jets]-1.1*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-1.1*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);


  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw_dRNNC2D);
  histo.push_back(h_PU0_raw_histo_old);
  histo.push_back(h_PU0_raw_histo);
  histo.push_back(h_PU200_PUS_dRNNC2D);
  histo.push_back(h_PU200_PUS_histo_old);
  histo.push_back(h_PU200_PUS_histo);


  
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 cone");
  leg_entry.push_back("PU=0 histo old");
  leg_entry.push_back("PU=0 histo new");
  leg_entry.push_back("PU=200 cone + PUS");
  leg_entry.push_back("PU=200 histo old + PUS");
  leg_entry.push_back("PU=200 histo new + PUS");

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
  prof[0]->GetYaxis()->SetRangeUser(-0.6,1.2);
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


  c->SaveAs("plots/profile_L1jet_response_pt_PU200_PUS_histo.pdf");  


}




void plot_profile_L1jet_response_pt_PU200_raw_C3D_histo(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";


  TH2F* h_PU0_raw_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU200_raw_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);


  TH2F* h_PU0_raw_histo_old = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_old/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU200_raw_histo_old = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto_old/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

 
  TH2F* h_PU0_raw_histo = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU200_raw_histo = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);




  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw_dRNNC2D);
  histo.push_back(h_PU0_raw_histo_old);
  histo.push_back(h_PU0_raw_histo);
  histo.push_back(h_PU200_raw_dRNNC2D);
  histo.push_back(h_PU200_raw_histo_old);
  histo.push_back(h_PU200_raw_histo);


  
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 cone");
  leg_entry.push_back("PU=0 histo old");
  leg_entry.push_back("PU=0 histo new");
  leg_entry.push_back("PU=200 cone");
  leg_entry.push_back("PU=200 histo old");
  leg_entry.push_back("PU=200 histo new");

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
  prof[0]->GetYaxis()->SetRangeUser(-0.6,1.2);
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


  c->SaveAs("plots/profile_L1jet_response_pt_PU200_raw_histo.pdf");  


}







void plot_profile_L1jet_response_eta_PU200_PUS_C3D_histo(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";


  TH2F* h_PU0_raw_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);
  TH2F* h_PU200_PUS_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",13,1.2,2.9,97,0.06,2);


  TH2F* h_PU0_raw_histo_old = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_old/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);
    TH2F* h_PU200_PUS_histo_old = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto_old/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","max(jets_pt[VBF_parton_jets]-0.7*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-0.7*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",13,1.6,2.9,97,0.06,2);



  TH2F* h_PU0_raw_histo = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);
   TH2F* h_PU200_PUS_histo = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","max(jets_pt[VBF_parton_jets]-1.1*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-1.1*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",13,1.6,2.9,97,0.06,2);



  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw_dRNNC2D);
  histo.push_back(h_PU0_raw_histo_old);
  histo.push_back(h_PU0_raw_histo);
  histo.push_back(h_PU200_PUS_dRNNC2D);
  histo.push_back(h_PU200_PUS_histo_old);
  histo.push_back(h_PU200_PUS_histo);


  
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 cone");
  leg_entry.push_back("PU=0 histo old");
  leg_entry.push_back("PU=0 histo new");
  leg_entry.push_back("PU=200 cone + PUS");
  leg_entry.push_back("PU=200 histo old + PUS");
  leg_entry.push_back("PU=200 histo new + PUS");


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
  prof[0]->GetYaxis()->SetRangeUser(-0.6,1.2);
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


  c->SaveAs("plots/profile_L1jet_response_eta_PU200_PUS_histo.pdf");  


}







void plot_profile_L1jet_response_pt_PU200_C3D_histo(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  TH2F* h_PU200_PUS_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);

  TH2F* h_PU200_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);

  TH2F* h_PU200_PUS_histo_old = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto_old/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","max(jets_pt[VBF_parton_jets]-0.7*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-0.7*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);

  TH2F* h_PU200_cal_histo_old = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto_old/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.36*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-0.7*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-0.7*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-0.7*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-0.7*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);


  TH2F* h_PU200_PUS_histo = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","max(jets_pt[VBF_parton_jets]-1.1*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-1.1*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);

  TH2F* h_PU200_cal_histo = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.17*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-1.1*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.07929e-01* pow(log(max(jets_pt[VBF_parton_jets]-1.1*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-1.1*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-1.1*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);
 


  vector<TH2F*> histo;
  histo.push_back(h_PU200_PUS_dRNNC2D);
  histo.push_back(h_PU200_PUS_histo_old);
  histo.push_back(h_PU200_PUS_histo);
  histo.push_back(h_PU200_cal_dRNNC2D);
  histo.push_back(h_PU200_cal_histo_old);
  histo.push_back(h_PU200_cal_histo);


  
  vector<TString> leg_entry;
  leg_entry.push_back("PU=200 cone + PUS");
  leg_entry.push_back("PU=200 histo old + PUS");
  leg_entry.push_back("PU=200 histo new + PUS");
  leg_entry.push_back("PU=200 cone + PUS + JEC");
  leg_entry.push_back("PU=200 histo + PUS + JEC");
  leg_entry.push_back("PU=200 histo new + PUS + JEC");

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
  prof[0]->GetYaxis()->SetRangeUser(-0.6,1.2);
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


  c->SaveAs("plots/profile_L1jet_response_pt_PU200_histo.pdf");  


}








void plot_turnons_L1SingleJet_dRNNC2D_histo_PU200(int L1pt_dRNNC2D, int L1pt_histo){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  double x[18]={0,40,60,70,80,90,100,110,120,130,140,160,180,200,250,300,400,500};
  int nbins=17;

  //double x[15]={0,25,35,40,45,50,55,60,65,75,80,90,100,120,150};
  //int nbins=14;

  TH1F* h_PU200_denom_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_cal_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i",L1pt_dRNNC2D),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D->Divide(h_PU200_cal_dRNNC2D,h_PU200_denom_dRNNC2D);



   TH1F* h_PU200_denom_histo = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_cal_histo = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.17*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-1.1*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.07929e-01* pow(log(max(jets_pt[VBF_parton_jets]-1.1*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-1.1*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i",L1pt_histo),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_histo = new TGraphAsymmErrors();
  gr_PU200_cal_histo->Divide(h_PU200_cal_histo,h_PU200_denom_histo);



  vector<TGraphAsymmErrors*> turnons;
  turnons.push_back(gr_PU200_cal_dRNNC2D);
  turnons.push_back(gr_PU200_cal_histo);

  vector<TString> leg_entry;
  leg_entry.push_back(Form("Cone SingleJet%i",L1pt_dRNNC2D));
  leg_entry.push_back(Form("Histo SingleJet%i",L1pt_histo));

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


  c->SaveAs(Form("plots/turnons_L1SingleJet%i_dRNNC2D_SingleJet%i_histo_PU200.pdf",L1pt_dRNNC2D,L1pt_histo));  


}








void plot_profile_L1jet_response_pt_PU0_C3D_histo_raw(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  TH2F* h_PU0_raw_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_raw_histo = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_raw_histo_0p03 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C3D_polarHisto_dR0p03/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_raw_histo_thresh_20MIPT = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_thresh_20MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_raw_histo_thresh_50MIPT = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_thresh_50MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  

  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw_dRNNC2D);
  histo.push_back(h_PU0_raw_histo);
  histo.push_back(h_PU0_raw_histo_0p03);
  histo.push_back(h_PU0_raw_histo_thresh_20MIPT);
  histo.push_back(h_PU0_raw_histo_thresh_50MIPT);

  
  vector<TString> leg_entry;
  leg_entry.push_back("Cone dr=0.01");
  leg_entry.push_back("Histo dr=0.01 Max. finding");
  leg_entry.push_back("Histo dr=0.03 Max. finding");
  leg_entry.push_back("Histo dr=0.01 20 MIPT-thresh.");
  leg_entry.push_back("Histo dr=0.01 50 MIPT-thresh.");

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
  prof[0]->GetYaxis()->SetRangeUser(-0.5,1.2);
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


  c->SaveAs("plots/profile_L1jet_response_pt_PU0_histo_raw.pdf");  


}









void plot_profile_L1jet_response_pt_PU0_C3D_histo_cal(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  TH2F* h_PU0_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_cal_histo = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.17*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.07929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_cal_histo_0p03 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C3D_polarHisto_dR0p03/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_cal_histo_thresh_20MIPT = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_thresh_20MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.10*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.01929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_cal_histo_thresh_50MIPT = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_thresh_50MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.20*(4.98004e+00 -1.25767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);


  vector<TH2F*> histo;
  histo.push_back(h_PU0_cal_dRNNC2D);
  histo.push_back(h_PU0_cal_histo);
  histo.push_back(h_PU0_cal_histo_0p03);
  histo.push_back(h_PU0_cal_histo_thresh_20MIPT);
  histo.push_back(h_PU0_cal_histo_thresh_50MIPT);

  
  vector<TString> leg_entry;
  leg_entry.push_back("Cone dr=0.01");
  leg_entry.push_back("Histo dr=0.01 Max. finding");
  leg_entry.push_back("Histo dr=0.03 Max. finding");
  leg_entry.push_back("Histo dr=0.01 20 MIPT-thresh.");
  leg_entry.push_back("Histo dr=0.01 50 MIPT-thresh.");


  TLegend* leg=new TLegend(0.3,0.15,0.7,0.5);
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
  prof[0]->GetYaxis()->SetRangeUser(-0.5,1.2);
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


  c->SaveAs("plots/profile_L1jet_response_pt_PU0_histo_cal.pdf");  


}







void plot_profile_L1jet_response_pt_PU0_C3D_histo_cal_Lower2p4(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.4 && genjet_pt[VBF_parton_genjet]>20";

  TH2F* h_PU0_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_cal_histo = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.17*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.07929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_cal_histo_0p03 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C3D_polarHisto_dR0p03/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_cal_histo_thresh_20MIPT = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_thresh_20MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.10*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.01929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_cal_histo_thresh_50MIPT = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_thresh_50MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.20*(4.98004e+00 -1.25767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);


  vector<TH2F*> histo;
  histo.push_back(h_PU0_cal_dRNNC2D);
  histo.push_back(h_PU0_cal_histo);
  histo.push_back(h_PU0_cal_histo_0p03);
  histo.push_back(h_PU0_cal_histo_thresh_20MIPT);
  histo.push_back(h_PU0_cal_histo_thresh_50MIPT);

  
  vector<TString> leg_entry;
  leg_entry.push_back("Cone dr=0.01");
  leg_entry.push_back("Histo dr=0.01 Max. finding");
  leg_entry.push_back("Histo dr=0.03 Max. finding");
  leg_entry.push_back("Histo dr=0.01 20 MIPT-thresh.");
  leg_entry.push_back("Histo dr=0.01 50 MIPT-thresh.");


  TLegend* leg=new TLegend(0.3,0.15,0.7,0.5);
  leg->SetHeader("#splitline{p_{T}(gen. jet)>20 GeV}{1.6<|#eta(gen.jet)|<2.4}");
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
  prof[0]->GetYaxis()->SetRangeUser(-0.5,1.2);
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


  c->SaveAs("plots/profile_L1jet_response_pt_PU0_histo_cal_Lower2p4.pdf");  


}








void plot_profile_L1jet_response_pt_PU0_C3D_histo_cal_Larger2p4(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>2.4 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  TH2F* h_PU0_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_cal_histo = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.17*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.07929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_cal_histo_0p03 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C3D_polarHisto_dR0p03/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_cal_histo_thresh_20MIPT = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_thresh_20MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.10*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.01929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_cal_histo_thresh_50MIPT = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_thresh_50MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.20*(4.98004e+00 -1.25767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);


  vector<TH2F*> histo;
  histo.push_back(h_PU0_cal_dRNNC2D);
  histo.push_back(h_PU0_cal_histo);
  histo.push_back(h_PU0_cal_histo_0p03);
  histo.push_back(h_PU0_cal_histo_thresh_20MIPT);
  histo.push_back(h_PU0_cal_histo_thresh_50MIPT);

  
  vector<TString> leg_entry;
  leg_entry.push_back("Cone dr=0.01");
  leg_entry.push_back("Histo dr=0.01 Max. finding");
  leg_entry.push_back("Histo dr=0.03 Max. finding");
  leg_entry.push_back("Histo dr=0.01 20 MIPT-thresh.");
  leg_entry.push_back("Histo dr=0.01 50 MIPT-thresh.");


  TLegend* leg=new TLegend(0.3,0.15,0.7,0.5);
  leg->SetHeader("#splitline{p_{T}(gen. jet)>20 GeV}{2.4<|#eta(gen.jet)|<2.9}");
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
  prof[0]->GetYaxis()->SetRangeUser(-0.5,1.2);
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


  c->SaveAs("plots/profile_L1jet_response_pt_PU0_histo_cal_Larger2p4.pdf");  


}









void plot_profile_L1jet_response_eta_PU0_C3D_histo_cal(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  TH2F* h_PU0_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);

  TH2F* h_PU0_cal_histo = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","1.17*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.07929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);

  TH2F* h_PU0_cal_histo_0p03 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C3D_polarHisto_dR0p03/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);

  TH2F* h_PU0_cal_histo_thresh_20MIPT = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_thresh_20MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","1.10*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.01929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);

  TH2F* h_PU0_cal_histo_thresh_50MIPT = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_thresh_50MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","1.20*(4.98004e+00 -1.25767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);


  vector<TH2F*> histo;
  histo.push_back(h_PU0_cal_dRNNC2D);
  histo.push_back(h_PU0_cal_histo);
  histo.push_back(h_PU0_cal_histo_0p03);
  histo.push_back(h_PU0_cal_histo_thresh_20MIPT);
  histo.push_back(h_PU0_cal_histo_thresh_50MIPT);

  
  vector<TString> leg_entry;
  leg_entry.push_back("Cone dr=0.01");
  leg_entry.push_back("Histo dr=0.01 Max. finding");
  leg_entry.push_back("Histo dr=0.03 Max. finding");
  leg_entry.push_back("Histo dr=0.01 20 MIPT-thresh.");
  leg_entry.push_back("Histo dr=0.01 50 MIPT-thresh.");


  TLegend* leg=new TLegend(0.3,0.15,0.7,0.5);
  leg->SetHeader("#splitline{p_{T}(gen. jet)>20 GeV}{1.6<|#eta(gen.jet)|<2.4}");
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
  prof[0]->GetYaxis()->SetRangeUser(-0.5,1.2);
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


  c->SaveAs("plots/profile_L1jet_response_eta_PU0_histo_cal.pdf");  


}








void plot_profile_L1jet_response_eta_PU200_PUS_C3D_histo_test(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";


  TH2F* h_PU0_raw_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);
  TH2F* h_PU200_PUS_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",13,1.2,2.9,97,0.06,2);

  TH2F* h_PU200_PUS_dRNNC2D_test = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","max(jets_pt[VBF_parton_jets]-10*190*3.14159*pow(0.01,2)*tanh(abs(jets_eta[VBF_parton_jets]))*pow(sinh(abs(jets_eta[VBF_parton_jets])),2),0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-10*190*3.14159*pow(0.01,2)*tanh(abs(jets_eta[VBF_parton_jets]))*pow(sinh(abs(jets_eta[VBF_parton_jets])),2))>0",13,1.2,2.9,97,0.06,2);


  //TH2F* h_PU0_raw_histo = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",13,1.6,2.9,97,0.06,2);
  //TH2F* h_PU200_PUS_histo = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta[VBF_parton_genjet])","max(jets_pt[VBF_parton_jets]-1.1*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-1.1*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",13,1.6,2.9,97,0.06,2);



  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw_dRNNC2D);
  //histo.push_back(h_PU0_raw_histo);
  histo.push_back(h_PU200_PUS_dRNNC2D);
  histo.push_back(h_PU200_PUS_dRNNC2D_test);
  //histo.push_back(h_PU200_PUS_histo);


  
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 cone");
  //leg_entry.push_back("PU=0 histo new");
  leg_entry.push_back("PU=200 cone + PUS");
  leg_entry.push_back("PU=200 cone + PUS test");
  //leg_entry.push_back("PU=200 histo new + PUS");


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
  prof[0]->GetYaxis()->SetRangeUser(-0.6,1.2);
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


  c->SaveAs("plots/profile_L1jet_response_eta_PU200_PUS_histo_test.pdf");  


}










void plot_profile_L1jet_response_pt_PU200_C3D_histo_raw_test(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  TH2F* h_PU200_raw_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU200_raw_histo = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU200_raw_histo_0p03 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C3D_polarHisto_dR0p03/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU200_raw_histo_thresh_20MIPT = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto_thresh_20MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU200_raw_histo_thresh_50MIPT = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto_thresh_50MIPT/jet_ntuples_merged/ntuple_jet_merged_1*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);



  vector<TH2F*> histo;
  histo.push_back(h_PU200_raw_dRNNC2D);
  histo.push_back(h_PU200_raw_histo);
  histo.push_back(h_PU200_raw_histo_0p03);
  histo.push_back(h_PU200_raw_histo_thresh_20MIPT);
  histo.push_back(h_PU200_raw_histo_thresh_50MIPT);

  vector<TString> leg_entry;
  leg_entry.push_back("Cone dr=0.01");
  leg_entry.push_back("Histo dr=0.01 Max. finding");
  leg_entry.push_back("Histo dr=0.03 Max. finding");
  leg_entry.push_back("Histo dr=0.01 20 MIPT-thresh.");
  leg_entry.push_back("Histo dr=0.01 50 MIPT-thresh.");
  



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
  prof[0]->GetYaxis()->SetRangeUser(-0.6,1.2);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(2.,1.21,"CMS Simulation Preliminary, VBF H#rightarrowinv. PU=200 #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(0,1,500,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_response_pt_PU200_raw_histo.pdf");  


}














void plot_profile_L1jet_response_pt_PU200_C3D_histo_cal(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  TH2F* h_PU200_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);

  TH2F* h_PU200_cal_histo = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.17*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-1.1*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.07929e-01* pow(log(max(jets_pt[VBF_parton_jets]-1.1*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * (jets_pt[VBF_parton_jets]-1.1*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-1.1*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);

  TH2F* h_PU200_cal_histo_0p03 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C3D_polarHisto_dR0p03/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);

  TH2F* h_PU200_cal_histo_thresh_20MIPT = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto_thresh_20MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.10*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.01929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);

  TH2F* h_PU200_cal_histo_thresh_50MIPT = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto_thresh_50MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.20*(4.98004e+00 -1.25767e+00 * log(max(jets_pt[VBF_parton_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * (jets_pt[VBF_parton_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);


  vector<TH2F*> histo;
  histo.push_back(h_PU200_cal_dRNNC2D);
  histo.push_back(h_PU200_cal_histo);
  histo.push_back(h_PU200_cal_histo_0p03);
  histo.push_back(h_PU200_cal_histo_thresh_20MIPT);
  histo.push_back(h_PU200_cal_histo_thresh_50MIPT);

  
  vector<TString> leg_entry;
 leg_entry.push_back("Cone dr=0.01");
  leg_entry.push_back("Histo dr=0.01 Max. finding");
  leg_entry.push_back("Histo dr=0.03 Max. finding");
  leg_entry.push_back("Histo dr=0.01 20 MIPT-thresh.");
  leg_entry.push_back("Histo dr=0.01 50 MIPT-thresh.");


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
  prof[0]->GetYaxis()->SetRangeUser(-0.5,1.2);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(2.,1.21,"CMS Simulation Preliminary, VBF H#rightarrowinv. PU=200 #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(0,1,500,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_response_pt_PU200_histo_cal.pdf");  


}










void plot_turnons_L1SingleJet_histo_PU200_test(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  double x[18]={0,40,60,70,80,90,100,110,120,130,140,160,180,200,250,300,400,500};
  int nbins=17;

  //double x[15]={0,25,35,40,45,50,55,60,65,75,80,90,100,120,150};
  //int nbins=14;

  int L1pt_dRNNC2D = 100;
  TH1F* h_PU200_denom_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_cal_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i",L1pt_dRNNC2D),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D->Divide(h_PU200_cal_dRNNC2D,h_PU200_denom_dRNNC2D);


  int L1pt_histo = 97;
  TH1F* h_PU200_denom_histo = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_cal_histo = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.17*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-1.1*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.07929e-01* pow(log(max(jets_pt[VBF_parton_jets]-1.1*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-1.1*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i",L1pt_histo),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_histo = new TGraphAsymmErrors();
  gr_PU200_cal_histo->Divide(h_PU200_cal_histo,h_PU200_denom_histo);

  int L1pt_histo_0p03 = 98;
  TH1F* h_PU200_denom_histo_0p03 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C3D_polarHisto_dR0p03/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_cal_histo_0p03 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C3D_polarHisto_dR0p03/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i",L1pt_histo_0p03),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_histo_0p03 = new TGraphAsymmErrors();
  gr_PU200_cal_histo_0p03->Divide(h_PU200_cal_histo_0p03,h_PU200_denom_histo_0p03);
 
  int L1pt_histo_thresh_20MIPT = 95;
  TH1F* h_PU200_denom_histo_thresh_20MIPT = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto_thresh_20MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_cal_histo_thresh_20MIPT = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto_thresh_20MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.10*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.01929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i",L1pt_histo_thresh_20MIPT),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_histo_thresh_20MIPT = new TGraphAsymmErrors();
  gr_PU200_cal_histo_thresh_20MIPT->Divide(h_PU200_cal_histo_thresh_20MIPT,h_PU200_denom_histo_thresh_20MIPT);
  
  int L1pt_histo_thresh_50MIPT = 98;
  TH1F* h_PU200_denom_histo_thresh_50MIPT = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto_thresh_50MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_cal_histo_thresh_50MIPT = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto_thresh_50MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.20*(4.98004e+00 -1.25767e+00 * log(max(jets_pt[VBF_parton_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i",L1pt_histo_thresh_50MIPT),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_histo_thresh_50MIPT = new TGraphAsymmErrors();
  gr_PU200_cal_histo_thresh_50MIPT->Divide(h_PU200_cal_histo_thresh_50MIPT,h_PU200_denom_histo_thresh_50MIPT);

  vector<TGraphAsymmErrors*> turnons;
  turnons.push_back(gr_PU200_cal_dRNNC2D);
  turnons.push_back(gr_PU200_cal_histo);
  turnons.push_back(gr_PU200_cal_histo_0p03);
  turnons.push_back(gr_PU200_cal_histo_thresh_20MIPT);
  turnons.push_back(gr_PU200_cal_histo_thresh_50MIPT);

  vector<TString> leg_entry;
  leg_entry.push_back(Form("Cone dR=0.01 SingleJet%i",L1pt_dRNNC2D));
  leg_entry.push_back(Form("#splitline{Histo dR=0.01 Max. finding}{SingleJet%i}",L1pt_histo));
  leg_entry.push_back(Form("#splitline{Histo dR=0.03 Max. finding}{SingleJet%i}",L1pt_histo_0p03));
  leg_entry.push_back(Form("#splitline{Histo dR=0.01 20 MIPT-thresh.}{SingleJet%i}",L1pt_histo_thresh_20MIPT));
  leg_entry.push_back(Form("#splitline{Histo dR=0.01 50 MIPT-thresh.}{SingleJet%i}",L1pt_histo_thresh_50MIPT));

  leg_entry.push_back(Form("Histo dR=0.01 thresh. 50MIPT SingleJet%i",L1pt_histo_thresh_50MIPT));

  TLegend* leg=new TLegend(0.4,0.12,0.85,0.55);
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


  c->SaveAs("plots/turnons_L1SingleJet_histo_PU200_test.pdf");  


}







void plot_turnons_L1SingleJet_histo_PU200_lowthresh_test(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  //double x[18]={0,40,60,70,80,90,100,110,120,130,140,160,180,200,250,300,400,500};
  //int nbins=17;

  double x[16]={0,25,35,40,45,50,55,60,65,70,75,80,90,100,120,150};
  int nbins=15;

  int L1pt_dRNNC2D = 50;
  TH1F* h_PU200_denom_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_cal_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i",L1pt_dRNNC2D),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D->Divide(h_PU200_cal_dRNNC2D,h_PU200_denom_dRNNC2D);


  int L1pt_histo = 54;
  TH1F* h_PU200_denom_histo = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_cal_histo = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.17*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-1.1*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.07929e-01* pow(log(max(jets_pt[VBF_parton_jets]-1.1*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-1.1*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i",L1pt_histo),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_histo = new TGraphAsymmErrors();
  gr_PU200_cal_histo->Divide(h_PU200_cal_histo,h_PU200_denom_histo);

  int L1pt_histo_0p03 = 52;
  TH1F* h_PU200_denom_histo_0p03 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C3D_polarHisto_dR0p03/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_cal_histo_0p03 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C3D_polarHisto_dR0p03/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i",L1pt_histo_0p03),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_histo_0p03 = new TGraphAsymmErrors();
  gr_PU200_cal_histo_0p03->Divide(h_PU200_cal_histo_0p03,h_PU200_denom_histo_0p03);
 
  int L1pt_histo_thresh_20MIPT = 48;
  TH1F* h_PU200_denom_histo_thresh_20MIPT = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto_thresh_20MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_cal_histo_thresh_20MIPT = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto_thresh_20MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.10*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.01929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i",L1pt_histo_thresh_20MIPT),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_histo_thresh_20MIPT = new TGraphAsymmErrors();
  gr_PU200_cal_histo_thresh_20MIPT->Divide(h_PU200_cal_histo_thresh_20MIPT,h_PU200_denom_histo_thresh_20MIPT);
  
  int L1pt_histo_thresh_50MIPT = 49;
  TH1F* h_PU200_denom_histo_thresh_50MIPT = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto_thresh_50MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_cal_histo_thresh_50MIPT = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto_thresh_50MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.20*(4.98004e+00 -1.25767e+00 * log(max(jets_pt[VBF_parton_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i",L1pt_histo_thresh_50MIPT),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_histo_thresh_50MIPT = new TGraphAsymmErrors();
  gr_PU200_cal_histo_thresh_50MIPT->Divide(h_PU200_cal_histo_thresh_50MIPT,h_PU200_denom_histo_thresh_50MIPT);

  vector<TGraphAsymmErrors*> turnons;
  turnons.push_back(gr_PU200_cal_dRNNC2D);
  turnons.push_back(gr_PU200_cal_histo);
  turnons.push_back(gr_PU200_cal_histo_0p03);
  turnons.push_back(gr_PU200_cal_histo_thresh_20MIPT);
  turnons.push_back(gr_PU200_cal_histo_thresh_50MIPT);

  vector<TString> leg_entry;
  leg_entry.push_back(Form("Cone dR=0.01 SingleJet%i",L1pt_dRNNC2D));
  leg_entry.push_back(Form("#splitline{Histo dR=0.01 Max. finding}{SingleJet%i}",L1pt_histo));
  leg_entry.push_back(Form("#splitline{Histo dR=0.03 Max. finding}{SingleJet%i}",L1pt_histo_0p03));
  leg_entry.push_back(Form("#splitline{Histo dR=0.01 20 MIPT-thresh.}{SingleJet%i}",L1pt_histo_thresh_20MIPT));
  leg_entry.push_back(Form("#splitline{Histo dR=0.01 50 MIPT-thresh.}{SingleJet%i}",L1pt_histo_thresh_50MIPT));

  leg_entry.push_back(Form("Histo dR=0.01 thresh. 50MIPT SingleJet%i",L1pt_histo_thresh_50MIPT));

  TLegend* leg=new TLegend(0.4,0.12,0.85,0.55);
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
  turnons[0]->GetXaxis()->SetLimits(0,150);
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
  
  TLine* line = new TLine(0,0.95,150,0.95);
  line->Draw("same");

  //TLine* line2 = new TLine(50,0.,50,1.);
  //line2->Draw("same");

  TLatex *texl = new TLatex(1.57,1.01,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV PU200");
  texl->SetTextSize(0.03);
  texl->Draw("same");
  gPad->SetTicks();


  c->SaveAs("plots/turnons_L1SingleJet_histo_PU200_lowthresh_test.pdf");  


}









void plot_profile_L1jet_response_pt_PU0_C3D_histo_raw_TC(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  TH2F* h_PU0_raw_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_raw_histo_0p03 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C3D_polarHisto_dR0p03/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_raw_histo_thresh_20MIPT = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_thresh_20MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);


  TH2F* h_PU0_raw_histo_0p03_TC = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C3D_polarHisto_dR0p03_TC/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_raw_histo_thresh_20MIPT_TC = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_thresh_20MIPT_TC/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  

  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw_dRNNC2D);
  histo.push_back(h_PU0_raw_histo_0p03);
  histo.push_back(h_PU0_raw_histo_thresh_20MIPT);
  histo.push_back(h_PU0_raw_histo_0p03_TC);
  histo.push_back(h_PU0_raw_histo_thresh_20MIPT_TC);
  
  vector<TString> leg_entry;
  leg_entry.push_back("C2D + Cone dr=0.01");
  leg_entry.push_back("C2D + Histo dr=0.03 Max. finding");
  leg_entry.push_back("C2D + Histo dr=0.01 20 MIPT-thresh.");
  leg_entry.push_back("TC + Histo dr=0.03 Max. finding");
  leg_entry.push_back("TC + Histo dr=0.01 20 MIPT-thresh.");

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
  prof[0]->GetYaxis()->SetRangeUser(-0.5,1.2);
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


  c->SaveAs("plots/profile_L1jet_response_pt_PU0_histo_raw_TC.pdf");  


}







void plot_profile_L1jet_response_pt_PU0_C3D_histo_cal_TC(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  TH2F* h_PU0_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_cal_histo_0p03 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C3D_polarHisto_dR0p03/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_cal_histo_thresh_20MIPT = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_thresh_20MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.10*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.01929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU0_cal_histo_0p03_TC = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C3D_polarHisto_dR0p03_TC/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","0.84*(5.09004e+00 -1.22767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  
  TH2F* h_PU0_cal_histo_thresh_20MIPT_TC = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_thresh_20MIPT_TC/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","0.98*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.00929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

 

  vector<TH2F*> histo;
  histo.push_back(h_PU0_cal_dRNNC2D);
  histo.push_back(h_PU0_cal_histo_0p03);
  histo.push_back(h_PU0_cal_histo_thresh_20MIPT);
  histo.push_back(h_PU0_cal_histo_0p03_TC);
  histo.push_back(h_PU0_cal_histo_thresh_20MIPT_TC);

  
  vector<TString> leg_entry;
  leg_entry.push_back("C2D + Cone dr=0.01");
  leg_entry.push_back("C2D + Histo dr=0.03 Max. finding");
  leg_entry.push_back("C2D + Histo dr=0.01 20 MIPT-thresh.");
  leg_entry.push_back("TC + Histo dr=0.03 Max. finding");
  leg_entry.push_back("TC + Histo dr=0.01 20 MIPT-thresh.");

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
  prof[0]->GetYaxis()->SetRangeUser(-0.5,1.2);
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


  c->SaveAs("plots/profile_L1jet_response_pt_PU0_histo_cal_TC.pdf");  


}








void plot_profile_L1jet_response_pt_PU200_C3D_histo_raw_TC(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  TH2F* h_PU200_raw_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU200_raw_histo_0p03 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C3D_polarHisto_dR0p03/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU200_raw_histo_thresh_20MIPT = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto_thresh_20MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU200_raw_histo_0p03_TC = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C3D_polarHisto_dR0p03_TC/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);

  TH2F* h_PU200_raw_histo_thresh_20MIPT_TC = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto_thresh_20MIPT_TC/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);


  vector<TH2F*> histo;
  histo.push_back(h_PU200_raw_dRNNC2D);
  histo.push_back(h_PU200_raw_histo_0p03);
  histo.push_back(h_PU200_raw_histo_thresh_20MIPT);
  histo.push_back(h_PU200_raw_histo_0p03_TC);
  histo.push_back(h_PU200_raw_histo_thresh_20MIPT_TC);

  vector<TString> leg_entry;
  leg_entry.push_back("C2D + Cone dr=0.01");
  leg_entry.push_back("C2D + Histo dr=0.03 Max. finding");
  leg_entry.push_back("C2D + Histo dr=0.01 20 MIPT-thresh.");
  leg_entry.push_back("TC + Histo dr=0.03 Max. finding");
  leg_entry.push_back("TC + Histo dr=0.01 20 MIPT-thresh."); 


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
  prof[0]->GetYaxis()->SetRangeUser(-0.6,1.2);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(2.,1.21,"CMS Simulation Preliminary, VBF H#rightarrowinv. PU=200 #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(0,1,500,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_response_pt_PU200_raw_histo_TC.pdf");  


}











void plot_profile_L1jet_response_pt_PU200_C3D_histo_cal_TC(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  // TH2F* h_PU200_cal_dRNNC2D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);
  // std::cout << __LINE__ << std::endl;
  // TH2F* h_PU200_cal_histo_0p03 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C3D_polarHisto_dR0p03/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);
  // std::cout << __LINE__ << std::endl;
  TH2F* h_PU200_cal_histo_thresh_20MIPT = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto_thresh_20MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.10*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.01929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);
  //  qwert
  std::cout << __LINE__ << std::endl;
  TH2F* h_PU200_cal_histo_thresh_20MIPT_nosmear = single_plot2D("/vols/cms/snwebb/HGC_ntuples/VBF_Hinv_PU200_C3D_polarHisto_nosmear_thresh_20MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.10*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.01929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);


  TH2F* h_PU200_cal_histo_0p03_TC = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C3D_polarHisto_dR0p03_TC/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","0.84*(5.09004e+00 -1.22767e+00 * log(max(jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * (jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);

  TH2F* h_PU200_cal_histo_0p03_nosmear_TC = single_plot2D("/vols/cms/snwebb/HGC_ntuples/VBF_Hinv_PU200_C3D_polarHisto_nosmear_Max_dR0p03_TC/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","0.84*(5.09004e+00 -1.22767e+00 * log(max(jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * (jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);
  
  // TH2F* h_PU200_cal_histo_thresh_20MIPT_TC = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto_thresh_20MIPT_TC/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","0.98*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.00929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * (jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);

  vector<TH2F*> histo;
  //  histo.push_back(h_PU200_cal_dRNNC2D);
  //  histo.push_back(h_PU200_cal_histo_0p03);


  histo.push_back(h_PU200_cal_histo_thresh_20MIPT);  //normal
  histo.push_back(h_PU200_cal_histo_0p03_TC);//normal


  histo.push_back(h_PU200_cal_histo_thresh_20MIPT_nosmear);  
  histo.push_back(h_PU200_cal_histo_0p03_nosmear_TC);


  //  histo.push_back(h_PU200_cal_histo_thresh_20MIPT_TC);  
  
  vector<TString> leg_entry;
  //  leg_entry.push_back("C2D + Cone dr=0.01");
  //  leg_entry.push_back("C2D + Histo dr=0.03 Max. finding");
  leg_entry.push_back("C2D + Histo dr=0.01 20 MIPT-thresh.");//norm
  leg_entry.push_back("TC + Histo dr=0.03 Max. finding");//norm

  //leg_entry.push_back("TC + Histo dr=0.01 20 MIPT-thresh."); 

  leg_entry.push_back("C2D + Histo dr=0.01 20 MIPT-thresh. no-smear");
  leg_entry.push_back("TC + Histo dr=0.03 Max. finding no-smear");


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
  prof[0]->GetYaxis()->SetRangeUser(-0.5,1.2);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(2.,1.21,"CMS Simulation Preliminary, VBF H#rightarrowinv. PU=200 #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(0,1,500,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_response_pt_PU200_histo_cal_TC.pdf");  


}








void plot_turnons_L1SingleJet_histo_PU200_TC(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  double x[18]={0,40,60,70,80,90,100,110,120,130,140,160,180,200,250,300,400,500};
  int nbins=17;

  //double x[15]={0,25,35,40,45,50,55,60,65,75,80,90,100,120,150};
  //int nbins=14;

  int L1pt_dRNNC2D = 100;
  TH1F* h_PU200_denom_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_cal_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i",L1pt_dRNNC2D),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D->Divide(h_PU200_cal_dRNNC2D,h_PU200_denom_dRNNC2D);


  int L1pt_histo_0p03 = 98;
  TH1F* h_PU200_denom_histo_0p03 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C3D_polarHisto_dR0p03/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_cal_histo_0p03 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C3D_polarHisto_dR0p03/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i",L1pt_histo_0p03),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_histo_0p03 = new TGraphAsymmErrors();
  gr_PU200_cal_histo_0p03->Divide(h_PU200_cal_histo_0p03,h_PU200_denom_histo_0p03);
 
  int L1pt_histo_thresh_20MIPT = 95;
  TH1F* h_PU200_denom_histo_thresh_20MIPT = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto_thresh_20MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_cal_histo_thresh_20MIPT = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto_thresh_20MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.10*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.01929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i",L1pt_histo_thresh_20MIPT),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_histo_thresh_20MIPT = new TGraphAsymmErrors();
  gr_PU200_cal_histo_thresh_20MIPT->Divide(h_PU200_cal_histo_thresh_20MIPT,h_PU200_denom_histo_thresh_20MIPT);


  int L1pt_histo_0p03_TC = 97;
  TH1F* h_PU200_denom_histo_0p03_TC = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C3D_polarHisto_dR0p03_TC/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_cal_histo_0p03_TC = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C3D_polarHisto_dR0p03_TC/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& 0.84*(5.09004e+00 -1.22767e+00 * log(max(jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0) >%i",L1pt_histo_0p03_TC),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_histo_0p03_TC = new TGraphAsymmErrors();
  gr_PU200_cal_histo_0p03_TC->Divide(h_PU200_cal_histo_0p03_TC,h_PU200_denom_histo_0p03_TC);
 
  int L1pt_histo_thresh_20MIPT_TC = 97;
  TH1F* h_PU200_denom_histo_thresh_20MIPT_TC = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto_thresh_20MIPT_TC/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_cal_histo_thresh_20MIPT_TC = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto_thresh_20MIPT_TC/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& 0.98*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.00929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0) >%i",L1pt_histo_thresh_20MIPT_TC),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_histo_thresh_20MIPT_TC = new TGraphAsymmErrors();
  gr_PU200_cal_histo_thresh_20MIPT_TC->Divide(h_PU200_cal_histo_thresh_20MIPT_TC,h_PU200_denom_histo_thresh_20MIPT_TC);
  
  

  vector<TGraphAsymmErrors*> turnons;
  turnons.push_back(gr_PU200_cal_dRNNC2D);
  turnons.push_back(gr_PU200_cal_histo_0p03);
  turnons.push_back(gr_PU200_cal_histo_thresh_20MIPT);
  turnons.push_back(gr_PU200_cal_histo_0p03_TC);
  turnons.push_back(gr_PU200_cal_histo_thresh_20MIPT_TC);

  vector<TString> leg_entry;
  leg_entry.push_back(Form("#splitline{C2D + Cone dR=0.01}{SingleJet%i}",L1pt_dRNNC2D));
  leg_entry.push_back(Form("#splitline{C2D + Histo dR=0.03}{ Max. finding SingleJet%i}",L1pt_histo_0p03));
  leg_entry.push_back(Form("#splitline{C2D + Histo dR=0.01}{20 MIPT-thresh. SingleJet%i}",L1pt_histo_thresh_20MIPT));
  leg_entry.push_back(Form("#splitline{TC + Histo dR=0.03}{Max. finding SingleJet%i}",L1pt_histo_0p03_TC));
  leg_entry.push_back(Form("#splitline{TC + Histo dR=0.01}{20 MIPT-thresh. SingleJet%i}",L1pt_histo_thresh_20MIPT_TC));

  TLegend* leg=new TLegend(0.4,0.12,0.85,0.6);
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


  c->SaveAs("plots/turnons_L1SingleJet_histo_PU200_TC.pdf");  


}









void plot_turnons_L1SingleJet_histo_PU200_lowthresh_TC(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  double x[16]={0,25,35,40,45,50,55,60,65,70,75,80,90,100,120,150};
  int nbins=15;


  int L1pt_dRNNC2D = 50;
  TH1F* h_PU200_denom_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_cal_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i",L1pt_dRNNC2D),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D->Divide(h_PU200_cal_dRNNC2D,h_PU200_denom_dRNNC2D);

  int L1pt_histo_0p03 = 50;
  //int L1pt_histo_0p03 = 52;
  TH1F* h_PU200_denom_histo_0p03 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C3D_polarHisto_dR0p03/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_cal_histo_0p03 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C3D_polarHisto_dR0p03/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i",L1pt_histo_0p03),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_histo_0p03 = new TGraphAsymmErrors();
  gr_PU200_cal_histo_0p03->Divide(h_PU200_cal_histo_0p03,h_PU200_denom_histo_0p03);
 
  int L1pt_histo_thresh_20MIPT = 50;
  //int L1pt_histo_thresh_20MIPT = 48;
  TH1F* h_PU200_denom_histo_thresh_20MIPT = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto_thresh_20MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_cal_histo_thresh_20MIPT = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto_thresh_20MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.10*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.01929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i",L1pt_histo_thresh_20MIPT),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_histo_thresh_20MIPT = new TGraphAsymmErrors();
  gr_PU200_cal_histo_thresh_20MIPT->Divide(h_PU200_cal_histo_thresh_20MIPT,h_PU200_denom_histo_thresh_20MIPT);

  int L1pt_histo_0p03_TC = 50;
  //int L1pt_histo_0p03_TC = 51;
  TH1F* h_PU200_denom_histo_0p03_TC = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C3D_polarHisto_dR0p03_TC/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_cal_histo_0p03_TC = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C3D_polarHisto_dR0p03_TC/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& 0.84*(5.09004e+00 -1.22767e+00 * log(max(jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0) >%i",L1pt_histo_0p03_TC),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_histo_0p03_TC = new TGraphAsymmErrors();
  gr_PU200_cal_histo_0p03_TC->Divide(h_PU200_cal_histo_0p03_TC,h_PU200_denom_histo_0p03_TC);
 
  int L1pt_histo_thresh_20MIPT_TC = 50;
  //int L1pt_histo_thresh_20MIPT_TC = 47;
  TH1F* h_PU200_denom_histo_thresh_20MIPT_TC = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto_thresh_20MIPT_TC/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_cal_histo_thresh_20MIPT_TC = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto_thresh_20MIPT_TC/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& 0.98*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.00929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0) >%i",L1pt_histo_thresh_20MIPT_TC),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_histo_thresh_20MIPT_TC = new TGraphAsymmErrors();
  gr_PU200_cal_histo_thresh_20MIPT_TC->Divide(h_PU200_cal_histo_thresh_20MIPT_TC,h_PU200_denom_histo_thresh_20MIPT_TC);
  
  

  vector<TGraphAsymmErrors*> turnons;
  turnons.push_back(gr_PU200_cal_dRNNC2D);
  turnons.push_back(gr_PU200_cal_histo_0p03);
  turnons.push_back(gr_PU200_cal_histo_thresh_20MIPT);
  turnons.push_back(gr_PU200_cal_histo_0p03_TC);
  turnons.push_back(gr_PU200_cal_histo_thresh_20MIPT_TC);

  vector<TString> leg_entry;
  leg_entry.push_back(Form("#splitline{C2D + Cone dR=0.01}{SingleJet%i}",L1pt_dRNNC2D));
  leg_entry.push_back(Form("#splitline{C2D + Histo dR=0.03}{ Max. finding SingleJet%i}",L1pt_histo_0p03));
  leg_entry.push_back(Form("#splitline{C2D + Histo dR=0.01}{20 MIPT-thresh. SingleJet%i}",L1pt_histo_thresh_20MIPT));
  leg_entry.push_back(Form("#splitline{TC + Histo dR=0.03}{Max. finding SingleJet%i}",L1pt_histo_0p03_TC));
  leg_entry.push_back(Form("#splitline{TC + Histo dR=0.01}{20 MIPT-thresh. SingleJet%i}",L1pt_histo_thresh_20MIPT_TC));

  TLegend* leg=new TLegend(0.45,0.12,0.85,0.6);
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


  c->SaveAs("plots/turnons_L1SingleJet_histo_PU200_lowthresh_TC.pdf");  


}






