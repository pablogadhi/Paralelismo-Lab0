// HelloWorld.cpp : This file contains the 'main' function. Program execution begins and ends there.
// It also contains a trivial example of the use of the thread function.

#include <iostream>
#include "pthread.h"
#include <stdlib.h>
#include <vector>

using namespace std;

class Data
{
    vector<int> myvector;
    int result;

public:
    Data();
    Data(vector<int>, int);
    void set_result(int);
    int get_result();
    vector<int> get_vector();
};

Data::Data(vector<int> a, int b)
{
    myvector = a;
    result = b;
}

Data::Data()
{
    myvector = vector<int>();
}

void Data::set_result(int a)
{
    result = a;
}

int Data::get_result()
{
    return result;
}

vector<int> Data::get_vector()
{
    return myvector;
}

void *my_rank(void *data)
{
    // std::cout << "Hola Mundo desde thread " << rango << "\n";
    // std::cout << "---- Waiting ... \n";
    srand(time(NULL));
    for (int i = 0; i < rand() % 5000; i++)
    {
        /* code */
    }
    // cout << rango << endl;
    Data* casted_data = (Data *)data;
    (*casted_data).set_result((*casted_data).get_vector()[(*casted_data).get_result()]);
    pthread_exit(NULL);
}

int main()
{
    const int num_cores = 4;
    pthread_t mythreads[num_cores];
    // promise<string> mypromises[num_cores];
    // future<string> futures[num_cores];
    vector<int> myvec = {5, 4, 3, 2};
    Data datas[num_cores];
    for (int n = 0; n < num_cores; n++)
    {
        datas[n] = Data(myvec, n);
        pthread_create(&mythreads[n], NULL, my_rank, (void *)&datas[n]);
    }

    for (int n = 0; n < num_cores; n++)
    {
        pthread_join(mythreads[n], NULL);
    }

    for (int n = 0; n < num_cores; n++)
    {
        cout << datas[n].get_result() << endl;
    }

    pthread_exit(NULL);

    return 0;
}