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

int ILE;


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
		ILE--;
	}
	
};






















int main(){
	ios_base::sync_with_stdio(0);
	
	l_zest = 1;
	while(1){
		cin >> N >> M;
		if( N == 0 && M == 0 ) break;
		
		ILE = N;
		
		FAU fau(N);
		REP(i,M){
			cin >> a >> b;
			fau.Union( a-1,b-1 );
		}
		
		cout << "Case " << l_zest++ << ": " << ILE << endl;
		
		
	}
	
	
	
	
	
	return 0;
}












