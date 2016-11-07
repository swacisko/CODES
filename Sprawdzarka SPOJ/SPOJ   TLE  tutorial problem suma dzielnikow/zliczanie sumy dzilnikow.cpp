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
#include<string.h>
#include<sstream>
#include<fstream>
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

int N,M,K,a,b,c,y,t,w,l_zest;
const int INF = 1000000001;
const double EPS = 10e-9;
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


int main(){

	VI primes = PrimeList( 1000000 );
//	primes.insert( primes.begin(),1 );
	map<int,bool> mapa;
	
	scanf( "%d",&l_zest );
	while(l_zest--){
		
		scanf( "%d",&N );
		M = N;
		mapa.clear();
		VI fac;
		int t = 0;
		while( primes[t] <= N ){
			while( !(N % primes[t]) ){
				fac.PB( primes[t] );
				N /= primes[t];
			}
			t++;
		}
		
		VI il;
		il.PB(1);
		
		REP( i,SIZE(fac) ){
			int g = SIZE( il );
			REP(k,g){
				if( mapa.find( il[k] * fac[i] ) == mapa.end() && il[k]*fac[i] <= M ){
					il.PB( il[k] * fac[i] );
					mapa.insert( MP( il[k]*fac[i], true ) );
				}
			}
		}
		
		
	/*	FOREACH(it,fac) cout << *it << " ";
		cout << endl;
		FOREACH(it,il) cout << *it << " ";
		cout << endl;
	*/	
		int suma = 0;
		REP( i,SIZE(il) ) suma += il[i];
		
		printf( "%d\n",suma );
		
		
	}
	
	
}

















