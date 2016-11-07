#include<cstdio>
//#include<iostream>
#include<vector>
#include<string>
//#include<map>
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
#define WRITE( V ){ REP(trx,SIZE(V)) printf( "%d ",V[trx] ); printf("\n"); }
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




bool next_comb( VI & comb, int S ){
	
	comb.PB( S );
	int p = SIZE(comb)-2;
	
	while( p >= 0 && comb[p] == comb[p+1] - 1 ) p--;
	
	comb.pop_back();
	
	if( p < 0 ) return false;
	
	comb[p]++;
	p++;
	while( p < SIZE(comb) ) {
		comb[p] = comb[p-1] + 1;
		p++;
	}
	
	
	
	return true;
}


void solve(){
	
	bitset<36> tab[36];
	
	REP( i,36 ) tab[i].reset();
	
	
	int M;
	scanf( "%d",&M );
	
	int a,b;
	REP( i,M ){
		scanf( "%d %d",&a,&b );
		
		tab[a-1].set( b-1,true );
		//tab[b-1].set(a-1,true);
	}
	
	bitset<36> intersection;
	
	int ans = 1;
	
	VI comb;
	VI grtr;
	
	for( int i=1; i*i <= M; i++ ){
		
		grtr.clear();
		
		REP( k, 36 ){
			if( (int)tab[k].count() >= i ) grtr.PB(k);
		}
		
		int S = SIZE(grtr);
		
		if( S < i ) break;
		
		comb = VI(i);
		REP(k,SIZE(comb)) comb[k] = k;
		
	//	printf( "\ni = %d grtr:   ",i ); WRITE(grtr);
		
		do{
			
		//	printf( "comb:  " ); WRITE(comb);
		
			intersection = tab[ grtr[ comb[0] ] ];
			
			REP( j, SIZE(comb) ){
				intersection &= tab[ grtr[ comb[j] ] ];
			}
			
			if( (int)intersection.count() >= i ){
				ans = i;
				break;
			}
			
			
			
		}while( next_comb(comb, S) == true );
		
	}
	
	
	printf("%d\n",ans);
	
	
	

}

int main(){
	int l_zest;
	scanf( "%d",&l_zest );  

    while( l_zest-- ){
		
		solve();
		
	}

	return 0;
}












