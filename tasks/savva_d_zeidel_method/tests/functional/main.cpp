#include <gtest/gtest.h>
#include <stb/stb_image.h>

#include <algorithm>
#include <array>
#include <cstddef>
#include <ostream>
#include <string>
#include <tuple>
#include <vector>

#include "savva_d_zeidel_method/common/include/common.hpp"
#include "savva_d_zeidel_method/mpi/include/ops_mpi.hpp"
#include "savva_d_zeidel_method/seq/include/ops_seq.hpp"
#include "util/include/func_test_util.hpp"
#include "util/include/util.hpp"

namespace savva_d_zeidel_method {

std::ostream &operator<<(std::ostream &os, const TestType &test_param);

std::ostream &operator<<(std::ostream &os, const TestType &test_param) {
  const auto &in = test_param.in;

  const auto &name = test_param.name;

  os << "Test[" << name << ", n=" << in.n << ", a.size=" << in.a.size() << ", b.size=" << in.b.size() << "]";
  return os;
}

class SavvaDZeidelFuncTests : public ppc::util::BaseRunFuncTests<InType, OutType, TestType> {
  // тест один общий
 public:
  static std::string PrintTestParam(const TestType &test_param) {  // конструктор названия тестов
    const auto &seidelstruct = test_param.in;
    const auto &name_test = test_param.name;
    return name_test + "_" + "matrix_size_" + std::to_string(seidelstruct.n);
  }

 protected:
  void SetUp() override {  // здесь данные готовятся - например читаются изображения
    TestType params = std::get<static_cast<std::size_t>(ppc::util::GTestParamIndex::kTestParams)>(GetParam());
    input_data_ = params.in;
    right_output_data_ = params.out;
  }

  bool CheckTestOutputData(OutType &output_data) final {
    if (output_data.size() != right_output_data_.size()) {
      return false;
    }
    for (size_t i = 0; i < output_data.size(); ++i) {
      if (0.001 < std::abs(output_data[i] - right_output_data_[i])) {
        return false;
      }
    }
    return true;
  }

  InType GetTestInputData() final {
    return input_data_;
  }

 private:
  InType input_data_;
  OutType right_output_data_;
};

namespace {
// реализация (но пока не запуск) тестов
TEST_P(SavvaDZeidelFuncTests, MatmulFromPic) {  // не изменяется во всех задачах - генерация теста с параметрами
  ExecuteTest(GetParam());
}

// const SeidelInput param1{0, {}, {}};
// const OutType vec1{};

const SeidelInput param2{1, {2.0}, {4.0}};
const OutType vec2{2.0};

const SeidelInput param3{2, {3.0, 1.0, 2.0, 5.0}, {5.0, 12.0}};
const OutType vec3{1.0, 2.0};

const SeidelInput param4{3, {10.0, -1.0, 2.0, -2.0, 15.0, 3.0, 1.0, 2.0, 20.0}, {11.0, 16.0, 23.0}};
const OutType vec4{1.0, 1.0, 1.0};

static const double v5_0 = 353950.0 / 1068421.0;
static const double v5_1 = 485788.0 / 1068421.0;
static const double v5_2 = 61566.0 / 1068421.0;
static const double v5_3 = 503188.0 / 1068421.0;

const SeidelInput param5{
    4, {5.0, 0.5, 1.2, 0.1, 0.2, 6.0, 0.3, 0.4, 1.1, 0.2, 7.0, 0.3, 0.1, 0.4, 0.3, 8.0}, {2.0, 3.0, 1.0, 4.0}};
const OutType vec5{v5_0, v5_1, v5_2, v5_3};

static const double v6_0 = -3082820798382051.0 / 12480150365419456.0;
static const double v6_1 = 2481857355488935.0 / 6240075182709728.0;
static const double v6_2 = -8818834781200853.0 / 64107151648602824.0;

const SeidelInput param6{
    3, {-8.731, 0.214, -0.517, 0.421, 10.842, -0.318, -0.356, 0.419, -9.953}, {2.312948, 4.251926, 1.623761}};
const OutType vec6{v6_0, v6_1, v6_2};
// std::make_tuple(param1, vec1, "empty_system"),
const std::array<TestType, 5> kTestParam = {{{param2, vec2, "single_equation"},
                                             {param3, vec3, "two_by_two_system"},
                                             {param4, vec4, "three_by_three_negative"},
                                             {param5, vec5, "four_by_four_fractional"},
                                             {param6, vec6, "three_by_three_negative_fractional"}}};

// не изменяется (определяет какие тесты будем запускать - сек и мпай )
const auto kTestTasksList =
    std::tuple_cat(ppc::util::AddFuncTask<SavvaDZeidelSEQ, InType>(kTestParam, PPC_SETTINGS_savva_d_zeidel_method),
                   ppc::util::AddFuncTask<SavvaDZeidelMPI, InType>(kTestParam, PPC_SETTINGS_savva_d_zeidel_method));

const auto kGtestValues = ppc::util::ExpandToValues(kTestTasksList);

const auto kPerfTestName = SavvaDZeidelFuncTests::PrintFuncTestName<SavvaDZeidelFuncTests>;

INSTANTIATE_TEST_SUITE_P(PicMatrixTests, SavvaDZeidelFuncTests, kGtestValues,
                         kPerfTestName);  // здесь запуск тестов

}  // namespace

}  // namespace savva_d_zeidel_method
