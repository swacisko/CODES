#include<iostream>
#include<cstdio>
#include<string>
#include<vector>
using namespace std;
vector<bool>Rep;
string s;
int main()
{
	int l_zest;
	cin>>l_zest;
	
while(l_zest--)
{
    //int n;
    //cin>>n;
    cin>>s;
    //int t = 0;
    while(s.size() && s[0]=='0')s=s.substr(1);
    while(s!="")
    {
        Rep.push_back( s[s.size()-1]%2 );
        //t++;
        int c=0,x;
        int tt = s.size();
        for(int i = 0; i<tt; i++)
        {
            x=s[i]-'0';
            //printf("%d",x);
            s[i]=(x+c)/2+'0';
            if(x%2)c=10;
            else c=0;
        }
        while(s.size() && s[0]=='0')s=s.substr(1);
    }
    /*for(int i = Rep.size()-2; i >=0; i--)
    {
        if(Rep[i]!=Rep[i+1])printf("1");
        else printf("0");
    }*/
    
    bool czy_da_sie = true;
    int opcja;
    if( Rep[0] == Rep[Rep.size()-1] ) opcja = 1;
    else opcja = 2;
    
    switch(opcja)
    {
		case 1:
			{
				for(int i=0; i<Rep.size(); i++)
				{
					if( Rep[i] != Rep[ Rep.size() - 1 - i ] )
					{
						czy_da_sie = false;
						break;
					}
				}
				break;
			}
		case 2:
			{
				for(int i=0; i<Rep.size(); i++)
				{
					if( Rep[i] == Rep[ Rep.size() - 1 - i ] )
					{
						czy_da_sie = false;
						break;
					}
				}
				break;
			}
	}
    
    if( czy_da_sie ) cout<<"TAK"<<endl;
    else cout<<"NIE"<<endl;
    
    Rep.clear();
    cin.ignore();
   // getchar();
   
} // koniec while'a

    return 0;
}




