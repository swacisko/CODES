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
#define WRITE(V) FOREACH(it,V) cout << *it << " "; cout << endl;

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
typedef vector<PII> VPII;













int main(){
	ios_base::sync_with_stdio(0);
	cin >> N;
	
	VI V( 3*N );
	REP( i,3*N ){
		cin >> V[i];
		V[i]--;
	}
	
	VVI pos( N, VI(3,-1) );
	REP(i,3*N){
		if( pos[ V[i] ][0] == -1 ) pos[ V[i] ][0] = i;
		else if( pos[V[i]][1] == -1 ) pos[V[i]][1] = i;
		else pos[V[i]][2] = i;
	}
	
	VPII pairs(N);
	REP( i,N ) pairs[i] = MP( pos[i][1] - pos[i][0], pos[i][2] - pos[i][1] );
	REP( i,N ) pairs[i].ST %= N;
	REP(i,N) pairs[i].ND %= N;
	
	sort( ALL(pairs) );
	
//	FOREACH(it,pairs) cout << it->ST << " " << it->ND << endl;
	
	int t = 1;
	int L = 0;
	int ind = 1;
	
	while( ind < SIZE(pairs) ){
		if( pairs[ind] == pairs[ind-1] ) t++;
		else{
			L = max(L,t);
			t = 1;			
		}
		ind++;
	}
	
	L = max(L,t);
	cout << L << endl;
	
	
	
}





