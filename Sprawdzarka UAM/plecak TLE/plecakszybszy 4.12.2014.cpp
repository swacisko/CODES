//#include<stdio.h>
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
//#include<cmath>
//#include<queue>
//#include<time.h>
//#include<string.h>
//#include<fstream>
//#include<sstream>
#include<algorithm>
//#include<conio.h>
//#include<iomanip>

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
typedef vector< VPII > VVPII;

int N,waga;
VVPII tab;
VI M;
VPII V;


/*
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
*/


int main(){
	ios_base::sync_with_stdio(0);
	
	
	int l_zest;
	cin >> l_zest;
	while( l_zest-- ){
		cin >> N >> waga;
		
		V = VPII(N);
		tab = VVPII( waga+1 ); // tab[a][i].ST - to jest maxymalna wartosc upakowania maksymalnego o wadze a dla przedmiotu nr tab[a][i].ND;
		tab[0].PB( MP(0,0) );
		
		M = VI(waga+1, -INF);
						
		
		FOR(i,1,N) cin >> V[i-1].ST >> V[i-1].ND;
		sort( ALL(V) );
		reverse( ALL(V) ); // teraz mam w kolejnosci nierosnacych wag
		V.insert( V.begin(), MP(0,0) );
		
	//	cout << "Oto twoje posortowane przedmioty" << endl;
	//	REP( i,SIZE(V) ) cout << V[i].ST << ", " << V[i].ND << endl;
	//	ENDL(2);
		
		
		M[0] = 0;
		FOR(i,1,N){ // dla kazdego przedmiotu
		//	cout << "Rozwazam przedmiot nr " << i << " -> (" << V[i].ST << "," << V[i].ND << ")" << endl;
			FORD( a,waga,0 ){				
			//	tab[a][i] = M[a]; // przepisuje 'maksimum'
				int val = M[a];
				
			//	if( M[a] != -INF || !tab[a].empty() ) cout << "\ta = " << a << flush;
				
			//	if( M[a] != -INF ) cout << "\tM["<<a<<"] = " << M[a] << endl;
			//	if( !tab[a].empty() )cout << "\tOto wszystkie pary != -INF" << endl;
			//	REP( r,SIZE(tab[a]) ) cout << "\t\t" << tab[a][r].ST << "," << tab[a][r].ND << endl;
				
				
				if( a + V[i].ST > waga ){
					tab[a].clear();
					continue;
				}
				
				REP( k, SIZE(tab[a]) ){
					if( a + V[i].ST <= waga ){
						tab[ a + V[i].ST ].PB( MP( tab[a][k].ST + V[i].ND, tab[a][k].ND  ) ); //
					//	cout << "\t\t\tpush_backuje pare " << tab[a][k].ST + V[i].ND << " , " << tab[a][k].ND << endl;
						 
						if( M[ a + V[i].ST ] < tab[a][k].ST + V[i].ND ) M[ a + V[i].ST ] = tab[a][k].ST + V[i].ND; // tutaj zapisuje maksimum dla danej wagi 
						
						
						
					}
					
				}
				
				tab[a].clear();
				if( val != -INF ) tab[a].PB( MP( val,i ) );
				
				
			}
			
		//	wypisz(i);
			
		}
		
		
		int res = -INF;
		REP( a,waga+1 ){
			REP( k, SIZE(tab[a]) ) if( tab[a][k].ND == 0 ) if( res < tab[a][k].ST ) res = tab[a][k].ST;			
		}
		
		REP( a,waga+1 ){
			REP( k,SIZE(tab[a]) ){
				if( a + V[ tab[a][k].ND ].ST > waga ){
				//	cout << "to moze byc upakowanie maksymalne:  a = " << a << "  k = " << k << endl;
					if( res < tab[a][k].ST ){
						res = tab[a][k].ST;
					}
					
					
				}
			}
			
		}
		
	//	ENDL(2);
		cout << res << endl;
		
		
		
		
	}
	
	return 0;
}












