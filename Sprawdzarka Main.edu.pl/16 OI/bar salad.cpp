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






int main(){
	
	
	cin >> N;
	VI V(N);
	char c;
	REP(i,N){
		cin >> c;
		V[i] = (c == 'p' ? 1 : 0 );
	}
	
//	WRITE(V);
	VI left(N,0);
	VI right(N,0);
	
	int jab,pom,ile;
	
	REP(i,N){
		jab = pom = ile = 0;
		FOR(k,i,N){
			V[k] ? pom++ : jab++;
			if( jab > pom ) break;
			else ile++;
			if( k == N-1 ) ile--;
		}
		right[i] = ile;
	}
	reverse( ALL(V) );
	REP(i,N){
		jab = pom = ile = 0;
		FOR(k,i,N){
			V[k] ? pom++ : jab++;
			if( jab > pom ) break;
			else ile++;
			if( k == N-1 ) ile--;
		}
		left[i] = ile;
	}
	
	reverse( ALL(left) );
	
//	WRITE(right);
//	WRITE(left);	
	
	int MAX = 0;
	
	REP( i,N ){
		FOR(k,i,N){
			if( right[i] >= k-i+1 && left[k] >= k-i+1 ) MAX = max( MAX, k-i+1 );
		}
	}
	
	cout << MAX << endl;
	
	
	
	
	
	
	
	
	
	
	return 0;
}




















