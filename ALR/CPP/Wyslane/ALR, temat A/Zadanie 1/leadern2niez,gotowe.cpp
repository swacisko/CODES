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


int ILE_KOMUNIKATOW;


// klasa reprezentujaca komunikat
// wektor obiektow tej klasy jest przechowywany przez kazdy z wierzcholkow - obiektow klasy vert
class notif{
public:
	notif() : liczba(BLANK) {}
	notif( int l, int fr ) : from(fr), liczba(l) {}
	int from;
	int liczba;	
	static const int BLANK = -INF - 170;
};

typedef vector<notif> VN;
typedef vector< VN > VVN;

ostream & operator<<( ostream & str, notif & no ){
	str << "liczba = " << no.liczba;
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
	vector<vert> *graph_copy;
	
	//************* TUTAJ JEST CZESC, GDZIE DODAJE NOWE DANE, TYPOWE DLA KONKRETNEGO ZADANIA
	
	int runda;
	void updateRoundData(){
		(*graph_copy)[id].which_case = which_case;
		(*graph_copy)[id].runda = runda;
	}
	
	
	//**********************************
	

	// jako parametr przyjmuje ilosc wierzcholkow lacznie w grafie, w ktorym jest tworzony ten wierzcholek
	// N jest potrzebne tylko do inicjalizacja tablicy kom
	vert( int N = 0, vector<vert> *wsk = 0, vector<vert> *wsk_copy = 0 ) : HOW_MANY_CASES(1), kom( VVN(N, VN() ) ), graph(wsk), graph_copy(wsk_copy) {
		id = next_id++;
		id_los = rand() % 1000;
		which_case = 0;
		runda = 0;
	}

	// execute to funkcja w ktorej powinien znajdywac sie glowny kod programu
	// zamiat fiber_yield jest switch, ktory wykonuje odpowiedni kod
	void execute(){
		
		switch( which_case ){
			case 0:{
				if( runda == 0 ){
					sendMessage( neighbours[0], id_los );
					runda++;
					break;					
				}
				FOR(i,0,1){					
					notif nf = getLatestMessage( neighbours[i] );
					if( nf.liczba == notif::BLANK ) continue;
					else if( nf.liczba == id_los ){
						REP(i,10) cout << "ID = " << id << "  id_los = " << id_los << "    JESTEM LEADEREM!!!" << endl;
						break;
					}
					
					REP(k,2) if( neighbours[k] == nf.from ) sendMessage( neighbours[ (k+1)%2 ], max( nf.liczba, id_los ) );
					
				}
				
				runda++;
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
		notif s( notif::BLANK,-1 );
		if( SIZE( kom[sock] ) > 0 ){
			s = kom[sock][0];
			kom[sock].erase( kom[sock].begin() );
			//(*graph_copy)[id].kom[sock].erase( (*graph_copy)[id].kom[sock].begin() ); // musze usunac takze w grafie, ktory nie jest kopia, tzn komunikaty nie sa usuwane z rundy na runde...
		}
		return s;
	}
	
	// funkcja sluzy do wypisywania informacji o danym wierzcholku, wywolywana przez symulator po zakonczeniu rundy
	void writeState(){
		cout << "ID = " << id << "  id_los = " << id_los << endl;
			cout << endl << "\tKomunikaty to:\t";
			REP(i,2){
				if( kom[ neighbours[i] ].size()==0 ) continue;
				cout << "Od wierzch id = " << neighbours[i] << ": " << kom[ neighbours[i] ][0] << ", ";
			}
		ENDL(1);
	}
	
	// funkcja wysyla sasiadowi nr sock wiadomosc mess
	void sendMessage( int sock, int mess ){
		(*graph_copy)[ sock ].kom[id].PB( notif( mess,id ) ); // dodaje wiadomosc do nowej wersji grafu, wersji grafu z nastepnej rundy
		ILE_KOMUNIKATOW++;
	}
			

};
//********************************* KONIEC KLASY  WERT, CIAG DLASZY PRZESTREZNI NAZW SYMULATOR



	int which_vertex = 0;	
	vector<vert> graph, graph_copy;
	
	
	// funkcja tworzy w tab ring na N wierzcholkach, UWAGA, TWORZONY JEST RING NJIEZORIENTOWANY!!!
	void createRing( int N ){
		number_of_vertices = N;
		graph.clear();
		REP(i,N) graph.PB( vert( N, &graph, &graph_copy ) );
		REP(i,N)	graph[i].neighbours.PB( (i+1)%N );		
		REP( i,N ) graph[ (i+1)%N ].neighbours.PB(i); // w tej petli tworze ring - dodaje odpowiednio sasiadow :)
		REP(i,N) random_shuffle( ALL( graph[i].neighbours ) );
		graph_copy = graph;
	}
	
	// funkcja visualize wywoluje dla kazdego wierzcholka grafu funkcje writeState odpowiedzialna za wpisania informacji o danym wierzcholku
	void visualize(){
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
			REP(i, SIZE(graph_copy) ) graph_copy[i].kom = VVN( number_of_vertices, VN() );
		//	cout << "Powrocilem do \"konsoli\" " << endl;
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
	
	cout << "Podaj ilosc wierzcholkow, ktore chcesz miec w ringu:\t";
	int N;
	cin >> N;
	
	createRing(N);
	cout << "Oto twoj ring" << endl;
	writeGraph();
	ENDL(2);
	
	ILE_KOMUNIKATOW = 0;
	
	cout << "Aby wykonac kolajna runde, wybierz 'r' i zatwierdz ENTER" << endl
		<< "Aby wyswietlic stan wierzcholkow, wybierz 'v' i zatwierdz ENTER" << endl
		<< "Aby wyczyscic ekran wybierz 'P' i zatwierdz ENTER" << endl;
	
	char znak;
	int round_nr = 0;
	while( cin >> znak ){ // aby symulowac nastepna runde nalezy wpisac r i ENTER :)
		if( znak == 'r' ){
			cout << "Round nr " << ++round_nr << endl;
			nextRound();
			ENDL(0);
		}
		else if( znak == 'v' ){ // aby wyswietlic stan wierzcholkow wcisnij 'v' ( jak visualize )
			visualize();
			ENDL(1);
		}
		else if( znak == 'P' ) system("clear"); // aby wyczyscic ekran wcisnij 'P'
				
	}
	
}











