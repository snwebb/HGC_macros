#include "TGraphErrors.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <iomanip>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TH1.h>
#include <TF1.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TGaxis.h>
#include <TLatex.h>
#include <TRandom3.h>
#include <TLine.h>

using namespace std;

double DoubleCB(double* x, double* par){
  double xx = x[0];
  double norm = par[0];
  double mean = par[1];
  double width = par[2];
  double alpha1 = par[3];
  double n1 = par[4];
  double alpha2 = par[5];
  double n2 = par[6];
  double t = (xx-mean)/width;
  if (t>-alpha1 && t<alpha2)
    return norm*exp(-0.5*t*t);
  else if(t<=-alpha1){
    double A1 = (pow(n1/abs(alpha1),n1))*exp(-alpha1*alpha1/2.);
    double B1 = n1/abs(alpha1)-abs(alpha1);
    return norm*A1*pow(B1-t,-n1);
  }
  else{ //t>=alpha2:
    double A2 = pow(n2/abs(alpha2),n2)*exp(-alpha2*alpha2/2.);
    double B2 = n2/abs(alpha2)-abs(alpha2);
    return norm*A2*pow(B2+t,-n2);
  }

}





TF1* doubleCBFit(TH1F* histo, double rangeInSigma=2., int fitrebin=1){

  TString hname = histo->GetName();
  hname+="_copy";
  TH1F* histoCopy = (TH1F*)histo->Clone(hname);
  histoCopy->SetDirectory(0);
  double mean = histoCopy->GetMean();
  double rms = histoCopy->GetRMS();
  histoCopy->Rebin(fitrebin);
  TF1* fit=new TF1("gaussFit", "gaus", mean-rms, mean+rms);
  fit->SetParameter(1,mean);
  fit->SetParameter(2,rms);
  histoCopy->Fit(fit, "RN");
  mean = fit->GetParameter(1);
  rms = fit->GetParameter(2);
  double norm = fit->GetParameter(0);
  fit = new TF1("gaussFit", "gaus", mean-rms, mean+rms);
  fit->SetParameter(1,mean);
  fit->SetParameter(2,rms);
  histoCopy->Fit(fit, "RN");
  mean = fit->GetParameter(1);
  rms = fit->GetParameter(2);
  norm = fit->GetParameter(0);
  fit = new TF1("doubleCBFit", DoubleCB, mean-rangeInSigma*rms, mean+rangeInSigma*rms, 7);
  fit->SetParLimits(1, mean-rms, mean+rms);
  fit->SetParLimits(2, rms/rangeInSigma, rms*rangeInSigma);
  fit->SetParLimits(3, 0.1, 10.);
  fit->SetParLimits(4, 0., 30.);
  fit->SetParLimits(5, 0.1, 10.);
  fit->SetParLimits(6, 0., 30.);
  fit->SetParameter(0,norm);
  fit->SetParameter(1,mean);
  fit->SetParameter(2,rms);
  fit->SetParameter(3, 1.);
  fit->SetParameter(4, 1);
  fit->SetParameter(5, 1.);
  fit->SetParameter(6, 1);
  histoCopy->Fit(fit, "R");
  histoCopy->Delete();
  return fit;
}


vector<float> effectiveRMS(TH1F* histo, double fraction=0.683, int fitrebin=1){

  TString hname = histo->GetName();
  hname+="_copy";
  TH1F* histoCopy = (TH1F*)histo->Clone(hname);
  histoCopy->SetDirectory(0);
  int nbins = histoCopy->GetNbinsX();

  TF1* fit = doubleCBFit(histoCopy,3.,fitrebin);
  double maxX = fit->GetParameter(1);
  int maxBinX = histoCopy->GetXaxis()->FindBin(maxX);
  double binWidth = histoCopy->GetXaxis()->GetBinWidth(maxBinX);
  histoCopy->Delete();

  vector<int> indexRMSLeftList;
  vector<int> indexRMSRightList;
  vector<double> rmsList;

  int nTries = 20;
  TRandom3* random = new TRandom3();
 bool goLeft = true;

  for(int n=0; n<nTries; n++){
    hname = histo->GetName();
    hname+="_copy";
    histoCopy = (TH1F*) histo->Clone(hname);
    histoCopy->SetDirectory(0);

    for(int b=1; b<nbins+1; b++){
      double newValue = random->Poisson(histoCopy->GetBinContent(b));
      histoCopy->SetBinContent(b, newValue);
    }


    double totalIntegral = histoCopy->Integral(0,nbins+1);
    //double totalIntegral = histoCopy->Integral();
    double sumBins = 0.;
    double sumErrorBins = 0.;
    int indexRMSLeft = 0;
    int indexRMSRight = 0;
    int indexLeft = 0;
    int indexRight = 0;
    sumBins += histoCopy->GetBinContent(maxBinX)/totalIntegral;

    for(int b=0; b<nbins+1; b++){
      int bRight = maxBinX + indexRight + 1;
      int bLeft = maxBinX - indexLeft - 1;

      if(bRight>nbins){
        cout<<"WARNING: effectiveRMS: bin reached histo boundary"<<endl;
        int binRMSRight = bRight;
        int binRMSLeft = bLeft;
        break;
      }
      if (bLeft<=0){
        cout<<"WARNING: effectiveRMS: bin reached histo boundary"<<endl;
        int binRMSRight = bRight;
        int binRMSLeft = bLeft;
        break;
      }

      double nRight = histoCopy->GetBinContent(bRight);
      double nLeft  = histoCopy->GetBinContent(bLeft);

      if (nLeft>nRight){
        sumBins += nLeft/totalIntegral;
        indexLeft += 1;
      }
      else if (nRight>nLeft){
        sumBins += nRight/totalIntegral;
        indexRight += 1;
      }
      else{
        if(goLeft){
          sumBins += nLeft/totalIntegral;
          indexLeft += 1;
          goLeft = false;
        }
        else{
          sumBins += nRight/totalIntegral;
          indexRight += 1;
          goLeft = true;
        }
      }

      if (sumBins >= fraction){
        indexRMSLeft  = indexLeft;
        indexRMSRight  = indexRight;
        break;
      }

    }

    double xLeft = histoCopy->GetXaxis()->GetBinCenter(maxBinX - indexRMSLeft);
    double xRight = histoCopy->GetXaxis()->GetBinCenter(maxBinX + indexRMSRight);
    //cout<<xLeft<<","<<xRight<<endl;;
    double rms = (xRight - xLeft)/2.;
    rmsList.push_back(rms);
    
  }
    
  double rms=0;
  double rmsError = 0;
  TH1F* rms_histo=new TH1F("rms_histo","rms_histo",1000,0,0.5);
    
  for(unsigned int i=0; i<rmsList.size(); i++){
    rms_histo->Fill(rmsList[i]);
  }


  //rms/=rmsList.size();
  //rmsError=sqrt(rmsError/rmsList.size()-pow(rms,2));
  rms=rms_histo->GetMean();
  rmsError=rms_histo->GetStdDev();
  
  rmsError = max(rmsError, 1./sqrt(12.)*binWidth);
  cout<<rms<<","<<rmsError<<endl;
  
  vector<float> result;
  result.push_back(rms);
  result.push_back(rmsError);
  return result;
  
}





TH1F* histo_ET_resolution_noPUS(TString filename, TString var, TString cut){

  TChain * tree = new TChain("HGCalTriggerNtupleJet");
  tree->Add(filename);

  TString all_cuts=cut;

  tree->Draw(var + ">>g(500,-2,2)",all_cuts+ " && jets_pt[VBF_parton_jets]>0","goff");
  
  TH1F* g=(TH1F*) ((TH1F*)gDirectory->Get("g"))->Clone();
  //g->Scale(1/g->Integral());
  
  return g;
  
}





TH1F* histo_ET_resolution_noPUS_histo(TString filename, TString cut){
  
  TChain * tree = new TChain("HGCalTriggerNtupleJet");
  tree->Add(filename);

  TString all_cuts=cut;

  tree->Draw("(genjet_pt[VBF_parton_genjet] - 1.17*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.07929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets] ) / genjet_pt[VBF_parton_genjet]>>g(500,-2,2)",all_cuts+ " && jets_pt[VBF_parton_jets]>0","goff");

  
  TH1F* g=(TH1F*) ((TH1F*)gDirectory->Get("g"))->Clone();
  //g->Scale(1/g->Integral());
  
  return g;
  
}





TH1F* histo_ET_resolution_noPUS(TString filename, TString cut){
  
  TChain * tree = new TChain("HGCalTriggerNtupleJet");
  tree->Add(filename);

  TString all_cuts=cut;

  tree->Draw("(genjet_pt[VBF_parton_genjet] - (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]) ) / genjet_pt[VBF_parton_genjet]>>g(500,-2,2)",all_cuts+ " && jets_pt[VBF_parton_jets]>0","goff");

  
  TH1F* g=(TH1F*) ((TH1F*)gDirectory->Get("g"))->Clone();
  //g->Scale(1/g->Integral());
  
  return g;
  
}







