//#include<cstdio>
#include<iostream>
#include<vector>
#include<string>
//#include<map>
//#include<complex>
//#include<stack>
//#include<list>
#include<bitset>
#include<set>
//#include<iterator>
#include<cmath>
//#include<queue>
#include<time.h>
//#include<string.h>
//#include<fstream>
//#include<sstream>
#include<algorithm>
//#include<conio.h>

using namespace std;

#define REP( x,y ) for( int x=0; x<(y); ++x )
#define FORD( x,y,z ) for( int x=y; x>=(z); --x )
#define FOR(x,b,e) for( int x = b; x <= (e); ++x )
#define SIZE(v) (int)v.size()
#define ALL(c) c.begin(),c.end()
#define VAR(v,n) __typeof(n) v=(n)
#define FOREACH(i,c) for( VAR(i,c.begin());i!=c.end();++i )
#define PB push_back
#define MP make_pair
#define ST first
#define ND second
#define WRITE( V ){ REP(trx,SIZE(V)) cout << V[trx] << " "; cout << endl; }
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
typedef vector<bool> VB;
typedef vector< VB > VVB;
typedef long long LL;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;

typedef double _T;
typedef vector< _T > VT;
typedef vector< VT > VVT;
typedef pair<_T,_T> PTT;
typedef vector< PTT > VPTT;



int main(){
	ios_base::sync_with_stdio(0);
	
	int Z;
	cin >> Z;
	VI perm(Z+1);
	REP(i,Z) cin >> perm[i+1];
	
	cout << Z << endl;
	REP(i,Z) cout << perm[i+1] << endl;
	
	
	set<PII> zb;
	
	int R;
	cin >> R;
	
	
	cout << R << endl;
	
	
	char c;
	int x,y;
	int T = 0;
	
	VB was(Z+1,false);
	int ile = 0;
	REP(i,R){
		cin >> T;
		
		cout << T << " " << flush;
		ile += T;
		
		REP(k,Z+1) was[k] = false;
		
		REP(k,T){
			cin >> x >> c >> y;
			
			
			cout << x << c << y << " " << flush;
			
			
			if( x <= 0 || x > Z ){
				cout << "Zla numeracja druzyn, x = " << x << endl;
				return 0;
			}
			
			
			if( x == y ){
				cout << "Druzyna " << x << " gra sama ze soba" << endl;
				return 0;
			}
			
			if( was[x] == true ){
				cout << "1.Element " << x << " wystepuje wielokrotnie w rundzie " << i+1 << endl;
				return 0;
			}
			if( was[y] == true ){
				cout << "2.Element " << y << " wystepuje wielokrotnie w rundzie " << i+1 << endl;
				return 0;
			}
			
			if( zb.count( MP( min(x,y), max(x,y) ) ) > 0 ){
				cout << "Mecz " << x << " vs " <<y << " zostal juz rozegrany we wczesniejszej rundzie" << endl;
				return 0;
			}
			
			if( perm[x] == i+1 ){
				cout << "Element " << x << " wystepuje w rundzie " << i+1 << " a nie moze" << endl;
				return 0;
			}
			
			if( perm[y] == i+1 ){
				cout << "Element " << y << " wystepuje w rundzie " << i+1 << " a nie moze" << endl;
				return 0;
			}
					
			was[x] = was[y] = true;
			zb.insert( MP( min(x,y), max(x,y) ) );	
		}
		
		cout << endl;
		
	}
	
	if( 2*ile != Z*(Z-1) ){
		cout << "Rozegrano niewlasciwa liczbe meczy, liczba rozegrana to " << ile << "  a powinno byc " << Z*(Z-1)/2 << endl;
		return 0;
	}
	
	
	
	


	return 0;
}












