package tech.pegasys.teku.bls.impl.blst;

import java.util.ArrayList;
import java.util.List;
import org.apache.commons.lang3.tuple.Pair;
import tech.pegasys.jckzg.swig.Fr;
import tech.pegasys.jckzg.swig.G1;
import tech.pegasys.jckzg.swig.G1Vector;
import tech.pegasys.jckzg.swig.G2;
import tech.pegasys.jckzg.swig.G2Vector;

public class TestUtils {

  // static const scalar_t secret = {0xa4, 0x73, 0x31, 0x95, 0x28, 0xc8, 0xb6, 0xea, 0x4d, 0x08, 0xcc,
  //                                0x53, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  //                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  public final static Fr SECRET = Fr
      .from_jlongs(new long[]{0xa473319528c8b6eaL, 0x4d08cc5318L, 0, 0});

  public static Fr longToFr(long l) {
    return Fr.from_jlongs(new long[]{l, 0, 0, 0});
  }

  public static Pair<G1Vector, G2Vector> generateTrustedSetup(Fr secret, int n) {
    Fr sPow = Fr.getONE();

    G1 g1Generator = G1.getGENERATOR();
    G2 g2Generator = G2.getGENERATOR();

    List<G1> g1s = new ArrayList<>();
    List<G2> g2s = new ArrayList<>();
    for (int i = 0; i < n; i++) {
      g1s.add(g1Generator.mul(sPow));
      g2s.add(g2Generator.mul(sPow));
      sPow = sPow.mul(secret);
    }
    return Pair.of(new G1Vector(g1s), new G2Vector(g2s));
  }
}
