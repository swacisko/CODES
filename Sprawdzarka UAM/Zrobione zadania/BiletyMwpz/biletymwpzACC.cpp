//#include<cstdio>
#include<iostream>
#include<vector>
#include<string>
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

int M;
int N;
int ALL; // integer, that has 1 on position form 0 to N-1... needed to index maxxis table int proper algorithmic section...

string parseStringBit( int val ){
    string s;
    REP(i,10){
        if( val & ( 1 << i ) ) s += "1";
        else s += "0";
    }
    return s;
}

// second version, that return numbers, not ones, when bit if set to 1
string parseString( int val ){
    string s;
    REP(i,26){
        if( val & ( 1 << i ) ){
            if( i >= 10 ) s += (char)( '0' + i/10 );
            s += char( '0' + i%10 );
            s += ",";
        }
    }
 //   if( s.back() == ',' ) s.erase( s.begin() + SIZE(s)-1, s.end() );
    return s;
}

// nothing to be added...
struct Ticket{
    Ticket(){
        price = 0;
        lineTypes = 0;
        time = 0;
    }

    int price;
    int lineTypes; // lineTypes has on 2^i (i-th from the end) position 1 bit set if it can be used in i-th line type
    int time; // time, the ticket is valid after clicking...

};

// class representing a Segment- one part of the route
struct Segment{
    Segment(){
        from = to = type = 0;
    }

    int from; // beginning of time
    int to; // end of time...
    int type; // type of line i have to use in this segment...

};


vector<Ticket> tickets;
vector<Segment> segments;
VVI covering; // covering[i][j] is an integer, that has 1 on 2^k (k-th from an end) position if ticket nr i  can cover segment nr k, starting from segment nr j...
VI maxxis; // maxxis[i] is he minimum cost needed to cover segment denoted by number i in its bit representation...
VVI startFromTickets; // startFromTickets[i][k] is an integer j such that ticket nr j can cover segment i


void writeSegments(){
    cout << "Segments:" << endl;
    REP( i, SIZE( segments ) ) cout << "[" << segments[i].from << " , " << segments[i].to <<  ", " << segments[i].to - segments[i].from << ", "
        << (int) log2( segments[i].type ) << "]" << endl;
    cout << endl;
}

void writeTickets(){
    cout << "Tickets:" << endl;
    REP(i,M){
        cout << "Ticket nr " << i << ":  price = " << tickets[i].price << "  lineTypes = " << parseString( tickets[i].lineTypes )
            << "   time = " << tickets[i].time << endl;
    }
    cout << endl;
}

void writeStartFromTickets(){
    cout << "startFromTickets:" << endl;
    REP( i, N ){
        cout << "Number of tickets that can start at segment " << i << ":\t";
        REP( k, SIZE( startFromTickets[i] ) ) cout << startFromTickets[i][k] << "  ";
        cout << endl;
    }
    cout << endl;
}

void writeMaxxis(){
    cout << "Maxxis:" << endl;
    REP( i, 1<<N ){
        cout << "maxxis[" << i << "]=" << maxxis[i] << "   ";
        if( i%5 == 4 ) cout << endl;
    }
    cout << endl;
}

void writeCovering(){
    cout << "Covering:" << endl;
    REP( i, M ){
        REP( k, N ){
            cout << i << "-th ticket can cover " << parseString( covering[i][k] ) << " segment, when started at " << k << "-th segment" << endl;
        }
        cout << endl;
    }
}

void writeAll(){
    writeSegments();
    writeTickets();
    writeStartFromTickets();
  //  writeMaxxis();
    writeCovering();
}

void clearAll(){
    tickets.clear();
    segments.clear();
    covering.clear();
    maxxis.clear();
    startFromTickets.clear();
    ALL = 0;
}

void readData(){
    cin >> M;
    tickets = vector<Ticket>(M);

    int time, price, lineTypes;
    string types;
    REP(i,M){
        cin >> price >> types >> time;
        tickets[i].price = price;
        REP(k,SIZE(types)) tickets[i].lineTypes |= ( 1 << ( ( (int)types[k] ) - 'A' ) );
        if( time == 0 ) time = INF;
        tickets[i].time = time;
    } // after this loop all tickets should be read...

    cin >> N;
    segments = vector<Segment>( N );

    char type;
    int hh,mm,ss, from, to;
    char colon;
    REP(i,N){
        cin >> type >> hh >> colon >> mm >> colon >> ss;
        from = 3600*hh + 60*mm + ss;
        segments[i].type |= ( 1 << ( (int)type - 'A' ) );
        segments[i].from = from;

        cin >> hh >> colon >> mm >> colon >> ss;
        to = 3600*hh + 60*mm + ss;
        segments[i].to = to;

    }
    return;
}

