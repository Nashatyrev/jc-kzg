extern "C" {
#include "bls12_381.h"
}
#include <vector>

#include "exception.hpp"

class Poly;

#ifndef ___BLS12_381_HPP___
#define ___BLS12_381_HPP___

class Fr {
	friend class Poly;
	friend class KZG;
	friend class FFT;
	friend class G1;
	friend class G2;
	friend class BLS12_381;

private: 
	fr_t fr;

	Fr(fr_t _fr) { fr = _fr; }

	Fr(int64_t arr[4]) {
		fr_from_uint64s(&fr, (const uint64_t*) arr);
	}

public:
	static const Fr ZERO;
	static const Fr ONE;
	static const Fr NULL_FR;

	static Fr from_jlongs(int64_t arr[4]) {
		return Fr(arr);
	}

	Fr() {}

	bool is_zero() { return fr_is_zero(&fr); }
	bool is_one() { return fr_is_one(&fr); }
	bool is_null() { return fr_is_null(&fr); }
	bool equal(const Fr bb) { return fr_equal(&fr, &bb.fr); };

	Fr negate() {
		Fr ret;
		fr_negate(&ret.fr, &fr);
		return ret;
	}
	Fr add(const Fr b) {
		Fr ret;
		fr_add(&ret.fr, &fr, &b.fr);
		return ret;
	}
	Fr sub(const Fr b) {
		Fr ret;
		fr_sub(&ret.fr, &fr, &b.fr);
		return ret;
	}
	Fr mul(const Fr b) {
		Fr ret;
		fr_mul(&ret.fr, &fr, &b.fr);
		return ret;
	}
	Fr inv() {
		Fr ret;
		fr_inv(&ret.fr, &fr);
		return ret;
	}
	Fr div(const Fr b) {
		Fr ret;
		fr_div(&ret.fr, &fr, &b.fr);
		return ret;
	}
	Fr sqr() {
		Fr ret;
		fr_sqr(&ret.fr, &fr);
		return ret;
	}
	Fr pow(const int64_t n) {
		Fr ret;
		fr_pow(&ret.fr, &fr, n);
		return ret;
	}
	std::vector<long long> to_longs() {
		std::vector<long long> ret(4);
		fr_to_uint64s((uint64_t*)&ret[0], &fr);
		return ret;
	}
};

const Fr Fr::ZERO = Fr(fr_zero);
const Fr Fr::ONE= Fr(fr_one);
const Fr Fr::NULL_FR= Fr(fr_null);

class G1 {
	friend class Poly;
	friend class KZG;
	friend class FK20Single;
	friend class FK20Multi;
	friend class BLS12_381;
private:
	g1_t g1;

	G1(g1_t g1_) { g1 = g1_; }
	G1(const byte arr[48]) throw(KZGException) {
		blst_p1_affine p1_aff;
		BLST_TRY(blst_p1_uncompress(&p1_aff, arr));
		blst_p1_from_affine(&g1, &p1_aff);
	}

public:
	static const G1 IDENTITY;
	static const G1 GENERATOR;
	static const G1 NEGATIVE_GENERATOR;
	static G1 from_compressed(const signed char arr[48]) throw(KZGException) {
		return G1((byte*)arr);
	}
	static G1 linear_combination(std::vector<G1> g1s, std::vector<Fr> coeffs) {
		if (coeffs.size() == 0) return IDENTITY;

		G1 ret;
		g1_linear_combination(&ret.g1, (g1_t*)&g1s[0], (fr_t*)&coeffs[0], coeffs.size());
		return ret;
	}

	G1() {}

	bool is_inf() { return g1_is_inf(&g1); };
	G1 dbl() {
		G1 ret;
		g1_dbl(&ret.g1, &g1);
		return ret;
	}
	G1 add_or_dbl(const G1 b) {
		G1 ret;
		g1_add_or_dbl(&ret.g1, &g1, &b.g1);
		return ret;
	}
	bool equal(const G1 b) { return g1_equal(&g1, &b.g1); }
	G1 mul(const Fr b) {
		G1 ret;
		g1_mul(&ret.g1, &g1, &b.fr);
		return ret;
	}
	G1 sub(const G1 b) {
		G1 ret;
		g1_sub(&ret.g1, &g1, &b.g1);
		return ret;
	}
	void to_compressed(signed char out[48]) {
		blst_p1_compress((byte*)out, &g1);
	}
};

const G1 G1::IDENTITY = G1(g1_identity);
const G1 G1::GENERATOR= G1(g1_generator);
const G1 G1::NEGATIVE_GENERATOR= G1(g1_negative_generator);


class G2 {
	friend class Poly;
	friend class KZG;
	friend class BLS12_381;
private:
	g2_t g2;

	G2() {}
	G2(g2_t g2_) { g2 = g2_; }
	G2(const byte arr[96]) throw(KZGException) {
		blst_p2_affine p2_aff;
		BLST_TRY(blst_p2_uncompress(&p2_aff, arr));
		blst_p2_from_affine(&g2, &p2_aff);
	}

public:
	static const G2 GENERATOR;
	static const G2 NEGATIVE_GENERATOR;
	static G2* from_compressed(const signed char arr[96]) {
		return new G2((byte*)arr);
	}
	bool equal(G2 b) { return g2_equal(&g2, &b.g2); }
	G2 mul(const Fr b) {
		G2 ret;
		g2_mul(&ret.g2, &g2, &b.fr);
		return ret;
	}
	G2 add_or_dbl(const G2 b) {
		G2 ret;
		g2_add_or_dbl(&ret.g2, &g2, &b.g2);
		return ret;
	}
	G2 sub(const G2 b) {
		G2 ret;
		g2_sub(&ret.g2, &g2, &b.g2);
		return ret;
	}
	G2 dbl() {
		G2 ret;
		g2_dbl(&ret.g2, &g2);
		return ret;
	}
};

const G2 G2::GENERATOR = G2(g2_generator);
const G2 G2::NEGATIVE_GENERATOR = G2(g2_negative_generator);

class BLS12_381 {
public:
	static bool pairings_verify(G1 a1, G2 a2, G1 b1, G2 b2) {
		return ::pairings_verify(&a1.g1, &a2.g2, &b1.g1, &b2.g2);
	}
};

#endif // !___POLY_HPP___
