#include "Replay.h"
#include <stdio.h>
#include <iostream>
#include <fstream>



Replay::Replay() {
	//open replay.rep
	std::ifstream filestr("C:\\Users\\Gerben\\Documents\\GTA San Andreas User Files\\replay.rep", std::ios::binary | std::ios::ate);
	//std::ifstream filestr("C:\\Documents\\GTA San Andreas User Files\\replay.rep", std::ios::binary | std::ios::ate);

	if (!filestr) {
		std::cerr << "Unable to open file replay.rep";
		exit(1);   // call system to stop
	}

	std::streamsize size = filestr.tellg();
	filestr.seekg(0, std::ios::beg);

	std::vector<char> buf(size);
	filestr.read(buf.data(), size);

	int byteCounter;
	bool eof = false;
	int frameCount = 0;
	

	std::vector<char> sub(&buf[0], &buf[8]);
	tHeader* h = reinterpret_cast<tHeader*>(sub.data());
	int nextBlock = (unsigned int) buf[8];

	std::cout << "read header, nextblock: " << nextBlock << std::endl;

	byteCounter = 9;
	int filesize = 1008888800;
	int x = (int)((size - 8) / 100000);
	Frame f =  Frame();

	for (int i = 0; i < x; i++) {
		if (eof) {
			byteCounter = i * 100000 + 8;
			nextBlock = buf[byteCounter];
			byteCounter++;
		}
		eof = false;
		while (true) {
			switch (nextBlock) {
				case 5: {
						
						std::vector<char> cam(&buf[byteCounter], &buf[byteCounter + 87]);
						tblock5 *c = reinterpret_cast<tblock5*>(cam.data());
						byteCounter += 87;
						//f.setCamera(c);
						nextBlock = (unsigned int)buf[byteCounter];
						byteCounter++;
						//std::cout << "camera block" << std::endl;
					}
					break;
				case 6: {
						
						std::vector<char> daytime(&buf[byteCounter], &buf[byteCounter + 3]);
						tblock6 *dt = reinterpret_cast<tblock6*>(daytime.data());
						byteCounter += 3;
						//f.setDaytime(dt);
						nextBlock = (unsigned int)buf[byteCounter];
						byteCounter++;
						//std::cout << "daytime block" << std::endl;
					}
					break;
				case 7: {
						std::vector<char> weather(&buf[byteCounter], &buf[byteCounter + 7]);
						tblock7 *wt = reinterpret_cast<tblock7*>(weather.data());
						byteCounter += 7;
						//rf.setWeather(w);
						nextBlock = (unsigned int)buf[byteCounter];
						byteCounter++;
						//std::cout << "weather block" << std::endl;
					}
					break;
				case 9: {
						std::vector<char> time(&buf[byteCounter], &buf[byteCounter + 7]);
						tblock9 *wt = reinterpret_cast<tblock9*>(time.data());
						byteCounter += 7;
						//rf.setTiming(t);
						nextBlock = (unsigned int)buf[byteCounter];
						byteCounter++;
						//std::cout << "block 9" << std::endl;
					}
					break;
				case 15 :
				case 2: {
						std::vector<char> veh(&buf[byteCounter], &buf[byteCounter + 55]);
						tblock2 *v = reinterpret_cast<tblock2*>(veh.data());
						byteCounter += 55;
						f.vehicles.push_back(v->vehicle);
						nextBlock = (unsigned int)buf[byteCounter];
						//std::cout << "vehicle block 2" << std::endl;
						byteCounter++;
					}
					break;
				case 1: {
						std::vector<char> veh(&buf[byteCounter], &buf[byteCounter + 51]);
						tblock1 *v = reinterpret_cast<tblock1*>(veh.data());
						byteCounter += 51;
						f.vehicles.push_back(v->vehicle);
						//std::cout << "vehicle block 1" << std::endl;
						nextBlock = (unsigned int)buf[byteCounter];
						byteCounter++;
					}
					break;
				case 3: {
						std::vector<char> play(&buf[byteCounter], &buf[byteCounter + 7]);
						byteCounter += 7;

						//std::cout << "player block 3" << std::endl;
						nextBlock = (unsigned int)buf[byteCounter];
						byteCounter++;
					}
					break;
				case 18: {
						std::vector<char> b18(&buf[byteCounter], &buf[byteCounter + 75]);
						byteCounter += 75;
						//std::cout << "block 18" << std::endl;
						nextBlock = (unsigned int)buf[byteCounter];
						byteCounter++;
					}
					break;
				case 19: {
						std::vector<char> cloth(&buf[byteCounter], &buf[byteCounter + 119]);
						byteCounter += 119;
						//rf.setClothes(cl);
						//std::cout << "clothes block 19" << std::endl;
						nextBlock = (unsigned int)buf[byteCounter];
						byteCounter++;
					}
					break;
				case 4: {
						std::vector<char> ped(&buf[byteCounter], &buf[byteCounter + 51]);
						tblock4 *p = reinterpret_cast<tblock4*>(ped.data());
						byteCounter += 51;
						player.push_back(*p);
						//rf.setPed(pe);
						nextBlock = (unsigned int)buf[byteCounter];
						byteCounter++;
						//std::cout << "ped block 4" << std::endl;
					}
					break;
				case 12: {
						std::vector<char> b12(&buf[byteCounter], &buf[byteCounter + 15]);
						byteCounter += 15;
						//rf.setB12(b12);	
						nextBlock = (unsigned int)buf[byteCounter];
						byteCounter++;
						//std::cout << "block 12" << std::endl;
					}
					break;
				case 13: 
				case 14:
				case 8: {
						//std::cout << "end frame " << frameCount << std::endl;
						byteCounter += 3;
						frameCount++;
						frames.push_back(f);
						f = Frame();
						nextBlock = (unsigned int)buf[byteCounter];
						byteCounter++;
					}
					break;
				case 10: {
						byteCounter += 28;
						nextBlock = (unsigned int)buf[byteCounter];
						//std::cout << "block 10" << std::endl;
						byteCounter++;
					}
					break;
				case 11: {
						byteCounter += 20;
						nextBlock = (unsigned int)buf[byteCounter];
						//std::cout << "block 11" << std::endl;
						byteCounter++;
					}
					break;
				case 16: {
						byteCounter += 55;
						nextBlock = (unsigned int)buf[byteCounter];
						//std::cout << "block 16" << std::endl;
						byteCounter++;
					}
					break;
				case 17: {
						std::vector<char> veh(&buf[byteCounter], &buf[byteCounter + 59]);
						byteCounter += 59;
						//rf.addVehicle(v);
						nextBlock = (unsigned int)buf[byteCounter];
						//std::cout << "block 17" << std::endl;
						byteCounter++;
					}
					break;
				case 0: {
						std::cout << "EOF, frames:" << frameCount << std::endl;
						eof = true;
					}
					break;
			}
			if (eof == true) break;
		}
	}
		
	Frame* fr;
	tVehicle* tv;
	tblock4* p;
	int inds[255] = {0};

	std::cout << "Done reading, gathering vehicle data" << std::endl;

	//iterate over frames to aggregate tVehicles per vehicle
	for (int i = 0; i < frames.size(); i++) {
		fr = &frames[i];
		for (int j = 0; j < fr->vehicles.size(); j++) {
			tv = &fr->vehicles[j];

			if (inds[(int)tv->index] > 0) {
				inds[(int)tv->index]++;
				vehicles[(int)tv->index].push_back(*tv);
			} else {
				std::cout << "new index " << (int)tv->index << std::endl;
				inds[(int)tv->index]++;
				vehicles[(int)tv->index].push_back(*tv);
			}
		}
	}

	std::cout << "Done gathering" << std::endl;

	for (int i = 0; i < 255; i++) {
		if (inds[i] > 0) {

			std::cout << "index: " << i << " frames: " << inds[i] << " model ID: " << vehicles[i][0].modelID; 
			if (i == (player[0].vehicleIndex - 1)) {
				std::cout << " <<< ";
			}
			std::cout << std::endl;
		}
	}


	std::cout << ":: END ::" << std::endl;
}


Replay::~Replay() {

}
