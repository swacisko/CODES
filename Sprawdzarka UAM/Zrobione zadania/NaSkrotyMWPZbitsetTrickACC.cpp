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

#define MY_SIZE 10000
#define MY_SIZE1 1000
#define MY_SIZE2 2000
#define MY_SIZE3 3000
#define MY_SIZE4 4000
#define MY_SIZE5 5000
#define MY_SIZE6 6000
#define MY_SIZE7 7000
#define MY_SIZE8 8000
#define MY_SIZE9 9000
#define MY_SIZE10 10000

int TAB;

bitset<MY_SIZE1> tab1[MY_SIZE1];
bitset<MY_SIZE2> tab2[MY_SIZE2];
bitset<MY_SIZE3> tab3[MY_SIZE3];
bitset<MY_SIZE4> tab4[MY_SIZE4];
bitset<MY_SIZE5> tab5[MY_SIZE5];
bitset<MY_SIZE6> tab6[MY_SIZE6];
bitset<MY_SIZE7> tab7[MY_SIZE7];
bitset<MY_SIZE8> tab8[MY_SIZE8];
bitset<MY_SIZE9> tab9[MY_SIZE9];
bitset<MY_SIZE10> tab10[MY_SIZE10];
/*
bitset<MY_SIZE1> sola1;
bitset<MY_SIZE2> sola2;
bitset<MY_SIZE3> sola3;
bitset<MY_SIZE4> sola4;
bitset<MY_SIZE5> sola5;
bitset<MY_SIZE6> sola6;
bitset<MY_SIZE7> sola7;
bitset<MY_SIZE8> sola8;
bitset<MY_SIZE9> sola9;
bitset<MY_SIZE10> sola10;

bitset<MY_SIZE1> solb1;
bitset<MY_SIZE2> solb2;
bitset<MY_SIZE3> solb3;
bitset<MY_SIZE4> solb4;
bitset<MY_SIZE5> solb5;
bitset<MY_SIZE6> solb6;
bitset<MY_SIZE7> solb7;
bitset<MY_SIZE8> solb8;
bitset<MY_SIZE9> solb9;
bitset<MY_SIZE10> solb10;

bitset<MY_SIZE1> common1;
bitset<MY_SIZE2> common2;
bitset<MY_SIZE3> common3;
bitset<MY_SIZE4> common4;
bitset<MY_SIZE5> common5;
bitset<MY_SIZE6> common6;
bitset<MY_SIZE7> common7;
bitset<MY_SIZE8> common8;
bitset<MY_SIZE9> common9;
bitset<MY_SIZE10> common10;*/


template< int ile >
struct MyBitset{

    bitset<ile> tab;
    bool operator[]( int pos ){
        return tab[pos];
    }

    bitset<ile> operator&( const MyBitset<ile> & oth ){
        return tab & oth.tab;
    }

    bitset<ile> operator!(){
        return ~tab;
    }

    bitset<ile> operator^( const MyBitset<ile> & oth ){
        return tab ^ oth.tab;
    }

    void reset(){
        tab.reset();
    }
};


/*
typedef bitset<MY_SIZE> TYPE;
TYPE tab[MY_SIZE];
TYPE sola, solb;
TYPE temp;
TYPE common;*/


int N,M;
VPII edges;

void clearAll(){
    edges.clear();
    REP(i,1000*TAB) {
        if( TAB == 1 ) tab1[i].reset();
        else if( TAB == 2 ) tab2[i].reset();
        else if( TAB == 3 ) tab3[i].reset();
        else if( TAB == 4 ) tab4[i].reset();
        else if( TAB == 5 ) tab5[i].reset();
        else if( TAB == 6 ) tab6[i].reset();
        else if( TAB == 7 ) tab7[i].reset();
        else if( TAB == 8 ) tab8[i].reset();
        else if( TAB == 9 ) tab9[i].reset();
        else if( TAB == 10 ) tab10[i].reset();
    }
}

template< int ile >
void readData( bitset<ile> tab[] ){
    int a,b;
    REP(i,M){
        cin >> a >> b;
        tab[a-1][b-1] = tab[b-1][a-1] = true;
        edges[i] = MP( a-1,b-1 );
    }
}

