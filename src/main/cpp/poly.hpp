extern "C" {
#include "c_kzg.h"
}
#include <vector>
#include "bls12_381.hpp"
#include "exception.hpp"

#ifndef ___POLY_HPP___
#define ___POLY_HPP___

class Poly {
	friend class KZG;
	friend class FFT;
	friend class FK20Single;
	friend class FK20Multi;
private:
	poly _poly;

	Poly() {}
public:

	Poly(const int length) throw(KZGException) {
		CKZG_TRY(new_poly(&_poly, length));
	}

	Poly(std::vector<Fr> coeff) throw(KZGException) {
		fr_t* ptr = coeff.size() > 0 ? (fr_t*)&coeff[0] : NULL;
		CKZG_TRY(new_poly_with_coeffs(&_poly, ptr, coeff.size()));
	}
	~Poly() {
		free_poly(&_poly);
	}

	Poly* long_div(Poly *divisor) throw(KZGException) {
		Poly* ret = new Poly(_poly.length);
		CKZG_TRY(::new_poly_div(&ret->_poly, &_poly, &divisor->_poly));
		return ret;
	}

	Poly* mul(Poly* multiplicator) throw(KZGException) {
		Poly* ret = new Poly(_poly.length + multiplicator->_poly.length);
		CKZG_TRY(::poly_mul(&ret->_poly, &_poly, &multiplicator->_poly));
		return ret;
	}

	Fr eval(const Fr x) {
		Fr ret;
		eval_poly(&ret.fr, &_poly, &x.fr);
		return ret;
	}

	std::vector<Fr> coeff() {
		Fr* start = (Fr*)_poly.coeffs;
		Fr* end = (Fr*)(_poly.coeffs + _poly.length);
		std::vector<Fr> ret(start, end);
		return ret;
	}

	long long length() {
		return _poly.length;
	}
};

#endif // !___POLY_HPP___
