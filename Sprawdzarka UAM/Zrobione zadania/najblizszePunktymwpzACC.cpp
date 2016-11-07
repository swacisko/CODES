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
typedef long long LL;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;

int N;
VPII tab;

/*
int dst( PII p1, PII p2 ){
    int dst = 0;
    int x,y,X,Y,x2,y2;
    FOR(i,-1,1){
        FOR( k,-1,1 ){
            x = p1.ST + i*4000;
            y = p1.ND + k*4000;

            FOR( i2,-1,1 ){
                FOR(k2,-1,1){
                    x2 = p2.ST + i2*4000;
                    y2 = p2.ND + k2*4000;

                    X = x - x2;
                    Y = y - y2;
                    if( X*X + Y*Y > dst ) dst = X*X + Y*Y;
                }
            }
        }
    }
    return dst;
}*/

int dst( PII p1, PII p2 ){
    int x = min( abs(p1.ST - p2.ST), 4000 - abs(p1.ST - p2.ST) );
    int y = min( abs(p1.ND - p2.ND), 4000 - abs(p1.ND - p2.ND) );
    return x*x + y*y;
}

void clearAll(){
    tab.clear();
}


void readData(){
    cin >> N;
    tab = VPII(N);
    REP(i,N){
        cin >> tab[i].ST >> tab[i].ND;
    }

}

void solve(){
    clearAll();
    readData();

    int M = INF;
    int a=0, b=0;
    REP(i,N){
        FOR( k,i+1,N-1 ){
          //  if( i == k ) continue;
            if( dst( tab[i], tab[k] ) < M ){
                M = dst( tab[i], tab[k] );
                a = i;
                b = k;
            }
        }
    }

    cout << tab[a].ST << " " << tab[a].ND << " " << tab[b].ST << " " << tab[b].ND << endl;

}

int main(){
	ios_base::sync_with_stdio(0);
//	cout << fixed;
//	cout.precision(2);

    int l_zest;
    const int l_zest2 = l_zest; // this is only to remember, how many testcases there were at the beginning
    cin >> l_zest;
	while( l_zest-- ){
        solve();


	}


	return 0;
}












