/*
 * vector.cpp
 *
 *  Created on: 25 Apr 2014
 *      Author: gwessels
 */

#include "linalg.hpp"
#include <iostream>
#include <string>

using namespace std;

namespace LinAlg
{
	template<typename T>
	Vector<T>::Vector(int _c)
	{
		n_rows =_c;
		n_cols =1;
		list.resize(_c);
		this->initList(0);
	}

	template<typename T>
	Vector<T>::Vector(int _r, int _c)
	{
		try
			{
				if(_r>1 && _c>1)
					throw 0;
				n_rows =_r;
				n_cols =_c;
				list.resize(_r*_c);
				this->initList(0);
			}
			catch(int x)
			{
				if(x==0)
					cout << "Wrong Size. Vector requires either the row or column to be 1.";
				else
					cout << "FATAL ERROR: Vector(_rows,_cols).";
			}
	}

	template<typename T>
	Vector<T>::Vector(Vector<T>& _x)
	{
		this->n_rows	=_x.n_rows;
		this->n_cols	=_x.n_cols;
		this->list 		=_x.list;
	}

	template<typename T>
	Vector<T>::~Vector(void)
	{
		if(list.size()>0)
		{
			this->list.clear();
			this->n_rows=0;
			this->n_cols=0;
		}
	}

	template<typename T>
	int Vector<T>::getRows()
	{
		return n_rows;
	}

	template<typename T>
	int Vector<T>::getColumns()
	{
		return n_cols;
	}

	template<typename T>
	T Vector<T>::get(int _cell)
	{
		return list[_cell];
	}

	template<typename T>
	T* Vector<T>::getList()
	{
		return list;
	}

	template<typename T>
	void Vector<T>::set(int _c, T _val)
	{
		list[_c] = _val;
	}

	template<typename T>
	void Vector<T>::initList(T _fill)
	{
		for(int i=0;i<(n_rows*n_cols);i++)
			list[i]=_fill;
	}

	template<typename T>
	void Vector<T>::printVector()
	{
		try
			{
				string _whitespace="";
				if(n_rows>1)
					_whitespace = "\n";
				else if(n_cols>1)
					_whitespace = "\t";
				else
					throw 0;

				for(int _c=0; _c<n_rows*n_cols; _c++)
					cout << list[_c] << _whitespace;
				cout << "\n" << endl;
			}
			catch(int x)
			{
				if(x==0)
					cout << "Not a vector. Either the number of rows or columns need to be equal to 1.";
				else
					cout << "FATAL ERROR: printVector";
			}

	}

	template<typename T>
	void Vector<T>::transpose()
	{
		int _rows = this->n_rows;
		this->list 	 = list;
		this->n_rows = n_cols;
		this->n_cols = _rows;
	}

	template<typename T>
	void Vector<T>::swapCells(int _c1, int _c2)
	{
		T _placeholder = list[_c1];
		this->set(_c1,this->get(_c2));
		this->set(_c2,_placeholder);
	}
	// Subtract one cell from another
	// c1 -= factor*c2
	template<typename T>
	void Vector<T>::subtractCells(int _c1, T _factor, int _c2)
	{
		this->set(_c1,this->get(_c2)-_factor*(this->get(_c2)));
	}

	template<typename T>
	void Vector<T>::add(Vector<T> _vec)
	{
		try
			{
				//	Test Vector compatibility
				if(this->n_rows!=_vec.n_rows)
					throw 0;
				if(this->n_cols!=_vec.n_cols)
					throw 1;
				// Addition operator
				for(int i=0; i<this->list.size(); i++)
					this->list[i] += _vec.list[i];
			}
			catch(int x)
			{
				if(x==0)
					cout << "Unequal rows, vector sizes do not match." << endl;
				if(x==1)
					cout << "Unequal columns, vector sizes do not match." << endl;
			}
	}

	template<typename T>
	void Vector<T>::add(T _scalar)
	{
		for(int i=0; i<this->list.size(); i++)
			this->list[i] += _scalar;
	}

	template<typename T>
	void Vector<T>::subtract(Vector<T>& _vec)
	{
		try
			{
				//	Test Vector compatibility
				if(this->n_rows!=_vec.n_rows)
					throw 0;
				if(this->n_cols!=_vec.n_cols)
					throw 1;
				// Addition operator
				for(int i=0; i<this->list.size(); i++)
					this->list[i] -= _vec.list[i];
			}
			catch(int x)
			{
				if(x==0)
					cout << "Unequal rows, vector sizes do not match." << endl;
				if(x==1)
					cout << "Unequal columns, vector sizes do not match." << endl;
			}
	}

	template<typename T>
	void Vector<T>::subtract(T _scalar)
	{
		for(int i=0; i<this->list.size(); i++)
			this->list[i] -= _scalar;
	}