TH1F* histo_ET_resolution_PUS(TString filename, TString cut){
  
  TChain * tree = new TChain("HGCalTriggerNtupleJet");
  tree->Add(filename);

  TString all_cuts=cut;

  tree->Draw("(genjet_pt[VBF_parton_genjet] - (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) ) / genjet_pt[VBF_parton_genjet]>>g(500,-2,2)",all_cuts+ " && max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)>0","goff");

  
  TH1F* g=(TH1F*) ((TH1F*)gDirectory->Get("g"))->Clone();
  //g->Scale(1/g->Integral());
  
  return g;
  
}






TH1F* histo_ET_resolution_PUS_histo_old(TString filename, TString cut){
  
  TChain * tree = new TChain("HGCalTriggerNtupleJet");
  tree->Add(filename);

  TString all_cuts=cut;

  tree->Draw("(genjet_pt[VBF_parton_genjet] - (1.36*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-0.7*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-0.7*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-0.7*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) ) / genjet_pt[VBF_parton_genjet]>>g(500,-2,2)",all_cuts+ " && max(jets_pt[VBF_parton_jets]-0.7*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)>0","goff");

  
  TH1F* g=(TH1F*) ((TH1F*)gDirectory->Get("g"))->Clone();
  //g->Scale(1/g->Integral());
  
  return g;
  
}






TH1F* histo_ET_resolution_PUS_histo(TString filename, TString cut){
  
  TChain * tree = new TChain("HGCalTriggerNtupleJet");
  tree->Add(filename);

  TString all_cuts=cut;

  tree->Draw("(genjet_pt[VBF_parton_genjet] - (1.17*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-1.1*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.07929e-01* pow(log(max(jets_pt[VBF_parton_jets]-1.1*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-1.1*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) ) / genjet_pt[VBF_parton_genjet]>>g(500,-2,2)",all_cuts+ " && max(jets_pt[VBF_parton_jets]-1.1*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)>0","goff");

  
  TH1F* g=(TH1F*) ((TH1F*)gDirectory->Get("g"))->Clone();
  //g->Scale(1/g->Integral());
  
  return g;
  
}






TH1F* histo_ET_resolution_noPUS_dR0p03(TString filename, TString cut){
  
  TChain * tree = new TChain("HGCalTriggerNtupleJet");
  tree->Add(filename);

  TString all_cuts=cut;

  tree->Draw("1 - 1.06/(-4.82362e-01 + 4.58856e-01 * log(max(jets_pt[VBF_parton_jets],0)) -2.58405e-02 * pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]>>g(500,-2,2)",all_cuts+ " && jets_pt[VBF_parton_jets]>0","goff");

  
  TH1F* g=(TH1F*) ((TH1F*)gDirectory->Get("g"))->Clone();
  //g->Scale(1/g->Integral());
  
  return g;
  
}






TH1F* histo_ET_resolution_PUS_dR0p03(TString filename, TString cut){
  
  TChain * tree = new TChain("HGCalTriggerNtupleJet");
  tree->Add(filename);

  TString all_cuts=cut;

  tree->Draw("1 - 1.06/(-4.82362e-01 + 4.58856e-01 * log(max(jets_pt[VBF_parton_jets]-4.5*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) -2.58405e-02 * pow(log(max(jets_pt[VBF_parton_jets]-4.5*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-4.5*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]>>g(500,-2,2)",all_cuts+ " && max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)>0","goff");

  
  TH1F* g=(TH1F*) ((TH1F*)gDirectory->Get("g"))->Clone();
  //g->Scale(1/g->Integral());
  
  return g;
  
}






TH1F* histo_ET_resolution_tau_noPUS(TString filename, TString cut){
  
  TChain * tree = new TChain("HGCalTriggerNtupleJet");
  tree->Add(filename);

  TString all_cuts=cut;

  tree->Draw("(gentau_vis_pt - (1.1/(0.93-1/(0.2*max(jets_pt[gentau_jets],20)+1e-3*pow(max(jets_pt[gentau_jets],20),2))) * jets_pt[gentau_jets] ) ) / gentau_vis_pt >>g(500,-2,2)",all_cuts+ " && jets_pt[gentau_jets]>0","goff");

  
  TH1F* g=(TH1F*) ((TH1F*)gDirectory->Get("g"))->Clone();
  //g->Scale(1/g->Integral());
  
  return g;
  
}






TH1F* histo_ET_resolution_tau_PUS(TString filename, TString cut){
  
  TChain * tree = new TChain("HGCalTriggerNtupleJet");
  tree->Add(filename);

  TString all_cuts=cut;

  tree->Draw("(gentau_vis_pt - (1.1/(0.93-1/(0.2*max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20)+1e-3*pow(max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],20),2))) * max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],0)) ) / gentau_vis_pt >>g(500,-2,2)",all_cuts+ " && max(jets_pt[gentau_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[gentau_jets],0)>0","goff");

  
  TH1F* g=(TH1F*) ((TH1F*)gDirectory->Get("g"))->Clone();
  //g->Scale(1/g->Integral());
  
  return g;
  
}








