#include<stdio.h>
#include<iostream>
#include<iomanip>
using namespace std;

void SCAL_1(long long *tab1,long long p, long long q, long long r);
void SORT_SCAL(long long *tab1, long long p, long long r);

int main()
{	
	long long D,W,H,L, tab[30002]={}, k, i,j;

	double wys_wody=0, i1,L1;
	
	cin>>D;
	
	while(D--)
	{
		cin>>W>>H>>L;
		
		for(i=1; i<=W; ++i)
		{
			cin>>tab[i];
		}
		SORT_SCAL(tab,1,W);
		
		tab[W+1]=H;
		
		for(i=1; i<=W; ++i)
		{
			if( ( k=tab[i+1]-tab[i] )  )
			{
				if(L>=i*k)
				{
					L-=(i*k);
					wys_wody=(double)(tab[i+1]);
					if(tab[i+1]==H)					
					{
						wys_wody = (double)(H);
						break;
					}					
				}
				else
				{
					
					i1=(double)(i);
					L1=(double)(L);
					wys_wody = (L1/i1) + (double)(tab[i]);
					if(wys_wody>H)
					{
						wys_wody = (double)(H);
					}
					break;
				}
				
			}
			
			
		}		
		printf("%.5f \n",wys_wody);
	}
	
	
	
}

void SORT_SCAL(long long* tab1, long long p, long long r)
{
	if(p<r)
	{
		long long q=(p+r)/2;
		SORT_SCAL(tab1,p,q);
		SORT_SCAL(tab1,q+1,r);
		SCAL_1(tab1,p,q,r);		
	}	
}

void SCAL_1(long long* tab1,long long p, long long q, long long r)
{
	long long i=p, l=p, j=q+1;
	long long* tab2 = new long long[r+1];
	
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
	
}



