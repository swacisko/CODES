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
const int MAXVAL = 1000;

VI litery(30,0);

int npok2( int n, int k ){
	if( n <= 0 || k <= 0 ) return 1;
	LL res = 1;
	FOR(i,1,k){
		res *= ( n-k+i );
		res /= i;
	}
	return (int) (res % MOD);
}

VVLL binom;

void createBinomialTable(){
	binom = VVLL(MAXVAL);
	REP( i, SIZE(binom) ){
		binom[i] = VLL( i+1,0 );
		binom[i][0] = 1;
		binom[i][1] = i;
		binom[i][i] = 1;
	}
	
	FOR( i,0,MAXVAL-1 ){
		FOR(k,2,i-1){
			binom[i][k] = (binom[i-1][k-1] + binom[i-1][k])%MOD;
		}
	}	
}

LL npok( int n, int k ){
	if( n > MAXVAL || n < 0 || n > k || k < 0 ) return 0;
	else{
		return binom[n][k];
	}
}


//****************************************

// liczba wszystkich ciagow
LL allSeq(){
	LL res = 1;
	int NN = N;
	REP( i, SIZE(litery) ){
		if( litery[i] > 0 ){
			res *= (LL)binom[ NN ][ litery[i] ];
			if( res >= MOD ) res %= MOD;
			
			NN -= litery[i];			
		}
	}	
	
	return res % MOD;
}

// liczba rozwiazan rownania x1+x2+...+xk = n
LL sol( int k, int n ){
	return (LL)binom[ n+k-1 ][ k-1 ];	
}



LL allDifferent(){	
	LL res = 0;
	
	LL X = allSeq();
	
//	printf( "Alle different a = %d  b = %d  c = %d   all = %lld\n",a,b,c,X );
	
	LL Q1 = 1;
	int NN = N - a - c;
	REP( i, SIZE(litery) ){
		if( (i != (A - 'A')) && (i != (C - 'A')) && litery[i] > 0 ){
			Q1 *= (LL) binom[NN][ litery[i] ];
			if( Q1 >= MOD ) Q1 %= MOD;
			NN -= litery[i];
		}
	}
	
	LL Y = 0;
	FOR( i,c,N-a ){
		Y += (LL)binom[ i-1 ][c-1] * binom[ N-i ][ a ];
		if( Y >= MOD ) Y %= MOD;
	}
	
	Y *= Q1;
	if( Y >= MOD ) Y %= MOD;
	
//	printf( "\nSytuacje, gdy firstA jest za lastC:  Y = %lld\n",Y );
	
	
	LL Q2 = 1;
	NN = a+b+c+1;
	REP( i, SIZE(litery) ){
		if( ( i != (A-'A') ) && ( i != (B-'A') ) && ( i != (C-'A') ) && litery[i] > 0 ){
			Q2 *= (LL) sol( NN,litery[i] );
			if( Q2 >= MOD ) Q2 %= MOD;
			NN += litery[i];
		}
	}
	
	LL Z = 0;
	FOR( i,0,b ){
		FOR( k,1,a ){
			Z += (LL) sol( b-i+1,a-k ) * sol( i+1,c-1 );
			if( Z >= MOD ) Z %= MOD;
		}
	}
	
	Z *= Q2;
	if( Z >= MOD ) Z %= MOD;
	
//	printf( "Sytuacje, gdy firstA jest przed lastC, ale pomiedzy nie ma B:  Z = %lld\n",Z );
	
	res = X - Y - Z;
	//res %= MOD;
	while( res < 0 ) res+= MOD;
//	printf( "%lld = res = %lld - %lld - %lld\n\n",res,X,Y,Z );
	
	
	return res%MOD;	
}

// slowo trzyliterowe postaci ABA, a i b to liczba wystapien
int differentInTheMiddle( char A, char B, int a, int b ){
	LL res = 0;
	LL Q = 1;
	int NN = a+b+1;
	REP( i, SIZE(litery) ){
		if( ( i != (A-'A') ) && ( i != (B-'A') ) && litery[i] > 0 ){
			Q *= (LL) sol( NN,litery[i] );
			if( Q > MOD ) Q %= MOD;
			NN += litery[i];
		}
	}
	
	LL X = 0;
	FOR( k,1,b ){
		X += sol( a-1,k ) * (b-k+1);
		if( X >= MOD ) X %= MOD;
	}
	
	res = X*Q;
	//if( res >= MOD ) res %= MOD;
	while( res < 0 ) res+= MOD;
	
	return res%MOD;
	
}

// slowo trzyliterowe jest postaci AAB, a i b to liczba wystapien
int differentOnSide( char A, char B, int a, int b ){
	LL res = 0;
	
	LL X = allSeq();
	
	LL Y = 0;
	FOR(x,b,N-a){
		Y += (LL)binom[x-1][b-1] * binom[N-x][a];
		if( Y >= MOD ) Y %= MOD;
	}
	
	LL Q = b;
	int NN = a+b+1;	
	REP( i, SIZE(litery) ){
		if( ( i != (A-'A') ) && ( i != (B-'A') ) && litery[i] > 0 ){
			Q *= sol( NN, litery[i] );
			if( Q >= MOD ) Q %= MOD;
			NN += litery[i];
		}		
	}
	
	res = X - Y - Q;
	while( res < 0 ) res+= MOD;
	
	return res%MOD;	
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
		
		
		
		LL val;
		if( A != B && A != C && B != C ){
			if( a == 0 || b == 0 || c == 0 ){
				printf( "%d\n",0 );
				return;
			}
			
			val = allDifferent();			
		}
		else if( A == B && A != C ){
			if( a <= 1 || C == 0 ){
				printf( "%d\n",0 );
				return;
			}
			val = differentOnSide( A,C,a,c );
		}
		else if( A == C && A != B ){
			if( a <= 1 || B == 0 ){
				printf( "%d\n",0 );
				return;
			}
			val = differentInTheMiddle( A,B,a,b );
		}
		else if( B == C && A != C ){		
			if( b <= 1 || A == 0 ){
				printf( "%d\n",0 );
				return;
			}
			val = differentOnSide( B,A,b,a );
		}
		else{
			if( a < 3){
				printf( "%d\n",0 );
				return;
			}
			val = allSeq();
		}
	
		printf( "%lld\n",val );
}

int main(){

    int l_zest;    
    
    createBinomialTable();
    
    scanf( "%d",&l_zest );
    
	while( l_zest-- ){
        solve();


	}


	return 0;
}












