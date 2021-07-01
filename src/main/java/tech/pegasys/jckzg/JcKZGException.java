package tech.pegasys.jckzg;

public class JcKZGException extends RuntimeException {

  public JcKZGException() {
  }

  public JcKZGException(String message) {
    super(message);
  }

  public JcKZGException(String message, Throwable cause) {
    super(message, cause);
  }
}