void plot_effRMS_pT(){

  
  vector<TString> filename;
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root");

  vector<TString> leg_entry;
  leg_entry.push_back("PU=0");
  leg_entry.push_back("PU=200");
  

  vector<TString> cut;
  cut.push_back("VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20");
  cut.push_back("VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20");  

  double x[13]={20,40,60,80,100,120,140,160,180,200,220,250,300};
  int nbins = 12;


  vector<TGraphErrors*> graph;

  for(unsigned int i=0; i<filename.size(); i++){

    TGraphErrors* gr=new TGraphErrors();

    int n=0;
    for(int bin=0; bin<nbins; bin++){
      
      TH1F* histo = new TH1F();
      if(i==0)
	histo=histo_ET_resolution_noPUS(filename[i],Form(cut[i]+" && genjet_pt[VBF_parton_genjet]>%f && genjet_pt[VBF_parton_genjet]<%f",x[bin],x[bin+1]));
      else
	histo=histo_ET_resolution_PUS(filename[i],Form(cut[i]+" && genjet_pt[VBF_parton_genjet]>%f && genjet_pt[VBF_parton_genjet]<%f",x[bin],x[bin+1]));
      vector<float> eff_RMS=effectiveRMS(histo);
      gr->SetPoint(n,0.5*(x[bin]+x[bin+1]),eff_RMS[0]/(1-histo->GetMean()));
      gr->SetPointError(n,0.5*(-x[bin]+x[bin+1]),eff_RMS[1]/(1-histo->GetMean()));

      n++;

    }

    gr->SetLineWidth(2);

    if(i==0){
      gr->SetLineColor(1);
      gr->SetMarkerStyle(kFullCircle);
      gr->SetFillColor(0);
    }
    else if(i==1){
      gr->SetLineColor(2);
      gr->SetMarkerColor(2);
      gr->SetMarkerStyle(kFullCircle);
      gr->SetFillColor(0);
    }

    graph.push_back(gr);

  }


  graph[0]->GetXaxis()->SetRangeUser(10,310);
  graph[0]->GetYaxis()->SetRangeUser(0.,0.55);
  graph[0]->GetXaxis()->SetTitle("p_{T}(gen. jet) [GeV]");
  graph[0]->GetYaxis()->SetTitle("#sigma(p_{T}^{L1}/p_{T}^{gen})/<p_{T}^{L1}/p_{T}^{gen}>");
  //graph[0]->GetYaxis()->SetTitle("Resolution");
  graph[0]->GetYaxis()->SetTitleSize(0.04);
  graph[0]->GetYaxis()->SetTitleOffset(1.3);

  TLegend* leg=new TLegend(0.4,0.65,0.7,0.85);
  leg->SetHeader("1.6<|#eta(gen.jet)|<2.9");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  for(unsigned int i=0; i<graph.size();i++)
    leg->AddEntry(graph[i], leg_entry[i]);

  TCanvas *c = new TCanvas("c", "canvas", 850, 800);
  c->SetLeftMargin(0.15);
  gPad->SetTicks(1,1);

  graph[0]->Draw("AP");
  for(unsigned int i=1; i<graph.size(); i++)
    graph[i]->Draw("Psame");
  leg->Draw("same");

 TLatex *texl = new TLatex(21,0.56,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");
  gPad->SetTicks();

  c->SaveAs("plots/L1Jet_resolution_pT.pdf");

  return;


}








void plot_effRMS_eta(){

  
  vector<TString> filename;
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root");

  vector<TString> leg_entry;
  leg_entry.push_back("PU=0");
  leg_entry.push_back("PU=200");
  

  vector<TString> cut;
  cut.push_back("VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20");
  cut.push_back("VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20");  

  double x[14]={1.6,1.7,1.8,1.9,2.0,2.1,2.2,2.3,2.4,2.5,2.6,2.7,2.8,2.9};
  int nbins = 13;


  vector<TGraphErrors*> graph;

  for(unsigned int i=0; i<filename.size(); i++){

    TGraphErrors* gr=new TGraphErrors();

    int n=0;
    for(int bin=0; bin<nbins; bin++){
      
      TH1F* histo = new TH1F();
      if(i==0)
	histo=histo_ET_resolution_noPUS(filename[i],Form(cut[i]+" && abs(genjet_eta[VBF_parton_genjet])>%f && abs(genjet_eta[VBF_parton_genjet])<%f",x[bin],x[bin+1]));
      else
	histo=histo_ET_resolution_PUS(filename[i],Form(cut[i]+" && abs(genjet_eta[VBF_parton_genjet])>%f && abs(genjet_eta[VBF_parton_genjet])<%f",x[bin],x[bin+1]));
      vector<float> eff_RMS=effectiveRMS(histo);
      gr->SetPoint(n,0.5*(x[bin]+x[bin+1]),eff_RMS[0]/(1-histo->GetMean()));
      gr->SetPointError(n,0.5*(-x[bin]+x[bin+1]),eff_RMS[1]/(1-histo->GetMean()));

      n++;

    }

    gr->SetLineWidth(2);

    if(i==0){
      gr->SetLineColor(1);
      gr->SetMarkerStyle(kFullCircle);
      gr->SetFillColor(0);
    }
    else if(i==1){
      gr->SetLineColor(2);
      gr->SetMarkerColor(2);
      gr->SetMarkerStyle(kFullCircle);
      gr->SetFillColor(0);
    }

    graph.push_back(gr);

  }


  graph[0]->GetXaxis()->SetRangeUser(10,310);
  graph[0]->GetYaxis()->SetRangeUser(0.,0.55);
  graph[0]->GetXaxis()->SetTitle("|#eta(gen. jet)|");
  graph[0]->GetYaxis()->SetTitle("#sigma(p_{T}^{L1}/p_{T}^{gen})/<p_{T}^{L1}/p_{T}^{gen}>");
  //graph[0]->GetYaxis()->SetTitle("Resolution");
  graph[0]->GetYaxis()->SetTitleSize(0.04);
  graph[0]->GetYaxis()->SetTitleOffset(1.3);

  TLegend* leg=new TLegend(0.4,0.65,0.7,0.85);
  leg->SetHeader("p_{T}(gen.jet)>20 GeV");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  for(unsigned int i=0; i<graph.size();i++)
    leg->AddEntry(graph[i], leg_entry[i]);

  TCanvas *c = new TCanvas("c", "canvas", 850, 800);
  c->SetLeftMargin(0.15);
  gPad->SetTicks(1,1);

  graph[0]->Draw("AP");
  for(unsigned int i=1; i<graph.size(); i++)
    graph[i]->Draw("Psame");
  leg->Draw("same");

 TLatex *texl = new TLatex(1.51,0.56,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");
  gPad->SetTicks();

  c->SaveAs("plots/L1Jet_resolution_eta.pdf");

  return;


}








void plot_effRMS_pT_tau(){

  
  vector<TString> filename;
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root");

  vector<TString> leg_entry;
  leg_entry.push_back("PU=0");
  leg_entry.push_back("PU=200");
  

  vector<TString> cut;
  cut.push_back("gentau_jets>=0 && abs(gentau_vis_eta)>1.6 && abs(gentau_vis_eta)<2.9 && gentau_vis_pt>20 && gentau_decayMode>=0 && gentau_decayMode<=5");
  cut.push_back("gentau_jets>=0 && abs(gentau_vis_eta)>1.6 && abs(gentau_vis_eta)<2.9 && gentau_vis_pt>20 && gentau_decayMode>=0 && gentau_decayMode<=5");  

  double x[10]={20,30,40,50,60,70,80,100,150,200};
  int nbins = 9;


  vector<TGraphErrors*> graph;

  for(unsigned int i=0; i<filename.size(); i++){

    TGraphErrors* gr=new TGraphErrors();

    int n=0;
    for(int bin=0; bin<nbins; bin++){
      
      TH1F* histo = new TH1F();
      if(i==0)
	histo=histo_ET_resolution_tau_noPUS(filename[i],Form(cut[i]+" && gentau_pt>%f && gentau_pt<%f",x[bin],x[bin+1]));
      else
	histo=histo_ET_resolution_tau_PUS(filename[i],Form(cut[i]+" && gentau_pt>%f && gentau_pt<%f",x[bin],x[bin+1]));
      vector<float> eff_RMS=effectiveRMS(histo);
      gr->SetPoint(n,0.5*(x[bin]+x[bin+1]),eff_RMS[0]/(1-histo->GetMean()));
      gr->SetPointError(n,0.5*(-x[bin]+x[bin+1]),eff_RMS[1]/(1-histo->GetMean()));

      n++;

    }

    gr->SetLineWidth(2);

    if(i==0){
      gr->SetLineColor(1);
      gr->SetMarkerStyle(kFullCircle);
      gr->SetFillColor(0);
    }
    else if(i==1){
      gr->SetLineColor(2);
      gr->SetMarkerColor(2);
      gr->SetMarkerStyle(kFullCircle);
      gr->SetFillColor(0);
    }

    graph.push_back(gr);

  }


  graph[0]->GetXaxis()->SetRangeUser(10,210);
  graph[0]->GetYaxis()->SetRangeUser(0.,0.55);
  graph[0]->GetXaxis()->SetTitle("p_{T}(gen. #tau_{h}) [GeV]");
  graph[0]->GetYaxis()->SetTitle("#sigma(p_{T}^{L1}/p_{T}^{gen})/<p_{T}^{L1}/p_{T}^{gen}>");
  //graph[0]->GetYaxis()->SetTitle("Resolution");
  graph[0]->GetYaxis()->SetTitleSize(0.04);
  graph[0]->GetYaxis()->SetTitleOffset(1.3);

  TLegend* leg=new TLegend(0.4,0.65,0.7,0.85);
  leg->SetHeader("1.6<|#eta(gen. #tau_{h})|<2.9");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  for(unsigned int i=0; i<graph.size();i++)
    leg->AddEntry(graph[i], leg_entry[i]);

  TCanvas *c = new TCanvas("c", "canvas", 850, 800);
  c->SetLeftMargin(0.15);
  gPad->SetTicks(1,1);

  graph[0]->Draw("AP");
  for(unsigned int i=1; i<graph.size(); i++)
    graph[i]->Draw("Psame");
  leg->Draw("same");

 TLatex *texl = new TLatex(11,0.56,"CMS Simulation H#rightarrow#tau#tau #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");
  gPad->SetTicks();

  c->SaveAs("plots/L1Jet_resolution_pT_tau.pdf");

  return;


}








void plot_effRMS_eta_tau(){

  vector<TString> filename;
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/ggH_Htautau_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root");

  vector<TString> leg_entry;
  leg_entry.push_back("PU=0");
  leg_entry.push_back("PU=200");
  

  vector<TString> cut;
  cut.push_back("gentau_jets>=0 && abs(gentau_vis_eta)>1.6 && abs(gentau_vis_eta)<2.9 && gentau_vis_pt>20 && gentau_decayMode>=0 && gentau_decayMode<=5");
  cut.push_back("gentau_jets>=0 && abs(gentau_vis_eta)>1.6 && abs(gentau_vis_eta)<2.9 && gentau_vis_pt>20 && gentau_decayMode>=0 && gentau_decayMode<=5");  

  double x[14]={1.6,1.7,1.8,1.9,2.0,2.1,2.2,2.3,2.4,2.5,2.6,2.7,2.8,2.9};
  int nbins = 13;


  vector<TGraphErrors*> graph;

  for(unsigned int i=0; i<filename.size(); i++){

    TGraphErrors* gr=new TGraphErrors();

    int n=0;
    for(int bin=0; bin<nbins; bin++){
      
      TH1F* histo = new TH1F();
      if(i==0)
	histo=histo_ET_resolution_tau_noPUS(filename[i],Form(cut[i]+" && abs(gentau_eta)>%f && abs(gentau_eta)<%f",x[bin],x[bin+1]));
      else
	histo=histo_ET_resolution_tau_PUS(filename[i],Form(cut[i]+" && abs(gentau_eta)>%f && abs(gentau_eta)<%f",x[bin],x[bin+1]));
      vector<float> eff_RMS=effectiveRMS(histo);
      gr->SetPoint(n,0.5*(x[bin]+x[bin+1]),eff_RMS[0]/(1-histo->GetMean()));
      gr->SetPointError(n,0.5*(-x[bin]+x[bin+1]),eff_RMS[1]/(1-histo->GetMean()));

      n++;

    }

    gr->SetLineWidth(2);

    if(i==0){
      gr->SetLineColor(1);
      gr->SetMarkerStyle(kFullCircle);
      gr->SetFillColor(0);
    }
    else if(i==1){
      gr->SetLineColor(2);
      gr->SetMarkerColor(2);
      gr->SetMarkerStyle(kFullCircle);
      gr->SetFillColor(0);
    }

    graph.push_back(gr);

  }


  graph[0]->GetXaxis()->SetRangeUser(10,310);
  graph[0]->GetYaxis()->SetRangeUser(0.,0.55);
  graph[0]->GetXaxis()->SetTitle("|#eta(gen. #tau_{h})|");
  graph[0]->GetYaxis()->SetTitle("#sigma(p_{T}^{L1}/p_{T}^{gen})/<p_{T}^{L1}/p_{T}^{gen}>");
  //graph[0]->GetYaxis()->SetTitle("Resolution");
  graph[0]->GetYaxis()->SetTitleSize(0.04);
  graph[0]->GetYaxis()->SetTitleOffset(1.3);

  TLegend* leg=new TLegend(0.4,0.65,0.7,0.85);
  leg->SetHeader("p_{T}(gen. #tau_{h})>20 GeV");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  for(unsigned int i=0; i<graph.size();i++)
    leg->AddEntry(graph[i], leg_entry[i]);

  TCanvas *c = new TCanvas("c", "canvas", 850, 800);
  c->SetLeftMargin(0.15);
  gPad->SetTicks(1,1);

  graph[0]->Draw("AP");
  for(unsigned int i=1; i<graph.size(); i++)
    graph[i]->Draw("Psame");
  leg->Draw("same");

 TLatex *texl = new TLatex(1.51,0.56,"CMS Simulation H#rightarrow#tau#tau #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");
  gPad->SetTicks();

  c->SaveAs("plots/L1Jet_resolution_eta_tau.pdf");

  return;


}







void plot_effRMS_pT_dRC3D_0p03_recal_PU200(){

  
  vector<TString> filename;
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_0p03_recal/jet_ntuples_merged/ntuple_jet_merged_1*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_0p03_recal/jet_ntuples_merged/ntuple_jet_merged_1*.root");

  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 dR=0.01 default C3D cal.");
  leg_entry.push_back("PU=0 dR=0.03 C3D recal.");
  leg_entry.push_back("PU=200 dR=0.01 default C3D cal.");
  leg_entry.push_back("PU=200 dR=0.03 C3D recal.");
  

  vector<TString> cut;
  cut.push_back("VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20");
  cut.push_back("VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20");  
  cut.push_back("VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20");  
  cut.push_back("VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20");  


  double x[13]={20,40,60,80,100,120,140,160,180,200,220,250,300};
  int nbins = 12;


  vector<TGraphErrors*> graph;

  for(unsigned int i=0; i<filename.size(); i++){

    TGraphErrors* gr=new TGraphErrors();

    int n=0;
    for(int bin=0; bin<nbins; bin++){
      
      TH1F* histo = new TH1F();
      if(i==0)
	histo=histo_ET_resolution_noPUS(filename[i],Form(cut[i]+" && genjet_pt[VBF_parton_genjet]>%f && genjet_pt[VBF_parton_genjet]<%f",x[bin],x[bin+1]));
      else if(i==1)
	histo=histo_ET_resolution_noPUS_dR0p03(filename[i],Form(cut[i]+" && genjet_pt[VBF_parton_genjet]>%f && genjet_pt[VBF_parton_genjet]<%f",x[bin],x[bin+1]));
      else if(i==2)
	histo=histo_ET_resolution_PUS(filename[i],Form(cut[i]+" && genjet_pt[VBF_parton_genjet]>%f && genjet_pt[VBF_parton_genjet]<%f",x[bin],x[bin+1]));
      else
	histo=histo_ET_resolution_PUS_dR0p03(filename[i],Form(cut[i]+" && genjet_pt[VBF_parton_genjet]>%f && genjet_pt[VBF_parton_genjet]<%f",x[bin],x[bin+1]));
      vector<float> eff_RMS=effectiveRMS(histo);
      gr->SetPoint(n,0.5*(x[bin]+x[bin+1]),eff_RMS[0]/(1-histo->GetMean()));
      gr->SetPointError(n,0.5*(-x[bin]+x[bin+1]),eff_RMS[1]/(1-histo->GetMean()));

      n++;

    }

    gr->SetLineWidth(2);

    if(i==0){
      gr->SetLineColor(1);
      gr->SetMarkerStyle(kFullCircle);
      gr->SetFillColor(0);
    }
    else if(i==1){
      gr->SetLineColor(2);
      gr->SetMarkerColor(2);
      gr->SetMarkerStyle(kFullCircle);
      gr->SetFillColor(0);
    }
    else if(i==2){
      gr->SetLineColor(3);
      gr->SetMarkerColor(3);
      gr->SetMarkerStyle(kFullCircle);
      gr->SetFillColor(0);
    }
    else if(i==3){
      gr->SetLineColor(4);
      gr->SetMarkerColor(4);
      gr->SetMarkerStyle(kFullCircle);
      gr->SetFillColor(0);
    }

    graph.push_back(gr);

  }


  graph[0]->GetXaxis()->SetRangeUser(10,310);
  graph[0]->GetYaxis()->SetRangeUser(0.,0.55);
  graph[0]->GetXaxis()->SetTitle("p_{T}(gen. jet) [GeV]");
  graph[0]->GetYaxis()->SetTitle("#sigma(p_{T}^{L1}/p_{T}^{gen})/<p_{T}^{L1}/p_{T}^{gen}>");
  //graph[0]->GetYaxis()->SetTitle("Resolution");
  graph[0]->GetYaxis()->SetTitleSize(0.04);
  graph[0]->GetYaxis()->SetTitleOffset(1.3);

  TLegend* leg=new TLegend(0.4,0.65,0.7,0.85);
  leg->SetHeader("1.6<|#eta(gen.jet)|<2.9");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  for(unsigned int i=0; i<graph.size();i++)
    leg->AddEntry(graph[i], leg_entry[i]);

  TCanvas *c = new TCanvas("c", "canvas", 850, 800);
  c->SetLeftMargin(0.15);
  gPad->SetTicks(1,1);

  graph[0]->Draw("AP");
  for(unsigned int i=1; i<graph.size(); i++)
    graph[i]->Draw("Psame");
  leg->Draw("same");

 TLatex *texl = new TLatex(21,0.56,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");
  gPad->SetTicks();

  c->SaveAs("plots/L1Jet_resolution_pT_dRC3D_0p03_recal_PU200.pdf");

  return;


}









void plot_effRMS_pT_C3D_histo_PU0(){

  
  vector<TString> filename;
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_old/jet_ntuples_merged/ntuple_jet_merged_*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root");


  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 cone");
  leg_entry.push_back("PU=0 histo old");
  leg_entry.push_back("PU=0 histo new");
  

  vector<TString> cut;
  cut.push_back("VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20");
  cut.push_back("VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20");   
  cut.push_back("VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20");   


  double x[13]={20,40,60,80,100,120,140,160,180,200,220,250,300};
  int nbins = 12;


  vector<TGraphErrors*> graph;

  for(unsigned int i=0; i<filename.size(); i++){

    TGraphErrors* gr=new TGraphErrors();

    int n=0;
    for(int bin=0; bin<nbins; bin++){
      
      TH1F* histo;
      if(i<2) histo = histo_ET_resolution_noPUS(filename[i],Form(cut[i]+" && genjet_pt[VBF_parton_genjet]>%f && genjet_pt[VBF_parton_genjet]<%f",x[bin],x[bin+1]));
      else histo = histo_ET_resolution_noPUS_histo(filename[i],Form(cut[i]+" && genjet_pt[VBF_parton_genjet]>%f && genjet_pt[VBF_parton_genjet]<%f",x[bin],x[bin+1]));
      vector<float> eff_RMS=effectiveRMS(histo);
      gr->SetPoint(n,0.5*(x[bin]+x[bin+1]),eff_RMS[0]/(1-histo->GetMean()));
      gr->SetPointError(n,0.5*(-x[bin]+x[bin+1]),eff_RMS[1]/(1-histo->GetMean()));

      n++;

    }

    gr->SetLineWidth(2);

    if(i==0){
      gr->SetLineColor(1);
      gr->SetMarkerStyle(kFullCircle);
      gr->SetFillColor(0);
    }
    else if(i==1){
      gr->SetLineColor(2);
      gr->SetMarkerColor(2);
      gr->SetMarkerStyle(kFullCircle);
      gr->SetFillColor(0);
    }
    else if(i==2){
      gr->SetLineColor(3);
      gr->SetMarkerColor(3);
      gr->SetMarkerStyle(kFullCircle);
      gr->SetFillColor(0);
    }
    else if(i==3){
      gr->SetLineColor(4);
      gr->SetMarkerColor(4);
      gr->SetMarkerStyle(kFullCircle);
      gr->SetFillColor(0);
    }

    graph.push_back(gr);

  }


  graph[0]->GetXaxis()->SetRangeUser(10,310);
  graph[0]->GetYaxis()->SetRangeUser(0.,0.55);
  graph[0]->GetXaxis()->SetTitle("p_{T}(gen. jet) [GeV]");
  graph[0]->GetYaxis()->SetTitle("#sigma(p_{T}^{L1}/p_{T}^{gen})/<p_{T}^{L1}/p_{T}^{gen}>");
  //graph[0]->GetYaxis()->SetTitle("Resolution");
  graph[0]->GetYaxis()->SetTitleSize(0.04);
  graph[0]->GetYaxis()->SetTitleOffset(1.3);

  TLegend* leg=new TLegend(0.4,0.65,0.7,0.85);
  leg->SetHeader("1.6<|#eta(gen.jet)|<2.9");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  for(unsigned int i=0; i<graph.size();i++)
    leg->AddEntry(graph[i], leg_entry[i]);

  TCanvas *c = new TCanvas("c", "canvas", 850, 800);
  c->SetLeftMargin(0.15);
  gPad->SetTicks(1,1);

  graph[0]->Draw("AP");
  for(unsigned int i=1; i<graph.size(); i++)
    graph[i]->Draw("Psame");
  leg->Draw("same");

 TLatex *texl = new TLatex(21,0.56,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");
  gPad->SetTicks();

  c->SaveAs("plots/L1Jet_resolution_pT_C3D_histo.pdf");

  return;


}








void plot_effRMS_pT_C3D_histo_PU200(){

  
  vector<TString> filename;
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto_old/jet_ntuples_merged/ntuple_jet_merged_*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root");


  vector<TString> leg_entry;
  leg_entry.push_back("PU=200 cone");
  leg_entry.push_back("PU=200 histo old");
  leg_entry.push_back("PU=200 histo new");
  

  vector<TString> cut;
  cut.push_back("VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20");
  cut.push_back("VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20");   
  cut.push_back("VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20");   


  double x[13]={20,40,60,80,100,120,140,160,180,200,220,250,300};
  int nbins = 12;


  vector<TGraphErrors*> graph;

  for(unsigned int i=0; i<filename.size(); i++){

    TGraphErrors* gr=new TGraphErrors();

    int n=0;
    for(int bin=0; bin<nbins; bin++){
      
      TH1F* histo;
      if(i==0) histo = histo_ET_resolution_PUS(filename[i],Form(cut[i]+" && genjet_pt[VBF_parton_genjet]>%f && genjet_pt[VBF_parton_genjet]<%f",x[bin],x[bin+1]));
      else if(i==1) histo = histo_ET_resolution_PUS_histo_old(filename[i],Form(cut[i]+" && genjet_pt[VBF_parton_genjet]>%f && genjet_pt[VBF_parton_genjet]<%f",x[bin],x[bin+1]));
      else if(i==2) histo = histo_ET_resolution_PUS_histo(filename[i],Form(cut[i]+" && genjet_pt[VBF_parton_genjet]>%f && genjet_pt[VBF_parton_genjet]<%f",x[bin],x[bin+1]));

      vector<float> eff_RMS=effectiveRMS(histo);
      gr->SetPoint(n,0.5*(x[bin]+x[bin+1]),eff_RMS[0]/(1-histo->GetMean()));
      gr->SetPointError(n,0.5*(-x[bin]+x[bin+1]),eff_RMS[1]/(1-histo->GetMean()));

      n++;

    }

    gr->SetLineWidth(2);

    if(i==0){
      gr->SetLineColor(1);
      gr->SetMarkerStyle(kFullCircle);
      gr->SetFillColor(0);
    }
    else if(i==1){
      gr->SetLineColor(2);
      gr->SetMarkerColor(2);
      gr->SetMarkerStyle(kFullCircle);
      gr->SetFillColor(0);
    }
    else if(i==2){
      gr->SetLineColor(3);
      gr->SetMarkerColor(3);
      gr->SetMarkerStyle(kFullCircle);
      gr->SetFillColor(0);
    }
    else if(i==3){
      gr->SetLineColor(4);
      gr->SetMarkerColor(4);
      gr->SetMarkerStyle(kFullCircle);
      gr->SetFillColor(0);
    }

    graph.push_back(gr);

  }


  graph[0]->GetXaxis()->SetRangeUser(10,310);
  graph[0]->GetYaxis()->SetRangeUser(0.,0.55);
  graph[0]->GetXaxis()->SetTitle("p_{T}(gen. jet) [GeV]");
  graph[0]->GetYaxis()->SetTitle("#sigma(p_{T}^{L1}/p_{T}^{gen})/<p_{T}^{L1}/p_{T}^{gen}>");
  //graph[0]->GetYaxis()->SetTitle("Resolution");
  graph[0]->GetYaxis()->SetTitleSize(0.04);
  graph[0]->GetYaxis()->SetTitleOffset(1.3);

  TLegend* leg=new TLegend(0.4,0.65,0.7,0.85);
  leg->SetHeader("1.6<|#eta(gen.jet)|<2.9");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  for(unsigned int i=0; i<graph.size();i++)
    leg->AddEntry(graph[i], leg_entry[i]);

  TCanvas *c = new TCanvas("c", "canvas", 850, 800);
  c->SetLeftMargin(0.15);
  gPad->SetTicks(1,1);

  graph[0]->Draw("AP");
  for(unsigned int i=1; i<graph.size(); i++)
    graph[i]->Draw("Psame");
  leg->Draw("same");

 TLatex *texl = new TLatex(21,0.56,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");
  gPad->SetTicks();

  c->SaveAs("plots/L1Jet_resolution_pT_C3D_histo_PU200.pdf");

  return;


}












void plot_effRMS_pT_C3D_histo_PU0_test(){

  
  vector<TString> filename;
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C3D_polarHisto_dR0p03/jet_ntuples_merged/ntuple_jet_merged_*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_thresh_20MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_thresh_50MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root");

  vector<TString> leg_entry;
 leg_entry.push_back("Cone dr=0.01");
  leg_entry.push_back("Histo dr=0.01 Max. finding");
  leg_entry.push_back("Histo dr=0.03 Max. finding");
  leg_entry.push_back("Histo dr=0.01 20 MIPT-thresh.");
  leg_entry.push_back("Histo dr=0.01 50 MIPT-thresh.");

  

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";
  vector<TString> cuts;
  cuts.push_back(cut);
  cuts.push_back(cut);
  cuts.push_back(cut);
  cuts.push_back(cut);
  cuts.push_back(cut);

  vector<TString> var;
  var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]");
  var.push_back("1.17*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.07929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]");
  var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]");
  var.push_back("1.10*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.01929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]");
  var.push_back("1.20*(4.98004e+00 -1.25767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]");


  double x[13]={20,40,60,80,100,120,140,160,180,200,220,250,300};
  int nbins = 12;


  vector<TGraphErrors*> graph;

  for(unsigned int i=0; i<filename.size(); i++){

    TGraphErrors* gr=new TGraphErrors();

    int n=0;
    for(int bin=0; bin<nbins; bin++){

      TH1F* histo = histo_ET_resolution_noPUS(filename[i],var[i], Form(cuts[i]+" && genjet_pt[VBF_parton_genjet]>%f && genjet_pt[VBF_parton_genjet]<%f",x[bin],x[bin+1]));   
      vector<float> eff_RMS=effectiveRMS(histo);
      gr->SetPoint(n,0.5*(x[bin]+x[bin+1]),eff_RMS[0]/(histo->GetMean()));
      gr->SetPointError(n,0.5*(-x[bin]+x[bin+1]),eff_RMS[1]/(histo->GetMean()));
      n++;

    }

    gr->SetLineWidth(2);
    gr->SetLineColor(i+1);
    if(i>0) gr->SetMarkerColor(i+1);
    if(i>3){
      gr->SetLineColor(i+2);
      if(i>0) gr->SetMarkerColor(i+2);
    }

    gr->SetMarkerStyle(kFullCircle);
    gr->SetFillColor(0);
    
    graph.push_back(gr);

  }


  graph[0]->GetXaxis()->SetRangeUser(10,310);
  graph[0]->GetYaxis()->SetRangeUser(0.,0.55);
  graph[0]->GetXaxis()->SetTitle("p_{T}(gen. jet) [GeV]");
  graph[0]->GetYaxis()->SetTitle("#sigma(p_{T}^{L1}/p_{T}^{gen})/<p_{T}^{L1}/p_{T}^{gen}>");
  //graph[0]->GetYaxis()->SetTitle("Resolution");
  graph[0]->GetYaxis()->SetTitleSize(0.04);
  graph[0]->GetYaxis()->SetTitleOffset(1.3);

  TLegend* leg=new TLegend(0.4,0.65,0.7,0.85);
  leg->SetHeader("1.6<|#eta(gen.jet)|<2.9");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  for(unsigned int i=0; i<graph.size();i++)
    leg->AddEntry(graph[i], leg_entry[i]);

  TCanvas *c = new TCanvas("c", "canvas", 850, 800);
  c->SetLeftMargin(0.15);
  gPad->SetTicks(1,1);

  graph[0]->Draw("AP");
  for(unsigned int i=1; i<graph.size(); i++)
    graph[i]->Draw("Psame");
  leg->Draw("same");

 TLatex *texl = new TLatex(21,0.56,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV PU=0");
  texl->SetTextSize(0.03);
  texl->Draw("same");
  gPad->SetTicks();

  c->SaveAs("plots/L1Jet_resolution_pT_C3D_histo_test.pdf");

  return;


}








void plot_effRMS_pT_C3D_histo_PU0_test_etaLower2p4(){

  
  vector<TString> filename;
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C3D_polarHisto_dR0p03/jet_ntuples_merged/ntuple_jet_merged_*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_thresh_20MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_thresh_50MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root");

  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 cone dr=0.01");
  leg_entry.push_back("PU=0 histo dr=0.01");
  leg_entry.push_back("PU=0 histo dr=0.03");
  leg_entry.push_back("PU=0 histo dr=0.01 20 MIPT-thresh.");
  leg_entry.push_back("PU=0 histo dr=0.01 50 MIPT-thresh.");
  

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.4 && genjet_pt[VBF_parton_genjet]>20";
  vector<TString> cuts;
  cuts.push_back(cut);
  cuts.push_back(cut);
  cuts.push_back(cut);
  cuts.push_back(cut);
  cuts.push_back(cut);

  vector<TString> var;
  var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]");
  var.push_back("1.17*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.07929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]");
  var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]");
  var.push_back("1.10*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.01929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]");
  var.push_back("1.20*(4.98004e+00 -1.25767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]");


  double x[13]={20,40,60,80,100,120,140,160,180,200,220,250,300};
  int nbins = 12;


  vector<TGraphErrors*> graph;

  for(unsigned int i=0; i<filename.size(); i++){

    TGraphErrors* gr=new TGraphErrors();

    int n=0;
    for(int bin=0; bin<nbins; bin++){

      TH1F* histo = histo_ET_resolution_noPUS(filename[i],var[i], Form(cuts[i]+" && genjet_pt[VBF_parton_genjet]>%f && genjet_pt[VBF_parton_genjet]<%f",x[bin],x[bin+1]));   
      vector<float> eff_RMS=effectiveRMS(histo);
      gr->SetPoint(n,0.5*(x[bin]+x[bin+1]),eff_RMS[0]/(histo->GetMean()));
      gr->SetPointError(n,0.5*(-x[bin]+x[bin+1]),eff_RMS[1]/(histo->GetMean()));
      n++;

    }

    gr->SetLineWidth(2);
    gr->SetLineColor(i+1);
    if(i>0) gr->SetMarkerColor(i+1);
    if(i>3){
      gr->SetLineColor(i+2);
      if(i>0) gr->SetMarkerColor(i+2);
    }

    gr->SetMarkerStyle(kFullCircle);
    gr->SetFillColor(0);
    
    graph.push_back(gr);

  }


  graph[0]->GetXaxis()->SetRangeUser(10,310);
  graph[0]->GetYaxis()->SetRangeUser(0.,0.55);
  graph[0]->GetXaxis()->SetTitle("p_{T}(gen. jet) [GeV]");
  graph[0]->GetYaxis()->SetTitle("#sigma(p_{T}^{L1}/p_{T}^{gen})/<p_{T}^{L1}/p_{T}^{gen}>");
  //graph[0]->GetYaxis()->SetTitle("Resolution");
  graph[0]->GetYaxis()->SetTitleSize(0.04);
  graph[0]->GetYaxis()->SetTitleOffset(1.3);

  TLegend* leg=new TLegend(0.4,0.65,0.7,0.85);
  leg->SetHeader("1.6<|#eta(gen.jet)|<2.4");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  for(unsigned int i=0; i<graph.size();i++)
    leg->AddEntry(graph[i], leg_entry[i]);

  TCanvas *c = new TCanvas("c", "canvas", 850, 800);
  c->SetLeftMargin(0.15);
  gPad->SetTicks(1,1);

  graph[0]->Draw("AP");
  for(unsigned int i=1; i<graph.size(); i++)
    graph[i]->Draw("Psame");
  leg->Draw("same");

 TLatex *texl = new TLatex(21,0.56,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");
  gPad->SetTicks();

  c->SaveAs("plots/L1Jet_resolution_pT_C3D_histo_test_etaLower2p4.pdf");

  return;


}









void plot_effRMS_pT_C3D_histo_PU0_test_etaLarger2p4(){

  
  vector<TString> filename;
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C3D_polarHisto_dR0p03/jet_ntuples_merged/ntuple_jet_merged_*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_thresh_20MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_thresh_50MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root");

  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 cone dr=0.01");
  leg_entry.push_back("PU=0 histo dr=0.01");
  leg_entry.push_back("PU=0 histo dr=0.03");
  leg_entry.push_back("PU=0 histo dr=0.01 20 MIPT-thresh.");
  leg_entry.push_back("PU=0 histo dr=0.01 50 MIPT-thresh.");
  

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>2.4 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";
  vector<TString> cuts;
  cuts.push_back(cut);
  cuts.push_back(cut);
  cuts.push_back(cut);
  cuts.push_back(cut);
  cuts.push_back(cut);

  vector<TString> var;
  var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]");
  var.push_back("1.17*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.07929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]");
  var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]");
  var.push_back("1.10*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.01929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]");
  var.push_back("1.20*(4.98004e+00 -1.25767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]");


  double x[13]={20,40,60,80,100,120,140,160,180,200,220,250,300};
  int nbins = 12;


  vector<TGraphErrors*> graph;

  for(unsigned int i=0; i<filename.size(); i++){

    TGraphErrors* gr=new TGraphErrors();

    int n=0;
    for(int bin=0; bin<nbins; bin++){

      TH1F* histo = histo_ET_resolution_noPUS(filename[i],var[i], Form(cuts[i]+" && genjet_pt[VBF_parton_genjet]>%f && genjet_pt[VBF_parton_genjet]<%f",x[bin],x[bin+1]));   
      vector<float> eff_RMS=effectiveRMS(histo);
      gr->SetPoint(n,0.5*(x[bin]+x[bin+1]),eff_RMS[0]/(histo->GetMean()));
      gr->SetPointError(n,0.5*(-x[bin]+x[bin+1]),eff_RMS[1]/(histo->GetMean()));
      n++;

    }

    gr->SetLineWidth(2);
    gr->SetLineColor(i+1);
    if(i>0) gr->SetMarkerColor(i+1);
    if(i>3){
      gr->SetLineColor(i+2);
      if(i>0) gr->SetMarkerColor(i+2);
    }

    gr->SetMarkerStyle(kFullCircle);
    gr->SetFillColor(0);
    
    graph.push_back(gr);

  }


  graph[0]->GetXaxis()->SetRangeUser(10,310);
  graph[0]->GetYaxis()->SetRangeUser(0.,0.55);
  graph[0]->GetXaxis()->SetTitle("p_{T}(gen. jet) [GeV]");
  graph[0]->GetYaxis()->SetTitle("#sigma(p_{T}^{L1}/p_{T}^{gen})/<p_{T}^{L1}/p_{T}^{gen}>");
  //graph[0]->GetYaxis()->SetTitle("Resolution");
  graph[0]->GetYaxis()->SetTitleSize(0.04);
  graph[0]->GetYaxis()->SetTitleOffset(1.3);

  TLegend* leg=new TLegend(0.4,0.65,0.7,0.85);
  leg->SetHeader("2.4<|#eta(gen.jet)|<2.9");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  for(unsigned int i=0; i<graph.size();i++)
    leg->AddEntry(graph[i], leg_entry[i]);

  TCanvas *c = new TCanvas("c", "canvas", 850, 800);
  c->SetLeftMargin(0.15);
  gPad->SetTicks(1,1);

  graph[0]->Draw("AP");
  for(unsigned int i=1; i<graph.size(); i++)
    graph[i]->Draw("Psame");
  leg->Draw("same");

 TLatex *texl = new TLatex(21,0.56,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");
  gPad->SetTicks();

  c->SaveAs("plots/L1Jet_resolution_pT_C3D_histo_test_etaLarger2p4.pdf");

  return;


}











void plot_effRMS_pT_C3D_histo_PU200_test(){

  
  vector<TString> filename;
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto/jet_ntuples_merged/ntuple_jet_merged_*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C3D_polarHisto_dR0p03/jet_ntuples_merged/ntuple_jet_merged_*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto_thresh_20MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto_thresh_50MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root");

  vector<TString> leg_entry;
 leg_entry.push_back("Cone dr=0.01");
  leg_entry.push_back("Histo dr=0.01 Max. finding");
  leg_entry.push_back("Histo dr=0.03 Max. finding");
  leg_entry.push_back("Histo dr=0.01 20 MIPT-thresh.");
  leg_entry.push_back("Histo dr=0.01 50 MIPT-thresh.");
  

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";
  vector<TString> cuts;
  cuts.push_back(cut + "&& (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0");
  cuts.push_back(cut + "&& (jets_pt[VBF_parton_jets]-1.1*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0");
  cuts.push_back(cut + "&& (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0");
  cuts.push_back(cut + "&& (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0");
  cuts.push_back(cut + "&& (jets_pt[VBF_parton_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0");

  vector<TString> var;
  var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]");
  var.push_back("1.17*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-1.1*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.07929e-01* pow(log(max(jets_pt[VBF_parton_jets]-1.1*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-1.1*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]");
  var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]");
  var.push_back("1.10*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.01929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]");
  var.push_back("1.20*(4.98004e+00 -1.25767e+00 * log(max(jets_pt[VBF_parton_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-1.5*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]");


  double x[13]={20,40,60,80,100,120,140,160,180,200,220,250,300};
  int nbins = 12;


  vector<TGraphErrors*> graph;

  for(unsigned int i=0; i<filename.size(); i++){

    TGraphErrors* gr=new TGraphErrors();

    int n=0;
    for(int bin=0; bin<nbins; bin++){

      TH1F* histo = histo_ET_resolution_noPUS(filename[i],var[i], Form(cuts[i]+" && genjet_pt[VBF_parton_genjet]>%f && genjet_pt[VBF_parton_genjet]<%f",x[bin],x[bin+1]));   
      vector<float> eff_RMS=effectiveRMS(histo);
      gr->SetPoint(n,0.5*(x[bin]+x[bin+1]),eff_RMS[0]/(histo->GetMean()));
      gr->SetPointError(n,0.5*(-x[bin]+x[bin+1]),eff_RMS[1]/(histo->GetMean()));
      n++;

    }

    gr->SetLineWidth(2);
    gr->SetLineColor(i+1);
    if(i>0) gr->SetMarkerColor(i+1);
    if(i>3){
      gr->SetLineColor(i+2);
      if(i>0) gr->SetMarkerColor(i+2);
    }

    gr->SetMarkerStyle(kFullCircle);
    gr->SetFillColor(0);
    
    graph.push_back(gr);

  }


  graph[0]->GetXaxis()->SetRangeUser(10,310);
  graph[0]->GetYaxis()->SetRangeUser(0.,0.75);
  graph[0]->GetXaxis()->SetTitle("p_{T}(gen. jet) [GeV]");
  graph[0]->GetYaxis()->SetTitle("#sigma(p_{T}^{L1}/p_{T}^{gen})/<p_{T}^{L1}/p_{T}^{gen}>");
  //graph[0]->GetYaxis()->SetTitle("Resolution");
  graph[0]->GetYaxis()->SetTitleSize(0.04);
  graph[0]->GetYaxis()->SetTitleOffset(1.3);

  TLegend* leg=new TLegend(0.35,0.65,0.7,0.85);
  leg->SetHeader("1.6<|#eta(gen.jet)|<2.9");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  for(unsigned int i=0; i<graph.size();i++)
    leg->AddEntry(graph[i], leg_entry[i]);

  TCanvas *c = new TCanvas("c", "canvas", 850, 800);
  c->SetLeftMargin(0.15);
  gPad->SetTicks(1,1);

  graph[0]->Draw("AP");
  for(unsigned int i=1; i<graph.size(); i++)
    graph[i]->Draw("Psame");
  leg->Draw("same");

 TLatex *texl = new TLatex(21,0.76,"CMS Simulation VBF H#rightarrowinv. PU=200 #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");
  gPad->SetTicks();

  c->SaveAs("plots/L1Jet_resolution_pT_C3D_histo_PU200_test.pdf");

  return;


}








