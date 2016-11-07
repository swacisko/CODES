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

VD V;
const long double INFIN = 1e20;
const long double eps = 1e-8; // to moze byc za malo zgodnie ze specyfikacja zadania

bool isIn( long double b, long double &MAXL, long double &MINR ){
	MINR = INFIN;
	MAXL = 0;
	FOR(i,1,N){
		MINR = min( MINR, ( V[i+1]-b )/i );
		MAXL = max( MAXL, ( V[i]-b )/i );
	}
//	if( b <= 0 || b >= V[1] ) return true;
	return MINR >= MAXL;
}

long double findLeft( long double b, long double p ){
	long double q = b, MINR, MAXL,k;
	while( q-p > EPS ){
		k = (p+q)/2;
		if( isIn( k, MAXL,MINR ) ) q = k;
		else p = k;
	}
	return p;
}

long double findRight( long double b, long double q ){
	long double p = b, MINR, MAXL,k;
	while( q-p > EPS ){
		k = (p+q)/2;
		if( isIn(k, MAXL, MINR) ) p = k;
		else q = k;
	}
	return p;
}

long double findInterior( long double b, long double & p, long double & q ){
	long double MINR, MAXL, MINRE, MAXLE;
	p = -1e9, q = V[1];
	while( ! isIn( b, MAXL, MINR ) ){
		isIn( b+eps, MAXLE, MINRE );
		if( abs( MINRE - MAXLE ) <= abs( MINR - MAXL ) ) p = b;
		else q = b;
		b = (p+q)/2;
	}
	return b;
}



int main(){
	
//	scanf("%d",&N);
	cin >> N;
	V = VD(N+2);
	FOR(i,1,N) cin >> V[i];     // scanf( "%lf", &V[i] );
	V[N+1] = INFIN;
	long double p,q;
	long double b = findInterior( V[1]/2, p, q );
//	cout << "Interior found at:  " << b << endl;
	
	long double bmin = findRight( b, q );
//	cout << "bmin = " << bmin << endl;
	
	long double bmax = findLeft( b,p );
//	cout << "bmax = " << bmax << endl;
	
	long double l1,l2;
	isIn( bmin, l1,l2 );
	long double lmin = min(l1,l2);
	isIn( bmax,l1,l2 );
	long double lmax = max(l1,l2);
//	printf( "%.9lf %.9lf\n", lmin, lmax );

	cout << fixed;
	cout.precision(12);
	if( lmin < 0 ) lmin = 0;
	cout << lmin << " " << lmax << endl;
	
}
