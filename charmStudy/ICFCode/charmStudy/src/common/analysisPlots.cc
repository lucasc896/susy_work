#include "analysisPlots.hh"
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
#include "GenObject.hh"
#include "Compute_Variable.hh"
#include "MCOps.hh"

using namespace Operation;

// -----------------------------------------------------------------------------
analysisPlots::analysisPlots( const Utils::ParameterSet& ps ) :
// Misc
   dirName_( ps.Get<std::string>("DirName") ),
   nMin_( ps.Get<int>("MinObjects") ),
   nMax_( ps.Get<int>("MaxObjects") ),
   bTagAlgo_( ps.Get<int>("BTagAlgo") ),
   bTagAlgoCut_( ps.Get<double>("BTagAlgoCut") ),
   minDR_( ps.Get<double>("minDR") ),
   StandardPlots_( ps.Get<bool>("StandardPlots") ),
   threshold_( ps.Get<double>("threshold") )

   { 
   }

// -----------------------------------------------------------------------------
//
analysisPlots::~analysisPlots() {}

// -----------------------------------------------------------------------------
//
void analysisPlots::Start( Event::Data& ev ) {
   initDir( ev.OutputFile(), dirName_.c_str() );
   BookHistos();
}

// -----------------------------------------------------------------------------
//
void analysisPlots::BookHistos() {
   if ( StandardPlots_ ){ StandardPlots(); }

}

// -----------------------------------------------------------------------------
//
bool analysisPlots::Process( Event::Data& ev ) {
   if ( StandardPlots_ ){ StandardPlots(ev); }
   return true;
}



// -----------------------------------------------------------------------------
//
void analysisPlots::StandardPlots() {

   BookHistArray(h_nEvents,
      "n_Events",
      ";;# count",
      1, 0., 1.,
      2, 0, 1, false);

   BookHistArray(h_nJets,
     "n_Jets",
     ";nJets;# count",
     20, 0., 20.,
     1, 0, 1, true);

   BookHistArray(h_nBTagJets,
      "n_BTagged_Jets",
      ";nBJets;# count",
      10, 0., 10.,
      7, 0, 1, true);

   BookHistArray(h_jetPt,
      "jetPt",
      ";p_T (GeV);# count",
      1000, 0., 1000.,
      6, 0, 1, false);   

   BookHistArray(h_leadJetPt,
      "leadJetPt",
      ";p_T (GeV);# count",
      1000, 0., 1000.,
      6, 0, 1, false);

   BookHistArray(h_subLeadJetPt,
      "subLeadJetPt",
      ";p_T (GeV);# count",
      1000, 0., 1000.,
      6, 0, 1, false);   

   BookHistArray(h_commHT,
      "commHT",
      ";HT_(GeV);# count",
      1000, 0., 1000.,
      6, 0, 1, false);

   BookHistArray(h_MET,
      "MET",
      ";MET (GeV);# count",
      1000, 0., 1000.,
      6, 0, 1, false);

   BookHistArray(h_MHT,
      "MHT",
      ";MHT (GeV);# count",
      1000, 0., 1000.,
      6, 0, 1, false);

   BookHistArray(h_MHToverMET,
      "MHToverMET",
      ";MHT/MET;# count",
      100, 0., 10.,
      6, 0, 1, false);     

   BookHistArray(h_hadronicAlphaT,
      "hadronicAlphaT",
      ";alphaT;# count",
      1000, 0., 10.,
      6, 0, 1, false);

   BookHistArray(h_hadronicAlphaTZoom,
      "hadronicAlphaTZoom",
      ";alphaT;# count",
      100, 0., 1.,
      6, 0, 1, false);

   BookHistArray(h_leadJetdelPhi,
      "leadJetdelPhi",
      ";#delta #phi;# count",
      50, 0., 3.2,
      6, 0, 1, false);

   BookHistArray(h_stopGenPtVect,
      "stopGenPtVect",
      ";vectorial gen Pt;# count",
      1000, 0., 1000.,
      1, 0, 1, false);

   BookHistArray(h_stopGenPtScal,
      "stopGenPtScal",
      ";scalar gen Pt;# count",
      1000, 0., 1000.,
      1, 0, 1, false);

   BookHistArray(h_delPhi_vs_scalGenPt,
      "delPhi_vs_scalGenPt",
      ";scalar gen p_T stop pair (GeV);#delta #phi (lead jet pair);",
      200, 0., 1000.,
      20, 0., 3.2,
      1, 0, 1, false);

   BookHistArray(h_delPhi_vs_vectGenPt,
      "delPhi_vs_vectGenPt",
      ";vectorial gen p_T stop pair (GeV);#delta #phi (lead jet pair);",
      100, 0., 600.,
      20, 0., 3.2,
      1, 0, 1, false);

   BookHistArray(h_dPhiStopCharm,
      "dPhiStopCharm",
      ";#delta #phi (stop-charm);# count",
      50, 0, 3.2,
      1, 0, 1, false);

   BookHistArray(h_dPhiNeutCharm,
      "dPhiNeutCharm",
      ";#delta #phi (neut-charm);# count",
      50, 0, 3.2,
      1, 0, 1, false);

   BookHistArray(h_dPhiStopNeut,
      "dPhiStopNeut",
      ";#delta #phi (stop-neut);# count",
      50, 0, 3.2,
      1, 0, 1, false);

}