void plot_effRMS_pT_C3D_histo_PU0_TC(){
  //qwerty
  
  vector<TString> filename;
  filename.push_back("/vols/cms/snwebb/HGC_ntuples/VBF_Hinv_PU0_C3D_polarHisto_refinedMax/jet_ntuples_merged/ntuple_jet_merged_*.root");
  filename.push_back("/vols/cms/snwebb/HGC_ntuples/VBF_Hinv_PU0_C3D_polarHisto_crossRefinedMax/jet_ntuples_merged/ntuple_jet_merged_*.root");
  // filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_1*.root");
  // filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C3D_polarHisto_dR0p03/jet_ntuples_merged/ntuple_jet_merged_*.root");
  // filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_thresh_20MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root");
  // filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C3D_polarHisto_dR0p03_TC/jet_ntuples_merged/ntuple_jet_merged_*.root");
  // filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRC3D_polarHisto_thresh_20MIPT_TC/jet_ntuples_merged/ntuple_jet_merged_*.root");
  filename.push_back("/vols/cms/snwebb/HGC_ntuples/VBF_Hinv_PU0_C3D_polarHisto_refinedMax_TC/jet_ntuples_merged/ntuple_jet_merged_*.root");
  filename.push_back("/vols/cms/snwebb/HGC_ntuples/VBF_Hinv_PU0_C3D_polarHisto_crossRefinedMax_TC/jet_ntuples_merged/ntuple_jet_merged_*.root");

  vector<TString> leg_entry;
  leg_entry.push_back("C2D + Histo dr=0.01 Max. finding refined");
  leg_entry.push_back("C2D + Histo dr=0.01 Max. finding cross refined");
  // leg_entry.push_back("C2D + Cone dr=0.01");
  // leg_entry.push_back("C2D + Histo dr=0.03 Max. finding");
  // leg_entry.push_back("C2D + Histo dr=0.01 20 MIPT-thresh.");
  // leg_entry.push_back("TC + Histo dr=0.03 Max. finding");
  // leg_entry.push_back("TC + Histo dr=0.01 20 MIPT-thresh.");
  leg_entry.push_back("TC + Histo dr=0.01 Max. finding refined");
  leg_entry.push_back("TC + Histo dr=0.01 Max. finding cross refined");


  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";
  vector<TString> cuts;
  cuts.push_back(cut);
  cuts.push_back(cut);
  // cuts.push_back(cut);
  // cuts.push_back(cut);
  // cuts.push_back(cut);
  // cuts.push_back(cut);
  // cuts.push_back(cut);
  cuts.push_back(cut);
  cuts.push_back(cut);

  vector<TString> var;
  var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]");
  var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]");
  // var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]");
  // var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]");
  // var.push_back("1.10*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.01929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]");
  // var.push_back("0.84*(5.09004e+00 -1.22767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]");
  // var.push_back("0.98*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.00929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]");
  var.push_back("0.84*(5.09004e+00 -1.22767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]");
  var.push_back("0.84*(5.09004e+00 -1.22767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]");

  double x[13]={20,40,60,80,100,120,140,160,180,200,220,250,300};
  int nbins = 12;


  vector<TGraphErrors*> graph;

  for(unsigned int i=0; i<filename.size(); i++){

    TGraphErrors* gr=new TGraphErrors();

    int n=0;
    for(int bin=0; bin<nbins; bin++){

      TH1F* histo = histo_ET_resolution_noPUS(filename[i],var[i], Form(cuts[i]+" && genjet_pt[VBF_parton_genjet]>%f && genjet_pt[VBF_parton_genjet]<%f",x[bin],x[bin+1]));   
      vector<float> eff_RMS=effectiveRMS(histo);
      gr->SetPoint(n,0.5*(x[bin]+x[bin+1]),eff_RMS[0]/(histo->GetMean()));
      gr->SetPointError(n,0.5*(-x[bin]+x[bin+1]),eff_RMS[1]/(histo->GetMean()));
      n++;

    }

    gr->SetLineWidth(2);
    gr->SetLineColor(i+1);
    if(i>0) gr->SetMarkerColor(i+1);
    if(i>3){
      gr->SetLineColor(i+2);
      if(i>0) gr->SetMarkerColor(i+2);
    }

    gr->SetMarkerStyle(kFullCircle);
    gr->SetFillColor(0);
    
    graph.push_back(gr);

  }


  graph[0]->GetXaxis()->SetRangeUser(10,310);
  graph[0]->GetYaxis()->SetRangeUser(0.,0.55);
  graph[0]->GetXaxis()->SetTitle("p_{T}(gen. jet) [GeV]");
  graph[0]->GetYaxis()->SetTitle("#sigma(p_{T}^{L1}/p_{T}^{gen})/<p_{T}^{L1}/p_{T}^{gen}>");
  //graph[0]->GetYaxis()->SetTitle("Resolution");
  graph[0]->GetYaxis()->SetTitleSize(0.04);
  graph[0]->GetYaxis()->SetTitleOffset(1.3);

  TLegend* leg=new TLegend(0.4,0.65,0.7,0.85);
  leg->SetHeader("1.6<|#eta(gen.jet)|<2.9");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  for(unsigned int i=0; i<graph.size();i++)
    leg->AddEntry(graph[i], leg_entry[i]);

  TCanvas *c = new TCanvas("c", "canvas", 850, 800);
  c->SetLeftMargin(0.15);
  gPad->SetTicks(1,1);

  graph[0]->Draw("AP");
  for(unsigned int i=1; i<graph.size(); i++)
    graph[i]->Draw("Psame");
  leg->Draw("same");

 TLatex *texl = new TLatex(21,0.56,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV PU=0");
  texl->SetTextSize(0.03);
  texl->Draw("same");
  gPad->SetTicks();

  c->SaveAs("plots/L1Jet_resolution_pT_C3D_histo_TC.pdf");

  return;


}










