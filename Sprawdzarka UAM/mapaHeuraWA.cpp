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
typedef vector< VB > VVB;

VVI V;
VVI dst;

int N,a,b,E;

void clearAll(){

}

void initializeAll(){
    dst = VVI(N+1,VI(N+1,-INF));
}

void readData(){
    cin >> N >> E;
    V = VVI(N+1);
    REP(i,E){
        cin >> a >> b;
        //V[a-1].PB(b-1);
        //V[b-1].PB(a-1);
        V[a].PB(b);
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
    VVI G(N+1);
    FOR(i,1,N){
        FOR( k,1,N ){
            if( dst[i][k] & 1 ) G[i].PB(k);
        }
    }
    return G;
}

bool hasTriangle( VVI & graph ){
    VVB adjacency(N+1,VB(N+1,false));

 //   WRITE_ALL(graph);

    REP(i,N+1) REP( k,SIZE(graph[i]) ) adjacency[ i ][ graph[i][k] ] = adjacency[ graph[i][k] ][i] = true;

  //  WRITE_ALL(adjacency);

    REP(i,N+1){
        REP( k, SIZE(graph[i]) ){
            a = graph[i][k];
           // FOR(j,k+1, SIZE(graph[i])-1 ){
            REP( j,SIZE(graph[i]) ){
                b = graph[i][j];
                if( i != j && adjacency[a][b] ) {
                    //    cout << "Jest trojkat " << i << " " << a << " " << b << endl;
                        return true;
                }
            }
        }
    }

    return false;
}

bool bipartiteDFS( int nr, int par, VI & colors, VVI & graph ){
  //  cout << "Jestem w bipartiteBFS, nr = " << nr << "   par = " << par << "   " << "myColor = " << colors[nr] << endl;
    REP( i, SIZE( graph[nr] ) ){
        int nbr = graph[nr][i];
        if( nbr == par ) continue;
        if( colors[ nbr ] != -1 && colors[ nbr ] == colors[nr] ) return false;
        else{
            if( colors[ nbr ] == -1 ){
                colors[ nbr ] = ( colors[nr]+1 ) % 2;
                if( !bipartiteDFS( nbr,nr,colors,graph ) ) return false;
            }
        }
    }
    return true;
}

bool isbipartite( VVI & graph, VI & colors ){
    colors = VI( SIZE(graph),-1 );
    REP( i, SIZE(graph) ){
        if( colors[i] == -1 ){
            colors[i] = 0;
            if( !bipartiteDFS( i,i,colors, graph ) ) return false;
         //   cout << endl;
        }
    }

   // cout << "GRAF JEST DWUDZIELNY" << endl;

    return true;
}


//****************************************************************************** CUNNING TEMPLATE SECTION
template<class _T>
bool K23( _T & V, VI & colors ){
 //   cout << "K23" << endl;
    VAR( temp,V[0] );
    REP( i, SIZE(V) ){
        FOR( k, i+1, SIZE(V)-1 ){
            if( colors[i] == colors[k] && colors[i] != -1 ){
                temp = V[i] & V[k];
                if( temp.count() >= 3 ) {
                    //    cout << "Graf K23 " << i << " " << k << endl;
                        return true;
                }
            }
        }
    }

    return false;
}

template<class _T>
void createBtsGraph( _T & V, VVI & graph, VI & colors ){
  //  cout << "createBtsGraph" << endl;
    REP( i, SIZE(graph) ){
        REP( j, SIZE(graph[i]) ){
            V[i][ graph[i][j] ] = 1;
        }
    }
}

template<class _T>
bool solveTempK23( _T & V, VVI & graph, VI & colors ){
  //  cout << "solveTempK23" << endl;
    createBtsGraph( V, graph,colors );
    return K23( V,colors );
}

bool containsK23( VVI & graph, VI & colors ){
  //  cout << "containsK23()" << endl;
    vector< bitset<101> > vbts101( SIZE(graph) );
    vector< bitset<701> > vbts701( SIZE(graph) );

    if( SIZE(graph) < 100 ) return solveTempK23( vbts101, graph, colors );
    else return solveTempK23( vbts701, graph,colors );

}

void solve(){
    clearAll();
    readData();
    initializeAll();


    REP(i,N+1) BFS(i); // i complete an array of distances between all vertices
   // cout << "Tablica odleglosci:" << endl;
  //  WRITE_ALL(dst);

   // V.clear(); // i dont need it any more...

    VVI G = getDistanceGraph(); // i create distance graph
  //  cout << "Distance graph:" << endl;
  //  WRITE_ALL(G);

  //  dst.clear(); // i dont nedd it any more either now

  //  WRITE_ALL(V);

    VI colors;
    if( !isbipartite(V, colors) || hasTriangle( G ) || containsK23( V,colors ) ){
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











