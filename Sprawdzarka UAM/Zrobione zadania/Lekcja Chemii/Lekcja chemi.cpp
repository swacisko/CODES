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
#define ST first
#define ND second

int N,M,a,b;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;

int main(){
	
	double masy[] = {
		0,
		1,
		4,
		7,
		9.,
		11,
		12,
		14,
		16,
		19,
		20,
		23,
		24,
		27,
		28,
		31,
		32,
		35,
		40		
	};
	
	double suma;
	int l_zest;
	cin >> l_zest;
	int k;
	while(l_zest--){
		
		cin >> k;
		suma = 0;
		for(int i=0; i<k; i++){
			cin >> a;
			suma +=  masy[a];
		}
		
		cout << (int) ( suma / 6.02545 ) << endl;
	}
	
	
	
	
}