// -----------------------------------------------------------------------------
//
std::ostream& analysisPlots::Description( std::ostream& ostrm ) {
   ostrm << "Charm Study Analysis Plots ";
   ostrm << "(bins " << nMin_ << " to " << nMax_ << ") ";
   return ostrm;
}


// -----------------------------------------------------------------------------
//
bool analysisPlots::StandardPlots( Event::Data& ev ) {
// main module
   unsigned int nobjkt = ev.CommonObjects().size();
   double evWeight = ev.GetEventWeight();

   h_nEvents[0]->Fill( .5 );

   // a couple event level vetoes
   if (!StandardPlots_) return true;
   if( nobjkt < nMin_ || nobjkt > nMax_ ) return true;

   h_nEvents[1]->Fill( .5, evWeight );


   double evHT                = ev.CommonHT();
   double hadronicAlphaT      = ev.HadronicAlphaT();
   double mht                 =ev.CommonMHT().Pt();
   int nCommJet               = ev.JD_CommonJets().accepted.size();
   vector<double> v_MHTMET    = getMHTandMET( ev );
   vector<double> v_StopGenPt = getStopGenPt( ev );
   int nbjet = 0, plotIndex = 0;

   //
//
   for(int i=0; i<nCommJet; i++){
      // count number of btagged jets
      if( ev.GetBTagResponse(ev.JD_CommonJets().accepted.at(i)->GetIndex(), bTagAlgo_) > bTagAlgoCut_ ) nbjet++;
   }



   h_nJets[0]     ->Fill( nCommJet, evWeight );
   h_nBTagJets[0] ->Fill( nbjet, evWeight );

   // get plot index
   plotIndex = getPlotIndex( nbjet );
   
   h_nBTagJets[plotIndex+1]         ->Fill( nbjet );
   h_commHT[plotIndex]              ->Fill( evHT, evWeight );
   h_hadronicAlphaT[plotIndex]      ->Fill( hadronicAlphaT, evWeight );
   h_hadronicAlphaTZoom[plotIndex]  ->Fill( hadronicAlphaT, evWeight );
   h_MHT[plotIndex]                 ->Fill( mht, evWeight );
   h_MET[plotIndex]                 ->Fill( v_MHTMET[1], evWeight );
   h_MHToverMET[plotIndex]          ->Fill( v_MHTMET[2], evWeight );
   h_stopGenPtVect[0]               ->Fill( v_StopGenPt.at(0), evWeight );
   h_stopGenPtScal[0]               ->Fill( v_StopGenPt.at(1), evWeight );

   for(int i=0; i<nCommJet; i++) h_jetPt[plotIndex]->Fill( ev.JD_CommonJets().accepted.at(i)->Pt(), evWeight );

   double jetDeltaPhi = 0;
   if (ev.JD_CommonJets().accepted.size()>1){
      jetDeltaPhi = ROOT::Math::VectorUtil::DeltaPhi(*ev.JD_CommonJets().accepted.at(0),*ev.JD_CommonJets().accepted.at(1));
      h_leadJetdelPhi[plotIndex] ->Fill( fabs(jetDeltaPhi), evWeight );
      h_delPhi_vs_scalGenPt[0]   ->Fill( v_StopGenPt.at(1), fabs(jetDeltaPhi), evWeight );
      h_delPhi_vs_vectGenPt[0]   ->Fill( v_StopGenPt.at(0), fabs(jetDeltaPhi), evWeight );
      
      h_leadJetPt[plotIndex]     ->Fill( ev.JD_CommonJets().accepted.at(0)->Pt(), evWeight );
      h_subLeadJetPt[plotIndex]  ->Fill( ev.JD_CommonJets().accepted.at(1)->Pt(), evWeight );
   }
   
   Event::GenObject gStop1(0.,0.,0.,0.,0,0,0,0);
   Event::GenObject gStop2(0.,0.,0.,0.,0,0,0,0);
   Event::GenObject gCharm1(0.,0.,0.,0.,0,0,0,0);
   Event::GenObject gCharm2(0.,0.,0.,0.,0,0,0,0);
   Event::GenObject gNeut1(0.,0.,0.,0.,0,0,0,0);
   Event::GenObject gNeut2(0.,0.,0.,0.,0,0,0,0); 
   Event::GenObject gEmpty(0.,0.,0.,0.,0,0,0,0);  
   for( std::vector<Event::GenObject>::const_iterator igen = ev.GenParticles().begin(); igen != ev.GenParticles().end(); ++igen ){
      if( (*igen).GetID() == 1000006 )    gStop1 = *igen;
      if( (*igen).GetID() == -1000006 )   gStop2 = *igen;

      if( (*igen).GetStatus() == 3 ){   
         if( (fabs((*igen).GetID()) == 4) && ((*igen).GetMotherID() == 1000006) )         gCharm1 = *igen;
         if( (fabs((*igen).GetID()) == 4) && ((*igen).GetMotherID() == -1000006) )        gCharm2 = *igen;
         if( (fabs((*igen).GetID()) == 1000022) && ((*igen).GetMotherID() == 1000006) )   gNeut1 = *igen;
         if( (fabs((*igen).GetID()) == 1000022) && ((*igen).GetMotherID() == -1000006) )  gNeut2 = *igen;
      }

   }
   if( (gStop1!=gEmpty) && (gStop2 !=gEmpty) && (gCharm1 !=gEmpty) && (gCharm2 !=gEmpty) && (gNeut1 !=gEmpty) && (gNeut2 !=gEmpty) ){
      h_dPhiStopCharm[0]->Fill( getGenDeltaPhi(gStop1, gCharm1), evWeight );
      h_dPhiStopCharm[0]->Fill( getGenDeltaPhi(gStop2, gCharm2), evWeight );
      h_dPhiNeutCharm[0]->Fill( getGenDeltaPhi(gNeut1, gCharm1), evWeight );
      h_dPhiNeutCharm[0]->Fill( getGenDeltaPhi(gNeut2, gCharm2), evWeight );
      h_dPhiStopNeut[0] ->Fill( getGenDeltaPhi(gStop1, gNeut1), evWeight );
      h_dPhiStopNeut[0] ->Fill( getGenDeltaPhi(gStop2, gNeut2), evWeight );   
   }


   return true;

}


