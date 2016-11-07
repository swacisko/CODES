#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<algorithm>

using namespace std;

#define REP( x,y ) for( int x=0; x<y; x++ )
#define PB push_back
#define PH push_heap
#define POP pop_back
#define MP make_pair

int N,M,a,b;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;


VVI g;
VVI induced;
VI upper;
VI bottom;
VI path;
bool tab[100010]; // sprawdzenie, czy krawedz dzieli drzewo na 2 poddrzewa, z ktorych kazdy zawiera wierzcholek stopnia conajmniej 3
bool tab2[100010];
bool tab3[100010];
int ile[100010];
bool isOnPath[100010];

void clearAll(){
	g.clear();
	induced.clear();
	upper.clear();
	bottom.clear();
	path.clear();
	
	REP(i,N) tab2[i] = false;
	REP(i,N) tab[i] = false;
	REP(i,N) tab3[i] = false;
	REP(i,N) isOnPath[i] = false;
	REP(i,N)ile[i] = 0;
	
	REP(i,N) g.PB( VI());
	REP(i,N) induced.PB( VI());
}


void backDFS( int index, int parent ){
//	cout << "Jestem w backDFS, index = " << index+1 << "  parent = " << parent+1 << endl;
	REP( i,g[index].size() ){
		if( g[index][i] != parent ){
			backDFS( g[index][i], index );
		}
	}
	
	int il = 0;
//	if( index != parent ){
		
		REP( i,g[index].size() ){
			if( g[index][i] != parent && ( tab[ g[index][i] ] == true || g[ g[index][i] ].size() >= 3 ) ){
				tab[index] = true;
			}
			
			if( g[index][i] != parent && tab[ g[index][i] ] == true ) il++;
		}
//	}
	
	ile[index] = il;
	
	if( g[index].size() >= 4 ) tab[index] = true;
}

void forDFS( int index, int parent ){
	if( index != parent ){		
		if( tab2[parent] == true || g[parent].size() >= 3 ) {
			tab2[index] = true;
			ile[ index ]++;
		}
	}
	
	if( g[index].size() >= 4 ) tab2[index] = true;
	
	
	REP( i,g[index].size() ){
		if( g[index][i] != parent ){
			forDFS( g[index][i], index );
		}
	}
	
	
}

void scalTab( int index, int parent ){
	if( parent != index ){
		if( ( tab2[parent] == true || ile[parent] >= 2 ) && tab[index] == true ){
			tab3[parent] = true;
			tab3[index] = true;
		}
		
		REP(i, g[index].size()){
			if( g[index][i] != parent ){
				scalTab( g[index][i], index );
			}
		}
		
	}
	else{
		REP(i,g[index].size()){
			scalTab( g[index][i], index );
		}
	}
}

void forwardDFS( int index, int parent ){ // tutaj takze wyznaczam graph indukowany
	if( index != parent ){
	//	cout << "index = " << index+1 << "   parent = " << parent+1 << endl;
		if( tab3[parent] == true && tab3[index] == true ){
			induced[index].PB(parent);
			induced[parent].PB(index);
			
			REP( i,g[index].size() ){
				if( g[index][i] != parent && tab3[ g[index][i] ] == true ){
					forwardDFS( g[index][i], index );
				}
			}		
		}
		else{
			REP( i, g[index].size() ){
				if( g[index][i] != parent ) forwardDFS( g[index][i], index );
			}
		}	
	}
	else{
		REP( i, g[index].size() ){
			forwardDFS( g[index][i], index );
		}
	}	
}


void writeGraph( VVI &v ){
	cout << endl;
	REP( i, v.size() ){
		cout << i+1 << ":  ";
		REP( k, v[i].size() ){
			cout << v[i][k]+1 << " ";
		}
		cout << endl;
	}
}

void writePathBack( int index, int parent ){ // wszystkie wierzcholki dodajemy do bottom
//	cout << "Jestem w writePathBack, index = " << index+1 << "  parent = " << parent+1 << "  g["<<index+1<<"].size() = " << g[index].size() << endl;
	
	REP( i,g[index].size() ){
		if( g[index][i] != parent && ( isOnPath[ g[index][i] ] == false ) ){
			writePathBack( g[index][i], index );
		}
	}
	
	bottom.PB( index );
	isOnPath[index] = true; // w tym przypadku tablica isOnPath pelni funkcje ifWas, oznacza tylko, ze do niektorych wierzcholkow nie mamy wchodzic
}

