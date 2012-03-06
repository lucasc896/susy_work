#include <boost/python.hpp>
#include "TruthAnalysis.hh"
#include "Ops.hh"
#include "Trigger.hh"
#include "EventDump.hh"

using namespace boost::python;

BOOST_PYTHON_MODULE(libchris) {

  class_<Operation::TruthAnalysis, bases<Operation::_Base> >( "TruthAnalysis",
                    init<const Utils::ParameterSet&>());
  
  class_<Operation::eventDump, bases<Operation::_Base> >( "EventDump", init<>());
  
  class_<Operation::Trigger, bases<Operation::_Base> >( "PL_TriggerPlots",
                    init<const Utils::ParameterSet&>());

}