void plot_effRMS_pT_C3D_histo_PU200_TC(){

  
  vector<TString> filename;
  //  filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root");
  //  filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C3D_polarHisto_dR0p03/jet_ntuples_merged/ntuple_jet_merged_*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto_thresh_20MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root");
  filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C3D_polarHisto_dR0p03_TC/jet_ntuples_merged/ntuple_jet_merged_*.root");


  filename.push_back("/vols/cms/snwebb/HGC_ntuples/VBF_Hinv_PU200_C3D_polarHisto_nosmear_thresh_20MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root");
  filename.push_back("/vols/cms/snwebb/HGC_ntuples/VBF_Hinv_PU200_C3D_polarHisto_nosmear_Max_dR0p03_TC/jet_ntuples_merged/ntuple_jet_merged_*.root");

  //  filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto_thresh_20MIPT_TC/jet_ntuples_merged/ntuple_jet_merged_*.root");

  vector<TString> leg_entry;
  //  leg_entry.push_back("C2D + Cone dr=0.01");
  //  leg_entry.push_back("C2D + Histo dr=0.03 Max. finding");
  leg_entry.push_back("C2D + Histo dr=0.01 20 MIPT-thresh.");
  leg_entry.push_back("TC + Histo dr=0.03 Max. finding");
  //  leg_entry.push_back("TC + Histo dr=0.01 20 MIPT-thresh.");

  leg_entry.push_back("C2D + Histo dr=0.01 20 MIPT-thresh. no smear");
  leg_entry.push_back("TC + Histo dr=0.03 Max. finding no smear");

  

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";
  vector<TString> cuts;
  cuts.push_back(cut + "&& (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0");
  // cuts.push_back(cut + "&& (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0");
  // cuts.push_back(cut + "&& (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0");
  //  cuts.push_back(cut + "&& (jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0");
  cuts.push_back(cut + "&& (jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0");

  cuts.push_back(cut + "&& (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0");
  cuts.push_back(cut + "&& (jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0");

  vector<TString> var;
  // var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]");
  // var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]");
  var.push_back("1.10*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.01929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]");

  var.push_back("0.84*(5.09004e+00 -1.22767e+00 * log(max(jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * (jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])/genjet_pt[VBF_parton_genjet]");

  // var.push_back("0.98*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.00929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * (jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])/genjet_pt[VBF_parton_genjet]");






  var.push_back("1.10*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.01929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]");

  var.push_back("0.84*(5.09004e+00 -1.22767e+00 * log(max(jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * (jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])/genjet_pt[VBF_parton_genjet]");


  double x[13]={20,40,60,80,100,120,140,160,180,200,220,250,300};
  int nbins = 12;


  vector<TGraphErrors*> graph;

  for(unsigned int i=0; i<filename.size(); i++){

    TGraphErrors* gr=new TGraphErrors();

    int n=0;
    for(int bin=0; bin<nbins; bin++){

      TH1F* histo = histo_ET_resolution_noPUS(filename[i],var[i], Form(cuts[i]+" && genjet_pt[VBF_parton_genjet]>%f && genjet_pt[VBF_parton_genjet]<%f",x[bin],x[bin+1]));   
      vector<float> eff_RMS=effectiveRMS(histo);
      gr->SetPoint(n,0.5*(x[bin]+x[bin+1]),eff_RMS[0]/(histo->GetMean()));
      gr->SetPointError(n,0.5*(-x[bin]+x[bin+1]),eff_RMS[1]/(histo->GetMean()));
      n++;

    }

    gr->SetLineWidth(2);
    gr->SetLineColor(i+1);
    if(i>0) gr->SetMarkerColor(i+1);
    if(i>3){
      gr->SetLineColor(i+2);
      if(i>0) gr->SetMarkerColor(i+2);
    }

    gr->SetMarkerStyle(kFullCircle);
    gr->SetFillColor(0);
    
    graph.push_back(gr);

  }


  graph[0]->GetXaxis()->SetRangeUser(10,310);
  graph[0]->GetYaxis()->SetRangeUser(0.,0.75);
  graph[0]->GetXaxis()->SetTitle("p_{T}(gen. jet) [GeV]");
  graph[0]->GetYaxis()->SetTitle("#sigma(p_{T}^{L1}/p_{T}^{gen})/<p_{T}^{L1}/p_{T}^{gen}>");
  //graph[0]->GetYaxis()->SetTitle("Resolution");
  graph[0]->GetYaxis()->SetTitleSize(0.04);
  graph[0]->GetYaxis()->SetTitleOffset(1.3);

  TLegend* leg=new TLegend(0.35,0.65,0.7,0.85);
  leg->SetHeader("1.6<|#eta(gen.jet)|<2.9");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  for(unsigned int i=0; i<graph.size();i++)
    leg->AddEntry(graph[i], leg_entry[i]);

  TCanvas *c = new TCanvas("c", "canvas", 850, 800);
  c->SetLeftMargin(0.15);
  gPad->SetTicks(1,1);

  graph[0]->Draw("AP");
  for(unsigned int i=1; i<graph.size(); i++)
    graph[i]->Draw("Psame");
  leg->Draw("same");

 TLatex *texl = new TLatex(21,0.76,"CMS Simulation VBF H#rightarrowinv. PU=200 #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");
  gPad->SetTicks();

  c->SaveAs("plots/L1Jet_resolution_pT_C3D_histo_PU200_TC.pdf");

  return;


}








