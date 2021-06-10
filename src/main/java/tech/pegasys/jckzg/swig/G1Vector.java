/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 4.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package tech.pegasys.jckzg.swig;

public class G1Vector extends java.util.AbstractList<G1> implements java.util.RandomAccess {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected G1Vector(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(G1Vector obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  @SuppressWarnings("deprecation")
  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        CKzgJNI.delete_G1Vector(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public G1Vector(G1[] initialElements) {
    this();
    reserve(initialElements.length);

    for (G1 element : initialElements) {
      add(element);
    }
  }

  public G1Vector(Iterable<G1> initialElements) {
    this();
    for (G1 element : initialElements) {
      add(element);
    }
  }

  public G1 get(int index) {
    return doGet(index);
  }

  public G1 set(int index, G1 e) {
    return doSet(index, e);
  }

  public boolean add(G1 e) {
    modCount++;
    doAdd(e);
    return true;
  }

  public void add(int index, G1 e) {
    modCount++;
    doAdd(index, e);
  }

  public G1 remove(int index) {
    modCount++;
    return doRemove(index);
  }

  protected void removeRange(int fromIndex, int toIndex) {
    modCount++;
    doRemoveRange(fromIndex, toIndex);
  }

  public int size() {
    return doSize();
  }

  public G1Vector() {
    this(CKzgJNI.new_G1Vector__SWIG_0(), true);
  }

  public G1Vector(G1Vector other) {
    this(CKzgJNI.new_G1Vector__SWIG_1(G1Vector.getCPtr(other), other), true);
  }

  public long capacity() {
    return CKzgJNI.G1Vector_capacity(swigCPtr, this);
  }

  public void reserve(long n) {
    CKzgJNI.G1Vector_reserve(swigCPtr, this, n);
  }

  public boolean isEmpty() {
    return CKzgJNI.G1Vector_isEmpty(swigCPtr, this);
  }

  public void clear() {
    CKzgJNI.G1Vector_clear(swigCPtr, this);
  }

  public G1Vector(int count, G1 value) {
    this(CKzgJNI.new_G1Vector__SWIG_2(count, G1.getCPtr(value), value), true);
  }

  private int doSize() {
    return CKzgJNI.G1Vector_doSize(swigCPtr, this);
  }

  private void doAdd(G1 x) {
    CKzgJNI.G1Vector_doAdd__SWIG_0(swigCPtr, this, G1.getCPtr(x), x);
  }

  private void doAdd(int index, G1 x) {
    CKzgJNI.G1Vector_doAdd__SWIG_1(swigCPtr, this, index, G1.getCPtr(x), x);
  }

  private G1 doRemove(int index) {
    return new G1(CKzgJNI.G1Vector_doRemove(swigCPtr, this, index), true);
  }

  private G1 doGet(int index) {
    return new G1(CKzgJNI.G1Vector_doGet(swigCPtr, this, index), false);
  }

  private G1 doSet(int index, G1 val) {
    return new G1(CKzgJNI.G1Vector_doSet(swigCPtr, this, index, G1.getCPtr(val), val), true);
  }

  private void doRemoveRange(int fromIndex, int toIndex) {
    CKzgJNI.G1Vector_doRemoveRange(swigCPtr, this, fromIndex, toIndex);
  }

}
