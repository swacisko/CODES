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


int N, M;
VVI V;

VVI temp;

int ones[50][50][50][50];
int twos[50][50][50][50];

void createOnes(){	
	REP( i,M ) REP(k,N) REP( j,M ) REP( l, N ) ones[i][k][j][l] = 0;
	
	
	FOR( y,0,N-1 ) {
		FOR(x,0,M-1){
			if( V[y][x] == 1 ) ones[y][x][y][x] = 1;
		}
	}
	
		
	int ile;
	FOR( y,0,N-1 ){
		ile = 0;
		FOR(x,0,M-1){
			if( V[y][x] == 1 ) ile++;
			ones[y][0][y][x] = ile;
		}
	}
	
	FOR( y,0,N-1 ){
		FOR( x,0,M-1 ){
			FOR( j,x+1,M-1 ){
				ones[y][x][y][j] = ones[y][0][y][j];
				if( x > 0 ) ones[y][x][y][j] -= ones[y][0][y][x-1];				
			}			
		}
	}
	

	FOR( y,0,N-1 ){
		FOR( x,0,M-1 ){
			
			FOR( y2,y+1,N-1 ){
				FOR( x2,x,M-1 ){
					ones[y][x][y2][x2] = ones[y][x][y2-1][x2];
					if( x2 > x ) ones[y][x][y2][x2] += ones[y2][x][y2][x2];					
				}					
			}				
		}	
	}
	
	
	
}

void createTwos(){	
	REP( i,M ) REP(k,N) REP( j,M ) REP( l, N ) twos[i][k][j][l] = 0;
	
	
	FOR( y,0,N-1 ) {
		FOR(x,0,M-1){
			if( V[y][x] == 2 ) twos[y][x][y][x] = 1;
		}
	}
	
		
	int ile;
	FOR( y,0,N-1 ){
		ile = 0;
		FOR(x,0,M-1){
			if( V[y][x] == 2 ) ile++;
			twos[y][0][y][x] = ile;
		}
	}
	
	FOR( y,0,N-1 ){
		FOR( x,0,M-1 ){
			FOR( j,x+1,M-1 ){
				twos[y][x][y][j] = twos[y][0][y][j];
				if( x > 0 ) twos[y][x][y][j] -= twos[y][0][y][x-1];				
			}			
		}
	}
	

	FOR( y,0,N-1 ){
		FOR( x,0,M-1 ){
			
			FOR( y2,y+1,N-1 ){
				FOR( x2,x,M-1 ){
					twos[y][x][y2][x2] = twos[y][x][y2-1][x2];
					if( x2 > x ) twos[y][x][y2][x2] += twos[y2][x][y2][x2];					
				}					
			}				
		}	
	}	
}


int getOverlap( PII A1, PII A2, PII B1, PII B2 ){
	
	int x = max( 0, min(A2.ST,B2.ST) - B1.ST );
	int y = max( 0, min(A2.ND,B2.ND) - B1.ND );
	
	return x*y;
}


int getArea( PII A, PII B ){	
	return abs( ( B.ST - A.ST ) * ( B.ND - A.ND ) );	
}



void solve(){
	scanf( "%d %d",&N,&M );
	
	V = VVI(N, VI(M));
	
	REP( i, N ){
		REP(k,M){
			scanf( "%d", &V[i][k] );			
		}
	}
	
	createOnes();
	createTwos();
	
	FOR( y,0,N-1 ){
		FOR(x,0,M-1){
			FOR( y2,y,N ){
				FOR( x2,x,M ){
				//	printf( "ones[%d][%d][%d][%d] = %d\n", y,x,y2,x2, ones[y][x][y2][x2] );
				}
				
			}
			
			
		}
	}  
	
	
	int Xst = M, Yst = N, Xnd = 0, Ynd = 0;
	
	FOR( x,0,M-1 ){
		FOR(y,0,N-1){
			if( V[y][x] == 2 ){
					Yst = min( Yst,y );
					Xst = min( Xst,x );
					
					Ynd = max( Ynd,y );
					Xnd = max( Xnd,x );
			}
		}
	}
	
	int XXst,XXnd,YYst,YYnd;
	
	int ans = INF;
	
	FOR( y,Yst,Ynd ){
		
		FOR( Yp,y,Ynd ){
			FOR( Xp,Xst,Xnd ){
				
				
				XXst = INF;
				YYst = INF;
				
				XXnd = -1;
				YYnd = -1;
				
				
				FOR( j, Yst,Yp ){
					if( twos[j][Xp+1][j][Xnd] > 0 ){
						YYst = min( YYst, j );
						YYnd = max( YYnd,j );						
					}					
				}
				
				FOR( j,Yp+1,Ynd ){
					if( twos[j][Xst][j][Xnd] > 0 ){
						YYst = min( YYst, j );
						YYnd = max( YYnd,j );						
					}
				}
				
				FOR( k, Xst,Xp ){
					if( twos[Yp+1][k][Ynd][k] > 0 ){
						XXst = min( XXst, k );
						XXnd = max( XXnd,k );						
					}					
				}
				
				int D = INF;
				if( ones[y][Xst][Yp][Xp] == 0 ){
					D = getArea( MP( y,Xst ) , MP( Yp,Xp ) );
					
					if( XXst != INF && ones[YYst][XXst][YYnd][XXnd] == 0  ){							
							D += getArea( MP( YYst,XXst ), MP( YYnd,XXnd ) );
							D -= getOverlap( MP( y,Xst ) , MP( Yp,Xp ), MP( YYst,XXst ), MP( YYnd,XXnd )  );	
						
					}
					else if( XXst != INF && ones[YYst][XXst][YYnd][XXnd] > 0 ) D = INF;
					else D--;					
				}
				
				ans = min( ans,D );
			}			
		}
		
	}
	
	
	if( ans == INF ){
		printf( "%d\n",-1 );
	}
	else{
		printf("%d\n",ans);		
	}


}

int main(){
	
	
		solve();
		
	

	return 0;
}












