//#include<cstdio>
#include<iostream>
#include<vector>
//#include<string>
//#include<map>
//#include<complex>
//#include<stack>
//#include<list>
//#include<bitset>
#include<set>
//#include<iterator>
#include<cmath>
//#include<queue>
#include<time.h>
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

int CONSTRUCTOR;


template<class _T>
class VEBTree{
public:
    // size denotes the number of elements, we want to store, hence from 0 to size-1
    VEBTree( int size = 1<<30 ){
        int height = ceil( log2( log2(size) ) );
        int sq = ( 1 << ( 1 << ( height-1 ) ) );
      //  cout << "size = " << size << "   sq = " << sq << endl;
        *this = VEBTree( size-1, sq );
    }

    VEBTree( int ee, int sq ) : e(ee), sqr(sq) {
        CONSTRUCTOR++;
   //     cout << "ee = " << ee << "   sq = " << sq << endl;
        if( ee <= 1 ){ // if i am the node in the utmost low level
      //      cout << "I am in ee <= 1" << endl;
        }
        else{
            int ile = (int)ceil( ((double)(e+1)) / (double)sqr );
            sons.clear();
            REP(i,ile) sons.PB( VEBTree( sqr-1, (int)round( sqrt(sqr) ) ) );
         //   sons.PB( VEBTree( e%sqr, (int)round( sqrt(sqr) ) ) );

       //     cout << "I leave the constructor" << endl;
         //   cout << "In constructor, SIZE(sons) = " << SIZE(sons) << endl;
        }
    }

    // recursive destructor...
   /* ~VEBTree(){
        REP(i,SIZE(sons)) sons[i].~VEBTree();
        sons.clear();
    }*/

    // setValue set value at position pos on val
    void setVal( int pos, _T val ){
      //  cout << "e = " << e << "   pos = " << pos << "   val = " << val << endl;
        if( e <= 1 ){ // if i am to acces element
            if( pos > e ) cout << "PLACEMENT ERROR, POSITION OUT OF BOUNDS IN SETVAL" << endl;
            else{
                nd.tab[pos] = val;
                return;
            }
        }
        else{ // if i am to call recursively...
            int newind = pos/sqr;
         //   cout << "SIZE(sons) = " << SIZE(sons) << "    newind = " << newind << "\t" << flush;
            int newpos = pos - newind*sqr; // the same as pos%sqr;
         //   cout << "  newpos = " << newpos << endl;
            sons[newind].setVal( newpos, val );
        }
    }

    // return value at position pos, or deafaultval element, if there was nothing inserted yet at position pos
    _T getVal( int pos, _T defaultval ){
        if( e <= 1 ){
            if( pos > e ) cout << "PLACEMENT ERROR, POSITION OUT OF BOUNDS IN GETVAL" << endl;
            else return nd.tab[pos];
            return 0;
        }
        int newind = pos/sqr;
        int newpos = pos - newind*sqr; // the same as pos%sqr;

        return sons[newind].getVal( newpos, defaultval );
    }

    // deletes value from position pos from the tree
    void erasePos( int pos ){
        if( e <= 1 ){
            if( pos > e ) cout << "PLACEMENT ERROR, POSITION OUT OF BOUNDS IN GETVAL" << endl;
            else{
                nd.tab[pos] = -INF;
                return;
            }
        }
        int newind = pos/sqr;
        int newpos = pos - newind*sqr; // the same as pos%sqr;

        sons[newind].erasePos( newpos );
        return;
    }

    // call fuction fun with element stored at position pos as its parameter
    // returns true if operation was executed ( function called ) and false otherwise
    bool execute( int pos, void (*fun)( _T &elt ) ){
        if( e <= 1 ){
            if( pos > e ) cout << "PLACEMENT ERROR, POSITION OUT OF BOUNDS IN GETVAL" << endl;
            else{
                if( nd.tab[pos] != -INF ) { fun( nd.tab[pos] ); return true; }
            }
        }
        int newind = pos/sqr;
        int newpos = pos - newind*sqr; // the same as pos%sqr;
        return sons[newind].execute( newpos,fun );
    }


//********* czesc prywatna klasy
private:
    // klasa, ktora przechowuje elementy, czyli ta najbardziej 'dolna'
    class Node{
    public:
        Node(){
            tab[0] = tab[1] = -INF;
        }
        Node( _T st, _T nd ){
            tab[0] = st;
            tab[1] = nd;
        }
        _T tab[2];
    };



