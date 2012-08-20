#ifndef hadronic_include_dataSubmission_hh
#define hadronic_include_dataSubmission_hh

#include "PlottingBase.hh"
#include "Utils.hh"
#include "Types.hh"

class TH1D;
class TH2D;

namespace Operation {

  class dataSubmission : public PlottingBase {

  public:

    dataSubmission( const Utils::ParameterSet& );
    ~dataSubmission();

    void Start( Event::Data& );
    bool Process( Event::Data& );


  std::ostream& Description( std::ostream& );

private:

    void BookHistos();
    Double_t MT2( Event::Data& );
    Double_t MT2_Leading( Event::Data& );
    Double_t DeltaHT( Event::Data& );
    std::string dirName_;
    UInt_t nMin_;
    UInt_t nMax_;
    std::vector<double> GenPt_;
    std::vector<double> GenEta_;
    std::vector<double> Pt_Eta_Eff_;
    std::vector<double> Mistag_GenPt_;
    std::vector<double> Mistag_GenEta_;
    std::vector<double> Mistag_Pt_Eta_Eff_;
    std::vector<double> JetPt_High_;
    std::vector<double> JetPt_Low_;
    std::vector<double> Variation_;

    bool StandardPlots_;
    bool DY_;

    void StandardPlots();
    bool StandardPlots( Event::Data& );

  };

}

#endif // hadronic_include_WeeklyUpdatePlots_hh
