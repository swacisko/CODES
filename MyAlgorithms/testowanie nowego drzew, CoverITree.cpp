#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<complex>
#include<stack>
#include<list>
#include<set>
#include<bitset>
#include<set>
#include<iterator>
#include<cmath>
#include<queue>
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
#define WRITE( V ) FOREACH(it,V) cout << *it << ", "; cout << endl;
#define WRITE_ALL(V,s)  cout << s << endl;  REP( i,SIZE(V) ){ cout << "i = " << i << endl;  FOREACH(it,V[i]) cout << *it << ", "; cout << endl;     }

int N,M,K,a,b,c,y,t,w,l_zest;
const long double EPS = 1e-11;
const int INF = 1000000001;
typedef vector<long double> VD;
typedef pair<long double,int> PDI;
typedef pair<long double, long double> PDD;
typedef vector<bool> VB;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef map< PII, bool > MPIIB;
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;


struct FAU{
	int *p,*w;
	FAU( int n ) : p(new int[n]), w(new int[n]) {
		REP(x,n) p[x] = w[x] = -1;
	}
	~FAU(){
		delete[] p;
		delete[] w;
	}
	
	int Find( int x ){
		return ( p[x]<0 ) ? x : p[x] = Find( p[x] );
	}
	
	void Union( int x, int y ){
		if( (x = Find(x)) == (y = Find(y)) ) return;
		if( w[x] > w[y] ) p[y] = x;
		else p[x] = y;
		if( w[x] == w[y] ) w[y]++;
	}
	
};


// Drzewo MaxTree umozliwia dodawanie elementów z przypisana im wartoscia oraz
// wyszukiwanie najwiekszej wartosci na dowolnym spójnym przedziale elementów
struct MaxTree{
	int *el,s;
	
	//	Konstruktor przyjmuje jako parametr wysokosc konstruowanego drzewa (dziedzina
	// elementów to [0..2^size-1])
	// jesli mamy tablice o rozmiarze n, to trzeba wywolac konstruktor z parametrem size = (int) ceil( log2(n) )
	MaxTree( int size ){
		el = new int[ 2*( s = (1 << size) ) ];
		REP(x,2*s) el[x] = 0;
	}
	
	~MaxTree(){
		delete[] el;
	}
	
	// Funkcja zmienia wartosc elementu p na v
	void Set( int p, int v ){
	// Ustaw wartosc elementu p na v, oraz zaktualizuj wierzcho³ki na
	// sciezce do korzenia, wyliczajac dla nich maksimum z ich lewego i prawego
	// syna
		for( p+=s, el[p] = v, p>>=1; p>0; p>>=1 ) el[p] = max( el[ p << 1 ], el[ (p << 1) + 1 ]  );
	}
	
	// Funkcja wyznacza najwieksza wartosc na przedziale elementów [p..k]
	int Find( int p, int k ){
		int m = -INF;
		p+=s;
		k+=s;
		// Przeszukiwanie drzewa rozpoczyna sie od lisci reprezentujacych elementy
		// p i k. Dopóki weze³ p jest rózny od wez³a k...
		while( p < k ){
		// Jesli aktualne wez³y p i k zawieraja w swoich poddrzewach ca³y
		// przeszukiwany przedzia³, to nastepuje aktualizacja wyniku
			if( (p&1) == 1 ) m = max( m,el[p++] );
			if( (k&1) == 0 ) m = max( m,el[k--] );
			
			// Przejdz do ojców wez³ów p i k
			p >>= 1;
			k >>= 1;
		}
		if( p == k ) m = max( m,el[p] );
		return m;
	}
};



// Struktura umozliwia dodawanie elementów z przypisana wartoscia oraz sprawdzanie
// sumy wartosci na dowolnym przedziale elementów
struct CountTree{
	int *el,s;
	// Konstruktor przyjmuje jako parametr wysokosc konstruowanego drzewa (dziedzina
	// kluczy to [0..2^size-2]) 
	// jesli chcemy strowrzyc drzewo dla n-elemetnowej tablicy zadanej wczesnie, to tworzymy drzewko
		// dla size = ceil( log2(n) ) 
	CountTree( int size ){
		el = new int[ 2*( s = (1 << size) ) ];
		REP(x,2*s) el[x] = 0;
	}
	
