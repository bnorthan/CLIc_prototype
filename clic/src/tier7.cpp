
#include "tier7.hpp"
#include "tier0.hpp"
#include "tier1.hpp"
#include "tier2.hpp"
#include "tier3.hpp"
#include "tier4.hpp"
#include "tier5.hpp"
#include "tier6.hpp"

namespace cle::tier7
{

auto
voronoi_otsu_labeling_func(const Device::Pointer & device,
                           const Array::Pointer &  src,
                           Array::Pointer          dst,
                           float                   spot_sigma,
                           float                   outline_sigma) -> Array::Pointer
{
  tier0::create_like(src, dst, dType::UINT32);
  auto temp = tier1::gaussian_blur_func(device, src, nullptr, spot_sigma, spot_sigma, spot_sigma);
  auto spot = tier1::detect_maxima_box_func(device, temp, nullptr);
  temp = tier1::gaussian_blur_func(device, src, nullptr, outline_sigma, outline_sigma, outline_sigma);
  auto segmentation = tier4::threshold_otsu_func(device, temp, nullptr);
  auto binary = tier1::binary_and_func(device, spot, segmentation, nullptr);
  temp = tier6::masked_voronoi_labeling_func(device, binary, segmentation, nullptr);
  return tier1::mask_func(device, temp, segmentation, dst);
}


} // namespace cle::tier7
