#include<iostream>
using namespace std;


int main()
{
	ios_base::sync_with_stdio(0);
	
	int l_zest,N, *sheets, changes, ones, zeroes;
	cin>>l_zest;
	
	while(l_zest--)
	{
		cin>>N;
		changes = ones = zeroes = 0;
		
		sheets = new int[N+1];
		
		for(int i=1; i<=N; i++)
		{
			cin>>sheets[i];
		}
		
		for(int i=1; i<N; i++)
		{
			if( sheets[i]==1 ) ones++;
			else zeroes++;
			
			if( sheets[i]!=sheets[i+1] ) changes++;
			if( changes > 1 ) break;
		}
		if( sheets[N]==1 ) ones++;
		else zeroes++;
		
		if( changes > 1 )
		{
			cout<<"NIGDY"<<endl;
			continue;
		}
		else
		{
			if( changes == 0 && sheets[1]==0 )
			{
				cout<< 0 <<endl;
				continue;
			}
			else if( changes == 0 && sheets[1]==1 )
			{
				cout<< 1 <<endl;
				continue;
			}
			else if( ones > 1 && zeroes > 1 )
			{
				 cout<<"NIGDY"<<endl;
				 continue;
			}
			else if( N==2 )
			{
				if( sheets[1]==0 )
				{
					cout<< 1 <<endl;
					continue;
				}
				else
				{
					cout<< 2 <<endl;
					continue;
				}
			}
			else // jezeli N>=3 i jest tylko jedna zmiana i ktorychs z jedynek lub zer jest dokaldnie 1
			{
				if( sheets[1]==0 && sheets[2]==0 )
				{
					cout<<"NIGDY"<<endl;
					continue;
				}
				else if( sheets[1]==0 && sheets[2]==1 )
				{
					cout<< 1 <<endl;
					continue;
				}
				else if( sheets[1]==1 && sheets[2]==0 )
				{
					cout<< 2 <<endl;
					continue;
				}
				else
				{
					cout<<"NIGDY"<<endl;
					continue;
				}
			}
			
			
		}
		
		
		
		
		
		delete[]sheets;
		sheets = 0;
	}
	
	
	
}
