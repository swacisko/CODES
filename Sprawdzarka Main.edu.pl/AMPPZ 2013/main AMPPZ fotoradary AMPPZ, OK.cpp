#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<complex>
#include<stack>
#include<list>
#include<set>
#include<bitset>
#include<set>
#include<iterator>
#include<cmath>
#include<queue>
#include<time.h>
#include<string.h>
#include<fstream>
#include<sstream>
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

int N,M,K,a,b,c,y,t,w,l_zest;
const int INF = 1000000001;
const double EPS = 10e-9;
typedef vector<double> VD;
typedef pair<double,int> PDI;
typedef pair<double, double> PDD;
typedef vector<bool> VB;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef map< PII, bool > MPIIB;
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;

VVI V;
VI ans;

void gen(){
	VI t;
	REP(i,SIZE(V)) if( SIZE(V[i]) == 1 ){
		ans.PB(i);
		t.PB(i);
	}
	
	VI g;
	VI st(N);
	REP(i,SIZE(V)) st[i] = SIZE(V[i]);	
//	FOREACH(it,t) cout << *it+1 << " "; cout << endl;
	
	g.clear();
	int x = 2;	
	while( x++ < K && SIZE(ans) < N ){
		REP(i,SIZE(t)){
		//	cout << "t[i] = " << t[i]+1 << endl;
			REP( k,SIZE(V[t[i]]) ){
				st[ V[t[i]][k] ]--;
			//	cout << "\tV[t[i]][k] = " << V[t[i]][k] + 1 << "   st[ten_wierzcholek] = " << st[ V[t[i]][k] ] << endl;		
				if( st[ V[t[i]][k] ] == 1 ){
				//	cout << "Dodaje wierzcholek " << V[t[i]][k]+1 << endl;
					g.PB( V[t[i]][k] );
				}				
			}
		}
		int c = 0;
		if( x == K ) {
			ans.PB( g[0] );
			break;
		}
		x++;
		while( SIZE(ans) < N && c < SIZE(g) ) ans.PB( g[c++] );
		
		swap( g,t );
		g.clear();	
	}
	
/*	if( SIZE(ans) < N && (K&1) ){
		VB tab( N,0 );
		REP(i,SIZE(ans)) tab[ans[i]] = 1;
		REP(i,N) if( !tab[i] ){
			ans.PB(i);
			break;
		}
	}*/
}


int main(){
	
	scanf( "%d %d",&N,&K );
	
	V = VVI(N);
	ans.clear();
	
	REP(i,N-1){
		scanf("%d %d",&a,&b);
		V[a-1].PB(b-1);
		V[b-1].PB(a-1);
	}
	
	if( N == 1 || K == 1 ){ // jesli moze byc tylko jeden fotoradar
		printf( "1\n1\n" );
		return 0;
	}
	
	
	gen();
	
	printf( "%d\n", SIZE(ans) );
	sort( ALL(ans) );
	REP(i,SIZE(ans)){
		printf("%d ",ans[i] + 1);
	}
	printf("\n");
		
	return 0;	
}








