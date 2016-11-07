#include<iostream>
#include<vector>
#include<string.h>
using namespace std;
 
int Tury[1031][2];
int MAX[1031];
 
int N,M,l_zest,T,L,f1,f2,max1,max2,maxs;
 
inline int mod(int f1)
{
    return f1<0?-f1:f1;
}
inline bool czy_zdazy( int x1, int y1, int x2, int y2, int w_ilu_turach )
{
     if( mod( x1-x2 ) + mod( y1-y2 ) < w_ilu_turach+1 ) return true;
     else return false;
}
 
int main()
{
    ios_base::sync_with_stdio(0); 
    
    
    cin>>l_zest;
    
    while(l_zest--)
    {
        max1 = max2 = 0;
                
                   memset( Tury, 0,2*1031*4 );                  
                   memset( MAX,0,1031*4 );
                   cin>>N>>M>>T;
                   L= N + M - 2;
                   
                   for(int i=0; i<T; i++)
                   {
                           cin>>Tury[i][0]>>Tury[i][1];
                   }
                   
                   max1 = 0;
                   for(int i=T-1; i>=0; i--)
                   {
                           max2 = 0;
                           for(int k= i+L+1; k>i; k--)
                           {
                                    if( czy_zdazy( Tury[i][0], Tury[i][1], Tury[k][0], Tury[k][1], k-i ) )
                                    {
                                            if( max2 < MAX[k] ) max2 = MAX[k];
                                    }
                           }
                           
                           MAX[i] = max1>max2?max1+1:max2+1;
                           if( max1 < MAX[i+L+1] ) max1 = MAX[i+L+1];
                           
                       // MAX[i] = max1>max2?max1+1:max2+1;
                   }
              
                               maxs = 0;
                            for(int i=0; i<T; i++)
                            {
                                if( MAX[i] > maxs ) maxs = MAX[i]; 
                            }     
                                
                            cout << maxs << endl;
    }
    
    
    
    
    
}
