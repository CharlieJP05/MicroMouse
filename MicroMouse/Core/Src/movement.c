#include "main.h"
#include "Structs.h"
#include "Algorithm.h"
#include "queue.h"
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

int Currentheading = 0;



int turn_move(Queue path){
	int NewHeading;

    Position CurrentPos = pop(&path);
    Position NextPos = peek(&path);

    //This is east
    if(CurrentPos.x < NextPos.x){
    	NewHeading = EAST;

    }
    if(CurrentPos.x > NextPos.x){
    	NewHeading = WEST;

    }
    if(CurrentPos.y< NextPos.y){
    	NewHeading = NORTH;

    }
    if(CurrentPos.y > NextPos.y){
    	NewHeading = SOUTH;

    }

    int diff = NewHeading - CurrentHeading;

       // Wrap values to range -3 to 3
    if(diff > 2){
           diff -= 4;
       }
    if(diff < -2){
           diff += 4;
       }

       // Degrees to turn
    int degrees = diff * 90;

       // Update heading
    CurrentHeading = NewHeading;

    return degrees;

}

