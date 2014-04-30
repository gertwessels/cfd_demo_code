/*
 * Tensor.h
 *
 *  Created on: 30 Apr 2014
 *      Author: gwessels
 */

#ifndef TENSOR_H_
#define TENSOR_H_

namespace LinAlg
{
template <typename T>
class Tensor {
	public:
		Tensor();
		Tensor(int *dimsension);
		Tensor(Tensor<T>& x);
		virtual ~Tensor();

		T*		getList();
		int*	getDim();
		void	initList(T fill);

		void	add(Tensor<T> tensor);
		void 	add(T scalar);
		void 	subtract(Tensor<T> tensor);
		void 	subtract(T scalar);
		void 	multiply(T scalar);

		Tensor 	operator+ (const Tensor&) const;
		Tensor 	operator+ (const T) const;
		Tensor 	operator- (const Tensor&) const;
		Tensor 	operator- (const T) const;
		Tensor 	operator* (const Tensor&) const;
		Tensor	operator* (const T) const;
		void	operator= (const Tensor&);

	protected:
		int* 	dimension;
		T* 		list;
		int 	size;
};

} /* namespace LinAlg */
#endif /* TENSOR_H_ */
