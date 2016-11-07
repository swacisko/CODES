#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<iomanip>
#include<algorithm>
#include<fstream>

using namespace std;

#define REP( x,y ) for( int x=0; x<y; x++ )
#define PB push_back
#define PH push_heap
#define POP pop_back
#define MP make_pair

int N,M,a,b;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;


VI primes;
bool czySumaRowna[2501];
VI factors; // factors of a*b number

int ktoresumy[] = {11,17,23,27,29,35,37,41,47,51,53,57,59,65,67,71,77,79,83,87,89,93,95,97,101,107,113,
117,119,121,123,125,127,131,135,137,143,145,147,149,155,157,161,163,167,171,173,177,179,185,187,189,191,197,203,205,207,209,211,
215,217,221,223,227,233,239,245,247,251,255,257,261,263,269,275,277,281,287,289,293,297,299,301,305,307,311,317,323,325,329,331,335,337,341,343,345,347,353,357,359,363,365,367,
371,373,377,379,383,387,389,395,397,401,405,407,409,413,415,419,425,427,429,431,437,439,443,449,455,457,461,467,473,475,477,479,483,485,487,491,495,497,499,503,507,509,513,515,
517,521,527,529,531,533,535,539,541,545,547,551,553,555,557,561,563,567,569,575,577,581,583,585,587,593,599,605,607,611,613,617,623,625,627,629,631,635,637,639,641,647,651,653,
657,659,665,667,671,673,677,683,689,691,695,697,701,705,707,709,713,715,719,725,727,731,733,737,739,743,747,749,751,755,757,761,765,767,769,773,777,779,781,783,785,787,791,793,
795,797,801,803,805,809,815,817,819,821,827,833,835,837,839,845,847,851,853,857,863,867,869,871,873,875,877,881,887,891,893,895,897,899,901,903,905,907,911,915,917,919,923,925,
927,929,935,937,941,945,947,953,957,959,961,963,965,967,971,975,977,981,983,987,989,991,995,997,1001,1003,1005,1007,1009,1013,1017,1019,1025,1027,1029,1031,1037,1039,1043,1045,
1049,1055,1057,1061,1067,1069,1073,1075,1079,1081,1085,1087,1091,1097,1103,1107,1109,1115,1117,1123,1127,1129,1133,1135,1145,1147,1151,1157,1163,1171,
1175,1179,1181,1187,1199,1205,1221,1223,1235,1237,1245,1271,1277,1283,1289,1307,1591,-1};



void getPrimes(){
	primes.clear();
	primes.PB(2);
	bool prime;
	for(int i=3; i<2500; i+=2){
		prime = true;
		for( int k=2; k*k <= i; k++ ){
			if( i%k == 0 ){
				prime = false;
				break;	
			}			
		}
		if( prime ) primes.PB( i );
	}
}

string getFirstAnswer( int a, int b ){
	factors.clear();
	int t = 2;
	int x = a*b;
	
	while( t <= x ){
		if( x % t == 0 ){
			factors.PB( t );
			x = x/t;
		}
		else t++;
	}
	
	cout << "a*b = " << a*b <<"   Dzielniki liczby " << a*b << " to:" << endl;
	REP(i,factors.size()) cout << factors[i] << " ";
	cout << endl;
	
	if( factors.size() <= 2 ){
		return string( "TAK, v1" );
	}
	else{
		REP( i,factors.size() ) if( factors[i] >= 2479 ) return string( "NIE, v1" );
		
		int c = 0;
		for( int i= 5000; i>=2; i-- ){
			if( a*b % i == 0 ){
				c = i;
				break;
			}
		}
		
		t = 2;
		int p; // najmniejszy dzielnik pierwszy liczby c
		while( t <= c ){
			if( c % t == 0 ){
				p = t;
				break;
			}
			else t++;
		}
		
	//	cout << endl <<  "c = " << c << endl << endl;
		
		if( (p*a*b) / c <= 5000 && (p*a*b)/c != c ) return string( "NIE, v2" );
		else return string( "TAK, v2" );
		
		
	}
}



string getSecondAnswer(){
	if( a + b >= 2479 ) return string( "TAK" );
	
	for( int i=a+b-2; i >= a+b-i; i-- ){
		if( getFirstAnswer( i, a+b-i ) == "TAK" ){			
		//	cout << endl << i << "  " << a+b-i << endl;
			return string("TAK");	
		}
	}
	
	return string("NIE");
}

string getThirdAnswer(){
	int ile = 0;
	
	for( int i=2; i*i<=a*b; i++ ){
		if( (a*b)%i == 0 ){
			if( i + (a*b)/i >= 2479 ){
				// pusty if, nic nie robie
			}
			else if( czySumaRowna[ i + (a*b)/i ] == true ){
				ile++;
			//	cout << i << "  " << a*b/i << endl;
			}
		}
	}
	
//	cout << "ile = " << ile << endl;
	if( ile == 1 ) return string("TAK");
	return string("NIE");

}
/*
void setCzySumaRowna(){	
	REP( i, 2501 ) czySumaRowna[i] = true;
	REP( i,2501 ){
		if( i % 2 == 0 ) czySumaRowna[i] = false;
	}
	
	REP( i, primes.size() ){
		czySumaRowna[ primes[i] + 2 ] = false;
	}
	
	REP( i, 5001 ){
		if( czySumaRowna[i] == false );
	}
}
*/
bool setSumaRowna(){
	REP(i,2501) czySumaRowna[i] = false;
	for( int i=0; ktoresumy[i] > 0; i++ ){
		czySumaRowna[ ktoresumy[i] ] = true;
	}
	
}

void clearAll();
int main(){	
	string s;
	
	getPrimes();
	setSumaRowna();
	
//	REP( i, 300 ) if( czySumaRowna[i] ) cout << i << endl;
	
//	setCzySumaRowna();
	
	//*********************************************** cos dla preprocesingu
/*	ofstream str( "Preprocessing.txt" );
	
	for( int i=0; i<2480; i++ ){
		a = i;
		b = 0;
		if( getSecondAnswer() == "NIE" ){
			str << i << ",";
		}
	}
	
	str.close();*/
	
/*	ofstream str( "KiedyTak.txt" );
	int zakres = 130;
	for( int i=2; i<=zakres; i++ ){
		for( int k=2; k<=i; k++ ){
			a = i;
			b = k;
			if( getFirstAnswer( i,k ) == "NIE" && getSecondAnswer()=="NIE" && getThirdAnswer() == "TAK" ){
				str << i << " " << k << endl << "NIE" << endl << "NIE" << endl << "TAK" << endl << endl;
				cout << i << " " << k << endl;
			}
		}
	}
	
	cout << endl << "Zakonczylem prace" << endl;
	str.close();*/
	
	//************************************************
	
//	REP(i,primes.size()) cout << primes[i] << "   "; // dobrze wczytuje liczby pierwsze
	
/*	for( int i=2; i<2477; i++ ){
		cout << setw(7) << i << ": " << czySumaRowna[i] << "  ";
		if( i % 10 == 0 ) cout << endl;
	}*/
	
	
	
	
	int l_zest;
	cin >> l_zest;
	
	while( l_zest-- ){
		cin >> a >> b;
		s = getFirstAnswer(a,b);
		cout << s << endl;
				
		if( s == "NIE" ){
			s = getSecondAnswer();
			cout << s << endl;	
		}
		else continue;
		
		if( s == "NIE" ) cout << getThirdAnswer() << endl;
		
	}
	
	
	
}


