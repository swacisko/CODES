#include<stdio.h>
//#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<cmath>
#include<queue>
#include<string.h>
#include<sstream>
#include<algorithm>

using namespace std;

#define REP( x,y ) for( int x=0; x<(y); x++ )
#define FORD( x,y,z ) for( int x=y; x>=(z); x-- )
#define FOR(x,b,e) for( int x = b; x <= (e); ++x )
#define SIZE(v) (int)v.size()
#define PB push_back
#define PH push_heap
#define POP pop_back
#define MP make_pair
#define ST first
#define ND second

int N,M,K,a,b,c,y,t,w,l_zest;
const int INF = 1000000001;
typedef vector<double> VD;
typedef pair<double,int> PDI;
typedef pair<double, double> PDD;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef map< PII, bool > MPIIB;
typedef long long LL;

struct BigNum{
#define REDUCE() while( len>1 && !cyf[len-1] ) len--;
	static const int BASE = 1000000000, BD = 9;

	int len,al;
	LL *cyf;
	BigNum( int v = 0, int l = 2 ) : len(1),al(l),cyf( new LL[l] ){
		REP(x,al) cyf[x] = 0;
		if( (cyf[0] = v) >= BASE ) przen(1);
	}
	~BigNum(){
		delete cyf;
	}

	void Res( int l ){
		if( l > al ){
			LL *n = new LL[ l = max(l,2*al) ];
			REP(x,l) n[x] = x >= al ? 0 : cyf[x];
			delete cyf;
			cyf = n;
			al = l;
		}
	}

	void przen(int p){
		int x = 0;
		for( ; x<p || cyf[x]<0 || cyf[x] >= BASE; x++ ){
			Res( x+2 );
				// W razoe [ptrzeby wykonaj zapozyczenie starszej cyfry
			if( cyf[x] < 0 ){
				LL i = ( -cyf[x] - 1 ) / BASE + 1;
				cyf[x] += i*BASE;
				cyf[x+1] -= i;
			}
			else if( cyf[x] >= BASE ) { // lub wykonaj przeniesienie powsta³ego nadmiaru
				LL i = cyf[x] / BASE;
				cyf[x] -= i*BASE;
				cyf[x+1] += i;
			}
		}
		len = max( len, x+1 );
		REDUCE();
	}

#define OPER1(op) bool operator op( const BigNum &a ) const
	BigNum & operator=(int a){
		REP(x,len) cyf[x] = 0;
		len = 1;
		if( (cyf[0] = a) >= BASE ) przen(1);
		return *this;
	}

	void operator*=(int a){
		REP(x,len) cyf[x] *= a;
		przen(len);
	}

	int operator%(int a){
		LL w = 0;
		FORD( p,len-1,0 ) w = ( w * BASE + cyf[p] ) % a;
		return w;
	}

};



int r[50];
bool *is;
VI sums;

LL *ktore;


int main(){
	int l_zest;
	
	scanf( "%d",&l_zest );
	while(l_zest--){
		
		scanf("%d",&N);
		sums.clear();
		is = new bool[N];
		ktore = new LL[N];
		
		REP(x,N)is[x] = false;
		REP(i,N) ktore[i] = 0;
		
		BigNum big(1,2);
		REP(i,50){
			r[i] = big%N;
			big *= 10;
		}
		
		sums.PB(0);
		int t = 0;
		int s;
		while( r[t] != 0 ){
			a = sums.size();
			REP(i,a){
				s = (sums[i] + r[t]) % N;				
				if( !is[ s ] ){
				//	printf( "i = %d  sums[%d] = %d   r[%d] = %d   s = %d\n",i,i,sums[i],t,r[t],s );
					is[ s ] = true;
					sums.PB( s );
					ktore[s] = ktore[ sums[i] ] + ( 1 << t );
					if( s == 0 ) goto end;
				}
			}
			t++;
		}
		
end:
	//	printf("s = %d  ktore[%d] = %d\n",s,s,ktore[s]);
		FORD( i,t,0 ){
			if( ( ktore[s] & ( 1 << i ) ) > 0 ) printf("1");
			else printf("0");
		}
		printf("\n");
		
		
	}
	
}