    int e; // end of the tree - GREATEST VALUE THAT WE WANT IN THE TREE!!!!!, hence number of possible elements to store equals e+1;
    //int length; // length = e+1;
    int sqr; // sqrt(length),  required for calculations

    vector< VEBTree > sons; // sons of the current VEBTree vertex
    Node nd; // if e-b == 1 then nd pointer != null

};









int main(){

    CONSTRUCTOR = 0;
    int ELT_NR = 1000;
 //   VEBTree<int> tree( ELT_NR );



    /*
    cout << "Manual testing" << endl;
    int casenr = 100;

    do{
        switch( casenr ){
            case 1:{
                int pos;
                cout << "Determine element index you want to be set:\t";
                cin >> pos;

                cout << "Determine value you want to be set:\t";
                int val;
                cin >> val;

                tree.setVal( pos, val );

                break;
            }
            case 2:{
                int pos;
                cout << "Determine position you want to access:\t";
                cin >> pos;

                int val = tree.getVal(pos,-INF);
                cout << "Accessed value equals to " << val << endl;

                break;
            }
            default:{
              //  system("cls");
                cout << "To insert element press 1" << endl << "To access element press 2" << endl;
            }

        }

        cout << "Choose option:\t";

    }while( cin >> casenr );*/



    set<int> zbior;
   // while(1);
   VEBTree<int> tree( ELT_NR );
   cout << "Tree created" << endl;

    cout << "Checking correctness" << endl;
    REP( i,ELT_NR ){
        int w;
        if( (w = rand()%3) == 0 ){
            int t = rand()%ELT_NR;
         //   cout << "Inserting " << t << endl;

            zbior.insert( t );
            tree.setVal( t,1 );
        }
        else if( w == 1 ){
            int t = rand()%ELT_NR;
            int is = zbior.count( t );
            if( is != 0 ) is = 1;
            else is = -INF;
            int istree = tree.getVal( t, -INF );

           // cout << "\tChecking for " << t << "   is = " << is << "   istree = " << istree << endl;

            if( is != istree ){
                cout << "FAILURE" << endl;
            }
        }
        else{
            int t = rand()%ELT_NR;
         //   cout << "\t\tErasing " << t << endl;
            zbior.erase(t);
            tree.erasePos(t);
        }
    }


    cout << "Checking time complexity" << endl;

    CONSTRUCTOR = 0;
    ELT_NR = 10000;
    int STEP = 10000;
    int MAX_SIZE = 100001;
  //  zbior.clear();
  //  tree.~VEBTree();

    int tx = clock();
    tree = VEBTree<int>( MAX_SIZE );
    cout << "It took    " << clock() - tx << "    miliseconds to create VEBTree on " << MAX_SIZE << " elements   CONSTRUCTOR was called " << CONSTRUCTOR << " times" << endl;
 //   while(1);

    while( ELT_NR <= MAX_SIZE ){

        // section for common set<int>
        zbior.clear();

        int t1 = clock();
        REP( i,10*ELT_NR ){
            int w = rand()%4;
            if( w == 0 ){
                zbior.insert( rand()%ELT_NR );
            }
            else if( w == 1 ){
                zbior.erase( rand()%ELT_NR );
            }
            else{
                int v = zbior.count( rand()%ELT_NR );
            }
        }

        cout << "It took the regular set<int>    " << ( clock() - t1 ) << "     miliseconds to execute " << ELT_NR << "  operations" << endl;
        zbior.clear();


         // section for VEBTree<int>

       // tree.~VEBTree();
      //  cout << "Tree deleted" << endl;
       // t1 = clock();
      //  tree = VEBTree<int>(ELT_NR);
      //  cout << "It took    " << clock() - t1 << "    miliseconds to create VEBTree on " << ELT_NR << " elements" << endl;

        t1 = clock();
        REP( i,10*ELT_NR ){
            int w = rand()%4;
            if( w == 0 ){
              //  cout << "SV  " << flush;
                tree.setVal( rand()%ELT_NR,1 );
            }
            else if( w == 1 ){
             //   cout << "EP " << flush;
                tree.erasePos( rand()%ELT_NR );
            }
            else{
              //  cout << "GV " << flush;
                tree.getVal( rand()%ELT_NR, -1  );
            }
        }

        cout << "It took the VEBTree<int>    " << ( clock() - t1 ) << "     miliseconds to execute " << ELT_NR <<
            "  operations   CONSTRUCTOR was called " << CONSTRUCTOR << " times" << endl;
        cout << endl;

        ELT_NR += STEP;
    }





    return 0;
}

















