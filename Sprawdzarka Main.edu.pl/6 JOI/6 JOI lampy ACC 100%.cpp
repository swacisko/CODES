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
#include<iterator>
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



struct interval{
	interval( double dl=0, int k=0, int nr=0 ){
		this->dl = dl;
		this->k = k;
		this->nr = nr;
		this->dl_calk = dl;
	}
	
	double dl, dl_calk;
	int nr,k;
	
	bool operator<( const interval & oth ) const {
		double w1=0,w2=0;
		w1 = dl_calk*dl_calk/(double)(k+1);
		w2 = dl_calk*dl_calk/(double)(k+2);
		
		double v1,v2;
		v1 = oth.dl_calk*oth.dl_calk/(double)(oth.k+1);
		v2 = oth.dl_calk*oth.dl_calk/(double)(oth.k+2);
	
		if( w1 - w2 < v1 - v2 ) return true;
		else if( w1 - w2 > v1 - v2 ) return false;
		else return nr < oth.nr;
	
	
	//	if( dl < oth.dl ) return 1;
	//	else if( dl > oth.dl ) return 0;
	//	else return nr < oth.nr;
	}	
		
};


vector<interval> V;



void addLamps( int K ){
	
	set<interval> zbior( ALL(V) );

//	FOREACH(it,zbior){
	//		cout << it->nr << "   " << it->dl << endl;
	//	}
	//	ENDL(3);
		
	
	interval T,F;
	set< interval >::iterator it;
	REP(i,K){
		it = zbior.end(); it--;
		T = *it;
		
	
	//	cout << "elementem o najwiekszej dlugosci jest:   nr = " << T.nr << "   dl = " << T.dl << "   dolozonych lamp = " << T.k << "    dl_calk = " << T.dl_calk << endl;

		T.k = T.k + 1;
		T.dl = T.dl_calk / (double)( T.k + 1 );
		zbior.erase( it );
		zbior.insert( T );
	}
	
	
	FOREACH(it,zbior) V[ it->nr ] = *it;
		
}













int main(){
	ios_base::sync_with_stdio(0);
	cout << fixed;
	cout.precision(12);
	
	int N,K;
	double D;
	cin >> N >> K >> D;
	
	V = vector<interval>( N-1 );
	
	int a,b;
	cin >> a;
	REP( i,N-1 ){
		cin >> b;
		V[i].dl = (double) (b-a);
		V[i].nr = i;
		V[i].k = 0;
		V[i].dl_calk = b-a;
		
		a = b;
	}
	
	addLamps( K );
	
	double wyn = 0;
	REP(i,SIZE(V)) wyn += V[i].dl * V[i].dl * (double)( V[i].k + 1 );
	wyn /= 4;
	
	cout << wyn << endl;
	
	
	
	
	
	
	
	
	return 0;
}












