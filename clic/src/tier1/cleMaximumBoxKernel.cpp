

#include "cleMaximumBoxKernel.hpp"
#include "cleExecuteSeparableKernel.hpp"

namespace cle
{

MaximumBoxKernel::MaximumBoxKernel(std::shared_ptr<GPU> t_gpu) : 
    Kernel( t_gpu,
            "maximum_separable",
            {"src", "dst"}
    )
{
    this->m_Sources.insert({this->m_KernelName, this->m_OclHeader});
}    

int MaximumBoxKernel::Radius2KernelSize(int t_r) const
{
    return static_cast<int>(t_r) * 2 + 1;
}

void MaximumBoxKernel::SetInput(Object& t_x)
{
    this->AddObject(t_x, "src");
}

void MaximumBoxKernel::SetOutput(Object& t_x)
{
    this->AddObject(t_x, "dst");
}

void MaximumBoxKernel::SetRadius(int x, int y, int z)
{
    this->m_x = x;
    this->m_y = y;
    this->m_z = z;
}

void MaximumBoxKernel::Execute()
{
    auto src = this->GetParameter<Object>("src");
    auto dst = this->GetParameter<Object>("dst");

    int nx = Radius2KernelSize(this->m_x);
    int ny = Radius2KernelSize(this->m_y);
    int nz = Radius2KernelSize(this->m_z);

    ExecuteSeparableKernel kernel(this->m_gpu);
    kernel.SetKernelName(this->m_KernelName);
    kernel.SetSources(this->m_Sources);
    kernel.SetInput(*src);
    kernel.SetOutput(*dst);
    kernel.SetSigma(this->m_x, this->m_y, this->m_z);
    kernel.SetKernelSize(nx, ny, nz);
    kernel.Execute();
}

} // namespace cle
