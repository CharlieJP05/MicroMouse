#include "Mapping.h"
#include "main.h"
#include "IO.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//include everything needed for mapping.c

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3 //define directions as numbers 	NESW

static int prev_L = 0;
static int prev_R = 0;  

static float x = 9;
static float y = 9;
static float theta = 0; //static variables for robot pose 
typedef struct
{
    float x;
    float y;
}vector;
//create the structure for a vector to store positions

extern uint8_t map[map_w][map_h]; //import map

vector vectorSensUs  = {0.f, 50.f};
vector vectorSensIR  = {1.f, 1.f};  //set vectors for the us and ir sensors

float wallLength = 16.5;
float gap = 1.2;      //set wall length and gap


void Mapping_init()
{

}
void add_wall(int mapX, int mapY, int dir){ //wall adding function
	int nx = mapX;
	int ny = mapY;    //set variables to hold new x and y 

	int OpDir = dir ^ 2;

	// set wall in current cell
	map[mapX][mapY] &= ~(0b11 << (dir*2));
	map[mapX][mapY] |=  (0b11 << (dir*2)); 

	// move to neighbour (corrected for x,y with north positive)
	switch(dir)
	{
	case 0: ny += 1; break; // N
	case 1: nx += 1; break; // E
	case 2: ny -= 1; break; // S
	case 3: nx -= 1; break; // W
	}

	// bounds check
	if(nx < 0 || nx >= map_w || ny < 0 || ny >= map_h){
		return;
	}

	// set wall in neighbour (OPPOSITE direction)
	map[nx][ny] &= ~(0b11 << (OpDir*2));
	map[nx][ny] |=  (0b11 << (OpDir*2));
}


void convertToMap(){ //func
	int mapX = x/map_w;
	int mapY = y/map_h;

	float localX = fmodf(x, 18.0f);
	float localY = fmodf(y, 18.0f);
			
	return;

}


void biggerOne(){

}


void Enc_locate(int new_L, int new_R)
{
	int delta_theta_L = new_L - prev_L;
	int delta_theta_R = new_R - prev_R;

	float dL = 42.0f * ((float)delta_theta_L / 2000.0f) * 2.0f * M_PI;
	float dR = 42.0f * ((float)delta_theta_R / 2000.0f) * 2.0f * M_PI;
	float d = (dL + dR) / 40.0f;
	float dtheta = ((dR - dL) / 80.0f) * (2.0f * M_PI / 13.0f);

	y += d * cos(theta + dtheta / 2.0f);
	x += d * sin(theta + dtheta / 2.0f);
	theta -= dtheta;

	LogXY();

	prev_L = new_L;
	prev_R = new_R;
}

float Mapping_GetX(void)
{
	return x;
}

float Mapping_GetY(void)
{
	return y;
}
void LogXY(void){
	char buf[64];

	int xi = (int)x;
	int yi = (int)y;
	int ti = (int)theta;

	int xf = (int)(x * 100) % 100;
	int yf = (int)(y * 100) % 100;
	int tf = (int)(theta * 100) % 100;

	if (xf < 0) xf = -xf;
	if (yf < 0) yf = -yf;
	if (tf < 0) tf = -tf;

	snprintf(buf, sizeof(buf),
		"x: %d.%02d, y: %d.%02d, t: %d.%02d\r\n",
		xi, xf, yi, yf, ti, tf);

	//Log(buf);
}

vector vecRotate(float x, float y, float theta)
{
	vector vec;

	vec.x = x * cosf(theta) - y * sinf(theta);
	vec.y = x * sinf(theta) + y * cosf(theta);

	return vec;
}

vector CalcLength(float theta, vector distance, vector sensPos)
{
	vector target;
	target.x = sensPos.x + distance.x;
	target.y = sensPos.y + distance.y;

	vector rotated = vecRotate(target.x, target.y, theta);

	vector result;
	result.x = x + rotated.x;
	result.y = y + rotated.y;

	return result;
}

void locateWall()
{
	float distance = US_Read();

	vector dis = {0.f, distance};
	dis = CalcLength(theta, dis, vectorSensUs);

	int xDiv = dis.x / 18.f;
	int yDiv = dis.y / 18.f;

	float xMod = fmodf(dis.x, 18.f);
	float yMod = fmodf(dis.y, 18.f);

	if (yMod > xMod)
	{
		add_wall(xDiv, yDiv, SOUTH);
	}
	else
	{
		add_wall(xDiv, yDiv, EAST);
	}
}

// possible functions:

// get all distances
// ???

// notes: US sensor accurtate up to 60 but maybe max it at 50?. any more and disregard. below 3 it goes back up so? idk
