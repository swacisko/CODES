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
VI f1,f2;

int ktoresumy[] = {11,17,23,27,29,35,37,41,47,51,53,57,59,65,67,71,77,79,83,87,89,93,95,97,101,107,113,117,119,121,123,125,127,131,135,137,143,145,147,149,
155,157,161,163,167,171,173,177,179,185,187,189,191,197,203,205,207,209,211,215,217,221,223,227,233,239,245,247,251,255,257,261,263,269,275,277,281,287,289,
293,297,299,301,305,307,311,317,323,325,329,331,335,337,341,343,345,347,353,357,359,363,365,367,371,373,377,379,383,387,389,395,397,401,405,407,409,413,415,
419,425,427,429,431,437,439,443,449,455,457,461,467,473,475,477,479,483,485,487,491,495,497,499,503,507,509,513,515,517,521,527,529,531,533,535,539,541,545,
547,551,553,555,557,561,563,567,569,575,577,581,583,585,587,593,599,605,607,611,613,617,623,625,627,629,631,635,637,639,641,647,651,653,657,659,665,667,671,
673,677,683,689,691,695,697,701,705,707,709,713,715,719,725,727,731,733,737,739,743,747,749,751,755,757,761,765,767,769,773,777,779,781,783,785,787,791,793,
795,797,801,803,805,809,815,817,819,821,827,833,835,837,839,845,847,851,853,857,863,867,869,871,873,875,877,881,887,891,893,895,897,899,901,903,905,907,911,
915,917,919,923,925,927,929,935,937,941,945,947,953,957,959,961,963,965,967,971,975,977,981,983,987,989,991,995,997,1001,1003,1005,1007,1009,1013,1017,1019,
1025,1027,1029,1031,1037,1039,1043,1045,1049,1055,1057,1061,1067,1069,1073,1075,1079,1081,1085,1087,1091,1097,1103,1107,1109,1113,1115,1117,1121,1123,1127,
1129,1133,1135,1139,1141,1143,1145,1147,1151,1157,1159,1161,1163,1169,1171,1175,1177,1179,1181,1185,1187,1193,1197,1199,1201,1205,1207,1209,1211,1213,1217,
1221,1223,1229,1235,1237,1241,1243,1245,1247,1249,1253,1255,1259,1265,1267,1269,1271,1273,1275,1277,1283,1287,1289,1295,1297,1301,1307,1311,1313,1315,1319,
1325,1327,1331,1333,1335,1337,1339,1341,1343,1345,1349,1351,1353,1355,1357,1359,1361,1365,1367,1373,1377,1379,1381,1385,1387,1391,1393,1395,1397,1399,1403,
1405,1407,1409,1413,1415,1417,1419,1421,1423,1427,1433,1439,1443,1445,1447,1451,1457,1459,1463,1465,1467,1469,1471,1475,1477,1479,1481,1487,1493,1499,1503,
1505,1507,1511,1515,1517,1519,1521,1523,1529,1531,1535,1537,1539,1541,1543,1547,1549,1553,1557,1559,1565,1567,1571,1575,1577,1579,1583,1589,1591,1593,1595,
1597,1601,1605,1607,1613,1617,1619,1625,1627,1631,1633,1635,1637,1643,1645,1647,1649,1651,1653,1655,1657,1661,1663,1667,1673,1675,1677,1679,1681,1683,1685,
1687,1691,1693,1697,1703,1705,1709,1715,1717,1719,1721,1727,1729,1733,1737,1739,1741,1745,1747,1751,1753,1757,1759,1763,1765,1767,1769,1771,1773,1775,1777,
1781,1783,1787,1793,1795,1799,1801,1805,1807,1809,1811,1815,1817,1819,1823,1827,1829,1831,1835,1837,1841,1843,1845,1847,1853,1855,1859,1861,1865,1867,1871,
1877,1883,1885,1887,1889,1895,1897,1899,1901,1905,1907,1911,1913,1917,1919,1921,1925,1927,1931,1937,1939,1943,1945,1947,1949,1955,1957,1961,1963,1965,1967,
1969,1971,1973,1979,1985,1987,1991,1993,1997,2003,2007,2009,2011,2015,2017,2021,2023,2025,2027,2033,2035,2037,2039,2043,2045,2047,2051,2053,2057,2059,2061,
2063,2067,2069,2075,2077,2079,2081,2087,2093,2095,2097,2099,2105,2107,2109,2111,2117,2119,2121,2123,2125,2129,2135,2137,2141,2147,2149,2151,2153,2159,2161,
2165,2167,2169,2171,2173,2175,2177,2179,2183,2185,2187,2189,2191,2193,2195,2197,2201,2203,2207,2211,2213,2219,2221,2225,2227,2231,2233,2235,2237,2243,2249,
2251,2255,2257,2259,2261,2263,2265,2267,2273,2277,2279,2281,2285,2287,2291,2293,2297,2301,2303,2305,2309,2315,2317,2321,2323,2325,2327,2329,2331,2333,2337,
2339,2345,2347,2351,2355,2357,2363,2365,2367,2369,2371,2375,2377,2381,2387,2389,2393,2397,2399,2403,2405,2411,2415,2417,2421,2423,2429,2431,2435,2437,2441,
2445,2447,2451,2453,2455,2457,2459,2465,2467,2471,2473,2477,-1};



inline void getPrimes(){
	primes.clear();
	primes.PB(2);
	bool prime;
	for(int i=3; i<5000; i+=2){
		prime = true;
		for( int k=0; k<primes.size(); k++ ){
			if( i % primes[k] == 0 ){
				prime = false;
				break;
			}
		}
		if( prime ) primes.PB( i );
	}
}

