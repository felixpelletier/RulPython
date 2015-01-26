#include <boost/thread.hpp> 
#include <boost/python.hpp>

class StrategieEngine {
	
	void updatePosition();
	private:
		boost::thread updateThread;
	public:
		StrategieEngine();
		~StrategieEngine();
};

