/*!	\file		stats_utilities.cpp
    \author		Ahmed Ibrahim
    \version	1.0.0
    \date		2024-07-12
    \Compiler       Microsoft Visual Studio C++ compiler (MSVC) version 17.8.4/std:c++20

    Utilities and functions to support statistical analysis in the stats.exe program.
*/


#include "../Stats/stats_utilities.hpp";
#include <iomanip>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

/** Check if a string represents a number.
 *  \param str The string to check.
 *  \return True if the string is a number, false otherwise.
 */
bool isNumber(const string& str) {
    // Check if the string is a number
    for (char const& c : str) {
        if (std::isdigit(c) == 0 && c != '.' && c != '-') {
            return false;
        }
    }
    return true;
}

/** Load data from input sources into a vector of doubles.
 *  Handles input from command line or file specified by argc and argv.
 *  \param population Reference to a vector where data will be stored.
 *  \param argc Number of arguments passed to the program.
 *  \param argv Array of arguments passed to the program.
 */
void load_data(double_vector& population, int argc, char* argv[]) {
    if (argc == 1 || argc > 2)
    {
        string input;
        while (!cin.eof()) {
            cin >> input;
            if (input == "end" || cin.eof())
                break;
            if (isNumber(input)) {
                double num_input = stod(input);
                population.push_back(num_input);
            }
        }
    }  
    else if (argc == 2)
    {
        ifstream infile;
        infile.open(argv[1]);
        if (!infile)
        {
            cerr <<"The system cannot find the file specified.\n" << argv[1];
            exit(EXIT_FAILURE);
        }
        
        std::string file_input;
        while (infile >> file_input) {
            infile >> file_input;
            if (file_input == "end" || infile.eof())
                break;
            double num_input = std::stod(file_input);
            population.push_back(num_input);
        }
        infile.close(); 
    }
}

/** Calculate the mean of a vector of doubles.
 *  \param vec Vector of doubles.
 *  \return Mean of the vector.
 */
double findMean(double_vector vec) {

    double mean = accumulate(vec.begin(), vec.end(), 0.0) / vec.size();
    return mean;
}

/** Calculate the median of a vector of doubles.
 *  \param vec Vector of doubles.
 *  \return Median of the vector.
 */
double findMedian(double_vector vec) {

    sort(vec.begin(), vec.end());
    int size = vec.size();
    if (size % 2 == 0)
        return (vec[size / 2] + vec[(size / 2) - 1]) / 2.0;
    else
        return vec[(size) / 2];
}

/** Calculate the variance of a vector of doubles.
 *  \param vec Vector of doubles.
 *  \return Variance of the vector.
 */
double findVariance(double_vector vec) {

    double variance{ 0 };
    double mean = findMean(vec);
    for (size_t i = 0; i < vec.size(); i++) {
        variance += (vec[i] - mean) * (vec[i] - mean);
    }
    variance /= vec.size();
    return variance;
}

/** Calculate the standard deviation of a vector of doubles.
 *  \param vec Vector of doubles.
 *  \return Standard deviation of the vector.
 */
double findSD(double_vector vec) {
    double variance = findVariance(vec);
    return sqrt(variance);
}

/** Calculate the mean absolute deviation about the mean of a vector of doubles.
 *  \param vec Vector of doubles.
 *  \return Mean absolute deviation about the mean.
 */
double findMeanAD(double_vector vec) {
    double mean_ad{ 0 };
    double mean = findMean(vec);
    for (size_t i = 0; i < vec.size(); i++) {
        mean_ad += abs((vec[i] - mean));
    }
    mean_ad /= vec.size();
    return mean_ad;
}

/** Calculate the mean absolute deviation about the median of a vector of doubles.
 *  \param vec Vector of doubles.
 *  \return Mean absolute deviation about the median.
 */
double findMedianAD(double_vector vec) {
    double median_ad{ 0 };
    double median = findMedian(vec);
    for (size_t i = 0; i < vec.size(); i++) {
        median_ad += abs((vec[i] - median));
    }
    median_ad /= vec.size();
    return median_ad;

}

/** Calculate the mean absolute deviation about a single mode of a vector of doubles.
 *  \param vec Vector of doubles.
 *  \param mode Mode value for which deviation is calculated.
 *  \return Mean absolute deviation about the specified mode.
 */
double findModeAD(double_vector vec, double mode) {
    double mode_ad{ 0 };
    for (size_t i = 0; i < vec.size(); i++) {
        mode_ad += abs((vec[i] - mode));
    }
    mode_ad /= vec.size();
    return mode_ad;
}

/** Find outliers in a vector of doubles based on 2 times the standard deviation.
 *  \param vec Vector of doubles.
 *  \return Vector of outliers.
 */
