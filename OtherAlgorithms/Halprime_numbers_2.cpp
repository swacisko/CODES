#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;



// funkcja zwraca listę wszystckih liczb pierwszych nie większych niz N
// zwrocona lista to wlasciwie nie jest lista tylko wektor
// vector<int> w      to dynamiczna tablica, ma w.size() elementow, do tablicy mozna dodac dowolny_element typu int poprzez w.push_back(dowolny_element)
vector<int> PrimeList( int N ){
	vector<int> w(1,2);
	int s = 0, i = 2;
	for(int l=3; l<= N-1; l++ ){
		i = 0;
		while( w[s]*w[s] <= l ) s++;
		while( i < s && l%w[i] ) i++;
		if( i == s ) w.push_back(l); // dodaje l do tablicy w jako kolejna znaleziona liczbe pierwsza
	}
	return w;
}


// Test pierwszosci Milerem - Rabinem w czsie logarytmicznym
// funkcja przeprowadza test Millera-Rabina dla liczby x przy podstawie n
bool PWit( long long x, long long n ){
	if( x >= n ) return 0;
	long long d = 1, y;
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
bool IsPrimeMR( long long x ){
	return !( x < 2 || PWit(2,x) || PWit(3,x) || PWit(5,x) || PWit(7,x) );
}



vector<int> primes;


bool sprawdz( int n ){
	int t = 0;
	for( int i=n-2; i<=n; i++ ){		
		t = 0;
		if( IsPrimeMR(i) ) return false;
		while( t < (int)primes.size() && primes[t]*primes[t] <= i ){
			if( (i % primes[t]) == 0 ){
			/*	if( n == 5355 ){
					cout << "n = 5355, i = " << i << "  primes[t] = " << primes[t] << "    i / primes[t] = " << i / primes[t] << endl;
					cout << "IsPrimeMR(" << i / primes[t] << ") = " << IsPrimeMR( i / primes[t] ) << endl;
				}*/
					
				if( IsPrimeMR( i / primes[t] ) == false ) {
					
					return false;
				}
				break;
			}
			t++;
		}
		
	}
	
	return true;
}


void wyznacz_trojki( int maxymalna ){
	
	for( int i=3; i<=maxymalna; i++ ){
		if( sprawdz(i) == true ){
			//cout << "Trojka (" << i-2 << "," << i-1 << "," << i << ") spelania warunki" << endl;
			cout << i << endl;
		}
		
	}
	
	//cout << endl;
	
	
	
	
	
}



int main(){

	cout << "Podaj maxymalna wartosc:\t";
	int maxymalna = 5000000;
	cin >> maxymalna;
	
	primes = PrimeList( maxymalna );
	
	wyznacz_trojki(maxymalna); // tutaj funkcja wypisuje na biezaco liczby, nie przetrzymuje ich w wektorze - widac na biezaco kolejne pojawiajace sie wyniki
	// ta wersja powinna dzialac zdecydowanie szybciej niz poprzednia
	

	return 0;
}
