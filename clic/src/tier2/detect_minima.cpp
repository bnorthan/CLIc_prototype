#include "tier0.hpp"
#include "tier1.hpp"
#include "tier2.hpp"

#include "utils.hpp"

#include "cle_detect_minima.h"

namespace cle::tier2
{

auto
detect_minima_func(const Device::Pointer & device,
                   const Array::Pointer &  src,
                   Array::Pointer          dst,
                   int                     radius_x,
                   int                     radius_y,
                   int                     radius_z,
                   std::string             connectivity) -> Array::Pointer
{
  tier0::create_like(src, dst, dType::BINARY);
  auto                temp = tier1::mean_func(device, src, nullptr, radius_x, radius_y, radius_z, connectivity);
  const KernelInfo    kernel = { "detect_minima", kernel::detect_minima };
  const ParameterList params = { { "src", temp }, { "dst", dst } };
  const RangeArray    range = { dst->width(), dst->height(), dst->depth() };
  execute(device, kernel, params, range);
  return dst;
}

} // namespace cle::tier2
