#include "Plotter.h"
#include <TVirtualFitter.h>

Plotter::Plotter( CmdLine * cmd ){

  _outdir = cmd->string_val( "--outdir" );
  std::system( ("mkdir -p plots/" + _outdir )   .c_str() );

  InitialiseLegend();
  InitialiseCanvas();
  InitialiseLatex();

}

Plotter::~Plotter(){
  if ( _canvas )
    delete _canvas;
  if ( _legend )
    delete _legend;
  if ( _latex )
    delete _latex;

}


void Plotter::InitialiseCanvas(){

  _canvas = new TCanvas("c"+_helper.counter(),"c",650,600);
  _canvas->SetLeftMargin(0.15);
  _canvas->SetRightMargin(0.15);

}

void Plotter::InitialiseLatex(){

  _latex = new TLatex();
  _latex->SetNDC();
  _latex->SetTextSize(0.03);
  _latex->SetText(0.2,0.9,"CMS Simulation Preliminary, VBF H#rightarrowinv. #sqrt{s}=14 TeV");
}

void Plotter::InitialiseLegend(){

  _legend = new TLegend(0.4,0.15,0.7,0.5);
  //  _legend->SetHeader("#splitline{p_T(gen. jet)>20 GeV}{1.6<|#eta(gen.jet)|<2.9}");
  //  _legend->SetHeader("#splitline{p_T(gen. jet)>20 GeV}{1.6<|#eta(gen.jet)|<2.9}");
  _legend->SetFillColor(0);
  _legend->SetBorderSize(0);
  _legend->SetTextSize(0.03);

}

void Plotter::SetLegendXY(Double_t x1, Double_t y1, Double_t x2, Double_t y2){

    _legend->SetX1(x1);
    _legend->SetY1(y1);
    _legend->SetX2(x2);
    _legend->SetY2(y2);

}

void Plotter::DrawGraphs(std::vector<TGraphErrors*>& graphs, std::vector<TString>& legend){

  TCanvas * c = _canvas;
  c->SetCanvasSize(800, 600);
  gPad->SetTicks(1,1);
  SetLegendXY( 0.6, 0.63, 0.82, 0.85  );
  _legend->Clear();
  int i = 0;
    for (auto &graph: graphs ){    
      
      graph->SetLineColor(i+1);      
      if(i>3){
	graph->SetLineColor(i+2);
      }

      if ( i==0 ){
	graph->Draw("ap");
	gStyle->SetOptStat(0);
	graph->SetTitle(";gen p_{T};Resolution");
	graph->GetXaxis()->SetRangeUser(20,300);
	graph->GetYaxis()->SetRangeUser(0,0.6);
	graph->Draw("apsame");
      }
      else {
	graph->Draw("psame");
      }
      _legend->AddEntry(graph, legend.at(i), "L" );
      i++;
    }


    _legend->Draw("same");
    c->SaveAs("plots/" + TString(_outdir) + "/res2.png");
    c->SaveAs("plots/" + TString(_outdir) + "/res2.root");
  //  c->SaveAs("plots/" + TString(_outdir) + "/"+sa.root");
  


}



void Plotter::DrawGraph(TGraph* graph, TString filename){

  TCanvas * c = _canvas;
  c->SetCanvasSize(800, 600);
  gPad->SetTicks(1,1);
  SetLegendXY( 0.6, 0.63, 0.82, 0.85  );
  _legend->Clear();

  graph->SetMarkerSize(1);
  graph->SetMarkerStyle(20);
  graph->Draw("ap");


  graph->SetTitle(";reco p_{T} Threshold;reco p_{T} at 95% efficiency");
  graph->GetXaxis()->SetRangeUser(0,250);
  graph->GetYaxis()->SetRangeUser(0,300);
  graph->Draw("apsame");
  graph->SaveAs("plots/" + TString(_outdir) + "/graph_"+filename+".root");
  
  c->SaveAs("plots/" + TString(_outdir) + "/"+filename+".png");
  c->SaveAs("plots/" + TString(_outdir) + "/"+filename+".root");

}



