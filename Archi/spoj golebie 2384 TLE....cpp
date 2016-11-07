#include<stdio.h>
#include<vector>
#include<string>
#include<cmath>
#include<string.h>
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
typedef int wtype;
typedef vector<wtype> VWT;
typedef vector<VWT> VVWT;

	VVI V; // ten wektor nalezy uzupelnic przed wywolaniem MaxFlow - to jest Graf, dla ktorego chcemy znalezc przeplyw
	VVWT W; // wagi w tej macierzy( o wymiarach SIZE(V) x SIZE(V) ) nalezy uzupelnic przed wywoalaniem funkcji MaxFlow	
	wtype MAX_FLOW;
	VVWT kraw; // wektor nasycenia danej krawedzi
	VB canReach; // wektor uzywany przy blockFlowDfs, do sprawdzania czy z danego wierzcholka da sie dojsc do ujscia, sluzy tylko w celu (wzglednej) optymalizacji czasowej	
	VVI V2; // tu jest przechowywany graf warstwowy...	
	VI dist;
	VI neigh;
	
	bool LayerBFS( int beg, int end ){
	//	VI dist(SIZE(V),INF); // odleglosc od zrodla przy tworzeniu garfu warstwowego
		fill( ALL(dist),INF );
		dist[beg] = 0;
		
	//	V2 = VVI(SIZE(V)); // to jest potrzebne do stworzenia grafu warstwowego	
		REP(i,SIZE(V2)) V2[i].clear();
	//	VI neigh( 1,beg ); // vector dla BFSa - kolejne wierzcholki
		neigh.clear();
		neigh.PB(beg);
		
		bool found = false;
		REP(i,SIZE(neigh)){
			if( found && dist[ neigh[i] ] > dist[ neigh[i-1] ] ) break; // uwaga!! nie powinno sie zdarzyc, ze odleglosc bedzie rowna 0, ale moze... jesli beg == end to SIGSEGV wyleci
			REP(k,SIZE( V[neigh[i]] )){
				if( V[neigh[i]][k] == end && W[ neigh[i] ][ V[neigh[i]][k] ] > 0 ) found = true;
				if( dist[ V[neigh[i]][k] ] == INF && W[ neigh[i] ][ V[neigh[i]][k] ] > 0 ){ // jesli jeszcze nie bylem w tym wierzcholku
					dist[ V[neigh[i]][k] ] = dist[ neigh[i] ] + 1;
					V2[ neigh[i] ].PB( V[neigh[i]][k] ); // to jest graf skierowany, weic tylko jedna krawedz dodaje
					neigh.PB( V[neigh[i]][k] );
				}
				else if( dist[ V[neigh[i]][k] ] == dist[ neigh[i] ] + 1 && W[ neigh[i] ][ V[neigh[i]][k] ] > 0 ){
					V2[ neigh[i] ].PB( V[neigh[i]][k] );
				}
			}
		}
		if( !found ) return false; // jesli nie ma sciezki, to zzwroc falsz
		// UWAGA UWAGA, funkcja remove_branches moze powodowac WA! trzeba to zmienic, albo zostawic bez :)
		return true;
	}
	bool blockFlowDfs( int num, int end, wtype minC, wtype & ile ){
//	WAR	cout << "Jestem na poczatku blockFlow, num = " << num+1 << "   minC = " << minC << endl;
		if( num == end ){ ile = INF; MAX_FLOW += minC; return true;	}
		if( !canReach[num] ) return false;
		wtype suma = 0,t;
		
		REP(i, SIZE( V2[num] ) ){
			t = min( minC - suma, W[num][ V2[num][i] ] );
			if( blockFlowDfs( V2[num][i],end, t, ile ) ){
				t = min( t,ile ); 
				kraw[num][ V2[num][i] ] += t;
				kraw[ V2[num][i] ][num] -= t;
				suma += t;
				W[num][ V2[num][i] ] -= t;
				W[ V2[num][i] ][num] += t;
				ile = suma;
				if( suma == minC ) return true;
			}
		}
		canReach[num] = false;
		return ( ile = suma ) > 0;	
	}	
	
	wtype MaxFlow( int beg, int end ){
		V2 = VVI(SIZE(V));
		dist = VI(SIZE(V),INF);
		kraw = VVWT( SIZE(W), VWT( SIZE(W),0 ) );
		wtype ile = 0;
		MAX_FLOW = 0;
		canReach = VB(SIZE(V));
		while( LayerBFS( beg,end ) ){
		//	canReach.clear();
			//canReach = VB( SIZE(V), true );
			fill( ALL(canReach),true );
			blockFlowDfs( beg,end,INF,ile );		
		} 
		return MAX_FLOW;
	}	
	VI bipartition; // 2 jesli wierzcholek nalezy do drugiej skladowej, 1 jesli nalezy do pierwszej
	
	inline bool bipartDfs( int num, int part ){
		bipartition[ num ] = part;
		REP(i,SIZE(V[num])){
			if( bipartition[ V[num][i] ] == part ) return false;
			else if( !bipartition[ V[num][i] ] ) if( !bipartDfs( V[num][i], (part%2)+1 ) ) return false;
		}
		return true;
	}
	
	inline bool BiPart(){
		bipartition = VI(SIZE(V),0);
		REP(i,SIZE(V)) if( !bipartition[i] ) if( !bipartDfs( i,1 ) ) return false;
		return true;
	}
	
	int MaxMatch(){
		if( !BiPart() ) return 0;
		V.PB( VI() ); // zrodlo
		V.PB( VI() ); // ujscie
		
		W = VVWT(SIZE(V), VWT(SIZE(V),0));
		REP(i,SIZE(V)-2){
			if( bipartition[i] == 1 ){
				V[ SIZE(V)-2 ].PB(i);
				W[ SIZE(V)-2 ][i] = 1;
				REP(k,SIZE(V[i])) W[ i ][ V[i][k] ] = 1;
			}
			else{
				V[i].PB( SIZE(V)-1 );
				W[i][ SIZE(V)-1 ] = 1;
			}
		}
	
		wtype res = MaxFlow( SIZE(V)-2, SIZE(V)-1 );
		return (int)res;
	}

int main(){
	int n,m;
	//cin >> n >> m;
	scanf("%d %d",&n,&m);
	
	V = VVI( n+m );
	int ile;
	int a;
	REP(i,n){
	//	cin >> ile;
		scanf("%d",&ile);
		REP(k,ile){
		//	cin >> a;
			scanf("%d",&a);
			V[i].PB(n+a-1);
			V[n+a-1].PB(i);
		}
	}
	
//	cout << MaxMatch() << endl;
	int wynik = MaxMatch();
	printf( "%d\n",wynik );	
	
}












