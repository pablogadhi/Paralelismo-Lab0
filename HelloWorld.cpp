// HelloWorld.cpp : This file contains the 'main' function. Program execution begins and ends there.
// It also contains a trivial example of the use of the thread function.

#include <iostream>
#include <thread>
#include <stdlib.h>
#include <future>
#include <vector>

using namespace std;

void my_rank(vector<int> test_vector, std::promise<string> &&p)
{
    // std::cout << "Hola Mundo desde thread " << rango << "\n";
    // std::cout << "---- Waiting ... \n";
    srand(time(NULL));
    for (int i = 0; i < rand() % 5000; i++)
    {
        /* code */
    }
    // cout << rango << endl;
    p.set_value(to_string(test_vector[0]));
}

int main()
{
    const int num_cores = 4;
    thread mythreads[num_cores];
    promise<string> mypromises[num_cores];
    future<string> futures[num_cores];
    vector<int> myvec = {0, 1, 2, 3};
    for (int n = 0; n < num_cores; n++)
    {
        futures[n] = mypromises[n].get_future();
        mythreads[n] = thread(my_rank, myvec, move(mypromises[n]));
    }

    for (int n = 0; n < num_cores; n++)
    {
        mythreads[n].join();
    }

    for (int n = 0; n < num_cores; n++)
    {
        cout << futures[n].get();
    }

    std::cout << "Hello World!\n";
    return 0;
}