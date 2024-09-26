#include "tier0.hpp"
#include "tier1.hpp"
#include "tier2.hpp"
#include "tier3.hpp"
#include "tier4.hpp"
#include "tier5.hpp"
#include "tier6.hpp"
#include "tier7.hpp"

#include "utils.hpp"

namespace cle::tier7
{

auto
fill_holes_func(const Device::Pointer & device, const Array::Pointer & src, Array::Pointer dst, float max_size)
  -> Array::Pointer
{
  tier0::create_like(src, dst, dType::LABEL);
  // get the holes by looking at the inverted image
  auto binary = tier1::greater_constant_func(device, src, nullptr, 0);
  auto inverted = tier1::binary_not_func(device, binary, nullptr);

  auto labels = tier5::connected_component_labeling_func(device, inverted, nullptr, "box");
  tier6::remove_small_labels_func(device, labels, dst, max_size);

  // invert the filtered image
  tier1::greater_constant_func(device, dst, binary, 0);
  tier1::binary_not_func(device, binary, inverted);

  auto centroids = tier5::reduce_labels_to_centroids_func(device, src, nullptr);
  auto voroi = tier2::extend_labeling_via_voronoi_func(device, centroids, nullptr);
  return tier1::mask_func(device, voroi, inverted, dst);
}


} // namespace cle::tier7
