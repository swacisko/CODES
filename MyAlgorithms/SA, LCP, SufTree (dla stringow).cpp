//#include<stdio.h>
#include<iostream>
#include<vector>
//#include<string>
#include<map>
//#include<complex>
#include<stack>
//#include<list>
//#include<bitset>
#include<set>
#include<iterator>
#include<cmath>
//#include<queue>
#include<ctime>
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

/*
JEst to wlasne drzewo przedzialowe, w ktorym wszystkie operacje wykonywane sa od gory
Nie jest wiec to najszybsze drzewo, ale operacje wstawiania i znajdywania sa logarytmiczne
Tutaj pokrywa sie liczby od 0 do N, a nie przedzialy   -   jesli chcesz pokryc przedzialy musisz utozsamic liczbe 0 z przedzialem 0-1, liczbe 1 z przedzialem 1-2,  itd.

*/

struct CTree{
	#define NR (p1+k1)/2
	typedef int _T; // to co ma byc przechowywane w wezlach
	typedef pair<_T, int> PTT;
	int N; // ilosc liczb, na ktorych chcemy operowac, tzn jesli chcemy operowac na 5 liczbach, to potrzebujemy stworzyc tablice rozmiarow 2 * 8
	int s; // jest to liczba bedaca najmniejsza potega dwojki, nie mniejsza niz N, UWAGA - liczba   L do ktorej chcemy sie odniesc jest w tablicy tab na miejscu s + L
	_T* sum; // tablica sumy elementow w danym przedziale - w zasadzie to reprezentuje tylko liczby, ktore wstawiamuy do drzewa, zadnych sum nie przechowuje w wezlach, bo sie nie da :)
	_T* el; // tabllica reprezentujaca ilosc przedzialow pokrywajacych dany wezel
	PTT* _min; // tablica par oznaczajacych mimimum na danych przedziale oraz index tego minimum
	PTT* _max; // ---|--- maksimum ---|---
	int size; // rozmiar tablicy tab(i innych jesli beda)
	int p,k; // liczby p oraz k oznaczaja poczatek i koniec przedzialu, ktory chcemy dodac
	_T l; // l oznacza ilosc 'przedzialow' jakie chcemy dodac



	// konstruktor przyjmujacy jako wartosc maksymalna liczbe, na ktorej bedziemy wykonywac operacje, tzn tab bedzie reprezentowac liczby 0,1,2,...,N-1   !!!
	CTree( int aN = 0 ) : N(aN), s(1) {
		while( s <= N ) s <<= 1;
		size = (s << 1 );

		sum = new _T[size];
		el = new _T[size];
		_min = new PTT[size];
		_max = new PTT[size];
		REP(i,size){
			sum[i] = 0;
			el[i] = 0;
			_min[i].ST = INF; _min[i].ND = INF;
			_max[i].ST = -INF; _max[i].ND = INF;
		}
	}

	// tworzenie drzewa dla danej tablicy liczb w czasie liniowym, a nie liniowo-logarytmicznym
	// uwaga, do elementow tablic reprezentujacych element i przypisany zostanie element vac[i]
	CTree( const vector<_T> & vec ) : N(SIZE(vec)), s(1){
		while( s <= N ) s <<= 1;
		size = (s << 1 );
		sum = new _T[size];
		el = new _T[size];
		_min = new PTT[size];
		_max = new PTT[size];
		REP(i,size){
			sum[i] = 0;
			el[i] = 0;
			_min[i].ST = INF; _min[i].ND = INF;
			_max[i].ST = -INF; _max[i].ND = INF;
		}

		REP(i,SIZE(vec)) sum[s+i] = vec[i];
		FORD(i,s-1,1) sum[i] = sum[2*i] + sum[2*i+1]; // przypisuje sume do wszystkich elementow
		REP(i,SIZE(vec)){
			_min[s+i].ST = _max[s+i].ST = sum[s+i]; // wartosc w lisciach
			_min[s+i].ND = _max[s+i].ND = i; // nr indexu
		}

		FORD( i,s-1,1 ){
			_min[i] = ( _min[2*i].ST <= _min[2*i+1].ST ? _min[2*i] : _min[2*i+1] ); // UWAGA, tutaj od znokow zalezy, index ktorego z elementow o tej samej wartosci zostanie zwrocony!!
			_max[i] = ( _max[2*i].ST >= _max[2*i+1].ST ? _max[2*i] : _max[2*i+1] ); // jelsi jest <= lub >= to zostanie zwrocony najmniejszy index danewgo ekstremum
		}
	}

