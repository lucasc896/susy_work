#include "dataSubmission.hh"
#include "CommonOps.hh"
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
#include "GenMatrixBin.hh"

using namespace Operation;

// -----------------------------------------------------------------------------
dataSubmission::dataSubmission( const Utils::ParameterSet& ps ) :
// Misc
dirName_( ps.Get<std::string>("DirName") ),
  nMin_( ps.Get<int>("MinObjects") ),
  nMax_( ps.Get<int>("MaxObjects") ),
  GenPt_(ps.Get<std::vector<double> >("GenPt")),
  GenEta_(ps.Get<std::vector<double> >("GenEta")),
  Pt_Eta_Eff_(ps.Get<std::vector<double> >("Pt_Eta_Eff")),

  Mistag_GenPt_(ps.Get<std::vector<double> >("Mistag_GenPt")),
  Mistag_GenEta_(ps.Get<std::vector<double> >("Mistag_GenEta")),
  Mistag_Pt_Eta_Eff_(ps.Get<std::vector<double> >("Mistag_Pt_Eta_Eff")),

  JetPt_High_(ps.Get<std::vector<double> >("JetPt_High")),
  JetPt_Low_(ps.Get<std::vector<double> >("JetPt_Low")),
  Variation_(ps.Get<std::vector<double> >("Variation")),
  DY_(ps.Get<bool>("DY")),



  StandardPlots_( ps.Get<bool>("StandardPlots") )

  { 
  }

// -----------------------------------------------------------------------------
//
dataSubmission::~dataSubmission() {}

// -----------------------------------------------------------------------------
//
void dataSubmission::Start( Event::Data& ev ) {
  initDir( ev.OutputFile(), dirName_.c_str() );
  BookHistos();
}

// -----------------------------------------------------------------------------
//
void dataSubmission::BookHistos() {
  if ( StandardPlots_ )           { StandardPlots(); }
}

// -----------------------------------------------------------------------------
//
bool dataSubmission::Process( Event::Data& ev ) {
  if ( StandardPlots_ )               { StandardPlots(ev); }
  return true;
}



// -----------------------------------------------------------------------------
//
void dataSubmission::StandardPlots() {



}
// -----------------------------------------------------------------------------

std::ostream& dataSubmission::Description( std::ostream& ostrm ) {
  ostrm << "Hadronic Common Plots ";
  ostrm << "(bins " << nMin_ << " to " << nMax_ << ") ";
  return ostrm;
}

// -----------------------------------------------------------------------------



bool dataSubmission::StandardPlots( Event::Data& ev ) {

  


}
