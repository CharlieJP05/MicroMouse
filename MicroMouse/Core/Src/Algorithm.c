#include "Algorithm.h"
#include "main.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "queue.h"

// remember: add new funcs to h, any inputs are needed there too.


#define ABS(x) ((x) < 0 ? -(x) : (x))


int flood[8][6]; // rows then columns this is the full map
int goal[2] = {0,0};

#define N 0b00000001
#define S 0b00000100
#define E 0b00010000
#define W 0b01000000

uint8_t direction[4] = {N, S, E, W};

int dir_lookup[4][2]  = {{0,1},{0,-1},{1,0},{-1,0}};


void flood_fill_calc(uint8_t map[map_w][map_h], int goal[2]){
	// initialise flood map
	for(int r = 0; r < map_w; r++){
		for(int c = 0; c < map_h; c++){
			flood[r][c] = -1;
		}
	}

	// set goal
	flood[goal[0]][goal[1]] = 0;

	Queue queue;
	Queue_init(&queue);

	// append goal position
	append(&queue, goal[0], goal[1]);

	while (!isEmpty(&queue)){

		Position current = pop(&queue);

		int cx = current.x;
		int cy = current.y;

		int current_val = flood[cx][cy];
		uint8_t current_walls = map[cx][cy];

		for(int i = 0; i < 4; i++){

			if (!(current_walls & direction[i])){

				int *dir = dir_lookup[i];

				int nx = cx + dir[0];
				int ny = cy + dir[1];

				// bounds check
				if(nx >= 0 && nx < map_w && ny >= 0 && ny < map_h){

					if(flood[nx][ny] == -1){
						flood[nx][ny] = current_val + 1;
						append(&queue, nx, ny);
					}
				}
			}
		}
	}
}


void testing(){
	//uint8_t map[map_w][map_h];
	uint8_t map[map_w][map_h] = {0};
	int goal[2] = {3,4};

	flood_fill_calc(map, goal);
}