	template<typename T>
	Matrix<T> Vector<T>::multiply(Vector _v2)
	{
		Matrix<T> _M(this->n_rows,_v2.n_cols);
		try
			{
				if(this->n_cols!=_v2.n_rows)
					throw 0;

				if(this->n_rows==1)
				{
					for(int _c=0; _c<this->n_cols; _c++)
						_M.list[0] += this->list[_c]*_v2.list[_c];
				}
				else if(this->n_cols==1)
				{
					for(int _r1=0;_r1<this->n_rows;_r1++)
						for(int _c2=0;_c2<_v2.n_rows;_c2++)
							_M.set(_r1,_c2,this->list[_r1]*_v2.list[_c2]);
				}
				else
					throw 0;
			}
			catch(int x)
			{
				if(x==0)
					cout << "Vector sizes prohibit multiplication" << endl;
			}

		return _M;
	}

	template<typename T>
	Vector<T> Vector<T>::multiply(Matrix<T> M)
	{
		Vector<T> _vsol(1,M.n_cols);
		try
			{
				if(this->n_cols!= M.n_rows)
					throw 0;

				for(int _c=0;_c<M.n_cols; _c++)
					for(int _r=0;_r<M.n_rows;_r++)
						_vsol.list[_c]+=this->list[_r]*M.get(_r,_c);
			}
			catch(int x)
			{
				if(x==0)
					cout << "Vector sizes prohibit multiplication" << endl;
			}
		return _vsol;

	}


	template<typename T>
	void Vector<T>::multiply(T _scalar)
	{
		for(int i=0; i<this->list.size(); i++)
			this->list[i] *= _scalar;
	}

	template<typename T>
	Vector<T> Vector<T>::operator+ (const Vector& _vec) const
	{
		Vector<T> _ans(this->n_rows,this->n_cols);
		_ans.list = this->list;
		try
		{
			if(this->n_rows!=_vec.n_rows)
				throw 0;
			if(this->n_cols!=_vec.n_cols)
				throw 1;
			for(int i=0; i<this->list.size(); i++)
				_ans.list[i] = this->list[i] + _vec.list[i];
		}
		catch(int x)
		{
			if(x==0)
				cout << "Rows of vectors aren't equal." << endl;
			if(x==1)
				cout << "Columns of vectors aren't equal." << endl;
		}
		return _ans;
	}

	template<typename T>
	Vector<T> Vector<T>::operator+ (const T _scalar) const
	{
		Vector<T> _ans(this->n_rows,this->n_cols);
		for(int ind=0; ind<this->list.size();ind++)
			_ans.list[ind]=this->list[ind]+_scalar;

		return _ans;
	}

	template<typename T>
	Vector<T> Vector<T>::operator- (const Vector& _vec) const
	{
		Vector<T> _ans(this->n_rows,this->n_cols);
		_ans.list = this->list;
		try
		{
			if(this->n_rows!=_vec.n_rows)
				throw 0;
			if(this->n_cols!=_vec.n_cols)
				throw 1;
			for(int i=0; i<this->list.size(); i++)
				_ans.list[i] = this->list[i] - _vec.list[i];
		}
		catch(int x)
		{
			if(x==0)
				cout << "Rows of vectors aren't equal." << endl;
			if(x==1)
				cout << "Columns of vectors aren't equal." << endl;
		}
		return _ans;
	}

	template<typename T>
	Vector<T> Vector<T>::operator- (const T _scalar) const
	{
		Vector<T> _ans(this->n_rows,this->n_cols);

		for(int ind=0; ind<this->list.size();ind++)
			_ans.list[ind]=this->list[ind]-_scalar;

		return _ans;
	}


	template<typename T>
	Matrix<T> Vector<T>::operator* (const Vector B) const
	{

		static Matrix<T> C(this->n_cols,B.n_rows);
		try
		{
			if(this->n_cols!=B.n_rows)
				throw 0;

			C = this->multiply(B);

	//		for(int m=0; m<this->n_rows; m++)
	//		{
	//			for(int p=0; p<B.n_cols; p++)
	//			{
	//				static T _temp = 0;
	//				for(int n=0; n<this->n_cols; n++)
	//				{
	//					_temp =  _temp + this->list[this->n_cols*m+n]*B.list[B.n_cols*n+p];
	//				}
	//				C.set(m,p,_temp);
	//			}
	//		}
		}
		catch(int x)
		{
			if(x==0)
				cout << "Vector sizes prohibit multiplication" << endl;
		}
		return C;
	}

	//Vector operator* (const Matrix<T>) const;

	template<typename T>
	Vector<T> Vector<T>::operator* (const T _scalar) const
	{
		vector<T> temp = this->list;
		for(int ind=0; ind<temp.size();ind++)
			temp[ind]=temp[ind]*_scalar;

		return temp;
	}

	//Vector<T> Vector<T>::operator= (const Vector& _rhs)
	template<typename T>
	void Vector<T>::operator= (const Vector& _rhs)
	{
		//Vector _temp = *this;
		(*this).list   = _rhs.list;
		(*this).n_cols = _rhs.n_cols;
		(*this).n_rows = _rhs.n_rows;

		return;
	}
}
