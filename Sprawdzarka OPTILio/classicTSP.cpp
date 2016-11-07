//#include<cstdio>
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
#include<time.h>
//#include<string.h>
//#include<fstream>
//#include<sstream>
#include<algorithm>
//#include<conio.h>

using namespace std;

#define REP( x,y ) for( int x=0; x<(y); ++x )
#define FORD( x,y,z ) for( int x=y; x>=(z); --x )
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



namespace TSP{	
	typedef double _T;
	typedef vector< _T > VT;
	typedef vector< VT > VVT;
	typedef pair<_T,_T> PTT;
	typedef vector< PTT > VPTT;
	
	
	int N;
	double perimeter;
	VI cities; // cities[i] is the i-th town number on the tour - if tour start with city i, then cities[i] = 0	
	VPTT D; // these are cities' coordinates
	VVI closest; // closest[i][k] is the k-th closest city to town i
	PTT sortmark;
	VVD dst;
	VI tour;
	
	double dist( PTT & p, PTT & q ){
		return sqrt( (p.ST-q.ST)*(p.ST-q.ST) + (p.ND-q.ND)*(p.ND-q.ND) );
	}
	
	double dist( int a, int b ){
		return dst[a][b];
	}
	
	void createDst(){
		dst = VVD(N,VD(N));
		REP(i,N){
			for( int k=i; k<N; k++ ){
				dst[i][k] = dst[k][i] = dist( D[i], D[k] );
			}
		}
	}
	
	// used to sort
	bool sortcomp( int p, int q ){
		return dist( sortmark, D[p] ) < dist( sortmark,D[q] );
	}
	
	VI getTour(){
		/*
		VI tour(N);
		REP(i,N) tour[ cities[i] ] = i;
		*/
		return tour;
	}
	
	double getPerimeter(){
		//VI tour = getTour();
		double res = 0;
		REP( i,N-1 ){
			res += dist( D[tour[i]], D[tour[i+1]] );
		}
		res += dist( D[ tour.back() ], D[0] );
		return res;
	}
	

	void createClosest(){
	//	cout << "getClosest()" << endl;
		
		VI clst(N);
		REP(i,N) clst[i] = i;
		
		closest = VVI(N);
		REP(i,N){
			sortmark = D[i];
			sort( ALL(clst), sortcomp );
			closest[i] = clst;
			
		//	REP(k,SIZE(clst)) cout << clst[k]+1 << " ";
		//	cout << endl;
		}
		
		/*cout << "closest:" << endl;
		REP(i,N){
			cout << "closest["<<i+1<<"]:\t";
			REP(k,N) cout << closest[i][k]+1 << " ";
			cout << endl;
		}
		cout << "\tout of getClosest()" << endl;*/
	}
	
	// creates nearest-neighbour tour
	// in cities will be the nearest-neighbour tour craeted by this function
	void createNNTour(){
		//cout << "createNNTour()" << endl;
		
		cities = VI(N);
		cities[0] = 0;
		VB was(N,false);
		was[0] = true;
		int a=0,b;
		FOR(i,1,N-1){
			FOR( k,1, N-1 ){
				b = closest[a][k];
				if( !was[b] ){
				//	cout << "b = " << b << "     ";
					cities[b] = i;
					was[b] = true;
					a = b;
					break;
				}
			}
		}
		
		tour = VI(N);
		REP( i,N ) tour[ cities[i] ] = i;
		
		perimeter = getPerimeter();	
		
		//cout << "\tout of createNNTour()" << endl;
	}
	
	VI getKClosest( int city, int K=12 ){
		VI res;
		//REP(i,min(K,N)) res.PB( closest[city][i] );
		res.insert( res.begin(), closest[city].begin(), closest[city].begin() + min(K,N) );
		return res;
	}
	
	VI getFragment( VI & tour, int a, int b ){
		VI res;
		if( a < b ) res.insert( res.begin(), tour.begin() + a, tour.begin() + b+1 );
		else{
			res.insert( res.begin(), tour.begin()+a, tour.end() );
			res.insert( res.end(), tour.begin(), tour.begin()+b+1 );
		}
		
		/*for( int i=a; i != (b+1)%N ; i = (i+1)%N ){
			res.PB( tour[i] );
		}*/
		return res;
	}
	
	
	bool checkTour( VI & tour ){
		VB was(N,false);
		REP(i,N){
			if( was[tour[i]] ) return false;
			was[ tour[i] ] = true;
		}
		return true;
	}
	
