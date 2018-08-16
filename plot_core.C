#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TH2F.h>
#include <THStack.h>
#include <iostream>
#include <TLegend.h>
#include <TLatex.h>
#include <TProfile.h>
#include <TProfile2D.h>
#include <TStyle.h>
#include <TLine.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TF2.h>
#include <TGraphAsymmErrors.h>
#include "Helpers.C"
#include <vector>

using namespace std;


void plot_ratio_core(){

  TH1F* h_VBF_PU0 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_core_*.root","jets","jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets]","VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20 && jets_raw_Luca_pt[VBF_parton_jets]>50",100,0,1);
  TH1F* h_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_core_*.root","jets","jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets]","VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20 && jets_raw_Luca_pt[VBF_parton_jets]>50",100,0,1);

  TH1F* h_ZB_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_core_*.root","jets","jets_0p1_core_ok_pt/jets_raw_Luca_pt","jets_raw_Luca_pt>50",100,0,1);
  
  TH1F* h_VBF_PU200_PUS = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_core_*.root","jets","jets_0p1_core_ok_pt[VBF_parton_jets]/max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],1e-3)","VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20 && jets_raw_Luca_pt[VBF_parton_jets]>50",100,0,1);
  TH1F* h_ZB_PU200_PUS = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_core_*.root","jets","jets_0p1_core_ok_pt/max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_C3D,1e-3)","jets_raw_Luca_pt>50",100,0,1);
  /*cout<<"VBF PU200 PUS"<<endl;
  cout<<h_VBF_PU200_PUS->Integral()/h_VBF_PU200->Integral()<<endl;
  cout<<"ZB PU200 PUS"<<endl;
  cout<<h_ZB_PU200_PUS->Integral()/h_ZB_PU200->Integral()<<endl;


  h_VBF_PU200_PUS->Scale(1/h_VBF_PU200->Integral());
  h_ZB_PU200_PUS->Scale(1/h_ZB_PU200->Integral());
  h_VBF_PU0->Scale(1/h_VBF_PU0->Integral());
  h_VBF_PU200->Scale(1/h_VBF_PU200->Integral());
  h_ZB_PU200->Scale(1/h_ZB_PU200->Integral());*/

  vector<TH1F*> histo;
  histo.push_back(h_VBF_PU0);
  histo.push_back(h_VBF_PU200);
  histo.push_back(h_VBF_PU200_PUS);
  histo.push_back(h_ZB_PU200);
  histo.push_back(h_ZB_PU200_PUS);

  vector<TString> leg_entry;
  leg_entry.push_back("VBF PU=0");
  leg_entry.push_back("VBF PU=200");
  leg_entry.push_back("VBF PU=200 PUS");
  leg_entry.push_back("ZB PU=200");
  leg_entry.push_back("ZB PU=200 PUS");
  
  TLegend* leg=new TLegend(0.2,0.6,0.5,0.85);
  leg->SetHeader("Raw p_{T}(L1 jet)>50 GeV");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  for(unsigned int i=0; i<histo.size();i++){
    histo[i]->Scale(1/histo[i]->Integral());
    cout<<leg_entry[i]<<endl;
    cout<<histo[i]->Integral(0,50)<<endl;
    histo[i]->SetLineColor(i+1);
    if(i>3)
      histo[i]->SetLineColor(i+2);
    histo[i]->SetLineWidth(2); 
    leg->AddEntry(histo[i],leg_entry[i]);
  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  c->SetLogy();

  histo[0]->GetXaxis()->SetTitle("p_{T}(core)/p_{T}(L1 jet)");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.5);
  histo[0]->GetXaxis()->SetTitleOffset(1.2);
  histo[0]->GetYaxis()->SetRangeUser(4e-4,5e-1);
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,6e-1,"CMS Simulation #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/ratio_core_L1jet.pdf");  

  /*for(unsigned int i=0;i<histo.size();i++)
    delete histo[i];*/

  return;

}






