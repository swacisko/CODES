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

typedef double _T;
typedef vector< _T > VT;
typedef vector< VT > VVT;
typedef pair<_T,_T> PTT;
typedef vector< PTT > VPTT;

char tab[4001];
int N;
char A,B,C;
int a,b,c;
string s;
const int MOD = 1000000007;

VI litery(30,0);

int npok( int n, int k ){
	if( n <= 0 || k <= 0 ) return 1;
	LL res = 1;
	FOR(i,1,k){
		res *= ( n-k+i );
		res /= i;
	}
	return (int) (res % MOD);
}

VI dwumiana;

void createDwumiany(){
	dwumiana = VI(N+1,0);
	FOR( i,a-1,N ){
		dwumiana[i] = npok( i,a-1 );
	}
}


int allDifferent(){	
	LL Q = 1;	
	int g = N-a-c;
	REP( i, SIZE(litery) ){
		if( (i != A - 'A') && (i != C - 'A') ){
			Q *= (LL) npok( g, litery[i] );
			if( Q >= MOD ) Q %= MOD;
			g += litery[i];			
		}		
	}
	
	printf( "Q = %lld\n",Q );
	
	LL res = 0; // res to liczba tych ciagow, w ktorych nie ma podciagu ABC
	
	FOR(x,c,N-a){
		LL P = npok( x-1,c-1 );
		FOR( y,x+1,N-a+1 ){
			res += P * dwumiana[ N - y ];
			if( res >= MOD ) res %= MOD;			
		}		
	}
	
	printf( "res0 = %lld\n",res );
	
	res *= Q;
	if( res >= MOD ) res %= MOD;
	
	
	
	
	
	
	
	LL all = 1;
	g = 0;
	REP( i,SIZE(litery) ){
		all *= npok( N-g, litery[i] );
		g += litery[i];
	}
	
	printf( "all = %lld\n",all );
	
	
	
	
	return res;	
}

int differentInTheMiddle(){
	
	
}

int differentOnSide(){
	
	
}

int allTheSame(){
	
	
}


void solve(){
		
		scanf( "%s",tab );
		A = tab[0]; B = tab[1]; C = tab[2];
		
		scanf( "%s",tab );
		s = string(tab);
		
		N = SIZE(s);
		litery = VI(30,0);
		REP( i,SIZE(s) ) litery[ s[i] - 'A' ]++;
		a = litery[ A - 'A' ];
		b = litery[ B - 'A' ];
		c = litery[ C - 'A' ];
		
		if( a == 0 || b == 0 || c == 0 ){
			printf( "%d\n",0 );
			return;
		}
		
		createDwumiany();
		
		int val;
		if( A != B && A != C && B != C ){
			val = allDifferent();
		}
		else if( A == B && A != C ){
			val = differentOnSide();
		}
		else if( A == C && A != B ){
			val = differentInTheMiddle();
		}
		else if( B == C && A != C ){
			swap( A,C );
			val = differentOnSide();
		}
		else{
			val = allTheSame();
		}
	
		printf( "%d\n",val );
	
}

int main(){

    int l_zest;    
    
    scanf( "%d",&l_zest );
    
	while( l_zest-- ){
        solve();


	}


	return 0;
}












