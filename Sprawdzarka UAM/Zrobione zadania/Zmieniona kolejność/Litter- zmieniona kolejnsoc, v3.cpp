#include<iostream>
#include<sstream>
#include<string>
using namespace std;

char priorities[4];
bool zeroDivision;

void deleteSpaces( string &s ){
	for( long long i=0; i<s.length(); i++ ){
		if( s[i] == ' ' ){
			s.erase( s.begin() + i );
			i--;
		}
	}
}

long long findLastOpenBracket( string s, long long start ){ // zaczynam od start i ide w LEWO
	for( long long i=start; i>=0; i-- ){
		if( s[i] == '(' ) return i;
	}
	return -1;
}

long long findFirstCloseBracket( string s, long long start ){ // ide w prawo
	for( long long i=start; i<s.length(); i++ ){
		if( s[i] == ')' ) return i;
	}
	return -1;
}

long long stringValue( string s ){
	istringstream strum(s);
	long long t;
	strum >> t;
//	cout << "stringValue = " << t << endl;
	return t;
}
	
string toString( long long value ){
	ostringstream strum;
	strum << value;
//	cout << "toString = " << strum.str() << endl;
	return strum.str();
}

bool isNumber( string s ){
	int start = 0;
	if( s[0] == '-' ) start = 1;
	
	for( int i = start; i<s.size(); i++ ){
		if( s[i] < 48 || s[i] > 57 ) return false;
	}
	return true;	
}

long long calculateBracketless( string s ){
/*	while( s.find( "--" ) != string::npos ){ // tego nie moze byc bo zamienia -- na + a '+' moze miec iny priorytet, na pewnio nie dziala
		s.replace( s.find( "--" ), 2, "+",0,1 );
	}*/
	
//	cout << "bracketlestt string = " << s << endl;
	if( s.length() <= 2 || isNumber(s) ){ //( isNumber(s) && s[0] == '-'  ) ){
		return stringValue( s );
	}
	
	
	for( long long i=0; i<4; i++ ){
		if( priorities[i] == '-' ){
			int k = s.rfind( priorities[i] );
//			cout << "na zewnatrz k = " << k << "         ";
						
			while(  k > 0 && ( s[k-1] < 48 || s[k-1] > 58 )  ){
				k = s.rfind( priorities[i],k-1 );
				if( k == string::npos ) break;						
			}
			if( k == string::npos || k==0 ){
				continue;
			}
			
//			cout << "HAHA   ";
			int t = k;
			long long left = calculateBracketless( s.substr( 0, t ) );
			long long right = calculateBracketless( s.substr( t+1, s.length()-t ) ) ;
			
	//		cout << "\tleft = " << left << "  ---> " << s.substr( 0, t )
	//				 << "\t\tright = " << right << " ---> " << s.substr( t+1, s.length()-t ) << "\tpriority:  " << priorities[i] << "\toutcome = " << left - right << endl;
			
			return left-right;
		}
		
		if(  s.rfind( priorities[i] ) != string::npos 
			&& s[ s.rfind( priorities[i] )-1 ] >= 48 &&  s[ s.rfind( priorities[i] )-1 ] <=58 ){
			if( priorities[i] == '/' ){
				long long t = s.rfind( priorities[i] );
				long long left = calculateBracketless( s.substr( 0, t ) );
				long long right = calculateBracketless( s.substr( t+1, s.length()-t ) ) ;
				
	//			cout << "\tleft = " << left << "  ---> " << s.substr( 0, t )
	//				 << "\t\tright = " << right << " ---> " << s.substr( t+1, s.length()-t ) << "\tpriority:  " << priorities[i] << "\toutcome = " << left / right << endl;
				
				if( right == 0 ){
					zeroDivision = true;
					return 1;
				}
				else return left/right;
			}
			else{
				long long t = s.rfind( priorities[i] );
				long long left = calculateBracketless( s.substr( 0, t ) );
				long long right = calculateBracketless( s.substr( t+1, s.length()-t ) ) ;
				
				
				
				char c = priorities[i];
				if( c == '+' ){
		//			cout << "\tleft = " << left << "  ---> " << s.substr( 0, t )
		//			 << "\t\tright = " << right << " ---> " << s.substr( t+1, s.length()-t ) << "\tpriority:  " << priorities[i] << "\toutcome = " << left + right << endl;
					 
					 return left+right;
				} 
			//	else if( c == '-' ) return left-right;
				else if( c == '*' ){
		//			cout << "\tleft = " << left << "  ---> " << s.substr( 0, t )
		//			 << "\t\tright = " << right << " ---> " << s.substr( t+1, s.length()-t ) << "\tpriority:  " << priorities[i] << "\toutcome = " << left * right << endl;
					 
					  return left*right;
				}
			}
		}
	}
	
	
}
	
long long calculate( string s ){
	long long l = s.length()-1;
	long long p;
	long long outcome = 0;
	while( findLastOpenBracket( s,s.length()-1 ) != -1 ){
		outcome = 0;
		l = findLastOpenBracket( s,s.length()-1 );
		p = findFirstCloseBracket( s,l );
//		cout << "Obliczenia l i p sa poprawne, l,p = " << l << " , " << p << endl;
		outcome += calculateBracketless( s.substr( l+1, p-l-1 ) );
		if( zeroDivision ) break;
//		cout << "outcome = " << outcome << endl;
		s.replace( l,p-l+1, toString( outcome ), 0, toString( outcome ).length() );
//		cout << "new wyrazenie = " << s << endl;
		
	}
	
	return stringValue(s);
}

int main(){
	
	long long l_zest;
	
	cin >> l_zest;
	
	while( l_zest-- ){
		zeroDivision = false;
		
		string wyrazenie;
		char c,d;
		cin >> c;
		while( true ){
			d = c;
			cin >> c;
			if( ( d == '/' || d == '*' || d == '+' || d == '-' ) && ( c == '+' || c == '/' || c == '*' || c == '-' ) ) break;
			wyrazenie += d;
		}
		
		priorities[0] = d;
		priorities[1] = c;
		for( long long i=2; i<4; i++ ) cin >> priorities[i]; // wczytuje prioryteety
		
		deleteSpaces( wyrazenie );
		wyrazenie.insert( 0, "(" );
		wyrazenie += ")";
		
//		cout << "Wyrazenie = " << wyrazenie << endl;
		
		long long t = calculate( wyrazenie );
		
		if( zeroDivision ){
			cout << "DZIELENIE PRZEZ ZERO" << endl;
		}
		else{
			cout << t << endl;
		}
		
		
		
	}
	
	
	
	return 0;
	
}
