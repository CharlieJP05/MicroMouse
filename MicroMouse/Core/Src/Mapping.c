#include "Mapping.h"
#include "main.h"
#include "IO.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
// remember: add new funcs to h, any inputs are needed there too.


static int prev_L = 0;
static int prev_R = 0;

static float x = 0;
static float y = 0;
static float theta = 0;

extern uint8_t map[map_w][map_h];




void Mapping_init()
{

}

void add_wall(int mapX, int mapY, int dir){
	int nx = mapX;
	int ny = mapY;

	int OpDir = dir^2;

	map[mapX][mapY] &= ~(0b11 << dir*2);
	map[mapX][mapY]|= (1 << dir* 2);

	switch(dir)
	{
	case 0:
		nx+= 1;
		return;
	case 1:
		ny += 1;
		break;
	case 2:
		nx -= 1;
		break;
	case 3:
		ny -= 1;
		break;
	default:
		break;
	}

	if(nx < 0 || nx >map_w-1 || ny < 0|| ny > map_h-1){return;} //TODO change from thing -1 to proper


	map[nx][ny] &= ~(0b11 << dir*2);
	map[nx][ny]   |= (1 << dir* 2);

}


void convertToMap(){
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

	float d = (dL + dR) / 2.0f;
	float dtheta = ((dR - dL) / 80.0f) * (2.0f * M_PI / 13.0f);

	x += d * cos(theta + dtheta / 2.0f);
	y += d * sin(theta + dtheta / 2.0f);
	theta += dtheta;

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



// possible functions:

// get all distances
// ???

// notes: US sensor accurtate up to 60 but maybe max it at 50?. any more and disregard. below 3 it goes back up so? idk
