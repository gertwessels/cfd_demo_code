/*
 * Mat_test.cpp
 *
 *  Created on: 07 Feb 2014
 *      Author: gwessels
 */
#include "linalg.hpp"
#include <iostream>

using namespace std;
using namespace LinAlg;

int main(int argc, char* argv[])
{
//	Initialize variables
	int n_rows = 4;
	int n_cols = 5;
	int ind;
	Matrix<int> matA(n_rows,n_cols);

//	Assign values to matrix
	int temp = 1;
	for(ind=0;ind<n_rows;ind++)
	{
		for(int cols=0; cols<n_cols; cols++)
			matA.set(ind,cols,temp++);
	}
//	Print matrix to screen
	matA.printMatrix();

//	Retrieve diagonal of matrix and print to screen
	int* diag = matA.getDiag();
	ind=0;
	cout << endl;
	cout << "Diagonal: \n";
	while(ind<n_rows)
		cout << diag[ind++] << "\t";
	cout << "\n" << endl;

// Operators: Set up 3 matrices.  A(m,n), B(n,p), AA(m,n)
	int m=3;
	int n=2;
	int p=3;
	Matrix<float> A(m,n);
	Matrix<float> AA(m,n);
	Matrix<float> B(n,p);
	Matrix<float> prodAB(m,p);
	Matrix<float> prodBA(n,n);

	temp=1;
	for(int cols=0; cols<n; cols++)
	{
		for(int rows=0; rows<m; rows++)
		{
			A.set(rows,cols,rows+1);
			AA.set(rows,cols,temp++);
		}
		for(int cols2=0; cols2<p; cols2++)
			B.set(cols,cols2,cols2+temp);
	}

	Matrix<float> tempA(1);
	Matrix<float> tempB(B);

	cout << "A: \n" << endl;
	A.printMatrix();
	cout << "\nAA: \n" << endl;
	AA.printMatrix();
	cout << "\nB: \n" << endl;
	B.printMatrix();

// Operators: tempA=A;
	cout << "\ntempA = A\n" << endl;
	tempA = A;
	tempA.printMatrix();

// Operators: A+AA
	cout << "\nA + AA =\n" <<endl;
	//tempA.add(AA);
	tempA = tempA+AA;
	tempA.printMatrix();
// Operators: B+11
	cout << "\nB + 11 =\n" <<endl;
	//tempB.add(11.0);
	tempB = tempB+11.0;
	tempB.printMatrix();
// Operators: A-AA
	Matrix<float> tempA2(A);
	cout << "\nA - AA =\n" <<endl;
//	tempA2.subtract(AA);
	tempA2 = tempA2 - AA;
	tempA2.printMatrix();
// Operators: B-6
	cout << "\nB - 6 =\n" <<endl;
//	tempB.subtract(6);
	tempB = tempB - 6;
	tempB.printMatrix();
// Operators: A*B
	cout << "\nA x B =\n" <<endl;
	A.multiply(B,prodAB);
	//prodAB = A*B;
	prodAB.printMatrix();
// Operators: B*A
	cout << "\nB x A =\n" <<endl;
	B.multiply(A,prodBA);
	prodBA.printMatrix();
// Operators: B*5
	cout << "\nB x 5 =\n" <<endl;
	B.multiply(5);
	B.printMatrix();
	// Operators: BT
	cout << "\nTranspose(B) =\n" <<endl;
	B.transpose();
	B.printMatrix();

//	==== LINALG ====

	Matrix<float> C(3);
	std::vector<float> b(3);

	C.set(0,0,3);
	C.set(0,1,-4);
	C.set(0,2,5);
	C.set(1,0,-3);
	C.set(1,1,2);
	C.set(1,2,1);
	C.set(2,0,6);
	C.set(2,1,8);
	C.set(2,2,-1);

	b[0] = -1;
	b[1] = 1;
	b[2] = 35;

	//std::vector<float> x = LinAlg::solve(C,b);




}

