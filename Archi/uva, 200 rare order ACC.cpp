//#include<stdio.h>
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
int N,M,K,a,b,c,y,t,w,l_zest;
const long double EPS = 1e-11;
typedef vector<double> VD;
typedef pair<double,int> PDI;
typedef pair<double, double> PDD;
typedef vector<bool> VB;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;


namespace TOPO{
		
	VVI V;
	VI deg; // ilosc ojcow danego wierzcholka w grafie, jesli ma 0 to mozna go w danym momencie dodac do listy topologicznej
	VI kol; // kol[i] - nr wierzcholka ktory jest i-ty w kolejnosci topologicznej
	VB was; // zapisuje czy juz bylem w danym wierzcholku podczas topologicznego dfsa
	
	void DFS( int num ){
	//	if( deg[num] ) return;
		kol.PB( num );
		was[num] = 1;
		
		REP(i,SIZE( V[num] ) ){
			deg[ V[num][i] ]--;
			if( !deg[V[num][i]] ) DFS( V[num][i] );
		}
	}
	
	// funkcja nie zmienia kolejnosci wierzcholkow w kolejnosci topologicznej, tylko ustawia w wektorze kol ich odpowiednia kolejnosc
	// zmienic caly wektor trzeba to jeszcze przenumerowac
	// dziala w czasie liniowym, bo jest to DFS, ale nie jest to posortowane minimalnie leksykograficznie (do tego potrzeba NlgN
	void topoSort(){
		REP(i,SIZE(V)) if( !deg[i] && !was[i] ) DFS(i); // jesli juz nie ma ojscow  i jeszcze nie bylem w danym wierzcholku, to dodaje go do posortowanych		
	}
	
	// to jest funkcja odpowiedzialna za sortowanie topologiczne...
	void topo_sort(){
		was = VB( SIZE(V),false );
		deg = VI( SIZE(V) );
		REP(i,SIZE(V)) REP(k,SIZE(V[i])) deg[ V[i][k] ]++;
		topoSort();
	}
	
	// funkcja zwraca w wektorze wszystkie wierzcholki znajdujace sie na najdluzszej sciezce w kolejnosci ich wystepowania na tej sciezce
	VI longestPath(){
		topo_sort();
		VI maxy(N,0); // maxy[i] -> dlugosc najdluzszej sciezki zaczynjacej sie w wierzcholku i
		VI ind(N,INF); // ind[i] -> indeks syna na najdluzszej sciezce zaczynajacej sie w i
		
		FORD( i,SIZE(kol)-1,0 ){
			REP( k, SIZE( V[kol[i]] ) ){
				if( maxy[ kol[i] ] < maxy[ V[kol[i]][k] ] + 1 ){ // jesli zwieksza sie dlugosc sciezki, to przypisuje nowa makszymalna dlugosc i nowy index
					maxy[kol[i]] = maxy[ V[kol[i]][k] ] + 1;
					ind[ kol[i] ] = V[kol[i]][k];
				}
			}
		}
		
		int l_max = -1, ind_max = -1; // tutaj znajduje index wierzcholka bedacego poczatkiem najdluzszej sciezki
		REP(i,N){
			if( maxy[i] > l_max ){
				l_max = maxy[i];
				ind_max = i;
			}
		}
		
		VI l_path( 1,ind_max ); // tutaj bedzie sie znajdowala indeksami najdluzsza sciezka
		while( (ind_max = ind[ ind_max ]) < INF )	l_path.PB( ind_max );
		return l_path;
	}


}

using namespace TOPO;

// dla dwoch kolejnych stringow przegladam litera po literce tak dlugo az natrafie na roznice.
//wtedy dodaje odpowiednia krawedz
void addEdge( string s1, string s2 ){
	int p,k;
	for( p = 0, k = 0; p < SIZE(s1) && k < SIZE(s2) && s1[p] == s2[k]; p++, k++ );
	if( p < SIZE(s1) && k < SIZE(s2) ){
		V[ (int)s1[p] - 'A' ].PB( (int)s2[k] - 'A' );
	}
}




int main(){
	ios_base::sync_with_stdio(0);	
	
	
	V = VVI( 'Z' - 'A' + 1 );
	VB was2( 'Z' - 'A' + 1, false );
	
	string s;
	vector<string> vec;
	while( cin >> s ){
		if( s == "#" ) break;
		vec.PB(s);
		REP(i,SIZE(s)) was2[ (int)s[i] - 'A' ] = true;
	}
	
	REP(i,SIZE(vec)-1) FOR( k,i+1,SIZE(vec)-1 ) addEdge( vec[i], vec[k] );
	
	REP(i,SIZE(V)) sort( ALL(V[i]) );
	REP(i,SIZE(V)) V[i].resize( unique( ALL(V[i]) ) - V[i].begin() );
	
//	REP(i,SIZE(vec)) cout << vec[i] << endl;
//	REP(i,SIZE(V)) { REP(k,SIZE(V[i])) cout << V[i][k] << " "; cout << endl; }
	
	topo_sort();
	
	REP(i,SIZE(kol)){
		if( was2[ kol[i] ] ) cout << (char)( 'A' + kol[i] );
	}
	cout << endl;
	
	
	
	
	return 0;
}












