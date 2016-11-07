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
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;

int N;

VVI _next;
vector<string> slowo;
VVI first;


















int main(){
	ios_base::sync_with_stdio(0);
	
	cin >> N;
	
	_next = VVI(N);
	slowo = vector<string>(N);
	first = VVI(N);
	
	REP( i,N ){
		cin >> slowo[i];
		_next[i] = VI( SIZE( slowo[i] ), INF );
		first[i] = VI( 'z' - 'a' + 1, INF );
	}
	
	
	REP(i,N){
		FORD( k,SIZE(slowo[i])-1,0 ){
			if( first[i][ slowo[i][k] - 'a' ] == INF ){
				first[i][ slowo[i][k] - 'a' ] = k;
			}
			else{
				_next[i][k] = first[i][ slowo[i][k] - 'a' ];
				first[i][ slowo[i][k] - 'a' ] = k;
			}
		}
		
	}
	
	string bitek = "";
	int litera;
	bool dalej = true;
	
	while( dalej ){
		
		FORD( k, 'z'-'a',0 ){ // dla kazdej litery sprawdzam czy wystepuje we wszystkich slowach
			litera = k;
			REP(i,N){
				if( first[i][k] == INF ){
					litera = INF;
					break;
				}		
			}
			
			if( litera != INF ) break; // jesli znalazlem literke, to koncze			
			
			
		}
		
		
		if( litera == INF ) break; // jesli nie moge juz znalezc wiecej wspolnych liter, to break
		else{
			bitek += (char)( 'a' + litera );			
			REP( i,N ) REP( k,'z'-'a'+1 ) while( first[i][k] < first[i][litera] ) first[i][k] = _next[i][ first[i][k] ];
			REP( i,N ) first[i][litera] = _next[i][ first[i][litera] ];
		}
		
	}
	
	
	
	if( bitek == "" || bitek < "bitek" ) bitek = "bitek";
	
	cout << bitek << endl;
	
	
	
	return 0;
}












