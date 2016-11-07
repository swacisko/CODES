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



// pre[k] oznacz dlugosc najdluzszego wlasciwego prefixo-sufixu slowa    t1-t2-t3-...-tk, gdzie t1-t2-...-tn to wzorzec
// uwaga, pre jest liczone od 1 do wzo.size() a wzo to string, czyli od 0 do wzo.size()-1
void KMP( const char *str, const char *wzo, void (*fun)(int) ){ // DZIALA
	#define KMPH(z) while( k > 0 && wzo[k] != z[q] ) k = pre[k]; if( wzo[k] == z[q] ) k++;
	int pre[ strlen(wzo) + 1 ], k =0, q,m;
	pre[1] = 0;
	// wyznacz funkcje prefixowa dla zadanego wzorca
	for( q=1; wzo[q]; q++ ){
		KMPH(wzo);
		pre[q+1] = k;
	}
	
	m = q;
	k = 0;
	// dla kolejnych liter przeszukiwaneg o tekstu....
	for( q=0; str[q]; q++ ){
		// uzywajac funkcji prefixowej wyznacz dlugosc sufixu tekstu str[0...q], bedacego jednoczesnie sufixem wzorca
		KMPH(str);
		// jesli wyznaczony prefix jest dlugosci wzorca, to wywolujemy funkcje fun dla znalezionego wystapienia wzorca
		if( k == m ){
			fun( q - m + 1 );
			k = pre[k];
		}
	}	
}

void Disp( int t ){
	cout << "Znaleziono wystapienie wzorca na pozycji " << t << endl;
}


//*******************************************************************************   MINIMALNY OKRES SLOWA
// funkcja jako parametr przyjmuje tekst, a zwraca dlugosc minimalnego okresu tego slowa
int MinPeriod( const char *str ){ // DZIALA
	int pre[ strlen(str)+1 ], k = 0, q,m;
	pre[1] = 0;
	for( q=1; str[q]; q++ ){
		while( k > 0 && str[k] != str[q] ) k = pre[k];
		if( str[k] == str[q] ) k++;
		pre[q+1] = k;
	}
	
	return strlen(str) - pre[ strlen(str) ];	
}

//******************************************************************************  PROMIENIE PALINDROMOW
// funkcja wyznaczajaca promienie danego tekstu
// jesli niep == true to wylicza promienie palindromow nieparzystych, gdy p == false, to oblicza promienie palindromow parzystych
// jesli istnieje palindrom parzyssty, to podany jest jako jego srodek pierwszy index z prawej polowy, tzn dla slowa abba podany jako srodek zostanie
	// index = 2 (a=0, b=1, --> b = 2 <-- , a = 3 )
VI Manacher( const char *x, bool niep ){
	int n = strlen(x), i = 1, j = 0,k;
	VI r(n,0);
	while( i < n ){
		// dopoki kolejne litery palindromu o srodku na pozycji i sa takie same, zwieksz promien
		while( i - j > 0 && i + j + niep <= n && x[i-j-1] == x[i+j+niep] ) j++;
		r[i] = j;
		k = 1;
		// stosuja zaleznosci obliczyc jak najwiecej promieni...
		while( r[i-k] != j-k && j-k >= 0 ){
			r[i+k] = min( r[i-k], r[i]-k );
			k++;
		}
		
		j = max( 0,j-k );
		i+=k;		
	}
	return r;
}

//********************************************************************************

