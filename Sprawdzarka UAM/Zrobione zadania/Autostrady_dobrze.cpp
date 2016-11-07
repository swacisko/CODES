#include<iostream>
using namespace std;

void concomp(int** admat, bool *color, int ind);

int main()
{	
	ios_base::sync_with_stdio(0);
	
	int l_zest, N,M,miasto1,miasto2, ccomp;
	int* miasta[10001]; bool sasiedzi1[10001];
	int pary[2][250001];
	int ile_wsp[10001];
	bool color[10001];
	
	cin>>l_zest;
	
	while(l_zest--)
	{		
		ccomp=0;		
		cin>>N>>M;
		
		for(int i=1; i<=N; i++)
		{
			ile_wsp[i]=1;
			sasiedzi1[i]=false;
			color[i]=false;
		}
		
		for(int i=1; i<=M; i++)
		{
			cin>>pary[0][i]>>pary[1][i];
			ile_wsp[pary[0][i]]++;
			ile_wsp[pary[1][i]]++;
		}
		
		for(int i=1; i<=N; i++)
		{
			miasta[i] = new int[ile_wsp[i]];
			miasta[i][0]=0;
		}
		
		for(int i=1; i<=M; i++)
		{
			miasta[ pary[0][i] ][0]++;
			miasta[ pary[0][i] ][ miasta[ pary[0][i] ][0] ] = pary[1][i];
			
			miasta[ pary[1][i] ][0]++;
			miasta[ pary[1][i] ][ miasta[ pary[1][i] ][0] ] = pary[0][i];			
		}
	
		for(int i=1; i<=N; i++)
		{
			if(color[i]==false)
			{
				ccomp++;
				color[i]=true;
				concomp(miasta,color,i);				
			}
			
		}

		cout<<N-ccomp<<endl;
		
		for(int i=0; i<=N; i++)
		{
			delete[]miasta[i];
			miasta[i]=0;
		}
		
	}
		
	
}

//*********************************************************************************

void concomp(int** admat, bool *color, int ind)
{
	for(int i=1; i<=admat[ind][0]; i++)
	{
		if( color[ admat[ind][i] ]==false )
		{
			color[ admat[ind][i] ] = true; 
			
			concomp(admat,color,admat[ind][i]);
		}		
	}	
}



