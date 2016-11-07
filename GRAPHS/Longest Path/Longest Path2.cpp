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
#define WRITE( V ){ FOREACH(it,V) cout << *it+1 << ", "; cout << endl; }
#define WRITE_ALL(V) {  REP( i,SIZE(V) ){ cout  << i+1 << " ---- ";  FOREACH(it,V[i]) cout << *it+1 << ", "; cout << endl;     } }
#define WRP(p) p.ST+1 << " " << p.ND+1
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


VVI graph; // to jest wyjsciowy graf, w ktorym chce znalezc nadluzsza sciezke...


//***************************************************************************************************************************************   LONGEST PATH TOPOSORT
//*****************************************************   JEST TO W ZASADZIE JEDYNA DZIALAJACA METODA DLA WIEKSZEJ LICZBY WIERZCHOLKOW, DLA GRAFOW , KTORE NIE SĄ
//*****************************************************   EKSTREMALNIE RZADKIE. DLA GRAFOW RZADKICH LEPIEJ UZYC  SPANNING TREE with fluctuations

namespace TOPO{

	VVI V;
	VI deg; // ilosc ojcow danego wierzcholka w grafie, jesli ma 0 to mozna go w danym momencie dodac do listy topologicznej
	VI kol; // kol[i] - nr wierzcholka ktory jest i-ty w kolejnosci topologicznej
	VB was; // zapisuje czy juz bylem w danym wierzcholku podczas topologicznego dfsa
	int N;

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
	//    cout << "Wchodze do longestPath" << endl;
		topo_sort();
		N = SIZE(V);
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

	//	cout << "Wychodze z longestPath" << endl << endl;
		return l_path;
	}


}

void deleteCycleDFS( VVI & V, VB & was, int nr, int par, bool & found ){
    was[nr] = true;
    REP( i, SIZE( V[nr] ) ){
        if( V[nr][i] != par && was[ V[nr][i] ]  ){
            V[nr].erase( V[nr].begin() + i-- );
            found = true;
        }
        else if( V[nr][i] != par ) deleteCycleDFS( V, was, V[nr][i], nr, found );
    }

}

// return longest path. Parameters: graph V (can be disconnected) in which to look for the path, repetitions - number of topo sorts to do ( each topo sort can improve longest path.
// Maximum number of topo sorts equals 2^|E|.
// potrzeba w³aczyc srand( unsigned(time(0) ) );
VI longestPathTopoSort( VVI V, int repetitions ){
    VI res; res.clear();
    VI longest; longest.clear();
    REP( rep, repetitions ){
        TOPO::V = VVI( SIZE(V) );
        REP( k, SIZE(V) ){
            REP(j, SIZE(V[k]) ){
                if( V[k][j] > k ){ // kazda krawedz chce dodawac tylko jeden raz...
                    if( rand()%2 ){
                        TOPO::V[k].PB( V[k][j] );
                    }
                    else{
                        TOPO::V[ V[k][j] ].PB( k );
                    }
                }
            }
        } // po tej petli mam juz wybrana kolejna losowa orientacje krawedzi, ale moga byc cykle...

        VB was( SIZE(V),false );
        VI inDeg( SIZE(V),0 );
        REP( i, SIZE(V) ) REP( k, SIZE( TOPO::V[i] ) ) inDeg[ TOPO::V[i][k] ]++;
        bool found = false;
        REP( i, SIZE(V) ){
                was = VB( SIZE(V),false );
                deleteCycleDFS( TOPO::V,was,i,i,found );
        }

        if( found == false ) continue;

   //     cout << "losowo stworzony graf to:" << endl;
     //   WRITE_ALL( TOPO::V );

        res = TOPO::longestPath();
        if( SIZE(res) > SIZE(longest) ) longest = res;
    }

    return longest;
}

//********************************************************************************************************************************************   LONGEST PATH SPANNING TREE

// nazwa przestrzeni DIAM bierze sie ze slow DIAMETER, a my przeciez szukamy srednicy w drzewie, czyli najdluzszej sciezki :)
namespace DIAM{
	VVI V; // graf - drzewo
	VI path; // tutaj znajduje sie najdluzsza sciezka w danym drzewie(mozliwe ze jedna z wielu)
	VI dist; // dist[i] to odleglosc wierzcholka i od korzenia w drzewie(umownie od wierzcholka 0, bo korzen moze zostac wybrany dowolnie)
	VI par; // par[i] to rodzic danego wierzcholka na sciezce, jest to potrzebne do wyznaczenia najdluzszehj sciezki

