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
#define WRITE( V ) FOREACH(it,V) cout << *it << ", "; cout << endl;
#define WRITE_ALL(V,s)  cout << s << endl;  REP( i,SIZE(V) ){ cout << "i = " << i << endl;  FOREACH(it,V[i]) cout << *it << ", "; cout << endl;     }
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


typedef double wtype;
typedef vector<wtype> VWT;
typedef pair<wtype,int> PWTI;
typedef vector<VWT> VVWT;

// przestrzen nazw z danymi do przerobienia algorytmu dijkstry
namespace DIJ{
	
	VVI V;
	VVWT W; // wektor z wagami  W[i][k] to waga laczaca wierzcholke nr i z wierzch. nr V[i][k]
	
	// jako parametry przyjmuje zrodlo oraz referencje do wektora, w ktorym bedzie przetrzymywany rodzic na najkrtszej sciezce od beg do danego wierzcholka
	// jako razultat zwraca wektor z odleglosciami danych wierzcholkow od zrodla beg
	VWT Dijkstra( int beg, VI & par ){
		par = VI(SIZE(V));
		REP( i,SIZE(par) ) par[i] = i;
		
		VWT dst( SIZE(V),INF );
		dst[beg] = 0;
		priority_queue<PWTI> pq; // tworze kolejke priorytetowa - wagi musze dodawac ujemne,
		pq.push( MP( 0,beg ) );
		
		while( !pq.empty() ){
			int a = pq.top().ST;
			int b = pq.top().ND;
			pq.pop();		
			if( dst[b] < a ) continue;
			
			REP( i,SIZE(V[b]) ){
				if( dst[ V[b][i] ] > dst[b] + W[b][i] ){
					dst[ V[b][i] ] = dst[b] + W[b][i];
					par[ V[b][i] ] = b;
					pq.push( MP( -dst[ V[b][i] ], V[b][i] ) );
				}
			}
		}
		return dst;	
	}

}


/*
void Floyd(){
//	cout << "Floyd" << endl;
	REP(i,N){
		REP(k,N){
			REP(j,N){				
				if( shts[k][j] > shts[i][k] + shts[i][j] ){
					shts[k][j] = shts[i][k] + shts[i][j];
					//shts[j][k] = shts[k][j];
				}				
			}			
		}	
	}	
}*/




int main(){
	
	cin >> N >> M;
	DIJ::V = VVI(N);
	DIJ::W = VVWT(N);
	REP(i,M){
		cin >> a >> b >> c;
		DIJ::V[a].PB(b);
		DIJ::V[b].PB(a);
		DIJ::W[a].PB(c);
		DIJ::W[b].PB(c);
	}
	
	VI par;
	VWT dist = DIJ::Dijkstra(0,par);
	
	VVI paths(SIZE(DIJ::V));
	
	cout << "Odleglosc wierzcholka 0 to:" << endl;
	REP(i,SIZE(dist)){
		cout << "Do wierzcholka o numerze " << i << ":  " << dist[i] << ", a sciezka do niego ma postac:  ";
		int p = i;
		paths[i].PB(i);
		while( p != 0 ) paths[i].PB( (p = par[p]) );
		reverse( ALL(paths[i]) );
		WRITE(paths[i]); ENDL(1);
	}
	
	
}












