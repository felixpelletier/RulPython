#ifndef  utils_INC
#define  utils_INC


#include <boost/python.hpp>


namespace Rule{
template<class T> boost::python::list vectorToPython(const std::vector<T>& v);
}


#endif   /* ----- #ifndef utils_INC  ----- */
