#include "constants.h"

namespace math {
// init random
std::random_device rd;
std::mt19937 rng(rd());
std::uniform_int_distribution<int> uni(0, 100000007);

int getRand() {
    return uni(rng);
}
}  // namespace math
