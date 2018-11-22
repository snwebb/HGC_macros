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




void write_layer_jets_energy_fraction_pt_quantiles(TString process, int PU){

  TString VBF_sample = "/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1*.root";
  TString tau_sample_PU200 = "/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1*.root";
  TString tau_sample_PU0 = "/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root";
  TString ZB_sample = "/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1*.root";

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

  int nlayers = 52;

  TGraphErrors gr(nbins);
  vector<TGraphErrors> gr_quant(nq,gr);
  vector<vector<TGraphErrors> > gr_vec(nlayers,gr_quant);

  for(int layer=0;layer<nlayers;layer++){

    cout<<"layer="<<layer<<endl;

    TH2F* h_2D = single_plot2D(sample,"HGCalTriggerNtupleJet","jets_pt"+index,Form("layer_jets_energy_fraction[%i]",layer)+index,cut,nbins,0,200,10000,0,1);
    
    for(unsigned int pT_bin=1; pT_bin<=nbins; pT_bin++){

      TH1D* h_pT = h_2D->ProjectionY("h_pT",pT_bin,pT_bin);   
            
      double x=h_2D->GetXaxis()->GetBinCenter(pT_bin);
      cout<<"pT="<<x<<endl;
      double xerr=0.5*h_2D->GetXaxis()->GetBinWidth(pT_bin);

      h_pT->GetQuantiles(nq,yq,xq);
      for(int iq=0;iq<nq;iq++){
	gr_vec[layer][iq].SetPoint(pT_bin-1,x,yq[iq]);
	gr_vec[layer][iq].SetPointError(pT_bin-1,xerr,0);
      }

      delete h_pT;

    }

    delete h_2D;

  }



  TFile* f_new = TFile::Open("layer_jets_energy_fraction_pt_quantiles_"+process+Form("_PU%i",PU)+".root","RECREATE");

  for(int layer=0;layer<nlayers;layer++){
    for(unsigned int iq=0; iq<nq; iq++){
      gr_vec[layer][iq].Write(Form(process+"_fraction_layer%i_quant%i",layer,iq));
    }
  }

  f_new->Close();


}






void write_layer_cl3d_energy_fraction_pt_quantiles_tau(int PU){

  TString tau_sample_PU200 = "/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1*.root";
  TString tau_sample_PU0 = "/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root";

  TString tau_cut = "gentau_jets>=0 && abs(gentau_vis_eta)>1.6 && abs(gentau_vis_eta)<2.9 && gentau_vis_pt>20 && gentau_decayMode>=0 && gentau_decayMode<=5";
  
  TString tau_index = "[jets_cl3d[gentau_jets]]";


  TString sample;
  TString cut;
  TString index;
  
  if(PU==0)
    sample = tau_sample_PU0;
  else
    sample = tau_sample_PU200;

  cut = tau_cut;
  index = tau_index;

  int nbins = 20;
  int nq = 100;
  double xq[nq];
  double yq[nq];
  for(int i=0;i<nq;i++) xq[i]=float(i+1)/nq;

  int nlayers = 52;

  TGraphErrors gr(nbins);
  vector<TGraphErrors> gr_quant(nq,gr);
  vector<vector<TGraphErrors> > gr_vec(nlayers,gr_quant);

  for(int layer=0;layer<nlayers;layer++){

    cout<<"layer="<<layer<<endl;

    TH2F* h_2D = single_plot2D(sample,"HGCalTriggerNtupleJet","cl3d_pt"+index,Form("layer_cl3d_energy_fraction[%i]",layer)+index,cut,nbins,0,200,10000,0,1);
    
    for(unsigned int pT_bin=1; pT_bin<=nbins; pT_bin++){

      TH1D* h_pT = h_2D->ProjectionY("h_pT",pT_bin,pT_bin);   
            
      double x=h_2D->GetXaxis()->GetBinCenter(pT_bin);
      cout<<"pT="<<x<<endl;
      double xerr=0.5*h_2D->GetXaxis()->GetBinWidth(pT_bin);

      h_pT->GetQuantiles(nq,yq,xq);
      for(int iq=0;iq<nq;iq++){
	gr_vec[layer][iq].SetPoint(pT_bin-1,x,yq[iq]);
	gr_vec[layer][iq].SetPointError(pT_bin-1,xerr,0);
      }

      delete h_pT;

    }

    delete h_2D;

  }



  TFile* f_new = TFile::Open(Form("layer_cl3d_energy_fraction_pt_quantiles_tau_PU%i.root",PU),"RECREATE");

  for(int layer=0;layer<nlayers;layer++){
    for(unsigned int iq=0; iq<nq; iq++){
      gr_vec[layer][iq].Write(Form("tau_fraction_layer%i_quant%i",layer,iq));
    }
  }

  f_new->Close();


}








