#include <boost/python.hpp>
#include "charmEffStudy.hh"

using namespace boost::python;

BOOST_PYTHON_MODULE(lib_charmStudy) {

 class_<Operation::charmEffStudy, bases<Operation::_Base> >( "OP_charmEffStudy",
                    init<const Utils::ParameterSet&>());


}
