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
#define FORD( x,y,z ) for( int x=y; (x)>=(z); x-- )
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
#define WRP(p) p.ST << " " << p.ND
#define CLEAR( dst,quant ) memset( dst,0, (quant)*sizeof( __typeof(*dst) ) );

const int INF = 1000000001;
int N,M,K,a,b,c,y,t,w,l_zest;
const long double EPS = 1e-11;
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


int CEIL;
VI ile1,ile2,V;

bool fulfills( int p, int k, CoverITree & tree_1, CoverITree & tree_2, CoverITree &treeRev_1, CoverITree & treeRev_2 ){
//	cout << "Jestem w fulfills, gdzie p = " << p << "  k = " << k << endl;
	if( !(p&1) ){
		PII p1 = tree_1.getMinStat( p+1,k+1 );
		int val = p1.ST;
		if( p > 0 ) val -= ile1[p-1];
		val += p/2;
	//	cout << "val1 = " << val << endl;
		if( val < 0 ) return false;
		
		p = N - p - 1;
		k = N - k - 1;
		if( !(k&1) ){
			p1 = treeRev_1.getMinStat( k+1,p+1 );
			val = p1.ST;
			if( k > 1 ) val -= ile2[k-1];
			val += k/2 + 1;
		//	cout << "valRev1 = " << val << endl;
			if( val < 0 ) return false;
		}
		else{
			p1 = treeRev_2.getMinStat( k+1,p+1 );
			val = p1.ST;
			if( k > 0 ) val -= ile2[k-1];
			val += (k+1)/2 + 1;
		//	cout << "valRev2 = " << val << endl;
			if( val < 0 ) return false;
		}		
	}
	else{
		PII p1 = tree_2.getMinStat( p+1,k+1 );
		int val = p1.ST;
		if( p > 0 ) val -= ile1[p-1];
		val += (p+1)/2;
	//	cout << "val2 = " << val << endl;
		if( val < 0 ) return false;
		
		p = N - p - 1;
		k = N - k - 1;
		if( !(k&1) ){
			p1 = treeRev_1.getMinStat( k+1,p+1 );
			val = p1.ST;
			if( k > 0 ) val -= ile2[k-1];
			val += k/2;
		//	cout << "valRev3 = " << val << endl;
			if( val < 0 ) return false;
		}
		else{
			p1 = treeRev_2.getMinStat( k+1,p+1 );
			val = p1.ST;
			if( k > 0 ) val -= ile2[k-1];
			val += (k+1)/2;
		//	cout << "valRev4 = " << val << endl;
			if( val < 0 ) return false;
		}	
	}
	return true;
}

int main(){
	
	cin >> N;
	
	ile1 = VI(N,0);
	ile2 = VI(N,0);
	CEIL = (int) ceil( log2(N+1) + 0.01 );
	CoverITree tree_1(CEIL);
	CoverITree tree_2(CEIL);
	CoverITree treeRev_1(CEIL);
	CoverITree treeRev_2(CEIL);
	
	char c;
	REP(i,N){
		cin >> c;
		if( c == 'p' ) V.PB(1);
		else V.PB(0);
	}
	
//	cout << "N = " << N << "   CEIL = " << CEIL << "   tree.s = " << tree_1.s << endl;
//	cout << "V:      "; WRITE(V); cout << endl;
	
	REP(i,N) if( V[i] ) ile1[i] = ile1[ i>0?i-1:0 ]+1;
			else ile1[i] = ile1[ i>0?i-1:0 ];
	for(int i=1; i<=N; i+=2) tree_1.Add( i,N,-1 );
	for( int i=1; i<=N; i+=2 ) tree_2.Add(i+1,N,-1);
	REP(i,N) if( V[i] ){
		tree_1.Add(i+1,N,1);
		tree_2.Add(i+1,N,1);
	}
	
//	cout << "ile1:   "; WRITE(ile1); cout << endl;
//	cout << "tree_1:  "; FOR(i,1,N) cout << tree_1.getMinStat(i,i).ST << " "; cout << endl;
//	cout << "tree_2:  "; FOR(i,1,N) cout << tree_2.getMinStat(i,i).ST << " "; cout << endl;
	
	reverse( ALL(V) );
	REP( i,N ) if( V[i] ) ile2[i] = ile2[ i>0?i-1:0 ] + 1;
				else ile2[i] = ile2[ i>0?i-1:0 ];
	for(int i=1; i<=N; i+=2) treeRev_1.Add( i,N,-1 );
	for(int i=1; i<=N; i+=2) treeRev_2.Add( i+1,N,-1 );
	REP(i,N) if( V[i] ){
		treeRev_1.Add(i+1,N,1);
		treeRev_2.Add(i+1,N,1);
	}
	
	reverse( ALL(V) );
	
//	cout << "ile2:   "; WRITE(ile2); cout << endl;	
//	cout << "treeRev_1:  "; FOR(i,1,N) cout << treeRev_1.getMinStat(i,i).ST << " "; cout << endl;
//	cout << "treeRev_2:  "; FOR(i,1,N) cout << treeRev_2.getMinStat(i,i).ST << " "; cout << endl;
	
	int MAX = 0;
	int p = 0, k = 0;
	while( k < SIZE(V) ){
		if( fulfills(p,k, tree_1, tree_2, treeRev_1, treeRev_2 ) ){
			MAX = max( MAX, k-p+1 );
			k++;
		}
		else p++;
		if( p > k ) k = p;		
	}
	
	cout << MAX << endl;
	return 0;
	
}


























