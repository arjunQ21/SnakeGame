/*
Main File
Snake Game in C++
Written By: Arjun Adhikari
Github Repo Link: https://github.com/arjunq21/SnakeGame
*/

//including custom classes
#include "Globals.h"
#include "Point.h"
#include "Snake.h"
#include "Food.h"
#include "Graph.h"
#include "DirectionInput.h"

//predefined classes
#include <time.h>
#include <cstdlib>
#include <conio.h>
#include <thread>



main(){
	initThings() ;
	// Direction Input Thread
	thread DirectionInputListener( DirectionInput::listenInput );
	Graph G ;
	int score ;
	char playAgain = 'y' ;
	while(playAgain == 'y' || playAgain =='Y'){
		newStartedAt = clock() ;
		G.resetParts() ;
		G.snake.addPart(Point(HEIGHT / 2, 2), d_right, s_tail ) ;
		G.snake.addPart(Point(HEIGHT / 2, 3), d_right, s_head) ;
		score = 0 ;
		G.plotSnake() ;
		while(DirectionInput::pressedKey != 27 ){
			if( clock() % updateInterval == 0){
				G.snake.moveOneStep( DirectionInput::get() ) ;
				G.plotSnake() ;
				if(G.snake.ateItself() || G.snake.headAt.isInBorder()){
					G.showCenteredText("Game Over!!") ;
					showScore(score) ;
					cout << "\nYou died." ;
					cout << "Wanna Play Again? (y/n): " ;
					playAgain = DirectionInput::newPressedKey() ;
					G.snake.reset() ;
					break ;
				}
				// cout << "Food count: " << Food::count ;
				if(G.snakeAteFood()){
					score += G.food.score ;
					cout << "\a" ;
					G.plotSnake() ;
					// cout << "\n\aAte food." ;
				}
				showScore(score) ;			
			}
		}
		// if(!(playAgain == 'y' || playAgain =='Y')){
		// 	break ;
		// }
	}
	DirectionInput::stopListeningForInput() ;
	//joining thread
	if(DirectionInputListener.joinable()){
		DirectionInputListener.join() ;
		// cout << "\nStopped Listening for Direction Input." ;
		cout << "\nStopped Game.\nThanks for checking this game." ;
		cout << "\nPress any key to continue..." ;
		getch() ;
	}
}

