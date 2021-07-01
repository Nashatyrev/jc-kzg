extern "C" {
	#include "kzg_proofs.h"
}
#include "fft_common.hpp"
#include "bls12_381.hpp"
#include "poly.hpp"
#include "exception.hpp"
#include <vector>

class CKZGSettings {
private:
	KZGSettings settings;

public:
	CKZGSettings(CFFTSettings* fft_settings, std::vector<G1> g1_secrets, std::vector<G2> g2_secrets) {
		// TODO check g1_secrets.size() == g2_secrets.size()
		CKZG_TRY(new_kzg_settings(&settings, (g1_t*)&g1_secrets[0], (g2_t*)&g2_secrets[0], g1_secrets.size(), &fft_settings->settings));
	}
	~CKZGSettings() {
		free_kzg_settings(&settings);
	}

	G1 commit_to_poly(Poly* poly) {
		G1 ret;
		::commit_to_poly(&ret.g1, &poly->_poly, &settings);
		return ret;
	}

	G1 compute_proof_single(Poly* poly, Fr x0) {
		G1 ret;
		CKZG_TRY(::compute_proof_single(&ret.g1, &poly->_poly, &x0.fr, &settings));
		return ret;
	}
	G1 compute_proof_poly(Poly* poly, std::vector<Fr> x0) {
		G1 ret;
		CKZG_TRY(::compute_proof_multi(&ret.g1, &poly->_poly, (fr_t*) &x0[0], x0.size(), &settings));
		return ret;
	}
	bool check_proof_single(G1 commitment, G1 proof, Fr x, Fr y) {
		bool ret;
		CKZG_TRY(::check_proof_single(&ret, &commitment.g1, &proof.g1, &x.fr, &y.fr, &settings));
		return ret;
	}
	bool check_proof_multi(G1 commitment, G1 proof, Fr x, std::vector<Fr> ys) {
		bool ret;
		CKZG_TRY(::check_proof_multi(&ret, &commitment.g1, &proof.g1, &x.fr, (fr_t*)&ys[0], ys.size(), &settings));
		return ret;
	}
};