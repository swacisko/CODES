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


LL Binom( int n, int k ){
	#define Mark(x,y) for(int w=x, t=2; w>1; t++) while(!(w%t)) { w/=t; p[t]+=y;	}
	if( n < k || k < 0 ) return 0;
	int p[n+1];
	REP(x,n+1) p[x] = 0;
	//Wyznacz wartosc liczby n!/(n-k)! w postaci rozkladu na liczby pierwsze
	FOR( x,n-k+1,n ) Mark(x,1);
	//Podziel liczbe, ktorej rozklad znajduje sie w tablicy p przez k!
	FOR(x,1,k) Mark(x,-1);
	//Wylicz wartosc liczby na podstawie jej rozkladu na liczby pierwsze i 
	//zwroc wynik
	LL r = 1;
	FOR(x,1,n) while( p[x]-- ) r*=x;
	return r;	
}

// NWD euklidesem
LL GCD( LL x, LL y ){
	while(y) swap( x %= y, y );
	return x;
}

//funkcja wyznacza nwd oraz liczby l oraz k takie, ze l*a + k*b = nwd(a,b)
int GCDW( int a, int b, LL & l, LL & k ){
	if(!a){
		//gcd(0,b) = 0*0 + 1*b
		l = 0;
		k = 1;
		return b;
	}
	
	// Wyznacz rekurencyjnie wartosc najwiekszego wspolnego dzielnika oraz wspolczynniki
	// l oraz k
	
	int d = GCDW( b%a,a,k,l );
//	cout << "Przed:  a = " << a << "   b = " << b << "   l = " << l << "   k = " << k << endl;
	//zaktualizuj wartosci wspolczynikow oraz zwróæ wynik
	l -= ( b/a )*k;
//	cout << "Po:  b/a = " << b/a << "   a = " << a << "   b = " << b << "   l = " << l << "   k = " << k << endl;
	return d;
}

// Odwrotnosc modularna
// funkcja wyznacza takie x, ze a*x przystaje do 1 mod m
int RevMod( int a, int m ){
	LL x,y;
	if( GCDW(a,m,x,y)!= 1 ) return -1;
	// dokonaj przesuniecia zmiennej x, tak aby znajdowla sie w przedziale [0...m-1]
	x %= m;
	if( x<0 ) x+=m;
	return x;
}

//funkcja wyznacza rozwiazanie ukladu dwoch kongruencji
// x przyst a mod p
// x przyst b mod q
// jako c,r zwraca takie liczby, ze x przyst c mod r
// Chiñskie Twierdzenie o resztach
bool congr( int a, int b, int p, int q, int & c, int & r ){
	LL x,y;
	r = GCDW( p,q,x,y );
	//jesli liczba a nie orzystaje do b mod nwd(a,b) to nie ma rozwiazania
	if( (a-b) % r ) return 0;
	// wyznacz wartosci c i r zgodnie ze wzorami
	x = LL(a) + LL(p) * LL(b-a) / r * x;
	r = LL(p) * LL(q) / r;
	c = x%r;
	if( c < 0 ) c+=r;
	return 1;
}

// funkcja zwracajaca wartosc wyrazenia pow(a,b) mod q
// potegowanie modularne
int ExpMod( LL a, int b, int q ){
	LL p = 1;
	while( b > 0 ){
		if( b & 1 ) p = (a*p) % q;
		a = ( a * a ) % q;
		b >>= 1;
	}
	return p;
}

// sito erastotenesa, zwrocony vector na k-tej pozycji ma 1 jesli liczba k jest pierwsza
VB Sieve( int s ){
	VB V(s,1);
	V[0] = V[1] = 0;
	FOR( x,2,s ) if( V[x] && LL(s) >= LL(a)*LL(x) )
		for( int y=x*x; y<=s; y+=x ) V[y]=0;
	return V;
}

// lista liczb pierwszych
// UWAGA, to jest okolo 5 razy wolniejsze od sita, ale zzera duzo mniej pamieci
VI PrimeList( int n ){
	VI w(1,2);
	int s = 0, i = 2;
	FOR( l,3,n-1 ){
		i = 0;
		while( w[s]*w[s] <= l ) s++;
		while( i < s && l%w[i] ) i++;
		if( i == s ) w.PB(l);
	}
	return w;
}

