
#include "cleHistogramKernel.hpp"

#include "cleMaximumOfAllPixelsKernel.hpp"
#include "cleMemory.hpp"
#include "cleMinimumOfAllPixelsKernel.hpp"
#include "cleSumZProjectionKernel.hpp"
#include "cleUtils.hpp"

namespace cle
{

HistogramKernel::HistogramKernel (const ProcessorPointer &device) : Operation (device, 8, 1)
{
    std::string cl_header_ = {
#include "cle_histogram.h"
    };
    this->SetSource ("histogram", cl_header_);
}

void
HistogramKernel::SetInput (const Image &object)
{
    this->AddParameter ("src", object);
}

void
HistogramKernel::SetOutput (const Image &object)
{
    this->AddParameter ("histogram", object);
}

void
HistogramKernel::SetMinimumIntensity (const float &value)
{
    this->min_intensity_ = value;
}

void
HistogramKernel::SetMaximumIntensity (const float &value)
{
    this->max_intensity_ = value;
}

void
HistogramKernel::SetSteps (const int &step_x, const int &step_y, const int &step_z)
{
    this->AddParameter ("step_size_x", step_x);
    this->AddParameter ("step_size_y", step_y);
    this->AddParameter ("step_size_z", step_z);
}

void
HistogramKernel::SetNumBins (const size_t &bin)
{
    this->nb_bins_ = bin;
    this->AddConstant ("NUMBER_OF_HISTOGRAM_BINS", this->nb_bins_);
}

void
HistogramKernel::Execute ()
{
    float infinity = std::numeric_limits<float>::infinity ();

    auto dst = this->GetImage ("histogram");
    auto src = this->GetImage ("src");

    const size_t nb_partial_hist = src->Shape ()[1];

    if (this->min_intensity_ == infinity || this->max_intensity_ == infinity)
        {
            auto temp_scalar_buffer = Memory::AllocateObject (this->Device (), { 1, 1, 1 });

            MinimumOfAllPixelsKernel minimum_intensity_kernel (this->Device ());
            minimum_intensity_kernel.SetInput (*src);
            minimum_intensity_kernel.SetOutput (temp_scalar_buffer);
            minimum_intensity_kernel.Execute ();
            this->min_intensity_ = Memory::ReadObject<float> (temp_scalar_buffer).front ();

            MaximumOfAllPixelsKernel maximum_intensity_kernel (this->Device ());
            maximum_intensity_kernel.SetInput (*src);
            maximum_intensity_kernel.SetOutput (temp_scalar_buffer);
            maximum_intensity_kernel.Execute ();
            this->max_intensity_ = Memory::ReadObject<float> (temp_scalar_buffer).front ();
        }
    this->AddParameter ("minimum", this->min_intensity_);
    this->AddParameter ("maximum", this->max_intensity_);

    // create partial histogram step
    auto partial_hist = Memory::AllocateObject (this->Device (), { this->nb_bins_, 1, nb_partial_hist });
    this->AddParameter ("dst", partial_hist);

    this->SetRange (std::array<size_t, 3>{ nb_partial_hist, 1, 1 });
    this->Operation::Execute ();

    // run projection
    SumZProjectionKernel sum (this->Device ());
    sum.SetInput (partial_hist);
    sum.SetOutput (*dst);
    sum.Execute ();
}

} // namespace cle