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
#define WRITE( V ){ REP(trx,SIZE(V)) cout << V[trx] << " "; cout << endl; }
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

typedef vector<char> VC;

int ans[30];


VI indent;
VI type;
VI factor;
VC let;
int L;

VB was;

void getResult( int p, int fac ){
	if( p >= L ) return;
	was[p] = true;
	if( type[p] == 1 ){
	//	cout << "p = " << p << "   fac = " << fac << endl;
		ans[ let[p] - 'a' ] += fac;
	}
	else{
		int q = p+1;
		while( q < L && indent[q] > indent[p] && was[q] == false ){
			getResult( q, fac * factor[p] );
			q++;		
		}
		
		if( was[q] == false ) getResult( q,fac );		
	}
}


void solve(){
	
	cin >> L;
	
	vector<string> tab(L);
	
	REP(i,L){
		cin >> tab[i];	
	}
	
	indent = VI(L,0);
	factor = VI(L,0);
	let = VC(L);
	type = VI(L);
	was = VB(L,false);
	
	REP(i,L){
		REP( k, SIZE(tab[i]) ){
			if( tab[i][k] == '.' ) indent[i]++;
			else if( tab[i][k] == 'P' ){
				type[i] = 1;
			}
			else if( tab[i][k] == 'F' ){
				type[i] = 2;
			}
			else if( tab[i][k-1] == 'F' || ( k >= 2 && tab[i][k-2] == 'F' ) ){
				factor[i] *= 10;
				factor[i] += ( (int)(tab[i][k]) - '0'  );	
			//	cout << tab[i][k] << "   factor[i] = " << factor[i] << endl;			
			}
			else{
				let[i] = tab[i][k];
			}
		}		
	}
	
	/*cout << "indent" << endl;
	WRITE(indent);
	cout << "type" << endl;
	WRITE(type);
	cout << "factor" << endl;
	WRITE(factor);
	cout << "let" << endl;
	WRITE(let);
	
	
	
	int MININDENT = INF;
	REP(i,L ){
		MININDENT = min( MININDENT,indent[i] );
	}*/
	
	REP(i,30) ans[i] = 0;
	
	REP( i,L ){
		if( was[i] == false ) getResult(i,1);
	 }
	
	REP(i,30){
		if( ans[i] != 0 ){
			cout << (char)('a' + i) << " " << ans[i] << endl; 
		}
		
	}
	
	
	
	
}

int main(){
	ios_base::sync_with_stdio(0);
	

    solve();


	return 0;
}






/*


5
Px
Py
F3
..Px
..Pz

*/



