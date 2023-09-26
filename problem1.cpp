#include "rk4_adaptive.h"

#include <cmath>
#include <fstream>

int main() {
  auto f_factory = [](double a, double b) {
    return [a, b](double x, const std::vector<double> &y) {
      std::vector<double> result(2);
      result[0] = a - (1.0 + b) * y[0] + y[0] * y[0] * y[1];
      result[1] = b * y[0] - y[0] * y[0] * y[1];
      return result;
    };
  };

  auto f = f_factory(1.0, 1.0);

  auto stop = [](double x, const std::vector<double> &y) { return x > 100; };

  rk4_adaptive rka(2, 1e-10, 1e-10);
  double h = 0.01;
  auto y = rka.integrate(f, stop, h, 0.0, {2.0, 0.0});

  // b = 1 case
  std::ofstream output1("brusselator-b1.csv");
  for (int i = 0; i < rka.xs.size(); i++) {
    output1 << rka.xs[i] << "," << rka.result[i][0] << ","
                << rka.result[i][1] << std::endl;
  }
  output1.close();

  // b = 2 case
  auto f2 = f_factory(1.0, 2.0);
  y = rka.integrate(f2, stop, h, 0.0, {2.0, 0.0});

  std::ofstream output2("brusselator-b2.csv");
  for (int i = 0; i < rka.xs.size(); i++) {
    output2 << rka.xs[i] << "," << rka.result[i][0] << ","
                << rka.result[i][1] << std::endl;
  }
  output2.close();

  // b = 3 case
  auto f3 = f_factory(1.0, 3.0);
  y = rka.integrate(f3, stop, h, 0.0, {2.0, 0.0});

  std::ofstream output3("brusselator-b3.csv");
  for (int i = 0; i < rka.xs.size(); i++) {
    output3 << rka.xs[i] << "," << rka.result[i][0] << ","
                << rka.result[i][1] << std::endl;
  }
  output3.close();

  return 0;
}
