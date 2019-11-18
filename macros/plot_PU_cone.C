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
#include "Helpers.C"
#include <vector>

using namespace std;


void plot_cone_centers(){

  TH2F* h = single_plot2D("/data_CMS/cms/strebler/HGC/SingleNu_PU200_JB/calibr_cone_ntuples/calibr_cone_ntuples_1.root","HGCalTriggerNtuple","abs(cone_eta)","cone_phi","",100,1.0,3.5,100,-3.5,3.5);

  h->Scale(1/h->Integral());
  h->SetStats(0);
  h->SetTitle("");
  
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  //c->SetLogz();
  h->GetXaxis()->SetTitle("|#eta|");
  h->GetYaxis()->SetTitle("#phi");
  h->GetYaxis()->SetTitleOffset(1.7);
  h->GetZaxis()->SetRangeUser(0,8e-3);
  h->Draw("colz");


  TLatex *texl = new TLatex(1.,1.02*100,"CMS Simulation Neutrino gun, #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  c->SaveAs("plots/cone_centers.pdf");


}




void plot_cone_pt_C3D_TC_low_eta(){

  TH2F* h = single_plot2D("/data_CMS/cms/strebler/HGC/SingleNu_PU200_JB/calibr_cone_ntuples/calibr_cone_ntuples_*.root","HGCalTriggerNtuple","cone_calib_Luca_pt","cone_tc_calib_Luca_pt","abs(cone_eta)<2.1",100,0,200,100,0,200);

  h->Scale(1/h->Integral());
  h->SetStats(0);
  h->SetTitle("");
  
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  c->SetLogz();
  h->GetXaxis()->SetTitle("C3D cone p_{T} [GeV]");
  h->GetYaxis()->SetTitle("TC cone p_{T} [GeV]");
  h->GetYaxis()->SetTitleOffset(1.7);
  h->GetZaxis()->SetRangeUser(1e-9,1);
  h->Draw("colz");


  TLatex *texl = new TLatex(1.,1.02*200,"CMS Simulation Neutrino gun, #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  c->SaveAs("plots/cone_pt_2D_low_eta.pdf");


}





void plot_cone_pt_C3D_TC_high_eta(){

  TH2F* h = single_plot2D("/data_CMS/cms/strebler/HGC/SingleNu_PU200_JB/calibr_cone_ntuples/calibr_cone_ntuples_*.root","HGCalTriggerNtuple","cone_calib_Luca_pt","cone_tc_calib_Luca_pt","abs(cone_eta)>2.1",100,0,200,100,0,200);

  h->Scale(1/h->Integral());
  h->SetStats(0);
  h->SetTitle("");
  
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  c->SetLogz();
  h->GetXaxis()->SetTitle("C3D cone p_{T} [GeV]");
  h->GetYaxis()->SetTitle("TC cone p_{T} [GeV]");
  h->GetYaxis()->SetTitleOffset(1.7);
  h->GetZaxis()->SetRangeUser(1e-9,1);
  h->Draw("colz");


  TLatex *texl = new TLatex(1.,1.02*200,"CMS Simulation Neutrino gun, #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  c->SaveAs("plots/cone_pt_2D_high_eta.pdf");  


}






void plot_profile_cone_pt_C3D_eta(){

  TH2F* h = single_plot2D("/data_CMS/cms/strebler/HGC/SingleNu_PU200_JB/calibr_cone_ntuples/calibr_cone_ntuples_*.root","HGCalTriggerNtuple","abs(cone_eta)","cone_calib_Luca_pt","",16,1.45,3.05,100,0,100);

  h->Scale(1/h->Integral());
  h->SetStats(0);
  h->SetTitle("");
  
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  c->SetLogz();
  h->GetXaxis()->SetTitle("|#eta|");
  h->GetYaxis()->SetTitle("C3D cone p_{T} [GeV]");
  h->GetYaxis()->SetTitleOffset(1.7);
  h->GetZaxis()->SetRangeUser(1e-9,1);
  h->Draw("colz");

  TProfile prof = *(h->ProfileX());
  prof.SetStats(0);
  prof.BuildOptions(0,0,"s");
  prof.SetLineColor(kRed);
  prof.SetLineWidth(2);
  prof.Draw("same");

  TH2F* h2 = single_plot2D("/data_CMS/cms/strebler/HGC/SingleNu_PU200_JB/calibr_cone_ntuples/calibr_cone_ntuples_1.root","HGCalTriggerNtuple","abs(cone_eta)","cone_calib_Luca_pt","cone_calib_Luca_pt>0",16,1.45,3.05,100,0,100);
  TProfile prof2 = *(h2->ProfileX());
  prof2.SetStats(0);
  prof2.BuildOptions(0,0,"s");
  prof2.SetLineColor(kBlue);
  prof2.SetLineWidth(2);
  prof2.Draw("same");

  TLatex *texl = new TLatex(1.47,1.02*100,"CMS Simulation Neutrino gun, #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  c->SaveAs("plots/profile_cone_pt_C3D_eta.pdf");  


}







void plot_profile_cone_pt_tc_eta(){

  TH2F* h = single_plot2D("/data_CMS/cms/strebler/HGC/SingleNu_PU200_JB/calibr_cone_ntuples/calibr_cone_ntuples_*.root","HGCalTriggerNtuple","abs(cone_eta)","cone_tc_calib_Luca_pt","",16,1.45,3.05,100,0,100);

  h->Scale(1/h->Integral());
  h->SetStats(0);
  h->SetTitle("");
  
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  c->SetLogz();
  h->GetXaxis()->SetTitle("|#eta|");
  h->GetYaxis()->SetTitle("TC cone p_{T} [GeV]");
  h->GetYaxis()->SetTitleOffset(1.7);
  h->GetZaxis()->SetRangeUser(1e-9,1);
  h->Draw("colz");

  TProfile prof = *(h->ProfileX());
  prof.SetStats(0);
  prof.BuildOptions(0,0,"s");
  prof.SetLineColor(kRed);
  prof.SetLineWidth(2);
  prof.Draw("same");

  TH2F* h2 = single_plot2D("/data_CMS/cms/strebler/HGC/SingleNu_PU200_JB/calibr_cone_ntuples/calibr_cone_ntuples_1.root","HGCalTriggerNtuple","abs(cone_eta)","cone_tc_calib_Luca_pt","cone_tc_calib_Luca_pt>0",16,1.45,3.05,100,0,100);
  TProfile prof2 = *(h2->ProfileX());
  prof2.SetStats(0);
  prof2.BuildOptions(0,0,"s");
  prof2.SetLineColor(kBlue);
  prof2.SetLineWidth(2);
  prof2.Draw("same");

  TLatex *texl = new TLatex(1.47,1.02*100,"CMS Simulation Neutrino gun, #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  c->SaveAs("plots/profile_cone_pt_tc_eta.pdf");  


}








void plot_profile_only_eta(){

  //  TString filename = "/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1.root";
  //  TString filename = "/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_cone_ntuples/calibr_cone_ntuples_1.root";
  TString filename = "/vols/cms/snwebb/HGC_ntuples/DoubleNu/DoubleNu-PU200-stc-TCs-histoMax-DRA040-DRB02-NS/calibr_cone_ntuples/test10.root";

  // TH2F* h_tc = single_plot2D(filename,"HGCalTriggerNtuple","abs(cone_eta)","cone_tc_calib_pt","",16,1.45,3.05,100,0,100);
  // TH2F* h_tc0 = single_plot2D(filename,"HGCalTriggerNtuple","abs(cone_eta)","cone_tc_calib_pt","cone_tc_calib_pt>0",16,1.45,3.05,100,0,100);
  // TH2F* h_C3D = single_plot2D(filename,"HGCalTriggerNtuple","abs(cone_eta)","cone_calib_pt","",16,1.45,3.05,100,0,100);
  // TH2F* h_C3D0 = single_plot2D(filename,"HGCalTriggerNtuple","abs(cone_eta)","cone_calib_pt","cone_calib_pt>0",16,1.45,3.05,100,0,100);
 
  // TH2F* h_tc = single_plot2D(filename,"HGCalTriggerNtuple","abs(cone_eta)","cone_tc_calib_Luca_pt","",16,1.45,3.05,100,0,100);
  // TH2F* h_tc0 = single_plot2D(filename,"HGCalTriggerNtuple","abs(cone_eta)","cone_tc_calib_Luca_pt","cone_tc_calib_Luca_pt>0",16,1.45,3.05,100,0,100);
  // TH2F* h_C3D = single_plot2D(filename,"HGCalTriggerNtuple","abs(cone_eta)","cone_calib_Luca_pt","",16,1.45,3.05,100,0,100);
  // TH2F* h_C3D0 = single_plot2D(filename,"HGCalTriggerNtuple","abs(cone_eta)","cone_calib_Luca_pt","cone_calib_Luca_pt>0",16,1.45,3.05,100,0,100);

  TH2F* h_tc = single_plot2D(filename,"HGCalTriggerNtuple","abs(cone_eta)","cone_tc_pt_original","",16,1.45,3.05,100,0,100);
  TH2F* h_tc0 = single_plot2D(filename,"HGCalTriggerNtuple","abs(cone_eta)","cone_tc_pt_original","cone_tc_pt_original>0",16,1.45,3.05,100,0,100);
  TH2F* h_C3D = single_plot2D(filename,"HGCalTriggerNtuple","abs(cone_eta)","cone_pt_original","",16,1.45,3.05,100,0,100);
  TH2F* h_C3D0 = single_plot2D(filename,"HGCalTriggerNtuple","abs(cone_eta)","cone_pt_original","cone_pt_original>0",16,1.45,3.05,100,0,100);
 
  vector<TH2F*> histo;
  histo.push_back(h_tc);
  histo.push_back(h_tc0);
  histo.push_back(h_C3D);
  histo.push_back(h_C3D0);

  vector<TProfile*> prof;
  
  vector<TString> leg_entry;
  leg_entry.push_back("TC cone");
  leg_entry.push_back("TC cone p_{T}>0");
  leg_entry.push_back("C3D cone");
  leg_entry.push_back("C3D cone p_{T}>0");

  vector<TString> name;
  name.push_back("prof_cone_tc");
  name.push_back("prof_cone_tc_pTgt0");
  name.push_back("prof_cone_C3D");
  name.push_back("prof_cone_C3D_pTgt0");

  TLegend* leg=new TLegend(0.3,0.5,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);


  // TFile* f_new = TFile::Open("PU_cone_vs_eta_new.root");
  // if(f_new!=0){
  //   cout<<"PU_cone_vs_eta.root already exists, please delete it before converting again"<<endl;
  //   return;
  //   }  
  TFile*  f_new = TFile::Open("PU_cone_vs_eta_20190121-3.root","RECREATE");
  gStyle->SetOptTitle(0);
  
  for(unsigned int i=0; i<histo.size(); i++){

    TProfile* p = histo[i]->ProfileX();
    p->SetLineColor(i+1);
    p->SetLineWidth(2);
    p->BuildOptions(0,0,"s");
    p->SetStats(0);
    p->SetNameTitle(name[i],name[i]);    
    prof.push_back(p);
    leg->AddEntry(p,leg_entry[i]);
    p->Write();

  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  c->SetLogz();

  prof[0]->GetXaxis()->SetTitle("|#eta|");
  prof[0]->GetYaxis()->SetTitle("Cone p_{T} [GeV]");
  prof[0]->GetYaxis()->SetTitleOffset(1.7);  
  prof[0]->GetYaxis()->SetRangeUser(0,30);
  prof[0]->Draw();
  for(unsigned int i=1;i<prof.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");


  TLatex *texl = new TLatex(1.47,1.02*30,"CMS Simulation Neutrino gun, #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");
  
  cout<<"ok"<<endl;

  c->SaveAs("plots/profile_cone_pt_eta_comb.pdf");  
  f_new->Close();
  return;

}






