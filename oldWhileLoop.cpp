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