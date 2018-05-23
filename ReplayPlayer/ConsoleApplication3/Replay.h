#pragma once
#include <fstream>
#include <vector>
#include "Frame.h"
//#include "types.h"

class Replay {

public:
	Replay();
	Replay(std::ifstream f);
	~Replay();

	std::vector<tVehicle> vehicles[255];
	std::vector<tblock4> player;

private:
	std::vector<Frame> frames;
	
	
};

