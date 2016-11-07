#include<stdio.h>
#include<iostream>

using namespace std;

int inrow(char* tab, int rownum, char sign);
int incol(char* tab, int colnum, char sign);

int main()
{
	int l_zest, ruchy[26]={} ,wolne, t, jeden, index1, index2, rzad,kolumna;
	char plansza[26];
	const char M='M', J='J';
	
	scanf("%d",&l_zest);
	
	while(l_zest--)
	{
		for(int i=0; i<=25; i++)
		{
			plansza[i]=0;
		}
		
		t=1;
		wolne=25;
		
		for(int k=1; k<=25; k++)
		{
			scanf("%d",&ruchy[k]);
		}
		
		plansza[ruchy[1]]='M';
		wolne--;
		
		while(wolne)
		{	
			jeden=0;	
			rzad = (ruchy[t]+4)/5;
			if( ruchy[t]%5==0 ) kolumna = 5;
			else kolumna = ruchy[t]%5;
			
			if( inrow(plansza,rzad, M)>=3 && inrow(plansza,rzad, J)==0 )
			{
				for(int k=5*(rzad-1)+1; k<=5*rzad; k++)
				{
					if( plansza[k]==0 && incol(plansza,(k%5)?k%5:5,J)==0) 
					{
						jeden=1; index1=k;
						break;
					}
					else if(plansza[k]==0)
					{
						index2=k;
					}
					
				}
				if(jeden==1)
				{
					plansza[index1]='J';
					printf("%d ",index1);
				}
				else
				{
					plansza[index2]='J';
					printf("%d ",index2);
				}

			}				
			else if( incol(plansza,kolumna,M)>=3 && incol(plansza,kolumna,J)==0 )
			{
				for(int k=kolumna; k<=25; k+=5)
				{
					if( plansza[k]==0 && inrow(plansza,(k+4)%5,J)==0) 
					{
						jeden=1; index1=k;
						break;
					}
					else if(plansza[k]==0)
					{
						index2=k;
					}
					
				}
				if(jeden==1)
				{
					plansza[index1]='J';
					printf("%d ",index1);
				}
				else
				{
					plansza[index2]='J';
					printf("%d ",index2);
				}
			
			}
			else
			{
				if( plansza[13]==0 ) { plansza[13]='J'; printf("13 ");	}
				else if(plansza[7]==0) { plansza[7]='J'; printf("7 "); }
				else if(plansza[21]==0) { plansza[21]='J'; printf("21 "); }
				else if(plansza[5]==0) { plansza[5]='J'; printf("5 "); }				
				else if(plansza[11]==0){ plansza[11]='J'; printf("11 "); }
				else if(plansza[9]==0){ plansza[9]='J'; printf("9 "); }
				else if(plansza[15]==0){ plansza[15]='J'; printf("15 "); }
				else if(plansza[3]==0){ plansza[3]='J'; printf("3 "); }
				else if(plansza[18]==0){ plansza[18]='J'; printf("18 "); }
				else if(plansza[19]==0){ plansza[19]='J'; printf("19 "); }
				else
				{
					for(int k=1; k<=25; k++)
					{
						if(plansza[k]==0) { plansza[k]='J'; printf("%d ",k); break; }
					}
				}
				
				
				
			}
	
	
			while( plansza[ruchy[t]]!=0) t++;
						
			plansza[ruchy[t]]='M';
	
			wolne-=2;
		}
	/*	cout<<endl<<endl;
		for(int i=1; i<=5; i++)
		{
			for(int k=1; k<=5; k++)
			{
				cout<<plansza[5*(i-1)+k];
			}
			cout<<endl;
		}*/
	
	}
	
	
	
	
	
}

int inrow(char* tab, int rownum, char sign) // zwraca ilosc zadancych znakow w danym wierszu
{
	int ile=0, kon=5*rownum;
	for(int i=5*(rownum-1)+1; i<=kon; i++)
	{
		if( tab[i]==sign ) ile++;
	}
	return ile;
	
}

int incol(char* tab, int colnum, char sign) // zwraca ilosc zadanych znakow w danej kolumnie
{
	int ile=0;
	
	for(int i=colnum; i<=25; i+=5)
	{
		if( tab[i]==sign ) ile++;
	}
	return ile;
	
}
