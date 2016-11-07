#include<cstdio>
//#include<iostream>
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
#define VAR(v,n) __typeof(n) v=(n)
#define FOREACH(i,c) for( VAR(i,c.begin());i!=c.end();++i )
#define PB push_back
#define MP make_pair
#define ST first
#define ND second
#define WRITE( V ){ FOREACH(it,V) cout << *it << ", "; cout << endl; }
#define WRITE_ALL(V) {  REP( i,SIZE(V) ){ cout  << i << " ---- ";  FOREACH(it,V[i]) cout << *it << ", "; cout << endl;     } }
#define WRP(p) p.ST << " " << p.ND
#define CLEAR( dst,quant ) memset( dst,0, (quant)*sizeof( __typeof(*dst) ) );
#define ENDL(x) REP(crow,(x)) cout << endl;

const bool show_help = 1;
const int INF = 1000000001;
//int N,M,K,a,b,c,y,t,w,l_zest;
const long double EPS = 1e-11;
typedef vector<double> VD;
typedef vector< VD > VVD;
typedef pair<double,int> PDI;
typedef pair<double, double> PDD;
typedef vector< PDD > VPDD;
typedef vector<bool> VB;
typedef vector< VB > VVB;
typedef unsigned long long LL;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;

#define Det(a,b,c) ((long double)(b.ST-a.ST)*(c.ND-a.ND)-(long double)(b.ND-a.ND)*(c.ST-a.ST))
const PDD ZERO(0,0);


int getQuarter( PII p ){
	if( p.ST >= 0 ){
		if( p.ND >= 0 ) return 1;
		else return 4;
	}
	else{ // p.ST < 0
		if( p.ND >= 0 ) return 2;
		else return 3; 
	}	
}
  
// return -1 if p is in quarter with lower number 1 if converse and 0 if they are in the same quarter
int compareQuarters( PII p, PII q ){
	int qp = getQuarter(p);
	int qq= getQuarter(q);
	
	if( qp < qq ) return -1;
	else if( qp > qq ) return 1;
	else return 0;	
}


bool angleSortComp( PII p, PII q ){
	int t = compareQuarters(p,q);
	
	if( t == -1 ) return true;
	else if(t == 1) return false;
	else{ // if theese points are int he same quarter
		double dp = (double) p.ND / ( p.ST + EPS );
		double dq = (double) q.ND / ( q.ST + EPS );
		return dp < dq;
	}	
}


// sorts given points with respect to angle around center point
void angleSort( VPII & points, PII center ){
	
	points.pop_back(); // to nie jest element sortowania katowego
	
	REP( i, SIZE(points) ){
		points[i].ST -= center.ST;
		points[i].ND -= center.ND;		
	}
		
	sort( ALL(points),angleSortComp );
}



VPII points;
int x,y, N;

bool equals( double d1, double d2 ){
	return abs(d1-d2) < EPS;
}


//return true if point lies on the closed semiplane determined by line  through points    (0,0) - beg
bool liesOnClosedSemiplane( PII beg, PII point ){
	return Det( ZERO,beg,point ) >= 0;	
}


void writePoints(){
	REP(i,SIZE(points)){
		printf( "%d %d\n", points[i].ST, points[i].ND );
	}
}

#define WAR if(false)

void solve(){
	
	if( SIZE(points) <= 3 ){
		printf("1\n");
		return;
	}
	
	int p = 0, q = 1;
	
	angleSort(points, points.back());
	
WAR	printf("Tutaj posortowane punkty\n");
WAR	writePoints();
	
	#define MOD % SIZE(points)
WAR	printf( "p = %d   P = (%d,%d)   q = %d   Q = (%d,%d)\n",p,points[p].ST, points[p].ND,q, points[q MOD].ST, points[q MOD].ND ); 
	
	
	while( q MOD != p MOD && liesOnClosedSemiplane( points[p MOD], points[ q MOD ] ) ){
		 q++;
	}
	
WAR	printf( "p = %d   P = (%d,%d)   q = %d   Q = (%d,%d)\n",p,points[p].ST, points[p].ND,q, points[q MOD].ST, points[q MOD].ND );  	
	//printf("Tam\n");
	
	int minans = INF;
	
	int CONTROL = 0;
	
	do{
				
WAR		printf( "\nNEW LOOP   p = %d   q = %d\n",p,q );
		minans = min( minans, SIZE(points) - q + p );
		
		PII nextp = points[ (p+1) MOD ];
		PII P = points[p MOD];
		
		CONTROL = p;
		while( p <= CONTROL + N-1 && P.ST * nextp.ST >= 0 && P.ND * nextp.ND >= 0 && Det(ZERO,P,nextp) == 0 ){
WAR			printf( "p = %d   P = (%d,%d)    nextp = (%d,%d)\n",p,P.ST, P.ND, nextp.ST, nextp.ND );  
			p++;
			nextp = points[ (p+1) MOD ];
			P = points[p MOD];
		}
		p++;
		
WAR		printf( "\tp = %d   P = (%d,%d)    q = %d  Q = (%d,%d)\n",p,P.ST, P.ND, q,points[q MOD].ST, points[q MOD].ND );  
		while( q MOD != p MOD && liesOnClosedSemiplane( points[p MOD], points[q MOD] ) ) q++;;
WAR		printf( "\t\tp = %d   P = (%d,%d)   q = %d   Q = (%d,%d)\n",p,P.ST, P.ND, q,points[q MOD].ST, points[q MOD].ND );   
		
	} while( points[p MOD] != points[0] );
	
	
	printf( "%d\n", 1+minans );
	
	
	
	
}



int main(){
	
	
	int l_zest;
	scanf("%d",&l_zest);
	
	while(l_zest--){
		
		scanf("%d",&N); 
		
		points = VPII(N);
		
		REP(i,N){
			scanf("%d %d",&x,&y);
			points[i] = MP(x,y);			
		}
		
		
		solve();
		
	}
	
	
	
	
	
	
	
	return 0;
}



/*

6
5
-3 -3
5 5
-3 3
3 3
0 0

5
-3 -3
3 -3
-3 3
3 3
0 0

10
2 1
2 -1
-1 2
-2 -1
-2 1
-1 -2
1 2
1 -2
-2 -4
0 0

1
0 0
5
0 0
2 0
2 2
0 2
1 1

4
1000000 1000000
2 2
1 1
0 0

ans
1
2
4
1
2
1


*/
