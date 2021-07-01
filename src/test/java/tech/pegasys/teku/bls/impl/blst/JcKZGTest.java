package tech.pegasys.teku.bls.impl.blst;

import static org.assertj.core.api.Assertions.assertThat;
import static org.assertj.core.api.Assertions.assertThatThrownBy;

import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.Stream;
import org.apache.commons.lang3.tuple.Pair;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import tech.pegasys.jckzg.JcKZG;
import tech.pegasys.jckzg.JcKZGException;
import tech.pegasys.jckzg.swig.CFFTSettings;
import tech.pegasys.jckzg.swig.CKZGSettings;
import tech.pegasys.jckzg.swig.Fr;
import tech.pegasys.jckzg.swig.FrVector;
import tech.pegasys.jckzg.swig.G1;
import tech.pegasys.jckzg.swig.G1Vector;
import tech.pegasys.jckzg.swig.G2Vector;
import tech.pegasys.jckzg.swig.LongVector;
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

  @Test
  void frToLongs_testCorrectValueForFr1() {
    LongVector longs = Fr.getONE().to_longs();

    assertThat(longs).hasSize(4);
    assertThat(longs).containsExactly(1L, 0L, 0L, 0L);
  }

  @Test
  void frFromToLongs_roundtrip() {
    long[] longs = {0xa0c43757db972d7dL, 0x79d15a1e0677962cL, 0xf678865c0c95fa6aL,
        0x4e85fd4814f96825L};
    Fr fr = Fr.from_jlongs(longs);
    LongVector toLongs = fr.to_longs();
    assertThat(toLongs).containsExactlyElementsOf(Arrays.stream(longs).boxed().collect(Collectors.toList()));
  }

  @Test
  void frFromLongs_one() {
    Fr fr = Fr.from_jlongs(new long[]{1, 0, 0, 0});
    assertThat(fr.is_one()).isTrue();

  }

  @Test
  void frFromLongs_equal() {
    long[] longs = {0xa0c43757db972d7dL, 0x79d15a1e0677962cL, 0xf678865c0c95fa6aL,
        0x4e85fd4814f96825L};
    Fr fr1 = Fr.from_jlongs(longs);
    Fr fr2 = Fr.from_jlongs(longs);
    assertThat(fr1.equal(fr2)).isTrue();
    assertThat(fr2.to_longs()).containsExactlyElementsOf(fr1.to_longs());
  }

  @Test
  void recover_simple() {
    CFFTSettings cfftSettings = new CFFTSettings(2);
    List<Fr> poly = Stream.concat(
        IntStream.iterate(0, i -> i + 1)
            .limit(cfftSettings.max_width() / 2)
            .mapToObj(i -> Fr.from_jlongs(new long[]{i, 0, 0, 0})),
        Stream.generate(Fr::getZERO)
            .limit(cfftSettings.max_width() / 2))
        .collect(Collectors.toList());
    FrVector data = cfftSettings.fft_fr(new FrVector(poly), false);

    FrVector samples = new FrVector(
        List.of(data.get(0), Fr.getNULL_FR(), Fr.getNULL_FR(), data.get(3)));
    FrVector recovered = cfftSettings.recover_poly_from_samples(samples);

    for (int i = 0; i < data.size(); i++) {
      assertThat(recovered.get(i).equal(data.get(i))).isTrue();
    }

    FrVector back = cfftSettings.fft_fr(recovered, true);

    for (int i = 0; i < poly.size(); i++) {
      assertThat(back.get(i).equal(poly.get(i))).isTrue();
    }
  }

  @Test
  void newCFFTSettings_hugeScaleShouldCauseException() {
    assertThatThrownBy(() -> new CFFTSettings(32)).isInstanceOf(JcKZGException.class);
  }
}
