#include<cstdio>
#include<iostream>
#include<vector>
#include<string>
#include<map>
//#include<complex>
//#include<stack>
//#include<list>
#include<bitset>
#include<set>
//#include<iterator>
#include<cmath>
//#include<queue>
#include<time.h>
//#include<string.h>
//#include<fstream>
//#include<sstream>
#include<algorithm>
//#include<conio.h>

using namespace std;

#define REP( x,y ) for( int x=0; x<(y); ++x )
#define FORD( x,y,z ) for( int x=y; x>=(z); --x )
#define FOR(x,b,e) for( int x = b; x <= (e); ++x )
#define SIZE(v) (int)v.size()
#define ALL(c) c.begin(),c.end()
#define VAR(v,n) __typeof(n) v=(n)
#define FOREACH(i,c) for( VAR(i,c.begin());i!=c.end();++i )
#define PB push_back
#define MP make_pair
#define ST first
#define ND second
#define WRITE( V ){ REP(trx,SIZE(V)) cout << V[trx] << " "; cout << endl; }
#define WRITE_ALL(V) {  REP( i,SIZE(V) ){ cout  << i << " ---- ";  FOREACH(it,V[i]) cout << *it << ", "; cout << endl;     } }
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
typedef vector< VB > VVB;
typedef long long LL;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;

typedef double _T;
typedef vector< _T > VT;
typedef vector< VT > VVT;
typedef pair<_T,_T> PTT;
typedef vector< PTT > VPTT;





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



// Lowest Common Ancestor
namespace LCA{	
	VVI V; // jest to drzewo przechowywane(graf)
	CTree tree(0); // jest to drzewo przedzialowe przechowujace kod dfs naszego grafu(drzewa)
	VI code; // tutaj jest kod dfs preOrder
	VI first, last; 
	VI preOrder; // preOrder[i] to numer preorder wierzcholka i
	VI revPreOrder; // revPreOrder[i] to numer wierzcholka, ktorego preorder to i (czyli taka funkcja 'odwrotna' do preOrder
	
	void dfs( int par, int num, int & pre ){
		code.PB( pre );
		preOrder[num] = pre++; // przypisuje preOrder i zwiekszam pre
		REP(i,SIZE(V[num]))	if( V[num][i] != par ){
			dfs( num, V[num][i], pre );
			code.PB( preOrder[num] ); // dodaje moj numer preOrder(numer preOrder tego wierzcholka w ktorym wlasnie jestem)
		}		
	}
	
	// funkcja jako parametr przyjmuje numer wierzcholka, ktory ma byc traktowany jako korzen drzewa przy tworzeniu kodu dfs (drzewo jest dane w wektoreze V )
	void create_CTree( int root ){
		code.clear(); // zeruje wektor, bo w dfs push_back`uje
		preOrder = VI( SIZE(V),0 );
		revPreOrder = VI( SIZE(V),0 );
		int pre = 0;
		LCA::dfs( root,root, pre ); // tworze kod w wektorze code
		REP(i,SIZE(preOrder)) revPreOrder[ preOrder[i] ] = i;		
		
		tree = *(new CTree( code ) ); // tworze drzewo dla danego kodu dfs
		
		first = VI(SIZE(V),INF); // first[i] to index pierwszego wystapienia liczby i w kodzie dfs w wektorze code
		last = VI(SIZE(V),0); // last[i] to index ostatniego wystapienia
		
		REP(i,SIZE(code)){
			first[code[i]] = min( first[code[i]],i );
			last[code[i]] = max( last[code[i]],i );
		}	
		
	//	cout << "Zakonczylem prace w create_CTree(), kod to: "; WRITE(code);
	//	cout << "Numery preOrder twoich wierzcholkow to: "; WRITE(preOrder);
	}
	
	// pytanie o LCA dla dwoch danych wierzcholkow o numerach n1 oraz n2      jako rezultat zwraca numer najblizszego wspolnego przodka
	int Ask( int n1, int n2 ){
		int p = preOrder[n1]; // znajduje numery preOrder danych wierzcholkow
		int k = preOrder[n2];
		if( p > k ) swap(p,k); // teraz p < k, czyli first[p] < last[k]
	//	cout << "Numery preOrder danych wierzcholkow to " << p << " oraz " << k << endl;
	//	cout << "Pierwsze wystapienie wierzcholka p to: " << first[p] << ", a ostatnie wystapienie " << k << " to: " << last[k] << endl;
		int preNum = tree.FindMin( first[p], last[k] ).ST; // znajduje numer preOrder najblizszego wspolnego przodka
	//	cout << "Znalazlem preNum = " << preNum << endl;
		int num = revPreOrder[ preNum ]; // znajduje numer tego wierzcholka(LCA) w grafie
		return num;
	}
	
}



//****************************************************************  DRZEWO PRZEDZIALOWE WYMAGANE DO PRZECHOWYWANIA DANYCH


template<class _T>
struct IntervalTree{
	
	_T *tab;
	_T *maxval;
	int s;
	
	// N to liczba elementow, ktore chce przechowywac, czyli od   0   do   N-1
	IntervalTree( int N ){	
		s = 1;
		while( s < N ) s <<=1;
		s <<= 1;		
		
		tab = new _T[ s ];
		maxval = new _T[s];		
		REP(i,s) tab[i] = maxval[i] = 0;
		
		s >>= 1;				
	}
	
	void Add( int p, int q, int val ){
		p += s;
		q += s;
		while( p < q ){
			if( val > maxval[p] ) maxval[p] = val;
			if( val > maxval[q] ) maxval[q] = val;
			p++;
			q--;
			p >>= 1;
			q >>= 1;
		}
		
		if( p == q ){
			if( val > maxval[p] ) maxval[p] = val;
		}		
	}
	
