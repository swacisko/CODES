//#include<cstdio>
#include<iostream>
#include<vector>
#include<string>
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
#include<sstream>
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


string polecenie;

string getCommand(int nr){
	ostringstream str;
	if( nr < 10 ) str << "0" << nr;
	else str << nr;
	return str.str();


}


int main(){
	ios_base::sync_with_stdio(0);
	cout << fixed;
	cout.precision(2);

	cout << "Podaj nazwe:" << endl;
	string nazwa;
	cin >> nazwa;

	/* musi byc dany plik wykonywalny z zadanie   o nazwie   nazwa.exe
	 * ponadto musi byc katalog z plikami wejsciowymi tez o tej nazwie+numer, wszystkie pliki wejsciwe musza sie znajdowac w nim
	 * struktura wiec ma postac
	 * nazwa/nazwa01.in
	 * nazwa/nazwa02.in
	 * ...
	 * nazwa/nazwa10.in
	 *
	 *
	 * w katalogu nazwa  musi byc dany katalog outy, tam bede wysylane odpowiedzi
	 *
	 * */


    // uwaga, teraz jest zrobione pod windowsa !!!
	for( int i=1; i<=10; i++ ){
		polecenie = nazwa + "\\" + nazwa + ".exe < " + nazwa + "\\" + nazwa + getCommand(i) + ".in > " + nazwa + "\\outy\\" + nazwa + getCommand(i) + ".out";
		cout << "polecenie = " << polecenie << endl;
		system( polecenie.c_str() );


	}


	return 0;
}












