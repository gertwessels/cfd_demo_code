/*
 * LINALG.hpp
 *
 *  Created on: 11 Feb 2014
 *      Author: gwessels
 */

#ifndef LINALG_HPP_
#define LINALG_HPP_

#include <vector>

using namespace std;

namespace LinAlg
{
	template <typename T>
	class Matrix
	{
	public:
		Matrix(int n_rows);
		Matrix(int n_rows, int n_cols);
		Matrix(Matrix<T>& x);
		~Matrix();

		int getRows();
		int getColumns();
		T 	get(int row, int col);
		T*  getDiag();
		T* 	getList();

		void set(int row, int col, T value);

		void initList(T fill);
		void printMatrix();

		void transpose();
		void swapRow(int r1, int r2);
		void subtractRow(int r1, T factor, int r2);

		void add(Matrix<T> x);
		void add(T s);
		void subtract(Matrix<T>& x);
		void subtract(T s);
		// this x B = C
		void multiply(Matrix<T>& B, Matrix<T>& C);
		void multiply(T s);

		Matrix operator+ (const Matrix&) const;
		Matrix operator+ (const T) const;
		Matrix operator- (const Matrix&) const;
		Matrix operator- (const T) const;
	//	Matrix operator* (const Matrix&) const;
		Matrix operator* (const Matrix) const;
		Matrix operator* (const T) const;
	//	Matrix operator= (const Matrix&);
		void operator= (const Matrix&);

	protected:
		int n_rows;
		int n_cols;
		std::vector<T> list;
	};

	template <typename T>
	class Vector
	{
	public:
		Vector(int n_cells);
		Vector(int n_rows, int n_cols);
		Vector(Vector<T>& x);
		~Vector();

		int getRows();
		int getColumns();
		T 	get(int cell);
		T* 	getList();

		void set(int cell, T value);

		void initList(T fill);
		void printVector();

		void transpose();
		void swapCells(int c1, int c2);
		void subtractCells(int c1, T factor, int c2);

		void add(Vector<T> x);
		void add(T s);
		void subtract(Vector<T>& x);
		void subtract(T s);
		// this x B = C
		Matrix<T> multiply(Vector<T> v2);
		Vector<T> multiply(Matrix<T> M);
		void multiply(T s);

		Vector operator+ (const Vector&) const;
		Vector operator+ (const T) const;
		Vector operator- (const Vector&) const;
		Vector operator- (const T) const;
	//	Vector operator* (const Vector&) const;
		Matrix<T> operator* (const Vector) const;
	//	Vector operator* (const Matrix<T>) const;
		Vector operator* (const T) const;
	//	Vector operator= (const Vector&);
		void operator= (const Vector&);

	protected:
		int n_rows;
		int n_cols;
		std::vector<T> list;
	};

	class Solvers
	{
	public:
//		Vector<float> solveSystem(Matrix<float> A, Vector<float> b);
		void solveSystem(Matrix<float> A, Vector<float> b);

	};
}

#endif /* LINALG_HPP_ */
