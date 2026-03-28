#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <stdint.h>

void init(void); // add things it should do when robot starts here, aka map setup
void get_map(void); // outputs your map variable
void add_wall(void); // called from elsewhere, adds a wall at a location to your map variable
void remove_wall(void); // called from elsewhere, removes a wall at a location to your map variable
void recalculate(void); // calculate the best path, output a list of moves : N N N E W W W S or smt 


#endif // ALGORITHM_H