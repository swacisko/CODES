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
const int INF = 1000000000;
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
typedef vector< VB > VVB;

VVI V;
VVI dst;

int N,a,b,E;

void clearAll(){

}

void initializeAll(){
    dst = VVI(N,VI(N,-INF));
}

void readData(){
    cin >> N >> E;
    V = VVI(N);
    REP(i,E){
        cin >> a >> b;
        V[a].PB(b); // UWAGA, TUTAJ MUSI BYC TAK DODAWANE!! TO JEST BLAD W PRZYKLADACH Z ZADANIA
        V[b].PB(a);
    }
}

void BFS( int beg ){
    int ile = 0;
    VI neigh(1,beg);
    dst[beg][beg] = 0;
    REP(i,SIZE(neigh)){
        if( ile++ > N+10 ){
            while(true);
        }

        a = neigh[i];
        REP( k, SIZE(V[a]) ){ // for each neighbour of a
            b = V[a][k];
            if( dst[beg][b] == -INF ){
                dst[ beg ][b] = dst[beg][a] + 1;
                neigh.PB(b);
            }
        }
    }
}

// two vertices in the distance graph are connected if and only if there is a shortest path of odd length between them
VVI getDistanceGraph(){
    VVI G(N);
    REP(i,N){
        REP( k,N ){
            if( dst[i][k] & 1 ) G[i].PB(k);
        }
    }
    return G;
}

bool hasTriangle( VVI & graph ){
    VVB adjacency(N,VB(N,false));

    REP(i,N) REP( k,SIZE(graph[i]) ) adjacency[ i ][ graph[i][k] ] = adjacency[ graph[i][k] ][i] = true;

    REP(i,N){
        REP( k, SIZE(graph[i]) ){
            a = graph[i][k];
            FOR(j,k+1, SIZE(graph[i])-1 ){
                b = graph[i][j];
                if( adjacency[a][b] ) return true;
            }
        }
    }

    return false;
}


//main idea of the algorithms is following:
// if there exist three vertices a,b,c, such that the shortest paths between all three pairs among them are of odd length, the answer is NO
// else the answer is YES
void solve(){
    clearAll();
    readData();
    initializeAll();

    REP(i,N) BFS(i); // i complete an array of distances between all vertices
   // cout << "Tablica odleglosci:" << endl;
  //  WRITE_ALL(dst);


    VVI G = getDistanceGraph(); // i create distance graph
  //  cout << "Distance graph:" << endl;
  //  WRITE_ALL(G);

    if( hasTriangle( G ) ){
        cout << "NIE" << endl;
    }
    else cout << "TAK" << endl;


}

int main(){
	ios_base::sync_with_stdio(0);
	//cout << fixed;
	//cout.precision(2);


    solve();


	return 0;
}












