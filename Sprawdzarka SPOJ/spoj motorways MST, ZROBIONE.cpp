#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<cmath>
#include<fstream>
#include<queue>
#include<string.h>
#include<sstream>
#include<algorithm>

using namespace std;

#define REP( x,y ) for( int x=0; x<(y); x++ )
#define FORD( x,y ) for( int x=(y); x>=0; x-- )
#define PB push_back
#define PH push_heap
#define POP pop_back
#define MP make_pair
#define ST first
#define ND second

int N,M,a,b,c,x,y;
double t1,t2,j;
const int INF = 100000000;
typedef vector<double> VD;
typedef pair<double,int> PDI;
typedef pair<double, double> PDD;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef map< PII, bool > MPIIB;

template<class typ> inline typ maximum( typ a, typ b ){ return a > b ? a : b; }
template<class typ> inline typ minimum( typ a, typ b ){ return a < b ? a : b; }


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

struct P5I{
	P5I( double w,int av1, int av2, double aa, double bb ) : a(aa),b(bb),v1(av1),v2(av2),waga(w){}
	double waga,a,b;
	int v1,v2;
	bool operator<( const P5I oth )const { return waga < oth.waga;	}
};

vector< P5I > V;


inline double getCost( double j ){
	double cost = 0;
	FAU fau(N);
	sort( V.begin(), V.end() );
	
	REP(i,M){
		V[i].waga = ( ( (double)V[i].a )*j + (double)V[i].b );
	}
	
	REP( i,V.size() ){
		if( fau.Find( V[i].v1 ) != fau.Find( V[i].v2 ) ){
			cost += V[i].waga;
			fau.Union( V[i].v1, V[i].v2 );
		}
	}
	
	return cost;
}


int main(){
//	ios_base::sync_with_stdio(0);
//	cout << fixed;
//	cout.precision( 3 );
	ofstream strout( "outy_motorways.txt" );
	strout.precision(3);
	strout << fixed;
	int l_zest;
	int v1,v2;
	scanf( "%d",&l_zest );
//	cin >> l_zest;	
	while(l_zest--){
		scanf( "%d %d %lf %lf",&N,&M,&t1,&t2 );
	//	cin >> N >> M >> t1 >> t2;
		V.clear();
		
		REP(i,M){
			scanf( "%d %d %d %d",&v1,&v2,&a,&b );	
		//	cin >> v1 >> v2 >> a >> b;		
			V.PB( P5I( 0,v1,v2,a,b ) );
		}
		
		j = (t1+t2)/2;
		double p = getCost(t1), q = getCost(t2),c = getCost( j );
	//	printf( "p = %lf  q = %lf\n",p,q );
		
		// ((t2-t1) > 0.001) ||  
		while( (abs(q-p) > 0.000001  ) && ( (t2-t1) > 0.000001 )  ){ // dopoki roznica kosztow jest wieksza od 10^-5
			j = ( t1+t2 )/2;
		//	p = getCost(t1), q = getCost(t2);			
			c = getCost( j );
		//	printf( "\nOto dane:  t1 = %lf, p = %lf, t2 = %lf, q = %lf, j = %lf, c = %lf \n",t1,p,t2,q,j,c );	
		
			if( getCost( j + 0.000001 ) <= getCost( j - 0.000001 )  ){
			//	printf("Jedynka\n");
				t2 = j;
				q = c;
			}
			else{
				t1 = j;
				p = c;
			}
		}
		
		
		
		printf( "%.3lf %.3lf\n", j,c );
		strout << j << " " << c << endl;
	//	cout << j << " " << c << endl;
		
		
	}
	
	
}






















