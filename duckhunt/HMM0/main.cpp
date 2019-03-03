//
//  main.cpp
//  HelloWorld
//
//  Created by Héctor Esteban Cabezos on 15/1/19.
//  Copyright © 2019 Héctor Esteban Cabezos. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>

using namespace std;
int rows, columns;

vector<vector<float>> initiliaze_matrix(istringstream input) {
    input >> rows >> columns; // reads rows and after columns from the input string
    vector<vector<float>> array(rows,vector<float>(columns));
    for(int i = 0; i<rows; i++){
        for (int j = 0; j<columns; j++){
            input >> array[i][j];
        }
    }
    return array;
}

vector<float> initiliaze_vector(istringstream input) {
    input >> rows >> columns; // reads rows and after columns from the input string
    vector<float> array(columns);
    for (int j = 0; j<columns; j++){
        input >> array[j];
    }
    return array;
}

vector<float> multiply_matrices(vector<vector<float>> first, vector<float> second){
    vector<float> result(first[1].size());
    int i,j;
    for (i=0; i<first.size(); i++){
        for (j=0; j<first[0].size(); j++){
            result[j] = result[j] + second[i]*first[i][j];
        }
    }
    return result;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    string trans_matrix;
    string emis_matrix;
    string init_state_prob;
    //cout << "Introduce the transition matrix \n";
    getline (cin, trans_matrix);
    //cout << "Introduce the emission matrix \n";
    getline (cin, emis_matrix);
    //cout << "Introduce the initial state matrix \n";
    getline (cin, init_state_prob);


    vector<vector<float>> conditional = initiliaze_matrix(istringstream (trans_matrix));
    vector<vector<float>> emision = initiliaze_matrix(istringstream (emis_matrix));
    vector<float> state_prob = initiliaze_vector(istringstream (init_state_prob));

    vector<float> posterior_state = multiply_matrices(conditional, state_prob); // obtain posterior state probability
    vector<float> emision_prob_distr = multiply_matrices(emision, posterior_state); // obtain emision state probability
    std::ostringstream concatenate;
    concatenate << "1 " << emision_prob_distr.size();
    for (int i=0; i<emision_prob_distr.size(); i++){
        concatenate << " " << emision_prob_distr[i];
    }
    string result = concatenate.str();

    cout << result;

    return 0;
}