	~CountTree(){
		delete[] el;
	}
	
	 // uwaga, tutaj do wszystkich wezlow na sciezce nie dodaje wartosci v, tylko roznice miedzy el[p] i v
	// zmienia wartosc elementu el[p] na v
	void Set( int p, int v ){
		int t = v - el[p+s];
		for( p+=s; p; p>>=1 ) el[p] += t;
	}
	
	// Funkcja wyznacza sume wartosci na spójnym przedziale elementów [p..k]
	int Find( int p, int k ){
		int m = 0;
		p+=s;
		k+=s;
		
		while( p < k ){
			if( (p&1) == 1 ) m += el[p++];
			if( (k&1) == 0 ) m += el[k--];
			
			p >>= 1;
			k >>= 1;
		}
		if( p == k ) m += el[p];
		return m;
	}	
};


// uwaga, w tym drzewie przechowujemy tylko ilosc elementow o danej wartosci
// zluzy do wyznaczania k-tego najmniejszego elementu sposrob zadanego zbioru,
	// ale nie sposrob wybranego przedzialu tablicy..
	// do zbioru mozemy dodawac i usuwac elementy i za kazdym razem wyznaczac k-ty najmniejszy sposrod nich WSZYSTKICH
	// jesli mamy tablice i chcemy z danego przedzialu p...k wybrac t-ty najmniejszy element, to mozemy w czasie liniowym
	// zbudowac dla tego przedzalu drzewko i pozniej w czasie logarytmicznym znalezc t-ty majmniejszy element
	// czyli dla danego przedzialu znajdujemy ten t-ty element w czasie O( k - p )
struct PosTree{
	int *el,s;
	
	// jesli mamy tablice o rozmiarze n, to trzeba wywolac konstruktor z parametrem size = (int) ceil( log2(n) )
	PosTree( int size ){
		el = new int[ 2*( s = ( 1 << size ) ) ];
		REP(x,2*s) el[x] = 0;
	}
	
	~PosTree(){
		delete[] el;
	}
	
	// Funkcja dodaje/usuwa v wystapien elementu p
	void Add( int p, int v ){
	// Dla kazdego wez³a drzewa od liscia p do korzenia, aktualizowana jest
	// liczba elementów w poddrzewie
		for( p+=s; p>0; p >>=1 ) el[p] += v;		
	}
	
	// Funkcja wyznacza p-ta statystyke pozycyjna (p-ty najmniejszy element)
	int Find( int p ){
		int m = 1;
		while( m <= s ){	
			m <<= 1; // przechodzimy do lewego syna	
			
			// Jesli aktualne poddrzewo zawiera mniej elementów, niz wynosi numer
			// wyszukiwanej statystyki pozycyjnej, to nastepuje przejscie do prawego
			// syna				
			if( el[m] < p )	p -= el[m++];						
		}
		return m-s;
	}	
};



// Struktura umozliwia dodawanie i usuwanie odcinków oraz sprawdzanie obszaru
// przez nie pokrywanego
struct CoverTree{
	// UWAGA, liczbiue calkowitej a odpowiada przedzial [a-1,a]
	#define nr ( wp + wk + 1 ) >> 1
	int *el, *ma, s,p,k,il;
	
	// Konstruktor przyjmuje jako parametr wysokosc konstruowanego drzewa (konce
	// odcinków, na których wykonywane sa operacje naleza do przedzia³u [0..2^size-2])
	// jesli mamy tablice o rozmiarze n, to trzeba wywolac konstruktor z parametrem size = (int) ceil( log2(n) )
	CoverTree( int size ){ 
		// Tablica el przechowuje liczbe odcinków pokrywajacych w ca³osci przedzia³
		// reprezentowany przez odpowiedni weze³
		el = new int[ s = 1 << (size + 1) ];   // tutaj mogloby byc  tak jak wczesniej, ale wtedy w Add i Find
												// trzebaby pisac s zamiast s/2, ma = new int[2*s] w REP 2*s i tak dalej...
		
		// Tablica ma przechowuje sumaryczna pokryta powierzchnie przedzia³u
		// reprezentowanego przez odpowiedni weze³
		ma = new int[s];
		REP(x,s) el[x] = ma[x] = 0;
	}
	
