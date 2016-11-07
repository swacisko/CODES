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



int C,Q;
int mx,my;


struct Town{
    int x;
    int y;
    int b;
    int e;
    int d;
    int id;
    int s;
    bool was;


    Town( int idd, int xx, int yy, int bb, int ee, int dd, int ss ){
        x = xx;
        y = yy;
        b = bb;
        d = dd;
        e = ee;
        id = idd;
        s = ss;
        was = false;
    }


};

Town miasto( -1,-1,-1,-1,-1,-1,-1 );


typedef Town _T;
typedef vector<_T> VT;
typedef vector< VT > VVT;

VT clients;
VVI V;

int odl( _T t1, _T t2 ){
    return  (int) abs(t1.x - t2.x) + (int)abs(t1.y - t2.y );
}



VVI routs; // wektor oznaczajacy dorig... jest to ciag liczb, routs[0], ... takichh, ze ciezarowka odwiedza clients[ routs[0] ], ...
// uwaga, przy dodawaniu drogi trzeba najpierw dodac mx,my na poczatku!!!

int getLength(){
    int dl = 0;
    REP(i,SIZE(routs)){
        REP(k,SIZE( routs[i])-2 ){
            dl += odl( clients[ routs[i][k] ], clients[ routs[i][ k+1 ] ] );
        }
        dl += odl( miasto, clients[ routs[i][0] ] );
        dl += odl( miasto, clients[ routs[i][ SIZE(routs[i])-1 ] ] );
    }

    return dl;
}


// funkcja tworzy sciezke, ktora objezdza, kolejny zukowoz
// q oznacza pojemnosc jeszcze dostepna przez zukowoz, beg to misto, w ktorym aktualnie sie znajduje, zawsze rozne od mx,my
void getPath( int beg, int q, VI & path ){
  //  cout << "Jestem w getPath, beg = " << beg << endl;
    q -= clients[beg].d; // po tej operacji, w petli for w zmiennej q bedzie dostepa ilosc amunicji, jakie moze rozwiezc dany zukowoz...
    path.PB( beg );
    clients[beg].was = true;

    int ind = -1;
    int minim = INF;

    REP( i,SIZE(V[beg]) ){
        if( clients[ V[beg][i] ].was == false && clients[ V[beg][i] ].d <= q &&  minim > odl( miasto, clients[ V[beg][i] ] ) ){
            minim = odl( miasto, clients[ V[beg][i] ] );
            ind = V[beg][i];
        }
    }

    if( ind == -1 ) return;

    getPath( ind,q,path );
}




// funkcja wyznaczajaca polaczenia...
void solve(){
 //   cout << "Jestem w solve..." << endl;

    bool found = true;
    int minim = INF;
    int ind;

    while( found == true ){
        ind = 1;
        minim = INF;
        found = false;

        FOR( i,1,SIZE(clients)-1 ){
            if( clients[i].was == false &&  minim > odl( miasto, clients[i] ) ){
                minim = odl( miasto, clients[i] );
                ind = i;
                found = true;
            }
        }

        if( found == false ) break;


        VI path;
        path.clear();
        getPath( ind,Q,path );

        routs.PB( path );


        if( found == false ) break;

    }




}



int main(){
	ios_base::sync_with_stdio(0);



	cin >> C >> Q;
	cin >> mx >> my;

	miasto = Town( -1,mx,my,-1,1,-1,-1 );


    clients.clear();
    clients.PB( miasto ); // dodaje, bo klienci sa numerowani od 1  do C wlacznie
    int x,y,b,e,d,id,s;
    REP(i,C){
        cin >> id >> x >> y >> b >> e >> d >> s;
        clients.PB( Town( id,x,y,b,e,d,s ) );
    }

//    cout << "Wczytalem klientow" << endl;


    V = VVI( C+1 ); // to bedzie struktura grafu polaczen...
    FOR( i,1,SIZE(clients)-1 ){
        V[0].PB( i ); // miasto jest polaczone z kazda droga...

    }

 //   cout << "Dodalem miasto do grafu polacze, teraz stwprze caly graf" << endl;

    FOR( i,1,SIZE(clients)-1 ){
        FOR( k,1,SIZE(clients)-1 ){
            if( k != i && clients[i].e + clients[i].s + odl( clients[i], clients[k] ) <= clients[k].e ){
                V[i].PB(k);
            }
        }
    }

 //   cout << "Stworzlem graf polaczen" << endl;

    REP( i,SIZE(V) ) random_shuffle( ALL( V[i] ) );

  /*  FOR( i,1,SIZE(clients)-1 ){
        cout << "Klient nr " << i << "  ma polaczenia z klientami:  " << flush;
        REP(k,SIZE(V[i])) cout << V[i][k] << " ";
        cout << endl;
    }*/

    solve();



    cout << SIZE(routs) << " " << getLength() << endl;
    REP(i,SIZE(routs)){
        REP( k,SIZE(routs[i]) ){
            cout << clients[ routs[i][k] ].id << " ";
        }
        cout << endl;
    }


}












