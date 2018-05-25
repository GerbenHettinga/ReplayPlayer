// ConsoleApplication3.cpp : Defines the entry point for the console application.
//
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include "stdafx.h" 
#include <fstream>
#include "Replay.h"
#include <time.h>
using namespace std;

#include "declares.h"					// Declares the methods/variables for performing/tracking Freeplay functionality
#include "utilities.h"					// Declares/Implements the helper methods we'll be using (hooking into game, memory editing, misc)


Replay* rep;
int chosenVehicleID;

// --- Function Implementations ------------------------------------------------

// Stuff to do immediately when Freeplay has been (re/)hooked in
void init_freeplay()
{
	function_lock = false; debug_mode = false;
}

// Toggle Function lock
void do_lock()
{
	function_lock = !(function_lock);

}

void openReplay() {
	rep = new Replay();
}


void setSpeed(DWORD pVehicle, float a, float b, float c) {
	SetSingle(pVehicle + 0x44, a);
	SetSingle(pVehicle + 0x48, b);
	SetSingle(pVehicle + 0x4C, c);
}

void setSpeed(DWORD pVehicle, float speed) {
	SetSingle(pVehicle + 0x44, speed);
	SetSingle(pVehicle + 0x48, speed);
	SetSingle(pVehicle + 0x4C, speed);
}

void test() {
	DWORD pVehicle = GetLong(0xBA18FC);
	float a = GetSingle(pVehicle + 0x44);
	float b = GetSingle(pVehicle + 0x48);
	float c = GetSingle(pVehicle + 0x4C);
	setSpeed(pVehicle, 0.02, 0.02, 0.02);
}

void readChosenVehicle() {
	cin.clear();
	std::cout << "Choose the vehicle id" << std::endl;
	std::cin >> chosenVehicleID;
	std::cout << "Chosen vehicle id " << chosenVehicleID <<  std::endl;
}

void setLean(DWORD pVehicle, tblock4* ped) {

	//set bike animations
	float quantLean = (float)ped->unknown23.vehicleAnimAmount;
	float lean = 1.0f / 10.0f *  quantLean;
	float angle = 0.6f / 10.0f *  quantLean;
	if (ped->unknown23.vehicleAnimType == 195) {   //left
		SetSingle(pVehicle + 0x654, lean);
		SetSingle(pVehicle + 0x64C, -angle);
	}
	else if (ped->unknown23.vehicleAnimType == 196) { //forward
		SetSingle(pVehicle + 0x658, -lean);
	}
	else if (ped->unknown23.vehicleAnimType == 197) { //right
		SetSingle(pVehicle + 0x654, -lean);
		SetSingle(pVehicle + 0x64C, angle);
	}
	else if (ped->unknown23.vehicleAnimType == 198) { //backward
		SetSingle(pVehicle + 0x658, lean);
	}
}

void setReplayState(DWORD pVehicle, tVehicle* now, tVehicle* prev, tblock4* ped, float u) {
	DWORD pMtrx = GetLong(pVehicle + 0x14);
	RwV3D* xyz = &now->xyz.pos;
	char* right = now->xyz.xyz_right;
	char* up = now->xyz.xyz_top;

	float a, b, c, d, e, f, x, y, z;


	if (u > 0.0) {
		x = u * now->xyz.pos.X + (1.0 - u) * prev->xyz.pos.X;
		y = u * now->xyz.pos.Y + (1.0 - u) * prev->xyz.pos.Y;
		z = u * now->xyz.pos.Z + (1.0 - u) * prev->xyz.pos.Z;

		a = u * (float)now->xyz.xyz_right[0] + (1.0 - u) * (float)prev->xyz.xyz_right[0];
		b = u * (float)now->xyz.xyz_right[1] + (1.0 - u) * (float)prev->xyz.xyz_right[1];
		c = u * (float)now->xyz.xyz_right[2] + (1.0 - u) * (float)prev->xyz.xyz_right[2];

		d = u * (float)now->xyz.xyz_top[0] + (1.0 - u) * (float)prev->xyz.xyz_top[0];
		e = u * (float)now->xyz.xyz_top[1] + (1.0 - u) * (float)prev->xyz.xyz_top[1];
		f = u * (float)now->xyz.xyz_top[2] + (1.0 - u) * (float)prev->xyz.xyz_top[2];


	} else {
		x = now->xyz.pos.X;
		y = now->xyz.pos.Y;
		z = now->xyz.pos.Z;

		a = (float)right[0];
		b = (float)right[1];
		c = (float)right[2];

		d = (float)up[0];
		e = (float)up[1];
		f = (float)up[2];
	}

	//normalize up- and right-vectors
	float f_s = (a*a + b*b + c*c);
	 a = a / sqrt(f_s);
	 b = b / sqrt(f_s);
	 c = c / sqrt(f_s);

	float f_s2 = (d*d + e*e + f*f);
	d = d / sqrt(f_s2);
	e = e / sqrt(f_s2);
	f = f / sqrt(f_s2);

	//set positions
	SetSingle(pMtrx + 0x30, x);  // X
	SetSingle(pMtrx + 0x34, y);  // Y
	SetSingle(pMtrx + 0x38, z);  // Z

	SetSingle(pMtrx, a);  // right
	SetSingle(pMtrx + 0x04, b);  // right
	SetSingle(pMtrx + 0x08, c);  // right

	SetSingle(pMtrx + 0x10, d);  // look x
	SetSingle(pMtrx + 0x14, e);  // look y
	SetSingle(pMtrx + 0x18, f);  // look z

	SetSingle(pMtrx + 0x49C, 1.0);


	setLean(pVehicle, ped);
}


