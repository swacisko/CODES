
//#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
//#include<map>
//#include<complex>
//#include<stack>
//#include<list>
//#include<bitset>
#include<set>
//#include<iterator>
#include<cmath>
//#include<queue>
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
typedef vector<string> VS;
typedef vector< VS > VVS;

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





// klasa reprezentujaca komunikat
// wektor obiektow tej klasy jest przechowywany przez kazdy z wierzcholkow - obiektow klasy vert
class notif{
public:
//	notif(){}
	notif( int l, int fr ) : str(""), liczba(l), from(fr) {}
	notif( string s ) : str(s), liczba(0) {}
	notif( VVI v, int fr ) : V(v), from(fr) {}
//	notif( string s, int l ) : str(s), liczba(l) {}
	string str;
	int liczba;	
	int from;
	VVI V;
	static const int BLANK = -INF - 170;
};

typedef vector<notif> VN;
typedef vector< VN > VVN;

ostream & operator<<( ostream & str, notif & no ){
	str << "str = " << no.str << "   liczba = " << no.liczba;
	return str;	
}

// to jest przestrzen nazw, w ktorej znajduje sie symulator :)
namespace Symulator{
	
	int number_of_vertices; // to jest ilosc wierzcholkow  w tworzonym grafie
// ************************************** POCZATEK KLASY WEWNATRZ PRZESTRZENI SYMULATOR
class vert{
public:
	VI neighbours;  // to jest lista sasiadow danego wierzcholka, neighbours[i] to nr wierzch. na liscie Symulator::graph
	VVN kom; // to jest wektor komunikatow wyslanych do danego wierzcholka, kom[i][k] - jest to k-ty komunikat wyslany przez wierzcholek nr i do mnie
	
	int id; // id wierzcholka, unikatowe
	int id_los; // id losowe wierzcholka
	static int next_id; // statyczna zmienna, kazdemu wierzcholkowi przyporzadkowuje kolejne id
	
	int which_case; // to jest zmienna, ktora wyznacza nam, w ktorym miejscu mamy zaczac wykonywac kod w nastepnym wywolaniu funkcji execute
	int HOW_MANY_CASES; // to jest zmienna, ktora trzeba ustawic RECZNIE w konstruktorze przed kompilacja programu
	vector<vert> *graph;
	vector<vert> *graph_copy; // uwaga!! tego nie mozna uzywac, tworzac wlasny program, to jest tylko do symulowania rund programu
	
	//************* TUTAJ JEST CZESC, GDZIE DODAJE NOWE DANE, TYPOWE DLA KONKRETNEGO ZADANIA
	VVI V; // to jest graf znany dla danego wierzcholka
	
	// funckaj zwraca rozmiar obrazu drzewa... jesli jest on rowny 2*number_of_vertices, to znaczy ze juz mam caly obraz...
	int imageSize(){
		int ile = 0;
		REP(i,SIZE(V)) ile += SIZE(V[i]);
		return ile;
	}
		
	// funkcja usuwa z listy neighbours sasiada o numerze num
	void removeneigh( int num ){
		REP(i,SIZE(neighbours) ) if( neighbours[i] == num ){
			neighbours.erase( neighbours.begin()+i );
			break;
		}
	}
	
	// funkcja otrzymuje notif, i scala obraz grafu - ten ktory posiada z tym ktory otrzymuje od sasiada...
	void mergeGraph( notif nf ){
		VVI v2 = nf.V;
		REP( i,SIZE(v2) ) REP(k,SIZE(v2[i])) V[i].PB(v2[i][k]);
		V[id].PB( nf.from );
		V[nf.from].PB(id);
	}
	
	void updateRoundData(){
		(*graph_copy)[id].which_case = which_case;
		(*graph_copy)[id].V = V;
		(*graph_copy)[id].neighbours = neighbours;
	}
		
	//**********************************

	// jako parametr przyjmuje ilosc wierzcholkow lacznie w grafie, w ktorym jest tworzony ten wierzcholek
	// N jest potrzebne tylko do inicjalizacja tablicy kom
	vert( int N = 0, vector<vert> *wsk = 0, vector<vert> *wsk_copy = 0 ) : HOW_MANY_CASES(1), kom( VVN(N, VN() ) ), graph(wsk), graph_copy(wsk_copy) {
		id = next_id++;
		id_los = rand() % 130;
		which_case = 0;
		V = VVI( number_of_vertices );
	//	REP(i,SIZE(neighbours)) V[id].PB(neighbours[i]);
	}
	
	

