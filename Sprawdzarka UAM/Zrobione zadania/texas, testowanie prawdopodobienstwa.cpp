#include<iostream>
#include<cstdlib>
#include<time.h>

using namespace std;

int main()
{
	srand( unsigned( time(NULL) ) );
	
	int colour, value;
	
	int testy = 1000;
	
	cout << testy << endl;
	for(int x=1; x<testy; x++)
	{
		for(int i=0; i<7; i++)
		{
			colour = rand()%4;
			
			if( colour == 0 ) cout << "S";
			else if( colour == 1 ) cout << "H";
			else if( colour == 2 ) cout << "D";
			else cout << "C";
			
			value = rand()%13 + 2;
			
			if( value == 14 ) cout << "A ";
			else if( value == 13 ) cout << "K ";
			else if( value == 12 ) cout << "Q ";
			else if( value == 11 ) cout << "J ";
			else cout << value << " ";
		}
		
		cout << endl;
		
		
	}
	
	
	
	
}
