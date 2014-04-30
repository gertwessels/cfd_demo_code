/*
 * solvers.cpp
 *
 *  Created on: 24 Apr 2014
 *      Author: gwessels
 */

#include "linalg.hpp"

namespace LinAlg
{
	//Vector<float>
	void Solvers::solveSystem(Matrix<float> A, Vector<float> b)
	{
		Vector<float> _solution();

		Matrix<float> _a(A.getRows(),A.getColumns()+1);

		for(int i=0; i<_a.getRows(); i++)
			for(int j=0; j<_a.getColumns(); j++)
			{
				if(j<_a.getColumns()-1)
					_a.set(i,j,A.get(i,j));
	//			else
	//				_a.set(i,j,b[i]);
			}
		_a.printMatrix();

		//return _solution;
	}
}
