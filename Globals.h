#if !defined( GLOBALS_H )
#define GLOBALS_H

#include <iostream>

using namespace std ;

//for coordinate axes
#define HEIGHT 15
#define WIDTH 18
#define DIRECTION_INPUT_LIMIT 6
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
//ENUMs
enum Direction{ no_dir, d_up, d_right, d_down, d_left };
enum SnakePart{ no_part, s_body, s_tail, s_head };
//GLOBAL VARIABLES
extern SnakePart positions[ HEIGHT * WIDTH + 1] ;
extern Direction directions[ HEIGHT * WIDTH + 1] ;
// update interval of snake movement in milliseconds
extern int updateInterval ;
extern int gameStarted ;
extern int gameOver ;

// Function Declarations

int directionChangePossible( Direction from, Direction to) ;

Direction oppositeDirectionOf( Direction dir) ;

void initThings() ;

#endif
