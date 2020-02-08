#include <vector>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

int get_max(vector<int> num_vector)
{
    if (num_vector.size() > 2)
    {
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
    for (int i = 0; i < 10000; i++)
    {
        test.push_back(rand() % 50000);
    }

    // for (int i = 0; i < test.size(); i++)
    // {
    //     cout << test[i] << " ";
    // }
    // cout << endl;

    auto start_time = high_resolution_clock::now();
    int result = get_max(test);
    auto stop_time = high_resolution_clock::now();

    cout << "Resultado: " << result << endl;
    cout << "Duracion: " << duration_cast<microseconds>(stop_time - start_time).count() << endl;
    return 0;
}
