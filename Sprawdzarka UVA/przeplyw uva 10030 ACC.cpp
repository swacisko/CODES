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
#define WRITE( V ) FOREACH(it,V) cout << *it << ", "; cout << endl;
#define WRITE_ALL(V,s)  cout << s << endl;  REP( i,SIZE(V) ){ cout << i + 1 << ":  "; FOREACH(it,V[i]) cout << (*it) +1 << ", "; cout << endl;     }
#define WRP(p) p.ST << " " << p.ND
#define CLEAR( dst,quant ) memset( dst,0, (quant)*sizeof( __typeof(*dst) ) );
#define WAR if( show_help )
#define ENDL(x) REP(crow,(x)) cout << endl;

const bool show_help = 0;
const int INF = 1000000001;
int N,M,K,a,b,y,t,w,l_zest; long long c;
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

VVI V; // ten wektor nalezy uzupelnic przed wywolaniem MaxFlow - to jest Graf, dla ktorego chcemy znalezc przeplyw
typedef LL wtype;
typedef vector<wtype> VWT;
typedef vector<VWT> VVWT;
VVWT W; // wagi w tej macierzy( o wymiarach SIZE(V) x SIZE(V) ) nalezy uzupelnic przed wywoalaniem funkcji MaxFlow


wtype MAX_FLOW;
VVWT kraw; // wektor nasycenia danej krawedzi
VB canReach; // wektor uzywany przy blockFlowDfs, do sprawdzania czy z danego wierzcholka da sie dojsc do ujscia, sluzy tylko w celu (wzglednej) optymalizacji czasowej

VVI V2; // tu jest przechowywany graf warstwowy...

VVI transpose( VVI & v ){ // funkcja zwraca graf transponowany
	VVI g( SIZE(v) );
	REP( i,SIZE(v) )	REP( k,SIZE(v[i]) )	g[ v[i][k] ].PB(i);
	return g;
}
// przy tworzeniu grafu warstwowego moag mi sie utworzyc niechciane galezie, wypadaloby je wiec usunac
// UWAGA, jesli badamy przeplyw dla gafu skierowanego(tzn dodajemy krawedzie tylko w jedna strone, to nie mozna w LayerBFS wywolac tej funkcji!
void remove_branches( int beg,int end ){
	VVI v = transpose( V2 ); // transponuje graf
	VI neigh(1,end);
	VB was(SIZE(V),false); was[end] = true;
	
	REP(i,SIZE(neigh)) REP(k,SIZE( v[neigh[i]] ) ) if( !was[ v[neigh[i]][k] ] ){
		was[ v[neigh[i]][k] ] = true; // ide bfsem i sprawdzam, do ktorych wierzcholkow da sie dojsc z ujscia w grafie transponowanym
		neigh.PB( v[neigh[i]][k] );
	}
	v = V2; V2 = VVI(SIZE(V));
	neigh = VI(1,beg);
	VB wasIn(SIZE(V),false); wasIn[beg] = true;
//	VVWT wl = W2; W2 = VVWT(SIZE(W));
	
	REP(i,SIZE(neigh)) REP(k,SIZE(v[neigh[i]])) if( was[ v[neigh[i]][k] ] ){ // jesli z wierzcholka v[neigh[i]][k] ( czyli w pierwszym grafie warstwowym)  da sie dojsc do ujscia to...
		V2[neigh[i]].PB( v[neigh[i]][k] );
	//	W2[neigh[i]].PB( wl[neigh[i]][k] );
		if( !wasIn[ v[neigh[i]][k] ] ) neigh.PB( v[neigh[i]][k] );
		wasIn[ v[neigh[i]][k] ] = true;
	}
}

// BFS wyznaczajacy graf warstwowy. Jest to graf skierowany, przechowywany w V2 i W2
bool LayerBFS( int beg, int end ){
	VI dist(SIZE(V),INF); // odleglosc od zrodla przy tworzeniu garfu warstwowego
	dist[beg] = 0;
	
	V2 = VVI(SIZE(V)); // to jest potrzebne do stworzenia grafu warstwowego	
	VI neigh( 1,beg ); // vector dla BFSa - kolejne wierzcholki
//	W2 = VVWT(SIZE(W));
	
	bool found = false;
	REP(i,SIZE(neigh)){
		if( found && dist[ neigh[i] ] > dist[ neigh[i-1] ] ) break; // uwaga!! nie powinno sie zdarzyc, ze odleglosc bedzie rowna 0, ale moze... jesli beg == end to SIGSEGV wyleci
		REP(k,SIZE( V[neigh[i]] )){
			if( V[neigh[i]][k] == end && W[ neigh[i] ][ V[neigh[i]][k] ] > 0 ) found = true;
			if( dist[ V[neigh[i]][k] ] == INF && W[ neigh[i] ][ V[neigh[i]][k] ] > 0 ){ // jesli jeszcze nie bylem w tym wierzcholku
				dist[ V[neigh[i]][k] ] = dist[ neigh[i] ] + 1;
				V2[ neigh[i] ].PB( V[neigh[i]][k] ); // to jest graf skierowany, weic tylko jedna krawedz dodaje
			//	W2[ neigh[i] ].PB( W[neigh[i]][k] );
				neigh.PB( V[neigh[i]][k] );
			}
			else if( dist[ V[neigh[i]][k] ] == dist[ neigh[i] ] + 1 && W[ neigh[i] ][ V[neigh[i]][k] ] > 0 ){
				V2[ neigh[i] ].PB( V[neigh[i]][k] );
			//	W2[ neigh[i] ].PB( W[neigh[i]][k] );
			}
		}
	}
	
//	cout << "found = " << found << endl;
//	WRITE_ALL(V2,"");  ENDL(2);
	if( !found ) return false; // jesli nie ma sciezki, to zzwroc falsz
	remove_branches( beg,end ); // po wywolaniu tej procedury powinien byc piekny graf warstwowy, bez zbednych galezi, z ktorych nie da sie dojsc do wierzcholka
//	WRITE_ALL(V2,""); ENDL(3);
	return true;
}

