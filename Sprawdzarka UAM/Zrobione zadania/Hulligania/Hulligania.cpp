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

int N,M,a,b,x,y;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;

VVI cycles;
int wynik;
int tab[10010];
int licznik;

class Node{
	public:
		Node() : t(0), was(false) {
			
		}
		
		int t;
		bool was;
		
		VI neighbours;
		void push_back( int a ){
			neighbours.PB(a);
		}
		
		int operator[]( int pos ){
			return neighbours[pos];
		}
		
		int size(){
			return neighbours.size();
		}
};

typedef vector<Node> VN;
VN g;


void DFS( int index, int parent ){
	g[index].t = licznik;
	tab[licznik] = index;
	licznik++;
	g[index].was = true;
	
	REP( i, g[index].size() ){
		if( g[index][i] != parent && g[ g[index][i] ].t > 0 ){
			cycles.PB( VI(0) );
			for( int k=g[ g[index][i] ].t; k<=g[index].t; k++ ){
				cycles[ cycles.size()-1 ].PB( tab[k] );	
				
			}			
			
		}
		else if( g[ g[index][i] ].was == false ){
			DFS( g[index][i], index );
		}	
	}
	
	tab[licznik] = 0;
	g[index].t = 0;
	licznik--;
}

void clearAll(){
	wynik = 0;
	cycles.clear();
	
	g.clear();
	REP(i,N) g.PB( Node() );
	
	REP(i,N)tab[i] = 0;
	
	licznik = 1;
}

int getMaxPath( VI &v ){
	int ile = 0;
	int t = 0;
	int max = 0;	
	
	for( int i=0; i<v.size(); i++ ){
		if( g[ v[i] ].size() == 2 ) ile++;
		else{
			if( ile > max ) max = ile;
			ile = 0;
		}
	}
	
	if( ile > max ) max = ile;
	
	return max;
	
}

void wypiszCykl( VI &v ){
	REP(i,v.size()){
		cout << v[i] << " ";
	}
	cout << endl;
}

int main(){
	
	ios_base::sync_with_stdio(0);
	
	int l_zest;
	cin >> l_zest;
	while(l_zest--){
		cin >> N >> M;
		
		clearAll();
		
		REP(i,M){
			cin >> x >> y;
			g[x].PB(y);
			g[y].PB(x);
		}
		
		REP( i,N ){
			if( g[i].was == false ){
				DFS( i,i );				
			}
		}
		
	/*	cout << "Oto wszystkie cykle:" << endl;
		REP(i,cycles.size()){
			cout << "\t";
			REP( k,cycles[i].size() ){
				cout << cycles[i][k] << " ";
			}
			cout << "\tkoniec lini" << endl;
		}*/
		
		REP( i,N ){
			if( g[i].size() == 0 || g[i].size() == 1 ) wynik++;
		}
		
		int t_C,C;
		REP( i,cycles.size() ){
			t_C = getMaxPath( cycles[i] );
			C = cycles[i].size();
			
			if( t_C == C ){
		//		wypiszCykl( cycles[i] );
		//		cout << "t_C = " << t_C << "  ==  " << C << " = C" << endl << endl;
				if( C%2 == 0 ) wynik += 2;
				else wynik += 3;
			}
			else if( t_C + 1 == C ){
		//		wypiszCykl( cycles[i] );
		//		cout << "t_C + 1 = " << t_C + 1 << "  ==  " << C << " = C" << endl << endl;
				if( C%2 == 1 ) wynik += 2;
				else wynik++;
			}
			else if( C < 2*t_C + 2 ){
		//		wypiszCykl( cycles[i] );
		//		cout << "2t_C + 2 = " << 2*t_C + 2 << "  >  " << C << " = C" << endl << endl;
				wynik++;
			}			
		}
	//	cout << endl << endl;
		
		cout << wynik << endl;
		
	}// koniec while'a
	
}






