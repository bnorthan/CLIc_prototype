#include "cle.hpp"

#include <array>
#include <gtest/gtest.h>

class TestGenerateTouchMatrix : public ::testing::TestWithParam<std::string>
{
protected:
  std::array<float, 5 * 2 * 2>    input1 = { 1, 1, 0, 0, 0, 1, 1, 0, 3, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 4 };
  std::array<float, 5 * 2 * 2>    input2 = { 1, 1, 2, 2, 2, 1, 1, 2, 2, 2, 1, 0, 0, 2, 2, 1, 2, 2, 2, 2 };
  std::array<uint32_t, 5 * 3 * 1> valid = { 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1 };
  std::array<uint32_t, 3 * 5 * 1> output;
};

TEST_P(TestGenerateTouchMatrix, execute)
{
  std::string param = GetParam();
  cle::BackendManager::getInstance().setBackend(param);
  auto device = cle::BackendManager::getInstance().getBackend().getDevice("", "all");
  device->setWaitToFinish(true);

  auto gpu_input1 = cle::Array::create(5, 2, 2, 3, cle::dType::FLOAT, cle::mType::BUFFER, device);
  gpu_input1->write(input1.data());
  auto gpu_input2 = cle::Array::create(5, 2, 2, 3, cle::dType::FLOAT, cle::mType::BUFFER, device);
  gpu_input2->write(input2.data());

  auto gpu_output = cle::tier3::generate_binary_overlap_matrix_func(device, gpu_input1, gpu_input2, nullptr);

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

INSTANTIATE_TEST_SUITE_P(InstantiationName, TestGenerateTouchMatrix, ::testing::ValuesIn(getParameters()));