	~CoverTree(){
		delete[] el;
		delete[] ma;
	}
	
	// Funkcja pomocnicza wykorzystywana przez operacje dodawania i usuwania odcinków.
	// Wykonuje ona aktualizacje wartosci wez³ów
	void Mark( int wp, int wk, int g ){
		// Jesli odcinek który jest dodawany/usuwany, jest roz³aczny z przedzia³em
		// reprezentowanym przez aktualny weze³, to przerwij
		if( k <= wp || p >= wk ) return;
		
		// Jesli odcinek pokrywa w ca³osci przedzia³ aktualnego wez³a, to zmien wartosc el,
		if( p <= wp && k >= wk ) el[g] += il;
		else{
			// a jesli nie, to wykonaj aktualizacje zmiennych synów aktualnego wez³a
			Mark( wp, nr, 2*g );
			Mark( nr,wk,2*g+1 );
		}
		
		// Dokonaj aktualizacji pokrytego obszaru przetwarzanego przedzia³u
		ma[g] = el[g] > 0 ? wk - wp : ( wp == wk-1 ? 0 : ma[2*g] + ma[2*g + 1] );	
	}
	
	// Funkcja dodajaca i1 wystapien odcinka [p1..k1] do drzewa. W przypadku,
	// gdy i1 jest wartoscia ujemna, nastepuje usuwanie odcinka
	void Add( int p1, int k1, int i1 ){
		p = p1;
		k = k1;
		il = i1;
		Mark( 0, s/2,1 );
	}
	
	// Funkcja pomocnicza s³uzaca do wyznaczania pokrycia odcinka [p..k]
	int F( int wp, int wk, int g ){
		// Jesli testowany odcinek jest roz³aczny z aktualnym przedzia³em,
		// to pokrycie jest równe 0
		if( p >= wk || k <= wp ) return 0;
		
		// Jesli przedzia³ jest w ca³osci pokryty, to zwróc wielkosc
		// czesci wspólnej testowanego odcinka i przedzia³u
		if( el[g] > 0 ) return min( k,wk ) - max( p,wp );
		
		// Jesli odcinek pokrywa w ca³osci przedzia³, to zwróc pokrycie przedzia³u
		if( p <= wp && k >= wk ) return ma[g];
		
		// Zwróc jako wynik sume pokryc swoich synów
		return (wp == wk-1) ? 0 : ( F( wp , nr , 2*g ) + F( nr , wk , 2*g + 1) );		
	}
	
	// W³asciwa funkcja realizujaca wyznaczanie pokrycia przedzia³u [p1..k1]
	// pokryciem nazywamy tutaj ilosc 'pól' przedzialu p1-k1 pokrytych przez jakies przedzialy
		// ktore dodalismy wczesniej
	int Find( int p1, int k1 ){
		p = p1;
		k = k1;
		return F( 0, s/2, 1 );
	}
	
};