void Plotter::DrawEtaGraphs(std::vector<TGraphErrors*>& graphs){

  TCanvas * c = _canvas;
  c->SetCanvasSize(800, 600);
  gPad->SetTicks(1,1);
  std::vector<TString> legend;

  std::vector<TGraphErrors*> eta_graphs;
  std::vector<TGraphErrors*> eta_graphs2;
  TMultiGraph *mg = new TMultiGraph();
  mg->SetTitle("; #eta; Resolution");
  //2 eta bins
  // std::vector<float> eta_centres = {1.875,2.625};
  // float eta_width = 0.375;  

  //5 eta bins
  std::vector<float> eta_centres = {1.65, 1.95, 2.25, 2.55, 2.85};
  float eta_width = 0.15;  

  // int begin_bin = 2;
  // int end_bin = 5;
  int begin_bin = 5;
  int end_bin = 8;
  // int begin_bin = 8;
  // int end_bin = 13;



  // int begin_bin = 11;
  // int end_bin = 14;

  int count = 0;
  //  int count_type = 0;

  for (auto &graph: graphs ){    

    //    for ( int i = 0; i < graph->GetN(); i++ ){
    for ( int i = 0; i < end_bin-begin_bin; i++ ){

      TGraphErrors * g = 0;
      if ( count == 0 )	g = new TGraphErrors( graphs.size() );
      else g = eta_graphs.at(i);
      double tempx, tempy;
	graph->GetPoint(i+begin_bin, tempx, tempy);
	//	std::cout << count << " - " << eta_centres.at(count) << " - " << tempy << std::endl;
	g->SetPoint( count , eta_centres.at(count) , tempy ) ;
	g->SetPointError( count , eta_width , graph->GetErrorY(i+begin_bin) ) ;
	if ( count == 0 ) {
	  eta_graphs.push_back( g );
	  legend.push_back( TString( std::to_string(int(tempx))  + " pT STC4" ) );
	  //	  std::cout << legend.size() << std::endl;
	}
    }
    count++;
    if (count == 5) break;
  }


  int count2 = 0;
  count = 0;
  for (auto &graph: graphs ){    
    
    if ( count2 < 5 ){
      count2 ++;
      continue;
    }
    //    for ( int i = 0; i < graph->GetN(); i++ ){
    for ( int i = 0; i < end_bin-begin_bin; i++ ){
      TGraphErrors * g = 0;
      if ( count == 0 )	g = new TGraphErrors( graphs.size() );
      else g = eta_graphs2.at(i);
	double tempx, tempy;
	graph->GetPoint(i+begin_bin, tempx, tempy);
	//	std::cout << count << " - " << eta_centres.at(count) << " - " << tempy << std::endl;
	g->SetPoint( count , eta_centres.at(count) , tempy ) ;
	g->SetPointError( count , eta_width , graph->GetErrorY(i+begin_bin) ) ;

	if ( count == 0 ) {
	  eta_graphs2.push_back( g );
	  legend.push_back( TString( std::to_string(int(tempx))  + " pT 1bit" ) );
	  //	  std::cout << legend.size() << std::endl;
	}
    }
    count++;
  }


  SetLegendXY( 0.2, 0.3, 0.35, 0.75  );
  _legend->Clear();

  int i = 0;
  //Each graph is an eta point, 
  for (auto &graph: eta_graphs ){    
    graph->SetMarkerStyle(22);
    graph->SetLineColor(i+1);      
    graph->SetMarkerColor(i+1);      
    if(i>3){
      graph->SetLineColor(i+2);
      graph->SetMarkerColor(i+2);
    }
    //    if ( i > 2 ){
      mg->Add(graph, "p" );
      _legend->AddEntry(graph, legend.at(i), "LP" );
      //    }
    i++;
  }
  i = 0;
  for (auto &graph: eta_graphs2 ){    

    graph->SetMarkerStyle(20);

    if(i>3){
      graph->SetLineColor(i+2);
      graph->SetMarkerColor(i+2);
    }
    else{
      graph->SetLineColor(i+1);  
      graph->SetMarkerColor(i+1);    
    }
    //    if ( i > 2+5 ){
      mg->Add(graph, "p" );

  _legend->AddEntry(graph, legend.at(i+(end_bin-begin_bin)), "LP" );
      //    }
    i++;
  }


  mg->Draw("ap");
  mg->GetXaxis()->SetLimits(0.75,3);
  mg->GetYaxis()->SetRangeUser(0,0.6);


      _legend->Draw("same");

    c->SaveAs("plots/" + TString(_outdir) + "/eta_res.png");
    c->SaveAs("plots/" + TString(_outdir) + "/eta_res.root");
  //  c->SaveAs("plots/" + TString(_outdir) + "/"+sa.root");
  


}