void plot_ratio_core_pt100(){

  TH1F* h_VBF_PU0 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_core_*.root","jets","jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets]","VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20 && jets_raw_Luca_pt[VBF_parton_jets]>100",100,0,1);
  TH1F* h_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_core_*.root","jets","jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets]","VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20 && jets_raw_Luca_pt[VBF_parton_jets]>100",100,0,1);

  //TH1F* h_ZB_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_core_*.root","jets","jets_0p1_core_ok_pt/jets_raw_Luca_pt","jets_raw_Luca_pt>100",100,0,1);
  
  TH1F* h_VBF_PU200_PUS = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_core_*.root","jets","jets_0p1_core_ok_pt[VBF_parton_jets]/max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],1e-3)","VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20 && jets_raw_Luca_pt[VBF_parton_jets]>100",100,0,1);
  //TH1F* h_ZB_PU200_PUS = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_core_*.root","jets","jets_0p1_core_ok_pt/max(jets_raw_Luca_pt-2*jets_PU_subtr_cone_C3D,1e-3)","jets_raw_Luca_pt>100",100,0,1);

  /*h_VBF_PU200_PUS->Scale(1/h_VBF_PU200->Integral());
  h_ZB_PU200_PUS->Scale(1/h_ZB_PU200->Integral());
  h_VBF_PU0->Scale(1/h_VBF_PU0->Integral());
  h_VBF_PU200->Scale(1/h_VBF_PU200->Integral());
  h_ZB_PU200->Scale(1/h_ZB_PU200->Integral());*/

  vector<TH1F*> histo;
  histo.push_back(h_VBF_PU0);
  histo.push_back(h_VBF_PU200);
  histo.push_back(h_VBF_PU200_PUS);
  //histo.push_back(h_ZB_PU200);
  //histo.push_back(h_ZB_PU200_PUS);

  vector<TString> leg_entry;
  leg_entry.push_back("VBF PU=0");
  leg_entry.push_back("VBF PU=200");
  leg_entry.push_back("VBF PU=200 PUS");
  leg_entry.push_back("ZB PU=200");
  leg_entry.push_back("ZB PU=200 PUS");
  
  TLegend* leg=new TLegend(0.2,0.6,0.5,0.85);
  leg->SetHeader("Raw p_{T}(L1 jet)>100 GeV");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  for(unsigned int i=0; i<histo.size();i++){
    histo[i]->Scale(1/histo[i]->Integral());
    cout<<leg_entry[i]<<endl;
    cout<<histo[i]->Integral(0,50)<<endl;
    histo[i]->SetLineColor(i+1);
    if(i>3)
      histo[i]->SetLineColor(i+2);
    histo[i]->SetLineWidth(2); 
    leg->AddEntry(histo[i],leg_entry[i]);
  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  c->SetLogy();

  histo[0]->GetXaxis()->SetTitle("p_{T}(core)/p_{T}(L1 jet)");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.5);
  histo[0]->GetXaxis()->SetTitleOffset(1.2);
  histo[0]->GetYaxis()->SetRangeUser(4e-4,5e-1);
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,6e-1,"CMS Simulation #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/ratio_core_L1jet_pt100.pdf");  

  /*for(unsigned int i=0;i<histo.size();i++)
    delete histo[i];*/

  return;

}







void plot_ratio_pt_2D(){

  TH2F* histo = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_core_*.root","jets","jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets]","jets_raw_Luca_pt[VBF_parton_jets]","VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20",100,0,1,100,0,500);
  histo->Scale(1/histo->Integral());

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  c->SetLogz();

  histo->GetXaxis()->SetTitle("p_{T}(core)/p_{T}(L1 jet)");
  histo->GetYaxis()->SetTitle("p_{T}(L1 jet) [GeV]");
  histo->GetYaxis()->SetTitleOffset(1.5);
  histo->GetXaxis()->SetTitleOffset(1.2);
  //histo->GetZaxis()->SetRangeUser(4e-4,5e-1);
  histo->SetStats(0);
  histo->SetTitle("");
  histo->Draw("colz");


  TLatex *texl = new TLatex(0.01,502,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV PU=0");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/ratio_core_L1jet_pt_2D.pdf");  

  /*for(unsigned int i=0;i<histo.size();i++)
    delete histo[i];*/

  return;

}







