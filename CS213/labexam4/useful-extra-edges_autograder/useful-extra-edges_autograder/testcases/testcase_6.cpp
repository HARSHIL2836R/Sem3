#include "../useful-extra-edges.h"

Testcase::Testcase() {
    n = 100000;
    src = 100;
    dest = 100000;

    // Edges
    for(int i = 1; i <= n; i++) {
        addEdge(1, i, i);
    }

    // Extra Edges
    for(int i = 1; i < n; i++) {
        addExtraEdge(i, i+1, 1);
    }
}