#include "../useful-extra-edges.h"

Testcase::Testcase() {
    n = 100000;
    src = 1;
    dest = 100000;

    // Edges
    for(int i = 1; i <= n; i++) {
        if(2*i <= n) {
            addEdge(i, 2*i, 2*i);
        }
        if(2*i+1 <= n) {
            addEdge(i, 2*i+1, 2*i+1);
        }
    }

    // Extra Edges
    for(int i = 1; i < n-1; i++) {
        addExtraEdge(i, i+1, 1);
    }
    addExtraEdge(25000, 50000, 49999);
    addExtraEdge(50000, 100000, 99998);
}