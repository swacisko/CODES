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
template<class _T>
class CTree{
public:
	#define NR (p1+k1)/2
//	typedef int _T; // to co ma byc przechowywane w wezlach
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
			_min[i].ST = 0; _min[i].ND = i-s;
			_max[i].ST = 0; _max[i].ND = i-s;
		}
		
		FORD( i,s-1,1 ){
			_min[i] = ( _min[2*i].ST <= _min[2*i+1].ST ? _min[2*i] : _min[2*i+1] ); // UWAGA, tutaj od znokow zalezy, index ktorego z elementow o tej samej wartosci zostanie zwrocony!! 
			_max[i] = ( _max[2*i].ST >= _max[2*i+1].ST ? _max[2*i] : _max[2*i+1] ); // jelsi jest <= lub >= to zostanie zwrocony najmniejszy index danewgo ekstremum
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
	
	// funkcja dodaje l1 przedzialow p1, p1+1, ..., k1
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
	
	// funkcja zwraca sume elementow na przedziale p1-k1 wlacznie
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
	
	// funkcja zwraca wartosc oraz index minimum na przedziale p1-k1
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
	
	// funkcja zwraca wartosc oraz index maksimum na przedziale p1-k1
	PTT FindMax( int p1, int k1 ){
		p = p1;		k = k1;
		return help_max(0,s-1,1);
	}
	
	// funkcja ustawiajaca wartosc danego elementu o indeksie ind na okreslona wartosc val
	void set( int ind, _T val ){
		_T s = FindSum( ind, ind );
		Add( ind, ind, val - s );
	}
	
	// funkcja zwracajaca dana wartosc elementu o indeksie ind
	_T get( int ind ){
		return FindSum( ind, ind );
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
	
	void write(){
		REP( i, N ){
			cout << "Emelemt " << i <<"-ty:  " << FindSum( i,i ) << endl;
		}
		
		ENDL(1);
	}
	
};


// longest common subsequence w czasie O( N^2 )
namespace LCS{
	
	// funkcja zwracajaca jako wektor najdluzszy wspolny podciag dwoch wektorow przeslanych jako parametr
	// dziala w czasie kwadratowym
	VI lcs( VI & tab1, VI & tab2 ){
		int p = SIZE(tab1);
		int q = SIZE(tab2);
		tab1.insert( tab1.begin(),0 );
		tab2.insert( tab2.begin(),0 );
		int** tab = new int*[p+1];
		REP(i,p+1) tab[i] = new int[q+1];
		
		REP(i,p+1) tab[i][0] = 0;
		REP(i,q+1) tab[0][i] = 0;
		
		vector<VPII> help( p+1, VPII(q+1) );
		int ind = 0;
		
	//	cout << "jeszcze przed p = " << p << "  q = " << q << "  SZIE(tab1) = " << SIZE(tab1) << "   SZIE(tab2) = " << SIZE(tab2) << endl;
		
		FOR(i,1,p){
			FOR(j,1,q){
				if( tab1[i] == tab2[j] ){
					help[i][j] = MP( i-1,j-1 );
					tab[i][j] = tab[i-1][j-1] + 1;
				} 
				else{
					if( tab[i-1][j] > tab[i][j-1] )	help[i][j] = MP( i-1,j );
					else help[i][j] = MP( i,j-1 );
					
					tab[i][j] = max( tab[i-1][j], tab[i][j-1] );
				}
			}
		}
		
	//	cout << "Juz wiem tab[p][q] = tab["<< p <<"]["<< q <<"] = " << tab[p][q] << endl;
		
		VI ans( tab[p][q] );
		int ind2 = SIZE(ans)-1;
		while( p != 0 && q != 0 ){
			if( help[p][q] == MP( p-1,q-1 ) ){
				ans[ind2--] = tab1[p];
				p--;
				q--;
			}
			else if( help[p][q].ST == p-1 ) p--;
			else q--;
		}
			
		REP(i,p+1) delete[] tab[i];
		delete[] tab;
		
		return ans;
	}
	
	
	// funkcja zwraca w wektorze ans najdluzszy wspolny podciag dwoch permutacji liczb od 0 do N-1    przeslanych jako parametr perm1 i perm2
	// dziala w czasie linearytmicznym   ( czyli NlgN  )
	// to mozna stosowac nawet dla niepelnych permutacji, dla pewnych dwoch podciagow roznej dlugosci tej samej permutacji
	// np najdluzszym wspolnym podciagiem ciagow  5,7,1,9,2  oraz 8,9,1,0,5,2   to  5,2
	void lcsPerm( int N, const VI & perm1, const VI & perm2, VI & ans ){
		VI renum1(N); // renum[i] to index elementu i w permutacji perm1 lub INF jesli taki element nie istnieje
		fill( ALL(renum1), INF );
		REP( i, SIZE(perm1) ) renum1[ perm1[i] ] = i;
		
	//	cout << "renum1:  "; WRITE(renum1); ENDL(2);
		
		VI perm2cp( SIZE(perm2) ); // to jest permutacja perm2 po przenumerowaniu tak, aby byla zgodna z perm1 po przenumerowaniu
		REP(i, SIZE(perm2) ) perm2cp[i] = renum1[ perm2[i] ];
		
	//	cout << "perm2cp:  "; WRITE(perm2cp); ENDL(2);
				
		CTree<int> tree(N+1); // tworez drzewo przedzialowe
		tree.set( perm2cp[0], 1 ); // dodaje pierwsza wartosc dyn[0] do drzewa dla wartosci perm2cp[0]
		
		VI dyn( SIZE(perm2) ); // to jest tablica dla dynamika
		VI maxy( SIZE(perm2),INF ); // ta tablica jest potrzebna do odtworzenia danych
		fill( ALL(dyn),1 );
		
		VI indice( SIZE(dyn),-1 ); // indice[i] to takie j, ze perm2cp[j] = i;
		REP(i,SIZE(indice)) if( perm2cp[i] != INF ) indice[ perm2cp[i] ] = i;
		
	//	cout << "Jestem przed uzywanie CTree<int>" << endl;
		
		FOR( i,1, SIZE(dyn)-1 ){
			if( perm2cp[i] == INF ) continue;
			PII para = tree.FindMax( 0,perm2cp[i] );
			dyn[i] = para.ST + 1;
			maxy[i] = indice[ para.ND ]; // w danej chwili zapamietuje taki index j, ktorego wartosc dyn[j] jest najwieksza, j < i oraz perm2cp[j] < perm2cp[i]
			
			tree.set( perm2cp[i], dyn[i] );
		} 
		
	//	cout << "dyn:  "; WRITE(dyn); ENDL(2);
		
		int ind = max_element( ALL(dyn) ) - dyn.begin(); // ind to jest index maksymalnego elementu w tablicy dyn
		
	//	cout << "maxy: "; WRITE(maxy); ENDL(2);		
	//	cout << "znowu cos nie tak..." << endl;
		
		VI ren( SIZE(renum1) );
	//	cout << "No ale co..." << endl;
		REP(i,SIZE(renum1)){
			if( renum1[i] != INF ){
			//	cout << "renum1["<<i<<"] = " << renum1[i] << endl;
				ren[ renum1[i] ] = i;
			}
		}
		
	//	cout << "ind = " << ind << endl;
		ans.clear();
		while( ind != INF  ){
		//	cout << "ind = " << ind << "  perm2cp[ind] = " << perm2cp[ind] << endl;
			ans.PB( ren[ perm2cp[ind] ] );
			ind = maxy[ind];
		}
		
		reverse( ALL(ans) ); // musze odwrocic kolejnosc bo dodawalem od tylca
		
	}
	
	
	

}




int main(){
	ios_base::sync_with_stdio(0);
	
	int PR,p,q;
	cin >> PR;
	l_zest = 0;
	while( l_zest++ < PR ){
		cin >> N >> p >> q;
		VI v1(p+1), v2(q+1);
		REP(i,p+1) cin >> v1[i];
		REP(i,q+1) cin >> v2[i];
		
	/*	cout << "v1:  "; WRITE(v1);
		ENDL(2);
		cout << "v2:  "; WRITE(v2);
		ENDL(2);*/
		
		VI ans;
		LCS::lcsPerm( N*N+1, v1,v2, ans );
		
	/*	cout << "Dlugosc lcs to: " << SIZE(ans) << endl;
		cout << "A oto lcs: ";
		WRITE(ans);*/
		
		cout << "Case " << l_zest << ": " << SIZE(ans) << endl;
	//	WRITE(ans);
		
				
	}
	
	
	return 0;
}












