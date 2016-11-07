#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<complex>
#include<stack>
#include<list>
#include<set>
#include<bitset>
#include<set>
#include<iterator>
#include<cmath>
#include<queue>
#include<time.h>
#include<string.h>
#include<fstream>
#include<sstream>
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

int N,M,K,a,b,c,y,t,w,l_zest;
const int INF = 1000000001;
const double EPS = 10e-9;
typedef vector<double> VD;
typedef pair<double,int> PDI;
typedef pair<double, double> PDD;
typedef vector<bool> VB;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef map< PII, bool > MPIIB;
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;





int main(){
	
	int T,E;
	cin >> T >> E;
	
	VLL pw(T+1,0), cal(T+1,0); // moc i kalorie
	
	LL t,p,c;
	REP( i,E ){
		cin >> t >> p >> c;
		
		FORD( i,T,0 ) if( pw[i] > 0 || pw[i] == 0 && cal[i] > 0 || i == 0 ) if( i+t <= T ){
			if( pw[i+t] < pw[i] + p ){
				pw[i+t] = pw[i] + p;
				cal[i+t] = cal[i] + c;
			}
			else if( pw[i+t] == pw[i] + p && cal[i+t] < cal[i] + c ) cal[i+t] = cal[i] + c;
		}
	}
	
	LL MAX = 0;
	LL MAX_C = 0; // maxymalna ilosc kalori- to czego szukamy
	REP(i,T+1) if( pw[i] > MAX ){
		MAX = pw[i];
		MAX_C = cal[i];
	}
	else if( pw[i] == MAX && cal[i] > MAX_C ) MAX_C = cal[i];
	
//	cout << "MAX_C = " << MAX_C << "   MAX_P = " << MAX << endl;
	
	LL F,D;
	cin >> F >> D;
	VVLL ds( 5001, VLL(F+1,0) );
	
	LL c1,f;
	REP( i,D ){
		cin >> c1 >> f;
		FORD( i,5000,0 ){
			FORD( k,F,0 ){
				if( k + f <= F && i + c1 <= 5000 && ( i > 0 || k > 0 ) ) ds[i+c1][k+f] += ds[i][k];
			}
		}
		if( f <= F ) ds[c1][f] += ds[0][0] + 1;
	}
	
	LL SUMA = 0;
	
//	FOR(i,MAX_C,MAX_C+10) REP(k,F+1) cout << ds[i][k] << " ";
	
	FOR( i,MAX_C,5000 ) REP(k,F+1) SUMA += ds[i][k];
	if( MAX_C == 0 ) SUMA++;
	cout << SUMA % 15483359 << endl;
	
	
	
	
	
	
	
	
	
}