/*
// usuwa krawedz skierowana vw z zadanego grafu i z grafu wag
// tej funkcji uzywa sie w blockFlowDfs
void delEd( int v, int w, VVI & G, VVWT & GW ){
	REP(i,SIZE(G[v])) if( G[v][i] == w ){
		G[v].erase( G[v].begin() + i );
		GW[v].erase( GW[v].begin() + i );
		break;
	}
}*/




// wyznaczanie przeplywu blokujacego, minC to minimalny koszt krawedzi na danej sciezce, czyli w grafie warstwowym V2
// minC to minimalny koszt krawedzi podczas szukania sciezki, ale dla ojca wierzcholka num, czyli jesli np num = 1 a minC = 7, to znaczy ze na pewnej sciezce na ktorej jest num
// znajduje sie krawedz(przed num), ktorej waga jest rowna 7, a pozostale krawedzi przed num maja wieksze wagi
bool blockFlowDfs( int num, int end, wtype minC, wtype & ile ){
WAR	cout << "Jestem na poczatku blockFlow, num = " << num+1 << "   minC = " << minC << endl;
	if( num == end ){ ile = INF; MAX_FLOW += minC; return true;	}
	if( !canReach[num] ) return false;
	wtype suma = 0,t;
	
	REP(i, SIZE( V2[num] ) ){
		t = min( minC - suma, W[num][ V2[num][i] ] );
WAR		cout << "\tJestem przed ifem, minC = " << minC << "  suma = " << suma << "   minC - suma = " << minC - suma << "   num = " << num+1 << "  i = " << i << "   W["<<num+1<<"]["<<V2[num][i]+1<<"] = " << W[num][ V2[num][i] ] << "   t = " << t << endl << endl;
		
		if( blockFlowDfs( V2[num][i],end, t, ile ) ){
			t = min( t,ile ); // zawsze ile < t poza przypadkiem, gdy V2[num][i] == end
WAR			cout << "\t\tJestem w ifie w blockFlow, num = " << num+1 << "   t = " << t << "   minC = " << minC << "  suma = " << suma << endl;
		//	cout << "\t\t\t\t\t\t\tPLAPAL" << endl;
			kraw[num][ V2[num][i] ] += t;
			kraw[ V2[num][i] ][num] -= t;
			suma += t;
		//	cout << "\t\t\t\t\tTRATATA" << endl;
			W[num][ V2[num][i] ] -= t;
			W[ V2[num][i] ][num] += t;
		/*	if( W[num][ V2[num][i] ] == 0 ){
			//	delEd( num, V2[num][i],V,W );
			//	delEd( num, V2[num][i], V2,W2 );
				i--;
			}*/
			ile = suma;
		//	cout << "\t\t\t\t\tBLABLA" << endl;
			if( suma == minC ) return true;
		}
	}
	canReach[num] = false;
	return ( ile = suma ) > 0;	
}


wtype MaxFlow( int beg, int end ){
	kraw = VVWT( SIZE(W), VWT( SIZE(W),0 ) );
//	WRITE_ALL(W,"Wagi w macierzy W");
	
	wtype ile = 0;
	MAX_FLOW = 0;
	while( LayerBFS( beg,end ) ){
//		WRITE_ALL(V2,"Graf Warstwowy"); ENDL(2);
//		REP(i,SIZE(W)){ cout << i+1 << ":  "; REP(k,SIZE(W[i])) cout << W[i][ k ] << " "; cout << endl; }
		canReach.clear();
		canReach = VB( SIZE(V), true );
		blockFlowDfs( beg,end,INF,ile );		
	} 
	return MAX_FLOW;
}








int main(){
	int ile = 0;
	while( cin >> N ){	
	//	if( ile++ ) cout << endl;
		V = VVI(2*N);
		W = VVWT( 2*N+2, VWT(2*N+2,0) );
		
		VI cap(N);
		REP(i,N) cin >> cap[i];
		REP(i,N){
			V[N+i].PB(i);
			V[i].PB(N+i);
			W[N+i][i] = cap[i];
		}
		
		cin >> M;
		REP(i,M){
			cin >> a >> b >> c;
			V[a-1].PB( N+b-1);
			V[N+b-1].PB(a-1); // czy to musze dodawac?
			W[a-1][N+b-1] = c;
		}
		
		int B,D;
		cin >> B >> D;
		
		V.PB( VI() );
		V.PB( VI() );
		int source = SIZE(V)-2, fend = SIZE(V)-1;
		
	//	cout << "B = " << B << "   D = " << D << "   source = " << source << "   SIZE(V) = " << SIZE(V) << "   fend = " << fend << "   SIZE(W) = " << SIZE(W) <<  endl;
		
		REP(i,B){
			cin >> a;
			V[source].PB( N+a-1 );
			W[source][N+a-1] = INF;
		}
		
	//	cout << "Wczytalem B danych" << endl;
		
		REP(i,D){
			cin >> a;
			V[a-1].PB(fend);
			W[a-1][fend] = INF;
		}
		
	//	WRITE_ALL(V,"Graf V");
	//	WRITE_ALL(W,"Graf W");
		
		cout << MaxFlow( source, fend ) << endl;
	
	}
	
	return 0;
}












