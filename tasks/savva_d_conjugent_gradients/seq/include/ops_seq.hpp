#pragma once

#include "savva_d_conjugent_gradients/common/include/common.hpp"
#include "task/include/task.hpp"

namespace savva_d_conjugent_gradients {

class SavvaDConjugentGradientsSEQ : public BaseTask {
 public:
  static constexpr ppc::task::TypeOfTask GetStaticTypeOfTask() {
    return ppc::task::TypeOfTask::kSEQ;
  }
  explicit SavvaDConjugentGradientsSEQ(const InType &in);

 private:
  bool ValidationImpl() override;
  bool PreProcessingImpl() override;
  bool RunImpl() override;
  bool PostProcessingImpl() override;
};

}  // namespace savva_d_conjugent_gradients
