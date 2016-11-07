#include<stdio.h>
#include<iostream>
#include<vector>
/*
#include<string>
#include<map>
#include<complex>
#include<stack>
#include<list>
#include<set>
#include<bitset>
#include<set>
#include<iterator>
*/
#include<cmath>
/*
#include<queue>
#include<time.h>
#include<string.h>
#include<fstream>
#include<sstream>
*/
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
typedef long long LL;
const int INF = 1000000001;
LL N,M,K,a,b,c,y,t,w,l_zest,zycie;
const long double EPS = 1e-11;
typedef vector<double> VD;
typedef pair<double,int> PDI;
typedef pair<double, double> PDD;
typedef vector<bool> VB;
typedef vector<LL> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
//typedef map< PII, bool > MPIIB;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;

struct Monster{
	Monster( LL ad, LL aa, LL anr ) : d(ad), a(aa), nbr(anr) { dif = ad - aa;	}
	LL a,d,dif;
	LL nbr; // numer potworka
	bool operator<( const Monster & oth ) const{
		return d < oth.d;
	}
	bool operator<( int t ) const{
		return d < t;
	}
};

int main(){
	ios_base::sync_with_stdio(0);
	cin >> N >> zycie;
	
	LL d,a;
	vector<Monster> pos,neg;
	
	REP(i,N){
		cin >> d >> a;
		if( d <= a ) pos.PB( Monster( d,a,i+1 ) );
		else neg.PB( Monster( d,a,i+1 ) );
	}
	
	VI res;
	
	sort( ALL(pos) );
	
	VI res2;
	LL life = 1;
	
	REP( i,SIZE(pos) ){
		zycie -= pos[i].d;
		if( zycie <= 0 ) goto koniec;
		zycie += pos[i].a;
		res.PB( pos[i].nbr );
	}
	
	//cout << "zycie po dodatnich = " << zycie << endl;
	
	if( SIZE(neg) == 0 ) goto koniec;
	REP(i,SIZE(neg)) swap( neg[i].d, neg[i].a );
	sort( ALL(neg) );
	
	
	REP(i,SIZE(neg)){
		if( life < neg[i].d ) life = neg[i].d + 1;
		life -= neg[i].d;
		life += neg[i].a;
		res2.PB( neg[i].nbr );
	}
	
	if( life > zycie ){
		zycie = -INF;
		goto koniec;
	}
	else{
		reverse( ALL(res2) );
		REP(i,SIZE(res2)) res.PB( res2[i] );
	}

koniec:
	if( zycie <= 0 ){
		cout << "NIE" << endl;
	}
	else{
		cout << "TAK" << endl;
		REP(i,SIZE(res)) cout << res[i] << " ";
		cout << endl;
	}	
	
	return 0;
}












