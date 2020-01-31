#include "print_clusters.h"

#include <cassert>

using namespace std;

void print_output(const std::vector<sample_type>& samples,
                  const std::vector<int>& cluster_class, std::ostream& out)
{
    assert(samples.size() == cluster_class.size());
    for (size_t i = 0; i < samples.size(); ++i) {
        out << samples[i](0,0) << ';'
            << samples[i](1,0) << ';'
            << cluster_class[i] << '\n';
    }
}

void print_for_scalc(const std::vector<sample_type>& samples,
                     const std::vector<int>& cluster_class, std::ostream& out)
{
    assert(samples.size() == cluster_class.size());
    out << "x\ty\tclass\tcolor\tsize\n";
    for (size_t i = 0; i < samples.size(); ++i) {
        out << samples[i](0,0) << '\t'
            << samples[i](1,0) << '\t'
            << cluster_class[i] << '\t'
            << cluster_class[i] << '\t'
            << 1 << '\n';
    }
    out << 200 << '\t'
        << 200 << '\t'
        << -1 << '\t'
        << 0 << '\t'
        << 100 << '\n';
}