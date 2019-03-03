//
//  main.cpp
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

vector<vector<double>> initiliaze_matrix(istringstream& input, int rows, int columns) {
    vector<vector<double>> array(rows,vector<double>(columns));
    for(int i = 0; i<rows; i++){
        for (int j = 0; j<columns; j++){
            input >> array[i][j];
        }
    }
    return array;
}

vector<vector<double>> initiliaze_matrix_from_vector(vector<int> input, int rows, int columns) {
    vector<vector<double>> array(rows,vector<double>(columns));
    int counter = 0;
    for(int i = 0; i<rows; i++){
        for (int j = 0; j<columns; j++){
            array[i][j] = input[counter];
            counter ++;
        }
    }
    return array;
}

vector<double> initiliaze_vector(istringstream& input) {
    input >> columns;
    vector<double> array(columns);
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

vector<double> multiply_vectors(vector<double> first, vector<double> second){
    vector<double> result(first.size());
    int i;
    for (i=0; i<first.size(); i++){
        result[i] = first[i]*second[i];
    }
    
    return result;
}

vector<double> select_columns(vector<vector<double>> matrix, int column){
    vector<double> ret_vec(matrix.size());
    for (int i=0; i<matrix.size(); i++){
        ret_vec[i] = matrix[i][column];
    }
    return ret_vec;
}

int main(int argc, const char * argv[]) {

    string trans_matrix;
    getline (cin, trans_matrix);

    string emis_matrix;
    getline (cin, emis_matrix);

    string init_state_prob;
    getline (cin, init_state_prob);

    string sequence_emission;
    getline (cin, sequence_emission);

    float rows_trans, columns_trans;
    istringstream trans_stream_matrix = istringstream(trans_matrix);
    trans_stream_matrix >> rows_trans >> columns_trans;
    // Matrix transition
    vector<vector<double>> transition = initiliaze_matrix(trans_stream_matrix, rows_trans, columns_trans);

    istringstream emis_stream_matrix = istringstream(emis_matrix);
    emis_stream_matrix >> rows >> columns;
    // Matrix emision
    vector<vector<double>> emision = initiliaze_matrix(emis_stream_matrix, rows, columns);

    istringstream init_state_prob_stream = istringstream(init_state_prob);
    float rows_state;
    init_state_prob_stream >> rows_state;
    // Vector intitial state
    vector<double> init_state = initiliaze_vector(init_state_prob_stream); // should be converted to int

    // Vector emisions received
    istringstream sequence_em = istringstream(sequence_emission);
    vector<double> emission_vector = initiliaze_vector(sequence_em); // should be converted to int

    int number_obs = emission_vector.size();
    // Matrices
    vector<int> emission_vector_new(emission_vector.begin(), emission_vector.end());

    vector<vector<double>> delta(number_obs,vector<double>(init_state.size())); // the 0 is included
    vector<vector<double>> best_path(number_obs,vector<double>(init_state.size())); // the 0 is included

    int column = emission_vector[0]; //the first observation
    vector<double> column_vector = select_columns(emision, column);
    delta[0] = best_path[0] = multiply_vectors(column_vector,init_state);
    float previous_max = 0;
    float value_iterate = 0;
    int previous_index = 0;
    vector<double> selected_col;

    for (int i=1; i<number_obs; i++){
        selected_col = select_columns(emision, emission_vector[i]);
        for (int j=0; j<init_state.size(); j++){
            for (int past_value = 0; past_value<init_state.size(); past_value++){
                value_iterate = delta[i-1][past_value] * transition[past_value][j] * selected_col[j];
                if (value_iterate > previous_max){
                    previous_max = value_iterate;
                    previous_index = past_value;
                }
            }
            best_path[i][j] = previous_index;
            delta[i][j] = previous_max;
            previous_max = 0;
        }
    }
    int delta_T_max = 0;
    int index;
    double aux = 0;
    for (int i=0 ; i<init_state.size() ; i++){
        if (delta[number_obs-1][i] > aux){
            delta_T_max = i;
            aux = delta[number_obs-1][i];
        }
    }
    vector<double> best_track;
    best_track.push_back (delta_T_max);
    for (int i=1 ; i<number_obs ; i++){
        delta_T_max = best_path[number_obs-i][delta_T_max];
        best_track.push_back (delta_T_max);
    }
    std::ostringstream concatenate;
    concatenate << best_track[number_obs-1];
    string result = concatenate.str();
    for (int i=2 ; i<=number_obs ; i++){
        concatenate << " " << best_track[number_obs-i];

    }
    cout << concatenate.str();
    return 0;
}
