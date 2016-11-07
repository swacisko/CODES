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



int answer( string s1, string s2, int k ){
	int ile1 = 0, ile2 = 0;	
	
	REP(i,SIZE(s1)) if( s1[i] == ' ' ){
		s1.erase( s1.begin()+i );
		i--;
	}
	
	REP(i,SIZE(s2)) if( s2[i] == ' ' ){
		s2.erase( s2.begin()+i );
		i--;
	}
	
	if( SIZE(s1) < k || SIZE(s2) < k ) return 0;
	
	REP( i,SIZE(s1) ) if( s1[i] == 'a' || s1[i] == 'o' || s1[i] == 'y' || s1[i] == 'e' || s1[i] == 'u' || s1[i] == 'i' ) ile1++;
	REP( i,SIZE(s2) ) if( s2[i] == 'a' || s2[i] == 'o' || s2[i] == 'y' || s2[i] == 'e' || s2[i] == 'u' || s2[i] == 'i' ) ile2++;	
	if( ile1 != ile2 ) return 0;
	
	if( s1.substr( SIZE(s1)-k ) != s2.substr( SIZE(s2)-k ) ) return 0;
	return 1;
	
}


int main(){
	ios_base::sync_with_stdio(0);
	
	int ile = 0;
	int N,K;
	cin >> N >> K;
	string s1,s2;
	cin.ignore();
	REP(i,N){
		getline( cin,s1 );
		getline( cin,s2 );
		ile += answer( s1,s2,K );
	}
	
	cout << ile << endl;
	
	
	return 0;
}


