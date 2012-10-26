#ifndef hadronic_include_charmEffStudy_hh
#define hadronic_include_charmEffStudy_hh

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

  class charmEffStudy : public PlottingBase {

    public:
  
      charmEffStudy( const Utils::ParameterSet& );
      ~charmEffStudy();
  
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
  
      void StandardPlots();
      bool StandardPlots( Event::Data& ev);
      bool hasTrueQuark( const Event::Data& ev, int pdgID);
      int numTrueQuarks( const Event::Data& ev, int pdgID);
      bool matchedToGenQuark( const Event::Data& ev, const Event::Jet &jet, int pdgID, float minDR );
  
      //histos
      std::vector<TH1D*>  h_nJets;
      std::vector<TH1D*>  h_nBTagJets;
      std::vector<TH1D*>  h_nBTagJetsMatchB;
      std::vector<TH1D*>  h_nBTagJetsMatchC;
      std::vector<TH1D*>  h_nBTagJetsMatchL;
      std::vector<TH1D*>  h_nTrueB;
      std::vector<TH1D*>  h_nTrueC;
      std::vector<TH1D*>  h_BTagEff;
      std::vector<TH1D*>  h_CTagEff;
      std::vector<TH1D*>  h_bMatched_response;
      std::vector<TH1D*>  h_cMatched_response;
      std::vector<TH1D*>  h_lMatched_response;
  
      std::vector<TH2D*>  h_Thresh_v_BTagEff;
      std::vector<TH2D*>  h_Thresh_v_CTagEff;
     
  };

}

#endif // hadronic_include_WeeklyUpdatePlots_hh
