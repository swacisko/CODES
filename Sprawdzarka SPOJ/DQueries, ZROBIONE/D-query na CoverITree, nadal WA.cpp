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
		p = p1;
		k = k1+1;
		il = i1;
		Mark( 0, s/2,1 );
	}
	
	int F( int wp, int wk, int g ){
		if( p >= wk || k <= wp ) return 0;
		
		if( el[g] > 0 ) return minimum( k,wk ) - maximum( p,wp );
		
		if( p <= wp && k >= wk ) return ma[g];
		
		return (wp == wk-1) ? 0 : ( F( wp , nr , 2*g ) + F( nr , wk , 2*g + 1) );		
	}
	
	int Find( int p1, int k1 ){
		p = p1;
		k = k1+1;
		return F( 0, s/2, 1 );
	}
	
	int S( int wp, int wk, int g ){
		if( p >= wk || k <= wp )return 0;
		if( p <= wp && k >= wk )return sum[g];	
		return (wp == wk-1) ? el[g] : ( S( wp , nr , 2*g ) + S( nr , wk , 2*g + 1) + el[g]*( min(k,wk) - max(p,wp)  ) );		
	}
	
	int FindSum( int p1, int k1 ){
		p = p1;
		k = k1+1;
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
		p = p1;
		k = k1+1;
		return minstats( 0,s/2,1 );
	}
	
};


int main(){
	
	VI ans;
	//	ifstream strin("przykladowe_iny.txt");
		
		scanf( "%d",&N );
	//	strin >> N;
		
		CoverITree tree( ceil( log2(N+2) ) );
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
				tree.Add( i,i,1 ); // ustawiamy, ze wartosc el[s+i] = 1, tzn ze arr[i] jest zaznaczone
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
				ans.PB( tree.FindSum( queries[i].ST.ST, queries[i].ST.ND ) );
				i++;
			}
			
		//	printf( "i = %d\n",i );
			if(i >= d ) break;
			
			e = queries[i].ST.ST;			
		//	printf( "i = %d  t = %d  e = %d\n",i,t,e );
			
			while( t < e ){
				if( marked[t] == true && next[t] > t ){
					tree.Add(t,t,-1);
					marked[t] = false;
					marked[ next[t] ] = true;
					if( next[t] >= e ){
						tree.Add( next[t], next[t],1 );
					//	printf( "Dodaje do tree element %d\n",next[t] );
					}	
				}
				else if( marked[t] == true ){
					marked[t] = false;
					tree.Add( t,t,-1 );
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








