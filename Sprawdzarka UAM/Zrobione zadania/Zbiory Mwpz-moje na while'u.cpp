#include<iostream>
using namespace std;

int ile_podzbiorow;
void wypisz(int N, int *tab);
void funkcja(int N, int K, int M, void (*wypisz)(int,int*) );

int main()
{
	int l_zest, N,K,M;
	
	cin >> l_zest;
	
	while(l_zest--)
	{
		ile_podzbiorow=0;
		cin>>N>>K>>M;
		
		for(int i=K; i<=N ;i++)
		{
			if(ile_podzbiorow>=M) break;
			else
			{
				funkcja( i, K, M, wypisz );
			}
		}		
		
	}	
	
}

//********************************************************************************

void wypisz(int N, int *tab)
{
	cout<<"["<<N;
	
	for(int i=tab[0]-1; i>=1; i--)
	{
		cout<<","<<tab[i];
	}
	cout<<"]"<<endl;	
}

//*********************************************************************************

void funkcja(int N, int K,int M, void (*wypisz)(int,int*) )
{
	int* tab = new int[K+1];
	tab[0] = K; tab[K]=N;
	int t=0;
	
	for(int i=1; i<=K-1; i++)
	{
		tab[i]=i;
	}
	
	wypisz(N,tab);
	ile_podzbiorow++;
	
	while( tab[1]!=N-K+1 )
	{
		t++;
		if( tab[t] < tab[t+1]-1 )
		{
			if( ile_podzbiorow++ == M ) return;
			tab[t]++;
			t=0;
			wypisz(N,tab);			
		}
		else for(int i=1; i<=t; i++) tab[i]=i;
		
		
	}
	
	
}











