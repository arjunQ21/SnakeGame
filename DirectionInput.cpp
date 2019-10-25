#include "Globals.h"
#include "DirectionInput.h"

Direction DirectionInput::last = no_dir ;
int DirectionInput::stopListening = 0 ;
char DirectionInput::pressedKey = 27 ;
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