vector<double>find2xOutliers(double_vector vec) {
    double mean = findMean(vec);
    double std_dev = findSD(vec);
    vector<double>outliers;
    for (size_t i = 0; i < vec.size(); i++) {
        if (abs(vec[i] - mean) > 2 * std_dev)
            outliers.push_back(vec[i]);
    }
    return outliers;
}

/** Find outliers in a vector of doubles based on 3 times the standard deviation.
 *  \param vec Vector of doubles.
 *  \return Vector of outliers.
 */
vector<double>find3xOutliers(double_vector vec) {
    double mean = findMean(vec);
    double std_dev = findSD(vec);
    vector<double>outliers;
    for (size_t i = 0; i < vec.size(); i++) {
        if (abs(vec[i] - mean) > 3 * std_dev)
            outliers.push_back(vec[i]);
    }
    return outliers;
}

/** Calculate the slope of a linear regression line for a vector of doubles.
 *  \param vec Vector of doubles.
 *  \return Slope of the regression line.
 */
double findSlope(double_vector vec) {
    double valuesMean = findMean(vec);

    double indexesSum{ 0.0 };
    for (size_t i = 0; i < vec.size(); ++i) {
        indexesSum += i;
    }
    double indexesMean = indexesSum / vec.size();

    double squaredIndexesSum{ 0.0 };
    for (size_t i = 0; i < vec.size(); ++i) {
        squaredIndexesSum += i * i;
    }
    double ssxx = squaredIndexesSum - vec.size() * indexesMean * indexesMean;

    double meanIndexProductSum{ 0.0 };
    for (size_t i = 0; i < vec.size(); ++i) {
        meanIndexProductSum += i * vec[i];
    }
    double ssxy = meanIndexProductSum - vec.size() * indexesMean * valuesMean;

    return ssxy / ssxx;
}

/** Calculate the intercept of a linear regression line for a vector of doubles.
 *  \param vec Vector of doubles.
 *  \return Intercept of the regression line.
 */
double findIntercept(double_vector vec) {
    double valuesMean = findMean(vec);

    double indexesSum{ 0 };
    for (size_t i = 0; i < vec.size(); i++) {
        indexesSum += i;
    }
    double indexesMean = indexesSum * 1.0 / vec.size() * 1.0;

    double slope = findSlope(vec);

    return valuesMean - slope * indexesMean;
}

/** Merge two sorted vectors of doubles into a single sorted vector.
 *  \param vec1 First sorted vector.
 *  \param vec2 Second sorted vector.
 *  \return Merged sorted vector.
 */
vector<double>merge(double_vector vec1, double_vector vec2) {
    double_vector mergedVector;
    while (!vec1.empty() && !vec2.empty()) {
        if (vec1[0] <= vec2[0]) {
            mergedVector.push_back(vec1[0]);
            vec1.erase(vec1.begin());
        }
        else {
            mergedVector.push_back(vec2[0]);
            vec2.erase(vec2.begin());
        }
    }
    while (!vec1.empty()) {
        mergedVector.push_back(vec1[0]);
        vec1.erase(vec1.begin());
    }

    while (!vec2.empty()) {
        mergedVector.push_back(vec2[0]);
        vec2.erase(vec2.begin());
    }
    return mergedVector;
}

/** Sort a vector of doubles using merge sort algorithm.
 *  \param vec Vector of doubles.
 *  \return Sorted vector.
 */
vector<double>mergeSort(double_vector vec) {
    if (vec.size() <= 1)
        return vec;

    int half = vec.size() / 2;
    double_vector vec1(vec.begin(), vec.begin() + half);
    double_vector vec2(vec.begin() + half, vec.end());

    vec1 = mergeSort(vec1);
    vec2 = mergeSort(vec2);

    return merge(vec1, vec2);
}

/** Sort a vector of doubles using merge sort algorithm in place.
 *  \param vec Reference to the vector of doubles to be sorted.
 */
void ai_sort(double_vector& vec) {
    vec = mergeSort(vec);
}

/** Calculate the mode frequency and identify modes in a sorted vector of doubles.
 *  \param v Sorted vector of doubles.
 *  \param modes Vector to store mode values.
 *  \return Frequency of the mode(s).
 */
size_t mode_frequency(std::vector<double>&v, std::vector<double>&modes){
    ai_sort(v);
    size_t match{ 1 };	
    size_t mode_count{ 1 };	

    for (size_t i = 0; i < v.size() - 1; ++i)
    {
        if (v[i] == v[i + 1]) {
            match++;
        }
        else {
            if (match > mode_count) {
                modes.clear();
                modes.push_back(v[i]);
                mode_count = match;
            }
            else if (match == mode_count) {
                modes.push_back(v[i]);
            }
            match = 1;
        }
    }

    if (match > mode_count) {
        modes.clear();
        modes.push_back(v[v.size() - 1]);
        mode_count = match;
    }
    else if (match == mode_count) {
        modes.push_back(v[v.size() - 1]);
    }

    if (mode_count == 1) {
        modes.clear();
        mode_count = 0;
    }
    if (modes.size() * mode_count == v.size()) {
        modes.clear();
        mode_count = 0;
    }

    return mode_count;
 }

