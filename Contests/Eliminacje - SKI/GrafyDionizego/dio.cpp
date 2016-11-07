#include<cstdio>
//#include<iostream>
#include<vector>
#include<string>
//#include<map>
//#include<complex>
//#include<stack>
//#include<list>
#include<bitset>
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
#define WRITE( V ){ REP(trx,SIZE(V)) printf("%d ",V[trx]); printf("\n"); }
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


bitset<100> bit100[100];
bitset<200> bit200[200];
bitset<300> bit300[300];
bitset<400> bit400[400];
bitset<500> bit500[500];
bitset<600> bit600[600];
bitset<700> bit700[700];
bitset<800> bit800[800];
bitset<900> bit900[900];
bitset<1000> bit1000[1000];

//bool *flipped;
int N,M;


template<int ile>
void rekurencja( bitset<ile> *V, VI & C, VI & A, VI & B ){
	
	//printf( "\nW grafie pozostaly wierzcholki: " ); WRITE(C);
	//printf( "Oto krawedzie grafu:\n" ); REP( i, SIZE(C) ) REP( k, N ) if( V[ C[i] ].test(k) ) printf( "%d-%d   ",C[i],k );
	
	//sort( ALL(C) );
	int v = -1;
	REP( i, SIZE(C) ){
		if( V[ C[i] ].count() /*- (ile-N)*(flipped[ C[i] ]?1:0 ) )*/ % 2 == 1 ){ // tutaj jest stopien wierzholka C[i] w grafie
			v = i;
			break;
		}
	}	
	
	
	
	if( v == -1 ){
		A = C;
		return;
	}
	else{
		//printf( "Wierzcholek nr   %d   ma nieparzysty stopien\n",C[v] );
		
		swap( C[v], C.back() );
		v = C.back();
		C.pop_back();
		
		VI neigh;
		REP( i, SIZE(C) ){
			if( V[v].test( C[i] ) == 1 ){ // jezeli C[i] jest sasiadem v
				neigh.PB( C[i] ); 				
			}
			V[ C[i] ].set(v,false);
			V[v].set( C[i],false );
		}
		
	//	printf( "Sasiedzi wierzcholka %d:",v ); WRITE(neigh);
		
		REP( i,SIZE(neigh) ) V[ neigh[i] ].set( v,false );
		REP( i,SIZE(neigh) ){
			FOR( k,i+1, SIZE(neigh)-1 ){						
				V[ neigh[i] ].flip( neigh[k] );
				V[ neigh[k] ].flip( neigh[i] );				
			}		
		}
		
		rekurencja<ile>( V,C,A,B );		  
		
		int inters = 0;
		REP( i, SIZE(neigh) ){
			REP( k, SIZE(A) ){
				if( neigh[i] == A[k] ) inters++;
			}
		}
		
	//	printf( "inters = %d\n",inters );
		
		if( inters %2 == 0 ) A.PB( v );
		else B.PB( v );
		
	//	printf( "Dodalem wierzcholek %d\n",v );
	//	printf( "A:   " ); WRITE(A);
	//	printf( "B:   " ); WRITE(B);
		
		
	}
		
}


template<int ile>
void solve2( bitset<ile> *V ){
	
	scanf( "%d",&M );
	
	int a,b;
	REP( i,M ){
		scanf( "%d %d",&a,&b );
		V[a-1].set( b-1,1 );
		V[b-1].set( a-1,1 );
	}
	
	VI A;
	VI B;
	
	VI C(N); REP( i, N ) C[i] = i;
	
	rekurencja<ile>( V,C,A,B );
	
	printf("TAK\n");
	printf( "%d ", SIZE(A) );
	REP( i, SIZE(A) ) printf( "%d ", A[i]+1 );
	printf("\n");
	
	
}


void solve(){
	
	scanf( "%d",&N );
//	flipped = new bool[N];
//	REP(i,N) flipped[i] = false;
	
	if( N <= 100 ) solve2<100>(bit100);
	else if( N <= 200 ) solve2<200>(bit200);
	else if( N <= 300 ) solve2<300>(bit300);
	else if( N <= 400 ) solve2<400>(bit400);
	else if( N <= 500 ) solve2<500>(bit500);
	else if( N <= 600 ) solve2<600>(bit600);
	else if( N <= 700 ) solve2<700>(bit700);
	else if( N <= 800 ) solve2<800>(bit800);
	else if( N <= 900 ) solve2<900>(bit900);
	else solve2<1000>(bit1000);
	
	
	
//	delete[] flipped;
	
}




int main(){

    int l_zest;    
    
    scanf( "%d",&l_zest );
    
	while( l_zest-- ){
        solve();


	}


	return 0;
}












