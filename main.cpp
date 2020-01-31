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
    auto samples = createExample(50); // we will make 50 points from each class

    Cluster cluster(0.1, 8);

    auto cluster_class = cluster.search_clusters(3, samples);

    print_output(samples, cluster_class, cout);
    ofstream f("output.out");
    print_for_scalc(samples, cluster_class, f);

    return 0;
}

