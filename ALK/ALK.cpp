//#include<stdio.h>
#include<iostream>
#include<vector>
//#include<string>
//#include<map>
//#include<complex>
//#include<stack>
//#include<list>
//#include<bitset>
//#include<set>
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
#define WRITE_ALL(V,s,t) { cout << s << endl;  REP( i,SIZE(V) ){ cout  << i+1 << " ---- ";  FOREACH(it,V[i]) cout << *it+t << ", "; cout << endl;     } }
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
typedef long long LL;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;


void zad1( int N, int K){
	VI V(K);
	REP(i,K) V[i] = 1;
	
	int ind = K-1;
	while( ind >=0 ){
		WRITE(V);
		ENDL(1);
		
		ind = K-1;
		if( ind == K ) ind--;		
		while( ind >= 0 && V[ind] == N ) V[ind--] = 1;
		if( ind >= 0 ) V[ind]++;			
	}	
}


void zad2( VI & V, VI & tab, int dl, int ind, int K ){
	if( dl == K ){
		WRITE(tab);
		return;
	}
	
	FOR(i,ind,SIZE(V)-1){
		tab[dl] = V[i];
		zad2( V,tab,dl+1,i+1,K ); 
	}
		
}


void zad3( int N, int K){
	VI V(K+1);
	REP(i,K+1) V[i] = 1;
	
	int ind = K-1;
	while( ind > 0 ){
		FOR(i,1,SIZE(V)-1) cout << V[i] << " ";
		cout << endl;
		
		ind = K;		
		while( ind > 0 && V[ind] == ind ) V[ind--] = 1;
		if( ind > 0 ) V[ind]++;			
	}	
}


void wypisz( VB & v ){
	FOR(i,1,SIZE(v)-1){
		if( v[i] ) cout << i << " ";
	}
	ENDL(1);
}


void zad4( int N ){	
	VB v(N+1,false);
		
	int ind = N;
	while( ind > 0 ){
		wypisz(v);
		ENDL(1);
		
		ind = N;
		if( ind == N ) ind--;		
		while( ind > 0 && v[ind] == true ) v[ind--] = false;
		if( ind > 0 ) v[ind] = !v[ind];	
	}
	
}





int main(){
	ios_base::sync_with_stdio(0);
//	cout << fixed;
//	cout.precision(2);
	
	int N,K;
	cin >> N >> K;
	zad1(N,K);
	
	
	
	VI V(N);
	REP(i,N) V[i] = i+1;
	VI tab(K);
	zad2( V,tab,0,0,K );
	
	zad3( N,K );
	
	
	zad4(N);
	
	return 0;
}












