/* Rewrite the code that finds the agent with the best monthly sales average so
 * that it finds the agent with the highest median sales. As stated earlier, the median
 * of a set of values is the “one in the middle,” such that half of the other values
 * are higher and half of the other values are lower. If there is an even number
 * of values, the median is the simple average of the two values in the middle.
 * For example, in the set 10, 6, 2, 14, 7, 9, the values in the middle are 7 and 9.
 * The average of 7 and 9 is 8, so 8 is the median.
 */
#include <array>
#include <iostream>
#include <algorithm>
#include <cassert>

using std::array;
using std::cout;
using std::endl;
using std::sort;

const int NUM_AGENTS = 3;
const int NUM_MONTHS = 12;

const array<const array<int, NUM_MONTHS>, NUM_AGENTS> SALES = {{
    {1856, 498, 30924, 87478, 328, 2653, 387, 3754, 387587, 2873, 276, 32},
    {5865, 5456, 3983, 6464, 9957, 4785, 3875, 3838, 4959, 1122, 7766, 2534},
    {23, 55, 67, 99, 265, 376, 232, 223, 4546, 564, 4544, 3434}
}};

double calculate_median(array<int, NUM_MONTHS> sales);

// Calculate the median sales for each agent and output which is the very
// bestest.
int main()
{
    double highest_median = -1;
    double median;
    int bestest_agent = -1;
    int agent_ix = 0;

    for (auto &agent_sales : SALES) {
        median = calculate_median(agent_sales);
        cout << "Agent " << agent_ix << " has median sales = " << median
             << endl;
        if (median > highest_median) {
            highest_median = median;
            bestest_agent = agent_ix;
        }
        agent_ix++;
    }

    cout << "The bestest agent is number: " << bestest_agent
         << " with median sales of " << highest_median << endl;

    return 0;
}


// Calculate the median of a single agent's sales.
double calculate_median(array<int, NUM_MONTHS> sales)
{
    const int middle = NUM_MONTHS / 2;

    assert(middle * 2 == NUM_MONTHS);
    sort(sales.begin(), sales.end());

    return (double)(sales[middle - 1] + sales[middle]) / 2.0;
}

