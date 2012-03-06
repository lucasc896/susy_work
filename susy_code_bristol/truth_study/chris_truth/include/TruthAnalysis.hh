#ifndef hadronic_include_TruthAnalysis_hh
#define hadronic_include_TruthAnalysis_hh

#include "PlottingBase.hh"
#include "Utils.hh"
#include "Types.hh"

class TH1D;
class TH2D;

namespace Operation {

  class TruthAnalysis : public PlottingBase {

  public:

    TruthAnalysis( const Utils::ParameterSet& );
    ~TruthAnalysis();

    void Start( Event::Data& );
    bool Process( Event::Data& );

    std::ostream& Description( std::ostream& );

  private:

    void BookHistos();

	std::string dirName_;
    UInt_t nMin_;
    UInt_t nMax_;
    bool StandardPlots_;
    
    void StandardPlots();
    bool StandardPlots( Event::Data& );

	std::vector<TH1D*>  Chris_test_hist;

  };

}

#endif //hadronic_include_TruthAnalysis_hh
