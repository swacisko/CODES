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
typedef long long LL;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;


int N;

LL answer( VPII & pary ){
	
	bool* was = new bool[N+1];
	REP(i,N+1) was[i] = true;
	int* tab1 = new int[N+1];
	REP(i,N+1) tab1[i] = INF;
	REP(i,SIZE(pary)) tab1[ pary[i].ND ] = pary[i].ST;
	REP(i,SIZE(pary)) was[ pary[i].ND ] = false;
	
	int t = 0;
	LL L = 0;
	LL value = 0;
	REP( i,SIZE(pary) ){
		t = pary[i].ND;
		L = 0;
		while( t >=0 && (t != INF-1) && (!was[t]) ){
			L++;
			was[t] = true;
			t = tab1[t]-1;
		}
		
		value += (L*(L+1)) / 2;		
	}	
	
	delete[]was;
	delete[]tab1;
	
	return value;
	
}


int main(){
	ios_base::sync_with_stdio(0);
	
	cin >> N;
	
	char znak;
	vector<char> V(N);
	REP(i,N){
		cin >> V[i];
	}
	
	VPII pary;
	
	VI zamyk;
	FORD( i,N-1,0 ){
		if( V[i] == ')' ) zamyk.PB(i);
		else{
			if( SIZE(zamyk) > 0 ){
				pary.PB( MP( i,zamyk[ SIZE(zamyk)-1 ] ) );
				zamyk.pop_back();
			}
		}
	}
	
	REP(i,SIZE(pary)) swap( pary[i].ST, pary[i].ND );
	sort( ALL(pary) );	
	reverse( ALL(pary) );
	REP(i,SIZE(pary)) swap( pary[i].ST, pary[i].ND );
	
	cout << answer( pary ) << endl;
	
	
	
	
	
	
	return 0;
}












