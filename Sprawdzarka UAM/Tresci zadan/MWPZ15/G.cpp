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
typedef vector< PDD > VPDD;
typedef vector<bool> VB;
typedef unsigned long long LL;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;




int main(){
	
	int l_zest;
	scanf("%d",&l_zest);
	
	while(l_zest--){		
		
		int N,K;
		//cin >> N >> K;
		scanf("%d %d",&N,&K);
		
		VI tab(N);
		
		int X,Y;
		int beg = 0;
		int a,b;
		
		REP(i,N) tab[i] = i;
		VB was(N,false);
		
		REP(i,K){
			//cin >> a >> b;
			scanf("%d %d",&a,&b);
			swap( tab[a], tab[b] );
			was[a] = was[b] = true;			
		}
		
		X = Y = -1;
		REP(i,N){
			if( was[i] == false  ){
				if( X == -1 ) X = i;
				else{
					Y = i;
				}				
			}			
		}
		
		VPII ans;
		ans.clear();
		
		REP(i,N){
			if( tab[i] != i && i != X && i != Y ){
				beg = i;
				a = i;
				
				do{				
					if( tab[a] == beg ){
						swap( tab[Y], tab[a] );
						swap( tab[Y], tab[beg] );
						swap( tab[X], tab[a] );
						
						ans.PB( MP( Y,a ) );
						ans.PB( MP( Y,beg ) );
						ans.PB( MP( X,a ) );
						
						break;
					}
					else{
						swap( tab[X], tab[a] );
						ans.PB( MP(X,a) );
						
						a = tab[X];						
					}
				
				}while( true );				
			}			
		}		
		
		if( tab[X] == Y ){
			swap( tab[X], tab[Y] );
			ans.PB( MP(X,Y) );
		}		
		
		printf( "%d\n",SIZE(ans) );
		REP(i,SIZE(ans)){
			printf( "%d %d\n", ans[i].ST, ans[i].ND );
		}		
	}
	
	return 0;
}



/*
 1
 7 4
  0 1
  1 2
  2 3
  3 4
 */


