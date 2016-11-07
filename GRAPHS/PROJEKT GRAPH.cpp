#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<cmath>
#include<queue>
#include<string.h>
#include<sstream>
#include<algorithm>

using namespace std;

#define REP( x,y ) for( int x=0; x<y; x++ )
#define FORD( x,y ) for( int x=y; x>=0; x-- )
#define PB push_back
#define PH push_heap
#define POP pop_back
#define MP make_pair
#define ST first
#define ND second

int N,M,a,b,c,x,y;
const int INF = 100000000;
typedef long long LL;
typedef vector<double> VD;
typedef pair<double,int> PDI;
typedef pair<double, double> PDD;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef map< PII, bool > MPIIB;

template <class typ> // binary insert to ordered array
void insertB( vector<typ> &V, typ t ){
	int k;
	int p =0;
	int q = V.size();
	
	while( p < q ){
		k = (p+q)/2;
		if( t < V[k] ){
			q = k;
		}
		else{
			p = k+1;
		}
	}
	
//	cout << "Dodaje element t = " << t << "  na pozycje p = " << p << endl;
	V.insert( V.begin() + p, t );
}

template<class typ> // return index of found element or -1 if it isnt found
int searchB( vector<typ> &V, typ t ){
	int p = 0;
	int q = V.size()-1;
	int k;
	while( p <= q ){
		k = (p+q)/2;
		if( V[k] == t ) return k;
		if( V[p] == t ) return p;
		if( V[q] == t ) return q;
		
		if( t < V[k] ){
			q = k;
		}
		else{
			p = k+1;			
		}
	}
	
	return -1;
	
}

template<class typ>
typ maximum( typ a, typ b ){
	return a > b ? a : b;
}
template<class typ>
typ minimum( typ a, typ b ){
	return a < b ? a : b;
}

// ****************************************************************************************************************************** POCZATEK WALSCIWEJ KLASY NODE, EDGE I GRAPH

class Node{
public:
	Node(){}
	explicit Node( int anumber ) : number(anumber) {}
	Node( int anumber, VI neigh ) : number(anumber) { neighbours = neigh; 	}
	VI neighbours;
	int number;
	int mainGraphNumber;
	int toponum;
	bool isArtPoint;
	int PreOrder;
	int PostOrder;
	int conComp; // numer skladowej spojnosci, w ktorej jest dany wierzcholek, moze sie to przydac, np do silnie spojnych skladowych, czy set union w MST Kruskalem
	int low; // parametr low dla mostow i punktow artykulacji
	int dfssons;  // ilosc synow na drzewie rozpietym dfsem, potrzebne dla korzenia, aby sprwadzic czy jest punktem artykulacji
	
	
	int& operator[]( int pos ){ // zwraca numer sasiada na pozycji i
		if( pos < 0 || pos > neighbours.size() ){
			cout << "BLAD INDEKSOWANIA operator[] z klasy Node" << endl;
			return *new int(-1);
		}
		return neighbours[pos];
	}
	
	int size(){ return neighbours.size(); }	
	void push_back( int nod ){ neighbours.PB( nod ); }
	void sortNeighbours(){
		sort( neighbours.begin(), neighbours.end() );
	}
	
};

//****************************************************************************************************************************************************** KLASA EDGE

class Edge{
public:
	Edge(){}
	Edge( int abeg, int aend, int anumber = 0 ) : beg( Node(abeg) ), end( Node(aend) ){}
	Edge( Node abeg, Node aend, int anumber = 0, double aweight = 1 ) : beg(abeg), end(aend), number(anumber), weight(aweight) {}
	Node beg;
	Node end;
	double weight; // need it if want to call Dikstra etc
	int number; // need it if i want to identify edges e.g. by order it was given in input
	int mainGraphNumber;
	bool isBridge;
	
	bool operator<( const Edge &e ) const {
		if( beg.number < e.beg.number ) return true;
		else if( beg.number == e.beg.number && end.number < e.end.number ) return true;
		return false;
	}
//	bool operator==( const Edge e ) const {
//		return ( beg.number == e.beg.number && end.number == e.end.number && number == e.number );
//	}
	
	Node& operator[]( int pos ){
		if( pos < 0 || pos > 1 ) cout << "BLAD adresowania operatora[] w klasie Edge" << endl;
		else if( pos == 0 ) return beg;
		else return end;
	}
	
};
ostream& operator<<( ostream &str, Edge& e){
	str << 	"beg = " << e.beg.number << "  end = " << e.end.number << "  weight = " << e.weight << "  mainNumber = " << e.mainGraphNumber;
	return str;
}