// Struktura umozliwia dodawanie i usuwanie odcinków oraz sprawdzanie obszaru
// przez nie pokrywanego
// Strukturka przeznaczona do pokrywania przedzialow zbioru liczb calkowitych, aby pokryc przedzial [a,b] liczb calkowitych, to trzeba dodac ODCINEK [a-1,b]
// lub [a,b+1]  - bo t ofunkcje z CoverTree, w zaleznosci od wyboru, nalezy pozniej odpowiednio przesuwac argumenty wywolan funkcji Add,Find,FindSum
// Aby dodac do kazdej z liczb z przedzialu [a,b] liczbe K nalezy wywolac funkcje Add( a,b,K ) - wtedy dodajemy K odcinkow do drzewa
// Aby znalezc sume wartosci na przedziale [a,b] nalezy wywolac funkcje FindSum( a,b ) // wyszukiwanie sumy dla danego przedzialu dziala w czasie O(lgN) !! Hurra!
// Aby znaleŸc najwieksza wartosc na przedziale [a,b] nalezy wywolac funkcje getMaxStat(a,b), Zwraca PII - wartosc,index, gdzie index - to index zmiejszony o 1 - w tym drzewie wszystkie indeksowania
// do funkcji nalezy przesylac tak, jakbysmy praowali na tablicy 1,2,3,...,N, a nie liczone od 0. Jezeli jest wiecej niz jeden element o maxymalnej wartosci to zwracam mniejszy z indexow
// 
struct CoverITree{
	// UWAGA, liczbiue calkowitej a odpowiada przedzial [a-1,a]
	#define nr ( wp + wk + 1 ) >> 1
	int *el, *ma, *sum,s,p,k,il;
	PII *maxstat;
	PII *minstat;
	CoverITree( int size ){ 
		el = new int[ s = 1 << (size+1) ];  
		ma = new int[s];
		sum = new int[s];
		maxstat = new PII[s];
		minstat = new PII[s];
		REP(x,s) el[x] = ma[x] = sum[x] = 0;
		FOR(x,s/2,s-1){
			maxstat[x].ST = minstat[x].ST = 0;
			maxstat[x].ND = minstat[x].ND = x - s/2; // tu mozna dodac 1 aby indeksowanie bylo od 1 a nie od zera, w funkcjach to nie bedzie mialo zadnego wplywu
		}
		FORD( x,s/2-1,1 ){ // liniowo ide od tylu drzewa i przypisuje indexy
			if( maxstat[2*x].ST >= maxstat[2*x+1].ST ){
				maxstat[x].ST = maxstat[2*x].ST;
				maxstat[x].ND = maxstat[2*x].ND;
			}
			else{
				maxstat[x].ST = maxstat[2*x+1].ST;
				maxstat[x].ND = maxstat[2*x+1].ND;
			}
			
			if( minstat[2*x].ST <= minstat[2*x+1].ST ){
				minstat[x].ST = minstat[2*x].ST;
				minstat[x].ND = minstat[2*x].ND;
			}
			else{
				minstat[x].ST = minstat[2*x+1].ST;
				minstat[x].ND = minstat[2*x+1].ND;
			}
		}
	}
	
	~CoverITree(){
		delete[] el;
		delete[] ma;
		delete[] sum;
		delete[] maxstat;
		delete[] minstat;
	}
	
	void Mark( int wp, int wk, int g ){
		if( k <= wp || p >= wk ) return;		
		if( p <= wp && k >= wk ) el[g] += il;
		else{
			Mark( wp, nr, 2*g );
			Mark( nr,wk,2*g+1 );
		}		
		ma[g] = el[g] > 0 ? wk - wp : ( wp == wk-1 ? 0 : ma[2*g] + ma[2*g + 1] );
		
		if( 2*g < s ){ // to jest czesc do wyznaczania maksymalnego elementu w drzewie
			int M = ( maxstat[2*g].ST >= maxstat[2*g+1].ST ? 2*g : 2*g+1 );
			maxstat[g].ST = maxstat[M].ST + el[g];
			maxstat[g].ND = maxstat[M].ND; 
		}
		else maxstat[g].ST += il; // jesli jest lisciem to wystarczy, ze dodam do niego wartosc nowego pokrywajacego go przedzialu
		
		if( 2*g < s ){ // to jest czesc do wyznaczania minimalnego elementu w drzewie
			int M = ( minstat[2*g].ST <= minstat[2*g+1].ST ? 2*g : 2*g+1 );
			minstat[g].ST = minstat[M].ST + el[g];
			minstat[g].ND = minstat[M].ND;			
		}
		else minstat[g].ST += il; // jesli jest lisciem to wystarczy, ze dodam do niego wartosc nowego pokrywajacego go przedzialu
		
		if( p <= wp && k >= wk ) sum[g] += il*(wk-wp); // to jest czesc do wyznaczania sum na danym przedziale
		else sum[g] += il*( min(k,wk) - max(p,wp) );
	}
	
	void Add( int p1, int k1, int i1 ){
		p = p1-1;
		k = k1;
		il = i1;
		Mark( 0, s/2,1 );
	}
	
	int F( int wp, int wk, int g ){
		if( p >= wk || k <= wp ) return 0;
		
		if( el[g] > 0 ) return min( k,wk ) - max( p,wp );
		
		if( p <= wp && k >= wk ) return ma[g];
		
		return (wp == wk-1) ? 0 : ( F( wp , nr , 2*g ) + F( nr , wk , 2*g + 1) );		
	}
	
	int Find( int p1, int k1 ){
		p = p1-1;
		k = k1;
		return F( 0, s/2, 1 );
	}
	
