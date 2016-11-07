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
#define WRITE( V ){ FOREACH(it,V) cout << *it+1 << ", "; cout << endl; }
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
typedef map< PII, bool > MPIIB;
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;




struct FAU{
	int *p,*w;
	FAU( int n ) : p(new int[n]), w(new int[n]) {
		REP(x,n) p[x] = w[x] = -1;
	}
	~FAU(){
		delete[] p;
		delete[] w;
	}
	
	int Find( int x ){
		return ( p[x]<0 ) ? x : p[x] = Find( p[x] );
	}
	
	void Union( int x, int y ){
		if( (x = Find(x)) == (y = Find(y)) ) return;
		if( w[x] > w[y] ) p[y] = x;
		else p[x] = y;
		if( w[x] == w[y] ) w[y]++;
	}
	
};

typedef double wtype;
typedef vector<wtype> VWT;
typedef vector<VWT> VVWT; 


// przestrzen nazwa, w ktorej sa funkcje do tworzenia MST
namespace MST{
	
	VVI V;
	VVWT W; // wektorz przechowujacy wagi krawedzi    W[i][k] to waga krawedzi laczacej wierzcholek nr i z wierzcholkiem nr V[i][k]
	
	struct Edge{
		Edge( int a1, int b1, wtype w1 ) : a(a1), b(b1), w(w1){}
		int a,b;
		wtype w;
		bool operator<( const Edge & e1 )const{
			return w < e1.w;
		}
	};
	
	// funkcja przyjmuje jako parametr graf, a zwraca graf(minimalne drzewo rozpinajace) :)
	pair<VVI,VVWT> KruskalMst( VVI & V, VVWT & W ){
		VVI v(SIZE(V));
		VVWT w(SIZE(W));
		FAU fau(SIZE(V));
		vector<Edge> ed;
		REP(i,SIZE(V)) REP(k,SIZE(V[i])) ed.PB( Edge( i,V[i][k], W[i][k] ) );
		sort( ALL(ed) );
		int x,y;
		REP(i,SIZE(ed)){
			if( (x = fau.Find( ed[i].a ) ) != ( y = fau.Find( ed[i].b ) ) ){
				fau.Union( ed[i].a, ed[i].b );
				v[ed[i].a].PB(ed[i].b);
				v[ed[i].b].PB(ed[i].a);
				w[ed[i].a].PB(ed[i].w);
				w[ed[i].b].PB(ed[i].w);
			}
		}
		
		return MP( v,w );
	}

}




int main(){
	
	
	cin >> N >> M;
	MST::V = VVI(N);
	MST::W = VVWT(N);
	wtype w;
	REP(i,M){	
		cin >> a >> b >> w;
		MST::V[a-1].PB(b-1);
		MST::V[b-1].PB(a-1);
		MST::W[a-1].PB(w);
		MST::W[b-1].PB(w);
	}
	
	
	pair<VVI,VVWT> pr = MST::KruskalMst( MST::V,MST::W );
	
	WRITE_ALL(pr.ST,"Struktura drzewa:",1);
	ENDL(2);
	WRITE_ALL(pr.ND,"Wagi:",0);
	ENDL(2);
	
	
	
	
}