typedef vector<Node> VN;
typedef map<Edge, bool> ME;
typedef vector<vector<Edge> > VVE;
//************************************************************************************************************************************************ KLASA GRAPH
class Graph{
public:
	/*
	* if edgesOnMap = true ( it means 1 ), then edges will be kept on map, not in a two-dimensional array (in case of 0)
	* parametry edgesOnMap i directed trzeba ustwaic recznie, z reguly jest to podane w specyfikacji zadania
	*
	*/
	Graph( int vert_num=0, int edg_num=0 ) : vertices_num( vert_num ), edges_num(edg_num), edgesOnMap( 1 ), directed(0) {		
		nodes.clear();
		REP(i,vert_num) nodes.PB( Node(i) );
		renumerateNodeNumbers();
		assignMainGraphNumbers();
		setAndCheck();
	}
	
	Graph( VVI v ) : edgesOnMap(1), directed(0) {
		vertices_num = 0;
		nodes.clear();
		edges.clear();
		REP( i, v.size() ){
			addNode( v[i] );
		}
		
		edges_num = 0;
		REP( i,v.size() ){
			REP( k,v[i].size() ){
				addEdge( i,v[i][k] );
			}
		}
		assignMainGraphNumbers();
		setAndCheck();
	}
	
	Graph( VN v ){
		nodes = v;
		REP( i,nodes.size() ){
			REP( k,nodes[i].size() ){
				addEdge( i,nodes[i][k] );
			}
		}
		vertices_num = nodes.size();
		assignMainGraphNumbers();
		setAndCheck();
	}
	
	
	VN nodes;	
	ME edges;
	
	int vertices_num; // number of vertices
	int edges_num; // number of edges
	
	int directed; // 1 - directed, 0 -undirected
	int edgesOnMap; // edgesOnMap = true ( it means 1 ), then edges will be kept on map, not in a two-dimensional array (in case of 0)
	
	void clear(){
		nodes.clear();
		edges.clear();
		setAndCheck();
	}
	
	double getWeight( Edge e ); // wywoluje wersje wyjsciowa
	double getWeight( int beg, int end ); // to jest wersja wyjsciowa
	double getWeight( Node n1, Node n2 ); // wywoluje wersje wyjsciowa
	
	void addNode( Node n ); // dodaje wierzcholek
	void addNode( VI v ); // dodaje wierzcholek majac danych jego sasiadow
	void addNode( int abeg, int aend );
	
	void addEdge( int abeg, int aend, double aweight=1 );
	void addEdge( const Edge e ){ edges.insert( MP(e,true) ); }
	
	void removeEdge( Edge e );
	void removeEdge( int abeg, int aend );
	
	void addNEN( int abeg, int aend, double aweight=1 );
	
	void writeGraph();
	void writeGraphByMain();
	
	void writeEdges();
	
	Node& operator[]( int pos ){
		if( pos < 0 || pos > nodes.size() ) {
			cout << "BLAD INDEKSOWANIA operator[] klasy Graph" << endl;
			return *new Node(-1);
		}
		return nodes[pos];
	}
	
	void sortNeighbours();
	
	double getTotalEdgesWeight();
	
	
	void setAndCheck();
	void resetEdges(); // deletes all edges and insert edges on the base of nodes neioghbours
	void renumerateGraph(); // jezeli w grafie sa werzcholki o numerach x oraz y z czeg nodes[0].num = x i nodes[1].num = y, to nodes[0].negihbour[0] to bedzie 1, a nie y
	// dodaje takze potrzebne krawedzie
	void renumerateGraphMainWeird(); // to samo co renuerateGraph, tylko ze zamiast nodes[i].number jest nodes[i].mainGraphNumber - przydaje sie dla roznych skladowcyh
	
	void renumerateNodeNumbers(){ REP(i,nodes.size()) nodes[i].number = i;	} // sprawia, ze weirzcholek nodes[t] ma numer t;
	
	void renumerateEdgeNumbers();
	
	void assignMainGraphNumbers();
	
/********************************************************  SEKCJA ALGORYTMOW
*
*
*
*/
	void PostOrderDFS( int myNumber, int& dfsnum );
	void PreOrderDFS( int myNumber, int& dfsnum );
		
	void topoDFS( int myNumber );
	void topoConnectedDFS();
	int topoN;
	VN topoSort(); 
	/* zwraca wektor wierzcholkow, ze zmienionym indeksowaniem sasiadow, dostosowanym dla tego wektora
	* jednak numery wierzcholkow( n.number ) pozostaja takie jak w grafie
	*/
	VN longestPath();

	VD Dijkstra( int beg );
	
	Graph MSTPrim();
	
	void addComponentDFS( int myNumber, bool *ifWas, Graph &G );
	vector<Graph> undirectedConnectedComponents();
	void addDirComponentDFS( int myNumber, Graph &G );
	vector<Graph> directedConnectedComponents(); // uwaga, zwrocony jest transponowany graf pod wzgledem mainGraphNumbers, pod wzgledem number jest ok
	vector<Graph> connectedComponents();
	
	void connectedBridgesAndArtPoints( int &dfsnum, int myNumber, int parent );
	void bridgesAndArtPoints(); // uwaga!! dziala tylko dla grafow spojnych !!!    UWAGA, tylko dla grafów spójnych!!!
	
