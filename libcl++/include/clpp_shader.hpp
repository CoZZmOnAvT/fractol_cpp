/*
 * This file is part of LibCL++.

 * LibCL++ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LibCL++ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LibCL++. If not, see <https://www.gnu.org/licenses/>.
 *
 * Author: Pavlo Hrytsenko
*/

#ifndef LIBCLPP_INCLUDE_CLPP_SHADER_HPP_
#define LIBCLPP_INCLUDE_CLPP_SHADER_HPP_

#include <map>
#include <string>
#include <vector>

#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

namespace cozz {

namespace clpp {

class ClppCore;

class ClppShader final {
  public:
    ClppShader(const ClppCore& cl_core, const std::vector<std::string>& source_paths);
    ~ClppShader();

    void Build(const std::string& build_options = "");

    void BuildFor(cl_device_type device_type, const std::string& build_options = "");

    template <class... Args>
    void Calculate(const std::string& function, void* buffer, uint64_t buffer_size, std::vector<size_t> work_size,
                   const Args&... args);

  private:
    const ClppCore& cl_core_;

    cl_device_type device_build_for_;

    cl_program cl_program_;

    std::map<const std::string, cl_kernel> cl_kernels_;

    std::pair<cl_mem, uint64_t> device_memory_region_;

    void ReallocateDeviceMemoryRegion(uint64_t size);

    cl_kernel GetKernel(const std::string& name);

    template <class ParameterType>
    void SetKernelArgument(cl_kernel kernel, uint32_t n, const ParameterType& parameter);

    template <class ParameterType, class... Args>
    void SetKernelArgument(cl_kernel kernel, uint32_t n, const ParameterType& parameter, const Args&... args);
};

}  // namespace clpp

}  // namespace cozz

#include "clpp_shader.tpp"

#endif  // LIBCLPP_INCLUDE_CLPP_SHADER_HPP_
