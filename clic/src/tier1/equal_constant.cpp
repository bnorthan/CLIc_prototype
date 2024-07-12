#include "tier0.hpp"
#include "tier1.hpp"

#include "utils.hpp"

#include "cle_equal_constant.h"
#include "cle_greater_or_equal_constant.h"
#include "cle_not_equal_constant.h"
#include "cle_smaller_or_equal_constant.h"

namespace cle::tier1
{

auto
equal_constant_func(const Device::Pointer & device, const Array::Pointer & src, Array::Pointer dst, float scalar)
  -> Array::Pointer
{
  tier0::create_like(src, dst, dType::BINARY);
  const KernelInfo    kernel = { "equal_constant", kernel::equal_constant };
  const ParameterList params = { { "src", src }, { "dst", dst }, { "scalar", scalar } };
  const RangeArray    range = { dst->width(), dst->height(), dst->depth() };
  execute(device, kernel, params, range);
  return dst;
}

} // namespace cle::tier1
