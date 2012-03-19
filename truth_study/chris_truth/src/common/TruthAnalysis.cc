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
    
    BookHistArray( susy_scan,
    "mSUGRA_Scan_Plane",
    ";m0;m0.5",
    150, 0, 3000,
    51, 0, 1020,
    1, 0, 1, true );

	BookHistArray( bmulti_0pt,
	"b-multipicity_0gev_pt_cut",
	";num bs;count",
	4, 0, 4,
	1, 0, 1, false );

    BookHistArray( scan_bmulti_0pt,
    "mSUGRA_b-quark_multi-0_gev_pt_cut",
    ";m0;m0.5",
    150, 0, 3000,
    51, 0, 1020,
    4, 0, 1, false );
    
    BookHistArray( bmulti_50pt,
	"b-multipicity_50gev_pt_cut",
	";num bs;count",
	4, 0, 4,
	1, 0, 1, false );
    
    BookHistArray( scan_bmulti_50pt,
    "mSUGRA_b-quark_multi-50_gev_pt_cut",
    ";m0;m0.5",
    150, 0, 3000,
    51, 0, 1020,
    4, 0, 1, false );
    
    BookHistArray( bmulti_100pt,
	"b-multipicity_100gev_pt_cut",
	";num bs;count",
	4, 0, 4,
	1, 0, 1, false );
    
    BookHistArray( scan_bmulti_100pt,
    "mSUGRA_b-quark_multi-100_gev_pt_cut",
    ";m0;m0.5",
    150, 0, 3000,
    51, 0, 1020,
    4, 0, 1, false );

}


bool TruthAnalysis::StandardPlots( Event::Data& ev ) {
	unsigned int nobjkt = ev.CommonObjects().size();
	int numb[3];
    double M0 = 0.;
    double M12 = 0.;
    double MChi = 0.;

    if(ev.M0.enabled()){
      M0 = ev.M0();
    }
    if(ev.MG.enabled()){
      M0 = ev.MG();
    }
    if(ev.M12.enabled()){
      M12 = ev.M12();
    }
    if(ev.MLSP.enabled()){
      M12 = ev.MLSP();
    }
    if(ev.MChi.enabled()){
      MChi = ev.MChi();
    }	
    
    // set pt-cuts here
	numb[0] = Hasbquark(ev, 0.);
	numb[1] = Hasbquark(ev, 50.);
	numb[2] = Hasbquark(ev, 100.);

	if ( StandardPlots_ ) {
    //When nobj >= nMin_
    	if( nobjkt >= nMin_ && nobjkt <= nMax_){
      		//fill all of the multiplicity scan plots
      		for(int k=0;k<3;k++){
	      		if ( numb[0] == k){ scan_bmulti_0pt[k]	->Fill( M0,M12,1 );}
	      		if ( numb[1] == k){ scan_bmulti_50pt[k]	->Fill( M0,M12,1 );}
	      		if ( numb[2] == k){ scan_bmulti_100pt[k]->Fill( M0,M12,1 );}
	      	}
			if ( numb[0] > 2) { scan_bmulti_0pt[3]	->Fill( M0,M12,1 );}
			if ( numb[1] > 2) { scan_bmulti_50pt[3]	->Fill( M0,M12,1 );}
			if ( numb[2] > 2) { scan_bmulti_100pt[3]->Fill( M0,M12,1 );}
			
			bmulti_0pt[0]	->Fill(numb[0]);
			bmulti_50pt[0]	->Fill(numb[1]);
			bmulti_100pt[0]	->Fill(numb[2]);
			
			susy_scan[0]	->Fill( M0,M12,1 );
			
	    }// if obj >= nMin
	} //StandardPlots_
	
	return true;
}

int TruthAnalysis::Hasbquark( Event::Data& ev, float pt_cut ) {
	int num_bquark = 0;
	
	//need to change code here to include the GenMatrixBin module
	
	//loop over gen object event content
	for( std::vector<Event::GenObject>::const_iterator igen = ev.GenParticles().begin(); igen != ev.GenParticles().end(); ++igen ) {
    	if( isbquark( ev, (*igen), pt_cut ) ){
      		num_bquark++;
    	}
	}
	
	return num_bquark;
}

bool TruthAnalysis::isbquark( Event::Data& ev, const Event::GenObject& gobj, float pt_cut ){

  if( gobj.GetStatus()==3 ){ //only status3 objects considered
  	 if( fabs( gobj.GetID() )==5 ){ //only b-quarks considered
  		if( gobj.Pt() > 0. && fabs( gobj.Eta() ) < 15. ){
  			//return true;
  			if( gobj.Pt() > pt_cut) return true;
	  	}	
	 }  
  }

  return false;
}
