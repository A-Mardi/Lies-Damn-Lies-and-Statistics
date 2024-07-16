#pragma once
/*!	\file		stats_utilities.hpp
    \author		Ahmed Ibrahim
    \version	1.0.0
    \date		2024-07-12
    \Compiler       Microsoft Visual Studio C++ compiler (MSVC) version 17.8.4/std:c++20

    Utilities and functions to support statistical analysis in the stats.exe program.
*/

//Imported Libraries
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iomanip>
using namespace std;

//Types
using double_vector = std::vector<double>;

//Functions
bool isNumber(const string& str);

void load_data(double_vector& population, int argc, char* argv[]);

inline double findCount(double_vector vec) {
	return vec.size();
}
inline double findMax(double_vector vec) {
    return *std::max_element(vec.begin(), vec.end());
}
inline double findMin(double_vector vec) {
    return *std::min_element(vec.begin(), vec.end());
}

double findMax(double_vector);

double findRange(double_vector);

double findMean(double_vector);

double findMedian(double_vector);

double findVariance(double_vector);

double findSD(double_vector);

double findMeanAD(double_vector);

double findMedianAD(double_vector);

double findModeAD(double_vector vec, double mode);

vector<double>find2xOutliers(double_vector);

vector<double>find3xOutliers(double_vector vec);

double findSlope(double_vector);

double findIntercept(double_vector vec);

vector<double>merge(double_vector vec1, double_vector vec2);

vector<double>mergeSort(double_vector vec);

void ai_sort(double_vector& vec);

size_t mode_frequency(std::vector<double>& v, std::vector<double>& modes);

void print_stats_top(double count, double min, double max, double mean, double median, double variance, double sd);

void print_mode(double_vector modes, size_t modeFrequency, size_t no_of_modes);

void print_absoulute_devs(double meanAD, double medianAD, double ModeAD);
void print_absoulute_devs(double meanAD, double medianAD);

void print_stats_bottom(double slope, double intercept);

void print_outliers(double_vector outliers2x, double_vector outliers3x);
