#include <vector>
#include <stdlib.h>
#include <iterator>
#include <iostream>
#include <time.h>

using namespace std;

int get_max(vector<int> num_vector)
{
    if (num_vector.size() > 2)
    {
        vector<int> part_1, part2;
        int result_1, result_2;

        result_1 = get_max(vector<int>(num_vector.begin(), num_vector.begin() + num_vector.size() / 2));
        result_2 = get_max(vector<int>(num_vector.begin() + num_vector.size() / 2, num_vector.end()));
        return max(result_1, result_2);
    }
    else
    {
        return max(num_vector[0], num_vector[1]);
    }
}

int main(int argc, char const *argv[])
{
    vector<int> test;
    srand(time(NULL));
    for (int i = 0; i < 10; i++)
    {
        test.push_back(rand() % 50);
    }

    for (int i; i < test.size(); i++)
    {
        cout << test[i] << " ";
    }
    cout << endl;
    cout << get_max(test) << endl;
    return 0;
}