	double getDist( int citya, VI & frag, int cityz ){
		if( frag.empty() ) return dist( citya, cityz );
		double d = dist( citya, frag[0] );
		REP( i, SIZE(frag)-1 ) d += dist( frag[i], frag[i+1] );
		d += dist( frag.back(), cityz );
		return d;
	}
	
	void _pathKOpt( int city, int K ){
		//cout << "pathKOpt,  city = " << city+1 << "   K = " << K << endl;
		//cout << "tour:\t"; WRITE(tour);
		
		if( K > N-1 ) K = N-1;
		int a = cities[city];
		int A = a;
		
		//cout << "\ta = " << a << "   (a+K+1)%N = " << (a+K+1)%N  << endl;
		
		VI v;
		for( int i=(a+1)%N; i !=(a+K+1)%N; i=(i+1)%N ) v.PB( tour[i] );
			
		int z = tour[ (a+K+1)%N ];	
		a = tour[a];
		
		
		//cout << "\ta = " << a+1 << "  z = " << z+1 << "\tv:  "; WRITE(v);
		
		double d = getDist(a,v,z);
		perimeter -= d;
		sort( ALL(v) );
		VI best = v;
		double minres = INF;		
		
		do{
			d = getDist( a,v,z );
			if( d < minres ){
				minres = d;
				best = v;
			}			
		}while( next_permutation( ALL(v) ) );
		
		REP( i, SIZE(v) ){
			int t = (A+1+i)%N;
			tour[ t ] = best[i];
			cities[ tour[ t ] ]	= t;		
		}
		
		perimeter += minres;
		
	//	cout << "\tbest:  "; WRITE(best);
		//cout << "\t\ttour pod koniec pathKOpt:\t"; WRITE(tour);
				
	}
	
	
	// makes the 3-opt operation in the vicinity of city p
	// takes O(N) time to perform single 3-opt operation
	void _3opt( int city, int K ){
		
		VI v;
		//VI tour = getTour();
		//REP( i,N ) cities[ tour[i] ] = i;
		
				
		VI clst = getKClosest( city,K );
		
		set<int> forbiden;
		int a,b;
		double distdiff = 0;
		
		REP(i,3){
			do{
				a = clst[ rand()% SIZE(clst)  ];
				b = cities[a];
				b = tour[ (b+1)%N ];
			}while( forbiden.count(a) != 0 || forbiden.count(b) != 0 );
			v.PB(a);
			v.PB(b);
			
			
			forbiden.insert(a);
			forbiden.insert(b);
			distdiff += dist( D[a],D[b] );
		}
		
		a = 0;
		REP(i,N){
			for( int k=0; k<6; k+=2 ){
				if( tour[i] == v[k] ){
					swap( v[a], v[k] );
					++a;
					swap( v[a], v[k+1] );
					++a;					
				}
			}  
		}
		
		int c,d,e,f;
		a = v[0];
		b = v[1];
		c = v[2];
		d = v[3];
		e = v[4];
		f = v[5];
				
		perimeter -= distdiff;
		
		VI BC, DE, FA, X,Y,Z;
		BC = getFragment( tour,cities[b],cities[c] );
		DE = getFragment( tour, cities[d], cities[e]  );
		FA = getFragment( tour, cities[f], cities[a]  );
		
		X = BC;
		Y = DE;
		Z = FA;
		bool revX = false, revY = false;
		
		if( dist( a,b ) + dist( c,e ) + dist( d,f ) < distdiff ){ // abcedf
			X = BC;
			Y = DE;
			
			revY = true;
			revX = false;
			
			//reverse( ALL(Y) );
			distdiff = dist( a,b ) + dist( c,e ) + dist( d,f );
		//	cout << "1st" << endl;
		}		
		if( dist( a,c ) + dist(b,d) + dist(e,f) < distdiff ){ //acbdef
			X = BC;
			Y = DE;
			
			revX = true;
			revY = false;
			distdiff = dist( a,c ) + dist(b,d) + dist(e,f);
		}
		if (dist( a,c ) + dist(b,e) + dist( d,f ) < distdiff ){ //acbedf
			X = BC;
			Y = DE;
			
			revX = revY = true;
			
			distdiff = dist( a,c ) + dist(b,e) + dist(d,f );
		}
		if (dist( a,d ) + dist(e,c ) + dist( b,f ) < distdiff ){ //adecbf
			X = DE;
			Y = BC;
			revY = true;
			revX = false;
			distdiff = dist( a,d ) + dist( e,c ) + dist( b,f );
		}
		if (dist( a,d ) + dist( e,b ) + dist( c,f ) < distdiff ){ //adebcf
			X = DE;
			Y = BC;	
			revX = revY = false;
			distdiff = dist( a,d ) + dist( e,b ) + dist( c,f );
		}
		if (dist( a,e) + dist( d,b ) + dist( c,f ) < distdiff ){ //aedbcf
			X = DE;
			Y = BC;	
			revX = true;
			revY = false;
			distdiff = dist( a,e ) + dist( d,b ) + dist( c,f );
		}
		if (dist( a,e ) + dist( d,c ) + dist( b,f ) < distdiff ){ //aedcbf
			X = DE;
			Y = BC;	
			revX = revY = true;
			distdiff = dist( a,e ) + dist( d,c ) + dist( b,f );
		}
		
		perimeter += distdiff;
		
		if( revX ) reverse( ALL(X) );
		if( revY ) reverse( ALL(Y) );
		
		tour = X;
		tour.insert( tour.end(),ALL(Y) );
		tour.insert( tour.end(), ALL(Z) );
		
		
		REP( i,N ) cities[ tour[i] ] = i;
		//TSP::tour = tour;
		
	}
	
	
	
	
	VI TSP( VPTT & DD ){
		D = DD;
		N = SIZE(D);
				
		createDst();
		createClosest();
		createNNTour();
		
		REP(i,N) cities[tour[i]] = i;	
				
	//	cout << "At the beginning perimeter = " << perimeter << endl;
	//	cout << "Tour is in the form:   " << flush;		
	//	WRITE( tour );
		
		VI perm(N);
		REP(i,N) perm[i] = i;
		
		int repet = 100; // the more repetitons- the more 3-opt operations will be done, and hence, the greater chance, the tour will be shorter
		int A = 12;
		REP(i,repet){
			
			random_shuffle( ALL(perm) );
			REP( k,SIZE(perm) ){
				if( k < (N/3) ) _pathKOpt( perm[ (k+(N/2))%N ], 5 );			
				_3opt( perm[k],A );								
			}
			
			if( i%10 <= 1 ) A = 26;
			else A = 12;
			
			//REP(t,5) _pathKOpt( perm[ rand()%N ], 8 );
			
				//cout << "After another series of 3-opt, perimeter equals  --> " << perimeter << "  <--  Tour is in the form:   " << flush;
				//VI t = getTour();
				//WRITE( t );	
			
		}
		
	// cout << "At the end perimeter = " << perimeter << endl;
	// cout << "Tour is in the form:   " << flush;
	// WRITE( tour );
		
		return tour;
	}
	
	
}