	~CTree(){
		delete[] sum; sum = 0;
		delete[] el; el = 0;
		delete[] _min; _min = 0;
		delete[] _max; _max = 0;
	}

	// p1 - poczatek przedzialu reprezentowanego przez wezel,  k1 - koniec przedzialu repr.przez wezel,  g - numer wezla
	void help_add( int p1, int k1, int g ){
		if( p1 > k || k1 < p ) return; // jesli przedzialy sa rozlaczne, to nic nie robie
		if( p1 >= p && k1 <= k ){ // jesli wstawiany przedzal zawiera w calosci przedzial reprezentowany przez wezel to...
			sum[g] += l*( min( k,k1 ) - max( p,p1 ) + 1 );
			el[g] += l;
			_min[g].ST += l;
			_max[g].ST += l;
			return;
		}

		// w przeciwnym razie rozbijam wezel na 2 podwezly
		help_add( p1, NR, 2*g );
		help_add( NR + 1, k1, 2*g+1 );

		int overlap = min( k,k1 ) - max( p,p1 ) + 1;
		sum[g] = sum[2*g] + sum[2*g+1] + overlap*el[g];
		_min[g] = ( _min[2*g].ST <= _min[2*g+1].ST ? _min[2*g] : _min[2*g+1] ); // UWAGA, tutaj od znokow zalezy, index ktorego z elementow o tej samej wartosci zostanie zwrocony!!
		_max[g] = ( _max[2*g].ST >= _max[2*g+1].ST ? _max[2*g] : _max[2*g+1] ); // jelsi jest <= lub >= to zostanie zwrocony najmniejszy index danewgo ekstremum
		_min[g].ST += el[g];
		_max[g].ST += el[g];
	}

	void Add( int p1, int k1, int l1 ){
		p = p1;		k = k1;		l = l1;
		help_add( 0,s-1,1 );
	}


	// p1 - poczatek przedzialu reprezentowanego przez wezel,  k1 - koniec przedzialu repr.przez wezel,  g - numer wezla
	_T help_sum( int p1, int k1, int g ){
		if( p1 > k || k1 < p ) return 0; // jesli przedzialy sa rozlaczne, to nic nie robie
		if( p1 >= p && k1 <= k ) return sum[g]; // jesli wstawiany przedzal zawiera w calosci przedzial reprezentowany przez wezel to zwracam wartosc sum danego wezla
												// poniewaz wartosc sum jest aktualizowana w help_add, wiec teraz nie musze dodawac iloscynu dlugosci przedzialu z el[g]
		int overlap = min( k,k1 ) - max( p,p1 ) + 1;
		return ( help_sum( p1,NR, 2*g ) + help_sum( NR + 1, k1, 2*g+1 ) + overlap*el[g]  ); // ale tutaj dodaje wartosci znalezione w podwezlach plus ilosc pokryc danego wezla
	}

	_T FindSum( int p1, int k1 ){
		p = p1;		k = k1;
		return help_sum( 0,s-1,1 );
	}


	// p1 - poczatek przedzialu reprezentowanego przez wezel,  k1 - koniec przedzialu repr.przez wezel,  g - numer wezla
	PTT help_min( int p1, int k1, int g ){
		if( p1 > k || k1 < p ) return MP( INF, INF ); // jesli przedzialy sa rozlaczne to zwracam cos co jest wieksze od wszystkiego
		if( p1 >= p && k1 <= k ) return _min[g]; // jesli caly przedzial jest zawarty, to zwracam minimum reprezentowane przez dany wezel
		PTT minpair = min( help_min( p1,NR,2*g ), help_min( NR + 1, k1, 2*g+1 ) ); // biore minimum z podwezlow
		minpair.ST += el[g];
		return minpair;
	}

	PTT FindMin( int p1, int k1 ){
		p = p1;		k = k1;
		return help_min(0,s-1,1);
	}



	PTT help_max( int p1, int k1, int g ){
		if( p1 > k || k1 < p ) return MP( -INF, -INF ); // jesli przedzialy sa rozlaczne to zwracam cos co jest wieksze od wszystkiego
		if( p1 >= p && k1 <= k ) return _max[g]; // jesli caly przedzial jest zawarty, to zwracam minimum reprezentowane przez dany wezel
		PTT maxpair = max( help_max( p1,NR,2*g ), help_max( NR + 1, k1, 2*g+1 ) ); // biore minimum z podwezlow
		maxpair.ST += el[g];
		return maxpair;
	}

