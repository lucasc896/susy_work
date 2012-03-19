#ifndef hadronic_include_Trigger_hh
#define hadronic_include_Trigger_hh

#include "PlottingBase.hh"
#include "Utils.hh"
#include "Types.hh"

class TH1D;
class TH2D;

namespace Operation {

  class Trigger : public PlottingBase {

  public:

    Trigger( const Utils::ParameterSet& );
    ~Trigger();

    void Start( Event::Data& );
    bool Process( Event::Data& );

    std::ostream& Description( std::ostream& );

  private:

    void BookHistos();

    std::string dirName_;
    UInt_t nMin_;
    UInt_t nMax_;
    bool ECompare(const LorentzV & o1, const LorentzV & o2);
    
    bool StandardPlots_;
    void StandardPlots();
    bool StandardPlots( Event::Data& );
    bool AlphaT_;
    bool Alphat( Event::Data &);
    void Alphat();
    };

  }

#endif // hadronic_include_Trigger_hh