void writePathForward( int index, int parent ){ // wszystkie wierzcholki dodajemy do bottom
//	cout << "Jestem w writePathForward, index = " << index+1 << "  parent = " << parent+1 << "  g["<<index+1<<"].size() = " << g[index].size() << endl;

	bottom.PB(index);
	isOnPath[index] = true; // w tym przypadku tablica isOnPath pelni funkcje ifWas, oznacza tylko, ze do niektorych wierzcholkow nie mamy wchodzic
	
	REP( i,g[index].size() ){
		if( g[index][i] != parent && ( isOnPath[ g[index][i] ] == false ) ){
			writePathForward( g[index][i], index );
		}
	}
}

void writePaths( int index, int parent ){
//	cout << endl << endl << "Jestem w writePaths, index = " << index+1 << "  parent = " << parent+1 << "  g["<<index+1<<"].size() = " << g[index].size() << endl << endl;
	if( g[index].size() == 3 ){
		int a = -1, b = -1; // a oraz b to numery dwoch sasiadow, nie rodzicow
		if( g[index][0] != parent && a == -1 ) a = g[index][0];
		if( g[index][1] != parent && a == -1 ) a = g[index][1];
		else if( g[index][1] != parent && a != -1 ) b = g[index][1];
		if( g[index][2] != parent ) b = g[index][2];
		
		if( isOnPath[a] == false ) writePathBack( a,index );
		bottom.PB( index );
		if( isOnPath[b] == false ) writePathForward( b,index );
		isOnPath[index] = true;
	}
	else if( g[index].size() == 2 ) {
		int a = g[index][0];
		if( g[index][1] != parent ) a = g[index][1] ;
		if( isOnPath[ a ] == false ) writePathBack( a, index );
		bottom.PB( index );
		isOnPath[index] = true;
	}
	else bottom.PB( index );
}


void createSolution(){
	REP( i,path.size() ){
		REP( k,g[ path[i] ].size() ){
			if( isOnPath[ g[ path[i] ][k] ] == false ){
				writePaths( g[ path[i] ][k], path[i] );
			}
		}
		upper.PB( path[i] );
	}	
}



