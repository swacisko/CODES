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
//#include<conio.h>

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
//int N,M,K,a,b,c,y,t,w,l_zest;
const long double EPS = 1e-11;
typedef vector<double> VD;
typedef vector< VD > VVD;
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

const int ROZMIAR = 3000011;
LL tab[ ROZMIAR ];

int Collatz( LL n ){
//	if( n >= 100000000000000000 ) cout << "over LL? " << endl;
	if( n < ROZMIAR && tab[n] != 0 ) return tab[n];
	else if( n < ROZMIAR ) return tab[n] = 1 + Collatz( (n&1) ? 3*n+1 : n>>1 );
	else return 1 + Collatz( (n&1) ? 3*n+1 : n>>1 );
}






int main(){
//	ios_base::sync_with_stdio(0);
//	cout << fixed;
//	cout.precision(2);
	
	tab[1] = 1;
	FOR(i,2,1000000) Collatz( i );	
	
	int a,b, l_zest = 0;
	while( cin >> a ){
		cin >> b;
	//	if( l_zest++ >= 1 ) cout << endl;
		LL M = 0;
		int c = a, d = b;
		if( a > b ) swap(a,b);
		FOR(i,a,b) M = max( M,tab[i] );
		cout << c << " " << d << " " << M << endl;
		
	}
	
	
	return 0;
}












