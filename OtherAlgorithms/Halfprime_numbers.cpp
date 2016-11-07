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



// funkcja zwraca listę liczb, które stanowią trójkę liczb polpierwszych
// dokladniej, jezeli trojka a,a+1,a+2 jest trojka liczb, z ktorych kazda jest postaci p*q (p i q pierwsze) to w zwroconym wektorze
// bedzie wystepowala liczba a+2 (i tylko ta liczba, dla kazdej trojki zapisuje i zwracam tylko najwieksza z nich)

// jak to dziala? tworze wszystki liczby pierwsze do maxymalna/2;  nastepnie biorac wszystkie pary liczb pierwszych, ktorych iloczyn jest nie wiekszy niz maxymalna
// tworze wszystki liczby polpierwsze do zadanego zakresu. Sortuje wszystkie otrzymane liczby polpierwsze i sprawdzam, ktore z nich wystepuja trzy po sobie.
vector<int> wyznacz_trojki( int maxymalna ){
	vector<int> pierwsze = PrimeList(maxymalna); // tworze liste liczb pierwszych nie wiekszych niz polowa maksymalnej wartosci
	
	vector<int> polpierwsze;
	
	for( int i=0; i<(int)pierwsze.size(); i++ ){
		
		for( int k=i; k<(int)pierwsze.size() && (long long)pierwsze[i]*pierwsze[k] <= maxymalna; k++  ){
			
			polpierwsze.push_back( pierwsze[i] * pierwsze[k] ); // dodaje kolejna liczbe polpierwsza
			/*if( pierwsze[i] * pierwsze[k] == 5355 ){
				cout << "WTF? pierwsze[i] = " << pierwsze[i] << "   pierwsze[k] = " << pierwsze[k] << endl;
			}*/
		}
	}
	
	
	sort( polpierwsze.begin(), polpierwsze.end() ); // sortuje wszystkie otrzymane liczby polpierwsze (wszystkie sa nie wieksze niz maxymalna) od najmniejszej do najwiekszej
	
	vector<int> wynik;
	for( int i=2; i<(int)polpierwsze.size(); i++ ){
		if( (polpierwsze[i-1] == polpierwsze[i]-1) && (polpierwsze[i-2] == polpierwsze[i]-2) ){ // jezeli trzy kolejne uzyskane liczby polpierwsze sa trzema kolejnymi liczbami natuarlnymi to dodaje je do tablicy wynikowej
			wynik.push_back( polpierwsze[i] );
			
		/*	if( polpierwsze[i] == 5355 ){
				cout << "polp[i-2] = " << polpierwsze[i-2] << "  polp[i-1] = " << polpierwsze[i-1] << "   polp[i] = " << polpierwsze[i] << endl;
			}
			*/
		}		
	}
	
	return wynik;
		
}



int main(){

	cout << "Podaj maxymalna wartosc:\t";
	int maxymalna = 5000000;
	cin >> maxymalna;
	
	vector<int> wynik = wyznacz_trojki(maxymalna);
	
	for( int i=0; i<(int)wynik.size(); i++ ){
		cout << wynik[i] << endl;		
	}
	

	return 0;
}
