/*
 * Tensor.cpp
 *
 *  Created on: 30 Apr 2014
 *      Author: gwessels
 */

#include "Tensor.h"
#include <vector>
#include <iostream>

using namespace std;

namespace LinAlg
{
	template <typename T>
	Tensor<T>::Tensor()
	{
		this->list		= new std::vector<T>;
		this->dimension	= new std::vector<T>;
		this->size		= 0;
	}
	template <typename T>
	Tensor<T>::Tensor(int* _dimensions)
	{
		this->dimension	= _dimensions;

		int _size = 0;
		for(int i=0; i<this->dimension.size(); i++)
			_size += _dimensions[i];

		this->size	= _size;
		this->list	= new std::vector<T>(_size);
	}
	template <typename T>
	Tensor<T>::Tensor(Tensor<T>& _x)
	{
		this->list 	  	= _x.list;
		this->dimension = _x.dimension;
		this->size 		= _x.size;
	}
	template <typename T>
	Tensor<T>::~Tensor()
	{
        if(this->size>0)
        {
                this->list.clear();
                this->dimension.clear();
                this->size = 0;
        }
	}

	template <typename T>
	T* Tensor<T>::getList()
	{
		return this->list();
	}
	template <typename T>
	void Tensor<T>::initList(T _fill)
	{
		for(int i=0; i<this->size; i++)
		{
			this->list[i] = _fill;
		}
	}

	template <typename T>
	void Tensor<T>::add(Tensor<T> _tensor)
	{
		try
		{
			if(this->dimension.size()!=_tensor.dimension.size())
				throw 0;
			for(int i=0; i<this->dimension.size(); i++)
				if(this->dimension[i]!=_tensor.dimension[i])
					throw 0;

			for(int i=0; i<this->size; i++)
				this->list[i] += _tensor.list[i];
		}
		catch(int _err)
		{
			if(_err==0)
				cout << "ERROR: Dimensions of tensors do not match" << endl;
		}
	}
	template <typename T>
	void Tensor<T>::add(T _scalar)
	{
		for(int i=0; i<this->size; i++)
			this->list[i] += _scalar;
	}
	template <typename T>
	void Tensor<T>::subtract(Tensor<T> _tensor)
	{
		try
		{
			if(this->dimension.size()!=_tensor.dimension.size())
				throw 0;
			for(int i=0; i<this->dimension.size(); i++)
				if(this->dimension[i]!=_tensor.dimension[i])
					throw 0;

			for(int i=0; i<this->size; i++)
				this->list[i] -= _tensor.list[i];
		}
		catch(int _err)
		{
			if(_err==0)
				cout << "ERROR: Dimensions of tensors do not match" << endl;
		}
	}
	template <typename T>
	void Tensor<T>::subtract(T _scalar)
	{
		for(int i=0; i<this->size; i++)
			this->list[i] -= _scalar;
	}
	template <typename T>
	void Tensor<T>::multiply(T _scalar)
	{
		for(int i=0; i<this->size; i++)
			this->list[i] *= _scalar;
	}

	template <typename T>
	Tensor 	operator+ (const Tensor&) const
	{

	}
//	Tensor 	operator+ (const T) const;
//	Tensor 	operator- (const Tensor&) const;
//	Tensor 	operator- (const T) const;
//	Tensor 	operator* (const Tensor&) const;
//	Tensor	operator* (const T) const;
//	void	operator= (const Tensor&);


} /* namespace LinAlg */
