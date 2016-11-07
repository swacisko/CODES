#include<cstdio>
//#include<iostream>
#include<vector>
//#include<string>
//#include<map>
//#include<complex>
//#include<stack>
//#include<list>
//#include<bitset>
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



int N, M;

VI inY;
VI inX;
set<PII> edges;


void solve(){
	edges.clear();
	inX.clear();
	inY.clear();

	//cin >> N >> M;
	scanf( "%d %d",&N,&M );
	
	inX = VI(N-1);
	REP(i,N-1) inX[i] = i+1;
	
	
	inY.clear();
	inY.PB(0);
	
	
	int a,b;
	REP(i,M){
		//cin >> a >> b;
		scanf( "%d %d",&a,&b );
		a--;
		b--;
		edges.insert( MP( min(a,b), max(a,b) ) );
	}
	
	
	REP( i, SIZE( inY ) ){
		a = inY[i];
		
		
		
		REP( k, SIZE(inX) ){
			b = inX[k];
					
			if( edges.count( MP( min(a,b), max(a,b) ) ) == 0 ){
				inY.PB( b );
				swap( inX[k], inX.back() );
				inX.pop_back();
				k--;				
			}			
			
			
		}
		
		
	}
	
	
	if( SIZE(inY) >= N ){
		//cout << "TAK" << endl;		
		printf( "TAK\n" );
	}
	else{
	//	cout << "NIE" << endl;
		printf( "NIE\n" );
	}
	
	
	
	
	
	
}






int main(){
//	ios_base::sync_with_stdio(0);
//	cout << fixed;
//	cout.precision(2);

    int l_zest;    
    //cin >> l_zest;
    scanf( "%d",&l_zest );
    
	while( l_zest-- ){
        solve();


	}


	return 0;
}











