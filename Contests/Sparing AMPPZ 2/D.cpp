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



VPII costs;
int P;
int N;


// teraz tablica jest posortowana stabilnie, od najwiekszego do najmniejszego
void sortCosts(){
	REP( i,SIZE(costs) ){
		for( int k=SIZE(costs)-1; k>=i+1; k--  ){
			if( costs[k].ST > costs[k-1].ST ){
				swap( costs[k], costs[k-1] );
			}			
		}		
	}	
}


void revSort(VPII costs){
	VPII p = costs;
	REP( i, SIZE(costs) ){
		p[ costs[i].ND ] = costs[i];
	}
	costs = p;
}


void solve(){
	
	scanf("%d %d",&P,&N);
	
	costs = VPII(N);
	
	int a;
	REP( i,N ){
		scanf( "%d",&a );
		costs[i] = MP( a,i );		
	}
	
	
	sortCosts();
	
//	printf( "Posortowane koszty:\n" ); REP( i,N ) printf( "(%d,%d)\n",costs[i].ST, costs[i].ND );
	
	VI ans(N,0);
	int avg;
	int amount;
	
	while( P > 0 && SIZE(costs) > 0 ){
		avg = P / SIZE(costs);
		
		amount = min( max(avg,1), costs.back().ST - ans[ costs.back().ND ] );
		
	//	printf( "avg = %d    amount = %d\n",avg,amount );
		
		int p = 0;
		while( P > 0 && p < SIZE(costs) ){
			ans[ costs[p].ND ] += amount;
			P -= amount;
			p++;
		}
		
		
		while( ans[ costs.back().ND ] == costs.back().ST ) costs.pop_back();		
	}
	
	if( P > 0 ){
		printf( "IMPOSSIBLE\n" );
	}
	else{
		
		REP(i,N-1){
			printf( "%d ", ans[i] );
		}
		
		printf( "%d\n",ans[N-1] );
		
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












