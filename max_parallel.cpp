#include <vector>
#include <stdlib.h>
#include <iterator>
#include <iostream>
#include <time.h>
#include <thread>
#include <future>

using namespace std;

void get_max(vector<int> num_vector, promise<int> &&p)
{
    if (num_vector.size() > 2)
    {
        vector<int> part_1, part2;
        promise<int> result_1, result_2;
        future<int> future_1 = result_1.get_future();
        future<int> future_2 = result_2.get_future();

        get_max(vector<int>(num_vector.begin(), num_vector.begin() + num_vector.size() / 2), move(result_1));
        get_max(vector<int>(num_vector.begin() + num_vector.size() / 2, num_vector.end()), move(result_2));
        p.set_value(max(future_1.get(), future_2.get()));
    }
    else
    {
        p.set_value(max(num_vector[0], num_vector[1]));
    }
}

// template <class T>
// vector<vector<T>> slice_vector(vector<T> original_vector, int parts)
// {
// }

int main(int argc, char const *argv[])
{
    const int num_cores = 4;

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

    thread mythreads[num_cores];
    promise<string> promises[num_cores];
    future<string> futures[num_cores];
    for (int n = 0; n < num_cores; n++)
    {
        vector<int> sliced_vector = vector<int>(test.begin() + n * test.size() / num_cores, test.begin() + (n + 1) * test.size() / num_cores);
        futures[n] = promises[n].get_future();
        mythreads[n] = thread(get_max, sliced_vector, move(promises[n]));
    }

    for (int n = 0; n < num_cores; n++)
    {
        mythreads[n].join();
    }

    for (int n = 0; n < num_cores; n++)
    {
        cout << futures[n].get();
    }

    return 0;
}
