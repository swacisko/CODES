#include<iostream>
using namespace std;


int main()
{
	int l_zest;
	int a1,b1,c1,a2,b2,c2;
	
	cin >> l_zest;
	
	while( l_zest-- )
	{
		cin >> a1 >> b1 >> c1 >> a2 >> b2 >> c2;
		
		cout << "TAK";
		if( a1 >= a2 )
		{
			if( b1 >= b2 )
			{
				cout << " W1" << endl;
			}
			else if( c1 >= c2 )
			{
				cout << " A1 A2 W1" << endl;
			}
			else
			{
				cout << " B1 B2 W2" << endl;
			}
		}
		else if( a2 > a1 )
		{
			if( b2 >= b1 )
			{
				cout << " W2" << endl;
			}
			else if( c2 >= c1 )
			{
				cout << " A1 A2 W2" << endl;
			}
			else
			{
				cout << " B1 B2 W1" << endl;
			}
		}	
	}
}