void plot_turnons_L1SingleJet_core_cut(int L1pt){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  double x[17]={0,50,80,100,120,130,140,150,160,170,180,200,220,260,300,400,500};

  TH1F* h_PU0_denom = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]",cut,16,x);
  TH1F* h_PU0_raw = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]",cut+Form(" && jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets]>0.5&& jets_raw_Luca_pt[VBF_parton_jets]>%i",L1pt),16,x);
  TGraphAsymmErrors* gr_PU0_raw = new TGraphAsymmErrors();
  gr_PU0_raw->Divide(h_PU0_raw,h_PU0_denom);
  TH1F* h_PU0_cal = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]",cut+Form("&& jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets]>0.5 && (4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]>%i",L1pt),16,x);
  TGraphAsymmErrors* gr_PU0_cal = new TGraphAsymmErrors();
  gr_PU0_cal->Divide(h_PU0_cal,h_PU0_denom);

  TH1F* h_PU200_denom = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]",cut,16,x);
  TH1F* h_PU200_raw = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]",cut+Form("&& jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets]>0.5 && jets_raw_Luca_pt[VBF_parton_jets]>%i",L1pt),16,x);
  TGraphAsymmErrors* gr_PU200_raw = new TGraphAsymmErrors();
  gr_PU200_raw->Divide(h_PU200_raw,h_PU200_denom);
  TH1F* h_PU200_PUS = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]",cut+Form("&& jets_0p1_core_ok_pt[VBF_parton_jets]/max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],1e-3)>0.5 && max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)>%i",L1pt),16,x);
  TGraphAsymmErrors* gr_PU200_PUS = new TGraphAsymmErrors();
  gr_PU200_PUS->Divide(h_PU200_PUS,h_PU200_denom);
  TH1F* h_PU200_PUS_cal = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]",cut+Form("&& jets_0p1_core_ok_pt[VBF_parton_jets]/max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],1e-3)>0.5 && (4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)),2) ) * max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)>%i",L1pt),16,x);
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


  c->SaveAs(Form("plots/turnons_L1SingleJet%i_core.pdf",L1pt));  


}







void plot_profile_L1jet_response_core_ratio_PU200_pt0(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";


  TH2F* h_PU0_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,1,97,0.06,2);
  TH2F* h_PU0_cal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets]","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,1,97,0.06,2);

  TH2F* h_PU200_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,1,97,0.06,2);
  TH2F* h_PU200_PUS_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","jets_0p1_core_ok_pt[VBF_parton_jets]/max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],1e-3)","max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets])>0",25,0,1,97,0.06,2);
  TH2F* h_PU200_PUS_cal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","jets_0p1_core_ok_pt[VBF_parton_jets]/max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],1e-3)","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)),2) ) * max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets])>0",25,0,1,97,0.06,2);

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

  prof[0]->GetXaxis()->SetTitle("Core p_{T}(L1)/p_{T}(L1)");
  prof[0]->GetYaxis()->SetTitle("p_{T}(L1)/p_{T}(gen. jet)");
  prof[0]->GetYaxis()->SetTitleOffset(1.7);
  prof[0]->GetYaxis()->SetRangeUser(0,1.2);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.21,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(0,1,1,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_response_core_ratio_PU200_pT0.pdf");  


}



void plot_2D_L1jet_response_core_ratio_PU0_core_cal(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";


  TH2F* histo = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,1,97,0.06,2);  
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  histo->GetXaxis()->SetTitle("Core p_{T}(L1)/p_{T}(L1)");
  histo->GetYaxis()->SetTitle("p_{T}(L1)/p_{T}(gen. jet)");
  histo->GetYaxis()->SetTitleOffset(1.7);
  histo->GetYaxis()->SetRangeUser(0,2.);
  histo->SetStats(0);
  histo->SetTitle("");
  histo->Draw("colz");


  TProfile* p = (TProfile*)histo->ProfileX()->Clone();
  p->BuildOptions(0,0,"s");
  p->SetLineColor(kRed);
  p->SetLineWidth(2);
  p->Draw("same");

  TF1* f = new TF1("f","([0] + [1]/([2] - x))",0,1);
  f->SetParameter(0,2.757e-01);
  f->SetParameter(1,6.198e-02);
  f->SetParameter(2,1.145);
  p->Fit(f);

  TLatex *texl = new TLatex(0.01,2.01,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV PU=0");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/2D_L1jet_response_core_ratio_PU0_core_cal.pdf");  


}






