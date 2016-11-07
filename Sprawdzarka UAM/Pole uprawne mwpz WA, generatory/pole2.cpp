//#include<stdio.h>
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

int ILE = 0;
int N,M,K;
const int NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3;
int *AsInCol;
int *AsInRow;
int *BsInCol;
int *BsInRow;



class tile{
public:
	int x,y;
	char letter;
	bool onPath;
	
	tile* par;	
	tile * next;
	tile* tab[4];
	
	// konstruktor, celowo ustawiam letter na 'D', zeby bylo rozne od 'A' i od 'B'
	tile( int ax=-1, int ay=-1 ) : onPath(false), letter('D'), x(ax), y(ay) {
		REP(i,4) tab[i] = 0;
		par = 0;
		next = 0;
	}
	
/*	tile* operator[]( int c ){
		if( c < 0 || c > 3 ){ cout << "BLAD INDEKSOWANIA W OPERATORZE [] W STRUKTURZE TILE" << endl; return 0;		}
		return tab[c];		
	}*/
	
	void deleteTile(){
		REP( i,4 ) if( tab[i] != 0 ) tab[i]->tab[ (i+2)%4 ] = tab[ (i+2)%4 ];
	}	
	
};

void assignLetter( tile * pole ){
	if( AsInCol[pole->y] > BsInCol[pole->y] ) pole->letter = 'B';
	else pole->letter = 'A';
	if( AsInRow[pole->x] > BsInRow[pole->x] ) pole->letter = 'B';
//	else pole->letter = 'A'; 
	if( pole->next != 0 && AsInCol[pole->y] == BsInCol[pole->y] && AsInRow[pole->x] == BsInRow[pole->x] ){
		if( pole->next->letter == 'A' ) pole->letter = 'B';
		else if( pole->next->letter == 'B' ) pole->letter = 'A';
	}
	
	
	if( pole->letter == 'A' ){
		AsInCol[pole->y]++;
		AsInRow[pole->x]++;
	}
	else{
		BsInCol[pole->y]++;
		BsInRow[pole->x]++;
	}
	
WAR	REP(i,ILE) cout << "\t";
WAR	cout << "Do pola (" << pole->x << "," << pole->y << ") przypisuje litere " << pole->letter << endl;
}

// funkcja do zaznaczania rogow danego obszaru - co drugi 'A' i coi drugi 'B'
// jako parametr przyjmuje jedno z pol nalezace do obszaru
void corners( tile * pole ){
WAR	REP(i,ILE-1) cout << "\t";
WAR	cout << "Jestem w corners" << endl;

	tile * wsk = pole, *son;
	char letter = 'A';
	do{
		WAR	REP(i,ILE-1) cout << "\t";
		WAR cout << "(" << pole->x << "," << pole->y << ")" << endl;
		son = pole;
		pole = pole->par;
		if( ( son->x != pole->par->x ) && ( son->y != pole->par->y ) ){ // jesli plytka pokazywana przez wskaznik pole jest rogiem, to...
			pole->letter = letter;
			letter = ( (letter == 'A') ? 'B' : 'A' );
		}
		
	}while( pole != wsk );
	pole = wsk;
	
WAR	REP(i,ILE-1) cout << "\t";
WAR	cout << "Wychodze z corners" << endl;
}

// funkcja do przypisywanie liter polom na znalezionym obszarze, ale nie lezacym na rogu tego obszaru
// przyjmuje jako parametr jedno z pol, ktore znajduje sie na obaszarze, reszte obchodzi dzieki wksaznikowi par
void insides( tile * pole ){
WAR	REP(i,ILE-1) cout << "\t";
WAR	cout << "Jestem w insides" << endl;
	
	tile * wsk = pole, *son;
	do{		
		son = pole;
		pole = pole->par;
		if( ( son->x == pole->par->x ) || ( son->y == pole->par->y ) ){ // jesli plytka pokazywana przez wskaznik pole NIE JEST rogiem, to...
			assignLetter(pole);
		}
		
	}while( pole != wsk );
	pole = wsk;
	
WAR	REP(i,ILE-1) cout << "\t";
WAR	cout << "Wychodze z insides" << endl;
}

// funkcja sluzy do usuwania wszystkich pol znadujacych sie na danym obszarze
void deleteTiles( tile * pole ){
WAR	REP(i,ILE-1) cout << "\t";
WAR	cout << "Jestem w deleteTiles" << endl;
	
	tile * wsk = pole;
	do{
		pole = pole->par;
		pole->deleteTile();
	} while( pole != wsk );	
	pole = wsk;
	
WAR	REP(i,ILE-1) cout << "\t";
WAR	cout << "Wychodze z deleteTiles" << endl;
}



