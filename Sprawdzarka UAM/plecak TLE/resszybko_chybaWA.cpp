//#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
//#include<map>
//#include<complex>
//#include<stack>
//#include<list>
//#include<bitset>
#include<set>
//#include<iterator>
#include<cmath>
//#include<queue>
#include<time.h>
#include<string.h>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<conio.h>
#include<iomanip>

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
typedef vector<string> VS;
typedef vector< VS > VVS;

int N,waga;
VVI tab;
VI M;
VPII V;



void wypisz( int ii ){
	cout << "Po rozwazeniu przedmiotu nr " << ii << " = (" << V[ii].ST << "," << V[ii].ND << ") " << " tablica wyglada nastpujaco:" << endl;
	cout << setw(5) << "" << flush;
	REP( i,N+2 ) cout << setw(5) << i << " " << flush;
	cout << setw(5) << "M" << flush;
	ENDL(1);
	REP( i,SIZE(tab) ){
		cout << setw(5) << i << "  " << flush;
		REP( k, SIZE(tab[i]) ){
			if( tab[i][k] != -INF ) cout << setw(5) << tab[i][k] << " " << flush;
			else cout << setw(5) << "-INF" << " " << flush;
		} 
		
		if( M[i] != -INF ) cout << setw(5) << M[i] << endl;
		else cout << setw(5) << "-INF" << endl;
	}
	
	ENDL(2);
}



int main(){
	
	
	int l_zest;
	cin >> l_zest;
	while( l_zest-- ){
		cin >> N >> waga;
		
		V = VPII(N);
		tab = VVI( waga+1, VI(N+2,-INF) );
		M = VI(waga+1, -INF);
						
		
		FOR(i,1,N) cin >> V[i-1].ST >> V[i-1].ND;
		sort( ALL(V) );
		reverse( ALL(V) ); // teraz mam w kolejnosci nierosnacych wag
		V.insert( V.begin(), MP(0,0) );
		
	//	cout << "Oto twoje posortowane przedmioty" << endl;
	//	REP( i,SIZE(V) ) cout << V[i].ST << ", " << V[i].ND << endl;
	//	ENDL(2);
		
		tab[0][0] = 0;
		M[0] = 0;
		FOR(i,1,N){ // dla kazdego przedmiotu
			FORD( a,waga,0 ){
				tab[a][i] = M[a]; // przepisuje 'maksimum'
			//	if( a + V[i].ST > waga ) continue; // jesli nie moge dolozyc kolejnego klocka, to koniec
				
				FORD( k, i-1, 0 ){
					if( tab[a][k] != -INF && a + V[i].ST <= waga ){
						tab[ a + V[i].ST ][k] = tab[a][k] + V[i].ND; // 
						if( M[ a + V[i].ST ] < tab[ a+V[i].ST ][k] ) M[ a + V[i].ST ] = tab[ a+V[i].ST ][k]; // tutaj zapisuje maksimum dla danej wagi 
						
						
						
					}
					
					tab[a][k] = -INF;
					
				}
				
				
			}
			
		//	wypisz(i);
			
		}
		
		
		int res = -INF;
		REP( a,waga+1 ) if( res < tab[a][0] ) res = tab[a][0];
		
		REP( a,waga+1 ){
			REP( k,N+1 ){
				if( tab[a][k] != -INF && a + V[k].ST > waga ){
				//	cout << "to moze byc upakowanie maksymalne:  a = " << a << "  k = " << k << endl;
					if( res < tab[a][k] ){
						res = tab[a][k];
					}
					
					
				}
			}
			
		}
		
	//	ENDL(2);
		cout << res << endl;
		
		
		
		
	}
	
	
}












