#include<iostream>
#include<string>
using namespace std;

const int sek = 24*60*60;

int main()
{
	string *tab;
	int l_zest,N,t,T, ile_ciastek,M;
	
	cin>>l_zest;
	
	while( l_zest-- )
	{
		ile_ciastek = 0;
		cin>>N>>M;
		
		for(int i=0; i<N; i++)
		{
			cin>>t;
			ile_ciastek += sek / t;
		}
		
		if( ile_ciastek%M == 0 )
		{
			cout<<ile_ciastek / M << endl;
		}
		else
		{
			cout << ile_ciastek / M + 1 << endl;  
		}
		
		
	}

		
}