	PTT FindMax( int p1, int k1 ){
		p = p1;		k = k1;
		return help_max(0,s-1,1);
	}



	void operator=( const CTree & oth ){
		delete[]sum; sum = 0;
		delete[]el; el = 0;
		delete[]_min; _min = 0;
		delete[]_max; _max = 0;

		size = oth.size;
		N = oth.N;
		s = oth.s;

		sum = new _T[ size ];
		el = new _T[ size ];
		_min = new PTT[ size ];
		_max = new PTT[ size ];

		REP(i,size){
			sum[i] = oth.sum[i];
			el[i] = oth.el[i];
			_min[i] = oth._min[i];
			_max[i] = oth._max[i];
		}

	}

};



// jest to struktura reprezentujaca slownik slow bazowych
// dla danego slowa tworzy sie slownik jako preprocessing w czasie O( n(lgn)^2 ) - ale to jest tylko przez sortowanie, wiec generalnie O(nlgn)
// po tym preprocessingu mozna w czasie stalym porownywac leksykograficznie jego dowolne podslowa - funkcja compare
struct KMR{
	string word; // to jest slowo, dla ktorego buduje slownik slow bazowych
	map<PII,int> mapa; // mapa przyporzadkowujaca kazdej parze liczb jakas inna liczbe - identyfikator, para(0,X) oznacza pojedyncza litere, a nie dwa przedzialy
	set<char> zbior; // kazdej literze na poczatku trzeba przypisac identyfikator leksykograficznie
	VVI V; // to jest wektor zawierajacy identyfikatory.  V[i][k] to identyfikator podslowa o poczatku na pozycji i oraz dlugosci 2^k
	int id;

	KMR(){}

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




// przestrzen nazw, w ktorej przechowywane sa tablice SA, LCP oraz LPF oraz wszystkie potrzebne algorytmy do ich wyznaczania
namespace SUF{

	string word;
	KMR dic; // slownik KMR dla danego slowa, la ktorego bede tworzyl tablice suf
	VI suf; // wektor intow, taki, ze suf[i] to index poczatku i-tego leksykograficznie sufiksu slowa word
	VI revsuf; // permutacja odwrotna do  tablicy suf, czyli  revSuf[i] to index, na ktorym w tablicy suf wystepuje wartosc i

	// funkcja do leksykograficznego porownywania sufiksow danego slowa za pomoca slownika KMR
	// jako parametry przyjmuje poczatek pierwszego i poczatek drugiego
	bool compFun( const int a, const int b ){
		return dic.compare( a,SIZE(word)-1, b, SIZE(word)-1 ) == -1;
	}

	// ta funkcja jest odpowiedzialna za stworzenie tablicy suf oraz revsuf
	void createSuf(){
		suf.clear();
		REP(i,SIZE(word)) suf.PB( i );
		sort( ALL(suf), compFun );
		revsuf = VI(SIZE(suf));
		REP(i,SIZE(suf)) revsuf[ suf[i] ] = i;
	}

	// to jest taki jakby konstruktor
	void SA( string s ){
		word = s;
		dic = KMR(s);
		createSuf();
	}

	// funkcja sluzaca do wypisania tablicy SA( czyli wektora suf)
	void writeSA(){
		cout << "Tablica suf:" << endl;
		REP(i,SIZE(word)){
			cout << "suf["<<i<<"] = " << suf[i] << " odpowiada suffixowi " << word.substr( suf[i] ) << endl;
		}
		cout << endl << "Tablica revsuf:" << endl;
		REP(i,SIZE(revsuf)) cout << "revsuf["<<i<<"] = " << revsuf[i] << endl;
		cout << endl;
	}

//************************************ tu jest czesc dotyczaca LCP

	CTree tree;
	VI lcp; // tablica lcp...   lcp[i] to dlugosc najdluzszego wspolnego prefiksu suffiksow reprezentowanych przez suf[i] oraz suf[i+1]... dlaego tez jest rozmiaru SIZE(suf)-1

	// funkcja przyjmuje jako parametry poczatki dwoch sufiksow slowa word
	// jako wartosc zwraca dlugosc najdluzszego prefixu tych sufiksow
	// to jest Brut, czyli sprawdza literka po literce
	int longestPrefix( int p, int k ){
		int ile = 0;
	//	cout << "\t\tp = " << p << "   k = " << k << "   word["<<p<<"] = " << word[p] << "    word["<<k<<"] = " << word[k] << endl;
		while( p < SIZE(word) && k < SIZE(word) && (word[p++] == word[k++]) ) ile++;
	//	cout << "\t\tp = " << p << "   k = " << k << "   Zwracam wartosc ile = " << ile << endl;
		return ile;
	}

