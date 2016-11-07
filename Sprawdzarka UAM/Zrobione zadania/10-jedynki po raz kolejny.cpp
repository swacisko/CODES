#include<stdio.h>


int main()
{

	int N, liczba;

	scanf("%d",&N);

	while(N--)
	{
		scanf("%d",&liczba);
		
		for(int i=0; i*(i+1)/2 <= liczba-1; i++)
		{
			if((i*(i+1)/2 == liczba-1))
			{
				printf("1 ");
			}
			else if( (i+1)*(i+2)/2 > liczba-1)
			{
				printf("0 ");
			}
			
			
		}
		
		
		
		
	}
	
}

