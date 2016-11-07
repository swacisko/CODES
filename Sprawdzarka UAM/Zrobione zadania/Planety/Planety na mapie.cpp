#include<iostream>
#include<map>
using namespace std;

int main()
{
		ios_base::sync_with_stdio(0);
        int N;
		int tab[3000][2];
        
        cin>>N;
        
        map< int, map <int,int> > mymap;
        map< int, map <int,int> >:: iterator it;
        map<int,int>::iterator iter;
       
        
        for(int i=0; i<N; i++)
        {
                cin>>tab[i][0] >> tab[i][1];
        }
        
        if( N <= 1 )
        {
			cout << 0 << endl;
			return 0;
		}
		
        int x,y;	
        
        for(int i=0; i<N; i++)
        {
                for(int k=i+1; k<N; k++)
                {
					x = tab[i][0] - tab[k][0];
					y = tab[i][1] - tab[k][1] ;
					
					if( ( it = mymap.find( x ) ) != mymap.end() &&  ( iter = it->second.find( y ) ) != it->second.end() ){
						iter->second++;
					}
					else{
						map<int,int> t = map<int,int>();
						t.insert( pair<int,int>(y,1) );
						mymap.insert( pair<int, map<int,int> >( x, t ) );
					}
					
				/*	x = -x;
					y = -y;
					
					if( ( it = mymap.find( x ) ) != mymap.end() &&  ( iter = it->second.find( y ) ) != it->second.end() ){
						iter->second++;
					}
					else{
						map<int,int> t = map<int,int>();
						t.insert( pair<int,int>(y,1) );
						mymap.insert( pair<int, map<int,int> >( x, t ) );
					}				*/
                }
        }
        
        int max = 0;
        int d;
        
     /*   cout << "To wektory jakie mozesz stworzyc:" << endl;
        for( it = mymap.begin(); it!=mymap.end(); it++ ){
			for( iter = it->second.begin(); iter != it->second.end(); iter++  ){
				cout << "x = " << it->first << ",  y = " << iter->first << "   ilosc wystapien = " << iter->second << endl;
			}		
        }*/
        
        
        for( it = mymap.begin(); it!=mymap.end(); it++ ){
			for( iter = it->second.begin(); iter != it->second.end(); iter++  ){
				d = iter->second;
				if( d > max ) max = d;
			}		
        }
        
        cout << max;
        
}
