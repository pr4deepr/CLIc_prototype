#ifndef __CORE_CLEBACKEND_HPP
#define __CORE_CLEBACKEND_HPP

#include "cleTypes.hpp"
#include "clic.hpp"

#include <iostream>

namespace cle::Backend
{

inline auto
GetNumberOfPlatforms() -> size_t
{
  cl_int  err = CL_SUCCESS;
  cl_uint ret_num_platforms = 0;
  err = clGetPlatformIDs(0, nullptr, &ret_num_platforms);
  if (err != CL_SUCCESS)
  {
    std::cerr << "Backend error in GetNumberOfPlatforms : " << GetOpenCLErrorInfo(err) << std::endl;
  }
  return ret_num_platforms;
}

inline auto
GetPlatformPointer(const size_t & platform_index) -> cl::Platform
{
  cl_int         err = CL_SUCCESS;
  cl_platform_id platform = nullptr;
  err = clGetPlatformIDs(platform_index, &platform, nullptr);
  if (err != CL_SUCCESS)
  {
    std::cerr << "Backend error in GetPlatformPointer : " << GetOpenCLErrorInfo(err) << std::endl;
  }
  return cl::Platform(platform, true);
}

inline auto
GetPlatformPointerList() -> std::vector<cl::Platform>
{
  cl_int                    err = CL_SUCCESS;
  std::vector<cl::Platform> platform_list = {};
  err = cl::Platform::get(&platform_list);
  if (err != CL_SUCCESS)
  {
    std::cerr << "Backend error in GetPlatformPointerList : " << GetOpenCLErrorInfo(err) << std::endl;
  }
  return platform_list;
}

inline auto
GetPlatformName(const cl::Platform & platform_pointer) -> std::string
{
  return platform_pointer.getInfo<CL_PLATFORM_NAME>();
}

inline auto
GetDevicesListFromPlatform(const cl::Platform & platform_pointer, const DeviceType & device_type)
  -> std::vector<cl::Device>
{
  cl_int                  err = CL_SUCCESS;
  std::vector<cl::Device> device_list;
  err = platform_pointer.getDevices(device_type, &device_list);
  if (err != CL_SUCCESS)
  {
    std::cerr << "Backend error in GetDevicesListFromPlatform : " << GetOpenCLErrorInfo(err) << std::endl;
  }
  return device_list;
}

inline auto
GetDevicesListFromPlatform(const cl::Platform & platform_pointer) -> std::vector<cl::Device>
{
  cl_int                  err = CL_SUCCESS;
  std::vector<cl::Device> device_list;
  err = platform_pointer.getDevices(CL_DEVICE_TYPE_ALL, &device_list);
  if (err != CL_SUCCESS)
  {
    std::cerr << "Backend error in GetDevicesListFromPlatform : " << GetOpenCLErrorInfo(err) << std::endl;
  }
  return device_list;
}

inline auto
GetDeviceName(const cl::Device & device_pointer) -> std::string
{
  return device_pointer.getInfo<CL_DEVICE_NAME>();
}

inline auto
GetDeviceType(const cl::Device & device_pointer) -> DeviceType
{
  cl_device_type type = device_pointer.getInfo<CL_DEVICE_TYPE>();
  return static_cast<DeviceType>(type);
}

inline auto
GetDeviceVersion(const cl::Device & device_pointer) -> std::string
{
  return device_pointer.getInfo<CL_DEVICE_VERSION>();
}

inline auto
DeviceIsAvailable(const cl::Device & device_pointer) -> bool
{
  return device_pointer.getInfo<CL_DEVICE_AVAILABLE>() == CL_TRUE;
}

inline auto
GetDeviceExtensions(const cl::Device & device_pointer) -> std::string
{
  return device_pointer.getInfo<CL_DEVICE_EXTENSIONS>();
}

inline auto
ImageSupport(const cl::Device & device_pointer) -> bool
{
  return device_pointer.getInfo<CL_DEVICE_IMAGE_SUPPORT>() == CL_TRUE;
}

inline auto
GetContextPointer(const cl::Device & device_pointer) -> cl::Context
{
  cl_int      err = CL_SUCCESS;
  cl::Context context(device_pointer, nullptr, nullptr, nullptr, &err);
  if (err != CL_SUCCESS)
  {
    std::cerr << "Backend error in GetContextPointer : " << GetOpenCLErrorInfo(err) << std::endl;
  }
  return context;
}

inline auto
GetContextPointer(const std::vector<cl::Device> & device_pointer_list) -> cl::Context
{
  cl_int      err = CL_SUCCESS;
  cl::Context context(device_pointer_list, nullptr, nullptr, nullptr, &err);
  if (err != CL_SUCCESS)
  {
    std::cerr << "Backend error in GetContextPointer : " << GetOpenCLErrorInfo(err) << std::endl;
  }
  return context;
}

inline auto
GetQueuePointer(const cl::Device & device_pointer, const cl::Context & context_pointer, const bool & in_order)
  -> cl::CommandQueue
{
  cl_command_queue_properties props = 0;
  if (!in_order)
  {
    props = CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE;
  }
  cl_int           err = CL_SUCCESS;
  cl::CommandQueue queue(context_pointer, device_pointer, props, &err);
  if (err != CL_SUCCESS)
  {
    std::cerr << "Backend error in GetQueuePointer : " << GetOpenCLErrorInfo(err) << std::endl;
  }
  return queue;
}

inline auto
GetBufferPointer(const cl::Context &       context_pointer,
                 const MemAllocationType & memory_alloc_mode,
                 const HostAccessType &    host_access_type,
                 const KernelAccessType &  kernel_access_type,
                 const size_t              size_in_bytes) -> cl::Memory
{
  cl_int           err = CL_SUCCESS;
  cl_mem_flags     flags = memory_alloc_mode | host_access_type | kernel_access_type;
  const cl::Buffer memory(context_pointer, flags, size_in_bytes, nullptr, &err);
  if (err != CL_SUCCESS)
  {
    std::cerr << "Backend error in GetBufferPointer: " << GetOpenCLErrorInfo(err) << std::endl;
  }
  return cl::Memory(memory.get(), true);
}

inline auto
GetImagePointer(const cl::Context &           context_pointer,
                const MemAllocationType &     memory_alloc_mode,
                const HostAccessType &        host_access_type,
                const KernelAccessType &      kernel_access_type,
                const ChannelType &           image_channel_order,
                const DataType &              image_channel_datatype,
                const std::array<size_t, 3> & shape) -> cl::Memory
{
  cl_int          err = CL_SUCCESS;
  cl_mem_flags    flags = memory_alloc_mode | host_access_type | kernel_access_type;
  cl::ImageFormat image_format;
  image_format.image_channel_order = image_channel_order;
  image_format.image_channel_data_type = image_channel_datatype;
  if (shape[2] > 1)
  {
    const cl::Image3D memory(context_pointer, flags, image_format, shape[0], shape[1], shape[2], 0, 0, nullptr, &err);
    if (err != CL_SUCCESS)
    {
      std::cerr << "Backend error in GetImagePointer 3D: " << GetOpenCLErrorInfo(err) << std::endl;
    }
    return cl::Memory(memory.get(), true);
  }
  if (shape[1] > 1)
  {
    const cl::Image2D memory(context_pointer, flags, image_format, shape[0], shape[1], 0, nullptr, &err);
    if (err != CL_SUCCESS)
    {
      std::cerr << "Backend error in GetImagePointer 2D: " << GetOpenCLErrorInfo(err) << std::endl;
    }
    return cl::Memory(memory.get(), true);
  }

  const cl::Image1D memory(context_pointer, flags, image_format, shape[0], nullptr, &err);
  if (err != CL_SUCCESS)
  {
    std::cerr << "Backend error in GetImagePointer 1D: " << GetOpenCLErrorInfo(err) << std::endl;
  }
  return cl::Memory(memory.get(), true);
}

inline auto
GetObjectType(const cl::Memory & obj) -> cl_mem_object_type
{
  return obj.getInfo<CL_MEM_TYPE>();
}

inline auto
GetProgramPointer(const cl::Context & context_pointer, const std::string & source_code) -> cl::Program
{
  cl_int      err = CL_SUCCESS;
  cl::Program program(context_pointer, source_code, false, &err);
  if (err != CL_SUCCESS)
  {
    std::cerr << "Backend error in GetProgramPointer : " << GetOpenCLErrorInfo(err) << std::endl;
  }
  return program;
}

inline auto
BuildProgram(const cl::Program &             program_pointer,
             const std::vector<cl::Device> & device_pointer,
             const std::string &             options = "") -> bool
{
  cl_int err = program_pointer.build(device_pointer, options.c_str());
  if (err != CL_SUCCESS)
  {
    std::cerr << "Backend error in BuildProgram : " << GetOpenCLErrorInfo(err) << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

inline auto
BuildProgram(const cl::Program & program_pointer, const cl::Device & device_pointer, const std::string & options = "")
  -> bool
{
  cl_int err = program_pointer.build(device_pointer, options.c_str());
  if (err != CL_SUCCESS)
  {
    std::cerr << "Backend error in BuildProgram : " << GetOpenCLErrorInfo(err) << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

inline auto
GetBuildStatus(const cl::Device & device_pointer, const cl::Program & program_pointer) -> BuildStatus
{
  cl_build_status status = program_pointer.getBuildInfo<CL_PROGRAM_BUILD_STATUS>(device_pointer);
  return static_cast<BuildStatus>(status);
}

inline auto
GetBuildLog(const cl::Device & device_pointer, const cl::Program & program_pointer) -> std::string
{
  return program_pointer.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device_pointer);
}

inline auto
GetKernelPointer(const cl::Program & program_pointer, const std::string & kernel_name) -> cl::Kernel
{
  cl_int     err = CL_SUCCESS;
  cl::Kernel kernel(program_pointer, kernel_name.c_str(), &err);
  if (err != CL_SUCCESS)
  {
    std::cerr << "Backend error in GetKernelPointer : " << GetOpenCLErrorInfo(err) << std::endl;
  }
  return kernel;
}

inline auto
SetKernelArgument(cl::Kernel * kernel_pointer, const int & arg_index, const cl::Memory & memory_pointer) -> void
{
  cl_int err = kernel_pointer->setArg(arg_index, memory_pointer);
  if (err != CL_SUCCESS)
  {
    std::cerr << "Backend error in SetKernelArgument : " << GetOpenCLErrorInfo(err) << std::endl;
  }
}

inline auto
SetKernelArgument(cl::Kernel * kernel_pointer, const int & arg_index, float scalar) -> void
{
  cl_int err = kernel_pointer->setArg(arg_index, scalar);
  if (err != CL_SUCCESS)
  {
    std::cerr << "Backend error in SetKernelArgument : " << GetOpenCLErrorInfo(err) << std::endl;
  }
}

inline auto
SetKernelArgument(cl::Kernel * kernel_pointer, const int & arg_index, int scalar) -> void
{
  cl_int err = kernel_pointer->setArg(arg_index, scalar);
  if (err != CL_SUCCESS)
  {
    std::cerr << "Backend error in SetKernelArgument : " << GetOpenCLErrorInfo(err) << std::endl;
  }
}

inline auto
GetNumberOfKernelArguments(const cl::Kernel & kernel_pointer) -> size_t
{
  return kernel_pointer.getInfo<CL_KERNEL_NUM_ARGS>();
}

inline auto
GetKernelArgumentName(const cl::Kernel & kernel_pointer, const int & index) -> std::string
{
  return kernel_pointer.getArgInfo<CL_KERNEL_ARG_NAME>(index);
}

inline auto
GetKernelArgumentType(const cl::Kernel & kernel_pointer, const int & index) -> std::string
{
  return kernel_pointer.getArgInfo<CL_KERNEL_ARG_TYPE_NAME>(index);
}

inline auto
WaitQueueToFinish(const cl::CommandQueue & queue_pointer) -> void
{
  cl_int err = queue_pointer.finish();
  if (err != CL_SUCCESS)
  {
    std::cerr << "Backend error in : " << GetOpenCLErrorInfo(err) << std::endl;
  }
}

inline auto
EnqueueKernelExecution(const cl::CommandQueue &      queue_pointer,
                       const cl::Kernel &            kernel_pointer,
                       const std::array<size_t, 3> & global_size) -> void
{
  cl::NDRange global(global_size[0], global_size[1], global_size[2]);
  cl_int      err = CL_SUCCESS;
  err = queue_pointer.enqueueNDRangeKernel(kernel_pointer, cl::NullRange, global, cl::NullRange);
  if (err != CL_SUCCESS)
  {
    std::cerr << "Backend error in : " << GetOpenCLErrorInfo(err) << std::endl;
  }
}

inline auto
EnqueueReadFromBuffer(const cl::CommandQueue & queue_pointer,
                      const cl::Memory &       buffer_pointer,
                      const bool &             block_flag,
                      const size_t &           offset,
                      const size_t &           length_in_bytes,
                      void *                   host_pointer) -> void
{
  const cl::Buffer memory(buffer_pointer.get(), true);
  cl_int           err = queue_pointer.enqueueReadBuffer(
    memory, static_cast<cl_bool>(block_flag), offset, length_in_bytes, host_pointer, nullptr, nullptr);
  if (err != CL_SUCCESS)
  {
    std::cerr << "Backend error in EnqueueReadFromBuffer: " << GetOpenCLErrorInfo(err) << std::endl;
  }
}

inline auto
EnqueueWriteToBuffer(const cl::CommandQueue & queue_pointer,
                     const cl::Memory &       buffer_pointer,
                     const bool &             block_flag,
                     const size_t &           offset,
                     const size_t &           length_in_bytes,
                     const void *             host_memory_pointer) -> void
{
  const cl::Buffer memory(buffer_pointer.get(), true);
  cl_int           err = queue_pointer.enqueueWriteBuffer(
    memory, static_cast<cl_bool>(block_flag), offset, length_in_bytes, host_memory_pointer, nullptr, nullptr);
  if (err != CL_SUCCESS)
  {
    std::cerr << "Backend error in EnqueueWriteToBuffer: " << GetOpenCLErrorInfo(err) << std::endl;
  }
}

inline auto
EnqueueReadFromBufferRegion(const cl::CommandQueue &      queue_pointer,
                            const cl::Memory &            buffer_pointer,
                            const bool &                  block_flag,
                            const std::array<size_t, 3> & buffer_origin,
                            const std::array<size_t, 3> & host_origin,
                            const std::array<size_t, 3> & region,
                            void *                        host_memory_pointer) -> void
{
  // cl_int err = CL_SUCCESS;
  // err = clEnqueueReadBufferRect(queue_pointer.get(), buffer_pointer.get(), block_flag, buffer_origin, host_origin,
  // region, 0, 0, 0, 0, host_memory_pointer, 0, nullptr, nullptr); if(err != CL_SUCCESS) { std::cerr << "Backend error
  // in : " << GetOpenCLErrorInfo(err) << std::endl;}
}

inline auto
EnqueueWriteToBufferRegion(const cl::CommandQueue &      queue_pointer,
                           const cl::Memory &            buffer_pointer,
                           const bool &                  block_flag,
                           const std::array<size_t, 3> & buffer_origin,
                           const std::array<size_t, 3> & host_origin,
                           const std::array<size_t, 3> & region,
                           void *                        host_memory_pointer) -> void
{
  // cl_int err = CL_SUCCESS;
  // err = clEnqueueWriteBufferRect(queue_pointer.get(), buffer_pointer.get(), block_flag, buffer_origin, host_origin,
  // region, 0, 0, 0, 0, host_memory_pointer, 0, nullptr, nullptr); if(err != CL_SUCCESS) { std::cerr << "Backend error
  // in : " << GetOpenCLErrorInfo(err) << std::endl;}
}

template <class NativeType>
inline auto
EnqueueFillBuffer(const cl::CommandQueue & queue_pointer,
                  const cl::Memory &       buffer_pointer,
                  const bool &             block_flag,
                  const size_t &           offset,
                  const size_t &           length_in_bytes,
                  const NativeType &       pattern) -> void
{
  const cl::Buffer memory(buffer_pointer.get(), true);
  cl_int           err = queue_pointer.enqueueFillBuffer(memory, pattern, offset, length_in_bytes, nullptr, nullptr);
  if (err != CL_SUCCESS)
  {
    std::cerr << "Backend error in EnqueueFillBuffer : " << GetOpenCLErrorInfo(err) << std::endl;
  }
  if (block_flag)
  {
    WaitQueueToFinish(queue_pointer);
  }
}

inline auto
EnqueueCopyBuffer(const cl::CommandQueue & queue_pointer,
                  const cl::Memory &       src_buffer_pointer,
                  const cl::Memory &       dst_buffer_pointer,
                  const bool &             block_flag,
                  const size_t &           src_offset,
                  size_t                   dst_offset,
                  const size_t &           length_in_bytes) -> void
{
  const cl::Buffer src_memory(src_buffer_pointer.get(), true);
  const cl::Buffer dst_memory(dst_buffer_pointer.get(), true);
  cl_int           err =
    queue_pointer.enqueueCopyBuffer(src_memory, dst_memory, src_offset, dst_offset, length_in_bytes, nullptr, nullptr);
  if (err != CL_SUCCESS)
  {
    std::cerr << "Backend error in EnqueueCopyBuffer : " << GetOpenCLErrorInfo(err) << std::endl;
  }
  if (block_flag)
  {
    WaitQueueToFinish(queue_pointer);
  }
}

inline auto
EnqueueCopyBufferRegion(const cl::CommandQueue &      queue_pointer,
                        const cl::Memory &            src_buffer_pointer,
                        const cl::Memory &            dst_buffer_pointer,
                        const bool &                  block_flag,
                        const std::array<size_t, 3> & src_origin,
                        const std::array<size_t, 3> & dst_origin,
                        const std::array<size_t, 3> & region) -> void
{
  // cl_int err = CL_SUCCESS;
  // err = clEnqueueCopyBufferRect(queue_pointer.get(), src_buffer_pointer.get(), dst_buffer_pointer.get(), src_origin,
  // dst_origin, region, 0, 0, 0, 0, 0, nullptr, nullptr); if(err != CL_SUCCESS) { std::cerr << "Backend error in : " <<
  // GetOpenCLErrorInfo(err) << std::endl;} if(block_flag) { WaitQueueToFinish(queue_pointer); }
}

inline auto
EnqueueCopyBufferToImage(const cl::CommandQueue &      queue_pointer,
                         const cl::Memory &            src_buffer_pointer,
                         const cl::Memory &            dst_image_pointer,
                         const bool &                  block_flag,
                         const size_t &                src_offset,
                         const std::array<size_t, 3> & dst_origin,
                         const std::array<size_t, 3> & dst_region) -> void
{
  cl_int           err = CL_SUCCESS;
  const cl::Buffer src_memory(src_buffer_pointer.get(), true);
  switch (dst_image_pointer.getInfo<CL_MEM_TYPE>())
  {
    case CL_MEM_OBJECT_IMAGE1D: {
      const cl::Image1D dst_memory(dst_image_pointer.get(), true);
      err = queue_pointer.enqueueCopyBufferToImage(
        src_memory, dst_memory, src_offset, dst_origin, dst_region, nullptr, nullptr);
      break;
    }
    case CL_MEM_OBJECT_IMAGE2D: {
      const cl::Image2D dst_memory(dst_image_pointer.get(), true);
      err = queue_pointer.enqueueCopyBufferToImage(
        src_memory, dst_memory, src_offset, dst_origin, dst_region, nullptr, nullptr);
      break;
    }
    case CL_MEM_OBJECT_IMAGE3D: {
      const cl::Image3D dst_memory(dst_image_pointer.get(), true);
      err = queue_pointer.enqueueCopyBufferToImage(
        src_memory, dst_memory, src_offset, dst_origin, dst_region, nullptr, nullptr);
      break;
    }
  }
  if (err != CL_SUCCESS)
  {
    std::cerr << "Backend error in EnqueueCopyBufferToImage : " << GetOpenCLErrorInfo(err) << std::endl;
  }
  if (block_flag)
  {
    WaitQueueToFinish(queue_pointer);
  }
}

inline auto
EnqueueCopyImageToBuffer(const cl::CommandQueue &      queue_pointer,
                         const cl::Memory &            src_image_pointer,
                         const cl::Memory &            dst_buffer_pointer,
                         const bool &                  block_flag,
                         const std::array<size_t, 3> & src_origin,
                         const std::array<size_t, 3> & src_region,
                         size_t                        dst_offset) -> void
{
  cl_int           err = CL_SUCCESS;
  const cl::Buffer dst_memory(dst_buffer_pointer.get(), true);
  switch (src_image_pointer.getInfo<CL_MEM_TYPE>())
  {
    case CL_MEM_OBJECT_IMAGE1D: {
      const cl::Image1D src_memory(src_image_pointer.get(), true);
      err = queue_pointer.enqueueCopyImageToBuffer(
        src_memory, dst_memory, src_origin, src_region, dst_offset, nullptr, nullptr);
      break;
    }
    case CL_MEM_OBJECT_IMAGE2D: {
      const cl::Image2D src_memory(src_image_pointer.get(), true);
      err = queue_pointer.enqueueCopyImageToBuffer(
        src_memory, dst_memory, src_origin, src_region, dst_offset, nullptr, nullptr);
      break;
    }
    case CL_MEM_OBJECT_IMAGE3D: {
      const cl::Image3D src_memory(src_image_pointer.get(), true);
      err = queue_pointer.enqueueCopyImageToBuffer(
        src_memory, dst_memory, src_origin, src_region, dst_offset, nullptr, nullptr);
      break;
    }
  }
  if (err != CL_SUCCESS)
  {
    std::cerr << "Backend error in EnqueueCopyImageToBuffer : " << GetOpenCLErrorInfo(err) << std::endl;
  }
  if (block_flag)
  {
    WaitQueueToFinish(queue_pointer);
  }
}

inline auto
EnqueueReadFromImage(const cl::CommandQueue &      queue_pointer,
                     const cl::Memory &            image_pointer,
                     const bool &                  block_flag,
                     const std::array<size_t, 3> & origin,
                     const std::array<size_t, 3> & region,
                     void *                        host_memory_pointer) -> void
{
  cl_int err = CL_SUCCESS;
  switch (image_pointer.getInfo<CL_MEM_TYPE>())
  {
    case CL_MEM_OBJECT_IMAGE1D: {
      const cl::Image1D memory(image_pointer.get(), true);
      err = queue_pointer.enqueueReadImage(
        memory, static_cast<cl_bool>(block_flag), origin, region, 0, 0, host_memory_pointer, nullptr, nullptr);
      break;
    }
    case CL_MEM_OBJECT_IMAGE2D: {
      const cl::Image2D memory(image_pointer.get(), true);
      err = queue_pointer.enqueueReadImage(
        memory, static_cast<cl_bool>(block_flag), origin, region, 0, 0, host_memory_pointer, nullptr, nullptr);
      break;
    }
    case CL_MEM_OBJECT_IMAGE3D: {
      const cl::Image3D memory(image_pointer.get(), true);
      err = queue_pointer.enqueueReadImage(
        memory, static_cast<cl_bool>(block_flag), origin, region, 0, 0, host_memory_pointer, nullptr, nullptr);
      break;
    }
  }
  if (err != CL_SUCCESS)
  {
    std::cerr << "Backend error in EnqueueReadFromImage : " << GetOpenCLErrorInfo(err) << std::endl;
  }
}

inline auto
EnqueueWriteToImage(const cl::CommandQueue &      queue_pointer,
                    const cl::Memory &            image_pointer,
                    const bool &                  block_flag,
                    const std::array<size_t, 3> & origin,
                    const std::array<size_t, 3> & region,
                    const void *                  host_memory_pointer) -> void
{
  cl_int err = CL_SUCCESS;
  switch (image_pointer.getInfo<CL_MEM_TYPE>())
  {
    case CL_MEM_OBJECT_IMAGE1D: {
      const cl::Image1D memory(image_pointer.get(), true);
      err = queue_pointer.enqueueWriteImage(
        memory, static_cast<cl_bool>(block_flag), origin, region, 0, 0, host_memory_pointer, nullptr, nullptr);
      break;
    }
    case CL_MEM_OBJECT_IMAGE2D: {
      const cl::Image2D memory(image_pointer.get(), true);
      err = queue_pointer.enqueueWriteImage(
        memory, static_cast<cl_bool>(block_flag), origin, region, 0, 0, host_memory_pointer, nullptr, nullptr);
      break;
    }
    case CL_MEM_OBJECT_IMAGE3D: {
      const cl::Image3D memory(image_pointer.get(), true);
      err = queue_pointer.enqueueWriteImage(
        memory, static_cast<cl_bool>(block_flag), origin, region, 0, 0, host_memory_pointer, nullptr, nullptr);
      break;
    }
  }
  if (err != CL_SUCCESS)
  {
    std::cerr << "Backend error in EnqueueWriteToImage : " << GetOpenCLErrorInfo(err) << std::endl;
  }
}

template <class NativeType>
inline auto
EnqueueFillImage(const cl::CommandQueue &      queue_pointer,
                 const cl::Memory &            image_pointer,
                 const bool &                  block_flag,
                 const std::array<size_t, 3> & origin,
                 const std::array<size_t, 3> & region,
                 const NativeType &            pattern) -> void
{
  cl_int err = CL_SUCCESS;
  switch (image_pointer.getInfo<CL_MEM_TYPE>())
  {
    case CL_MEM_OBJECT_IMAGE1D: {
      const cl::Image1D memory(image_pointer.get(), true);
      err = queue_pointer.enqueueFillImage(memory, pattern, origin, region, nullptr, nullptr);
      break;
    }
    case CL_MEM_OBJECT_IMAGE2D: {
      const cl::Image2D memory(image_pointer.get(), true);
      err = queue_pointer.enqueueFillImage(memory, pattern, origin, region, nullptr, nullptr);
      break;
    }
    case CL_MEM_OBJECT_IMAGE3D: {
      const cl::Image3D memory(image_pointer.get(), true);
      err = queue_pointer.enqueueFillImage(memory, pattern, origin, region, nullptr, nullptr);
      break;
    }
  }
  if (err != CL_SUCCESS)
  {
    std::cerr << "Backend error in EnqueueFillImage : " << GetOpenCLErrorInfo(err) << std::endl;
  }
  if (block_flag)
  {
    WaitQueueToFinish(queue_pointer);
  }
}

inline auto
EnqueueCopyImage(const cl::CommandQueue &      queue_pointer,
                 const cl::Memory &            src_image_pointer,
                 const cl::Memory &            dst_image_pointer,
                 const bool &                  block_flag,
                 const std::array<size_t, 3> & src_origin,
                 const std::array<size_t, 3> & dst_origin,
                 const std::array<size_t, 3> & region) -> void
{
  cl_int err = CL_SUCCESS;
  switch (src_image_pointer.getInfo<CL_MEM_TYPE>())
  {
    case CL_MEM_OBJECT_IMAGE1D: {
      const cl::Image1D src_memory(src_image_pointer.get(), true);
      const cl::Image1D dst_memory(dst_image_pointer.get(), true);
      err = queue_pointer.enqueueCopyImage(src_memory, dst_memory, src_origin, dst_origin, region, nullptr, nullptr);
      break;
    }
    case CL_MEM_OBJECT_IMAGE2D: {
      const cl::Image2D src_memory(src_image_pointer.get(), true);
      const cl::Image2D dst_memory(dst_image_pointer.get(), true);
      err = queue_pointer.enqueueCopyImage(src_memory, dst_memory, src_origin, dst_origin, region, nullptr, nullptr);
      break;
    }
    case CL_MEM_OBJECT_IMAGE3D: {
      const cl::Image3D src_memory(src_image_pointer.get(), true);
      const cl::Image3D dst_memory(dst_image_pointer.get(), true);
      err = queue_pointer.enqueueCopyImage(src_memory, dst_memory, src_origin, dst_origin, region, nullptr, nullptr);
      break;
    }
  }
  if (err != CL_SUCCESS)
  {
    std::cerr << "Backend error in EnqueueCopyImage : " << GetOpenCLErrorInfo(err) << std::endl;
  }
  if (block_flag)
  {
    WaitQueueToFinish(queue_pointer);
  }
}

} // namespace cle::Backend

#endif // __CORE_CLEBACKEND_HPP
