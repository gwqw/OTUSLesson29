#include "kkmeans_cluster.h"

// The contents of this file are in the public domain. See LICENSE_FOR_EXAMPLE_PROGRAMS.txt
/*
    This is an example illustrating the use of the kkmeans object
    and spectral_cluster() routine from the dlib C++ Library.

    The kkmeans object is an implementation of a kernelized k-means clustering
    algorithm.  It is implemented by using the kcentroid object to represent
    each center found by the usual k-means clustering algorithm.

    So this object allows you to perform non-linear clustering in the same way
    a svm classifier finds non-linear decision surfaces.

    This example will make points from 3 classes and perform kernelized k-means
    clustering on those points.  It will also do the same thing using spectral
    clustering.

    The classes are as follows:
        - points very close to the origin
        - points on the circle of radius 10 around the origin
        - points that are on a circle of radius 4 but not around the origin at all
*/

using namespace std;

std::vector<int> Cluster::search_clusters(int cluster_count, const std::vector<sample_type> &samples) {
    test.set_number_of_centers(cluster_count);
    std::vector<sample_type> initial_centers;
    pick_initial_centers(cluster_count, initial_centers, samples, test.get_kernel());
    test.train(samples, initial_centers);

    std::vector<int> res;
    res.reserve(samples.size());
    for (const auto& sample : samples) {
        res.push_back(test(sample));
    }
    return res;
}

std::vector<int> Cluster::search_spectral_clusters(int cluster_count, const std::vector<sample_type> &samples) {
    std::vector<int> res;
    res.reserve(samples.size());

    std::vector<unsigned long> assignments = spectral_cluster(kernel_type{}, samples, cluster_count);
    res = {assignments.begin(), assignments.end()};
    return res;
}

using namespace dlib;

void cluster_data(const std::vector<sample_type>& samples) {
    // Here we declare an instance of the kcentroid object.  It is the object used to
    // represent each of the centers used for clustering.  The kcentroid has 3 parameters
    // you need to set.  The first argument to the constructor is the kernel we wish to
    // use.  The second is a parameter that determines the numerical accuracy with which
    // the object will perform part of the learning algorithm.  Generally, smaller values
    // give better results but cause the algorithm to attempt to use more dictionary vectors
    // (and thus run slower and use more memory).  The third argument, however, is the
    // maximum number of dictionary vectors a kcentroid is allowed to use.  So you can use
    // it to control the runtime complexity.
    kcentroid<kernel_type> kc(kernel_type(),0.01, 8);

    // Now we make an instance of the kkmeans object and tell it to use kcentroid objects
    // that are configured with the parameters from the kc object we defined above.
    kkmeans<kernel_type> test(kc);

    // tell the kkmeans object we made that we want to run k-means with k set to 3.
    // (i.e. we want 3 clusters)
    test.set_number_of_centers(3);

    // You need to pick some initial centers for the k-means algorithm.  So here
    // we will use the dlib::pick_initial_centers() function which tries to find
    // n points that are far apart (basically).
    std::vector<sample_type> initial_centers;
    pick_initial_centers(3, initial_centers, samples, test.get_kernel());

    // now run the k-means algorithm on our set of samples.
    test.train(samples, initial_centers);

    // now loop over all our samples and print out their predicted class.  In this example
    // all points are correctly identified.
    for (const auto& sample : samples) {
        cout << sample(0,0) << " ";
        cout << sample(1,0) << " ";
        cout << test(sample) << "\n";
    }

    // Now print out how many dictionary vectors each center used.  Note that
    // the maximum number of 8 was reached.  If you went back to the kcentroid
    // constructor and changed the 8 to some bigger number you would see that these
    // numbers would go up.  However, 8 is all we need to correctly cluster this dataset.
    cout << "num dictionary vectors for center 0: " << test.get_kcentroid(0).dictionary_size() << endl;
    cout << "num dictionary vectors for center 1: " << test.get_kcentroid(1).dictionary_size() << endl;
    cout << "num dictionary vectors for center 2: " << test.get_kcentroid(2).dictionary_size() << endl;


    // Finally, we can also solve the same kind of non-linear clustering problem with
    // spectral_cluster().  The output is a vector that indicates which cluster each sample
    // belongs to.  Just like with kkmeans, it assigns each point to the correct cluster.
    std::vector<unsigned long> assignments = spectral_cluster(kernel_type(), samples, 3);
    cout << mat(assignments) << endl;
}