#ifndef _PlotterEventDisplay_h_
#define _PlotterEventDisplay_h_

#include "Helpers.h"
#include "Plotter.h"

class PlotterEventDisplay : public Plotter {

 private:

 public:

  using Plotter::Plotter;

  void Draw( TH1 * hist, TString option, TString savename );

};

#endif