inline int getNumber( VI &v ){
	int x = 1;
	REP( i,v.size() ) x *= v[i];
	return x;
}

inline void getFactorization( int x, VI &fac ){
//	cout << "FAKTORUJE" << endl;
	fac.clear();
	int t = 0;
	while( primes[t] <= x ){
		if( x % primes[t] == 0 ){
			fac.PB( primes[t] );
			x /= primes[t];
		}
		else t++;
	}
}

string getFirstAnswer( int a, int b ){
	int x = a*b;
	
	getFactorization( x, factors );
	
//	cout << "a*b = " << a*b <<"   Dzielniki liczby " << a*b << " to:" << endl;
//	REP(i,factors.size()) cout << factors[i] << " ";
//	cout << endl;
	
	if( factors.size() <= 2 ){
		return string( "TAK" );
	}
	else{
		REP( i,factors.size() ) if( factors[i] >= 2479 ) return string( "TAK" );
		
		int c = 0; // najmniejsza liczba <= 5000 dzielaca a*b
		for( int i = 5000; i >=2; i-- ){
			if( (a*b) % i == 0 && ( i < a*b ) ){
				c = i;
				break;
			}
		}
		
//		cout << endl <<  "c = " << c << endl << endl;
				
		// uwaga, tutaj sprawdzam, czy moge dokonac zamiany
		
		int fe = c;
		int ge = (a*b)/c;
		
		getFactorization( fe, f1 );		
		getFactorization( ge,f2 );
		
		//	cout << "f1:     "; REP( i,f1.size() ) cout << f1[i] << " ";
		//	cout << endl << "f2:    "; REP(i,f2.size()) cout << f2[i] << " ";
		//	cout << endl;
		
		
		
	/*	if( f1.size() >= 2 && f2.size() >=1 ){
			swap( f1[0], f2[0] );
			
			int fer = getNumber( f1 );
			int ger = getNumber( f2 );
			
			if( f1[0] != f2[0] && ( fer <=5000 && fer != ge ) && ( ger <= 5000 && ger!=fe ) ){
			//	cout << "Chyba dziala";
				return string( "NIE" );
			}
			
			swap( f1[0], f2[0] );		
		}*/
		
		int fer,ger;
		int index1 = 0;
		int index2 = 0;
		double minq = 100000;
		
		REP( i,f1.size() ){
			REP( k, f2.size() ){
				if( f1[i] <= f2[k] ) break;
				if( minq > (double)(f1[i] / f2[k]) ){
					index1 = i;
					index2 = k;
					minq = (double)( f1[i] / f2[k] );
				}							
			}
		}
		
//		cout << "index1 = " << index1 << "index2 = " << index2 << endl;
				swap( f1[index1], f2[index2] );
				
			//	cout << "f1:     "; REP( i,f1.size() ) cout << f1[i] << " ";
			//	cout << endl << "f2:    "; REP(i,f2.size()) cout << f2[i] << " ";
			//	cout << endl;
				
				fer = getNumber( f1 );
				ger = getNumber( f2 );
			//	cout << "fer = " << fer << "   ger = " << ger << endl;
				
				if( f1[index1] != f2[index2] && ( fer <=5000 && fer != ge ) && ( ger <= 5000 && ger!=fe ) ){
				//	cout << "Chyba dziala";
					return string( "NIE" );
				}
				
				swap( f1[index1], f2[index2] );
		
		
		
		//koniec sprawdzania
		
		
	
		int t = 0;
		int p; // najmniejszy dzielnik pierwszy liczby c
		while( primes[t] <= c ){
			if( c % primes[t] == 0 ){
				p = primes[t];
				break;
			}
			t++;
		}
		
	//	cout << "Jestem na koncu, p = " << p << endl;
		if( (p*a*b) / c <= 5000 && (p*a*b)/c != c ) return string( "NIE" );
		return string( "TAK" );
		
		
	}
}



inline string getSecondAnswer(){
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
inline bool setSumaRowna(){
	REP(i,2501) czySumaRowna[i] = false;
	for( int i=0; ktoresumy[i] > 0; i++ ){
		czySumaRowna[ ktoresumy[i] ] = true;
	}
	
}

void clearAll();
int main(){
	ios_base::sync_with_stdio(0);
	string s;
	
	getPrimes();
//	REP( i, primes.size() ) cout << primes[i] << " ";
	setSumaRowna();
	
//	REP( i, 300 ) if( czySumaRowna[i] ) cout << i << endl;
	
//	setCzySumaRowna();
	
	//*********************************************** cos dla preprocesingu
/*	ofstream str( "Preprocessing.txt" );
	
	for( int i=4; i<2480; i++ ){
		a = i;
		b = 0;
		if( getSecondAnswer() == "NIE" ){
			str << i << ",";
		}
	}
	cout << "Zakonczylem prace preprocessingu" << endl;
	
	str.close();*/
	
/*	ofstream str( "KiedyTak.txt" );
	int zakres = 130;
	for( int i=2; i<=zakres; i++ ){
		for( int k=2; k<=i; k++ ){
			a = i;
			b = k;
			if( getFirstAnswer( i,k ) == "NIE" && getSecondAnswer()=="NIE" && getThirdAnswer() == "TAK" ){
				str << i << " " << k << endl << "NIE" << endl << "NIE" << endl << "TAK" << endl << endl;
			//	cout << i << " " << k << endl;
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


