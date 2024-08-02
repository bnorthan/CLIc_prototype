#include "tier0.hpp"
#include "tier1.hpp"
#include "tier3.hpp"

namespace cle::tier3
{

auto
statistics_of_labelled_pixels(const Device::Pointer & device,
                              const Array::Pointer &  input,
                              Array::Pointer          intensity) -> StatisticsMap
{
  // create intensity if not set
  if (intensity == nullptr)
  {
    // std::cerr << "Warning: no intensity was provided. Pixels intensity will be set to their label value." <<
    // std::endl;
    tier0::create_like(input, intensity, dType::FLOAT);
    intensity->fill(0);
    // tier1::copy_func(device, label, intensity);
  }

  return compute_statistics_per_labels(device, input, intensity);
}


} // namespace cle::tier3
