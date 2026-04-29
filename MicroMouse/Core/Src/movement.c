#include "main.h"
#include "Structs.h"
#include "Queue.h"
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3


void Rotate(Position path[], int length)
{
	int heading = NORTH;

	for (int i = 0; i < length - 1; i++)
	{
		Position current = path[i];
		Position target  = path[i + 1];

		int dx = target.x - current.x;
		int dy = target.y - current.y;

		int desired_heading;

		if (dx == 1 && dy == 0)        desired_heading = EAST;
		else if (dx == -1 && dy == 0)  desired_heading = WEST;
		else if (dx == 0 && dy == 1)   desired_heading = NORTH;
		else if (dx == 0 && dy == -1)  desired_heading = SOUTH;
		else continue; // invalid step

		// rotate to match heading
		int turn = (desired_heading - heading + 4) % 4;

		switch (turn)
		{
			case 0:
				// no turn
				break;

			case 1:
				// turn right
				break;

			case 2:
				// turn 180
				break;

			case 3:
				// turn left
				break;
		}

		heading = desired_heading;
	}
}

void move(){
    
}