	// execute to funkcja w ktorej powinien znajdywac sie glowny kod programu
	// zamiat fiber_yield jest switch, ktory wykonuje odpowiedni kod
	void execute(){
		
		switch( which_case ){
			case 0:{
				// teraz, jesli otrzymalem jakies obrazy, to scalam swoje obrazy :)
				REP(i,SIZE(neighbours)){						
						notif nf = getLatestMessage( neighbours[i] );
						while( nf.liczba != notif::BLANK ){ // dopoki mam wiadomosc, to scalam ytrzymywane obrazy...
							cout << "id = " << id << "  Odbieram obraz od wierzcholka " << nf.from << endl;
							mergeGraph( nf );
							removeneigh(nf.from);
							nf = getLatestMessage( neighbours[i] );
							cout << "\tnf.liczba = " << nf.liczba << endl;			
						}
				}	
				
				if( id == 0 ){ // obraz scaigamy do wierzcholka o id=0
					if( imageSize() == 2*number_of_vertices-2 ){
						cout << "Moje id = " << id << "  mam obraz grafu!! Oto on:" << endl;
						REP(i,SIZE(V)){
							cout << "Wierzcholek nr " << i << " << ma sasiadow:\t";
							REP(k,SIZE(V[i])) cout << V[i][k] << " ";
							cout << endl;
						}
					}
									
					
				}
				else if( SIZE(neighbours) == 1 ){ // jesli jestem lisciem to wysylam swoj obraz do jedynego sasiada ktory mi zostal
											// UWAGA, w tym algorytmie zmieniam tablice neighbours z rundy na runde...
					cout << "id = " << id << "   SIZE(neighbours) == " << SIZE(neighbours) << "  wysylam obraz so wierzcholka " << neighbours[0] << endl;
					sendMessage( neighbours[0], V );
					neighbours.clear();				
				}
				
				
					
				break;				
			}	
			default:{
				
				
				
			}		
			
		} // koniec switch'a
		
		updateRoundData();
		
	}
	
	// funkcja zwraca pierwsza w kolejce wiadomosc wyslana przez wierzcholek nr sock do mnie
	// dodatkowo ta funkcja usuwa z kolejki wiadomosci odczytana wiadomosc
	// jezeli w kolejce do danego wierzcholka nie ma wiadomosci, to funkcja zwraca notif, w ktorym liczba == notif::BLANK
	notif getLatestMessage( int sock ){
		notif s( notif::BLANK, -1 );
		if( SIZE( kom[sock] ) > 0 ){
			s = kom[sock][0];
			kom[sock].erase( kom[sock].begin() );
			(*graph_copy)[id].kom[sock].erase( (*graph_copy)[id].kom[sock].begin() ); // musze usunac takze w grafie, ktory nie jest kopia, tzn komunikaty nie sa usuwane z rundy na runde...
		}
		return s;
	}
	
	// funkcja sluzy do wypisywania informacji o danym wierzcholku, wywolywana przez symulator po zakonczeniu rundy
	// UWAGA, tutaj wypisuje w odwrotnej kolejnosci niz jest podane w algorytmie!!, aby wypisywac tak jak jest w algorytmie nalezy zamienic cutColor() na 
	// getProperColor()
	void writeState(){
		cout << "Jestem wierzcholkiem o id = " << id << "  id_los = " << id_los << endl;
		cout << "Obraz grafu:" << endl;
		REP( i,SIZE(V) ){
			if( !V[i].empty() ){
				cout << "\tSasiedzi wierzcholka " << i << ":\t";
				REP(k,SIZE(V[i])) cout << V[i][k] << " ";
				cout << endl;
			}
		}
		ENDL(1);		
	}
	
