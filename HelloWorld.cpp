// HelloWorld.cpp : This file contains the 'main' function. Program execution begins and ends there.
// It also contains a trivial example of the use of the thread function.

#include <iostream>
#include <thread>
#include <stdlib.h>
#include <future>

using namespace std;

void my_rank(int rango, std::promise<string> &&p)
{
    // std::cout << "Hola Mundo desde thread " << rango << "\n";
    // std::cout << "---- Waiting ... \n";
    srand(time(NULL));
    for (int i = 0; i < rand() % 5000; i++)
    {
        /* code */
    }
    cout << rango << endl;
    p.set_value(to_string(rango));
}

int main()
{
    const int num_cores = 4;
    thread mythreads[num_cores];
    promise<string> mypromises[num_cores];
    future<string> futures[num_cores];
    for (int n = 0; n < num_cores; n++)
    {
        futures[n] = mypromises[n].get_future();
        mythreads[n] = thread(my_rank, n, move(mypromises[n]));
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