#include<iostream>
using namespace std;

int NWD(int, int);
int main()
{
    int liczba_zestawow, L[4];
    
    cin>>liczba_zestawow;
    
    for(int i=0; i<liczba_zestawow; i++)
    {
            for(int k=0; k<4; k++)
            {
                    
                    
            cin>>L[k];
            
            }
      L[2]=L[2]*L[3] / NWD( L[2], L[3]);
      L[1]=L[1]*L[2] / NWD(L[1],L[2]); 
      cout<<(L[0]*L[1] / NWD(L[0],L[1]) );
    }
   
}
int NWD(int A,int B)
{
    int M,m,r;
    if(A>B)
    {
           M=A;
           m=B;
    }
    else 
    {
         M=B;
         m=A;
    }
    r=M%m;
    while(r!=0)
    {
               M=m;
               m=r;
               r=M%m;
    }
    return m;
    
}
