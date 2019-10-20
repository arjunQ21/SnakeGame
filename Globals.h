#if !defined( GLOBALS_H )
#define GLOBALS_H

#include <iostream>
#include <time.h>
#include <cstdlib>
#include <conio.h>

using namespace std ;

//for coordinate axes
#define HEIGHT 10
#define WIDTH 15
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
extern int updateInterval ;

// Function Declarations

int directionChangePossible( Direction from, Direction to) ;

Direction oppositeDirectionOf( Direction dir) ;

#endif
