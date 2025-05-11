#include "banker.h"
#include <cassert> // For assert function

using namespace std;


/**
 * @brief Constructor to initialize the system state.
 * @param threads The number of threads in the system (n).
 * @param resources The number of resource types in the system (m).
 */
SystemState::SystemState(const int threads, const int resources) : n(threads), m(resources) {}

/**
 * @brief Checks if one vector is less than or equal to another.
 * @param vec1 The first vector (left-hand side).
 * @param vec2 The second vector (right-hand side).
 * @return True if vec1 <= vec2 for all elements, false otherwise.
 */
bool SystemState::LTE(const vector<int>& vec1, const vector<int>& vec2) const {
    assert(vec1.size() == vec2.size()); // Ensure vectors are of the same size
    for (size_t i = 0; i < vec1.size(); i++) {
        if (vec1[i] > vec2[i]) {
            return false;
        }
    }
    return true;
}




