//#include<stdio.h>
#include<iostream>
#include<vector>
//#include<string>
//#include<map>
//#include<complex>
//#include<stack>
//#include<list>
//#include<bitset>
#include<set>
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

  
int binom( int N, int K ){
	if( N < K ) return 0;	
	LL n = 1;
	LL k = 1;
	int p = N;
	int q = 1;
	while( p >= N-K+1 && q <= K ){
		if( p <= N ) n *= p--;
		if( q <= K ) n /= q++;
	}
	return n;
}


typedef vector< VVI > VVVI;
typedef vector< VVVI > VVVVI;

VVVVI tab;

// funkcja generuje wszystkie k-eltowe podzbiory zbioru N-eltowego w uporzadkowaniu minimalnych zmian
// dzial=a dynamicznie, tzn dla wszystkich i <= N oraz k <= K tworzy wszystkie mozliwe odpowiedzi
void generate( int N, int K ){
	tab.clear();
	tab = VVVVI(N+1);
	REP(i,N+1) tab[i] = VVVI( N+1, VVI(0) );
	
	VVI help(1);
	VVI zero;
	REP(i,N+1){
		tab[i][i] = help; 
		help[0].PB(i+1);
		
		if( i >= 1 ) tab[i][1] = zero;
		zero.PB( VI( 1,i+1 ) );
		
		tab[i][0] = VVI(0);
	}	
	// teraz mam juz dane warunki poczatkowe
	
	VI help2;
	VVI help3;
	FOR( i,2,N ){
		FOR(k,2,i-1){
			help.clear();
			
			REP( t, SIZE( tab[i-1][k] ) ) help.PB( tab[i-1][k][t] );
			
			int ind = SIZE(help);
			FORD( t, SIZE( tab[i-1][k-1] )-1, 0 ) help.PB( tab[i-1][k-1][t] );

			FOR( t,ind, SIZE(help)-1 ) help[t].PB(i);
			tab[i][k] = help;
		}
	}

}



// funkcja rank dla podzbiorow k-eltowych N-eltowego zbioru
int rank( int N, int K, VI & V ){
	int r = 0;
	int jeden = 1;
	FORD(i, SIZE(V)-1, 0){
		r += binom( V[i], i+1 ) * jeden;
		jeden *= -1;
	}
	
	if( K & 1 ) r--;
	return r;
}


// funkcja unrank dla k-eltowych podzbiorow n-eltowego zbioru
VI unrank( int N, int K, int r ){
	int x = N;
	VI V;
	FORD( i,K,1 ){
		while( binom(x,i) > r ) x--;
		V.PB(x+1);
		r = binom(x+1,i) - r - 1;
	}
	reverse( ALL(V) );
	return V;
}







int main(){
	ios_base::sync_with_stdio(0);
	cout << fixed;
	cout.precision(2);
	
	
	int N,K;
	
	while( true ){
		cout << "Podaj nr zadania:\t";
		int nr;
		cin >> nr;
		switch(nr){

			case 1:{
				cout << "Podaj N:\t";
				cin >> N;
				
				cout << "Podaj K:\t";
				cin >> K;
				if( K == 0 ){
					cout << "Zbior pusty" << endl;
					break;
				}
				
				generate(N,K);
				REP( i, SIZE( tab[N][K] ) ){
					REP( k, SIZE(tab[N][K][i] ) ) cout << tab[N][K][i][k] << " ";
					cout << endl;
				}
	
				ENDL(2);

				break;
			}
			
			case 2:{
				cout << "Podaj N:\t";
				cin >> N;
				
				cout << "Podaj K:\t";
				cin >> K;
				VI V(K);
				if( K == 0 ){
					cout << "ranga zbioru pustego to 0" << endl;
					break;
				}
				
				cout << "Podaj te elementy:\t";
				FOR(i,0,K-1) cin >> V[i];

				//sort( V.rbegin(), V.rend() );
				int r = rank( N,K,V );
				cout << "ranga = " << r << endl;



				break;
			}
			
			
			
			case 3:{
				cout << "Podaj N:\t";
				cin >> N;
				
				cout << "Podaj K:\t";
				cin >> K;
				VI V(K);
				if( K == 0 ){
					cout << "???" << endl;
					break;
				}

				cout << "Podaj range:\t";
				int r;
				cin >> r;
				
				VI G = unrank( N,K,r );
				WRITE(G);
				ENDL(2);

				break;
			}
			
			default:{
				system("clear");
			}
			
		}
	}
	
	
	
	
	
	
	
	return 0;
}












