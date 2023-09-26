#include "rk4_adaptive.h"

#include <cmath>
#include <fstream>

int main() {
  double sigma = 10.0;
  double beta = 8.0 / 3.0;
  double rho = 28.0;

  double x0 = 1.0;
  double y0 = 1.0;
  double z0 = 1.0;

  auto f = [sigma, beta, rho](double x, const std::vector<double> &y) {
    std::vector<double> result(3);
    result[0] = sigma * (y[1] - y[0]);
    result[1] = y[0] * (rho - y[2]) - y[1];
    result[2] = y[0] * y[1] - beta * y[2];
    return result;
  };

  auto stop = [](double x, const std::vector<double> &y) { return x > 200; };

  rk4_adaptive rka(3, 1e-10, 1e-10);
  double h = 0.01;
  auto y = rka.integrate(f, stop, h, 0.0, {x0, y0, z0});

  std::ofstream output_file("lorenz.csv");
  for (int i = 0; i < rka.xs.size(); i++) {
    output_file << rka.xs[i] << "," << rka.result[i][0] << ","
                << rka.result[i][1] << "," << rka.result[i][2] << std::endl;
  }
  output_file.close();

  return 0;
}