// ALGORYTM BAKERA - WYSZUKIWANIE WIELU WZORCOW W TEKSCIE
// do dodania wzroca sluzy funkcja       addWord( char * );
// przed rozpoczeciem wyszukiwania wzorcy trzeba stworzyc drzewo prefiksowo-sufixowe, czy wywolac funkcje       calcLink();
// do wyszukiwania wzorcy w tekscie sluza dwie funkcje      searchAll( const char*, void(*func)(int,int) )
// oraz     searchFirst( const char *, void(*func)(int,int) )   funkcja func przyjmuje jako parametry kolejno numer znalezionego wzorca oraz 
// jego pozycje w tekscie
struct mkmp{
	// struktura reprezentujaca wierzcholek w drzewie wzrocow
	struct leaf{
		// mapa son sluzy do reprezentowania krawedzi wychodzacych z wierzcholka
		map<char,leaf*> son;
		// element lnk reprezentuje wartosc funkcji prefiksowej wierzcholka, natomiast wo jest wskaznikiem na wierzcholek najdluzszego wzorca, bedacego jednoczesnie
		// sufiksem dla tekstu aktualnego wierzcholka
		leaf *lnk, *wo;
		// zmienna reprezentuje numer wzorca wierzcholka(jesli wierzcholek nie reprezentuje zadnego wzorca to jest to -1)
		int el;
		leaf() : el(-1){}
	};
	// wektor zawieracjacy dlugosci poszczegolnych wzorcow wstawionych do struktury
	VI len;
	// korzen drzewa
	leaf root;
	// pomoicnicza funkcja przetwarzajaca litere tekstu i dokonujaca odpowiedniego przejscia w drzewie
	leaf *mv( leaf * w, char l ){
		// dopoki wierzcholek nie ma syna dla litery l przesuwaj sie wzdluz funkcji prefiksowej
		while( w != &root && w->son.find(l) == w->son.end() ) w = w->lnk;
		// jesli wierzcholek w posiada syna dla litery l, to przejdz do teo wierzcholka
		if( w->son.find(l) != w->son.end() ) w = w->son[l];
		return w;
	}
	// funkcja wstawia nowy wzorzec do struktury
	int addWord( const char *s ){
		int l = strlen(s);
		leaf *p = &root;
		// Przejdz od korzenia drzewa do wierzcholka reprezentujacego caly wzorzec, ewentualnie towrzac jeszcze nie istniejace wierzcholki
		for( ; *s; ++s ){
			VAR( e,p->son.find( *s ) );
			p = ( e == p->son.end() ? p->son[*s] = new leaf : e->second );
		}
		// jezeli aktualny wierzcholek nie reprezentuje jezcze zadnego wzorca to przypisz mu nowy identyfikator i zapamietaj jego dlugosc
		if( p->el == -1 ){
			p->el = SIZE(len);
			len.PB(l);
		}
		// zwroc identyfikator wzroca
		return p->el;
	}
	// funkcja wyznacza funkcje prefiksowa dla wierzcholkow drzewa. Wylicza ona rowniez wartosci pol wo
	void calcLink(){
		// wektor l jest uzywany jako kolejka dla przeszukiwania drzewa metoda BFS
		vector<leaf*> l;
		leaf *w;
		root.lnk = root.wo = 0;
		// wstaw do kolejki wzystkich synow korzenia oraz ustaw ich funkcje prefiksowa na korzen
		FOREACH(it,root.son){
			l.PB( it->ND );
			it->ND->lnk = &root;
		}
		// dla wszystkich elementow z kolejki...
		REP(x, SIZE(l) ){
			// wyliczenie pola wo - jego wartosc to wierzcholek wskazywany przez funkcje prefiksowa(jesli reprezentuja on wzorzec), lub w przeciwnym
			// wypadku wartosc pola wo tego wierzcholka
			l[x]->wo = ( l[x]->lnk->el != -1 ) ? l[x]->lnk : l[x]->lnk->wo;
			// dla kazdego syna aktualnego wierzcholka(litere prowadzaca do syna reprezentuje it->ST) ...
			FOREACH( it,l[x]->son ){
				l.PB(it->ND);
				//wyznaczanie wartosci funkcji prefiksowej
				w = l[x]->lnk;
				// dokonaj przejscia z wierzcholka w
				w = mv( w,it->ST );
				// ustaw wierzcholek jako wartosc funkcji prefiksowej
				it->ND->lnk = w;
			}
		}
	}
	// funkcja wyszukuje wszystkie wystapienia wzorcow w zadanym tekscie i dla kazdego znalezionego wystapnienia wywoluje funkcje func
	void searchAll( const char *s, void(*func)(int,int) ){
		leaf *p = &root;
		// dla kazdej kolejnej litery przeszukiwanego tekstu...
		for( int x=0; s[x]; ++x ){
			//dokonaj przejscia dla litery s[x]
			p = mv( p,s[x] );
			// jesli aktualny wierzcholek(lub pewne jeg osufiksy) reprezentuja wzorzec, to wywolaj dla nich funkcje func
			for( VAR(r,p); r; r = r->wo )
			if( r->el != -1 ) func( x - len[r->el] + 1, r->el );
		}
	}
	