void plot_layer_fractions_VBF_95eff(){

  TFile* f = TFile::Open("layer_jets_energy_fraction_pt_quantiles_VBF.root");

  vector<TString> gr;
  gr.push_back("VBF_fraction_layer40_quant94");
  gr.push_back("VBF_fraction_layer30_quant94");
  gr.push_back("VBF_fraction_layer20_quant94");
  gr.push_back("VBF_fraction_layer15_quant94");
  gr.push_back("VBF_fraction_layer12_quant94");
  gr.push_back("VBF_fraction_layer10_quant94");
  gr.push_back("VBF_fraction_layer7_quant94");
  gr.push_back("VBF_fraction_layer5_quant94");
  gr.push_back("VBF_fraction_layer3_quant94");
  gr.push_back("VBF_fraction_layer1_quant94");

  vector<TString> leg_entry;
  leg_entry.push_back("Layer #40");
  leg_entry.push_back("Layer #30");
  leg_entry.push_back("Layer #20");
  leg_entry.push_back("Layer #15");
  leg_entry.push_back("Layer #12");
  leg_entry.push_back("Layer #10");
  leg_entry.push_back("Layer #7");
  leg_entry.push_back("Layer #5");
  leg_entry.push_back("Layer #3");
  leg_entry.push_back("Layer #1");
  
  TLegend* leg=new TLegend(0.6,0.4,0.8,0.85);
  leg->SetHeader("#bf{95% eff.}");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  vector<TGraphErrors*> graphs;

  for(unsigned int i=0;i<gr.size();i++){
    
    TGraphErrors* graph = (TGraphErrors*)f->Get(gr[i]);
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
  graphs[0]->GetYaxis()->SetTitle("Cut on energy fraction");
  graphs[0]->GetYaxis()->SetTitleOffset(1.7);
  graphs[0]->GetXaxis()->SetLimits(0,200.);
  graphs[0]->GetYaxis()->SetRangeUser(0,1.05);
  graphs[0]->SetTitle("");
  graphs[0]->Draw();
  
  for(unsigned int i=1;i<graphs.size();i++)
    graphs[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(2.,1.07,"CMS Simulation Preliminary, VBF H#rightarrow inv. #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.029);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/layer_fractions_VBF_95eff.pdf");  
  f->Close();

}
  





void plot_layer_fractions_tau_95eff(){

  TFile* f = TFile::Open("layer_jets_energy_fraction_pt_quantiles_tau.root");

  vector<TString> gr;
  gr.push_back("tau_fraction_layer40_quant94");
  gr.push_back("tau_fraction_layer30_quant94");
  gr.push_back("tau_fraction_layer20_quant94");
  gr.push_back("tau_fraction_layer15_quant94");
  gr.push_back("tau_fraction_layer12_quant94");
  gr.push_back("tau_fraction_layer10_quant94");
  gr.push_back("tau_fraction_layer7_quant94");
  gr.push_back("tau_fraction_layer5_quant94");
  gr.push_back("tau_fraction_layer3_quant94");
  gr.push_back("tau_fraction_layer1_quant94");

  vector<TString> leg_entry;
  leg_entry.push_back("Layer #40");
  leg_entry.push_back("Layer #30");
  leg_entry.push_back("Layer #20");
  leg_entry.push_back("Layer #15");
  leg_entry.push_back("Layer #12");
  leg_entry.push_back("Layer #10");
  leg_entry.push_back("Layer #7");
  leg_entry.push_back("Layer #5");
  leg_entry.push_back("Layer #3");
  leg_entry.push_back("Layer #1");
  
  TLegend* leg=new TLegend(0.6,0.4,0.8,0.85);
  leg->SetHeader("#bf{95% eff.}");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  vector<TGraphErrors*> graphs;

  for(unsigned int i=0;i<gr.size();i++){
    
    TGraphErrors* graph = (TGraphErrors*)f->Get(gr[i]);
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
  graphs[0]->GetYaxis()->SetTitle("Cut on energy fraction");
  graphs[0]->GetYaxis()->SetTitleOffset(1.7);
  graphs[0]->GetXaxis()->SetLimits(0,200.);
  graphs[0]->GetYaxis()->SetRangeUser(0,1.05);
  graphs[0]->SetTitle("");
  graphs[0]->Draw();
  
  for(unsigned int i=1;i<graphs.size();i++)
    graphs[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(2.,1.07,"CMS Simulation Preliminary, H#rightarrow#tau#tau #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.029);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/layer_fractions_tau_95eff.pdf");  
  f->Close();

}
  








void plot_layer_fractions_ZB_95eff(){

  TFile* f = TFile::Open("layer_jets_energy_fraction_pt_quantiles_ZB.root");

  vector<TString> gr;
  gr.push_back("ZB_fraction_layer40_quant94");
  gr.push_back("ZB_fraction_layer30_quant94");
  gr.push_back("ZB_fraction_layer20_quant94");
  gr.push_back("ZB_fraction_layer15_quant94");
  gr.push_back("ZB_fraction_layer12_quant94");
  gr.push_back("ZB_fraction_layer10_quant94");
  gr.push_back("ZB_fraction_layer7_quant94");
  gr.push_back("ZB_fraction_layer5_quant94");
  gr.push_back("ZB_fraction_layer3_quant94");
  gr.push_back("ZB_fraction_layer1_quant94");

  vector<TString> leg_entry;
  leg_entry.push_back("Layer #40");
  leg_entry.push_back("Layer #30");
  leg_entry.push_back("Layer #20");
  leg_entry.push_back("Layer #15");
  leg_entry.push_back("Layer #12");
  leg_entry.push_back("Layer #10");
  leg_entry.push_back("Layer #7");
  leg_entry.push_back("Layer #5");
  leg_entry.push_back("Layer #3");
  leg_entry.push_back("Layer #1");
  
  TLegend* leg=new TLegend(0.6,0.4,0.8,0.85);
  leg->SetHeader("#bf{95% eff.}");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  vector<TGraphErrors*> graphs;

  for(unsigned int i=0;i<gr.size();i++){
    
    TGraphErrors* graph = (TGraphErrors*)f->Get(gr[i]);
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
  graphs[0]->GetYaxis()->SetTitle("Cut on energy fraction");
  graphs[0]->GetYaxis()->SetTitleOffset(1.7);
  graphs[0]->GetXaxis()->SetLimits(0,200.);
  graphs[0]->GetYaxis()->SetRangeUser(0,1.05);
  graphs[0]->SetTitle("");
  graphs[0]->Draw();
  
  for(unsigned int i=1;i<graphs.size();i++)
    graphs[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(2.,1.07,"CMS Simulation Preliminary, Neutrino Gun #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.029);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/layer_fractions_ZB_95eff.pdf");  
  f->Close();

}
  








void plot_layer_fractions_compar_95eff(){

  TFile* f_VBF = TFile::Open("layer_jets_energy_fraction_pt_quantiles_VBF.root");
  TFile* f_tau = TFile::Open("layer_jets_energy_fraction_pt_quantiles_tau.root");
  TFile* f_ZB = TFile::Open("layer_jets_energy_fraction_pt_quantiles_ZB.root");

  vector<TString> gr;
  gr.push_back("VBF_fraction_layer15_quant94");
  gr.push_back("tau_fraction_layer15_quant94");
  gr.push_back("ZB_fraction_layer15_quant94");
  gr.push_back("VBF_fraction_layer10_quant94");
  gr.push_back("tau_fraction_layer10_quant94");
  gr.push_back("ZB_fraction_layer10_quant94");
  gr.push_back("VBF_fraction_layer5_quant94");
  gr.push_back("tau_fraction_layer5_quant94");
  gr.push_back("ZB_fraction_layer5_quant94");
  gr.push_back("VBF_fraction_layer1_quant94");
  gr.push_back("tau_fraction_layer1_quant94");
  gr.push_back("ZB_fraction_layer1_quant94");

  vector<TString> leg_entry;
  leg_entry.push_back("VBF Layer #15");
  leg_entry.push_back("#tau Layer #15");
  leg_entry.push_back("ZB Layer #15");
  leg_entry.push_back("VBF Layer #10");
  leg_entry.push_back("#tau Layer #10");
  leg_entry.push_back("ZB Layer #10");
  leg_entry.push_back("VBF Layer #5");
  leg_entry.push_back("#tau Layer #5");
  leg_entry.push_back("ZB Layer #5");
  leg_entry.push_back("VBF Layer #1");
  leg_entry.push_back("#tau Layer #1");
  leg_entry.push_back("ZB Layer #1");

  
  TLegend* leg=new TLegend(0.6,0.4,0.8,0.85);
  leg->SetHeader("#bf{95% eff.}");
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
  graphs[0]->GetYaxis()->SetTitle("Cut on energy fraction");
  graphs[0]->GetYaxis()->SetTitleOffset(1.7);
  graphs[0]->GetXaxis()->SetLimits(0,200.);
  graphs[0]->GetYaxis()->SetRangeUser(0,1.05);
  graphs[0]->SetTitle("");
  graphs[0]->Draw();
  
  for(unsigned int i=1;i<graphs.size();i++)
    graphs[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(2.,1.07,"CMS Simulation Preliminary, #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.029);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/layer_fractions_compar_95eff.pdf");  
  f_VBF->Close();
  f_tau->Close();
  f_ZB->Close();

}
  







void plot_layer_fractions_compar_layer5(){

  TFile* f_VBF = TFile::Open("layer_jets_energy_fraction_pt_quantiles_VBF.root");
  TFile* f_tau = TFile::Open("layer_jets_energy_fraction_pt_quantiles_tau.root");
  TFile* f_ZB = TFile::Open("layer_jets_energy_fraction_pt_quantiles_ZB.root");

  vector<TString> gr;
  gr.push_back("VBF_fraction_layer5_quant94");
  gr.push_back("tau_fraction_layer5_quant94");
  gr.push_back("ZB_fraction_layer5_quant94");
  /*gr.push_back("VBF_fraction_layer5_quant74");
  gr.push_back("tau_fraction_layer5_quant74");
  gr.push_back("ZB_fraction_layer5_quant74");*/
  gr.push_back("VBF_fraction_layer5_quant49");
  gr.push_back("tau_fraction_layer5_quant49");
  gr.push_back("ZB_fraction_layer5_quant49");

  vector<TString> leg_entry;
  leg_entry.push_back("VBF 95%");
  leg_entry.push_back("#tau 95%");
  leg_entry.push_back("ZB 95%");
  /*leg_entry.push_back("VBF 75%");
  leg_entry.push_back("#tau 75%");
  leg_entry.push_back("ZB 75%");*/
  leg_entry.push_back("VBF 50%");
  leg_entry.push_back("#tau 50%");
  leg_entry.push_back("ZB 50%");
  
  TLegend* leg=new TLegend(0.6,0.4,0.8,0.85);
  leg->SetHeader("Layer #5");
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
  graphs[0]->GetYaxis()->SetTitle("Cut on energy fraction");
  graphs[0]->GetYaxis()->SetTitleOffset(1.7);
  graphs[0]->GetXaxis()->SetLimits(0,200.);
  graphs[0]->GetYaxis()->SetRangeUser(0,1.05);
  graphs[0]->SetTitle("");
  graphs[0]->Draw();
  
  for(unsigned int i=1;i<graphs.size();i++)
    graphs[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(2.,1.07,"CMS Simulation Preliminary, #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.029);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/layer_fractions_compar_layer5.pdf");  
  f_VBF->Close();
  f_tau->Close();
  f_ZB->Close();

}
  










void plot_turnons_L1SingleJet_dRNNC2D_PU200_layer5_95eff(int L1pt){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  //double x[18]={0,40,60,70,80,90,100,110,120,130,140,160,180,200,250,300,400,500};
  //int nbins=17;

  double x[16]={0,25,35,40,45,50,55,60,65,75,80,90,100,120,150,300};
  int nbins=15;


  TH1F* h_PU200_denom_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_cal_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D->Divide(h_PU200_cal_dRNNC2D,h_PU200_denom_dRNNC2D);

  TH1F* h_PU200_cal_dRNNC2D_cut = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i && layer_jets_energy_fraction[5][VBF_parton_jets]<(1.38718e+01/(jets_pt[VBF_parton_jets]+2.85485e+01)+7.04647e-02)",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D_cut = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D_cut->Divide(h_PU200_cal_dRNNC2D_cut,h_PU200_denom_dRNNC2D);


  TH1F* h_PU200_cal_dRNNC2D_cut_relaxed = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i && (layer_jets_energy_fraction[5][VBF_parton_jets]<(1.38718e+01/(jets_pt[VBF_parton_jets]+2.85485e+01)+7.04647e-02) || 1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)>60)",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D_cut_relaxed = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D_cut_relaxed->Divide(h_PU200_cal_dRNNC2D_cut_relaxed,h_PU200_denom_dRNNC2D);

  TH1F* h_PU200_cal_dRNNC2D_cut_0p2 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i && layer_jets_energy_fraction[5][VBF_parton_jets]<0.2",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D_cut_0p2 = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D_cut_0p2->Divide(h_PU200_cal_dRNNC2D_cut_0p2,h_PU200_denom_dRNNC2D);

  TH1F* h_PU200_cal_dRNNC2D_cut_0p2_relaxed = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i && (layer_jets_energy_fraction[5][VBF_parton_jets]<0.2  || 1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)>60)",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D_cut_0p2_relaxed = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D_cut_0p2_relaxed->Divide(h_PU200_cal_dRNNC2D_cut_0p2_relaxed,h_PU200_denom_dRNNC2D);


  vector<TGraphAsymmErrors*> turnons;
  turnons.push_back(gr_PU200_cal_dRNNC2D);
  //turnons.push_back(gr_PU200_cal_dRNNC2D_cut);
  turnons.push_back(gr_PU200_cal_dRNNC2D_cut_relaxed);
  //turnons.push_back(gr_PU200_cal_dRNNC2D_cut_0p2);
  turnons.push_back(gr_PU200_cal_dRNNC2D_cut_0p2_relaxed);


  vector<TString> leg_entry;
  leg_entry.push_back("Default");
  leg_entry.push_back("95% cut layer#5");
  //leg_entry.push_back("95% cut layer#5 relaxed");
  leg_entry.push_back("0.2 cut");
  //leg_entry.push_back("0.2 cut relaxed");



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


  c->SaveAs(Form("plots/turnons_L1SingleJet%i_dRNNC2D_PU200_layer5_95eff.pdf",L1pt));  


}








void plot_turnons_L1SingleJet_dRNNC2D_PU200_layer5_compar(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  //double x[18]={0,40,60,70,80,90,100,110,120,130,140,160,180,200,250,300,400,500};
  //int nbins=17;

  double x[16]={0,25,35,40,45,50,55,60,65,75,80,90,100,120,150,300};
  int nbins=15;


  TH1F* h_PU200_denom_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut,nbins,x);
  TH1F* h_PU200_cal_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i",50),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D->Divide(h_PU200_cal_dRNNC2D,h_PU200_denom_dRNNC2D);


  TH1F* h_PU200_cal_dRNNC2D_cut_relaxed = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i && (layer_jets_energy_fraction[5][VBF_parton_jets]<(1.38718e+01/(jets_pt[VBF_parton_jets]+2.85485e+01)+7.04647e-02) || 1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)>60)",49),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D_cut_relaxed = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D_cut_relaxed->Divide(h_PU200_cal_dRNNC2D_cut_relaxed,h_PU200_denom_dRNNC2D);

  TH1F* h_PU200_cal_dRNNC2D_cut_0p2_relaxed = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]",cut+Form("&& (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) >%i && (layer_jets_energy_fraction[5][VBF_parton_jets]<0.2  || 1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)>60)",45),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D_cut_0p2_relaxed = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D_cut_0p2_relaxed->Divide(h_PU200_cal_dRNNC2D_cut_0p2_relaxed,h_PU200_denom_dRNNC2D);


  vector<TGraphAsymmErrors*> turnons;
  turnons.push_back(gr_PU200_cal_dRNNC2D);
  turnons.push_back(gr_PU200_cal_dRNNC2D_cut_relaxed);
  turnons.push_back(gr_PU200_cal_dRNNC2D_cut_0p2_relaxed);


  vector<TString> leg_entry;
  leg_entry.push_back("Default SingleJet50");
  leg_entry.push_back("95% cut SingleJet49");
  leg_entry.push_back("0.2 cut SingleJet45");
  leg_entry.push_back("0.2 cut relaxed");



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


  c->SaveAs("plots/turnons_L1SingleJet_dRNNC2D_PU200_layer5_95eff_compar.pdf");  


}









void plot_turnons_L1SingleTau_dRNNC2D_PU200_layer5_95eff(int L1pt){

  TString cut = "gentau_jets>=0 && abs(gentau_vis_eta)>1.6 && abs(gentau_vis_eta)<2.9 && gentau_vis_pt>0 && gentau_decayMode>=0 && gentau_decayMode<=5";
  TString cut_Phase1 = "abs(tauEta)>1.6 && abs(tauEta)<3.0 && tau_genindex==5";

  double x[23]={0,10,20,25,30,33,35,37,39,40,41,43,45,47,50,55,60,65,75,80,90,100,150};
  int nbins=22;

  double x2[13]={0,20,25,30,35,38,40,42,45,50,60,80,100};
  int nbins2=12;



  TH1F* h_PU200_denom_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","gentau_vis_pt",cut,nbins,x);
  TH1F* h_PU200_cal_dRNNC2D = single_plot("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","gentau_vis_pt",cut+Form("&& 1.1/(0.93-1/(0.2*max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20)+1e-3*pow(max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20),2))) * (jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets]) >%i",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D->Divide(h_PU200_cal_dRNNC2D,h_PU200_denom_dRNNC2D);



  TH1F* h_PU200_cal_dRNNC2D_cut = single_plot("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","gentau_vis_pt",cut+Form("&& 1.1/(0.93-1/(0.2*max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20)+1e-3*pow(max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20),2))) * (jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets]) >%i && layer_jets_energy_fraction[5][gentau_jets]<(2.23755e+01/(jets_pt[gentau_jets]+5.02328e+01)+2.04305e-05)",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D_cut = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D_cut->Divide(h_PU200_cal_dRNNC2D_cut,h_PU200_denom_dRNNC2D);


  TH1F* h_PU200_cal_dRNNC2D_cut_relaxed = single_plot("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","gentau_vis_pt",cut+Form("&& 1.1/(0.93-1/(0.2*max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20)+1e-3*pow(max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20),2))) * (jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets]) >%i && (layer_jets_energy_fraction[5][gentau_jets]<(2.23755e+01/(jets_pt[gentau_jets]+5.02328e+01)+2.04305e-05) || jets_pt[gentau_jets]>45)",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D_cut_relaxed = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D_cut_relaxed->Divide(h_PU200_cal_dRNNC2D_cut_relaxed,h_PU200_denom_dRNNC2D);


  TH1F* h_PU200_cal_dRNNC2D_cut_0p2 = single_plot("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","gentau_vis_pt",cut+Form("&& 1.1/(0.93-1/(0.2*max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20)+1e-3*pow(max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20),2))) * (jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets]) >%i && (layer_jets_energy_fraction[5][gentau_jets]<0.2)",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D_cut_0p2 = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D_cut_0p2->Divide(h_PU200_cal_dRNNC2D_cut_0p2,h_PU200_denom_dRNNC2D);

  TH1F* h_PU200_cal_dRNNC2D_cut_0p2_relaxed = single_plot("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","gentau_vis_pt",cut+Form("&& 1.1/(0.93-1/(0.2*max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20)+1e-3*pow(max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20),2))) * (jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets]) >%i && (layer_jets_energy_fraction[5][gentau_jets]<0.2 || jets_pt[gentau_jets]>45)",L1pt),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D_cut_0p2_relaxed = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D_cut_0p2_relaxed->Divide(h_PU200_cal_dRNNC2D_cut_0p2_relaxed,h_PU200_denom_dRNNC2D);


  vector<TGraphAsymmErrors*> turnons;
  turnons.push_back(gr_PU200_cal_dRNNC2D);
  turnons.push_back(gr_PU200_cal_dRNNC2D_cut);
  turnons.push_back(gr_PU200_cal_dRNNC2D_cut_relaxed);
  turnons.push_back(gr_PU200_cal_dRNNC2D_cut_0p2);
  turnons.push_back(gr_PU200_cal_dRNNC2D_cut_0p2_relaxed);

  vector<TString> leg_entry;
  leg_entry.push_back("Default");
  leg_entry.push_back("95% cut layer#5");
  //leg_entry.push_back("95% cut layer#5 relaxed");
  leg_entry.push_back("Fraction layer#5 <0.2");
  //leg_entry.push_back("Fraction layer#5 <0.2 relaxed");


  TLegend* leg=new TLegend(0.4,0.12,0.85,0.55);
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


  TLatex *texl = new TLatex(1.57,1.01,"CMS Simulation, H#rightarrow#tau#tau #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");
  gPad->SetTicks();


  c->SaveAs(Form("plots/turnons_L1SingleTau%i_dRNNC2D_PU200_layer5_95eff.pdf",L1pt));  


}











void plot_turnons_L1SingleTau_dRNNC2D_PU200_layer5_compar(){

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



  TH1F* h_PU200_cal_dRNNC2D_cut_relaxed = single_plot("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","gentau_vis_pt",cut+Form("&& 1.1/(0.93-1/(0.2*max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20)+1e-3*pow(max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20),2))) * (jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets]) >%i && (layer_jets_energy_fraction[5][gentau_jets]<(2.23755e+01/(jets_pt[gentau_jets]+5.02328e+01)+2.04305e-05) || jets_pt[gentau_jets]>45)",40),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D_cut_relaxed = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D_cut_relaxed->Divide(h_PU200_cal_dRNNC2D_cut_relaxed,h_PU200_denom_dRNNC2D);



  TH1F* h_PU200_cal_dRNNC2D_cut_0p2_relaxed = single_plot("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","gentau_vis_pt",cut+Form("&& 1.1/(0.93-1/(0.2*max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20)+1e-3*pow(max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20),2))) * (jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets]) >%i && (layer_jets_energy_fraction[5][gentau_jets]<0.2 || jets_pt[gentau_jets]>45)",39),nbins,x);
  TGraphAsymmErrors* gr_PU200_cal_dRNNC2D_cut_0p2_relaxed = new TGraphAsymmErrors();
  gr_PU200_cal_dRNNC2D_cut_0p2_relaxed->Divide(h_PU200_cal_dRNNC2D_cut_0p2_relaxed,h_PU200_denom_dRNNC2D);


  vector<TGraphAsymmErrors*> turnons;
  turnons.push_back(gr_PU200_cal_dRNNC2D);
  turnons.push_back(gr_PU200_cal_dRNNC2D_cut_relaxed);
  turnons.push_back(gr_PU200_cal_dRNNC2D_cut_0p2_relaxed);

  vector<TString> leg_entry;
  leg_entry.push_back("SingleTau40");
  leg_entry.push_back("95% cut SingleTau40");
  leg_entry.push_back("0.2 cut SingleTau39");


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


  c->SaveAs(Form("plots/turnons_L1SingleTau_dRNNC2D_PU200_layer5_compar.pdf"));  


}




void plot_ROC_VBF(){

  TString file_sig = "/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root";
  TString file_bkg = "/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root";

  TString VBF_cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20 && jets_pt[VBF_parton_genjet]>20";
  TString ZB_cut = "jets_pt>20";

  
  vector<TGraphErrors*> ROCs;
  vector<TString> leg_entry;
  

  //ROCs.push_back(get_ROC_VBF(file_sig,file_bkg,VBF_cut,ZB_cut,"layer_jets_energy_fraction[3]",100,0,1,false));
  ROCs.push_back(get_ROC_VBF(file_sig,file_bkg,VBF_cut,ZB_cut,"layer_jets_energy_fraction[5]",100,0,1,false));
  /*ROCs.push_back(get_ROC_VBF(file_sig,file_bkg,VBF_cut,ZB_cut,"layer_jets_energy_fraction[7]",100,0,1,false));
  ROCs.push_back(get_ROC_VBF(file_sig,file_bkg,VBF_cut,ZB_cut,"layer_jets_energy_fraction[10]",100,0,1,false));
  ROCs.push_back(get_ROC_VBF(file_sig,file_bkg,VBF_cut,ZB_cut,"layer_jets_energy_fraction[20]",100,0,1,false));
  ROCs.push_back(get_ROC_VBF(file_sig,file_bkg,VBF_cut,ZB_cut,"layer_jets_energy_fraction[30]",100,0,1,false));*/
  ROCs.push_back(get_ROC_VBF(file_sig,file_bkg,VBF_cut,ZB_cut,"jets_pt",480,20,500,true));
  ROCs.push_back(get_ROC_VBF_2D(file_sig,file_bkg,VBF_cut,ZB_cut,"layer_jets_energy_fraction[5]",100,0,1,false));


  //leg_entry.push_back("Layer #3");
  leg_entry.push_back("Layer #5");
  //leg_entry.push_back("Layer #7");
  //leg_entry.push_back("Layer #10");
  //leg_entry.push_back("Layer #20");
  //leg_entry.push_back("Layer #30");
  leg_entry.push_back("Jet p_{T}");
  leg_entry.push_back("Jet p_{T} + Layer #5");
  

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

  
  c->SaveAs("plots/ROC_layer_fraction_VBF.pdf");  



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
  ROCs.push_back(get_ROC_VBF(file_sig,file_bkg,VBF_cut,ZB_cut,"layer_jets_energy_fraction[20]",100,0,1,false));
  ROCs.push_back(get_ROC_VBF(file_sig,file_bkg,VBF_cut,ZB_cut,"layer_jets_energy_fraction[30]",100,0,1,false));


  leg_entry.push_back("Layer #3");
  leg_entry.push_back("Layer #5");
  leg_entry.push_back("Layer #7");
  leg_entry.push_back("Layer #9");
  leg_entry.push_back("Layer #11");
  leg_entry.push_back("Layer #20");
  leg_entry.push_back("Layer #30");
  
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

  
  c->SaveAs("plots/ROC_layer_fraction_VBF_layer.pdf");  



}








void plot_ROC_VBF(float pT_min, float pT_max){

  TString file_sig = "/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root";
  TString file_bkg = "/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root";

  TString VBF_cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20 && jets_pt[VBF_parton_genjet]>20";
  VBF_cut += Form(" && jets_pt[VBF_parton_genjet]>%f && jets_pt[VBF_parton_genjet]<%f",pT_min,pT_max);
  TString ZB_cut = "jets_pt>20";
  ZB_cut += Form(" && jets_pt>%f && jets_pt<%f",pT_min,pT_max);

  
  vector<TGraphErrors*> ROCs;
  vector<TString> leg_entry;
  

  ROCs.push_back(get_ROC_VBF(file_sig,file_bkg,VBF_cut,ZB_cut,"layer_jets_energy_fraction[3]",100,0,1,false));
  ROCs.push_back(get_ROC_VBF(file_sig,file_bkg,VBF_cut,ZB_cut,"layer_jets_energy_fraction[5]",100,0,1,false));
  ROCs.push_back(get_ROC_VBF(file_sig,file_bkg,VBF_cut,ZB_cut,"layer_jets_energy_fraction[7]",100,0,1,false));
  ROCs.push_back(get_ROC_VBF(file_sig,file_bkg,VBF_cut,ZB_cut,"layer_jets_energy_fraction[10]",100,0,1,false));
  ROCs.push_back(get_ROC_VBF(file_sig,file_bkg,VBF_cut,ZB_cut,"layer_jets_energy_fraction[20]",100,0,1,false));
  ROCs.push_back(get_ROC_VBF(file_sig,file_bkg,VBF_cut,ZB_cut,"layer_jets_energy_fraction[30]",100,0,1,false));

  leg_entry.push_back("Layer #3");
  leg_entry.push_back("Layer #5");
  leg_entry.push_back("Layer #7");
  leg_entry.push_back("Layer #10");
  leg_entry.push_back("Layer #20");
  leg_entry.push_back("Layer #30");

  TLegend* leg=new TLegend(0.2,0.4,0.4,0.8);
  leg->SetHeader(Form("%i<p_(T)<%i GeV",int(pT_min),int(pT_max)));
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
  c->SetGrid();
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  
  ROCs[0]->GetXaxis()->SetTitle("Signal eff.");
  ROCs[0]->GetYaxis()->SetTitle("Bkg eff.");
  ROCs[0]->GetYaxis()->SetTitleOffset(1.7);
  ROCs[0]->GetXaxis()->SetLimits(0.,1.);
  ROCs[0]->GetYaxis()->SetRangeUser(2e-4,1.);
  ROCs[0]->SetTitle("");
  ROCs[0]->Draw("APL");
  for(unsigned int i=1;i<ROCs.size();i++)
    ROCs[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(0.51,1.02,"CMS Simulation #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs(Form("plots/ROC_layer_fraction_VBF_pt%i_%i.pdf",int(pT_min),int(pT_max)));  



}









void plot_ROC_tau(){

  TString file_sig = "/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root";
  TString file_bkg = "/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root";

  TString tau_cut = "gentau_jets>=0 && abs(gentau_vis_eta)>1.6 && abs(gentau_vis_eta)<2.9 && gentau_vis_pt>20 && gentau_decayMode>=0 && gentau_decayMode<=5 && jets_pt[gentau_jets]>20";
  TString ZB_cut = "jets_pt>20";

  
  vector<TGraphErrors*> ROCs;
  vector<TString> leg_entry;
  

  //ROCs.push_back(get_ROC_tau(file_sig,file_bkg,tau_cut,ZB_cut,"layer_jets_energy_fraction[3]",100,0,1,false));
  ROCs.push_back(get_ROC_tau(file_sig,file_bkg,tau_cut,ZB_cut,"layer_jets_energy_fraction[5]",100,0,1,false));
  /*ROCs.push_back(get_ROC_tau(file_sig,file_bkg,tau_cut,ZB_cut,"layer_jets_energy_fraction[7]",100,0,1,false));
  ROCs.push_back(get_ROC_tau(file_sig,file_bkg,tau_cut,ZB_cut,"layer_jets_energy_fraction[10]",100,0,1,false));
  ROCs.push_back(get_ROC_tau(file_sig,file_bkg,tau_cut,ZB_cut,"layer_jets_energy_fraction[20]",100,0,1,false));
  ROCs.push_back(get_ROC_tau(file_sig,file_bkg,tau_cut,ZB_cut,"layer_jets_energy_fraction[30]",100,0,1,false));*/
  ROCs.push_back(get_ROC_tau(file_sig,file_bkg,tau_cut,ZB_cut,"jets_pt",480,20,500,true));
  ROCs.push_back(get_ROC_tau_2D(file_sig,file_bkg,tau_cut,ZB_cut,"layer_jets_energy_fraction[5]",100,0,1,false));


  //leg_entry.push_back("Layer #3");
  leg_entry.push_back("Layer #5");
  //leg_entry.push_back("Layer #7");
  //leg_entry.push_back("Layer #10");
  //leg_entry.push_back("Layer #20");
  //leg_entry.push_back("Layer #30");
  leg_entry.push_back("Jet p_{T}");
  leg_entry.push_back("Jet p_{T} + Layer #5");
  
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

  
  c->SaveAs("plots/ROC_layer_fraction_tau.pdf");  



}






void plot_ROC_tau_layer(){

  TString file_sig = "/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root";
  TString file_bkg = "/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root";

  TString tau_cut = "gentau_jets>=0 && abs(gentau_vis_eta)>1.6 && abs(gentau_vis_eta)<2.9 && gentau_vis_pt>20 && gentau_decayMode>=0 && gentau_decayMode<=5 && jets_pt[gentau_jets]>20";
  TString ZB_cut = "jets_pt>20";

  
  vector<TGraphErrors*> ROCs;
  vector<TString> leg_entry;
  

  ROCs.push_back(get_ROC_tau(file_sig,file_bkg,tau_cut,ZB_cut,"layer_jets_energy_fraction[3]",100,0,1,false));
  ROCs.push_back(get_ROC_tau(file_sig,file_bkg,tau_cut,ZB_cut,"layer_jets_energy_fraction[5]",100,0,1,false));
  ROCs.push_back(get_ROC_tau(file_sig,file_bkg,tau_cut,ZB_cut,"layer_jets_energy_fraction[7]",100,0,1,false));
  ROCs.push_back(get_ROC_tau(file_sig,file_bkg,tau_cut,ZB_cut,"layer_jets_energy_fraction[9]",100,0,1,false));
  ROCs.push_back(get_ROC_tau(file_sig,file_bkg,tau_cut,ZB_cut,"layer_jets_energy_fraction[11]",100,0,1,false));
  ROCs.push_back(get_ROC_tau(file_sig,file_bkg,tau_cut,ZB_cut,"layer_jets_energy_fraction[20]",100,0,1,false));
  ROCs.push_back(get_ROC_tau(file_sig,file_bkg,tau_cut,ZB_cut,"layer_jets_energy_fraction[30]",100,0,1,false));

  leg_entry.push_back("Layer #3");
  leg_entry.push_back("Layer #5");
  leg_entry.push_back("Layer #7");
  leg_entry.push_back("Layer #9");
  leg_entry.push_back("Layer #11");
  leg_entry.push_back("Layer #20");
  leg_entry.push_back("Layer #30");

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

  
  c->SaveAs("plots/ROC_layer_fraction_tau_layer.pdf");  



}








void plot_ROC_tau(float pT_min, float pT_max){

  TString file_sig = "/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root";
  TString file_bkg = "/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root";

  TString tau_cut = "gentau_jets>=0 && abs(gentau_vis_eta)>1.6 && abs(gentau_vis_eta)<2.9 && gentau_vis_pt>20 && gentau_decayMode>=0 && gentau_decayMode<=5 && jets_pt[gentau_jets]>20";
  tau_cut += Form(" && jets_pt[gentau_genjet]>%f && jets_pt[gentau_genjet]<%f",pT_min,pT_max);
  TString ZB_cut = "jets_pt>20";
  ZB_cut += Form(" && jets_pt>%f && jets_pt<%f",pT_min,pT_max);

  
  vector<TGraphErrors*> ROCs;
  vector<TString> leg_entry;
  

  ROCs.push_back(get_ROC_tau(file_sig,file_bkg,tau_cut,ZB_cut,"layer_jets_energy_fraction[3]",100,0,1,false));
  ROCs.push_back(get_ROC_tau(file_sig,file_bkg,tau_cut,ZB_cut,"layer_jets_energy_fraction[5]",100,0,1,false));
  ROCs.push_back(get_ROC_tau(file_sig,file_bkg,tau_cut,ZB_cut,"layer_jets_energy_fraction[7]",100,0,1,false));
  ROCs.push_back(get_ROC_tau(file_sig,file_bkg,tau_cut,ZB_cut,"layer_jets_energy_fraction[10]",100,0,1,false));
  ROCs.push_back(get_ROC_tau(file_sig,file_bkg,tau_cut,ZB_cut,"layer_jets_energy_fraction[20]",100,0,1,false));
  ROCs.push_back(get_ROC_tau(file_sig,file_bkg,tau_cut,ZB_cut,"layer_jets_energy_fraction[30]",100,0,1,false));

  leg_entry.push_back("Layer #3");
  leg_entry.push_back("Layer #5");
  leg_entry.push_back("Layer #7");
  leg_entry.push_back("Layer #10");
  leg_entry.push_back("Layer #20");
  leg_entry.push_back("Layer #30");

  TLegend* leg=new TLegend(0.6,0.6,0.85,0.8);
  leg->SetHeader(Form("%i<p_(T)<%i GeV",int(pT_min),int(pT_max)));
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
  c->SetGrid();
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  
  ROCs[0]->GetXaxis()->SetTitle("Signal eff.");
  ROCs[0]->GetYaxis()->SetTitle("Bkg eff.");
  ROCs[0]->GetYaxis()->SetTitleOffset(1.7);
  ROCs[0]->GetXaxis()->SetLimits(0.,1.);
  ROCs[0]->GetYaxis()->SetRangeUser(2e-4,1.);
  ROCs[0]->SetTitle("");
  ROCs[0]->Draw("APL");
  for(unsigned int i=1;i<ROCs.size();i++)
    ROCs[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(0.51,1.02,"CMS Simulation #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs(Form("plots/ROC_layer_fraction_tau_pt%i_%i.pdf",int(pT_min),int(pT_max)));  



}








void plot_ROC_tau_DM(int DM){

  TString file_sig = "/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root";
  TString file_bkg = "/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root";

  TString tau_cut = "gentau_jets>=0 && abs(gentau_vis_eta)>1.6 && abs(gentau_vis_eta)<2.9 && gentau_vis_pt>20 && gentau_decayMode>=0 && gentau_decayMode<=5 && jets_pt[gentau_jets]>20";
  tau_cut += Form(" && gentau_decayMode==%i",DM);
  TString ZB_cut = "jets_pt>20";

  
  vector<TGraphErrors*> ROCs;
  vector<TString> leg_entry;
  

  //ROCs.push_back(get_ROC_tau(file_sig,file_bkg,tau_cut,ZB_cut,"layer_jets_energy_fraction[3]",100,0,1,false));
  ROCs.push_back(get_ROC_tau(file_sig,file_bkg,tau_cut,ZB_cut,"layer_jets_energy_fraction[5]",100,0,1,false));
  /*ROCs.push_back(get_ROC_tau(file_sig,file_bkg,tau_cut,ZB_cut,"layer_jets_energy_fraction[7]",100,0,1,false));
  ROCs.push_back(get_ROC_tau(file_sig,file_bkg,tau_cut,ZB_cut,"layer_jets_energy_fraction[10]",100,0,1,false));
  ROCs.push_back(get_ROC_tau(file_sig,file_bkg,tau_cut,ZB_cut,"layer_jets_energy_fraction[20]",100,0,1,false));
  ROCs.push_back(get_ROC_tau(file_sig,file_bkg,tau_cut,ZB_cut,"layer_jets_energy_fraction[30]",100,0,1,false));*/
  ROCs.push_back(get_ROC_tau(file_sig,file_bkg,tau_cut,ZB_cut,"jets_pt",480,20,500,true));
  ROCs.push_back(get_ROC_tau_2D(file_sig,file_bkg,tau_cut,ZB_cut,"layer_jets_energy_fraction[5]",100,0,1,false));


  //leg_entry.push_back("Layer #3");
  leg_entry.push_back("Layer #5");
  //leg_entry.push_back("Layer #7");
  //leg_entry.push_back("Layer #10");
  //leg_entry.push_back("Layer #20");
  //leg_entry.push_back("Layer #30");
  leg_entry.push_back("Jet p_{T}");
  leg_entry.push_back("Jet p_{T} + Layer #5");
  

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
  c->SetLogy();
  
  ROCs[0]->GetXaxis()->SetTitle("Signal eff.");
  ROCs[0]->GetYaxis()->SetTitle("Bkg eff.");
  ROCs[0]->GetYaxis()->SetTitleOffset(1.7);
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

  
  c->SaveAs(Form("plots/ROC_layer_fraction_tau_DM%i.pdf",DM));  



}









void plot_jets_layer5(){

  TH1F* h_VBF_PU0 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","layer_jets_energy_fraction[5][VBF_parton_jets]","VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20",100,0,1);
  TH1F* h_tau_PU0 = single_plot("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","layer_jets_energy_fraction[5][gentau_jets]","gentau_jets>=0 && abs(gentau_vis_eta)>1.6 && abs(gentau_vis_eta)<2.9 && gentau_vis_pt>20 && gentau_decayMode>=0 && gentau_decayMode<=5",100,0,1);

  TH1F* h_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","layer_jets_energy_fraction[5][VBF_parton_jets]","VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20",100,0,1);
  TH1F* h_tau_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","layer_jets_energy_fraction[5][gentau_jets]","gentau_jets>=0 && abs(gentau_vis_eta)>1.6 && abs(gentau_vis_eta)<2.9 && gentau_vis_pt>20 && gentau_decayMode>=0 && gentau_decayMode<=5",100,0,1);
  TH1F* h_ZB_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","layer_jets_energy_fraction[5]","jets_pt>20",100,0,1);


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
  //c->SetLogy();

  histo[0]->GetXaxis()->SetTitle("Energy fraction");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,1.2*histo[0]->GetMaximum());
  //histo[0]->GetYaxis()->SetRangeUser(1e-5,2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(0.02,1.02*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/jets_layer_fraction5.pdf");  


}








void plot_jets_layer5_pT(){


  TH1F* h_ZB_PU200_pt20_40 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","layer_jets_energy_fraction[5]","jets_pt>20 && jets_pt<40",100,0,1);
  TH1F* h_ZB_PU200_pt40_60 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","layer_jets_energy_fraction[5]","jets_pt>40 && jets_pt<60",100,0,1);
  TH1F* h_ZB_PU200_pt60 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","layer_jets_energy_fraction[5]","jets_pt>60",100,0,1);


  vector<TH1F*> histo;
  histo.push_back(h_ZB_PU200_pt20_40);
  histo.push_back(h_ZB_PU200_pt40_60);
  histo.push_back(h_ZB_PU200_pt60);


  vector<TString> leg_entry;
  leg_entry.push_back("PU PU=200 20<p_{T}<40 GeV");
  leg_entry.push_back("PU PU=200 40<p_{T}<60 GeV");
  leg_entry.push_back("PU PU=200 p_{T}>60 GeV");


  TLegend* leg=new TLegend(0.3,0.6,0.8,0.85);
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

  histo = sort_histo(histo);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  TGaxis::SetMaxDigits(4);
  //c->SetLogy();

  histo[0]->GetXaxis()->SetTitle("Energy fraction");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,1.02*histo[0]->GetMaximum());
  //histo[0]->GetYaxis()->SetRangeUser(1e-5,2*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(0.02,1.02*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/jetslayer_fraction5_pT.pdf");  


}









void plot_C3D_layer5(){

  TH1F* h_tau_PU0 = single_plot("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","layer_jets_energy_fraction[5][gentau_jets]","gentau_jets>=0 && abs(gentau_vis_eta)>1.6 && abs(gentau_vis_eta)<2.9 && gentau_vis_pt>20 && gentau_decayMode>=0 && gentau_decayMode<=5",100,0,1);

  TH1F* h_tau_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","layer_jets_energy_fraction[5][gentau_jets]","gentau_jets>=0 && abs(gentau_vis_eta)>1.6 && abs(gentau_vis_eta)<2.9 && gentau_vis_pt>20 && gentau_decayMode>=0 && gentau_decayMode<=5",100,0,1);

  TH1F* h_tau_C3D_PU0 = single_plot("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","layer_cl3d_energy_fraction[5][jets_cl3d[gentau_jets]]","gentau_jets>=0 && abs(gentau_vis_eta)>1.6 && abs(gentau_vis_eta)<2.9 && gentau_vis_pt>20 && gentau_decayMode>=0 && gentau_decayMode<=5",100,0,1);

  TH1F* h_tau_C3D_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","layer_cl3d_energy_fraction[5][jets_cl3d[gentau_jets]]","gentau_jets>=0 && abs(gentau_vis_eta)>1.6 && abs(gentau_vis_eta)<2.9 && gentau_vis_pt>20 && gentau_decayMode>=0 && gentau_decayMode<=5",100,0,1);


  vector<TH1F*> histo;
  histo.push_back(h_tau_PU0);
  histo.push_back(h_tau_PU200);
  histo.push_back(h_tau_C3D_PU0);
  histo.push_back(h_tau_C3D_PU200);

  vector<TString> leg_entry;
  leg_entry.push_back("#tau_{h} PU=0");
  leg_entry.push_back("#tau_{h} PU=200");
  leg_entry.push_back("#tau_{h} PU=0 C3D");
  leg_entry.push_back("#tau_{h} PU=200 C3D");

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

  histo = sort_histo(histo);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  TGaxis::SetMaxDigits(4);
  c->SetLogy();

  histo[0]->GetXaxis()->SetTitle("Energy fraction");
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

  
  TLatex *texl = new TLatex(0.02,1.02*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/C3D_layer_fraction5.pdf");  


}









void plot_C3D_layer5_pt20(){

  TH1F* h_tau_PU0 = single_plot("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","layer_jets_energy_fraction[5][gentau_jets]","gentau_jets>=0 && abs(gentau_vis_eta)>1.6 && abs(gentau_vis_eta)<2.9 && gentau_vis_pt>20 && gentau_decayMode>=0 && gentau_decayMode<=5 && jets_pt>20",100,0,1);

  TH1F* h_tau_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","layer_jets_energy_fraction[5][gentau_jets]","gentau_jets>=0 && abs(gentau_vis_eta)>1.6 && abs(gentau_vis_eta)<2.9 && gentau_vis_pt>20 && gentau_decayMode>=0 && gentau_decayMode<=5 && jets_pt>20",100,0,1);

  TH1F* h_tau_C3D_PU0 = single_plot("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","layer_cl3d_energy_fraction[5][jets_cl3d[gentau_jets]]","gentau_jets>=0 && abs(gentau_vis_eta)>1.6 && abs(gentau_vis_eta)<2.9 && gentau_vis_pt>20 && gentau_decayMode>=0 && gentau_decayMode<=5 && cl3d_pt[jets_cl3d[gentau_jets]]>20",100,0,1);

  TH1F* h_tau_C3D_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","layer_cl3d_energy_fraction[5][jets_cl3d[gentau_jets]]","gentau_jets>=0 && abs(gentau_vis_eta)>1.6 && abs(gentau_vis_eta)<2.9 && gentau_vis_pt>20 && gentau_decayMode>=0 && gentau_decayMode<=5 && cl3d_pt[jets_cl3d[gentau_jets]]>20",100,0,1);


  vector<TH1F*> histo;
  histo.push_back(h_tau_PU0);
  histo.push_back(h_tau_PU200);
  histo.push_back(h_tau_C3D_PU0);
  histo.push_back(h_tau_C3D_PU200);

  vector<TString> leg_entry;
  leg_entry.push_back("#tau_{h} PU=0");
  leg_entry.push_back("#tau_{h} PU=200");
  leg_entry.push_back("#tau_{h} PU=0 C3D");
  leg_entry.push_back("#tau_{h} PU=200 C3D");

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

  histo = sort_histo(histo);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  TGaxis::SetMaxDigits(4);
  c->SetLogy();

  histo[0]->GetXaxis()->SetTitle("Energy fraction");
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

  
  TLatex *texl = new TLatex(0.02,1.02*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/C3D_layer_fraction5_pt20.pdf");  


}







void plot_layer_cl3d_energy_fraction5_pt_tau(){


  TH2F* h_tau_layer5_jet_PU200 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","jets_pt[gentau_jets]","layer_jets_energy_fraction[5][gentau_jets]","gentau_jets>=0 && abs(gentau_vis_eta)>1.6 && abs(gentau_vis_eta)<2.9 && gentau_vis_pt>20 && gentau_decayMode>=0 && gentau_decayMode<=5",15,0,150,10000,0,1);
  TH2F* h_tau_layer5_jet_PU0 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","jets_pt[gentau_jets]","layer_jets_energy_fraction[5][gentau_jets]","gentau_jets>=0 && abs(gentau_vis_eta)>1.6 && abs(gentau_vis_eta)<2.9 && gentau_vis_pt>20 && gentau_decayMode>=0 && gentau_decayMode<=5",15,0,150,10000,0,1);
   TH2F* h_tau_layer5_cl3d_PU200 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","cl3d_pt[jets_cl3d[gentau_jets]]","layer_cl3d_energy_fraction[5][jets_cl3d[gentau_jets]]","gentau_jets>=0 && abs(gentau_vis_eta)>1.6 && abs(gentau_vis_eta)<2.9 && gentau_vis_pt>20 && gentau_decayMode>=0 && gentau_decayMode<=5",15,0,150,10000,0,1);
   TH2F* h_tau_layer5_cl3d_PU0 = single_plot2D("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","cl3d_pt[jets_cl3d[gentau_jets]]","layer_cl3d_energy_fraction[5][jets_cl3d[gentau_jets]]","gentau_jets>=0 && abs(gentau_vis_eta)>1.6 && abs(gentau_vis_eta)<2.9 && gentau_vis_pt>20 && gentau_decayMode>=0 && gentau_decayMode<=5",15,0,150,10000,0,1);


  vector<TH2F*> histo;
  histo.push_back(h_tau_layer5_jet_PU0);
  histo.push_back(h_tau_layer5_jet_PU200);
  histo.push_back(h_tau_layer5_cl3d_PU0);
  histo.push_back(h_tau_layer5_cl3d_PU200);
  
  vector<TString> leg_entry;
  leg_entry.push_back("#tau_{h} PU=0 L1 jet");
  leg_entry.push_back("#tau_{h} PU=200 L1 jet");  
  leg_entry.push_back("#tau_{h} PU=0 L1 C3D");
  leg_entry.push_back("#tau_{h} PU=200 L1 C3D");
  


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
    h->SetLineWidth(5);
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
  h_dummy->GetYaxis()->SetTitle("Energy fraction Layer 5");
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


  c->SaveAs("plots/layer_cl3d_energy_fraction_pt_tau_dRNNC2D.pdf");  


}









void plot_layer_cl3d_energy_fraction5_pt_VBF(){

  TString file_sig_PU0 = "/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root";
  TString file_sig_PU200 = "/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root";
  TString file_bkg = "/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root";

  TString VBF_cut = "VBF_parton_genjet[0]>=0 && VBF_parton_jets[0]>=0 && abs(genjet_eta[VBF_parton_genjet[0]])>1.6 && abs(genjet_eta[VBF_parton_genjet[0]])<2.9 && genjet_pt[VBF_parton_genjet[0]]>20 && cl3d_jet==VBF_parton_jets[0]";
  TString ZB_cut = "cl3d_jet>=0 && jets_pt[cl3d_jet]>20";

   TH2F* h_VBF_layer5_cl3d_PU0 = single_plot2D(file_sig_PU0,"HGCalTriggerNtupleJet","cl3d_pt","layer_cl3d_energy_fraction[5]",VBF_cut,15,0,150,10000,0,1);
   TH2F* h_VBF_layer5_cl3d_PU200 = single_plot2D(file_sig_PU200,"HGCalTriggerNtupleJet","cl3d_pt","layer_cl3d_energy_fraction[5]",VBF_cut,15,0,150,10000,0,1);
   TH2F* h_ZB_layer5_cl3d_PU200 = single_plot2D(file_bkg,"HGCalTriggerNtupleJet","cl3d_pt","layer_cl3d_energy_fraction[5]",ZB_cut,15,0,150,10000,0,1);


  vector<TH2F*> histo;
  histo.push_back(h_VBF_layer5_cl3d_PU0);
  histo.push_back(h_VBF_layer5_cl3d_PU200);
  histo.push_back(h_ZB_layer5_cl3d_PU200);
  
  vector<TString> leg_entry;
  leg_entry.push_back("VBF PU=0");
  leg_entry.push_back("VBF PU=200");
  leg_entry.push_back("ZB PU=200");
 


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
  h_dummy->GetYaxis()->SetTitle("Energy fraction Layer 5");
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


  c->SaveAs("plots/layer_cl3d_energy_fraction_pt_VBF.pdf");  


}









void plot_layer_cl3d_energy_fraction5_eta_VBF(){

  TString file_sig_PU0 = "/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root";
  TString file_sig_PU200 = "/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root";
  TString file_bkg = "/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root";

  TString VBF_cut = "VBF_parton_genjet[0]>=0 && VBF_parton_jets[0]>=0 && abs(genjet_eta[VBF_parton_genjet[0]])>1.6 && abs(genjet_eta[VBF_parton_genjet[0]])<2.9 && genjet_pt[VBF_parton_genjet[0]]>20 && cl3d_jet==VBF_parton_jets[0]";
  TString ZB_cut = "cl3d_jet>=0 && jets_pt[cl3d_jet]>20";

   TH2F* h_VBF_layer5_cl3d_PU0 = single_plot2D(file_sig_PU0,"HGCalTriggerNtupleJet","abs(cl3d_eta)","layer_cl3d_energy_fraction[5]",VBF_cut,15,1.5,3.0,10000,0,1);
   TH2F* h_VBF_layer5_cl3d_PU200 = single_plot2D(file_sig_PU200,"HGCalTriggerNtupleJet","abs(cl3d_eta)","layer_cl3d_energy_fraction[5]",VBF_cut,15,1.5,3.0,10000,0,1);
   TH2F* h_ZB_layer5_cl3d_PU200 = single_plot2D(file_bkg,"HGCalTriggerNtupleJet","abs(cl3d_eta)","layer_cl3d_energy_fraction[5]",ZB_cut,15,1.5,3.0,10000,0,1);


  vector<TH2F*> histo;
  histo.push_back(h_VBF_layer5_cl3d_PU0);
  histo.push_back(h_VBF_layer5_cl3d_PU200);
  histo.push_back(h_ZB_layer5_cl3d_PU200);
  
  vector<TString> leg_entry;
  leg_entry.push_back("VBF PU=0");
  leg_entry.push_back("VBF PU=200");
  leg_entry.push_back("ZB PU=200");
 


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


  TH2F* h_dummy = new TH2F("","",15,1.5,3.0,1000,0,1); 
  h_dummy->GetXaxis()->SetTitle("|#eta|");
  h_dummy->GetYaxis()->SetTitle("Energy fraction Layer 5");
  h_dummy->GetYaxis()->SetTitleOffset(1.7);
  h_dummy->GetYaxis()->SetRangeUser(0,1.);
  h_dummy->SetStats(0);
  h_dummy->SetTitle("");
  h_dummy->Draw("candlex(00000301)");
  for(unsigned int i=0;i<histo.size();i++)
    histo[i]->Draw("candlex(00000301)same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.51,1.02,"CMS Simulation #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/layer_cl3d_energy_fraction_eta_VBF.pdf");  


}







void write_layer_cl3d_energy_fraction_pt_quantiles(TString process, int PU){

  TString VBF_sample_PU0 = "/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root";
  TString VBF_sample_PU200 = "/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root";
  TString ZB_sample = "/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root";

  TString VBF_cut = "VBF_parton_genjet[0]>=0 && VBF_parton_jets[0]>=0 && abs(genjet_eta[VBF_parton_genjet[0]])>1.6 && abs(genjet_eta[VBF_parton_genjet[0]])<2.9 && genjet_pt[VBF_parton_genjet[0]]>20 && cl3d_jet==VBF_parton_jets[0]";
  TString ZB_cut = "cl3d_jet>=0 && jets_pt[cl3d_jet]>20";


  TString sample;
  TString cut;
  
  if(process=="VBF"){
    if(PU==200)
      sample = VBF_sample_PU200;
    else
      sample = VBF_sample_PU0;
    cut = VBF_cut;
  }
  else if(process=="ZB"){
    sample = ZB_sample;
    cut = ZB_cut;
  }


  int nbins = 20;
  int nq = 100;
  double xq[nq];
  double yq[nq];
  for(int i=0;i<nq;i++) xq[i]=float(i+1)/nq;

  int nlayers = 52;

  TGraphErrors gr(nbins);
  vector<TGraphErrors> gr_quant(nq,gr);
  vector<vector<TGraphErrors> > gr_vec(nlayers,gr_quant);

  for(int layer=0;layer<nlayers;layer++){
    if(layer<27 && layer%2==0) continue;

    cout<<"layer="<<layer<<endl;

    TH2F* h_2D = single_plot2D(sample,"HGCalTriggerNtupleJet","cl3d_pt",Form("layer_cl3d_energy_fraction[%i]",layer),cut,nbins,0,40,10000,0,1);
    
    for(unsigned int pt_bin=1; pt_bin<=nbins; pt_bin++){

      TH1D* h_pt = h_2D->ProjectionY("h_pt",pt_bin,pt_bin);   
            
      double x=h_2D->GetXaxis()->GetBinCenter(pt_bin);
      cout<<"pt="<<x<<endl;
      double xerr=0.5*h_2D->GetXaxis()->GetBinWidth(pt_bin);

      h_pt->GetQuantiles(nq,yq,xq);
      for(int iq=0;iq<nq;iq++){
	gr_vec[layer][iq].SetPoint(pt_bin-1,x,yq[iq]);
	gr_vec[layer][iq].SetPointError(pt_bin-1,xerr,0);
      }

      delete h_pt;

    }

    delete h_2D;

  }



  TFile* f_new = TFile::Open("layer_cl3d_energy_fraction_pt_quantiles_"+process+Form("_PU%i",PU)+".root","RECREATE");

  for(int layer=0;layer<nlayers;layer++){
    for(unsigned int iq=0; iq<nq; iq++){
      gr_vec[layer][iq].Write(Form(process+"_fraction_layer%i_quant%i",layer,iq));
    }
  }

  f_new->Close();


}








void write_layer_cl3d_energy_fraction_eta_quantiles(TString process, int PU){

  TString VBF_sample_PU0 = "/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root";
  TString VBF_sample_PU200 = "/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root";
  TString ZB_sample = "/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root";

  TString VBF_cut = "VBF_parton_genjet[0]>=0 && VBF_parton_jets[0]>=0 && abs(genjet_eta[VBF_parton_genjet[0]])>1.6 && abs(genjet_eta[VBF_parton_genjet[0]])<2.9 && genjet_pt[VBF_parton_genjet[0]]>20 && cl3d_jet==VBF_parton_jets[0]";
  TString ZB_cut = "cl3d_jet>=0 && jets_pt[cl3d_jet]>20";


  TString sample;
  TString cut;
  
  if(process=="VBF"){
    if(PU==200)
      sample = VBF_sample_PU200;
    else
      sample = VBF_sample_PU0;
    cut = VBF_cut;
  }
  else if(process=="ZB"){
    sample = ZB_sample;
    cut = ZB_cut;
  }


  int nbins = 15;
  int nq = 100;
  double xq[nq];
  double yq[nq];
  for(int i=0;i<nq;i++) xq[i]=float(i+1)/nq;

  int nlayers = 52;

  TGraphErrors gr(nbins);
  vector<TGraphErrors> gr_quant(nq,gr);
  vector<vector<TGraphErrors> > gr_vec(nlayers,gr_quant);

  for(int layer=0;layer<nlayers;layer++){
    if(layer<27 && layer%2==0) continue;

    cout<<"layer="<<layer<<endl;

    TH2F* h_2D = single_plot2D(sample,"HGCalTriggerNtupleJet","abs(cl3d_eta)",Form("layer_cl3d_energy_fraction[%i]",layer),cut,nbins,1.5,3.,10000,0,1);
    
    for(unsigned int eta_bin=1; eta_bin<=nbins; eta_bin++){

      TH1D* h_eta = h_2D->ProjectionY("h_eta",eta_bin,eta_bin);   
            
      double x=h_2D->GetXaxis()->GetBinCenter(eta_bin);
      cout<<"eta="<<x<<endl;
      double xerr=0.5*h_2D->GetXaxis()->GetBinWidth(eta_bin);

      h_eta->GetQuantiles(nq,yq,xq);
      for(int iq=0;iq<nq;iq++){
	gr_vec[layer][iq].SetPoint(eta_bin-1,x,yq[iq]);
	gr_vec[layer][iq].SetPointError(eta_bin-1,xerr,0);
      }

      delete h_eta;

    }

    delete h_2D;

  }



  TFile* f_new = TFile::Open("layer_cl3d_energy_fraction_eta_quantiles_"+process+Form("_PU%i",PU)+".root","RECREATE");

  for(int layer=0;layer<nlayers;layer++){
    for(unsigned int iq=0; iq<nq; iq++){
      gr_vec[layer][iq].Write(Form(process+"_fraction_layer%i_quant%i",layer,iq));
    }
  }

  f_new->Close();


}







void plot_layer_fractions_c3d_compar_layer5_eta(){

  TFile* f_VBF = TFile::Open("layer_cl3d_energy_fraction_eta_quantiles_VBF_PU0.root");
  TFile* f_ZB = TFile::Open("layer_cl3d_energy_fraction_eta_quantiles_ZB_PU200.root");

  vector<TString> gr;
  gr.push_back("VBF_fraction_layer5_quant94");
  gr.push_back("ZB_fraction_layer5_quant94");
  gr.push_back("VBF_fraction_layer5_quant79");
  gr.push_back("ZB_fraction_layer5_quant79");
  gr.push_back("VBF_fraction_layer5_quant49");
  gr.push_back("ZB_fraction_layer5_quant49");

  vector<TString> leg_entry;
  leg_entry.push_back("VBF 95%");
  leg_entry.push_back("ZB 95%");
  leg_entry.push_back("VBF 80%");
  leg_entry.push_back("ZB 80%");
  leg_entry.push_back("VBF 50%");
  leg_entry.push_back("ZB 50%");
  
  TLegend* leg=new TLegend(0.6,0.4,0.8,0.85);
  leg->SetHeader("Layer #5");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  vector<TGraphErrors*> graphs;

  for(unsigned int i=0;i<gr.size();i++){
    
    TGraphErrors* graph;
    if(gr[i].Contains("VBF"))
      graph = (TGraphErrors*)f_VBF->Get(gr[i]);
    else if(gr[i].Contains("ZB"))
      graph = (TGraphErrors*)f_ZB->Get(gr[i]);
    //for(unsigned int j=20;j>10;j--)
    //  graph->RemovePoint(j);
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

  graphs[0]->GetXaxis()->SetTitle("|#eta|(C3D)");
  graphs[0]->GetYaxis()->SetTitle("Cut on energy fraction");
  graphs[0]->GetYaxis()->SetTitleOffset(1.7);
  graphs[0]->GetXaxis()->SetLimits(1.4,4.0);
  graphs[0]->GetYaxis()->SetRangeUser(0,1.05);
  graphs[0]->SetTitle("");
  graphs[0]->Draw();
  
  for(unsigned int i=1;i<graphs.size();i++)
    graphs[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(1.42,1.07,"CMS Simulation Preliminary, #sqrt{s}=14 TeV");
  texl->SetTextSize(0.029);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/layer_fractions_c3d_compar_layer5_eta.pdf");  
  f_VBF->Close();
  f_ZB->Close();

}
  






void plot_layer_fractions_c3d_compar_layer5_pt(){

  TFile* f_VBF = TFile::Open("layer_cl3d_energy_fraction_pt_quantiles_VBF_PU0.root");
  TFile* f_ZB = TFile::Open("layer_cl3d_energy_fraction_pt_quantiles_ZB_PU200.root");

  vector<TString> gr;
  gr.push_back("VBF_fraction_layer5_quant94");
  gr.push_back("ZB_fraction_layer5_quant94");
  gr.push_back("VBF_fraction_layer5_quant79");
  gr.push_back("ZB_fraction_layer5_quant79");
  gr.push_back("VBF_fraction_layer5_quant49");
  gr.push_back("ZB_fraction_layer5_quant49");

  vector<TString> leg_entry;
  leg_entry.push_back("VBF 95%");
  leg_entry.push_back("ZB 95%");
  leg_entry.push_back("VBF 80%");
  leg_entry.push_back("ZB 80%");
  leg_entry.push_back("VBF 50%");
  leg_entry.push_back("ZB 50%");
  
  TLegend* leg=new TLegend(0.6,0.4,0.8,0.85);
  leg->SetHeader("Layer #5");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  vector<TGraphErrors*> graphs;

  for(unsigned int i=0;i<gr.size();i++){
    
    TGraphErrors* graph;
    if(gr[i].Contains("VBF"))
      graph = (TGraphErrors*)f_VBF->Get(gr[i]);
    else if(gr[i].Contains("ZB"))
      graph = (TGraphErrors*)f_ZB->Get(gr[i]);
    //for(unsigned int j=20;j>10;j--)
    //  graph->RemovePoint(j);
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

  graphs[0]->GetXaxis()->SetTitle("p_{T}(C3D) [GeV]");
  graphs[0]->GetYaxis()->SetTitle("Cut on energy fraction");
  graphs[0]->GetYaxis()->SetTitleOffset(1.7);
  graphs[0]->GetXaxis()->SetLimits(0.,40.0);
  graphs[0]->GetYaxis()->SetRangeUser(0,1.05);
  graphs[0]->SetTitle("");
  graphs[0]->Draw();
  
  for(unsigned int i=1;i<graphs.size();i++)
    graphs[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(1.42,1.07,"CMS Simulation Preliminary, #sqrt{s}=14 TeV");
  texl->SetTextSize(0.029);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/layer_fractions_c3d_compar_layer5_pt.pdf");  
  f_VBF->Close();
  f_ZB->Close();

}
  




