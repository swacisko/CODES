#include<iostream>
using namespace std;

int closest_left(int *diam, int pole);
int closest_right(int *diam, int pole);

int main()
{
	int l_zest, N, M, n, runda, l, r, pole, min;
	int czas[501][501];
	int *diam[501];
	
	cin>>l_zest;
	
	while(l_zest--)
	{
		cin>>N>>M;
		runda=M;
		
		for(int i=1; i<=M; i++)
		{
			cin>>n;
			diam[i]=new int[n+1];
			diam[i][0]=n+1;            // ilosc elementow tablicy diam[i];
			for(int k=1; k<=n; k++)
			{				
				cin>>diam[i][k];
			}
		}	
			for(int i=1; i<M; i++)
			{
				for(int j=1; j<diam[i][0]; j++)
				{
					czas[i][diam[i][j]]=M*N;
				}
			}
		
		for(int i=1; i<diam[M][0]; i++)
		{
			czas[M][diam[M][i]]=0;
		}
		
		while(runda>1)
		{
			for(int i=1; i<diam[runda][0]; i++)
			{
				pole=diam[runda][i];
				l=closest_left(diam[runda-1],pole);
				r=closest_right(diam[runda-1],pole);
												
				if(l!=0)
				{
					if( czas[runda-1][l] > czas[runda][pole] + pole - l )
					{
						czas[runda-1][l] = czas[runda][pole] + pole - l;
					}
				}
				if(r!=0)
				{
					if( czas[runda-1][r] > czas[runda][pole] + r - pole  )
					{
						czas[runda-1][r] = czas[runda][pole] + r - pole;
					}
				}
			}
			runda-=1;			
		} //while
		
		for(int i=1; i<diam[1][0]; i++)
		{
			czas[1][diam[1][i]]+=diam[1][i]-1;
		}
		
		min=M*N;
		
		for(int i=1; i<diam[1][0]; i++)
		{			
			if( czas[1][diam[1][i]] < min )
			{
				min=czas[1][diam[1][i]];			
			}
		}
		
		cout<<min<<endl;
	
	}
	
	
	
	
	
	
	
}
int closest_left(int *diam, int pole)
{
	int i=1, min=0;
	
	while(i<diam[0])
	{		
		if(diam[i] <= pole)
		{
			min=i;
		}
		i++;
	}
	if(min!=0) return diam[min];
	else return 0;
}
int closest_right(int *diam, int pole)
{
	int i=diam[0]-1, min=0;
	
	while(i>0)
	{		
		if(diam[i] >= pole)
		{
			min=i;
		}
		i--;
	}
	if(min!=0) return diam[min];
	else return 0;
	
}


