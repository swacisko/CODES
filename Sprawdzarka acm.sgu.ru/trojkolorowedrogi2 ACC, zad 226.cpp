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
#define WRITE_ALL(V,s,t) { cout << s << endl;  REP( i,SIZE(V) ){ cout  << i+1 << " ---- ";  FOREACH(it,V[i]) cout << *it+t << ", "; cout << endl;     } }
#define WRP(p) p.ST << " " << p.ND
#define CLEAR( dst,quant ) memset( dst,0, (quant)*sizeof( __typeof(*dst) ) );
#define WAR if( show_help )
#define ENDL(x) REP(crow,(x)) cout << endl;

const bool show_help = 0;
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

VVI V; // struktura grafu
VVI W; // W[i][k] to kolor drogi laczacej wierzcholek   i   z wierzcholkiem   V[i][k]

int *dist[3]; // dist[i][n] oznacza dlugosc najkrotszej drogi z wierzcholka 0 do wierzcholka n, konczacej sie krawedzia koloru i   !!!
int *totaldist; // totaldist[n] oznacza minimalny dystans od wierzcholka 0 do n, czyli jest rowny       minimum po i z dist[i][n]

// strukturka potrzebna do przechowywania wierzcholkow
struct my_s{
	my_s( int n, int d, int c ) : num(n), dist(d), col(c){}
	int num; // numer wierzcholka
	int dist; // odleglosc wierzcholka o numerze num od wierzcholka 0, przy czym wejscie do tego wierzcholka nastapilo krawedza koloru col
	int col;
//	bool operator<( const my_s & oth ) const{ // to jest zupelnie niepotrzebn
//		return dist < oth.dist;
//	}
};


// algorytm z zadania
// dla kazdego wierzcholka i kazdego koloru prowadze 'jak gdyby osobny bfs', tzn dla kazdego wierzcholka zapamietuje najkrotsza droge do niego z wierzcholka 0, ktora konczy sie krawedzia okreslonego koloru
// i jesli znajde krotsza droge, to dodaje do bfsa dany wierzcholek. To powoduje, ze wierzcholki nie sa przetwarzane zawsze wzgledem rosnacej odleglosci od wierzcholka 0,
// tylko wzgledem rosnacej odleglosci(od wierzcholka 0) dla kazdego z kolorow
//calosc wydaje mi sie ze nie przekracza czasowo 3 * O(N)
void BFS(){
	vector<my_s> neigh; // wektor przechowujacy wierzcholki, odpowiednik last i current w BFSie ktory kiedys pisalem
	REP(i,SIZE(V[0])){
		neigh.PB( my_s( V[0][i],1,W[0][i] ) );
		dist[W[0][i]][V[0][i]] = 1;
		totaldist[V[0][i]] = 1;
	}
	
	REP(crt,SIZE(neigh)){ // crt - taka dziwna nazwa na zmienna, tylko po to zeby nie zajmowac zmiennej i, ani k :)
		my_s S = neigh[crt];
		
		REP(i,SIZE(V[S.num])){ // dla kazdego sasiada aktualnie przetwarzanego wierzcholka
			if( S.col != W[S.num][i] ){ // jesli jest to sasiad, do ktorego moge dojsc krawedzia koloru innego, niz ten, ktorym przyszedlem do wierzcholka S.num to...
			
				if( dist[ W[S.num][i] ][ V[S.num][i] ] > 1 + S.dist ){ // jesli znalazlem krotsza droge
					dist[ W[S.num][i] ][ V[S.num][i] ] = 1 + S.dist;
					totaldist[ V[S.num][i] ] = min( totaldist[V[S.num][i]], 1 + S.dist );
					neigh.PB( my_s( V[S.num][i], 1+S.dist, W[S.num][i] ) );
				}				
			}			
		}		
	}	
}


int main(){
	ios_base::sync_with_stdio(0);
	
	cin >> N >> M;
	
	V = VVI(N); // tworze vector<vector<int> > dla struktury grafu
	W = VVI(N); // tworze vector<vecor<int> > dla 'mapy' kolorow drog
	
	// ustawiam zmienne na nieskonczonosc, czyli ze jeszcze nigdy nie bylem w danych wierzcholkach, idac drga danego koloru, etc. ...
	REP(i,3) dist[i] = new int[N];
	totaldist = new int[N];
	REP(i,N) totaldist[i] = INF;
	REP(i,3) REP(k,N) dist[i][k] = INF;
	REP(i,3) dist[i][0] = 0;
	
	
	
	REP(i,M){
		cin >> a >> b >> c;
		V[a-1].PB(b-1);
		W[a-1].PB(c-1);
	}
	
	
	BFS();
	
	
	if( totaldist[N-1] == INF ) cout << -1 << endl;	 // jesli nie istnieje droga, to wypisuja -1
	else	cout << totaldist[N-1] << endl;
	
}












