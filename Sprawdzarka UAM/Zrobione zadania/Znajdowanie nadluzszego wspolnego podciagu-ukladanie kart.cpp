#include<iostream>
using namespace std;

void SORT_SCAL(int* tab1, int p, int r);
void SCAL_1(int* tab1,int p, int q, int r);

inline int max(int liczba1, int liczba2)
{
	if( liczba1>liczba2 ) return liczba1;
	else return liczba2;	
}

int main()
{
	int l_zest, N, liczby[1001], posortowane[1001], wynik[1001][1001];
	
	cin>>l_zest;
	
	while(l_zest--)
	{
		cin>>N;
		
		for(int i=1; i<=N; i++)
		{
			cin>>posortowane[i];
			
			liczby[i] = posortowane[i];
		}
		
		SORT_SCAL(posortowane, 1, N);
		
		for(int i=0; i<=N; i++)
		{
			wynik[i][0] = wynik[0][i] = 0;
		}
		
		for(int i=1; i<=N; i++)
		{
			for(int j=1; j<=N; j++)
			{
				if( liczby[i]==posortowane[j] )
				{
					wynik[i][j] = wynik[i-1][j-1] + 1;
				}
				else
				{
					wynik[i][j] = max( wynik[i-1][j], wynik[i][j-1] );
				}
				
			}
		}
		
		cout<<( N-wynik[N][N] )<<endl;		
	}	
}

void SORT_SCAL(int *tab1, int p, int r)
{
	if(p<r)
	{
		int q=(p+r)/2;
		SORT_SCAL(tab1,p,q);
		SORT_SCAL(tab1,q+1,r);
		SCAL_1(tab1,p,q,r);		
	}	
}

void SCAL_1(int* tab1,int p, int q, int r)
{
	int i=p, l=p, j=q+1;
	int* tab2=new int[r+1];
	
	while(i<=q && j<=r)
	{
		if(tab1[i]<=tab1[j])
		{
			tab2[l]=tab1[i];
			i++;
		}
		else
		{
			tab2[l]=tab1[j];
			j++;
		}
		l++;
	}
	
	while(i<=q)
	{
		tab2[l]=tab1[i];
		i++;
		l++;
	}
	while(j<=r)
	{
		tab2[l]=tab1[j];
		j++;
		l++;
	}
	for(i=p; i<=r; i++)
	{
		tab1[i]=tab2[i];
	}
	
	delete[]tab2;
	tab2=0;
	
}

