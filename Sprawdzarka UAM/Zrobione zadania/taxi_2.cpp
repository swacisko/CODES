#include<stdio.h>


int main()
{
	int maximum[50],max=0, min=2000000, wspxmax=0, wspxmin=0, wspymax=0, wspymin=0, D,i,k,N,x=0,y=0;
	int wart(int liczba);

	scanf("%d",&D);

	for(i=0; i<D; i++)
	{
		scanf("%d",&N);

		max=0; min=2000000; wspxmax=0; wspxmin=1000000; wspymax=0; wspymin=1000000;

		for(k=0; k<N; k++)
		{
			scanf("%d %d",&x,&y);

			if(max<x+y)
			{
				max=x+y;
				wspxmax=x;
				wspymax=y;
			}
			if(min>x+y)
			{
				min=x+y;
				wspxmin=x;
				wspymin=y;
			}

		}

		maximum[i]=( wart(wspxmax-wspxmin) + wart(wspymax-wspymin) );

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

//        UWAGA!! Liczone jest tylko po przekatnej wzgledem y=x, ale nie jest liczone po pzekatnej y=-x +k 