void solve(){
	
	int N=0;
		
	vector< pair<double,double> > D(100000);
	
	double x,y;
	int id;
	
	bool waszero = false;
	while( cin >> id ){
		cin >> x >> y;
		
		//if( id > 10000 ) while(1);
		
		if( id == 0 ) waszero = true;
		D[id] = MP( x,y );
		N++;
	}
	
	if( waszero == false ) D.erase( D.begin() );
	else D.pop_back();
	
	D.resize(N);
	
	VI tour = TSP::TSP(D);
	/*VI tour(N);
	REP(i,N) tour[i] = i;
	random_shuffle( ALL(tour) );*/
	
	REP(i,SIZE(tour)){
		//printf("%d ", tour[i]+1);
		cout << tour[i]+1 << " ";
	}
	cout << endl;
	//printf("\n");
}



int main(){
	srand( unsigned(time(0)) );
	ios_base::sync_with_stdio(0);
	
	solve();




	return 0;
}


/*

8 17
0 0 1 2 3 4 5 6 7
5 5 1 2 3 4 5 6 7
-3 -3 1 2 3 4 5 6 7
-2 2 1 2 3 4 5 6 7
1 -1 1 2 3 4 5 6 7
3 -14 1 2 3 4 5 6 7
4 -15 1 2 3 4 5 6 7
-1 10 1 2 3 4 5 6 7











*/








