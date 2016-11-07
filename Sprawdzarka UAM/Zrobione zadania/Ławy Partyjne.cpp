#include<iostream>
using namespace std;


int main()
{
	int l_rzed, ile_w_rzed[1001]={0}, ile_grup, a, b, suma;
	
	cin>>l_rzed;
	
	for(int i=1; i<=l_rzed; i++)
	{
		cin>>ile_w_rzed[i];		
			
	}
	
	cin>>ile_grup;
	
	for(int i=0; i<ile_grup; i++)
	{
		suma=0;
		cin>>a>>b;
		
		for(int k=a; k<=b; k++)
		{
			
			suma+=ile_w_rzed[k];
			
		}
		cout<<suma;
	}
	
	
	
	
	
	
	

}
