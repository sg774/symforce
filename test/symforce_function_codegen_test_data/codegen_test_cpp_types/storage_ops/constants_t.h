// ----------------------------------------------------------------------------
// This file was autogenerated by symforce. Do NOT modify by hand.
// ----------------------------------------------------------------------------
#pragma once

#include <cassert>
#include <vector>

namespace codegen_test_cpp_types {
namespace StorageOps {

template<>
inline size_t StorageDim<constants_t>() {
  return 1;
};

template<>
inline void ToStorage<constants_t>(const constants_t& value, std::vector<double>* vec) {
  assert(vec != nullptr);
  std::vector<double>& v = (*vec);
  v.resize(1);

  v[0] = value.epsilon;
}

template<typename Container>
void FromStorage(const Container& elements, constants_t* out) {
  assert(out != nullptr);
  out->epsilon = elements[0];
}

}  // namespace StorageOps
}  // namespace codegen_test_cpp_types