TGraphErrors * Plotter::DrawProfile(TH2F * hist, TString savename, Option_t * option = ""){

  TCanvas * c = _canvas;
  c->SetCanvasSize(800, 600);
  gPad->SetTicks(1,1);
  SetLegendXY( 0.6, 0.45, 0.82, 0.75  );

  TProfile* pmean = hist->ProfileX( "profile_mean");
  TProfile* p_rms = hist->ProfileX( "profile", 1, -1, option );

  double start = 20;
  double end = 300;

  int order = 2;

  TF1 * pol_choice;
  if ( order == 1){
    pol_choice  = new TF1 ( "pol", "[0] + [1]*x" , 20 , 350);
  }
  else if (  order ==2){
    pol_choice  = new TF1 ( "pol", "[0] + [1]*x + [2]*x*x" , 20 , 350);
  }


  TF1 * f_mean = (TF1*)pol_choice->Clone("f_mean" );
  TF1 * f_rmsup = (TF1*)pol_choice->Clone("f_rmsup" );
  TF1 * f_rmsdown = (TF1*)pol_choice->Clone("f_rmsdown" );

  TFitResultPtr r;
  TFitResultPtr r_rmsup;
  TFitResultPtr r_rmsdown;

  r =  pmean->Fit( pol_choice, "R","",start,end);
  
  pmean->Draw();
  pmean->GetYaxis()->SetRangeUser(0,400);
  pmean->Draw("same");
  
  p_rms->Draw("same");
  
  TGraphErrors * rms_up = new TGraphErrors( p_rms->GetNbinsX() );
  TGraphErrors * rms_down = new TGraphErrors( p_rms->GetNbinsX() );
  TGraphErrors * resolution = new TGraphErrors( p_rms->GetNbinsX() );
  resolution->SetTitle( "" );

  std::vector<double> rms;  
  std::vector<double> rms_err;  
  double bins_per_unit = hist->GetNbinsY()/hist->GetYaxis()->GetBinLowEdge(hist->GetNbinsY()+1);
  TRandom3* random = new TRandom3();

  bool bootstrap = false;
 
  for (int i = 1; i < p_rms->GetNbinsX()+1; i++){
    std::vector<double> rms_list;  
    int centralbin_nominal = 0;
    double xval_nom = p_rms->GetBinContent(i);
    for (int y = 1; y < hist->GetNbinsY()+1; y++){
      if ( xval_nom > hist->GetYaxis()->GetBinLowEdge(y) && xval_nom < hist->GetYaxis()->GetBinLowEdge(y+1) ){
	centralbin_nominal=y;
	break;
      }
    }

    int nTries = 100;
    if ( bootstrap ){

      for(int n=0; n<nTries; n++){
	
	TH1D * histCopy = new TH1D( "histcopy", "", hist->GetNbinsY(), hist->GetYaxis()->GetBinLowEdge(1), hist->GetYaxis()->GetBinLowEdge(hist->GetNbinsY() + 1 ) ) ;
	for (int y = 1; y < hist->GetNbinsY()+1; y++){
	  histCopy->SetBinContent(y, random->Poisson( hist->GetBinContent(i,y) ) );
	}
	double total = histCopy->Integral();
	double xval = p_rms->GetBinContent(i);
	int centralbin = 0;

	for (int y = 1; y < hist->GetNbinsY()+1; y++){
	  if ( xval > histCopy->GetXaxis()->GetBinLowEdge(y) && xval < histCopy->GetXaxis()->GetBinLowEdge(y+1) ){
	    centralbin=y;
	    break;
	  }
	}
	if (total>0.00001){ 
	  for (int y = 1; y < histCopy->GetNbinsX()+1; y++){
	    double frac = histCopy->Integral(centralbin-y,centralbin+y);    
	    if ( frac/total  > 0.683 ){
	    //	    ybin = y;	  
	      rms_list.push_back( double(y) );
	      break;
	    }
	  }
	}
	else{
	  rms_list.push_back(100);      
	}
	
	histCopy->Delete();

      }//ntries
    
    
      auto min_value = *std::min_element(rms_list.begin(),rms_list.end());
      auto max_value = *std::max_element(rms_list.begin(),rms_list.end());

      TH1F* rms_histo=new TH1F("rms_histo","rms_histo",2000,min_value-1,max_value+1);
      for(unsigned int a=0; a<rms_list.size(); a++){
	rms_histo->Fill(rms_list.at(a));
      }
      
      rms.push_back( rms_histo->GetMean() );
      rms_err.push_back( rms_histo->GetStdDev() );
      rms_histo->Delete();

    }
    else{
      
      double err = 0;
      double total = hist->IntegralAndError(i,i,1,hist->GetNbinsY() , err);

      if (total>0.00001){ 
	
	for (int y = 1; y < hist->GetNbinsY()+1; y++){
	  
	  double frac = hist->Integral(i,i,centralbin_nominal-y,centralbin_nominal+y);    
	  if ( frac/total  > 0.683 ){
	     
	    rms.push_back( double(y) );
	    rms_err.push_back(   double(y)/( std::sqrt(2) * err ) );
	    break;
	  }
	}
      }
      else{
	std::cout << i << " - " << total << std::endl;
	std::cout << "errsize = " << rms_err.size() << std::endl;
	// rms.push_back(rms.at(i-1) );      
	// rms_err.push_back( rms_err.at(i-1) );      
	rms.push_back(1 );      
	rms_err.push_back( 1 );      

	std::cout << "errsize = " << rms_err.size() << std::endl;
      }
    
    }



    //normal way    
    rms_up  ->SetPoint(i-1, p_rms->GetBinCenter(i), double(centralbin_nominal+rms.at(i-1))/double(bins_per_unit) );
    rms_down->SetPoint(i-1, p_rms->GetBinCenter(i), double(centralbin_nominal-rms.at(i-1))/double(bins_per_unit) );
    
    rms_up  ->SetPointError(i-1, 0, double (rms_err.at(i-1))/double (bins_per_unit) );
    rms_down->SetPointError(i-1, 0, double (rms_err.at(i-1))/double (bins_per_unit) );
     
  }


  r_rmsup = rms_up->Fit(pol_choice, "RS", "", start, end);
  r = rms_down->Fit(pol_choice, "R", "", start, end);  

  f_mean->SetParameter( 0, pmean->GetFunction("pol")->GetParameter( 0 ) ); 
  f_mean->SetParameter( 1, pmean->GetFunction("pol")->GetParameter( 1 ) );
  f_mean->SetParameter( 2, pmean->GetFunction("pol")->GetParameter( 2 ) );
  f_mean->SetParErrors ( pmean->GetFunction("pol")->GetParErrors() );
  
  f_rmsup->SetParameter( 0, rms_up->GetFunction("pol")->GetParameter( 0 ) );
  f_rmsup->SetParameter( 1, rms_up->GetFunction("pol")->GetParameter( 1 ) );
  f_rmsup->SetParameter( 2, rms_up->GetFunction("pol")->GetParameter( 2 ) );
  f_rmsup->SetParErrors ( rms_up->GetFunction("pol")->GetParErrors() );
  
  f_rmsdown->SetParameter( 0, rms_down->GetFunction("pol")->GetParameter( 0 ) );
  f_rmsdown->SetParameter( 1, rms_down->GetFunction("pol")->GetParameter( 1 ) );
  f_rmsdown->SetParameter( 2, rms_down->GetFunction("pol")->GetParameter( 2 ) );
  f_rmsdown->SetParErrors ( rms_down->GetFunction("pol")->GetParErrors() );
 
  f_rmsup->SetRange(start,end);
  f_rmsdown->SetRange(start,end);

  f_rmsup->Draw("same");
  f_rmsdown->Draw("same");
  f_mean->SetLineColor(kGreen);
  f_mean->Draw("same");

  pmean->Draw("same");		
  gPad->SetTicks();

  c->SaveAs("plots/" + TString(_outdir) + "/" + savename + ".png");
  c->SaveAs("plots/" + TString(_outdir) + "/" + savename + ".root");

  c->Clear();

  std::cout << "--------------" << std::endl;
  for (int i = 1; i < p_rms->GetNbinsX()+1; i++){

    //Using the fits
    double x[1] = { p_rms->GetBinCenter(i) };
    double err[1];  // error on the function at point x0
    r_rmsup->GetConfidenceIntervals(1, 1, 1, x, err, 0.683, false);

    double sigma = 0;
    double sigma_err = 0;

    if ( order == 1){
    //1st order pol1
      sigma = 0.5 * std::abs( f_mean->GetX(f_rmsup->Eval(p_rms->GetBinCenter(i)) ) - f_mean->GetX(f_rmsdown->Eval(p_rms->GetBinCenter(i)) ) ); 
      sigma_err = 0.5 * std::abs( f_mean->GetX(f_rmsup->Eval(p_rms->GetBinCenter(i)) + err[0]    ) - f_mean->GetX(f_rmsdown->Eval(p_rms->GetBinCenter(i)) - err[0] ) ); 
    }
    else if (order == 2){
      //2nd order pol2
      sigma = 0.5 * std::abs( _helper.Get2dX(f_mean,f_rmsup->Eval(p_rms->GetBinCenter(i)) ) - _helper.Get2dX(f_mean,f_rmsdown->Eval(p_rms->GetBinCenter(i)) ) ); 
      sigma_err = 0.5 * std::abs( _helper.Get2dX(f_mean,f_rmsup->Eval(p_rms->GetBinCenter(i)) + err[0]  ) - _helper.Get2dX(f_mean,f_rmsdown->Eval(p_rms->GetBinCenter(i)) - err[0] ) ); 
    }


    std::cout << p_rms->GetBinCenter(i) << " -  "<< f_rmsup->Eval(p_rms->GetBinCenter(i)) << " - " << f_mean->GetX(f_rmsup->Eval(p_rms->GetBinCenter(i)) ) << std::endl;
    std::cout << sigma << std::endl;


    //    Using the 68% counting method
    //    double sigma_68 = rms.at(i-1)/double(bins_per_unit);
    // double sigma_err = rms_err.at(i-1)/double(bins_per_unit);
    // //  std::cout << "err from fit = " << err[0]  <<  " - " << sigma_err << std::endl;
    // sigma = std::abs( f_mean->GetX( sigma + f_mean->Eval(p_rms->GetBinCenter(i) ) ) - p_rms->GetBinCenter(i) );
    // sigma_err = std::abs( f_mean->GetX( sigma_err + f_rmsup->Eval(p_rms->GetBinCenter(i) ) ) - p_rms->GetBinCenter(i) );
    //    sigma_err = std::abs( f_mean->GetX( err[0] + f_mean->Eval(p_rms->GetBinCenter(i) ) ) - p_rms->GetBinCenter(i) );


    resolution->SetPoint(i-1, p_rms->GetBinCenter(i), sigma/p_rms->GetBinCenter(i));
    resolution->SetPointError(i-1, 0.5*p_rms->GetBinWidth(i), std::abs(sigma-sigma_err)/p_rms->GetBinCenter(i));

  }

  resolution->Draw();
  resolution->GetXaxis()->SetRangeUser(start,end);
  resolution->GetYaxis()->SetRangeUser(0,0.6);
  resolution->Draw("same");
  c->SaveAs("plots/" + TString(_outdir) + "/"+savename+"resolution.png");
  c->SaveAs("plots/" + TString(_outdir) + "/"+savename+"resolution.root");


  //Special Code for producing example plot
  /*
  //  std::cout << _helper.Get2dX(f_mean, 72.98 ) << std::endl;

  for ( int z = 1; z < hist->GetNbinsX(); z++){  
    TH1D * hist_projection = hist->ProjectionY("hist_proj",z,z);
    TH1D * hist_gen = (TH1D*)hist_projection->Clone("hist_gen");
    hist_gen->Reset();
    for ( int i = 1; i < hist_projection->GetNbinsX()+1; i++){
      
      double event =  _helper.Get2dX(f_mean, hist_projection->GetBinCenter(i) );

      //      std::cout << "1: " << hist_projection->GetBinCenter(i) << " - " << f_mean->Eval( event )  << std::endl;
      //      std::cout  << hist_projection->GetBinCenter(i)/f_mean->Eval( event ) << std::endl;
      for ( int j = 0; j < hist_projection->GetBinContent(i); j++ ){
	hist_gen->Fill(event);
      }
      
    }
    
    hist_gen->Rebin( 16 );
    hist_projection->Rebin( 16 );

    c->Clear();
    hist_gen->Draw();
    c->SaveAs("plots/" + TString(_outdir) + "/"+savename+"projected_gen_"+std::to_string(z)+".png");
    c->SaveAs("plots/" + TString(_outdir) + "/"+savename+"projected_gen_"+std::to_string(z)+".root");


    c->Clear();
    hist_projection->Draw();
    c->SaveAs("plots/" + TString(_outdir) + "/"+savename+"projected_reco_"+std::to_string(z)+".png");
    c->SaveAs("plots/" + TString(_outdir) + "/"+savename+"projected_reco_"+std::to_string(z)+".root");

      }
  */

  return resolution;
}


