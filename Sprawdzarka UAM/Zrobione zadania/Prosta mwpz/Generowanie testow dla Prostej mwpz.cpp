#include<iostream>
#include<time.h>
#include<cstdlib>
#include<fstream>

using namespace std;


int main(){
	
	srand( unsigned( time(0) ) );
	ofstream str( "Prosta_iny.txt" );
	
	int x,y;
	bool tab[20000];
	
	
	int l_zest = 50;
	str << l_zest << endl;
	int T = 10000;
	
	while( l_zest-- ){
		
		for( int i=0; i<T; i++ ) tab[i] = false;
		
		int d = 10000;
		str << d << endl;
		
		for( int i=0; i<d; i++ ){
			x = rand() % T - T/2;
			while(  tab[ y = rand() % T] == true );
			tab[y] = true;
			str << x << " " << y - T/2 << " ";
		}
		str << endl;
	}
	
	str.close();
	
}
