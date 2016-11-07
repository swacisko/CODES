#include<cstdio>
//#include<iostream>
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
typedef vector< PDD > VPDD;
typedef vector<bool> VB;
typedef long long LL;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;

double getArea( VPDD & V ){
	double res = 0;
	int g = 0;
	REP(i,SIZE(V)){
		g = (i+1)%SIZE(V);
		res += V[i].ST * V[g].ND - V[g].ST * V[i].ND;		
	}
	return abs(res)/2;
	
}

double getDistance( PDD p, PDD q ){
	double x = p.ST - q.ST, y = p.ND - q.ND;
	
	return sqrt( x*x + y*y );	
}

double getCircumference( VPDD & V ){
	double res = 0;
	
	REP(i,SIZE(V)){
		res += getDistance( V[i], V[ (i+1)%SIZE(V) ] );		
	}
	return res;	
}


int main(){
	//ios_base::sync_with_stdio(0);
	int l_zest;
	//cin >> l_zest;
	
	//cout << fixed;
	//cout.precision(5);
	scanf("%d",&l_zest);
	
	int N,K;
	
	
	const double PI = 3.141592653589;
	
	while(l_zest--){
	//	cin >> N >> K;
	scanf("%d %d",&N,&K);
		
		VPDD V(N);
		REP(i,N){
			//cin >> V[i].ST >> V[i].ND;
			scanf("%lf %lf",&V[i].ST, &V[i].ND);	
		}
		
		double area = getArea(V);
		double circ = getCircumference(V);
		
		double res = area + circ*K + PI*K*K;
		
		//cout << "area = " << area << "   circumference = " << circ << "   res = " << res << endl;
		
		//cout << res << endl;
		printf("%.6lf\n",res);
		
	}

	

	return 0;
}


/*


3
3 2
0 0
0 5
5 0

4 0
-1000 -1000
1000 -1000
1000 1000
-1000 1000

4 1
-1000 -1000
1000 -1000
1000 1000
-1000 1000







 

*/