void Plotter::Draw(std::vector<TH1F*>& hists, std::vector<TString>& legend, TString savename, bool logy){

  _legend->Clear();
  TCanvas * c = _canvas;
  c->SetCanvasSize(800, 600);
  gPad->SetTicks(1,1);
  SetLegendXY( 0.7, 0.5, 0.82, 0.75  );

  int i = 0;
  for (auto &hist: hists ){    

    TH1F* histo = hist;
  
    _legend->AddEntry( histo, legend.at(i) , "L");    

    histo->SetLineColor(i+1);
    if(i>3){
      histo->SetLineColor(i+2);
    }
    histo->SetTitle(";offline p_{T} [GeV];Rate [kHz]");

    if ( i == 0 ){
	histo->Draw();
	gPad->SetLogy(logy);
	if ( !gPad->GetLogy() ) histo->SetMinimum(0);
	else histo->SetMinimum(0.1);
	histo->Draw("same");
	// histo->SetMaximum(70000);
	// histo->SetMinimum(1);
    }
    else{
      histo->Draw("same");
    }
    histo->SaveAs("plots/" + TString(_outdir) + "/" + savename + "_" + legend.at(i) + ".root");
    i++;
    histo->SetName("cl3dpt");


  }

  //_latex->Draw("same");
  _legend->Draw("same");

  gPad->SetTicks();
  c->SaveAs("plots/" + TString(_outdir) + "/" + savename + ".root");
  c->SaveAs("plots/" + TString(_outdir) + "/" + savename + ".png");

}