void plot_3D_L1jet_response_pT_core_ratio_PU0_core_cal(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";


  TH3F* histo = single_plot3D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","jets_raw_Luca_pt[VBF_parton_jets]","jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,25,0,1,97,0.06,2);  
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  TProfile2D* p = (TProfile2D*)histo->Project3DProfile()->Clone();
  p->GetXaxis()->SetTitle("p_{T}(L1) [GeV]");
  p->GetYaxis()->SetTitle("Core p_{T}(L1)/p_{T}(L1)");
  p->GetYaxis()->SetTitleOffset(1.7);
  p->GetZaxis()->SetTitle("p_{T}(L1)/p_{T}(gen. jet)");
  p->GetZaxis()->SetTitleOffset(1.2);
  p->SetTitle("");
  p->SetStats(0);
  p->Draw("colz");

  TF2* f = new TF2("f","([0] + [1]/([2] - x))*(1/([3]+[4]*log(y)+[5]*pow(log(y),2)))",0,1,0,500);
  f->SetParameter(0,2.757e-01);
  f->SetParameter(1,6.198e-02);
  f->SetParameter(2,1.145);
  f->SetParameter(3,4.4374);
  f->SetParameter(4,-0.948102);
  f->SetParameter(5,.0686934);
  p->Fit(f);


  TLatex *texl = new TLatex(0.01,502,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV PU=0");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/3D_L1jet_response_pt_core_ratio_PU0_core_cal.pdf");  


}










void plot_profile_L1jet_response_core_ratio_PU0_core_cal(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";


  TH2F* h_PU0_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,1,97,0.06,2);
  TH2F* h_PU0_ptcal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets]","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,1,97,0.06,2);
  TH2F* h_PU0_corecal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets]","1/(2.757e-01 + 6.198e-02/(1.145 - jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets])) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,1,97,0.06,2);
  TH2F* h_PU0_coreptcal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets]","1/(6.24495e-01 + 7.77704e-02/(1.30993e+00 - jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets])) * ( 4.36986e+00 -1.14779e+00 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + 9.89410e-02* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,1,97,0.06,2); 
  TH2F* h_PU0_coreptcal_pTfirst = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets]","1/(5.96346e-01 + 1.36914e-01/(1.25776e+00 - jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets])) * (4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,1,97,0.06,2); 
  TH2F* h_PU0_coreptcal_corefirst = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets]","1/(2.757e-01 + 6.198e-02/(1.145 - jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets])) * 1/(-3.81093e-01 + 5.25168e-01 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) -3.92350e-02* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,1,97,0.06,2); 
  


  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw);
  histo.push_back(h_PU0_ptcal);
  histo.push_back(h_PU0_corecal);
  histo.push_back(h_PU0_coreptcal);
  histo.push_back(h_PU0_coreptcal_pTfirst);
  histo.push_back(h_PU0_coreptcal_corefirst);
  

  
  vector<TString> leg_entry;
  leg_entry.push_back("No calibr.");
  leg_entry.push_back("Jet calibr. vs p_{T}");
  leg_entry.push_back("Jet calibr. vs core ratio");
  leg_entry.push_back("2D jet calibr. simult.");
  leg_entry.push_back("2D jet calibr. p_{T} + core ratio");
  leg_entry.push_back("2D jet calibr. core ratio + p_{T}");

  TLegend* leg=new TLegend(0.4,0.5,0.7,0.85);
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

  prof[0]->GetXaxis()->SetTitle("Core p_{T}(L1)/p_{T}(L1)");
  prof[0]->GetYaxis()->SetTitle("p_{T}(L1)/p_{T}(gen. jet)");
  prof[0]->GetYaxis()->SetTitleOffset(1.7);
  prof[0]->GetYaxis()->SetRangeUser(0,2.5);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,2.51,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(0,1,1,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_response_core_ratio_PU0_core_cal.pdf");  


}