// -----------------------------------------------------------------------------
//
int analysisPlots::getPlotIndex( int nbjet ){
   
   for(int i=0; i<5; i++){
      if (nbjet==i)  return i;
      if (nbjet>4)   return 5;
   }

   return 0;

}


// -----------------------------------------------------------------------------
//
vector<double> analysisPlots::getMHTandMET( Event::Data& ev ){

  vector<double> rev;

  PolarLorentzV mHT(0.,0.,0.,0.);
  std::vector<Event::Jet const *>::const_iterator ijet = ev.JD_CommonJets().accepted.begin();
  std::vector<Event::Jet const *>::const_iterator jjet = ev.JD_CommonJets().accepted.end();
  std::vector<Event::Jet const *>::const_iterator ibaby = ev.JD_CommonJets().baby.begin();
  std::vector<Event::Jet const *>::const_iterator jbaby = ev.JD_CommonJets().baby.end();

  for(; ijet!=jjet; ++ijet){
    if( (*ijet)->Pt() > threshold_ ){
      mHT -= (**ijet);
    }
  }
  for( ; ibaby!=jbaby; ++ibaby){
    if( (*ibaby)->pt() > threshold_ ){
      mHT -= (**ibaby);
    }
  }

  rev.push_back(mHT.Pt());
  LorentzV calomet = LorentzV(*ev.metP4pfTypeI());
  //  LorentzV calomet = LorentzV(*ev.metP4ak5());
  //  LorentzV calomet = LorentzV(*ev.metP4calo());
  //  LorentzV calomet = LorentzV(*ev.metP4pf());
  //  LorentzV calomet = LorentzV(*ev.metP4caloTypeI());

  for(int i = 0; i < int(ev.LD_CommonElectrons().accepted.size());i++){
    calomet = calomet+(*ev.LD_CommonElectrons().accepted[i]);
  }
  for(int i = 0; i < int(ev.PD_CommonPhotons().accepted.size());i++){
    calomet = calomet+(*ev.PD_CommonPhotons().accepted[i]);
  }
  for(int i = 0; i < int(ev.LD_CommonMuons().accepted.size());i++){
    calomet = calomet+(*ev.LD_CommonMuons().accepted[i]);
  }

  rev.push_back(calomet.Pt());

  double mhtovermet = mHT.Pt()/calomet.Pt();
  rev.push_back( mhtovermet );

  return rev;

}


// -----------------------------------------------------------------------------
//
vector<double> analysisPlots::getStopGenPt( Event::Data& ev ){

   vector<double> v_genPtVals;

   PolarLorentzV genPtVect(0.,0.,0.,0.);
   double genPtScal = 0;

   for( std::vector<Event::GenObject>::const_iterator igen = ev.GenParticles().begin(); igen != ev.GenParticles().end(); ++igen ) {
      if ( fabs((*igen).GetID())==1000006 ){
         genPtVect += (*igen);
         genPtScal += (*igen).Pt();
      }
   }

   v_genPtVals.push_back( genPtVect.Pt() );
   v_genPtVals.push_back( genPtScal );

   //std::cout << "Vector: " << v_genPtVals.at(0) << " Scalar: " << v_genPtVals.at(1) << std::endl;

   return v_genPtVals;

}

double analysisPlots::getGenDeltaPhi( const Event::GenObject& gOb1, const Event::GenObject& gOb2 ){

   double dPhi = ROOT::Math::VectorUtil::DeltaPhi( gOb1, gOb2 );
   return fabs( dPhi );

}