char getLetter( tile * pole ){
	tile * wsk = pole;
	int ile = 1;
	char letter = 'A';
	pole = pole->par;
	while( pole != 0 ){
		ile++;
		if( AsInCol[pole->y] > BsInCol[pole->y] ){
			letter = 'B';
			break;
		} 
		else letter = 'A';
		if( AsInRow[pole->x] > BsInRow[pole->x] ){
			letter = 'B';
			break;
		}
		pole = pole->par;
	}
	pole = wsk;
	if( ile % 2 == 0 ) letter = ( (letter == 'A')?'B':'A' );
	cout << "pole = (" << pole->x << "," << pole->y << ")   letter = " << letter << endl;
	return letter;
}




// funkcja przyjmuje wskaznik na jakies pole oraz wskaznik na kierunek, Z KTOREGO PRZYSZEDLEM do danego pola
bool dfs( tile* pole, int from ){
WAR	ILE++;
WAR	REP(i,ILE) cout << "\t";
WAR	cout << "Jestem w dfs w plytce (" << pole->x << "," << pole->y << ")    from = " << ( from == NORTH?"NORTH":( from==EAST?"EAST":(from==SOUTH?"SOUTH":"WEST") ) ) << endl;
	
	
	if( pole->letter == 'A' || pole->letter == 'B' ) return false;
	if( pole->onPath == true ){ // jesli jestem w polu, ktore jest na sciezce, to...
		corners( pole );
	//	insides( pole );
		deleteTiles( pole );
		return true;
	}
//WAR	if( pole->par != 0 ) cout << "Jestem w dfs w plytce (" << pole->x << "," << pole->y << ")   par = " << pole->par->x << "," << pole->par->y << endl;
	pole->onPath = true;
	
	int ileZer = 0; tile * parent = pole;
	REP( i,4 ) if( pole->tab[i] == 0 ) ileZer++; else parent = pole->tab[i];
	if( ileZer == 3 && parent == pole->par ){
		pole->letter = getLetter(pole);
		if( pole->letter == 'A' ){
			AsInCol[pole->y]++;
			AsInRow[pole->x]++;
		}
		else{
			BsInCol[pole->y]++;
			BsInRow[pole->x]++;
		}
		pole->deleteTile();
		return false;
	}
	
	
	REP( i,4 ){ // najpierw wywoluje dfs'y dla kazdego, w tej petli tylko dla tych pol, ktore sa pod katem prostym
		if( from > 5 || ( i != from && i != ( from+2 )%4 ) ){
			while( pole->tab[i] != 0 && (pole->tab[i]->par = pole) && ( pole->next = pole->tab[i] ) && dfs( pole->tab[i], (i+2)%4 ) ){
				if( pole->letter == 'A' || pole->letter == 'B' ){
WAR					ILE--;
					return true;
				}
			//	if( pole->tab[i] != 0 ) assignLetter(pole);
			}
		}
	}
	
WAR	REP(i,ILE) cout << "\t";
WAR	cout << "JEstem po pierwszej(prostopadlej) petli w plytce (" << pole->x << "," << pole->y << ")" << endl;
	
	REP(i,4){ // w tej petli poruszam sie dalej, w tym samym kierunku co przed chwila
		if( from > 5 || ( i == ( from + 2 ) % 4 ) ){
			while( pole->tab[i] != 0 && (pole->tab[i]->par = pole) && ( pole->next = pole->tab[i] ) && dfs( pole->tab[i], (i+2)%4 ) ){
WAR				ILE--;
				assignLetter(pole);
				return true;
			} // tutaj przechodze dalej w tym samym kierunku, wiec na pewno nie naleze do zadnego obwodu...
		}
	}
	
	
	assignLetter(pole);
	
WAR	REP(i,ILE) cout << "\t";
WAR	cout << "Jestem na koncu przed usuwaniem plytki (" << pole->x << "," << pole->y << ")    letter = " << pole->letter << endl;
	
	pole->deleteTile(); // jesli jestem na koncu sciezki, tzn nie moge isc nigdzie dalej, poza strona przeciwna do tej, z ktorej przyszedlem, toopdowiednio usuwam dana plytke...

WAR	ILE--;
	return false;
}

