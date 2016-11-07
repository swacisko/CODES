#include<iostream>
#include<map>
using namespace std;



int N=0;
long long tab[3000][2];
typedef map< pair<int,int>, int > MPIII;
typedef pair<int,int> PII;
MPIII::iterator it;

MPIII mymap;
		
int main()
{
	//	ios_base::sync_with_stdio(0);        
        
        mymap.clear();
        
        cin>>N;   
        
        
        for(long long i=0; i<N; i++)
        {
                cin>>tab[i][0] >> tab[i][1];
        }
        
        
	        long long x=0,y=0;	
	        
	        for(long long i=0; i<N; i++)
	        {
	                for(long long k=i+1; k<N; k++)
	                {
					//	if( i == k ) break;
						
						x = tab[i][0] - tab[k][0];
						y = tab[i][1] - tab[k][1] ;
						
						PII p(x,y);
						
						if( ( it = mymap.find( p ) ) != mymap.end() ){
							it->second++;
						}
						else{
							mymap.insert( make_pair( p, 1 ) );
						}
						
						PII q(-x,-y);
						
						if( ( it = mymap.find( q ) ) != mymap.end() ){
							it->second++;
						}
						else{
							mymap.insert( make_pair( q, 1 ) );
						}
						
	                }
	        }
	        
	        long long max = 0;
	        long long d;
	        
	     /*   cout << "To wektory jakie mozesz stworzyc:" << endl;
	        for( it = mymap.begin(); it!=mymap.end(); it++ ){
				for( iter = it->second.begin(); iter != it->second.end(); iter++  ){
					cout << "x = " << it->first << ",  y = " << iter->first << "   ilosc wystapien = " << iter->second << endl;
				}		
	        }*/
	        
	        for( it = mymap.begin(); it!=mymap.end(); it++ ){
				if( it->second > max ) max = it->second;
	        }
	        
	        
	        cout << max << endl;
		 
	
	return 0;
}
