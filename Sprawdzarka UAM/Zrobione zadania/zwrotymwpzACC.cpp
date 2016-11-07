//#include<cstdio>
#include<iostream>
#include<vector>
#include<string>
//#include<map>
//#include<complex>
//#include<stack>
//#include<list>
#include<bitset>
//#include<set>
//#include<iterator>
//#include<cmath>
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
typedef vector< VB > VVB;
typedef long long LL;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;

#define BITSETSIZE 60

int Width;
int Height;
int N;
string objects; // string which contains consecutive objects thrown into the store
bitset<BITSETSIZE> hole; // state of the store
VVB allSolids[15][5];
bitset<BITSETSIZE> allSolidsBit[15][5];

/*
void drawHole(){
    FORD( y, SIZE(hole)-1,0 ){
        if( y < Height ) cout << "x";
        else cout << " ";

        REP(x,Width){
            if( hole[x][y] == true ) cout << "x";
            else cout << " ";
        }

        if( y < Height ) cout << "x";
        else cout << " ";

        cout << endl;
    }

    REP(i,Width+2) cout << "x";
    ENDL(2);
}*/

void drawSolid( VVB solid ){
    FORD( y, SIZE( solid[0] )-1,0 ){
        REP( x,SIZE(solid) ) if( solid[x][y] ) cout << "x";
                            else cout << " ";
        cout << endl;
    }
}


// return a solid which represents a block
// solid is a VVB( N, VB(M) ), when it has height of M and width of N
// start point of the solid is its bottom left corner.
VVB getSolid( char t ){
    VVB solid;
    if( t == 'o' ) return VVB( 2, VB(2,true) );
    else if( t == 'l' ){
        solid = VVB( 2, VB(3,false) );
        solid[0][0] = solid[0][1] = solid[0][2] = solid[1][0] = true;
        return solid;
    }
    else if( t == 'p' ){
        solid = VVB(2, VB(3,true));
        solid[1][0] = false;
        return solid;
    }
    else if( t == 't' ){
        solid = VVB(3,VB(3,true));
        solid[0][0] = solid[0][1] = solid[2][0] = solid[2][1] = false;
        return solid;
    }
    else if( t == 'j' ){
        solid = VVB(2, VB(3,true));
        solid[0][1] = solid[0][2] = false;
        return solid;
    }
    else if( t == 'i' ){
        return VVB( 1, VB(3,true) );
    }
    else if( t == 'u' ){
        solid = VVB(3,VB(3,true));
        solid[1][1] = solid[1][2] = false;
        return solid;
    }
    else if( t == '.' ){
        return VVB(1,VB(1,true));
    }
    else if( t == ':' ){
        return VVB(1,VB(2,true));
    }
    else if( t == '4' ){
        solid = VVB(2,VB(3,true));
        solid[0][0] = solid[1][2] = false;
        return solid;
    }
    else if( t == 'b' ){
        solid = VVB(2,VB(3,true));
        solid[1][0] = solid[1][2] = false;
        return solid;
    }
}

// return number of different solids i can create with this block
int getRotations( char t ){
    if( t == 'o' ) return 1;
    else if( t == 'l' ) return 4;
    else if( t == 'p' ) return 4;
    else if( t == 't' ) return 4;
    else if( t == 'j' ) return 4;
    else if( t == 'i' ) return 2;
    else if( t == 'u' ) return 2;
    else if( t == '.' ) return 1;
    else if( t == ':' ) return 2;
    else if( t == '4' ) return 2;
    else if( t == 'b' ) return 4;
}

// return a solid after rotation right at an angle of 90 degree
VVB rotateSolid( VVB  solid ){
    VVB cp( solid[0].size(), VB( solid.size(),false ) );
    REP( i, SIZE( solid ) ){
        REP( k, SIZE(solid[i]) ){
            if( solid[i][k] ){
                cp[k][ solid.size()-1-i ] = true;
            }
        }
    }
    return cp;
}


void createAllSolids(){
  //  cout << "createAllSolids" << endl;
    REP(i, SIZE(objects) ) allSolids[i][0] = getSolid( objects[i] );
    REP( i, SIZE(objects) ){
        if( objects[i] == 'u' ) allSolids[i][1] = rotateSolid( rotateSolid( allSolids[i][0] ) );
        else REP(k, getRotations( objects[i] )-1 ) allSolids[i][k+1] = rotateSolid( allSolids[i][k] );
    }
 //   cout << "\tOut of createAllSolids" << endl;
}

void createAllSolidsBit(){
 //   cout << "createAllSolidsBit" << endl;
    REP(i, objects.size() ) REP(k,4) allSolidsBit[i][k].reset();
    REP(i, objects.size() ){
        REP(k, getRotations( objects[i] ) ){
            int width = allSolids[i][k].size();
            int height = allSolids[i][k][0].size();

            REP( x, width ){
                REP(y, height ){
                //    cout << "x = " << x << "   y = " << y << endl;
                    if( allSolids[i][k][x][y] ) allSolidsBit[i][k][ (height-1-y)*Width + x  ] = true;
                }
            }
        }
    }
 //   cout << "\tOut of createAllSolidsBit" << endl;
}