void Plotter::Draw( TH1F * hist, TString legend = "", TString savename = "temp", bool logy){
    
    std::vector<TH1F*> vechist = {hist};
    std::vector<TString> leghist = {legend};
    Draw( vechist, leghist, savename, logy );

}


void Plotter::Draw(std::vector<HistObject>& hists, int nbins, double xlow, double xhigh, TString savename){

  TCanvas * c = _canvas;
  TLegend * legend = _legend;
  SetLegendXY( 0.6, 0.5, 0.82, 0.75  ); 
  legend->Clear();
  c->Clear();
  c->SetCanvasSize(800, 600);
  gPad->SetTicks(1,1);


  int i = 0;
  double max = 0;
  TH1F* first = 0;
  for (auto &hist: hists ){    

    TH1F* histo = 0;
    histo = _helper.single_plot( hist.filename(), hist.treename(), hist.var(), hist.cut(), nbins, xlow, xhigh );

    histo->Scale(1/histo->Integral() );
    legend->AddEntry( histo, hist.leg_entry(), "L");    
    
    std::cout << hist.leg_entry() << " - " << histo->GetName() << std::endl;

    histo->SetLineColor(i+1);
    if(i>3){
      histo->SetLineColor(i+2);
    }
    histo->SetTitle("");

    if ( i == 0 ){
      first = histo;
      histo->Draw();
      max = 1.3*histo->GetBinContent(histo->GetMaximumBin());
    }
    else{
      if (1.3*histo->GetBinContent(histo->GetMaximumBin()) > max){
	max = 1.3*histo->GetBinContent(histo->GetMaximumBin());
	first->SetMaximum(max);
      }
      histo->Draw("same");
    }
    i++;
    //    histo->SetName("cl3dpt");
    //    histo->SaveAs("plots/" + TString(_outdir) + "/" + savename + ".root");
  }
  legend->Draw();
  //  _latex->Draw("same");

  gPad->Modified(); gPad->Update(); 
  gPad->SetTicks();

  c->SaveAs("plots/" + TString(_outdir) + "/" + savename + ".png");
  c->SaveAs("plots/" + TString(_outdir) + "/" + savename + ".root");


}




