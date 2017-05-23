/*
 * vectormath.cpp
 *
 *  Created on: Aug 25, 2011
 *      Author: sturmju
 */

#include <symboliccpp/symbolicc++.h>

Vector<Symbolic> df(const Vector<Symbolic> &s,const Symbolic &x){
	Vector<Symbolic> ds(s.size());
	for(size_t i=0;i<s.size();i++) {
		ds[i] = df(s[i],x);
	}
	return ds;
}

int main(void) {
	Symbolic x("x");
	Symbolic y("y");

	Vector<Symbolic> A(2);
	A[0]=x;
	A[1]=y;
	cout << A << endl;

	Symbolic alpha("alpha");
	Symbolic X;

	X = ( ( cos(alpha), sin(alpha) ),
	       (-sin(alpha), cos(alpha) ) );

	Matrix<Symbolic> M(2,2);
	M[0][0] = cos(alpha);
	M[0][1] = sin(alpha);
	M[1][0] = -sin(alpha);
	M[1][1] = Cos(1.00);

	cout << Symbolic(M[1][1][alpha==1])<<endl;

	cout << M * A << endl;

	cout << df(M*A,x) << endl;
}
