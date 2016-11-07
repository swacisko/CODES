#include<stdio.h>
#include<string>
#include<map>
#include<vector>
#include<cmath>
#include<queue>
#include<string.h>
#include<sstream>
#include<algorithm>

using namespace std;

#define REP( x,y ) for( int x=0; x<(y); x++ )
#define FORD( x,y,z ) for( int x=y; x>=(z); x-- )
#define FOR(x,b,e) for( int x = b; x <= (e); ++x )
#define SIZE(v) (int)v.size()
#define PB push_back
#define PH push_heap
#define POP pop_back
#define MP make_pair
#define ST first
#define ND second

int N,M,K,a,b,c,y,t,w,l_zest;
const int INF = 1000000001;
typedef vector<double> VD;
typedef pair<double,int> PDI;
typedef pair<double, double> PDD;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef map< PII, bool > MPIIB;
typedef long long LL;


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


struct CoverITree{
	// UWAGA, liczbiue calkowitej a odpowiada przedzial [a-1,a]
	#define nr ( wp + wk + 1 ) >> 1
	int *el,s,p,k,il;
	PII *maxstat;
	CoverITree( int size ){ 
		el = new int[ s = 1 << (size+1) ];
		maxstat = new PII[s];
		REP(x,s) el[x] = 0;
		FOR(x,s/2,s-1){
			maxstat[x].ST = 0;
			maxstat[x].ND = x - ( s >> 1 ) + 1; // tu mozna dodac 1 aby indeksowanie bylo od 1 a nie od zera, w funkcjach to nie bedzie mialo zadnego wplywu
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
		}
	}
	
	~CoverITree(){
		delete[] el;
		delete[] maxstat;
	}
	
	void Mark( int wp, int wk, int g ){
		if( k <= wp || p >= wk ) return;		
		if( p <= wp && k >= wk ) el[g] += il;
		else{
			Mark( wp, nr, 2*g );
			Mark( nr,wk,2*g+1 );
		}
		
		if( 2*g < s ){ // to jest czesc do wyznaczania maksymalnego elementu w drzewie
			int M = ( maxstat[2*g].ST > maxstat[2*g+1].ST ? 2*g : 2*g+1 );
			maxstat[g].ST = maxstat[M].ST + el[g];
			maxstat[g].ND = maxstat[M].ND; 
		}
		else maxstat[g].ST += il; // jesli jest lisciem to wystarczy, ze dodam do niego wartosc nowego pokrywajacego go przedzialu

	}
	
	void Add( int p1, int k1, int i1 ){
		p = p1-1;
		k = k1;
		il = i1;
		Mark( 0, s>>1 ,1 );
	}
	
	PII maxstats( int wp, int wk, int g ){
		if( p >= wk || k <= wp )	return MP( -INF,-INF ); // jesli jest rozlaczny, to zwracam bzdety		
		if( (p <= wp && k >= wk) || ( wp == wk-1 ) )	return maxstat[g]; // jesli jest pokryty w calosci to zwracam jego stat
		PII m1 = maxstats( wp,nr,2*g );
		PII m2 = maxstats( nr,wk,2*g+1 );
		PII M;
		if( m1.ST > m2.ST ){ M.ST = m1.ST; M.ND = m1.ND;	}
		else{ M.ST = m2.ST; M.ND = m2.ND;  }
		M.ST += el[g];
		return M;
	}
	
	PII getMaxStat( int p1, int k1 ){
		p = p1-1;
		k = k1;
		return maxstats( 0,s>>1,1 );
	}

};




vector< pair<int,pair<PII,int> > > V;
const int VAL = int( ceil( log2(50010) )+0.1 ) ;

int main(){
	
	int ILE = 0;
	scanf("%d",&l_zest);
	while(l_zest--){
		scanf("%d",&N);
		ILE = 0;
		V.clear();
		CoverITree coveri_tree( VAL );
		CountTree count_tree( VAL );
		
		REP(i,N){
			scanf( "%d %d %d",&a,&b,&c );
			coveri_tree.Add( a,b,1 );
			V.PB( MP( b-a, MP( MP(a,b),c) ) );
		}
		
		sort( V.begin(), V.end() );
		
		REP( i,V.size() ){
		//	printf( "\ni = %d  V[%d].ST.ST = %d  V[%d].ST.ND = %d   V[%d].ND = %d\n",i,i,V[i].ND.ST.ST,i,V[i].ND.ST.ND,i,V[i].ND.ND );
			t = V[i].ND.ND - count_tree.Find( V[i].ND.ST.ST, V[i].ND.ST.ND );
		//	printf( "count_tree_VAL = %d\n", count_tree.Find( V[i].ND.ST.ST, V[i].ND.ST.ND ) );
			if( t < 0 ) t = 0;
			
			REP(k,t){
				a = coveri_tree.getMaxStat( V[i].ND.ST.ST, V[i].ND.ST.ND ).ND;
		//		printf( "\tgetMaxStat_index = %d\n",a );
				coveri_tree.Add( a,a, /*-coveri_tree.FindSum( a,a )*/ -INF );
				ILE++;
				count_tree.Set( a,1 );
			}
			
			coveri_tree.Add( V[i].ND.ST.ST, V[i].ND.ST.ND,-1 );
		}
		
		printf( "%d\n",ILE );
		
		
	}
	
	
}



















