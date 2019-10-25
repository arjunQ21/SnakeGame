//definition of global variables and functions
#include "Globals.h" 

int updateInterval = 80 ;
int gameStarted = 0 ;

// Global arrays redeclarations
SnakePart positions[ HEIGHT * WIDTH + 1] ;
Direction directions[ HEIGHT * WIDTH + 1] ;


//Global Function Definitions
int directionChangePossible( Direction from, Direction to){
	if(from == Direction(no_dir) || to == Direction(no_dir)){
		return 0 ;
	}
	if(from == d_right && to == d_left ){
		return 0 ;
	}
	if(from == d_left && to == d_right ){
		return 0 ;
	}
	if(from == d_up && to == d_down ){
		return 0 ;
	}
	if(from == d_down && to == d_up ){
		return 0 ;
	}
	return 1 ;	
}

Direction oppositeDirectionOf( Direction dir){
	switch(dir){
		case no_dir:
			cout << "there is no direction opposite of no_dir., returning itself." ;
			return dir ;
		case d_right:
			return d_left ;
		case d_left :
			return d_right ;
		case d_up:
			return d_down ;
		case d_down:
			return d_up ;				
	}
}

