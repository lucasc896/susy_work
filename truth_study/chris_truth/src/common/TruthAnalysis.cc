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
#include "GenObject.hh"

using namespace Operation;

//constructor of TruthAnalysis class
TruthAnalysis::TruthAnalysis( const Utils::ParameterSet& ps ) :

dirName_( ps.Get<std::string>("DirName") ),
nMin_( ps.Get<int>("MinObjects") ),
nMax_( ps.Get<int>("MaxObjects") ),

StandardPlots_( ps.Get<bool>("StandardPlots") ),
PrePlots_( ps.Get<bool>("PrePlots") )

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
	if ( PrePlots_ ) { PrePlots(); }
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

	BookHistArray( postbmulti,
    "No. of b quarks post-selection",
    ";b multiplicity;# count",
    10, 0, 10,
    1, 0, 1, true );
    
}

void TruthAnalysis::PrePlots() {

	BookHistArray( prebmulti,
    "No. of b quarks pre-selection",
    ";b multiplicity;# count",
    10, 0, 10,
    1, 0, 1, true );	
    
}

bool TruthAnalysis::StandardPlots( Event::Data& ev ) {
	unsigned int nobjkt = ev.CommonObjects().size();

	if ( StandardPlots_ ) {
    //When nobj >= nMin_
    	if( nobjkt >= nMin_ && nobjkt <= nMax_){
      			postbmulti[0]->			Fill(Hasbquark(ev));
	    }// if obj >= nMin
	} //StandardPlots_
	
	return true;
}

bool TruthAnalysis::PrePlots( Event::Data& ev ) {
	unsigned int nobjkt = ev.CommonObjects().size();

	if ( PrePlots_ ) {
    //When nobj >= nMin_
    	if( nobjkt >= nMin_ && nobjkt <= nMax_){
      			prebmulti[0]->			Fill(Hasbquark(ev));
	    }// if obj >= nMin
	} //StandardPlots_
	
	return true;
}

int TruthAnalysis::Hasbquark( Event::Data& ev ) {
	int num_bquark = 0;
	
	//loop over gen object event content
	for( std::vector<Event::GenObject>::const_iterator igen = ev.GenParticles().begin(); igen != ev.GenParticles().end(); ++igen ) {
    	if( isbquark( ev, (*igen) ) ){
      		num_bquark++;
    	}
	}
	
	return num_bquark;
}

bool TruthAnalysis::isbquark( Event::Data& ev, const Event::GenObject& gobj ){
  bool isbquark=false;

    //is on-shell
  if( gobj.GetStatus() == 3 ) {
	  //looks for a b-quark
    if( fabs( gobj.GetID() ) == 5 ){ 

      if( gobj.Pt() > 0 && fabs( gobj.Eta() ) < 15. ){
	  	isbquark = true;
	  } //pt and eta
    } //ID
  } //Status

  return isbquark;
}
