#ifndef _Plotter_h_
#define _Plotter_h_


#include "Helpers.h"
#include "CmdLine.h"

class Plotter{

 private:

  void InitialiseLegend();
  void InitialiseCanvas();
  void InitialiseLatex();
  std::vector<HistObject> _histlist;
  TFile * _fileout;

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

  void Draw(std::vector<HistObject>& hists, int nbins, double xlow, double high, TString savename);
  void Draw(std::vector<TH1F*>& hists, std::vector<TString>& legend,  TString savename, bool logy = false);
  TGraphErrors * DrawProfile(TH2F * hist, TString savename, Option_t * option);
  TH2F * Draw2D(HistObject hist, int nbins1, double xlow1, double high1, int nbins2, double xlow2, double high2, TString savename);
  TH2F * Draw2D(HistObject hist, int nbins1, double* x, int nbins2, double xlow2, double high2, TString savename);
  TH2F * Draw2D(HistObject hist, int nbins1, double* x, int nbins2, double* y, TString savename);
  void DrawGraphs (std::vector<TGraphErrors*>& graphs, std::vector<TString>& legend);
  void DrawEtaGraphs (std::vector<TGraphErrors*>& graphs);
  //  void DrawGraphs (std::vector<TGraph*>& graphs);


  template< class T > void SaveFile( std::vector<T>& graphs ){
    _fileout = new TFile ( ("plots/"+_outdir+"/graphs.root").c_str(), "RECREATE");
    for (auto &graph: graphs ){
      graph->Write( );
    };
    _fileout->Close();
    _fileout->Delete();
  }

  //    void SaveFile( std::vector<TGraph*>& graphs );
};


#endif
