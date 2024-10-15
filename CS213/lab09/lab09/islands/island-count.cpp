#include "dfs.h"
// here T1 is a matrix (2D vector of int) and T2 is a matrix (2D vector of bool)

// validate
// check the indices and additional conditions after which you would use dfs
template <typename T1, typename T2> bool DFS::validate(T1& M, int i, int j, T2& v) {
        if (i >= 0 && i < M.size() && j >= 0 && j < M[0].size() && v[i][j] != 1) {
        return true;
    }
    else return false;
}

// this function need not be used for island count problem
template <typename T1, typename T2> bool DFS::terminate(T1& M, int i, int j, T2& v) {
    return false;
}

// dfs
// modify the data structure (matrix M and/or v) as needed
// you can solve this without modifying M
// use the row and col vectors to access neighbors of (i,j)
// validate the neighbour before you use dfs
template <typename T1, typename T2> void DFS::dfs(T1& M, int i, int j, T2& v) {
    if (validate(M,i,j,v)){
        v[i][j] = 1;
        for (int a = 0; a < row.size(); a++) {
            if (validate(M, i + row[a], j + col[a], v)) {
                if (M[i + row[a]][j + col[a]] == 1){
                    dfs(M, i + row[a], j + col[a], v);
                }
            }
        }
    }
}
