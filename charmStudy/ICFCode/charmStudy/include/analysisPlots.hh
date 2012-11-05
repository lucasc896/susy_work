#ifndef hadronic_include_analysisPlots_hh
#define hadronic_include_analysisPlots_hh

#include "PlottingBase.hh"
#include "Utils.hh"
#include "Types.hh"
#include "JetData.hh"
#include "EventData.hh"
#include "GenObject.hh"
#include "Lepton.hh"

class TH1D;
class TH2D;

namespace Operation {

  class analysisPlots : public PlottingBase {

    public:
  
      analysisPlots( const Utils::ParameterSet& );
      ~analysisPlots();
  
      void Start( Event::Data& );
      bool Process( Event::Data& );
      std::ostream& Description( std::ostream& );
  
    private:
  
      void BookHistos();
      std::string dirName_;
      UInt_t nMin_;
      UInt_t nMax_;
      UInt_t bTagAlgo_;
      double bTagAlgoCut_;
      double minDR_;
      bool StandardPlots_;
      double threshold_;      
  
      void StandardPlots();
      bool StandardPlots( Event::Data& ev );
      int getPlotIndex( int nbjet );
      vector<double> getMHTandMET( Event::Data& ev );
      vector<double> getStopGenPt( Event::Data& ev );
      double getGenDeltaPhi( const Event::GenObject& gOb1, const Event::GenObject& gOb2 );
  
      //histos
      std::vector<TH1D*>  h_nEvents;
      std::vector<TH1D*>  h_nJets;
      std::vector<TH1D*>  h_nBTagJets;
      std::vector<TH1D*>  h_jetPt;
      std::vector<TH1D*>  h_leadJetPt;
      std::vector<TH1D*>  h_subLeadJetPt;
      std::vector<TH1D*>  h_commHT;
      std::vector<TH1D*>  h_MET;
      std::vector<TH1D*>  h_MHT;
      std::vector<TH1D*>  h_MHToverMET;
      std::vector<TH1D*>  h_hadronicAlphaT;
      std::vector<TH1D*>  h_hadronicAlphaTZoom;
      std::vector<TH1D*>  h_leadJetdelPhi;
      std::vector<TH1D*>  h_stopGenPtVect;
      std::vector<TH1D*>  h_stopGenPtScal;
      std::vector<TH2D*>  h_delPhi_vs_scalGenPt;
      std::vector<TH2D*>  h_delPhi_vs_vectGenPt;
      std::vector<TH1D*>  h_dPhiStopCharm;
      std::vector<TH1D*>  h_dPhiNeutCharm;
      std::vector<TH1D*>  h_dPhiStopNeut;

  };

}

#endif // hadronic_include_WeeklyUpdatePlots_hh
