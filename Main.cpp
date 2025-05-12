#include "banker.h"

int main() {

        int n, m;
        std::cout << "Enter the number of threads in the system: ";
        std::cin >> n;
        std::cout << "Enter the number of resource types in the system: ";
        std::cin >> m;

        SystemState system(n, m);
        system.inputState();
        system.menu();

        return 0;
    

}