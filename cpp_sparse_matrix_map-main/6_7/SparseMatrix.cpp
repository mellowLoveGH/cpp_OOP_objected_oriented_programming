#include <fstream>
#include <sstream>
#include <iomanip>
#include <math.h>
#include <set>
#include "SparseMatrix.h"

void print(map<int, map<int, double> > mat) {
	map<int, map<int, double> >::iterator it = mat.begin();
	while (it != mat.end()) {
		map<int, double> m = it->second;
		map<int, double>::iterator subit = m.begin();
		while (subit != m.end()) {
			std::cout << it->first << ", " << subit->first << " -- " << subit->second << endl;
				
			subit++;
		}
		it++;
	}
	std::cout << endl;
}

void Merge(double rcdata[], double vdata[], int l, int q, int r) {
	int n = r - l + 1;//临时数组存合并后的有序序列
	double* tmp = new double[n];
	double* tmp1 = new double[n];
	int i = 0;
	int left = l;
	int right = q + 1;
	while (left <= q && right <= r) {
		if (rcdata[left] <= rcdata[right]) {
			tmp[i] = rcdata[left];
			tmp1[i] = vdata[left];//
			left++;
		}
		else {
			tmp[i] = rcdata[right];
			tmp1[i] = vdata[right];//
			right++;
		}
		i++;
	}		
	while (left <= q) {
		tmp[i] = rcdata[left];
		tmp1[i] = vdata[left];//
		left++;
		i++;
	}		
	while (right <= r) {
		tmp[i] = rcdata[right];
		tmp1[i] = vdata[right];//
		right++;
		i++;
	}		
	for (int j = 0; j < n; ++j) {
		rcdata[l + j] = tmp[j];
		vdata[l + j] = tmp1[j];//
	}
		
	delete[] tmp;//删掉堆区的内存
	delete[] tmp1;
}

void MergeSort(double rcdata[], double vdata[], int l, int r) {
	if (l == r)
		return;  //递归基是让数组中的每个数单独成为长度为1的区间
	int q = (l + r) / 2;
	MergeSort(rcdata, vdata, l, q);
	MergeSort(rcdata, vdata, q + 1, r);
	Merge(rcdata, vdata, l, q, r);
}


//O(n)
void SparseMatrix::resize(int nr, int nc) {	
	row = nr;
	col = nc;
	//
	map<int, map<int, double> > matrix;
	map<int, map<int, double> >::iterator it = mat.begin();
	while (it != mat.end()) {
		int r = it->first;
		if (r <= row) {
			map<int, double> m1 = it->second;
			map<int, double>::iterator subit = m1.begin();
			while (subit != m1.end()) {
				int c = subit->first;
				if (c <= col) {
					matrix[r][c] = subit->second;
				}
				subit++;
			}
		}
		it++;
	}
	mat = matrix;
}

int SparseMatrix::getNumRows() {
	return row;
}

int SparseMatrix::getNumCols() {
	return col;
}

//O(n)
int SparseMatrix::getNumOfNonZeros() {
	int len = 0;
	map<int, map<int, double> >::iterator it = mat.begin();
	while (it != mat.end()) {
		map<int, double> m1 = it->second;
		map<int, double>::iterator subit = m1.begin();
		while (subit != m1.end()) {
			if (subit->second != 0){
				len++;
			}
			subit++;
		}		
		it++;
	}

	return len;
}

bool SparseMatrix::readFromFile(string filename) {
	string line;
	ifstream infile(filename);	

	int number = 0;

	if (infile) {
		while (getline(infile, line)) {
			//cout << line << endl;
			stringstream numbers;
			numbers << line;
			if (!numbers.eof()) {
				double r;
				double c;
				double d;
				numbers >> r;
				numbers >> c;
				numbers >> d;
				//cout << r << ", " << c << ", " << d << endl;

				if (row < r) {
					row = r;
				}
				if (col < c) {
					col = c;
				}
				
				setValue(r, c, d);
				number++;
				SUM = SUM + d;
				//s = s + d;
			}
		}
		
	}
	else {
		return false;
	}
	infile.close();
	//std::cout << "---" << row << ", " << col << endl;
	length = number;
	
	getTranspose();
	return true;
}

//O(1)
void SparseMatrix::setValue(int r, int c, double val) {
	if (mat.count(r) == 1) {
		mat[r][c] = val;
	}
	else {
		map<int, double> m;
		m.insert({ c, val });
		mat.insert({ r, m });
	}	
}

//O(1)
double SparseMatrix::getValue(int row, int col) {
	if (mat.count(row) == 1) {
		if (mat[row].count(col) == 1) {
			return mat[row][col];
		}
	}
	return 0;
}

