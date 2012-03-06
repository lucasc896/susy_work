#include "Trigger.hh"
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

using namespace Operation;

// -----------------------------------------------------------------------------
Trigger::Trigger( const Utils::ParameterSet& ps ) :
// Misc
dirName_( ps.Get<std::string>("DirName") ),
  nMin_( ps.Get<int>("MinObjects") ),
  nMax_( ps.Get<int>("MaxObjects") ),
// MT2
  StandardPlots_( ps.Get<bool>("StandardPlots") ),
  AlphaT_(ps.Get<bool>("AlphaT") )
  {}

// -----------------------------------------------------------------------------
//
Trigger::~Trigger() {}

// -----------------------------------------------------------------------------
//
void Trigger::Start( Event::Data& ev ) {
  initDir( ev.OutputFile(), dirName_.c_str() );
  BookHistos();
}

// -----------------------------------------------------------------------------
//
void Trigger::BookHistos() {
  if ( StandardPlots_ )           { StandardPlots(); }
  if ( AlphaT_ )                      { Alphat(); }
}

// -----------------------------------------------------------------------------
//
bool Trigger::Process( Event::Data& ev ) {
  if ( StandardPlots_ )               { StandardPlots(ev); }
  if ( AlphaT_ )                      { Alphat(ev); }
  return true;
}

// -----------------------------------------------------------------------------
//
std::ostream& Trigger::Description( std::ostream& ostrm ) {
  ostrm << "Hadronic Common Plots ";
  ostrm << "(bins " << nMin_ << " to " << nMax_ << ") ";
  return ostrm;
}

// -----------------------------------------------------------------------------
//

void Trigger::Alphat(){

}


void Trigger::StandardPlots() {

  
}
// -----------------------------------------------------------------------------
//
// struct Trigger::EComp_sort
// {
//   bool operator() (const LorentzV & o1, const LorentzV & o2)  {
//     return(o1.Et() > o2.Et());
//   }
// };

template<template <typename> class P = std::less >
struct sort_LVec_Et
{
   template<class T1, class T2>
   bool operator()(const T1 & o1, const T2 & o2)
   {
       return P<double>()( o2.Et(), o1.Et() );
   }
};
// -----------------------------------------------------------------------------
//

bool Trigger::StandardPlots( Event::Data& ev ) {

  return true;
}

bool Trigger::Alphat( Event::Data& ev ) {

  // Alpha_t variable
  std::vector<Event::Jet const *>::const_iterator ijet = ev.JD_CommonJets().accepted.begin();
  std::vector<Event::Jet const *>::const_iterator jjet = ev.JD_CommonJets().accepted.end();
  std::vector<LorentzV> newJets;
  double Ht = 0.,mhtx = 0.,mhty = 0., dHt = 0., mHt = 0., aT = 0.,codeAlphaT= 0.;
    cout << "______________START EVENT__________________ " << endl;
    std::vector<LorentzV> firstCol;
    std::vector<LorentzV> secondCol;
  for( ; ijet != jjet; ijet++){
    newJets.push_back(**ijet);
    cout <<"Jet Et is " << (*ijet)->Et() << " Jet No is" << newJets.size() << endl;
    std::vector<bool> pseudo;
    codeAlphaT = AlphaT()( newJets, pseudo, true );
    if ( pseudo.size() != newJets.size() ) { abort(); }

    Ht += (*ijet)->Et();
    mhtx-=((*ijet)->Pt())*cos((*ijet)->phi());
    mhty-=((*ijet)->Pt())*sin((*ijet)->phi());
    mHt = sqrt(mhty*mhty + mhtx*mhtx); // Make MHT
    dHt = std::min( fabs(dHt + (*ijet)->Et() ) , fabs(dHt - (*ijet)->Et()) );


    // ( fabs(dHt + (*ijet)->Et() ) < fabs(dHt - (*ijet)->Et()) ? firstCol.push_back( *ijet ) : secondCol.push_back( *ijet ) );

    aT = ( Ht - fabs(dHt) ) / ( 2. * sqrt( ( Ht*Ht ) - ( mHt*mHt ) ) ); // calc alphaT


    cout << dHt << " Min Delta HT from Iterative method \n ______________________________" << std::endl;
    cout << " Assumption wrong " << codeAlphaT << " != " << aT <<  " No Jets considered " << newJets.size() << endl;


  }
  return true;
}


