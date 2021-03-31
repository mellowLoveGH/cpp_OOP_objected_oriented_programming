#include <iostream>
#include <list>
#include <string>
#include <iterator>
#include <algorithm>
using namespace std;

struct Champion {
	string name;
	int health;
};

list<Champion>::iterator operator+(list<Champion>::iterator it, const int num) {
	if (num <= 0)
		return it;

	for (int i = 0; i < num; i++)
	{
		it++;
	}
	return it;
}

list<Champion>::iterator operator-(list<Champion>::iterator it, const int num) {
	if (num <= 0)
		return it;

	for (int i = 0; i < num; i++)
	{
		it--;
	}
	return it;
}

void show_list(list<Champion> LIST) {
	std::list<Champion>::iterator it;
	for (it = LIST.begin(); it != LIST.end(); ++it) {
		cout << "(" << it->name << ", " << it->health << ")-";
	}
	cout << endl;
}

bool compareByName(const Champion& lhs, const Champion& rhs) {
	return lhs.name < rhs.name;
}

void sort_by_name(list<Champion>& LIST) {
	LIST.sort(compareByName);
}

void remove(string name, list<Champion>& LIST) {

	std::list<Champion>::iterator it = LIST.begin();
	while (!(it->name == name)) {
		it++;
	}

	LIST.erase(it);
}


int main() {
	string name_list[] = { "Vayne", "Mundo", "Elise", "Kayle" };
	double health_list[] = { 498, 582, 529, 574 };
	list<Champion> LIST;

	for (int i = 0; i < 4; i++) {
		Champion C = { name_list[i], health_list[i] };
		LIST.push_back(C);
	}
	show_list(LIST);

	Champion C = { string("Ashe"), 527 };
	LIST.insert(LIST.begin() + 2, C);
	show_list(LIST);

	Champion D = { string("Sona"), 482 };
	LIST.insert(LIST.end() - 1, D);
	show_list(LIST);

	sort_by_name(LIST);
	show_list(LIST);

	remove("Mundo", LIST);
	show_list(LIST);

	system("pause");
	return 0;
}
