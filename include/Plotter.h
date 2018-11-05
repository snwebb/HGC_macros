#ifndef _Plotter_h_
#define _Plotter_h_


#include "Helpers.h"

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

 public:

  Plotter();
  ~Plotter();

};


#endif
