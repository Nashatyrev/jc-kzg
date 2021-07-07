package tech.pegasys.teku.bls.impl.blst;

import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.LongStream;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Disabled;
import org.junit.jupiter.api.Test;
import tech.pegasys.jckzg.JcKZG;
import tech.pegasys.jckzg.swig.FFT;
import tech.pegasys.jckzg.swig.Fr;
import tech.pegasys.jckzg.swig.FrVector;

@Disabled
public class Benchmarks {

  static int scale = 15;

  static FrVector data;
  static FrVector someSamples;
  static FFT FFT;

  @BeforeAll
  static void setup() {
    JcKZG.loadNativeLibrary();

    FFT = new FFT(scale);

    data = new FrVector(LongStream.range(0, FFT.max_width() / 2)
        .mapToObj(l -> Fr.from_jlongs(new long[]{l, 0, 0, 0}))
        .collect(Collectors.toList()));

    FrVector oddData = FFT.das_fft_extension(data);
//    FrVector oddData = slowDasFftExtension(FFT, evenData);
    List<Fr> allSamples = IntStream
        .range(0, data.size() * 2)
        .mapToObj(i -> i % 2 == 0 ? data.get(i / 2) : oddData.get(i / 2))
        .collect(Collectors.toList());

    someSamples = new FrVector(IntStream
        .range(0, allSamples.size())
        .mapToObj(i -> i % 3 == 0 ? Fr.getNULL_FR() : allSamples.get(i))
        .collect(Collectors.toList()));
  }

  @Test
  void naiveExtensionBench() {
    while (true) {
      long s = System.currentTimeMillis();
      for (int i = 0; i < 100; i++) {
        JcKZGTest.slowDasFftExtension(FFT, data);
      }
      System.out.println("Time: " + (System.currentTimeMillis() - s));
    }
  }

  @Test
  void extensionBench() {
    while (true) {
      long s = System.currentTimeMillis();
      for (int i = 0; i < 100; i++) {
        FFT.das_fft_extension(data);
      }
      System.out.println("Time: " + (System.currentTimeMillis() - s));
    }
  }

  @Test
  void recoverBench() {
    while (true) {
      long s = System.currentTimeMillis();
      for (int i = 0; i < 1; i++) {
        FFT.recover_poly_from_samples(someSamples);
      }
      System.out.println("Time: " + (System.currentTimeMillis() - s));
    }
  }

  @Test
  void longRunningMemLeakTest() {
    while (true) {
      FrVector frs2 = JcKZGTest.slowDasFftExtension(FFT, data);
      frs2.delete();
      FrVector frs = FFT.das_fft_extension(data);
      frs.delete();
      FrVector frs1 = FFT.recover_poly_from_samples(someSamples);
      frs1.delete();
    }
  }
}