	// dfs wyznaczajacy odleglosci wierzcholkow od korzenia
	void dfs( int par, int num, int dst ){
		dist[num] = dst;
		REP(i,SIZE(V[num])) if( V[num][i] != par ){
			dfs( num, V[num][i], dst+1 );
		}
	}

	// bfs wyznaczajacy rodzicow na najdluzszej sciezce
	void bfs( int beg ){
		VI neigh(1,beg); par[beg] = INF; // poczatek sciezki nie ma rodzica, wiec INF
		REP(i,SIZE(neigh)){
			REP(k,SIZE( V[neigh[i]] )){ // dla kazdego sasiada kolejnego wierzcholka z bfsa...
				if( par[ V[neigh[i]][k] ] == -1 ){ // jesli jeszcze nie bylem w tym sasiedzie, to go dodaje oraz dodaje jego rodzica
					par[ V[neigh[i]][k] ] = neigh[i];
					neigh.PB( V[neigh[i]][k] );
					dist[ V[neigh[i]][k] ] = dist[ neigh[i] ] + 1;
				}
			}
		}
	}

	// funkcja zwracajaca najdluzsza sciezke w drzewie V
	VI getDiameter(){
		dist = VI( SIZE(V),0 );
		par = VI( SIZE(V),-1 );
		path.clear();

		dfs( 0,0,0 );
		int m = -1, ind = -1; // znajudje maksymalna odleglosc oraz index tego wierzcholka
		REP(i,SIZE(dist)){
			if( dist[i] > m ){
				m = dist[i];
				ind = i;
			}
		}
		dist = VI( SIZE(V),0 ); // zeruje dystans przed bfsem
		bfs(ind);

		m = -1; ind = -1;
		REP(i,SIZE(dist)){ // znajduje index najdalaszego wierzcholka... jest on koncem najdluzszej sciezki
			if( dist[i] > m ){
				m = dist[i];
				ind = i;
			}
		}
		path.PB(ind);
		while( ( ind = par[ind] ) != INF ) path.PB(ind); // poruszam sie od wierzcholka do rodzica tak dlugo az dojde do poczatku
		return path;
	}
}

// returns random spanning tree of graph V (must be connected!), must be srand(...) turned on
VVI getRandomSpanningTree( const VVI G ){
	VVI V = G;
 //   cout << "Wchodze do getRandomSpanningTree" << endl;
    VVI tree( SIZE(V) );
    REP( i, SIZE(V) ) random_shuffle( ALL(V[i]) );
    VI seq( SIZE(V) );
    REP( i, SIZE(seq) ) seq[i] = i;
    random_shuffle( ALL(seq) );

    VB is( SIZE(V),false );
    is[ seq[0] ] = true;
    VPII kolejka;
    REP( i, SIZE( V[ seq[0] ] ) ) kolejka.PB( MP( seq[0], V[ seq[0] ][i] ) ); // dodaje wszystkich sasiadow wierzcholka seq[0]

    while( kolejka.size() > 0 ){
      //  cout << "SIZE(kolejka) = " << SIZE(kolejka) << ":\t";
      //  REP(i,SIZE(kolejka)) cout << WRP(kolejka[i]) << " --- ";
      //  ENDL(1);

        int ind = rand() % SIZE( kolejka );
        int v1 = kolejka[ind].ST, v2 = kolejka[ind].ND; // biore losowo wybrana krawedz...
        swap( kolejka[ind], kolejka[ SIZE(kolejka)-1 ] ); // usuwam krawedz z kolejki
        kolejka.pop_back();
        if( is[v1] == false && is[v2] == true ) swap( v1,v2 );

        if( is[v2] == false ){ // jesli jednego wierzcholka nie ma jeszcze w drzewie, to go dodaje...
            tree[v1].PB(v2);
            tree[v2].PB(v1);
            is[v2] = true;
            REP( i, SIZE( V[v2] ) ){
                if( is[ V[v2][i] ] == false ){ // dodaje krawedz, ale tylko wtedy, jesli jest sens ja pozniej ropatrywac
                    kolejka.PB( MP( v2, V[v2][i] ) );
                }
            }
        }
    }

//   cout << "Stworzylem losowe drzewo" << endl;
 //   WRITE_ALL( tree );
 //   ENDL(2);

    return tree;
}