template< int ile >
void solve( bitset<ile> tab[] /*, bitset<ile> common, bitset<ile> sola, bitset<ile> solb*/ ){
  //  cout << "tab[0] ma " << tab[0].size() << "  elementow" << endl;
    int a,b,c,d;
    VAR( sola, tab[0] );
    VAR( solb, tab[0] );
    VAR( common, tab[0] );

    REP( i, SIZE(edges) ){
        a = edges[i].ST;
        b = edges[i].ND;

      //  temp = ( tab[a] & tab[b] );
      //  temp = ~temp; // teraz temp to jest tab[a] xor tab[b]

        common = tab[a] & tab[b];

        sola = tab[a]^common;
       // sola = tab[a] & ( ~tab[b] );
       // sola &= temp; // teraz sola ma sasiadow, ktorzy naleza tylko do A, ale nie naleza do B

        solb = tab[b]^common;
      //  solb = tab[b] & ( ~tab[a] );
      //  solb &= temp; // teraz solb ma sasiadow, ktorzy maleza tylko do B, ale nie naleza do A


      /*  cout << "Rozwazam krawedz " << a+1 << " - " << b+1 << endl;
        cout << "sola = ";  REP(i,N) cout << sola[i] << " ";
        cout << endl << "solb = ";  REP(i,N) cout << solb[i] << " ";
        ENDL(1);*/


        if( sola.any() && solb.any() ){
            c = d = -1;
            REP( i, N ){
                if( sola[i] && i != b ) c = i;
                if( solb[i] && i != a ) d = i;

                if( c != -1 && d != -1 ){ // jesli znalazlem rozlacznych sasiadow, to wypisuje wynik i tyle
                    cout << "NIE ";
                    if( tab[c][d] ) cout << "C ";
                    else cout << "S ";

                    cout << c+1 << " " << a+1 << " " << b+1 << " " << d+1 << endl;

                    return;
                }
            }


        }

    }

    cout << "TAK" << endl;


}

int main(){
	ios_base::sync_with_stdio(0);



    int l_zest;
    cin >> l_zest;
	while( l_zest-- ){
        cin >> N >> M;

        TAB = (int) ceil( (double)N/1000 );
      //  cout << "TAB = " << TAB << endl;

        clearAll();

        edges = VPII(M);

        if( TAB == 1 ) readData<MY_SIZE1>( tab1 );
        else if( TAB == 2 ) readData<MY_SIZE2>( tab2 );
        else if( TAB == 3 ) readData<MY_SIZE3>( tab3 );
        else if( TAB == 4 ) readData<MY_SIZE4>( tab4 );
        else if( TAB == 5 ) readData<MY_SIZE5>( tab5 );
        else if( TAB == 6 ) readData<MY_SIZE6>( tab6 );
        else if( TAB == 7 ) readData<MY_SIZE7>( tab7 );
        else if( TAB == 8 ) readData<MY_SIZE8>( tab8 );
        else if( TAB == 9 ) readData<MY_SIZE9>( tab9 );
        else if( TAB == 10 ) readData<MY_SIZE10>( tab10 );


     /*   cout << "Oto twoj graf" << endl;
        REP(i,N){
            cout << i+1 << ": ";
            REP(k,N) cout << tab[i][k] << " ";
            cout << endl;
        }*/

        if( TAB == 1 ) solve<MY_SIZE1>( tab1  );
        else if( TAB == 2 ) solve<MY_SIZE2>( tab2 );
        else if( TAB == 3 ) solve<MY_SIZE3>( tab3 );
        else if( TAB == 4 ) solve<MY_SIZE4>( tab4 );
        else if( TAB == 5 ) solve<MY_SIZE5>( tab5 );
        else if( TAB == 6 ) solve<MY_SIZE6>( tab6 );
        else if( TAB == 7 ) solve<MY_SIZE7>( tab7 );
        else if( TAB == 8 ) solve<MY_SIZE8>( tab8 );
        else if( TAB == 9 ) solve<MY_SIZE9>( tab9 );
        else if( TAB == 10 ) solve<MY_SIZE10>( tab10 );


	}


	return 0;
}












