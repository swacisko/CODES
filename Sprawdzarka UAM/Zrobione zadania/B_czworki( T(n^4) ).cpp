#include<iostream>
#include<stdio.h>
using namespace std;

int main()
{
	short l_zest, N, liczba, ile=0, M,a,b;
	bool tab[201][201];
	cin>>l_zest;
	
	while(l_zest--)
	{
		scanf("%d %d",&N,&M);
		
		for(int i=1; i<=N; i++)
		{
			for(int k=1; i<=N; k++)
			{
				tab[i][k]=false;
			}
		}
		
		for(int j=1; j<=M; j++)
		{
			scanf("%d %d",&a, &b);
			tab[a][b]=true
		}
		
		
		ile=0;
		
		for(int i=1; i<=N; i++)
		{
			for(int j=i+1; j<=N; j++)
			{
				if(tab[i][j])
				{
					for(int k=i+1; k<=N; k++)
					{
						if(tab[j][k])
						{
							for(int l=j+1; l<=N; l++)
							{
								if(tab[k][l])
								{
									for(int t=i+1; t<=N; t++)
									{
										if( tab[l][t] && tab[t][i] )
										{
											ile++;
										}										
									}						
								}							
							}
						}
					}
				}
			}
		}
		
		
		
		cout<<ile<<"\n";
		
		
		
	}	
	
}

/*

if(tab[k][l] && tab[l][i])
								{
									ile++;
								}
								
								*/
