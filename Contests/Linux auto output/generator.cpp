#include<iostream>
#include<time.h>
#include<ctime>
#include<algorithm>

using namespace std;


int main(){
	srand(unsigned(time(0)));
	
	int k = 10;
	while( k-- ) cout << rand() % 10  << " ";
	cout << endl;
	
	return 0;
}