	// funkcja tworzaca i wpelniajaca wektor lcp
	void createLCP(){
		lcp = VI(SIZE(word)-1);
		int ile = 0; // zmienna ile reprezentuje w danym obiegu petli wartosc lcp[ revsuf[i-1] ];
		REP(i,SIZE(word)){ // zaczynam od najdluzszego sufiksu, czyli od sufiksu na pozycji revsuf[0] w tablicy suf
			if( revsuf[i] == SIZE(word)-1 ){ // jesli to jest ostatni leksykograficznie sufiks slowa word, to go opuszczam, ale nastepna wartosc bede musial liczyc brutem(i tak liniowo :) )
				ile = 0;
				continue;
			}
			else if( i == 0 || revsuf[i] == SIZE(word)-2 || ( i > 0 && revsuf[i-1] == SIZE(word)-1 ) ) ile = lcp[ revsuf[i] ] = longestPrefix( suf[ revsuf[i] ], suf[revsuf[i]+1] );
		/*	else if( i == 0 ){ // jesli to jest pierwszy obieg petli, to musze liczyc od samego poczatku
				 lcp[ revsuf[i] ] = longestPrefix( suf[ revsuf[i] ], suf[revsuf[i]+1] );
				 ile = lcp[ revsuf[i] ];
			}*/
			else{ // w przeciwnym razie moge zaczac liczenie poczawszy od pozycji suf[i] + ile+
				lcp[ revsuf[i] ] = max( lcp[ revsuf[i-1] ]-1, 0) + longestPrefix( suf[revsuf[i]]+max(ile-1,0), suf[revsuf[i]+1]+max(ile-1,0) );
				ile = lcp[ revsuf[i] ];
			}

		//	if( revsuf[i] != SIZE(word)-1 ) cout << "lcp[ revsuf["<<i<<"] ] = " << "lcp["<<revsuf[i]<<"] = " << lcp[revsuf[i]] << endl;
		}
	}

	// to jest jakby konstruktor - dla danego slowa wywoluje sie ta funkcje, a po jej zakonczeniu jest gotowe wszystko co potrzeba do algorytmow z LCP
	void LCP( string s ){
		SA(s);
		createLCP();
		tree = CTree(lcp);
	}

	// funkcja jako parametr przyjmuje poczatek dwoch roznych suffixow
	// funkcja zwraca dlugosc najdluzszego wspolnego prefixu suffiksow slowa word rozpoczynajacych sie na indeksach p oraz k
	// funkcja dziala w czasie logarytmicznym O(lgN), gdzie N = SIZE(word) z powodu drzewa przedzialowego
	// za pomoca tej funkcji mozna rowniez wyznaczyc inna metoda tablice PREF, ktorej w tej przestrzeni nazw nie napisalem
	// wyglada na to ze dziala dobrze :)
	int longestDifSuf( int p, int k ){
		int ti = revsuf[p], tj = revsuf[k];
		int ka = min(ti,tj), Ka = max(ti,tj);
		if( ka == Ka ) return SIZE(word) - p;
		return tree.FindMin( ka, Ka-1 ).ST;
	}

	// funkcja zwracajaca ilosc roznych podslow w tekscie word
	int countSubwords(){
		int N = SIZE(word);
		int suma = 0;
		REP(i,SIZE(lcp)) suma += lcp[i];
		return (N*(N+1))/2 - suma;
	}


