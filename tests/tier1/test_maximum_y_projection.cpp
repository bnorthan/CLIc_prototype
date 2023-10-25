#include "cle.hpp"

#include <array>
#include <random>

#include <gtest/gtest.h>

class TestMaximumProjectionY : public ::testing::TestWithParam<std::string>
{
protected:
  std::array<float, 10 * 1 * 3> output;
  std::array<float, 10 * 5 * 3> input;
  std::array<float, 10 * 1 * 3> valid;

  virtual void
  SetUp()
  {
    std::fill(input.begin(), input.end(), static_cast<float>(0));
    std::fill(valid.begin(), valid.end(), static_cast<float>(10));
    for (auto it = input.begin(); it != input.end(); std::advance(it, 10 * 5))
    {
      for (size_t j = 0; j < 10; j++)
      {
        int idx = (it - input.begin() + j) + (rand() % 5) * 10;
        input[idx] = static_cast<float>(10);
      }
    }
  }
};

TEST_P(TestMaximumProjectionY, execute)
{
  std::string param = GetParam();
  cle::BackendManager::getInstance().setBackend(param);
  auto device = cle::BackendManager::getInstance().getBackend().getDevice("", "all");

  auto gpu_input = cle::Array::create(10, 5, 3, cle::dType::FLOAT, cle::mType::BUFFER, device);
  gpu_input->write(input.data());

  auto gpu_output = cle::tier1::maximum_y_projection_func(device, gpu_input, nullptr);

  gpu_output->read(output.data());
  for (int i = 0; i < output.size(); i++)
  {
    EXPECT_EQ(output[i], valid[i]);
  }
}

std::vector<std::string>
getParameters()
{
  std::vector<std::string> parameters;
#if USE_OPENCL
  parameters.push_back("opencl");
#endif
#if USE_CUDA
  parameters.push_back("cuda");
#endif
  return parameters;
}

INSTANTIATE_TEST_CASE_P(InstantiationName, TestMaximumProjectionY, ::testing::ValuesIn(getParameters()));
