#include <iostream>
#include <math.h>
int get_change(int m) {
  
  return floor((double)m/10) + floor((double)(m%10)/5) + (m%5);
}

int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}
