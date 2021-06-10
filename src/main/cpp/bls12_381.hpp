extern "C" {
#include "bls12_381.h"
}

class Poly;

#ifndef ___BLS12_381_HPP___
#define ___BLS12_381_HPP___

struct Fr {
	friend class Poly;
	friend class CKZGSettings;
	friend class CFFTSettings;

private: 
	fr_t fr;

	Fr() {}

	Fr(int64_t arr[]) {
		fr_from_uint64s(&fr, (const uint64_t*) arr);
	}

public:
	static Fr from_jlongs(int64_t arr[]) {
		return Fr(arr);
	}
};

struct G1 {
	friend class Poly;
	friend class CKZGSettings;
private:
	g1_t g1;

	G1() {}
	G1(const byte arr[48]) {
		blst_p1_affine p1_aff;
		blst_p1_uncompress(&p1_aff, arr);
		blst_p1_from_affine(&g1, &p1_aff);
	}

public:
	static G1* from_compressed(const signed char arr[48]) {
		return new G1((byte*)arr);
	}
};

struct G2 {
	friend class Poly;
	friend class CKZGSettings;
private:
	g2_t g2;

	G2() {}
	G2(const byte arr[96]) {
		blst_p2_affine p2_aff;
		blst_p2_uncompress(&p2_aff, arr);
		blst_p2_from_affine(&g2, &p2_aff);
	}

public:
	static G2* from_compressed(const signed char arr[96]) {
		return new G2((byte*)arr);
	}
};
#endif // !___POLY_HPP___
