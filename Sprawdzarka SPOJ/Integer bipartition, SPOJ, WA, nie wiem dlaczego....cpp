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

long long N,M,K,a,b,c,y,t,w,l_zest;
const int INF = 1000000001;
const double EPS = 10e-9;
typedef vector<double> VD;
typedef pair<double,int> PDI;
typedef pair<double, double> PDD;
typedef vector<bool> VB;
typedef vector<long long> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef map< PII, bool > MPIIB;
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;


VI ans;

LL invert( LL rev ){
	LL a = 0;
	while( rev > 0 ){
		a = 10*a + rev%10;
		rev /= 10;
	}
	return a/10;
}

void Add( LL rev ){
	ans.PB( invert( rev ) );
}

void funend( LL up, LL down, LL l, LL rev ){
	if( l == 0 || l == up+down ) return;
	while( l > 0 ){
	//	cout << "\tJestem w while'u, up = " << up << "  down = " << down << "  l = " << l << "  rev = " << rev << endl;
		l -= ( up + down );
		l /= 10;
		rev = 10*rev + up;
		up = down;
		if( l <= 0 || ( l < 10 && up != l ) ) break;
		REP( i,10 ){
			if( (i + up)%10 == l%10 ){
				down = i;
				break;
			}
		}
	}
//	if( l == 0 ) cout << "\t\tDodaje wartosc " << invert(rev) << endl;
	if( l == 0 ) Add(rev);	
}

void funrec( LL l, LL rev ){
	if( l <= 0 ) return;
/*	if( l == 0 ){
		Add(rev);
		cout << "l = " << l << "  Dodaje wartosc " << invert(rev) << endl;
		return;
	}*/
	if( l < 10 ){
		rev = 10*rev + l;
	//	cout << "l = " << l << "  Dodaje wartosc " << invert(rev) << endl;
		Add(rev);
		return;
	}
	
	REP( i,10 ){
		REP(k,10){
			if( l%10 == (i+k)%10 ){
				if( i == k ) funrec( (l-i-k)/10, 10*rev+i );
				else funend( i,k,l,rev );	
			}
		}
	}
}

bool check( LL greater, LL lower ){
	ostringstream  sg; sg << greater;
	ostringstream sl; sl << lower;
	string s1 = sg.str(), s2 = sl.str();
	return s2.size() < s1.size();
}

void writeMe( LL l, LL n ){
	ostringstream sg; sg << l;
	ostringstream sl; sl << N-l;
	string s1 = sg.str(), s2 = sl.str();
	printf( "%ld + ",l );
	REP( i, SIZE(s1) - SIZE(s2) - 1  ) printf("0");
	printf( "%ld = %ld\n",n-l,n );
}

int main(){
	
	scanf( "%ld",&l_zest );
	while(l_zest--){
		scanf( "%ld",&N );
		
		ans.clear();
		funrec( N,1 );
		
		sort(ALL(ans));
		for( LL i=0; i<SIZE(ans);i++ ){
			if( !check( ans[i], N - ans[i] ) ){
				ans.erase( ans.begin() + i );
				i--;
			}
		}
		
		sort( ALL(ans) );
		printf( "%ld\n",SIZE(ans) );
		FOREACH( it,ans ){
			writeMe( *it,N );
		}
	//	printf( "\n" );
		
	}
	
	
}
















