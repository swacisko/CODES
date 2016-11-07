#include<iostream>
using namespace std;


inline int module(int value)
{
	if(value>=0)return value;
	else return -value;
}

int main()
{
	int l_zest, s1,s2,o1,o2,dist;
	
	cin>>l_zest;
	
	while(l_zest--)
	{
		dist=0;
		cin>>s1>>s2>>o1>>o2;
		
		dist=module(s1-o1)+module(s2)+module(o2);
		
		cout<<dist<<endl;
		
		
		
		
		
	}
	
	
	
	
	
	
}

