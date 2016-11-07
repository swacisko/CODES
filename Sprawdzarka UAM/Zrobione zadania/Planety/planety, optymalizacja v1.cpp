#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
 
const int inf = (1<<31) + 10; // czy to infinity bedzie wystarczajace dla tego zadania?


bool myfun( int *v, int *w ){
	return ( ( v[0] < w[0] ) || ( v[0] == w[0] && v[1] < w[1] )  );
}
 
 
int main()
{
	
		ios_base::sync_with_stdio(0);
        int N;
		int **tab;
        vector< int* > V; // szybciej bedzie zamienic na wskaznik, uniknie sie wtedy zbednego kopiowania wekt do vectora
        
        cin>>N;
        
        
        tab = new int*[N];
        for(int i=0; i<N; i++) tab[i] = new int[2];
        
        for(int i=0; i<N; i++)
        {
                cin>>tab[i][0] >> tab[i][1];
        }
        
        if( N == 1 )
        {
			cout << 0 << endl;
			return 0;
		}
		
		int x,y;
        
        int *v, *w;

        
        for(int i=0; i<N; i++)
        {
                for(int k=i+1; k<N; k++)
                {
					x = tab[i][0] - tab[k][0];
					y = tab[i][1] - tab[k][1];
					
					v = new int[2];
					v[0] = x; v[1] = y;
					V.push_back( v );
					
					w = new int[2];
					w[0] = -x;
					w[1] = -y;
					V.push_back( w );
                }
        }
        
        sort( V.begin(), V.end(), myfun );
        
    /*    for( int i=0; i<V.size(); i++ ){
			cout << V[i][0] << "  " << V[i][1] << endl;
        }*/
        int *t = new int[2];
        t[0] = inf;
        t[1] = inf;
        V.push_back( t );
        
      
        int L = 1, index = 0, max = 0;
        while( index < V.size()-1 )
        {
                if( V[index][0] == V[index+1][0] && V[index][1] == V[index+1][1] )
                {
                        L++;
                }
                else
                {
                        if( L>max ) max = L;
                        
                        L = 1;
                }
                
                index++;        
        }
        
        if( L>max ) max = L;
       
        cout << max << endl;
        
        return 0;
}
