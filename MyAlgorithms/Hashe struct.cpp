//#include<stdio.h>
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
#include<time.h>
#include<string.h>
//#include<fstream>
//#include<sstream>
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
#define WRITE( V ){ FOREACH(it,V) cout << *it << ", "; cout << endl; }
#define WRITE_ALL(V,s,t) { cout << s << endl;  REP( i,SIZE(V) ){ cout  << i+1 << " ---- ";  FOREACH(it,V[i]) cout << *it+t << ", "; cout << endl;     } }
#define WRP(p) p.ST << " " << p.ND
#define CLEAR( dst,quant ) memset( dst,0, (quant)*sizeof( __typeof(*dst) ) );
#define WAR if( show_help )
#define ENDL(x) REP(crow,(x)) cout << endl;

const bool show_help = 1;
const int INF = 1000000001;
int N,M,K,a,b,c,y,t,w,l_zest;
const long double EPS = 1e-11;
typedef vector<double> VD;
typedef pair<double,int> PDI;
typedef pair<double, double> PDD;
typedef vector<bool> VB;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;

// UWAGA UWAGA!!
// dziala dobrze, ale tylko przy porownywaniu slow o dlugosci nie mniejszej niz max(10,20-MR), gdzie MR to liczba liter w alfabecie
// jesli chcemy porownywac dluzsze slowa to lepiej to robic brutem litera po iterze lub KMR(ktory moze kiedys zrobie :) )


//**********************************************************************************   HASZOWANIE      JUZ DZIALA, chyba jest dobrze
// jesli chcemy w czasie stalym porownywac, czy dane dwa teksty sa rowne, to dla kazdego z tekstu generujemy VVLL table, ktora zawierac 3 rozne
// tablice z haszami
// Do uzywania z tej przestrzeni sluza wlasciwie tylko 3 funkcje - Funkcja Start HashSpace uruchamian tylko raz na samym poczatku programu, oraz 2 funkcje
// crTable uruchamiana dla kazdego stringu oraz equals do porownywania podslow
struct Hash{
	
	static VLL P; // wektor zawierajacy rozne podstawy przy haszowaniu
	VVLL table; // table zawiera tablice numerow haszowych przy roznych podstawach, table[i] - przy podstawie P[i]
	static VVLL wyk;
	static const int MAX_L = 1000; // wartosc oznaczajac maksymalne dlugosci slowa jakie bedziemy przetwarzac
	
	static const LL AS = 29; // rozmiar alfabetu
	
	static void createPod(){
		P.clear();
	//	P.PB( 100002 ); // uwaga, tutaj liczba nie jest pierwsza, ale liczba 100001 jest
		P.PB( 200000471 );
		P.PB( 132006311 );
	//	P.PB( 400001231 );
	}
	
	// UWAGA, tutaj str musi byc zlozony tylko z malych liter, w przeciwnym razie trzeba bedzie sprawdzac wielkosc, gdy h1 == h2
	VLL HashNum( const char *str, LL x ){ // x to liczba, wzgledem ktorej modulo podajemy wynik
		int s = strlen( str );
		VLL tab( s,0 );
		
		tab[s-1] = (LL) ( (int)str[s-1] - 'a' );
		FORD( i, s-2, 0 ){
			tab[i] = AS*tab[i+1];
			tab[i] += (LL)( (int) str[i] - 'a' );
			tab[i] %= x;
		}
		return tab;
	}
	
	// funkcja tworzy tablice kolejnych poteg liczby AS mnodulo P[i]
	static void crWyk(){
		wyk = VVLL( SIZE(P) );
		VLL t(MAX_L+1,0); t[0] = 1;
		REP( i,P.size() ){
			FOR( k,1,MAX_L ){
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
		return ( ht[p] - wyk[p_nr][k-p+1]*ht[k+1]/*%P[p_nr]*/ )%P[p_nr]; // czy tu nie powinno byc abs zamiast modulo ??? ??? ??? ??		
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
	static void StartHashSpace(){
		createPod();
		crWyk();		
	}
	
};

VLL Hash::P;
VVLL Hash::wyk;

//********************************************************************************



int main(){
	
	srand( unsigned( time(0) ) );
	Hash::StartHashSpace();
	
	N = 100; // ilosc roznych slow, a takze dlugosc tych slow
	K = 500000;
	
	string s1,s2;
	string str1, str2;
	VVLL table1, table2;
	
	Hash H1;
	
	int MR = 3; // ilosc roznych liter, ktora ma byc w slowie
	
	REP( i,N ){
		MR = rand()%5 + 1;
		a = rand()%N + 2;
		b = rand()%N + 2;
		int c = min( a,b );		
		s1.clear();
		s2.clear();
		
		REP(k,a) s1 += char( 97 + rand()%MR ); // tworze losowe stringi5
		REP(k,b) s2 += char( 97 + rand()%MR );			
		
	//	cout << "Twoje stringi to:" << endl << "s1: " << s1 << endl << "s2: " << s2 << endl;
		
		table1 = H1.crTable( s1.c_str() );
		table2 = H1.crTable( s2.c_str() );
		
		REP(k,K){
			int beg1 = rand() % SIZE(s1);
			int beg2 = rand() % SIZE(s2);
			if( beg1 == SIZE(s1)-1 ) beg1--;
			if( beg2 == SIZE(s2)-1 ) beg2--;
			
			int dl1 = rand() % ( SIZE(s1) - beg1 );
			int dl2 = rand() % ( SIZE(s2) - beg2 );
			
			int dl = min( dl1, dl2 );
			if( dl == 0 ) dl++;
			
			str1 = s1.substr( beg1, dl );
			str2 = s2.substr( beg2, dl ) ;
		//	cout << "podslowo [" << beg1 << "," << beg1+dl << "] slowa s1 to: " << str1 << endl
		//		<<  "podslowo [" << beg2 << "," << beg2+dl << "] slowa s2 to: " << str2 << endl;
				
			bool the_same_hash = H1.equals( table1, beg1, beg1 + dl-1, table2, beg2, beg2 + dl-1 );
			bool the_same_comp = ( str1 == str2 );
			
			if( the_same_hash != the_same_comp && SIZE(str1) > max( 10, 20-MR ) ){
				cout << "ROZNICA!" << endl << "Stringi to:" << endl << "s1 = " << s1 << endl << "s2 = " << s2 << endl << "beg1 = " << beg1 << "    beg2 = " << beg2 << endl
					 << "dl = " << dl << endl << "substr1 = " << str1 << endl << "substr2 = " << str2 << endl;
				cout << "Wedlug hashy: " << the_same_hash << " != " << the_same_comp << " wedlug comparisona" << endl;
				ENDL(3);				
			}
				
		}	
		
	//	ENDL(3);		
		
	}
	
	
	
	
	
	
	
	
}





























