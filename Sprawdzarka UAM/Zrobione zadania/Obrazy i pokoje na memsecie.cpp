#include<iostream>
#include<string.h>
using namespace std;


int main()
{
	ios_base::sync_with_stdio(0);
	
	int l_zest,*tab,f1,*dl, rooms,N,*when;
	bool *was, *was_in_turn;
	cin>>l_zest;
	
	while(l_zest--)
	{
		rooms = 0;
		cin>>N;		
		tab = new int[N];
		dl = new int[N];
		was = new bool[N];
		was_in_turn = new bool[N];
		when = new int[N];
		
		for(int i=0; i<N; i++)
		{
			cin>>f1;
			tab[i]=f1-1;
		}
		
		memset( was,0,N );
		memset( dl,0,4*N );
		
		for(int i=0; i<N; i++)
		{
			f1=i;
			if( ! was[i] ) // jezeli jeszcze nie byl w pokoju nr i to zaczynamy dana operacje
			{			
				memset( was_in_turn,0,N ); // zapisujemy, ze w danej turze jeszcze nigdzie nie bylismy
				memset(when,0,4*N); // when[j] oznacza, ze w pokoju j bylismy w when[j]-tym kroku
						
				for(int k=0; k<N; k++)
				{		
					was[f1] = true;	// zapisujemy ze juz byl w pokoju
					was_in_turn[f1] = true;
					f1 = tab[f1];	
												
					if( was[f1] && was_in_turn[f1] ) 
					{
						dl[i] = k+1 - when[f1];
						break;
					}
					else if( was[f1] && ( ! was_in_turn[f1] ) )
					{
						dl[i]=0;
						break;
					}
					else when[f1] = k+1;
							
										
											
				}
			}
		}
		
		for(int i=0; i<N; i++) rooms+=dl[i];
		
		cout<<rooms<<endl;
		
		delete[]when;
		delete[]was_in_turn;
		delete[]was;
		delete[]tab;
		delete[]dl;
		
	}
	
	
	
	
}
