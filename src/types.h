#pragma once

#include <concepts>
#include <type_traits>

template <typename T>
concept numeric = std::is_arithmetic_v<T> && !std::same_as<T, bool> &&
                  !std::same_as<T, char> && !std::same_as<T, char16_t> &&
                  !std::same_as<T, char32_t> && !std::same_as<T, wchar_t>;