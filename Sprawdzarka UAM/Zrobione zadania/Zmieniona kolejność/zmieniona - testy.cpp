#include<iostream>
#include<cstdlib>
#include<time.h>
#include<fstream>

using namespace std;

int main(){
	
	srand( unsigned( time(0) ) );
	ofstream str( "Zmieniona_kolejnosc.txt" );
	
	int N = 5;
	str << N << endl;
	
	bool brAv;
while( N-- ){
	
	int ile_nawiasow = 0;
	int M = 14;
	for( int i=1; i<M; i++ ){
		int r = rand()%4;
		if( i % 2 == 1 ){
			int a = rand()%50;
			
			str << a;
			
			brAv = true;
			if( r%10 == 0 ){
				if( brAv && ile_nawiasow > 0 ){
					str << ")";
					ile_nawiasow--;
				}
				
			
			}
			
		}
		else{
			brAv = false;
			char c;
			switch( r ){
				case 0:{
					c = '+';
					break;
				}
				case 1:{
					c = '-';
					break;
				}
				case 2:{
					c = '*';
					break;
				}
				case 3:{
					int e = rand()%15;
					if( e > 3 ) c = '/';
					else if( e == 0 ) c = '+';
					else if( e == 1 ) c = '*';
					else if( e == 2 ) c = '-';
				}						
				
			}
			
			str << c;
			
			if( r%5 == 0 ){
				if( ile_nawiasow == 0 ){
					str << "(";
					ile_nawiasow++;
				}
				else{
					str << "(";
					ile_nawiasow++;
				}				
			
			}			
		}		
	}
	
	for( int i=0; i<ile_nawiasow; i++ ) str << ")";
	str << endl;
	
	char tab[] = { '-', '+', '*', '/' };
	for( int i=4; i>0; i-- ){
		int r = rand()%i;
		str << tab[r];
		for( int i=r; i<3; i++ ) tab[i] = tab[i+1];	
	}
	
	str << endl;
	
} // koniec whilea
	str.close();
	
}



