/*
 * matrix.cpp
 *
 *  Created on: 11 Feb 2014
 *      Author: gwessels
 */

#include "linalg.hpp"
#include <iostream>

using namespace std;

namespace LinAlg
{
	template<typename T>
	Matrix<T>::Matrix(int _r)
	{
		n_rows =_r;
		n_cols =_r;
		list.resize(_r*_r);
		this->initList(0);
	}

	template<typename T>
	Matrix<T>::Matrix(int _r, int _c)
	{
		n_rows =_r;
		n_cols =_c;
		list.resize(_r*_c);
		this->initList(0);
	}

	template<typename T>
	Matrix<T>::Matrix(Matrix<T>& _x)
	{
		this->n_rows	=_x.n_rows;
		this->n_cols	=_x.n_cols;
		this->list 		=_x.list;
	}

	template<typename T>
	Matrix<T>::~Matrix(void)
	{
		if(list.size()>0)
		{
			this->list.clear();
			this->n_rows=0;
			this->n_cols=0;
		}
	}

	template<typename T>
	int Matrix<T>::getRows()
	{
		return n_rows;
	}

	template<typename T>
	int Matrix<T>::getColumns()
	{
		return n_cols;
	}

	template<typename T>
	T Matrix<T>::get(int _r, int _c)
	{
		return list[n_cols*_r+_c];
	}

	template<typename T>
	T* Matrix<T>::getDiag()
	{
		std::vector<T> _diag;
		_diag.resize(n_rows);
		for(int _r=0;_r<n_rows;_r++)
			_diag[_r] = list[_r*n_cols+_r];
		return _diag;
	}

	template<typename T>
	T* Matrix<T>::getList()
	{
		return list;
	}

	template<typename T>
	void Matrix<T>::set(int _r, int _c, T _val)
	{
		list[n_cols*_r+_c] = _val;
	}

	template<typename T>
	void Matrix<T>::initList(T _fill)
	{
		for(int i=0;i<(n_rows*n_cols);i++)
			list[i]=_fill;
	}

	template<typename T>
	void Matrix<T>::printMatrix()
	{
		for(int _r=0; _r<n_rows; _r++)
		{
			for(int _c=0; _c<n_cols; _c++)
				cout << list[n_cols*_r+_c] <<"\t";
			cout << "\n" << endl;
		}
	}

	template<typename T>
	void Matrix<T>::transpose()
	{
		Matrix<T> _temp(n_cols,n_rows);
		//_temp.list = this->list;
		for(int _r=0; _r<n_rows; _r++)
		{
			for(int _c=0; _c<n_cols; _c++)
				_temp.set(_c,_r,this->get(_r,_c));
		}
		this->list 	 = _temp.list;
		this->n_rows = _temp.n_rows;
		this->n_cols = _temp.n_cols;
	}

	template<typename T>
	void Matrix<T>::swapRow(int r1, int r2)
	{
		T _placeholder;
		for(int _c=0; _c<n_cols; _c++)
		{
			_placeholder = this->get(r1,_c);
			this->set(r1,_c,this->get(r2,_c));
			this->set(r2,_c,_placeholder);
		}
	}
	// Subtract one row from another
	// r1 -= factor*r2
	template<typename T>
	void Matrix<T>::subtractRow(int r1, T factor, int r2)
	{
		for(int _c=0; _c<n_cols; _c++)
			this->set(r1,_c,this->get(r1,_c)-factor*(this->get(r2,_c)));
	}

	template<typename T>
	void Matrix<T>::add(Matrix<T> _mat)
	{
		try
			{
				//	Test matrix compatibility
				if(this->n_rows!=_mat.n_rows)
					throw 0;
				if(this->n_cols!=_mat.n_cols)
					throw 1;
				// Addition operator
				for(int i=0; i<this->list.size(); i++)
					this->list[i] += _mat.list[i];
			}
			catch(int x)
			{
				if(x==0)
					cout << "Rows of matrices aren't equal." << endl;
				if(x==1)
					cout << "Columns of matrices aren't equal." << endl;
			}
	}

	template<typename T>
	void Matrix<T>::add(T _scalar)
	{
		for(int i=0; i<this->list.size(); i++)
			this->list[i] += _scalar;
	}

	template<typename T>
	void Matrix<T>::subtract(Matrix<T>& _mat)
	{
		try
			{
				//	Test matrix compatibility
				if(this->n_rows!=_mat.n_rows)
					throw 0;
				if(this->n_cols!=_mat.n_cols)
					throw 1;
				// Addition operator
				for(int i=0; i<this->list.size(); i++)
					this->list[i] -= _mat.list[i];
			}
			catch(int x)
			{
				if(x==0)
					cout << "Rows of matrices aren't equal." << endl;
				if(x==1)
					cout << "Columns of matrices aren't equal." << endl;
			}
	}

	template<typename T>
	void Matrix<T>::subtract(T _scalar)
	{
		for(int i=0; i<this->list.size(); i++)
			this->list[i] -= _scalar;
	}

