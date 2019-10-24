#if !defined( DIRECTION_INPUT_H )
#define DIRECTION_INPUT_H

#include "Globals.h"
#include <iostream>
#include <thread>
#include <conio.h>

using namespace std ;

class DirectionInput{
		static Direction inputStack[ DIRECTION_INPUT_LIMIT ] ;
		static Direction map( char c){
			switch( c ){
				case KEY_UP:
					return d_up ;
				case KEY_DOWN:
					return d_down ;
				case KEY_LEFT:
					return d_left ;
				case KEY_RIGHT:
					return d_right ;
				default:
					return no_dir ;	
			}
		}
		static string mapToWords( Direction dir){
			switch( dir ){
				case d_up:
					return "UP" ;
				case d_down:
					return "DOWN" ;
				case d_left:
					return "LEFT" ;
				case d_right:
					return "RIGHT" ;
				case no_dir:
					return "NO DIR" ;
				default:
					return "NONE" ;					
			}
		}
	public:
		static void listenInput(){
			cout << "Listening for input." ;
			while(stopListening != 1){
				cout << "\nEnter Direction: " ;
				pressedKey = getch();
				if(pressedKey != 27){
					processKeyPressed() ;
				}else{
					break ;
				}
			}
		}
		static Direction input, last ;
		static char pressedKey ;
		static int stopListening ;
		static Direction get(){
			if(inputStack[0] == Direction(no_dir)){
				return last ;
			}else{
				return (last = inputStack[0]) ;
			}
			popFirstFromStack() ;
		}
		static void init(){
			stopListening = 0 ;
			input = d_right ;
			last = d_right ;
			for(int i = 0 ; i < DIRECTION_INPUT_LIMIT ; i++){
				inputStack[i] = no_dir ;
			}
			inputStack[0] = d_right ;

		}
		static void stopListeningForInput(){
			stopListening = 1 ;
			cout << "\nPress any key to stop listening for direction input." ;
		}
		static void listen(){
			thread inputListener( listenInput ) ;
			if(inputListener.joinable()){
				inputListener.join() ;
				cout << "\nStopped Listening for direction input." ;
			}
		}
		static void processKeyPressed( ){
			Direction pressedDirection = map( pressedKey ) ;
			if(pressedDirection == Direction(no_dir)){
				cout << "\ninvalid direction input '" << pressedKey << "' .\n";		
			}else{
				pushToStack( pressedDirection ) ;
				cout << "\nDirection read from keyboard." ;
			}
			showStack() ;
		}
		static int filledUpto(){
			int i ;
			for( i = 0 ; i < DIRECTION_INPUT_LIMIT ; i++){
				if(inputStack[i] == Direction(no_dir)){
					break ;
				}
			}
			return i - 1 ;
		}
		static int emptyRoomsInStack(){
			return DIRECTION_INPUT_LIMIT - 1 - filledUpto() ;
		}
		static void pushToStack( Direction dir ){
			if(emptyRoomsInStack() > 0){
				inputStack[ filledUpto() + 1 ] = dir ;
				cout << "\nDirection " << mapToWords(dir) << " pushed to stack." ;
			}else{
				cout << "\nStack Full Error. Cannot add more than " << DIRECTION_INPUT_LIMIT << " inputs in stack." ;
			}
		}
		static void popFirstFromStack(){
			for( int i = 0 ; i < DIRECTION_INPUT_LIMIT - 1 ; i++){
				inputStack[ i ] = inputStack[ i + 1] ;
			}
			inputStack[ DIRECTION_INPUT_LIMIT - 1] = no_dir ;
			cout << "\nPopped First from stack." ;
		}
		static void showStack(){
			// just for now
			// system("CLS") ;
			cout << "\nDirection Input Stack: \n" ;
			for( int i = 0 ; i < DIRECTION_INPUT_LIMIT ; i++){
				cout << "\n\t[ " << i << " ] => " << inputStack[i] <<endl ;
			}
			cout << "\nFilled Upto Index: " << filledUpto() ;
			cout << "\nEmpty Rooms in Stack: " << emptyRoomsInStack() ;
		}
};


#endif
