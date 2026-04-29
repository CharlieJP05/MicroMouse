#include "Algorithm.h"
#include "main.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "queue.h"
#include "Structs.h"
int flood[map_w][map_h]; // flood variable stores the floodfill values for the whole map

#define N 0b00000011
#define E 0b00001100
#define S 0b00110000
#define W 0b11000000 // bit masks for each direction selection

uint8_t direction[4] = {N, E, S, W}; // list of all directions for lookup

int dir_lookup[4][2]  = {{0,1},{1,0},{0,-1},{-1,0}}; // lookup of the deltas of directions


void flood_fill_calc(uint8_t map[map_w][map_h], int goal[2]){ // calculates the floodfill
	// initialise flood map to -1 all over
	for(int r = 0; r < map_w; r++){
		for(int c = 0; c < map_h; c++){
			flood[r][c] = -1;
		}
	}

	// set goal points to 0
	flood[3][2] = 0;
	flood[4][2] = 0;
	flood[3][3] = 0;
	flood[4][3] = 0;

	Queue queue; // creates a queue of points to look at
	Queue_init(&queue);

	// append goal positions to queue
	append(&queue, 3, 2);
	append(&queue, 4, 2);
	append(&queue, 3, 3);
	append(&queue, 4, 3);

	while (!isEmpty(&queue)){ // run whilst there are available squares to search

		Position current = pop(&queue); // get current item

		int cx = current.x; // x and y of item
		int cy = current.y;

		int current_val = flood[cx][cy]; // flood value of item
		uint8_t current_walls = map[cx][cy]; // walls around item

		for(int i = 0; i < 4; i++){ // for each direction

			if (!(current_walls & direction[i])){ // if no wall
				int *dir = dir_lookup[i]; // get delta for this dir

				int nx = cx + dir[0]; // get new positions
				int ny = cy + dir[1];

				// bounds check
				if(nx >= 0 && nx < map_w && ny >= 0 && ny < map_h){

					if(flood[nx][ny] == -1){ // set value to 1+ current if its unset
						flood[nx][ny] = current_val + 1;
						append(&queue, nx, ny); // add this spot to
					}
				}
			}
		}
		
		
	}
	
}

Queue getPath(vector pos ){
	Queue path;
	path.append(pos);
	
	for(int i = 0; i < 4; i++){ // for each direction

			if (!(current_walls & direction[i])){ // if no wall
				int *dir = dir_lookup[i]; // get delta for this dir
				if(flood[pos.x][pos.y] > flood[pos.x+dir][pos.y+dir]){
					path.append(vector { pos.x+dir,pos.y+dir});

				}
	
			}
		}
	return path;
	

}


void testing(map){
	//uint8_t map[map_w][map_h];
	int goal[2] = {3,2};

	flood_fill_calc(map, goal);
}


void Calabrate(){}