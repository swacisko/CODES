
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


const int NORTH = 0;
const int EAST = 1;
const int SOUTH = 2;
const int WEST = 3;


// klasa reprezentujaca komunikat
// wektor obiektow tej klasy jest przechowywany przez kazdy z wierzcholkow - obiektow klasy vert
class notif{
public:
//	notif(){}
	notif( VI mess, int fr ) : idnrs(mess), from(fr) {}
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
	VI idnrs;
	int N;
	
	void updateRoundData(){
		(*graph_copy)[id].which_case = which_case;
		(*graph_copy)[id].round_nr = round_nr;
		(*graph_copy)[id].idnrs = idnrs;
		(*graph_copy)[id].N = N;
	}
		
	//**********************************

	// jako parametr przyjmuje ilosc wierzcholkow lacznie w grafie, w ktorym jest tworzony ten wierzcholek
	// N jest potrzebne tylko do inicjalizacja tablicy kom
	vert( int N = 0, vector<vert> *wsk = 0, vector<vert> *wsk_copy = 0 ) : HOW_MANY_CASES(3), kom( VVN(N, VN() ) ), graph(wsk), graph_copy(wsk_copy) {
		id = next_id++;
		id_los = rand() % 130;
		which_case = 0;
		round_nr = 0;
		idnrs = VI( N,INF );
		idnrs[id] = id_los;
		this->N = (int)sqrt( number_of_vertices+1 );
	//	V = VVI( number_of_vertices );
	//	REP(i,SIZE(neighbours)) V[id].PB(neighbours[i]);
	}
	
	void rewrite( VI v ){
		if( SIZE(v) != SIZE(idnrs) ) cout << "BLAD rozmiaru tablic id = " << id << "  idnrs.size()=" << idnrs.size() << "  v.size()=" << v.size() << endl;
		REP(i,SIZE(idnrs)) idnrs[i] = min( idnrs[i], v[i] );
	}

