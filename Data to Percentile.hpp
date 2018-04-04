//
//  Data to Percentile.hpp
//  CVS data to CVS percentile
//
//  Created by Sam Ferguson on 2018-04-01.
//

#ifndef Data_to_Percentile_hpp
#define Data_to_Percentile_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

namespace SKFData2Per {

    class Data2Per {
    public:
        //default constructor
        Data2Per();
        //constructor
        Data2Per(string filename);
        //print out our csv file, takes name, pointer to array with all the columns we want printed, size of that array, what column to start at and weather there is a header to consider
        void printFile(string outFileName, const int arr[], const int size, const int start, bool header);
        //sets our incoming csv file to our vector matrix m_data
        void setData();
        //calculates the percentile of each element in a column and sets it to our vector matrix takes a start and end row, a pointer to an int array containing the columns we want calculated and the size of that array
        void calcPer(int start, int end, int size, int arr[]);
        //delete unwanted rows by making sure the value in a certain column is higher than the one provided, takes the column index in question, the value that index must be above and a start and end row
        void deleteData(int col, double value, int start, int end);
        //getter for our m_data vector matrix
        vector<vector<string> > getData() const;
        //getter for the current number of rows
        int getTotalRows();
        
        
    private:
        vector<vector<string> > m_dataCopy;
        vector<vector<string> > m_data;
        int m_totalRows{0};
        string m_filename{""};

        
        
        
    };
}



#endif /* Data_to_Percentile_hpp */
