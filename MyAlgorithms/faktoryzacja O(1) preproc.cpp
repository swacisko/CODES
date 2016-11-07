#include<stdio.h>
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


// przestrzen do faktoryzacji liczb w czasie stalym po liniowym preprocessingu i pamieci liniowej od najwiekszej wartosci
namespace FACT{	
	int MSIZE = 8000001;	
	
	VI primes; // przed wywolaniem funkcji factorize nalezy wywolac primes = PrimeList(n)
			 // jest to wektor kolejnych liczb pierwszych nie wiekszych niz MSIZE
			
	VI tab;
	
	// sito erastotenesa, zwrocony vector na k-tej pozycji ma 1 jesli liczba k jest pierwsza
	void Sieve( int s ){
		VB V(s,1);
		V[0] = V[1] = 0;
		FOR( x,2,s ) if( V[x] && LL(s) >= LL(x)*LL(x) )
			for( int y=x*x; y<=s; y+=x ) V[y]=0;
		REP(x,s) if(V[x]) primes.PB(x);
	}
	
	// to jest funkcja ktora trzeba wywolac przed zadawaniem pytac o dzielniki jakiejsc liczby
	void factor_preproc( int N ){
		MSIZE = N+1;
		tab = VI(MSIZE+1); // dla pewnosci dodaje 1
		Sieve( (int)sqrt(MSIZE) ); // to jest znajdowanie liczb pierwszych sietem eratostenesa
		REP(i,MSIZE) tab[i] = INF;
		REP(i,SIZE(primes)) tab[ primes[i] ] = primes[i];
		FOR(i,2,MSIZE-1){
			for( int k = i; (LL)k*i < (LL)MSIZE; k++ ) tab[k*i] = min( tab[k], tab[i] ); // tutaj chyba mogloby byc tab[k*i] = tab[i], zawsze troche szybciej
		}
		REP(i,MSIZE) if( tab[i] == INF ) tab[i] = i;
	}	
	
	// funkcja zwracajaca wektor zawierajacy faktoryzacje liczby N, np  dla 24 zwroci 2,2,2,3
	VI getFactors( int N ){
		VI v;
		while( N > 1 ){
			v.PB( tab[N] );
			N /= tab[N];
		}
		return v;
	}

}

int main(){
//	primes = Sieve( (int)sqrt(MSIZE) );
//	factor_preproc();
//	printf("gotowe");
//	REP(i,30) cout << "tab["<<i<<"] = " << tab[i] << endl;

	FACT::	factor_preproc( 8000000 );
	
	scanf("%d",&l_zest);
	while( l_zest-- ){
		scanf("%d",&N);
		if( N == 1 ){
			printf("1\n");
			continue;
		}
		
		VI v = FACT::getFactors(N);
		WRITE(v);
		
		printf("\n");
		
	}
	
	
	return 0;
}