TH2F * Plotter::Draw2D( HistObject hist, int nbins1, double xlow1, double xhigh1, int nbins2, double xlow2, double xhigh2, TString savename){

  TCanvas * c = _canvas;
  c->SetCanvasSize(800, 600);
  gPad->SetTicks(1,1);
  SetLegendXY( 0.6, 0.5, 0.82, 0.75  );

  TH2F* histo = 0;
  histo = _helper.single_plot2D( hist.filename(), hist.treename(), hist.var(), hist.cut(), nbins1, xlow1, xhigh1, nbins2, xlow2, xhigh2 );
  
  _legend->AddEntry( histo, hist.leg_entry(), "L");    


  // histo->SetLineColor(i+1);
  // if(i>3){
  //   histo->SetLineColor(i+2);
  // }
  histo->SetTitle("");
  
  //    if ( i == 0 )

  histo->Draw("COLZ");
  gPad->SetLogz(1);
  histo->Draw("COLZsame");

  // else{
  //   histo->Draw("same");
  // }
  
  //  _latex->Draw("same");
  //  _legend->Draw("same");

  gPad->SetTicks();

  c->SaveAs("plots/" + TString(_outdir) + "/" + savename + ".png");
  c->SaveAs("plots/" + TString(_outdir) + "/" + savename + ".root");

  return histo;
}