	// funkcja wysyla sasiadowi nr sock wiadomosc mess
	void sendMessage( int sock, VVI mess ){
		(*graph_copy)[ sock ].kom[id].PB( notif( mess,id ) ); // dodaje wiadomosc do nowej wersji grafu, wersji grafu z nastepnej rundy
	}
			

};
//********************************* KONIEC KLASY  WERT, CIAG DLASZY PRZESTREZNI NAZW SYMULATOR



	int which_vertex = 0;	
	vector<vert> graph, graph_copy;
	
	
	// funkcja dodaje do grafu graph dane z drzewa V tak, aby w graph byla reprezentacja drzewa ukorzenionego. Jako poczatek biore wierzcholek nr nr
	void addTreeDfs( VVI V, int nr, int par = -1 ){
		if( par != -1 ) graph[nr].neighbours.PB( par );  
		REP( i, SIZE(V[nr]) ){
			if( V[nr][i] != par ){
				graph[nr].neighbours.PB( V[nr][i] );
				addTreeDfs( V, V[nr][i], nr );
			}
			//else graph[nr].par = par;
		}
	}
	
	// funkcja tworzy w tab ring na N wierzcholkach
	void createTree( int N ){
		number_of_vertices = N;
		graph.clear();		
		REP(i,N) graph.PB( vert( N, &graph, &graph_copy ) );
		
		VVI V = generateTree(N);
		addTreeDfs( V, 0 );
		
		graph_copy = graph;
	}
	
	// funkcja visualize wywoluje dla kazdego wierzcholka grafu funkcje writeState odpowiedzialna za wpisania informacji o danym wierzcholku
	void visualize(){
		cout << "SIZE(graph) = " << SIZE(graph) << endl;
		REP(i,SIZE(graph) ){
			 graph[i].writeState();
			 ENDL(1);
		}
		
		ENDL(2);
	}
	
	// funkcja wypisuje graf, ktory stworzylismy - tylko strukture, tzn listy sasiedztwa
	void writeGraph(){
		REP(i,SIZE(graph)){
			cout << "Wierzcholek nr " << i << " ma sasiadow: ";
			REP(k,SIZE(graph[i].neighbours)) cout << graph[i].neighbours[k] << " ";
			cout << endl;
		}
	}
	
	void execNextVert(){
		if( which_vertex == -2 ){
			ENDL(2);
			cout << "Koniec dzialania programu, which_vertex = -2" << endl; 
			return;
		}
		else if( which_vertex == -1 ){ // jesli jestem w danej turze w "konsoli"
			graph = graph_copy;
			cout << "Powrocilem do \"konsoli\" " << endl;
		//	visualize();
		}
		else graph[ which_vertex ].execute();
		
		which_vertex++;
		if( which_vertex == number_of_vertices ) which_vertex = -1; // jesli koncze prace na ostatnim wierzcholku to prezchodze do konsoli		
	}
	
	// funkcja, ktora dla kazdego wierzcholka wywoluje funkcje execute i powraca do "konsoli"
	void nextRound(){
		REP( i,number_of_vertices+1 ) execNextVert();		
	}
		

}




int Symulator::vert::next_id = 0;

using namespace Symulator;
int main(){
	srand( time(0) );
	
	cout << "Podaj ilosc wierzcholkow, ktore chcesz miec w drzewie:\t";
	int N;
	cin >> N;
	
	createTree(N);
	cout << "Oto twoje drzewo:" << endl;
	writeGraph();
	ENDL(2);
	
	cout << "Aby wykonac kolajna runde, wybierz 'r' i zatwierdz ENTER" << endl
		<< "Aby wyswietlic stan wierzcholkow, wybierz 'v' i zatwierdz ENTER" << endl
		<< "Aby wyczyscic ekran wybierz 'P' i zatwierdz ENTER" << endl;
	
	char znak;
	int round_nr = 0;
	while( cin >> znak ){ // aby symulowac nastepna runde nalezy wpisac r i ENTER :)
		if( znak == 'r' ){
			cout << "Round nr " << ++round_nr << endl;
			nextRound();
			ENDL(2);
		}
		else if( znak == 'v' ){ // aby wyswietlic stan wierzcholkow wcisnij 'v' ( jak visualize )
			visualize();
			ENDL(2);
		}
		else if( znak == 'P' ) system("clear"); // aby wyczyscic ekran wcisnij 'P'
				
	}
	
}












