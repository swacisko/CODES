//#include<stdio.h>
#include<iostream>
#include<vector>
//#include<string>
//#include<map>
//#include<complex>
//#include<stack>
//#include<list>
//#include<bitset>
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


struct my_s{
	
	my_s( int st, int nd, bool bth = true ) : ST(st), ND(nd), both(bth), val( st+nd ) {}
	int ST,ND;
	bool both;
	int val;
	
	
	bool operator<( const my_s & oth ) const{
		if( ST < oth.ST ) return true;
		else if( ST == oth.ST ) return ND < oth.ND;
		else return false;	
	}
	
	bool operator==( const my_s & oth ) const{
		return ST == oth.ST && ND == oth.ND;	
	}
	
};


ostream& operator<< ( ostream & str, const my_s & ms ){
	str << "ST = " << ms.ST << "   ND = " << ms.ND << "   both = " << ms.both << endl;
	return str;	
}

int solve( int N, int K, VI & V, VI & G ){
	int res = 0;
	multiset<my_s> zbiorV;
	REP(i,SIZE(V)) zbiorV.insert( my_s( 3*V[i], 2*V[i] ) );
	
	sort( ALL(G) );
	multiset<int> zbiorG( ALL(G) );
	
	bool can = true;
	set<my_s>::iterator itV;
	set<int>::iterator itG;
	while( !zbiorG.empty() && !zbiorV.empty() ){
		itV = zbiorV.end();
		itV--;
		
	//	cout << "Oto twoje ciuchy" << endl;
	//	WRITE(zbiorV);
	//	ENDL(2);
	//	cout << "Oto twoje klamerki" << endl;
	//	WRITE(zbiorG);
	//	ENDL(2);
		
		if( itV->both ){ // jesli to jest para
			itG = zbiorG.lower_bound( itV->val );
			if( itG != zbiorG.end() ){ // jesli jestem w stanie polryc calosc
				res++;
				zbiorV.erase( itV );
				zbiorG.erase( itG );
			}
			else{ // w przeciwnym razie jedyne co robie to rozbijam na mniejsze pojedyncze elementy
				int x = itV->val / 5;
				zbiorV.erase( itV );
				zbiorV.insert( my_s( 3*x,0,0 ) );
				zbiorV.insert( my_s( 2*x,0,0 ) );				
			}
			
		}
		else{ // jesli to jest pojedynczy element
			itG = zbiorG.lower_bound( itV->ST );
			if( itG != zbiorG.end() ){
				res++;
				zbiorV.erase( itV );
				zbiorG.erase( itG );
			}
			else{
				can = false;
				break;
			}			
		}	
		
	}
	
	if( zbiorG.empty() && !zbiorV.empty() ) can = false;
	
	if( !can ) return -1;
	return res;
}


int main(){
	ios_base::sync_with_stdio(0);
	cout << fixed;
	cout.precision(2);
	
	
	
	int N,K;
	cin >> N >> K;
	
	VI V(N);
	REP(i,N) cin >> V[i];
	
	VI G(K);
	REP(i,K) cin >> G[i];
	
	int res = solve( N,K,V,G );
	
	if( res == -1 ) cout << "NIE" << endl;
	else cout << res << endl;
	
	
	
	
	return 0;
}












