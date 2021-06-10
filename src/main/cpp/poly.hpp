extern "C" {
#include "poly.h"
}
#include <vector>
#include "bls12_381.hpp"

#ifndef ___POLY_HPP___
#define ___POLY_HPP___

class Poly {
	friend class CKZGSettings;
	friend class CFFTSettings;
private:
	poly _poly;

	Poly() {}
public:

	Poly(const int length) {
		new_poly(&_poly, length);
	}

	Poly(std::vector<Fr> coeff) {
		new_poly_with_coeffs(&_poly, (fr_t*)&coeff[0], coeff.size());
	}
	~Poly() {
		free_poly(&_poly);
	}

	Poly* long_div(Poly *divisor) {
		Poly* ret = new Poly();
		new_poly_long_div(&ret->_poly, &_poly, &divisor->_poly);
		return ret;
	}

	Fr eval(const Fr x) {
		Fr ret;
		eval_poly(&ret.fr, &_poly, &x.fr);
		return ret;
	}
};

#endif // !___POLY_HPP___
