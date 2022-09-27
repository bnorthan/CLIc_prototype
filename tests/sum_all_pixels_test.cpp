

#include <random>

#include "clesperanto.hpp"

template <class type>
auto
run_test(const std::array<size_t, 3> & shape, const cle::ObjectType & mem_type) -> bool
{
  std::vector<type> input(shape[0] * shape[1] * shape[2]);
  std::fill(input.begin(), input.end(), 1);

  cle::Clesperanto cle;
  cle.GetDevice()->WaitForKernelToFinish();
  auto gpu_input = cle.Push<type>(input, shape, mem_type);
  auto gpu_output = cle.Create<type>({ 1, 1, 1 }, mem_type);
  cle.SumOfAllPixels(gpu_input, gpu_output);
  auto output = cle.Pull<type>(gpu_output).front();

  return output == input.size();
}

auto
main(int argc, char ** argv) -> int
{
  if (!run_test<float>({ 10, 1, 1 }, cle::BUFFER))
  {
    return EXIT_FAILURE;
  }
  if (!run_test<signed int>({ 10, 1, 1 }, cle::BUFFER))
  {
    return EXIT_FAILURE;
  }
  if (!run_test<unsigned int>({ 10, 1, 1 }, cle::BUFFER))
  {
    return EXIT_FAILURE;
  }
  if (!run_test<signed short>({ 10, 1, 1 }, cle::BUFFER))
  {
    return EXIT_FAILURE;
  }
  if (!run_test<unsigned short>({ 10, 1, 1 }, cle::BUFFER))
  {
    return EXIT_FAILURE;
  }
  if (!run_test<signed char>({ 10, 1, 1 }, cle::BUFFER))
  {
    return EXIT_FAILURE;
  }
  if (!run_test<unsigned char>({ 10, 1, 1 }, cle::BUFFER))
  {
    return EXIT_FAILURE;
  }
  if (!run_test<float>({ 10, 7, 1 }, cle::BUFFER))
  {
    return EXIT_FAILURE;
  }
  if (!run_test<signed int>({ 10, 7, 1 }, cle::BUFFER))
  {
    return EXIT_FAILURE;
  }
  if (!run_test<unsigned int>({ 10, 7, 1 }, cle::BUFFER))
  {
    return EXIT_FAILURE;
  }
  if (!run_test<signed short>({ 10, 7, 1 }, cle::BUFFER))
  {
    return EXIT_FAILURE;
  }
  if (!run_test<unsigned short>({ 10, 7, 1 }, cle::BUFFER))
  {
    return EXIT_FAILURE;
  }
  if (!run_test<signed char>({ 10, 7, 1 }, cle::BUFFER))
  {
    return EXIT_FAILURE;
  }
  if (!run_test<unsigned char>({ 10, 7, 1 }, cle::BUFFER))
  {
    return EXIT_FAILURE;
  }
  if (!run_test<float>({ 5, 3, 2 }, cle::BUFFER))
  {
    return EXIT_FAILURE;
  }
  if (!run_test<signed int>({ 5, 3, 2 }, cle::BUFFER))
  {
    return EXIT_FAILURE;
  }
  if (!run_test<unsigned int>({ 5, 3, 2 }, cle::BUFFER))
  {
    return EXIT_FAILURE;
  }
  if (!run_test<signed short>({ 5, 3, 2 }, cle::BUFFER))
  {
    return EXIT_FAILURE;
  }
  if (!run_test<unsigned short>({ 5, 3, 2 }, cle::BUFFER))
  {
    return EXIT_FAILURE;
  }
  if (!run_test<signed char>({ 5, 3, 2 }, cle::BUFFER))
  {
    return EXIT_FAILURE;
  }
  if (!run_test<unsigned char>({ 5, 3, 2 }, cle::BUFFER))
  {
    return EXIT_FAILURE;
  }
  if (!run_test<float>({ 10, 1, 1 }, cle::IMAGE))
  {
    return EXIT_FAILURE;
  }
  if (!run_test<signed int>({ 10, 1, 1 }, cle::IMAGE))
  {
    return EXIT_FAILURE;
  }
  if (!run_test<unsigned int>({ 10, 1, 1 }, cle::IMAGE))
  {
    return EXIT_FAILURE;
  }
  if (!run_test<signed short>({ 10, 1, 1 }, cle::IMAGE))
  {
    return EXIT_FAILURE;
  }
  if (!run_test<unsigned short>({ 10, 1, 1 }, cle::IMAGE))
  {
    return EXIT_FAILURE;
  }
  if (!run_test<signed char>({ 10, 1, 1 }, cle::IMAGE))
  {
    return EXIT_FAILURE;
  }
  if (!run_test<unsigned char>({ 10, 1, 1 }, cle::IMAGE))
  {
    return EXIT_FAILURE;
  }
  if (!run_test<float>({ 10, 7, 1 }, cle::IMAGE))
  {
    return EXIT_FAILURE;
  }
  if (!run_test<signed int>({ 10, 7, 1 }, cle::IMAGE))
  {
    return EXIT_FAILURE;
  }
  if (!run_test<unsigned int>({ 10, 7, 1 }, cle::IMAGE))
  {
    return EXIT_FAILURE;
  }
  if (!run_test<signed short>({ 10, 7, 1 }, cle::IMAGE))
  {
    return EXIT_FAILURE;
  }
  if (!run_test<unsigned short>({ 10, 7, 1 }, cle::IMAGE))
  {
    return EXIT_FAILURE;
  }
  if (!run_test<signed char>({ 10, 7, 1 }, cle::IMAGE))
  {
    return EXIT_FAILURE;
  }
  if (!run_test<unsigned char>({ 10, 7, 1 }, cle::IMAGE))
  {
    return EXIT_FAILURE;
  }
  if (!run_test<float>({ 5, 3, 2 }, cle::IMAGE))
  {
    return EXIT_FAILURE;
  }
  if (!run_test<signed int>({ 5, 3, 2 }, cle::IMAGE))
  {
    return EXIT_FAILURE;
  }
  if (!run_test<unsigned int>({ 5, 3, 2 }, cle::IMAGE))
  {
    return EXIT_FAILURE;
  }
  if (!run_test<signed short>({ 5, 3, 2 }, cle::IMAGE))
  {
    return EXIT_FAILURE;
  }
  if (!run_test<unsigned short>({ 5, 3, 2 }, cle::IMAGE))
  {
    return EXIT_FAILURE;
  }
  if (!run_test<signed char>({ 5, 3, 2 }, cle::IMAGE))
  {
    return EXIT_FAILURE;
  }
  if (!run_test<unsigned char>({ 5, 3, 2 }, cle::IMAGE))
  {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}