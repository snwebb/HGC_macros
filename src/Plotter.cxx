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

  delete _canvas;
  delete _legend;
  delete _latex;

}


void Plotter::InitialiseCanvas(){

  _canvas = new TCanvas("c","c",650,600);
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
  SetLegendXY( 0.6, 0.5, 0.82, 0.75  );
  _legend->Clear();
  int i = 0;
    for (auto &graph: graphs ){    
      
      graph->SetLineColor(i+1);      
      if(i>3){
	graph->SetLineColor(i+2);
      }

      if ( i==0 ){
	graph->Draw("ap");
	graph->SetTitle(";gen p_{T};Resolution");
	graph->GetXaxis()->SetRangeUser(20,300);
	graph->GetYaxis()->SetRangeUser(0,0.4);
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
  mg->GetYaxis()->SetRangeUser(0,0.4);


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

  // TF1 * f_mean = new TF1 ( "f_mean", "[0] + [1]*x" , 0, 400);
  // TF1 * f_rmsup = new TF1 ( "f_rmsup", "[0] + [1]*x" ,0 , 400);
  // TF1 * f_rmsdown = new TF1 ( "f_rmsdown", "[0] + [1]*x",0, 400 );


  // TF1 * f_mean = new TF1 ( "f_mean", "[0] + [1]*x + [2]*x*x" , 0, 400);
  // TF1 * f_rmsup = new TF1 ( "f_rmsup", "[0] + [1]*x + [2]*x*x" ,0 , 400);
  // TF1 * f_rmsdown = new TF1 ( "f_rmsdown", "[0] + [1]*x + [2]*x*x",0, 400 );

  //  TF1 * Logx = new TF1 ( "logx", "[0]+ [1]*TMath::Log(x+[2]) + [3]*TMath::Log(x+[2])*TMath::Log(x+[2])*x" );
  //  TF1 * Logx = new TF1 ( "logx", "[0]+ [1]*TMath::Log(x+[2]) + [3]*pow(TMath::Log(x+[4]),2)*x" );
  //  TF1 * Logx = new TF1 ( "logx", "[0]+ [1]*pow(TMath::Log(x),2)*x + [2]*TMath::Log(x)" );
  ///    TF1 * Logx = new TF1 ( "logx", "[0]+ [1]*pow(TMath::Log(x),2)*x + [2]*TMath::Log(x+)" );
  //    TF1 * Logx = new TF1 ( "logx", "[0]+ [1]*pow(TMath::Log(x),2)*TMath::Exp(-x) + [2]*x" );

  //    TF1 * Logx = new TF1 ( "logx", "[0]+ [1]*pow(TMath::Log([2]*x),2)*x - TMath::Log([2]*x+20)" );

  //    TF1 * Logx = new TF1 ( "logx", "[0] + [1]*pow(TMath::Log(10*x),2)*x -[2]*TMath::Log(10*x+50)" );

  //    TF1 * Logx = new TF1 ( "logx", "[0] + [1]*pow(TMath::Log([2]*1000000000*x),2)*x -[3]*TMath::Log(10*x+200)" );
  //    TF1 * Logx = new TF1 ( "logx", "[0] + [1]*pow(TMath::Log([2]*100000*x),1)*x -[3]*TMath::Log(10*x+200)" );


  TF1 * Logx = new TF1 ( "logx", "[0] + [1]*TMath::Log(x)*x + [2]*x -[3]*TMath::Log([4]*x+200)" , 5 , 350);  
  Logx->SetParLimits( 0, 10,1000);
  Logx->SetParLimits( 1, -0.5,0.5);
  Logx->SetParLimits( 2, 0.001,10);
  Logx->SetParLimits( 3, 1,1000);
  Logx->SetParLimits( 4, 0.001,50);

  TF1 * pol1 = new TF1 ( "pol1", "[0] + [1]*x" , 20 , 350);  

    //    Logx->SetParLimits( 5, 100,300);

  // tf1 * Logx = new TF1 ( "logx", "[0]+ [1]*pow(TMath::Log(x+[3]),2)*x + [2]*TMath::Log(x+[4])" );

  // TF1 * f_mean = new TF1 ( "f_mean", "[0] + [1]*x + [2]*x*x + [3]*x*x*x" , 0, 400);
  // TF1 * f_rmsup = new TF1 ( "f_rmsup", "[0] + [1]*x + [2]*x*x + [3]*x*x*x" ,0 , 400);
  // TF1 * f_rmsdown = new TF1 ( "f_rmsdown", "[0] + [1]*x + [2]*x*x + [3]*x*x*x",0, 400 );

  // TF1 * f_mean = new TF1 ( "f_mean", Logx , 5, 350);
  // TF1 * f_rmsup = new TF1 ( "f_rmsup", Logx , 5, 350);
  // TF1 * f_rmsdown = new TF1 ( "f_rmsdown", Logx , 5, 350);


  TF1 * f_mean = (TF1*)pol1->Clone("f_mean" );
  TF1 * f_rmsup = (TF1*)pol1->Clone("f_rmsup" );
  TF1 * f_rmsdown = (TF1*)pol1->Clone("f_rmsdown" );

  // TF1 * f_mean = (TF1*)Logx->Clone("f_mean" );
  // TF1 * f_rmsup = (TF1*)Logx->Clone("f_rmsup" );
  // TF1 * f_rmsdown = (TF1*)Logx->Clone("f_rmsdown" );

   TFitResultPtr r;
  TFitResultPtr r_rmsup;
  TFitResultPtr r_rmsdown;

   //   r =  pmean->Fit( "pol1", "R","",20,200);
   //   r =  pmean->Fit( "pol3", "R","",0,400);

   //   r =  pmean->Fit( "[0]+[1]*TMath::Log(x+[2])*x", "R","",0,400);
   //   r =  pmean->Fit( "[0]*TMath::Erf(x)", "R","",0,400);
   //   TVirtualFitter::SetMaxIterations( 1000000 );

   //   r =  pmean->Fit( Logx, "R","",5,350);


   r =  pmean->Fit( pol1, "R","",20,300);



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
    //    std::cout << "we have " <<  p_rms->GetNbinsX()+1 << " bins " << std::endl;
    //    std::cout << "bin i of x = " << i << std::endl;

    std::vector<double> rms_list;  
    //    std::vector<double> rms_err_list;
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

	// rms_up  ->SetPoint(i-1, p_rms->GetBinCenter(i), p_rms->GetBinContent(i)+p_rms->GetBinError(i));
	// rms_down->SetPoint(i-1, p_rms->GetBinCenter(i), p_rms->GetBinContent(i)-p_rms->GetBinError(i));
	
      // rms_up  ->SetPointError(i-1, p_rms->GetBinWidth(i)/2, pmean->GetBinError(i) );
      // rms_down->SetPointError(i-1, p_rms->GetBinWidth(i)/2, pmean->GetBinError(i) );
	
	histCopy->Delete();

      }//ntries
    
    
      auto min_value = *std::min_element(rms_list.begin(),rms_list.end());
      auto max_value = *std::max_element(rms_list.begin(),rms_list.end());
      //      std::cout << "min max -= " << min_value << " - " << max_value << std::endl;
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
      //      std::cout << "Total = " << total << std::endl;
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


    
    //    std::cout << rms.size() << " - " << rms_err.size() << std::endl;


    //normal way    
    rms_up  ->SetPoint(i-1, p_rms->GetBinCenter(i), double(centralbin_nominal+rms.at(i-1))/double(bins_per_unit) );
    rms_down->SetPoint(i-1, p_rms->GetBinCenter(i), double(centralbin_nominal-rms.at(i-1))/double(bins_per_unit) );
    
    //test way
    // rms_up  ->SetPoint(i-1, p_rms->GetBinCenter(i), p_rms->GetBinContent(i)+p_rms->GetBinError(i) );
    // rms_down  ->SetPoint(i-1, p_rms->GetBinCenter(i), p_rms->GetBinContent(i)-p_rms->GetBinError(i) );
    






    //    std::cout << " ------- " << double (rms_err.at(i-1)) << " - " << double (rms_err.at(i-1))/double (bins_per_unit) << std::endl;

    rms_up  ->SetPointError(i-1, 0, double (rms_err.at(i-1))/double (bins_per_unit) );
    rms_down->SetPointError(i-1, 0, double (rms_err.at(i-1))/double (bins_per_unit) );
    // rms_up  ->SetPointError(i-1, 0.5*p_rms->GetBinWidth(i), double (rms_err.at(i-1))/double (bins_per_unit) );
    // rms_down->SetPointError(i-1, 0.5*p_rms->GetBinWidth(i), double (rms_err.at(i-1))/double (bins_per_unit) );
     
  }


  
  // r = rms_up->Fit("pol3", "R", "", 0, 400);
  // r = rms_down->Fit("pol3", "R", "", 0, 400);


  r_rmsup = rms_up->Fit(pol1, "RS", "", 20, 300);
  
  r = rms_down->Fit(pol1, "R", "", 20, 300);  

  f_mean->SetParameter( 0, pmean->GetFunction("pol1")->GetParameter( 0 ) );
  
  f_mean->SetParameter( 1, pmean->GetFunction("pol1")->GetParameter( 1 ) );
  
  f_mean->SetParErrors ( pmean->GetFunction("pol1")->GetParErrors() );
  
  f_rmsup->SetParameter( 0, rms_up->GetFunction("pol1")->GetParameter( 0 ) );
  f_rmsup->SetParameter( 1, rms_up->GetFunction("pol1")->GetParameter( 1 ) );
  f_rmsup->SetParErrors ( rms_up->GetFunction("pol1")->GetParErrors() );
  
  f_rmsdown->SetParameter( 0, rms_down->GetFunction("pol1")->GetParameter( 0 ) );
  f_rmsdown->SetParameter( 1, rms_down->GetFunction("pol1")->GetParameter( 1 ) );
  f_rmsdown->SetParErrors ( rms_down->GetFunction("pol1")->GetParErrors() );

  
  f_rmsup->SetRange(20,300);
  f_rmsdown->SetRange(20,300);

  f_rmsup->Draw("same");
  f_rmsdown->Draw("same");
  f_mean->Draw("same");

  //rms_up->Draw("same");
  //  rms_down->Draw("same");

  pmean->Draw("same");		

  gPad->SetTicks();
  //  gPad->RedrawAxis();

  c->SaveAs("plots/" + TString(_outdir) + "/" + savename + ".png");
  c->SaveAs("plots/" + TString(_outdir) + "/" + savename + ".root");

  c->Clear();

     std::cout << "--------------" << std::endl;
  for (int i = 1; i < p_rms->GetNbinsX()+1; i++){


    //Using the fits
    double x[1] = { p_rms->GetBinCenter(i) };
    double err[1];  // error on the function at point x0
    r_rmsup->GetConfidenceIntervals(1, 1, 1, x, err, 0.683, false);




    double sigma = 0.5 * std::abs( f_mean->GetX(f_rmsup->Eval(p_rms->GetBinCenter(i)) ) - f_mean->GetX(f_rmsdown->Eval(p_rms->GetBinCenter(i)) ) ); 
    double sigma_err = 0.5 * std::abs( f_mean->GetX(f_rmsup->Eval(p_rms->GetBinCenter(i)) + err[0]    ) - f_mean->GetX(f_rmsdown->Eval(p_rms->GetBinCenter(i)) - err[0] ) ); 


    std::cout << p_rms->GetBinCenter(i) << " -  "<< f_rmsup->Eval(p_rms->GetBinCenter(i)) << " - " << f_mean->GetX(f_rmsup->Eval(p_rms->GetBinCenter(i)) ) << std::endl;
    std::cout << sigma << std::endl;

    //Using the 68% counting method
    // double sigma_68 = rms.at(i-1)/double(bins_per_unit);
    // double sigma_err = rms_err.at(i-1)/double(bins_per_unit);
    //     std::cout << "err from fit = " << err[0]  <<  " - " << sigma_err << std::endl;
    // sigma = std::abs( f_mean->GetX( sigma + f_mean->Eval(p_rms->GetBinCenter(i) ) ) - p_rms->GetBinCenter(i) );
    //    sigma_err = std::abs( f_mean->GetX( sigma_err + f_rmsup->Eval(p_rms->GetBinCenter(i) ) ) - p_rms->GetBinCenter(i) );
    // //    sigma_err = std::abs( f_mean->GetX( err[0] + f_mean->Eval(p_rms->GetBinCenter(i) ) ) - p_rms->GetBinCenter(i) );


    //    std::cout << "21: " <<  i <<" - " << sigma << " - " << sigma_err << std::endl;



    // std::cout << i << " - " << p_rms->GetBinCenter(i) << std::endl;
    // std::cout << "1: " <<  sigma1 << " - " << sigma_err1 << std::endl;    
    // std::cout << "22: " <<  sigma << " - " << sigma_err << std::endl;


    resolution->SetPoint(i-1, p_rms->GetBinCenter(i), sigma/p_rms->GetBinCenter(i));
    resolution->SetPointError(i-1, 0.5*p_rms->GetBinWidth(i), std::abs(sigma-sigma_err)/p_rms->GetBinCenter(i));


  }

  resolution->Draw();
  resolution->GetXaxis()->SetRangeUser(20,300);
  resolution->GetYaxis()->SetRangeUser(0,0.4);
  resolution->Draw("same");
  c->SaveAs("plots/" + TString(_outdir) + "/"+savename+"resolution.png");
  c->SaveAs("plots/" + TString(_outdir) + "/"+savename+"resolution.root");

  // std::cout << f_rmsup->Eval(60) << " - " << f_rmsdown->Eval(60) << std::endl;
  // //  std::cout << f_mean->GetX(f_rmsup->Eval(60)) << " - " << f_mean->GetX(f_rmsdown->Eval(60)) << std::endl;
  // std::cout << f_mean->GetX(94.7561) << " - " << f_mean->GetX(64.9826) << std::endl;
  // std::cout << "Sigma at 60 = " << 0.5 * std::abs( f_mean->GetX(f_rmsup->Eval(60)) - f_mean->GetX(f_rmsdown->Eval(60)) ) << std::endl;

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
    histo->SetTitle("");

    if ( i == 0 ){
	histo->Draw();
       	gPad->SetLogy(logy);
    }
    else{
      histo->Draw("same");
    }
    i++;
    histo->SetName("cl3dpt");

  }

  //_latex->Draw("same");
  _legend->Draw("same");

  gPad->SetTicks();
  c->SaveAs("plots/" + TString(_outdir) + "/" + savename + ".root");
  c->SaveAs("plots/" + TString(_outdir) + "/" + savename + ".png");

}


