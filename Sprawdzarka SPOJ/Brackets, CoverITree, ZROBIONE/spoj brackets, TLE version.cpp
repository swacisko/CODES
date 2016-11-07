#include<iostream>
//#include<stdio.h>
using namespace std;
int N;
bool check( bool *buf ){
	int zeroes = 0;
	int ones = 0;
	for( int i=0; i<N; i++ ){
		if( buf[i] ) ones++;
		else zeroes++;
		if( zeroes < ones ) return false;
	}
	return true;
}


int main(){
	ios_base::sync_with_stdio(0);
	bool *buf;
	int m,t;
	char c;
	int zeroes = 0;
	int ones = 0;
	int l_zest = 0;
	while( l_zest++ < 10 ){
	//	scanf( "%d",&N );
		cin >> N;
		buf = new bool[N];
		for(int i=0; i<N; i++){
		//	scanf( "%c",&c );
			cin >> c;
			if( c == ')' ){
				buf[i] = 1;
				ones++;
			} 
			else{
				buf[i] = 0;
				zeroes++;
			}
		}
		
	//	for(int i=0; i<N; i++) cout << buf[i] << " ";
	//	cout << endl;
	//	printf( "Test %d:\n",l_zest );
		
		cout << "Test " << l_zest << ":" << endl;
	//	scanf("%d",&m);
		cin >> m;
		for(int i=0; i<m; i++){
		//	scanf("%d",&t);
			cin >> t;			
			
			if( t == 0 ){				
				if( zeroes == ones && check( buf ) ) cout << "YES" << endl; //printf("YES\n");
				else cout << "NO" << endl; //printf("NO\n");
			}
			else{
				if( buf[t] ){
					ones--;
					zeroes++;
				}
				else{
					zeroes--;
					ones++;
				}
				
				if( buf[t-1] ) buf[t-1] = false;
				else buf[t-1] = true;
			}
			
			//cout << "\tzeroes = " << zeroes << "   ones = " << ones << endl;
		//	for(int k=0; k<N; k++) cout << buf[k] << " ";
		//	cout << endl;
		}
		
		delete[]buf;
	}
	
	
	
}
