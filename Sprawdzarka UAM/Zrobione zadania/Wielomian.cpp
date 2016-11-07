#include<iostream>

using namespace std;

int pot(int a, int b)
{
	int suma=1;
	for(int i=0; i<b; i++)
	{
		suma*=a;
	}
	return suma;
}

int main()
{
	int n, m, k, R, s_wsp=0, t, tab[11]={0};
	
	cin>>t;
	
	while(t--)
	{
		cin>>n>>k>>m>>R;
		
		for(int k=0; k<=n; k++)
		{
			if(k==0) {  tab[0]=R%m; s_wsp=tab[0]; }
			
			if(k>0)
			{		
				tab[k]=	((R-s_wsp)%(pot(m,k+1)))/pot(m,k) ;	
				s_wsp+=tab[k]*pot(m,k);
								
			}
			
		}
		
		
		for(int k=n; k>=0; k--)
		{
			if(k<n) 
			{
				if(k>0)
				{
				cout<<"+"<<tab[k]<<"x^"<<k;
				}
				else cout<<"+"<<tab[k];
				
			}
			else cout<<tab[k]<<"x^"<<k;
			
		}
		cout<<endl;
		
	}
	
	return 0;
}

