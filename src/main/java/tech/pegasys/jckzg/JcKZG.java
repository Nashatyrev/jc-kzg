package tech.pegasys.jckzg;

import java.util.Map;

public class JcKZG {

  private static final Map<String, String> ARCH_MAPPING = Map.of(
      "x86_64", "x86_64",
      "amd64", "x86_64",
      "aarch64", "aarch64"
  );
  private static boolean loaded = false;

  public static synchronized void loadNativeLibrary() throws UnsupportedOperationException {
    if (loaded) {
      return;
    }
    String libLocation = "/" + getArch() + "/" + System.mapLibraryName("jc-kzg");
    try {
      NativeUtils.loadLibraryFromJar(libLocation);
      loaded = true;
    } catch (Throwable e) {
      throw new UnsupportedOperationException(
          "Couldn't load native library (from resource " + libLocation + "): ", e);
    }
  }

  private static String getArch() {
    String osArch = System.getProperty("os.arch");
    String arch = ARCH_MAPPING.get(osArch);
    if (arch == null) {
      throw new UnsupportedOperationException(
          "Unknown arch value from 'os.arch' property: '" + osArch + "'");
    }
    return arch;
  }
}