	// funkjca wypisujaca zawartosc tablicy LCP
	void writeLCP(){
		cout << "Tablica lcp:" << endl;
		REP(i,SIZE(lcp)) cout << "lcp["<<i<<"] = " << lcp[i] << " odpowiada najdluzszemu wspolnemu prefiksowi suffiksow " << word.substr( suf[i] ) << " oraz " << word.substr( suf[i+1] ) << endl;
		cout << endl;
	}


//******************************************  tutaj jest czesc dotyczaca algorytmu  LPF



};



//*******************************************  TUTAJ JEST DRZEWO SUFIKSOWE WLASNEJ ROBOTY, mam nadizeje, ze uda sie je zbudowac w O( N * (lgN)^2 )  , czyli tyle co KMR :)
// uwaga!! drzewo sufiksowe korzysta  z danych z przestrzeni SUF, jesli wczesniej jej do czegos uzywalem, musze stworzyc kopie!! w przeciwnym razie strace dane!
// calkowity czas budowy drzewa to O( N*(lgN)^2) - potrzebne na budowe slownika KMR   plus   suma_po_i (    max( 0, lcp[i+1] - lcp[i] )    )
class SufTree{
public:
		// to jest klasa, ktora reprezentuje wierzcholek drzewa sufiksowego... mogze byc w nich pzrechowywane wiele rzeczy...
		class Node{
		public:
			map<char, Node* > sons; // to jest mapa synow w drzewie. Dla kazdej literki, ktora w danym wezle ma sens jest zwianazy inny wierzcholek reprezentujacy dalsze czesci sufiksu
			Node* par; // to jest wskaznik na rodzica danego wierzcholka
			int p,k; // to jest poczatek i koniec fragmentu slowa word z klasy SufTree, dla ktorego jest budowane to drzewo...
			int dist; // jest to odleglosc ostatniego znaku od korzenia, jest to potrzebne do budowania drzewa sufiksowego w czasie hmmmmm   liniowym?   w kazdym razie szybszym...
						// np pojedyncza dane podslowo, ktrego rodzicem jest korzen ma dist = length
						// jeszcze innymi slowy, jesli dany wierzcholek reprezentuje koncowke sufiksu, tzn isEnd == true, to ten sufiks zaczyna sie na pozycji    SIZE(word)-dist

			// tutaj sa juz rzeczy, ktore nie sa potrzebne do budowania drzewa sufiksowego, sa tylko wzbogaceniem drzewa potrzebnm do roznych algorytmow
			bool isEnd; // to jest parametr oznaczajacy, czy dany fragment sufiksu reprezentpwany przez wezel jest koncem tego sufiksu. Jesto to odpowiednik znaku   #    na koncu tekstu
			int length; // to jest dlugosc slowa reprezentowanego przez ten wierzcholek, czyli po prostu p-k+1

			// tutaj jest konstruktor tworzacy wierzcholek. beg i end to odpowiednio p oraz k z tej klasy, czyli indeksy textu word
			Node( Node* rodzic, int beg, int end, int dst ) : p(beg), k(end), par(rodzic), dist(dst) {
				length = k-p+1;
				isEnd = false;
			}
			~Node(){
				FOREACH(it,sons) delete it->ND;
			}


		};


		string word; // to jest slowo, dla ktorego budujemy drzewo sufiksowe, jest ono zakonczone znakiem #
	//	const char end_sign;
		KMR dic; // to jest slownik
		VI suf; // to jest tablica suf dla danego slowa
		VI revsuf; // to jest tablica revsuf dla danego slowa
		VI lcp; // to jest tablica lcp dla danego slowa
		Node* root; // to jest wierzcholek drzewa
		Node* wskaz; // to jest wskaznik potrzebny przy tworzeniu drzewa... przyspiesza czas budowy drzewa znacznie (moze nawet liniowo?)
						// podczas wstawiania wierzcholkow jesli sie nie myle jes twskaz->dist == lcp[i-1]
//		Node* akt; // to jest wskaznik na wierzcholek, w ktorym aktualnie jestem, potrzebne przy tworzeniu drzewa...

		// to jest konstruktor, tworzacy drzewo sufiksowe dla danego slowa
		SufTree( string& s ) : /*end_sign( (char)('z'+1) )*/ word(s) {
		//	word = s + end_sign;
			initSUF();
			root = new Node( 0,-1,-1,0 );  root->length = 0;
			createTree(); // tutaj wywoluje funkcje tworzaca drzewo
		}

		~SufTree(){
			delete root;
		}

		// to jest funkcja, ktora inicjalizuje   zmienne dic, sa, revsuf oraz lcp
		void initSUF(){
			SUF::LCP( word ); // tutaj tworze wszystkie tablice i wogole z przestrzeni SUF, czyli tworze suf, lcp, revsuf i dic w przestrzeni suf
		/*	swap( dic, SUF::dic ); // a tutaj po kolei zamieniam wszystko, aby nie przepisywac wielokrotnie tego samego - to jest w czasie stalym
			swap( suf, SUF::suf );
			swap( revsuf, SUF::revsuf );
			swap( lcp, SUF::lcp );*/
			dic = SUF::dic;
			suf = SUF::suf;
			revsuf = SUF::revsuf;
			lcp = SUF::lcp;
		}

