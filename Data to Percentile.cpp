//
//  Data to Percentile.cpp
//  CVS data to CVS percentile
//
//  Created by Sam Ferguson on 2018-04-01.
//

#include "Data to Percentile.hpp"
#include <fstream>
#include <algorithm>
#include <math.h>

using namespace std;

//function to sort pairs by the second value in said pair
static bool sortbysec(const pair<double,int> &a,
                      const pair<double,int> &b)
{
    return (a.second < b.second);
}

namespace SKFData2Per {
    Data2Per::Data2Per(){
    }
    Data2Per::Data2Per(string filename): m_filename(filename){
        
    }
    void Data2Per::printFile(string outFileName, const int arr[], const int size, const int start, bool header){
       
        
        if(outFileName == "")
            return;
        
        //create the file
        ofstream outFile;
        
        
        outFile.open(outFileName);
        
        if(outFile.is_open()){
            
            //check for header
            if(header){
                
                //loop through the first line, adding a % and a copy of the header to the next one if the data beneth is not a duplicate (meaning we have calculated a percentile for it
                for(int j = 0; j< size; j++){
                    if(m_data[1][arr[j]] != m_dataCopy[1][arr[j]]){
                        if(j == size){
                            outFile<<m_data[0][arr[j]]<<"%"<<m_data[0][arr[j]];
                        }
                        else{
                            outFile<<m_data[0][arr[j]]<<"%"<<","<<m_data[0][arr[j]]<<",";
                        }
                    }
                    else{
                        if(j == size){
                            outFile<<m_data[0][arr[j]];
                        }
                        else{
                            outFile<<m_data[0][arr[j]]<<",";
                        }
                    }
                    
                }
                outFile<<endl;
                //with a header we loop through the vector matrix starting with row 1 instead of 0
                for(int i = start+1; i<m_data.size(); i++){
                    for(int j = 0; j < size; j++){
                        
                        //check for ","'s inside the elements
                        if (m_data[i][arr[j]].find(",") != string::npos){
                            m_data[i][arr[j]].erase(m_data[i][arr[j]].find(","), 1);
                        }
                        
                        
                        
                        //add's element/"," or just element if last item in vector plus the original value of the cell after it if a percentile has been calculated
                        if(m_data[i][arr[j]] != m_dataCopy[i][arr[j]]){
                            if(j == size){
                                outFile<<m_data[i][arr[j]]<<","<<m_dataCopy[i][arr[j]];
                            }
                            else{
                                outFile<<m_data[i][arr[j]]<<","<<m_dataCopy[i][arr[j]]<<",";
                            }
                        }
                        else{
                            if(j == size){
                                outFile<<m_data[i][arr[j]];
                            }
                            else{
                                outFile<<m_data[i][arr[j]]<<",";
                            }
                        }
                    }
                    outFile<<endl;
                }
            }
            else{
                //if no header start looping at row 0
                for(int i = start; i<m_data.size(); i++){
                    for(int j = 0; j < size; j++){
                        
                        //check for ","'s inside the elements
                        if (m_data[i][arr[j]].find(",") != string::npos){
                            m_data[i][arr[j]].erase(m_data[i][arr[j]].find(","), 1);
                        }
                        
                        
                        
                        //add's element/"," or just element if last item in vector plus the original value of the cell after it if a percentile has been calculated
                        if(m_data[i][arr[j]] != m_dataCopy[i][arr[j]]){
                            if(j == size - 1){
                                outFile<<m_data[i][arr[j]]<<","<<m_dataCopy[i][arr[j]];
                            }
                            else{
                                outFile<<m_data[i][arr[j]]<<","<<m_dataCopy[i][arr[j]]<<",";
                            }
                        }
                        else{
                            if(j == size - 1){
                                outFile<<m_data[i][arr[j]];
                            }
                            else{
                                outFile<<m_data[i][arr[j]]<<",";
                            }
                        }
                    }
                    outFile<<endl;
                }
            }
            outFile.close();
        }
        else{
            cout<< "could not create file: " << outFileName << endl;
        }
    }
    void Data2Per::setData(){
        if(m_filename == "")
            return;
        
        //open the file
        ifstream input;
        
        input.open(m_filename);
        
        if(input.is_open()){
            //string to hold line
            string line;
            //vector to hold the row
            vector<string> tempvector;
            
            //loop to get each line of file
            while (!input.eof()){
                
                //gets lines of file, self advance with each output to line (second variable)
                getline(input, line);
                
                //count the total rows
                m_totalRows++;
                
                size_t start = 0;
                //find the first comma
                size_t end = line.find(",");
                size_t len = 0;
                
                len = end - start;
                
                char bufferpre[len];
                
                //add our line to the vector
                if(len == 0){
                    tempvector.push_back("");
                }
                else{
                    line.copy(bufferpre, len, start);
                    bufferpre[len] ='\0';
                    tempvector.push_back(bufferpre);
                }
                
                
                start = end;
                
                end = line.find(",", end+1);
                
                //loop through the rest of our values now that the first one is set
                while(true){
                    
                    //find lenth of our varible
                    len = end - start;
                    len--;
                    
                    char buffer[len];
                    
                    //add our line to the vector
                    if(len == 0){
                        tempvector.push_back("");
                    }
                    else{
                        line.copy(buffer, len, start+1);
                        buffer[len] ='\0';
                        tempvector.push_back(buffer);
                    }
                    
                    //set start to end for next time arround
                    start = end;
                    
                    //set end to next comma for next time arorund
                    end = line.find(",", end+1);
                    //if our comma is not found in the string then exit
                    if(end == string::npos){
                        
                        len = line.length() - start;
                        
                        char buffer2[len];
                        
                        if(len == 0){
                            tempvector.push_back("");
                        }
                        else{
                            line.copy(buffer2, len, start+1);
                            buffer2[len] ='\0';
                            tempvector.push_back(buffer2);
                        }
                        
                        break;
                    }
                }
                //add the vector to the matrix and clear it for next time arround
                m_data.push_back(tempvector);
                tempvector.clear();
            }
            //make a copy of our matrix for printing
            m_dataCopy = m_data;
            input.close();
        }
        else{
            cout<< "could not read file: " << m_filename << endl;
        }
        
    }
    void Data2Per::calcPer(int start, int end, int size, int arr[]){
        
        vector< pair <double,int> > indextCol;
        int col = 0;
        char period[2] = ".";
        
        //loop throuhg all the columns in question
        for(int i = 0; i < size; i++){
            
            col = arr[i];
            
            
            //loop through the rows
            for(int j = start; j<end; j++){
                
                //make pairs for sorting, adding an index so we can put the calculated values back in the right place
                if(m_data[j][col] == "" || stod(m_data[j][col]) == 0){
                    indextCol.push_back(make_pair(0.0, j));
                }
                else if(m_data[j][col].front() == period[0]){
                    indextCol.push_back(make_pair(stod(m_data[j][col]), j));
                }
                else{
                    indextCol.push_back(make_pair(stod(m_data[j][col]), j));
                }
            }
            //sort the index
            sort(indextCol.begin(), indextCol.end());
            //reverse(indextCol.begin(), indextCol.end());
            double watch = 0.0;
            
            //calculate the percentile
            for(int j = start; j<end; j++){
                if(indextCol[j-start].first == watch){
                    indextCol[j-start].first = indextCol[j-start-1].first;
                }
                else{
                    watch = indextCol[j-start].first;
                    indextCol[j-start].first = (j/(double)end)*100;
                }
                // cout << indextCol[i-1].first << " "
                // << indextCol[i-1].second << endl;
            }
            
            //sort by the index so we can put it back in the right place
            sort(indextCol.begin(), indextCol.end(), sortbysec);
            
            //put the percentile back where we got our original value
            for(int j = start; j<end; j++){
                m_data[j][col] = to_string(indextCol[j-start].first);
                
//                cout << indextCol[i-1].first << " "
//                << indextCol[i-1].second << endl;
            }
           //clear our vector of pairs
            indextCol.clear();
            
            }
    }
    vector<vector<string> > Data2Per::getData() const{
        vector<vector<string> > data;
        
        data = m_data;
        
        return data;
        
    }
    void Data2Per::deleteData(int col, double value, int start, int end){
        
        //loop through the rows
        for(int i = start; i <= end; i++){
            
            //check if the value is high enough and if now errase the vector
            if(stod(m_data[i][col]) < value){
                m_data.erase(m_data.begin()+i);
                m_dataCopy.erase(m_dataCopy.begin()+i);
                //the vector is shorter now so we must ajust a few things
                end--;
                i--;
                m_totalRows--;
           
            }
        }

        
    }
    int Data2Per::getTotalRows(){
        int rows = m_totalRows;
        
        return rows;
    }

}
