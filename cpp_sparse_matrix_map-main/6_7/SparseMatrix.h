#ifndef _SPARSE_MATRIX_H_
#define _SPARSE_MATRIX_H_

#include <iostream>
#include <string>
#include<vector>
#include <map> 

using namespace std;

class SparseMatrix
{
public:
	// nr x nc sparse matrix is constructed. If they are not given, 1x1 matrix by default 
	SparseMatrix(int nr = 0, int nc = 0) {
		row = nr;
		col = nc;		
	}
	~SparseMatrix() { }

	// resize the matrix to nr x nc. 
	// if increased, the added parts are filled with zeros
	void resize(int nr, int nc);

	int getNumRows();	// return number of rows
	int getNumCols();	// return number of columns
	int getNumOfNonZeros();	// return number of non-zero elements

	// file access
	// read a sparse matrix from a text file
	// the file format is "row col val" 
	bool readFromFile(string filename);

	// data access
	void setValue(int row, int col, double val); // write val at (i,j)
	double getValue(int row, int col); // read value of (i,j)

	// operations
	SparseMatrix operator+(SparseMatrix& M); // matrix addition
	SparseMatrix operator-(SparseMatrix& M); // matrix subtraction
	SparseMatrix operator*(SparseMatrix& M); // matrix multiplication
	bool operator==(SparseMatrix& M);	// true if all elements are equal
	SparseMatrix operator-();				// inverting the sign of all elements

	//
	void transpose();
	map<int, map<int, double> >  getTranspose();

	// summary
	double rowSum(int row); // calculate the sum of elements in a "row"-th row
	double colSum(int col); // calculate the sum of elements in a "col"-th column
	double sum(); // calculate the sum of all elements
	bool isAllAbsLessThan(double val); // true if the absolute value of all elements are less than val


private:
	// declare whatever you want
	int row;
	int col;
	vector<double> data;
	map<int, map<int, double> > mat;
	map<int, map<int, double> > transposeMat;
	int length = 0;
	int mode = 1000 * 100 * 2;
	double SUM = 0;
};


#endif