		// to jest funkcja odpowiedzialna za stworzenie drzewa, czyli za odpowiednie dodawanie wierzcholkow(Node)
		void createTree(){
			lcp.PB(0); // dodaje ostatnia wartosc do lcp, aby nie miec wyjatku przy odwolywaniu sie do tablicy( bo SIZE(lcp) == SIZE(suf)-1 )
			wskaz = root; // na poczatek wskanikiem jest root

			REP( i,SIZE(lcp) ){
				if( wskaz->dist > lcp[i]  ){ // w tej sytuacji musze dodac reszte sufiksu z tablic suf[i] a pozniej troche sie cofnac...
				//	cout << "wskaz->dist = " << wskaz->dist << " > " << lcp[i] << " = lcp["<<i<<"]" << endl;
					addNode( suf[i] + wskaz->dist, SIZE(word)-1 ); // pocztakime stringu jest jego index w tekscie przesuniety o dlugosc wspolnego prefixu wstawianeo sufixu :)
					back_to( lcp[i]  );
				}
				else if( wskaz->dist == lcp[i] ){ // w tej sytuacji musze tylko wstawic nowy wierzcholek, nie wiecej :)
				//	cout << "wskaz->dist = " << wskaz->dist << " == " << lcp[i] << " = lcp["<<i<<"]" << endl;
					addNode( suf[i] + wskaz->dist, SIZE(word)-1 ); // pocztakime stringu jest jego index w tekscie przesuniety o dlugosc wspolnego prefixu wstawianeo sufixu :)
				}
				else if( wskaz->dist < lcp[i] ){ // w tej sytuacji musze wstawic jako nowy wierzcholek wspolny fragment prefixu sufiksu i oraz sufiksu i+1
				//	cout << "wskaz->dist = " << wskaz->dist << " < " << lcp[i] << " = lcp["<<i<<"]" << endl;
					wskaz = addNode(  suf[i] + wskaz->dist, suf[i] + lcp[i]-1  ); // dodaje fragment sufixu
					if( suf[i] + wskaz->dist <= SIZE(word)-1 ) addNode( suf[i] + wskaz->dist, SIZE(word)-1 ); // a teraz dodaje drugi fragment
				}
		//		cout << endl;
			}
			// teraz musze dodaj ostatni sufiks z tablice SA, ten dla ktorego dodalem sztucznie wartosc do lcp... jego fragment zaczyna sie na pozycji nr
			// musze usunac znak # wychodzacy z korzenia, zatem:
		//	root->sons.erase( end_sign );
		}

		// funkcja odpowiedzialna za przeniesienie wskaznika wskaz do tylu na najblizszy korzeniowi wierzcholek, dla ktorego dist >= nr    (i w razei czego rozbicie pewnych wierzcholkow na podwierzcholki...
		void back_to( int nr ){
			if( nr == 0 ){
				wskaz = root;
				return;
			}
			while( wskaz->par->dist >= nr ) wskaz = wskaz->par; // tutaj sie przenosze na odpowiedni wiezrcholek

			// teraz trzeba rozbic wierzcholek na podwierzcholki...
			if( wskaz->dist == nr ) return; // jesli nr(czyli lcp[i] ) == wskaz->dist, to nie musze rozbijac wierzcholkow
			Node* first = new Node( wskaz, wskaz->k - wskaz->dist + nr + 1, wskaz->k, wskaz->dist ); // w przeciwnym razie tworze wierzcholek reprezeentujacy
									// koncowke podslowa reprezentowanego przez wskaz, odpowiednio ustawiam beg i end oraz dist
			first->isEnd = wskaz->isEnd;
			wskaz->isEnd = false; // po rozbiciu na pewno dany wierzcholek nie reprezentuje konca sufiksu
		//	cout << "Rozbijam wierzcholek "; FOR(i,wskaz->p, wskaz->k) cout << word[i];
			// teraz musze zmienic dane w wierzcholku wskaz - troche go przyciac
			wskaz->k = wskaz->k - wskaz->dist + nr;
			wskaz->dist = nr;
			wskaz->length = wskaz->k - wskaz->p + 1;
			swap( first->sons, wskaz->sons ); // zamieniam mapy synow
			wskaz->sons[ word[first->p] ] = first; // dodaje syna wierzcholka wskazd
			first->par = wskaz;
		//	cout << "  na wierzcholki ";FOR(i,wskaz->p, wskaz->k) cout << word[i];  cout << "  oraz "; FOR(i,first->p, first->k) cout << word[i]; cout << endl;
		//	cout << endl;
		}

