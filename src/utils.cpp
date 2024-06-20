#include "utils.h"
#include <cstdint>

uintptr_t user_data_convert(uintptr_t pointer, size_t index)
{
    if (pointer == 0) {
        return 0;
    } else {
        return reinterpret_cast<uintptr_t *>(pointer)[index];
    }
}

void user_data_set(uintptr_t pointer, size_t index, uintptr_t data)
{
    reinterpret_cast<uintptr_t *>(pointer)[index] = data;
}