void plot_profile_L1jet_response_pT_PU0_core_cal(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";


  TH2F* h_PU0_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  TH2F* h_PU0_ptcal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  TH2F* h_PU0_corecal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","1/(2.757e-01 + 6.198e-02/(1.145 - jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets])) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  TH2F* h_PU0_coreptcal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","1/(6.24495e-01 + 7.77704e-02/(1.30993e+00 - jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets])) * ( 4.36986e+00 -1.14779e+00 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + 9.89410e-02* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  TH2F* h_PU0_coreptcal_pTfirst = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","1/(5.96346e-01 + 1.36914e-01/(1.25776e+00 - jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets])) * (4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2); 
  TH2F* h_PU0_coreptcal_corefirst = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","1/(2.757e-01 + 6.198e-02/(1.145 - jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets])) * 1/(-3.81093e-01 + 5.25168e-01 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) -3.92350e-02* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2); 

 

  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw);
  histo.push_back(h_PU0_ptcal);
  histo.push_back(h_PU0_corecal);
  histo.push_back(h_PU0_coreptcal);
  histo.push_back(h_PU0_coreptcal_pTfirst);
  histo.push_back(h_PU0_coreptcal_corefirst);
  
  vector<TString> leg_entry;
  leg_entry.push_back("No calibr.");
  leg_entry.push_back("Jet calibr. vs p_{T}");
  leg_entry.push_back("Jet calibr. vs core ratio");
  leg_entry.push_back("2D jet calibr. simult.");
  leg_entry.push_back("2D jet calibr. p_{T} + core ratio");
  leg_entry.push_back("2D jet calibr. core ratio + p_{T}");

  TLegend* leg=new TLegend(0.2,0.5,0.5,0.85);
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

  prof[0]->GetXaxis()->SetTitle("p_{T}(gen. jet)");
  prof[0]->GetYaxis()->SetTitle("p_{T}(L1)/p_{T}(gen. jet)");
  prof[0]->GetYaxis()->SetTitleOffset(1.7);
  prof[0]->GetYaxis()->SetRangeUser(0,2.6);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(2,2.61,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(0,1,500,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_response_pt_PU0_core_cal.pdf");  


}









void plot_profile_L1jet_resolution_core_ratio_PU0_core_cal(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";


  TH2F* h_PU0_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,1,97,0.06,2);
  TH2F* h_PU0_ptcal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets]","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,1,97,0.06,2);
  TH2F* h_PU0_corecal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets]","1/(2.757e-01 + 6.198e-02/(1.145 - jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets])) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,1,97,0.06,2);
  TH2F* h_PU0_coreptcal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets]","1/(6.24495e-01 + 7.77704e-02/(1.30993e+00 - jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets])) * ( 4.36986e+00 -1.14779e+00 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + 9.89410e-02* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,1,97,0.06,2); 
  TH2F* h_PU0_coreptcal_pTfirst = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets]","1/(5.96346e-01 + 1.36914e-01/(1.25776e+00 - jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets])) * (4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,1,97,0.06,2); 
  TH2F* h_PU0_coreptcal_corefirst = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets]","1/(2.757e-01 + 6.198e-02/(1.145 - jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets])) * 1/(-3.81093e-01 + 5.25168e-01 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) -3.92350e-02* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,1,97,0.06,2); 
  


  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw);
  histo.push_back(h_PU0_ptcal);
  histo.push_back(h_PU0_corecal);
  histo.push_back(h_PU0_coreptcal);
  histo.push_back(h_PU0_coreptcal_pTfirst);
  histo.push_back(h_PU0_coreptcal_corefirst);
  

  
  vector<TString> leg_entry;
  leg_entry.push_back("No calibr.");
  leg_entry.push_back("Jet calibr. vs p_{T}");
  leg_entry.push_back("Jet calibr. vs core ratio");
  leg_entry.push_back("2D jet calibr. simult.");
  leg_entry.push_back("2D jet calibr. p_{T} + core ratio");
  leg_entry.push_back("2D jet calibr. core ratio + p_{T}");

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
      cout<<"yq="<<yq[0]<<","<<yq[1]<<","<<yq[2]<<","<<yq[3]<<endl;
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

  graph[0]->GetXaxis()->SetTitle("Core p_{T}(L1)/p_{T}(L1)");
  graph[0]->GetYaxis()->SetTitle("RMS(p_{T}(L1)/p_{T}(gen. jet)) / <p_{T}(L1)/p_{T}(gen. jet)>");
  graph[0]->GetYaxis()->SetTitleOffset(1.7);
  graph[0]->GetYaxis()->SetRangeUser(0,2.);
  graph[0]->SetTitle("");
  graph[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    graph[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,2.01,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV PU=0");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_resolution_core_ratio_PU0_core_cal.pdf");  


}









