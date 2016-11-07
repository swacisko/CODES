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

zadanie jest nastepujace:   dodajemy pewne przedzialy [a,b] do drzewa przedzialowego
nastepnie pytamy:   wypisz wszystkie przedzialy do drzewa, ktore zawieraja   dany punkt P, czyli np wszystkie przedzialy zawierajace w sobie liczbe 7
przyklad:   dodajemy przedzialy  [1,5] oraz [3,17]. Punkt 2 jest zawarty tylko w przedziale [1,5] nastomiast 4 jest juz zawarty w obydwu

dodawanie przedzialu dziala w czasie logarytmicznym - do funkcji wysylamy przedzial i numer tego przedzialu
zapytanie to O( lgN + K ), gdzie K to ilosc przedzialow pokrywajacych dany punkt - zwracane sa numery przedzialow, nie przedzialy

elementami drzewa sa wektory vector<int>

*/

class CVTree{
public:
	#define NR (p1+k1)/2
	int N; // ilosc liczb, na ktorych chcemy operowac, tzn jesli chcemy operowac na 5 liczbach, to potrzebujemy stworzyc tablice rozmiarow 2 * 8
	int s; // jest to liczba bedaca najmniejsza potega dwojki, nie mniejsza niz N, UWAGA - liczba   L do ktorej chcemy sie odniesc jest w tablicy tab na miejscu s + L
	int size; // rozmiar tablicy tab(i innych jesli beda)
	int p,k; // liczby p oraz k oznaczaja poczatek i koniec przedzialu, ktory chcemy dodac
	int num; // l oznacza numer przedzialu, ktory dodajemy na danym przedziale
	
	VVI total; // to jest wektor numerow przedzialow, ktore pokrywaja w calosci przedzial reprezentowany przez dany wierzcholek
	
	
	// konstruktor przyjmujacy jako wartosc maksymalna liczbe, na ktorej bedziemy wykonywac operacje, tzn tab bedzie reprezentowac liczby 0,1,2,...,N-1   !!!
	CVTree( int aN ) : N(aN), s(1) {
		while( s <= N ) s <<= 1;
		size = (s << 1 );
				
		total = VVI(size);		
	}
	
	// p1 - poczatek przedzialu reprezentowanego przez wezel,  k1 - koniec przedzialu repr.przez wezel,  g - numer wezla
	void help_add( int p1, int k1, int g ){
		if( p1 > k || k1 < p ) return; // jesli przedzialy sa rozlaczne, to nic nie robie
		if( p1 >= p && k1 <= k ){ // jesli wstawiany przedzal zawiera w calosci przedzial reprezentowany przez wezel to...
			total[g].PB( num );
			return;
		}
		
		// w przeciwnym razie rozbijam wezel na 2 podwezly
		help_add( p1, NR, 2*g );
		help_add( NR + 1, k1, 2*g+1 );
	}
	
	// funkcja dodaje numer num do przedzialu [p1,k1]
	void Add( int p1, int k1, int num ){
		p = p1;		k = k1;		this->num = num;
		help_add( 0,s-1,1 );
	}
	
	void help_find( int p1, int k1, int g, VI & ans ){
		if( p1 > k || k1 < p ) return; // jesli przedzialy sa rozlaczne, to nic nie robie
		if( p1 >= p && k1 <= k ){ // jesli wstawiany przedzal zawiera w calosci przedzial reprezentowany przez wezel to...
			REP( i,SIZE(total[g]) ) ans.PB( total[g][i] ); // dodaje wszystkie numery, ktore pokrywaja dany przedzial w calosci
			return;
		}
		
		// w przeciwnym razie rozbijam wezel na 2 podwezly
		help_find( p1, NR, 2*g, ans );
		help_find( NR + 1, k1, 2*g+1, ans );
		
		REP( i,SIZE(total[g]) )ans.PB( total[g][i] );
	}
	
	// funkcja jako parametry przyjmuje punkt, dla ktorego chcemy wyznaczyc numery przedzialow go pokrywajacych, 
	//a jako rezultat w wektorze ans zwraca numery przedzialow dodanych wczesniej do drzewa, ktore pokrywaja punkt p1
	void Find( int p1, VI & ans ){
		p = p1; k = p1; ans.clear();
		help_find( 0,s-1,1, ans );
		sort( ALL(ans) );
		ans.resize( unique(ALL(ans)) - ans.begin() );
	}
};





int main(){
	
	cout << "Podaj prosze rozmiar drzewa (zakres przedzialow):  ";
	cin >> N;
	CVTree tree(N);
	
	VPII inter;
	
	cout << "Podaj ile chcesz przedzialow dodac:   ";
	cin >> N;
	REP(i,N){
		cout << "Podaj przedzial nr " << i << ":  ";
		cin >> a >> b;
		inter.PB( MP(a,b) );
		tree.Add( a,b-2,i );
	}

	
	
	while(1){
		cout << "Podaj punkt a, dla ktorego mam wypisac wszystkie" << endl << "numery przedzialow zawierajace ten punkt:   ";
		cin >> a;
		
		VI ans;
		tree.Find( a,ans );
		
		REP(i,SIZE(ans)){
			cout << "Punkt " << a << " jest zawarty w przedziale nr " << ans[i] << ", czyli [" << inter[ans[i]].ST << "," << inter[ans[i]].ND << "]" << endl;
		}
		
		ENDL(2);
		
	}

	
	
}












