#include "Vector.hpp"
#include <iostream>
#include <string>

int main()
{
    try
    {
        std::cout << "--- 1. Testing Initializer List & Iterators ---" << std::endl;
        Vector<std::string> words = {"Apple", "Banana", "Cherry", "Date"};
        words.push_back("Elderberry");

        // Testing range-based for loop (requires begin/end iterators)
        for (const auto &word : words)
        {
            std::cout << word << " ";
        }
        std::cout << "\nSize: " << words.size() << " | Capacity: " << words.capacity() << std::endl;

        std::cout << "\n--- 2. Testing Move Semantics (The 'Efficient' part) ---" << std::endl;

        Vector<std::string> movedWords = std::move(words);

        std::cout << "Moved words count: " << movedWords.size() << std::endl;
        std::cout << "Original words count (should be 0): " << words.size() << std::endl;

        std::cout << "\n--- 3. Testing 2D Vector (Vector of Vectors) ---" << std::endl;
        Vector<Vector<int>> matrix;
        matrix.push_back({1, 2, 3});
        matrix.push_back({4, 5, 6});
        matrix.push_back({7, 8, 9});

        std::cout << "Matrix [1][1] value: " << matrix.at(1).at(1) << std::endl; // Should be 5

        std::cout << "\n--- 4. Testing Erase & Insert (Iterators) ---" << std::endl;
        Vector<int> nums = {10, 20, 30, 40, 50};
        auto it = nums.begin() + 2; // Pointing to 30

        nums.erase(it);      // Erase 30
        nums.insert(100, 0); // Insert 100 at the front

        std::cout << "Modified Nums: " << nums; // Uses your friend operator<<

        std::cout << "\n--- 5. Testing Exception Safety ---" << std::endl;
        // This should trigger your out_of_range exception
        std::cout << "Trying to access index 100..." << std::endl;
        std::cout << nums.at(100) << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "EXCEPTION CAUGHT: " << e.what() << std::endl;
    }

    return 0;
}