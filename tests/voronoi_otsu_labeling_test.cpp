
#include <random>
#include "clesperanto.hpp"
#include "utils.hpp"

template<class type>
std::array<size_t,3> generate_data(std::vector<type>& arr_1,
                                   std::vector<type>& valid, size_t width, size_t height, size_t depth)
{
    arr_1.resize(width*height*depth);
    valid.resize(width*height*depth);
    arr_1 = {0, 0, 1, 1, 0, 0,
             0, 1, 8, 9, 1, 0,
             0, 1, 7, 6, 1, 0,
             0, 0, 1, 1, 1, 0,
             0, 0, 1, 1, 1, 0,
             0, 0, 1, 8, 7, 1,
             0, 0, 1, 1, 1, 0};
    valid = {0, 0, 1, 1, 0, 0,
             0, 1, 1, 1, 1, 0,
             0, 1, 1, 1, 1, 0,
             0, 0, 2, 2, 2, 0,
             0, 0, 0, 2, 2, 0,
             0, 0, 2, 2, 2, 0,
             0, 0, 0, 2, 2, 0};
    return std::array<size_t,3> {width, height, depth};
}

template<class type>
std::vector<type> run_kernel_with_buffer( std::vector<type>& arr_1, std::array<size_t,3>& shape)
{
    cle::Clesperanto cle;
    cle.Ressources()->SetWaitForKernelToFinish(true);
    auto oclArray_A = cle.Push<type>(arr_1, shape);
    auto ocl_output = cle.Create<type>(shape);
    cle.VoronoiOtsuLabeling(oclArray_A, ocl_output, 1, 1);  
    auto output = cle.Pull<type>(ocl_output); 
    return output; 
}

template<class type>
std::vector<type> run_kernel_with_image( std::vector<type>& arr_1, std::array<size_t,3>& shape)
{
    cle::Clesperanto cle;
    cle.Ressources()->SetWaitForKernelToFinish(true);
    auto oclArray_A = cle.Push<type>(arr_1, shape, "image");
    auto ocl_output = cle.Create<type>(shape, "image");
    cle.VoronoiOtsuLabeling(oclArray_A, ocl_output, 1, 1);  
    auto output = cle.Pull<type>(ocl_output);  
    return output; 
}

template<class type>
bool test(size_t width, size_t height, size_t depth)
{
    std::vector<type> arr_1, valid;
    std::array<size_t,3> shape = generate_data<type>(arr_1, valid, width, height, depth);
    auto arr_buffer = run_kernel_with_buffer<type>(arr_1, shape);    
    if (IsDifferent(arr_buffer, valid))
    {
        std::cerr << "kernel ("<<width<<","<<height<<","<<depth<<") using buffer ... FAILED! " << std::endl;
        return true;
    }
    auto arr_image  = run_kernel_with_image<type>(arr_1, shape);
    if (IsDifferent(arr_image, valid))
    {
        std::cerr << "kernel ("<<width<<","<<height<<","<<depth<<") using image ... FAILED! " << std::endl;
        return true;
    }
    return false;
}

int main(int argc, char **argv)
{
    if (test<float>(6, 7, 1))
    {
        std::cerr << "VoronoiOtsuLabeling kernel 2d ... FAILED! " << std::endl;
        return EXIT_FAILURE;
    }
    
    std::cout << "VoronoiOtsuLabeling kernel test ... PASSED! " << std::endl;
    return EXIT_SUCCESS;
}