	Graph transpose(); // transponuje graf - krawedz 2->1 staje sie krawedzia 1->2
};

//************************************************************************************************************************************************** FUNKCJE SKLADOWE KLASY GRAPH
void Graph::removeEdge( Edge e ){
	if( directed ) edges.erase(e);
	else{
		edges.erase( e );
		edges.erase( Edge( e.end, e.beg ) );
	}
}

void Graph::removeEdge( int abeg, int aend ){
	removeEdge( Edge(abeg,aend) );
}

void Graph::writeGraph(){
	REP( i,nodes.size() ){
		cout << "Wierzcholek nr " << i << "=" <<nodes[i].number << ":\t";
		REP( k, nodes[i].size() ){
			cout << nodes[i][k] << " ";
		}
		cout << endl;
	}
	writeEdges();
	cout << endl;
}

void Graph::writeGraphByMain(){
	REP( i,nodes.size() ){
		cout << "Wierzcholek nr " << i << "=" << nodes[i].mainGraphNumber << ":\t";
		REP( k, nodes[i].size() ){
			cout << nodes[ nodes[i][k] ].mainGraphNumber << " ";
		}
		cout << endl;
	}
	writeEdges();
	cout << endl;
}

void Graph::writeEdges(){
	cout << "Edges:" << endl;
	for( ME::iterator it = edges.begin(); it!=edges.end(); it++ ){
		Edge e = it->ST;
		cout << e << endl;
	}	
}

void Graph::sortNeighbours(){ // caution!! i sort only int arrays in nodes[i], not nodes-array
	REP( i,nodes.size() ){
		nodes[i].sortNeighbours();
	}
}

double Graph::getTotalEdgesWeight(){
	double w = 0;
	for( ME::iterator it = edges.begin(); it!=edges.end(); it++ ){
		w += ( (it->ST).weight );
	}
	if( !directed ) w/=2;
	return w;
}

void Graph::renumerateEdgeNumbers(){ 
	int ile = 0; 
	for( ME::iterator it = edges.begin(); it!=edges.end(); ++it ){
		const Edge *e = &it->ST;
		Edge *f = const_cast<Edge*>(e);
		f->number = ile++;
	}
}

void Graph::assignMainGraphNumbers(){  
	REP(i,nodes.size()) nodes[i].mainGraphNumber = i; //wierzcholki
	int ile = 0;
	for( ME::iterator it = edges.begin(); it!=edges.end(); ++it ){ // przypisuje numery krawedziom
		const Edge *e = &it->ST;
		Edge *f = const_cast<Edge*>(e);
		f->mainGraphNumber = ile++;
	}
}
	
double Graph::getWeight( Edge e ){
	return getWeight( e.beg.number, e.end.number );
}
double Graph::getWeight( int beg, int end ){
	if( edgesOnMap ){
		ME::iterator p = edges.find( Edge( beg,end ) );
		if( p == edges.end() ) cout << "Nie ma takiej krawedzi..." << endl;
		else return p->ST.weight;
	}
/*	else{
		return edges[beg][end].weight;
	}*/
}
double Graph::getWeight( Node n1, Node n2 ){
	return getWeight( n1.number, n2.number );
}

void Graph::addNode( Node n ){
	Node n2 = n;
	n2.number = vertices_num++;
	nodes.PB( n2 );
}

void Graph::addNode( int abeg, int aend ){
	if( directed ) nodes[abeg].PB(aend);
	else{
		nodes[abeg].PB(aend);
		nodes[aend].PB(abeg);
	}
}

void Graph::addNode( VI v ){	
	nodes.PB( Node( vertices_num++, v ) );
}

void Graph::addEdge( int abeg, int aend, double aweight ){
	if( edgesOnMap ){ // jesli krawedzie sa przechowywane na mapie
		if( directed ){
			Edge e( abeg, aend, edges_num++);
			edges.insert( MP( e, true ) );
		}
		else{			
			Edge e( abeg, aend, edges_num );			
			if( edges.find( e ) != edges.end() ) return; // jesli juz tak krawedz istniejem to nic nie bede robil...
			e.weight = aweight;
			
			edges.insert( MP( e, true ) );
			
			Edge f( aend, abeg, edges_num++ );
			f.weight = aweight;
			edges.insert( MP( f, true ) );
		}
	}
/*	else{ // jesli krawedzie sa na tablicy dwuwymiarowej
		if( directed ){
			edges[abeg][aend].is = true;
		}
		else{
			edges[abeg][aend].is = true;
			edges[aend][abeg].is = true;
		}
	}*/
}

void Graph::addNEN( int abeg, int aend, double aweight ){
	if( directed ){
		nodes[abeg].PB( aend );
		addEdge( abeg,aend,aweight );
	}
	else{
		nodes[abeg].PB( aend );
		nodes[aend].PB( abeg );
		addEdge( abeg,aend,aweight );
	}
}

// renumerateGraph

