
#include <cassert>
#include <random>

#include "clesperanto.hpp"

template <class type>
auto
run_test (const std::array<size_t, 3> &shape, const cl_mem_object_type &mem_type) -> bool
{
    std::vector<float> input (shape[0] * shape[1] * shape[2]);
    std::vector<type> valid (shape[0] * shape[1] * shape[2]);
    std::fill (input.begin (), input.end (), static_cast<type> (0));
    std::fill (valid.begin (), valid.end (), static_cast<type> (0));
    const int center = (shape[0] / 2) + (shape[1] / 2) * shape[0] + (shape[2] / 2) * shape[1] * shape[0];
    input[center] = 100;
    if (valid.size () == 27)
        valid = {
            static_cast<type> (1.41674721F), static_cast<type> (2.33582091F), static_cast<type> (1.41674721F),
            static_cast<type> (2.33582115F), static_cast<type> (3.85111761F), static_cast<type> (2.33582115F),
            static_cast<type> (1.41674721F), static_cast<type> (2.33582091F), static_cast<type> (1.41674721F),
            static_cast<type> (2.33582115F), static_cast<type> (3.85111761F), static_cast<type> (2.33582115F),
            static_cast<type> (3.85111785F), static_cast<type> (6.34941959F), static_cast<type> (3.85111785F),
            static_cast<type> (2.33582115F), static_cast<type> (3.85111761F), static_cast<type> (2.33582115F),
            static_cast<type> (1.41674721F), static_cast<type> (2.33582091F), static_cast<type> (1.41674721F),
            static_cast<type> (2.33582115F), static_cast<type> (3.85111761F), static_cast<type> (2.33582115F),
            static_cast<type> (1.41674721F), static_cast<type> (2.33582091F), static_cast<type> (1.41674721F)
        };

    if (valid.size () == 9)
        valid = {
            static_cast<type> (5.85501814F), static_cast<type> (9.6532917F), static_cast<type> (5.85501814F),
            static_cast<type> (9.65329266F), static_cast<type> (15.9155874F), static_cast<type> (9.65329266F),
            static_cast<type> (5.85501814F), static_cast<type> (9.6532917F), static_cast<type> (5.85501814F)
        };

    if (valid.size () == 3)
        valid = {
            static_cast<type> (24.1971455F), static_cast<type> (39.8943443F), static_cast<type> (24.1971455F)
        };

    cle::Clesperanto cle;
    cle.GetDevice ()->WaitForKernelToFinish ();
    auto gpu_input = cle.Push<float> (input, shape, mem_type);
    auto gpu_output = cle.Create<type> (shape, mem_type);
    cle.GaussianBlur (gpu_input, gpu_output, 1, 1, 1);
    auto output = cle.Pull<type> (gpu_output);

    //! how can we improve float accuracy between gpu and cpu?
    // std::transform (output.begin (), output.end (), output.begin (), [] (const type &x) { return static_cast<type> (std::floor (static_cast<float> (x) * 1000) / 1000); });
    // std::transform (valid.begin (), valid.end (), valid.begin (), [] (const type &x) { return static_cast<type> (std::floor (static_cast<float> (x) * 1000) / 1000); });

    // std::copy (std::begin (input),
    //            std::end (input),
    //            std::ostream_iterator<type> (std::cout, ", "));
    // std::cout << std::endl;

    // std::copy (std::begin (valid),
    //            std::end (valid),
    //            std::ostream_iterator<type> (std::cout, ", "));
    // std::cout << std::endl;

    // std::copy (std::begin (output),
    //            std::end (output),
    //            std::ostream_iterator<type> (std::cout, ", "));
    // std::cout << std::endl;

    return std::equal (output.begin (), output.end (), valid.begin ());
}

auto
main (int argc, char **argv) -> int
{
    assert (run_test<float> ({ 3, 1, 1 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<int> ({ 3, 1, 1 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<unsigned int> ({ 3, 1, 1 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<short> ({ 3, 1, 1 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<unsigned short> ({ 3, 1, 1 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<char> ({ 3, 1, 1 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<unsigned char> ({ 3, 1, 1 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<float> ({ 3, 3, 1 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<int> ({ 3, 3, 1 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<unsigned int> ({ 3, 3, 1 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<short> ({ 3, 3, 1 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<unsigned short> ({ 3, 3, 1 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<char> ({ 3, 3, 1 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<unsigned char> ({ 3, 3, 1 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<float> ({ 3, 3, 3 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<int> ({ 3, 3, 3 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<unsigned int> ({ 3, 3, 3 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<short> ({ 3, 3, 3 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<unsigned short> ({ 3, 3, 3 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<char> ({ 3, 3, 3 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<unsigned char> ({ 3, 3, 3 }, CL_MEM_OBJECT_BUFFER));
    assert (run_test<float> ({ 3, 1, 1 }, CL_MEM_OBJECT_IMAGE1D));
    //    assert (run_test<int>({ 3, 1, 1 }, CL_MEM_OBJECT_IMAGE1D));
    //    assert (run_test<unsigned int>({ 3, 1, 1 }, CL_MEM_OBJECT_IMAGE1D));
    //    assert (run_test<short>({ 3, 1, 1 }, CL_MEM_OBJECT_IMAGE1D));
    //    assert (run_test<unsigned short>({ 3, 1, 1 }, CL_MEM_OBJECT_IMAGE1D));
    //    assert (run_test<char>({ 3, 1, 1 }, CL_MEM_OBJECT_IMAGE1D));
    //    assert (run_test<unsigned char>({ 3, 1, 1 }, CL_MEM_OBJECT_IMAGE1D));
    assert (run_test<float> ({ 3, 3, 1 }, CL_MEM_OBJECT_IMAGE1D));
    //    assert (run_test<int>({ 3, 3, 1 }, CL_MEM_OBJECT_IMAGE1D));
    //    assert (run_test<unsigned int>({ 3, 3, 1 }, CL_MEM_OBJECT_IMAGE1D));
    //    assert (run_test<short>({ 3, 3, 1 }, CL_MEM_OBJECT_IMAGE1D));
    //    assert (run_test<unsigned short>({ 3, 3, 1 }, CL_MEM_OBJECT_IMAGE1D));
    //    assert (run_test<char>({ 3, 3, 1 }, CL_MEM_OBJECT_IMAGE1D));
    //    assert (run_test<unsigned char>({ 3, 3, 1 }, CL_MEM_OBJECT_IMAGE1D));
    assert (run_test<float> ({ 3, 3, 3 }, CL_MEM_OBJECT_IMAGE1D));
    //    assert (run_test<int>({ 3, 3, 3 }, CL_MEM_OBJECT_IMAGE1D));
    //    assert (run_test<unsigned int>({ 3, 3, 3 }, CL_MEM_OBJECT_IMAGE1D));
    //    assert (run_test<short>({ 3, 3, 3 }, CL_MEM_OBJECT_IMAGE1D));
    //    assert (run_test<unsigned short>({ 3, 3, 3 }, CL_MEM_OBJECT_IMAGE1D));
    //    assert (run_test<char>({ 3, 3, 3 }, CL_MEM_OBJECT_IMAGE1D));
    //    assert (run_test<unsigned char>({ 3, 3, 3 }, CL_MEM_OBJECT_IMAGE1D));
    return EXIT_SUCCESS;
}