// funkcja wyznacza liste liczb pierwszych uzywajac do tego sita Erastostenesa
VI PrimeListS( int s ){
	VB l = Sieve(++s);
	VI V;
	REP(x,s) if(l[x]) V.PB(x);
	return V;
}


// WOLNY test pierwszosci, w czasie O(  sqrt(n)  )
bool IsPrime( int n ){
	if(n==1)return 0;
	for( int x = 2; x*x <= n; x++ ){
		if(!(n%x)) return 0;
	}
	return 1;
}

// Test pierwszosci Milerem - Rabinem w czsie logarytmicznym
// funkcja przeprowadza test Millera-Rabina dla liczby x przy podstawie n
bool PWit( LL x, LL n ){
	if( x >= n ) return 0;
	LL d = 1, y;
	int t = 0, l = n-1;
	while( !( l & 1 ) ){
		++t;
		l >>= 1;
	}
	for( ; l>0 || t--; l>>=1 ){
		if( l & 1 ) d = (d*x)%n;
		if( !l ){
			x = d;
			l = -1;
		}
		y = (x*x)%n;
		// jesli test millera wykryl, ze licza nie jest pierwsza to zwroc prawde
		if( y == 1 && x != 1 && x != n-1 ) return 1;
		x = y;
	}
	
	return x != 1;
}

// funkcja sprawdza, czy dana liczba jest pierwsza. w tym celu wykonuje test millera-rabina przy podstawie 2,3,5,7
// dziala dla zakresu  do okolo 2 000 000 000
bool IsPrimeMR( LL x ){
	return !( x < 2 || PWit(2,x) || PWit(3,x) || PWit(5,x) || PWit(7,x) );
}


VI primes; // przed wywolaniem funkcji factorize nalezy wywolac primes = PrimeList(n)

// rozklada liczbe na czynniki pierwsze
VI factorize( int n ){
	int t = 0;
	VI prim;
	while( t < SIZE(primes) && primes[t] <= n ){
		if( !(n%primes[t]) ){
			prim.PB( primes[t] );
			n /= primes[t];
		}
		else t++;
	}
	if( n > 1 ) prim.PB(n);
	return prim;	
}

// funkcja zwraca w wektorze prim rozne liczby pierwsze, a w wektorze mult ilosc ich wystapienia, tzn mult[i] okresla ilosc razy jakas wystapila liczba prim[i] w rozkladzie n
void factorize( int n, VI &prim, VI &mult ){
	VI vec = factorize( n );
	int l = 1, ind = 1;
	prim.clear(); mult.clear();
	while( ind < SIZE(vec) ){
		if( vec[ind] == vec[ind-1] ) l++;
		else{
			prim.PB( vec[ind-1] );
			mult.PB( l );
			l = 1;
		}
		ind++;
	}
	prim.PB( vec[ SIZE(vec)-1 ] );
	mult.PB(l);
}

// funkcja zwraca w wektorze wszystkie mozliwe rozne iloczyny utworzone z liczb przeslanych jakos parametr ( nazwa od possible products )
VI posProducts( VI &vec ){
	set<int> myset;
	VI nums; nums.PB(vec[0]);
	myset.insert( vec[0] );
	
	FOR( i,1,SIZE(vec)-1 ){
		int t = SIZE(nums);
		REP( k,t ){
			if( myset.find( nums[k]*vec[i] ) == myset.end() ){
				myset.insert( nums[k]*vec[i] );
				nums.PB( nums[k]*vec[i] );
			}
		}
		if( myset.find( vec[i] ) == myset.end() ){
			myset.insert( vec[i] );
			nums.PB( vec[i] );
		}
	}
	sort( ALL( nums ) );
	return nums;
}

namespace FI{
	VI PrimeList( int n ){
		VI w(1,2);
		int s = 0, i = 2;
		FOR( l,3,n-1 ){
			i = 0;
			while( w[s]*w[s] <= l ) s++;
			while( i < s && l%w[i] ) i++;
			if( i == s ) w.PB(l);
		}
		return w;
	}
	
	VI primes;
	int* fi;
	
