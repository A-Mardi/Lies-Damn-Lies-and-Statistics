# Lies, Damn Lies, and Statistics 

Course: INFO-1156 Object-Oriented Programming in C++

Professor: Garth Santor/Janice Manning

## Project Overview

This C++ 20 console application performs a series of statistical analyses on a dataset of real numbers and performs a least squares regression analysis. The dataset can be input via console (cin) or a file through command line input, and the program handles an arbitrary number of data points.

The project involves calculating:

Number of values

Minimum and maximum values

Arithmetic mean

Statistical median

Mean absolute deviation (mean, median, mode)

Variance and standard deviation (population statistics)

Mode (handling multimodal lists)

Least squares regression line

Outliers (1x, 2x, 3x deviations)

Additionally, a custom sorting algorithm (quick, merge, or heap sort) is implemented to sort the dataset.

## Features

Dynamic Input Handling: Accepts data from console input, piped input, or files.

Parallel Sorting: Implements a custom sorting algorithm, sorting two arrays in parallel.

Full Statistical Analysis: Outputs key statistics including mean, median, mode, variance, and more.

Least Squares Regression: Calculates the slope and y-intercept of a regression line.

Outlier Detection: Identifies 1x, 2x, and 3x outliers from the dataset.

## How to Run

**Clone the repository:**

`git clone <https://github.com/A-Mardi/Lies-Damn-Lies-and-Statistics>`

**Build the project in Visual Studio**

**Run the application:**

`./stats.exe`

**Enter the data via the console or provide a file using the command line:**

`./stats.exe < input.txt`

Sample Input

`5 6 6 7 7 7 8 8 9 end`

Sample Output
```
stats 1.0.0 (2024), (c) 2024 Ahmed Ibrahim
Enter a list of whitespace-separated real numbers terminated by ^Z or 'end'.
5 6 6 7 7 7 8 8 9 end

---------------------------------------------
# elements                                  9
minimum                                 5.000
maximum                                 9.000
mean                                    7.000
median                                  7.000
variance                                1.333
std. dev.                               1.155
---------------------------------------------
# modes                                     1
mode frequency                              3
mode                                    7.000
---------------------------------------------
mean absolute deviations:
...about the mean                       0.889
...about the median                     0.889
...about the mode                       0.889
---------------------------------------------
regression slope                        0.433
regression intercept                    5.267
---------------------------------------------
Outliers(2x)                      no outliers
Outliers(3x)                      no outliers
```
## Ownership

This project is the property of **Garth Santor** & **Fanshawe College** and is created for the purposes of the INFO-1156 Object-Oriented Programming in C++ course. Unauthorized distribution or use of this project without permission from Garth Santor & Fanshawe College is prohibited.

## Author

Ahmed Ibrahim
