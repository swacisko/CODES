//#include<cstdio>
#include<iostream>
#include<vector>
//#include<string>
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

int N,M;
PII V[1001];
int tab[8001];

int RES;


// N w parametrze tej funkcji oznacza, do ktorego przedmiotu wlacznie moge rozpatrywac przedmioty podczas upakowan :)
// M zas oznacza, poczawszy od jakiej wagi bede mogl sprawdzac, czy upakowanie jest maksymalne ;d
// suma_val oznacza sume wartosci przedmiotow od N+1 do ::N+1
void plecak( int N, int M, int suma_val ){
//	cout << "::N = " << ::N << "  ::M = " << ::M << "  N = " << N << "  M = " << M << endl;
//	cout << "\tsuma_val = " << suma_val << endl;
	
	if( N == 0 && M >= 0 ){
		if( RES < suma_val ) RES = suma_val;
	}
	else if( M == 0 ) if( RES < suma_val ) RES = suma_val;
	if( N <= 0 || M <= 0 ) return;	
	
	
	
	REP( i,::M+1 ) tab[i] = -INF;
	
	FOR(i,1,N){
		FORD( k,::M - V[i].ST, 0 ){
			if( k == 0 ){ // jesli jest to pierwszy przedmiot w plecaku, to zawsze moge probowac go dolozyc
				if( tab[ V[i].ST ] < V[i].ND ) tab[ V[i].ST ] = V[i].ND;
			}
			else if( tab[k] != -INF ){ // jesli dokladam przedmiot to tylko do tych wag, ktore juz cos w sobie maja
				if( tab[ k + V[i].ST ] < tab[k] + V[i].ND ) tab[ k + V[i].ST ] = tab[k] + V[i].ND;
			}			
		}	
	}
	
/*	cout << "\tOto plecak:" << endl << "\t";
	FOR( i,1,::M){
		cout << tab[i] << "   ";
	}
	ENDL(1);
*/	
	FOR( i, max( 0, M-V[N+1].ST ), M-1 ){ 
//		cout << "\tRES = " << RES << "  i = " << i << "  tab[i] = " << tab[i] << endl;  
		if( RES < suma_val + tab[i] ) RES = suma_val + tab[i]; // kazde z upakowan o tej masie jest upakowaniem kaksymalnym, wiec moge je porownac do wszystkich innych
		// upakowan maksymalnych
	}
	
	
	
}


bool comparator( const PII & p1, const PII & p2 ){
	if( p1.ST > p2.ST ) return true;
	else if( p1.ST < p2.ST ) return false;
	else if( p1.ND > p2.ND ) return true;
	else return false;
}



int main(){
	ios_base::sync_with_stdio(0);
	
	int l_zest;
	cin >> l_zest;
	while( l_zest-- ){
		RES = -INF;
		cin >> N >> M;
		
		V[0].ST = V[0].ND = N;
		FOR(i,1,N) cin >> V[i].ST >> V[i].ND;
		
		sort( V+1, V+N+1, comparator );
		
	//	cout << "Oto posortowane przedmioty:" << endl;
	//	FOR(i,1,N) cout <<WRP(V[i]) << endl;
		
		int S = 0,s=0; // to jest na wypadek, gdyby wszystkie przedmioty wchodzily do plecaka i zostawialy jeszcze jakies miejsce wolne...
		FOR(i,1,N){
			s += V[i].ST;
			S += V[i].ND;
			if( i == N ){
				if( s <= M ){
					RES = S;
				}
			}
		}
		
		int T = N;
		int waga;
		int suma = 0;
		int suma_val = 0;
		
		while( T >= 1 ){ // to jest wlasciwa petla, ktora zostanie wykonana maksimum pesymistycznie 1*sqrtN razy, w kazdym obiegu zostanie wywolany plecak :)
			plecak( T-1, M - suma + 1, suma_val );		
			
			waga = V[T].ST;
			while( T >= 1 && V[T].ST == waga ){
				suma_val += V[T].ND;
				suma += V[T].ST;
				T--;
								
			}
		}  
		
		cout << RES << endl;
		
		
	}
	
	
	return 0;
}