// return longest path. Parameters: CONNECTED (!!!) graph V in which to look for the path, repetitions - number of spanning trees to create
VI longestPathSpanningTree( VVI V, int repetitions ){
    VI res, longest;
    REP( i, repetitions ){
        DIAM::V = getRandomSpanningTree( V );
        DIAM::getDiameter();
        if( SIZE(DIAM::path) > SIZE(longest) ) longest = DIAM::path;
    }
    return longest;
}


// ********************************************************************************    now other version of longestPathSpanningTree - should be faster and much more reliable...
//*********************************************************************************    SPANNING TREE with fluctuations, good only for sparse graphs, for dense ones use topoSort method!!!
bool getCycleInTree( VVI & V, VB & was, int nr, int par, VI & cycle ){
 //   cout << "nr = " << nr << endl;
    was[nr] = true;
    REP( i, SIZE(V[nr]) ){
        if( V[nr][i] != par && was[V[nr][i]] ){
            cycle.PB( V[nr][i] );
            cycle.PB(nr);
            return true;
        }

        if( V[nr][i] != par && getCycleInTree( V, was, V[nr][i], nr, cycle ) == true ){
            if( cycle[0] != cycle.back() ) cycle.PB(nr);
            return true;
        }
    }

    return false;
}

// removes edge vw from graph V
void removeEdge( VVI & V, int v, int w ){
  //  cout << "removeEdge" << endl;
    REP(x,2){
        REP( i, SIZE(V[v]) ){
            if( V[v][i] == w ){
                V[v].erase( V[v].begin() + i );
                break;
            }
        }
    swap(v,w);
    }
  //  cout << "Usunalem krawedz " << v << " " << w << endl;
}

// adds random edge from edges to V, and erases it from edges
void addRandomEdge( VVI & V, set< PII > & edges ){
  //  cout << "Add random edge" << endl;
    set< PII >::iterator it = edges.begin();
    int x = rand()%SIZE(edges);
    REP(i,x) it++;

    int a = it->ST;
    int b = it->ND;
    V[a].PB(b);
    V[b].PB(a);

    edges.erase( *it );
  //  cout << "Dodalem krawedz " << a+1 << " " << b+1 << endl;
}

void createEdges( VVI & V, VVI & tree, set< PII > & edges ){
    edges.clear();
    REP( i, SIZE(V) ){
        REP(k,SIZE(V[i])){
            if( V[i][k] > i ) edges.insert( MP( i, V[i][k] ) );
        }
    }

    REP( i, SIZE(tree) ){
        REP( k, SIZE(tree[i]) ){
            if( tree[i][k] > i ) edges.erase( MP( i, tree[i][k] ) );
        }
    }
}

// return longest path after repetitions, using spanning tree method with fluctuations
VI longestPathSpanningTreeFluctuation( VVI V, int repetitions ){
    DIAM::V = getRandomSpanningTree(V);

    set< PII > edges; // here are all edges, that are in V and are NOT in tree
    VI longest, cycle;
    VB was( SIZE(V),false );
    int los;

    createEdges( V, DIAM::V, edges );
  //  cout << "Oto edges" << endl;
  //  FOREACH( it,edges ) cout << it->ST+1 << " " << it->ND+1 << " --- ";
   // ENDL(2);

    REP( x, repetitions ){
      //  cout << "Moje drzewo to:" << endl;
      //  WRITE_ALL( DIAM::V );

      //  cout << "Poczatek" << endl;

        DIAM::getDiameter();
        if( SIZE(DIAM::path) > SIZE(longest) ) longest = DIAM::path;

      //  cout << "Srodek" << endl;

        addRandomEdge(DIAM::V, edges); // i add random edge to the tree
        fill( ALL(was),false );
        cycle.clear();
        getCycleInTree( DIAM::V, was, 0,0, cycle ); // now i get the only one cycle that occurs in the ( tree + random_edge )

      //  cout << "I got the cycle, SIZE(cycle) = " << SIZE(cycle) << ":\t";
     //   WRITE(cycle);
      //  ENDL(2);

        los = rand()%( SIZE(cycle)-1 ); // I take random edge  in the cycle
        removeEdge( DIAM::V, cycle[los], cycle[los+1] );
        edges.insert( MP( min( cycle[los], cycle[los+1] ), max( cycle[los], cycle[los+1] ) ) ); // I add removed edge to the tree..., so that i can again use getDiameter

      //  cout << "Koniec" << endl;
    }

    return longest;
}

