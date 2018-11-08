#include "jet_ntuple_merger_v2.h"
#include "CmdLine.h"

int main( int argc, char ** argv ){

  CmdLine cmd( argc, argv ) ;


  std::string filein   = cmd.string_val( "--filein" ) ;
  std::string treename = cmd.string_val( "--treename", "hgcalTriggerNtuplizer/HGCalTriggerNtuple" ) ;

  std::string filein_jet   = cmd.string_val( "--filein_jet" ) ;
  std::string treename_jet = cmd.string_val( "--treename_jet", "jets" ) ;
  std::string fileout   = cmd.string_val( "--fileout" ) ;

  jet_ntuple_merger_v2 jnm;
  
  jnm.add_jet( filein, treename, filein_jet, treename_jet, fileout );

  return 0;
}
