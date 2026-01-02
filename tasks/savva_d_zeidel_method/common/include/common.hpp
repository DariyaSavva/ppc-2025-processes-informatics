#pragma once

#include <string>
#include <tuple>
#include <vector>

#include "task/include/task.hpp"

namespace savva_d_zeidel_method {

struct SeidelInput {
  int n;
  std::vector<double> a;
  std::vector<double> b;
};

using InType = SeidelInput;
using OutType = std::vector<double>;
using TestType = std::tuple<SeidelInput, OutType, std::string>;
using BaseTask = ppc::task::Task<InType, OutType>;

}  // namespace savva_d_zeidel_method
