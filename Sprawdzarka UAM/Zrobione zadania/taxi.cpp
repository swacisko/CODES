/*
#include<stdio.h>
#include<iostream>

int main()
{
	int wart(int);
	int D,i,k,max=0, maximum[50],l,liczba[50];


	int wspx[40001]={0};

	int wspy[40001]={0};

	scanf("%d",&D);

	for(i=0; i<D; i++)
	{
		max=0;

		scanf("%d",&liczba[i]);
		
			for(k=1; k<=liczba[i]; k++)
			{
				scanf("%d %d",&wspx[k],&wspy[k]);
			}

		for(l=1; l<=liczba[i]; l++)
		{
			for(k=l+1; k<=liczba[i]; k++)
			{
				if( max < wart( wspx[l]-wspx[k] ) +  wart( wspy[l]-wspy[k] ) )
				{
					max = wart( wspx[l]-wspx[k] ) +  wart( wspy[l]-wspy[k] );
				}
				
			}
			
		}
		
		maximum[i]=max;
	}
	
	for(i=0; i<D; i++)
	{
		printf("%d\n",maximum[i]);

	}
	

}
int wart(int liczba)
{
	if(liczba<0) return (-liczba);
	else return liczba;

}
*/