
#include <random>

#include "cleUtils.hpp"
#include "clesperanto.hpp"

template <class type>
std::array<size_t, 3>
generate_data (std::vector<type> &arr_1,
               std::vector<type> &valid, size_t width, size_t height, size_t depth)
{
    arr_1.resize (width * height * depth);
    valid.resize (width * height * depth);

    arr_1 = { static_cast<type> (1.0), static_cast<type> (2.0), static_cast<type> (3.0), static_cast<type> (4.0), static_cast<type> (5.0), static_cast<type> (6.0), static_cast<type> (7.0), static_cast<type> (8.0), static_cast<type> (9.0), static_cast<type> (10.0), static_cast<type> (11.0), 12.0f }; // 6.0058594 skimage
    valid = { static_cast<type> (0.0), static_cast<type> (0.0), static_cast<type> (0.0), static_cast<type> (0.0), static_cast<type> (0.0), static_cast<type> (0.0), static_cast<type> (1.0), static_cast<type> (1.0), static_cast<type> (1.0), static_cast<type> (1.0), static_cast<type> (1.0), 1.0f };    // 6.00392 clic

    return std::array<size_t, 3>{ width, height, depth };
}

#include <random>

#include "clesperanto.hpp"

template <class type>
auto
run_test (const std::array<size_t, 3> &shape, const cl_mem_object_type &mem_type) -> bool
{
    std::vector<type> input (shape[0] * shape[1] * shape[2]);
    std::vector<type> valid (shape[0] * shape[1] * shape[2]);

    input = { static_cast<type> (1.0), static_cast<type> (2.0), static_cast<type> (3.0), static_cast<type> (4.0), static_cast<type> (5.0), static_cast<type> (6.0), static_cast<type> (7.0), static_cast<type> (8.0), static_cast<type> (9.0), static_cast<type> (10.0), static_cast<type> (11.0), static_cast<type> (12.0) }; // 6.0058594 skimage
    valid = { static_cast<type> (0.0), static_cast<type> (0.0), static_cast<type> (0.0), static_cast<type> (0.0), static_cast<type> (0.0), static_cast<type> (0.0), static_cast<type> (1.0), static_cast<type> (1.0), static_cast<type> (1.0), static_cast<type> (1.0), static_cast<type> (1.0), static_cast<type> (1.0) };    // 6.00392 clic

    cle::Clesperanto cle;
    cle.GetDevice ()->WaitForKernelToFinish ();
    auto gpu_input = cle.Push<type> (input, shape, mem_type);
    auto gpu_output = cle.Create<type> (shape, mem_type);
    cle.ThresholdOtsu (gpu_input, gpu_output);
    auto output = cle.Pull<type> (gpu_output);

    return std::equal (output.begin (), output.end (), valid.begin ());
}

auto
main (int argc, char **argv) -> int
{
    if (!run_test<float> ({ 12, 1, 1 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<int> ({ 12, 1, 1 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<unsigned int> ({ 12, 1, 1 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<short> ({ 12, 1, 1 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<unsigned short> ({ 12, 1, 1 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<char> ({ 12, 1, 1 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<unsigned char> ({ 12, 1, 1 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<float> ({ 6, 2, 1 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<int> ({ 6, 2, 1 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<unsigned int> ({ 6, 2, 1 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<short> ({ 6, 2, 1 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<unsigned short> ({ 6, 2, 1 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<char> ({ 6, 2, 1 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<unsigned char> ({ 6, 2, 1 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<float> ({ 3, 2, 2 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<int> ({ 3, 2, 2 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<unsigned int> ({ 3, 2, 2 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<short> ({ 3, 2, 2 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<unsigned short> ({ 3, 2, 2 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<char> ({ 3, 2, 2 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<unsigned char> ({ 3, 2, 2 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<float> ({ 12, 1, 1 }, CL_MEM_OBJECT_IMAGE1D))
        return EXIT_FAILURE;
    //    if (!run_test<int>({ 12, 1, 1 }, CL_MEM_OBJECT_IMAGE1D)) return EXIT_FAILURE;
    //    if (!run_test<unsigned int>({ 12, 1, 1 }, CL_MEM_OBJECT_IMAGE1D)) return EXIT_FAILURE;
    //    if (!run_test<short>({ 12, 1, 1 }, CL_MEM_OBJECT_IMAGE1D)) return EXIT_FAILURE;
    //    if (!run_test<unsigned short>({ 12, 1, 1 }, CL_MEM_OBJECT_IMAGE1D)) return EXIT_FAILURE;
    //    if (!run_test<char>({ 12, 1, 1 }, CL_MEM_OBJECT_IMAGE1D)) return EXIT_FAILURE;
    //    if (!run_test<unsigned char>({ 12, 1, 1 }, CL_MEM_OBJECT_IMAGE1D)) return EXIT_FAILURE;
    if (!run_test<float> ({ 6, 2, 1 }, CL_MEM_OBJECT_IMAGE1D))
        return EXIT_FAILURE;
    //    if (!run_test<int>({ 6, 2, 1 }, CL_MEM_OBJECT_IMAGE1D)) return EXIT_FAILURE;
    //    if (!run_test<unsigned int>({ 6, 2, 1 }, CL_MEM_OBJECT_IMAGE1D)) return EXIT_FAILURE;
    //    if (!run_test<short>({ 6, 2, 1 }, CL_MEM_OBJECT_IMAGE1D)) return EXIT_FAILURE;
    //    if (!run_test<unsigned short>({ 6, 2, 1 }, CL_MEM_OBJECT_IMAGE1D)) return EXIT_FAILURE;
    //    if (!run_test<char>({ 6, 2, 1 }, CL_MEM_OBJECT_IMAGE1D)) return EXIT_FAILURE;
    //    if (!run_test<unsigned char>({ 6, 2, 1 }, CL_MEM_OBJECT_IMAGE1D)) return EXIT_FAILURE;
    if (!run_test<float> ({ 3, 2, 2 }, CL_MEM_OBJECT_IMAGE1D))
        return EXIT_FAILURE;
    //    if (!run_test<int>({ 3, 2, 2 }, CL_MEM_OBJECT_IMAGE1D)) return EXIT_FAILURE;
    //    if (!run_test<unsigned int>({ 3, 2, 2 }, CL_MEM_OBJECT_IMAGE1D)) return EXIT_FAILURE;
    //    if (!run_test<short>({ 3, 2, 2 }, CL_MEM_OBJECT_IMAGE1D)) return EXIT_FAILURE;
    //    if (!run_test<unsigned short>({ 3, 2, 2 }, CL_MEM_OBJECT_IMAGE1D)) return EXIT_FAILURE;
    //    if (!run_test<char>({ 3, 2, 2 }, CL_MEM_OBJECT_IMAGE1D)) return EXIT_FAILURE;
    //    if (!run_test<unsigned char>({ 3, 2, 2 }, CL_MEM_OBJECT_IMAGE1D)) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}