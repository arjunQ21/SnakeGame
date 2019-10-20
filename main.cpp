/*
Main File
Snake Game in C++
Written By: Arjun Adhikari
Github Repo Link: https://github.com/arjunq21/SnakeGame
*/
#include "Globals.h"
#include "Point.h"
#include "Snake.h"
#include "Food.h"
#include "Graph.h"
#include "DirectionInput.h"


main(){
	srand(clock()) ;
	Graph G ;
	G.snake.addPart(Point(2, 2), d_right, s_tail ) ;
	G.snake.addPart(Point(2, 3), d_right, s_head) ;
//	G.snake.addPart(Point(2, 4), d_down) ;
//	G.snake.addPart(Point(3, 4), d_down) ;
//	G.snake.addPart(Point(4, 4), d_down) ;
//	G.snake.addPart(Point(5, 4), d_right) ;
//	G.snake.addPart(Point(5, 5), d_down) ;
//	G.snake.addPart(Point(6, 5), d_down) ;
//	G.snake.addPart(Point(7, 5), d_right) ;
//	G.snake.addPart(Point(7, 6), d_right) ;
//	G.snake.addPart(Point(7, 7), d_right) ;
//	G.snake.addPart(Point(7, 8), d_right , s_head) ;
//	G.snake.addPart(Point(5, 6), d_right , s_head) ;
	cout << "Use arrow keys to move the snake.\n" ;
	cout << "Press any key to start game,\n 'esc' to end game at any moment." ;
	char input ;
	int i = 0, score = 0 ;
	input = getch() ;
	if(input == 27){
		exit(0) ;
	}
	G.plotSnake() ;
	while( (input = getch() ) != 27 ){
//		if(clock() % 1000 == 0){
//			cout << "inside timer.\n";
			switch(input){
				case KEY_UP:
					G.snake.moveOneStep( Direction(d_up)) ;
					G.plotSnake() ;
					break ;
				case KEY_DOWN:
					G.snake.moveOneStep( Direction(d_down)) ;
					G.plotSnake() ;
					break ;
				case KEY_LEFT:
					G.snake.moveOneStep( Direction(d_left)) ;
					G.plotSnake() ;
					break ;
				case KEY_RIGHT:
					G.snake.moveOneStep( Direction(d_right)) ;
					G.plotSnake() ;
					break ;	
				default:
					cout << "invalid input '" << input << "' .\n";			
			}
			if(G.snake.ateItself() || G.snake.headAt.isInBorder()){
//				cout << "\n\nYou died." ;
				G.showCenteredText("Game Over!!") ;
				break ;
			}
			cout << "Food count: " << Food::count ;
			if(G.snakeAteFood()){
				score += G.food.score ;
				G.plotSnake() ;
				cout << "\n\aAte food." ;
			}
			cout << "\n\t\tScore: " << score ;
	}
}