//*********************************************************************  CHECK
// return true if path is a path and exists in given graph
bool existsPathInGraph( VVI & V, VI & path ){
    VB was( SIZE(V),false );
    REP( i, SIZE(path) ){
        if( was[ path[i] ] == true ) return false;
        was[ path[i] ] = true;
    }

    bool found = false;
    REP( i, SIZE(path)-1 ){
        found = false;
        REP( k, SIZE( V[ path[i] ] ) ){
            if( V[ path[i] ][k] == path[i+1] ){
                found = true;
                break;
            }
        }
        if( found == false ) return false;
        found = false;
        REP( k, SIZE( V[ path[i+1] ] ) ){
            if( V[ path[i+1] ][k] == path[i] ){
                found = true;
                break;
            }
        }
        if( found == false ) return false;
    }

    return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************  NOW LONGEST PATH USING GROWING TREES


set<PII> getEdgesInT( VVI T ){
	set<PII> zb;
	REP( i, SIZE(T) ){
		REP(k,SIZE(T[i])){			
			if( T[i][k] > i ) zb.insert( MP( i,T[i][k] ) );
		}
	}
	return zb;
}

set<PII> getEdgesInGNotT( const VVI G, set<PII> T_edges ){
	set<PII> zb;
	REP(i,SIZE(G)){
		REP(k,SIZE(G[i])){
			if( G[i][k] > i ){					
				if( T_edges.count( MP( i,G[i][k] ) ) ) continue;
				else zb.insert( MP( i,G[i][k] ) );	
			}
		}
	}
	return zb;
}

bool isConnected( VVI V ){
	VB was( SIZE(V),false );
	was[0] = true;
	VI neigh( 1,0 );
	REP(i,SIZE(neigh)){
		int a = neigh[i];
		was[a] = true;
		REP( k, SIZE( V[a] ) ){
			int b = V[a][k];
			if( !was[b] ){
				neigh.PB(b);
				was[b] = true;
			}
		}
	}
	REP(i,SIZE(was)){
		if( !was[i] ) return false;
	}
	return true;
}

VVI switchEdges( VVI T, PII add_edge, PII remove_edge ){
	T[ add_edge.ST ].PB( add_edge.ND );
	T[ add_edge.ND ].PB( add_edge.ST );
	
	int a = remove_edge.ST, b = remove_edge.ND;
	REP( k, SIZE( T[a] ) ){
		if( T[a][k] == b ){
			T[a].erase( T[a].begin()+k );
			break;
		}
	}
	swap(a,b);
	REP( k, SIZE( T[a] ) ){
		if( T[a][k] == b ){
			T[a].erase( T[a].begin()+k );
			break;
		}
	}
	return T;
}


VVI improveTree( VVI T, set<PII> &T_edges, set<PII> &GNotT_edges ){
	
	VVI T2;
	DIAM::V = T;
	int L = SIZE( DIAM::getDiameter() ), l;
	
	VI cycle; VB was(SIZE(T),false);
	
	FOREACH( it,T_edges ){
		FOREACH( itr, GNotT_edges ){
			T2 = switchEdges( T,*itr,*it );
			if( isConnected(T2) == false ) continue;
			
			PII gnt = *itr;
			PII t = *it;
			
			//cout << "\tDo drzewa T dodalem krawedz " << WRP(gnt) << " i usunalem krawedz " << WRP(t) << endl;
			
			DIAM::V = T2;
			l = SIZE( DIAM::getDiameter() );
			if( l > L ){
				
				T_edges.erase( t );
				T_edges.insert( gnt );
				GNotT_edges.erase( gnt );
				GNotT_edges.insert( t );				
				return T2;				
			}			
		}		
	}
	
	cout << "Nie da sie poprawic drzewa" << endl;
	return T;
}


void improveTree2( VVI &T2, set<PII> &T_edges, set<PII> &GNotT_edges ){
	
	//VVI T2 = T;
	DIAM::V = T2;
	int L = SIZE( DIAM::getDiameter() ), l;
	
	VI cycle;
	VB was(SIZE(T2),false);
	
	int a,b;
	FOREACH( itr, GNotT_edges ){
		PII gnt = *itr;		
		cycle.clear();
		fill( ALL(was),false );
				
		//T2 = T;
		T2[gnt.ST].PB( gnt.ND );
		T2[gnt.ND].PB( gnt.ST );
		 
		getCycleInTree( T2,was,SIZE(T2[0]), SIZE(T2[0]),cycle ); // tutaj zamiast SIZE(T2[0]) moze byc dowolny rand modulo SIZE(T2)
		if( SIZE(cycle) == 0 ) cout << "SIZE(cycle) = 0 !! BLAD, cykl musi istniec! !!" << endl;
		
		//cout << endl << "OTO ZNALEZIONY CYKL" << endl;
		//WRITE(cycle);
		bool found = false;
		REP( i, SIZE(cycle)-1 ){
		//	cout << "SIZE(cycle) = " << SIZE(cycle) << "    i = " << i << endl;
			a = cycle[i];
			b = cycle[ i+1 ];	
			if( a > b ) swap(a,b);	
			
			
			REP( k, SIZE( T2[a] ) ){
				if( T2[a][k] == b ){
					T2[a].erase( T2[a].begin()+k );
					break;
				}
			}
			swap(a,b);
			REP( k, SIZE( T2[a] ) ){
				if( T2[a][k] == b ){
					T2[a].erase( T2[a].begin()+k );
					break;
				}
			}
			swap(a,b);
			//cout << "\tDo drzewa T dodalem krawedz " << WRP(gnt) << " i usunalem krawedz " << WRP(t) << endl;
			
			DIAM::V = T2;
			l = SIZE( DIAM::getDiameter() );
			if( l > L ){
				PII t = MP( a,b );			
				T_edges.erase( t );
				T_edges.insert( gnt );
				GNotT_edges.erase( gnt );
				GNotT_edges.insert( t );					
				//return T2;
				
				//T = T2;
				found = true;
				break;											
			}
			
		//	cout << "a = " << a << "   b = " << b << endl;
			T2[a].PB(b);
			T2[b].PB(a);
		//	cout << "\thaha" << endl;		
		}
		
		if( found == false ){
			a = gnt.ST;
			b = gnt.ND;
			REP( k, SIZE( T2[a] ) ){
				if( T2[a][k] == b ){
					T2[a].erase( T2[a].begin()+k );
					break;
				}
			}
			swap(a,b);
			REP( k, SIZE( T2[a] ) ){
				if( T2[a][k] == b ){
					T2[a].erase( T2[a].begin()+k );
					break;
				}
			}
		}
		
	}		
	
	//return T2;
}

VI longestPathGrowingTree( const VVI G ){

	VVI T = getRandomSpanningTree( G );
	int lastLength = 0, currentLength = 0;
	VI lpath;
	
	set<PII> T_edges = getEdgesInT(T);
	set<PII> GNotT_edges = getEdgesInGNotT(G,T_edges);
	
	
	do{
		swap( currentLength, lastLength );
		
	//	cout << "Drzewo T przed ulepszeniem" << endl;
	//	WRITE_ALL(T);
		
		T = improveTree( T, T_edges, GNotT_edges );		
		
	//	cout << "Drzewo T po ulepszeniu" << endl;
	//	WRITE_ALL(T);
		
		DIAM::V = T;
		//cout << "\tPrzed getDiameter" << endl;
		lpath = DIAM::getDiameter();
		//cout << "\tP getDiameter" << endl;
		
		currentLength = SIZE(lpath);		
		
		
	}while( currentLength > lastLength );
	return lpath;
	
}

// TO JEST ODPOWIEDNIK WERSJI LONGEST_PATH_GROWING_TREE, działa w przybliżeniu tak samo dobrze
// tzn randomizowanie tak samo - czasami minimalnie lepiej, czasami minimalnie gorzej,   ale  ZDECYDOWANIE SZYBCIEJ NIZ POPRZEDNIA WERSJA !!! 
VI longestPathGrowingTree2( const VVI G ){

	VVI T = getRandomSpanningTree( G );
	int lastLength = 0, currentLength = 0;
	VI lpath;
	
	set<PII> T_edges = getEdgesInT(T);
	set<PII> GNotT_edges = getEdgesInGNotT(G,T_edges);
	
	
	do{
		swap( currentLength, lastLength );
		
	//	cout << "Drzewo T przed ulepszeniem" << endl;
	//	WRITE_ALL(T);
		
		improveTree2( T, T_edges, GNotT_edges );		
		
	//	cout << "Drzewo T po ulepszeniu" << endl;
	//	WRITE_ALL(T);
		
		DIAM::V = T;
		//cout << "\tPrzed getDiameter" << endl;
		lpath = DIAM::getDiameter();
		//cout << "\tP getDiameter" << endl;
		
		currentLength = SIZE(lpath);		
		
		if( currentLength == lastLength ) cout << "Nie da sie poprawic drzewa" << endl;
	}while( currentLength > lastLength );
	return lpath;
	
}




int main(){
	ios_base::sync_with_stdio(0);
	srand( unsigned( time(0) ) );


	//cout << "Podaj liczbe wierzcholkow i krawedzi grafu:" << endl;
    int N,M;
  //  cin >> N >> M;
    const int NSCOPE = 150;
    const int DENSITY = NSCOPE/5;
    N = NSCOPE;
    M = 0;
    VVI V(N);
    
generate:    
    V = VVI(N);
	M = 0;
 
    REP(i,N) FOR(k,i+1,N-1){
        if( rand()%DENSITY == 0 ){
            V[i].PB(k);
            V[k].PB(i);
            M++;
        }
    }
    
    if( !isConnected(V) ) goto generate;

	cout << "N = " << N << endl;
    cout << "M = " << M << endl;
  //  cout << "Graf ma postac" << endl;
  //  WRITE_ALL(V);


   /* int a,b;
    VVI V(N);
    REP(i,M){
        cout << "Podaj " << i+1 << "-sza krawedz(od 1 do " << N<< "):\t";
        cin >> a >> b;
        V[a-1].PB( b-1 );
        V[b-1].PB(a-1);
    }*/

   // cout << "Podaj liczbe iteracji, ktore mam wykonac w poszukiwaniu najdluzszej sciezki:\t";
    int iterations = 500;
 //   cin >> iterations;

    VI pathTopoSort = longestPathTopoSort(V,iterations);
    cout << "Najdluzsza sciezka w longestPath metoda TopoSort to: " << endl;
    cout << "SIZE = " << SIZE( pathTopoSort ) << endl << "Wierzcholki:\t";
    WRITE( pathTopoSort );
    cout << "Sprawdzenie: " << existsPathInGraph( V,pathTopoSort ) << endl;
    ENDL(2);

    /*VI pathSpanningTree = longestPathSpanningTree(V, iterations);
    cout << "Najdluzsza sciezka w longestPath metoda SpanningTree to: " << endl;
    cout << "SIZE = " << SIZE( pathSpanningTree ) << endl << "Wierzcholki:\t";
    WRITE( pathSpanningTree );
    cout << "Sprawdzenie: " << existsPathInGraph( V,pathSpanningTree ) << endl;
    ENDL(2);

    VI pathSpanningTreeFluctuation = longestPathSpanningTreeFluctuation( V, iterations );
    cout << "Najdluzsza sciezka w longestPath metoda SpanningTreeFluctuations to: " << endl;
    cout << "SIZE = " << SIZE( pathSpanningTreeFluctuation ) << endl << "Wierzcholki:\t";
    WRITE( pathSpanningTreeFluctuation );
    cout << "Sprawdzenie: " << existsPathInGraph( V,pathSpanningTreeFluctuation ) << endl;
    ENDL(2);*/
    
    
    /*VI pathGrowingTree = longestPathGrowingTree( V );
    cout << "Najdluzsza sciezka w longestPath metoda GrowingTree to: " << endl;
    cout << "SIZE = " << SIZE( pathGrowingTree ) << endl << "Wierzcholki:\t";
    WRITE( pathGrowingTree );
    cout << "Sprawdzenie: " << existsPathInGraph( V,pathGrowingTree ) << endl;
    ENDL(2);*/
    
    VI pathGrowingTree2 = longestPathGrowingTree2( V );
    cout << "Najdluzsza sciezka w longestPath metoda GrowingTree2 to: " << endl;
    cout << "SIZE = " << SIZE( pathGrowingTree2 ) << endl << "Wierzcholki:\t";
    WRITE( pathGrowingTree2 );
    cout << "Sprawdzenie: " << existsPathInGraph( V,pathGrowingTree2 ) << endl;
    ENDL(2);

	return 0;
}












