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
typedef vector< PDD > VPDD;
typedef vector<bool> VB;
typedef long long LL;
typedef vector<unsigned int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;

VI PrimeList( int n ){
	//cout << "Tworze liste liczb pierwszych" << endl;
	VI w(1,2);
	int s = 0, i = 2;
	FOR( l,3,n ){
		i = 0;
		while( w[s]*w[s] <= (unsigned int) l ) s++;
		while( i < s && l%w[i] ) i++;
		
	//	if( l*(l-1) > n ) break;
		if( i == s ) w.PB(l);
	}
	//cout << "\tStworzylem liste liczb pierwszych" << endl;
	return w;
}
	
VI primes;
	

// Test pierwszosci Milerem - Rabinem w czsie logarytmicznym
// funkcja przeprowadza test Millera-Rabina dla liczby x przy podstawie n
bool PWit( LL x, LL n ){
	if( x >= n ) return 0;
	LL d = 1, y;
	int t = 0, l = n-1;
	while( !( l & 1 ) ){
		++t;
		l >>= 1;
	}
	for( ; l>0 || t--; l>>=1 ){
		if( l & 1 ) d = (d*x)%n;
		if( !l ){
			x = d;
			l = -1;
		}
		y = (x*x)%n;
		// jesli test millera wykryl, ze licza nie jest pierwsza to zwroc prawde
		if( y == 1 && x != 1 && x != n-1 ) return 1;
		x = y;
	}
	
	return x != 1;
}

// funkcja sprawdza, czy dana liczba jest pierwsza. w tym celu wykonuje test millera-rabina przy podstawie 2,3,5,7
// dziala dla zakresu  do okolo 2 000 000 000
bool IsPrimeMR( LL x ){
	return !( x < 2 || PWit(2,x) || PWit(3,x) || PWit(5,x) || PWit(7,x) );
}	


void writeT( VLL & V ){
	REP(i,SIZE(V)){
		printf("%lld ",V[i]);
	}
	printf("\n");
}
	
void writeM( map<unsigned int,unsigned int> & M ){
	FOREACH(it,M) printf( "%d -> %d\n",it->ST, it->ND );	
} 

void solve(unsigned int N){
	//primes = PrimeList( N );
	//writeT(primes);
	
	//VI V,temp;
	
//	V.PB(N);
	int Q = 1;
	
	map<unsigned int, unsigned int> mapV, maptemp;
	mapV[N] = 1;
	map<unsigned int, unsigned int>::iterator it, itv;
	
	
	REP(i,SIZE(primes)){
		if( primes[i] * (primes[i]-1) > N ){
			Q = i;
			break;
		}
	}
	
	//printf("Q = %d\n",Q);
	
	REP(i,Q){
		maptemp.clear();
	//	printf("i = %d   primes[%d] = %d\n",i,i,primes[i]);
		
		//printf("\nV:\t");
		//writeT(V);
		
		for( itv = mapV.begin(); itv != mapV.end(); itv++ ){
			if( (itv->ST) % (primes[i]-1) == 0 ){
				//temp.PB( V[k] / ( primes[i]-1 ) );
				maptemp[ (itv->ST) / ( primes[i]-1 ) ]+= itv->ND;
			}
		}
		
		//printf( "Dodalem co trzeba modulo (primes-1)\n"); 
		
		//printf("temp:\t");
		//writeT(temp);
		
		/*REP(k,SIZE(temp)){
			if( temp[k] % primes[i] == 0 ) {
				temp.PB( temp[k] / primes[i] );
			}	
		}*/
		
		it = maptemp.end();
		do
		{
			if( maptemp.empty() ) break;
			it--;
		//	printf("petla do while, it->ST = %d    it->ND = %d\n",it->ST, it->ND);
			if( it->ST % primes[i] == 0 ) {
				maptemp[ it->ST / primes[i] ] += it->ND;				
			}
			
		} while( it != maptemp.begin() );
		
		//printf("temp:\t");
		//writeT(temp);
		
		/*REP(k,SIZE(temp)){
			V.PB( temp[k] );
		}*/
		
	//	printf("\nmaptemp:\n");
	//	writeM(maptemp);
	//	printf("\tmaqpv:\n");
	//	writeM(mapV);
	//	
	//	for( it = maptemp.begin(); it != maptemp.end(); it++ );
		for( it = maptemp.begin(); it != maptemp.end(); it++ ){
		//	printf("union maptemp i mapV, it->ST = %d\n", it->ST);
			mapV[ it->ST ] += it->ND;
		//	printf( "dodalem %d do mapV\n",it->ST );		
		}
		
				
	}
	
	int res = 0;
	
	//writeT(V);
	
	/*REP(i,SIZE(V)){
		if( (LL)(V[i]+1)*V[i] > N && IsPrimeMR( V[i]+1 )  ) res++;
		else if( V[i] == 1 ) res++;
	}*/
	
	//printf("mapa mapV\n");
	//writeM(mapV);
	//printf( "teraz zapisze wynik\n" );
	
	for( itv = mapV.begin(); itv != mapV.end(); itv++ ){
		if( (LL)(itv->ST) * ( itv->ST + 1 ) > N && IsPrimeMR( itv->ST + 1 ) ) res += itv->ND;
		else if( itv->ST == 1 ) res += itv->ND;
		
	}
	
	printf("%d\n",res);
	
	
}

int main(){
	primes = PrimeList( 1 << 20 );
	
	/*for(int i=1; i<=50; i++){
		if( i > 1 && i&1 ) continue;
		printf("i = %d  ",i);
		solve(i);
		//printf("\n");
	}*/
	
	
	int l_zest;
	scanf("%d",&l_zest);
	unsigned int N;
	
	
	
	while(l_zest--){
		
		scanf("%u",&N);
		
		solve(N);
		
		
		
	}
	
	

	return 0;
}