void Plotter::Draw(std::vector<HistObject>& hists, int nbins, double xlow, double xhigh, TString savename){

  TCanvas * c = _canvas;
  c->SetCanvasSize(800, 600);
  gPad->SetTicks(1,1);
  SetLegendXY( 0.6, 0.5, 0.82, 0.75  );

  int i = 0;
  for (auto &hist: hists ){    

    TH1F* histo = 0;
    histo = _helper.single_plot( hist.filename(), "HGCalTriggerNtupleJet", hist.var(), hist.cut(), nbins, xlow, xhigh );

    _legend->AddEntry( histo, hist.leg_entry(), "L");    


    histo->SetLineColor(i+1);
    if(i>3){
      histo->SetLineColor(i+2);
    }
    histo->SetTitle("");

    if ( i == 0 )
	histo->Draw();
    else{
      histo->Draw("same");
    }
    i++;
    histo->SetName("cl3dpt");
    histo->SaveAs("plots/" + TString(_outdir) + "/" + savename + ".root");
  }

  //  _latex->Draw("same");
  //  _legend->Draw("same");

  gPad->SetTicks();

  c->SaveAs("plots/" + TString(_outdir) + "/" + savename + ".png");

}




TH2F * Plotter::Draw2D( HistObject hist, int nbins1, double xlow1, double xhigh1, int nbins2, double xlow2, double xhigh2, TString savename){

  TCanvas * c = _canvas;
  c->SetCanvasSize(800, 600);
  gPad->SetTicks(1,1);
  SetLegendXY( 0.6, 0.5, 0.82, 0.75  );


  TH2F* histo = 0;
  histo = _helper.single_plot2D( hist.filename(), "HGCalTriggerNtupleJet", hist.var(), hist.cut(), nbins1, xlow1, xhigh1, nbins2, xlow2, xhigh2 );
  
  _legend->AddEntry( histo, hist.leg_entry(), "L");    


    // histo->SetLineColor(i+1);
    // if(i>3){
    //   histo->SetLineColor(i+2);
    // }
    histo->SetTitle("");

    //    if ( i == 0 )
    histo->Draw();
	// else{
    //   histo->Draw("same");
    // }

    //  _latex->Draw("same");
  //  _legend->Draw("same");

  gPad->SetTicks();

  c->SaveAs("plots/" + TString(_outdir) + "/" + savename + ".png");

  return histo;
}


TH2F * Plotter::Draw2D( HistObject hist, int nbins1, double* x, int nbins2, double xlow2, double xhigh2, TString savename){

  TCanvas * c = _canvas;
  c->SetCanvasSize(800, 600);
  gPad->SetTicks(1,1);
  SetLegendXY( 0.6, 0.5, 0.82, 0.75  );

  TH2F* histo = 0;
  histo = _helper.single_plot2D( hist.filename(), "HGCalTriggerNtupleJet", hist.var(), hist.cut(), nbins1, x, nbins2, xlow2, xhigh2 );
  _legend->AddEntry( histo, hist.leg_entry(), "L");    
  histo->SetTitle("");
  histo->Draw();
  gPad->SetTicks();

  c->SaveAs("plots/" + TString(_outdir) + "/" + savename + ".png");

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
  
