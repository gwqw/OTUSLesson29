#include <iostream>

#include <vector>
#include <fstream>

#include "kkmeans_cluster.h"
#include "samples_sample.h"
#include "print_clusters.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc <= 1) {
        cout << "kkmeans <n> [<ktype> [<tolerance> [<max_dict_size>]]]\n"
                "n -- clusters number\n"
                "ktype -- type of kernel: 0 - radial (default), 1 - polynomial, 2 - sigmoid, 3 - linear, 4 - histogram\n"
                "Example: cat input.txt | kkmeans 3\n";
        return 0;
    }
    try {
        auto cluster_num = stol(argv[1]);
        ClusterType ctype = ClusterType::RADIAL;
        double tolerance = 0.1;
        size_t max_dict_size = 8;
        if (argc > 2) {
            auto ct = stol(argv[2]);
            if (ct < 5) {
                ctype = static_cast<ClusterType>(ct);
            }
            if (argc > 3) {
                tolerance = stod(argv[3]);
                if (argc > 4) {
                    max_dict_size = stol(argv[4]);
                }
            }
        }

        auto samples = readSamples(cin);

        auto cluster = makeCluster(ctype, tolerance, max_dict_size);

        auto cluster_classification = cluster->search_clusters(cluster_num, samples);

        print_output(samples, cluster_classification, cout);
        ofstream f("output.out");
        print_for_scalc(samples, cluster_classification, f);

        return 0;

    } catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }
}

