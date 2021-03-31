# cpp_sparse_matrix_map
c++, sparse matrix, read data, store, operations, using map data-structure

sparse matrix:
An n-by-m matrix is usually described by nm numbers, 
but the description with non-zero values and their coordinates are also possible.
Such description is quite useful for a large sparse matrix, 
of which dimension is large but most elements are zero.

For example, to describe a 1M x 1M matrix with 1M non-zero elements, 
the ordinary description still requires 10^12 numbers 
but the sparse description only requires 3x10^6 numbers. 
In the sparse matrix description, if a zero element is set as a non-zero value, 
a new table entry should be added.
If a non-zero element is set as zero, then the corresponding element should be removed.

In practical programing with floating numbers, checking the exact value is not easy. 
So, we often consider two value a and b are equal if |a-b|<DELTA. 
In this project, use 10^-10 for DELTA. 
Also keep in mind that reducing the computation time is important in this project.
You can check your computation time in test4()

1. data structure for a sparse matrix.
2. how to find the corresponding value given row and column as well as how to insert and delete the sparse matrix table entries.
setValue() and getValue()
3. implementation of readFromFile(), which reads a sparse matrix table from a text file. 
You can refer the file format from data2_1.txt. How long it takes to read data4_4.txt file?
Run test1() to test4() and report the screen shot of the result. 

