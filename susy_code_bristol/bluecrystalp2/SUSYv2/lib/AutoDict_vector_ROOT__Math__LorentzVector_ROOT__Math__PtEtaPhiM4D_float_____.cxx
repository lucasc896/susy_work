#include "vector"
#include "Math/LorentzVector.h"
#ifdef __CINT__ 
#pragma link C++ nestedclasses;
#pragma link C++ nestedtypedefs;
#pragma link C++ class vector<ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<float> > >+;
#pragma link C++ class vector<ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<float> > >::*;
#ifdef G__VECTOR_HAS_CLASS_ITERATOR
#pragma link C++ operators vector<ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<float> > >::iterator;
#pragma link C++ operators vector<ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<float> > >::const_iterator;
#pragma link C++ operators vector<ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<float> > >::reverse_iterator;
#endif
#endif