		// funkcja dodajaca wierzcholek jako syn wierzcholka wskazywanego przez wskaz, dla fragmentu tekstu word od beg do end
		Node* addNode( int beg, int end ){
			Node* temp = new Node( wskaz, beg, end, wskaz->dist + end - beg + 1   );
			wskaz->sons[ word[beg] ] = temp; // dodaje syna
			temp->par = wskaz;
			if( end == SIZE(word)-1 ) temp->isEnd = true; // jesli end to index ostatniego znaku sufiksu,
		//	cout << " ----- Dodaje wierzcholek reprezentujacy fragment "; FOR(i,beg,end) cout << word[i]; cout << endl;
			return temp; // zwracam wskaznik do nowo utworzonego wierzcholka
		}


		// funkcja sluzaca do pokazania drzewa sufiksowego
		void writeTree( Node* wsk, int depth );

		// funkcja wypisujaca odpowiednie tablice drzewa SufTree
		void writeSufs(){
			SUF::writeSA();
			SUF::writeLCP();
		}

		// funkcja zwracajaca ilosc roznych podslow danego slowa, trzeba ja wywolac z parametrem   root
		int countSubwords( Node* wsk );

		// funkcja zwracajaca index poczatku i konca najdluzszego slowa wystepujacego conajmniej n razy w tekscie
		PII ncountLongestSubword( int n );
		int helpLongestSubword( Node* wsk, int n ); // funkcja pomocnicza, jako parametr

