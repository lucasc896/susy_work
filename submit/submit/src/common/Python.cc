#include <boost/python.hpp>
#include "dataSubmission.hh"

using namespace boost::python;

BOOST_PYTHON_MODULE(lib_data_Submit) {

 class_<Operation::dataSubmission, bases<Operation::_Base> >( "dataSubmission",
                    init<const Utils::ParameterSet&>());


}
