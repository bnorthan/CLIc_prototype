#include "tier0.hpp"
#include "tier1.hpp"

#include "utils.hpp"

#include "cle_nonzero_minimum_box.h"
#include "cle_nonzero_minimum_diamond.h"

namespace cle::tier1
{

auto
nonzero_minimum_func(const Device::Pointer & device,
                     const Array::Pointer &  src,
                     Array::Pointer          dst0,
                     Array::Pointer          dst1,
                     std::string             connectivity) -> Array::Pointer
{
  tier0::create_like(src, dst1);
  KernelInfo kernel = { "nonzero_minimum_box", kernel::nonzero_minimum_box };
  if (connectivity == "sphere")
  {
    kernel = { "nonzero_minimum_diamond", kernel::nonzero_minimum_diamond };
  }
  const ParameterList params = { { "src", src }, { "dst0", dst0 }, { "dst1", dst1 } };
  const RangeArray    range = { dst1->width(), dst1->height(), dst1->depth() };
  execute(device, kernel, params, range);
  return dst1;
}

auto
nonzero_minimum_diamond_func(const Device::Pointer & device,
                             const Array::Pointer &  src,
                             Array::Pointer          dst0,
                             Array::Pointer          dst1) -> Array::Pointer
{
  return nonzero_minimum_func(device, src, dst0, dst1, "sphere");
}

auto
nonzero_minimum_box_func(const Device::Pointer & device,
                         const Array::Pointer &  src,
                         Array::Pointer          dst0,
                         Array::Pointer          dst1) -> Array::Pointer
{
  return nonzero_minimum_func(device, src, dst0, dst1, "box");
}

} // namespace cle::tier1
