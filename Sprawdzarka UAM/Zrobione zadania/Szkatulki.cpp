#include<iostream>
using namespace std;

int main()
{
	int l_zest, K, N, M, suma_monet, liczba;
	int **szkatulki;
	bool *klucze;
	int *w_szk;
	
	cin>>l_zest;
	
	while(l_zest--)
	{
		suma_monet=0;
		cin>>N;
		
		szkatulki = new int*[N+1];		
		klucze = new bool[N+1];
		w_szk = new int[N+1];
		
		cin>>K;
		for(int i=1; i<=N; i++)
		{
			klucze[i]=false;
		}
		
		for(int i=1; i<=K; i++)
		{
			cin>>liczba;
			klucze[liczba]=true;
		}
		
		for(int i=1; i<=N; i++)
		{
			cin>>w_szk[i];
			cin>>liczba;
			szkatulki[i] = new int[liczba+1];
			szkatulki[i][0] = liczba;
			
			for(int j=1; j<=liczba; j++)
			{
				cin>>szkatulki[i][j];
			}
			
			
		}
		
		for(int i=1; i<=N; i++)
		{
			if(klucze[i])
			{
				suma_monet+=w_szk[i];
				w_szk[i]=0;
				
				for(int j=1; j<=szkatulki[i][0]; j++)
				{
					klucze[szkatulki[i][j]]=true;
				}
				
				szkatulki[i][0]=0;
				
				klucze[i]=false;
				i=0;
			}
			
			
			
		}
		
		
		cout<<suma_monet<<endl;
		
		delete klucze;
		delete w_szk;
	}
	
	
	
	
	
	
}
