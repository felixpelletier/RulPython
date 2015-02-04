#include <utils.h>

#include <boost/python.hpp>

namespace Rule{

template<class T>
boost::python::list vectorToPython(const std::vector<T>& v)
{
    boost::python::list plist;
    for (auto &element : v){
	plist.append(element);
    }
    return plist;
};

}