//O(n), if M.length > this.length, n = M.length
SparseMatrix SparseMatrix::operator+(SparseMatrix& M) {	
	if (row != M.getNumRows() || col != M.getNumCols()) {
		return NULL;
	}

	int counter = 0;
	SparseMatrix C(row, col);
	map<int, map<int, double> >::iterator it = mat.begin();
	map<int, map<int, double> >::iterator itM = M.mat.begin();
	//
	while (it != mat.end() && itM != M.mat.end()) {
		//r, rm
		int r = it->first;
		int rM = itM->first;
		//increment the smaller
		if (r < rM) {
			map<int, double> m = it->second;
			map<int, double>::iterator subit = m.begin();
			while (subit != m.end()) {
				int c = subit->first;
				double v = subit->second;
				//
				C.mat[r][c] = v;
				subit++;

				counter++;
			}
			it++;
		}
		//increment both
		else if (r == rM) {
			map<int, double> m = it->second;
			map<int, double>::iterator subit = m.begin();

			map<int, double> mM = itM->second;
			map<int, double>::iterator subitM = mM.begin();
			//
			while (subit != m.end() && subitM != mM.end()) {
				int c = subit->first;
				double v = subit->second;

				int cM = subitM->first;
				double vM = subitM->second;
				////increment the smaller
				if (c < cM) {
					C.mat[r][c] = v;
					subit++;
				}
				//increment both
				else if (c == cM) {
					C.mat[r][c] = v + vM;
					if (C.mat[r][c] == 0) {
						C.mat[r].erase(c);
					}
					subitM++;
					subit++;
				}
				else {
					C.mat[r][cM] = vM;
					subitM++;
				}
				counter++;
			}
			//
			while (subit != m.end()){
				int c = subit->first;
				double v = subit->second;
				C.mat[r][c] = v;
				subit++;
			}
			//
			while (subitM != mM.end()) {
				int c = subitM->first;
				double v = subitM->second;
				C.mat[r][c] = v;
				subitM++;
			}
			it++;
			itM++;
		}
		//increment the smaller
		else {
			map<int, double> m = itM->second;
			map<int, double>::iterator subit = m.begin();
			while (subit != m.end()) {
				int c = subit->first;
				double v = subit->second;
				//
				C.mat[rM][c] = v;
				subit++;

				counter++;
			}
			itM++;
		}
	}

	//
	while (it != mat.end()) {
		map<int, double> m = it->second;
		map<int, double>::iterator subit = m.begin();
		while (subit != m.end()) {
			int c = subit->first;
			double v = subit->second;
			//
			C.mat[it->first][c] = v;
			subit++;

			counter++;
		}
		it++;
	}

	while (itM != M.mat.end()) {
		map<int, double> m = itM->second;
		map<int, double>::iterator subit = m.begin();
		while (subit != m.end()) {
			int c = subit->first;
			double v = subit->second;
			//
			C.mat[it->first][c] = v;
			subit++;

			counter++;
		}
		itM++;
	}
	C.length = length;
	//cout << length << ", " << M.length << ",  " << counter << endl;
	return C;	
}

//O(n), if M.length > this.length, n = M.length
SparseMatrix SparseMatrix::operator-(SparseMatrix& M) {
	if (row != M.getNumRows() || col != M.getNumCols()) {
		return NULL;
	}

	int counter = 0;
	SparseMatrix C(row, col);
	map<int, map<int, double> >::iterator it = mat.begin();
	map<int, map<int, double> >::iterator itM = M.mat.begin();
	//
	while (it != mat.end() && itM != M.mat.end()) {
		//r, rm
		int r = it->first;
		int rM = itM->first;
		//
		if (r < rM) {
			map<int, double> m = it->second;
			map<int, double>::iterator subit = m.begin();
			while (subit != m.end()) {
				int c = subit->first;
				double v = subit->second;
				//
				C.mat[r][c] = v;
				subit++;

				counter++;
			}
			it++;
		}
		else if (r == rM) {
			map<int, double> m = it->second;
			map<int, double>::iterator subit = m.begin();

			map<int, double> mM = itM->second;
			map<int, double>::iterator subitM = mM.begin();
			//
			while (subit != m.end() && subitM != mM.end()) {
				int c = subit->first;
				double v = subit->second;

				int cM = subitM->first;
				double vM = subitM->second;

				if (c < cM) {
					C.mat[r][c] = v;
					subit++;
				}
				else if (c == cM) {
					C.mat[r][c] = v - vM;
					if (C.mat[r][c] == 0) {
						C.mat[r].erase(c);
					}

					subitM++;
					subit++;
				}
				else {
					C.mat[r][cM] = -vM;
					subitM++;
				}
				counter++;
			}
			//
			while (subit != m.end()) {
				int c = subit->first;
				double v = subit->second;
				C.mat[r][c] = v;
				subit++;
			}
			//
			while (subitM != mM.end()) {
				int c = subitM->first;
				double v = subitM->second;
				C.mat[r][c] = -v;
				subitM++;
			}

			it++;
			itM++;
		}
		else {
			//
			map<int, double> m = itM->second;
			map<int, double>::iterator subit = m.begin();
			while (subit != m.end()) {
				int c = subit->first;
				double v = subit->second;
				//
				C.mat[rM][c] = -v;
				subit++;

				counter++;
			}
			itM++;
		}
	}

	//
	while (it != mat.end()) {
		map<int, double> m = it->second;
		map<int, double>::iterator subit = m.begin();
		while (subit != m.end()) {
			int c = subit->first;
			double v = subit->second;
			//
			C.mat[it->first][c] = v;
			subit++;

			counter++;
		}
		it++;
	}

	while (itM != M.mat.end()) {
		map<int, double> m = itM->second;
		map<int, double>::iterator subit = m.begin();
		while (subit != m.end()) {
			int c = subit->first;
			double v = subit->second;
			//
			C.mat[it->first][c] = -v;
			subit++;

			counter++;
		}
		itM++;
	}
	C.length = length;
	//cout << length << ", " << M.length << ",  " << counter << endl;
	return C;
}

