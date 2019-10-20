#if !defined( POINT_H )
#define POINT_H

#include <iostream>
#include <string>
using namespace std ;

class Point{
		void setUniIndex(){
			uniIndex = (lineNo - 1)*width + fromLeft  ;
		}
		void setCoords(){
			fromLeft = ( uniIndex % width == 0 ) ? width : uniIndex % width ;
			lineNo = ( uniIndex - fromLeft ) / width + 1 ;
		}
	public:
		int lineNo, fromLeft, uniIndex ;
		static int height, width ;
//		Direction direction ;
		Point(){
			lineNo = -1 ;
			fromLeft = -1 ;	
			uniIndex = -1 ;	
//			direction = no_dir ;
//			isValid() ;
		}
		Point(int line, int left ){
			lineNo = line ;
			fromLeft = left ;
			uniIndex = (lineNo - 1)*width + fromLeft  ;
			isValid() ;
		}
		Point(int uni_index ){
			uniIndex = uni_index ;
			fromLeft = ( uniIndex % width == 0 ) ? width : uniIndex % width ;
			lineNo = ( uniIndex - fromLeft ) / width + 1 ;
			isValid() ;
		}
		static void showDirectionArray(){
			int i ;
			for(i = 1 ; i <= height * width ; i++){
				cout << "\n[" << i << "] => " << Point(i).getDirection() ;
			}
		}	
		static void resetDirections(){
			int i ;
			for(i = 1 ; i <= height * width ; i++){
				directions[ i ] = Direction(no_dir) ;
			}			
		}	
		Direction getDirection( ){
			if(isInsideBounds()){
				return directions[ uniIndex ] ;
			}
			cout << ", so returning no_dir at this point.\n" ;
			return Direction( no_dir ) ;
		}
		void setDirection( Direction dir ){
			if( isInsideBounds()){
				directions[ uniIndex ] = dir ;
				return ;
			}
			cout << ", so setting no_dir at this point.\n" ;
			directions[uniIndex] = Direction(no_dir) ;			
		}		
		static Point above( Point a){
			if(a.isInsideBounds()){
				return Point( a.lineNo - 1, a.fromLeft) ;
			}
			cout << ", so cant find any point above. Returning itself, i.e" << a.toString() ;
			return a;
		}
		static Point below( Point a){
			if(a.isInsideBounds()){
				return Point( a.lineNo + 1, a.fromLeft) ;
			}
			cout << ", so cant find any point below. Returning itself, i.e" << a.toString() ;
			return a;
		}
		static Point atRightOf( Point a){
			if(a.isInsideBounds()){
				return Point( a.lineNo , a.fromLeft + 1) ;
			}
			cout << ", so cant find any point at right. Returning itself, i.e" << a.toString() ;
			return a;
		}
		static Point atLeftOf( Point a){
			if(a.isInsideBounds()){
				return Point( a.lineNo , a.fromLeft - 1 ) ;
			}
			cout << ", so cant find any point at left. Returning itself, i.e" << a.toString() ;
			return a;
		}
//		static Point aheadByDirection( Point a, Direction dir){
//			if(dir != no_dir ){
//				switch( dir ){
//					case Direction(d_right):
//						return Point::atRightOf( a ) ;
//						break ;
//					case Direction(d_left):
//						return Point::atLeftOf( a ) ;
//						break ;
//					case Direction(d_up):
//						return Point::above( a ) ;
//						break ;
//					case Direction(d_down):
//						return Point::below( a ) ;
//						break ;
//					default:
//						cout << "Cant find any point ahead of " << a.toString("", ", so returning itself.\n") ;
//						return a ;				
//				}			
//			}else{
//				cout << "Cant find any point ahead of " << a.toString("", ", since no_dir is passed as direction. so returning itself.\n") ;
//				return a ;
//			}
//		}
		static Point aheadOf( Point a, Direction dir = no_dir){
			if(dir == no_dir ) dir = a.getDirection() ;
 			if(a.isValidPart()){
				switch( dir ){
					case Direction(d_right):
						return Point::atRightOf( a ) ;
						break ;
					case Direction(d_left):
						return Point::atLeftOf( a ) ;
						break ;
					case Direction(d_up):
						return Point::above( a ) ;
						break ;
					case Direction(d_down):
						return Point::below( a ) ;
						break ;
					default:
						cout << "Cant find any point ahead of " << a.toString("", ", so returning itself.\n") ;
						return a ;				
				}
			}
			cout << ", So cant find any point ahead of " << a.toString("", ", so returning itself.\n") ;
			return a ;
		}
		int hasValidDirection(){
			if(getDirection() == Direction(no_dir)){
				cout << "Invalid Part at " << toString() << ", because there is no direction data at this point.\n" ;
				return 0 ;
			}
			return 1 ;			
		}
		int hasValidPart(){
			if(positions[ uniIndex ] == SnakePart(no_part)){
				cout << "Invalid Part at " << toString() << ", because there is no snakePart data at this point.\n" ;
				return 0 ;
			}	
			return 1 ;		
		}
		int isValidPart(){
			if(hasValidPart() && hasValidDirection() && isInsideBounds()){
				return 1 ;
			}
			return 0 ;
		}
		static SnakePart getSnakePartAt( Point p){
			if(p.isInsideBounds()){
				return positions[ p.uniIndex ] ;
			}
			//for error
			cout << ", so cant get snake part and returning no_part." ;
			return SnakePart(no_part );
		}				
		int isInBorder(){
			if(lineNo >= 0 && lineNo <= height + 1  && fromLeft >= 0 && fromLeft <= width + 1 ){
				if(lineNo == 0 || lineNo == height + 1  || fromLeft == 0 || fromLeft == width + 1 ){
					return 1 ;
				}
				return 0 ;
			}else{
				cout << "Invalid Point ( " << lineNo << ", " << fromLeft  << ") for border touch check." ;
				return 0 ;
			}			
		}	
		int containsSnake(){
			if(isInsideBounds()){
				int i ;
				for( i = 1 ; i <= HEIGHT * WIDTH ; i++){
					if(positions[ uniIndex ] != SnakePart(no_part)){
//						cout << positions[uniIndex] ;
						return 1 ;
					}
				}
				if( i == HEIGHT * WIDTH + 1){
					return 0 ;
				}
			}
			cout << ", so cant check if this point contains snake." ;
			return 0 ;
		}

//		int isValidSnakePart(){
//			if(isValid()){
//				int uniIndex = Graph::coordsToIndex(lineNo, fromLeft) ;
////				Point 
//				SnakePart part = positions[uniIndex] ;
//				Point atRight = Point::atRightOf( this ) , atLeft = Point::atLeftOf( this ) , above = Point::above( this ), below = Point::below( this ) ;
//				int bodyAtRight = getSnakePartByPoint(atRight) == SnakePart(s_body) ;
//				int bodyAtLeft = getSnakePartByPoint(atLeft) == SnakePart(s_body) ;
//				if(part == SnakePart(no_part)){
//					return 0 ;
//				}
//				if(part == SnakePart(s_tail) || part == SnakePart(s_head)){
//					if(		getSnakePartByPoint(atRight) == SnakePart(s_body) 
//						||  getSnakePartByPoint(atLeft) == SnakePart(s_body) 
//						||  getSnakePartByPoint(above) == SnakePart(s_body) 
//						||  getSnakePartByPoint(below) == SnakePart(s_body) 
//					){
//						return 1 ;
//					}
//					return 0 ;
//				}
//				if(part == SnakePart(s_body)){
//					
//				}
//			}
//		}	
		void show(){
			cout << " ( " << lineNo << ", " << fromLeft << " ) ";
		}
		string toString(string pre = " ", string post = " "){
			string str = "" ;
			str = str + pre + "( " + to_string(lineNo) + ", " + to_string(fromLeft) + " ) => [ " + to_string(uniIndex) + " ]" + post ;
			return str ;
		}
		// Point (0, WIDTH + 1 ) is Valid
		int isValid(){
			if(lineNo >= 0 && lineNo <= height + 1 && fromLeft >= 0 && fromLeft <= width + 1 ){
				return 1 ;
			}
			cout << toString("Point", " is not valid.") ;
			return 0 ;
		}
		// Point (0, WIDTH + 1 ) is not inside bounds
		int isInsideBounds(){
			if(lineNo > 0 && lineNo <= height && fromLeft > 0 && fromLeft <= width ){
				return 1 ;
			}
			cout << "Point " << toString() << " is not within bounds (" << height << ", " << width << " )." ;
			return 0 ;			
		}	
		operator == ( Point a){
			return uniIndex == a.uniIndex ;
		}	
		
};

#endif

