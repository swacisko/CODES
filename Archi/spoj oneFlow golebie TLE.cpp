#include<stdio.h>
#include<iostream>
#include<vector>
//#include<string>
//#include<map>
//#include<complex>
//#include<stack>
//#include<list>
//#include<bitset>
//#include<set>
//#include<iterator>
#include<cmath>
//#include<queue>
//#include<time.h>
#include<string.h>
//#include<fstream>
//#include<sstream>
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
#define WRITE( V ){ FOREACH(it,V) cout << *it << ", "; cout << endl; }
#define WRITE_ALL(V,s,t) { cout << s << endl;  REP( i,SIZE(V) ){ cout  << i+1 << " ---- ";  FOREACH(it,V[i]) cout << *it+t << ", "; cout << endl;     } }
#define WRP(p) p.ST << " " << p.ND
#define CLEAR( dst,quant ) memset( dst,0, (quant)*sizeof( __typeof(*dst) ) );
#define WAR if( show_help )
#define ENDL(x) REP(crow,(x)) cout << endl;

const bool show_help = 1;
const int INF = 1000000001;
int N,M,K,a,b,c,y,t,w,l_zest;
const long double EPS = 1e-11;
typedef vector<double> VD;
typedef pair<double,int> PDI;
typedef pair<double, double> PDD;
typedef vector<bool> VB;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;

const int ILE = 10001;
#define GROS N+M+2

VI V[ILE];
int layer[ ILE ];
bool was[ ILE ];

// BFS wyznaczajacy w tablicy layer nuer warstwy do ktorej nalezy dany wierzcholek
// zaczynam bfs'a z poczatku
// zwraca true, jesli doszedlem do end, lub false, jesli sie nie da
bool layerBFS( int beg, int end ){
	CLEAR( layer,ILE )
//	REP(i,SIZE(V)) layer[i] = 0;
	
//	cout << "layerBFS" << "  beg = " << beg << "   end = " << end << endl;
	VI neigh(1,beg);
	REP(i,SIZE(neigh)){
	//	cout << "neigh[i] = " << neigh[i] << endl;
		if( layer[ end ] != 0 && layer[ neigh[i] ] == layer[end] ) return true;
		REP(k,SIZE( V[neigh[i]] )){
			if( layer[  V[neigh[i]][k]  ] == 0/* && V[neigh[i]][k] != beg*/ ){
				neigh.PB( V[neigh[i]][k] );
				layer[ V[neigh[i]][k] ] = layer[ neigh[i] ] + 1;
			}
		}
	}
	
	
	return layer[end] != 0;
}

// dfs do findPath
bool fpdfs( int num ){
	was[num] = true;
	if( num == GROS-1 ) return true;
	REP(i,SIZE( V[num] )){
		if( !was[ V[num][i] ] )  if( layer[ V[num][i] ] == layer[num]+1 )  if( fpdfs( V[num][i] ) ){ // jesli znalazlem sciezke do ujscia
			V[ V[num][i] ].PB(num);
		//	V[num].erase( V[num].begin()+i ); // zmieniam krawedz na przeciwna
			swap( V[num][i], V[num][ SIZE(V[num])-1 ] );
			V[num].pop_back();
			return true;
		}
	}
	return false;
}

// dfs, ktory znajduje ilosc sciezek w danym grafie wartswowym
// lay to numer wartswy, w ktorej sie aktualnie znajduje
inline int findPath(){
	CLEAR( was, ILE );
//	cout << endl << "findPath" << endl;
	int ile =0;
	while( fpdfs( GROS-2 ) ) ile++;
	return ile;
}

// przeplyw dla krawedzi jednostkowych
int oneFlow(){
	int ile = 0;
	while( layerBFS( GROS-2, GROS-1  ) ){ // dopoki moge znalezc graf warstwowy
		ile += findPath();
	/*	cout << endl << endl;
		REP(i,SIZE(V)){
			cout << i << "   ";
			REP(k,SIZE(V[i])) cout << V[i][k] << " ";
			cout << endl;
		}
		REP(i,SIZE(V)) cout << "layer["<<i<<"] = " << layer[i] << endl;
		cout << "oneFlow" << endl;*/
	}
	return ile;
}


int match(){
	V[GROS-2] = VI(N);
	REP(i,N) V[ GROS-2 ][i] = i; // dodaje zrodlo
	FOR(i,N,N+M-1 ) V[i].PB( GROS-1 ); // dodaje ujscie
	
	return oneFlow(); // zwracam maksymalna warotsc przeplywu
	
}







int main(){
	
	int ile;
	scanf("%d %d",&N,&M);
	
	REP(i,N){
		scanf("%d",&ile);
		V[i] = VI(ile);
		REP(k,ile){
			scanf("%d",&a);
			V[i][k] = N+a-1;
		}
	}
	
/*	REP(i,SIZE(V)){
		cout << i << "   ";
		REP(k,SIZE(V[i])) cout << V[i][k] << " ";
		cout << endl;
	}*/
	
	printf( "%d\n", match() );
	
}