	// funkcja wyszukuje pierwsze wystapienie kazdego ze wzrocow w zadanym tekscie i dla kazdego znlezionego wystapienia wywoluje funkcje func
	void searchFirst( const char *s, void(*func)(int,int) ){
		leaf *p = &root, *r, *t;
		// dla kazdej kolejnej litery przesukiwanego tekstu...
		for( int x=0; s[x]; ++x ){
			// dokonaj przejscia dla litery s[x]
			p = mv( p,s[x] );
			// wywolaj funkcje func dla wszystkich znalezionych wzorcow ora usun informacje o tych wzrocach aby nie zostaly znalezione ponownie
			r = p;
			while(r){
				// jesli wierzcholek reprezentuje wzorzec, to wywolaj funkcje func
				if( r->el != -1 ) func( x - len[r->el] + 1, r->el );
				// usun identyfikator wzorca, aby nie zostal znaleziony po raz kolejny
				r->el = -1;
				// przejdz do kolejnego wzorca i wyzeruj licznik wo, aby nie wykonywac tego ruchu w przyszlosci
				t = r;
				r = r->wo;
				t->wo = 0;
			}
		}
	}	
};

void DispMkmp( int x, int p ){
	cout << "Znaleziono wzorzec " << x << " na pozycji " << p << endl;
}

//******************************************************************************  DRZEWO SUFIKSOWE

template<typename _T> struct SufTree{
	struct SufV{
		map<char,SufV*> sons;
		int p,k;
		bool s;
		_T e;
		SufV *par;
		SufV( int p, int k, SufV *par, bool s ) : p(p), k(k), par(par), s(s){}
		~SufV(){
			FOREACH(it,sons) delete it->second;
		}
	};	
	
	struct VlP{
		SufV *p;
		char l;
		VlP( SufV *p, char l ) : p(p), l(l) {}
		bool operator<( const VlP &a ) const{
			return (a.p > p) || ( a.p == p && a.l > l );
		}
	};
	
	SufV root;
	string text;
	SufTree( const string& t ) : root(0,0,0,0), text(t){
		map<VlP,SufV*> lnk;
		set<VlP> test;
		int len = t.length();
		SufV *v = root.sons[ t[len-1] ] = new SufV( len-1,len,&root,1 );
		lnk[ VlP(&root,t[len-1]) ] = v;
		test.insert( VlP( &root, t[len-1] ) );
		FORD( i,len-2 ,0){
			char a = t[i];
			if( !root.sons[a] ){
				SufV *it = v;
				while(it){
					test.insert( VlP(it,a) );
					it = it->par;
				}
				it = v;
				lnk[ VlP(it,a) ] = v = root.sons[t[i]] = new SufV( i,len,&root,1 );
			}
			else{
				char lw;
				SufV *head, *head2, *x, *x1;
				int lw2 = 0, gl = 0;
				for( x = v; x != &root && test.find( VlP(x,a) ) == test.end(); x = x->par ) lw2 += x->k - x->p;
				for( x1 = x; x1 && !lnk[VlP(x1,a)]; x1 = x1->par ){
					 gl += x1->k - x1->p;
					 lw = t[x1->p];
				}
				if( x1 ) gl--;
				SufV *head1 = x1 ? lnk[VlP(x1,a)] : &root;
				if( x == x1 ) head = head1;
				else{
					head2 = (!x1) ? root.sons[a] : head1->sons[lw];
					head = head1->sons[t[head2->p]] = new SufV( head2->p, head2->p + 1 + gl, head1, 0 );
					head->sons[t[head->k]] = head2;
					head2->p = head->k;
					head2->par = head;
					for( VAR(it, test.lower_bound( VlP(head2,0))); it->p == head2; ) test.insert( VlP(head,(it++)->l) );
				}
				for( SufV *it = v; it!=x1; it = it->par ) test.insert( VlP(it,a) );
				lnk[VlP(x,a)] = head;
				SufV *v1 = v;
				v = head->sons[t[len-lw2]] = new SufV( len-lw2, len,head,1 );
				lnk[VlP(v1,a)] = v;
			}
		}		
	}	
};

