extern "C" {
#include "fft_common.h"
#include "c_kzg.h"
#include "zero_poly.h"
#include "recover.h"
#include "das_extension.h"
}
#include <vector>
#include "poly.hpp"
#include "bls12_381.hpp"

#ifndef ___FFT_COMMON_HPP___
#define ___FFT_COMMON_HPP___

class CFFTSettings {
friend class CKZGSettings;

private:
    FFTSettings settings;
public:
    CFFTSettings(unsigned int max_scale) {
        new_fft_settings(&settings, max_scale);
    }

    ~CFFTSettings() {
        free_fft_settings(&settings);
    }

    std::vector<Fr> das_fft_extentions(std::vector<Fr> vals) {
        Fr* ret = new Fr[vals.size()];
        std::copy(vals.begin(), vals.end(), ret);
        ::das_fft_extension((fr_t*)ret, vals.size(), &settings);
        return std::vector<Fr>(ret, ret + vals.size());
    }

    std::vector<Fr> recover_poly_from_samples(std::vector<Fr> samples) {
        Fr *ret = new Fr[samples.size()];
        ::recover_poly_from_samples((fr_t*)ret, (fr_t*)&samples[0], samples.size(), &settings);
        return std::vector<Fr>(ret, ret + samples.size());
    }

    Poly* do_zero_poly_mul_partial(std::vector<int64_t> indices, int64_t stride) {
        Poly* ret = new Poly();
        ::do_zero_poly_mul_partial(&(ret->_poly), (uint64_t*)indices[0], indices.size(), stride, &settings);
        return ret;
    }
};

#endif // !___FFT_COMMON_HPP___
