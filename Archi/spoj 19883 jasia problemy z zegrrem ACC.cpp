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


typedef vector<PDD> VPDD;



int main(){
	
	double ah, am, bh, bm; // godziny i minuty a oraz b   ( od ahour, aminute, bhout, bminute :)   )
	
	VPDD V; // to jest wektor, ktory przechowuje godziny i minuty, dla ktorych wskazowki sie poklrywaja ( pair<double,double> )
	REP( i,23 ){
		if( i == 11 ) continue;
		double x = (double)i;
		while( x >= 12 ) x -= 12;
		double t = 60*x / 11;
		V.PB( MP( (double)i, t ) );
	}
	
	
	cin >> l_zest;
	while( l_zest-- ){
		
		char c;
		cin >> ah >> c >> am >> bh >> c >> bm; // wczytuje dane jako double
		
		int t = 0;
		int ile = 0; // to jest licznik
		double ah2 = ah, am2 =am, bh2 = bh, bm2 = bm;
		if( ah2 > bh2 || ( ah2 == bh2 && am2 > bm2 ) ){ // jesli A > B to swap'uje 
			swap( ah2, bh2 );
			swap( am2, bm2 );
		}
		
	/*	if( ah == bh && am == bm ){
			cout << 22 << endl;
			continue;
		}*/
		
		while( t < SIZE(V) ){ // przelatuje wszystkie godziny, dla ktorych pwskazowki sie pokrywaja
			
			if( V[t].ST >= ah2 && V[t].ST <= bh2 ){ // we wnetrzu tych ifow, rozbijam sobie na przypadki kiedy godziny sa takie same, rozne, minuty takie same, ...
				if( ah2 < bh2 ){
					if( V[t].ST == ah2 && V[t].ND >= am2 ) ile++;
					else if( V[t].ST == bh2 && V[t].ND <= bm2 ) ile++;
					else if( V[t].ST > ah2 && V[t].ST < bh2 ) ile++;
				}
				else{
					if( V[t].ND >= am2 && V[t].ND <= bm2 ) ile++;
				}				
			}
			t++;
		}
		
	//	cout << "ile = " << ile << endl;
	
		if( ah > bh || ( ah == bh && am > bm ) ){
			if( ( ah==0 && am==0 ) || ( bh==0 && bm==0 ) ) ile--; // jesli godzina poczatkowa lub koncowa jest 00:00 to musze odiac 1 od licznika, bo licze go niepotrzebnie...
			ile = 22 - ile;
		}
		
		cout << ile << endl;
	}
	
	
	
}












