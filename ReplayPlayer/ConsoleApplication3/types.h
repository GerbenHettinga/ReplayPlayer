#pragma pack(1)
struct RwV3D
{
	float X;
	float Y;
	float Z;
};

#pragma pack(1)
struct RwMatrix
{
	RwV3D   right;
	int   flags;
	RwV3D   top;
	int   __gap1;
	RwV3D   at;
	int   __gap2;
	RwV3D   pos;
	int   __gap3;
};

#pragma pack(1)
struct tClothes
{
	//unsigned long   modelCRCs[10]<format = hex>;
	//unsigned long   textureCRCs[18]<format = hex>;
	//short    fat, muscle;
};

#pragma pack(1)
struct tXYZ
{
	RwV3D   pos;
	char xyz_right[3];
    char xyz_top[3];
};

#pragma pack(1)
struct tHeader
{
	char Sig[8];
};

#pragma pack(1)
struct tVehicle
{
	char    index;
	unsigned char     health; /* divided by 4 */
	unsigned char     gasPedal; /* multiplied by 100.0 */
	tXYZ    xyz;
	char      unknown1[2];
	char     unknown2[2]; /* 0045BA03 */
	short      modelID;
	/*28*/  int     unknown; /* CAutomobile.damageManager.field_14 */
	unsigned char     velocity[3];
	unsigned char     steerAngle1;
	char     unknown_flags[9];
	unsigned char     colors[2];
	char      unknown_flag; /* isplayervehicle? 0045B901 */
	/*48*/  char      unknown_flag2; /* CVehicle.field_594 */
	char      __gap2[3];
};

#pragma pack(1)
struct tblock5
{
	/* 5 */
	bool        boolplayerInVehicle;
	char        __gap1[2];
	RwMatrix    camera;
	char       __gap2[8];
	RwV3D       playerPos;
};

#pragma pack(1)
struct tblock6
{
	/* 6 */
	char    currentHour;
	char	 currentMinute;
	char   __gap;
};

#pragma pack(1)
struct tblock7
{
	/* 7 */
	char    unknown_weather; /*save*/
	char    unknown_weather2; /*save*/
	char    __gap;
	float   unknown; /*save*/
};

#pragma pack(1)
struct tblock9
{
	/* 9 */
	char   __gap3[3];
	int   currentTime;
};

#pragma pack(1)
struct tblock2
{
	/* 2, 15 */
	tVehicle vehicle;
	char    unknown2[2]; /* [ecx+640h].f08] */
	char    __gap4[2];
};

#pragma pack(1)
struct tblock17
{
	/* 17 */
	tVehicle vehicle;
	int    unknown[2]; /* 0045E69B */
};

#pragma pack(1)
struct tblock16
{
	/* 16 */
	tVehicle vehicle;
	int    unknown; /* 0045E652 */
};

#pragma pack(1)
struct tblock3
{
	/* 3 - player */
	char   index;
	char    modelID;
	char   pedtype;
	char    __gap5[3];
};

#pragma pack(1)
struct tblock19
{
	/* 19 - PlayerClothes  */
	char    __gap6[3];
	tClothes   clothes;
};

#pragma pack(1)
struct tblock4
{
	/* 4 */
	char index;
	unsigned char   angle;
	char    vehicleIndex;
#pragma pack(1)
	struct  unknownAnimations /* 0045B187 */
	{
		short    walkingAnim;
		char	 walkingAnimAmount;
		char    unknown6[2]; //always the same
		char    __gap1;
		short    unknown5;
		char    unknown2[4];
		short    vehicleAnimType;
		char     vehicleAnimAmount; //0 to 12 max lean forward
		char    unknown3[3]; //always the same
		char    __gap2[2];
	} unknown23;
	tXYZ    xyz;
	short    __gap3;
	short   currentWeapon;
	short    unknown;
	char    unknown1;
	char    unknown2;
	char    __gap7[2];
};

#pragma pack(1)
struct tblock12
{
	/* 12 */
	char    __gap8[3];
	int     unknown1[2];
	char    unknown;
	char    unknown2;
	char    __gap9[2];
};

#pragma pack(1)
struct tblock8
{
	/* 8 end of frame */
	char    __gap10[3];
};

#pragma pack(1)
struct tblock1
{
	tVehicle vehicle;
};

#pragma pack(1)
struct tblock10
{
	char   unknown[27];
};

#pragma pack(1)
struct tblock11
{
	char    unknown[19];
};

#pragma pack(1)
struct tblock18
{
	char    unknown[75];
};