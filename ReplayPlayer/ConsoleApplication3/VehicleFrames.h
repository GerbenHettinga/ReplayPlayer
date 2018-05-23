#pragma once
#include "types.h"
#include <vector> 

class VehicleFrames
{
public:
	VehicleFrames();
	~VehicleFrames();

	std::vector<tVehicle> frames;
};