	template<typename T>
	void Matrix<T>::multiply(Matrix& B,Matrix& C)
	{
		try
		{
			if(this->n_cols!=B.n_rows)
				throw 0;

			for(int m=0; m<this->n_rows; m++)
			{
				for(int p=0; p<B.n_cols; p++)
				{
					T _temp = 0;
					for(int n=0; n<this->n_cols; n++)
					{
						_temp = _temp + this->get(m,n)*B.get(n,p);
					}
					C.set(m,p,_temp);
				}
			}
			//return C;
		}
		catch(int x)
		{
			if(x==0)
				cout << "Matrix sizes prohibit multiplication" << endl;
		}
	}

	template<typename T>
	void Matrix<T>::multiply(T _scalar)
	{
		for(int i=0; i<this->list.size(); i++)
			this->list[i] *= _scalar;
	}

	template<typename T>
	Matrix<T> Matrix<T>::operator+ (const Matrix& _mat) const
	{
		Matrix<T> _ans(this->n_rows,this->n_cols);
		_ans.list = this->list;
		try
		{
			if(this->n_rows!=_mat.n_rows)
				throw 0;
			if(this->n_cols!=_mat.n_cols)
				throw 1;
			for(int i=0; i<this->list.size(); i++)
				_ans.list[i] = this->list[i] + _mat.list[i];
		}
		catch(int x)
		{
			if(x==0)
				cout << "Rows of matrices aren't equal." << endl;
			if(x==1)
				cout << "Columns of matrices aren't equal." << endl;
		}
		return _ans;
	}

	template<typename T>
	Matrix<T> Matrix<T>::operator+ (const T _scalar) const
	{
		Matrix<T> _ans(this->n_rows,this->n_cols);
		for(int ind=0; ind<this->list.size();ind++)
			_ans.list[ind]=this->list[ind]+_scalar;

		return _ans;
	}

	template<typename T>
	Matrix<T> Matrix<T>::operator- (const Matrix& _mat) const
	{
		Matrix<T> _ans(this->n_rows,this->n_cols);
		_ans.list = this->list;
		try
		{
			if(this->n_rows!=_mat.n_rows)
				throw 0;
			if(this->n_cols!=_mat.n_cols)
				throw 1;
			for(int i=0; i<this->list.size(); i++)
				_ans.list[i] = this->list[i] - _mat.list[i];
		}
		catch(int x)
		{
			if(x==0)
				cout << "Rows of matrices aren't equal." << endl;
			if(x==1)
				cout << "Columns of matrices aren't equal." << endl;
		}
		return _ans;
	}

	template<typename T>
	Matrix<T> Matrix<T>::operator- (const T _scalar) const
	{
		Matrix<T> _ans(this->n_rows,this->n_cols);

		for(int ind=0; ind<this->list.size();ind++)
			_ans.list[ind]=this->list[ind]-_scalar;

		return _ans;
	}

	//template<typename T>
	//Matrix<T> Matrix<T>::operator* (const Matrix& B) const
	template<typename T>
	Matrix<T> Matrix<T>::operator* (const Matrix B) const
	{
	//	vector<T> temp = this->list;
	//	vector<T> tempMat = _mat.list;
	//	static  Matrix<T> C(this->n_cols, B.n_rows);
		static  Matrix<T> C(this->n_cols,B.n_rows);
		try
		{
			if(this->n_cols!=B.n_rows)
				throw 0;

			for(int m=0; m<this->n_rows; m++)
			{
				for(int p=0; p<B.n_cols; p++)
				{
					static T _temp = 0;
					for(int n=0; n<this->n_cols; n++)
					{
	//					list[n_cols*_r+_c];
	//					_temp = _temp + this->get(m,n)*B.get(n,p);
	//					_temp = _temp + this->list[n_cols*m+n]*B.get(n,p);

						_temp =  _temp + this->list[this->n_cols*m+n]*B.list[B.n_cols*n+p];
	//					_temp =  1.0;//B.n_cols;//(T)B.list[B.n_cols*n+p];
					}
					C.set(m,p,_temp);
	//				C.list[C.n_cols*m+p] = _temp;
				}
			}
		}
		catch(int x)
		{
			if(x==0)
				cout << "Matrix sizes prohibit multiplication" << endl;
		}
		return C;
	}

	template<typename T>
	Matrix<T> Matrix<T>::operator* (const T _scalar) const
	{
		vector<T> temp = this->list;
		for(int ind=0; ind<temp.size();ind++)
			temp[ind]=temp[ind]*_scalar;

		return temp;
	}

	//Matrix<T> Matrix<T>::operator= (const Matrix& _rhs)const
	template<typename T>
	void Matrix<T>::operator= (const Matrix& _rhs)
	{
		//Matrix _temp = *this;
		(*this).list   = _rhs.list;
		(*this).n_cols = _rhs.n_cols;
		(*this).n_rows = _rhs.n_rows;

		return;
	}
}
