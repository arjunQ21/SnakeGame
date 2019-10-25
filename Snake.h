#if !defined( SNAKE_H )
#define SNAKE_H

#include <iostream>
#include "Globals.h"
#include "Point.h"
using namespace std ;

class Snake{
	public:
		int length = 3 ;
		Point headAt, tailAt ;
//		Point activePoints[ HEIGHT * WIDTH + 1] ;
		string  bodyLetter, tailLetter ;
		Direction activeDirection = d_right ;
		Snake(){
			headAt = Point(5, 5) ;
			tailAt = Point(5, 2) ;
			resetParts() ;
			bodyLetter = "*" ;
			tailLetter = "+" ;
//			addPart(Point(5, 2), Direction(d_right), SnakePart(s_tail)) ;
		}
		void removePart( Point at ){
			directions[at.uniIndex] = Direction(no_dir) ;
			positions[at.uniIndex] = SnakePart(no_part) ;
		}
		void addPart( Point At, Direction dir, SnakePart part = s_body ){
			if(At.isInsideBounds()){
				if(!( part == SnakePart(no_part) || dir == Direction(no_dir))){
					positions[ At.uniIndex ] = part ;
					At.setDirection( dir ) ;
				}else{
					cout << "Either direction or part is empty. Cant add this data at " << At.toString("Point") <<".\n" ;
					return ;
				}
//				Graph::setDirection(dir,  At ) ;
				if(part == SnakePart(s_head) ){
					headAt = At ;
				}
				if(part == SnakePart( s_tail )){
					tailAt = At ;
				}
				return ;
			}
			cout << ", so cant add part at this point.\n" ;
		}
		void resetParts(){
			int i ;
			for( i = 1 ; i <= Point::height * Point::width ; i++){
				positions[i] = SnakePart(no_part) ;
			}
		}
		void moveOneStep( Direction dir ){
			if(directionChangePossible(headAt.getDirection(), dir)){
				Point newHeadAt = Point::aheadOf(headAt, dir ) ;
				Point newTailAt = Point::aheadOf( tailAt ) ;
				removePart( tailAt ) ;
				addPart(headAt, dir , s_body ) ;
				addPart(newHeadAt, dir , s_head) ;
				headAt = newHeadAt ;
				tailAt = newTailAt ;
			}else{
				cout << "cant move in this direction.\n";
				//so move in previous direction
				moveOneStep(headAt.getDirection()) ;
			}
		}
		int getLength(){
			int i ;
			Point P = tailAt ;
			for( i = 1 ; i <= HEIGHT * WIDTH ; i++){
				P = Point::aheadOf(P) ;
				if( P == headAt){
					break ;
				}
			}
			return ( i <= HEIGHT * WIDTH ) ? ++i : i ;
		}
		void increaseLength(){
			Direction dir = tailAt.getDirection() ;
			Point newTailAt = Point::aheadOf(tailAt,oppositeDirectionOf(dir) ) ;
			if(newTailAt.isInsideBounds()){
				addPart(tailAt, dir , s_body) ;
				tailAt = Point::aheadOf(tailAt,oppositeDirectionOf(dir) ) ;
				addPart(tailAt, dir , s_tail ) ;
				cout << "\nlength incremented." ;
			}
		}
		int ateItself(){
			static int lastLength = getLength() ;
//			cout << "\n Last len: " << lastLength << ", present len: " << getLength() ;
			if(lastLength > getLength()){
				cout << "\nSnake ate itself." ;
				gameOver = 1 ;
				return 1 ;
			}
			lastLength = getLength() ;
			return 0 ;
		}
};

#endif

