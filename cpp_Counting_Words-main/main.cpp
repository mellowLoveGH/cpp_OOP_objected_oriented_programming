#include <iostream>
#include <string>
#include<vector>
#include <map> 
#include <fstream>
#include <sstream>
#include<algorithm>

using namespace std;

string removeMarks(string str) {
	int size = str.length();
	string w = "";
	for (int i = 0; i < size; i++)
	{
		char ch = str[i];
		if (ch >= 'a' && ch <= 'z') {
			w = w + ch;
		}
		else if (ch >= 'A' && ch <= 'Z') {
			//ch = ch + 32;
			w = w + ch;
		}
		else {

		}
	}
	return w;
}

int main()
{
	// filestream variable file 
	fstream file;
	string word, t, q, filename;

	// filename of the file 
	filename = "text1.txt";

	// opening file 
	file.open(filename.c_str());

	map<string, int> collection;
	// extracting words from the file 
	while (file >> word)
	{
		// displaying content 
		//cout << word << endl;
		//word = removeMarks(word);

		if (word == "") {
			continue;
		}

		if (collection.count(word) == 1) {
			collection[word] = collection[word] + 1;
		}
		else {
			collection[word] = 1;
		}
	}

	int number = 0;
	map<string, int>::iterator it = collection.begin();
	map<int, vector<string> > list;
	while (it != collection.end()) {
		string w = it->first;
		int frequency = it->second;

		if (list.count(frequency) == 1) {
			//int num = list[frequency].size();
			list[frequency].push_back(w);
		}
		else {
			vector<string> sublist;
			sublist.push_back(w);
			list[frequency] = sublist;
		}
		it++;
	}

	//
	int print_size = 25;
	map<int, vector<string> >::reverse_iterator list_it = list.rbegin();
	while (list_it != list.rend()) {
		int fre = list_it->first;
		vector<string> vc = list_it->second;
		
		
		if (vc.size() == 1) {
			number++;
		}

		if (print_size > 0) {
			for (int i = 0; i < vc.size(); i++)
			{
				cout << vc[i] << " ";
			}
			cout << ": " << fre;
			cout << endl;
		}

		print_size--;

		list_it++;
	}
	cout << number << endl;
	system("pause");
	return 0;
}
