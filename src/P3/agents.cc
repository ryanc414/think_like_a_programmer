/* Rewrite the code that finds the agent with the best monthly sales average so
 * that it finds the agent with the highest median sales. As stated earlier, the median
 * of a set of values is the one in the middle, such that half of the other values
 * are higher and half of the other values are lower. If there is an even number
 * of values, the median is the simple average of the two values in the middle.
 * For example, in the set 10, 6, 2, 14, 7, 9, the values in the middle are 7 and 9.
 * The average of 7 and 9 is 8, so 8 is the median.
 *
 * Consider this modification of the sales array: Because salespeople come and
 * go throughout the year, we are now marking months prior to a sales agent's
 * hiring, or after a sales agent's last month, with a -1. Rewrite your highest
 * sales average, or highest sales median, code to compensate.
 */
#include <array>
#include <iostream>
#include <algorithm>

constexpr int kNumAgents = 3;
constexpr int kNumMonths = 12;

const std::array<const std::array<int, kNumMonths>, kNumAgents> kSales = {{
    {-1, -1, 30924, 87478, 328, 2653, 387, 3754, 387587, 2873, 276, 32},
    {5865, 5456, 3983, 6464, 9957, 4785, 3875, 3838, 4959, 1122, 7766, -1},
    {-1, 55, 67, 99, 265, 376, 232, 223, 4546, 564, -1, -1}
}};

double CalculateMedian(std::array<int, kNumMonths> sales);

// Calculate the median sales for each agent and output which is the very
// bestest.
int main() {
    double highest_median = -1;
    int bestest_agent = -1;
    int agent_ix = 0;

    for (auto &agent_sales : kSales) {
        double median = CalculateMedian(agent_sales);
        std::cout << "Agent " << agent_ix << " has median sales = " << median
             << std::endl;
        if (median > highest_median) {
            highest_median = median;
            bestest_agent = agent_ix;
        }
        agent_ix++;
    }

    std::cout << "The bestest agent is number: " << bestest_agent
         << " with median sales of " << highest_median << std::endl;

    return 0;
}


// Calculate the median of a single agent's sales.
// An agent's sales may start or end with -1s to signify them having not
// started or left. Take this into account and only find the median of the
// sub-set that is non-negative.
double CalculateMedian(std::array<int, kNumMonths> sales) {
    int start = 0;
    int end = kNumMonths - 1;

    while (sales[start] == -1 && start < kNumMonths) {
        ++start;
    }

    while (sales[end] == -1 && end > 0) {
        --end;
    }

    // If the start and end overlap that must mean there are no valid sales
    // figures, i.e. the array is all -1s. This is not valid data, so raise.
    if (start > end) {
        throw std::runtime_error("No valid sales figures found.");
    }

    const int num_sales = (end + 1) - start;
    const int middle = (num_sales / 2) + start;
    std::sort(sales.begin() + start, sales.begin() + end);

    // If there were any -1s in the middle of the sales values, they will be
    // sorted to the start of our sales. This is invalid data, so raise an
    // exception.
    if (sales[start] == -1) {
        throw std::runtime_error("Only expect -1s at start or end of sales.");
    }

    if (num_sales % 2 == 0) {
        return static_cast<double>(sales[middle - 1] + sales[middle]) / 2.0;
    } else {
        return static_cast<double>(sales[middle]);
    }
}