void Graph::renumerateGraph(){
	int max = 0;
	REP(i,nodes.size()){
		if( nodes[i].number > max ){
				 max = nodes[i].number;
		}
	}
	
	int *zmiana = new int[max+1];
	REP( i,max+1 ) zmiana[i] = 0;
	
	REP( i,nodes.size() ) zmiana[ nodes[i].number ] = i;	
	
	REP( i,nodes.size() ){
		REP( k,nodes[i].size() ){			
			nodes[i][k] = zmiana[ nodes[i][k] ];
		}
	}
	
	delete[]zmiana;
}

void Graph::renumerateGraphMainWeird(){
	int max = 0;
	REP(i,nodes.size()){
		if( nodes[i].mainGraphNumber > max ){
				 max = nodes[i].mainGraphNumber;
		}
	}
	
	int *zmiana2 = new int[max+1];
	REP( i,max+1 ) zmiana2[i] = 0;
	
	REP( i,nodes.size() ) zmiana2[ nodes[i].mainGraphNumber ] = i;	
	
	REP( i,nodes.size() ){
		REP( k,nodes[i].size() ){			
			nodes[i][k] = zmiana2[ nodes[i][k] ];
		}
	}
	
	delete[]zmiana2;
}

// reset Edges

void Graph::resetEdges(){
	edges.clear();
	int num = 0;
	REP(i,nodes.size()){
		REP(k,nodes[i].size()){
			edges.insert( MP( Edge( i,nodes[i][k],num++ ),true) );
		}
	}
}

// setAndCheck

void Graph::setAndCheck(){
	vertices_num = nodes.size();
	if( directed ) edges_num = edges.size();
	else edges_num = edges.size()/2;
}

//****** Sortowanie topologiczne
void Graph::topoDFS( int myNumber ){	
	REP( i,nodes[myNumber].size() ){
		if( nodes[ nodes[myNumber][i] ].toponum == 0 ){
			topoDFS( nodes[myNumber][i] );
		}
	}
	
	nodes[myNumber].toponum = topoN;
	topoN--;
}

void Graph::topoConnectedDFS(){
	int *tab = new int[vertices_num];
	REP(i,vertices_num) tab[i] = true;
	REP( i,nodes.size() ){
		REP(k,nodes[i].size() ){
			tab[ nodes[i][k] ] = false;
		}
	}
	
	REP(i,nodes.size()){
		if( nodes[i].toponum == 0 && tab[i] == true ){
			topoDFS( i );
		}
	}
}

bool topoSortFun( const Node &n1, const Node &n2 ){
	return n1.toponum < n2.toponum;
}

vector<Node> Graph::topoSort(){
	topoN = vertices_num;
	REP( i,nodes.size() ) nodes[i].toponum = 0;
	topoConnectedDFS();
	
	vector<Node> vec;
	vec.clear();
	int *tab = new int[nodes.size()];
	REP( i,nodes.size() ) tab[ nodes[i].toponum-1 ] = i;
	
	REP( i,nodes.size() ) vec.PB( nodes[ tab[i] ] );
	
	int *zmiana = new int[nodes.size()]; // tutaj jest to samo co renumerateGraph
	REP( i,nodes.size() ) zmiana[ vec[i].number ] = i; // wierzcholek o numerze i jest na miejscu zmiana[i]
	REP( i,vec.size() ){
		REP(k,vec[i].size()){
			vec[i][k] = zmiana[ vec[i][k] ];
		}
	}
	
	delete[]tab; tab = 0;
	delete[]zmiana; zmiana = 0;
	return vec;
}
//***** Koniec sortowania topologicznego


//****** Najdluzsza sciezka

VN Graph::longestPath(){
	VN vec = topoSort();
	int *tab = new int[ vec.size() ]; // index syna, dla ktorego jest najduzsza sciezka
	int *dl = new int[ vec.size() ]; // dlugosc najdluzszej sciazki zaczynajacej sie w danym wierzcholku
	REP( i,vec.size() ){
		tab[i] = 0;
		dl[i] = 0;
	}
	
	int max=0, ind=0;
	FORD( i,vec.size()-1 ){
		max = -1;
		ind = infinity;
		
		REP( k,vec[i].size() ){
			if( dl[ vec[i][k] ] > max ){
				max = dl[ vec[i][k] ];
				ind = vec[i][k];
			}
		}
		
		tab[i] = ind;
		dl[i] = max+1;
	}
	
	VN v;
	v.clear();
	
	max = -infinity;
	ind = infinity;
	REP( i,vec.size() ){
		if( dl[ i ] > max ){
			max = dl[ i ];
			ind = i;
		}
	}
	
	int t;
	for( t=ind; dl[t] > 0; t = tab[t] )	v.PB( vec[t] );
	v.PB( vec[t] );
	
	delete[]tab; tab = 0;
	delete[]dl; dl = 0;
	return v;
}
// ********* koniec najdluzszej sciezki


// Dijkstra

