#include<iostream>
using namespace std;
#include<stdio.h>


int znajdz_droge(bool *diam, int pole, int runda, int M, int N );

int main()
{
	int l_zest, N, M,n, liczba, l_krok;
	bool diam[502][502];
	
	int czas[501][501];
	
	cin>>l_zest;
	
	while(l_zest--)
	{
		scanf("%d %d",&N,&M);
		
		for(int i=1; i<=M; i++)
		{
			scanf("%d",&n);
			for(int k=1; k<=n; k++)
			{
				scanf("%d",&liczba);
				diam[i][liczba]=true;
			}
		}
		
		cout<<znajdz_droge( diam, 1, 1, M, N);
		
		
		
		
		
		for(int i=1; i<=M; i++)
		{
			for(int k=0; k<=501;k++)
			{
				diam[i][k]=false;
			}
		}
	}
	
	
	
	
}

int znajdz_droge(bool diam[][502], int pole, int runda, int M, int N )
{
	if(runda==M)
	{
		int i=pole, j=pole;
		while(i>=1 && diam[runda][i]==false) i--;
		while( j<=N && diam[runda][j]==false) j++;
				
		if(i>=1 && j<=N)
		{
			if( pole-i > j-pole)
			{				
				return (j-pole);
			}
			else
			{				
				  return (pole-i);
			}
		}
		if(i>=1)
		{
			return (pole-i);
		}
		else
		{
			return (j-pole);
		}
	
	}

	if( diam[runda+1][pole]==true  )
	{
		return znajdz_droge(diam,pole,runda+1,M,N);
	}
	else
	{
		int i=pole, j=pole, liczba1, liczba2;
		while(i>=1 && diam[runda][i]==false) i--;
		while( j<=N && diam[runda][j]==false) j++;
				
		if(i>=1 && j<=N)
		{
			liczba1=znajdz_droge(diam,pole-i,runda+1,M,N);
			liczba2=znajdz_droge(diam,j-pole,runda+1,M,N);
			
			
			if( liczba1+ pole-i > liczba2 + j-pole)
			{				
				return liczba2 + j - pole;
			}
			else
			{
				 return liczba1 + pole - i;
			}
		}
		if(i>=1)
		{
			return znajdz_droge(diam,pole-i,runda+1,M,N);
		}
		else
		{
			return znajdz_droge(diam,j-pole,runda+1,M,N);
		}
		
		
	}
	
	
}




