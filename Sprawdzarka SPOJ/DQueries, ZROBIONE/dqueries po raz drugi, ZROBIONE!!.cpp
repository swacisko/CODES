#include<stdio.h>
//#include<iostream>
#include<vector>
#include<string>
#include<map>
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

int N,K,a,b,c,y,t,w,l_zest;
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


bool *marked;
int *arr;
int Left[1000010];
int *next;
bool M[1000010];


vector< pair< PII,int> > vec;


int main(){

	int q;
	REP(i,1000010) {
		Left[i] = -1;
		M[i] = false;
	}
	
	scanf("%d",&N);
	vec.clear();
	marked = new bool[N+1];
	arr = new int[N+1];
	next = new int[N+1];
	CountTree tree( int( ceil(log2(N+2)) + 0.1 ) );
	
	REP( i,N ){
		scanf( "%d",&t );
		arr[i] = t;	
		marked[i] = false;	
	}

	FORD(i,N-1,0){
		next[ i ] = Left[ arr[i] ];
		Left[ arr[i] ] = i;
	}
	
//	REP(i,N) printf( "next[%d] = %d\n",i,next[i] );
	
	REP( i,N ){
		if( M[ arr[i] ] == false ){
			M[ arr[i] ] = true;
			marked[ i ] = true;
			tree.Set( i,1 );
	//		printf( "marked[%d] = true\n",i );
		}
	}

	scanf("%d",&q);
//	vec.PB( MP( MP(0,1),-1 ) );
	REP( i,q ){
		scanf( "%d %d",&a,&b );
		vec.PB( MP( MP(a-1,b-1),i ) );
	}
	
	sort( vec.begin(), vec.end() );
	
	
	VI ans;
	ans.clear();
	
	int lbeg = 0;
	int ind = 0;
	int ile = 0;
	int t = 0;
	int e = 0;
	
	while( t < vec[0].ST.ST ){
		if( marked[t] == true ){
			marked[t] = false;
			tree.Set( t,0 );
			
			if( next[t] != -1 && next[t] >= vec[0].ST.ST ) {
				marked[ next[t] ] = true;
				tree.Set( next[t],1 );
			}
		}
		t++;
	}
	
	REP( i,q+1 ){
	//	REP( k,N ) printf( "marked[%d] = %d\n",k,marked[k] );
	//	printf("\ntree:\n");
	//	FOR( k,tree.s,tree.s+5 ) printf( "tree[%d] = %d\n",k,tree.el[k] );
	//	printf("\n");
		
		lbeg = vec[i].ST.ST;
		ind = i;
		while( ind < q && lbeg == vec[ind].ST.ST ){
			ile = tree.Find( vec[ind].ST.ST, vec[ind].ST.ND );
		//	printf( "Wstawiam przedzial %d-%d do odpowiedzi o numerze %d  ile = %d\n",lbeg,vec[i].ST.ND,vec[i].ND,ile );
			ans.PB( ile );
			ind++;
		}
		
		if( ind >= q ) break;
		t = lbeg;
		e = vec[ind].ST.ST;
		
		while( t < e ){
			if( marked[t] == true ){
				marked[t] = false;
				tree.Set( t,0 );
				
				if( next[t] != -1 && next[t] >= e ) {
					marked[ next[t] ] = true;
					tree.Set( next[t],1 );
				}
			}			
			t++;			
		}
		
		i = ind-1;
	}
	
//	ans.erase( ans.begin() );
//	vec.erase( vec.begin() );
	int *shuffle = new int[q];
	REP(i,q){
		shuffle[ vec[i].ND ] = ans[i];
	}
	
	REP(i,q) printf("%d\n",shuffle[i]);
//	REP(i,q) cout << shuffle[i] << endl;
	
}








