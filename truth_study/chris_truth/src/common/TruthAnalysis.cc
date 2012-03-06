#include "TruthAnalysis.hh"
#include "EventData.hh"
#include "KinSuite.hh"
#include "TH1D.h"
#include "TH2D.h"
#include "Types.hh"
#include "mt2_bisect.hh"
#include "AlphaT.hh"
#include "Jet.hh"
#include "Math/VectorUtil.h"
#include "JetData.hh"
#include "TMath.h"

using namespace Operation;

//constructor of TruthAnalysis class
TruthAnalysis::TruthAnalysis( const Utils::ParameterSet& ps ) :

dirName_( ps.Get<std::string>("DirName") ),
nMin_( ps.Get<int>("MinObjects") ),
nMax_( ps.Get<int>("MaxObjects") ),

StandardPlots_( ps.Get<bool>("StandardPlots") )

   {}
   
   
//destructor of TruthAnalysis class
TruthAnalysis::~TruthAnalysis() {}


//definition of the Start function
void TruthAnalysis::Start( Event::Data& ev) {
	initDir( ev.OutputFile(), dirName_.c_str() );
	BookHistos();
}


//definition of the BookHistos() private function
void TruthAnalysis::BookHistos() {
	if ( StandardPlots_ ) { StandardPlots(); }
} //don't really follow why this needs to be done

//definition of the Process public function
bool TruthAnalysis::Process ( Event::Data& ev ) {
	if ( StandardPlots_ ) { StandardPlots(ev); }
}

//definition the printout tool
std::ostream& TruthAnalysis::Description( std::ostream& ostrm ) {
  ostrm << "Hadronic Common Plots ";
  ostrm << "(bins " << nMin_ << " to " << nMax_ << ") ";
  return ostrm;
}


void TruthAnalysis::StandardPlots() {

	BookHistArray( Chris_test_hist,
    "test1",
    ";x;# y",
    10, 0., 1,
    nMax_+1, 0, 1, true );
    
}


bool TruthAnalysis::StandardPlots( Event::Data& ev ) {

	Chris_test_hist[0]->Fill(0.5);
	return true;
}
