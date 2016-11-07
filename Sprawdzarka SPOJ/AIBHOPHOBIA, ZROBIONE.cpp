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


char s[6200];
int dl[6101][6101];


int main(){
		
	scanf( "%d",&l_zest );
	while(l_zest--){
		
		scanf( "%s",&s );
		
		int N = strlen( s );
		REP(i,N) dl[i][i] = 1;
		REP(i,N-1) dl[i][i+1] = ( s[i] == s[i+1] ? 2 : 1 );
		
		FOR( i,2,N ){
			REP( k,N-i+1 ){
				a = k;
				b = k + i - 1;
				dl[a][b] = max( max( dl[a+1][b], dl[a][b-1] ) , s[a] == s[b] ? 2 + dl[a+1][b-1] : 0  );
			}
		}
		
		printf( "%d\n", N - dl[0][N-1] );
		
	}
		
}



