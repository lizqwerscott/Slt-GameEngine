#ifndef UTILS_H
#define UTILS_H

#include <cstddef>
#include <cstdint>

uintptr_t user_data_convert(uintptr_t pointer, size_t index);
void user_data_set(uintptr_t pointer, size_t index, uintptr_t data);

#endif
