#ifndef ___FK20_HPP___
#define ___FK20_HPP___

extern "C" {
#include "c_kzg.h"
}

#include <vector>
#include "poly.hpp"
#include "bls12_381.hpp"
#include "exception.hpp"

class FK20Single;
class FK20Multi;

class FK20 {
public:
	static FK20* create_single(KZG* kzg, long long n2) throw (KZGException);
	static FK20* create_multi(KZG* kzg, long long n2, long long chunk_len) throw (KZGException);

	virtual std::vector<G1> da_calc_proofs(Poly* poly) throw (KZGException) = 0;
	virtual ~FK20() {};
};

class FK20Single : public FK20 {
private:
	FK20SingleSettings _settings;
public:
	FK20Single(KZG* kzg, long long n2) {
		CKZG_TRY(new_fk20_single_settings(&_settings, n2, &kzg->settings));
	}
	std::vector<G1> da_calc_proofs(Poly* poly) throw (KZGException) {
		std::vector<G1> ret(2 * poly->length());
		CKZG_TRY(da_using_fk20_single((g1_t*)&ret[0], &poly->_poly, &_settings));
		return ret;
	};
	~FK20Single() {
		free_fk20_single_settings(&_settings);
	};
};

class FK20Multi: public FK20 {
private:
	FK20MultiSettings _settings;
public:
	FK20Multi(KZG* kzg, long long n2, long long chunk_len) {
		CKZG_TRY(new_fk20_multi_settings(&_settings, n2, chunk_len, &kzg->settings));
	}
	std::vector<G1> da_calc_proofs(Poly* poly) throw (KZGException) {
		std::vector<G1> ret(2 * poly->length() / _settings.chunk_len);
		CKZG_TRY(da_using_fk20_multi((g1_t*)&ret[0], &poly->_poly, &_settings));
		return ret;
	};
	~FK20Multi() {
		free_fk20_multi_settings(&_settings);
	};
};

FK20* FK20::create_single(KZG* kzg, long long n2) throw (KZGException) {
	return new FK20Single(kzg, n2);
}

FK20* FK20::create_multi(KZG* kzg, long long n2, long long chunk_len) throw (KZGException) {
	return new FK20Multi(kzg, n2, chunk_len);
}

#endif // ___FK20_HPP___
