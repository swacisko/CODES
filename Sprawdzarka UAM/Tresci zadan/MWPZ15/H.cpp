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
typedef vector< VB > VVB;
typedef unsigned long long LL;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;



int N,M;
int tab[5000][5000];
int V[5000];
bool ans[5000][5000];
VPII res;

// *********GLOBAL DATA


void createAnswer( int a, int b ){
	if( a >= b ) return;
	
	if( ans[a][b] == true ){
		createAnswer( a, V[b]-1 );
		createAnswer( V[b]+1,b-1 );
		
		//res.insert( res.end(), MP( V[b],b ) );
		res.PB( MP( V[b],b ) );
		
		//r.insert( r.end(), ALL(r2) );
		//res.insert( res.end(), ALL(r) );
	}
	else createAnswer( a,b-1 );
	
}

void writeAnswer( VPII ans ){
	printf("%d\n",SIZE(ans));
	REP(i,SIZE(ans)){
		printf("%d %d\n",ans[i].ST+1,ans[i].ND+1);
	}	
}

/*
void dynamicSolution(){
	//tab = VVI(N,VI(N,0));
	//ans = VVB(N,VB(N,false));
	
	REP(i,N) REP(k,N) tab[i][k] = ans[i][k] = 0;
	
	int a,b;
	
	for(int dl = 2; dl<=N; dl++){
		
		for( int k = 0; k<=N-dl; k++ ){
			if( (a = V[ (b = k + dl - 1) ]) < b && a >= k ){
				if( tab[k][ a-1 ] + tab[ a+1 ][ b-1 ] + 1 > tab[k][b-1] ){
					
					tab[k][b] = tab[k][ a-1 ] + tab[ a+1 ][ b-1 ] + 1 ;
					ans[k][b] = true;
				}
				else{
					tab[k][b] = tab[k][b-1];
				//	ans[k][k+dl-1] = false;
				}				
			}
			else{
				tab[k][b] = tab[k][b-1];
				//ans[k][k+dl-1] = false;
			}
			
		//	printf( "tab[%d][%d] = %d\n", k, k+dl-1, tab[k][k+dl-1] );		
		}	
		//printf("\n");			
	}	
}*/

void dynamicSolution2(int,int);

int getValue( int a, int b ){
	if( a >= b ) return 0;
	else if( tab[a][b] != -1 ) return tab[a][b];
	else dynamicSolution2( a,b );
	
	return tab[a][b];
	
}



void dynamicSolution2( int a, int b ){
	
	int r1 = -1, r2 = 0;
	
	if( V[b] < b && V[b] >= a ){
		r1 = 1 + getValue( a, V[b]-1 ) + getValue( V[b]+1,b-1 );		
	}
	
	r2 = getValue( a,b-1 );
	
	if( r1 > r2 ){
		tab[a][b] = r1;
		ans[a][b] = true;
	}
	else{
		tab[a][b] = r2;
		ans[a][b] = false;		
	}	
}




void solve(){
	scanf("%d %d",&N,&M);
	int a,b;
	//V = VI(N,-1);
	
	REP(i,N) V[i] = -1;
	
	REP(i,M){
		scanf("%d %d",&a,&b);
		V[a-1] = b-1;
		V[b-1] = a-1;		
	}
	
	REP(i,N) REP(k,N) { tab[i][k] = -1; ans[i][k] = false; }
	
	dynamicSolution2(0,N-1);
	
	res.clear();
	createAnswer(0,N-1);
	
	sort( ALL(res) );
	writeAnswer( res );
	
	
}


int main(){
	
	int l_zest;
	scanf("%d",&l_zest);
	
	while(l_zest--){
		
		solve();
		
		
	}
	
	return 0;
}


