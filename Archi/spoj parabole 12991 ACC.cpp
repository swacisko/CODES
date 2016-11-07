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


// funkcja liczy calke na przedziale x1 do x2 z paraboli ax2 + bx + c
double area( double a, double b, double c, double x1, double x2 ){
	double p1 = a * ( x2*x2*x2 - x1*x1*x1) / 3;
	double p2 = b * ( x2*x2 - x1*x1 ) / 2;
	double p3 = c * (x2-x1);
	return p1 + p2 + p3;
}

// funkcja przeyjmujaca wspolczynniki paraboli i zwracajaca wszystkie pierwiastki tej paraboli (jesli jakiegos nie ma to zwraca INF )
PDD roots( double a, double b, double c ){
	double delta = b*b - 4*a*c;
	if( delta < 0 ) return MP( (double)INF, (double)INF );
	if( delta == 0 ) return MP(  -b/(2*a)  , (double)INF );
	else return MP( ( -b - sqrt(delta) ) / (2*a), ( -b + sqrt(delta) ) / (2*a)  );
}








int main(){
	
	cout << fixed;
	cout.precision(2);
	
	
	
	cin >> l_zest;
	while( l_zest-- ){
		double res = 0;
		double a1,b1,c1,a2,b2,c2; // odpowiednie wspolczynnuiki
		cin >> a1 >> b1 >> c1 >> a2 >> b2 >> c2;
		
		PDD rts = roots( a1-a2, b1-b2, c1-c2 ); // wyznaczam punkty przeciecia paraboli
		
		if( rts.ST == (double)INF || rts.ND == (double)INF ){ // jesli parabole sie nie przecinaja lub przecinaja tylko w jednym miejscu to pole jest zerowe
			cout << res << endl;
			continue;
		}
		
		double x1 = rts.ST, x2 = rts.ND; // to sa punkty przeciecia paraboli, x1 < x2
		
	/*	// wyznaczam miejsca zerowe dla obydwu paraboli
		PDD rt1 = roots( a1,b1,c1 );
		PDD rt2 = roots( a2,b2,c2 );*/
		
		res = area( a2,b2,c2,x1,x2 ) - area( a1,b1,c1,x1, x2 );
		
		cout << res << endl;
		
		
		// jesli ktoras z paraboli przecina os OX pomiedzy x1  oraz x2 to dodaje ja do wektora, aby rozpatrzac pola na przedzialach
		
		
		
		
		
		
	}
	
	
	
}












