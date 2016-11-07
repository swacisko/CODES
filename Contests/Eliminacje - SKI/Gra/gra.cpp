#include<cstdio>
//#include<iostream>
#include<vector>
#include<string>
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

#define REP( x,y ) for( int x=0; x<(y); ++x )
#define FORD( x,y,z ) for( int x=y; x>=(z); --x )
#define FOR(x,b,e) for( int x = b; x <= (e); ++x )
#define SIZE(v) (int)v.size()
#define ALL(c) c.begin(),c.end()
#define VAR(v,n) __typeof(n) v=(n)
#define FOREACH(i,c) for( VAR(i,c.begin());i!=c.end();++i )
#define PB push_back
#define MP make_pair
#define ST first
#define ND second
#define WRITE( V ){ REP(trx,SIZE(V)) printf( "%d  ",V[trx] ); printf("\n"); }
#define WRITE_ALL(V) {  REP( i,SIZE(V) ){ cout  << i << " ---- ";  FOREACH(it,V[i]) cout << *it << ", "; cout << endl;     } }
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
typedef vector< VB > VVB;
typedef long long LL;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;

typedef double _T;
typedef vector< _T > VT;
typedef vector< VT > VVT;
typedef pair<_T,_T> PTT;
typedef vector< PTT > VPTT;


LL GCD( LL x, LL y ){
	while(y) swap( x %= y, y );
	return x;
}


int N,K,M;

VVI V;
VI patyczki;

VB was;
VI D;

VI temp;

void getAllD( int num ){
	was[num] = true;
	temp.PB( patyczki[num] );
	
	REP( i, SIZE( V[num]) ){
		if( !was[ V[num][i] ] ){
			getAllD( V[num][i] );
		}
	}
}


int getGCD( VI t ){
	if( SIZE(t) == 0 ){
		printf( "BLAD!! SIZE(t) = 0\n" );
		return -1;
	}
	
	int g = t[0];
	REP( i, SIZE(t) ){
		g = GCD( g, t[i] );
	}
	return g;	
}



void solve(){
	scanf( "%d %d %d",&N,&K,&M );
	
	V = VVI(N);
	was = VB(N,false);
	patyczki = VI(N);
	D.clear();
	
	int a,b;
	REP( i,K ){
		scanf( "%d %d",&a,&b );
		V[a-1].PB(b-1);
		V[b-1].PB(a-1);		
	}
	
	REP( i, N ){
		scanf( "%d",&a);
		patyczki[i] = a;
	}
	
	REP( i,N ){
		if( !was[i] ){
			temp.clear();						
			getAllD(i);
			
		//	printf( "Liczby patyczkow w skladowej spojnosci wierzcholka %d:   ",i ); WRITE(temp);
		//	printf( "GCD tych wszystkich elementow = %d\n", getGCD(temp) );
			
			D.PB( getGCD(temp) );
			
		}
	}
	
//	printf( "Wszystkie najwieksze wspolne dzielniki:   " ); WRITE(D);
	
	REP( i, SIZE(D) ){
		D[i] = GCD( D[i],M );
	}
	
	int ilezer = 0;
	REP( i, SIZE(D) ){
		if( D[i] == M ) ilezer++;
	}
	
	if( ilezer == SIZE(D) ){
		printf( "TAK\n" );
		return;
	}
	else if( ilezer > 0 && ilezer < SIZE(D) ){
		printf( "NIE\n" );
		return;
	}
	
//	printf( "Wszystkie gcd wziete z %d:  ",M ); WRITE(D);
	
	int g = getGCD( D );
	
	REP( i, SIZE(D) ){
		D[i] /= g;
	}
	
//	printf( "Wszystkie gcd, juz wzglednie pierwsze:  " ); WRITE(D);
	
	bool ans = true;
	LL val = g;
	REP( i, SIZE(D) ){
		val *= (LL) D[i];
		if( val >= M ){
			ans = false;
			break;
		}
	}
	
	if( ans == false ){
		printf( "NIE\n" );
	}
	else{
		printf( "TAK\n" );
	}
	
	
}

int main(){

    int l_zest;    
    
    scanf( "%d",&l_zest );
    
	while( l_zest-- ){
        solve();


	}


	return 0;
}












