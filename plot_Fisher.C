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

#include <vector>

using namespace std;


void draw_weights(){

  //vector<float> w1 = {-2.04613,-3.43434,-3.52741,-0.641428,1.63015,1.72426,2.55182,3.7712,3.05594,4.19388,3.04662,1.95578,2.92687,0.337107,-1.36569,0.662399,0.490461,0.886983,0.566291,3.62657,0.697395,1.08258,2.39743,3.30359,0.667652,0.344089,7.99027,4.89368,2.82031,5.01364,3.67732,3.15481,5.40121,0.162698,11.0507,6.4112,2.57398,-2.11481};

  //vector<float> w2 = { -1.83464f, -3.35853f, -2.65147f, -0.498758f, 1.29053f, 2.24311f, 2.71012f, 4.50412f, 3.30848f, 4.55931f, 2.90686f, 1.87420f, 3.31785f, 0.490263f, -0.923447f, 0.680648f, 0.728287f, 0.956625f, 0.779487f, 4.07334f, 1.08731f, 1.57581f, 2.96377f, 4.06176f, 0.553739f, -0.0887574f, 7.33712f, 3.31031f, 3.33608f, 2.23893f, 6.08362f, 10.4506f, -0.884434f, 5.25114f, 10.9429f, -3.63482f, 17.3468f, -5.80591f };

  vector<float> w1 = { -2.19465f, -1.87364f, -1.66775f, -1.30156f, -1.02639f, -0.876539f, -0.768602f, -0.523715f, -0.648102f, -0.517912f, -0.670387f, -0.696750f, -0.565943f, -0.711266f, -0.757421f, -0.553625f, -0.510087f, -0.438490f, -0.450306f, -0.256428f, -0.385574f, -0.312418f, -0.232202f, -0.203622f, -0.272561f, -0.296243f };

  vector<float> w2 = { -2.27675f, -1.88695f, -1.65127f, -1.30671f, -1.00629f, -0.882970f, -0.781570f, -0.504960f, -0.637268f, -0.484294f, -0.651698f, -0.704922f, -0.577723f, -0.744577f, -0.776692f, -0.553100f, -0.538148f, -0.444603f, -0.450670f, -0.233005f, -0.340507f, -0.289663f, -0.222869f, -0.205046f, -0.308257f, -0.308722f };
  
  

  TH1F* h1 = new TH1F("h1","h1",39,0,39);
  TH1F* h2 = new TH1F("h2","h2",39,0,39);

  for(unsigned int k=0;k<w1.size();k++){
    h1->Fill(k,w1[k]);
    h2->Fill(k,w2[k]);    
  }

  h1->SetLineColor(kBlue);
  h1->SetLineWidth(2);
  h2->SetLineColor(kRed);
  h2->SetLineWidth(2);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h1->GetXaxis()->SetTitle("Layer");
  h1->GetYaxis()->SetTitle("Layer weight");
  h1->GetYaxis()->SetTitleOffset(1.7);
  //h1->GetYaxis()->SetRangeUser(-3,1.2);
  h1->GetYaxis()->SetRangeUser(-7,21);
  h1->SetStats(0);
  h1->SetTitle("");
  h1->Draw("hist");
  h2->Draw("histsame");

   
  TLatex *texl = new TLatex(0.002,1.01*h1->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();

  c->SaveAs("plots/layer_weights_Fisher.pdf");  


}




void plot_fraction_layer5(){

  TString VBF_cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";
  TString ZB_cut = "jets_pt>20";


  TH1F* h_VBF = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","layer_jets_energy_fraction[5][VBF_parton_jets]",VBF_cut,100,0,1);
  TH1F* h_ZB = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","layer_jets_energy_fraction[5]",ZB_cut,100,0,1);
  
  vector<TH1F*> histo;
  histo.push_back(h_ZB);
  histo.push_back(h_VBF);
  
   vector<TString> leg_entry;
  leg_entry.push_back("ZB PU=200");
  leg_entry.push_back("VBF PU=200");

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

  histo = sort_histo(histo);

  histo[0]->GetXaxis()->SetTitle("Fraction layer #5");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(0.002,1.01*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();

  c->SaveAs("plots/layer_jet_fraction5.pdf");  


}






void plot_Fisher(){

  TString VBF_cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";
  TString tau_cut = "gentau_jets>=0 && abs(gentau_vis_eta)>1.6 && abs(gentau_vis_eta)<2.9 && gentau_vis_pt>20 && gentau_decayMode>=0 && gentau_decayMode<=5";
  TString ZB_cut = "jets_pt>20";


  TH1F* h_VBF = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","jets_Fisher_VBF[VBF_parton_jets]",VBF_cut,100,-4,6);
  TH1F* h_tau = single_plot("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","jets_Fisher_VBF[gentau_jets]",tau_cut,100,-4,6);
  TH1F* h_ZB = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","jets_Fisher_VBF",ZB_cut,100,-4,6);
  
  vector<TH1F*> histo;
  histo.push_back(h_ZB);
  histo.push_back(h_VBF);
  histo.push_back(h_tau);
  
   vector<TString> leg_entry;
  leg_entry.push_back("ZB PU=200");
  leg_entry.push_back("VBF PU=200");
  leg_entry.push_back("#tau_{h} PU=200");

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

  histo = sort_histo(histo);

  histo[0]->GetXaxis()->SetTitle("Fisher discr.");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(-3.95,1.01*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();

  c->SaveAs("plots/jets_Fisher_VBF.pdf");  


}







void plot_fraction_layer5_ZB_pt(){


  TH1F* h_ZB_pt20_40 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","layer_jets_energy_fraction[5]","jets_pt>20 && jets_pt<40",100,0,1);
  TH1F* h_ZB_pt40_60 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","layer_jets_energy_fraction[5]","jets_pt>40 && jets_pt<60",100,0,1);
  TH1F* h_ZB_pt60 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","layer_jets_energy_fraction[5]","jets_pt>60",100,0,1);
  
  vector<TH1F*> histo;
  histo.push_back(h_ZB_pt20_40);
  histo.push_back(h_ZB_pt40_60);
  histo.push_back(h_ZB_pt60);
  
  vector<TString> leg_entry;
  leg_entry.push_back("ZB 20<p_{T}<40 GeV");
  leg_entry.push_back("ZB 40<p_{T}<60 GeV");
  leg_entry.push_back("ZB p_{T}>60 GeV");

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

  histo = sort_histo(histo);

  histo[0]->GetXaxis()->SetTitle("Fraction layer #5");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(0.002,1.01*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();

  c->SaveAs("plots/layer_jet_fraction5_ZB_pt.pdf");  


}







void plot_Fisher_ZB_pt(){


  TH1F* h_ZB_pt20_40 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","jets_Fisher_VBF","jets_pt>20 && jets_pt<40",100,-4,6);
  TH1F* h_ZB_pt40_60 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","jets_Fisher_VBF","jets_pt>40 && jets_pt<60",100,-4,6);
  TH1F* h_ZB_pt60 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","jets_Fisher_VBF","jets_pt>60",100,-4,6);
  
  vector<TH1F*> histo;
  histo.push_back(h_ZB_pt20_40);
  histo.push_back(h_ZB_pt40_60);
  histo.push_back(h_ZB_pt60);
  
  vector<TString> leg_entry;
  leg_entry.push_back("ZB 20<p_{T}<40 GeV");
  leg_entry.push_back("ZB 40<p_{T}<60 GeV");
  leg_entry.push_back("ZB p_{T}>60 GeV");

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

  histo = sort_histo(histo);

  histo[0]->GetXaxis()->SetTitle("Fisher discr.");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(-3.98,1.01*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();

  c->SaveAs("plots/jet_Fisher_ZB_pt.pdf");  


}







void plot_ROC_VBF_layer(){

  TString file_sig = "/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root";
  TString file_bkg = "/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root";

  TString VBF_cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20 && jets_pt[VBF_parton_genjet]>20";
  TString ZB_cut = "jets_pt>20";

  
  vector<TGraphErrors*> ROCs;
  vector<TString> leg_entry;
  

  ROCs.push_back(get_ROC_VBF(file_sig,file_bkg,VBF_cut,ZB_cut,"layer_jets_energy_fraction[3]",100,0,1,false));
  ROCs.push_back(get_ROC_VBF(file_sig,file_bkg,VBF_cut,ZB_cut,"layer_jets_energy_fraction[5]",100,0,1,false));
  ROCs.push_back(get_ROC_VBF(file_sig,file_bkg,VBF_cut,ZB_cut,"layer_jets_energy_fraction[7]",100,0,1,false));
  ROCs.push_back(get_ROC_VBF(file_sig,file_bkg,VBF_cut,ZB_cut,"layer_jets_energy_fraction[9]",100,0,1,false));
  ROCs.push_back(get_ROC_VBF(file_sig,file_bkg,VBF_cut,ZB_cut,"layer_jets_energy_fraction[11]",100,0,1,false));
  ROCs.push_back(get_ROC_VBF(file_sig,file_bkg,VBF_cut,ZB_cut,"jets_Fisher_VBF",100,-4,6,true));


  leg_entry.push_back("Layer #3");
  leg_entry.push_back("Layer #5");
  leg_entry.push_back("Layer #7");
  leg_entry.push_back("Layer #9");
  leg_entry.push_back("Layer #11");
  leg_entry.push_back("Fisher discr.");

  
  TLegend* leg=new TLegend(0.6,0.2,0.85,0.6);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  for(unsigned int i=0;i<ROCs.size();i++){
    TGraphErrors* ROC = ROCs[i];
    ROC->SetLineWidth(2);
    ROC->SetLineColor(i+1);
    if(i>3)
      ROC->SetLineColor(i+2);     
    ROC->SetFillColor(0);
    leg->AddEntry(ROC,leg_entry[i]);
  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  c->SetGrid();
  c->SetLogy();
  
  ROCs[0]->GetXaxis()->SetTitle("Signal eff.");
  ROCs[0]->GetYaxis()->SetTitle("Bkg eff.");
  ROCs[0]->GetYaxis()->SetTitleOffset(1.7);
  //ROCs[0]->GetXaxis()->SetLimits(0.,1.);
  //ROCs[0]->GetYaxis()->SetRangeUser(0.,1.);
  ROCs[0]->GetXaxis()->SetLimits(0.5,1.);
  ROCs[0]->GetYaxis()->SetRangeUser(1e-2,1.);
  ROCs[0]->SetTitle("");
  ROCs[0]->Draw("APL");
  for(unsigned int i=1;i<ROCs.size();i++)
    ROCs[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(0.51,1.02,"CMS Simulation #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();

  
  c->SaveAs("plots/ROC_layer_fraction_VBF_layer_Fisher.pdf");  



}









void plot_ROC_VBF_2D_Fisher(){

  TString file_sig = "/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root";
  TString file_bkg = "/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root";

  TString VBF_cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20 && jets_pt[VBF_parton_genjet]>20";
  TString ZB_cut = "jets_pt>20";

  
  vector<TGraphErrors*> ROCs;
  vector<TString> leg_entry;
  
  ROCs.push_back(get_ROC_VBF(file_sig,file_bkg,VBF_cut,ZB_cut,"jets_pt",480,20,500,true));
  ROCs.push_back(get_ROC_VBF(file_sig,file_bkg,VBF_cut,ZB_cut,"layer_jets_energy_fraction[5]",100,0,1,false));
  ROCs.push_back(get_ROC_VBF(file_sig,file_bkg,VBF_cut,ZB_cut,"jets_Fisher_VBF",100,-3,4,true));
  ROCs.push_back(get_ROC_VBF_2D(file_sig,file_bkg,VBF_cut,ZB_cut,"layer_jets_energy_fraction[5]",100,0,1,false));
  ROCs.push_back(get_ROC_VBF_2D(file_sig,file_bkg,VBF_cut,ZB_cut,"jets_Fisher_VBF",100,-3,4,true));

  leg_entry.push_back("Jet p_{T}");
  leg_entry.push_back("Layer #5");
  leg_entry.push_back("Fisher discr.");
  leg_entry.push_back("Jet p_{T} + Layer #5");
  leg_entry.push_back("Jet p_{T} + Fisher discr.");
  

  TLegend* leg=new TLegend(0.2,0.5,0.5,0.8);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  for(unsigned int i=0;i<ROCs.size();i++){
    TGraphErrors* ROC = ROCs[i];
    ROC->SetLineWidth(2);
    ROC->SetLineColor(i+1);
    if(i>3)
      ROC->SetLineColor(i+2);     
    ROC->SetFillColor(0);
    leg->AddEntry(ROC,leg_entry[i]);
  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  c->SetGrid();
  c->SetLogy();
  
  ROCs[0]->GetXaxis()->SetTitle("Signal eff.");
  ROCs[0]->GetYaxis()->SetTitle("Bkg eff.");
  ROCs[0]->GetYaxis()->SetTitleOffset(1.7);
  //ROCs[0]->GetXaxis()->SetLimits(0.,1.);
  //ROCs[0]->GetYaxis()->SetRangeUser(0.,1.);
  ROCs[0]->GetXaxis()->SetLimits(0.5,1.);
  ROCs[0]->GetYaxis()->SetRangeUser(1e-2,1.);
  ROCs[0]->SetTitle("");
  ROCs[0]->Draw("APL");
  for(unsigned int i=1;i<ROCs.size();i++)
    ROCs[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(0.51,1.02,"CMS Simulation #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();

  
  c->SaveAs("plots/ROC_2D_VBF_Fisher.pdf");  



}





void write_layer_jets_energy_fraction_pt_quantiles(TString process, int PU){

  TString VBF_sample = "/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root";
  TString tau_sample_PU200 = "/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root";
  TString tau_sample_PU0 = "/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root";
  TString ZB_sample = "/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root";

  TString VBF_cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";
  TString tau_cut = "gentau_jets>=0 && abs(gentau_vis_eta)>1.6 && abs(gentau_vis_eta)<2.9 && gentau_vis_pt>20 && gentau_decayMode>=0 && gentau_decayMode<=5";
  TString ZB_cut = "1";
  
  TString VBF_index = "[VBF_parton_jets]";
  TString tau_index = "[gentau_jets]";
  TString ZB_index = "";

  TString sample;
  TString cut;
  TString index;
  
  if(process=="VBF"){
    sample = VBF_sample;
    cut = VBF_cut;
    index = VBF_index;
  }
  else if(process=="tau"){
    if(PU==200)
      sample = tau_sample_PU200;
    else
      sample = tau_sample_PU0;
    cut = tau_cut;
    index = tau_index;
  }
  else if(process=="ZB"){
    sample = ZB_sample;
    cut = ZB_cut;
    index = ZB_index;
  }


  int nbins = 20;
  int nq = 100;
  double xq[nq];
  double yq[nq];
  for(int i=0;i<nq;i++) xq[i]=float(i+1)/nq;

  TGraphErrors gr(nbins);
  vector<TGraphErrors> gr_quant(nq,gr);

  TH2F* h_2D = single_plot2D(sample,"HGCalTriggerNtupleJet","jets_pt"+index,"jets_Fisher_VBF"+index,cut,nbins,0,200,1000,-4,6);
    
  for(int pT_bin=1; pT_bin<=nbins; pT_bin++){

    TH1D* h_pT = h_2D->ProjectionY("h_pT",pT_bin,pT_bin);   
            
    double x=h_2D->GetXaxis()->GetBinCenter(pT_bin);
    cout<<"pT="<<x<<endl;
    double xerr=0.5*h_2D->GetXaxis()->GetBinWidth(pT_bin);

    h_pT->GetQuantiles(nq,yq,xq);
    for(int iq=0;iq<nq;iq++){
      gr_quant[iq].SetPoint(pT_bin-1,x,yq[iq]);
      gr_quant[iq].SetPointError(pT_bin-1,xerr,0);
    }

    delete h_pT;

  }

  delete h_2D;


  TFile* f_new = TFile::Open("Fisher_jets_pt_quantiles_"+process+Form("_PU%i",PU)+".root","RECREATE");

  for(int iq=0; iq<nq; iq++){
    gr_quant[iq].Write(Form(process+"_Fisher_quant%i",iq));    
  }

  f_new->Close();


}









void plot_compar_Fisher(){

  TFile* f_VBF = TFile::Open("Fisher_jets_pt_quantiles_VBF_PU200.root");
  TFile* f_tau = TFile::Open("Fisher_jets_pt_quantiles_tau_PU200.root");
  TFile* f_ZB = TFile::Open("Fisher_jets_pt_quantiles_ZB_PU200.root");

  vector<TString> gr;
  gr.push_back("VBF_Fisher_quant4");
  gr.push_back("tau_Fisher_quant4");
  gr.push_back("ZB_Fisher_quant4");
  /*gr.push_back("VBF_Fisher_quant24");
  gr.push_back("tau_Fisher_quant24");
  gr.push_back("ZB_Fisher_quant24");*/
  gr.push_back("VBF_Fisher_quant49");
  gr.push_back("tau_Fisher_quant49");
  gr.push_back("ZB_Fisher_quant49");

  vector<TString> leg_entry;
  leg_entry.push_back("VBF 95%");
  leg_entry.push_back("#tau_{h} 95%");
  leg_entry.push_back("ZB 95%");
  /*leg_entry.push_back("VBF 75%");
  leg_entry.push_back("#tau_{h} 75%");
  leg_entry.push_back("ZB 75%");*/
  leg_entry.push_back("VBF 50%");
  leg_entry.push_back("#tau_{h} 50%");
  leg_entry.push_back("ZB 50%");
  
  TLegend* leg=new TLegend(0.6,0.4,0.8,0.85);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  vector<TGraphErrors*> graphs;

  for(unsigned int i=0;i<gr.size();i++){
    
    TGraphErrors* graph;
    if(gr[i].Contains("VBF"))
      graph = (TGraphErrors*)f_VBF->Get(gr[i]);
    else if(gr[i].Contains("tau"))
      graph = (TGraphErrors*)f_tau->Get(gr[i]);
    else if(gr[i].Contains("ZB"))
      graph = (TGraphErrors*)f_ZB->Get(gr[i]);
    for(unsigned int j=20;j>10;j--)
      graph->RemovePoint(j);
    graph->SetLineColor(i+1);
    if(i>3)
      graph->SetLineColor(i+2);
    if(i>7)
      graph->SetLineColor(i-7);   
    graph->SetLineWidth(2);
    graph->SetFillColor(0);
    leg->AddEntry(graph,leg_entry[i]);
    graphs.push_back(graph);

  }



  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  graphs[0]->GetXaxis()->SetTitle("p_{T}(L1 jet) [GeV]");
  graphs[0]->GetYaxis()->SetTitle("Cut on Fisher discr.");
  graphs[0]->GetYaxis()->SetTitleOffset(1.7);
  graphs[0]->GetXaxis()->SetLimits(0,200.);
  graphs[0]->GetYaxis()->SetRangeUser(-2,2);
  graphs[0]->SetTitle("");
  graphs[0]->Draw();
  
  for(unsigned int i=1;i<graphs.size();i++)
    graphs[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(2.,2.02,"CMS Simulation Preliminary, #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.029);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/Fisher_compar_quant.pdf");  
  f_VBF->Close();
  f_ZB->Close();

}
  









void plot_turnons_L1SingleJet_dRNNC2D_PU200_Fisher(int L1pt){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  //double x[18]={0,40,60,70,80,90,100,110,120,130,140,160,180,200,250,300,400,500};
  //int nbins=17;

  double x[16]={0,25,35,40,45,50,55,60,65,75,80,90,100,120,150,300};
  int nbins=15;


  TH1F* h_PU200_denom_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_cal_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D->Divide(h_PU200_cal_dRNNC2D,h_PU200_denom_dRNNC2D);

  TH1F* h_PU200_cal_dRNNC2D_cut_0p2 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i && (layer_jets_energy_fraction[5][VBF_parton_jets]<0.2 )",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D_cut_0p2 = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D_cut_0p2->Divide(h_PU200_cal_dRNNC2D_cut_0p2,h_PU200_denom_dRNNC2D);

  TH1F* h_PU200_cal_dRNNC2D_cut_0p2_relaxed = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i && (layer_jets_energy_fraction[5][VBF_parton_jets]<0.2  || 1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)>60)",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D_cut_0p2_relaxed = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D_cut_0p2_relaxed->Divide(h_PU200_cal_dRNNC2D_cut_0p2_relaxed,h_PU200_denom_dRNNC2D);

  TH1F* h_PU200_cal_dRNNC2D_cut_Fisher = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i && (jets_Fisher_VBF[VBF_parton_jets]>0.5)",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D_cut_Fisher = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D_cut_Fisher->Divide(h_PU200_cal_dRNNC2D_cut_Fisher,h_PU200_denom_dRNNC2D);


  TH1F* h_PU200_cal_dRNNC2D_cut_Fisher_relaxed = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i && (jets_Fisher_VBF[VBF_parton_jets]>0.5 || 1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)>60)",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D_cut_Fisher_relaxed = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D_cut_Fisher_relaxed->Divide(h_PU200_cal_dRNNC2D_cut_Fisher_relaxed,h_PU200_denom_dRNNC2D);


  vector<TGraphAsymmErrors*> turnons;
  turnons.push_back(gr_PU200_cal_dRNNC2D);
  turnons.push_back(gr_PU200_cal_dRNNC2D_cut_0p2);
  turnons.push_back(gr_PU200_cal_dRNNC2D_cut_0p2_relaxed);
  turnons.push_back(gr_PU200_cal_dRNNC2D_cut_Fisher);
  turnons.push_back(gr_PU200_cal_dRNNC2D_cut_Fisher_relaxed);


  vector<TString> leg_entry;
  leg_entry.push_back("Default");
  leg_entry.push_back("Fraction layer#5<0.2");
  leg_entry.push_back("+ relaxed");
  leg_entry.push_back("Fisher discr.>0.5");
  leg_entry.push_back("+ relaxed");



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


  c->SaveAs(Form("plots/turnons_L1SingleJet%i_dRNNC2D_PU200_Fisher.pdf",L1pt));  


}







void plot_turnons_L1SingleJet_dRNNC2D_PU200_Fisher_compar(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  //double x[18]={0,40,60,70,80,90,100,110,120,130,140,160,180,200,250,300,400,500};
  //int nbins=17;

  double x[16]={0,25,35,40,45,50,55,60,65,75,80,90,100,120,150,300};
  int nbins=15;


  TH1F* h_PU200_denom_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_cal_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i",50),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D->Divide(h_PU200_cal_dRNNC2D,h_PU200_denom_dRNNC2D);


  TH1F* h_PU200_cal_dRNNC2D_cut_0p2_relaxed = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i && (layer_jets_energy_fraction[5][VBF_parton_jets]<0.2  || 1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)>60)",45),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D_cut_0p2_relaxed = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D_cut_0p2_relaxed->Divide(h_PU200_cal_dRNNC2D_cut_0p2_relaxed,h_PU200_denom_dRNNC2D);



  TH1F* h_PU200_cal_dRNNC2D_cut_0p5_Fisher = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i && (jets_Fisher_VBF[VBF_parton_jets]>0.5  || 1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)>60)",46),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D_cut_0p5_Fisher = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D_cut_0p5_Fisher->Divide(h_PU200_cal_dRNNC2D_cut_0p5_Fisher,h_PU200_denom_dRNNC2D);


  vector<TGraphAsymmErrors*> turnons;
  turnons.push_back(gr_PU200_cal_dRNNC2D);
  turnons.push_back(gr_PU200_cal_dRNNC2D_cut_0p2_relaxed);
  turnons.push_back(gr_PU200_cal_dRNNC2D_cut_0p5_Fisher);


  vector<TString> leg_entry;
  leg_entry.push_back("Default SingleJet50");
  leg_entry.push_back("#splitline{Fraction layer#5<0.2}{SingleJet45}");
  leg_entry.push_back("#splitline{Fisher discr.>0.5}{SingleJet46}");


  TLegend* leg=new TLegend(0.45,0.12,0.85,0.55);
  leg->SetHeader("#splitline{L1_SingleJet}{1.6<|#eta(gen.jet)|<2.9}");
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


  c->SaveAs("plots/turnons_L1SingleJet_dRNNC2D_PU200_Fisher_compar.pdf");  


}






void plot_turnons_L1SingleTau_dRNNC2D_PU200_Fisher(int L1pt){

  TString cut = "gentau_jets>=0 && abs(gentau_vis_eta)>1.6 && abs(gentau_vis_eta)<2.9 && gentau_vis_pt>0 && gentau_decayMode>=0 && gentau_decayMode<=5";
  TString cut_Phase1 = "abs(tauEta)>1.6 && abs(tauEta)<3.0 && tau_genindex==5";

  double x[22]={0,10,20,25,30,33,35,37,39,40,41,43,45,47,50,55,60,65,75,80,90,100};
  int nbins=21;

  double x2[13]={0,20,25,30,35,38,40,42,45,50,60,80,100};
  int nbins2=12;



  TH1F* h_PU200_denom_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","gentau_vis_pt",cut,nbins,x);
  TH1F* h_PU200_cal_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","gentau_vis_pt",cut+Form("&& 1.1/(0.93-1/(0.2*max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20)+1e-3*pow(max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20),2))) * (jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets]) >%i",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D->Divide(h_PU200_cal_dRNNC2D,h_PU200_denom_dRNNC2D);


  TH1F* h_PU200_cal_dRNNC2D_cut_0p2 = single_plot("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","gentau_vis_pt",cut+Form("&& 1.1/(0.93-1/(0.2*max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20)+1e-3*pow(max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20),2))) * (jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets]) >%i && (layer_jets_energy_fraction[5][gentau_jets]<0.2)",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D_cut_0p2 = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D_cut_0p2->Divide(h_PU200_cal_dRNNC2D_cut_0p2,h_PU200_denom_dRNNC2D);

  TH1F* h_PU200_cal_dRNNC2D_cut_0p2_relaxed = single_plot("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","gentau_vis_pt",cut+Form("&& 1.1/(0.93-1/(0.2*max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20)+1e-3*pow(max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20),2))) * (jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets]) >%i && (layer_jets_energy_fraction[5][gentau_jets]<0.2 || 1.1/(0.93-1/(0.2*max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20)+1e-3*pow(max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20),2))) * (jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets])>45)",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D_cut_0p2_relaxed = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D_cut_0p2_relaxed->Divide(h_PU200_cal_dRNNC2D_cut_0p2_relaxed,h_PU200_denom_dRNNC2D);


  TH1F* h_PU200_cal_dRNNC2D_Fisher_0p5 = single_plot("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","gentau_vis_pt",cut+Form("&& 1.1/(0.93-1/(0.2*max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20)+1e-3*pow(max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20),2))) * (jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets]) >%i && (jets_Fisher_VBF[gentau_jets]>0.5)",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D_Fisher_0p5 = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D_Fisher_0p5->Divide(h_PU200_cal_dRNNC2D_Fisher_0p5,h_PU200_denom_dRNNC2D);

  TH1F* h_PU200_cal_dRNNC2D_Fisher_0p5_relaxed = single_plot("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","gentau_vis_pt",cut+Form("&& 1.1/(0.93-1/(0.2*max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20)+1e-3*pow(max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20),2))) * (jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets]) >%i && (jets_Fisher_VBF[gentau_jets]>0.5 || 1.1/(0.93-1/(0.2*max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20)+1e-3*pow(max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20),2))) * (jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets])>45)",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D_Fisher_0p5_relaxed = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D_Fisher_0p5_relaxed->Divide(h_PU200_cal_dRNNC2D_Fisher_0p5_relaxed,h_PU200_denom_dRNNC2D);



  vector<TGraphAsymmErrors*> turnons;
  turnons.push_back(gr_PU200_cal_dRNNC2D);
  //turnons.push_back(gr_PU200_cal_dRNNC2D_cut_0p2);
  turnons.push_back(gr_PU200_cal_dRNNC2D_cut_0p2_relaxed);
  //turnons.push_back(gr_PU200_cal_dRNNC2D_Fisher_0p5);
  turnons.push_back(gr_PU200_cal_dRNNC2D_Fisher_0p5_relaxed);

  vector<TString> leg_entry;
  leg_entry.push_back("Default");
  leg_entry.push_back("Fraction layer#5 <0.2");
  //leg_entry.push_back("+ relaxed");
  leg_entry.push_back("Fisher discr.>0.5");
  //leg_entry.push_back("+ relaxed");


  TLegend* leg=new TLegend(0.5,0.12,0.85,0.55);
  leg->SetHeader(Form("#splitline{L1_SingleTau%i}{1.6<|#eta(gen.#tau_{h})|<2.9}",L1pt));
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


  TLatex *texl = new TLatex(1.57,1.01,"CMS Simulation, H#rightarrow#tau#tau #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");
  gPad->SetTicks();


  c->SaveAs(Form("plots/turnons_L1SingleTau%i_dRNNC2D_PU200_Fisher.pdf",L1pt));  


}











void plot_turnons_L1SingleTau_dRNNC2D_PU200_Fisher_compar(){

  TString cut = "gentau_jets>=0 && abs(gentau_vis_eta)>1.6 && abs(gentau_vis_eta)<2.9 && gentau_vis_pt>0 && gentau_decayMode>=0 && gentau_decayMode<=5";
  TString cut_Phase1 = "abs(tauEta)>1.6 && abs(tauEta)<3.0 && tau_genindex==5";

  double x[22]={0,10,20,25,30,33,35,37,39,40,41,43,45,47,50,55,60,65,75,80,90,100};
  int nbins=21;

  double x2[13]={0,20,25,30,35,38,40,42,45,50,60,80,100};
  int nbins2=12;



  TH1F* h_PU200_denom_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","gentau_vis_pt",cut,nbins,x);
  TH1F* h_PU200_cal_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","gentau_vis_pt",cut+Form("&& 1.1/(0.93-1/(0.2*max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20)+1e-3*pow(max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20),2))) * (jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets]) >%i",40),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D->Divide(h_PU200_cal_dRNNC2D,h_PU200_denom_dRNNC2D);


  TH1F* h_PU200_cal_dRNNC2D_cut_0p2_relaxed = single_plot("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","gentau_vis_pt",cut+Form("&& 1.1/(0.93-1/(0.2*max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20)+1e-3*pow(max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20),2))) * (jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets]) >%i && (layer_jets_energy_fraction[5][gentau_jets]<0.2 || 1.1/(0.93-1/(0.2*max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20)+1e-3*pow(max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20),2))) * (jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets])>45)",38),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D_cut_0p2_relaxed = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D_cut_0p2_relaxed->Divide(h_PU200_cal_dRNNC2D_cut_0p2_relaxed,h_PU200_denom_dRNNC2D);


  TH1F* h_PU200_cal_dRNNC2D_Fisher_0p5_relaxed = single_plot("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","gentau_vis_pt",cut+Form("&& 1.1/(0.93-1/(0.2*max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20)+1e-3*pow(max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20),2))) * (jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets]) >%i && (jets_Fisher_VBF[gentau_jets]>0.5 || 1.1/(0.93-1/(0.2*max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20)+1e-3*pow(max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20),2))) * (jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets])>45)",38),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D_Fisher_0p5_relaxed = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D_Fisher_0p5_relaxed->Divide(h_PU200_cal_dRNNC2D_Fisher_0p5_relaxed,h_PU200_denom_dRNNC2D);



  vector<TGraphAsymmErrors*> turnons;
  turnons.push_back(gr_PU200_cal_dRNNC2D);
  turnons.push_back(gr_PU200_cal_dRNNC2D_cut_0p2_relaxed);
  turnons.push_back(gr_PU200_cal_dRNNC2D_Fisher_0p5_relaxed);

  vector<TString> leg_entry;
  leg_entry.push_back("SingleTau40");
  leg_entry.push_back("#splitline{Fraction layer#5 <0.2}{SingleTau38}");
  leg_entry.push_back("#splitline{Fisher discr.>0.5}{SingleTau38}");


  TLegend* leg=new TLegend(0.5,0.12,0.85,0.55);
  leg->SetHeader("#splitline{L1_SingleTau}{1.6<|#eta(gen.#tau_{h})|<2.9}");
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


  TLatex *texl = new TLatex(1.57,1.01,"CMS Simulation, H#rightarrow#tau#tau #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");
  gPad->SetTicks();


  c->SaveAs("plots/turnons_L1SingleTau_dRNNC2D_PU200_Fisher_compar.pdf");  


}












void plot_Fisher_c3d_alllength(){

  TString VBF_cut = "VBF_parton_genjet[0]>=0 && VBF_parton_jets[0]>=0 && abs(genjet_eta[VBF_parton_genjet[0]])>1.6 && abs(genjet_eta[VBF_parton_genjet[0]])<2.9 && genjet_pt[VBF_parton_genjet[0]]>20 && cl3d_jet==VBF_parton_jets[0]";
  TString ZB_cut = "cl3d_jet>=0 && jets_pt[cl3d_jet]>20";

  TH1F* h_VBF_PU0_Fisher_jet = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","cl3d_Fisher_cl3d",VBF_cut,100,0,3);

  TH1F* h_VBF_PU200_Fisher_jet = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","cl3d_Fisher_cl3d",VBF_cut,100,0,3);

  TH1F* h_ZB_Fisher_jet = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","cl3d_Fisher_cl3d",ZB_cut,100,0,3);

  
  vector<TH1F*> histo;
  histo.push_back(h_VBF_PU0_Fisher_jet);
  histo.push_back(h_VBF_PU200_Fisher_jet);
  histo.push_back(h_ZB_Fisher_jet);

  
  vector<TString> leg_entry;
  leg_entry.push_back("VBF PU=0");
  leg_entry.push_back("VBF PU=200");
  leg_entry.push_back("ZB PU=200");

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

  histo = sort_histo(histo);

  histo[0]->GetXaxis()->SetTitle("Fisher discr.(C3D)");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(0.1,1.01*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();

  c->SaveAs("plots/c3d_Fisher_jet_VBF_alllength.pdf");  


}









void plot_showerlength_c3d(){

  TString VBF_cut = "VBF_parton_genjet[0]>=0 && VBF_parton_jets[0]>=0 && abs(genjet_eta[VBF_parton_genjet[0]])>1.6 && abs(genjet_eta[VBF_parton_genjet[0]])<2.9 && genjet_pt[VBF_parton_genjet[0]]>20 && cl3d_jet==VBF_parton_jets[0]";
  TString ZB_cut = "cl3d_jet>=0 && jets_pt[cl3d_jet]>20";

  TH1F* h_VBF_PU0_Fisher_jet = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","cl3d_showerlength",VBF_cut,50,0,50);

  TH1F* h_VBF_PU200_Fisher_jet = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","cl3d_showerlength",VBF_cut,50,0,50);

  TH1F* h_ZB_Fisher_jet = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","cl3d_showerlength",ZB_cut,50,0,50);

  
  vector<TH1F*> histo;
  histo.push_back(h_VBF_PU0_Fisher_jet);
  histo.push_back(h_VBF_PU200_Fisher_jet);
  histo.push_back(h_ZB_Fisher_jet);

  
  vector<TString> leg_entry;
  leg_entry.push_back("VBF PU=0");
  leg_entry.push_back("VBF PU=200");
  leg_entry.push_back("ZB PU=200");

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

  
  TLatex *texl = new TLatex(0.5,1.01*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();

  c->SaveAs("plots/c3d_showerlength.pdf");  


}







void plot_layer_short_c3d(){

  TString VBF_cut = "VBF_parton_genjet[0]>=0 && VBF_parton_jets[0]>=0 && abs(genjet_eta[VBF_parton_genjet[0]])>1.6 && abs(genjet_eta[VBF_parton_genjet[0]])<2.9 && genjet_pt[VBF_parton_genjet[0]]>20 && cl3d_jet==VBF_parton_jets[0] && cl3d_showerlength==1";
  TString ZB_cut = "cl3d_jet>=0 && jets_pt[cl3d_jet]>20 && cl3d_showerlength==1";

  TH1F* h_VBF_PU0_Fisher_jet = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","cl3d_firstlayer",VBF_cut,50,0,50);

  TH1F* h_VBF_PU200_Fisher_jet = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","cl3d_firstlayer",VBF_cut,50,0,50);

  TH1F* h_ZB_Fisher_jet = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","cl3d_firstlayer",ZB_cut,50,0,50);

  
  vector<TH1F*> histo;
  histo.push_back(h_VBF_PU0_Fisher_jet);
  histo.push_back(h_VBF_PU200_Fisher_jet);
  histo.push_back(h_ZB_Fisher_jet);

  
  vector<TString> leg_entry;
  leg_entry.push_back("VBF PU=0");
  leg_entry.push_back("VBF PU=200");
  leg_entry.push_back("ZB PU=200");

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

  histo = sort_histo(histo);

  histo[0]->GetXaxis()->SetTitle("First layer");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(0.5,1.01*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();

  c->SaveAs("plots/c3d_firstlayer_short.pdf");  


}








void plot_c3d_short_ptfraction(){

  TString VBF_cut = "VBF_parton_genjet[0]>=0 && VBF_parton_jets[0]>=0 && abs(genjet_eta[VBF_parton_genjet[0]])>1.6 && abs(genjet_eta[VBF_parton_genjet[0]])<2.9 && genjet_pt[VBF_parton_genjet[0]]>20 && cl3d_jet==VBF_parton_jets[0]";
  TString ZB_cut = "cl3d_jet>=0 && jets_pt[cl3d_jet]>20";

  TH1F* h_VBF_PU0_Fisher_jet_short = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","cl3d_pt/jets_pt[cl3d_jet]",VBF_cut + "&& cl3d_showerlength==1",100,0,1);

  TH1F* h_VBF_PU0_Fisher_jet = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","cl3d_pt/jets_pt[cl3d_jet]",VBF_cut + "&& cl3d_showerlength>1",100,0,1);


  TH1F* h_VBF_PU200_Fisher_jet_short = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","cl3d_pt/jets_pt[cl3d_jet]",VBF_cut + "&& cl3d_showerlength==1",100,0,1);

  TH1F* h_VBF_PU200_Fisher_jet = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","cl3d_pt/jets_pt[cl3d_jet]",VBF_cut + "&& cl3d_showerlength>1",100,0,1);


  TH1F* h_ZB_Fisher_jet_short = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","cl3d_pt/jets_pt[cl3d_jet]",ZB_cut + "&& cl3d_showerlength==1",100,0,1);


  TH1F* h_ZB_Fisher_jet = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","cl3d_pt/jets_pt[cl3d_jet]",ZB_cut + "&& cl3d_showerlength>1",100,0,1);




  
  vector<TH1F*> histo;
  histo.push_back(h_VBF_PU0_Fisher_jet_short);
  histo.push_back(h_VBF_PU0_Fisher_jet);
  histo.push_back(h_VBF_PU200_Fisher_jet_short);
  histo.push_back(h_VBF_PU200_Fisher_jet);
  histo.push_back(h_ZB_Fisher_jet_short);
  histo.push_back(h_ZB_Fisher_jet);

  
  vector<TString> leg_entry;
  leg_entry.push_back("VBF PU=0 short");
  leg_entry.push_back("VBF PU=0 long");
  leg_entry.push_back("VBF PU=200 short");
  leg_entry.push_back("VBF PU=200 long");
  leg_entry.push_back("ZB PU=200 short");
  leg_entry.push_back("ZB PU=200 long");

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

  histo = sort_histo(histo);

  histo[0]->GetXaxis()->SetTitle("Fisher discr.(C3D)");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(1e-3,2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(0.05,1.2*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();

  c->SaveAs("plots/c3d_short_ptfraction.pdf");  


}









void plot_Fisher_c3d(){

  TString VBF_cut = "VBF_parton_genjet[0]>=0 && VBF_parton_jets[0]>=0 && abs(genjet_eta[VBF_parton_genjet[0]])>1.6 && abs(genjet_eta[VBF_parton_genjet[0]])<2.9 && genjet_pt[VBF_parton_genjet[0]]>20 && cl3d_jet==VBF_parton_jets[0] && cl3d_showerlength>1";
  TString ZB_cut = "cl3d_jet>=0 && jets_pt[cl3d_jet]>20  && cl3d_showerlength>1";

  TH1F* h_VBF_PU0_Fisher_jet = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","cl3d_Fisher_jet",VBF_cut,100,-4,6);

  TH1F* h_VBF_PU200_Fisher_jet = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","cl3d_Fisher_jet",VBF_cut,100,-4,6);

  TH1F* h_ZB_Fisher_jet = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","cl3d_Fisher_jet",ZB_cut,100,-4,6);

  
  vector<TH1F*> histo;
  histo.push_back(h_VBF_PU0_Fisher_jet);
  histo.push_back(h_VBF_PU200_Fisher_jet);
  histo.push_back(h_ZB_Fisher_jet);

  
  vector<TString> leg_entry;
  leg_entry.push_back("VBF PU=0");
  leg_entry.push_back("VBF PU=200");
  leg_entry.push_back("ZB PU=200");

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

  histo = sort_histo(histo);

  histo[0]->GetXaxis()->SetTitle("Fisher discr.(C3D)");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(-3.95,1.01*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();

  c->SaveAs("plots/c3d_Fisher_jet_VBF.pdf");  


}







void plot_Fisher_c3d_c3d(){

  TString VBF_cut = "VBF_parton_genjet[0]>=0 && VBF_parton_jets[0]>=0 && abs(genjet_eta[VBF_parton_genjet[0]])>1.6 && abs(genjet_eta[VBF_parton_genjet[0]])<2.9 && genjet_pt[VBF_parton_genjet[0]]>20 && cl3d_jet==VBF_parton_jets[0] && cl3d_showerlength>1";
  TString ZB_cut = "cl3d_jet>=0 && jets_pt[cl3d_jet]>20  && cl3d_showerlength>1";

  TH1F* h_VBF_PU0_Fisher_jet = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","cl3d_Fisher_cl3d",VBF_cut,100,0,3);

  TH1F* h_VBF_PU200_Fisher_jet = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","cl3d_Fisher_cl3d",VBF_cut,100,0,3);

  TH1F* h_ZB_Fisher_jet = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","cl3d_Fisher_cl3d",ZB_cut,100,0,3);

  
  vector<TH1F*> histo;
  histo.push_back(h_VBF_PU0_Fisher_jet);
  histo.push_back(h_VBF_PU200_Fisher_jet);
  histo.push_back(h_ZB_Fisher_jet);

  
  vector<TString> leg_entry;
  leg_entry.push_back("VBF PU=0");
  leg_entry.push_back("VBF PU=200");
  leg_entry.push_back("ZB PU=200");

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

  histo = sort_histo(histo);

  histo[0]->GetXaxis()->SetTitle("Fisher discr.(C3D)");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(0.1,1.01*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();

  c->SaveAs("plots/c3d_Fisher_cl3d_VBF.pdf");  


}







void plot_layer5_fraction_c3d(){

  TString VBF_cut = "VBF_parton_genjet[0]>=0 && VBF_parton_jets[0]>=0 && abs(genjet_eta[VBF_parton_genjet[0]])>1.6 && abs(genjet_eta[VBF_parton_genjet[0]])<2.9 && genjet_pt[VBF_parton_genjet[0]]>20 && cl3d_jet==VBF_parton_jets[0]";
  TString ZB_cut = "cl3d_jet>=0 && jets_pt[cl3d_jet]>20";

  TH1F* h_VBF_PU0_Fisher_jet = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","layer_cl3d_energy_fraction[5]",VBF_cut,100,0,1);

  TH1F* h_VBF_PU200_Fisher_jet = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","layer_cl3d_energy_fraction[5]",VBF_cut,100,0,1);

  TH1F* h_ZB_Fisher_jet = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtupleJet","layer_cl3d_energy_fraction[5]",ZB_cut,100,0,1);

  
  vector<TH1F*> histo;
  histo.push_back(h_VBF_PU0_Fisher_jet);
  histo.push_back(h_VBF_PU200_Fisher_jet);
  histo.push_back(h_ZB_Fisher_jet);

  
  vector<TString> leg_entry;
  leg_entry.push_back("VBF PU=0");
  leg_entry.push_back("VBF PU=200");
  leg_entry.push_back("ZB PU=200");

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

  histo = sort_histo(histo);

  histo[0]->GetXaxis()->SetTitle("Layer 5 fraction");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(2e-4,2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(0.05,1.2*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();

  c->SaveAs("plots/layer5_fraction_c3d.pdf");  


}








void plot_ROC_Fisher_C3D(){

  TString file_sig_PU0 = "/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root";
  TString file_sig_PU200 = "/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root";
  TString file_bkg = "/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root";

  TString VBF_cut = "VBF_parton_genjet[0]>=0 && VBF_parton_jets[0]>=0 && abs(genjet_eta[VBF_parton_genjet[0]])>1.6 && abs(genjet_eta[VBF_parton_genjet[0]])<2.9 && genjet_pt[VBF_parton_genjet[0]]>20 && cl3d_jet==VBF_parton_jets[0]";
  TString ZB_cut = "cl3d_jet>=0 && jets_pt[cl3d_jet]>20";

  
  vector<TGraphErrors*> ROCs;
  vector<TString> leg_entry;
  
  ROCs.push_back(get_ROC_VBF_C3D(file_sig_PU0,file_bkg,VBF_cut,ZB_cut,"layer_cl3d_energy_fraction[5]",100,0,1,false));
  ROCs.push_back(get_ROC_VBF_C3D(file_sig_PU0,file_bkg,VBF_cut,ZB_cut,"cl3d_Fisher_jet",100,-5,5,true));
  ROCs.push_back(get_ROC_VBF_C3D(file_sig_PU0,file_bkg,VBF_cut,ZB_cut,"cl3d_Fisher_cl3d",100,0,2.5,false));

  ROCs.push_back(get_ROC_VBF_C3D(file_sig_PU200,file_bkg,VBF_cut,ZB_cut,"layer_cl3d_energy_fraction[5]",100,0,1,false));
  ROCs.push_back(get_ROC_VBF_C3D(file_sig_PU200,file_bkg,VBF_cut,ZB_cut,"cl3d_Fisher_jet",100,-5,5,true));
  ROCs.push_back(get_ROC_VBF_C3D(file_sig_PU200,file_bkg,VBF_cut,ZB_cut,"cl3d_Fisher_cl3d",100,0,2.5,false));



  leg_entry.push_back("Fraction layer #5 VBF PU=0");
  leg_entry.push_back("Jet Fisher discr. VBF PU=0");
  leg_entry.push_back("C3D Fisher discr. VBF PU=0");
  leg_entry.push_back("Fraction layer #5 VBF PU=200");
  leg_entry.push_back("Jet Fisher discr. VBF PU=200");
  leg_entry.push_back("C3D Fisher discr. VBF PU=200");

  
  TLegend* leg=new TLegend(0.2,0.6,0.5,0.85);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  for(unsigned int i=0;i<ROCs.size();i++){
    TGraphErrors* ROC = ROCs[i];
    ROC->SetLineWidth(2);
    ROC->SetLineColor(i+1);
    if(i>3)
      ROC->SetLineColor(i+2);     
    ROC->SetFillColor(0);
    leg->AddEntry(ROC,leg_entry[i]);
  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  c->SetGrid();
  //c->SetLogy();
  
  ROCs[0]->GetXaxis()->SetTitle("Signal eff.");
  ROCs[0]->GetYaxis()->SetTitle("Bkg eff.");
  ROCs[0]->GetYaxis()->SetTitleOffset(1.7);
  ROCs[0]->GetXaxis()->SetLimits(0.,1.);
  ROCs[0]->GetYaxis()->SetRangeUser(0.,1.);
  //ROCs[0]->GetXaxis()->SetLimits(0.5,1.);
  //ROCs[0]->GetYaxis()->SetRangeUser(1e-2,1.);
  ROCs[0]->SetTitle("");
  ROCs[0]->Draw("APL");
  for(unsigned int i=1;i<ROCs.size();i++)
    ROCs[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02,"CMS Simulation #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();

  
  c->SaveAs("plots/ROC_Fisher_C3D_VBF.pdf");  



}








void plot_ROC_Fisher_C3D_etabins(){

  TString file_sig_PU0 = "/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root";
  TString file_sig_PU200 = "/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root";
  TString file_bkg = "/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root";

  TString VBF_cut = "VBF_parton_genjet[0]>=0 && VBF_parton_jets[0]>=0 && abs(genjet_eta[VBF_parton_genjet[0]])>1.6 && abs(genjet_eta[VBF_parton_genjet[0]])<2.9 && genjet_pt[VBF_parton_genjet[0]]>20 && cl3d_jet==VBF_parton_jets[0]";
  TString ZB_cut = "cl3d_jet>=0 && jets_pt[cl3d_jet]>20";

  
  vector<TGraphErrors*> ROCs;
  vector<TString> leg_entry;
  
  ROCs.push_back(get_ROC_VBF_C3D(file_sig_PU0,file_bkg,VBF_cut + " && abs(cl3d_eta)>1.5 && abs(cl3d_eta)<1.6",ZB_cut + " && abs(cl3d_eta)>1.5 && abs(cl3d_eta)<1.6","layer_cl3d_energy_fraction[5]",100,0,1,false));
  ROCs.push_back(get_ROC_VBF_C3D(file_sig_PU0,file_bkg,VBF_cut + " && abs(cl3d_eta)>1.7 && abs(cl3d_eta)<1.8",ZB_cut + " && abs(cl3d_eta)>1.7 && abs(cl3d_eta)<1.8","layer_cl3d_energy_fraction[5]",100,0,1,false));
  ROCs.push_back(get_ROC_VBF_C3D(file_sig_PU0,file_bkg,VBF_cut + " && abs(cl3d_eta)>1.9 && abs(cl3d_eta)<2.0",ZB_cut + " && abs(cl3d_eta)>1.9 && abs(cl3d_eta)<2.0","layer_cl3d_energy_fraction[5]",100,0,1,false));
  ROCs.push_back(get_ROC_VBF_C3D(file_sig_PU0,file_bkg,VBF_cut + " && abs(cl3d_eta)>2.1 && abs(cl3d_eta)<2.2",ZB_cut + " && abs(cl3d_eta)>2.1 && abs(cl3d_eta)<2.2","layer_cl3d_energy_fraction[5]",100,0,1,false));
  ROCs.push_back(get_ROC_VBF_C3D(file_sig_PU0,file_bkg,VBF_cut + " && abs(cl3d_eta)>2.3 && abs(cl3d_eta)<2.4",ZB_cut + " && abs(cl3d_eta)>2.3 && abs(cl3d_eta)<2.4","layer_cl3d_energy_fraction[5]",100,0,1,false));
  ROCs.push_back(get_ROC_VBF_C3D(file_sig_PU0,file_bkg,VBF_cut + " && abs(cl3d_eta)>2.5 && abs(cl3d_eta)<2.6",ZB_cut + " && abs(cl3d_eta)>2.5 && abs(cl3d_eta)<2.6","layer_cl3d_energy_fraction[5]",100,0,1,false));
  ROCs.push_back(get_ROC_VBF_C3D(file_sig_PU0,file_bkg,VBF_cut + " && abs(cl3d_eta)>2.7 && abs(cl3d_eta)<2.8",ZB_cut + " && abs(cl3d_eta)>2.7 && abs(cl3d_eta)<2.8","layer_cl3d_energy_fraction[5]",100,0,1,false));
  ROCs.push_back(get_ROC_VBF_C3D(file_sig_PU0,file_bkg,VBF_cut + " && abs(cl3d_eta)>2.8 && abs(cl3d_eta)<2.9",ZB_cut + " && abs(cl3d_eta)>2.8 && abs(cl3d_eta)<2.9","layer_cl3d_energy_fraction[5]",100,0,1,false));
  ROCs.push_back(get_ROC_VBF_C3D(file_sig_PU0,file_bkg,VBF_cut + " && abs(cl3d_eta)>2.9 && abs(cl3d_eta)<3.0",ZB_cut + " && abs(cl3d_eta)>2.9 && abs(cl3d_eta)<3.0","layer_cl3d_energy_fraction[5]",100,0,1,false));



  leg_entry.push_back("1.5<|#eta|<1.6");
  leg_entry.push_back("1.7<|#eta|<1.8");
  leg_entry.push_back("1.9<|#eta|<2.0");
  leg_entry.push_back("2.1<|#eta|<2.2");
  leg_entry.push_back("2.3<|#eta|<2.4");
  leg_entry.push_back("2.5<|#eta|<2.6");
  leg_entry.push_back("2.7<|#eta|<2.8");
  leg_entry.push_back("2.8<|#eta|<2.9");
  leg_entry.push_back("2.9<|#eta|<3.0");


  
  TLegend* leg=new TLegend(0.2,0.6,0.5,0.85);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  for(unsigned int i=0;i<ROCs.size();i++){
    TGraphErrors* ROC = ROCs[i];
    ROC->SetLineWidth(2);
    ROC->SetLineColor(i+1);
    if(i>3)
      ROC->SetLineColor(i+2);  
    if(i>7)
      ROC->SetLineColor(i+3);  
    ROC->SetFillColor(0);
    leg->AddEntry(ROC,leg_entry[i]);
  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  c->SetGrid();
  //c->SetLogy();
  
  ROCs[0]->GetXaxis()->SetTitle("Signal eff.");
  ROCs[0]->GetYaxis()->SetTitle("Bkg eff.");
  ROCs[0]->GetYaxis()->SetTitleOffset(1.7);
  ROCs[0]->GetXaxis()->SetLimits(0.,1.);
  ROCs[0]->GetYaxis()->SetRangeUser(0.,1.);
  //ROCs[0]->GetXaxis()->SetLimits(0.5,1.);
  //ROCs[0]->GetYaxis()->SetRangeUser(1e-2,1.);
  ROCs[0]->SetTitle("");
  ROCs[0]->Draw("APL");
  for(unsigned int i=1;i<ROCs.size();i++)
    ROCs[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02,"CMS Simulation #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();

  
  c->SaveAs("plots/ROC_Fisher_C3D_VBF_etabins.pdf");  



}








void plot_ROC_Fisher_C3D_ptbins(){

  TString file_sig_PU0 = "/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root";
  TString file_sig_PU200 = "/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root";
  TString file_bkg = "/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root";

  TString VBF_cut = "VBF_parton_genjet[0]>=0 && VBF_parton_jets[0]>=0 && abs(genjet_eta[VBF_parton_genjet[0]])>1.6 && abs(genjet_eta[VBF_parton_genjet[0]])<2.9 && genjet_pt[VBF_parton_genjet[0]]>20 && cl3d_jet==VBF_parton_jets[0]";
  TString ZB_cut = "cl3d_jet>=0 && jets_pt[cl3d_jet]>20";

  
  vector<TGraphErrors*> ROCs;
  vector<TString> leg_entry;
  
  ROCs.push_back(get_ROC_VBF_C3D(file_sig_PU0,file_bkg,VBF_cut + " && cl3d_pt<2",ZB_cut + " && cl3d_pt<2","layer_cl3d_energy_fraction[5]",100,0,1,false));
  ROCs.push_back(get_ROC_VBF_C3D(file_sig_PU0,file_bkg,VBF_cut + " && cl3d_pt>2 && cl3d_pt<4",ZB_cut + " && cl3d_pt>2 && cl3d_pt<4","layer_cl3d_energy_fraction[5]",100,0,1,false));
  ROCs.push_back(get_ROC_VBF_C3D(file_sig_PU0,file_bkg,VBF_cut + " && cl3d_pt>4 && cl3d_pt<6",ZB_cut + " && cl3d_pt>4 && cl3d_pt<6","layer_cl3d_energy_fraction[5]",100,0,1,false));
  ROCs.push_back(get_ROC_VBF_C3D(file_sig_PU0,file_bkg,VBF_cut + " && cl3d_pt>6 && cl3d_pt<8",ZB_cut + " && cl3d_pt>6 && cl3d_pt<8","layer_cl3d_energy_fraction[5]",100,0,1,false));
  ROCs.push_back(get_ROC_VBF_C3D(file_sig_PU0,file_bkg,VBF_cut + " && cl3d_pt>8 && cl3d_pt<10",ZB_cut + " && cl3d_pt>8 && cl3d_pt<10","layer_cl3d_energy_fraction[5]",100,0,1,false));
  ROCs.push_back(get_ROC_VBF_C3D(file_sig_PU0,file_bkg,VBF_cut + " && cl3d_pt>10 && cl3d_pt<15",ZB_cut + " && cl3d_pt>10 && cl3d_pt<15","layer_cl3d_energy_fraction[5]",100,0,1,false));
  ROCs.push_back(get_ROC_VBF_C3D(file_sig_PU0,file_bkg,VBF_cut + " && cl3d_pt>15 && cl3d_pt<20",ZB_cut + " && cl3d_pt>15 && cl3d_pt<20","layer_cl3d_energy_fraction[5]",100,0,1,false));
  ROCs.push_back(get_ROC_VBF_C3D(file_sig_PU0,file_bkg,VBF_cut + " && cl3d_pt>20 && cl3d_pt<30",ZB_cut + " && cl3d_pt>20 && cl3d_pt<30","layer_cl3d_energy_fraction[5]",100,0,1,false));
  ROCs.push_back(get_ROC_VBF_C3D(file_sig_PU0,file_bkg,VBF_cut + " && cl3d_pt>30",ZB_cut + " && cl3d_pt>30","layer_cl3d_energy_fraction[5]",100,0,1,false));


  leg_entry.push_back("p_{T}<2 GeV");
  leg_entry.push_back("2<p_{T}<4 GeV");
  leg_entry.push_back("4<p_{T}<6 GeV");
  leg_entry.push_back("6<p_{T}<8 GeV");
  leg_entry.push_back("8<p_{T}<10 GeV");
  leg_entry.push_back("10<p_{T}<15 GeV");
  leg_entry.push_back("15<p_{T}<20 GeV");
  leg_entry.push_back("20<p_{T}<30 GeV");
  leg_entry.push_back("p_{T}>30 GeV");
  
  TLegend* leg=new TLegend(0.2,0.6,0.5,0.85);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  for(unsigned int i=0;i<ROCs.size();i++){
    TGraphErrors* ROC = ROCs[i];
    ROC->SetLineWidth(2);
    ROC->SetLineColor(i+1);
    if(i>3)
      ROC->SetLineColor(i+2);  
    if(i>7)
      ROC->SetLineColor(i+3);  
    ROC->SetFillColor(0);
    leg->AddEntry(ROC,leg_entry[i]);
  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  c->SetGrid();
  //c->SetLogy();
  
  ROCs[0]->GetXaxis()->SetTitle("Signal eff.");
  ROCs[0]->GetYaxis()->SetTitle("Bkg eff.");
  ROCs[0]->GetYaxis()->SetTitleOffset(1.7);
  ROCs[0]->GetXaxis()->SetLimits(0.,1.);
  ROCs[0]->GetYaxis()->SetRangeUser(0.,1.);
  //ROCs[0]->GetXaxis()->SetLimits(0.5,1.);
  //ROCs[0]->GetYaxis()->SetRangeUser(1e-2,1.);
  ROCs[0]->SetTitle("");
  ROCs[0]->Draw("APL");
  for(unsigned int i=1;i<ROCs.size();i++)
    ROCs[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02,"CMS Simulation #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();

  
  c->SaveAs("plots/ROC_Fisher_C3D_VBF_ptbins.pdf");  



}


