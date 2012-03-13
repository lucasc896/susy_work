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
#include "GenMatrixBin.hh"

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
}

//definition of the Process public function
bool TruthAnalysis::Process ( Event::Data& ev ) {
	if ( StandardPlots_ ) { StandardPlots(ev); }
return true;
}

//definition the printout tool
std::ostream& TruthAnalysis::Description( std::ostream& ostrm ) {
  ostrm << "Truth b multiplicity plots";
  ostrm << "(bins " << nMin_ << " to " << nMax_ << ") ";
  return ostrm;
}


void TruthAnalysis::StandardPlots() {

	BookHistArray( bmulti,
    "No. of b quarks",
    ";b multiplicity;# count",
    8, 0, 8,
    1, 0, 1, true );   

}


bool TruthAnalysis::StandardPlots( Event::Data& ev ) {
	unsigned int nobjkt = ev.CommonObjects().size();

	if ( StandardPlots_ ) {
    //When nobj >= nMin_
    	if( nobjkt >= nMin_ && nobjkt <= nMax_){
      			bmulti[0]->			Fill(Hasbquark(ev));
	    }// if obj >= nMin
	} //StandardPlots_
	
	return true;
}

int TruthAnalysis::Hasbquark( Event::Data& ev ) {
	int num_bquark = 0;
	
	//need to change code here to include the GenMatrixBin module
	
	//loop over gen object event content
	for( std::vector<Event::GenObject>::const_iterator igen = ev.GenParticles().begin(); igen != ev.GenParticles().end(); ++igen ) {
    	if( isbquark( ev, (*igen) ) ){
      		num_bquark++;
    	}
	}
	
	return num_bquark;
}

bool TruthAnalysis::isbquark( Event::Data& ev, const Event::GenObject& gobj ){

  if( gobj.GetStatus()==3 ){ //only status3 objects considered
  	 if( fabs( gobj.GetID() )==5 ){ //only b-quarks considered
  		if( gobj.Pt() > 0. && fabs( gobj.Eta() ) < 15. ){
	  		return true;
	  	}	
	 }  
  }

  return false;
}
