//#include<stdio.h>
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
//#include<string.h>
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


// nazwa przestrzeni DIAM bierze sie ze slow DIAMETER, a my przeciez szukamy srednicy w drzewie, czyli najdluzszej sciezki :)
namespace DIAM{
	VVI V; // graf
	VI path; // tutaj znajduje sie najdluzsza sciezka w danym drzewie(mozliwe ze jedna z wielu)
	VI dist; // dist[i] to odleglosc wierzcholka i od korzenia w drzewie(umownie od wierzcholka 0, bo korzen moze zostac wybrany dowolnie)
	VI par; // par[i] to rodzic danego wierzcholka na sciezce, jest to potrzebne do wyznaczenia najdluzszehj sciezki
	
	// dfs wyznaczajacy odleglosci wierzcholkow od korzenia
	void dfs( int par, int num, int dst ){
		dist[num] = dst;
		REP(i,SIZE(V[num])) if( V[num][i] != par ){
			dfs( num, V[num][i], dst+1 );
		}
	}
	
	// bfs wyznaczajacy rodzicow na najdluzszej sciezce
	void bfs( int beg ){
		VI neigh(1,beg); par[beg] = INF; // poczatek sciezki nie ma rodzica, wiec INF
		REP(i,SIZE(neigh)){
			REP(k,SIZE( V[neigh[i]] )){ // dla kazdego sasiada kolejnego wierzcholka z bfsa...
				if( par[ V[neigh[i]][k] ] == -1 ){ // jesli jeszcze nie bylem w tym sasiedzie, to go dodaje oraz dodaje jego rodzica
					par[ V[neigh[i]][k] ] = neigh[i];
					neigh.PB( V[neigh[i]][k] );
					dist[ V[neigh[i]][k] ] = dist[ neigh[i] ] + 1;
				}
			}
		}
	}
	
	// funkcja zwracajaca najdluzsza sciezke w drzewie V
	VI getDiameter(){
		dist = VI( SIZE(V),0 );
		par = VI( SIZE(V),-1 );
		
		dfs( 0,0,0 );
		int m = -1, ind = -1; // znajudje maksymalna odleglosc oraz index tego wierzcholka
		REP(i,SIZE(dist)){
			if( dist[i] > m ){
				m = dist[i];
				ind = i;
			}
		}
		
		dist = VI( SIZE(V),0 ); // zeruje dystans przed bfsem
		bfs(ind);
		
		m = -1; ind = -1;
		REP(i,SIZE(dist)){ // znajduje index najdalaszego wierzcholka... jest on koncem najdluzszej sciezki
			if( dist[i] > m ){
				m = dist[i];
				ind = i;
			}
		}
		
		path.PB(ind);
		while( ( ind = par[ind] ) != INF ) path.PB(ind); // poruszam sie od wierzcholka do rodzica tak dlugo az dojde do poczatku
		return path;		
	}
	
	
	
}












int main(){
	
	cout << "Podaj ilosc wierzcholkow drzewa: ";
	cin >> N;

	VVI V(N);
	REP(i,N-1){
		cout << "Podaj krawedz " << i+1 << endl;
		cin >> a >> b;
		V[a-1].PB(b-1);
		V[b-1].PB(a-1);
	}
	
	DIAM::V = V;
	
	VI path =  DIAM::getDiameter();
	cout << "Najdluzsza sciezka w twoim grafie ma dlugosc " << SIZE(path)-1 << endl;
	REP(i,SIZE(path)) cout << path[i] + 1 << " ";
	cout << endl;
		
	
	
}












