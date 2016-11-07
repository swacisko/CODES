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

int N,M,K,a,b,c,y,t,w,l_zest;
const long double EPS = 1e-11;
typedef vector<long double> VD;
typedef pair<long double,int> PDI;
typedef pair<long double, long double> PDD;
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
const int INF = 1000000001;



int main(){

	LL N,M;
	cin >> N >> M;
	
	VLL west(N);
	VLL north(M);
	REP(i,N) cin >> west[i];
	REP(i,M) cin >> north[i];
	
	VLL ile(1000001,0);
	REP( i, N ) ile[ west[i] ]++;
	
	VLL ile2 = ile;	
	FOR(i,1,1000001) ile2[i] += ile2[i-1];
	
	REP( i,1000001 ) ile[i] *= i;
	FOR(i,1,1000001) ile[i] += ile[i-1];
	
	LL MAXN = 0, MAXW = 0;
	REP(i,N) MAXW = max( MAXW, west[i] );
	REP(i,M) MAXN = max( MAXN, north[i] );
	
//	LL MINW = INF, MINN = INF;
//	REP( i,N ) MINW = min( MINW, west[i] );
//	REP(i,N) MINN = min( MINN, north[i] );
	
	if( MAXN != MAXW ){
		cout << "NIE" << endl;
		return 0;
	}
	
//	cout << "ile"  << endl;
//	REP(i,10) cout << ile[i] << " ";
	
//	cout << endl << endl << "ile2" << endl;
//	REP(i,10) cout << ile2[i] << " ";
//	cout << endl;
	
	
	LL sum = 0;
	REP( i,M ){
	//	cout << "i = " << i << "   ";
		if( north[i] > 0 ) sum += north[i] * N - ( north[i] * ile2[north[i]-1]  - ile[north[i]-1] );
	//	if( north[i] > 0 ) cout << "Dodaje wartosc " <<  north[i] * N - ( north[i] * ile2[north[i]-1]  - ile[north[i]-1] ) << endl;
	}
	
	cout << sum << endl;
	
	
	
	
	
	
}