// ************* liczba wystapien wzorca w tekscie
// orzed zliczaniem nalezy wywolac ponizsza funkcje
int STSuffixC( SufTree<int>::SufV& v ){
	v.e = v.s;
	FOREACH(it,v.sons) v.e += STSuffixC( *(it->second) );
	return v.e;
}
// funkcja jako parametr przyjmuje drzewo sufiksowe reprezentujace tekst i wzorzec, a zwraca ilosc wystapien wzorca w danym tekscie
int STFindCount( SufTree<int> &st, const char *t ){
	int tp = 0, x;
	VAR( v, &(st.root) );
	while( t[tp] ){
		if( !( v = v->sons[t[tp]] ) ) return 0;
		for( x = v->p; x < v->k && t[tp]; )
		if( t[tp++] != st.text[x++] ) return 0;
	}
	return v->e;
}


//************** liczba roznych podslow slowa
// funkcja wyznacza liczbe roznych podslow w tekscie poprzez zliczanie dlugosci krawedzi w drzewie sufiksowym
int STSubWords( SufTree<int>::SufV & v ){
	int r = v.k - v.p;
	FOREACH( it,v.sons ) r+= STSubWords( *(it->second) );
	return r;
}

// *************najdluzsze podslowo wystepujace n razy
// do konstruktora nalezy przekazac tekst t oraz liczbe n. Wyznaczone najdluzsze podslowo mozna odczytac z pol p oraz k oznaczajacych odpowiednio
// poczatek i koniec podslowa tekstu t
struct STLongestWord{
	int p,k,c;
	int Find( SufTree<int>::SufV & v, int d ){
		d += v.k - v.p;
		v.e = v.s;
		FOREACH(it,v.sons) v.e += Find( *(it->ND),d );
		if( v.e >= c && d > k-p ){
			k = v.k;
			p = v.k - d;
		}
		return v.e;
	}
	
	STLongestWord( const string & t, int c ) : p(0), k(0), c(c){
		SufTree<int> tr(t);
		Find(tr.root, 0);
	}	
};

// ***************************************************************************** maxymalny leksykograficznie sufiks, algorytm Duvala
// funkcja zwraca indeks poczatku maxymalnego leksykograficznie sufiksu
int maxSuf( const char *x ){
	int i=0, j=1, k=1, p=1;
	char a,b;
	while( x[j+k-1] ){
		if( ( a = x[i+k-1] ) < ( b = x[j+k-1] ) ){
			i = j++;
			k = p = 1;
		} else if( a > b ){
			j += k;
			k = 1;
			p = j - i;
		} else if( a == b && k != p ) k++;
		else{
			j += p;
			k = 1;
		}
	}
	return i;
}

//***************************************************************************** rownowaznosc cykliczna
// slowa s1,s2,s3,...,sn oraz t1,t2,...,tn sa rownowazne cyklicznie, jezeli dla pewnego k zachodzi sk,sk+1,...,sn,s1,s2,...,sk-1 = t1,t2,...,tn
// funkcja sprawdza, czy dane dwa teksty sa swoimi rownowaznosciami cyklicznymi
bool cycEq( const char *s1, const char *s2 ){
	int n = strlen(s1), i=0, j=0, k=0;
	if( n != strlen(s2) ) return 0;
	while( i < n && j < n && k < n ){
		k = 1;
		while( k <= n && s1[ (i+k)%n ] == s2[ (j+k)%n ] ) k++;
		if( k <= n ) if( s1[ (i+k)%n ] > s2[ (j+k)%n ] ) i += k;
		else j += k;
	}
	return k > n;
}

// *************************************************************************** minimalna leksykograficzne cyklicznosc slowa
// funkcja jako rezultat zwraca numer pierwszej litery, rozpoczynajacej minimalna leksykograficznie cyklicznosc slowa
// ta funkcja to jest prawie to samo co znajdywanie maxymalnego sufiksu slowa, tylko zamiat "<"  mamy  ">"  i bierzemy modulo strlen(x)
int minLexCyc( const char *x ){
	int i = 0, j = 1, k = 1, p = 1,a,b,l = strlen(x);
	while( j + k <= (l << 1) ){
		if( (a = x[ (i+k-1)%l ]) > (b = x[ (j+k-1)%l ]) ){
			i = j++;
			k = p = 1;
		} else if( a < b ){
			j += k;
			k = 1;
			p = j - i;
		} else if( a == b && k != p ) k++;
		else{
			j += p;
			k = 1;
		}	
	}
	return i;
}

