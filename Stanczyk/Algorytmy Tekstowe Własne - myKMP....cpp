#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<complex>
#include<stack>
#include<list>
#include<set>
#include<bitset>
#include<set>
#include<iterator>
#include<cmath>
#include<queue>
#include<time.h>
#include<string.h>
#include<fstream>
#include<sstream>
#include<algorithm>

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
#define WRITE( V ) FOREACH(it,V) cout << *it << ", "; cout << endl;
#define WRITE_ALL(V,s)  cout << s << endl;  REP( i,SIZE(V) ){ cout << "i = " << i << endl;  FOREACH(it,V[i]) cout << *it << ", "; cout << endl;     }
#define WRP(p) p.ST << " " << p.ND 

const int INF = 1000000001;
int N,M,K,a,b,c,y,t,w,l_zest;
const long double EPS = 1e-11;
typedef vector<long double> VD;
typedef pair<long double,int> PDI;
typedef pair<long double, long double> PDD;
typedef vector<bool> VB;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef map< PII, bool > MPIIB;
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;


//****************************************************************************** W£ASNY KMP DLA STRINGOW ORAZ WERSJA DLA DOWOLNYCH STRUKTUR

void myKMP( string & text, string & wzo, VI & wyst ){
	wyst.clear(); // czyszcze tablice wystapien wzorca w tekscie
	string str = wzo + "%" + text; // uwaga, tu musi byc znak, ktory nie wystepuje w zadnym ze stringow    wzo, ani text
	int *pref = new int[ SIZE(str)+1 ];
	int k = 0; pref[1] = 0;
	FOR( i,1,SIZE(str)-1 ){
		while( k > 0 && str[k] != str[i] )	k = pref[k];
		if( str[k] == str[i] ) k++;
		pref[i+1] = k;
		if( i > SIZE(wzo) && k == SIZE(wzo) )	wyst.PB( i - 2*SIZE(wzo) );		
	}
	delete[]pref;
}


// *****************************************************************************
// w³asny KMP dal dwolonych struktur

template<class typ>
bool equals( typ a, typ b ){
	if( a == 0 || b == 0 ) return 0;
	return *a == *b;
}

template<class typ>
void myKMP( vector<typ> & text, vector<typ> & wzo, VI & wyst ){
	wyst.clear(); // czyszzcze tablice wystapien wzroca w tekscie
	vector<typ*> str; // tworze wektor wskaznikow, aby moc dodac element '%', czyli inny od wszystkich. Poniewaz nie wiem jaki to typ, wiec nie moge stworzyc takiego elementu, moge co najwyzej wskaznik na null
	REP( i,SIZE(wzo) ) str.PB( &wzo[i] );
	str.PB(0);
	REP(i,SIZE(text)) str.PB( &text[i] );
	
	int *pref = new int[ SIZE(str)+1 ];
	int k = 0; pref[1] = 0;
	FOR( i,1,SIZE(str)-1 ){
		while( k > 0 && !equals( str[k], str[i] ) )	k = pref[k];
		if( equals( str[k], str[i] ) ) k++;
		pref[i+1] = k;
		if( i > SIZE(wzo) && k == SIZE(wzo) )	wyst.PB( i - 2*SIZE(wzo) );		
	}
	delete[]pref;
}



// UWAGA     UWAGA    UWAGA
// ta strukture lepiej czerpac z pliku      wlasne_algorytmy/"testowanie_haszy.cpp"

//**********************************************************************************   HASZOWANIE      JUZ DZIALA, chyba jest dobrze
// jesli chcemy w czasie stalym porownywac, czy dane dwa teksty sa rowne, to dla kazdego z tekstu generujemy VVLL table, ktora zawierac 3 rozne
// tablice z haszami
// Do uzywania z tej przestrzeni sluza wlasciwie tylko 3 funkcje - Funkcja Start HashSpace uruchamian tylko raz na samym poczatku programu, oraz 2 funkcje
// crTable uruchamiana dla kazdego stringu oraz equals do porownywania podslow
namespace Hash{
	
	VLL P; // wektor zawierajacy rozne podstawy przy haszowaniu
	VVLL table; // table zawiera tablice numerow haszowych przy roznych podstawach, table[i] - przy podstawie P[i]
	VVLL wyk;
	const int MAX_L = 1000; // wartosc oznaczajac maksymalne dlugosci slowa jakie bedziemy przetwarzac
	
	int AS = 30; // rozmiar alfabetu
	
	void createPod(){
		P.clear();
	//	P.PB( 100002 ); // uwaga, tutaj liczba nie jest pierwsza, ale liczba 100001 jest
		P.PB( 200000471 );
		P.PB( 132006311 );
		P.PB( 400001231 );
	}
	
