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
#include<conio.h>

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
	notif( int l ) : liczba(l), str("") {}
	notif( string s ) : str(s), liczba(0) {}
//	notif( string s, int l ) : str(s), liczba(l) {}
	string str;
	int liczba;	
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
	
	int par;
	string color;
	
	void updateRoundData(){
		(*graph_copy)[id].which_case = which_case;
		(*graph_copy)[id].color = color;
		(*graph_copy)[id].par = par;
	}
	
	// funkcja zamienia id na string
	void convertIdToString(){
		int ile = 0;
		while( ( 1 << ile ) <= id_los ){
			if( id_los & ( 1 << ile ) ) color[ile] = '1';
			ile++;
		}
	}
	
	// funkcja zwraca color bez koncowych zer
	string cutColor(){
		string T = "";
		int t = 0;
		REP(i,SIZE(color)) if( color[i] == '1' ) t = i;
		REP(i,t+1) T += color[i];
		return T;
	}
	
	// funkcja zwraca string odwrocony liczby, tzn dla liczby 8 zwroci "0001"
	string parseString( int n ){
		if( n == 0 ) return "0";
		int ile = 0;
		string s = "";
		while( (1<<ile) <= n ){
			if( n & (1<<ile) ) s += '1';
			else s += '0';
			ile++;
		}
		return s;
	}
	
	// funkcja zwraca kolor zapisany w postaci binarnej w poprawnej kolejnosci, tzn "0001000000000..." zostanie zwrocone jako "1000"
	string getProperColor( string s ){
		int ind = 0;
		REP(i,SIZE(s)) if( s[i] == '1' ) ind = i;
		string T = ""; FOR(i,0,ind) T += s[i];
		reverse( ALL(T) );
		return T;		
	}
	
	// zwraca inta odpowiadajacego danemu stringowi, s musi byc przeslany w poprawnej, nieodrwoconej kolejnosci
	int parseInt( string s ){
		int r = 0;
		REP( i, SIZE(s) ){
			if( s[i] == '1' ) r += ( 1 << ( SIZE(s)-i-1 ) );
		}
		return r;
	}
	
	//**********************************

	// jako parametr przyjmuje ilosc wierzcholkow lacznie w grafie, w ktorym jest tworzony ten wierzcholek
	// N jest potrzebne tylko do inicjalizacja tablicy kom
	vert( int N = 0, vector<vert> *wsk = 0, vector<vert> *wsk_copy = 0 ) : HOW_MANY_CASES(2), kom( VVN(N, VN() ) ), graph(wsk), graph_copy(wsk_copy) {
		id = next_id++;
		id_los = rand() % 130;
		which_case = 0;
		par = -1;
		color = string( 30, '0' ); // dla pewnosci zeby nigdy nie wyjsc poza zakres ustawiam 30 zer :)
	}
	
	

	// execute to funkcja w ktorej powinien znajdywac sie glowny kod programu
	// zamiat fiber_yield jest switch, ktory wykonuje odpowiedni kod
	void execute(){
		
		switch( which_case ){
			case 0:{
				REP( i, SIZE(neighbours) ) sendMessage( neighbours[i], color );
				
				which_case = 1;	
				break;				
			}
			case 1:{				
				if( par == -1 ){
					REP( i, SIZE(neighbours) ) sendMessage( neighbours[i], color );
					break;	
				}
								
				int ind = 0;
				string par_color = getLatestMessage( par ).str;
				while( ind < SIZE(color) && color[ind] == par_color[ind] ) ind++;
				if( ind >= 30 ){
					ENDL(5);
					cout << "GDZIES MUSI BYC BLAD, IND = " << ind << ",  A POWINNO BYC < 30 !!!" << endl;
					ENDL(5);
					break;
				}
				cout << "id = " << id << "  color = " << cutColor() << "   par_color = " << flush; REP(i,10) cout << par_color[i]; cout << endl;
				cout << "\tind = " << ind << endl;
				
				color = color[ind] + parseString(ind);
				while( SIZE(color) < 30 ) color += '0';
				
				REP( i, SIZE(neighbours) ) sendMessage( neighbours[i], color ); // wysylam do wszystkich synow swoj wlasny kolor
				
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
		notif s( notif::BLANK );
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
		cout << "\tcolor = " << cutColor() << "  color->parseInt = " << parseInt( getProperColor(color) ) << endl << "\tpar = " << par << "  synowie:  ";
		REP(i,SIZE(neighbours)) cout << neighbours[i] << " ";
		ENDL(1);		
	}
	
	// funkcja wysyla sasiadowi nr sock wiadomosc mess
	void sendMessage( int sock, string mess ){
		(*graph_copy)[ sock ].kom[id].PB( notif( mess ) ); // dodaje wiadomosc do nowej wersji grafu, wersji grafu z nastepnej rundy
	}
			

};
//********************************* KONIEC KLASY  WERT, CIAG DLASZY PRZESTREZNI NAZW SYMULATOR



	int which_vertex = 0;	
	vector<vert> graph, graph_copy;
	int number_of_vertices; // to jest ilosc wierzcholkow  w tworzonym grafie
	
	// funkcja dodaje do grafu graph dane z drzewa V tak, aby w graph byla reprezentacja drzewa ukorzenionego. Jako poczatek biore wierzcholek nr nr
	void addTreeDfs( VVI V, int nr, int par = -1 ){
		REP( i, SIZE(V[nr]) ){
			if( V[nr][i] != par ){
				graph[nr].neighbours.PB( V[nr][i] );
				addTreeDfs( V, V[nr][i], nr );
			}
			else graph[nr].par = par;
		}
	}
	
	void convertColors(){
		REP( i, SIZE(graph) ) graph[i].convertIdToString();		
	}
	
	// funkcja tworzy w tab ring na N wierzcholkach
	void createTree( int N ){
		number_of_vertices = N;
		graph.clear();		
		REP(i,N) graph.PB( vert( N, &graph, &graph_copy ) );
		
		VVI V = generateTree(N);
		addTreeDfs( V, 0 );
		convertColors();	
		
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
	
	createTree(10);
	writeGraph();
	ENDL(2);
	
	char znak;
	int round_nr = 0;
	while( znak = getch() ){ // aby symulowac nastepna runde nalezy wpisac r i ENTER :)
		if( znak == 'r' ){
			cout << "Round nr " << ++round_nr << endl;
			nextRound();
			ENDL(2);
		}
		else if( znak == 'v' ){ // aby wyswietlic stan wierzcholkow wcisnij 'v' ( jak visualize )
			visualize();
			ENDL(2);
		}
		else if( znak == 'P' ) system("cls"); // aby wyczyscic ekran wcisnij 'P'
				
	}
	
}












