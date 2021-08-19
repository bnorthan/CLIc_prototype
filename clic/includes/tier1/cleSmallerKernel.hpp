
#ifndef __cleSmallerKernel_hpp
#define __cleSmallerKernel_hpp

#include "cleKernel.hpp"

namespace cle
{
    
class SmallerKernel : public Kernel
{

private:
    std::string source_2d = 
        #include "cle_smaller_2d.h" 
        ;
    std::string source_3d = 
        #include "cle_smaller_3d.h" 
        ;

public:
    SmallerKernel (std::shared_ptr<GPU> gpu) : 
        Kernel( gpu, 
                "smaller",
                {"src1" , "src2", "dst"}
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

#endif // __cleSmallerKernel_hpp