TH2F * Plotter::Draw2D( HistObject hist, int nbins1, double* x, int nbins2, double xlow2, double xhigh2, TString savename){

  TCanvas * c = _canvas;
  c->SetCanvasSize(800, 600);
  gPad->SetTicks(1,1);
  SetLegendXY( 0.6, 0.5, 0.82, 0.75  );

  TH2F* histo = 0;
  histo = _helper.single_plot2D( hist.filename(), hist.treename(), hist.var(), hist.cut(), nbins1, x, nbins2, xlow2, xhigh2 );
  _legend->AddEntry( histo, hist.leg_entry(), "L");    
  histo->SetTitle("");
  histo->Draw();
  gPad->SetTicks();

  c->SaveAs("plots/" + TString(_outdir) + "/" + savename + ".png");
  c->SaveAs("plots/" + TString(_outdir) + "/" + savename + ".root");

  return histo;
}







//void Plotter::SaveFile( std::vector<TGraph*>& graphs ){



// TH2F * Plotter::Draw2D( HistObject hist, int nbins1, double* x, int nbins2, double* y, TString savename){

//   TCanvas * c = _canvas;
//   c->SetCanvasSize(800, 600);
//   gPad->SetTicks(1,1);
//   SetLegendXY( 0.6, 0.5, 0.82, 0.75  );


//   TH2F* histo = 0;
//   //  histo = _helper.single_plot2D( hist.filename(), "HGCalTriggerNtupleJet", hist.var(), hist.cut(), nbins1, xlow1, xhigh1, nbins2, xlow2, xhigh2 );
//   histo = _helper.single_plot2D( hist.filename(), "HGCalTriggerNtupleJet", hist.var(), hist.cut(), nbins1, x, nbins2, y  );
  
//   _legend->AddEntry( histo, hist.leg_entry(), "L");    

//   histo->SetTitle("");
//   histo->Draw();
//   gPad->SetTicks();

//   c->SaveAs("plots/" + TString(_outdir) + "/" + savename + ".png");

//   return histo;
// }
  