void plot_profile_L1jet_resolution_pT_PU0_core_cal(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";


  TH2F* h_PU0_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  TH2F* h_PU0_ptcal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  TH2F* h_PU0_corecal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","1/(2.757e-01 + 6.198e-02/(1.145 - jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets])) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  TH2F* h_PU0_coreptcal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","1/(6.24495e-01 + 7.77704e-02/(1.30993e+00 - jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets])) * ( 4.36986e+00 -1.14779e+00 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + 9.89410e-02* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  TH2F* h_PU0_coreptcal_pTfirst = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","1/(5.96346e-01 + 1.36914e-01/(1.25776e+00 - jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets])) * (4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2); 
  TH2F* h_PU0_coreptcal_corefirst = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","1/(2.757e-01 + 6.198e-02/(1.145 - jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets])) * 1/(-3.81093e-01 + 5.25168e-01 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) -3.92350e-02* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2); 

 

  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw);
  histo.push_back(h_PU0_ptcal);
  histo.push_back(h_PU0_corecal);
  histo.push_back(h_PU0_coreptcal);
  histo.push_back(h_PU0_coreptcal_pTfirst);
  histo.push_back(h_PU0_coreptcal_corefirst);
  
  vector<TString> leg_entry;
  leg_entry.push_back("No calibr.");
  leg_entry.push_back("Jet calibr. vs p_{T}");
  leg_entry.push_back("Jet calibr. vs core ratio");
  leg_entry.push_back("2D jet calibr. simult.");
  leg_entry.push_back("2D jet calibr. p_{T} + core ratio");
  leg_entry.push_back("2D jet calibr. core ratio + p_{T}");

  TLegend* leg=new TLegend(0.4,0.5,0.7,0.85);
  leg->SetHeader("#splitline{p_T(gen. jet)>20 GeV}{1.6<|#eta(gen.jet)|<2.9}");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  
  vector<TGraphErrors*> graph;

  for(unsigned int i=0;i<histo.size();i++){

    TGraphErrors* gr = new TGraphErrors(histo[i]->GetNbinsX());


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
      Double_t xq[4] = {0.25,0.5,0.75,1};
      Double_t yq[4];
      proj->GetQuantiles(4,yq,xq);
      gr->SetPoint(j-1,histo[i]->GetXaxis()->GetBinCenter(j),(yq[2]-yq[0])/yq[1]);
      //gr->SetPoint(j-1,proj->GetBinCenter(j),(yq[2]-yq[0]));
      cout<<(yq[2]-yq[0])<<endl;
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

  graph[0]->GetXaxis()->SetTitle("p_{T}(gen. jet)");
  graph[0]->GetYaxis()->SetTitle("RMS(p_{T}(L1)/p_{T}(gen. jet)) / <p_{T}(L1)/p_{T}(gen. jet)>");
  graph[0]->GetYaxis()->SetTitleOffset(1.7);
  graph[0]->GetYaxis()->SetRangeUser(0,1.);
  graph[0]->SetTitle("");
  graph[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    graph[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(2,1.01,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV PU=0");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_resolution_pt_PU0_core_cal.pdf");  


}












void plot_profile_L1jet_response_core_ratio_PU200_core_cal(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  TH2F* h_PU0_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,1,97,0.06,2);
  TH2F* h_PU0_ptcal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets]","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,1,97,0.06,2);
  TH2F* h_PU0_coreptcal_pTfirst = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets]","1/(5.96346e-01 + 1.36914e-01/(1.25776e+00 - jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets])) * (4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,1,97,0.06,2); 

  TH2F* h_PU200_raw_PUS = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets]","max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)>0",25,0,1,97,0.06,2);
  
  TH2F* h_PU200_ptcal_PUS = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets]","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)),2) ) * max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)>0",25,0,1,97,0.06,2);
    TH2F* h_PU200_coreptcal_pTfirst_PUS = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets]","1/(5.96346e-01 + 1.36914e-01/(1.25776e+00 - jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets])) * (4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)),2) ) * max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)>0",25,0,1,97,0.06,2); 


  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw);
  histo.push_back(h_PU0_ptcal);
  histo.push_back(h_PU0_coreptcal_pTfirst);
  histo.push_back(h_PU200_raw_PUS);
  histo.push_back(h_PU200_ptcal_PUS);
  histo.push_back(h_PU200_coreptcal_pTfirst_PUS);
  

  
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 No calibr.");
  leg_entry.push_back("PU=0 Jet calibr. vs p_{T}");
  leg_entry.push_back("PU=0 2D jet calibr.");
  leg_entry.push_back("PU=200 + PUS");
  leg_entry.push_back("PU=200 + PUS +Jet calibr. vs p_{T}");
  leg_entry.push_back("PU=200 + PUS + 2D jet calibr.");



  TLegend* leg=new TLegend(0.25,0.5,0.7,0.85);
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

  prof[0]->GetXaxis()->SetTitle("Core p_{T}(L1)/p_{T}(L1)");
  prof[0]->GetYaxis()->SetTitle("p_{T}(L1)/p_{T}(gen. jet)");
  prof[0]->GetYaxis()->SetTitleOffset(1.7);
  prof[0]->GetYaxis()->SetRangeUser(0,2.5);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,2.51,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(0,1,500,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_response_core_ratio_PU200_core_cal.pdf");  


}









