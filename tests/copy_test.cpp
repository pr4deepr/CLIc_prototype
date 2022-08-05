
#include <random>

#include "clesperanto.hpp"

template <class type>
auto
run_test (const std::array<size_t, 3> &shape, const cl_mem_object_type &mem_type) -> bool
{
    std::vector<type> input (shape[0] * shape[1] * shape[2]);
    std::vector<type> valid (shape[0] * shape[1] * shape[2]);
    std::fill (input.begin (), input.end (), static_cast<type> (10));
    std::fill (valid.begin (), valid.end (), static_cast<type> (10));

    cle::Clesperanto cle;
    cle.GetDevice ()->WaitForKernelToFinish ();
    auto gpu_input = cle.Push<type> (input, shape, mem_type);
    auto gpu_output = cle.Create<type> (shape, mem_type);
    cle.Copy (gpu_input, gpu_output);
    auto output = cle.Pull<type> (gpu_output);

    return std::equal (output.begin (), output.end (), valid.begin ());
}

auto
main (int argc, char **argv) -> int
{
    if (!run_test<float> ({ 5, 1, 1 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<int> ({ 5, 1, 1 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<unsigned int> ({ 5, 1, 1 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<short> ({ 5, 1, 1 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<unsigned short> ({ 5, 1, 1 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<char> ({ 5, 1, 1 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<unsigned char> ({ 5, 1, 1 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<float> ({ 5, 3, 1 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<int> ({ 5, 3, 1 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<unsigned int> ({ 5, 3, 1 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<short> ({ 5, 3, 1 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<unsigned short> ({ 5, 3, 1 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<char> ({ 5, 3, 1 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<unsigned char> ({ 5, 3, 1 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<float> ({ 5, 3, 2 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<int> ({ 5, 3, 2 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<unsigned int> ({ 5, 3, 2 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<short> ({ 5, 3, 2 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<unsigned short> ({ 5, 3, 2 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<char> ({ 5, 3, 2 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<unsigned char> ({ 5, 3, 2 }, CL_MEM_OBJECT_BUFFER))
        return EXIT_FAILURE;
    if (!run_test<float> ({ 5, 1, 1 }, CL_MEM_OBJECT_IMAGE1D))
        return EXIT_FAILURE;
    //    if (!run_test<int>({ 5, 1, 1 }, CL_MEM_OBJECT_IMAGE1D)) return EXIT_FAILURE;
    //    if (!run_test<unsigned int>({ 5, 1, 1 }, CL_MEM_OBJECT_IMAGE1D)) return EXIT_FAILURE;
    //    if (!run_test<short>({ 5, 1, 1 }, CL_MEM_OBJECT_IMAGE1D)) return EXIT_FAILURE;
    //    if (!run_test<unsigned short>({ 5, 1, 1 }, CL_MEM_OBJECT_IMAGE1D)) return EXIT_FAILURE;
    //    if (!run_test<char>({ 5, 1, 1 }, CL_MEM_OBJECT_IMAGE1D)) return EXIT_FAILURE;
    //    if (!run_test<unsigned char>({ 5, 1, 1 }, CL_MEM_OBJECT_IMAGE1D)) return EXIT_FAILURE;
    if (!run_test<float> ({ 5, 3, 1 }, CL_MEM_OBJECT_IMAGE1D))
        return EXIT_FAILURE;
    //    if (!run_test<int>({ 5, 3, 1 }, CL_MEM_OBJECT_IMAGE1D)) return EXIT_FAILURE;
    //    if (!run_test<unsigned int>({ 5, 3, 1 }, CL_MEM_OBJECT_IMAGE1D)) return EXIT_FAILURE;
    //    if (!run_test<short>({ 5, 3, 1 }, CL_MEM_OBJECT_IMAGE1D)) return EXIT_FAILURE;
    //    if (!run_test<unsigned short>({ 5, 3, 1 }, CL_MEM_OBJECT_IMAGE1D)) return EXIT_FAILURE;
    //    if (!run_test<char>({ 5, 3, 1 }, CL_MEM_OBJECT_IMAGE1D)) return EXIT_FAILURE;
    //    if (!run_test<unsigned char>({ 5, 3, 1 }, CL_MEM_OBJECT_IMAGE1D)) return EXIT_FAILURE;
    if (!run_test<float> ({ 5, 3, 2 }, CL_MEM_OBJECT_IMAGE1D))
        return EXIT_FAILURE;
    //    if (!run_test<int>({ 5, 3, 2 }, CL_MEM_OBJECT_IMAGE1D)) return EXIT_FAILURE;
    //    if (!run_test<unsigned int>({ 5, 3, 2 }, CL_MEM_OBJECT_IMAGE1D)) return EXIT_FAILURE;
    //    if (!run_test<short>({ 5, 3, 2 }, CL_MEM_OBJECT_IMAGE1D)) return EXIT_FAILURE;
    //    if (!run_test<unsigned short>({ 5, 3, 2 }, CL_MEM_OBJECT_IMAGE1D)) return EXIT_FAILURE;
    //    if (!run_test<char>({ 5, 3, 2 }, CL_MEM_OBJECT_IMAGE1D)) return EXIT_FAILURE;
    //    if (!run_test<unsigned char>({ 5, 3, 2 }, CL_MEM_OBJECT_IMAGE1D)) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}