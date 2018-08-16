#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <iostream>
#include <TLegend.h>
#include <TGraphErrors.h>
#include <TFile.h>
#include <TTree.h>
#include <TLatex.h>
#include "Helpers.C"





float AUC(TGraphErrors* ROC){

  float auc = 0;
  double x1,y1,x2,y2;

  for(int i=0; i<ROC->GetN(); i++){

    ROC->GetPoint(i,x1,y1);
    ROC->GetPoint(i+1,x2,y2);
    auc += 0.5*fabs(x1-x2)*(y1+y2);

  }

  return auc;

}


TGraphErrors* get_ROC_VBF(TString file_sig, TString file_bkg, TString cut_sig, TString cut_bkg, TString var, int nbin, float min, float max, bool sig_up){


  TH1F* h_sig = single_plot(file_sig,"HGCalTriggerNtupleJet",var+"[VBF_parton_jets]",cut_sig,nbin,min,max);
  TH1F* h_bkg = single_plot(file_bkg,"HGCalTriggerNtupleJet",var,cut_bkg,nbin,min,max);
  
  double N_sig=h_sig->Integral();
  cout<<"N_sig="<<N_sig<<endl;
  double N_bkg=h_bkg->Integral();
  cout<<"N_bkg="<<N_bkg<<endl;

  int bindown=0;
  int binup=h_sig->GetNbinsX();

  TGraphErrors* ROC=new TGraphErrors();
  int n=0;

  for(int i=0;i<=nbin;i++){

    double n_sig_acc=h_sig->Integral(bindown,i);
    double n_bkg_acc=h_bkg->Integral(bindown,i);

    if(sig_up){
      n_sig_acc=h_sig->Integral(i,binup);
      n_bkg_acc=h_bkg->Integral(i,binup);
    }

    double sigeff=n_sig_acc/N_sig;
    double bkgfake=n_bkg_acc/N_bkg;

    ROC->SetPoint(n,sigeff,bkgfake);

    n++;

  }

  return ROC;


}






TGraphErrors* get_ROC_VBF_2D(TString file_sig, TString file_bkg, TString cut_sig, TString cut_bkg, TString var, int nbin, float min, float max, bool sig_up){

  int nbin_eff=100;

  TH2F* h_sig = single_plot2D(file_sig,"HGCalTriggerNtupleJet",var+"[VBF_parton_jets]","jets_pt[VBF_parton_jets]",cut_sig,nbin,min,max,480,20,500);
  TH2F* h_bkg = single_plot2D(file_bkg,"HGCalTriggerNtupleJet",var,"jets_pt",cut_bkg,nbin,min,max,480,20,500);
  
  double N_sig=h_sig->Integral();
  cout<<"N_sig="<<N_sig<<endl;
  double N_bkg=h_bkg->Integral();
  cout<<"N_bkg="<<N_bkg<<endl;

  int bindown=0;
  int binup=h_sig->GetNbinsX();

  TGraphErrors* ROC=new TGraphErrors();

  pair<double,double> dummy=make_pair(0.,1.);
  vector<pair<double,double> > efficiencies(nbin_eff,dummy);

  int n=0;

  for(int i=1;i<=nbin;i++){

    cout<<"i="<<i<<endl;
    
    for(int j=1;j<=479;j++){

      double n_sig_acc=0.;
      double n_bkg_acc=0.;

      if(sig_up){
	n_sig_acc=h_sig->Integral(i,binup,j,479);
	n_bkg_acc=h_bkg->Integral(i,binup,j,479);
      }

      else{
	n_sig_acc=h_sig->Integral(bindown,i,j,479);
	n_bkg_acc=h_bkg->Integral(bindown,i,j,479);
      }

      double sigeff=n_sig_acc/N_sig;
      double bkgfake=n_bkg_acc/N_bkg;
      
      int bin_eff = abs(sigeff*nbin_eff);
      if(bkgfake < efficiencies[bin_eff].second){	
	efficiencies[bin_eff].first=sigeff;
	efficiencies[bin_eff].second=bkgfake;
      }      
            
    }

  }


  int npoints=0;

  for(int n=0;n<nbin_eff;n++){
    	
    double sigeff = efficiencies[n].first;
    double bkgfake = efficiencies[n].second;

    if(sigeff>0){

      cout<<"(x,y)=("<<sigeff<<","<<bkgfake<<")"<<endl;
      ROC->SetPoint(npoints,sigeff,bkgfake);         
      npoints++;

    }
  }


  return ROC;


}







TGraphErrors* get_ROC_tau(TString file_sig, TString file_bkg, TString cut_sig, TString cut_bkg, TString var, int nbin, float min, float max, bool sig_up){


  TH1F* h_sig = single_plot(file_sig,"HGCalTriggerNtupleJet",var+"[gentau_jets]",cut_sig,nbin,min,max);
  TH1F* h_bkg = single_plot(file_bkg,"HGCalTriggerNtupleJet",var,cut_bkg,nbin,min,max);
  
  double N_sig=h_sig->Integral();
  cout<<"N_sig="<<N_sig<<endl;
  double N_bkg=h_bkg->Integral();
  cout<<"N_bkg="<<N_bkg<<endl;

  int bindown=0;
  int binup=h_sig->GetNbinsX();

  TGraphErrors* ROC=new TGraphErrors();
  int n=0;

  for(int i=0;i<=nbin;i++){

    double n_sig_acc=h_sig->Integral(bindown,i);
    double n_bkg_acc=h_bkg->Integral(bindown,i);

    if(sig_up){
      n_sig_acc=h_sig->Integral(i,binup);
      n_bkg_acc=h_bkg->Integral(i,binup);
    }

    double sigeff=n_sig_acc/N_sig;
    double bkgfake=n_bkg_acc/N_bkg;

    ROC->SetPoint(n,sigeff,bkgfake);

    n++;

  }

  return ROC;


}






