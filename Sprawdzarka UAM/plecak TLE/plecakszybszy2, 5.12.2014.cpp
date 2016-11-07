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
//typedef vector<double> VD;
//typedef vector< VD > VVD;
typedef pair<double,int> PDI;
typedef pair<double, double> PDD;
//typedef vector<bool> VB;
typedef long long LL;
//typedef vector<int> VI;
//typedef vector< VI > VVI;
typedef pair<int,int> PII;
//typedef pair<LL,LL> PLL;
//typedef vector<LL> VLL;
//typedef vector<VLL> VVLL;
typedef vector<PII> VPII;
//typedef vector<string> VS;
//typedef vector< VS > VVS;
//typedef vector< VPII > VVPII;

int N,waga;
PII tab[8010][1010];
int M[8010];
PII V[1010];


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
	
	REP( a,8005 ) REP( k,1005 ) tab[a][k] = MP( -INF,0 );
	REP( i,8005 ) M[i] = -INF;
	REP( i,1005 ) V[i] = MP( 0,0 );
	
	int l_zest;
	cin >> l_zest;
	while( l_zest-- ){
		cin >> N >> waga;
		
	//	cout << "TABLICA.ST" << endl;
	//	REP( i,waga+1 ){
	//		cout << "i = " << i << "  " << flush;
	//		REP( k,N+2 ) cout << setw(5) << tab[i][k].ST << " " << flush;
	//		cout << endl;
	//	}
	
	//	REP( a,8005 ) REP( k,1005 ) tab[a][k] = MP( -INF,0 );
	//	REP( i,8005 ) M[i] = -INF;
		REP( i,1005 ) V[i] = MP( 0,0 );
				
		
		tab[0][1] = MP( 0,0 );
		REP(i,waga+1) tab[i][0].ST = 0;
		tab[0][0].ST = 1;
		
		REP( i,waga+1 ) M[i] = -INF;
		M[0] = 0;
		
								
	//	VPII D(N);
		FOR(i,1,N) cin >> V[i].ST >> V[i].ND;		
		sort( V+1,V+N+1 );
		reverse( V+1,V+N+1 ); // teraz mam w kolejnosci nierosnacych wag
		//D.insert( D.begin(), MP(0,0) );
		
		//FOR( i,1,N ) V[i] = D[i];
		V[0].ST = N;
		
	//	cout << "Oto twoje posortowane przedmioty" << endl;
	//	FOR( i,1,V[0].ST ) cout << V[i].ST << ", " << V[i].ND << endl;
	//	ENDL(2);
		
		
		FOR(i,1,N){ // dla kazdego przedmiotu
		//	cout << "Rozwazam przedmiot nr " << i << " -> (" << V[i].ST << "," << V[i].ND << ")" << endl;
			FORD( a,waga,0 ){				
				int val = M[a];
				
			//	if( M[a] != -INF || tab[a][0].ST > 0 ) cout << "\ta = " << a << flush;
				
			//	if( M[a] != -INF ) cout << "\tM["<<a<<"] = " << M[a] << endl;
			//	if( tab[a][0].ST > 0 )cout << "\t\ttab["<<a<<"][0].ST = " << tab[a][0].ST << "\tOto wszystkie pary != -INF" << endl;
			//	FOR( r,1,tab[a][0].ST ) cout << "\t\t" << tab[a][r].ST << "," << tab[a][r].ND << endl;
				
				
				if( a + V[i].ST > waga ){
					tab[a][0].ST = 0;
					continue;
				}
				
				FOR( k,1, tab[a][0].ST ){
					if( a + V[i].ST <= waga ){
						//tab[ a + V[i].ST ].PB( MP( tab[a][k].ST + V[i].ND, tab[a][k].ND  ) ); //
						
						tab[ a + V[i].ST ][ tab[a+V[i].ST][0].ST + 1 ] = MP( tab[a][k].ST + V[i].ND, tab[a][k].ND  );
						tab[ a+V[i].ST ][0].ST++;
					//	cout << "\t\t\tpush_backuje pare " << tab[a][k].ST + V[i].ND << " , " << tab[a][k].ND << endl;
						 
						if( M[ a + V[i].ST ] < tab[a][k].ST + V[i].ND ) M[ a + V[i].ST ] = tab[a][k].ST + V[i].ND; // tutaj zapisuje maksimum dla danej wagi 
						
						
						
					}
					
				}
				
				tab[a][0].ST = 0;
				//tab[a].PB( MP( val,i ) );
				if( val != -INF ) {
					tab[a][ 1 ] = MP( val,i );
					tab[a][0].ST = 1;
				}
				
				
			}
			
		//	wypisz(i);
			
		}
		
		
		int res = -INF;
		REP( a,waga+1 ){
			FOR( k,1, tab[a][0].ST ) if( tab[a][k].ND == 0 ) if( res < tab[a][k].ST ) res = tab[a][k].ST;			
		}
		
		REP( a,waga+1 ){
			FOR( k,1,tab[a][0].ST ){
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












