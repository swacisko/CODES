//#include<cstdio>
#include<iostream>
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

typedef vector< VPII > VVPII;
typedef vector<char> VC;
typedef vector< VC > VVC;

VVPII par;
VVB was;
int N,M;
VVC tab;

const int UP = 0;
const int RIGHT = 1;
const int DOWN = 2;
const int LEFT = 3;

PII head,tail;
int ILE;

int I[] = {-1,0,1};
int K[] = {-1,0,1};

bool goesLeft( int r, int c, int r2, int c2 ){
	bool g = false;
		int pr = par[r][c].ST;
		int pc = par[r][c].ND;
	
	if( head == MP(r,c) ) g = false;
	else{
		
		if( r2 == (r + 1) ){
			if( pc == (c+1) ) g = true;
			
		}else if( r2 == (r-1) ){
			if( pc == (c-1) ) g = true;
			
		}else if( c2 == (c+1) ){
			if( pr == (r-1) ) g = true;
			
		} else if( c2 == (c-1) ){
			if( pr == (r+1) ) g= true;
		}
		else g = false;
	}
	
	/*if( r == 0 && c == 3 ){
		cout << "JEstem w punkcie " << 1 << "," << 4 << "   par: " << pr << "," << pc << " r2 = " << r2 << "  c2 = " << c2 << "   zwracam " << g << endl;
	}*/
	return g;
}

bool dfs( int r, int c, int ile ){
	//REP(i,ile) cout << "    ";
	//cout << "r = " << r << "  c = " << c << "   ile = " << ile << endl;

	was[r][c] = true;
	
	if( tail.ST == r && tail.ND == c && ile == ILE ){
		return true;
	}
	
	
	
	int i,k;
	for( int a=0;a<=2;a++ ){
		for( int b=0; b<=2; b++ ){
			i = I[a];
			k = K[b];
			
			if( i*k == 0 && (i+k != 0) ){			
				
				if( r+i >= 0 && r+i < N && c+k >= 0 && c+k < M && (goesLeft( r,c,r+i,c+k )==false) && 
					((tab[r+i][c+k] == 'x') || (tab[r+i][c+k] == 'R')) && (was[r+i][c+k] == false)  ){
					par[r+i][c+k] = MP(r,c);
					if( dfs( r+i,c+k,ile+1 ) ){						
						return true;
					}					
				}			
			}	
			
		}
	}
	
	was[r][c] = false;
	return false;
}

void solve(){
	cin >> N >> M;
	
	tab = VVC(N,VC(M));
	was = VVB(N,VB(M,false));
	par = VVPII( N, VPII(M) );
	ILE = 2;
	
	REP( i,N ){
		REP(k,M){
			cin >> tab[i][k];
			if( tab[i][k] == 'G' ){
				head = MP( i,k );				
			}
			else if( tab[i][k] == 'R' ){
				tail = MP(i,k);
			}
			else if( tab[i][k] == 'x' ){
				ILE++;
			}
		}
	}
	
	/*if( dfs( head.ST, head.ND,1 ) ){
		cout << "TRUE" << endl;
	}
	else cout << "FALSE" << endl;
	*/
	
	dfs( head.ST, head.ND,1 );
	
	int x = tail.ST, y = tail.ND;
	
	//cout << x+1 << " " << y+1 << endl;
	VPII ans;
	ans.PB( MP( x+1,y+1 ) );
	
	ILE = 0;
	while( head != MP(x,y) ){
		int xt = x;
		x = par[x][y].ST;
		y = par[xt][y].ND;
		//cout << x+1 << " " << y+1 << endl;
		ans.PB( MP(x+1,y+1) );
		
		//if( ILE++ > M*N + 5 ) while(1);
	}
	
	REP( i,SIZE(ans) ){
		cout << ans[i].ST << " " << ans[i].ND << endl;
	}
	
	
}

int main(){
	
        solve();


	return 0;
}












