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


map<int, bool> mp;
LL WD;
LL ILE;
LL STAR;

bool gen( LL val ){
	if( ILE == STAR ) return true;
//	cout << "ILE = " << ILE << "   STAR = " << STAR << "   val = " << val << endl;
	REP( i,K ){
		LL c = 10 * ( val % WD ) + i;
		if( mp.find( c ) == mp.end() ){
			mp.insert( MP(c,1) );
			ILE++;
			if( gen( c ) ){
				printf("%d",i);
				return true;
			}
			ILE--;
			mp.erase( c );
		}
	}
	return false;	
}


int main(){
	scanf("%d",&l_zest);
	while(l_zest--){		
		scanf("%d %d",&N,&K);
		mp.clear();
		ILE = N;
		STAR = (int)pow(K,N)+N-1;
		WD = (int)pow(10,N-1);
		
		mp.insert( MP(0,1) );
		
		printf( "%d ", STAR );
		gen( 0 );
		REP(i,N) printf("0");
		printf("\n");
		
	///	printf( "%d %s\n", s.size(), s.c_str() );
		
	}
}







