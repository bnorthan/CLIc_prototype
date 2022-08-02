
#include <cassert>
#include <random>

#include "clesperanto.hpp"

template <class type>
auto
run_test (const std::array<size_t, 3> &shape, const cl_mem_object_type &mem_type) -> bool
{
    std::vector<type> input (shape[0] * shape[1] * shape[2]);
    std::vector<type> valid (shape[0] * shape[1] * 1);
    std::fill (input.begin (), input.end (), static_cast<type> (0));
    std::fill (valid.begin (), valid.end (), static_cast<type> (10));
    for (auto it = input.begin (); (it - input.begin ()) < shape[1] * shape[0]; it++)
        {
            int idx = (it - input.begin ()) + (rand () % shape[2]) * shape[0] * shape[1];
            input[idx] = static_cast<type> (10);
        }

    cle::Clesperanto cle;
    cle.GetDevice ()->WaitForKernelToFinish ();
    auto gpu_input = cle.Push<type> (input, shape, mem_type);
    auto gpu_output = cle.Create<type> ({ shape[0], shape[1], 1 }, mem_type);
    cle.MaximumZProjection (gpu_input, gpu_output);
    auto output = cle.Pull<type> (gpu_output);

    return std::equal (output.begin (), output.end (), valid.begin ());
}

auto
main (int argc, char **argv) -> int
{
    assert (run_test<float> ({ 10, 1, 1 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<int> ({ 10, 1, 1 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<unsigned int> ({ 10, 1, 1 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<short> ({ 10, 1, 1 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<unsigned short> ({ 10, 1, 1 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<char> ({ 10, 1, 1 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<unsigned char> ({ 10, 1, 1 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<float> ({ 10, 7, 1 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<int> ({ 10, 7, 1 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<unsigned int> ({ 10, 7, 1 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<short> ({ 10, 7, 1 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<unsigned short> ({ 10, 7, 1 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<char> ({ 10, 7, 1 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<unsigned char> ({ 10, 7, 1 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<float> ({ 10, 7, 5 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<int> ({ 10, 7, 5 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<unsigned int> ({ 10, 7, 5 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<short> ({ 10, 7, 5 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<unsigned short> ({ 10, 7, 5 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<char> ({ 10, 7, 5 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<unsigned char> ({ 10, 7, 5 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<float> ({ 10, 1, 1 }, CL_MEM_OBJECT_IMAGE1D));
    assert (run_test<int> ({ 10, 1, 1 }, CL_MEM_OBJECT_IMAGE1D));
    assert (run_test<unsigned int> ({ 10, 1, 1 }, CL_MEM_OBJECT_IMAGE1D));
    assert (run_test<short> ({ 10, 1, 1 }, CL_MEM_OBJECT_IMAGE1D));
    assert (run_test<unsigned short> ({ 10, 1, 1 }, CL_MEM_OBJECT_IMAGE1D));
    assert (run_test<char> ({ 10, 1, 1 }, CL_MEM_OBJECT_IMAGE1D));
    assert (run_test<unsigned char> ({ 10, 1, 1 }, CL_MEM_OBJECT_IMAGE1D));
    assert (run_test<float> ({ 10, 7, 1 }, CL_MEM_OBJECT_IMAGE1D));
    assert (run_test<int> ({ 10, 7, 1 }, CL_MEM_OBJECT_IMAGE1D));
    assert (run_test<unsigned int> ({ 10, 7, 1 }, CL_MEM_OBJECT_IMAGE1D));
    assert (run_test<short> ({ 10, 7, 1 }, CL_MEM_OBJECT_IMAGE1D));
    assert (run_test<unsigned short> ({ 10, 7, 1 }, CL_MEM_OBJECT_IMAGE1D));
    assert (run_test<char> ({ 10, 7, 1 }, CL_MEM_OBJECT_IMAGE1D));
    assert (run_test<unsigned char> ({ 10, 7, 1 }, CL_MEM_OBJECT_IMAGE1D));
    assert (run_test<float> ({ 10, 7, 5 }, CL_MEM_OBJECT_IMAGE1D));
    assert (run_test<int> ({ 10, 7, 5 }, CL_MEM_OBJECT_IMAGE1D));
    assert (run_test<unsigned int> ({ 10, 7, 5 }, CL_MEM_OBJECT_IMAGE1D));
    assert (run_test<short> ({ 10, 7, 5 }, CL_MEM_OBJECT_IMAGE1D));
    assert (run_test<unsigned short> ({ 10, 7, 5 }, CL_MEM_OBJECT_IMAGE1D));
    assert (run_test<char> ({ 10, 7, 5 }, CL_MEM_OBJECT_IMAGE1D));
    assert (run_test<unsigned char> ({ 10, 7, 5 }, CL_MEM_OBJECT_IMAGE1D));
    return EXIT_SUCCESS;
}