void initializeAll(){
    covering = VVI( M, VI(N,0) );
    maxxis = VI( 1<<N, INF );
    startFromTickets = VVI( N );
}

void createALLVariable(){
    ALL = 0;
    REP( i,N ) ALL |= ( 1 << i );
}

void createStartFromTickets(){
  //  cout << "I enter into createStartFromTickets" << endl;

    REP(i,M){ // for each ticket...

        REP(j,N){ // for each segment...
            if( covering[i][j] > 0 ){ // if i-th ticket can cover j-th segment...
                startFromTickets[j].PB( i );
            }
        }
    }
}

// function creates covering vector...
void createCovering(){
 //   cout << "I enter createCovering" << endl;

    REP( i,M ){ // for each ticket...
        REP( j,N ){ // starting from each segment...
            if( tickets[i].lineTypes & segments[j].type ){ // if i can cover the starting point...
                int endPoint = segments[j].from + tickets[i].time;
                FOR( k,j,N-1 ){ // for all the reamaining segments...
                    if( ( tickets[i].lineTypes & segments[k].type ) > 0 && endPoint >= segments[k].to ){ // if i can ride this line and have enough time...
                        covering[i][j] |= ( 1 << ( k ) );
                    }
                }
            }
        }
    }
}

int getStartingSegment( int remaining ){
    REP(i,26) if( (remaining & (1<<i) ) > 0 ) return i;
    return -INF;
}
/*
void wait(int seconds)
{
    clock_t end = clock() + (seconds * CLOCKS_PER_SEC);
    while ( clock() < end);
}*/


// this is the recurrent part, that creates in a dynamic way the maxxis table
// remaining denotes all segments that still need to be covered... at least its bit representation does...
// return minimum value needed to cover remaining segments...
int createMaxxis( int remaining ){
  //  cout << "I am in createMaxxis, remaining = " << remaining << "  =  " << parseString( remaining ) << endl;

    if( remaining == 0 ){ // if all are covered, i can return...
     //   cout << endl;
        return 0;
    }
    else if( maxxis[remaining] != INF ){
        return maxxis[ remaining ];
    }
    else{ // else i have to check all possibilities...

        int remainingCopy = remaining; // copy of the rameining integer...
        int minval = INF; // i will look for the minimum in the cost of remaining segments...
        int currentValue;
        int ticketNr;
        int startSegment = getStartingSegment(remaining); // i should start from this segment... all previous are already covered...
     //   cout << "startSegment before REP = " << startSegment << endl;

        REP( i, SIZE( startFromTickets[startSegment] ) ){ // for each ticket, that can cover the start segment...
            ticketNr = startFromTickets[ startSegment ][i];
            currentValue = tickets[ ticketNr ].price;

            remainingCopy = remaining ; //  now it contains the segments that i need to check afterwards...
            remainingCopy &= ( ~covering[ticketNr][startSegment] );
            remainingCopy &=  ( ~ (1<<startSegment) );

        /*    cout << "remaining = " << parseString(remaining) << "  startSegment = " << startSegment << "  ticketNr = " << ticketNr
            << " cov = " << parseString( covering[ticketNr][startSegment] )
             << endl << "\tremainingCopy = " << parseString(remainingCopy) << endl;
        */


            currentValue += createMaxxis( remainingCopy );

            if( minval > currentValue ){
                minval = currentValue;
            }

          //  wait(1);

        }

        if( maxxis[remaining] > minval ) maxxis[remaining] = minval; // i assign found minimal value, not to calculate it multiple times, just to return this value later form second if

        return minval; // i return the minimal cost needed to cover remaining segments..
    }

}

void solve(){
    clearAll();
    readData();
    initializeAll();

    createALLVariable();
    createCovering();
    createStartFromTickets();

  //  writeAll();

    cout << createMaxxis( ALL );


}



int main(){
	ios_base::sync_with_stdio(0);
	//cout << fixed;
//cout.precision(2);

    solve();


	return 0;
}












