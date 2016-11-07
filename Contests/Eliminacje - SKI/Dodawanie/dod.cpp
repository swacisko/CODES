#include<cstdio>
//#include<iostream>
#include<vector>
#include<string>
#include<map>
//#include<complex>
//#include<stack>
//#include<list>
#include<bitset>
#include<set>
//#include<iterator>
#include<cmath>
//#include<queue>
#include<time.h>
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
#define WRITE( V ){ REP(trx,SIZE(V)) cout << V[trx] << " "; cout << endl; }
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


VLL L;
int N;
LL W;

bool canGetSum(){	
	VLL T;
	T.PB(0);
	REP( i, SIZE(L) ){
		int a = SIZE(T);
		REP( k,a ){
			if( T[k] + L[i] <= W ) T.PB( T[k] + L[i] );
		}		
	}
	
	REP( i, SIZE(T) ){
		if( T[i] == W ) return true;
	}
	return false;
	
}


LL add1( LL a, LL b ){
	if( a+b == W ){
		printf( "%lld + %lld = %lld\n",a,b,W );
	}
	return a+b;
}

LL add2( LL a, LL b ){
	long long d = 10;
	
	while( d <= b ) d *= 10;
	if( d*a+b == W ){
		printf( "%lld + %lld = %lld\n",a,b,W );
	}
	if( d * (long long)a + b > W )  return W+1;
	
	else return d*a+b;
}


VLL possibleResults( VLL values ){
	
	int M = SIZE(values);
	if( M == 1 ) return values;
			
	int a = 1;
	
	VLL V1, V2;
	
	VLL res;
	
	while( a < (1<<M)-1 ){
		
		V1.clear();
		V2.clear();
		int p = 0;
		while( ( 1 << p ) < (1<<M) ){
			if( (a & ( 1 << p )  ) > 0 ) V1.PB( values[p] );
			else V2.PB( values[p] );
			p++;
		}
		
		
		/*if( SIZE(V1) == SIZE(values) || SIZE(V2) == SIZE(values) ){
			printf( "TO LARGE SUBSETS\n" );
			break;
		}*/
		
		VLL P1 = possibleResults( V1 );
		VLL P2 = possibleResults( V2 );
		
		/*printf( "a = %d\n",a );
		printf( "values:\t" );  REP( i, SIZE(values) ) printf( "%lld ", values[i] );
		printf( "\nV1:\t" );  REP( i, SIZE(V1) ) printf( "%lld ", V1[i] );
		printf( "\nV2:\t" );  REP( i, SIZE(V2) ) printf( "%lld ", V2[i] );				
		printf( "\nP1:\t" );  REP( i, SIZE(P1) ) printf( "%lld ", P1[i] );
		printf( "\nP2:\t" );  REP( i, SIZE(P2) ) printf( "%lld ", P2[i] );
		printf( "\n" );
		*/
		REP( i,SIZE(P1) ) res.PB(P1[i]);
		REP( i,SIZE(P2) ) res.PB(P2[i]);
		
		REP( i, SIZE(P1) ){
			REP( k, SIZE(P2) ){
				res.PB( add1( P1[i], P2[k] ) );
				res.PB( add2( P1[i], P2[k] ) );			
			}			
		}
		
		a++;
	}
	
	
	
	sort( ALL( res ) );
	res.resize( unique( ALL(res) ) - res.begin() );
	FORD( i,SIZE(res)-1,0 ){
		if( res[i] > W ) res.pop_back();
	}
	
	
	return res;	
}



void solve(){
		
	scanf( "%d", &N );
	L = VLL(N);
	REP(i,N){
		scanf( "%lld",&L[i] );
	}
	scanf( "%lld",&W );
	
	bool teacher = canGetSum();
	
	if( teacher == true ){
		printf( "TAK\n" );
		
	}
	else{
		VLL przemyslaw = possibleResults( L );
		
		bool found = false;
		REP( i,SIZE(przemyslaw) ){
			if( przemyslaw[i] == W ){
				found = true;
				break;
			}
		}
		if( found == false ){
			printf( "TAK\n" );			
		}
		else{
			printf( "NIE\n" );
		}
		
		
		
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












