#include<cstdio>
#include<iostream>
#include<vector>
#include<string>
#include<map>
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
typedef vector< PDD > VPDD;
typedef vector<bool> VB;
typedef long long LL;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;



int matches( char beg, char end ){	
	if(  beg == '[' && end == ']' ) return 1;
	else if( beg == '[' && end == '?' ) return 1;
	else if( beg == '?' && end == ']' ) return 1;
	else if( beg == '(' && end == ')' ) return 1;
	else if( beg == '(' && end == '?' ) return 1;
	else if( beg == '?' && end == ')' ) return 1;
	else if( beg == '{' && end == '}' ) return 1;
	else if( beg == '{' && end == '?' ) return 1;
	else if( beg == '?' && end == '}' ) return 1;
	else if( beg == '?' && end == '?' ) return 3;
	else return 0;	  
}

const int MOD = 100000;



int main(){
	
	
	int L;
	cin >> L;
	
	VVLL tab(L, VLL(L,0));
	
	string s;
	cin >> s;
	
	
	
	if( L % 2 == 1 ){
		cout << 0 << endl;
	}
	else{
		for( int DL = 2; DL <= L; DL+=2 ){ // dla ciagow o danej dlugosci
			//cout << "DL = " << DL << endl;
			for(int i=0; i<=L-DL; i++){ // dla kazdej pozycji i podciagu o dlugosci DL
			//	cout << "\ti = " << i << endl;
				
					if( DL == 2 ) tab[i][i+DL-1] += matches(s[i],s[i+DL-1]) ;
					else tab[i][i+DL-1] +=  matches(s[i],s[i+DL-1]) * tab[i+1][i+DL-2];
				
				
				for(int k=i+1; k<=i+DL-2; k+=2){
					//cout << "\t\tk = " << k << endl;
						tab[i][i+DL-1] += matches( s[i], s[k] ) *(k==i+1?1: tab[i+1][k-1] )* tab[k+1][i+DL-1]; // tutaj dodaje wszystkie mozliwe podzialy...					
				}
				
				tab[i][i+DL-1] %= MOD;
				//cout << "\ttab[" << i<< "][" << i+DL-1 << "] = " << tab[i][i+DL-1] << endl;				
			}		
			
		}
		
		cout << tab[0][L-1]%MOD << endl;
	}
	
	

	return 0;
}






