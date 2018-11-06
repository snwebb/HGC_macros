#ifndef _PlotterResolution_h_
#define _PlotterResolution_h_

#include "Helpers.h"
#include "Plotter.h"

class PlotterResolution : public Plotter {

 private:

 public:

  void Draw(std::vector<HistObject>& hists, std::vector<double>& x, TString savename);
  //  void Draw(std::string process, std::vector<TString> &filename, std::vector<TString> &leg_entry, std::vector<TString> &var, std::vector<double>& x, TString cut);
  std::vector<float> effectiveRMS(const TH1F* histo, double fraction= 0.683, int fitrebin= 1);
  //  TH1F* histo_ET_resolution_Gamma_noPUS(TString filename, TString var, TString cut);
  TH1F* histo_ET_resolution(TString filename, TString var, TString cut, std::string process, bool PUS, double binlow, double binhigh);
  TF1* doubleCBFit(TH1F* histo, double rangeInSigma=2., int fitrebin=1);
  static double DoubleCB( double* x, double* par);
};



#endif
