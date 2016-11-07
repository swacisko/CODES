#include<iostream>
//#include<string.h>
using namespace std;
 
int N,M;
 
int haszowce[10001][2]; // haszowce[i][0] - nr debu, haszowce[i][1]nr buku wybranego przez i tego haszowca
bool na_ktorym_drzewie[10001]; // oznacza, na ktorym drzewie siedzi haszowiecc nr i - wartosc 0 lub 1- index tablicy-dab lub buk
bool czy_juz_byl[10001];
int drzewa[10001]; // drzewa[i]-nr haszowca, ktory siedzi na danym drzewie
 
bool sciezka( int poczatek, int haszowiec )
{
    if( drzewa[poczatek]==0 )
        {
                drzewa[poczatek] = haszowiec;
                na_ktorym_drzewie[haszowiec] = !na_ktorym_drzewie[haszowiec];
                return true;            
        }
        else if( czy_juz_byl[poczatek]==true ) return false;
        else
        { 
                czy_juz_byl[poczatek] = true;
                if( sciezka( haszowce[ drzewa[poczatek] ][ !  na_ktorym_drzewie[ drzewa[poczatek] ] ], drzewa[poczatek]  ) )
                {
                        drzewa[poczatek] = haszowiec;
                        na_ktorym_drzewie[haszowiec] = ! na_ktorym_drzewie[haszowiec];
                        return true;            
                }
        }
        return false;   
        
}
 
bool ulokuj( int dab, int buk, int haszowiec )
{       
        if( drzewa[dab]==0 )
        {
                drzewa[dab] = haszowiec;
                na_ktorym_drzewie[haszowiec] = 0;
                return true;
        }
        else if( drzewa[buk]==0 )
        {
                drzewa[buk] = haszowiec;
                na_ktorym_drzewie[haszowiec] = 1;
                return true;
        }
        else 
        {
                for(int i=0; i<2*N; i++) czy_juz_byl[i]=false; // przy kazdym lokowaniu haszowca, zeruje tablice dla danej sciezki
                if( sciezka( dab, haszowiec ) )
                {
                        drzewa[dab] = haszowiec;
                        na_ktorym_drzewie[haszowiec] = 0;
                        return true;
                }               
                else 
                {
                        for(int i=0; i<2*N; i++) czy_juz_byl[i]=false; // przy kazdym lokowaniu haszowca, zeruje tablice dla danej sciezki
                        if( sciezka( buk, haszowiec ) )
                        {
                                drzewa[buk] = haszowiec;
                                na_ktorym_drzewie[haszowiec] = 1;
                                return true;
                        }
                }
        }
        
        return false;
}
 
 
int main()
{
        ios_base::sync_with_stdio(0);
        int l_zest,f1,f2,dab,buk; // N-liczba drzew kazdeu gatunku, M-liczba haszowcow
        bool czy_sie_da;
        cin>>l_zest;
        
        
        while( l_zest-- )
        {
                czy_sie_da = true;
                cin>>N>>M;
                for(int i=0; i<2*N; i++) drzewa[i]=0;
                for(int i=0; i<=M; i++) na_ktorym_drzewie[i] = 0;
                for(int i=1; i<=M; i++)
                {
                        cin>>dab>>buk;
                        if( czy_sie_da )
                        {
                        	haszowce[i][0] = dab;
                       		 haszowce[i][1] = buk;
                       	 	if( ! ulokuj( dab,buk,i  ) )
                        	{
                       	         czy_sie_da = false;
                       		}
						}
                }
                
                if( czy_sie_da == true )
                {
                        cout<<1<<" ";
                        for(int i=1; i<=M; i++)
                        {
                                cout<<haszowce[i][ na_ktorym_drzewie[ i ] ]<<" ";
                        }
                        cout<<endl;
                }
                else cout<<0<<endl;
                
                
                
                
        }
        
        
        
        
}
