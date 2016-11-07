//#include<stdio.h>
#include<iostream>
#include<vector>
//#include<string>
//#include<map>
//#include<complex>
//#include<stack>
//#include<list>
//#include<bitset>
//#include<set>
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
#define WRITE_ALL(V,s,t) { cout << s << endl;  REP( i,SIZE(V) ){ cout  << i+1 << " ---- ";  FOREACH(it,V[i]) cout << *it+t << ", "; cout << endl;     } }
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
typedef long long LL;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;





int solve( string s, int K ){
	bool allD = true;
	REP(i,SIZE(s)) if( s[i] == 'S' ) allD = false;
	if( allD == true ) return SIZE(s); // jesli s to sa same litery D
	
	
	bool allS = true;
	REP(i,SIZE(s)) if( s[i] == 'D' ) allS = false;
	if( allS == true ) return 0; // jesli s to sa same litery D
	
	
	VI V;
	int left = 0, right = 0;
	int p = 0;
	while( p < SIZE(s) && s[p] == 'D' ){
		p++; left++;
	}
	
	int q = SIZE(s)-1;
	while( q >=0 && s[q] == 'D' ){
		q--;
		right++;
	}
	
	K += 2;
	
//	cout << "p = " << p << "   q = " << q << endl;
	
	int ile = 0;
	FOR( x, p, q ){
		if( s[x] == 'D' ) ile++;
		else{
			if( x > 0 && x != p && s[x-1] == 'D' ) V.PB( ile );
			ile = 0;
		}
	}
	
	sort( ALL(V) );
	reverse( ALL(V) );
	
	if( K == 3 ) return max( left+right, ( SIZE(V) ? V[0] : 0   ) );
	if( K == 2 ) return max( left, max( right, ( SIZE(V) ? V[0] : 0   )  ) );
	
//	cout << "V:  "; WRITE(V);
//	cout << "let = " << left <<"   right = " << right << endl;
	
	int MAX = 0;
	
	int ILE = 0;
	int Kcopy = K;
	int x = 0;
	{ // jesli bierzemy left i bierzemy right
		K-=2;
		x = 0;
		ILE = left + right;
		while( x < SIZE(V) && K >= 2 ){
			ILE += V[x];
			K -= 2;
			x++;
		}
		
		MAX = max( MAX, ILE );		
	}
	
//	cout << "MAX = " << MAX << endl;
	K = Kcopy;
	
	{ // jesli bierzemy left, ale nie bierzemy right
		K--;
		x = 0;
		ILE = left;
		while( x < SIZE(V) && K >= 2 ){
			ILE += V[x];
			K -= 2;
			x++;
		}
		
		MAX = max( MAX, ILE );		
	}
	
//	cout << "MAX = " << MAX << endl;
	K = Kcopy;
	
	{ //jesli bierzemy right, ale nie bgierzemy left
		K--;
		x = 0;
		ILE = right;
		while( x < SIZE(V) && K >= 2 ){
			ILE += V[x];
			K -= 2;
			x++;
		}
		
		MAX = max( MAX, ILE );		
	}
	
//	cout << "MAX = " << MAX << endl;
	K = Kcopy;
	
	{ // jesl nie bierzemy zadnego
		x = 0;
		ILE = 0;
		while( x < SIZE(V) && K >= 2 ){
			ILE += V[x];
			K -= 2;
			x++;
		}
		
		MAX = max( MAX, ILE );		
	}
//	cout << "MAX = " << MAX << endl;
	
	return MAX;
	
}











int main(){
	ios_base::sync_with_stdio(0);
	cout << fixed;
	cout.precision(2);
	
	int N,K;
	int l_zest;
	cin >> l_zest;
	while( l_zest--){
		
		cin >> K;
		string s;
		cin >> s;
		
		cout << solve( s,K ) << endl;
		
		
		
		
	}
	
	
	
//	SSDDSDDDSSDDDDD
	
	
	return 0;
}













