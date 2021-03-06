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
int N,M,K,a,b,c,y,t,w,l_zest,d;
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






namespace FI{
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
	
	VI primes;
	int* fi;
	
	// funkcja jako parametr przyjmuje liczbe naturalna dla ktorej chce znalezc wszystkie wartosci fi
	// jako rezultat zwraca wskaznik na tablice intow fi, taka ze fi[x] to wartosc funkcji fi eulera dla x
	int* createFi( int N ){
		primes = PrimeList( N );
		fi = new int[ N ];
		fi[1] = 1, fi[0] = 0;
		FOR( i,1,N ){
			REP(k,SIZE(primes)){
				if( i * primes[k] > N ) break;
				if( !( i % primes[k] ) ) fi[ i * primes[k] ] = primes[k] * fi[i];
				else fi[ primes[k] * i ] = fi[i] * ( primes[k] - 1 );
			}
		}
		return fi;
	}
	
	

}





int main(){
	
	int N = 100;
	FI::createFi( N );
	
	FOR(i,1,N) cout << "fi["<<i<<"] = " << FI::fi[i] << endl;
	
	
	
	
}












