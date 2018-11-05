#ifndef _PlotterResponse_h_
#define _PlotterResponse_h_


#include "Plotter.h"

class PlotterResponse : public Plotter {


 private:

 public:

  void Draw(std::vector<TH2F*> &histo, std::vector<TString> &legentry, std::string plotname, std::string xvar);

};

#endif