	// UWAGA, tutaj str musi byc zlozony tylko z malych liter, w przeciwnym razie trzeba bedzie sprawdzac wielkosc, gdy h1 == h2
	VLL HashNum( const char *str, int x ){ // x to liczba, wzgledem ktorej modulo podajemy wynik
		int s = strlen( str );
		VLL tab( s,0 );
		
		tab[s-1] = (int)str[s-1] - 'a';
		FORD( i, s-2, 0 ){
			tab[i] = AS*tab[i+1];
			tab[i] += (int) str[i] - 'a';
			tab[i] %= x;
		}
		return tab;
	}
	
	// funkcja tworzy tablice kolejnych poteg liczby AS mnodulo P[i]
	void crWyk( int size ){
		wyk = VVLL( SIZE(P) );
		VLL t(size+1,0); t[0] = 1;
		REP( i,P.size() ){
			FOR( k,1,size ){
				t[k] = t[k-1]*AS;
				t[k] %= P[i];
			}
			wyk[i] = t;
		}
	}
	
	LL getValue( VLL &ht, int p, int k, int p_nr ){
		if( k == SIZE(ht)-1 ) return ht[p]; // jesli k jest ostatnia litera slowa
	//	cout << endl << "\t ht["<<p<<"] = " << ht[p] << " ht["<<k+1<<"] = " << ht[k+1] << "  wyk["<<p_nr<<"]["<<k-p+1<<"] = " << wyk[p_nr][k-p+1] << "  P["<<p_nr<<"] = " << P[p_nr] << endl;
	//	cout << " \t ----> " << ( ht[p] - wyk[p_nr][k-p+1]*ht[k+1] ) % P[p_nr] << endl;
		return ( ht[p] - wyk[p_nr][k-p+1]*ht[k+1]%P[p_nr] );//&P[p_nr]; // czy tu nie powinno byc abs zamiast modulo ??? ??? ??? ??		
	}
	
	// funkcja sprawdzajaca, czy dwa slowa(podslowa) sa takie same... jakos ht1 i ht2 przesylamy tablice haszujace obu GLOWNYCH stringow, jako p1,p2,k1,k2
	// poczatki i konce podslow, ktore chcemy sprawdzic, k to konce podslow, liczone wlacznie!
	// p_nr oznacza numer podstawy z tablicy P, czyli od 0 do 3, jesli tablica P ma 4 elementy
	bool equals( VVLL & ht1, int p1, int k1, VVLL &ht2, int p2, int k2 ){
		REP( i,SIZE(P) ){
			if( getValue( ht1[i], p1,k1,i ) != getValue( ht2[i],p2,k2,i ) ){
			//	cout << "ROZNICA w wartosciach, dla ht1 jest to " << getValue( ht1[i], p1,k1,i ) 
			//			<< endl << "\t\t a dla ht2 jest to " << getValue( ht2[i],p2,k2,i ) << endl;
				return false;
			}
		}
		return true;
	}
	
	// dla danego tekstu ta funkcja zwraca 3 rozne tablice z haszami, wystarczy 
	VVLL crTable( const char *str ){
		table = VVLL( SIZE(P) );
		REP( i,P.size() ) table[i] = HashNum( str, P[i] );
		return table;
	}
	
	// ta funkcje wywolujemy, aby wypelnic podstawowe tablice
	void StartHashSpace(){
		createPod();
		crWyk( MAX_L );		
	}
	
};

//********************************************************************************





int main(){
	
	
	// myKMP
	while(true){
		cout << "Podaj tekst: ";
		string text;
		cin >> text;
		cout << endl << "Podaj wzorzec: ";
		string wzorzec;
		cin >> wzorzec;
		VI wyst;
		myKMP( text, wzorzec, wyst );
		cout << "Slowo " << wzorzec << " wystepuje w tekscie " << text << " na pozycjach: ";
		WRITE(wyst);
		cout << endl << endl << endl;
	}
	
	
	
	
	
	
	
	
	
	
	// WLASNE HASZOWANIE	
	Hash::StartHashSpace();
	string s1,s2;
	while( cin >> s1 >> s2 ){
		VVLL h1 = Hash::crTable( s1.c_str() );
		VVLL h2 = Hash::crTable( s2.c_str() );
		
	/*	cout << "Wartosci haszujace dla h1 to: ";	REP( k, h1.size() ) {
			REP(i,h1[k].size() ) cout << h1[k][i] << " ";
			cout << endl;
		}
		cout << endl << endl << "Wartosci hasuzjace dla h2 to: "; REP(k,h2.size()){
			REP(i,h2[k].size()) cout << h2[k][i] << " ";
			cout << endl;			
		}
		cout << endl;*/
		
		cout << "W podanych tekstach podslowa zaczynajace sie na pozycji 0 a konczace na pozycji " << s1.size()-1 << " oraz " << s2.size()-1 << " sa" << endl;
		if( Hash::equals( h1,0,s1.size()-1,h2,0,s2.size()-1 ) ) cout << "\tTAKIE SAME" << endl;
		else cout << "\tROZNE" << endl;
	}
	
	
	
	
}













