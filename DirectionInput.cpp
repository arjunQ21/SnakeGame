#include "Globals.h"
#include "DirectionInput.h"
// #include <time.h>
// #include <thread>
// #include <conio.h>

Direction DirectionInput::input = d_right ;
Direction DirectionInput::last = d_right ;
int DirectionInput::stopListening = 0 ;
char DirectionInput::pressedKey = 0 ;
Direction DirectionInput::inputStack[ DIRECTION_INPUT_LIMIT ] ;
// int c = 0;
// void showTime(){
// 	int t = 0 ;
// 	while(c < 20){
// 		if(clock()%1000 == 0){
// 			cout << "\nTime: " << t++ << " secs." ;
// 			// showInputs() ;
// 		}
// 	}
// }

// main(){
// 	thread inputListener( DirectionInput::listenInput ) ;
// 	cout << "hi" ;
// 	showTime() ;
// 	if(inputListener.joinable()){
// 		inputListener.join() ;
// 		cout << "\nStopped Listening for direction input." ;
// 	}
// }
