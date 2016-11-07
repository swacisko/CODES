#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

typedef vector<int> VI;
#define PB push_back

int N,M,a,b;
bool V[200][200];
VI solution;
VI globalSolution;
bool usuniety[200];

void wypiszGraf(){
	for(int i=0; i<N; i++){
		if( usuniety[i] == true ) continue;
		cout << i+1 << " --> ";
		for(int k=0;k<N; k++){
			if( V[i][k] == true && usuniety[k] == false ){
				cout << k+1 << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
}

void wypiszSasiedztwo( VI &s ){
	for( int i=0; i<s.size(); i++ ){
		cout << s[i]+1 << " ";
	}
	cout << endl;
}
 
void clearTables(){
	for( int i=0; i<N; i++ ){
		for(int k=0; k<N; k++){
			V[i][k] = false;
		}
	}
	
	globalSolution.clear();
	solution.clear();
	for( int i=0; i<N; i++ ) usuniety[i] = false;
}

void recurrence(){
//	static int petla = 0;
//	petla++;
//	if( petla >=5 ) return;
	
//	cout << "StanGrafu:" << endl;
//	wypiszGraf();
	
	int index = -1;
	for( int i=0; i<N; i++ ){
		if( V[i][i] == true && usuniety[i] == false ){
			index = i;
			break;
		}
	}
	
	
	
	if( index != -1 ){
	//	cout << "Znalazlem wierzcholek z petla: " << index+1 << endl;
		
		VI s;
		s.clear();
		
		for( int i=0; i<N; i++ ){
			if( V[index][i] == true && usuniety[index] == false ){
				s.PB(i);
			}
		}
		
	//	cout << endl << "Oto sasiedztwo wierzcholka " << index+1 << ":" << endl;
	//	wypiszSasiedztwo(s);
		
		for( int i=0; i<N; i++ ){
			if( i != index && V[index][i] == true && usuniety[ i ] == false ){
				for( int k=0; k<N; k++ ){
					if( k!=i && k != index && V[index][k] == true && usuniety[ k ] == false ){
						V[ i ][ k ] = !V[ i ][ k ];	
					//	cout << "Zero i jeden:  " <<  V[ V[index][i] ][ V[index][k] ] << " " << !V[ V[index][i] ][ V[index][k] ];
					//	cout << "i = " << i+1 << "  k = " << k+1 << endl <<  "Przed chwila V["<<i+1 << "][" << k+1 << "] = " <<	!V[ i ][ k ] 
					//		<< "  teraz	V["<<i+1 << "][" << k+1 << "] = " << V[ i ][ k ] << endl;
					}						
				}	
				
				V[ i ][ i ] = !V[ i ][ i ];	
			}
			
		}
		usuniety[index] = true;
	//	cout << "index = " << index << " usuniety[" << index << "] = " << usuniety[index] << endl;
		// dopelnienei grafu zrobione
		
	//	cout << endl << "Oto dopelnienie grafu:" << endl;
	//	wypiszGraf();
	//	cout << endl << endl << string( 50,'*' ) << endl << endl;		
		
		
		bool pusty = true;
		
		for( int i=0; i<N; i++ ){
			for(int k=0; k<N; k++){
				if( V[i][k] == true ){
					pusty = false;
					break;
				}
			}
		}
		
		if( pusty == true ) return;
		else recurrence();
		
		
		int p = 0;
		int q = 0;
		int common = 0;
		
	//	cout << "Sasiedztwo wierzcholka " << index+1 << ":" << endl << "\t";
	//	wypiszSasiedztwo( s );
		
	//	cout << endl << "Aktualne rozwiazanie:" << endl << "\t";
	//	wypiszSasiedztwo( solution );
		
		sort( solution.begin(), solution.end() );
		sort( s.begin(), s.end() );
		
		while( p < solution.size() && q < s.size() ){
			if( solution[p] == s[q] ){
				common++;
				p++;
			}
			else if( solution[p] < s[q]  ) p++;
			else q++;
		}
		
		if( common %2 == 0 ){
			solution.PB( index );
			globalSolution.PB( index );
		}
		
	//	cout << endl << "Common = " << common << endl << "Rozwiazanie po ewentualnym dodaniu:" << endl << "\t";
	//	wypiszSasiedztwo( solution );
	}
	
	return;	
}


int main(){
	ios_base::sync_with_stdio(0);
	
	int l_zest;
	
	cin >> l_zest;
	while( l_zest-- ){
		
		clearTables();
		cin >> N >> M;
		
		for( int i=0; i<M; i++ ){
			cin >> a >> b;
			
			V[a-1][b-1] = true;
			V[b-1][a-1] = true;
		}
		
		recurrence();
		
		cout << globalSolution.size() << endl;
		for( int i=0; i<globalSolution.size(); i++ ){
			cout << globalSolution[i]+1 << " ";
		}
		cout << endl;
	}
	
	
}
