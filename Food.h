#if !defined( FOOD_H )
#define FOOD_H

#include <iostream>
#include "Point.h"
using namespace std ;

class Food{
	public:
		static int count ;
		int score ;
		int eaten ;
		Point at ;
		Food(){
			
		}
		Food(Point atPoint){
			if(atPoint.isInsideBounds()){				
				at = atPoint;
			}else{
				cout << "so, food may not be at suitable point." ;
				at = -- atPoint.uniIndex;
			}
				score = 1 ;
				count ++ ;
				eaten = 0 ;
		}
		void setScore( int c){
			if(c <= 5 ){
				score = c ;
			}
		}
//		static Food atRandomPoint( ){
//			int random = rand() % ( HEIGHT * WIDTH ) + 1 ;
//			Point p = random ;
//			if(p.containsSnake()){
//				return Food::atRandomPoint() ;
//			}else{
//				return(Food(p)) ;
//			}
//		}
		static Food atRandomPoint(){
			int inactiveSnakeParts[ HEIGHT * WIDTH + 1] ; 
			int i, count = 0, randIndex;
			for(i = 1 ;i <= HEIGHT * WIDTH ; i++){
				if(Point(i).containsSnake()){
//					inactiveSnakeParts[ i ] = -1 ;
					continue ;
				}else{
					inactiveSnakeParts[ ++count ] = i ;
//					count ++ ;
				}
			}
			if(count == 0){
				cout << "You Won, Congrats." ;
				exit(0) ;
//				return Food(Point(1)) ;
			}else{
				randIndex = inactiveSnakeParts[ rand() % ( count ) + 1 ] ;
				return Food(Point(randIndex)) ;
			}
			
		}
//		static Point 
};

#endif
