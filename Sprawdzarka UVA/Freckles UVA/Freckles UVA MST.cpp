#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<map>
#include<cmath>
#include<queue>
#include<string.h>
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
typedef pair<double,double> PDD;
const int infinity = 100000000;
typedef vector<double> VD;
typedef pair<double,int> PDI;
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

// ****************************************************** POCZATEK WALSCIWEJ KLASY NODE, EDGE I GRAPH

class Node{
public:
	Node(){}
	explicit Node( int anumber ) : number(anumber) {}
	Node( int anumber, VI neigh ) : number(anumber) { neighbours = neigh; 	}
	VI neighbours;
	int number;
	int toponum;
	
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


class Edge{
public:
	Edge(){}
	Edge( int abeg, int aend, int anumber = 0 ) : beg( Node(abeg) ), end( Node(aend) ){}
	Edge( Node abeg, Node aend, int anumber = 0, double aweight = 1 ) : beg(abeg), end(aend), number(anumber), weight(aweight) {}
	Node beg;
	Node end;
	double weight; // need it if want to call Dikstra etc
	int number; // need it if i want to identify edges e.g. by order it was given in input
	
	bool operator<( const Edge &e ) const {
		if( beg.number < e.beg.number ) return true;
		else if( beg.number == e.beg.number && end.number < e.end.number ) return true;
		return false;
	}
	bool operator==( const Edge e ) const {
		return ( beg.number == e.beg.number && end.number == e.end.number && number == e.number );
	}
	
	Node& operator[]( int pos ){
		if( pos < 0 || pos > 1 ) cout << "BLAD adresowania operatora[] w klasie Edge" << endl;
		else if( pos == 0 ) return beg;
		else return end;
	}
	
};
ostream& operator<<( ostream &str, Edge& e){
	str << 	"beg = " << e.beg.number << "  end = " << e.end.number << "  weight = " << e.weight << endl;
	return str;
}

typedef vector<Node> VN;
typedef map<Edge, bool> ME;
typedef vector<vector<Edge> > VVE;

class Graph{
public:
	/*
	* if edgesOnMap = true ( it means 1 ), then edges will be kept on map, not in a two-dimensional array (in case of 0)
	* parametry edgesOnMap i directed trzeba ustwaic recznie, z reguly jest to podane w specyfikacji zadania
	*
	*/
	Graph( int vert_num=0, int edg_num=0 ) : vertices_num( vert_num ), edges_num(edg_num), edgesOnMap( 1 ), directed(0) {		
		if( edgesOnMap == 1 ) edges.clear();
	/*	else if( edgesOnMap == 0 ){  // tego uzywamy, gdy chcemy przechowywac krawedziena tablicy - macierzy sasiedztwa
			edges.clear();
			REP( i,vert_num ) edges.PB( vector<int>() );
		}*/
		
		nodes.clear();
		REP(i,vert_num) nodes.PB( Node(i) );
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
		
	}
	Graph( VN v ){
		nodes = v;
		//    ...    tu trzeba jeszcze troche pouzupelniac...
	}
	
	
	VN nodes;	
	ME edges;
	//VVE edges;
	
	int vertices_num; // number of vertices
	int edges_num; // number of edges
	
	int directed; // 1 - directed, 0 -undirected
	int edgesOnMap; // edgesOnMap = true ( it means 1 ), then edges will be kept on map, not in a two-dimensional array (in case of 0)
	
	double getWeight( Edge e ); // wywoluje wersje wyjsciowa
	double getWeight( int beg, int end ); // to jest wersja wyjsciowa
	double getWeight( Node n1, Node n2 ); // wywoluje wersje wyjsciowa
	
	void addNode( Node n ); // dodaje wierzcholek
	void addNode( VI v ); // dodaje wierzcholek majac danych jego sasiadow
	
	void addEdge( int abeg, int aend, double aweight=1 );
	
	void addNEN( int abeg, int aend, double aweight=1 );
	
	void writeGraph(){
		cout << "Wierzcholki:" << endl;
		REP( i,nodes.size() ){
			cout << "Wierzcholek nr " << i+1 << ":\t";
			REP( k, nodes[i].size() ){
				cout << nodes[i][k]+1 << " ";
			}
			cout << endl;
		}
		cout << endl << "Krawedzie:" << endl;
		for( ME::iterator it = edges.begin(); it!=edges.end(); it++ ) cout << (it->ST).beg.number << " " << (it->ST).end.number << " " << (it->ST).weight << endl;
	}
	
	Node& operator[]( int pos ){
		if( pos < 0 || pos > nodes.size() ) {
			cout << "BLAD INDEKSOWANIA operator[] klasy Graph" << endl;
			return *new Node(-1);
		}
		return nodes[pos];
	}
	
