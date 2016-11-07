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

int N,M,K,a,b,c,y,t,w,l_zest;
const int INF = 1000000001;
const double EPS = 10e-9;
typedef vector<double> VD;
typedef pair<double,int> PDI;
typedef pair<double, double> PDD;
typedef vector<bool> VB;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef vector<PII> VPII;
typedef map< PII, bool > MPIIB;
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;

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


int main(){
	
	cin >> l_zest;
	while(l_zest--){
		
		cin >> N >> M; // ilsoc wierzcholkow i krawedzi
		TOPO::deg = VI(N,0);
		TOPO::kol.clear();
		TOPO::V = VVI(N);
		TOPO::was = VB(N,0);
		
		REP(i,M){
			cin >> a >> b;
			TOPO::V[a-1].PB(b-1);
			TOPO::deg[b-1]++;
		}
		
		TOPO::topoSort();
		
		
		FOREACH(it,TOPO::kol) cout << *it + 1 << " ";
		cout << endl;
		
		VI l_path = TOPO::longestPath();
		FOREACH(it,l_path) cout << *it + 1 << " ";
		cout << endl;
		
		
	}
	
	
	
	
	
	
	
	
}