/** Print stats including count, min, max, mean, median, variance, and standard deviation.
 *  \param count Number of elements.
 *  \param min Minimum value.
 *  \param max Maximum value.
 *  \param mean Mean value.
 *  \param median Median value.
 *  \param variance Variance value.
 *  \param sd Standard deviation value.
 */
void print_stats_top(double count, double min, double max, double mean, double median, double variance, double sd) {
    cout << left << setw(30) << "# elements" << right << fixed << setprecision(0) << setw(30) << count << endl;
    cout << setprecision(3);
    cout << left << setw(30) << "minimum" << right << setw(30) << min << endl
    << left << setw(30) << "maximum" << right << setw(30) << max << endl
    << left << setw(30) << "mean" << right << setw(30) << mean << endl
    << left << setw(30) << "median" << right << setw(30) << median << endl
    << left << setw(30) << "variance" << right << setw(30) << variance << endl
    << left << setw(30) << "std. dev." << right << setw(30) << sd << endl;
}

/** Print mode information including mode count and mode values.
 *  \param modes Vector of mode values.
 *  \param modeFrequency Frequency of the mode(s).
 *  \param no_of_modes Number of modes.
 */
void print_mode(double_vector modes, size_t modeFrequency, size_t no_of_modes) {
    if (modes.empty()) {
        cout << left << setw(30) << "# modes" << right << setw(30) << "no mode" << endl;
    }
    else {
        cout << left << setw(30) << "# modes" << right << setw(30) << no_of_modes << endl
        << left << setw(30) << "modeFrequency" << right << setw(30) << modeFrequency << endl
        << left << setw(30) << "modes" << right;
        for (const auto& mode : modes) {
            cout << setw(30) << mode << endl << setw(30) << " ";
        }
        cout << endl;
    }
}

/** Print mean absolute deviations about the mean, median, and mode of a vector of doubles.
 *  \param meanAD Mean absolute deviation about the mean.
 *  \param medianAD Mean absolute deviation about the median.
 *  \param ModeAD Mean absolute deviation about the mode.
 */
void print_absoulute_devs(double meanAD, double medianAD, double ModeAD) {
    cout << left << setw(30) << "mean absolute deviations:" << endl;
    cout << setprecision(3);
    cout << left << setw(30) << "...about the mean" << right << setw(30) << meanAD << endl
        << left << setw(30) << "...about the median" << right << setw(30) << medianAD << endl
        << left << setw(30) << "...about the mode" << right << setw(30) << ModeAD << endl;  
}

/** Print mean absolute deviations about the mean and median of a vector of doubles.
 *  \param meanAD Mean absolute deviation about the mean.
 *  \param medianAD Mean absolute deviation about the median.
 */
void print_absoulute_devs(double meanAD, double medianAD) {
    cout << left << setw(30) << "mean absolute deviations:" << endl;
    cout << setprecision(3);
    cout << left << setw(30) << "...about the mean" << right << setw(30) << meanAD << endl
        << left << setw(30) << "...about the median" << right << setw(30) << medianAD << endl;
}

/** Print regression slope and intercept of a vector of doubles.
 *  \param slope Slope of the regression line.
 *  \param intercept Intercept of the regression line.
 */
void print_stats_bottom(double slope, double intercept) {
    cout << setprecision(3);
    cout << left << setw(30) << "regression slope" << right << setw(30) << slope << endl
        << left << setw(30) << "regression intercept" << right << setw(30) << intercept << endl;
}

/** Print outliers based on 2x and 3x standard deviations from the mean of a vector of doubles.
 *  \param outliers2x Vector of outliers based on 2x standard deviation.
 *  \param outliers3x Vector of outliers based on 3x standard deviation.
 */
void print_outliers(double_vector outliers2x, double_vector outliers3x) {
    
    if (outliers2x.empty())
        cout << left << setw(30) << "Outliers(2x)" << right << setw(30) << "no outliers" << endl;
    else {
        cout << left << setw(30) << "Outliers(2x)" << right << setw(29) << "# outliers = " << outliers2x.size() << endl;
        for (const auto& outlier2x : outliers2x) {
            cout << right << setw(60) << outlier2x << endl << setw(30) << " ";
        }
        cout << endl;
    }
    if(outliers3x.empty())
        cout << left << setw(30) << "Outliers(3x)" << right << setw(30) << "no outliers" << endl;
    else {
        cout << left << setw(30) << "Outliers(2x)" << right << setw(29) << "# outliers = " << outliers3x.size() << endl;
        for (const auto& outlier3x : outliers3x) {
            cout << right << setw(60) << outlier3x << endl << setw(30) << " ";
        }
        cout << endl;
    }
}
