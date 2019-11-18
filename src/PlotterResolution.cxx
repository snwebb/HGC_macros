#include "PlotterResolution.h"


void PlotterResolution::Draw(std::vector<HistObject>& hists, std::vector<double>& x, TString savename){

  std::system( ("mkdir -p plots/" + _outdir )   .c_str() );

  std::vector<TGraphErrors*> graph;

  int i = 0;  
  for (auto &hist: hists ){    

    TGraphErrors* gr=new TGraphErrors();
    
    int n=0;
    for(unsigned int bin=0; bin<x.size()-1; bin++){
      
      TH1F* histo = 0;
      //      histo = histo_ET_resolution(hist.filename(),hist.var(), Form(hist.cut()+" && genjet_pt>%f && genjet_pt<%f",x[bin],x[bin+1]), hist.process(), hist.PUS() );   

      histo = histo_ET_resolution(hist.filename(),hist.var(), hist.cut(), hist.process(), hist.PUS(), x[bin], x[bin+1]);   
      histo->SaveAs( (std::to_string(x[bin]) +".root").c_str() );
      if ( histo == 0 ) {
	return;
      }
	std::cout << "histin = " << histo->Integral() << std::endl;
      std::vector<float> eff_RMS=effectiveRMS(histo);

      std::cout << "n:" << n << eff_RMS[0] << " - " << (1-histo->GetMean()) <<  std::endl;
      gr->SetPoint(n,0.5*(x[bin]+x[bin+1]),eff_RMS[0]/(1-histo->GetMean()));
      //gr->SetPoint(n,0.5*(x[bin]+x[bin+1]),eff_RMS[0]/(histo->GetMean()));
      //std::cout << "n: "<< n << ", " << 0.5*(x[bin]+x[bin+1]) << std::endl;
           gr->SetPointError(n,0.5*(-x[bin]+x[bin+1]),eff_RMS[1]/(1-histo->GetMean()));
	   // gr->SetPointError(n,0.5*(-x[bin]+x[bin+1]),eff_RMS[1]/(histo->GetMean()));
      n++;
      histo->Delete();
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
    i++;
  }

  graph[0]->GetXaxis()->SetRangeUser(10,310);
  //  graph[0]->GetYaxis()->SetRangeUser(0.,0.55);
  //  graph[0]->GetXaxis()->SetRangeUser(24.99,25.01);
  //  graph[0]->GetYaxis()->SetRangeUser(0.035,0.055);
  graph[0]->GetXaxis()->SetTitle("p_{T}(gen. jet) [GeV]");
  graph[0]->GetYaxis()->SetTitle("#sigma(p_{T}^{L1}/p_{T}^{gen})/<p_{T}^{L1}/p_{T}^{gen}>");
  graph[0]->GetYaxis()->SetTitleSize(0.04);
  graph[0]->GetYaxis()->SetTitleOffset(1.3);

  _legend->SetHeader("1.6<|#eta(gen.jet)|<2.9");
  SetLegendXY( 0.55, 0.7, 0.82, 0.85  );

  for(unsigned int i=0; i<graph.size();i++)
    _legend->AddEntry(graph[i], hists.at(i).leg_entry() );

  TCanvas * c = _canvas;
  c->SetCanvasSize(850, 800);
  gPad->SetTicks(1,1);

  graph[0]->Draw("AP");
  graph[0]->SetMaximum(0.4);
  graph[0]->SetMinimum(0.01);
  for(unsigned int i=1; i<graph.size(); i++)
    graph[i]->Draw("Psame");
  _legend->Draw("same");


  _latex->Draw("same");
  gPad->SetTicks();



  c->SaveAs("plots/" + TString(_outdir) + "/" + savename + ".pdf");
  c->SaveAs("plots/" + TString(_outdir) + "/" + savename + ".png");
  c->SaveAs("plots/" + TString(_outdir) + "/" + savename + ".root");


}




std::vector<float> PlotterResolution::effectiveRMS(const TH1F* histo, double fraction, int fitrebin ){

  TString hname = histo->GetName();
  hname+="_copy";
  //  histo->SaveAs( hname+ ".root"  );
  TH1F* histoCopy = (TH1F*)histo->Clone(hname);
  histoCopy->SetDirectory(0);
  int nbins = histoCopy->GetNbinsX();

  TF1* fit = doubleCBFit(histoCopy,3.,fitrebin);
  double maxX = fit->GetParameter(1);
  fit->Delete();
  int maxBinX = histoCopy->GetXaxis()->FindBin(maxX);
  //  std::cout << "maxbinx = " << maxBinX << std::endl;
  double binWidth = histoCopy->GetXaxis()->GetBinWidth(maxBinX);
  histoCopy->Delete();

  std::vector<int> indexRMSLeftList;
  std::vector<int> indexRMSRightList;
  std::vector<double> rmsList;

  int nTries = 20;
  TRandom3* random = new TRandom3();
  bool goLeft = true;
  
  for(int n=0; n<nTries; n++){
    hname = histo->GetName();
    hname+="_copy";
    histoCopy = (TH1F*) histo->Clone(hname);
    //    histoCopy->SetDirectory(0);


    for(int b=1; b<nbins+1; b++){
      double newValue = random->Poisson(histoCopy->GetBinContent(b));
      histoCopy->SetBinContent(b, newValue);
    }


    double totalIntegral = histoCopy->Integral(0,nbins+1);
    
    std::cout << "TOTAL INTE =  "<< totalIntegral << std::endl;

    //double totalIntegral = histoCopy->Integral();
    double sumBins = 0.;
    //    double sumErrorBins = 0.;
    int indexRMSLeft = 0;
    int indexRMSRight = 0;
    int indexLeft = 0;
    int indexRight = 0;
    sumBins += histoCopy->GetBinContent(maxBinX)/totalIntegral;
    std::cout << "bin cont max bin = " << histoCopy->GetBinContent(maxBinX) << std::endl;
    for(int b=0; b<nbins+1; b++){
      int bRight = maxBinX + indexRight + 1;
      int bLeft = maxBinX - indexLeft - 1;

      if(bRight>nbins){
	std::cout<<"WARNING: effectiveRMS: bin reached histo boundary"<<std::endl;
        // int binRMSRight = bRight;
        // int binRMSLeft = bLeft;
        break;
      }
      if (bLeft<=0){
        std::cout<<"WARNING: effectiveRMS: bin reached histo boundary"<<std::endl;
        // int binRMSRight = bRight;
        // int binRMSLeft = bLeft;
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
    //cout<<xLeft<<","<<xRight<<std::endl;;
    double rms = (xRight - xLeft)/2.;
    rmsList.push_back(rms);

    histoCopy->Delete();    
  }
    
  double rms=0;
  double rmsError = 0;
  TH1F* rms_histo=new TH1F("rms_histo","rms_histo",2000,0,1);
    
  for(unsigned int i=0; i<rmsList.size(); i++){
    rms_histo->Fill(rmsList[i]);
    std::cout << "filling: " << rmsList[i] << std::endl;
  }

  //  rms_histo->SaveAs( "rms_histo.root" );

  //rms/=rmsList.size();
  //rmsError=sqrt(rmsError/rmsList.size()-pow(rms,2));
  rms=rms_histo->GetMean();
  rmsError=rms_histo->GetStdDev();
  
  rms_histo->Delete();

  rmsError = std::max(rmsError, 1./sqrt(12.)*binWidth);
  std::cout<<"rms,rmserr: " << rms<<","<<rmsError<<std::endl;
  
  std::vector<float> result;
  result.push_back(rms);
  result.push_back(rmsError);
  return result;
  
}



TH1F* PlotterResolution::histo_ET_resolution(TString filename, TString var, TString cut, std::string process, bool PUS, double binlow, double binhigh){


  TChain * tree = new TChain("HGCalTriggerNtupleJet");

  tree->Add(filename);

  if (tree->GetEntries() == 0 ) {
    std::cout << "Tree has zero entries, no output produced" << std::endl;
    return 0;
  }
    
  TString all_cuts="";
  if ( process == "Gamma" ) {

    all_cuts = Form(cut+" && genjet_pt>%f && genjet_pt<%f",binlow,binhigh);

    if ( !PUS )
      tree->Draw(var + ">>g(500,-2,2)",all_cuts+ " && jets_pt>0","goff");  
    if ( PUS )
      tree->Draw(var + ">>g(500,-2,2)",all_cuts+ " && jets_pt>0","goff");  

  }

  if ( process == "Jets" ) {

    all_cuts = Form(cut+" && genjet_pt[VBF_parton_genjet]>%f && genjet_pt[VBF_parton_genjet]<%f",binlow,binhigh);

    if ( !PUS ){
      std::cout << "\"" << var + ">>g(500,-2,2)\",\"" << all_cuts << "&& jets_pt[VBF_parton_jets]>0\"" << std::endl;
      tree->Draw(var + ">>g(500,-2,2)",all_cuts+ " && jets_pt[VBF_parton_jets]>0","goff");  
    }
    if ( PUS ){
      std::cout << var + ">>g(500,-5,5), " << all_cuts << "&& jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets]>0" << std::endl;
      //            tree->Draw(var + ">>g(500,-5,5)",all_cuts+ " && jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets]>0","goff");  
//      tree->Draw(var + ">>g(500,-5,5)",all_cuts+ " && (jets_pt[VBF_parton_jets]-jets_PU_subtr_cone_tc[VBF_parton_jets])>0","goff");  
      tree->Draw(var + ">>g(500,-3,3)",all_cuts+ " && (jets_pt[VBF_parton_jets]-jets_PU_subtr_cone_tc[VBF_parton_jets])>0","goff");  
    }

  }
    
  //    std::cout << var + ">>g(500,-2,2)," + all_cuts+ " && jets_pt[VBF_parton_jets]>0" << std::endl;

  TH1F* g=(TH1F*) ((TH1F*)gDirectory->Get("g"))->Clone();
  
  return g;
  
}

TF1* PlotterResolution::doubleCBFit(TH1F* histo, double rangeInSigma, int fitrebin){

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
  fit = new TF1("doubleCBFit", PlotterResolution::DoubleCB, mean-rangeInSigma*rms, mean+rangeInSigma*rms, 7);
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

double PlotterResolution::DoubleCB(double* x, double* par){
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

