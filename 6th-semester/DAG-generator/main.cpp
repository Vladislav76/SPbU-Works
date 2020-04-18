#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

long MIN_PER_RANK = 28; /* Nodes/Rank: How 'fat' the DAG should be.  */
long MAX_PER_RANK = 30;
long MIN_RANKS = 200;    /* Ranks: How 'tall' the DAG should be.  */
long MAX_RANKS = 200;
long PERCENT = 90;     /* Chance of having an Edge.  */

vector<pair<long,long>> edges = {};

void generate() {
    long i, j, k, nodes = 0;
    srandom(time(nullptr));

    long ranks = MIN_RANKS + (random() % (MAX_RANKS - MIN_RANKS + 1));

    for (i = 0; i < ranks; i++)
    {
        /* New nodes of 'higher' rank than all nodes generated till now.  */
        long new_nodes = MIN_PER_RANK + (random() % (MAX_PER_RANK - MIN_PER_RANK + 1));

        /* Edges from old nodes ('nodes') to new ones ('new_nodes').  */
        for (j = 0; j < nodes; j++)
            for (k = 0; k < new_nodes; k++)
                if ((random() % 100) < PERCENT)
                    edges.push_back(make_pair<>(j + 1, k + nodes + 1));

        nodes += new_nodes; /* Accumulate into old node set.  */
    }

    ofstream file;

    string dir = "../dataset/";
    string ext1 = ".mtx";
    string ext2 = ".dot";
    string fileName = to_string(nodes) + "v_" + to_string(edges.size()) + "e";

    // .mtx
    file.open(dir + fileName + ext1);

    file << "%%MatrixMarket matrix coordinate integer general\n";
    file << "%%GraphBLAS GrB_BOOL\n";

    file << nodes << " " << nodes << " " << edges.size() << "\n";

    for (pair<long,long> e : edges) {
        file << e.first << " " << e.second << " " << "1\n";
    }

    file.close();

    // .dot
//    file.open(dir + fileName + ext2);
//
//    file << "digraph {\n";
//    for (pair<long,long> e : edges) {
//        file << "  " << e.first << " -> " << e.second << ";\n";
//    }
//    file << "}\n";
//
//    file.close();
}

int main(int argc, char **argv)
{
    generate();
    return 0;
}
