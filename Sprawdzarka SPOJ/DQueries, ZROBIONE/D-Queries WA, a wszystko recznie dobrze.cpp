#include<stdio.h>
//#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<cmath>
#include<queue>
#include<fstream>
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

int N,K,a,b,c,y,d,t,w,l_zest;
const int INF = 1000000001;
typedef vector<double> VD;
typedef pair<double,int> PDI;
typedef pair<double, double> PDD;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef map< PII, bool > MPIIB;
typedef long long LL;

template<class typ> inline typ maximum( typ a, typ b ){ return a > b ? a : b; }
template<class typ> inline typ minimum( typ a, typ b ){ return a < b ? a : b; }

int *arr;
bool *marked;
int *next; // next[i] - pozycja nastepnego elementu o wartosc arr[i], lub -1, gdy nastepnej nie ma
//int *leftMost;
int *leftMost;
bool *M;
vector< pair<PII,int> > queries;

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
		for( p+=s; p>0; p>>=1 ) el[p] += t;
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

/*
VI n2;

void getSecondAnswer( int p, int q ){
	bool *is = new bool[10000];
	REP(x,10000) is[x] = false;
	int ile = 0;
	FOR(i,p-1,q-1){
		if( !is[ arr[i] ] ){
			ile++;
			is[ arr[i] ] = true;
		}
	}
	n2.PB(ile);
	delete[]is;
}*/


int main(){
	
	VI ans;
	//	ifstream strin("przykladowe_iny.txt");
		
		scanf( "%d",&N );
	//	strin >> N;
		
		CountTree tree( ceil( log2(N) ) );
	//	printf( "tree.s = %d\n",tree.s ); // to sie zgadza
	
		arr = new int[N];
	//	leftMost = new int[N];
		marked = new bool[N];
		
		int MAXIMAL = 0;
		REP(i,N){
			scanf( "%d",&a );
			MAXIMAL = maximum( MAXIMAL,a );
			arr[i] = a;
		//	strin >> arr[i];
		}
		
		M = new bool[ MAXIMAL + 15 ];
		leftMost = new int[ MAXIMAL + 15 ];
		
		REP( i,MAXIMAL+10 ) M[i] = true;
		REP( i,N ) M[ arr[i] ] = false;		
		REP(i,N) marked[i] = false;
		REP( i,MAXIMAL + 10 ) leftMost[i] = -1;
		REP(i,N){
			if( !M[ arr[i] ] ){ 
				M[ arr[i] ] = true;
				marked[i] = true;
				tree.Set( i,1 ); // ustawiamy, ze wartosc el[s+i] = 1, tzn ze arr[i] jest zaznaczone
			}
		}
		
		next = new int[N];
		FORD( i,N-1,0 ){
			next[i] = leftMost[ arr[i] ];
			leftMost[ arr[i] ] = i;			
		}
		
	//	REP(i,N) printf( "next[%d] = %d\n",i,next[i] );
		
		scanf( "%d",&d );
	//	strin >> d;
	
		queries.clear();
		REP(i,d){
			scanf( "%d %d",&a,&b );
		//	strin >> a >> b;
			queries.PB( MP( MP(a-1,b-1),i ) );
		//	getSecondAnswer(a,b);
		}
		
	//	vector< pair<PII,int> > kol = queries;
		
		sort( queries.begin(), queries.end() ); // sortuje wzgledem rosnacego poczatku przedzialu
		
	//	printf( "Wczytalem queries\n" );
//		REP(i,d) printf( "[%d,%d]  ",queries[i].ST.ST, queries[i].ST.ND );
	//	printf("\n");
		
		ans.clear();
		int t,e;
		REP( i,d ){
			
			t = queries[i].ST.ST;
			while( i < d && queries[i].ST.ST == t ){
				ans.PB( tree.Find( queries[i].ST.ST, queries[i].ST.ND ) );
				i++;
			}
			
		//	printf( "i = %d\n",i );
			if(i >= d ) break;
			
			e = queries[i].ST.ST;			
		//	printf( "i = %d  t = %d  e = %d\n",i,t,e );
			
			while( t < e ){
				if( marked[t] == true && next[t] > t ){
					tree.Set(t,0);
					marked[t] = false;
					marked[ next[t] ] = true;
					if( next[t] >= e ){
						tree.Set( next[t],1 );
					//	printf( "Dodaje do tree element %d\n",next[t] );
					}	
				}
				else if( marked[t] == true ){
					marked[t] = false;
					tree.Set( t,0 );
				}
				
				t++;
			}
			i--;
		}
		
	//	printf( "Jestem poza repem\n" );
		int *shuffle = new int[d];
		REP(i,d){
			shuffle[ queries[i].ND ] = ans[i];
		}
		REP(i,d){
		//	if( shuffle[i] == n2[i] );// printf("Jest ok  %d  powinno byc == %d\n",shuffle[i],n2[i] );			
		//	else printf( "\n%d  powinno byc == %d, ale tak nie jest!!!! query nr %d,  a = %d  b = %d \n",shuffle[i],n2[i],i,kol[i].ST.ST, kol[i].ST.ND );
			if( i < d-1 ) printf( "%d\n",shuffle[i] );
			else printf( "%d",shuffle[i] );
		}
		
	//	printf("BEZ NOWEJ LINI");
		delete[]arr; arr =0;
		delete[]next; next=0;
	//	delete[]leftMost;
		delete[]marked; marked=0;
		delete[]shuffle; shuffle=0;
	
	return 0;
}








