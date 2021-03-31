#include <iostream>
#include <cstdlib>
#include "matrix.h"

using namespace std;
double * subMatrix(double *mData, int n, int i, int j);

Matrix::Matrix(int nr, int nc)
{
	mNrow = nr;
	mNcol = nc;
	mData = new double[nr * nc];
	for (int i = 0; i < nr * nc; i++)
	{
		mData[i] = 0;
	}
}

Matrix::~Matrix()
{
	//delete[] mData;
}

int Matrix::getNrow()
{
	return mNrow;
}

int Matrix::getNcol()
{
	return mNcol;
}

void Matrix::fillRandInt(int start, int end)
{
	Matrix A = *this;
	for (int i = 0; i < A.mNrow*A.mNcol; i++) {
		A.mData[i] = rand() % (end - start + 1) + start;
	}
}

bool Matrix::add(Matrix &M)
{
	if (M.getNcol() != mNcol || M.getNrow() != mNrow)
		return false;

	Matrix A = *this;
	for (int i = 0; i < mNrow; i++) {
		for (int j = 0; j < mNcol; j++) {
			A.mData[i*A.mNcol + j] = A.mData[i*A.mNcol + j] + M.mData[i*A.mNcol + j];
		}
	}
	return true;
}

bool Matrix::multiply(Matrix &M)
{
	Matrix A = *this;
	if (A.mNcol != M.mNrow) {
		return false;
	}
	Matrix aa(A.mNrow, M.mNcol);
	double s = 0;
	for (int i = 0; i < A.mNrow; i++)
	{
		for (int m = 0; m < M.mNcol; m++)
		{
			for (int j = 0; j < A.mNcol; j++)
			{
				s = s + A.mData[i*A.mNcol + j] * M.mData[j*M.mNcol + m];
			}
			aa.mData[i*aa.mNcol + m] = s;
			s = 0;
		}
	}
	*this = aa;

	return true;
}

bool Matrix::transpose()
{
	Matrix A = *this;
	int col = A.mNrow;
	int row = A.mNcol;
	Matrix aa(row, col);

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			aa.mData[i*col + j] = A.mData[j*A.mNcol + i];
		}
	}
	*this = aa;
	return true;
}

void Matrix::show()
{
	Matrix A = *this;
	for (int i = 0; i < A.mNrow*A.mNcol; i++) {
		cout << A.mData[i] << "\t";

		int line = i + 1;
		if (line % A.mNcol == 0) {
			cout << endl;
		}
	}
}

double Matrix::det()
{
	if (mNrow!= mNcol) {
		cout << "the matrix that is not square has no determinant" << endl;
		return -1.0;
	}

	if (mNrow == 1) {
		return mData[0];
	}
	if (mNrow == 2) {
		return mData[0]* mData[3] - mData[1] * mData[2];
	}
	if (mNrow == 3) {
		double sum = 0;
		double* a00 = subMatrix(mData, 3, 0, 0);
		sum = sum + mData[0] * (a00[0] * a00[3] - a00[1] * a00[2]);
		double* a01 = subMatrix(mData, 3, 0, 1);
		sum = sum - mData[1] * (a01[0] * a01[3] - a01[1] * a01[2]);
		double* a02 = subMatrix(mData, 3, 0, 2);
		sum = sum + mData[2] * (a02[0] * a02[3] - a02[1] * a02[2]);
		return sum;
	}

	return 0.0;
}

double * subMatrix(double *mData, int n, int k1, int k2) {
	int L = n - 1;
	int count = 0;
	Matrix A(L, L);
	double* sub = new double[L * L];

	for (int i = 0; i < n; i++) {
		if (i == k1) {
			continue;
		}
		for (int j = 0; j < n; j++) {
			if (j == k2) {
				continue;
			}
			sub[count] = mData[i*n + j];
			count++;
		}
	}

	return sub;
}
