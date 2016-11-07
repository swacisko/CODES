#include<cstdio>
//#include<iostream>
#include<vector>
//#include<string>
//#include<map>
//#include<complex>
//#include<stack>
//#include<list>
#include<bitset>
#include<set>
//#include<iterator>
#include<cmath>
//#include<queue>
//#include<time.h>
//#include<string.h>
//#include<fstream>
//#include<sstream>
#include<algorithm>
//#include<conio.h>

using namespace std;

#define REP( x,y ) for( int x=0; x<(y); x++ )
#define FORD( x,y,z ) for( int x=y; x>=(z); x-- )
#define FOR(x,b,e) for( int x = b; x <= (e); ++x )
#define SIZE(v) (int)v.size()
#define ALL(c) c.begin(),c.end()
#define VAR(v,n) _intypeof(n) v=(n)
#define FOREACH(i,c) for( VAR(i,c.begin());i!=c.end();++i )
#define PB push_back
#define MP make_pair
#define ST first
#define ND second
#define WRITE( V ){ FOREACH(it,V) cout << *it << ", "; cout << endl; }
#define WRITE_ALL(V) {  REP( i,SIZE(V) ){ cout  << i << " ---- ";  FOREACH(it,V[i]) cout << *it << ", "; cout << endl;     } }
#define WRP(p) p.ST << " " << p.ND
#define CLEAR( dst,quant ) memset( dst,0, (quant)*sizeof( _intypeof(*dst) ) );
#define WAR if( show_help )
//#define ENDL(x) REP(crow,(x)) cout << endl;

const int MILJON = 1000000;

const bool show_help = 1;
long long INF = 1000000001;
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
typedef vector<char> VC;
typedef vector< VC > VVC;


VVI SUMY;

int getsumy( int w, int h1, int h2 ){
	if( h1 < 0 ) h1 = 0;
	if( h2 >= SIZE(SUMY) ) h2 = SIZE(SUMY)-1;
	
	int res = SUMY[h2][w];
	if( h1 > 0 ) res -= SUMY[h1-1][w];
	return res;	
}


class CTree{
public:
	#define NR ((p1+k1)>>1)
//	typedef int int; // to co ma byc przechowywane w wezlach
	int N; // ilosc liczb, na ktorych chcemy operowac, tzn jesli chcemy operowac na 5 liczbach, to potrzebujemy stworzyc tablice rozmiarow 2 * 8
	int s; // jest to liczba bedaca najmniejsza potega dwojki, nie mniejsza niz N, UWAGA - liczba   L do ktorej chcemy sie odniesc jest w tablicy tab na miejscu s + L
	int* sum; // tablica sumy elementow w danym przedziale - w zasadzie to reprezentuje tylko liczby, ktore wstawiamuy do drzewa, zadnych sum nie przechowuje w wezlach, bo sie nie da :)
	int* el; // tabllica reprezentujaca ilosc przedzialow pokrywajacych dany wezel
	int size; // rozmiar tablicy tab(i innych jesli beda)
	int p,k; // liczby p oraz k oznaczaja poczatek i koniec przedzialu, ktory chcemy dodac
	int l; // l oznacza ilosc 'przedzialow' jakie chcemy dodac 
	int ID;
	
	
	// konstruktor przyjmujacy jako wartosc maksymalna liczbe, na ktorej bedziemy wykonywac operacje, tzn tab bedzie reprezentowac liczby 0,1,2,...,N-1   !!!
	CTree( int aN, int id ) : N(aN), s(1), ID(id) {
		while( s <= N ) s <<= 1;
		size = (s << 1 );
				
		sum = new int[size];		
		el = new int[size];		
		REP(i,size){ 
			sum[i] = 0;
			el[i] = 0;
		}
		
	}
		
	~CTree(){
		delete[] sum; sum = 0;
		delete[] el; el = 0;
	}
	
	// p1 - poczatek przedzialu reprezentowanego przez wezel,  k1 - koniec przedzialu repr.przez wezel,  g - numer wezla
	void help_Add( int p1, int k1, int g ){
		if( p1 > k || k1 < p ) return; // jesli przedzialy sa rozlaczne, to nic nie robie
		if( p1 >= p && k1 <= k ){ // jesli wstawiany przedzal zawiera w calosci przedzial reprezentowany przez wezel to...
			sum[g] += l*getsumy( ID, max( p,p1 ), min(k,k1) );
			el[g] += l;
			return;
		}
		
		// w przeciwnym razie rozbijam wezel na 2 podwezly
		help_Add( p1, NR, (g<<1) );
		help_Add( NR + 1, k1, (g<<1)+1 );
		
	//	int overlap = min( k,k1 ) - max( p,p1 ) + 1;
		sum[g] = sum[(g<<1)] + sum[(g<<1)+1] + el[g]* getsumy( ID, max(p,p1), min(k,k1) ) ;
		
	}
	
