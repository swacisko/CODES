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
short N,M,K,a,b,c,y,t,w,l_zest;
const long double EPS = 1e-11;
typedef vector<double> VD;
typedef pair<double,int> PDI;
typedef pair<double, double> PDD;
typedef vector<bool> VB;
typedef vector<short> VI;
typedef vector< VI > VVI;
typedef pair<short,short> PII;
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;


/*

zadanie jest nastepujace:   dodajemy pewne przedzialy [a,b] do drzewa przedzialowego
nastepnie pytamy:   wypisz wszystkie przedzialy do drzewa, ktore zawieraja   dany punkt P, czyli no wszystkie przedzialy zawierajace w sobie liczbe 7
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
	short p,k; // liczby p oraz k oznaczaja poczatek i koniec przedzialu, ktory chcemy dodac
	short num; // l oznacza numer przedzialu, ktory dodajemy na danym przedziale
	
	VVI total; // to jest wektor numerow przedzialow, ktore pokrywaja w calosci przedzial reprezentowany przez dany wierzcholek
	
	
	// konstruktor przyjmujacy jako wartosc maksymalna liczbe, na ktorej bedziemy wykonywac operacje, tzn tab bedzie reprezentowac liczby 0,1,2,...,N-1   !!!
	CVTree( int aN=0 ) : N(aN), s(1) {
		while( s <= N ) s <<= 1;
		size = (s << 1 );
				
		total = VVI(size);		
	}
	
	// p1 - poczatek przedzialu reprezentowanego przez wezel,  k1 - koniec przedzialu repr.przez wezel,  g - numer wezla
	void help_add( short p1, short k1, int g ){
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
	void Add( short p1, short k1, short num ){
		p = p1;		k = k1;		this->num = num;
		help_add( 0,s-1,1 );
	}
	
	void help_find( short p1, short k1, int g, VI & ans ){
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
	void Find( short p1, VI & ans ){
		p = p1; k = p1; ans.clear();
		help_find( 0,s-1,1, ans );
	//	if( SIZE(ans) <= 1 ) return;
	//	sort( ALL(ans) );
	//	ans.resize( unique(ALL(ans)) - ans.begin() );
	}
	
	void help_erase( short p1, short k1, int g ){
		if( p1 > k || k1 < p ) return; // jesli przedzialy sa rozlaczne, to nic nie robie
		if( p1 >= p && k1 <= k ){ // jesli wstawiany przedzal zawiera w calosci przedzial reprezentowany przez wezel to...
			total[g].erase( lower_bound( ALL(total[g]), num ) );
			return;
		}
		
		// w przeciwnym razie rozbijam wezel na 2 podwezly
		help_erase( p1, NR, 2*g );
		help_erase( NR + 1, k1, 2*g+1 );		
	}
	
	void erase( short p1, short k1, short num ){
		p = p1; k = k1; this->num = num;
		help_erase( 0,s-1,1 );
	}
	
};



CVTree tree;
VPII inter;
vector<char> loc; // loc[i] to S lub N w zaleznosci od tego, gdzie ulozylismy dany przedzial
VB was; // was[i] = true, gdy rozwazalismy juz przedzial i

void DFS( short num, char aktloc /*short depth*/ ){
	was[num] = true;
	if( inter[num].ST == inter[num].ND-1 ) return; // nie ma sensu rozwaz przedzialow dlugosci 1
//	REP(i,depth) cout << "\t";
	
//	tree.erase( inter[num].ST+1, inter[num].ND-1, num );
	
	loc[num] = aktloc;
	
	short	a = inter[num].ST;
	short b = inter[num].ND;
	
//	cout << "Rozwazam przedzial " << num << " = " << WRP( inter[num] ) << "   a = " << a << "    b = " << b << "  aktloc = " << aktloc << endl;
			
	VI ans;
	tree.Find( a,ans );
	
	
//	REP(i,depth) cout << "\t";
////	cout << "\tPrzedzialy zawierajace poczatek tego przedzialu to:   ";  REP(i,SIZE(ans)) cout << WRP( inter[ans[i]] ) << "  |  ";
//	ENDL(2);
	
	REP(i,SIZE(ans)){
		if( inter[num].ST >= inter[ ans[i] ].ST && inter[num].ND <= inter[ans[i]].ND ) continue; // jesli rozwazany przedzial ans[i] w calosci pokrywa przedzial num to nie ma sensu go rozwazac
		if( !was[ans[i]] ){
			DFS( ans[i], ( aktloc == 'S' ? 'N' : 'S' )/*,depth+1*/ );
		}
	}
	
	
	// teraz to samo dla drugiej strony
	ans.clear();
//	cout << "a = " << a << "   b = " << b << endl;
	tree.Find( b,ans );
//	cout << "a = " << a << "   b = " << b << endl;
	
//	REP(i,depth) cout << "\t";
//	cout << "\tPrzedzialy zawierajace koniec("<<b<<") tego przedzialu to:   ";  REP(i,SIZE(ans)) cout << WRP( inter[ans[i]] ) << "  |  ";
//	ENDL(2);
	
	REP(i,SIZE(ans)){
		if( inter[num].ST >= inter[ ans[i] ].ST && inter[num].ND <= inter[ans[i]].ND  ) continue;
		if( !was[ans[i]] ){
			DFS( ans[i], ( aktloc == 'S' ? 'N' : 'S' )/*,depth+1*/ );
		}
	}
	
}




