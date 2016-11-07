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

bool show_help = 0;
const int INF = 1000000001;
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


VI primes;
VI PrimeList( int n ){
	VI w(1,2);
	int s = 0, i = 2;
	FOR( l,3,n-1 ){
		i = 0;
		while( w[s]*w[s] <= l ) s++;
		while( i < s && l%w[i] ) i++;
		if( i == s ) w.PB(l);
	}
	return w;
}
/*
void facilitate( int & n ){
	int t = 0;
	while( t < SIZE(primes) && primes[t] <= t ){
		if( !(n%primes[t]) ){
			while( !(n%primes[t]) ) n /= primes[t];
			n *= primes[t];
		}
		t++;
	}
}*/

VI factorize( int n ){
	int t = 0;
	VI prim;
	while( t < SIZE(primes) && primes[t] <= n ){
		if( !(n%primes[t]) ){
			prim.PB( primes[t] );
			n /= primes[t];
		}
		else t++;
	}
	if( n > 1 ) prim.PB(n);
	return prim;	
}

int main(){
	primes = PrimeList( 100000 );
	
	cin >> N;
	
	VI A(N);
	VI B;
	REP(i,N) cin >> A[i];
	REP( i,N ) if( A[i] == 1 ){
		cout << 1 << endl;	return 0;
	}
	if( N == 1 && A[0] != 1){
		cout << "BRAK" << endl; return 0;
	}
	else if( N == 1 ){
		cout << "BRAK" << endl; return 0;
	}
	
//	REP(i,N) facilitate( A[i] );
	
	VVI V(N);
	REP(i,N) V[i] = factorize( A[i] );
	
	VI res(N), result = V[0];
	VI::iterator itr;
	
	FOR(i,1,N-1){
		swap(res,result);
		result = VI( SIZE(res) );
		itr = set_intersection( ALL(V[i]), ALL(res), result.begin() );
		result.resize( itr - result.begin() );
		if( !SIZE(result) ) break;		
	}
	
WAR 	cout << "Wczytalem liczby" << endl;

	if( SIZE(result) ){
		cout << "BRAK" << endl;
		return 0;
	}
	
	a = b = -1;
	int MIN = INF;
	REP(i,N){
		FOR(k,i+1,N-1){
			result = V[i];
			itr = set_intersection( ALL(V[i]), ALL(V[k]), result.begin() );
			if( itr - result.begin() < MIN ){
				a = i;
				b = k;
				MIN = itr - result.begin();
			}
		}
	}

WAR cout << "Najmniejsze przeciecie zachodzi dla liczb na pozycjach " << a << "  oraz " << b << endl;
	
	result = V[a];
	itr = set_intersection( ALL(V[a]), ALL(V[b]), result.begin() );
	result.resize( itr-result.begin() );	
	MIN = 0;
	
	VB was(N,0);
	was[a] = was[b] = true;
	
	int ile = 0;
	while( SIZE(result) > 0 ){
		ile++;
WAR		cout << "Jestem w while'u, rozmiar przeciecia to:" << SIZE(result) << endl;
		MIN = INF;
		REP(i,N){
			if( !was[i] ){
				res = result;
				itr = set_intersection( ALL(V[i]), ALL(result), res.begin() );
				res.resize( itr - res.begin() );
				if( SIZE(res) < MIN ){
					MIN = SIZE(res);
					a = i;
				}
			}
		}		
		was[a] = true;
		res = result;
		itr = set_intersection( ALL(result), ALL( V[a] ), res.begin() );
		res.resize( itr - res.begin() );
		result = res;		
	}
	
	cout << ile + 2 << endl;
	
	
	
	
	
}












