/*
    File for debugging testcases under MS Visual Studio

    In MSVC choose "Test" configuration, then Local Debugger would run the main() function below
*/
#ifdef JCKZG_MSVC_TEST

extern "C" {

#include "c_kzg.h"
#include "test_util.h"
#include "c_kzg_alloc.h"
#include "control.h"

}

#define TEST_CHECK(result) ASSERT(result)

int main(int args_len, char** args) {
    FFTSettings fs;
    KZGSettings ks;
    FK20MultiSettings fk;
    uint64_t n, chunk_len, chunk_count, width;
    uint64_t secrets_len;
    g1_t* s1;
    g2_t* s2;
    poly p;
    uint64_t vv[] = { 1, 2, 3, 4, 7, 8, 9, 10, 13, 14, 1, 15, 1, 1000, 134, 33 };
    g1_t commitment;
    g1_t* all_proofs;
    fr_t* extended_coeffs, * extended_coeffs_fft;
    fr_t* ys, * ys2;
    uint64_t domain_stride;

    chunk_len = 16;
    chunk_count = 1;
    n = chunk_len * chunk_count;
    width = 4 + 5 + 1;
    secrets_len = 1 << width;

    TEST_CHECK(C_KZG_OK == new_g1_array(&s1, secrets_len));
    TEST_CHECK(C_KZG_OK == new_g2_array(&s2, secrets_len));


    generate_trusted_setup(s1, s2, &secret, secrets_len);
    TEST_CHECK(C_KZG_OK == new_fft_settings(&fs, width));
    TEST_CHECK(C_KZG_OK == new_kzg_settings(&ks, s1, s2, secrets_len, &fs));
    TEST_CHECK(C_KZG_OK == new_fk20_multi_settings(&fk, n * 2, chunk_len, &ks));

    // Create a test polynomial: 512 coefficients
    TEST_CHECK(C_KZG_OK == new_poly(&p, n));
    for (int i = 0; i < chunk_count; i++) {
        for (int j = 0; j < chunk_len; j++) {
            uint64_t v = vv[j];
            if (j == 3) v += i;
            if (j == 5) v += i * i;
            fr_from_uint64(&p.coeffs[i * chunk_len + j], v);
        }
        fr_negate(&p.coeffs[i * chunk_len + 12], &p.coeffs[i * chunk_len + 12]);
        fr_negate(&p.coeffs[i * chunk_len + 14], &p.coeffs[i * chunk_len + 14]);
    }

    TEST_CHECK(C_KZG_OK == commit_to_poly(&commitment, &p, &ks));

    // Compute the multi proofs, assuming that the polynomial will be extended with zeros
    TEST_CHECK(C_KZG_OK == new_g1_array(&all_proofs, 2 * chunk_count));
    TEST_CHECK(C_KZG_OK == da_using_fk20_multi(all_proofs, &p, &fk));
}

#endif