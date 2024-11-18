// DO NOT MODIFY THIS FILE

#include <iostream>
#include <fstream>
#include "check-tree.h"
using namespace std;


int main(){

    int marks = 0;
    int num_tests = 16;

    int false_rets = 0;

    for(int i = 1; i <= num_tests; i++){
        ifstream infile("testcases/input/" + to_string(i) + ".txt");

        unsigned n;
        infile >> n;

        vector<vector<int>> dist(n, vector<int>(n));

        for(unsigned i = 0; i < n; i++){
            for(unsigned j = 0; j < n; j++){
                infile >> dist[i][j];
            }
        }

        infile.close();


        bool result, actual;
        vector<tuple<int, int, int>> found_tree;
        result = check_tree(n, dist, found_tree);

        if(!result) false_rets++;

        ifstream resfile("testcases/output/" + to_string(i) + ".txt");
        resfile >> actual;
        resfile.close();

        if(result == actual){

            if(result == 0){
                cerr << "Test case " << i << " passed" << endl;
                marks++;
                continue;
            }

            vector<vector<int>> newdist(n, vector<int>(n));
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    newdist[i][j] = 1e9;
                    newdist[j][i] = 1e9;
                }
                newdist[i][i] = 0;
            }

            for(auto &[u, v, w] : found_tree){
                newdist[u][v] = w;
                newdist[v][u] = w;
            }

            for(int k = 0; k < n; k++){
                for(int i = 0; i < n; i++){
                    for(int j = 0; j < n; j++){
                        newdist[i][j] = min(newdist[i][j], newdist[i][k] + newdist[k][j]);
                    }
                }
            }

            bool correct = true;
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    if(newdist[i][j] != dist[i][j]){
                        correct = false;
                        break;
                    }
                }
                if(!correct) break;
            }

            if(correct){
                cerr << "Test case " << i << " passed" << endl;
                marks++;
            }   
            else{
                cerr << "Test case " << i << " failed for tree" << endl;
                for(auto &[u, v, w] : found_tree){
                    cerr << u << " " << v << " " << w << endl;
                }

            }
        }
        else{
            cerr << "Test case " << i << " failed for flag" << endl;
        }
    }

    if(false_rets == num_tests) marks = 0;
    cout << "Total score: " << marks << "/" << num_tests << endl;
    
    return 0;
}
