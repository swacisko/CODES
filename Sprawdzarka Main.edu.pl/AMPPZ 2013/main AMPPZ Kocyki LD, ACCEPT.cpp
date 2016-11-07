#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<cmath>
#include<queue>
#include<string.h>
#include<sstream>
#include<algorithm>

using namespace std;

#define REP( x,y ) for( long long x=0; x<(y); x++ )
#define FORD( x,y,z ) for( long long x=y; x>=(z); x-- )
#define FOR(x,b,e) for( long long x = b; x <= (e); ++x )
#define SIZE(v) (long long)v.size()
#define PB push_back
#define PH push_heap
#define POP pop_back
#define MP make_pair
#define ST first
#define ND second

long long N,M,K,a,b,c,y,t,w,l_zest;
const long long INF = 1000000001;
typedef vector<long double> VD;
typedef pair<long double,long long> PDI;
typedef pair<long double, long double> PDD;
typedef vector<long long> VI;
typedef vector< VI > VVI;
typedef pair<long long,long long> PII;
typedef map< PII, bool > MPIIB;
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef long double LD;

struct CoverITree{
	// UWAGA, liczbiue calkowitej a odpowiada przedzial [a-1,a]
	#define nr ( wp + wk + 1 ) >> 1
	LL *el, *sum,s,p,k,il;
	LL *sqr;
	CoverITree( LL size ){ 
		el = new LL[ s = 1 << (size+1) ];  
	//	ma = new int[s];
		sqr = new LL[s];
		sum = new LL[s];
		REP(x,s) el[x]  = sum[x] = sqr[x] = 0;
	}
	
	~CoverITree(){
		delete[] el;
	//	delete[] ma;
		delete[] sum;
		delete[] sqr;
	}
	
	void Mark( LL wp, LL wk, LL g ){
		if( k <= wp || p >= wk ) return;		
		if( p <= wp && k >= wk ){
			 el[g] += il;
			 sqr[g] += (LL)( 2*il*sum[g] + (wk-wp)*il*il );
		}
		else{
			Mark( wp, nr, 2*g );
			Mark( nr,wk,2*g+1 );
			
			LL su = (LL)(sum[2*g] + sum[2*g+1]);
			sqr[g] = (LL)(sqr[2*g] + sqr[2*g+1] );
			sqr[g] += (LL)( 2*el[g]*su + ( wk-wp )*el[g]*el[g] );
		}		
	//	ma[g] = el[g] > 0 ? wk - wp : ( wp == wk-1 ? 0 : ma[2*g] + ma[2*g + 1] );
		
		if( p <= wp && k >= wk ) sum[g] += il*(wk-wp); // to jest czesc do wyznaczania sum na danym przedziale
		else sum[g] += il*( min(k,wk) - max(p,wp) );
	}
	
	void Add( LL p1, LL k1, LL i1 ){
		p = p1-1;
		k = k1;
		il = i1;
		Mark( 0, s/2,1 );
	}
	
	LL S( LL wp, LL wk, LL g ){
		if( p >= wk || k <= wp )return 0;
		if( p <= wp && k >= wk )return sum[g];	
		return (wp == wk-1) ? el[g] : ( S( wp , nr , 2*g ) + S( nr , wk , 2*g + 1) + el[g]*( min(k,wk) - max(p,wp)  ) );		
	}
	
	LL FindSum( LL p1, LL k1 ){
		p = p1-1;
		k = k1;
		return S( 0,s/2,1 );
	}
	
	LL Squares( LL wp, LL wk, LL g, LL sumka ){
		if( k <= wp || p >= wk ) return 0;		
		if( p <= wp && k >= wk ){ // jesli pokrywa caly przedzial, to moge aktualizowac...
			LL sqre = sqr[g];
			sqre += 2*sum[g]*sumka + (wk-wp)*sumka*sumka;
			return sqre;		
		}
		
		return (wp==wk-1) ? sqr[g] : Squares(wp,nr,2*g,sumka+el[g]) + Squares(nr,wk,2*g+1,sumka+el[g]);
	}
	
	LL FindSquares( LL p1, LL k1 ){
		p = p1-1;
		k = k1;
		return Squares( 0,s/2,1,0 );
	}
	
};




#define KON false
#define POCZ true

vector< pair< pair<int,bool>,LL > > V;

const LL VAL = (LL)( ceil( log2(2000010) ) + 0.1 );
int main(){
	LL d;
//	scanf( "%d %d %d",&N,&a,&b );
	cin >> N >> a >> b;
	
	CoverITree tree( VAL );
	
	REP(i,N){
	//	scanf( "%d %d",&c,&d );
		cin >> c >> d;
		V.PB( MP( MP(c, POCZ),d  ) );
		V.PB( MP( MP(c+a,KON),d ) );
	}

	sort( V.begin(), V.end() );
	
	LL t = 0,y1,y2;
	LL x1;
	bool kran = false; // kraniec
	bool was = false;
	long double SUMA = 0;
	LL prev = V[0].ST.ST;
	
	long double N1 = N;
	long double N2 = ( N1 * ( N1 - 1 ) ) / 2;
	long double SUMA2 = 0;
	
	while( t < V.size() ){
		x1 = V[t].ST.ST;
		kran = V[t].ST.ND;		
		was = false;
		
		while( t < V.size() && V[t].ST.ST == x1 ){
			y1 = V[t].ND;
			y2 = V[t].ND+b;
			
			if( was == false ){ // jesli natrafimy na koniec to mozemy od razu dodac pole, pod warunkiem ze jeszcze go nie zliczalismy
				was = true;
				SUMA = (long double)( (long double)( tree.FindSquares(1,2000000) - (long double)tree.FindSum(1,2000000) ) / N1 / (N1-1) * (long double)( x1-prev ) );
				SUMA2 += SUMA;
			}
			
			if( V[t].ST.ND == KON ){
				was = true;
				tree.Add( y1+1,y2,-1 );
			}
			
			if( V[t].ST.ND == POCZ ){ // jesli jest poczatek, to tez musze doda, bo pozniej zgubie prev
				was = true;
				tree.Add( y1+1,y2,1 );
			}
			t++;
		}
		
		prev = x1;
	}
	
//	SUMA2 /= N1-1;
//	SUMA2 /= N1;
//	SUMA2 *= 2;
//	printf( "%.4lf\n",SUMA2 );
	cout << fixed;
	cout.precision(4);
	cout << SUMA2 << endl;
	
	return 0;	
}





















