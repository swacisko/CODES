#include<iostream>
#include<vector>
#include<time.h>
#include<fstream>
#include<cstdlib>
#include<algorithm>
using namespace std;

int main(){
	srand( (unsigned)time(0) );
	
	
	ofstream str( "Iny.txt" );	
	int l_zest = 10;
	
	str << l_zest << endl;
	while(l_zest--){
		
	
	int N = 8, M = 8;	
	str << N << " " << M << endl;	
	for( int i=0; i<N; i++ ){
		for( int k=0; k<M; k++ ){
			str << rand()%10 << " ";
		}
		str << endl;
	}
	
	} // koniec whilea
	str.close();
}
