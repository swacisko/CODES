
#include<stdio.h>
#include<iostream>

using namespace std;
extern int potega(int, int);
int main()
{
	int N, max=0;
	cin>>N;

	
	int *liczby=new int[N];
	bool *wyjscie=new bool[N];

	

	for(int i=0; i<N; i++)
	{
		cin>>liczby[i];
		if(max<liczby[i]) max=liczby[i];
	}
	for(int i=0; i<N; i++)
	{
		wyjscie[i]=false;
	}

	for(int k=0; 1 + k*(k+1)/2 <=max; k++)
	{
		for(int i=0; i<N; i++)
		{
			if(k>=500 && ((2*liczby[i]-1)%k)==0 && ((2*liczby[i]-1)%(k+1))==0 )
			{
				wyjscie[i]=true;
			}
			else if(liczby[i]== 1+ k*(k+1)/2) 
			{
				wyjscie[i]=true;
			}
		}

	}
		
	for(int i=0; i<N; i++)
	{
		
		cout<<wyjscie[i]<<" ";
	}
	

}
int potega(int podstawa, int wykladnik)
{
	int c=podstawa;
	int b=1;

	while(!(wykladnik==0))
	{
		if(wykladnik%2==0)
		{
			c=c*c;
			wykladnik/=2;
		}
		else 
		{
			b=b*c;
			wykladnik-=1;
		}	
		
	}
	return b;


}
