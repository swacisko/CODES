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

/*
bool canFormSameCol( int rowa, int rowb, int cola, int colb ){
    int M = max( rowa, rowb );
    int m = min( rowa, rowb );

}*/


int getNumOnPos( int row, int col ){
    int x = 1, p = 1, r = 1, c = 1;
    int ile = 1;
    while( r < row ){
        x += p;
        p ++;
       // ile++;
        r++;
    }

  //  cout << "\tx = " << x << endl;

    while( c < col ){
        x++;
        c++;
    }

 //   cout << "\tx = " << x << endl;

    return x;
}


void getPos( int a, int &rowa, int &cola ){
    int x = 1, p = 1, row = 1, col = 1;
    int ile = 1;
    while( x + p <= a ){
     //   cout << "x = " <<x << "  p = " << p << "  ile = " << ile << "  rowa = " << rowa << endl;
        rowa++;
        x += p;
        p++;
      //  ile++;
    }

  //  cout << "\tx = " << x << endl;

    while( x < a ){
        cola++;
        x++;
    }

  //  cout << "\tx = " << x << endl;
}

bool canFormDif( int rowa, int rowb, int cola, int colb ){
    int Mr = max(rowa,rowb);
    int mr = min(rowa,rowb);

    int Mc  = max(cola,colb);
    int mc = min(cola,colb);

  //  cout << "Mr = " << Mr << "  mr= " << mr << "   Mc = " << Mc << "   mc = " << mc << endl;

    int x = 1, p = 2, c = 1;
    int nr = getNumOnPos(mr,Mc);
  //  cout << "nr = " << nr << endl;
    int ile = 2;
    while( x + p <= nr ){
        x += p;
        p++;
        c++;
    }

    if( c < Mc ) return false;

}

int main(){
	ios_base::sync_with_stdio(0);
	cout << fixed;
	cout.precision(2);

    int a,b;
    cin >> a >> b;

    int rowa=1, cola=1, rowb=1, colb=1;

    getPos( a, rowa, cola );
    getPos( b, rowb, colb );

   // cout << "a = " << a << "    rowa = " << rowa << "   cola = " << cola << endl;
 //   cout << "b = " << b << "   rowb = " << rowb << "   colb = " << colb << endl;

    if( rowa != rowb && cola != colb && ( abs(rowa-rowb) != abs(cola - colb)   )  ){
        cout << "none" << endl;
    }
    else{
        if( rowa == rowb ){ // jesli sa w tym samym rzedzie...
            int M = max( cola, colb );
            int m = min( cola, colb );

            int dif = M - m;
            int n1 = getNumOnPos( rowa + dif, M ); // wypisuje to ponizej
            int n2 = getNumOnPos( rowa - dif, m ); // wypisuje to powyzej

            if( n1 > n2 ) swap( n1,n2 );
            cout << n1;
            if( n2 != INF ) cout << " " << n2 << endl;
            else cout << endl;

        }
        else if( cola == colb ) {
            int M = max(rowa,rowb);
            int m = min(rowa,rowb);
            int dif = M - m;

            int n1 = getNumOnPos( M,cola + dif );
            int n2 = INF;
            if( cola - dif >= 1 ){
                   n2 = getNumOnPos( m, cola - dif );
            }

             if( n1 > n2 ) swap( n1,n2 );
            cout << n1;
            if( n2 != INF ) cout << " " << n2 << endl;
            else cout << endl;
        }
        else{
            int Mr = max(rowa,rowb);
            int mr = min(rowa,rowb);

            int Mc  = max(cola,colb);
            int mc = min(cola,colb);

            int n1 = getNumOnPos( Mr,mc );
            int n2 = INF;

        //    cout << "Aaaa" << endl;
            if( canFormDif(rowa,rowb,cola,colb) ){
             //       cout << "Jestem tu" << endl;
                 n2 = getNumOnPos( mr,Mc );
            }

            if( n1 > n2 ) swap( n1,n2 );
            cout << n1;
            if( n2 != INF ) cout << " " << n2 << endl;
            else cout << endl;


        }




    }



	return 0;
}












