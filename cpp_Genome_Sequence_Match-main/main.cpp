#include <fstream>
#include <iostream>
#include <string>
using namespace std;

//for two strings with same length
//calculate the matches
int match(string str1, string str2) {
	int L1 = str1.length();
	int L2 = str2.length();

	if (L1 == L2) {
		int count = 0;
		for (int i = 0; i < L1; i++)
		{
			if (str1[i] == str2[i]) {
				count++;
			}
		}
		return count;
	}
	return 0;
}

//for every line from tp53.txt
//calculate the matches with substring, allowing mismatches
int matchStr(string str, string sub, int mis) {

	int N = 0;

	int L1 = str.length();
	int L2 = sub.length();

	if (L1 >= L2) {
		int start = 0;
		int end = start + L2;
		while (end < L1) {
			end = start + L2;

			string str1 = str.substr(start, L2);
			//cout << str1 << endl;

			int count = match(str1, sub);
			if (count + mis >= L2) {
				N++;
			}

			start++;
		}

	}

	return N;
}

int main()
{

	//read file
	ifstream infile;
	string path = "tp53.txt";
	infile.open(path);

	string sub = "ACCGTT";
	int mis = 2;
	//sub = "TTCCTAGCG";
	//mis = 3;

	cout << "the substring: " << sub << endl;
	
	string str;
	int num = 0;
	int N = 0;
	while (!infile.eof()) {
		getline(infile, str);
		if (num > 0) {
			N = N + matchStr(str, sub, mis);
		}
		num++;
	}
	cout << "how many: " << N << endl;

	//close
	infile.close();
	system("pause");
	return 0;
}