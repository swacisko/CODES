//#include<cstdio>
#include<iostream>
#include<vector>
//#include<string>
#include<map>
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

VVI V;
VVI W;
VPII E;
VVI X;

map< PII, int > ans;

VB was;
VI ncost;
VI dist;


bool isLeaf( int n ){
    return SIZE( V[n] ) == 1;
}


void longest( int beg, int dst ){
    was[beg] = true;
    dist[beg] = dst;

    REP( i, SIZE( V[beg] ) ){
        if( !was[ V[beg][i] ] ){
            longest( V[beg][i], dst+1 );
        }
    }
}


void DFS_EDGE( int beg, int& cost ){
    was[beg] = true;
    REP( i, SIZE( V[beg] ) ){
        if( !was[ V[beg][i] ] ){
            if( isLeaf( V[beg][i] ) ){
            //    W[beg][ i ] = cost;
                ans[ MP(beg, V[beg][i] ) ] = ans[ MP( V[beg][i],beg ) ] = cost;

                cost--;
                DFS_EDGE( V[beg][i], cost );
            }
        }
    }

    REP( i, SIZE( V[beg] ) ){
        if( !was[ V[beg][i] ] ){
            if( !isLeaf( V[beg][i] ) ){
             //   W[beg][ i ] = cost;
                ans[ MP(beg, V[beg][i] ) ] = ans[ MP( V[beg][i],beg ) ] = cost;

                cost--;
                DFS_EDGE( V[beg][i], cost );
            }
        }
    }

    return;
}
/*
int help( VI& V1, VI& V2, int p, int q ){
    int ind = p;
    FOR(i,p,q-1){
        if( W[i] <= W[q] ){
                swap( V1[i], V1[ind] );
                swap( V2[i], V2[ind] );
                ind++;
        }
    }
    swap( V1[ind], V1[q] );
    swap( V2[ind], V2[q] );
    return ind;

}

void quicksort( VI& V1, VI& V2, int p, int q ){
    if( p < q ){
        int k = help( V1,V2,p,q );
        quicksort( V1,V2,p,k-1 );
        quicksort( V1,V2,k+1,q );
    }
}*/


void DFS_NODE( int beg, int& cost, bool now ){

    was[beg] = true;
    if( now == true ){
       // cout << "DFS_NODE beg = " << beg << "  cost = " << cost << "   now = " << now << endl;
        ncost[beg] = cost;
        cost++;
        REP( i,SIZE( V[beg] ) ){
            if( !was[ V[beg][i] ] ){
                if( !isLeaf( V[beg][i] ) ) DFS_NODE( V[beg][i], cost, !now );
            }
        }
    }
    else{
        if( SIZE(V[beg]) == 1 ) return;
        else{
        //  cout << "\nDFS_NODE beg = " << beg << "  cost = " << cost << "   now = " << now << endl;
          /*  VI V2 = V[beg];
            VI W2 = W[beg];

          //  quicksort( W2, V2, 0, SIZE(W2)-1 );
          //  reverse( ALL(W2) );
             // juz mam posortowanych sasiadow po malejacych wartosciach wag...

             REP( i,SIZE(V2) ){
                if( !was[ V2[i] ] ){
                    if( isLeaf( V2[i] ) ) DFS_NODE( V2[i], cost, !now );
                }
             }

            cout << "TUTAJ?" << endl;
             REP( i,SIZE(V2) ){
                if( !was[ V2[i] ] ){
                    if( !isLeaf( V2[i] ) ) DFS_NODE( V2[i], cost, !now );
                }
             }*/

             REP( i,SIZE(V[beg]) ){
                if( !was[ V[beg][i] ] ){
                    if( isLeaf( V[beg][i] ) ) DFS_NODE( V[beg][i], cost, !now );
                }
             }

           //  cout << "\tTUTAJ?" << endl;
             REP( i,SIZE( V[beg]) ){
                if( !was[ V[beg][i] ] ){
                    if( !isLeaf( V[beg][i] ) ) DFS_NODE( V[beg][i], cost, !now );
                }
             }

        }
    }

  //  cout << "Wychodze..." << endl << endl;
    return;
}



void clearAll(){
    V.clear();
    E.clear();
    was.clear();
    dist.clear();
    W.clear();
    ncost.clear();
    ans.clear();
}

void initAll( int N ){
    V = VVI(N);
    W = VVI(N);
    E = VPII(N-1);
    was = VB( N,false );
    dist = VI(N,0);
    ncost = VI(N,0);
}

void solve(){
  //  cout << "Jestem w solve" << endl;
    clearAll();

    int N;
    int a,b;
    cin >> N;
    initAll( N );
 //   cout << "Jestem po initAll()" << endl;

    REP(i,N-1){
        cin >> a >> b;

        E[i].ST = a-1;
        E[i].ND = b-1;

        V[a-1].PB(b-1);
        V[b-1].PB(a-1);

        W[a-1].PB(0);
        W[b-1].PB(0);
    }

  //  cout << "Wszystko wczytalem" << endl;

 /*   cout << "Oto graf:" << endl;
    WRITE_ALL(V);
    REP(i,SIZE(V))  quicksort( V[i],W[i],0,SIZE(V[i])-1 );
    cout << "Oto posortowany graf:" << endl;
    WRITE_ALL(V);
    return;*/

    longest( 0,0 );

  /*  cout << "Oto tablica dystansow" << endl;
    REP(i,SIZE(dist)){
        cout << "dist[" << i <<"] = " << dist[i] << endl;
    }*/
  //  int ind = max_element( ALL(dist) ) - dist.begin();


    int ind = 0, max_val = -1;
    REP( i,SIZE(dist) ){
        if( dist[i] >= max_val ){
            max_val = dist[i];
            ind = i;
        }
    }

 //   cout << "index o maxymalnym dystansie to " << ind << endl;

    int ecost = 2*N-1;


    fill( ALL(was), false );
    DFS_EDGE( ind, ecost );
  //  REP(i,N-1) cout << "Krawedzi " << E[i].ST << " " << E[i].ND << "  przypisalem wage " << W[ E[i].ST ][ E[i].ND ] << endl;

    fill( ALL(was), false );
    int cost = 1;
    DFS_NODE( ind, cost,true );

  //  cost++; // ??

    fill( ALL(was), false );
    was[ind] = true;
    DFS_NODE( V[ind][0], cost,true );


    REP( i,N ) cout << ncost[i] << " ";
    cout << endl;

 /*   cout << "Graf:" << endl;
    WRITE_ALL(V);*/


    REP( i,N-1) {
       // if( W[ E[i].ST ][ E[i].ND ] != 0  ) cout << W[ E[i].ST ][ E[i].ND ] << " ";
       // else cout << W[ E[i].ND ][ E[i].ST ] << " ";
       cout << ans[ E[i] ] << " ";
    }
    cout << endl;


}





int main(){
	ios_base::sync_with_stdio(0);
    int l_zest;
    cin >> l_zest;

	while( l_zest-- ){

        solve();

	}


	return 0;
}