	// funkcja jako parametr przyjmuje liczbe naturalna dla ktorej chce znalezc wszystkie wartosci fi
	// jako rezultat zwraca wskaznik na tablice intow fi, taka ze fi[x] to wartosc funkcji fi eulera dla x
	int* createFi( int N ){
		primes = PrimeList( N );
		fi = new int[ N ];
		fi[1] = 1, fi[0] = 0;
		FOR( i,1,N ){
			REP(k,SIZE(primes)){
				if( i * primes[k] > N ) break;
				if( !( i % primes[k] ) ) fi[ i * primes[k] ] = primes[k] * fi[i];
				else fi[ primes[k] * i ] = fi[i] * ( primes[k] - 1 );
			}
		}
		return fi;
	}
	
	

}



int main(){
	
/*	//BINOM
	int n,k;
	while(cin >> n >> k) cout << "Binom(" << n << "," << k << ") = " << Binom(n,k) << endl;
	return 0;*/
	
/*	// GCDW
	LL l,k;
	int a,b;
	while(cin>>a>>b){
		int gcd = GCDW( a,b,l,k );
		cout << endl;
		cout << endl << "gcd("<<a<<","<<b<<") = " << GCDW(a,b,l,k);
		cout << " = " <<l<<"*"<<a<<" + " <<k<<"*"<<b<<endl;
	}
	return 0;*/
	
/*	// Odwrotnosc modularna
	int a,m;
	while(cin>>a>>m){
		cout << "Rownanie: " << a <<"*x = 1 (mod " << m << ")" << endl;
		int sol = RevMod( a,m );
		if( sol == -1 ) cout << "Brak rozwiazan" << endl;
		else cout << "x = " << sol << endl;
	}
	return 0;*/
	
	// KONGRUENCJE
/*	int a,b,p,q,c,v;
	while( cin >> a >> p >>b >> q ){
		cout << a << " (mod "<<p<<"),  " << b << " (mod "<<q<<"),  rozwiazanie: ";
		if( congr( a,b,p,q,c,v ) ) cout << c << " (mod " << v << ")" << endl;
		else cout << "Brak rozwiazan" << endl;
	}
	return 0;*/
	
/*	// Potegowanie modularne
	int a ,b ,q;
	while( cin >> a >> b >> q  ){
		cout << a << " do potegi " << b << " (mod " << q << ") = " << ExpMod(a,b,q) << endl;		
	}
	return 0;*/
	
/*	// Sito Eratostenesa
	int n;
	cin >> n;
	VB V = Sieve(n+1);
	REP(x,n) cout << x << ( V[x] ? " jest pierwsza" : " nie jest pierwsza" ) << endl;
	return 0;	*/

	// listy liczb pierwszych
/*	int n;
	cin >> n;
	VI l = PrimeListS(n);
	int count = 0;
	cout << "Lista liczb pierwszych mniejsza od " << n << ": " << endl;
	FOREACH(it,l){
		if( count++ ) cout << ", ";
		if( !(count%20) ) cout << endl;
		cout << *it;
	}
	return 0;*/
	
/*	// Test pierwszosci Millera_Rabina
	int b,e,count = 0;
	cin >> b >> e;
	while( b < e ){
		if( IsPrimeMR( b ) ) cout << b << ( !(++count % 5) ? "\n" : "\t" );
		b++;
	}
	return 0; */
	
	// Porownanie poprawnosci tstu pierwszosci 
/*	int b,e;
	cin >> b >> e;
	while( b < e ){
		bool c = IsPrime(b);
		bool d = IsPrimeMR(b);
		if( c != d ) cout << "ROZNICA!!! Liczba dla ktorej sprwadzam wartosc to: " << b << endl << "\tCzy jest pierwsza zweyklym algorytmem: " << c << endl
							<< "\tCzy jest pierwsza Millerem_Rabinem: " << d << endl;
							b++;
	}*/
	
	int c = 10000000;
	ofstream strout( "Lp.txt" );
	int t = 0;
	while( t < 4 ){
		if( IsPrimeMR( c++ ) ){
			strout << c-1 << endl;
			c *= 2;
			t++;
		}
		
	}
	
	
}

















