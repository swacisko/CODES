#include<stdio.h>
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
int N,M,K,a,b,c,y,t,w,l_zest;
const long double EPS = 1e-11;
typedef vector<double> VD;
typedef vector< VD > VVD;
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


VI g;
VI next;
int leftest[1000001];
VI ile;
VPII mark;


PII correct( int a, int b, int c, int val ){
//	cout << "Jestem w correct, a = " << a << "   b = " << b << "   c = " << c << "   val = " << val << endl;
	set<int> was;
	PII ans( INF,INF );
	FOR( i,a,c ){
		if( g[i] <= val && was.count(i) == 0 ){
			int t = i, t2 = 1;
			while( t2 < K && t <= b ){
				t = next[t];
				was.insert(t);
				t2++;
			}
			if( t <= b ){
				val = g[i];
				ans = MP( i,t );
			}			
		}		
	}
	
	if( ans != MP( INF,INF ) ) return ans;
//	cout << "ans = " << WRP(ans) << endl;
	return MP( INF,INF );	
}








int main(){
//	ios_base::sync_with_stdio(0);
//	cout << fixed;
//	cout.precision(2);
	
//	cin >> N >> K;
	scanf( "%d %d", &N, &K );
	
	g = VI( N );	
	REP(i,N) scanf( "%d", &g[i] ); //cin >> g[i];
	
	next = VI(N,INF);
	REP(i,1000001) leftest[i] = INF;
	FORD( i,N-1,0 ){
		next[i] = leftest[ g[i] ];
		leftest[ g[i] ] = i;
	}
	
	ile = VI(N,0);
	int last = INF;
	FORD( i,N-1,0 ){
		if( next[i] < last && ile[ next[i] ] == K-1 ){
			ile[i] = K;
			last = i;
			mark.PB( MP( i,g[i] ) );
		}
		else if( next[i] < last ) ile[i] = ile[ next[i] ] + 1;
		else ile[i] = 1;
	}
	
	if( SIZE(mark) == 0 ){
		cout << 0 << endl;
		return 0;
	}
	
	reverse( ALL(mark) );
	
	REP( i,SIZE(mark) ){
		int t = mark[i].ST, t2 = 1;
		while( t2 < K ){
			t = next[t];
			t2++;
		}
		mark[i].ND = t;
	}
	
	mark.insert( mark.begin(), MP( -1,-1 ) );
	mark.PB( MP( N,N ) );
	
	
	//*************  beg
/*	cout << "Oto tablica mark po pierwszych obliczeniach:" << endl;
	FOR(i,1,SIZE(mark)-2) cout << WRP( mark[i] ) << endl;
	FOR( i,1, SIZE(mark)-2 ){
		int t = mark[i].ST, t2 = 1;
		while( t2 < K ){
		//	cout << "t = " << t << endl;
			cout << g[t] << " ";
			t = next[t];
			t2++;
		}
		cout << g[t] << " ";
	}
	
	ENDL(2);*/
	//***************  end
	
	int a,b,c,val;
	FOR( i,1,SIZE(mark)-2 ){
		a = mark[i-1].ND + 1;
		b = mark[i+1].ST - 1;
		val = g[ mark[i].ST ];
		c = mark[i].ST - 1;
		PII p = correct( a,b,c,val );
		
	//	cout << "Zwrocona para przez correct to:  " << WRP(p) << endl << endl;
		
	//	if( p == MP(INF,INF) ) break;
		if( p != MP(INF,INF) ) mark[i] = p;
	}
	
	//*************  beg
//	cout << "Oto tablica mark po ostatnich obliczeniach:" << endl;
//	FOR(i,1,SIZE(mark)-2) cout << WRP( mark[i] ) << endl;
//	ENDL(2);
	//**********  end
	
	
	cout << K*( SIZE(mark)-2 ) << endl;
	FOR( i,1, SIZE(mark)-2 ){
		int t = mark[i].ST, t2 = 1;
		while( t2 < K ){
	//		cout << "t = " << t << endl;
			//cout << g[t] << " ";
			printf( "%d ", g[t] );
			t = next[t];
			t2++;
		}
	//	cout << g[t] << " ";
		printf( "%d ", g[t] );
	}
	
	cout << endl;
	
	
	return 0;
}












