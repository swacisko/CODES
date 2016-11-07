#include<iostream>

using namespace std;
int find_min_time(int tab[], int N);

int main()
{
	bool tab[101][101];
	int l_zest, czas[101], N, M, miasto1, miasto2, poczatek, time[101]={0}, t;  //poczatek-miasto do ktorego chcemy dojechac
		
	
	cin>>l_zest;
	
	while(l_zest--)
	{
		cin>>N>>M;
		
			for(int i=0; i<101; i++)
		{		
			for(int k=0; k<101; k++)
			{
				tab[i][k]=false;
			}
		}		
		
		for(int i=0; i<101; i++)
		{
			czas[i]=N+1;
		}
		
		for(int i=1 ;i<=M; i++)
		{
			cin>>miasto1>>miasto2;	
			
			tab[miasto1][miasto2] = tab[miasto2][miasto1] = true;		
		}
		cin>>poczatek;
		
		for(int i=1; i<=N; i++)
		{
			if( tab[poczatek][i] == true )
			{
				czas[i]=1;
				time[i]=1;
				tab[i][poczatek]=false;
			}
		}
		czas[poczatek]=N+1;
		
		for(int j=1; j<=N-1; j++)
		{
			t=find_min_time(czas,N);
			for(int i=1; i<=N; i++)
			{
				if( tab[t][i] == true )
				{
					if( czas[i] > time[t]+1 )
					{
						czas[i]=time[t]+1;
						time[i]=czas[i];
					}
					
					tab[i][t]=false;
					tab[t][i]=false;
					
					if(i==1)
					{
						cout<<time[1]<<endl;
						goto koniec;
					}
				}
				
				
			}
			
			czas[t]=N+1;
		}
		
		cout<<"NIE"<<endl;
		
		
		
		
		
	koniec:	;
	}

}
int find_min_time(int tab[], int N)   // zwraca index najmiejszego elementu tablicy
{
	int index=0;
	int min=N+1;
	
	for(int i=1; i<=N; i++)
	{
		if( tab[i] < min )
		{
			min=tab[i];
			index=i;
		}
	}
	return index;
	
	
}







