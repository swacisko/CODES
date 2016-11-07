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
#include<fstream>
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



VI tab; // tab[i] is the value of sum ( f(k) ) for k in [ i*10^6, (i+1)*10^6 ]


LL sumOfDivisors( int N ){
    if( N == 0 ) return 0;
    LL res = 0;

    for( int i=1; i*i <= N; i++ ){
        if( N%i != 0 ) continue;
        res += i;
        if( i*i != N ) res += N/i;
    }

    return res;
}

void createTab(){
    tab.clear();
    LL res = 0;
    REP(i,10000){
        res = 0;

        FOR( k,i*100000, (i+1)*100000 ){
            res += sumOfDivisors(k);
        }


        cout << i << "    ->  " << res << endl;
        tab.PB(res);
    }

    ofstream str( "tab.txt" );

    str << "int tab[] = {";
    REP(i,SIZE(tab)) str << tab[i] << "," << endl;
    str << "};" << endl;
    str.close();
}



int main(){
	ios_base::sync_with_stdio(0);
	cout << fixed;
	cout.precision(2);

    int t = 0;
    REP(i,11) t += sumOfDivisors(i);
    cout << t << endl;

    t = 0;

    for( i = 1; i<= 10; i++ ){
        t += i * ( ( int ) N/i );

    }
    cout << t << endl;

    cout << sumOfDivisors(100) << endl;
    createTab();



	return 0;
}












