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
#define WRITE(T) FOREACH(it,T) cout << it->ST << " " << it->ND << endl; cout << endl;

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


vector<char> V;

void gen( VPII & v ){
	int p = 0, q = 0, jab = 0, pom = 0;
	while( q < SIZE( V ) ){
		if(V[q] == 'p'){
			pom++;
			q++;
		}
		else{
			if( pom > jab ){ jab++; q++;}
			else{
				if(pom) v.PB( MP(p,q-1) );
				p = (++q);
				jab = pom = 0;
				while( q < SIZE(V) && V[q] == 'j' ) p = (++q);
			}
		}
	}	
	if(pom) v.PB( MP( p,q-1 ) ); // jesli doojezdzamy do konca tablicy, to tz trzeba dodac przedzial
}


int main(){
	
	cin >> N;
	V = vector<char>(N);
	REP(i,N) cin >> V[i];
	
	VPII left;// = VPII(N);
	VPII right;// = VPII(N);
	
	gen( left );
	reverse( ALL(V) );
	gen(right);
	
	REP(i,SIZE(right)) swap( right[i].ST, right[i].ND );
	REP(i,SIZE(right)){
		right[i].ST = N - 1 - right[i].ST;
		right[i].ND = N - 1 - right[i].ND;
	}
	
	if( SIZE(left) == 0 ){
		cout << 0 << endl;
		return 0;
	}
	
	WRITE(left);
	cout << endl;
	WRITE(right);
	
	int p1 = left[0].ST, q1 = left[0].ND, p2 = right[0].ST, q2 = right[0].ND;
	int p = 0, q = 0;
	int MAX = 0;
	
	while( p < SIZE(left) && q < SIZE(right) ){
		while( q1 <= q2 ){
			if( p1 < p2 || ( p1 == p2 && q1 == q2 ) ) MAX = max( MAX, min(q1,q2) - max(p1,p2)+1 );
			if( (++p) < SIZE(left) ){
				p1 = left[p].ST;
				q1 = left[p].ND;
			}
			else break;
		}
		if( p >= SIZE(left) ) break;
		while( q2 <= q1 ){
			if( p2 < p1 || ( p1 == p2 && q2 == q1 ) ) MAX = max( MAX, min(q1,q2) - max(p1,p2)+1 );
			if( (++q) < SIZE(right) ){
				p2 = right[q].ST;
				q2 = right[q].ND;
			}
			else break;
		}		
	}
	
	cout << MAX << endl;
	return 0;	
	
}















