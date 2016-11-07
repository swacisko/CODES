#include<iostream>
#include<stdio.h>

using namespace std;




int main()
{
    int l_zest, N;
    
    float tab[10001]={0}, liczba;   
    
    cin>>l_zest;
    
    while(l_zest--)
    {
        cin>>N;
        
        scanf("%f",&tab[1]);
        printf("1");
        
        for(int i=2; i<=N; i++)
        {
                scanf("%f",&tab[i]);
                
                for(int j=i; j>=2; j--)
                {
                        if(tab[j-1]<tab[j])
                        {
                            liczba=tab[j];
                        	tab[j]=tab[j-1];
                        	tab[j-1]=liczba;
                        	if(j==2) printf(" 1");
                        }
                        else
                        {
                            printf(" %d",j);
                          	j=1;
                        }
                        
                                               
                                
                }               
                
        }                  
              
             printf("\n");
                
    }   //while
  
}
