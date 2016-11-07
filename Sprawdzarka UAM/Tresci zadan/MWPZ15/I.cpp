//#include<cstdio>
#include<iostream>
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

int main(){
	
	int N,K;
	
	// JEST TO SPRAWDZENIE KODU ZNALEZIONEGO NA FB, COS MI SIE PRZY NIM PSULO I JESTEM CIEKAW CZY NAPRAWDE TAKI JAK PODANY NA STRONIE DZIALA...
	
	cin >> N >> K;
	
	FOR(i,1,N-K){
		cout << 3 << " ";		
	}
	
	FOR(i,1,K){
		cout << 4 << " ";
	}
	
	FOR(i,0,N-3 - 1){ // UWAGA, TUTAJ NA FB JEST BLAD!!
		cout << 4 << " ";
	}
	
	cout << 2 << " " << 4 << " ";
	
	FOR(i,0,N-1 - 1){ // UWAGA, TUTAJ NA FB JEST BLAD!!
		cout << 2 << " ";
	}
	
	FOR(i,0,N-2 - 1){ // UWAGA< TUTAJ NA FB JEST BLAD!!
		cout << 3 << " ";
	}
	
	cout << 4 << " " << 3 << " " << 4 << endl;
	
	
	
	return 0;
}


