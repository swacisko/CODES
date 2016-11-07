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
#define WRITE( V ){ REP(trx,SIZE(V)) printf( "%d ",V[trx] ); printf("\n"); }
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
typedef vector< VPII > VVPII;



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


VVI mapa;
int N,M;

VVI horiz, vert, sq;
VVPII largsq;

vector< CTree* > treesvert, treeshoriz;


void solve(){
	char c;
	
	scanf( "%d %d",&N,&M );
	
	mapa = VVI(N,VI(M,0));
	
	REP( i,N ){
		REP(k,M){
			
			//scanf( "%c",&c );
			cin >> c;
			
			if( c == '.' ) mapa[i][k] = 1;
			else mapa[i][k] = 0;			
		}
	}
	
	printf( "jestem tu\n" ); 
	
	horiz = mapa;
	vert = mapa;
	sq = mapa;
	
	REP( y,N ){
		FOR( x,1,M-1 ){
			if( horiz[y][x] == 1 ) horiz[y][x] += horiz[y][x-1];			
		}
	}
	
	REP( x,M ){
		FOR( y,1,N-1 ){
			if( vert[y][x] == 1 ) vert[y][x] += vert[y-1][x];
		}		
	}
	
	cout << "Tutaj tez" << endl;
	
	int p,q,z;
	FOR( y,1,N-1 ){
		FOR( x,1,M-1 ){
			if( mapa[y][x] == 1 ){		
				p = vert[y][x];
				q = horiz[y][x];
				z = sq[y-1][x-1];		
				sq[y][x] = min( z+1, min( p,q ) );
			}
		}		
	}
	
	cout << "i tu" << endl;
	
	CTree tree(M+1);
	cout << "nono" << endl;
	treeshoriz.clear();
	REP(i,N) treeshoriz.PB( new CTree(M+1) );
	
	cout << "hau" << endl;
	tree = CTree(N+1);
	treesvert.clear();
	REP(i,M) treesvert.PB( new CTree(N+1) );
	
	cout << "Tutaj?" << endl;
	
	REP( y,N ){
		REP( x,M ){
			treeshoriz[y]->Add( x,x,vert[y][x] );
			treesvert[x]->Add( y,y, horiz[y][x] );			
		}		
	}
	
	largsq = VVPII(N, VPII(M) );
	REP(y,N) REP(x,M) largsq[y][x].ST = largsq[y][x].ND = mapa[y][x];
	
	PII P,temp;
	//int t,a,b;
	
	cout << "A nawet tu" << endl;
	REP( y,N ){
		REP( x,M ){
			if( y == 0 && mapa[y][x] == 1 ){
				largsq[y][x].ST = 1;
				largsq[y][x].ND = horiz[y][x];
			}
			else if( x == 0 && mapa[y][x] == 1 ){
				largsq[y][x].ST = vert[y][x];
				largsq[y][x].ND = 1;				
			}
			else if( x != 0 && y != 0 && mapa[y][x] == 1 ){
				
				temp = largsq[y-1][x];
				
				if( temp.ND >= horiz[y][x] ){
					P.ST = temp.ST+1;
					P.ND = temp.ND;
				}
				else{
					P.ST = treeshoriz[y]->FindMin( x - horiz[y][x]+1,x ).ST;
					P.ND = horiz[y][x];
					
					if( 1+horiz[y][x] > P.ST + P.ND ){
						P.ST = 1;
						P.ND = horiz[y][x];
					}			
				}
				
				largsq[y][x] = P;
				
				temp = largsq[y][x-1];
				
				if( temp.ST >= vert[y][x] ){
					P.ST = temp.ST;
					P.ND = temp.ND+1;					
				}
				else{
					P.ST = vert[y][x];
					P.ND = treesvert[x]->FindMin( x - vert[y][x]+1,x ).ST;
					
					if( 1 + vert[y][x] > P.ST + P.ND ){
						P.ST = vert[y][x];
						P.ND = 1;
					}					
				}
				
				if( largsq[y][x].ST + largsq[y][x].ND < P.ST + P.ND ) largsq[y][x] = P;				
			}			
		}		
	}
	
	
	
	
	
	
	
	
	
	
	map<int,int> ans;
	
	
	REP( y,N ){
		REP( x,M ){
				ans[ 2* (largsq[y][x].ST + largsq[y][x].ND ) ]++;							
		}		
	}
	
	
	for( map<int,int>::iterator it = ans.begin(); it != ans.end(); it++ ){
		
		printf( "%d x %d\n", it->ND, it->ST );
		
		
		
	}
	
	

}







int main(){
	int l_zest;
	scanf( "%d",&l_zest );  

    while( l_zest-- ){
		
		solve();
		
	}

	return 0;
}