void playReplay() {

	DWORD pActor = GetLong(0xB6F5F0);
	DWORD pVehicle = GetLong(0xBA18FC);

	DWORD pMtrx = GetLong(pVehicle + 0x14);

	int count = 1;

	double time_counter = 0;

	clock_t this_time = clock();
	clock_t last_time = this_time;

	tVehicle* now;
	tVehicle* prev = &rep->vehicles[chosenVehicleID][0];
	int i = 0;
	int interp = 0;
	std::cout << rep->vehicles[chosenVehicleID].size() << std::endl;
	while (i < rep->vehicles[chosenVehicleID].size()) {

		this_time = clock();

		time_counter += (double)(this_time - last_time);

		last_time = this_time;

		now = &rep->vehicles[chosenVehicleID][i];

		setLean(pVehicle, &rep->player[i]);

		
		//75 fps
		if (time_counter >(double)(13 * CLOCKS_PER_SEC / 1000)) {
			time_counter -= (double)(13 * CLOCKS_PER_SEC / 1000);
			
			if (interp < 1) {
				setReplayState(pVehicle, now, prev, &rep->player[i], 0.0);
				i++;
				prev = now;
			} else {
				setReplayState(pVehicle, now, prev, &rep->player[i], (float) interp * 0.333);		
			}	
			
			interp = (interp + 1) % 3;
		} 
	}
	
	std::cout << "done" << std::endl;

}


int _tmain(int argc, _TCHAR* argv[])
{
	bool first_run = true;
	bool manual_slowmo = false;
	HWND window_hook;
	HANDLE process_hook;
	// Main loop, repeat forever

	while (true == true)
	{
		// Ensure we are hooked into the game				[which we aren't to begin with, and will no longer be if the game is closed]
		if (first_run || !process_active(process_hook))
		{
			if (!first_run)
			{
				cout << endl << "GTA SA Game Closed - will remain in standby until itself closed, or another instance of SA is opened." << endl;
				CloseHandle(process_hook);
			}

			window_hook = hook_in_window();
			process_hook = hook_in_process(window_hook);
			cout << "\"Replay Reader \& Player\" - by Reynolds based on Freeplay by Dannye" << endl << endl;
			first_run = false;
			init_freeplay();								// Stuff to do immediately when Freeplay has been (re/)hooked in
		}

		// If game not inactive/minimized, lets do stuff!
		if (!IsIconic(window_hook))
		{

			if (!function_lock)									// [and if 'function lock' NOT ON...]
			{
						// "J" Pressed: read replay
				if (key_pressed(0x4B)) playReplay(); //K
				
			}
		}

		if (key_pressed(0x4A)) openReplay(); //J
		if (key_pressed(0x4D)) readChosenVehicle();  //M
		if (key_pressed(0x4E)) test(); //N

		Sleep(100);		// Refresh Rate Approx 1 Second
	}
	return 0;
}





