#ifndef _PlotterResponse_h_
#define _PlotterResponse_h_

#include "Plotter.h"

class PlotterResponse : public Plotter {


 private:

 public:

  using Plotter::Plotter;
  void Draw(std::vector<HistObject>& hists, std::string savename, std::string xvar);
  //  void Draw(std::vector<TH2F*> &histo, std::vector<TString> &legentry, std::string savename, std::string xvar);

};

#endif