int main(){
	
/*	// Algorytm KMP
	string pattern, text;
	cin >> text >> pattern;
	cout << "Wyszukiwanie " << pattern << " w tekscie " << text << endl;
	KMP( text.c_str(), pattern.c_str(),&Disp );*/
	
	
	
/*	// Minimalny okres slowa
	string text;
	while( cin >> text ){
		int t = MinPeriod( text.c_str() );
		cout << "Minimalny okres slowa " << text << " to " << text.substr( 0,t ) << endl;
	}*/
	
	
	
/*	// MANACHER
	string text;
	cin >> text;
	cout << "Analizowany tekst: " << text << endl;
	VI res  = Manacher( text.c_str(), 0 );
	cout << "Palindromy parzyste: ";
	FOREACH(it,res) cout << *it << " ";
	cout << endl;
	cout << "Palindromy nieparzyste: ";
	res = Manacher( text.c_str(), 1 );
	FOREACH(it,res) cout << *it << " ";
	cout << endl;*/
	
	
	
/*	// ALGORYTM BAKERA - wyszukiwanie wielu wzorcow wtekscie	
	mkmp search;
	string text;
	int n;
	cin >> n; // wczytaj liczbe wzrocow
	REP(x,n){
		cin >> text;
		cout << "Dodawanie wzorca " << text << endl;
		search.addWord( text.c_str() );
	}
	
	search.calcLink(); // wyznaczamy funkcje prefiksowa
	cin >> text;
	cout << "Przeszukiwanie tekstu " << text << endl;
	search.searchAll( text.c_str(), &DispMkmp );
	return 0;*/
	
	
	
	
	
	
	// Drzewo SUFIKSOWE i funkcje drzewa sufiksowego
	
/*	//liczba wystapien wzorca w tekscie
	string text;
	cin >> text;
	cout << "Przeszukiwany tekst: " << text << endl;
	SufTree<int> tree( text.c_str() );
	STSuffixC( tree.root );
	while( cin >> text ) cout << "Wzorzec: " << text << " wsytepuje " << STFindCount( tree, text.c_str() ) << " razy" << endl;
	return 0;*/
	
	
	
	
/*	// liczba roznych podslow slowa
	string text;
	while( cin >> text ){
		SufTree<int> tree(text);
		cout << text << " ma " << STSubWords(tree.root) << " podslow" << endl;
	}*/
	
	
	
	
/*	// najdluzse podslowo wystepujace n razy
	string text;
	int n;
	while( cin >> text >> n ){
		STLongestWord str( text,n );
		cout << "Podslowo slowa " << text << " wystepujace " << n << " razy: " << endl << text.substr( str.p, str.k - str.p ) << endl;
	}
	return 0;*/
	
	
	
	
/*	// Maksymalny leksykograficznie sufiks
	string text;
	while(cin >> text){
		cout << "Maksymalny leksykograficznie sufiks slowa " << text << " = " << text.substr( maxSuf( text.c_str() ) ) << endl;
	}*/;
	
	
	
	
/*	// rownowaznosc cykliczna
	int n; // liczba tekstow
	cin >> n;
	vector<string> text(n);
	REP(x,n) cin >> text[x];
	REP(x,n) REP(y,x) cout << "Slowa " << text[x] << " oraz " << text[y] << ( cycEq( text[x].c_str(), text[y].c_str() ) ? "" : " nie" ) <<
						" sa rownowazne cyklicznie" << endl;
						return 0;*/
						
						
						
						
	
	// Minimalna leksykograficznie syklicznosc slowa
	string text;
	while( cin >> text ){
		int res = minLexCyc( text.c_str() );
		cout << "Minimalna rownowazcnosc cykliczna " << text << " = " << text.substr( res, text.length()-res ) << text.substr(0,res) << endl;
	}
	
	
	
}













