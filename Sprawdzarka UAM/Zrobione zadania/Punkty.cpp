#include<iostream>
#include<vector>
using namespace std;

const double infinity = 10000000;

template<class typ>
void zamien( typ& a, typ& b )
{
	typ c = a;
	a = b;
	b = c;	
}

template< class typ >
int podzial( typ tab, int p, int r )
{
	int i = p-1;
	for(int j=p; j<r; j++)
	{
		if( tab[j] > tab[r] )
		{
			i++;
			zamien( tab[j], tab[i] );
		}
	}
	
	zamien( tab[i+1], tab[r] );
	return i+1;	
}

template< class typ >
void quicksort( typ tab, int p, int r )
{
	if( p < r )
	{
		int q = podzial( tab,p,r );
		quicksort( tab,p,q-1 );
		quicksort( tab,q+1,r );
	}	
}

int main()
{
	int l_zest,N;
	double pkt_max, nietrywialne;
	int L;
	double f1,f2;
	int **tab;
	double *kat;
	int index = 0;
	
	cin>>l_zest;
	
	while( l_zest-- )
	{
		nietrywialne = 0;
		pkt_max = 2;
		cin>>N;
		kat = new double[N];
		tab = new int*[N];
		for(int i=0; i<N; i++) tab[i] = new int[2];
		
		for(int i=0; i<N; i++)
		{
			cin>>tab[i][0]>>tab[i][1];
		}
		
		for(int i=0; i<N; i++)
		{
			index = 0;
			for(int k=0; k<N; k++)
			{
				if( i!=k )
				{
					if( tab[i][0]==tab[k][0] )
					{
						kat[index] = infinity;
					}
					else
					{
						kat[index] = ( (double)( tab[i][1] - tab[k][1] ) / (double)( tab[i][0] - tab[k][0] )  );
					}
					index++;
				}
			}
			
			kat[N-1] = -infinity;
			quicksort( kat,0,N-1 );
			
		/*	cout<<"Sprawdzam stan posortowanej tablicy:"<<endl;
			for(int i=0; i<N-1; i++) cout<<kat[i]<<" ";
			cout<<endl; */
			
			index = 0; // teraz index bedzie sluzyl do czego innego niz przed petla
			L = 2;
			
			while( index < N-1  )
			{
				if( kat[index] == kat[index+1] )
				{
					L++;
				}
				else
				{
					if( L>=3 )
					{
						nietrywialne += (double) 1/L;
					}
					if( L > pkt_max ) pkt_max = L;
					
					L=2;
				}
				
				index++;
			}			
		}
		
		cout<<N<<" "<<nietrywialne<<" "<<pkt_max<<endl;
		
		for(int i=0; i<N; i++) delete tab[i];
		delete[]tab;
		delete[]kat;
	}

	
	
	
	
	
}


















