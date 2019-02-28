/* Write a program that is given an array of integers and determines the mode,
 * which is the number that appears most frequently in the array.
 */
#include <iostream>
#include <vector>
#include <map>

std::vector<int> get_input();
std::vector<int> find_modes(const std::vector<int> &vec);

int main() {
    const std::vector<int> input = get_input();
    const std::vector<int> modes = find_modes(input);

    if (modes.size() > 0) {
        std::cout << "Mode(s) of input = " << modes.front();
        for (auto mode = modes.begin() + 1; mode < modes.end(); ++mode) {
            std::cout << ", " << *mode;
        }
        std::cout << std::endl;
    } else {
        std::cout << "Input has no mode." << std::endl;
    }

    return 0;
}

// Get a vector of input from the user.
std::vector<int> get_input() {
    std::vector<int> input;
    int num_inputs;

    std::cout << "How many elements do you want to enter?" << std::endl
              << "> ";
    std::cin >> num_inputs;
    if (num_inputs < 1) {
        throw std::range_error("Number of elements must be > 0.");
    }
    input.reserve(num_inputs);

    for (int i = 0; i < num_inputs; ++i) {
        std::cout << "Enter element " << i + 1 << " / " << num_inputs
                  << std::endl << "> ";

        int next_input;
        std::cin >> next_input;
        input.push_back(next_input);
    }

    return input;
}

// Find the modal value(s) of a vector of ints. There may be multiple modes
// if multiple values appear equally frequently, or there may be no mode
// if every value appears with equal frequency.
std::vector<int> find_modes(const std::vector<int> &input) {
    std::map<int, int> counts;

    // Count the number of occurences of each value.
    for (int val : input) {
        counts[val]++;
    }

    // Iterate through the counts to find the modal values. If there are
    // multiple values with the same mode we want to return all of them.
    std::vector<int> curr_modes;
    curr_modes.reserve(input.size());
    int max_count = 0;

    for (auto &pair : counts) {
        if (pair.second > max_count) {
            max_count = pair.second;
            curr_modes.clear();
            curr_modes.push_back(pair.first);
        } else if (pair.second == max_count) {
            curr_modes.push_back(pair.first);
        }
    }

    // If all values in the input are modal, then we consider there to be
    // no mode.
    if ((curr_modes.size() * max_count) == input.size()) {
        curr_modes.clear();
    }

    return curr_modes;
}

