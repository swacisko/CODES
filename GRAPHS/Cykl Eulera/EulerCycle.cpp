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

namespace EUL{		
	
	VVI V; // graf
	VI cycle; // wektora zawierajacy cykl eulera do wywolanieu jakiejsc z funkcji EulerCyckle lub DirEulerCycle
	VB was; // czy bylem w danym weirzcholku
	//MPIIB edge_map; // mapa potrzebna do sprawdzenia, czy w grafie ktory nie jest skierowany juz dana krawedzia przechodzilem
	//MPIIB::iterator iter1;
	set<PII> edge_map;
	
	// funkcja tylko do znajdowania cyklu eulera w grafie skierowanym, dziala w czasie O(n+m)
	void DirEulerCycle( int num ){ // UWAGA UWAGA ta funkcja psuje graf, przed wywolaniem stworz kopie zapasowa !! !! !! !! !! !!
		REP( i,V[num].size() ){
			int d = V[num][i];
			V[num].erase( V[num].begin() + i-- ); // jesli usuwam krawedz, to musze zmniejszyc 
			DirEulerCycle( d );		
		}
		cycle.PB( num );
	}
	
	// funkcja do znajdowania cvyklu eulera w dowolnym grafie, dzialajaca w czasie O( (N+M)lgN )
	void EulerCycle( int num ){ // Moze byc uzywane do znajdowania cyklu eulera , nie psuje grafu
		REP( i,SIZE( V[num] ) ){
			if( edge_map.find( MP(num,V[num][i]) ) == edge_map.end() ){
				edge_map.insert(  MP( num,V[num][i] ) );
				edge_map.insert( MP( V[num][i],num )  );
				EulerCycle( V[num][i] );
			}
		}
		cycle.PB( num );
	}

}

int main(){
	
	
	cin >> l_zest;
	while(l_zest--){
		cin >> N >> M;
		EUL::V = VVI(N);
		REP(i,M){
			cin >> a >> b;
			EUL::V[a-1].PB(b-1); // tutaj tworze akurat graf skierowany
			EUL::V[b-1].PB(a-1);
		}
		
		cout << "Oto twoj cykle Eulera dla grafow skierowanych, w czasei liniowym:" << endl;
		VVI g = EUL::V;
		EUL::DirEulerCycle(0);
		reverse( ALL(EUL::cycle) ); // po wykonaniu funkcjio tzeba odwrocic sciezke
		
		FOREACH(it,EUL::cycle) cout << *it + 1 << " ";
		cout << endl;
		
		cout << endl << "A teraz wersja w czasie NlgN ale dla dowolnych grafow:" << endl;
		EUL::V = g;
		EUL::edge_map.clear();
		EUL::cycle.clear();
		EUL::EulerCycle(0);
		reverse( ALL(EUL::cycle) ); // po wykonaniu funkcjio tzeba odwrocic sciezke
		
		FOREACH(it,EUL::cycle) cout << *it + 1 << " ";
		cout << endl;
	}
	
	
	
	
	
	
	
	
	
}








