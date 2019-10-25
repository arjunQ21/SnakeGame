#if !defined( GRAPH_H )
#define GRAPH_H

#include <iostream>
#include "Snake.h"
#include "Food.h"
#include "Point.h"
using namespace std ;

class Graph{
	string inputLetters[HEIGHT * WIDTH + 1] ;
	public:

	static int height, width;
	Snake snake;
	Food food ;
	Direction d_resetter ;
	int paddingLeft ;
	string borderH, borderV, default_content, padding, paddingLeftText, resetter ;
		Graph(){
			height = HEIGHT ;
			width = WIDTH ;
			paddingLeft = 25 ;
			borderH = "=" ;
			borderV = "||" ;
			default_content = " " ;
			padding = " " ;
			resetter = "`";
			d_resetter = no_dir ;
			paddingLeftText = getStringWith(paddingLeft, padding) ;
			food = Food::atRandomPoint() ;
			resetInputs() ;
			resetDirections() ;
		}
		void showInputArray(){
			int i ;
			for(i = 1 ; i <= height * width ; i++){
				cout << "\n[" << i << "] => " << getInput(i) ;
			}
		}		
		void show(){
			system("CLS") ;
			cout << endl << endl ;
			int i ;
			for( i = 0 ; i <= height + 1 ; i++ ){
				showLine(i) ;
			}
			resetInputs() ;
		}
		void putRegularly(string str, Point startingPoint ){
			if( ! startingPoint.isValid() ) return ;
			int i, j  ;
			string sub ;
			for( i = startingPoint.uniIndex, j = 0 ; j < str.length() ; i++, j++ ){
				sub = str.at(j) ;
				put(sub, Point(i)) ;
			}
		}
		void put( string str, Point P){
			if(str.length() != 1){
				cout << "Error, can put single letter only.\n" ;
				return ;
			}
			if(str.compare(resetter) == 0){
				cout << "Error, '" << resetter << "' cannot be added in space.\n" ;
				return ;
			}
			if(P.isInsideBounds()){
				setInput(str, P) ;	
				return ;		
			}
			cout << ", so cant put '" << str << "' at that point.\n" ;
		}
		
		void keepFood(){
			if(food.eaten){
				food = Food::atRandomPoint() ;
			}
			string foodStr = "O" ;
			if(Food::count % 5 == 0){
				food.score = 5 ;
			}
			// cout << "food ocunt: " << Food::count << ", food score: " << food.score ;
			if(food.score == 1){
				foodStr = "o" ;
			}else{
				foodStr = "O" ;
			}
			setInput(foodStr, food.at ) ;
			
		}
		
		int snakeAteFood(){
			if(food.at.containsSnake()){
				food.eaten = 1 ;
				snake.increaseLength() ;
				return 1 ;
			}
			return 0 ;
		}
		
		void plotSnake(){
			int i ;
			resetInputs() ;
			keepFood() ;
			Point currentPoint = snake.tailAt ;
			while( 1 ){
				if(!currentPoint.isInsideBounds()){
					show() ;
					break ;
				}
				string inputLetter = "~" ;
				// head may not have direction, but direction is compulsory for all other points
//				if(!(currentPoint == snake.headAt) ){
					if(currentPoint.getDirection() == Direction(no_dir)){
						cout << "No direction data at " << currentPoint.toString("Point", ", so stopping plotting from this point.\n") ;
						break ;
					}
//				}
				if(currentPoint == snake.headAt ){
//					switch ( currentPoint.getDirection() )	{
//						case Direction( d_up ):
//							inputLetter = "^" ;
//							break ;
//						case Direction(d_right):
//							inputLetter = ">" ;
//							break ;
//						case Direction (d_left ):
//							inputLetter = "<" ;
//							break ;
//						case Direction (d_down)	:
//							inputLetter = "+" ;
//							break ;		
//					}
					inputLetter = "@" ;
				}else if(currentPoint == snake.tailAt){
					inputLetter = snake.tailLetter ;
				}else{
					// for body
					inputLetter = snake.bodyLetter ;
				}
				setInput( inputLetter, currentPoint ) ;
				if(currentPoint == snake.headAt){
					show() ;
					break ;
				}
				currentPoint = Point::aheadOf( currentPoint );
			}
			cout << snake.headAt.toString("Head at: ") ;
			cout << endl << "Length: " << snake.getLength() << endl ;
		}
		void showCenteredText( string s){
			int l = s.length() ;
			int startFromLeft = 1 ;
			if(l >= WIDTH ){
				startFromLeft = 1 ;
			}else{
				startFromLeft = (WIDTH -l)/2 + 1 ;
			}
			resetInputs() ;
//			Point putAt( HEIGHT / 2, startFromLeft) ;
			putRegularly(s, Point(HEIGHT / 2 , startFromLeft )) ;
			show() ;
		}
	private:		
		void setInput(string str, Point at){
			if(at.isInsideBounds() && str.length() == 1 ){
				inputLetters[ at.uniIndex ] = str ;
				return ;
			}
			cout << ", so cant set input at this point.\n" ;
		}
		string getInput( Point at){
			if(at.isInsideBounds() ){
				return inputLetters[ at.uniIndex ] ;
			}
			cout << ", so cant get input from this point, returning default resetter.\n" ;
			return resetter ;
		}
		void resetInputs(){
			int i ;
			for( i = 1 ; i <= height * width  ; i++){
				setInput(resetter, Point(i)) ;
			}
		}
		void resetDirections(){
			int i ;
			for( i = 1 ; i <= height * width  ; i++){
				Point(i).setDirection(d_resetter) ;
//				setDirection(d_resetter , Point(i)) ;
			}
		}		
		void showLine(int lineNumber ){
			//paddingLeft
			string lineOut = paddingLeftText ;
			//border
			lineOut.append(borderV) ;
			//top border and bottom border
			if((lineNumber == 0) || (lineNumber == height + 1)) {
				lineOut.append(getStringWith(width * 2, borderH)) ;	
			}else{
			//line specific options
				int i  ;
				for( i = (lineNumber - 1)*width + 1 ; i <= lineNumber*width ; i++){
	//					cout << i << ", " ;
//					string toDisplay = *(inputLetters + i) ;
					if(getInput(i).compare(resetter) == 0){
						lineOut.append(default_content) ;
					}else{
						lineOut.append(getInput(i)) ;
					}
					lineOut.append(" ") ;
				}
			
			}
			//ending border
			lineOut.append(borderV) ;
			//new line at end
			lineOut.append("\n") ;
			cout << lineOut ;
		}
		static string getStringWith(int len, string s){
			int i = 0 ;
			string out ;
			for(i = 0 ; i < len ; i++){
				out.append(s);
			}
			return out ;
		}
};


#endif