TGraphErrors* get_ROC_tau_2D(TString file_sig, TString file_bkg, TString cut_sig, TString cut_bkg, TString var, int nbin, float min, float max, bool sig_up){

  int nbin_eff=100;

  TH2F* h_sig = single_plot2D(file_sig,"HGCalTriggerNtupleJet",var+"[gentau_jets]","jets_pt[gentau_jets]",cut_sig,nbin,min,max,480,20,500);
  TH2F* h_bkg = single_plot2D(file_bkg,"HGCalTriggerNtupleJet",var,"jets_pt",cut_bkg,nbin,min,max,480,20,500);
  
  double N_sig=h_sig->Integral();
  cout<<"N_sig="<<N_sig<<endl;
  double N_bkg=h_bkg->Integral();
  cout<<"N_bkg="<<N_bkg<<endl;

  int bindown=0;
  int binup=h_sig->GetNbinsX();

  TGraphErrors* ROC=new TGraphErrors();

  pair<double,double> dummy=make_pair(0.,1.);
  vector<pair<double,double> > efficiencies(nbin_eff,dummy);
  vector<pair<double,double> > cuts(nbin_eff,dummy);

  int n=0;

  for(int i=0;i<=nbin;i++){

    cout<<"i="<<i<<endl;
    
    for(int j=0;j<=479;j++){

      double n_sig_acc=0.;
      double n_bkg_acc=0.;

      if(sig_up){
	n_sig_acc=h_sig->Integral(i,binup,j,479);
	n_bkg_acc=h_bkg->Integral(i,binup,j,479);
      }

      else{
	n_sig_acc=h_sig->Integral(bindown,i,j,479);
	n_bkg_acc=h_bkg->Integral(bindown,i,j,479);
      }

      double sigeff=n_sig_acc/N_sig;
      double bkgfake=n_bkg_acc/N_bkg;
      
      int bin_eff = abs(sigeff*nbin_eff);
      if(bkgfake < efficiencies[bin_eff].second){
	efficiencies[bin_eff].first=sigeff;
	efficiencies[bin_eff].second=bkgfake;
	cuts[bin_eff].first = h_sig->GetXaxis()->GetBinLowEdge(i);
	cuts[bin_eff].second = h_sig->GetYaxis()->GetBinLowEdge(j);       
      }      
            
    }

  }


  int npoints=0;

  for(int n=0;n<nbin_eff;n++){
    	
    double sigeff = efficiencies[n].first;
    double bkgfake = efficiencies[n].second;

    if(sigeff>0){

      cout<<"(x,y)=("<<sigeff<<","<<bkgfake<<") pT>"<<cuts[n].second<<" fraction<"<<cuts[n].first<<endl;
      ROC->SetPoint(npoints,sigeff,bkgfake);         
      npoints++;

    }
  }


  return ROC;


}









TGraphErrors* get_ROC_VBF_C3D(TString file_sig, TString file_bkg, TString cut_sig, TString cut_bkg, TString var, int nbin, float min, float max, bool sig_up){


  TH1F* h_sig = single_plot(file_sig,"HGCalTriggerNtupleJet",var,cut_sig,nbin,min,max);
  TH1F* h_bkg = single_plot(file_bkg,"HGCalTriggerNtupleJet",var,cut_bkg,nbin,min,max);
  
  double N_sig=h_sig->Integral();
  cout<<"N_sig="<<N_sig<<endl;
  double N_bkg=h_bkg->Integral();
  cout<<"N_bkg="<<N_bkg<<endl;

  int bindown=0;
  int binup=h_sig->GetNbinsX();

  TGraphErrors* ROC=new TGraphErrors();
  int n=0;

  for(int i=0;i<=nbin;i++){

    double n_sig_acc=h_sig->Integral(bindown,i);
    double n_bkg_acc=h_bkg->Integral(bindown,i);

    if(sig_up){
      n_sig_acc=h_sig->Integral(i,binup);
      n_bkg_acc=h_bkg->Integral(i,binup);
    }
    

    double sigeff=n_sig_acc/N_sig;
    double bkgfake=n_bkg_acc/N_bkg;

    if(sig_up){
      double x=h_sig->GetBinLowEdge(i);
      cout<<"x>"<<x<<" sigeff="<<sigeff<<" bkgfake="<<bkgfake<<endl;
    }
    else{
      double x=h_sig->GetBinLowEdge(i+1);
      cout<<"x<"<<x<<" sigeff="<<sigeff<<" bkgfake="<<bkgfake<<endl;
    }

    ROC->SetPoint(n,sigeff,bkgfake);

    n++;

  }

  return ROC;


}


