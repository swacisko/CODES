//#include<cstdio>
#include<iostream>
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
#define WRITE( V ){ REP(trx,SIZE(V)) cout << V[trx] << " "; cout << endl; }
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



namespace FLOW{
	
	
	VVI V; // ten wektor nalezy uzupelnic przed wywolaniem MaxFlow - to jest Graf, dla ktorego chcemy znalezc przeplyw
	typedef int wtype;
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
		
		REP(i,SIZE(neigh)) REP(k,SIZE(v[neigh[i]])) if( was[ v[neigh[i]][k] ] ){ // jesli z wierzcholka v[neigh[i]][k] ( czyli w pierwszym grafie warstwowym)  da sie dojsc do ujscia to...
			V2[neigh[i]].PB( v[neigh[i]][k] );
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
	//	remove_branches( beg,end ); // po wywolaniu tej procedury powinien byc piekny graf warstwowy, bez zbednych galezi, z ktorych nie da sie dojsc do wierzcholka
		// UWAGA, algorymt dziala w praktyce szybciej bez wywolania remove_branches(beg,end);
		return true;
	}
	
	// wyznaczanie przeplywu blokujacego, minC to minimalny koszt krawedzi na danej sciezce, czyli w grafie warstwowym V2
	// minC to minimalny koszt krawedzi podczas szukania sciezki, ale dla ojca wierzcholka num, czyli jesli np num = 1 a minC = 7, to znaczy ze na pewnej sciezce na ktorej jest num
	// znajduje sie krawedz(przed num), ktorej waga jest rowna 7, a pozostale krawedzi przed num maja wieksze wagi
	bool blockFlowDfs( int num, int end, wtype minC, wtype & ile ){
//	WAR	cout << "Jestem na poczatku blockFlow, num = " << num+1 << "   minC = " << minC << endl;
		if( num == end ){ ile = INF; MAX_FLOW += minC; return true;	}
		if( !canReach[num] ) return false;
		wtype suma = 0,t;
		
		REP(i, SIZE( V2[num] ) ){
			t = min( minC - suma, W[num][ V2[num][i] ] );
//	WAR		cout << "\tJestem przed ifem, minC = " << minC << "  suma = " << suma << "   minC - suma = " << minC - suma << "   num = " << num+1 << "  i = " << i << "   W["<<num+1<<"]["<<V2[num][i]+1<<"] = " << W[num][ V2[num][i] ] << "   t = " << t << endl << endl;
			
			if( blockFlowDfs( V2[num][i],end, t, ile ) ){
				t = min( t,ile ); // zawsze ile < t poza przypadkiem, gdy V2[num][i] == end
//	WAR			cout << "\t\tJestem w ifie w blockFlow, num = " << num+1 << "   t = " << t << "   minC = " << minC << "  suma = " << suma << endl;
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
	
	// funkcja zwracajaca wartosc maksymalnego przeplywu z zrodla-beg   do ujscia - end
	wtype MaxFlow( int beg, int end ){
		kraw = VVWT( SIZE(W), VWT( SIZE(W),0 ) );
//	WAR	WRITE_ALL(W,"Wagi w macierzy W");
		
		wtype ile = 0;
		MAX_FLOW = 0;
		while( LayerBFS( beg,end ) ){
//	WAR		WRITE_ALL(V2,"Graf Warstwowy");  WAR ENDL(2);
//	WAR		REP(i,SIZE(W)){ cout << i+1 << ":  "; REP(k,SIZE(W[i])) cout << W[i][ k ] << " "; cout << endl; }
			canReach.clear();
			canReach = VB( SIZE(V), true );
			blockFlowDfs( beg,end,INF,ile );		
		} 
		return MAX_FLOW;
	}


}





int M,Z;
VI zwyciestwa;
VI przegrane;
VVI pozostale;

using namespace FLOW;


void readData(){
	cin >> Z >> M;
	zwyciestwa = VI(Z,0);
	przegrane = VI(Z);
	pozostale = VVI( Z, VI(Z));
	REP(i,Z) cin >> zwyciestwa[i] >> przegrane[i];
	
	REP(i,Z)  REP(k,Z)  cin >> pozostale[i][k];				
		
}


bool hasChance( int team ){
//	cout << "team = " << team << endl;
	
	bool chance = false;
	
	V = VVI( Z+2 );
	W = VVWT( Z+2, VWT(Z+2,0));
	
	int zwv0 = M - przegrane[team];
	
//	cout << "zwv0 = " << zwv0 << endl;
	
	int suma_pozostale = 0;
	REP(i,Z){
		REP(k,Z){
			if( i != team && k != team ){
				suma_pozostale += pozostale[i][k];
			}
		}
	}
	
	REP(i,Z){
		if(i == team) continue;
		V[0].PB( i+1 );
		V[i+1].PB(Z+1);
		
		FOR(k,i+1,Z-1) if( k != team ) W[0][i+1] += pozostale[i][k];
		if( zwv0 - zwyciestwa[i] >= 0 ) W[i+1][Z+1] = zwv0 - zwyciestwa[i];
		
		FOR(k,i+1,Z-1){
			if( k != team ){
				W[i+1][k+1] = pozostale[i][k];
				
				V[i+1].PB(k+1);
				V[k+1].PB(i+1);
			}
						
		}
		
	}
	
//	cout << "Oto graf V" << endl;
//	WRITE_ALL(V);
	
//	cout << "Oto graf wag W" << endl;
//	WRITE_ALL(W);

//	cout << "suma_pozostale = " << suma_pozostale << endl;
	
	int flow = 0;
	if( (flow = MaxFlow(0,Z+1) ) >= suma_pozostale/2 ) chance = true;
//	cout << "flow = " << flow << endl;
	
	REP(i,Z){
		if( i != team ) if( zwv0 < zwyciestwa[i] ) chance = false;
	}
	
	
	if( !chance ) cout << team+1 << " ";
	return chance;
}


void solve(){
    readData();
   
	bool num = true;
	
	REP(i,Z){
		if( !hasChance(i) ){
			num = false;			
		}
	//	cout << endl << endl;
	}
	
	//cout << "num = " << num << endl;
    
    if( num ) cout << 0 << endl;
    else cout << endl;
    
}

int main(){
	ios_base::sync_with_stdio(0);
	//cout << fixed;
	//cout.precision(2);

    int l_zest;    
    cin >> l_zest;
    
	while( l_zest-- ){
        solve();


	}


	return 0;
}

/*
1
7 6
6 0
0 1
0 1
0 1
0 1
0 1
0 1
0 0 0 0 0 0 0
0 0 1 1 1 1 1
0 1 0 1 1 1 1
0 1 1 0 1 1 1
0 1 1 1 0 1 1
0 1 1 1 1 0 1
0 1 1 1 1 1 0

Odp:  2 3 4 5 6 7


5 10
2 0
3 0
2 1
1 3
0 2
0 5 0 0 1
5 0 1 0 1
0 1 0 4 1
0 0 4 0 1
1 1 1 1 0

Odp:  0


6 11
1 0
2 3
0 3
6 1
1 3
7 0
0 2 1 0 3 0
2 0 3 0 1 0
1 3 0 0 3 0
0 0 0 0 0 4
3 1 3 0 0 0
0 0 0 4 0 0

odp: 2 3 5






*/