void presentAllSolids(){
    REP(i, SIZE(objects)){
        cout << objects[i] << endl;
        REP(r,getRotations( objects[i] ) ){
            cout << "\tRotation nr " << r << endl;
            drawSolid( allSolids[i][r] );
        }
        ENDL(2);
    }
}


void presentSolid( VVB solid ){
    REP(i,4){
        cout << "After " << i << " rotations it looks like" << endl;
        drawSolid(solid);
        solid = rotateSolid(solid);
        ENDL(1);
    }
}

void presentSolidBit( int nr, int rot ){
    cout << "NextSolid  nr = " << nr << "  rot = " << rot << endl;
    REP(y,Height){
        REP(x,Width){
            if( allSolidsBit[nr][rot][ y*Width + x ] ) cout << "x";
            else cout << " ";
        }
        cout << endl;
    }
}

void presentSolidBit( bitset<BITSETSIZE> bts ){
     REP(y,Height){
        cout << "\tx";
        REP(x,Width){
            if( bts[ y*Width + x ] ) cout << "x";
            else cout << " ";
        }
        cout << "x" << endl;
    }
    cout << "\t" << flush;
    REP(i,Width+2) cout << "x";
    ENDL(2);
}

void presentAllSolidsBit(){
    REP( i,SIZE(objects) ){
        REP(k, getRotations( objects[i] ) ){
            presentSolidBit( i,k );
        }
    }
    ENDL(2);
}

void presentHoleBit(){
    REP(y,Height){
        cout << "x";
        REP(x,Width){
            if( hole[ y*Width + x ] ) cout << "x";
            else cout << " ";
        }
        cout << "x" << endl;
    }

    REP( i,Width+2 ) cout << "x";
    ENDL(2);
}

bool locate( bitset<BITSETSIZE> & bts, int height ){
   // cout << "HoleState:" << endl;
 //   presentHoleBit();

    int p = 0;
    while( p <= Height - height ){
     //   presentSolidBit(bts);
        if( (hole&bts).any() ){
            break;
        }
        else{
            p++;
            bts <<= Width;
        }
    }
  //  cout << "p = " << p << endl;

    if( p == 0 ) return false;
    else{
        bts >>= Width;
        hole |= bts;
        return true;
    }
}

void undoLocate( bitset<BITSETSIZE> & bts ){
    hole &= (~bts);
}


void clearAll(){
    hole.reset();
}

void initializeAll(){

}

void readData(){
    cin >> Width >> Height >> N;
    objects = "";
    cin >> objects;
}

// checks if it can fit all gifts, starting from giftNb  into the store
bool solveRec( int giftNb ){
    if( giftNb == N ) return true;
    else{
        bitset<BITSETSIZE> temp;

        int width, height;
        REP( k, getRotations( objects[giftNb] ) ){ // dla kazdej bryly...
            width = allSolids[giftNb][k].size();
            height = allSolids[giftNb][k][0].size();

            REP( x,Width - width+1 ){ // for each point to which i can fasten my block...
                temp = allSolidsBit[giftNb][k] << x;
              //  temp <<= x;

             //   presentHoleBit();

                if( locate( temp, height ) == false ) continue;
                else{
                 //   cout << "I located my block" << endl;
                 //   cout << "F";
                    if( solveRec( giftNb+1 ) == true ) return true;
                    else undoLocate( temp );
                }

            }

        }

    }

    return false;
}

int getVolume( char t ){
    if( t == 'o' ) return 4;
    else if( t == 'l' ) return 4;
    else if( t == 'p' ) return 5;
    else if( t == 't' ) return 5;
    else if( t == 'j' ) return 4;
    else if( t == 'i' ) return 3;
    else if( t == 'u' ) return 7;
    else if( t == '.' ) return 1;
    else if( t == ':' ) return 2;
    else if( t == '4' ) return 4;
    else if( t == 'b' ) return 4;
}

bool checkSum(){
  //  cout << "checkSum" << endl;
    int sum = 0;
    REP( i, SIZE(objects) ){
        sum += getVolume( objects[i] );
    }
   // cout << "sum = " << sum << endl;
    return sum <= Width*Height;
}

void generateRandomData(){
    Height = rand()%5 + 3;
    Width = rand()%5 + 3;
    N = rand()%11 + 1;
    objects = "";
    char tab[] = { 'o','l','p','t','j','i','4',':','.','u','b' };
    REP( i,N ) objects += tab[ rand()%11 ];
}

void writeData(){
    cout << "Width = " << Width << endl << "Height = " << Height << endl << "N = " << N << endl << objects << endl;
}

void solve(){
    clearAll();
    readData();

  //  generateRandomData();
  //  writeData();

    initializeAll();

    createAllSolids();
   // presentAllSolids();

    createAllSolidsBit();
  //  presentAllSolidsBit();


  /*  REP(i,SIZE(objects)){
        cout << objects[i] << endl;
        presentSolid( getSolid( objects[i] ) );
        ENDL(2);
    }
    drawHole();*/


    if( checkSum() == false ){
        cout << "NIE" << endl;
        return;
    }

  //  cout << "LICZE" << endl;

    if( solveRec(0) ) cout << "TAK" << endl;
    else cout << "NIE" << endl;

}

int main(){
	ios_base::sync_with_stdio(0);
	srand( unsigned( time(0) ) );

   // REP(i,100000){
        solve();
  //      ENDL(1);
  //  }


	return 0;
}












