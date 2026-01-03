#pragma once

#include <string>
#include <tuple>
#include <vector>

#include "task/include/task.hpp"

namespace savva_d_zeidel_method {

struct SeidelInput {
  int n = 0;
  std::vector<double> a{};
  std::vector<double> b{};
};

using InType = SeidelInput;
using OutType = std::vector<double>;
using TestType = std::tuple<SeidelInput, OutType, std::string>;
using BaseTask = ppc::task::Task<InType, OutType>;

std::ostream &operator<<(std::ostream &os, const TestType &test_param) {
  const auto &in = std::get<0>(test_param);
  const auto &out = std::get<1>(test_param);
  const auto &name = std::get<2>(test_param);
  os << "Test[" << name << ", n=" << in.n << ", a.size=" << in.a.size() << ", b.size=" << in.b.size()
     << ", out.size=" << out.size() << "]";
  return os;
}

}  // namespace savva_d_zeidel_method
