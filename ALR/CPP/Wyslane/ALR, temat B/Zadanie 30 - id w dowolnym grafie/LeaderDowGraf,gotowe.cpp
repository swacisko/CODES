
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
#include<iomanip>

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


int START;


// klasa reprezentujaca komunikat
// wektor obiektow tej klasy jest przechowywany przez kazdy z wierzcholkow - obiektow klasy vert
class notif{
public:
//	notif(){}
//	notif( VI mess, int fr ) : idnrs(mess), from(fr) {}
	notif( int l = BLANK, int fr=-1 ) : liczba(l), from(fr) {}
//	notif( VVI v, int fr ) : V(v), from(fr) {}
//	notif( string s, int l ) : str(s), liczba(l) {}
//	string str;
	int liczba;	
	int from;
	VI idnrs;
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
	vector<vert> *graph_copy; // uwaga!! tego nie mozna uzywac, tworzac wlasny program, to jest tylko do symulowania rund programu
	
	//************* TUTAJ JEST CZESC, GDZIE DODAJE NOWE DANE, TYPOWE DLA KONKRETNEGO ZADANIA
	
	int round_nr;
	int par_id_los;
	set<int> was;
	bool isLeader;
	
	void updateRoundData(){
		(*graph_copy)[id].which_case = which_case;
		(*graph_copy)[id].round_nr = round_nr;
		(*graph_copy)[id].par_id_los = par_id_los;
		(*graph_copy)[id].was = was;
		(*graph_copy)[id].isLeader = isLeader;
	}
		
	//**********************************

	// jako parametr przyjmuje ilosc wierzcholkow lacznie w grafie, w ktorym jest tworzony ten wierzcholek
	// N jest potrzebne tylko do inicjalizacja tablicy kom
	vert( int N = 0, vector<vert> *wsk = 0, vector<vert> *wsk_copy = 0 ) : HOW_MANY_CASES(2), kom( VVN(N, VN() ) ), graph(wsk), graph_copy(wsk_copy) {
		id = next_id++;
		id_los = rand() % 1000;
		which_case = 0;
		round_nr = 0;
		par_id_los = -1;
		isLeader = true;
		was.clear();
	//	V = VVI( number_of_vertices );
	//	REP(i,SIZE(neighbours)) V[id].PB(neighbours[i]);
	}
	

	// execute to funkcja w ktorej powinien znajdywac sie glowny kod programu
	// zamiat fiber_yield jest switch, ktory wykonuje odpowiedni kod
	void execute(){
		
		switch( which_case ){
			case 0:{
				if( round_nr == 0 ){
					REP(i,SIZE(neighbours)) sendMessage(neighbours[i], id_los, id_los);
				}
				
				notif nf;
				REP(i,SIZE(neighbours)){
					nf = getLatestMessage(neighbours[i]);
					if( nf.liczba != notif::BLANK ){
						if( !was.count( nf.from ) ){
							was.insert( nf.from );
							int mx = max( id_los, nf.liczba );
							if( mx > id_los ) isLeader = false;
							
							REP( k,SIZE(neighbours) ){
								if( k != i ){
									if( mx == nf.from ) sendMessage( neighbours[k], mx, nf.from );
									else sendMessage( neighbours[k], mx, nf.from );									
								}
							}							
						}						
					}
				}
				
				
				round_nr++;
				if( round_nr > number_of_vertices+2 ){
					which_case++;
				}
				break;				
			}
			case 1:{
				if( isLeader ) cout << "id = " << setw(2) << id << "   id_los = " << setw(3) << id_los << "  JESTEM LEADEREM!!!" << endl;
				
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
		cout << "Jestem wierzcholkiem o id = " << setw(2) << id << "  id_los = " << setw(3) << id_los << "   isLeader = " << isLeader << endl;		
	}
	
	// funkcja wysyla sasiadowi nr sock wiadomosc mess
	void sendMessage( int sock, int val, int from ){
		(*graph_copy)[ sock ].kom[id].PB( notif( val, from ) ); // dodaje wiadomosc do nowej wersji grafu, wersji grafu z nastepnej rundy
	}
			

};
//********************************* KONIEC KLASY  WERT, CIAG DLASZY PRZESTREZNI NAZW SYMULATOR



	int which_vertex = 0;	
	vector<vert> graph, graph_copy;
	
	
	void createRandomGraph( int N ){
		number_of_vertices = N;
		REP(i,N) graph.PB(vert(N,&graph,&graph_copy));
		
		REP(i,N){
			FOR(k,i+1,N-1){
				if(k!=i){
					if( rand()%(N-1) <= 2 ){
						graph[i].neighbours.PB(k);
						graph[k].neighbours.PB(i);
					}
				}
			}
		}		
		
		graph_copy = graph;				
	}
	
	
	// funkcja visualize wywoluje dla kazdego wierzcholka grafu funkcje writeState odpowiedzialna za wpisania informacji o danym wierzcholku
	void visualize(){
		cout << "SIZE(graph) = " << SIZE(graph) << endl;
		REP(i,SIZE(graph) ){
			 graph[i].writeState();
			 //ENDL(1);
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
	
	cout << "Podaj ilosc wierzcholkow grafu:\t";
	int N;
	cin >> N;
	
	cout << endl << "Czy chcesz stworzyc wlasny graf? Jesli tak to wpisz TAK i zatwierdz\n\tJesli nie to wpisz cokolwiek innego i zatwierdz..." << endl;
	string s;
	cin >> s;
	
	START = 0;
	if( s == "TAK" || s == "tak" ){
		cout << endl << "Tworzysz graf skierowany. Podawaj krawedzie, jakie chcesz dodawac.\nWierzcholki liczone od 0 do N-1" << endl
			<< "Jesli nie chcesz juz wiecej dodac, wpisz -1" << endl;
		REP(i,N) graph.PB( vert(N,&graph,&graph_copy) );
		number_of_vertices = N;
		int a,b;
		while( cin >> a ){
			if(a==-1)break;
			cin >> b;
			graph[a].neighbours.PB(b);
			graph[b].neighbours.PB(a);
		}
		graph_copy = graph;
			
	}
	else{
		createRandomGraph(N);
	} 
	
	
	cout << "Oto twoj graf:" << endl;
	writeGraph();
	/*	REP(i,N){
		cout << "Sasiedzi wierzcholka " << i << " to:\t" << flush;
		REP(k,SIZE(graph[i].neighbours)) cout << graph[i].neighbours[k] << " ";
		cout << endl;
	}*/
	
	
	cout << endl << "Aby wykonac kolajna runde, wybierz 'r' i zatwierdz ENTER" << endl
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