	void sortNeighbours(){ // caution!! i sort only int arrays in nodes[i], not nodes-array
		REP( i,nodes.size() ){
			nodes[i].sortNeighbours();
		}
	}
	
	double getTotalEdgesWeight(){
		double w = 0;
		for( ME::iterator it = edges.begin(); it!=edges.end(); it++ ){
			w += ( (it->ST).weight );
		}
		if( !directed ) w/=2;
		return w;
	}
	
/********************************************************  SEKCJA ALGORYTMOW
*
*
*
*/
	
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
};

//******************************************************* FUNKCJE SKLADOWE KLASY GRAPH

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
	
	int *zmiana = new int[nodes.size()];
	REP( i,nodes.size() ) zmiana[ vec[i].number ] = i; // wierzcholek o numerze i jest na miejscu zmiana[i]
	REP( i,vec.size() ){
		REP(k,vec[i].size()){
			vec[i][k] = zmiana[ vec[i][k] ];
		}
	}
	
/*	REP( i,vec.size() ){
		cout << i << ":  ";
		REP(k,vec[i].size()){
			cout << vec[i][k] << " ";
		}
		cout << endl;
	}*/
	
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
	//			cout << "i = " << i << "  vec[i][k] = " << vec[i][k] << " max = " << max << "  ind = " << ind << "   dl[ vec[i][k] ] = " << dl[ vec[i][k] ] << endl;
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
	int a = 0,b = 0,ind = 0;
	REP( i,nodes[0].size() ){
		it = edges.find( Edge( ind,nodes[0][i] ) );
//		cout << "sasiad nr 0 ma numer:" << nodes[0].number << "  jego sasiad to: " << nodes[0][i] << endl;
		e = it->ST;
		if( e.weight < min ){
			min = e.weight;
			b = nodes[0][i];			
		}
	}
	
//	cout << "a = " << a << "  b = " << b << "  min = " << min << endl;
	
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
	
//	REP(i,nodes.size()) if( tree[i] ) cout << i+1 << " ";
//	cout << endl;
//	cout << "TRALAHAHAHA  AHAH" << endl;
	
	int ile_w_drzewie = 2,t=0;
	while( ile_w_drzewie < nodes.size() ){
		pair<double, Edge> p = pq.top();
		pq.pop();
		e = p.ND;
		a = e.beg.number;
		b = e.end.number;
		w = -p.ST;
		
//		cout << "a = " << a+1 << "  b = " << b+1 << "  w = " << w << endl;
//		REP(i,nodes.size()) if( tree[i] ) cout << i+1 << " ";
//		cout << endl << endl;
		
		if( tree[a] == true && tree[b] == true ) continue;
		else if( tree[a] == false ) t = a;
		else t = b;
		
		
//		cout << "a = " << a << "  b = " << b << "  w = " << w << endl;
		
		
		myTree.addNEN( a,b,w );
		
		tree[t] = true;
		REP( i,nodes[t].size() ){
			if( tree[ nodes[t][i] ] == false ){
				it = edges.find( Edge( t,nodes[t][i] ) );
//				if( it == edges.end() ) cout << "END" << endl << "END" << endl << "END" << endl;
				e = it->ST;
				pq.push( MP(-e.weight, e) );				
			}
		}
		
		ile_w_drzewie++;
	}
	
	return myTree;
	
}

//**************************************************************** KONIEC FUNKCJI SKLADOWYCH KLASY GRAPH


int main(){	
	cout << fixed;
	cout.precision(2);
	VVI V;
	
	ofstream strout( "outy.txt" );
	int l_zest;
	cin >> l_zest;
	while(l_zest--){
		
		cin >> N;
		if( N == 1 ){
			cout << (double)0 << endl << endl;
			continue;
		}
		
		PDD *tab = new PDD[N];
		V.clear();
		REP(i,N) V.PB( VI() );
		
		double x,y;
		REP(i,N){
			cin >> x >> y;
			tab[i] = MP(x,y);
		}
		
		for( int i=0; i<N; i++ ){
			for(int k=0; k<N; k++){
				if( i!=k ) V[i].PB(k);
			}
		}
		Graph G(V);
		
		double a,b,c,d,e,f;
		G.edges.clear();
		for(int i=0; i<N; i++){
			for(int k=i+1; k<N; k++){
				a = tab[i].ST;
				b = tab[i].ND;
				c = tab[k].ST;
				d = tab[k].ND;
				e = a-c;
				f = b-d;
				d = sqrt( e*e + f*f );
			//	cout << "d = " << d << endl;
				
				G.addEdge( i,k,d );
			}
		}
	//	
//		G.writeGraph();
		
		Graph T = G.MSTPrim();
//		T.writeGraph();
		
		
		
		strout << T.getTotalEdgesWeight() << endl;
		if( l_zest > 0 ) strout << endl; 
		
		delete[]tab; tab = 0;

	}
	
	strout.close();
}






