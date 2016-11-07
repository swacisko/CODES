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
#define WRITE( V ){ REP(trx,SIZE(V)) cout << V[trx] << " "; }
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

VI conf;
VVI proby;
VPII resp;
VI code;


int C = 9; // number of colors
int L = 6; // length


bool nextConf( VI & V ){
	int p = L-1;
	
	while( p >= 0 && V[p] == C ) p--;
	
	if( p < 0 ) return false;
	
	V[p]++;
	FOR( x,p+1,L-1 ) V[x] = 0;
	return true;
}


bool check( VI proba, PII resp, VI code, int & c, int & on ){
	c = 0;
	on = 0;	
	
	FOR(x,1,C){
		int m, M;
		m = M = 0;
		REP( i,L ){
			if( proba[i] == x ) m++;
			if( code[i] == x ) M++;
		}
		
		c += min( M,m );		
	}
	
	REP(i,L){
		if( proba[i] == code[i] ){
			on++;
			c--;
		}
	}
	
	if( c == resp.ST && on == resp.ND ) return true;
	else return false;
}


int r_num = 0;
void random_code( VI & V ){
	V = VI(L);
	REP( i, L ){
		V[i] = rand()%(C+1);
	}
	
	if( r_num%3!=0 && r_num < L ) V[r_num] = code[r_num];
	r_num++;
}



bool solve(){
	conf.clear();
	code.clear();
	proby.clear();
	resp.clear();
	
	int c,on,ile;
	
	r_num = 0;
	random_code(code);
	r_num = 0;
	do{
		VI t;
		random_code(t);
		proby.PB(t);
		check( t,MP(0,0),code,c,on );
		resp.PB( MP(c,on) );
		
		ile = 0;
		conf = VI(L,0);
		
		cout << "proby.size() = " << SIZE(proby) << endl;
		
		do{
			bool ok = true;
			REP( i, SIZE(proby) ){
				if( check( proby[i], resp[i],conf,c,on ) == false ) ok = false;
			}
			if( ok == true ) ile++;
			if( ile > 1 ) break;
			
		}while( nextConf(conf) );
		
		cout << "ile = " << ile << endl;
		
	}while( ile > 1 );
	
	if( ile == 0 ) return false;
	return true;	
	
}



int main(){
	srand( unsigned(time(0)) );
	ios_base::sync_with_stdio(0);
	cout << fixed;
	cout.precision(2);

    while( solve() && SIZE(proby) > 17 ){	
		
	}
	
	cout << "code:" << endl;
	WRITE(code);
	cout << endl << "attempts:" << endl;
	REP(i,SIZE(proby)){
		WRITE(proby[i]);
		cout << "   ---   " << WRP(resp[i]) << endl;
	}
	
	
    

	return 0;
}












