#pragma once

#include <vector>

#include <dlib/clustering.h>

// Here we declare that our samples will be 2 dimensional column vectors.
// (Note that if you don't know the dimensionality of your vectors at compile time
// you can change the 2 to a 0 and then set the size at runtime)
using sample_type = dlib::matrix<double,2,1>;

// Now we are making a typedef for the kind of kernel we want to use.  I picked the
// radial basis kernel because it only has one parameter and generally gives good
// results without much fiddling.
using kernel_type = dlib::radial_basis_kernel<sample_type>;

class Cluster {
public:
    explicit Cluster(double tolerance = 0.001, std::size_t max_dict_size = 8)
    : kc(kernel_type(0.1), tolerance, max_dict_size),
      test(kc)
    {}

    std::vector<int> search_clusters(int cluster_count,
                                     const std::vector<sample_type>& samples);
private:
    dlib::kcentroid<kernel_type> kc;
    dlib::kkmeans<kernel_type> test;
};
