// main.cpp
// Project UID 5366c7e2b77742d5b2142097e51561a5

// Project 1 - Statistics
// Name: Christopher Felix
// Unique Name: chrisfx

#include "stats.h"
#include "p1_library.h"
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <limits>

using namespace std;
using std::cin;

void print_summary(vector<double> v);
    

int main()
{
    vector<double> stats_for_p1;
    vector<vector<double>> summary_vec;

    string file_name;
    string column_name;

    cout << "enter a filename" << endl;
    cin >> file_name;

    cout << "enter a column name" << endl;
    cin >> column_name;
    stats_for_p1 = extract_column(file_name, column_name);
    summary_vec = summarize(stats_for_p1);

    
    cout << "reading column " << column_name << " from " << file_name << endl;

    print_summary(stats_for_p1);
    cout << "count = " << count(stats_for_p1) << endl;
    cout << "sum = " << sum(stats_for_p1) << endl;
    cout << "mean = " << mean(stats_for_p1) << endl;
    cout << "stdev = " << stdev(stats_for_p1) << endl;
    cout << "median = " << median(stats_for_p1) << endl;
    cout << "mode = " << mode(stats_for_p1) << endl;
    cout << "min = " << min(stats_for_p1) << endl;
    cout << "max = " << max(stats_for_p1) << endl;
    cout << "  0th percentile = " << percentile(stats_for_p1, 0) << endl;
    cout << " 25th percentile = " << percentile(stats_for_p1, 0.25) << endl;
    cout << " 50th percentile = " << percentile(stats_for_p1, 0.50) << endl;
    cout << " 75th percentile = " << percentile(stats_for_p1, 0.75) << endl;
    cout << "100th percentile = " << percentile(stats_for_p1, 1) << endl;

    return 0;
}

void print_summary(vector<double> v) {
    cout << "Summary (value: frequency)" << endl;

    vector<vector<double>> summary = summarize(v);
    
    for (size_t i = 0; i < summary.size(); ++i) {
        cout << summary[i][0] << ": " << summary[i][1] << endl;
    }

    cout << endl;

}