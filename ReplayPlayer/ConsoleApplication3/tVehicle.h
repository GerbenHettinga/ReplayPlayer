#include "tXYZ.h"

class tVehicle {

	short index;
	int health; //unsigned byte
	int gasPedal; //unsigned byte
	tXYZ xyz; //18 
	short[] unknown1; //2
	short[] unknown2; //2 /* 0045BA03 */
	int modelID; //word
	int unknown; /* CAutomobile.damageManager.field_14 */
	int[] velocity; //3-xyz unsigned bytes
	int steerAngle; //unsigned byte
	short[] unknown_flags; //9
	int[] colors; //2 unsigned bytes
	short unknown_flag; /* isplayervehicle? 0045B901 */
	short unknown_flag2; /* CVehicle.field_594 */
	short[] gap; //3

};