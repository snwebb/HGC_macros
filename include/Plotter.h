#ifndef _Plotter_h_
#define _Plotter_h_


#include "Helpers.h"
#include "CmdLine.h"

class Plotter{

 private:

  void InitialiseLegend();
  void InitialiseCanvas();
  void InitialiseLatex();

 protected:

  TLegend * _legend;
  TCanvas * _canvas;
  TLatex * _latex;
  Helpers _helper;
  std::string  _outdir;

  void SetLegendXY(Double_t x1, Double_t y1, Double_t x2, Double_t y2);

 public:

  Plotter();
  Plotter( CmdLine * cmd );
  ~Plotter();


};


#endif
