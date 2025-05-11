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

	/**
		* @brief Checks if one vector is less than or equal to another.
		* @param vec1 The first vector (left-hand side).
		* @param vec2 The second vector (right-hand side).
		* @return True if vec1 <= vec2 for all elements, false otherwise.
		*/
	bool LTE(const std::vector<int>& vec1, const std::vector<int>& vec2) const;

	/**
	 * @brief Determines if the system is in a safe state and provides the safe sequence.
	 * @param allocation The current allocation matrix.
	 * @param available The current available vector.
	 * @param need The current need matrix.
	 * @return A vector containing the safe sequence if the system is safe, or an empty vector if not.
	 */
	std::vector<int> safe(const std::vector<std::vector<int>>& allocation,
		const std::vector<int>& available,
		const std::vector<std::vector<int>>& need) const;

public:

	/**
	 * @brief Constructor to initialize the system state.
	 * @param threads The number of threads in the system (n).
	 * @param resources The number of resource types in the system (m).
	 */
	SystemState(const int threads, const int resources);

	/**
	 * @brief Inputs the initial state of the system from the user.
	 */
	void inputState();

	/**
	 * @brief Checks if the system is in a safe state and prints the result.
	 */
	void isSafeState() const;

	/**
	 * @brief Handles a resource request from a thread.
	 * @param request The resource request vector.
	 * @param Ti The thread index making the request.
	 */
	void resourceRequest(const std::vector<int>& request, const int Ti);

	/**
	 * @brief Handles the release of resources by a thread.
	 * @param release The resource release vector.
	 * @param Ti The thread index releasing the resources.
	 */
	void releaseResources(const std::vector<int>& release, const int Ti);

	/**
	 * @brief Displays the current state of the system, including all matrices and vectors.
	 */
	void displayState() const;

	/**
	 * @brief Interactive menu for user operations on the system.
	 */
	void menu();

};

#endif // BANKER_H