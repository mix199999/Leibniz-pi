#include <iostream>
#include <thread>
#include <chrono>
#include<vector>
#include <iomanip>
#include <string>
using namespace std;



double calculateLeibniz(int start, int end, double& result);

int main()
{


    //vector of threads
    vector<thread> t;

    //length of The Gregory-Leibniz Series
    int iterations = 1000000000;


    // number of threads
    int numberOfThreads;

    //number of operations per thread
    vector<int> threadOperations;


    // result of calculations for single Thread calculating
    double result = 0;

    // result of calculations for multiple Threads calculating
    double resultMultiThreads = 0;
   
   

    

    while (true)
    {
        cout << "Maximum number of threads: " << thread::hardware_concurrency() << endl;
        cout << "Insert below number of threads:" << endl;
        //sending value from input stream to the variable
        cin >> numberOfThreads;
        if (numberOfThreads > thread::hardware_concurrency())
        {
            printf("Value is too big\n");
        }
        else
        {
            break;
        }


    }


    //temporary variable storing the result of iterations % numberOfThreads
    int temp = iterations % numberOfThreads;




    //distribution of tasks between threads if result of (iterations % numberOfThreads) not equal 0
    if (temp != 0)
    {
        iterations -= temp;

        //counting the number of operations per thread
        for (size_t i = 0; i < numberOfThreads; i++)
        {
            threadOperations.push_back(iterations / numberOfThreads);


        }


        threadOperations[numberOfThreads - 1] = (iterations / numberOfThreads) + temp;




        for (size_t i = 0; i < numberOfThreads; i++)
        {

            if (i == 0)
            {
                t.push_back(thread(calculateLeibniz, 0, threadOperations[i], ref(resultMultiThreads)));

            }

            else
            {
                int temV = threadOperations[i - 1];
                t.push_back(thread(calculateLeibniz, temV + temV, threadOperations[i], ref(resultMultiThreads)));

            }


        }



        auto begin = chrono::high_resolution_clock::now();

        for (size_t i = 0; i < numberOfThreads; i++)
        {
            if (t[i].joinable())
                t[i].join();
            else
                printf("Cannot join thread Nr: %d\n", i);
        }


        auto end = chrono::high_resolution_clock::now();

        //counting 
        chrono::duration<double, milli> elapsed = end - begin;
        cout << "---Results for multiple threads calculation---" << endl;
        cout << setprecision(4) << "Computing time " << elapsed.count() / 1000 << "s" << endl;
        cout << setprecision(11) << "Calculated PI value: " << 4 * resultMultiThreads << endl;
        cout << "-----------------------------------------" << endl;

    }

    else
    {


        for (int i = 0; i < numberOfThreads; i++)
        {
            threadOperations.push_back(iterations / numberOfThreads);



        }
        for (int i = 0; i < numberOfThreads; i++)
        {

            if (i == 0)
            {
                t.push_back(thread(calculateLeibniz, 0, threadOperations[i], ref(resultMultiThreads)));

            }

            else
            {
                int temV = threadOperations[i - 1];
                t.push_back(thread(calculateLeibniz, temV + temV, threadOperations[i], ref(resultMultiThreads)));

            }
        }
        auto begin = chrono::high_resolution_clock::now();

        for (size_t i = 0; i < numberOfThreads; i++)
        {
            if (t[i].joinable())
                t[i].join();
            else
                printf("Cannot join thread Nr: %d\n", i);
        }


        auto end = chrono::high_resolution_clock::now();


        chrono::duration<double, milli> elapsedMultiThreads = end - begin;
        cout << "---Results for multiple threads calculation---" << endl;
        cout << setprecision(4) << "Computing time " << elapsedMultiThreads.count() / 1000 << "s" << endl;
        cout << setprecision(11) << "Calculated PI value: " << 4 * resultMultiThreads << endl;
        cout << "-----------------------------------------" << endl;

    }

    //single thread section begin
    iterations = 1000000000;

    auto begin2 = chrono::high_resolution_clock::now();


    calculateLeibniz(result, iterations, result);


    auto end2 = chrono::high_resolution_clock::now();



    chrono::duration<double, milli> elapsedSingleThread = end2 - begin2;

    cout << "---Results for single thread calculation---" << endl;
    cout << setprecision(4) << "Computing time " << elapsedSingleThread.count() / 1000 << "s" << endl;
    cout << setprecision(11) << "Calculated PI value: " << 4 * result << endl;
    cout << "-----------------------------------------" << endl;

    //single thread section end
    system("pause");
    return 0;
}

/// <summary>
///Function returns sum of sub-rank of The Gregory-Leibniz Series
/// </summary>
/// <param name="start"> first index of the sequence of numbers</param>
/// <param name="end">last index of the sequence of numbers</param>
/// <param name="result">sum of the sub-rank</param>
double calculateLeibniz(int start, int end, double& result)
{
    double sum = 0;
    double diff = 0;

    for (size_t i = start; i < end; i++)
    {

        if (i % 4 == 1)
        {
            sum += (1.0 / i);
        }
        else if (i % 4 == 3)
        {
            diff -= (1.0 / i);
        }
    }
    return result += sum + diff;
}
