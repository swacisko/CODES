#include<iostream>
#include<vector>
using namespace std;

/*void display( vector<int>T )
{
	for(int i=0; i<T.size();i++)
	{
		cout<<T[i]<<" ";
	}
	cout<<endl;
}*/

int main()
{
	ios_base::sync_with_stdio(0);
	
	int l_zest,N, how_many_left, party, color, tab[3],k, first, party1, party2; // tab[1] i tab[2] oznacza odpowiednio ilosc osob w pierwszej partii i w drugiej
	vector<int>T; vector<int>C;
	
	cin>>l_zest;
	
	while(l_zest--)
	{
		cin>>N;
		tab[1] = tab[2] = 0; k=0; how_many_left = 2*N;
		
		cin>>party;
		color = party;
		tab[party]++;
		first = party; // zaznaczam do ktorej partii nalezy pierwsza osoba
		
		for( int i=1; i<2*N; i++ )
		{
			cin>>party;
			tab[party]++;
			if( party != color )
			{
				T.push_back( tab[color] );
				C.push_back( tab[color] );
				color = party;				
				tab[party] = 1;
			}			
		}
		T.push_back( tab[color] );
		C.push_back( tab[color] );
		
		
		/*for(int i=0; i<T.size(); i++)
		{
			cout<<T[i]<<" ";
		}*/
		
	//	display(T);
		color = 1; // niezaleznie od tego, czy pierwszy jest z partii 1 czy 2 to nadajemy mu kolor 1 w celu ulatwienia sprawy, da sie wtedy badac parzystosc
		int t = T.size(); 
		k=-1; // zeby po pierwszej petli na while'u zaczynalo sie od 0
		while( how_many_left > 2 )
		{
			k = (k+1) % t;
			if( T[k]!=0 && color != k%2 )
			{
				T[k]--;
				how_many_left--;
				color = k%2;
			}
			
			//cout<<"k = "<<k<<"\t";; display(T);
		
		}		
		
		for(int i=0; i<t-1; i++)
		{
			C[i+1]+=C[i];  
		}
		
		for(int i=0; i<t; i++)
		{
			if( T[i]!=0 && first==1 )
			{
				if( i%2 == 0 ) party1 = C[i];
				else party2 = C[i];
			}
			else if( T[i]!=0 )
			{
				if( i%2 == 0 ) party2 = C[i];
				else party1= C[i];
			}
		}
		
		cout<<party1<<" "<<party2<<endl;
		
		T.clear();
		C.clear();
	}
	
	

}

