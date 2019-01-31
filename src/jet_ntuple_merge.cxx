#include "jet_ntuple_merger_v2.h"
#include "CmdLine.h"

int main( int argc, char ** argv ){

  CmdLine cmd( argc, argv ) ;


  std::string filein   = cmd.string_val( "--filein" ) ;
  std::string treename = cmd.string_val( "--treename", "hgcalTriggerNtuplizer/HGCalTriggerNtuple" ) ;

  std::string filein_jet   = cmd.string_val( "--filein_jet", "" ) ;
  std::string treename_jet = cmd.string_val( "--treename_jet", "jets" ) ;
  std::string fileout   = cmd.string_val( "--fileout" ) ;


  std::string runtype   = cmd.string_val( "--runtype" ) ;

  jet_ntuple_merger_v2 jnm;
  
  if ( runtype == "jet" )
    jnm.add_jet( filein, treename, filein_jet, treename_jet, fileout );

  if ( runtype == "pu" )
    jnm.create_cones( filein, treename, fileout );

  if ( runtype == "layer" )
    jnm.calibrate_layer( filein, treename, fileout, true, false, true );




  return 0;
}