void plot_profile_L1jet_response_pT_PU200_core_cal(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";


  TH2F* h_PU0_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  TH2F* h_PU0_ptcal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  TH2F* h_PU0_coreptcal_pTfirst = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","1/(5.96346e-01 + 1.36914e-01/(1.25776e+00 - jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets])) * (4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2); 

  TH2F* h_PU200_raw_PUS = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);
  TH2F* h_PU200_ptcal_PUS = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)),2) ) * max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2);

  TH2F* h_PU200_coreptcal_pTfirst_PUS = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","1/(5.96346e-01 + 1.36914e-01/(1.25776e+00 - jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets])) * (4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)),2) ) * max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& (jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets])>0",25,0,500,97,0.06,2); 

 
  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw);
  histo.push_back(h_PU0_ptcal);
  histo.push_back(h_PU0_coreptcal_pTfirst);
  histo.push_back(h_PU200_raw_PUS);
  histo.push_back(h_PU200_ptcal_PUS);
  histo.push_back(h_PU200_coreptcal_pTfirst_PUS);
  
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 No calibr.");
  leg_entry.push_back("PU=0 Jet calibr. vs p_{T}");
  leg_entry.push_back("PU=0 2D jet calibr.");
  leg_entry.push_back("PU=200 + PUS");
  leg_entry.push_back("PU=200 + PUS +Jet calibr. vs p_{T}");
  leg_entry.push_back("PU=200 + PUS + 2D jet calibr.");


  TLegend* leg=new TLegend(0.25,0.5,0.7,0.85);
  leg->SetHeader("#splitline{p_T(gen. jet)>20 GeV}{1.6<|#eta(gen. jet)|<2.9}");
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

  prof[0]->GetXaxis()->SetTitle("p_{T}(gen. jet)");
  prof[0]->GetYaxis()->SetTitle("p_{T}(L1)/p_{T}(gen. jet)");
  prof[0]->GetYaxis()->SetTitleOffset(1.7);
  prof[0]->GetYaxis()->SetRangeUser(0,2.5);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(2,2.51,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(0,1,500,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_response_pt_PU200_core_cal.pdf");  


}









void plot_profile_L1jet_resolution_core_ratio_PU200_core_cal(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";


  TH2F* h_PU0_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,1,97,0.06,2);
  TH2F* h_PU0_ptcal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets]","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,1,97,0.06,2);
  TH2F* h_PU0_coreptcal_pTfirst = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets]","1/(5.96346e-01 + 1.36914e-01/(1.25776e+00 - jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets])) * (4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,1,97,0.06,2); 

    TH2F* h_PU200_raw_PUS = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","jets_0p1_core_ok_pt[VBF_parton_jets]/max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],1e-3)","max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)>0",25,0,1,97,0.06,2);
    TH2F* h_PU200_ptcal_PUS = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","jets_0p1_core_ok_pt[VBF_parton_jets]/max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],1e-3)","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)),2) ) * max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)>0",25,0,1,97,0.06,2);
    TH2F* h_PU200_coreptcal_pTfirst_PUS = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","jets_0p1_core_ok_pt[VBF_parton_jets]/max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],1e-3)","1/(5.96346e-01 + 1.36914e-01/(1.25776e+00 - jets_0p1_core_ok_pt[VBF_parton_jets]/max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],1e-3))) * (4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)),2) ) * max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)>0",25,0,1,97,0.06,2); 


  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw);
  histo.push_back(h_PU0_ptcal);
  histo.push_back(h_PU0_coreptcal_pTfirst);
  histo.push_back(h_PU200_raw_PUS);
  histo.push_back(h_PU200_ptcal_PUS);
  histo.push_back(h_PU200_coreptcal_pTfirst_PUS);
  

  
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 No calibr.");
  leg_entry.push_back("PU=0 Jet calibr. vs p_{T}");
  leg_entry.push_back("PU=0 2D jet calibr.");
  leg_entry.push_back("PU=200 + PUS");
  leg_entry.push_back("PU=200 + PUS +Jet calibr. vs p_{T}");
  leg_entry.push_back("PU=200 + PUS + 2D jet calibr.");

  TLegend* leg=new TLegend(0.4,0.5,0.7,0.85);
  leg->SetHeader("#splitline{p_T(gen. jet)>20 GeV}{1.6<|#eta(gen.jet)|<2.9}");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  
  vector<TGraphErrors*> graph;

  for(unsigned int i=0;i<histo.size();i++){

    TGraphErrors* gr = new TGraphErrors();
    TProfile* p = (TProfile*)histo[i]->ProfileX()->Clone();
    p->BuildOptions(0,0,"s");
    for(unsigned int j=1;j<=p->GetNbinsX();j++){
      float x = p->GetBinCenter(j);
      float y = p->GetBinError(j)/p->GetBinContent(j);
      if(y>1 || p->GetBinContent(j)==0) continue;
      gr->SetPoint(j-1,x,y);
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

  graph[0]->GetXaxis()->SetTitle("Core p_{T}(L1)/p_{T}(L1)");
  graph[0]->GetYaxis()->SetTitle("RMS(p_{T}(L1)/p_{T}(gen. jet)) / <p_{T}(L1)/p_{T}(gen. jet)>");
  graph[0]->GetYaxis()->SetTitleOffset(1.7);
  graph[0]->GetYaxis()->SetRangeUser(0,1.2);
  graph[0]->SetTitle("");
  graph[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    graph[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.21,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_resolution_core_ratio_PU200_core_cal.pdf");  


}









void plot_profile_L1jet_resolution_pT_PU200_core_cal(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";


  TH2F* h_PU0_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  TH2F* h_PU0_ptcal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  TH2F* h_PU0_coreptcal_pTfirst = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","1/(5.96346e-01 + 1.36914e-01/(1.25776e+00 - jets_0p1_core_ok_pt[VBF_parton_jets]/jets_raw_Luca_pt[VBF_parton_jets])) * (4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2); 

  TH2F* h_PU200_raw_PUS = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)>0",25,0,500,97,0.06,2);
  TH2F* h_PU200_ptcal_PUS = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)),2) ) * max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)>0",25,0,500,97,0.06,2);
  TH2F* h_PU200_coreptcal_pTfirst_PUS = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","1/(5.96346e-01 + 1.36914e-01/(1.25776e+00 - jets_0p1_core_ok_pt[VBF_parton_jets]/max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],1e-3))) * (4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],20)),2) ) * max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]",cut+"&& max(jets_raw_Luca_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_C3D[VBF_parton_jets],0)>0",25,0,500,97,0.06,2); 

 
  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw);
  histo.push_back(h_PU0_ptcal);
  histo.push_back(h_PU0_coreptcal_pTfirst);
  histo.push_back(h_PU200_raw_PUS);
  histo.push_back(h_PU200_ptcal_PUS);
  histo.push_back(h_PU200_coreptcal_pTfirst_PUS);
  

  
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 No calibr.");
  leg_entry.push_back("PU=0 Jet calibr. vs p_{T}");
  leg_entry.push_back("PU=0 2D jet calibr.");
  leg_entry.push_back("PU=200 + PUS");
  leg_entry.push_back("PU=200 + PUS +Jet calibr. vs p_{T}");
  leg_entry.push_back("PU=200 + PUS + 2D jet calibr.");


  TLegend* leg=new TLegend(0.4,0.5,0.7,0.85);
  leg->SetHeader("#splitline{p_T(gen. jet)>20 GeV}{1.6<|#eta(gen.jet)|<2.9}");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  
  vector<TGraphErrors*> graph;

  for(unsigned int i=0;i<histo.size();i++){

    TProfile* p = (TProfile*)histo[i]->ProfileX()->Clone();
    p->BuildOptions(0,0,"s");
    TGraphErrors* gr = new TGraphErrors(p->GetNbinsX());
    for(unsigned int j=1;j<=p->GetNbinsX();j++){
      float x = p->GetBinCenter(j);
      float y = p->GetBinError(j)/p->GetBinContent(j);      
      if(y>1 || p->GetBinContent(j)==0) continue;
      gr->SetPoint(j-1,x,y);
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

  graph[0]->GetXaxis()->SetTitle("p_{T}(gen. jet)");
  graph[0]->GetYaxis()->SetTitle("RMS(p_{T}(L1)/p_{T}(gen. jet)) / <p_{T}(L1)/p_{T}(gen. jet)>");
  graph[0]->GetYaxis()->SetTitleOffset(1.7);
  graph[0]->GetYaxis()->SetRangeUser(0,0.6);
  graph[0]->SetTitle("");
  graph[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    graph[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(2,1.51,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_resolution_pt_PU200_core_cal.pdf");  


}