VD Graph::Dijkstra( int beg ){
	double t;
	priority_queue< PDI > pq;
	pq.push( MP( 0,beg ) );
	
	VD distances( nodes.size() );
	REP( i,distances.size() ) distances[i] = infinity;
	distances[beg] = 0;
	
	int ind;
	double dist;
	while( !pq.empty() ){
		PDI p = pq.top();
		dist = -p.ST;
		ind = p.ND;
		pq.pop();
		
		if( dist == distances[ind] ){
			REP( i,nodes[ind].size() ){
				if( dist + (t=getWeight( ind, nodes[ind][i] ) ) < distances[ nodes[ind][i] ] ){
					distances[ nodes[ind][i] ] = dist + t;
					pq.push( MP( -dist-t, nodes[ind][i] ) );
				}				
			}			
		}		
	}
	
	return distances;
}


// Minimal Spanning tree , algorytm Prima

Graph Graph::MSTPrim(){
	Graph myTree( nodes.size(),0 );
	priority_queue< pair<double,Edge> > pq;
	bool *tree = new bool[nodes.size()]; // tutaj zapisuje, czy dany wierzcholek nalezy juz do rozpinanego drzewa
	REP(i,nodes.size()) tree[i] = false;
		
	Edge e;
	ME::iterator it;
	double min = infinity,w=1;
	int a=0,b=0,ind = 0;
	REP( i,nodes[0].size() ){
		it = edges.find( Edge( ind,nodes[0][i] ) );
		e = it->ST;
		if( e.weight < min ){
			min = e.weight;
			b = nodes[0][i];
		}
	}
		
	myTree.addNEN( a,b,min );
	tree[a] = true;
	tree[b] = true;
	REP( i,nodes[a].size() ){ // dodaje wszystkie krawedzie wierzcholka a
		if( tree[nodes[a][i]] == false ){
			it = edges.find( Edge( a, nodes[a][i] ) );
			e = it->ST;
			pq.push( MP( -e.weight, e ) );
		}
	}
	REP( i,nodes[b].size() ){ // dodaje wszystkie krawedzie wierzcholka b
		if( tree[nodes[b][i]] == false ){
			it = edges.find( Edge( b, nodes[b][i] ) );
			e = it->ST;
			pq.push( MP( -e.weight, e ) );
		}
	}

	int ile_w_drzewie = 2,t=0;
	while( ile_w_drzewie < nodes.size() ){
		pair<double, Edge> p = pq.top();
		pq.pop();
		e = p.ND;
		a = e.beg.number;
		b = e.end.number;
		w = -p.ST;
	
		if( tree[a] == true && tree[b] == true ) continue;
		else if( tree[a] == false ) t = a;
		else t = b;
		
		myTree.addNode( a,b );
		myTree.addEdge( e );
		
		tree[t] = true;
		REP( i,nodes[t].size() ){
			if( tree[ nodes[t][i] ] == false ){
				it = edges.find( Edge( t,nodes[t][i] ) );
				e = it->ST;
				pq.push( MP(-e.weight, e) );				
			}
		}
		
		ile_w_drzewie++;
	}
	
	myTree.setAndCheck();
	return myTree;
	
}


// connectedComponents

void Graph::addComponentDFS( int myNumber, bool *ifWas, Graph &G ){
	ifWas[myNumber] = true;
	G.addNode( nodes[myNumber] );
	G.nodes[ G.nodes.size()-1 ].number = nodes[myNumber].number;
	REP( i,nodes[myNumber].size() ){
		if( ifWas[ nodes[myNumber][i] ] == false ){
			addComponentDFS( nodes[myNumber][i], ifWas, G );
		}
	}	
}

vector<Graph> Graph::undirectedConnectedComponents(){
	vector<Graph> graphs;
	Graph G;
	bool *ifWas = new bool[nodes.size()];
	REP(i,nodes.size()) ifWas[i] = false;
	ME::iterator it;
	
	REP( i,nodes.size() ){
		if( ifWas[i] == false ){
			G.clear();
			addComponentDFS( i,ifWas, G );
			
			G.renumerateGraph();	
			REP( k,G.nodes.size() ){
				REP(t,G.nodes[k].size()){					
					if( (it=edges.find( Edge( G.nodes[k].number, G.nodes[ G.nodes[k][t] ].number ) )) != edges.end() ){
						Edge e = it->ST;
						G.addEdge( e );
					}
				}
			}
			
			G.renumerateNodeNumbers();			
			G.setAndCheck();
			graphs.PB(G);
		}
	}
	
	delete[]ifWas; ifWas = 0;
	return graphs;
}

void Graph::PreOrderDFS( int myNumber, int& dfsnum ){
	nodes[myNumber].PreOrder = dfsnum++;
	REP( i,nodes[myNumber].size() ){
		if( nodes[ nodes[myNumber][i] ].PreOrder == 0 ){
			PreOrderDFS( nodes[myNumber][i], dfsnum );
		}
	}
}

