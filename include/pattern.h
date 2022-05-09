#ifndef PATTERN_H
#define PATTERN_H

#include <string>

const int PATTERN_NUM = 9;
const std::string PATTERN_NAME[] = {
    "fresh\t\t",     "static\t\t", "stride\t\t", "pointer\t\t", "pointer_chase",
    "pointer_array", "indirect\t", "chain\t\t",  "other\t\t"};
enum PATTERN : uint16_t {
  FRESH,
  STATIC,
  STRIDE,
  pointer,
  POINTER_A,
  POINTER_B,
  INDIRECT,
  CHAIN,
  OTHER
};

static std::unordered_map<std::string, PATTERN> const pattern_table = {
    {"fresh", PATTERN::FRESH},
    {"static", PATTERN::STATIC},
    {"stride", PATTERN::STRIDE},
    {"pointer", PATTERN::pointer},
    {"pointer_chase", PATTERN::POINTER_A},
    {"pointer_array", PATTERN::POINTER_B},
    {"indirect", PATTERN::INDIRECT},
    {"chain", PATTERN::CHAIN},
    {"other", PATTERN::OTHER}};

template <typename E>
constexpr auto to_underlying(E e) noexcept {
  return static_cast<std::underlying_type_t<E>>(e);
}

const uint32_t INTERVAL = 128;
const uint16_t STRIDE_THERSHOLD = 32;
const uint16_t POINTER_A_THERSHOLD = 32;
const uint16_t INDIRECT_THERSHOLD = 32;
const uint16_t PATTERN_THERSHOLD = 32;
const uint16_t POINTER_THERSHOLD = 32;
const uint16_t CHAIN_THERSHOLD = 32;
const uint16_t STATIC_THERSHOLD = 256;

#endif