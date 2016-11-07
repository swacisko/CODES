//#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
//#include<map>
//#include<complex>
//#include<stack>
//#include<list>
//#include<bitset>
//#include<set>
//#include<iterator>
//#include<cmath>
//#include<queue>
//#include<time.h>
//#include<string.h>
//#include<fstream>
//#include<sstream>
#include<algorithm>
//#include<conio.h>
//#include<iomanip>

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
typedef vector<string> VS;
typedef vector< VS > VVS;
typedef vector< VPII > VVPII;

int N,M;
PII obj[1005]; // obj[i].ST - weight of i-th object,   obj[i].ND = value of i-th object...
int lastweight[1005];
int lastval[1005];

int sack[8005];

int ANS; // result;


// updates current state of knapsack with object indexed nr
void updateKnapsack( int nr ){
    int w = obj[nr].ST;
    int v = obj[nr].ND;

    FORD(i,M,0){
        if( sack[i] != -INF ){
            if( i + w <= M ){
                if( sack[i+w] < sack[i] + v ) sack[i+w] = sack[i] + v;
            }
        }
    }
    return;

}




void check( int nr ){
    int a = max( 0, M+1-lastweight[nr] );
    int b = M - lastweight[nr+1];
  //  cout << "I am in check, a = " << a << "   b = " << b << endl;

 //   if( a > b ) return;

    int mx = -INF;
    FOR(i,a,b){
        if( sack[i] > mx ) mx = sack[i];
    }

  //  cout << "mx = " << mx << endl;
   // ANS = max( ANS, max( lastval[nr+1], mx + lastval[nr+1] )  );
   if( mx != -INF ) ANS = max( ANS, mx + lastval[nr+1] );

}

void checkAll(){
    int mass = 0;
    FOR(i,1,N) mass += obj[i].ST;

    if( mass <= M ){
        int val = 0;
        FOR(i,1,N) val += obj[i].ND;
        ANS = val;

   //     cout << "In  checkAll  ANS = " << ANS << endl;
    }

}


void writeObjects(){
    cout << "Objects" << endl;
    FOR( i,1,N ) cout << WRP(obj[i]) << endl;
}

void writeKnapsack(){
    cout << "Knapsack" << endl;
    FOR(i,1,M) cout << i << " -> " << sack[i] << endl;
}

void writeLasts(){
    cout << "Lastweight" << endl;
    FOR(i,1,N) cout << i << " -> " << lastweight[i] << endl;

    cout << endl << "Lastval" << endl;
    FOR(i,1,N) cout << i << " -> " << lastval[i] << endl;
}

int main(){
	ios_base::sync_with_stdio(0);


	int l_zest;
	cin >> l_zest;
	while( l_zest-- ){
        ANS = -INF;
        cin >> N >> M;

        REP(i,M+2) sack[i] = -INF;
        sack[0] = 0;

        REP(i,N+3) lastweight[i] = lastval[i] = 0;

        FOR(i,1,N){
            cin >> obj[i].ST >> obj[i].ND;
        }

        sort( obj+1, obj+N+1 );
        reverse( obj+1, obj+N+1 );
        obj[N+1].ST = obj[N+1].ND = 0;

        FORD(i,N,1){
            lastweight[i] = lastweight[i+1] + obj[i].ST;
            lastval[i] = lastval[i+1] + obj[i].ND;
        }

        checkAll();



     //   writeObjects();
     //   writeLasts();

        // here lies the core of the algorithm...
        // in following iterations, i check what is the possible maximum value of a package, where i-th element is the last NOT TAKEN from all objects
        // it is maximum form objects indexed 1 to (i-1)   on a certain range of weights plus sum of all values of objects indexed (i+1) to N

        FOR(i,1,N){
         //   cout << "I START CONSIDERING " << i << "-th OBJECT" << endl;
            check(i);
            updateKnapsack(i);

        //    cout << "ANS = " << ANS << endl;
         //   cout << "Current sack state is:" << endl;
         //   writeKnapsack();

         //   ENDL(1);
        }


        cout << ANS << endl;

     //   ENDL(3);
	}

	return 0;
}












