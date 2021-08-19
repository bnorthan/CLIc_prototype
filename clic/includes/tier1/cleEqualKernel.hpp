
#ifndef __cleEqualKernel_hpp
#define __cleEqualKernel_hpp

#include "cleKernel.hpp"

namespace cle
{
    
class EqualKernel : public Kernel
{

private:
    std::string source_2d = 
        #include "cle_equal_2d.h" 
        ;
    std::string source_3d = 
        #include "cle_equal_3d.h" 
        ;

public:

    EqualKernel (std::shared_ptr<GPU> gpu) : 
        Kernel( gpu,
                "equal",
                {"src1", "src2", "dst"}
        )
    {
        m_Sources.insert({this->m_KernelName + "_2d", source_2d});
        m_Sources.insert({this->m_KernelName + "_3d", source_3d});
    }
    void SetInput1(Buffer&);
    void SetInput2(Buffer&);
    void SetOutput(Buffer&);
    void Execute();

};

} // namespace cle

#endif // __cleGreaterKernel_hpp
