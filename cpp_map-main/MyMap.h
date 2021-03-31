#include <iostream>
#include <string>
using namespace std;

template <typename K, typename V>
class MyMap {
public:
	MyMap(int num) {
		keys = new K[num];
		values = new V[num];
		index = 0;
	}

	void insert(K k, V v) {
		keys[index] = k;
		values[index] = v;
		index++;
	}

	V* operator[] (K k) {
		int i = 0;
		while (keys[i] != k) {
			i++;
			if (i > index) {
				return NULL;
			}
		}

		V* v = &values[i];
		//cout << v << endl;
		return v;
	}

private:
	K *keys;
	V *values;
	int index;
};