void Graph::PostOrderDFS( int myNumber, int& dfsnum ){
	nodes[myNumber].PostOrder = -1; // to musi byc, zeby mi nie weszlo w nieskonczone petle, pod koniec DFSa i tak zmieniam ten numer na wlasciwy
	REP( i,nodes[myNumber].size() ){
		if( nodes[ nodes[myNumber][i] ].PostOrder == 0 ){
			PostOrderDFS( nodes[myNumber][i], dfsnum );
		}
	}
	nodes[myNumber].PostOrder = dfsnum++;
}
void Graph::addDirComponentDFS( int myNumber, Graph &G ){
	nodes[myNumber].PreOrder = -1; // to jest tylko po to aby nie wpasc w nieskonczona petle
	G.addNode( nodes[myNumber] );
	
	REP( i,nodes[myNumber].size() ){
		if( nodes[ nodes[myNumber][i] ].PreOrder == 0 ){
			addDirComponentDFS( nodes[myNumber][i], G );
		}
	}	
}

vector<Graph> Graph::directedConnectedComponents(){
	vector<Graph> graphs;
	Graph G; G.directed = true;
	
	*this = transpose(); // transponuje graf glowny, i dla niego wykonam odpowiedni pierwszy DFS, aby potem wykonac drugi DFS dla normalnego grafu
	REP(i,nodes.size()) nodes[i].PostOrder = 0;
	int dfsnum = 1;
	REP( i,nodes.size() ) if( nodes[i].PostOrder == 0 ) PostOrderDFS( i,dfsnum ); // tutaj wyznaczam postordery dla glownego grafu
	
	int *zmiana = new int[ nodes.size() ];
	REP( i,nodes.size() ) zmiana[i] = 0;
	REP( i,nodes.size() ) zmiana[ nodes[i].PostOrder-1 ] = i; // to jest potrzebne aby rozpatrzac postordery w kolejnosciu malejacej	
	
	*this = transpose(); // transponuje glowny graf;
	
	REP( i,nodes.size() ) nodes[i].PreOrder = 0; // zapisuje tutaj zera aby wywolac zaraz addDirComponentDFS   ... to taki odpowiednik ifWas	
	int conc = 0;
	REP( i,nodes.size() ) nodes[i].conComp = -1;
	
	REP( i,nodes.size() ){
		if( nodes[ zmiana[ nodes.size()-1-i ] ].PreOrder == 0 ){
			G.clear();		
			
			addDirComponentDFS( zmiana[ nodes.size()-1-i ],G ); // uwaga, musze teraz usunac te wierzcholki , listy sasiadow wierzcholkow w grafie G, ktore nie nalezy do tej skaldowej spojnosci
			REP( k,G.nodes.size() ) nodes[ G.nodes[k].mainGraphNumber ].conComp = conc;
			conc++;
			
			REP( k,G.nodes.size() ){
				REP(j,G.nodes[k].size()){
					if( nodes[ G.nodes[k][j] ].conComp != nodes[ G.nodes[k].mainGraphNumber ].conComp ){
						G.nodes[k].neighbours.erase( G.nodes[k].neighbours.begin() + j );
					}
				}
			}
						
			G.renumerateGraphMainWeird(); // renumeracja grafu, ale dla mainNumerów :)
			G.transpose(); // musze spowrotem odwrocic ten graf
			G.renumerateNodeNumbers();			
			
			/* // tutaj powinno sie dodawac odpiwednie krawedzie, ewentualnie je zamienic numerami, tak aby pasowaly do nowego grafu, ale 
			* to wtedy bedzie w czasie MlogM
			*/			
			
			G.setAndCheck();
			graphs.PB(G);
		}		
	}
	
//	*this = transpose(); // transponuje spowrotem glowny graf
	
	delete[]zmiana; zmiana = 0;
	return graphs;
}

vector<Graph> Graph::connectedComponents(){
	if( directed ) return directedConnectedComponents();
	else return undirectedConnectedComponents();
}

// connectedBridgesAndArtPoints

void Graph::connectedBridgesAndArtPoints( int &dfsnum, int myNumber, int parent ){
	nodes[myNumber].isArtPoint = false;
	nodes[myNumber].PreOrder = dfsnum++;
	nodes[myNumber].low = nodes[myNumber].PreOrder;
	nodes[myNumber].dfssons = 0;
	
	REP( i,nodes[myNumber].size() ){
		if( nodes[ nodes[myNumber][i] ].PreOrder == 0 ){ // jesli jeszcze nie bylem w danym wierzcholku - synu
			connectedBridgesAndArtPoints( dfsnum, nodes[myNumber][i], myNumber );
			nodes[myNumber].low = minimum( nodes[myNumber].low, nodes[ nodes[myNumber][i] ].low );
			
			if( nodes[ nodes[myNumber][i] ].low >= nodes[myNumber].PreOrder ) nodes[myNumber].isArtPoint = true;
			if( nodes[ nodes[myNumber][i] ].low == nodes[ nodes[myNumber][i] ].PreOrder ){
				ME::iterator it = edges.find( Edge( myNumber, nodes[myNumber][i] ) ); // to dodaje czasowosci logN do ca³ego algorytmu, ale nie obejde tego, jakos musze zapisywac krawedzie
				const Edge *e = &it->ST;
				Edge *f = const_cast<Edge*>(e);
				f->isBridge = true;
				
				ME::iterator itr = edges.find( Edge( nodes[myNumber][i], myNumber ) );
				const Edge *e2 = &itr->ST;
				Edge *f2 = const_cast<Edge*>(e2);
				f2->isBridge = true;
			}
			
			nodes[myNumber].dfssons++;
		}
		else if( nodes[myNumber][i] != parent ){
			nodes[myNumber].low = minimum( nodes[myNumber].low, nodes[ nodes[myNumber][i] ].PreOrder );
		}
	}	
}