	int S( int wp, int wk, int g ){
		if( p >= wk || k <= wp )return 0;
		if( p <= wp && k >= wk )return sum[g];	
		return (wp == wk-1) ? el[g] : ( S( wp , nr , 2*g ) + S( nr , wk , 2*g + 1) + el[g]*( min(k,wk) - max(p,wp)  ) );		
	}
	
	int FindSum( int p1, int k1 ){
		p = p1-1;
		k = k1;
		return S( 0,s/2,1 );
	}
	
	PII maxstats( int wp, int wk, int g ){
		if( p >= wk || k <= wp )	return MP( -INF,-INF ); // jesli jest rozlaczny, to zwracam bzdety		
		if( (p <= wp && k >= wk) || ( wp == wk-1 ) )	return maxstat[g]; // jesli jest pokryty w calosci to zwracam jego stat
		PII m1 = maxstats( wp,nr,2*g );
		PII m2 = maxstats( nr,wk,2*g+1 );
		PII M;
		if( m1.ST >= m2.ST ){ M.ST = m1.ST; M.ND = m1.ND;	}
		else{ M.ST = m2.ST; M.ND = m2.ND;  }
		M.ST += el[g];
		return M;
	}
	
	PII getMaxStat( int p1, int k1 ){
		p = p1-1;
		k = k1;
		return maxstats( 0,s/2,1 );
	}
	
	PII minstats( int wp, int wk, int g ){
		if( p >= wk || k <= wp )	return MP( INF,INF ); // jesli jest rozlaczny, to zwracam bzdety		
		if( (p <= wp && k >= wk) || ( wp == wk-1 ) )	return minstat[g]; // jesli jest pokryty w calosci to zwracam jego stat
		PII m1 = minstats( wp,nr,2*g );
		PII m2 = minstats( nr,wk,2*g+1 );
		PII M;
		if( m1.ST <= m2.ST ){ M.ST = m1.ST; M.ND = m1.ND;	}
		else{ M.ST = m2.ST; M.ND = m2.ND;  }
		M.ST += el[g];
		return M;
	}
	
	PII getMinStat( int p1, int k1 ){
		p = p1-1;
		k = k1;
		return minstats( 0,s/2,1 );
	}
	
};






int main(){
	

	
	
	// CoverITree
	int w1,w2,w3,n;
	// wczytaj zakres liczb dla ktorego chce stworzyc drzewko pokryciowe
	cin >> n;
	CoverITree tree( (int) (ceil( log2(n) ) + 0.1) );
	cout << "Drzewo pokryciowe i sumacyjne dla liczb calowitych:  tree.s = " << tree.s << endl;
	// wczytaj polecenia...
	while( cin >> w1 >> w2 >> w3 ){
		if( w1 == 0 ){
			//dodaj nowy odcinek
			tree.Add( w2,w3,1 );
			cout << "Dodanie odcinka [" << w2 << "," << w3 << "]" << endl;
		}
		else if( w1 == 1 ){
			// operacja usuwania odcinka
			tree.Add(w2,w3,-1);
			cout << "Usuniecie odcinka [" << w2 << "," << w3 << "]" << endl;
		}
		else if( w1 == 2 ){
			cout << "Suma elementow na przedziale [" << w2 << "," << w3 << "] = " << tree.FindSum( w2,w3 ) << endl;
			cout << "Oto twoje sum:" << endl;
			FOR(x,1,tree.s-1) cout << "sum["<<x<<"] = " << tree.sum[x] << endl;
		}
		else if( w1 == 3 ){
			PII p = tree.getMaxStat( w2,w3 );
			cout << "Najwiekszy element w drzewie ma wartosc " << p.ST << " a jego index to " << p.ND + 1 << endl;
		}
		else if( w1 == 4 ){
			PII p = tree.getMinStat( w2,w3 );
			cout << "Najmniejszy element w drzewie ma wartosc " << p.ST << " a jego index to " << p.ND + 1 << endl;
		}
		else{
			// wyznaczenie pokrycia na przedziale w2..w3
			cout << "Pokrycie odcinka [" << w2 << "," << w3 << "] = " << tree.Find( w2,w3 ) << endl;
		}
	}
	return 0;
	
	
}








