#include <vector>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include "pthread.h"

using namespace std;
using namespace std::chrono;

class Data
{
    vector<int> num_vector;
    int result;
    int depth;

public:
    Data();
    Data(vector<int>, int, int);
    void set_result(int);
    int get_result();
    vector<int> get_vector();
    int get_depth();
};

Data::Data(vector<int> a, int b, int c)
{
    num_vector = a;
    result = b;
    depth = c;
}

Data::Data()
{
    num_vector = vector<int>();
    result = -1;
    depth = 0;
}

void Data::set_result(int a)
{
    result = a;
}

int Data::get_result()
{
    return result;
}

int Data::get_depth()
{
    return depth;
}

vector<int> Data::get_vector()
{
    return num_vector;
}

void *get_max(void *data)
{
    Data *data_p = (Data *)data;
    vector<int> num_vector = (*data_p).get_vector();
    if (num_vector.size() > 2)
    {
        vector<int> part_1, part_2;
        Data data_1, data_2;

        part_1 = vector<int>(num_vector.begin(), num_vector.begin() + num_vector.size() / 2);
        part_2 = vector<int>(num_vector.begin() + num_vector.size() / 2, num_vector.end());

        data_1 = Data(part_1, -1, (*data_p).get_depth() + 1);
        data_2 = Data(part_2, -1, (*data_p).get_depth() + 1);

        get_max((void *)&data_1);
        get_max((void *)&data_2);

        int max_val = max(data_1.get_result(), data_2.get_result());
        (*data_p).set_result(max_val);
    }
    else
    {
        (*data_p).set_result(max(num_vector[0], num_vector[1]));
    }

    return (void *)0;
}

int main(int argc, char const *argv[])
{
    const int num_cores = 4;

    vector<int> test, results;
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

    pthread_t threads[num_cores];
    Data data[num_cores], last_result;

    for (int n = 0; n < num_cores; n++)
    {
        vector<int> vector_slice = vector<int>(test.begin() + n * test.size() / num_cores, test.begin() + (n + 1) * test.size() / num_cores);
        data[n] = Data(vector_slice, -1, 0);
    }

    auto start_time = high_resolution_clock::now();
    for (int n = 0; n < num_cores; n++)
    {
        pthread_create(&threads[n], NULL, get_max, (void *)&data[n]);
    }

    for (int n = 0; n < num_cores; n++)
    {
        pthread_join(threads[n], NULL);
    }

    for (int n = 0; n < num_cores; n++)
    {
        results.push_back(data[n].get_result());
    }

    last_result = Data(results, -1, 0);
    get_max((void *)&last_result);
    auto stop_time = high_resolution_clock::now();

    std::cout << "Resultado: " << last_result.get_result() << endl;
    std::cout << "Duracion: " << duration_cast<microseconds>(stop_time - start_time).count() << endl;

    pthread_exit(NULL);

    return 0;
}
