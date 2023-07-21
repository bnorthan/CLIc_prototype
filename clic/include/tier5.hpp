#ifndef __INCLUDE_TIER5_HPP
#define __INCLUDE_TIER5_HPP

#include "array.hpp"
#include "device.hpp"
#include "execution.hpp"

namespace cle::tier5
{

auto
combine_labels_func(const Device::Pointer & device,
                    const Array::Pointer &  src0,
                    const Array::Pointer &  src1,
                    Array::Pointer          dst) -> Array::Pointer;


auto
connected_components_labeling_box_func(const Device::Pointer & device, const Array::Pointer & src, Array::Pointer dst)
  -> Array::Pointer;

} // namespace cle::tier5

#endif // __INCLUDE_TIER5_HPP
