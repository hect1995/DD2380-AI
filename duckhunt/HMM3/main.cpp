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
#include <fstream>
#include <cmath>


using namespace std;
int rows, columns;

vector<vector<double> > initiliaze_matrix(istringstream& input, int rows, int columns) {
    vector<vector<double> > array(rows,vector<double>(columns));
    for(int i = 0; i<rows; i++){
        for (int j = 0; j<columns; j++){
            input >> array[i][j];
        }
    }
    return array;
}

vector<vector<double> > initiliaze_matrix_from_vector(vector<int> input, int rows, int columns) {
    vector<vector<double> > array(rows,vector<double>(columns));
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

vector<float> multiply_matrices(vector<vector<float> > first, vector<float> second){
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

vector<double> select_columns(vector<vector<double> > matrix, int column){
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
    vector<vector<double> > transition = initiliaze_matrix(trans_stream_matrix, rows_trans, columns_trans);

    istringstream emis_stream_matrix = istringstream(emis_matrix);
    emis_stream_matrix >> rows >> columns;
    // Matrix emision
    vector<vector<double> > emision = initiliaze_matrix(emis_stream_matrix, rows, columns);

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
    
    int M = 0;
    for (int i = 0; i<emission_vector_new.size(); i++){
        if (emission_vector_new[i]>M){
            M = emission_vector_new[i];
        }
    }
    //vector<double> pi(init_state.size(), 1/init_state.size());
    vector<double> pi(init_state.size());
    pi = init_state;
    vector<vector<double> > a;//(init_state.size(),vector<double>(init_state.size())); // initialized transition matrix
    a = transition;
    // TODO : Check rows sum to 1
    
    vector<vector<double> > b;//(init_state.size(),vector<double>(M+1)); // initialized transition matrix
    b = emision;

    // TODO : Check rows sum to 1

    int iters = 0;
    double oldLogProb = -999999999999999999;
    int maxIters = 50;
    double logProb = 0;
    while (iters<maxIters and logProb>oldLogProb){
        if (iters>0){
            oldLogProb = logProb;
        }
        vector<vector<double> > alpha(number_obs,vector<double>(pi.size()));
        int column = emission_vector[0];
        vector<double> column_vector = select_columns(b, column);
        vector<double> c(number_obs);
        for (int i = 0; i<pi.size(); i++){
            alpha[0][i] = pi[i]*column_vector[i];
            c[0] = c[0] + alpha[0][i];
        }
        // scale a0(i)
        c[0] = 1/c[0];
        for (int i = 0; i<pi.size(); i++){
            alpha[0][i] = c[0] * alpha[0][i];
        }
        // compute at(i)
        vector<double> column_v;
        for (int t=1; t<number_obs; t++){ // the first position (0) is consider before the loop
            c[t] = 0;
            column_v = select_columns(b, emission_vector[t]);
            for (int i=0; i<pi.size(); i++){
                alpha[t][i] = 0;
                for (int j=0; j<pi.size(); j++){
                    alpha[t][i] = alpha[t][i] + alpha[t-1][j]*a[j][i];
                }
                alpha[t][i] = alpha[t][i]*column_v[i];
                c[t] = c[t] + alpha[t][i];
            }
            // scale at(i)
            c[t] = 1/c[t];
            for (int i=0; i<pi.size(); i++){
                alpha[t][i] = c[t]*alpha[t][i];
            }
        }
  
        vector<vector<double> > beta(number_obs,vector<double>(pi.size())); // the 0 is included
        vector<double> vect(pi.size(), 1); // initialize a vector to all 0's
        for (int i=0; i<pi.size(); i++){
            beta[number_obs-1][i] = c[number_obs-1];
        }
        // beta pass
        vector<double> column_beta;
        for (int t=number_obs-2; t >= 0; t--){
            column_beta = select_columns(b, emission_vector[t+1]);
            for (int i=0; i<pi.size(); i++){
                beta[t][i] = 0;
                for (int j=0; j<pi.size(); j++){
                    beta[t][i] = beta[t][i] + a[i][j]*column_beta[j]*beta[t+1][j];
                }
                //scale beta_t
                beta[t][i] = c[t]*beta[t][i];
            }
        }

        vector<vector<vector<double> > > mu_ij(number_obs , vector<vector<double>>(pi.size(), vector<double>(pi.size())));
        vector<vector<double> > mu_i(number_obs , vector<double>(pi.size()));
        vector<double> column_mu;

        double denom = 0;
        for (int t = 0; t < number_obs-1; t++){
            denom = 0;
            column_mu = select_columns(b, emission_vector[t+1]);
            for (int i=0; i<pi.size(); i++){
                for (int j=0; j<pi.size(); j++){
                    denom = denom + alpha[t][i]*a[i][j]*column_mu[j]*beta[t+1][j];
                }
            }
            for (int i=0; i<pi.size(); i++){
                mu_i[t][i] = 0;
                for (int j=0; j<pi.size(); j++){
                    mu_ij[t][i][j] = alpha[t][i]*a[i][j]*column_mu[j]*beta[t+1][j] / denom;
                    mu_i[t][i] = mu_i[t][i] + mu_ij[t][i][j];
                }
            }
        }
        // Special case yT-1 for back-propagation
        denom = 0;
        for (int i=0; i<pi.size(); i++){
            denom = denom + alpha[number_obs-1][i];
        }
        for (int i=0; i<pi.size(); i++){
            mu_i[number_obs-1][i] = alpha[number_obs-1][i] / denom;
        }
        
        for (int i=0 ; i<pi.size() ; i++){
            pi[i] = mu_i[0][i];
        }
        
        // re-estimate A
        double numerator, denominator = 0;
        for (int i=0 ; i<pi.size() ; i++){
            for (int j=0 ; j<pi.size() ; j++){
                numerator = 0;
                denominator = 0;
                for (int t=0 ; t<number_obs-1 ; t++){
                    numerator = numerator + mu_ij[t][i][j];
                    denominator = denominator + mu_i[t][i];
                }
                a[i][j] = numerator / denominator;
            }
        }
        
        for (int i=0 ; i<pi.size() ; i++){
            for (int j=0 ; j<M+1 ; j++){
                numerator = 0;
                denominator = 0;
                for (int t=0 ; t<number_obs ; t++){
                    if (emission_vector_new[t] == j){
                        numerator = numerator + mu_i[t][i];
                    }
                    denominator = denominator + mu_i[t][i];
                }
                b[i][j] = numerator / denominator;
            }
        }
        logProb = 0;
        for (int i = 0; i < number_obs; i++){
            logProb = logProb + log(c[i]);
        }
        logProb = -logProb;
        iters ++;
    }
    cout << a.size() << " " << a[0].size();
    for (int i=0 ; i<pi.size() ; i++){
        for (int j=0 ; j<pi.size() ; j++){
            cout << " " << a[i][j];
        }
    }
    cout << endl;
    cout << b.size() << " " << b[0].size();
    for (int i=0 ; i<pi.size() ; i++){
        for (int j=0 ; j<M+1 ; j++){
            cout << " " << b[i][j];
        }
    }
    cout << endl;

    return 0;
}
