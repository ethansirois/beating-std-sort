#include "test.h"

std::vector<uint> populate(uint n, uint range) {
    std::vector<uint> vect;
    vect.reserve(n); // since we know the size already
    for (uint run = 0; run < n / range; ++run) {
        for (uint value = 0; value < range; ++value) {
            vect.push_back(value); 
        }
    }
    return vect;
}

int main() {

    std::vector<uint> ns{100, 1000, 10000, 100000, 1000000, 10000000};
    std::vector<uint> ranges{10, 100, 1000, 10000};
    std::vector<std::pair<double, double>> times;
    std::vector<std::pair<uint, uint>> details;
    for (uint range : ranges) {
        for (uint n : ns) {
            std::vector<uint> vect = populate(n, range);
            
            auto start{std::chrono::steady_clock::now()};
            auto end{std::chrono::steady_clock::now()};

            start = std::chrono::steady_clock::now();
            boost::sort::spreadsort::integer_sort(vect.begin(), vect.end());
            end = std::chrono::steady_clock::now();
            std::chrono::duration<double> elapsed_seconds_ss{end - start};


            start = std::chrono::steady_clock::now();
            std::sort(vect.begin(), vect.end());
            end = std::chrono::steady_clock::now();
            std::chrono::duration<double> elapsed_seconds_std{end - start};

            times.push_back(std::make_pair(elapsed_seconds_ss.count(), elapsed_seconds_std.count()));
            details.push_back(std::make_pair(range, n));
        }
    }
    for (uint r = 0; r < ranges.size(); ++r) {
        std::cout << "# at range r = " << ranges.at(r) << std::endl;
        std::cout << "spreadsort_times_" << r << " = " << "[";
        for (uint n = 0; n < ns.size() - 1; ++n) {
            std::cout << times[r * ns.size() + n].first << ", ";
        }
        std::cout << times[r * ns.size() + ns.size() - 1].first << "]" << std::endl;
        std::cout << "stdsort_times_" << r << " = " << "[";
        for (uint n = 0; n < ns.size() - 1; ++n) {
            std::cout << times[r * ns.size() + n].second << ", ";
        }
        std::cout << times[r * ns.size() + ns.size() - 1].second << "]" << std::endl;
    }
    return 0;
}