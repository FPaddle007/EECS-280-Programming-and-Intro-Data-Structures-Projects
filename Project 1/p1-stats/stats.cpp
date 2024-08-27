// stats.cpp
// Project UID 5366c7e2b77742d5b2142097e51561a5

#include "stats.h"
#include <cassert>
#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <limits>
#include "p1_library.h"

using namespace std;

vector<vector<double>> summarize(vector<double> v) // summary
{
    sort(v);
    vector<vector <double>> summary_vec;

    for (size_t i = 0; i < v.size() - 1; ) {
        double freq = 0;
        size_t j = i;

        while (v[i] == v[j] && j < v.size()) {
            ++freq;
            ++j;
        }

        vector<double> otherV = {v[i], freq};
        summary_vec.push_back(otherV);

//        cout << "{" << v[i] << ", " << freq << "}" << endl;
        
        freq = 0;
        i = j;
    }
    
    return summary_vec;
}

/*    
//vector<vector<double>> summary_vec;
//sort(v);
//double freq = 1;
vector<vector<double>> summary_vec;
sort(v);
vector<double> otherV;

for(int i = 0; i < static_cast<int>(v.size()) - 1; i++){
if(v[i] != v[i+1]){
otherV.push_back(v[i-1]);
summary_vec.push_back(otherV);
}
if(i == static_cast<int>(v.size()) - 1){
otherV.push_back(v[i]);
summary_vec.push_back(otherV);
}
} */  
/* 
   vector<double> summary_vec = v;
   sort(summary_vec);
   int size_summary_vec = static_cast <int>(summary_vec.size());
   vector<vector<double>> summarize(size_summary_vec, vector<double>(2));

   double num = summary_vec[0];
   double summary_vec_temp;

   for (int i = 1; i < size_summary_vec; i += 1) {
   int freq = 1;
   while (num == summary_vec[i]) {
   freq += 1;
   summary_vec_temp = summary_vec[i];
   num = summary_vec[i];
   i += 1;
   }
   int r = 0;
   summarize[r][0] = summary_vec_temp;
   summarize[r][0] = freq;
   summary_vec_temp = summary_vec[i];
   num = summary_vec[i];

   r += 1;
   }
   return summarize;
   }
   */

int count(vector<double> v) // count
{
    int size = static_cast<int>(v.size());

    return size;
}

double sum(vector<double> v) // sum
{

    double sum_of_integers = 0;

    for (int i = 0; i < count((v)); i++)
    {
        sum_of_integers += v[i];
    }
    return sum_of_integers;
}

double mean(vector<double> v) // mean
{

    double sum1 = sum(v);
    double count1 = count(v);
    double mean;
    mean = sum1 / count1;

    return mean;
}

double median(vector<double> v) // median
{
    sort(v);
    double median = v[0];

    if (count(v) % 2 != 0)
    {
        int index = (count(v) / 2);
        median = v[index];
    }
    else
    {
        if (count(v) % 2 == 0)
        {
            int upper_index = count(v) / 2;
            int lower_index = (count(v) / 2) - 1;
            double upper_value = v[upper_index];
            double lower_value = v[lower_index];
            median = (upper_value + lower_value) / 2;
        }
    }
    return median;
}

double mode(vector<double> v) // mode
{
    sort(v);

    double mode_val = v[0];
    int mode_freq = 0;

    for (size_t i = 0; i < v.size() - 1; ++i) {
        double current_val = v[i];
        int current_freq = 0;

        for (size_t j = i + 1; j < v.size(); ++j) {
            if (v[i] == v[j]) {
                ++current_freq;

                if (j == v.size() - 1 && current_freq > mode_freq) {
                    mode_val = current_val;
                    mode_freq = current_freq;
                }
            }
        }
    }

    return mode_val;
}

double min(vector<double> v) // min
{
    sort(v);
    return v[0];
}

double max(vector<double> v) // max
{
    sort(v);
    return v[v.size() - 1];
}

double stdev(vector<double> v) // standard deviation
{

    double sum_dev = 0, mean_dev, variance_dev = 0, std_dev;

    for (size_t s = 0; s < v.size(); ++s)
    {
        sum_dev += v[s];
    }
    mean_dev = mean(v);

    for (int s = 0; s < (int)v.size(); ++s)
    {
        variance_dev += (v[s] - mean_dev) * (v[s] - mean_dev);
    }
    variance_dev = variance_dev / (v.size() - 1);
    std_dev = sqrt(variance_dev);
    return std_dev;
}

double percentile(vector<double> v, double p) // percentile
{
    sort(v);
    double rank = p * (v.size() - 1);
    if(rank == v.size() - 1){
        return v[v.size() - 1];
    }
    return v[(int)rank] + (rank - (int)rank) * (v[int(rank) + 1] - v[(int) rank]);
}
