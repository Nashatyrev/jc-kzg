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
%module "CKzg"

%include "exception.i"
%include "std_string.i"
%include "stdint.i"
%include "enums.swg"
%include "arrays_java.i"
%include "std_vector.i"
//%include "windows.i"

%template(G1Vector) std::vector<G1>;
%template(G2Vector) std::vector<G2>;
%template(FrVector) std::vector<Fr>;
%template(LongVector) std::vector<int64_t>;

%begin %{
#include "../fft_common.hpp"
#include "../kzg.hpp"
#include "../bls12_381.hpp"
#include "../poly.hpp"
%}

%include "fft_common.hpp"
%include "kzg.hpp"
%include "bls12_381.hpp"
%include "poly.hpp"
