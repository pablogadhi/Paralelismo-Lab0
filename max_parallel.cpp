#include <vector>
#include <stdlib.h>
#include <iostream>
#include <thread>
#include <future>
#include <time.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

void get_max(vector<int> num_vector, std::promise<int> &&p)
{
    if (num_vector.size() > 2)
    {
        vector<int> part_1, part_2;
        promise<int> result_1, result_2;
        future<int> future_1 = result_1.get_future();
        future<int> future_2 = result_2.get_future();

        part_1 = vector<int>(num_vector.begin(), num_vector.begin() + num_vector.size() / 2);
        part_2 = vector<int>(num_vector.begin() + num_vector.size() / 2, num_vector.end());

        get_max(part_1, move(result_1));
        get_max(part_2, move(result_2));
        p.set_value(max(future_1.get(), future_2.get()));
    }
    else
    {
        p.set_value(max(num_vector[0], num_vector[1]));
    }
}

int main(int argc, char const *argv[])
{
    const int num_cores = 4;

    vector<int> test, results;
    srand(time(NULL));
    for (int i = 0; i < 40; i++)
    {
        test.push_back(rand() % 100);
    }

    // for (int i = 0; i < test.size(); i++)
    // {
    //     cout << test[i] << " ";
    // }
    // cout << endl;

    thread mythreads[num_cores];
    promise<int> promises[num_cores], last_promise;
    future<int> futures[num_cores], last_future;

    auto start_time = high_resolution_clock::now();
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
        results.push_back(futures[n].get());
    }

    last_future = last_promise.get_future();
    get_max(results, move(last_promise));
    auto stop_time = high_resolution_clock::now();

    cout << "Resultado: " << last_future.get() << endl;
    cout << "Duracion: " << duration_cast<microseconds>(stop_time - start_time).count() << endl;

    return 0;
}
