#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<complex>
#include<stack>
#include<list>
#include<set>
#include<bitset>
#include<set>
#include<iterator>
#include<cmath>
#include<queue>
#include<time.h>
#include<string.h>
#include<fstream>
#include<sstream>
#include<algorithm>

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

const bool show_help = 0;
const int INF = 1000000001;
int N,M,K,a,b,c,y,t,w,l_zest;
const long double EPS = 1e-11;
typedef vector<double> VD;
typedef pair<double,int> PDI;
typedef pair<double, double> PDD;
typedef vector<bool> VB;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef map< PII, bool > MPIIB;
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;

// funkcja generuje losowy ciag liczb calkowitych z przedzialu 1-N+2 i zwraca w postaci wektora
VI randSeq( int N ){
	VI V;
	REP( i,N ) V.PB( rand()%(N+2) );
	return V;
}

// funkcja jako parametr przyjmuje ilosc wierzcholkow jakie chcemy miec w drzewie
VVI generateTree( int N ){
	if( N <= 1 ) return VVI(1);
	if( N == 2 ){ VVI V(2); V[0].PB(1); V[1].PB(0); return V;	}
	VI last(N,-1); // ostatnie wystapienie liczby i w kodzie prufera jest na miejscu last[i]
	VI seq = randSeq( N-2 ); // generuje kod prufera
//WAR	{ cout << "Oto twoj kod prufera:   "; WRITE(seq); ENDL(3); }
	FORD( i,SIZE(seq)-1,0 ) if( last[ seq[i] ] == -1 ) last[ seq[i] ] = i;
//WAR { cout << "Oto last:  "; WRITE(last); ENDL(3); }
	int p = 0,t = INF;
	VVI V(N);
	REP(i,SIZE(seq)){
		if( t == INF ) while( ( t = p ) < SIZE(last) && last[p++] != -1 );
		
		V[t].PB( seq[i] );
		V[seq[i]].PB(t);
		last[t] = INF;
		
		t = INF;
		if( i == last[ seq[i] ] ){
			last[ seq[i] ] = -1;
			if( seq[i] < p ){
				last[seq[i]] = INF;
				t = seq[i];
			}
		}
	}
	REP( i,SIZE(last) ) if( last[i] == -1 && i != seq[SIZE(seq)-1] ){ p = i; break;	}
	V[p].PB( seq[ SIZE(seq)-1 ] );
	V[ seq[ SIZE(seq)-1 ] ].PB(p);
	return V;
}

// funkcja jako parametr przyjmuje wektor zawierajacy kod prufera - mozemy sami stworzyc kod prufera i dla niego odtworzyc drzewo
VVI generateTree( VI & code ){
	int N = SIZE(code) + 2;
	if( N == 2 ){ VVI V(2); V[0].PB(1); V[1].PB(0); return V;	}
	VI last(N,-1); // ostatnie wystapienie liczby i w kodzie prufera jest na miejscu last[i]
	VI seq = code;
//WAR	{ cout << "Oto twoj kod prufera:   "; WRITE(seq); ENDL(3); }
	FORD( i,SIZE(seq)-1,0 ) if( last[ seq[i] ] == -1 ) last[ seq[i] ] = i;
//WAR { cout << "Oto last:  "; WRITE(last); ENDL(3); }
	int p = 0,t = INF;
	VVI V(N);
	REP(i,SIZE(seq)){
		if( t == INF ) while( ( t = p ) < SIZE(last) && last[p++] != -1 );
		
		V[t].PB( seq[i] );
		V[seq[i]].PB(t);
		last[t] = INF;
		
		t = INF;
		if( i == last[ seq[i] ] ){
			last[ seq[i] ] = -1;
			if( seq[i] < p ){
				last[seq[i]] = INF;
				t = seq[i];
			}
		}
	}
	REP( i,SIZE(last) ) if( last[i] == -1 && i != seq[SIZE(seq)-1] ){ p = i; break;	}
	V[p].PB( seq[ SIZE(seq)-1 ] );
	V[ seq[ SIZE(seq)-1 ] ].PB(p);
	return V;
}

// dfs do funkcji isTree
bool dfs( int num, int par, VVI & V, VB & was ){
	was[num] = true;
	REP(i,SIZE(V[num])){
		if( V[num][i] != par ){
			if( was[ V[num][i] ] || !dfs( V[num][i], num, V,was ) ) return false;			
		}
	}
	return true;
}
// funkcja sprawdza, czy dany graf jest drzewem
bool isTree( VVI & V ){
	VB was(SIZE(V),0);
	if( !dfs( 0,0,V,was ) ) return false;
	REP(i,SIZE(was)) if( !was[i] ) return false;
	return true;
}


int main(){
	srand( unsigned(time(0)) );
	while( cin >> N ){
		system("cls");
		
		cout << N << endl << endl;
		VVI V = generateTree(N);
		WRITE_ALL(V,"Oto struktura wektorowa twoejgo drzewa:",1);
		
		cout << "Sprawdzenie, czu oby na pewno jest to drzewo: " << isTree( V ) << endl;
	}
	
	
}












