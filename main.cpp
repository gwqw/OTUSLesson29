#include <iostream>

#include <vector>
#include <fstream>

#include <dlib/clustering.h>

#include "kkmeans_cluster.h"
#include "samples_sample.h"
#include "print_clusters.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc <= 1) {
        cout << "kkmeans <n> [<tolerance> [<max_dict_size>]]\nn -- clusters number\nExample: cat input | kkmeans 3\n";
        return 0;
    }
    try {
        auto cluster_num = stol(argv[1]);
        double tolerance = 0.1;
        size_t max_dict_size = 8;
        if (argc > 2) {
            tolerance = stod(argv[2]);
            if (argc > 3) {
                max_dict_size = stol(argv[3]);
            }
        }

        //auto samples = createExample(50); // we will make 50 points from each class
        auto samples = readSamples(cin);

        Cluster cluster(tolerance, max_dict_size);

        auto cluster_class = cluster.search_clusters(cluster_num, samples);

        print_output(samples, cluster_class, cout);
        ofstream f("output.out");
        print_for_scalc(samples, cluster_class, f);

        return 0;

    } catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }
}

