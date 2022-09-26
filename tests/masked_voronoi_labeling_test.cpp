

#include <random>

#include "clesperanto.hpp"

template <class type>
auto
run_test(const std::array<size_t, 3> & shape, const cle::ObjectType & mem_type) -> bool
{
  std::vector<type> input1(shape[0] * shape[1] * shape[2]);
  std::vector<type> input2(shape[0] * shape[1] * shape[2]);
  std::vector<type> valid(shape[0] * shape[1] * shape[2]);
  if (shape[2] > 1)
  {
    input1 = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
    input2 = { 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1 };
    valid = { 1, 1, 1, 1, 0, 2, 1, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
              0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 4, 3, 3, 3, 0, 4, 4 };
  }
  else if (shape[1] > 1)
  {
    input1 = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
    input2 = { 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1 };
    valid = { 1, 1, 1, 1, 0, 2, 0, 0, 0, 0, 0, 0, 3, 3, 3, 0, 4, 4 };
  }
  else
  {
    input1 = { 1, 0, 0, 0, 0, 1 };
    input2 = { 1, 1, 1, 1, 0, 1 };
    valid = { 1, 1, 1, 1, 0, 2 };
  }

  cle::Clesperanto cle;
  cle.GetDevice()->WaitForKernelToFinish();
  auto gpu_input1 = cle.Push<type>(input1, shape, mem_type);
  auto gpu_input2 = cle.Push<type>(input2, shape, mem_type);
  auto gpu_output = cle.Create<type>(shape, mem_type);
  cle.MaskedVoronoiLabeling(gpu_input1, gpu_input2, gpu_output);
  auto output = cle.Pull<type>(gpu_output);

  return std::equal(output.begin(), output.end(), valid.begin());
}

auto
main(int argc, char ** argv) -> int
{
  if (!run_test<float>({ 6, 1, 1 }, cle::BUFFER))
    return EXIT_FAILURE;
  if (!run_test<int>({ 6, 1, 1 }, cle::BUFFER))
    return EXIT_FAILURE;
  if (!run_test<unsigned int>({ 6, 1, 1 }, cle::BUFFER))
    return EXIT_FAILURE;
  if (!run_test<short>({ 6, 1, 1 }, cle::BUFFER))
    return EXIT_FAILURE;
  if (!run_test<unsigned short>({ 6, 1, 1 }, cle::BUFFER))
    return EXIT_FAILURE;
  if (!run_test<char>({ 6, 1, 1 }, cle::BUFFER))
    return EXIT_FAILURE;
  if (!run_test<unsigned char>({ 6, 1, 1 }, cle::BUFFER))
    return EXIT_FAILURE;
  if (!run_test<float>({ 6, 3, 1 }, cle::BUFFER))
    return EXIT_FAILURE;
  if (!run_test<int>({ 6, 3, 1 }, cle::BUFFER))
    return EXIT_FAILURE;
  if (!run_test<unsigned int>({ 6, 3, 1 }, cle::BUFFER))
    return EXIT_FAILURE;
  if (!run_test<short>({ 6, 3, 1 }, cle::BUFFER))
    return EXIT_FAILURE;
  if (!run_test<unsigned short>({ 6, 3, 1 }, cle::BUFFER))
    return EXIT_FAILURE;
  if (!run_test<char>({ 6, 3, 1 }, cle::BUFFER))
    return EXIT_FAILURE;
  if (!run_test<unsigned char>({ 6, 3, 1 }, cle::BUFFER))
    return EXIT_FAILURE;
  if (!run_test<float>({ 6, 4, 2 }, cle::BUFFER))
    return EXIT_FAILURE;
  if (!run_test<int>({ 6, 4, 2 }, cle::BUFFER))
    return EXIT_FAILURE;
  if (!run_test<unsigned int>({ 6, 4, 2 }, cle::BUFFER))
    return EXIT_FAILURE;
  if (!run_test<short>({ 6, 4, 2 }, cle::BUFFER))
    return EXIT_FAILURE;
  if (!run_test<unsigned short>({ 6, 4, 2 }, cle::BUFFER))
    return EXIT_FAILURE;
  if (!run_test<char>({ 6, 4, 2 }, cle::BUFFER))
    return EXIT_FAILURE;
  if (!run_test<unsigned char>({ 6, 4, 2 }, cle::BUFFER))
    return EXIT_FAILURE;
  if (!run_test<float>({ 6, 1, 1 }, cle::IMAGE))
    return EXIT_FAILURE;
  //    if (!run_test<int>({ 6, 1, 1 }, cle::IMAGE)) return EXIT_FAILURE;
  //    if (!run_test<unsigned int>({ 6, 1, 1 }, cle::IMAGE)) return EXIT_FAILURE;
  //    if (!run_test<short>({ 6, 1, 1 }, cle::IMAGE)) return EXIT_FAILURE;
  //    if (!run_test<unsigned short>({ 6, 1, 1 }, cle::IMAGE)) return EXIT_FAILURE;
  //    if (!run_test<char>({ 6, 1, 1 }, cle::IMAGE)) return EXIT_FAILURE;
  //    if (!run_test<unsigned char>({ 6, 1, 1 }, cle::IMAGE)) return EXIT_FAILURE;
  if (!run_test<float>({ 6, 3, 1 }, cle::IMAGE))
    return EXIT_FAILURE;
  //    if (!run_test<int>({ 6, 3, 1 }, cle::IMAGE)) return EXIT_FAILURE;
  //    if (!run_test<unsigned int>({ 6, 3, 1 }, cle::IMAGE)) return EXIT_FAILURE;
  //    if (!run_test<short>({ 6, 3, 1 }, cle::IMAGE)) return EXIT_FAILURE;
  //    if (!run_test<unsigned short>({ 6, 3, 1 }, cle::IMAGE)) return EXIT_FAILURE;
  //    if (!run_test<char>({ 6, 3, 1 }, cle::IMAGE)) return EXIT_FAILURE;
  //    if (!run_test<unsigned char>({ 6, 3, 1 }, cle::IMAGE)) return EXIT_FAILURE;
  if (!run_test<float>({ 6, 4, 2 }, cle::IMAGE))
    return EXIT_FAILURE;
  //    if (!run_test<int>({ 6, 4, 2 }, cle::IMAGE)) return EXIT_FAILURE;
  //    if (!run_test<unsigned int>({ 6, 4, 2 }, cle::IMAGE)) return EXIT_FAILURE;
  //    if (!run_test<short>({ 6, 4, 2 }, cle::IMAGE)) return EXIT_FAILURE;
  //    if (!run_test<unsigned short>({ 6, 4, 2 }, cle::IMAGE)) return EXIT_FAILURE;
  //    if (!run_test<char>({ 6, 4, 2 }, cle::IMAGE)) return EXIT_FAILURE;
  //    if (!run_test<unsigned char>({ 6, 4, 2 }, cle::IMAGE)) return EXIT_FAILURE;
  return EXIT_SUCCESS;
}