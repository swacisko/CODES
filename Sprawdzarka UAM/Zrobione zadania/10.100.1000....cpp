#include<stdio.h>


int main()
{

	int N, max=0,jed=0;

	scanf("%d",&N);

	int *tab=new int[N];

	for(int i=0; i<N; i++)
	{
		scanf("%d",&tab[i]);
		if(max<tab[i])
		{
			 max=tab[i];
		}
	}
	bool *jedynki=new bool[max];

	for(int i=0; i<max; i++)
	{
		jedynki[i]=false;
	}

	jedynki[0]=true;

	for(int i=1; jed+i<max; i++)
	{
		jed+=i;
		jedynki[jed]=true;
	}

	for(int i=0; i<N; i++)
	{
		if(jedynki[tab[i]-1])
		{
			printf("1 ");
		}
		else printf("0 ");

	}
	
}