void getPathDFS( int index, int parent ){
	path.PB(index);
	REP(i, induced[index].size() ){
		if( induced[index][i] != parent ){
			getPathDFS( induced[index][i], index );
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	
	bool wKolko = false;
	int ileT = 0;
	VI degree3;
	int degreeGE4 = 0;
	int il = 0;
	
	int l_zest;
	cin >> l_zest;
	while(l_zest--){
		cin >> N;
		
		
		clearAll();
		
		REP(i,N-1){
			cin >> a >> b;
			g[a-1].PB(b-1);
			g[b-1].PB(a-1);
		}
		
	//	cout << "Jestem przed backDFS" << endl;
		backDFS( 0,0 );
		il = 0;
		REP( i,g[0].size() ){
			if( tab[ g[0][i] ] == true || g[ g[0][i] ].size() >= 3 ){
				il++;
			}
		}
//		cout << endl << "ile = " << ile << endl;
		if( il >= 2 ){
			tab[0] = true;			
		}
		ile[0] = il;
		
	/*	cout << "Stan tablicy tab przed forDFS:" << endl;
		REP(i,N) cout << i+1 << ":  " << tab[i] << endl;
		cout << endl;
		cout << "Stan tablicy tab2 przed forDFS:" << endl;
		REP(i,N) cout << i+1 << ":  " << tab2[i] << endl;
		cout << endl;
		cout << "Stan tablicy tab3 przed forDFS:" << endl;
		REP(i,N) cout << i+1 << ":  " << tab3[i] << endl;
		cout << endl;
		*/
		forDFS( 0,0 );
		scalTab( 0,0 );
		/*
		cout << "Tablica ile po forDFS:" << endl;
		REP( i,N ) cout << i+1 << ":  " << ile[i] << endl;
		
		cout << "Stan tablicy tab przed forawrdDFS:" << endl;
		REP(i,N) cout << i+1 << ":  " << tab[i] << endl;
		cout << endl;
		cout << "Stan tablicy tab2 przed forawrdDFS:" << endl;
		REP(i,N) cout << i+1 << ":  " << tab2[i] << endl;
		cout << endl;
		cout << "Stan tablicy tab3 przed forawrdDFS:" << endl;
		REP(i,N) cout << i+1 << ":  " << tab3[i] << endl;
		cout << endl;*/
		
		forwardDFS( 0,0 );
		
	
		cout << "Oto graf indukowany przez niepoprawne krawdzie:" << endl;
		writeGraph( induced );
		
	//	writeDFS(0,0,true);
		
		bool t = true;
		REP( i,induced.size() ){
			if( induced[i].size() >= 3 ){
				t = false;
				break;
			}
		}
		
		if( t == true ){
			int ind = -1;
			REP( i,N ) if( induced[i].size() == 1 ){	ind = i; break;		}
			if( ind != -1 ) getPathDFS( ind, ind );
			else{ // jezeli ind == -1 czyli gdy w grafie nie ma niepoprawnych krawedzi... bedziemy musieli samemu pewna czesc z nich oznaczyc
				degreeGE4 = -1;
				degree3.clear();
				
				REP( i,g.size() ){
					if( g[i].size() >= 4 ){
						degreeGE4 = i;
						break;
					}
					
					if( g[i].size() == 3 ){
						degree3.PB( i );
					}
				}
				
				if( degreeGE4 != -1 ){
					path.PB( degreeGE4 );
				//	cout << "Jestem w degreeGE4" << endl;
				}
				else{
					if( degree3.size() > 1 ){
						ileT = 0;
						wKolko = false;
						
						if( degree3.size() == 4 ){
							REP( i,degree3.size() ){
								ileT = 0;
								REP( k, g[ degree3[i] ].size() ){
									if( g[ g[ degree3[i] ][k] ].size() == 3 ) ileT++;
								}
								
								if( ileT == 3 ){
									if( i == 0 ) degree3.erase( degree3.begin() + 1 ); // nie mozemy usunac tego srodkowego wierzcholka stopnia 3
									else degree3.erase( degree3.begin() + 0 );
									break;
								}
							}
						}
						
						
						if( degree3.size() > 3 ) while(true); // w razei czego bede weidzial, ze gdzies wczesniej mi sie rabie program
						
						if( degree3.size() == 3 ){ // musze je ustawic w kolejnsci sciezki, a nie w losowej	
				//		cout << "Ale chociaz jestem\n w degree3.size() == 3 " << endl;					
							REP( i,degree3.size() ){
								ileT = 0;
								REP( k,g[ degree3[i] ].size() ){
									if( g[ g[ degree3[i] ][k] ].size() == 3 ) ileT++;
								}
								if( ileT >= 2 && i != 1 ){
									int inx = degree3[i];
									degree3.erase( degree3.begin() + i );
									degree3.insert( degree3.begin() + 1, inx );
							//		cout << "Jestem w INX" << endl;
								}
							}
							
						}
						
						REP( i, ( degree3.size() < 3 ? degree3.size() : 3 ) ){ // uwaga, do sciezki nie powinny byc dodawane wierzcholki w losowej kolejnosci!
							path.PB( degree3[i] );
						}
					}
					else{ // jeslie wsystkie wierzcholki maja stopien 1 lub 2
						if( degree3.size() == 0 ) path.PB( 0 ); // to dodajemy dowolny jeden wierzcholek
						else path.PB( degree3[0] );		// dodajemy jedyny wierzcholek stopnia 3				
					}
				}
			}
			
			
			
			
			REP( i, path.size() ){
				isOnPath[ path[i] ] = true;
			}
				
			//	writeDFS2( path[0], path[0], false );
			
			
			cout << "Oto twoja sciezka:"<< endl;
			REP( i,path.size() ) cout << path[i]+1 << " ";
			cout << endl;
			
		/*	cout << endl << "Oto isOnPath:" << endl;
			REP(i,N) cout << i+1 << ":  " << isOnPath[i] << endl;*/
			
			
			// zanim wywolam ponizsza funkcje musze miec juz obliczone sciezki, lub przyjamniej wyznaczona wirtualna sciezke, jezeli faktyczna nie istnieje
			createSolution();
			
			cout << "TAK" << endl;
			cout << upper.size();
			REP( i,upper.size() ){
				cout << " " << upper[i]+1;
			}
			cout << endl;
			cout << bottom.size();
			REP(i,bottom.size()){
				cout << " " << bottom[i]+1;
			}
			cout << endl;
		}
		else{
			cout << "NIE" << endl;
		}
		
	}
	
}






