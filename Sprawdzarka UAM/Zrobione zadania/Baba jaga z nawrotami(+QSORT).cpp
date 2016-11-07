#include<iostream>
using namespace std;

int SUMA,ILE;
void quicksort(int* tab, int p, int r);
int podzial(int*tab, int p, int r);
bool solve(int*tab, bool* ktore, int index);


int main()
{
	ios_base::sync_with_stdio(0);
	
	int l_zest,liczba,N, *wartosci, max;
	bool *ktore;
	cin>>l_zest;
	
	while(l_zest--)
	{
		cin>>N;
		wartosci = new int[N+1];
		ktore = new bool[N+1];
		wartosci[0]=N;
		SUMA=0; max=0; ILE=0;
		
		for(int i=1; i<=N; i++)
		{
			 cin>>wartosci[i];
			 SUMA+=wartosci[i];
			 if(wartosci[i] > max) max=wartosci[i];
			 ktore[i]=false;
		}
		
		quicksort(wartosci,1,N);
		
		if(SUMA%2 || max>SUMA/2) cout<<"NIE"<<endl;
		else
		{
			if( solve(wartosci,ktore,1) )
			{
				cout<<ILE<<" ";
				for(int i=1; i<=N; i++)
				{
					if( ktore[i] ) cout<<wartosci[i]<<" ";					
				}
				cout<<endl;
				
				cout<<N-ILE<<" ";
				for(int i=1; i<=N; i++)
				{
					if( !ktore[i] ) cout<<wartosci[i]<<" ";
				}
				cout<<endl;
			}
			else cout<<"NIE"<<endl;			
		}
		
		
		
		
		
		delete[]ktore; ktore=0;
		delete[]wartosci; wartosci=0;
	}
	
	
	
	
}
//*************************************************
bool solve(int*tab, bool* ktore, int index)
{
	static int suma;
	
if(index > 1)
{	
	for(int i=index; i<=tab[0]; i++)
	{
		suma+=tab[i];
		ktore[i]=true;
		ILE++;
		
		if( suma < SUMA/2 )
		{
			if( solve(tab,ktore,i+1) ) return true;			
		}
		else if( suma==SUMA/2 ) return true;
		
		suma-=tab[i];
		ktore[i]=false;
		ILE--;
	}
}
else
{
	suma=0;
	suma+=tab[1];
	ILE=1;
	ktore[1]=true;
	return solve(tab,ktore,2);
	
}
	
	return false;
}
//**********************************************
int podzial(int*tab, int p, int r)
{
	int x=tab[p];
	int i = r+1;
	int pamiec;
	
	for(int j=r; j>=p+1; j--)
	{
		if( tab[j] <= x ) // teraz sortuje sie od najwiekszej do najmniejszej. Aby zamienic kolejnosc wystarczy zmeinic na >=
		{
			i--;
			pamiec=tab[j];
			tab[j] = tab[i];
			tab[i] = pamiec;
		}
	}
	
	pamiec=tab[i-1];
	tab[i-1] = tab[p];
	tab[p] = pamiec;
	return i-1;
	
}
//****************************************************
void quicksort(int* tab, int p, int r)
{
	int q;
	if(p < r)
	{
		q=podzial(tab,p,r);
		quicksort(tab,p,q-1);
		quicksort(tab,q+1,r);
		
	}
	
}