//NEW 

void plot_effRMS_pT_C3D_histo_PU0_refinedmax(){

  vector<TString> filename;
  filename.push_back("/vols/cms/snwebb/HGC_ntuples/VBF_Hinv_PU0_C3D_polarHisto_refinedMax/jet_ntuples_merged/ntuple_jet_merged_*.root");
  // filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C3D_polarHisto_dR0p03/jet_ntuples_merged/ntuple_jet_merged_*.root");
  // filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto_thresh_20MIPT/jet_ntuples_merged/ntuple_jet_merged_*.root");
  // filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C3D_polarHisto_dR0p03_TC/jet_ntuples_merged/ntuple_jet_merged_*.root");
  // filename.push_back("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRC3D_polarHisto_thresh_20MIPT_TC/jet_ntuples_merged/ntuple_jet_merged_*.root");

  vector<TString> leg_entry;
  leg_entry.push_back("Refined maximum");
  // leg_entry.push_back("C2D + Histo dr=0.03 Max. finding");
  // leg_entry.push_back("C2D + Histo dr=0.01 20 MIPT-thresh.");
  // leg_entry.push_back("TC + Histo dr=0.03 Max. finding");
  // leg_entry.push_back("TC + Histo dr=0.01 20 MIPT-thresh.");

  

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";
  vector<TString> cuts;
  cuts.push_back(cut + "&& (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0");
  cuts.push_back(cut + "&& (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0");
  cuts.push_back(cut + "&& (jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0");
  cuts.push_back(cut + "&& (jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0");
  cuts.push_back(cut + "&& (jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])>0");

  vector<TString> var;
  var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]");
  var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]");
  var.push_back("1.10*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.01929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)/genjet_pt[VBF_parton_genjet]");
  var.push_back("0.84*(5.09004e+00 -1.22767e+00 * log(max(jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * (jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])/genjet_pt[VBF_parton_genjet]");
  var.push_back("0.98*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.00929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * (jets_pt[VBF_parton_jets]-2.6*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets])/genjet_pt[VBF_parton_genjet]");


  double x[13]={20,40,60,80,100,120,140,160,180,200,220,250,300};
  int nbins = 12;


  vector<TGraphErrors*> graph;

  for(unsigned int i=0; i<filename.size(); i++){

    TGraphErrors* gr=new TGraphErrors();

    int n=0;
    for(int bin=0; bin<nbins; bin++){

      TH1F* histo = histo_ET_resolution_noPUS(filename[i],var[i], Form(cuts[i]+" && genjet_pt[VBF_parton_genjet]>%f && genjet_pt[VBF_parton_genjet]<%f",x[bin],x[bin+1]));   
      vector<float> eff_RMS=effectiveRMS(histo);
      gr->SetPoint(n,0.5*(x[bin]+x[bin+1]),eff_RMS[0]/(histo->GetMean()));
      gr->SetPointError(n,0.5*(-x[bin]+x[bin+1]),eff_RMS[1]/(histo->GetMean()));
      n++;

    }

    gr->SetLineWidth(2);
    gr->SetLineColor(i+1);
    if(i>0) gr->SetMarkerColor(i+1);
    if(i>3){
      gr->SetLineColor(i+2);
      if(i>0) gr->SetMarkerColor(i+2);
    }

    gr->SetMarkerStyle(kFullCircle);
    gr->SetFillColor(0);
    
    graph.push_back(gr);

  }


  graph[0]->GetXaxis()->SetRangeUser(10,310);
  graph[0]->GetYaxis()->SetRangeUser(0.,0.75);
  graph[0]->GetXaxis()->SetTitle("p_{T}(gen. jet) [GeV]");
  graph[0]->GetYaxis()->SetTitle("#sigma(p_{T}^{L1}/p_{T}^{gen})/<p_{T}^{L1}/p_{T}^{gen}>");
  //graph[0]->GetYaxis()->SetTitle("Resolution");
  graph[0]->GetYaxis()->SetTitleSize(0.04);
  graph[0]->GetYaxis()->SetTitleOffset(1.3);

  TLegend* leg=new TLegend(0.35,0.65,0.7,0.85);
  leg->SetHeader("1.6<|#eta(gen.jet)|<2.9");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  for(unsigned int i=0; i<graph.size();i++)
    leg->AddEntry(graph[i], leg_entry[i]);

  TCanvas *c = new TCanvas("c", "canvas", 850, 800);
  c->SetLeftMargin(0.15);
  gPad->SetTicks(1,1);

  graph[0]->Draw("AP");
  for(unsigned int i=1; i<graph.size(); i++)
    graph[i]->Draw("Psame");
  leg->Draw("same");

 TLatex *texl = new TLatex(21,0.76,"CMS Simulation VBF H#rightarrowinv. PU=0 #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");
  gPad->SetTicks();

  c->SaveAs("plots/L1Jet_resolution_pT_C3D_histo_PU0_TC_RefinedMax.pdf");

  return;


}


