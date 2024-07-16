/*!	\file		stats.cpp
    \author		Ahmed Ibrahim
    \version	1.0.0
    \date		2024-07-12
    \Compiler   Microsoft Visual Studio C++ compiler (MSVC) version 17.8.4/std:c++20

    A program to take input from eithe the console or the command line and run a simple statsistical analysis on the data
*/

#include "../Stats/stats_utilities.hpp";

int main(int argc, char* argv[])
{
    cout << "stats 1.0.0: (c) 2024, Ahmed Ibrahim\n";

    vector<double> population;
    cout << "Enter a list of whitespace-separated real numbers terminated by ^Z or 'end'\n\n";

    load_data(population, argc, argv);
    if(population.empty())
        cerr << "empty data set!\nquitting... \n";

    cout << "------------------------------------------------------------\n";

    double count = findCount(population);
    double min = findMin(population);
    double max = findMax(population);
    double mean = findMean(population);
    double median = findMedian(population);
    double variance = findVariance(population);
    double sd = findSD(population);

    print_stats_top(count, min, max, mean, median, variance, sd);
    cout << "------------------------------------------------------------\n";

    double_vector modes;
    size_t modeFrequency = mode_frequency(population, modes);
    size_t no_of_modes = modes.size();

    print_mode(modes, modeFrequency, no_of_modes); 
    cout << "------------------------------------------------------------\n";

    double meanAD = findMeanAD(population);
    double medianAD = findMedianAD(population);
    if (modes.size() == 1) {
        double ModeAD = findModeAD(population, modes[0]);
        print_absoulute_devs(meanAD, medianAD, ModeAD);
    }
    else
        print_absoulute_devs (meanAD,  medianAD);
    cout << "------------------------------------------------------------\n";
    
    double slope = findSlope(population);
    double intercept = findIntercept(population);

    print_stats_bottom(slope, intercept);
    cout << "------------------------------------------------------------\n";
    
    double_vector outliers2x = find2xOutliers(population);
    double_vector outliers3x = find3xOutliers(population);
    
    print_outliers(outliers2x, outliers3x);
    
}

