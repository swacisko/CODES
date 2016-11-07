//#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
#include<map>
//#include<complex>
//#include<stack>
//#include<list>
//#include<bitset>
#include<set>
#include<iterator>
#include<cmath>
//#include<queue>
//#include<time.h>
//#include<string.h>
//#include<fstream>
//#include<sstream>
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



// jest to struktura reprezentujaca slownik slow bazowych
// dla danego slowa tworzy sie slownik jako preprocessing w czasie O( n(lgn)^2 ) - ale to jest tylko przez sortowanie, wiec generalnie O(nlgn)
// po tym preprocessingu mozna w czasie stalym porownywac leksykograficznie jego dowolne podslowa - funkcja compare
struct KMR{
	
	string word; // to jest slowo, dla ktorego buduje slownik slow bazowych
	map<PII,int> mapa; // mapa przyporzadkowujaca kazdej parze liczb jakas inna liczbe - identyfikator, para(0,X) oznacza pojedyncza litere, a nie dwa przedzialy
	set<char> zbior; // kazdej literze na poczatku trzeba przypisac identyfikator leksykograficznie
	VVI V; // to jest wektor zawierajacy identyfikatory.  V[i][k] to identyfikator podslowa o poczatku na pozycji i oraz dlugosci 2^k
	int id;
	
	KMR( string s ){
		word = s;
		id = 1;
		mapa.clear();
		zbior.clear();
		V = VVI( SIZE(word) ); // towrze wektor, do ktorego bede push_back'owal odpowiednie identyfikatory
		
		createKMR();
	}
	
	// funkcja przypisujaca kazdej literze identyfikator
	void assignLetters(){
		REP(i,SIZE(word)){ // w tej petli wybieram wszystkie litery wystepujace w moim slowie
			if( !zbior.count( word[i] ) ){
				zbior.insert( word[i] );
			}
		}
		
		map<char, int> mapka;		
		FOREACH(it,zbior) mapka[ *it ] = id++; // mapka[ c ] to identyfikaotr litery c		
		REP( i,SIZE(V) ) V[i].PB( mapka[ word[i] ] );		// po tej petli V[i][0] to identyfikator litery
	}
	
	// funkcja tworzaca juz do konca wektor V, czyli wlasciwy slownik slow bazowych
	void assignIdentifiers(){
		int t = 0, l = 2; // uwaga, l = 2^t oznacza dlugosc dla ktorej tworzymy identyfikatory
		VPII ident; // wektor zawierajacy pary z mapy, ktory bedziemy sortowac
		while( l <= SIZE(word) ){ // dopoki dlugosc nie przekracza dlugosci slowa
			ident.clear();
		//		REP(i,SIZE(V)) while( SIZE(V[i]) < t ) V[i].PB(0);
			
			for( int i = 0; i+l-1 < SIZE(word); i++ ){				
				if( !mapa.count( MP(  V[i][ t ], V[i+l/2][ t ]  ) ) ){ // jesli w mapie nie ma pary, ktora teraz przerabiam
					mapa[ MP(  V[i][ t ], V[i+l/2][ t ]  ) ] = INF; // na razie przypisuje sztuczny identyfikator, bo jeszcze nie wiem jaki bedzie mial numer
					ident.PB( MP( V[i][ t ], V[i+l/2][ t ] ) );
				}
			}
			
			sort( ALL(ident) ); // sortuje wszystkie pary
			REP(i,SIZE(ident)) mapa[ ident[i] ] = id++; // przypisuje  odpowiednie identyfikatory dla par w mapie
			
			for( int i = 0; i+l-1 < SIZE(word); i++ ){				
				V[i].PB(  mapa[ MP(  V[i][ t ], V[i+l/2][ t ]  ) ]  ); // przypisuje identyfikatory do wektora V, czyli glownego slownika KMR
			}
			
			t++;
			l<<=1;
		}		
	}
	
	// funkcja tworzaca wektor V zawierajacy identyfikatory
	void createKMR(){		
		assignLetters();
		assignIdentifiers();	
		
	}
	
	
	// funkcja porownujaca dwa podslowa w stringu   word.  Zwraca -1 jesli podslowo [start1...end1] < [start2...end2], 0 jesli sa rowne   oraz 1 jesli > leksykograficznie
	// funkcja dziala dla podslow roznej dlugosci, wiec mozna sprawdzic jak sie maja do siebie leksykograficznie dwa podslowa roznej dlugosci. Oczywiscie wtedy nigdy funkcja nie zwroci 0
	// jezeli slow s1 jest prefiksem slowa s2, przy czym gludosc s1 < dlugosc s2   to funkcja zwroci -1
	// funcja dziala w czasie stalym
	int compare( int start1, int end1, int start2, int end2 ){
		int t = 0, l = 1;
		int start = ( ( end1 - start1 < end2 - start2 ) ? start1 : start2 ); // to jest poczatek krotszego z podslow
		int end = ( ( end1 - start1 < end2 - start2 ) ? end1 : end2 ); // to jest koniec krotszego z podslow
		
		t = (int) log2( (double)( end - start + 1 ) ); // zamiast tego moze byc ponizszy while, ktory mi wyznacza odpowiedni index
		/*while( (l<<1) <= end - start + 1 ){
			t++;
			l <<= 1;
		}*/
		l = end - start + 1; // to jest dlugosc krotszego z tekstow
		l -= (int) pow(2,t);
		int v1 = V[start1][t];
		int v2 = V[ start1+l ][t];
		int w1 = V[start2][t];
		int w2 = V[ start2+l ][t];
		
		if( v1 < w1 ) return -1;
		else if( v1 > w1 ) return 1;
		else if( v2 < w2 ) return -1;
		else if( v2 > w2 ) return 1;
		else if( end1 - start1 == end2 - start2 ) return 0;
		else return (  ( end1 - start1 < end2 - start2 ) ? -1 : 1 );	
	}
	
	// funkcja wypisujaca zawartosc wektora V - tylko do sprawdzenia identyfikatorow, czy sa poprawnie
	void write(){
		WRITE_ALL(V,"Wektor V:",0);
	}



};




int main(){
	
	cout << "Podaj slowo dla ktorego chcesz stworzyc slownik:  ";
	string s;
	cin >> s;
	KMR slownik(s);
	
//	slownik.write();
	
	int start1, end1, start2, end2;
	while(true){
		cout << "Podaj poczatek i koniec pierwszego podslowa: ";
		cin >> start1 >> end1;
		cout << endl << "Podaj poczatek i koniec drugiego podslowa: ";
		cin >> start2 >> end2;
		
		cout << "Oto wynik pracy KMR:" << endl;
		cout << s.substr( start1, end1-start1+1 );
		int wyn = slownik.compare( start1, end1, start2, end2 );
		switch(wyn){
			case -1:{
				cout << " < ";
				break;
			}
			case 0:{
				cout << " == ";
				break;
			}
			case 1:{
				cout << " > ";
				break;
			}
			default:{
				
			}
		}
		
		cout << s.substr( start2, end2-start2+1 ); 
		ENDL(2);
	}
	
	
	
}












