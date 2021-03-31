#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "pmu.h"

#define NRUNS	1000
#define	NMEETS	50
//#define DEBUG

using namespace std;

int main(int argc, char** argv)
{
	// declare any variable you want

	srand(time(NULL));

	double total_score = 0;
	for (int n = 0; n < NRUNS; n++) {

		int score, my_pick = -1;
		pmu_init(NMEETS);

		//
		int min = 0;

		for (int i = 0; i < NMEETS; i++) {
			int cs = pmu_next();
			bool pick_this = false;

			// put your code here
			// example dumm code always picking the last
			if (min < cs) {
				min = cs;
				my_pick = min;
			}
			if (NMEETS > 30) {
				if (i == (NMEETS - 1) / 3) {
					pick_this = true;
				}
			}
			else {
				if (i == (NMEETS - 1)) {
					pick_this = true;
				}
			}


			if (pick_this == true) {				
				break;
			}
		}
		score = pmu_evaluate_and_clear(my_pick);
		total_score += score;
#ifdef DEBUG		
		cout << n + 1 << "th trial score is " << score << " for pick " << my_pick << endl;
#endif
	}
	cout << "NMEETS: " << NMEETS << endl;
	cout << "Final score is " << total_score / NRUNS / NMEETS << endl;

	system("pause");
	return 0;
}
