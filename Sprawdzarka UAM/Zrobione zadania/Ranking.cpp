#include<stdio.h>

using namespace std;

int main()
{
	int l_zest, miejsce, ile_osob;
	
	float tab[10001];
	
	scanf("%d",&l_zest);	
	
	while(l_zest--)
	{
		scanf("%d",&ile_osob);
		
				
		for(int i=1; i<=ile_osob; i++)
		{
			miejsce=1;
			scanf("%f",&tab[i]);			
			
			for(int k=1; k<=i; k++)
			{				
				if(tab[i]<tab[k])
				{					
					miejsce++;
				}								
			}			
			printf("%d ",miejsce);
		}
		printf("\n");
					
	}		
	return 0;
}


