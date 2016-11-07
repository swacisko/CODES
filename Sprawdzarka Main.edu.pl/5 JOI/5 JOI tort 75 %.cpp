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

LL N,K;
LL A,B;
VLL horiz, vert;



// funkcja zwraca ilosc pol wiekszych od K
LL binary( long double K ){
	LL ind = 0;
	LL ile = 0;
	
	FORD( i, SIZE(horiz)-1,0 ){
		while( ind < SIZE(vert) && (long double) ( vert[ind] * horiz[ i ] ) < K ) ind++;
		ile += SIZE(vert) - ind;
	}

	return ile;

}


//funckja zwraca najmniejsze pole wieksze od K
LL getMin( long double K ){
//	cout << "\tw getMin K = " << K << endl;
	LL ind = 0;
//	cout << "\tind = " << ind << endl;
	LL INF = 1; REP(i,17) INF *= 10;
	LL MIN = INF;

	FORD( i, SIZE(horiz)-1,0 ){
		while( ind < SIZE(vert) && (long double) ( vert[ind] * horiz[ i ] ) < K ) ind++;
		if( ind < SIZE(vert) ) MIN = min( MIN, (LL)( vert[ind] * horiz[ i ] )  );
	}
	
	if( MIN == INF ) return ( *horiz.rend() * ( *vert.rend()  ) );
	return MIN;

}


LL getAns( LL K ){
//	cout << "K = " << K << endl;

	long double p = 0, q = (long double)A*B + 1.5;
	long double k = p/2 + q/2;

	while( p < q ){
		LL t = binary( k );
	//	cout << "t = " << t << "   k = " << k << endl;
		if( t == K ) break;
		
	//	_sleep(10);

		if( t < K ) q = k-0.4;
		else if( t > K ) p = k+0.45;

		k = p/2 + q/2;
	}

	
	return getMin(k);


}






int main(){
	ios_base::sync_with_stdio(0);
	cout << fixed;
	cout.precision(2);
	

	cin >> A >> B;
	cin >> N >> K;
	LL a,b;
	a = 0;
	REP( i,N ){
		cin >> b;
		horiz.PB( b-a );
		a = b;
	}
	horiz.PB( A - b );

	a = 0;
	REP( i,N ){
		cin >> b;
		vert.PB( b-a );
		a = b;
	}
	vert.PB( B - b );
	

	sort( ALL(horiz) );
	sort( ALL(vert) );
	
//	WRITE(horiz);
//	WRITE(vert);

	cout << getAns(K) << endl;

	
	return 0;
}












