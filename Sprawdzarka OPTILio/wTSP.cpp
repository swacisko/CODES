#include<cstdio>
#include<iostream>
#include<vector>
#include<string>
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


struct FAU{
	int *p,*w;
	FAU( int n ) : p(new int[n]), w(new int[n]) {
		REP(x,n) p[x] = w[x] = -1;
	}
	~FAU(){
		delete[] p;
		delete[] w;
	}
	
	int Find( int x ){
		return ( p[x]<0 ) ? x : p[x] = Find( p[x] );
	}
	
	void Union( int x, int y ){
		if( (x = Find(x)) == (y = Find(y)) ) return;
		if( w[x] > w[y] ) p[y] = x;
		else p[x] = y;
		if( w[x] == w[y] ) w[y]++;
	}
	
};

typedef double wtype;
typedef vector<wtype> VWT;
typedef vector<VWT> VVWT; 


// przestrzen nazwa, w ktorej sa funkcje do tworzenia MST
namespace MST{
	
//	VVI V;
//	VVWT W; // wektorz przechowujacy wagi krawedzi    W[i][k] to waga krawedzi laczacej wierzcholek nr i z wierzcholkiem nr V[i][k]
	
	struct Edge{
		Edge( int a1, int b1, wtype w1 ) : a(a1), b(b1), w(w1){}
		int a,b;
		wtype w;
		bool operator<( const Edge & e1 )const{
			return w < e1.w;
		}
	};
	
	// funkcja przyjmuje jako parametr graf, a zwraca graf(minimalne drzewo rozpinajace) :)
	pair<VVI,VVWT> KruskalMst( VVI & V, VVWT & W ){
		VVI v(SIZE(V));
		VVWT w(SIZE(W));
		FAU fau(SIZE(V));
		vector<Edge> ed;
		REP(i,SIZE(V)) REP(k,SIZE(V[i])) ed.PB( Edge( i,V[i][k], W[i][k] ) );
		sort( ALL(ed) );
		int x,y;
		REP(i,SIZE(ed)){
			if( (x = fau.Find( ed[i].a ) ) != ( y = fau.Find( ed[i].b ) ) ){
				fau.Union( ed[i].a, ed[i].b );
				v[ed[i].a].PB(ed[i].b);
				v[ed[i].b].PB(ed[i].a);
				w[ed[i].a].PB(ed[i].w);
				w[ed[i].b].PB(ed[i].w);
			}
		}
		
		return MP( v,w );
	}

}





VPII D;
VVI V;
VVWT W;
double v;
int N;



double dist( int a, int b ){
	double d = D[a].ST - D[b].ST;
	double e = D[a].ND - D[b].ND;
	double f = d*d + e*e;
	return sqrt(f);	
}


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
	
	//points.pop_back(); // to nie jest element sortowania katowego
	
	REP( i, SIZE(points) ){
		points[i].ST -= center.ST;
		points[i].ND -= center.ND;		
	}
		
	sort( ALL(points),angleSortComp );
}

void write(VVI & T){
	REP(i,SIZE(T)){
		printf( "%d:\t",i );
		REP(k,SIZE(T[i])){
			printf( "%d ",T[i][k] );
		}
		printf("\n");
	}
}


void writeAnswerFromTree( VVI & V, int nr, int par ){
	//printf( "nr = %d    par = %d\n",nr,par );
	VI sons;
	REP( i, SIZE(V[nr]) ){
		if( V[nr][i] != par  ) sons.PB( V[nr][i] );  
	}
	
	VPII sonpoints;
	REP(i,SIZE(sons)) sonpoints.PB( D[sons[i]] );
	
	angleSort( sonpoints, D[nr] );
	
	reverse( ALL(sonpoints) );
	
	REP( i, SIZE(sonpoints) ){
		REP( k, SIZE(sons) ){
			if( sonpoints[i] == D[ sons[k] ] ){
				swap( sons[i], sons[k] );
				break;
			}
		}
	}
	
	//printf("sons\n");
	//WRITE(sons);
	
	
	/*int ind = 0;
	double M = (double)INF;
	int a = nr;
	while( SIZE(sons) > 0 ){
		M = (double)INF;
		ind = 0;
		REP( i, SIZE(sons) ){
			if( dist( a, sons[i] ) < M ){
				M = dist( a,sons[i] );
				ind = i;
			}
		}		
		writeAnswerFromTree( V, sons[ind],nr );		
		a = sons[ind];		
		swap( sons[ind], sons[ SIZE(sons)-1 ] );
		sons.pop_back();		
	}*/
	
	REP( i,SIZE(sons) ) writeAnswerFromTree( V, sons[i],nr );
	
	printf( "%d ",nr+1 );
	
}


void solve(){
	scanf( "%d %lf",&N,&v );
	
	V = VVI(N);
	W = VVWT(N);
	D = VPII(N);
	
	int x,y;
	
	REP(i,N){
		scanf( "%d %d",&x,&y );
		D[i] = MP( x,y );
		REP(k,7) scanf("%d",&x);		
	}
	
	REP(i,N){
		REP(k,N){
			if( i != k ){
				V[i].PB(k);
				W[i].PB( dist( i,k ) );						
			}
		}
	}
	
	VVI T = MST::KruskalMst( V,W ).ST;
		
//	write(T);
	//printf("\n\n");
		
	writeAnswerFromTree(T,0,0);	
	
}



int main(){
	
	
	solve();




	return 0;
}


/*

6 17
0 0 1 2 3 4 5 6 7
5 5 1 2 3 4 5 6 7
-3 -3 1 2 3 4 5 6 7
-2 2 1 2 3 4 5 6 7
1 -1 1 2 3 4 5 6 7
3 -14 1 2 3 4 5 6 7












*/








