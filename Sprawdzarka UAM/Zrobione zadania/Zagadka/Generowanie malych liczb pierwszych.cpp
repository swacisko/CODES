#include<iostream>
#include<fstream>


using namespace std;

int main(){
	
	ofstream str( "Primes.txt" );
	
	str << 2 << ", ";
	
	bool prime;
	for( int i=3; i<5000; i+=2 ){
		prime = true;
		for( int k=2; k*k <= i; k++ ){
			if( i%k == 0 ){
				prime = false;
			//	cout << i << " = " << k << " * " << i/k << endl;
				break;
			}
		}
		
		if( prime ){
			str << i << ", ";
		}
	}
	
	str.close();
	
}
