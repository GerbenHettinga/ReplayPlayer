#pragma once
#include "types.h"
#include <vector>

class Frame
{
public:
	
	//tblock3 Player; 
    //tblock4 Ped; 
    //tblock5 Camera; 
	//tblock6 DayTime; 
    //tblock7 Weather; 
	
	Frame();
	~Frame();

	std::vector<tVehicle> vehicles;
};