	// execute to funkcja w ktorej powinien znajdywac sie glowny kod programu
	// zamiat fiber_yield jest switch, ktory wykonuje odpowiedni kod
	void execute(){
		
		switch( which_case ){
			case 0:{
				//cout << "id = " << id << "  jestem w case 0" << endl;
				//cout << "\tmam sasiadow:\t"; REP(i,4) cout << neighbours[i] << " "; cout << endl;
				
				if( round_nr == 0 ){ // jesli to pierwsza runda, to trzeba jakos rozpoczac...
					if( neighbours[NORTH] == -1 ) sendMessage( neighbours[SOUTH], idnrs );
					if( neighbours[SOUTH] == -1 ) sendMessage( neighbours[NORTH], idnrs );				
				}
				else{
					notif nfn, nfs;
					
					if( neighbours[NORTH] != -1 ) nfn = getLatestMessage( neighbours[NORTH] );
					if( neighbours[SOUTH] != -1 ) nfs = getLatestMessage(neighbours[SOUTH]);
					
					if( nfn.liczba != notif::BLANK ){
						cout << "id = " << id << " odebralem wiadomosc od wierzcholka z gory" << endl;
						rewrite( nfn.idnrs );						
						if( neighbours[SOUTH] != -1 ) sendMessage( neighbours[SOUTH],idnrs );
					}
					if( nfs.liczba != notif::BLANK ){
						cout << "id = " << id << " odebralem wiadomosc od wierzcholka z dolu" << endl;
						rewrite( nfs.idnrs );
						if( neighbours[NORTH] != -1 ) sendMessage( neighbours[NORTH],idnrs );
					}
					
					
					
				}
				
				round_nr++;
				if( round_nr == N+1 ){
					which_case++;
					round_nr = 0;
				}
				break;				
			}
			case 1:{
				if( round_nr == 0 ){ // jesli to pierwsza runda, to trzeba jakos rozpoczac...
					if( neighbours[EAST] == -1 ) sendMessage( neighbours[WEST], idnrs );
					if( neighbours[WEST] == -1 ) sendMessage( neighbours[EAST], idnrs );				
				}
				else{
					notif nfe, nfw;
					
					if( neighbours[EAST] != -1 ) nfe = getLatestMessage( neighbours[EAST] );
					if( neighbours[WEST] != -1 ) nfw = getLatestMessage(neighbours[WEST]);
					
					if( nfe.liczba != notif::BLANK ){
						cout << "id = " << id << " odebralem wiadomosc od wierzcholka z prawej strony" << endl;
						rewrite( nfe.idnrs );
						if( neighbours[WEST] != -1 ) sendMessage( neighbours[WEST],idnrs );
					}
					if( nfw.liczba != notif::BLANK ){
						cout << "id = " << id << " odebralem wiadomosc od wierzcholka z lewej strony" << endl;
						rewrite( nfw.idnrs );
						if( neighbours[EAST] != -1 ) sendMessage( neighbours[EAST],idnrs );
					}
					
					
					
				}
				
				
				
				round_nr++;
				if( round_nr == N+1 ){
					which_case++;
					round_nr = 0;
				}
				
				
				break;
			}
			case 2:{
				cout << "KONIEC!  id = " << id << "  id_los = " << id_los << endl; /* << "   oto lista id, ktora ja znam:" << endl;
				REP( i, SIZE(idnrs) ){
					cout << "\tWierzcholek o id = " << i << "  ma id_los = " << idnrs[i] << endl;
				}
				*/
				
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
		cout << "Oto co wiem o id innych wierzcholkow(ktore znam)..." << endl;
		REP(i,SIZE(idnrs)){
			if( idnrs[i] != INF )cout << "\tWierzch nr " << i << " ma id_los = " << idnrs[i] << endl;
		}
		
		ENDL(1);		
	}
	
	// funkcja wysyla sasiadowi nr sock wiadomosc mess
	void sendMessage( int sock, VI mess ){
		(*graph_copy)[ sock ].kom[id].PB( notif( mess,id_los ) ); // dodaje wiadomosc do nowej wersji grafu, wersji grafu z nastepnej rundy
	}
			

};
//********************************* KONIEC KLASY  WERT, CIAG DLASZY PRZESTREZNI NAZW SYMULATOR



	int which_vertex = 0;	
	vector<vert> graph, graph_copy;
	
	
	void createMesh( int N ){
		number_of_vertices = N*N;
		REP(i,N*N) graph.PB( vert( N*N, &graph, &graph_copy ));
		REP(i,N){
			REP(k,N){
				if( i > 0 ) graph[i*N + k].neighbours.PB( (i-1)*N + k );
				else graph[i*N + k].neighbours.PB( -1 ); // jesli nie mam takiego sasiada bo jestem na boku siatki, to dolaczam -1
				
				if( k < N-1 ) graph[i*N + k].neighbours.PB( i*N + k+1 );
				else graph[i*N + k].neighbours.PB( -1 );
				
				if( i < N-1 ) graph[i*N + k].neighbours.PB( (i+1)*N + k );
				else graph[i*N + k].neighbours.PB( -1 );
				
				
				if( k > 0 ) graph[i*N + k].neighbours.PB( i*N + k-1);
				else graph[i*N + k].neighbours.PB( -1 );
				
			}			
		}
		
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
	
	cout << "Podaj dlugosc boku kraty:\t";
	int N;
	cin >> N;
	if( N == 1 ){
		cout << "Krata 1-elementowa?" << endl;
		return 0;
	}
	
	createMesh(N);
	cout << "Oto twoja krata:" << endl;
	REP(i,N){
		REP(k,N) cout << setw(3) << i*N + k << " ";
		cout << endl;
	}
	
/*	REP(i,N){
		REP(k,N){
			cout << i*N+k << " -> ";
			REP(t,4) cout << graph[i*N+k].neighbours[t] << " ";
			cout << endl;			
		}
		
		
	}*/
	
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












