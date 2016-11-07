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
int N,M,K,a,d,b,C,S,Q,c,y,t,w,l_zest;
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



VVI V;
VVI W;

VVI dst;

VI Dijkstra( int c1 ){
//	cout << "Badam odleglosci dla wierzcholka " << c1 << endl << endl;
	priority_queue<PII> pq;
	pq.push( MP( 0,c1 ) );	
	VI v(C,INF);
	v[c1] = 0;
	
	while( !pq.empty() ){
		int a = -pq.top().ST; // waga;
		int b = pq.top().ND; // nr wierzcholka;
		pq.pop();
	//	cout << "Wierzcholek o najmniejszej odleglosci to " << b << "   jego odl to: " << a << endl;
		if( a == v[b] )	REP( i,SIZE( V[b] ) ){ // dla kazdego sasiada wierzcholka b
			if( v[ V[b][i] ] > max( v[b], W[ b ][i] ) ){
				v[ V[b][i] ] = max( v[b], W[ b ][i] );
				pq.push( MP( -v[ V[b][i] ], V[b][i] ) );
			}
		}		
	}
	return v;
}




int main(){
	
	int test = 1;
	while( cin >> C >> S >> Q ){
		if( C == 0 && S == 0 && Q == 0 ) break;
		if( test > 1 ) ENDL(1);
		
		V = VVI( C );
		W = VVI(C);
		dst = VVI(C);
		
		REP(i,S){
			cin >> a >> b >> d;
			V[a-1].PB(b-1);
			V[b-1].PB(a-1);
			W[a-1].PB(d);
			W[b-1].PB(d);
		}
		
	//	WRITE_ALL(V,""); ENDL(2);
	//	WRITE_ALL(W,""); ENDL(2);
		
		REP( i,C ) dst[i] = Dijkstra( i );
		
	//	WRITE_ALL(dst,"");
		
		cout << "Case #" << test++ << endl;
		REP(i,Q){
			cin >> a >> b;
			if( dst[a-1][b-1] != INF ) cout << dst[a-1][b-1] << endl;
			else cout << "no path" << endl;
		}
	}
	
	return 0;	
}