	// funkcja dodaje l1 przedzialow p1, p1+1, ..., k1
	void Add( int p1, int k1, int l1=1 ){
	//	printf("Wchodze do Add\n");
		p = p1;		k = k1;		l = l1;
		help_Add( 0,s-1,1 );
	//	printf("Wychodze z Add\n");
	}
	
	
	// p1 - poczatek przedzialu reprezentowanego przez wezel,  k1 - koniec przedzialu repr.przez wezel,  g - numer wezla
	int help_sum( int p1, int k1, int g ){
		if( p1 > k || k1 < p ) return 0; // jesli przedzialy sa rozlaczne, to nic nie robie
		if( p1 >= p && k1 <= k ) return sum[g]; // jesli wstawiany przedzal zawiera w calosci przedzial reprezentowany przez wezel to zwracam wartosc sum danego wezla
												// poniewaz wartosc sum jest aktualizowana w help_Add, wiec teraz nie musze dodawac iloscynu dlugosci przedzialu z el[g]	
		//int overlap = min( k,k1 ) - max( p,p1 ) + 1;											
		return ( help_sum( p1,NR, (g<<1) ) + help_sum( NR + 1, k1, (g<<1)+1 ) + el[g]*getsumy( ID, max(p,p1), min(k,k1) )  ); // ale tutaj dodaje wartosci znalezione w podwezlach plus ilosc pokryc danego wezla
	}
	
	// funkcja zwraca sume elementow na przedziale p1-k1 wlacznie
	int FindSum( int p1, int k1 ){
	//	printf( "Wchodze do FindSum ID = %d  p1=%d  k1=%d\n", ID, p1,k1 );
		p = p1;		k = k1;
		int res = help_sum( 0,s-1,1 );
	//	printf("\tWychodze z FindSum ID = %d\n", ID);
		return res;
	}
	
	
	
	// funkcja ustawiajaca wartosc danego elementu o indeksie ind na okreslona wartosc val
	void set( int ind, int val ){
		int s = FindSum( ind, ind );
		Add( ind, ind, val - s );
	}
	
	// funkcja zwracajaca dana wartosc elementu o indeksie ind
	int get( int ind ){
		return FindSum( ind, ind );
	}
	
	/*void operator=( const CTree & oth ){
		delete[]sum; sum = 0;
		delete[]el; el = 0;
		
		size = oth.size;
		N = oth.N;
		s = oth.s;
		
		sum = new int[ size ];
		el = new int[ size ];
		
		REP(i,size){
			sum[i] = oth.sum[i];
			el[i] = oth.el[i];
		}
	}*/
	
	/*void write(){
		REP( i, N ){
			cout << "Emelemt " << i <<"-ty:  " << FindSum( i,i ) << endl;
		}
		
		ENDL(1);
	}*/
	
};


struct Well{
	
public:
		Well( int r, int id ){
			this->r = r;
			ID = id;
			w = h = -1;
		}
		
		int ID;
		int w,h;
		int r;	
};


bool sortById( const Well &v, const Well &w ){
	return v.ID < w.ID;
}

bool sortBySize( const Well &v, const Well &w ){
	return v.r < w.r;
}


typedef vector<Well> VW;

int R,W,H;
VW wells;
VVI mapa;
vector< CTree* > trees;
VVB was;
bool swapped;

void readData(){
	int r;
	scanf( "%d", &R );
	wells.clear();
	REP(i,R){
		scanf( "%d",&r );
		wells.PB( Well( r,i ) );
	}
	
	scanf( "%d %d", &W, &H );
		
	mapa = VVI( H, VI(W) );
	
	REP(i,H){
		REP(k,W){
			scanf( "%d", &mapa[i][k] );			
		}		
	}
	
	swapped = false;
	/*if( W > H ){
		swapped = true;
		VVI m = VVI(W,VI(H));
		REP( i, W ){
			REP( k,H ){
				m[i][k] = mapa[k][i];
			}			
		}		
		
		mapa = m;
		swap(W,H);
	}*/
	
	was = VVB( H, VB(W,false) );
	
}

void createTrees(){
	//printf("createTrees\n");
	
	trees.clear();
	REP(i,W){
		trees.PB( new CTree(H,i) );
	//	printf( "Dodalem %d drzewo\n", i+1 );
	}
	
	//printf("Stworzylem drzewa\n");
	REP( i, SIZE(mapa) ){
		REP( k, SIZE(mapa[i]) ){
				trees[k]->Add(i,i);
		//		printf( "%d,%d\t", mapa[i][k], trees[k]->FindSum(i,i) );
		}
	//	printf("\n");
	}	
}

void createSUMY(){
	SUMY = mapa;
	for( int i=1; i<H; i++ ){
		for(int k=0; k<W; k++){
			SUMY[i][k] += SUMY[i-1][k];	
		//	printf("%d\t", SUMY[i][k]);		
		}
	//	printf("\n");
	}	
}


int getSum( int w, int h, int r ){
	int sum = 0;
	int dh = 0;
	
	for( int i = w-r; i<= w+r; i++ ){
		//if( i < 0 || i >= W ) continue;	
		if( i < 0 ){ i = -1; continue; }
		else if( i >= W ) break;	
		
		dh = (int) sqrt( r*r - (w-i)*(w-i) );
		
		sum += trees[i]->FindSum( max(0,h-dh), min(H-1,h+dh) );						
	}
	
	return sum;
}