		// funkcja sprawdzajaca, czy wzo wystepuje w danym tekscie, zwraca adres 0 jesli nie istnieje lub wskaznik na Node, w ktorym konczy sie wzo
		// liniowo ze wzgledu na dlugosc wzo
		Node* occurs( string& wzo );
		// funkcja zwracajaca ilosc wystapien wzorca wzo w tekscie word,   dziala pesymistycznie liniowo ze wzgledu na SIZE(word), sredni czas jest pewnie o moc alfabetu razy szybszy(+- 20 razy)
		int countOccurs( string& wzo );
		int helpCountOccurs( Node* wsk );
		// funkcja zawracajaca wszystkie miejsca w tekscie word, w ktorych zaczyna sie wzorzec wzo - takie KMP :)
		VI allOccurs( string& wzo );
		void helpAllOccurs( Node* wsk, VI & v );

};

int SufTree::countSubwords( Node* wsk ){
	int ile = wsk->length;
	FOREACH(it,wsk->sons) ile += countSubwords( it->ND );
	return ile;
}


void SufTree::writeTree( Node* wsk, int depth ){
	FOREACH( it, wsk->sons ){
		REP(i,depth) cout << "\t";

		cout << "Jestem w synu reprezentujacym fragment tekstu ";
		FOR(i,it->ND->p, it->ND->k) cout << word[i]; cout /*<< "   length = " << it->ND->length << "   isEnd = " << it->ND->isEnd */<< endl;
		writeTree( it->ND, depth+1 );
	}
}

PII SufTree::ncountLongestSubword( int n ){

}

int SufTree::helpLongestSubword( Node* wsk, int n ){

}

SufTree::Node* SufTree::occurs( string& wzo ){
	Node* wsk=root;
	map<char,Node*>::iterator it;
//	if( ( it = root->sons.find( wzo[0] ) ) == root->sons.end() ) return false;
//	wsk = it->ND;
	int p = 0, p2 = INF;
	while( p < SIZE(wzo) ){
		if( p2 > wsk->k ){ // jesli wyszedlem poza zakres danego wierzcholka, to musze przejsc do nowego
			if( ( it = wsk->sons.find( wzo[p] ) ) == wsk->sons.end() ) break; // jesli nie moge przejsc dalej, to break;
			wsk = it->ND;
			p2 = wsk->p;
		}
	//	cout << "wzo["<<p<<"] = " << wzo[p] << "   word["<<p2<<"] = " << word[p2] << endl;
		if( wzo[p] != word[p2] ) break;
		p++; p2++;
	}

	return ( p == SIZE(wzo) ? wsk : 0 );
}

int SufTree::countOccurs( string& wzo ){
	Node* wsk = occurs( wzo );
	if( wsk == 0 ) return 0;
	return helpCountOccurs( wsk );
}

int SufTree::helpCountOccurs( Node* wsk ){
	int ile = 0;
	if( wsk->isEnd ) ile++;
	FOREACH(it, wsk->sons) ile += helpCountOccurs( it->ND );
	return ile;
}

VI SufTree::allOccurs( string& wzo ){
	VI v;
	Node* wsk = occurs( wzo );
	if( wsk == 0 ) return v;
	helpAllOccurs( wsk, v );
	return v;
}

void SufTree::helpAllOccurs( Node* wsk, VI & v ){
	if( wsk->isEnd ) v.PB( SIZE(word) - wsk->dist );
	FOREACH(it,wsk->sons) helpAllOccurs( it->ND, v );
}


//************************************************************************  koniec drzewa sufiksowego

int main(){

	srand( unsigned(time(0)) );
	cout << fixed;
	cout.precision(7);

/*	cout << "Podaj slowo, dla ktorego mam stworzyc tablice SA, LCP, LPF: ";
	string s;
	cin >> s;
	SUF::LCP( s );
	SUF::writeSA();
	SUF::writeLCP();

	cout << "Ilosc roznych podslow w slowie " << s << " wynosi: " << SUF::countSubwords() << endl << endl;

	 while(1) {
		cout << "Podaj poczatek sufiksow, ktore mam porownac; ";
		cin >> a >> b;
		cout << s.substr(a) << "   " << SUF::dic.compare( a, SIZE(s)-1, b, SIZE(s)-1 ) << "    " << s.substr( b ) << endl;
	}

	while(true){
		cout << "Podaj poczatek pierwszego i drugiego sufiksu, dla ktorych mam znalezc najdluzszy wspolny prefix: ";
		int a,b,c;
		cin >> a >> b;
		cout << "Najdluzszy wspolny prefix ma dlugosc: " << ( c = SUF::longestDifSuf( a,b ) ) << "  i jest postaci ";
		FOR(x,a,a+c-1) cout << s[x];
		cout << endl << endl;
	}


	*/


	//  SufTree

/*	cout << "Podaj slowo, dla ktorego mam zbudowac drzewo sufiksowe:  ";
	string s;
	cin >> s;

	SufTree tree(s);
//	tree.writeSufs();
//	ENDL(3);
//	tree.writeTree( tree.root,0 );


	ENDL(5);
	cout << "Ilosc roznych podslow twojego slowa metoda LCP to:  " << SUF::countSubwords() << endl;
	cout << "Ilosc roznych podslow twojego slowa metoda drzewa sufiksowego to:  " << tree.countSubwords( tree.root ) << endl;

	while(1){
		cout << "Podaj slowo, ja sprawdze czy wystepuje ono w tekscie:" << endl;
		cin >> s;
		cout << "Slowo  " << s << ( tree.occurs(s) ? "  wystepuje" : "  nie wystepuje" ) << " w twoim tekscie " << tree.countOccurs(s) << " razy" << endl;
		if( tree.occurs(s) ){
			VI v = tree.allOccurs(s);
			sort( ALL(v) );
			cout << "\tWystepuje on na pozycjach: "; WRITE(v);
		}

		ENDL(3);
	}*/


	int ILE = 100000, DL = 10000;
	vector<string> slowa;
	string slowo;
	REP( i, DL ){
        slowo += char( rand()%5 + 64 );
	}
	cout << "Stworzylem slowo glowne, word" << endl;
	int M = 0;
	string s;
	REP( i, ILE ){
        M = rand()%(DL-1) + 1;
        M++;
        s = "";
        REP(k,M){
            s += char( rand()%5 + 64 );
        }
        slowa.PB(s);
	}

	cout << "Stworzylem slowa" << endl;
	cout << "Teraz bede sprawdzak szybkosc wyszukiwania" << endl;

    double t1=0, t2=0, T;
    int x=0;
    t1 = clock();
    REP( i,SIZE(slowa) ){
        if( slowo.find( slowa[i] ) != string::npos ){
            x++;
        }
    }

    T = clock() - t1;

    cout << "Sprawdzenie wszystkich slow metoda biblioteczna zajelo mi " << T / CLOCKS_PER_SEC << " sekund    x = " << x << endl;

    t1 = clock();
    SufTree tree(slowo);
    cout << "Zbudowanie dzrewa sufiksowego zajelo mi " << ( clock() - t1 ) / CLOCKS_PER_SEC << " sekund" << endl;

    t2 = clock();
    x = 0;
    REP( i,SIZE(slowa) ){
        if( tree.occurs(slowa[i]) != 0 ) x++;
    }


    cout << "Sprawdzenie wszystkich slow drzewem sufiksowym zajelo mi " << ( clock()-t2 ) / CLOCKS_PER_SEC << "  sekund    x = " << x << endl;

    cout << "Calkowity czas na drzewo to " << ( clock()-t1 ) / CLOCKS_PER_SEC << " sekund" << endl;





}












