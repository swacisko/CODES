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
int N,M,K,a,b,c,y,t,w,l_zest;
const long double EPS = 1e-11;
typedef vector<double> VD;
typedef pair<double,int> PDI;
typedef pair<double, double> PDD;
typedef vector<bool> VB;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<double, double> PII;
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;

PII V[16];  // to jest wektor par  <double,double> zawierajacy wspolrzedne kolejnych osob
int W[16];  // to jest wektor numerow od 0 do 2*N-1 potrzebny do wygenerowania wszystkich podzialow

double min_val; // to jest wynik, ktory bedzie aktualizowany w count_min
double val; // to jest wartosc tymczasowa dla suma x1+x2+..


// rekurencyjne znajdowanie kazdego z podzialow
void grupuj( int beg ){
	if( beg == 2*N ){
		if( val < min_val ) min_val = val;		// jesli juz wszystkich polaczylem w pary, to sprawdzam, czy suma ich odleglosci nie jest ta minimalna
		return;
	}
	FOR(i,beg+1,2*N-1){ // dla kazdej osoby
		swap( W[beg+1], W[i] ); // zamieniam dwa elementy
		val += sqrt(     (V[W[beg]].ST-V[W[beg+1]].ST)*(V[W[beg]].ST-V[W[beg+1]].ST) + (V[W[beg]].ND - V[W[beg+1]].ND)*(V[W[beg]].ND - V[W[beg+1]].ND)     );
				// dodaje do val odleglosc tak wybranej pary
				// dodaje teraz, zeby nie liczyc tejk wartosci wielokrotnie	
				
		grupuj( beg+2 );		// rekurencyjnie wybieram pozostale pary
		
		
		val -= sqrt(     (V[W[beg]].ST-V[W[beg+1]].ST)*(V[W[beg]].ST-V[W[beg+1]].ST) + (V[W[beg]].ND - V[W[beg+1]].ND)*(V[W[beg]].ND - V[W[beg+1]].ND)     );	
				// odejmuje dana odleglosc, bo zmieniam pare na inna	
				
		swap( W[beg+1], W[i] ); // cofam zamiane miejsc
	}
}


int main(){
	ios_base::sync_with_stdio(0);
	
	cout << fixed;
	cout.precision(2);
	
	int zest = 1;
	while( cin >> N ){
		if( N == 0 ) break;
		
		min_val = INF; // to jest wynik
		string s;
		int x,y;
		REP(i,2*N) W[i] = i;
		
		REP(i,2*N){
			cin >> s >> x >> y;
			V[i] = MP(x,y);
		}
				
		grupuj( 0 ); // sprawdzam wszystkie mozliwosci :)
		
		cout << "Case " << zest << ": " << min_val << endl;		
		zest++;
	}
	
	
	
	
	
	return 0;
}












