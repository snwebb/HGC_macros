#include "Plotter.h"

Plotter::Plotter(){

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

  _latex = new TLatex(2.,1.21,"CMS Simulation Preliminary, VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  _latex->SetTextSize(0.03);

}

void Plotter::InitialiseLegend(){

  _legend = new TLegend(0.4,0.15,0.7,0.5);
  _legend->SetHeader("#splitline{p_T(gen. jet)>20 GeV}{1.6<|#eta(gen.jet)|<2.9}");
  //  _legend->SetHeader("#splitline{p_T(gen. jet)>20 GeV}{1.6<|#eta(gen.jet)|<2.9}");
  _legend->SetFillColor(0);
  _legend->SetBorderSize(0);
  _legend->SetTextSize(0.03);

}


