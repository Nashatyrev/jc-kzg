package tech.pegasys.teku.bls.impl.blst;

import org.junit.jupiter.api.Test;
import tech.pegasys.jckzg.JcKZG;
import tech.pegasys.jckzg.swig.CFFTSettings;
import tech.pegasys.jckzg.swig.CKZGSettings;
import tech.pegasys.jckzg.swig.G1Vector;
import tech.pegasys.jckzg.swig.G2Vector;

public class JcKZGTest {

  @Test
  void sanityTest() {
    JcKZG.loadNativeLibrary();

    CFFTSettings cfftSettings = new CFFTSettings(8);
    CKZGSettings ckzgSettings = new CKZGSettings(cfftSettings, new G1Vector(), new G2Vector());
  }
}
