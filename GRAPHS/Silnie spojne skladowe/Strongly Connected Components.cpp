#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<complex>
#include<stack>
#include<list>
#include<set>
#include<bitset>
#include<set>
#include<iterator>
#include<cmath>
#include<queue>
#include<time.h>
#include<string.h>
#include<fstream>
#include<sstream>
#include<algorithm>

using namespace std;

#define REP( x,y ) for( int x=0; x<(y); x++ )
#define FORD( x,y,z ) for( int x=y; x>=(z); x-- )
#define FOR(x,b,e) for( int x = b; x <= (e); ++x )
#define SIZE(v) (int)v.size()
#define ALL(c) c.begin(),c.end()
#define VAR(v,n) __typeof(n) v=(n)
#define FOREACH(i,c) for( VAR(i,c.begin());i!=c.end();++i )
#define PB push_back
#define MP make_pair
#define ST first
#define ND second

int N,M,K,a,b,c,y,t,w,l_zest;
const int INF = 1000000001;
const double EPS = 10e-9;
typedef vector<double> VD;
typedef pair<double,int> PDI;
typedef pair<double, double> PDD;
typedef vector<bool> VB;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef map< PII, bool > MPIIB;
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;


namespace SCC{

	VI PostOrder; // PostOrder[i] - numer post_order i-tego wierzcholka
	VVI V;
	VVI Comps; // Copms[i] - wektor w sklad ktorego wchodza wierzcholki i-tej silnie spojnej skladowej
	VI temp_comp; // wektor tymczasowy, reprezentujacy jedna spojna skladowa podczas jednej serii rekurencji Add_PO_DFS
	
	VB was; // czy juz bylem w danym wierzcholku
	
	void PO_DFS( int num, int & ponum ){ // funkcja wyznaczajaca numery Post_Order
		was[ num ] = true;
		REP( i,SIZE(V[num]) ) if( !was[ V[num][i] ] ) PO_DFS( V[num][i], ponum );
		PostOrder[ num ] = ponum++; // tutaj zapisuje numer PostOrder i zwiekszam ponum. Jest on przesylany przez referencje, 
										//wiec w innych rekurencjach tez bedzie zwiekszony
	}
	
	void Add_PO_DFS( int num ){ // Funkcja dodajaca do tymczasowej silnie spojnej skladowej kolejne weirzcholki
		was[num] = true;
		temp_comp.PB( num );
		REP(i, SIZE(V[num]) ) if( !was[ V[num][i] ] ) Add_PO_DFS( V[num][i] );
	}
	
	VVI transpose( VVI & v ){ // funkcja zwraca graf transponowany
		VVI g( SIZE(v) );
		REP( i,SIZE(v) )	REP( k,SIZE(v[i]) )	g[ v[i][k] ].PB(i);
		return g;
	}
	
	void StrConComp(){
		was = VB(N,0);
		PostOrder = VI(N);
		int ponum = 0;
		REP( i,N ) if( !was[i] ) PO_DFS( i,ponum ); // tutaj wyznaczam dla wszystkich wierzcholkow numery PostOrder
		
		VI sorted( N ); // tablica sorted[i] oznacza numer wierzcholka o numerze post_order rownym i
		REP( i,N ) sorted[ PostOrder[i] ] = i;
		
		V = transpose( V ); // odwracam graf aby wykonac na nim odpowiednie dfsy
		
		was = VB(N,0);
		FORD( i,N-1,0 ){ // zaczynjac od wierzcholka o najwiekszym numerze PostOrder w odwroconym grafie
			temp_comp.clear();
			if( !was[ sorted[i] ] ) Add_PO_DFS( sorted[i] ); // jesli jeszcze wierzcholek o numerze sorted[i] nie nalezy do spojen skladowej to go dodajemy wraz z cala silnie spojna skladowa
			if( SIZE(temp_comp) ) Comps.PB( temp_comp );
		}
		
		V = transpose( V ); // odwracam graf, aby byl w pozycji poczatkowej
	}


}


int main(){
	
	cin >> l_zest;
	while(l_zest--){
		
		cin >> N >> M;
		SCC::V = VVI(N);
		
		REP(i,M){
			cin >> a >> b;
			SCC::V[a-1].PB(b-1);
		}
		
		SCC::StrConComp();
		
		cout << "Oto twoje silnie spojne skladowe:" << endl;
		FOREACH( it,SCC::Comps ){
			FOREACH( itr, (*it) ){
				cout << *itr + 1 << " ";
			}
			cout << endl;
		}
		
	}
	
	
	
	
	
	
	
	
	
	
	
	
}









