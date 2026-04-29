#ifndef MAPPING_H
#define MAPPING_H
#include <Structs.h>
#include "main.h"
#include "Sensors.h"

void Mapping_init(void);
void Enc_locate(int new_L, int new_R);
float Mapping_GetX(void);
float Mapping_GetY(void);
void LogXY(void);
void add_wall(int mapX, int mapY, int dir);
#endif // MAPPING_H
