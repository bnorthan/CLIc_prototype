#include "tier0.hpp"
#include "tier1.hpp"

#include "utils.hpp"

#include "cle_erode_box.h"

namespace cle::tier1
{

auto
erode_box_func(const Device::Pointer & device, const Array::Pointer & src, Array::Pointer dst) -> Array::Pointer
{
  std::cerr << "Deprecated: Please use erode() instead\n";
  tier0::create_like(src, dst);
  const KernelInfo    kernel = { "erode_box", kernel::erode_box };
  const ParameterList params = { { "src", src }, { "dst", dst } };
  const RangeArray    range = { dst->width(), dst->height(), dst->depth() };
  execute(device, kernel, params, range);
  return dst;
}

// erode_box_slice_by_slice_func

} // namespace cle::tier1