	_T getVal( int p ){
		p += s;
		int m = maxval[p];
		while( p >= 1 ){
			if( maxval[p] > m ) m = maxval[p];
			p >>= 1;
		}
		return m;
	}
	
	void testMe(){
		int p = 10;
		REP( i,p ){
			int b = rand()%s;
			int a = rand()%(b+1);
			int v = rand()%(p*p);
			printf( "Dodaje pokrycie (%d,%d) o wartosci %d\n",a,b,v );	
			Add( a,b,v );	
		}  
		
		printf( "Oto stan drzewa\n" );
		REP(i,s){
			printf( "Maximum dla i=%d wynosi %d\n",i, getVal(i) );
		}
	}
	
	void writeMe(){
		REP(i,s){
			printf( "%d ", getVal(i) );
		}
		printf("\n");
	}
	
};


VVI V; // graf
VI depthOnPath; // depthOnPath[i] to glebokosc danego wierzcholka na swojej sciezce
VVI pathrev; // pathrev[i] to lista wierzcholkow nalezacych do sciezki nr i (glebokosc wierzcholka maleje na tej liscie)
VI path; // path[i] to nr sciezki, do ktorej nalezy wierzcholek nr i
VI par; // par[i] to nr wierzcholka bedacego rodzicem wierzcholka i
VI subtreeSize; // subtreeSize[i] to liczba wierzcholkow w poddrzewie o korzenie w i
vector< IntervalTree<int> > trees; // trees[i] is the interval tree representing path number i

void createTree( int num, int par ){
	::par[num] = par;
	subtreeSize[num] = 1;
	
	REP( i, SIZE(V[num]) ){
		if( V[num][i] != par ){
			createTree( V[num][i],num );
			subtreeSize[num] += subtreeSize[ V[num][i] ];
		}
	}	
}

void createPaths( int num, int &pathnum, int depth ){
	if( SIZE( pathrev ) <= pathnum ){
		pathrev.PB( VI(0) );		
	}
	
	pathrev[ pathnum ].PB(num);
	depthOnPath[ num ] = depth;
	path[num] = pathnum;
	
	if( num != par[num] && SIZE( V[num] ) == 1 ){
		IntervalTree<int> T(depth+3);
		trees.PB( T );
	}
	else{
		int M = 0;
		int ind = -1;
		REP( i, SIZE(V[num]) ){
			if( V[num][i] != par[num] ){
				if( subtreeSize[ V[num][i] ] > M ){
					M = subtreeSize[ V[num][i] ];
					ind = i;
				}
			}
		}
		
		if( ind == -1 ) return; // to mogloby sie zdarzyc, gdyby caly graf skladal sie tylko z jednego wierzcholka...
		
		createPaths( V[num][ind], pathnum, depth+1 );
		REP( i, SIZE(V[num]) ){
			if( i != ind && V[num][i] != par[num] ){
				//printf( "pathnum = %d   V[%d][%d] = %d\n", pathnum, num,i,V[num][i] );
				pathnum++;
				createPaths( V[num][i], pathnum,0 );
			}
		}		
	}	
}

//**********************
int N,M;

//**********************

void updateSinglePath( int a, int lca, int val ){
	int p = a;
	int q;
	
	while( path[p] != path[lca] ){
		q = pathrev[ path[p] ][0];
		trees[ path[p] ].Add( 0, depthOnPath[p],val );
		p = par[q];
	}
	
	trees[ path[p] ].Add( depthOnPath[lca], depthOnPath[p],val );	
}

void updateWholePath( int a, int b, int val ){
	int lca = LCA::Ask( a,b );
	//printf( "lca = %d\n",lca );
	updateSinglePath( a, lca, val );
	updateSinglePath( b, lca, val );	
}



void solve(){
	scanf( "%d %d",&N,&M );
	V = VVI(N);
	path = VI(N);
	par = VI(N);
	depthOnPath = VI(N);
	subtreeSize = VI(N);
	pathrev.clear();
	trees.clear();
	
	int a,b;
	REP( i,N-1 ){
		scanf( "%d %d",&a,&b );
		V[a-1].PB(b-1);
		V[b-1].PB(a-1);
	}
	
	LCA::V = V;
	LCA::create_CTree(0);
	
	createTree(0,0);
	int pathnum = 0;
	createPaths(0,pathnum,0);
	
	
	/*printf( "par:  " ); REP( i,N ) printf( "par[%d] = %d  ---  ", i,par[i] ); printf("\n");
	printf( "path:  " ); REP( i,N ) printf( "path[%d] = %d  ---  ", i, path[i] );
	printf( "\npathrev:\n" ); REP( i, SIZE(pathrev) ){ printf( "\tpathrev[%d]:  ",i ); REP( k, SIZE(pathrev[i]) ) printf( "%d  ---  ", pathrev[i][k] ); printf("\n"); }
	printf( "\ndepthOnPath:  " ); REP( i, N ) printf( "%d  ---  ",depthOnPath[i] ); printf("\n");
	printf( "\ntrees:\n" ); REP( i, SIZE(trees) ){ printf( "\ttree[%d]:  ",i ); trees[i].writeMe(); }
	*/
	
	int val;
	REP( i,M ){
		scanf( "%d %d %d",&a,&b,&val );
		
		//printf( "a = %d   b = %d   ",a-1,b-1 );
		updateWholePath( a-1,b-1,val );
	}
	
	REP(i,N){
		val = trees[ path[i] ].getVal( depthOnPath[i] );
		printf( "%d ", val );		
	}
	
	printf("\n");
	
	
	
}

int main(){
	
	
    int l_zest;    
    scanf( "%d",&l_zest );
    
	while( l_zest-- ){
        solve();


	}


	return 0;
}












