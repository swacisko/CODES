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



struct CoverITree{
	// UWAGA, liczbiue calkowitej a odpowiada przedzial [a-1,a]
	#define nr ( wp + wk + 1 ) >> 1
	int *el,s,p,k,il;
	PII *minstat;
	CoverITree( int size ){ 
		el = new int[ s = 1 << (size+1) ];
		minstat = new PII[s];
		REP(x,s) el[x] = 0;
		FOR(x,s/2,s-1){
		//	minstat[x].ST = -( (x+1)/2 - s/2 );
		    minstat[x].ST = 0;
			minstat[x].ND = x - s/2 + 1; // tu mozna dodac 1 aby indeksowanie bylo od 1 a nie od zera, w funkcjach to nie bedzie mialo zadnego wplywu
		}
		FORD( x,s/2-1,1 ){ // liniowo ide od tylu drzewa i przypisuje indexy			
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
		delete[] minstat;
	}
	
	void Mark( int wp, int wk, int g ){
		ILE++;
		if( k <= wp || p >= wk ) return;		
		if( p <= wp && k >= wk ) el[g] += il;
		else{
			Mark( wp, nr, 2*g );
			Mark( nr,wk,2*g+1 );
		}	
		
		if( 2*g < s ){ // to jest czesc do wyznaczania minimalnego elementu w drzewie
			int M = ( minstat[2*g].ST <= minstat[2*g+1].ST ? 2*g : 2*g+1 );
			minstat[g].ST = minstat[M].ST + el[g];
			minstat[g].ND = minstat[M].ND;			
		}
		else minstat[g].ST += il; // jesli jest lisciem to wystarczy, ze dodam do niego wartosc nowego pokrywajacego go przedzialu
	}
	
	void Add( int p1, int k1, int i1 ){
		p = p1-1;
		k = k1;
		il = i1;
		ILE = 0;
		Mark( 0, s/2,1 );
	}		
	
	PII minstats( int wp, int wk, int g ){
		ILE++;
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
		ILE = 0;
		return minstats( 0,s/2,1 );
	}
	int ILE;
};

bool *buf;
char strin[30001];


int main(){
//	ios_base::sync_with_stdio(0);
	int zeroes = 0;
	int ones = 0;
	l_zest = 0;
	while( l_zest++ < 10 ){
		//cin >> N;
		scanf("%d",&N);
		
		buf = new bool[N+1];
		REP(i,N+1) buf[i] = false;
		zeroes = ones = 0;
		CoverITree tree( ( ceil( log2(N) ) + 0.1 ) );
		for( int i=1; i<=N; i+=2 ) tree.Add( i,N,-1 );
		
		
		scanf("%s",strin);
		for( int i=0; strin[i];i++ ){
		//	cin >> c;
		//	scanf("%c",&c);
			c = strin[i];
			if( c == '(' ){
				tree.Add( i+1,N,1 );
				zeroes++;
				buf[i+1] = 0;
			}
			else{
				ones++;
				buf[i+1] = 1;
			}
		}
		
		
	//	cin >> M;
		scanf("%d",&M);
	//	cout << "Test " << l_zest << ":" << endl;
		printf( "Test %d:\n",l_zest );
		REP( i,M ){
		//	cin >> a;
			scanf("%d",&a);
			
			if( a == 0 ){
			//	FOR(k,1,tree.s-1) cout << "minstat["<<k<<"] = " << tree.minstat[k].ST << "  " << tree.minstat[k].ND << endl;				
			//	cout << endl << "zeroes = " << zeroes << "   ones = " << ones << "   Wartosc minstat z calego drzewa to:" << tree.getMinStat( 1,N ).ST << "  " << tree.getMinStat(1,N).ND << endl;
			
				if( zeroes != ones ) printf("NO\n"); // cout << "NO" << endl;
				else if( tree.getMinStat(1,N).ST < 0 ) printf("NO\n"); // cout << "NO" << endl;
				else printf("YES\n"); //cout << "YES" << endl;
			//	cout << " jesli zeroes != ones to:   Funkcje minstat wywolana przez getMinStat wywolano lacznie " << tree.ILE << "  razy w jednym wywolaniu" << endl;
				continue;
			}
			if( buf[a] == 1 ){
				tree.Add( a,N,1 );
				zeroes++;
				ones--;
			}
			else{
				tree.Add( a,N,-1 );
				zeroes--;
				ones++;
			}
		//	cout << "Funkcje Mark wywolano lacznie " << tree.ILE << "  razy w jednym wywolaniu funkcji Add" << endl;
			buf[a] = !buf[a];
		}
		
		
		delete[]buf;
	}
	
}















