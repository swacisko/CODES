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

/*
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
}*/




bool IsPrimeMR( LL x ){	
	for( int i=2; i*i <= x; ++i ){
		if( !(x%i) ) return false;
	}
	return true;	
}




int main(){
	ios_base::sync_with_stdio(0);
//	cout << fixed;
//	cout.precision(2);
	
	
	
	LL a,b;
	
	cin >> a >> b;
	
	VLL V;
//	V.PB(1);
	V.PB(2);
	V.PB(3);
	V.PB(5);
	V.PB(7);
	
	LL t = 0, ind = 0;
	while( t <= b && ind < SIZE(V) ){
		t = 10*V[ind] + 1;
		if( IsPrimeMR( t ) ) V.PB(t);
		t = 10*V[ind] + 3;
		if( IsPrimeMR( t ) ) V.PB(t);
		t = 10*V[ind] + 7;
		if( IsPrimeMR( t ) ) V.PB(t);
		t = 10*V[ind] + 9;
		if( IsPrimeMR( t ) ) V.PB(t);
		
		ind++;
		t = V[ind];	
	}
	
//	sort( ALL(V) );
//	V.erase( V.begin() );  

//	REP(i,SIZE(V)){
//		if( !(i%5) ) cout << endl;
//		cout << V[i] << ", ";
//	}
	
	int ile = 0;
	REP( i,SIZE(V) ){
		if( V[i] >= a && V[i] <= b ) ile++;
	}
	
	cout << ile << endl;
	
	
	
	
	return 0;
}