void AddToTrees( int w, int h, int r ){
	int dh = 0;
	
	for( int i = w-r; i<= w+r; i++ ){
		//if( i < 0 || i >= W ) continue;
		if( i < 0 ){ i = -1; continue; }
		else if( i >= W ) break;
		
		dh = (int) sqrt( r*r - (w-i)*(w-i) );
		
		trees[i]->Add( max(0,h-dh), min(H-1,h+dh) );
	}
}


PII getMinPos( int r ){
	
	PII pos;
	int minval = INF;
	int val;
	
	int DISTH = 29;
	int DISTW = 27;
	
	if( W*H*R <= 2000000 ) DISTW = DISTH = 1;
	
//	printf( "Hello1\n" );
	for( int i=0; i<H; i++ ){
		if( was[i][0] == true ) continue;
		val = getSum( 0,i,r );
		if( val < minval ){
			minval = val;
			pos = MP( i,0 );
		}
		
		if( was[i][W-1] == true ) continue;
		val = getSum( W-1,i,r );
		if( val < minval ){
			minval = val;
			pos = MP( i,W-1 );
		}			
	}
	
//	printf( "Hello2\n" );
	for( int k=0; k<W; k++ ){
		if( was[0][k] == true ) continue;
		val = getSum( k,0,r );
		if( val < minval ){
			minval = val;
			pos = MP( 0,k );
		}
		
		if( was[H-1][k] == true ) continue;
		val = getSum( k,H-1,r );
		if( val < minval ){
			minval = val;
			pos = MP( H-1,k );
		}		
	}
	
//	printf( "Hello3\n" );
	if( DISTW != 1 ){		
		for( int i=1; i<=4; i++ ){
			for( int k=1; k<=4; k++ ){
				if( was[i][k] == true ) continue;
				val = getSum( k,i,r );
				if( val < minval ){
					minval = val;
					pos = MP( i,k );
				}
				
				if( was[H-i-1][k] == true ) continue;
				val = getSum( k,H-i-1,r );
				if( val < minval ){
					minval = val;
					pos = MP( H-i-1,k );
				}
				
				if( was[i][W-k-1] == true ) continue;
				val = getSum( W-k-1,i,r );
				if( val < minval ){
					minval = val;
					pos = MP( i,W-k-1 );
				}
				
				if( was[H-i-1][W-k-1] == true ) continue;
				val = getSum( W-k-1,H-i-1,r );
				if( val < minval ){
					minval = val;
					pos = MP( H-i-1,W-k-1 );
				}
				
			}	
			
		}
	} // IF DISTW != 1
		
//	printf( "Hello4\n" );
	for( int i=1; i<H-1; i+= DISTH ){		
		for( int k=1; k<W-1; k+=DISTW ){
			if( was[i][k] == true ){
				//if( k >= 0 && k < W-1 ) k -= (DISTW-1);
				continue;
			}
			val = getSum( k,i,r );
			if( val < minval ){
				minval = val;
				pos = MP( i,k );
			}			
		}		
	}
	
	
	was[ pos.ST ][pos.ND] = true;
	
//	printf( "minval = %d\n",minval );
	return pos;
}

void writeMap(){
	
	REP( i, H ){
		REP(k,W){
			printf( "%d\t", trees[k]->FindSum(i,i) );
		}		
		printf("\n");
	}	
}


void solve(){
	readData();	
	createSUMY();
	createTrees();
	
//	printf("Przed czymkolwiek\n");
	//writeMap();
	
	sort( ALL(wells), sortBySize );
	
	reverse( ALL(wells) );
	
	PII pos;
	
	REP( r, R ){				
		
		
	//	printf( "Studnia %d: r = %d\n", r+1, wells[r].r );
		pos = getMinPos( wells[r].r );
		
		wells[r].h = pos.ST;
		wells[r].w = pos.ND;
		
		AddToTrees( pos.ND, pos.ST,wells[r].r );
		
	//	printf("Po dodaniu pierwszej studni na pozycji w = %d   h = %d\n\n", pos.ND, pos.ST );
	//	writeMap();
	}
	
	sort( ALL(wells), sortById );
	
	REP( i,R ){
		if( swapped == false ) printf( "%d %d\n", wells[i].h, wells[i].w );
		else printf( "%d %d\n", wells[i].w, wells[i].h );
	}
	
	
}

int main(){
	
	solve();	
	
	
	return 0;
}




/*
3
2 4 6
10 8
0 1 2 3 4 5 6 7 8 9
1 2 3 4 5 6 7 8 9 0
2 3 4 5 6 7 8 9 0 1
3 4 5 6 7 8 9 0 1 2
4 5 6 7 8 9 0 1 2 3
5 6 7 8 9 0 1 2 3 4
6 7 8 9 0 1 2 3 4 5
7 8 9 0 1 2 3 4 5 6






*/