SparseMatrix SparseMatrix::operator*(SparseMatrix& M) {
	if (col != M.getNumRows())
		return NULL;

	int counter = 0;
	//transpose
	map<int, map<int, double>> colMat = M.getTranspose();	
	//print(mat);
	//print(colMat);

	SparseMatrix C(row, M.getNumCols());
	map<int, map<int, double> >::iterator it = mat.begin();
	while (it != mat.end()) {
		int r = it->first;
		//
		map<int, double> m1 = it->second;
		vector<int> rs(m1.size());
		set<int> cs;
		int rsi = 0;
		map<int, double>::iterator subit = m1.begin();
		while (subit != m1.end()) {
			int c = subit->first;
			double v = subit->second;
			rs[rsi] = c;

			if (M.mat.count(c) == 1) {
				map<int, double> colM = M.mat[c];
				map<int, double>::iterator colit = colM.begin();
				while (colit != colM.end()) {
					int cn = colit->first;

					cs.insert(cn);
					colit++;

					counter++;
				}
			}

			rsi++;
			subit++;			
		}
		
		//
		set<int>::iterator col_it = cs.begin();
		while (col_it != cs.end()) {
			//cout << "   " << col_it->first;
			double s = 0;
			//
			map<int, double> m1 = colMat[*col_it];
			for (int i = 0; i < rs.size(); i++)
			{
				double v1 = mat[r][rs[i]];
				double v2 = 0;
				if (m1.count(rs[i]) == 1) {
					v2 = m1[rs[i]];
				}				
				s = s + v1 * v2;

				counter++;
			}
			//cout << "(" << r << ", " << col_it->first << "), " << s << endl;
			if (s != 0) {
				C.setValue(r, *col_it, s);
			}

			col_it++;
		}
		
		it++;
	}
	C.length = length;
	//cout << length << ", " << M.length << ",  " << counter << endl;
	return C;
}

bool SparseMatrix::operator==(SparseMatrix& M) {
	return true;
}

SparseMatrix SparseMatrix::operator-() {
	return NULL;
}

void SparseMatrix::transpose() {
	map<int, map<int, double> >::iterator it = mat.begin();
	while (it != mat.end()) {
		int r = it->first;
		map<int, double> m1 = it->second;
		map<int, double>::iterator subit = m1.begin();
		while (subit != m1.end()) {
			int c = subit->first;
			double v = subit->second;
			if (transposeMat.count(c) == 1) {
				transposeMat[c][r] = v;
			}
			else {
				map<int, double> m;
				m.insert({ r, v });
				transposeMat.insert({ c, m });
			}
			subit++;
		}
		it++;
	}
}

map<int, map<int, double> >  SparseMatrix::getTranspose() {
	if (transposeMat.size() == 0) {
		transpose();
	}
	return transposeMat;
}

double SparseMatrix::rowSum(int row) {
	if (mat.count(row) == 0) {
		return 0;
	}

	double rsum = 0;
		map<int, double> m1 = mat[row];
		map<int, double>::iterator subit = m1.begin();
		while (subit != m1.end()) {
			int c = subit->first;
			double v = subit->second;
			rsum = rsum + v;
			subit++;
		}

	return rsum;
}

double SparseMatrix::colSum(int col) {
	//transpose
	map<int, map<int, double>> colMat = getTranspose();
	if (colMat.count(col) == 0) {
		return 0;
	}

	double csum = 0;
	map<int, double> m1 = colMat[row];
	map<int, double>::iterator subit = m1.begin();
	while (subit != m1.end()) {
		int c = subit->first;
		double v = subit->second;
		csum = csum + v;
		subit++;
	}

	return csum;
}

double SparseMatrix::sum() {
	/*
	double s = 0;
	map<int, map<int, double> >::iterator it = mat.begin();
	while (it != mat.end()) {
		map<int, double> m = it->second;
		map<int, double>::iterator subit = m.begin();
		while (subit != m.end()) {
			s = s + subit->second;
			subit++;
		}
		it++;
	}
	*/

	return SUM;
}

bool SparseMatrix::isAllAbsLessThan(double val) {
	map<int, map<int, double> >::iterator it = mat.begin();
	while (it != mat.end()) {
		map<int, double> m = it->second;
		map<int, double>::iterator subit = m.begin();
		while (subit != m.end()) {
			int c = subit->first;
			double v = subit->second;
			//
			if (v > val) {
				return false;
			}
			subit++;
		}
		it++;
	}

	return true;
}

