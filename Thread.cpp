#include <thread>
#include <iostream>
#include <time.h>
#include <conio.h>

using namespace std ;

char inputs[20] ;
char lastInput ;
int c = 0 ;

void showInputs() ;

void show( int n, int times = 50){
	for(int i = 0 ; i < times ; i++){
		cout << n ;
	}
}

void readInput(){
	while( c < 20){
		cout << "\nPress any key: " ;
		inputs[ c++ ] = getche() ;
	}
	cout << "\nread input upto 20 chars " ;
}

void showTime(){
	int t = 0 ;
	while(c < 20){
		if(clock()%1000 == 0){
			cout << "\nTime: " << t++ << " secs." ;
			showInputs() ;
		}
	}
}

void showInputs(){
	cout << "\nInputs: [ " ;
	for( int i = 0 ; i < 20 ; i++){
		if(inputs[i] != -1){
			cout << inputs[i] << ", " ;
		}else{
			break ;
		}
	}
	cout << " ]\n" ;
}

main(){
	int i ;
	for( i = 0 ; i < 20 ; i++)
		inputs[i] = -1 ;
	thread t1(readInput ) ;
	showTime() ;
	if(t1.joinable()){
		t1.join() ;
		cout << "\nt1 joined." ;
	}	
}
