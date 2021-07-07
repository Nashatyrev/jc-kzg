/*
 * Copyright 2021 Benjamin Edgington
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
%module "JcKzg"

%include "exception.i"
%include "std_string.i"
%include "stdint.i"
%include "enums.swg"
%include "arrays_java.i"
%include "std_vector.i"

%template(G1Vector) std::vector<G1>;
%template(G2Vector) std::vector<G2>;
%template(FrVector) std::vector<Fr>;
%template(LongVector) std::vector<long long>;

%begin %{
#include "fft.hpp"
#include "kzg.hpp"
#include "fk20.hpp"
#include "bls12_381.hpp"
#include "poly.hpp"
%}

// Allow C++ exceptions to be handled in Java
%typemap(throws) KZGException {
  jclass excep = jenv->FindClass("tech/pegasys/jckzg/JcKZGException");
  if (excep)
    jenv->ThrowNew(excep, $1.what().c_str());
  return $null;
}

%typemap(javacode) Fr %{
  public boolean equals(Object obj) {
    if (obj instanceof $javaclassname)
      return (($javaclassname)obj).equal(this);
    else
      return false;
  }

  @Override
  public String toString() {
    LongVector longs = to_longs();
    return String.format("Fr[%016X %016X %016X %016X]",
        longs.get(0), longs.get(1), longs.get(2), longs.get(3)) ;
  }
%}

%ignore FK20Single;
%ignore FK20Multi;
%ignore Fr::Fr();
%ignore G1::G1();

%include "fft.hpp"
%include "kzg.hpp"
%include "fk20.hpp"
%include "bls12_381.hpp"
%include "poly.hpp"
