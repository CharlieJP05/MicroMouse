#include "Algorithm.h"
#include "main.h"
#include <string.h>

// remember: add new funcs to h, any inputs are needed there too.


#define ABS(x) ((x) < 0 ? -(x) : (x))

void init(void) // add things it should do when robot starts here, aka map setup
{

}

void get_map(void) // outputs your map variable
{

}

void add_wall(void) // called from elsewhere, adds a wall at a location to your map variable
{

}

void remove_wall(void) // called from elsewhere, removes a wall at a location to your map variable
{

}

void recalculate(void) // calculate the best path, output a list of moves : N N N E W W W S or smt 
{

}

// for (int i= 0 ; i < 9;i++){
// 	for (int j= 0 ; j < 7;j++){
// 		maze[j][i] = 0;
// 	}
// }
// for (int i= 0 ; i < 10;i++){
// 	for (int j= 0 ; j < 8;j++){
// 		walls[j][i] = 0;
// 	}
// }
// // set goal end points
// for (int i= 0 ; i < 8;i++){
// 	for (int j= 0 ; j < 9;j++){
// 	}
// }

// // Initialise maze
// for (int r = 0; r < 6; r++)
//     for (int c = 0; c < 8; c++)
//         maze[r][c] = 0;
// // Initialise walls
// for (int r = 0; r < 7; r++)
//     for (int c = 0; c < 9; c++)
//         walls[r][c] = 0;
// // Set maze values by distance from 2x2 goal (x=4-5, y=3-4)
// for (int r = 0; r < 6; r++) {
//     for (int c = 0; c < 8; c++) {
//         // Distance to nearest edge of goal rectangle
//         int dx = 0, dy = 0;
//         if      (c < 4) dx = 4 - c;  // left of goal
//         else if (c > 5) dx = c - 5;  // right of goal
//         if      (r < 3) dy = 3 - r;  // above goal
//         else if (r > 4) dy = r - 4;  // below goal
//         maze[r][c] = (uint8_t)(dx + dy);
//     }
// }