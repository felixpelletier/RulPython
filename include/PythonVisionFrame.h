#ifndef __PythonVisionFrame_H_
#define __PythonVisionFrame_H_

#include <stdint.h>
#include <memory>
#include "Pose.h"
#include <VisionFrame.h>
#include <boost/python.hpp>

namespace Rule {

typedef uint32_t uint32;

struct PythonVisionFrame
{
	
	PythonVisionFrame( const VisionFrame& visionFrame ){
		this->cameraId = visionFrame.cameraId;
		this->frameId = visionFrame.frameId;
		this->teamCount = visionFrame.teamCount;
		this->balls.append(*visionFrame.balls);
		for (int t = 0; t < visionFrame.teamCount; t++){
			Team team = Team(visionFrame.teams[t]);
			this->teams.append(team);
		}
	}

	struct Team {
		Team( const VisionFrame::Team& other ) {
			this->teamId = other.teamId;
			this->robotCount = other.robotCount;
			for (int r = 0; r < other.robotCount; r++){
				this->robots.append(other.robots[r]);
			}

		}

		uint32 teamId;
		boost::python::list robots;
		uint32 robotCount;
	};

	uint32 cameraId;
    	uint32 frameId;
    	uint32 teamCount;
	boost::python::list balls;
	boost::python::list teams;
	
};



} //namespace Rule

#endif //__PythonVisionFrame_H_
