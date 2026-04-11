#include <iostream>
#include <limits>
#include <Kokkos_Core.hpp>


int main(int argc, char* argv[]) {
    Kokkos::initialize(argc, argv); 
    {
        constexpr int N = 20;

        Kokkos::View<double*> x("x", N);

        Kokkos::parallel_for("init", N, KOKKOS_LAMBDA(int i){
            x(i) = i*i - 2*i;
        });
        
        auto x_host = Kokkos::create_mirror_view(x);
        Kokkos::deep_copy(x_host, x);

        for (int i = 0; i < 5; i++) {
            std::cout << "x(" << i << "): " << x_host(i) << std::endl;
        }
        std::cout << "..." << std::endl;
        std::cout << "x(" << N-1 << "): " << x_host(N-1) << std::endl;        

        double sum = 0.0;
        
        Kokkos::parallel_reduce(
            "sum", N, KOKKOS_LAMBDA(int i, double& local_sum) {
                local_sum += x(i);
            },
        sum
        );

        std::cout << "sum of x_i: " << sum << std::endl;

        double max_x = std::numeric_limits<double>::lowest();

        Kokkos::parallel_reduce(
            "max_x", N, KOKKOS_LAMBDA(const int i, double& local_max) {
                if (x(i) > local_max) {
                    local_max = x(i);
                }
            },
            Kokkos::Max<double>(max_x)
        );

        std::cout << "max of x_i: " << max_x << std::endl;

    }
    Kokkos::finalize();
    return 0;
}
