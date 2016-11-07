//#include<stdio.h>
#include<iostream>
#include<vector>
//#include<string>
//#include<map>
//#include<complex>
//#include<stack>
//#include<list>
//#include<bitset>
//#include<set>
//#include<iterator>
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
	CTree( int aN ) : N(aN), s(1) {
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













int main(){
	
	cout << "Podaj prosze ile chcesz miec liczb w drzewie:\t";
	cin >> N;
	VI vec(N);
	cout << "Podaj prosze teraz te liczby:" << endl;
	REP(i,N){
		cout << i << ":  ";
		cin >> vec[i];
	}
	
	cout << "Tworze drzewo CTree dla tych liczb" << endl;
	
	CTree tree(vec);
	
	ENDL(3);
	cout << "Aby dodac/usunac odcinek, wybierz 1" << endl << "Aby sprawdzic sume, wybierz 2" << endl << "Aby sprawdzic ekstrema wybierz 3"
		 << endl << "Aby wyczyscic ekran wybierz 4" << endl;
	
	int x,p,k,l;
	while( cin >> x ){
		
		switch( x ){
			case 1:{
				cout << endl << "Podaj przedzial, ktory chcesz dodac oraz jego liczebnosc:  ";
				cin >> p >> k >> l;
				tree.Add( p,k,l );
				ENDL(1);
				break;
			}
			case 2:{
				cout << endl << "Podaj przedzial, dla ktorego chcesz sprawdzic sume:  ";
				cin >> p >> k;
				cout << "Suma elementow na przedziale [" << p << "," << k << "] = " << tree.FindSum( p,k ) << endl << endl;
				break;
			}
			case 3:{
				cout << endl << "Podaj przedzial, dla ktorego chcesz sprawdzic ekstrema:  ";
				cin >> p >> k;
				cout << "Ekstrema na przedziale ["<<p<<","<<k<<"] to:" << endl;
				cout << "\tMinimum:" << endl << "\t\t\tWartosc: " << tree.FindMin(p,k).ST << endl << "\t\t\tIndex: " << tree.FindMin(p,k).ND << endl;
				cout << "\tMaximum:" << endl << "\t\t\tWartosc: " << tree.FindMax(p,k).ST << endl << "\t\t\tIndex: " << tree.FindMax(p,k).ND << endl;
				break;
			}
			case 4:{
				system("cls");
				REP(i,SIZE(vec)) cout << i << ": " << vec[i] << endl;
				ENDL(3);
				cout << "Aby dodac/usunac odcinek, wybierz 1" << endl << "Aby sprawdzic sume, wybierz 2" << endl << "Aby sprawdzic ekstrema wybierz 3"
					 << endl << "Aby wyczyscic ekran wybierz 4" << endl;
				break;
			}	
			
		}
	}
	
	
	
}












