rosbuild_find_ros_package(cuda)
set(CUDA_TOOLKIT_ROOT_DIR ${cuda_PACKAGE_PATH}/cuda)
set(CUDA_NVCC_EXECUTABLE  ${cuda_PACKAGE_PATH}/cuda/bin/nvcc)
set(CUDA_INCLUDE_DIRS ${cuda_PACKAGE_PATH}/cuda/include)

rosbuild_include(cuda FindCUDA)

set(CUDA_SDK_ROOT_DIR ${cuda_PACKAGE_PATH}/sdk)

CUDA_INCLUDE_DIRECTORIES(${cuda_PACKAGE_PATH}/sdk/shared/inc ${cuda_PACKAGE_PATH}/sdk/C/common/inc)
LINK_DIRECTORIES(${LINK_DIRECTORIES} ${cuda_PACKAGE_PATH}/sdk/shared/lib ${cuda_PACKAGE_PATH}/sdk/C/lib)

