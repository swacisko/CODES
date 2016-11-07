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
#define WRITE( V ){ FOREACH(it,V) cout << *it << ", "; cout << endl; }
#define WRITE_ALL(V,s) { cout << s << endl;  REP( i,SIZE(V) ){ cout << "i = " << i << endl;  FOREACH(it,V[i]) cout << *it << ", "; cout << endl;     } }
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
typedef map< PII, bool > MPIIB;
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;


VI bipartition; // 2 jesli wierzcholek nalezy do drugiej skladowej, 1 jesli nalezy do pierwszej
VVI V; // wektor, reprezentujacy graf dwudzielny, dla ktorego chcemy znalezc maksymalne skojarzenie
VI matching; // matching[i] - nr wierzcholka, z ktorym jest skojarzony wierzcholek i, lub -1, jesli nie jest wogole skojarzony
bool *was;

// zwraca falsz, jesli dana skladowa spojnosci nie jest dwudzielna, lub true, jesli jest
bool bipartDfs( int num, int part ){
	bipartition[ num ] = part;
	REP(i,SIZE(V[num])){
		if( bipartition[ V[num][i] ] == part ) return false;
		else if( !bipartition[ V[num][i] ] ) if( !bipartDfs( V[num][i], (part%2)+1 ) ) return false;
	}
	return true;
}

// zwraca wartosc logiczna tego, czy graf G jest dwudzielny
bool BiPart(){
	bipartition = VI(SIZE(V),0);
	REP(i,SIZE(V)) if( !bipartition[i] ) if( !bipartDfs( i,1 ) ) return false;
	return true;
}

// funkcja szuka sciezki powiekszajacej zaczynajacej sie w wierzcholku beg
bool findPath( int beg ){
	was[beg] = true;
	if( matching[ beg ] != -1 ) if( !was[ matching[beg] ] ){ // jesli jestem w wierzcholku skojarzonym, dla ktorego wierzcholek skojarzony nie by³ jeszcze odwiedzony, to przechodze do niego		
		 if( findPath( matching[beg] ) ) return true;
		else return false;
	}
	
	REP(i,SIZE(V[beg])){
		if( matching[ V[beg][i] ] == -1 || ( !was[ V[beg][i] ] && findPath( V[beg][i] ) ) ){ // jesli sasiad nie jest skojarzony, to moge od razu go skojarzyc
			matching[beg] = V[beg][i];
			matching[ V[beg][i] ] = beg;
			return true;
		}
		
	/*	if( !was[ V[beg][i] ] ){
			if( findPath( V[beg][i] ) ){
				matching[beg] = V[beg][i];
				matching[ V[beg][i] ] = beg;
				return true;
			}
		}*/
	}
	
	return false;
}


// zwraca 0 jesli graf nie jest dwudzielny, lub zapisuje w matching maksymalne skojarzenie i zwraca ilosc skojarzonych par
int MaxMatch(){
	matching = VI( SIZE(V),-1 );
	if( !BiPart() ) return 0;
	was = new bool[SIZE(V)];
	
	int res = 0;
	REP( i,SIZE(V) ){
		if( matching[i] == -1 ){
			CLEAR(was,SIZE(V));
			if( findPath(i) ) res++;
		}
	}
	
	delete[]was;
	return res;
}


// funkcja do wyznaczania wartosci maksymalnego skojarzenia w dowolnym grafie, jednak nie wyznaczy mi przyporzadkowania, bo zachodzi  floor(  s( V* ) / 2 ) = s( V ), czyli np s(V*) = 5 oraz s(V) = 2, dla cyklu C5
int MaxMatchAnyGraph(){
	VVI G( 2*SIZE(V) );
	REP(i,SIZE(V)){
		REP(k,SIZE(V[i])){
			G[i].PB( SIZE(V) + V[i][k] );
		}
	}
	
	swap( G,V );
	
	return MaxMatch() / 2;
}











int main(){
	
	cin >> l_zest;
	while(l_zest--){
		cin >> N >> M;
		V = VVI(N);
		REP(i,M){
			cin >> a >> b;
			V[a-1].PB(b-1);
			V[b-1].PB(a-1);
		}
		
		int res = 0;
		REP(i,SIZE(V)) if( SIZE(V[i]) == 0 ) res++;
		
		res += MaxMatch();
		
		cout << res << endl;
		
		
	}
	
	
}












