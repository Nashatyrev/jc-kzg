extern "C" {
#include "fft_fr.h"
#include "fft_common.h"
#include "c_kzg.h"
#include "zero_poly.h"
#include "recover.h"
#include "das_extension.h"
}
#include <vector>
#include "poly.hpp"
#include "bls12_381.hpp"
#include "exception.hpp"

#ifndef ___FFT_COMMON_HPP___
#define ___FFT_COMMON_HPP___

class CFFTSettings {
friend class CKZGSettings;

private:
    FFTSettings settings;

    std::vector<Fr> fft_fr(std::vector<Fr> vals, bool inverse) throw(KZGException) {
        Fr* ret = new Fr[vals.size()];
        CKZG_TRY(::fft_fr((fr_t*)ret, (fr_t*)&vals[0], inverse, vals.size(), &settings));
        return std::vector<Fr>(ret, ret + vals.size());
    }

public:
    CFFTSettings(unsigned int max_scale) throw(KZGException) {
        CKZG_TRY(new_fft_settings(&settings, max_scale));
    }

    ~CFFTSettings() {
        free_fft_settings(&settings);
    }

    std::vector<Fr> fft_fr(std::vector<Fr> vals) throw(KZGException) {
        return fft_fr(vals, false);
    }

    std::vector<Fr> fft_inverse_fr(std::vector<Fr> vals) throw(KZGException) {
        return fft_fr(vals, true);
    }

    std::vector<Fr> das_fft_extension(std::vector<Fr> vals) {
        // TODO: memleak ?
        Fr* ret = new Fr[vals.size()];
        std::copy(vals.begin(), vals.end(), ret);
        CKZG_TRY(::das_fft_extension((fr_t*)ret, vals.size(), &settings));
        return std::vector<Fr>(ret, ret + vals.size());
    }

    std::vector<Fr> recover_poly_from_samples(std::vector<Fr> samples) {
        Fr *ret = new Fr[samples.size()];
        CKZG_TRY(::recover_poly_from_samples((fr_t*)ret, (fr_t*)&samples[0], samples.size(), &settings));
        return std::vector<Fr>(ret, ret + samples.size());
    }

    Poly* do_zero_poly_mul_partial(std::vector<long long> indices, int64_t stride) {
        Poly* ret = new Poly();
        CKZG_TRY(::do_zero_poly_mul_partial(&(ret->_poly), (uint64_t*)indices[0], indices.size(), stride, &settings));
        return ret;
    }

    long long max_width() {
        return settings.max_width;
    }
};

#endif // !___FFT_COMMON_HPP___
