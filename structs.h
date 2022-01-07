#pragma once

typedef float vec3_t[3];

typedef struct
{
	__int32 serverTime; //0x0000 
	char _0x0004[12];
	__int32 isIngame; //0x0010 
	char _0x0014[156];
	__int32 pose; //0x00B0 
	char _0x00B4[80];
	__int32 clientNum; //0x0104 
	char _0x0108[72];
	__int32 health; //0x0150 
	char pad_0x0154[0x38]; //0x0154
	__int32 maxEntities; //0x018C 
	char pad_0x0190[0x68]; //0x0190
	__int32 state; //0x01F8 
	char _0x01FC[224];
	__int32 ammo2; //0x02DC 
	char _0x02E0[12];
	__int32 ammo1; //0x02EC 
	char _0x02F0[100];
	__int32 mag2; //0x0354 
	char _0x0358[8];
	__int32 grenade; //0x0360 
	char _0x0364[8];
	__int32 mag1; //0x036C 
	char _0x0370[8];
	__int32 nades; //0x0378 
}cg_t;

typedef struct
{
	__int32 xp; //0x0000 
	char pad_0x0004[0x4]; //0x0004
	__int32 prestige; //0x0008 
	char pad_0x000C[0x4]; //0x000C
	__int32 score; //0x0010 
	__int32 kills; //0x0014 
	__int32 streaks; //0x0018 
	__int32 deaths; //0x001C 
	char pad_0x0020[0x4]; //0x0020
	__int32 assists; //0x0024 
	__int32 headshots; //0x0028 
	char pad_0x002C[0x18]; //0x002C
	__int32 kdratio; //0x0044 
	__int32 wins; //0x0048 
	__int32 loses; //0x004C 
	__int32 ties; //0x0050 
	__int32 winstreak; //0x0054 
	char N00000D23[1499]; //0x0058 
	char weaponChallenges[284]; //0x0633 
	char perkChallenges[16]; //0x074F 
	char miscChallenges[187]; //0x075F

}stats_t;

typedef struct
{
	int x;
	int y;
	int width; //0x0008  
	int height; //0x000C  
	float fov_x; //0x0010  
	float fov_y; //0x0014  
	vec3_t vieworg; //0x0018
	vec3_t viewaxis[3]; //0x0024  
	char szUnknown1[16200]; //0x0048  
	vec3_t rdViewAngle; //0x3F90

}refdef_t;