void Graph::bridgesAndArtPoints(){
	REP( i,nodes.size() ) nodes[i].PreOrder = 0; // musze to wyzerowac
	
	if( nodes.size() == 1 ){nodes[0].isArtPoint = false; return;}
	
	for( ME::iterator it = edges.begin(); it!=edges.end(); ++it ){ // tutaj niestety musze w czasie o(M) zerowac krawedzie, ale mysle ze to przejdzie :)
		const Edge *e = &it->ST;
		Edge *f = const_cast<Edge*>(e);
		f->isBridge = false;
	}
	
	int dfsnum = 1;
	connectedBridgesAndArtPoints( dfsnum, 0, -1 );
	nodes[0].isArtPoint = false;
	if( nodes[0].dfssons >= 2 ) nodes[0].isArtPoint = true;	
}


// transpose

Graph Graph::transpose(){
	Graph G(nodes.size(),0);
	REP( i,nodes.size() ){
		REP( k,nodes[i].size() ){
			G.nodes[ nodes[i][k] ].PB(i);
		}
	}
	
	G.edges = edges;	
	for( ME::iterator it = G.edges.begin(); it!=G.edges.end(); it++ ){
		const Edge *e = &it->ST;
		Edge *f = const_cast<Edge*>(e);
		swap( f->beg, f->end );
	}
	return G;
}

//**************************************************************** KONIEC FUNKCJI SKLADOWYCH KLASY GRAPH


