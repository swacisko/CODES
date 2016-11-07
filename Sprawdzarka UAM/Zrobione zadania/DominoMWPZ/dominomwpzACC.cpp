//#include<cstdio>
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
//#include<cmath>
//#include<queue>
//#include<time.h>
//#include<string.h>
#include<fstream>
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
#define WRITE_ALL(V) { REP( i,SIZE(V) ){ cout  << i << " ---- ";  FOREACH(it,V[i]) cout << *it << ", "; cout << endl;     } }
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

typedef long double LD;

struct matr{
    matr( bool init = false ){
        REP(i,3) REP(k,3) tab[i][k] = (LD)0;
        if( init ) REP(i,3) tab[i][i] = (LD)1;
    }


    LD tab[3][3];
    LD& operator()( int p1, int p2 ){
        return tab[p1][p2];
    }

    void clear(){
        REP(i,3) REP(k,3) tab[i][k] = (LD)0;
    }

};

VVI V;
vector< matr > macierze;

template<class _T>
bool equals( _T a, _T b ){
   // return abs( a-b ) < EPS;
   if( a > b ) return a-b < EPS;
   else return b-a < EPS;
}

// zwraca wszystkich sasiadow danego wierzcholka, dla pierwszego klocka, sa to sasiedzi z obu stron!!
VI getNeighbours( int beg1, int beg2 = -1 ){
    VI neigh;
    REP( i, SIZE( V[beg1] ) ) if( V[beg1][i] != beg2 ) neigh.PB( V[beg1][i] );
    if( beg2 != -1 ) REP( i, SIZE( V[beg2] ) ) if( V[beg2][i] != beg1 ) neigh.PB( V[beg2][i] );
    sort( ALL(neigh) );
    return neigh;
}

// zwraca true, jesli jakos syn macierzy ma na pozycji (j+1)%3, (j+1)%3  jedynke...
bool check( int beg1, int j, int beg2 = -1 ){
    VI neigh = getNeighbours( beg1, beg2 );
    REP(i, SIZE(neigh) ) {
        if( equals( macierze[ neigh[i] ]( (j+1)%3, (j+1)%3 ), (LD)1 ) ) return true;
    }

    return false;
}


VB was;

void solve( int beg, int beg2 = -1 ){
 //   cout << "beg1 = " << beg  << "   beg2 = " << beg2 << endl;
    if( was[beg] ){
        while(1);
    }
    macierze[beg] = matr(false);
    was[beg] = true;

    VI neigh = getNeighbours( beg, beg2 );

 //   cout << "Moi sasiedzi to:\t";
 //   WRITE(neigh); ENDL(1);

    if( SIZE( neigh ) == 0 ){
        macierze[beg] = matr(true);
    //    cout << "\tbeg = " << beg << "   Moja macierz to:" << endl;
    //    REP(i,3){ cout << "\t"; REP(k,3) cout << macierze[beg].tab[i][k] << " "; cout << endl; }
    //    cout << "\tlisc, wychodze z beg = " << beg << endl << endl;
        return;
    }
    else{
        REP( i,SIZE( neigh ) ){
            solve( neigh[i] );
        }

        LD avg = 0;
        REP( i,3 ){
            REP(j,3){
                if( check( beg,j,beg2  ) ){
                    if( i == (j+1)%3 ) macierze[beg](i,j) = (LD)1;
                    else macierze[beg]( i,j ) = (LD)0;
                 //   cout << "Jestem w check, i = " << i << " j = " << j << "   " << macierze[beg](i,j) << endl;
                }
                else{
                    avg = (LD)0;

                    REP( k, SIZE( neigh ) ){ // dla kazdego sasiada:
                        avg += macierze[ neigh[k] ]( i, (j+1)%3 );
                    }

                    avg /= ( (LD)SIZE( neigh ) );
                    macierze[beg]( i,j ) = avg;
                }


            }
        }


    }

   /* cout << "\tbeg = " << beg << "  Moja macierz to:" << endl;
    REP(i,3){ cout << "\t"; REP(k,3) cout << macierze[beg].tab[i][k] << " "; cout << endl; }
    cout << "\twuchodze z beg = " << beg << endl << endl;*/

    return;
}



int main(){
	ios_base::sync_with_stdio(0);
	cout << fixed;
	cout.precision(3);

    int K;
    V.clear();
    cin >> K;

    was = VB(K+1,false);
    V = VVI( K+1 );
    int a,b;
    VPII edges;
    macierze = vector< matr >(K+1);

 //   cout << "K = " << K << endl;
    REP(i,K-1){
        cin >> a >> b;
        if( a > b ) swap( a,b );
        V[a].PB(b);
        edges.PB( PII(a,b) );

    }

    int start = 0;
    cin >> start;
    start--;

  //  cout << "Graf" << endl;
  //  WRITE_ALL(V);

    matr res1;


    solve( edges[start].ST, edges[start].ND );
    res1 = macierze[ edges[start].ST ]; // musze wziaz mniejsza liczbe oczek z pierwszego klocka

    LD J,M,S;
    J = M = S = LD(0);

    J = res1( 0,0 );
    M = res1( 1,0 );
    S = res1( 2,0 );

 /*   fill( ALL(was),false );

    solve( edges[start].ND, edges[start].ST );
    matr res2 = macierze[ edges[start].ND ];
    if( !equals( res2(0,0),J ) || !( equals( res2(1,0),M ) ) || !equals( res2(2,0),S ) ){
            cout << "BLAD" << endl;
            cout << J << " " << M << " " << S << endl;
            cout << res2(0,0) << " " << res2(1,0) << " " << res2(2,0) << endl;

            ofstream ostr( "Error.txt" );
            ostr << K << endl;
            REP(i,K-1) ostr << edges[i].ST << " " << edges[i].ND << endl;
            ostr << start+1 << endl;
            ostr.close();
    }*/

 //   J = (double)( (int) (J * 1000) ) / 1000;
 //   M = (double)( (int) (M * 1000) ) / 1000;
 //   S = (double)( (int) (S * 1000) ) / 1000;


    cout << J << " " << M << " " << S << endl;
  //  cout << res2(0,0) << " " << res2(1,0) << " " << res2(2,0) << endl;

	return 0;
}












