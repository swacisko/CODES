#include<cstdio>
//#include<iostream>
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
#define WRITE( V ){ REP(trx,SIZE(V)) printf( "%d ",V[trx] ); printf("\n"); }
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

int N,M;
VVI V;

namespace SCC{

	VI PostOrder; // PostOrder[i] - numer post_order i-tego wierzcholka
	VVI V;
	VVI Comps; // Copms[i] - wektor w sklad ktorego wchodza wierzcholki i-tej silnie spojnej skladowej
	VI temp_comp; // wektor tymczasowy, reprezentujacy jedna spojna skladowa podczas jednej serii rekurencji Add_PO_DFS
	
	VB was; // czy juz bylem w danym wierzcholku
	
	void PO_DFS( int num, int & ponum ){ // funkcja wyznaczajaca numery Post_Order
		was[ num ] = true;
		REP( i,SIZE(V[num]) ) if( !was[ V[num][i] ] ) PO_DFS( V[num][i], ponum );
		PostOrder[ num ] = ponum++; // tutaj zapisuje numer PostOrder i zwiekszam ponum. Jest on przesylany przez referencje, 
										//wiec w innych rekurencjach tez bedzie zwiekszony
	}
	
	void Add_PO_DFS( int num ){ // Funkcja dodajaca do tymczasowej silnie spojnej skladowej kolejne weirzcholki
		was[num] = true;
		temp_comp.PB( num );
	//	printf( "Jestem w wierzcholku %d i dodaje go do temp_comp\n",num );
		REP(i, SIZE(V[num]) ) if( !was[ V[num][i] ] ) Add_PO_DFS( V[num][i] );
	}
	
	VVI transpose( VVI & v ){ // funkcja zwraca graf transponowany
		VVI g( SIZE(v) );
		REP( i,SIZE(v) )	REP( k,SIZE(v[i]) )	g[ v[i][k] ].PB(i);
		return g;
	}
	
	void StrConComp(){
		Comps.clear();
		was = VB(N,0);
		PostOrder = VI(N);
		int ponum = 0;
		REP( i,N ) if( !was[i] ) PO_DFS( i,ponum ); // tutaj wyznaczam dla wszystkich wierzcholkow numery PostOrder
		
	//	printf( "Post order:  " ); WRITE(PostOrder);
		
		VI sorted( N ); // tablica sorted[i] oznacza numer wierzcholka o numerze post_order rownym i
		REP( i,N ) sorted[ PostOrder[i] ] = i;
		
		V = transpose( V ); // odwracam graf aby wykonac na nim odpowiednie dfsy
		
	//	printf( "sorted:  " ); WRITE(sorted);
		
		was = VB(N,0);
		FORD( i,N-1,0 ){ // zaczynjac od wierzcholka o najwiekszym numerze PostOrder w odwroconym grafie
			temp_comp.clear();
			if( !was[ sorted[i] ] ) Add_PO_DFS( sorted[i] ); // jesli jeszcze wierzcholek o numerze sorted[i] nie nalezy do spojen skladowej to go dodajemy wraz z cala silnie spojna skladowa
			if( SIZE(temp_comp) ) Comps.PB( temp_comp );
		}
		
		V = transpose( V ); // odwracam graf, aby byl w pozycji poczatkowej
	}


}




void solve(){
	V = VVI(N);
	
	int a,b;
	REP(i,M){
		scanf( "%d %d",&a,&b );
		V[a-1].PB(b-1);
	}
	
	SCC::V = V;
	SCC::StrConComp();
	
	VI ans;
	ans.clear();
	
	VI ext;
	
	REP( i, SIZE( SCC::Comps ) ){
		
		if( SIZE( SCC::Comps[i] ) > 1 ){
			ext.clear();
			
			REP( k, SIZE( SCC::Comps[i] ) ){
				REP( j, SIZE( V[ SCC::Comps[i][k] ] ) ){
					ext.PB( V[ SCC::Comps[i][k] ][j] ); 
				}								
			}
						
			sort( ALL(ext) );
			ext.resize( unique( ALL(ext) ) - ext.begin() );
			if( SIZE(ext) != SIZE( SCC::Comps[i] ) ) continue;
			
			
			REP( k, SIZE( SCC::Comps[i] ) ){
				ans.PB( SCC::Comps[i][k]+1 );		
			}
		}
	}
	
	REP( i, SIZE(V) ){
		if( SIZE(V[i]) == 0 || ( SIZE(V[i]) == 1 && V[i][0] == i ) ){
			//printf( "%d ", i+1 );
			ans.PB( i+1 );
		}
	}
	
	sort( ALL(ans) );
	
	REP( i, SIZE(ans)-1 ) {		
		printf( "%d ",ans[i] );		
	}
	
	if( SIZE(ans) > 0 ) printf( "%d\n", ans.back() );	
	else printf("\n");
	
}

int main(){

    while(1){
		
		scanf( "%d",&N );
		
		if( N == 0 ) break;
		scanf( "%d",&M );
		
		solve();
		
	}

	return 0;
}