/*
bool check( vector<tile*> & tab ){
	AsInRow = new int[N+1];
	BsInRow = new int[N+1];
	REP(i,N+1) AsInRow[i] = BsInRow[i] = 0;
	AsInCol = new int[M+1];
	BsInCol = new int[M+1];
	REP(i,M+1) AsInCol[i] = BsInCol[i] = 0;
	REP(i,SIZE(tab)){
		if( tab[i]->letter == 'A' ){
			AsInCol[ tab[i]->y ]++;
			AsInRow[ tab[i]->x ]++;
		}
		else{
			BsInCol[ tab[i]->y ]++;
			BsInRow[ tab[i]->x ]++;
		}
	}
	
	REP( i,N+1 ) if( abs( AsInRow[i] - BsInRow[i] ) > 1 ) return false;
	REP(i,M+1) if( abs( AsInCol[i] - BsInCol[i] ) > 1 ) return false;
	REP( i, SIZE(tab) ) if( tab[i]->letter != 'A' && tab[i]->letter != 'B' ) return false;
	
	return true;
}*/


int l_zest;

void solve(){
	ILE = 0;
	vector< tile* > tab1(K);
	AsInRow = new int[N+1];
	BsInRow = new int[N+1];
	REP(i,N+1) AsInRow[i] = BsInRow[i] = 0;
	AsInCol = new int[M+1];
	BsInCol = new int[M+1];
	REP(i,M+1) AsInCol[i] = BsInCol[i] = 0;
	vector< VPII > cols(M+1), rows(N+1);
	
	int x,y;	
	REP(i,K){ // teraz tworze tablice plytek, z ktorej potem bede odczytywal literki :)
		cin >> x >> y;
		tab1[i] = new tile(x,y);
		rows[x].PB( MP( y,i ) );
		cols[y].PB( MP( x,i ) );
endall:;
	}
	
WAR	cout << "Dodalem juz wszystko do tab1 i rows i cols" << endl;
	
	REP(i,N+1) sort( ALL( rows[i] ) );
	REP(i,M+1) sort( ALL( cols[i] ) );
	
WAR	cout << "JEstem po sortowaniu" << endl;
	
	REP( i,M+1 ){
		REP( k,SIZE(cols[i]) ){
			if( k > 0 ) tab1[ cols[i][k].ND ]->tab[NORTH] = tab1[ cols[i][k-1].ND ];
			if( k < SIZE(cols[i])-1 ) tab1[ cols[i][k].ND ]->tab[SOUTH] = tab1[ cols[i][k+1].ND ];
		}
	}
	
	REP(i,N+1){
		REP( k,SIZE(rows[i]) ){
			if( k > 0 ) tab1[ rows[i][k].ND ]->tab[WEST] = tab1[ rows[i][k-1].ND ];
			if( k < SIZE(rows[i])-1 ) tab1[ rows[i][k].ND ]->tab[EAST] = tab1[ rows[i][k+1].ND ];
		}
	}
	
WAR	cout << "Stworzylem strukture. Oto ona:" << endl;
WAR	REP( i,SIZE(tab1) ){
		cout << "Oto sasiedzi plytki (" << tab1[i]->x << "," << tab1[i]->y << "):" << endl;		
		if( tab1[i]->tab[NORTH] != 0 ) cout << "\tNORTH: (" << tab1[i]->tab[NORTH]->x << "," << tab1[i]->tab[NORTH]->y << ")" << endl;
		if( tab1[i]->tab[EAST] != 0 )cout << "\tEAST: (" << tab1[i]->tab[EAST]->x << "," << tab1[i]->tab[EAST]->y << ")" << endl;
		if( tab1[i]->tab[SOUTH] != 0 )cout << "\tSOUTH: (" << tab1[i]->tab[SOUTH]->x << "," << tab1[i]->tab[SOUTH]->y << ")" << endl;
		if( tab1[i]->tab[WEST] != 0 )cout << "\tWEST: (" << tab1[i]->tab[WEST]->x << "," << tab1[i]->tab[WEST]->y << ")" << endl;
	}
	
	// po ostatnich dwoch petlach( niezagniezdzonych ) powinienem miec juz zbudowana siec sasiadow dla kazdej plytki(pola) w tablicy tab1
	
	int ind = 0;
	REP( i,SIZE(tab1) ){
		ind = 10;
		while( tab1[i]->letter != 'A' && tab1[i]->letter != 'B' ) dfs( tab1[i], ind++ );
	}
	
WAR	REP(i,SIZE(tab1)) cout << "(" << tab1[i]->x << "," << tab1[i]->y << ")" << "   " << tab1[i]->letter << endl;
//	REP( i,SIZE(tab1) ) cout<</* "(" << tab1[i]->x << "," << tab1[i]->y << ")" << "   " << */ tab1[i]->letter << endl;
	
	
	
	
}




int main(){
	ios_base::sync_with_stdio(0);
	cout << fixed;
	cout.precision(2);
	srand( unsigned( time(0) ) );
	
	cin >> l_zest;
	
	
	while(l_zest--){
		
		cin >> N >> M >> K;
		
		solve();	
		
	}
	
	
	return 0;
}












