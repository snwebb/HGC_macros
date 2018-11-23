#include "PlotterEventDisplay.h"

void PlotterEventDisplay::Draw( TH1 * hist, TString option, TString savename ){

  std::system( ("mkdir -p plots/" + _outdir )   .c_str() );
  TCanvas * c = _canvas;
  
  if ( option == "3dtc" ){
    hist->GetXaxis()->SetTitle("#eta(TC)");
    hist->GetXaxis()->SetTitleOffset(1.5);
    hist->GetYaxis()->SetTitle("#phi(TC)");
    hist->GetZaxis()->SetTitle("layer(TC)");
    hist->SetTitle("");
    hist->Draw("BOX2");
  }
  
  if ( option == "3dcl" ){    
    hist->GetXaxis()->SetTitle("#eta(C2D)");
    hist->GetXaxis()->SetTitleOffset(1.5);
    hist->GetYaxis()->SetTitle("#phi(C2D)");
    hist->GetZaxis()->SetTitle("layer(C2D)");
    hist->SetTitle("");
    hist->Draw("BOX2");
  }


  if ( option == "2dc3d"){
    
    
    hist->GetXaxis()->SetTitle("#eta(C3D)");
    hist->GetXaxis()->SetTitleOffset(1.3);
    hist->GetYaxis()->SetTitle("#phi(C3D)");
    hist->GetZaxis()->SetTitle("p_{T}(C3D) [GeV]");
    hist->SetTitle("");
    hist->SetStats(0);
    c->SetLeftMargin(0.15);
    c->SetRightMargin(0.15);
    hist->SetMarkerSize(1.5);
    gStyle->SetPaintTextFormat("4.1f");
    hist->Draw("colz");

  }


  if ( option == "gen" ){



  hist->GetXaxis()->SetTitle("#eta(gen)");
  hist->GetXaxis()->SetTitleOffset(1.5);
  hist->GetYaxis()->SetTitle("#phi(gen)");
  hist->GetZaxis()->SetTitle("p_{T}(gen) [GeV]");
  hist->SetTitle("");
  hist->SetStats(0);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  hist->SetMarkerSize(1.2);
  gStyle->SetPaintTextFormat("4.1f");
  hist->Draw("text");


  }

  if ( option == "2dc3d" || option == "gen"){

    float phi_min  = -3.2;
    float phi_max  = 3.2;
    float eta_min  = -3.2;
    float eta_max  = 3.2;

    std::vector<TLine*> gr_x;
    std::vector<TLine*> gr_y;
    
    for(unsigned int i=0; i<216; i++){
      float phi = -TMath::Pi() + i*2*TMath::Pi()/216.;    
      if(phi>phi_min && phi<phi_max){
	TLine* line = new TLine(eta_min,phi,eta_max,phi);
	gr_x.push_back(line);
      }
    }
    
    for(unsigned int i=0; i<36; i++){
      float rOverZ = 0.09 + i*(0.52-0.09)/36.;
      float eta_plus = TMath::ASinH(1/rOverZ);
      if(eta_plus>eta_min && eta_plus<eta_max){
	TLine* line = new TLine(eta_plus,phi_min,eta_plus,phi_max);
	gr_y.push_back(line);
      }
      float eta_minus = -TMath::ASinH(1/rOverZ);
      if(eta_minus>eta_min && eta_minus<eta_max){
	TLine* line = new TLine(eta_minus,phi_min,eta_minus,phi_max);
	gr_y.push_back(line);
      }
    }
    
    for(auto& gr : gr_x)
      gr->Draw("same");
    for(auto& gr : gr_y)
      gr->Draw("same");
    
    
  }
  
  //    _latex->Draw("same");
  
  
  c->SaveAs("plots/" + TString(_outdir) + "/" + savename + ".pdf");
  
  
}
