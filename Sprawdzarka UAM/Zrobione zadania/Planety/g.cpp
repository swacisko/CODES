#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;



int N=0;
int tab[3000][2];
typedef pair<int, int> PII;

vector<PII> V;

int main()
{
	//	ios_base::sync_with_stdio(0);        
        
        V.clear();
        
        cin>>N;   
        
        
        for(int i=0; i<N; i++)
        {
                cin>>tab[i][0] >> tab[i][1];
        }
        
        
	    int x=0,y=0;	
	    PII p,q;
	    
	        for(int i=0; i<N; i++)
	        {
	                for(int k=i+1; k<N; k++)
	                {						
						x = tab[i][0] - tab[k][0];
						y = tab[i][1] - tab[k][1] ;
						
						p = make_pair(x,y);
						V.push_back( p );
						
						q = make_pair(-x,-y);
						V.push_back( q );											
	                }
	        }
	        
	        
	        sort( V.begin(), V.end() );
	        
	   //     for( int i=0; i<V.size(); i++ ) cout << V[i].first << "  " << V[i].second << endl;
	        
	        int max = 0;
	        int d;  
	    
	        int L = 1;
	        for( int i=1; i<V.size(); i++ ){
				if( V[i] == V[i-1] ) L++;
				else{
					if( L > max ) max = L;
					L = 1;
					
				}
	        }
	        
	        if( L > max ) max = L;
	        
	        
	        if( V.size() > 1 ) cout << max << endl;
	        else cout << "0" << endl;
		 
	
	return 0;
}
