#include "main.h"
#include "Structs.h"
#include "Algorithm.h"
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3


int getDirFromMove(int dx, int dy) {

    if (dx == 0 && dy == 1)  return 0; // N
    if (dx == 1 && dy == 0)  return 1; // E
    if (dx == 0 && dy == -1) return 2; // S
    if (dx == -1 && dy == 0) return 3; // W

    return -1;
}
Queue getRotations(Queue path, int start_facing) {

    Queue rotations;
    Queue_init(&rotations);

    if (isEmpty(&path)) return rotations;

    Position prev = pop(&path);
    int facing = start_facing;

    while (!isEmpty(&path)) {

        Position next = pop(&path);

        int dx = next.x - prev.x;
        int dy = next.y - prev.y;

        int target = getDirFromMove(dx, dy);

        // ignore invalid moves
        if (target == -1) {
            prev = next;
            continue;
        }

        int diff = (target - facing + 4) % 4;

        int angle = 0;

        if (diff == 0) {
            angle = 0;          // straight
        }
        else if (diff == 1) {
            angle = 90;         // turn right
        }
        else if (diff == 2) {
            angle = 180;        // turn around
        }
        else if (diff == 3) {
            angle = -90;        // turn left
        }

        append(&rotations, angle);

        facing = target;
        prev = next;
    }

    return rotations;
}

void spin(int degree){
    //turn by angle 
}

void move(){
    
}