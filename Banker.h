#ifndef BANKER_H
#define BANKER_H

#include <iostream>  // For input/output operations
#include <vector>    // For std::vector
#include <cassert>   // For assert

/**
 * @class SystemState
 * @brief Represents the state of the system for implementing the Banker's Algorithm.
 */
class SystemState {
   private:
       int n; ///< Number of threads in the system
       int m; ///< Number of resource types in the system
       std::vector<int> available; ///< Vector representing available resources
       std::vector<std::vector<int>> MAX; ///< Maximum demand matrix
       std::vector<std::vector<int>> allocation; ///< Allocation matrix
       std::vector<std::vector<int>> need; ///< Need matrix (MAX - Allocation)

};

#endif // BANKER_H