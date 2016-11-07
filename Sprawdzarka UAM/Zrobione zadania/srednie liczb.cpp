/*
#include<iostream>
#include<stdio.h>
using namespace std;

int main()
{
    int tab[1011]={0},suma=0, ile_jedynek=0, ile_zer=0;
    float srednia=0;
    
    int i=0; 
    while(tab[i]>=0)
    {
             scanf("%d",&tab[i]);
             if(tab[i]==1){ ile_jedynek++;}
             else if(tab[i]==0) {ile_zer++;}
             
              if(tab[i]==1)
              {
                     for(int k=0; k<=i; k++)
                     {
                             suma+=tab[k]; 
                                        
                     }
                     srednia = ((float)(suma-ile_jedynek))/((float)(i+1-ile_jedynek-ile_zer)); 
                                         
                     printf("%.2f \n",srednia);
                     suma=0;
                     
              }        
              else if(tab[i]==0)
              {
                   for(int k=0; k<i; k++)
                   {
                           if(tab[k]!=0 && tab[k]!=1)
                           {
                           printf("%d ", tab[k]);
                           }
                   }
                  printf("\n");
                   i++;
                   continue;
              }
              else if(tab[i]==-1)
              {
                   break;                   
              }
              i++;
           
    }
    
   
    
}
*/