int main(){
	/* // ***************************** testowanie wstawiania i wyszukiwania binarnego
	int ile, x;
	VI V;
	
	cout << "Podaj ile wartosci wstawic:\t";
	cin >> ile;
	REP(i,ile){
		cout << endl << "Podaj wartosc:\t";
		cin >> x;
		insertB( V,x  );
		REP(k,V.size()) cout << V[k] << " ";
		cout << endl << searchB(V,x);
	}
	*/
	
//ADASDAASDADA	
	
/*	// testowanie wstawiania do grafu i wypisywania grafu
	VVI V;
	V.clear();
	cout << "Podaj, ile chcesz wierzcholkow:\t"; cin >> N; REP(i,N) V.PB( VI() );
	cout << endl << "A krawedzi:\t"; cin >> M;
	REP( i,M ){
		cout << "Podaj " << i+1 << " krawedz:\t";
		cin >> a >> b;
		V[a-1].PB(b-1);
	//	V[b-1].PB(a-1);
	}
	
//ADSDAASDASA	
	
	// testowanie sortowania sasiadow
	Graph G( V );
	G.sortNeighbours();
	cout << "Oto twoj graf:" << endl;
	G.writeGraph();
	cout << endl << "Twoj graf ma " << G.vertices_num << " wierzcholkow i " << G.edges_num << " krawedzi" << endl;
	
	//testowanie sortowania topologicznego i najdluzszej sciezki
	cout << endl << endl << "A teraz wierzcholki posortowane topologicznie:" << endl;
	vector<Node> vec = G.topoSort();
	REP( i,vec.size() ) cout << vec[i].number+1 << " ";
	cout << endl;
	
	cout << "A oto bledne powiazania w nowym, posortowanym topologicznie grafie..." << endl;
	REP( i,vec.size() ){
		cout << i << ":\t";
		REP(k,vec[i].size()){
			cout << vec[i][k] << " ";
		}
		cout << endl;
	}
	
	cout << endl << "A oto najdluzsza sciazka w twoim grafie:" << endl;
	vec.clear();
	vec = G.longestPath();
	REP( i,vec.size() ){
		cout << vec[i].number+1 << " ";
	}*/
	
	
/*	//tVestowanie Dijkstry
	cout << "Podaj, ile chcesz wierzcholkow:\t"; cin >> N;
	cout << endl << "A krawedzi:\t"; cin >> M;
	
	Graph G(N,M);
	
	REP( i,M ){
		cout << "Podaj " << i+1 << " krawedz oraz wage:\t";
		cin >> a >> b >> c;
		
		G.addNEN( a-1,b-1,c );
	//	V[b-1].PB(a-1);
	}
	
	cout << "Podaj wierzcholek, dla ktorego chcesz znalezc dystanse:\t"; cin >> a;
	
	VI V = G.Dijkstra( a-1 );
	
	cout << "Oto dystanse:" << endl;
	REP(i,V.size()) cout << i+1 << ": " << V[i] << endl;
	
	cout << "Oto krawedzie twojego grafu:" << endl;
	for( ME::iterator it = G.edges.begin(); it!=G.edges.end(); it++){
		Edge e = it->ST;
		cout << e.beg.number+1 << " " << e.end.number+1 << " " << e.weight << endl;
	}*/
	
	
/*	//test Minimalnego drzewa rozpinajacego - algorytmem Prima
	cout << "Podaj, ile chcesz wierzcholkow:\t"; cin >> N;
	cout << endl << "A krawedzi:\t"; cin >> M;
	
	Graph G(N,0);
	
	REP( i,M ){
		cout << "Podaj " << i+1 << " krawedz oraz wage:\t";
		cin >> a >> b >> c;
		
		G.addNEN( a-1,b-1,c );
	//	V[b-1].PB(a-1);
	}
	
	
	cout << "A oto twoje minimalne drzewo rozpinajace:" << endl;
	Graph T = G.MSTPrim();
	T.writeGraph();
	
	cout << "A oto krawedzie drzewa rozpietego:" << endl;
	for( ME::iterator it = T.edges.begin(); it!=T.edges.end(); it++){
		Edge e = it->ST;
		cout << e.beg.number+1 << " " << e.end.number+1 << " " << e.weight << endl;
	}
	
	cout << "A to waga calkowita drzewa rozpietego:  " << T.getTotalEdgesWeight() << endl;*/
	
	
	
	//testowanie skladowych spojnosci grafu
	cout << "Podaj, ile chcesz wierzcholkow:\t"; cin >> N;
	cout << endl << "A krawedzi:\t"; cin >> M;
	
	Graph G(N,0);
	G.directed = false;
	
	REP( i,M ){
		cout << "Podaj " << i+1 << " krawedz:\t";
		cin >> a >> b;
		
		G.addNEN( a-1,b-1,1 );
	//	V[b-1].PB(a-1);
	}
	
//	G.writeGraph();
	G.assignMainGraphNumbers();
	G.sortNeighbours();
	
	vector<Graph> gr = G.connectedComponents();
	REP( i,gr.size() ){
		cout << "Graph nr " << i+1 << endl;
		gr[i].writeGraphByMain();
		cout << endl;
	}
	
	cout << "A oto numery w grafie glownym:" << endl;
	cout << "Wierzcholki:" << endl;
	REP( i,gr.size() ){
		REP(k,gr[i].nodes.size()){
			cout << gr[i].nodes[k].mainGraphNumber << " ";
		}
	}
	
	cout << endl << "A teraz krawedzie:" << endl;
	REP( i,gr.size() ){
		for( ME::iterator it = gr[i].edges.begin(); it!=gr[i].edges.end(); it++ ){
			cout << it->ST.mainGraphNumber << " ";
		}
	}
	
	
	
	
	
/*	// testowanie mostow i punktow artykulacji
	cout << "Podaj, ile chcesz wierzcholkow:\t"; cin >> N;
	cout << endl << "A krawedzi:\t"; cin >> M;
	
	Graph G(N,0);
	
	REP( i,M ){
		cout << "Podaj " << i+1 << " krawedz:\t";
		cin >> a >> b;
		
		G.addNEN( a-1,b-1,1 );
	//	V[b-1].PB(a-1);
	}
	
	G.setAndCheck();
	G.renumerateNodeNumbers();
	G.renumerateEdgeNumbers();
	G.assignMainGraphNumbers();
//	cout << "Numery glowne krawedzi przed algorytmem:" << endl;
//	for( ME::iterator it = G.edges.begin(); it!=G.edges.end(); ++it ){
//		cout << it->ST.mainGraphNumber << " ";
//	}
//	G.writeGraph();

	G.bridgesAndArtPoints();
		
	REP(i,G.nodes.size()){
		cout << G.nodes[i].number << " -> artPoint: " << G.nodes[i].isArtPoint << endl;
	}

	for( ME::iterator it = G.edges.begin(); it != G.edges.end(); ++it ){
		cout << it->ST.beg.number << " " << it->ST.end.number << "  bridge: " << it->ST.isBridge << endl;
	}*/
	
	
	
/*	// transpozycja grafu
	cout << "Podaj, ile chcesz wierzcholkow:\t"; cin >> N;
	cout << endl << "A krawedzi:\t"; cin >> M;
	
	Graph G(N,0);
	G.directed = true;
	
	REP( i,M ){
		cout << "Podaj " << i+1 << " krawedz:\t";
		cin >> a >> b;
		
		G.addNEN( a-1,b-1,1 );
	//	V[b-1].PB(a-1);
	}
	cout << "Przed transpozycja:" << endl;
	G.writeGraph();
	G = G.transpose();
	cout << endl << "Po transpozycji:" << endl;
	G.writeGraph();*/
	
	
}






