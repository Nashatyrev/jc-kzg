package tech.pegasys.teku.bls.impl.blst;

import static org.assertj.core.api.Assertions.assertThat;

import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;
import org.apache.commons.lang3.tuple.Pair;
import org.assertj.core.api.Assertions;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import tech.pegasys.jckzg.JcKZG;
import tech.pegasys.jckzg.swig.CFFTSettings;
import tech.pegasys.jckzg.swig.CKZGSettings;
import tech.pegasys.jckzg.swig.Fr;
import tech.pegasys.jckzg.swig.FrVector;
import tech.pegasys.jckzg.swig.G1;
import tech.pegasys.jckzg.swig.G1Vector;
import tech.pegasys.jckzg.swig.G2Vector;
import tech.pegasys.jckzg.swig.Poly;

public class JcKZGTest {

  @BeforeAll
  static void init() {
    JcKZG.loadNativeLibrary();
  }

  @Test
  void proofSingle() {
    long[] coeffs = new long[]{1, 2, 3, 4, 7, 7, 7, 7, 13, 13, 13, 13, 13, 13, 13, 13};
    int polyLen = coeffs.length;
    int secretsLen = polyLen + 1;

    List<Fr> frCoeffs = Arrays.stream(coeffs)
        .mapToObj(l -> Fr.from_jlongs(new long[]{l, 0, 0, 0}))
        .collect(Collectors.toList());
    Poly poly = new Poly(new FrVector(frCoeffs));

    Pair<G1Vector, G2Vector> trustedSetup = TestUtils
        .generateTrustedSetup(TestUtils.SECRET, secretsLen);
    G1Vector s1 = trustedSetup.getLeft();
    G2Vector s2 = trustedSetup.getRight();

    CFFTSettings cfftSettings = new CFFTSettings(4);
    CKZGSettings kzg = new CKZGSettings(cfftSettings, s1, s2);

    Fr x = TestUtils.longToFr(25);
    G1 commitment = kzg.commit_to_poly(poly);
    G1 proof = kzg.compute_proof_single(poly, x);

    Fr value = poly.eval(x);

    assertThat(kzg.check_proof_single(commitment, proof, x, value)).isTrue();
    assertThat(kzg.check_proof_single(commitment, proof, x, value.add(Fr.getONE()))).isFalse();
  }
}