int main(){
	

	cin >> N >> K;	
	
//	cout << "N = " << N << "   K = " << K << endl;
	
	tree = CVTree(N+5);	
	inter.clear();
	loc = vector<char>(K,'u');
	was = VB( K,0 );
	
	REP(i,K){
		cin >> a >> b;
		inter.PB( MP(a-1,b-1) );
		if( a == b-1 ) continue; // jesli przedzial jest dlugosci 2 to nie ma on najmniejszego znaczenia
		tree.Add( a,b-2,i ); // dodaje przedzial okrojony z kazdej strony o 1, aby drzewo wyznaczalo tylko te przedzialy, ktore zawieraja wewnatrz! siebie dany punkt
	}
	
//	REP( i,tree.size ) sort( ALL( tree.total[i] ) );
	
/*	vector< PII > inter2;
	REP( i,SIZE(inter) ){
		inter2.PB( MP( inter[i].ST,i ) );
		inter2.PB( MP( inter[i].ND,i ) );
	}
	
	sort( ALL(inter2) );*/
	
/*	cout << "Oto przedzialy inter:  " << endl; 
	REP(i,SIZE(inter)){
		cout << WRP(inter[i]) << endl;
	//	if( i % 5 == 0 ) ENDL(1);
	}*/
		
	REP( i,SIZE(was) ) if( !was[i] ) DFS( i, 'N' );
	
	bool can = true;
	VI ans;
	REP(i,SIZE(inter)){
		if( inter[i].ST == inter[i].ND-1 ) continue;
		
		tree.Find( inter[i].ST, ans );
		REP(k,SIZE(ans)){
			if( inter[i].ST >= inter[ans[k]].ST && inter[i].ND <= inter[ans[k]].ND ) continue;
			if( loc[ ans[k] ] == loc[i] ){
				can = false;
				goto endup;
			}
		}
			
		
		tree.Find( inter[i].ND, ans );	
		REP(k,SIZE(ans)){
			if( inter[i].ST >= inter[ans[k]].ST && inter[i].ND <= inter[ans[k]].ND ) continue;
			if( loc[ ans[k] ] == loc[i] ){
				can = false;
				goto endup;
			}
		}
		
	}
	
endup:	
	
	if( !can ) cout << "NIE" << endl;
	else{
		REP(i,SIZE(inter)){
			if( loc[i] != 'S' && loc[i] != 'N' ) cout << "N" << endl;
			else cout << loc[i] << endl; 
		}
	}
	
//	tree.Find( 6000,ans );
//	cout << "asdasdsdsd    " << SIZE( ans );
//	ENDL(3);
//	REP(i,SIZE(ans)) cout << WRP( inter[ans[i]] ) << "    |    ";
	
	
//	WRITE(loc);
	
	
	return 0;
}












