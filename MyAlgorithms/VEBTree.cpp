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

// _T stand for type of value, we ewant to store...
// _D stands for either int or long long  ( or BigNum, but i dont think there is any point in ding it for BigNum... )
template<class _T, class _D>
class VEBTree{
public:
    // size denotes the number of elements, we want to store, hence from 0 to size-1
    VEBTree( _D size = 1<<30 ){
        _D height = ceil( log2( log2((_D)size) ) );
      //  _D sq = ( 1 << ( 1 << ( height-1 ) ) ); // this should be done if _D is int type...
        _D sq=1,pw = 1<<( height-1 );
        REP(i,pw) sq <<= 1;
       // cout << "size = " << size << "   sq = " << sq << endl;
        *this = VEBTree( size-1, sq );
    }

    VEBTree( _D ee, _D sq ) : e(ee), nd(0), sqr(sq) {
      //  CONSTRUCTOR++; // IT IS ONLY FOR TESTING
      //  cout << "\tI am in constructor, ee = " << ee << "   sq = " << sq << endl;

        if( e <= 1 ){ // if i am the node in the utmost low level
            nd = new Node();
            return;
        }

        _D ile = (_D)ceil( (double)(e+1) / (double)sqr );
        sons = vector< VEBTree* >( ile );
        REP(i,SIZE(sons)) sons[i] = 0;

     //   cout << "In constructor, SIZE(sons) = " << SIZE(sons) << endl;
    }

    // recursive destructor...
    ~VEBTree(){
        if( e <= 1 ){ delete nd; nd = 0; }
        REP(i,SIZE(sons)) if( sons[i] != 0 ){ delete sons[i]; sons[i]=0; }
      //  sons.clear();
    }

    // setValue set value at position pos on val
    void setVal( _D pos, _T val ){
      //  cout << "e = " << e << "   pos = " << pos << "   val = " << val << endl;
        if( e <= 1 ){ // if i am to acces element
            if( pos > e ) cout << "PLACEMENT ERROR, POSITION OUT OF BOUNDS IN SETVAL" << endl;
            else{
                if( nd == 0 ) nd = new Node();
                else if( nd->tab[pos] == 0 ) nd->tab[pos] = new _T(val);
                else *nd->tab[pos] = val;
            }
        }
        else{ // if i am to call recursively...
            _D newind = pos/sqr;
         //   cout << "SIZE(sons) = " << SIZE(sons) << "    newind = " << newind << "\t" << flush;
            if( sons[newind]==0 ) sons[newind] = new VEBTree( sqr-1, (int)round( sqrt(sqr) ) ); // if such node does not exist yet, i add it...

            _D newpos = pos - newind*sqr; // the same as pos%sqr;
         //   cout << "  newpos = " << newpos << endl;
            sons[newind]->setVal( newpos, val );
        }
    }

    // return value at position pos, or deafaultval element, if there was nothing inserted yet at position pos
    _T getVal( _D pos, _T defaultval ){
        if( e <= 1 ){
            if( pos > e ) cout << "PLACEMENT ERROR, POSITION OUT OF BOUNDS IN GETVAL" << endl;
            else if( nd->tab[pos] == 0 ) return defaultval;
            else return *nd->tab[pos];
        }
        _D newind = pos/sqr;
        if( sons[newind] == 0 ) return defaultval;

        _D newpos = pos - newind*sqr; // the same as pos%sqr;
        return sons[newind]->getVal( newpos, defaultval );
    }

    // deletes value from position pos from the tree
    void erasePos( _D pos ){
        if( e <= 1 ){
            if( pos > e ) cout << "PLACEMENT ERROR, POSITION OUT OF BOUNDS IN GETVAL" << endl;
            else{
                if( nd->tab[pos] != 0 ){ delete nd->tab[pos]; nd->tab[pos] = 0; }
                return;
            }
        }
        _D newind = pos/sqr;
        if( sons[newind] == 0 ) return;

        _D newpos = pos - newind*sqr; // the same as pos%sqr;
        sons[newind]->erasePos( newpos );
        return;
    }

    // call fuction fun with element stored at position pos as its parameter
    // returns true if operation was executed ( function called ) and false otherwise
    bool execute( _D pos, void (*fun)( _T &elt ) ){
        if( e <= 1 ){
            if( pos > e ) cout << "PLACEMENT ERROR, POSITION OUT OF BOUNDS IN GETVAL" << endl;
            else{
                if( nd->tab[pos] == 0 )
                fun( nd->tab[pos] );
                return true;
            }
        }
        _D newind = pos/sqr;
        if( sons[newind] == 0 ) return false;

        _D newpos = pos - newind*sqr; // the same as pos%sqr;
        return sons[newind]->execute( newpos,fun );
    }


//********* czesc prywatna klasy
private:
    // klasa, ktora przechowuje elementy, czyli ta najbardziej 'dolna'
    class Node{
    public:
        Node(){
            tab[0] = new _T(0);
            tab[1] = new _T(0);
        }
        Node( _T st, _T nd ){
            tab[0] = st;
            tab[1] = nd;
        }
        ~Node(){
            REP(i,2){ if( tab[i] != 0 ) delete tab[i]; tab[i] = 0; }
        }
        _T* tab[2];
    };



    _D e; // end of the tree - GREATEST VALUE THAT WE WANT IN THE TREE!!!!!, hence number of possible elements to store equals e+1;
    //int length; // length = e+1;
    _D sqr; // sqrt(length),  required for calculations

    vector< VEBTree* > sons; // sons of the current VEBTree vertex
    Node* nd; // if e-b == 1 then nd pointer != null

};









int main(){

    CONSTRUCTOR = 0;

    LL ELT_NR = 300000;
    LL BIGRANGE = 1000000000;
   // REP(i,50) BIGRANGE <<= 1;
    VEBTree<int,int> tree( BIGRANGE );



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

        cout << "Constructor was called " << CONSTRUCTOR << " times " << endl << endl;;
        cout << "Choose option:\t";

    }while( cin >> casenr );*/



    set<int> zbior;

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
            int istree = tree.getVal( t, 0 );

         //   cout << "\tChecking for " << t << "   is = " << is << "   istree = " << istree << endl;

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

    ELT_NR = 100000; // maksymalny zasieg liczb w danej chwili dla drzewa...
    int MAX_SIZE = 2000000000;
   // REP(i,55) MAX_SIZE <<= 1; // maksymalny zasieg liczb, sens tylko dla liczb na tyle duzych, ze ich bezposrednie indeksowanie nie jest mozliwe...
    double STEP = 1.2;
    int ELEMENTS = 1000000; // liczba operacji w petli testujacej

  //  zbior.clear();
  //  tree.~VEBTree();
    while( ELT_NR <= MAX_SIZE ){

        // section for common set<int>
        zbior.clear();

        int t1 = clock();
        REP( i,ELEMENTS ){
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

        cout << "It took the regular set<int> " << ( clock() - t1 ) << "  miliseconds to execute " << ELEMENTS << "  operations within range (0," << ELT_NR << ")" << endl;
        zbior.clear();


         // section for VEBTree<int>

      //  tree.~VEBTree();
       // cout << "Tree deleted" << endl;
        t1 = clock();
        tree = VEBTree<int,int>(ELT_NR);


        REP( i,ELEMENTS ){
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

        cout << "It took the VEBTree<int> " << ( clock() - t1 ) << "  miliseconds to execute " << ELEMENTS << "  operations within range (0," << ELT_NR << ")" << endl;
        cout << endl;

        ELT_NR *= STEP;
    }





    return 0;
}

















