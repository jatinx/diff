#include <hip/hip_runtime.h>
#include <hip/hip_bf16.h>

#include <logger.hpp>

__global__ void bfloat_add(__hip_bfloat16 *a, __hip_bfloat16 *b,
                           __hip_bfloat16 *c) {
  *c = __hadd(*a, *b);
}

std::string bfloat162string(__hip_bfloat16 a) {
  std::string s = std::to_string(__bfloat162float(a));
  return s;
}

int main() {
  __hip_bfloat16 *d_a, *d_b, *d_c, a, b, c;
  hipMalloc(&d_a, sizeof(__hip_bfloat16));
  hipMalloc(&d_b, sizeof(__hip_bfloat16));
  hipMalloc(&d_c, sizeof(__hip_bfloat16));

  constexpr size_t size = 1024;
  for (size_t i = 0; i < size; i++) {
    a = __float2bfloat16(i + 1.5f);
    b = __float2bfloat16(i + 2.5f);

    hipMemcpy(d_a, &a, sizeof(__hip_bfloat16), hipMemcpyHostToDevice);
    hipMemcpy(d_b, &b, sizeof(__hip_bfloat16), hipMemcpyHostToDevice);

    bfloat_add<<<1, 1>>>(d_a, d_b, d_c);

    hipMemcpy(&c, d_c, sizeof(__hip_bfloat16), hipMemcpyDeviceToHost);

    log("Adding:", bfloat162string(a), "+", bfloat162string(b), "=",
        bfloat162string(c));
  }

  hipFree(d_a);
  hipFree(d_b);
  hipFree(d_c);
}