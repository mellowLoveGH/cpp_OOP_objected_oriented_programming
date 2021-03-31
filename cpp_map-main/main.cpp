#include <iostream> 
#include <string>
#include "MyMap.h"

using namespace std;

int main() {

	MyMap<string, int> M1(10);
	M1.insert("one", 1);
	M1.insert("two", 2);
	M1.insert("three", 3);
	if(M1["two"]) cout << *M1["two"] << endl;
	else cout << "No Match" << endl;
	if (M1["ten"]) cout << *M1["ten"] << endl;
	else cout << "No Match" << endl;

	MyMap<int, string> M2(10);
	M2.insert(10, "ten");
	M2.insert(20, "twenty");
	M2.insert(30, "thirty");
	if (M2[30]) cout << *M2[30] << endl;
	else cout << "No Match" << endl;

	system("pause");
	return 0;
}
