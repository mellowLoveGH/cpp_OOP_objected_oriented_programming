/********************************************************
 This is the code you need to modify.
 
 IMPORTANT NOTE
 1. Change "2016000000" in the filename, class name, 
   preprocessing statements to your real student id.
 2. Change "MyName" in the constructor to your real name.
 
 These two changes are very important to grade your submission.
 If you miss the changes, you will have a penalty.
 
**********************************************************/

// change "2016000000" to your real student id
#ifndef _BINGO_2016000000_H_
#define _BINGO_2016000000_H_

#include "setting.h"
#include "Bingo.h"

// change "2016000000" to your real student id
class Bingo_2016000000 : public Bingo
{
public:
	// change "2016000000" to your real student id
	Bingo_2016000000() {
		mName = "MyName";		// change "MyName" to your real name in English
	}
	// change "2016000000" to your real student id
	~Bingo_2016000000() { /* add whatever */ }
	
	int myCall(int *itscalls,int *mycalls,int ncalls);
	
private:
	// declare whatever you want
};


/********************************************************
  itcalls: a vector of int variables with size of "ncalls"
           showing the opponent's calls for the previous turns
  mycalls: a vector of int variables with size of "ncalls"
           showing my calls for the previous turns
  ncalls: number of previous turns
**********************************************************/
int Bingo_2016000000::myCall(int *itscalls,int *mycalls,int ncalls)
{
	// implement your strategy
	return 1;
}

#endif
