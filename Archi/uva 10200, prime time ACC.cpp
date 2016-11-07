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
typedef pair<int,int> PII;
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;

// Test pierwszosci Milerem - Rabinem w czsie logarytmicznym
// funkcja przeprowadza test Millera-Rabina dla liczby x przy podstawie n
bool PWit( LL x, LL n ){
	if( x >= n ) return 0;
	LL d = 1, y;
	int t = 0, l = n-1;
	while( !( l & 1 ) ){
		++t;
		l >>= 1;
	}
	for( ; l>0 || t--; l>>=1 ){
		if( l & 1 ) d = (d*x)%n;
		if( !l ){
			x = d;
			l = -1;
		}
		y = (x*x)%n;
		// jesli test millera wykryl, ze licza nie jest pierwsza to zwroc prawde
		if( y == 1 && x != 1 && x != n-1 ) return 1;
		x = y;
	}
	
	return x != 1;
}

// funkcja sprawdza, czy dana liczba jest pierwsza. w tym celu wykonuje test millera-rabina przy podstawie 2,3,5,7
// dziala dla zakresu  do okolo 2 000 000 000
bool IsPrimeMR( LL x ){
	return !( x < 2 || PWit(2,x) || PWit(3,x) || PWit(5,x) || PWit(7,x) );
}





int main(){
	ios_base::sync_with_stdio(0);
	cout << fixed;
	cout.precision(2);
	
	int tab[10001];
	REP( i,10000 ){
		if( IsPrimeMR( i*i + i + 41 ) ) tab[i] = 1;
	}
	
	int tab2[10001];
	FOR( i,0,10000 ) tab2[i] = tab[i] + tab2[i-1];	
	
	
	while( !cin.eof() ){
		cin >> a >> b;
		int primes = tab2[b] - ( (a == 0) ? 0 : tab2[a-1]   );
	//	int val;
		
	/*	val = a*a + a + 41;
		if( IsPrimeMR( val ) ) primes++;
		
		FOR(i,a+1,b){
			val = i*i + i + 41;
			if( IsPrimeMR( val ) ) primes++;
		}*/
	//	cout << "\tval = " << val << endl;
		
		double perc = ( (double)primes   ) / (   (double)( b-a+1 )   );
		perc *= 10000;
		perc = round(perc);
		perc /= 100;
		cout << perc << endl;
		
	}
	
	
	
	
	
	return 0;
}












