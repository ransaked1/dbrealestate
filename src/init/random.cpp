#include <random>
#include <chrono>

using namespace std;

// Generate random seed based on system clock //
unsigned gen_seed()
{
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  return seed;
}

// Randomly generate retail state //
string gen_status()
{
  srand(gen_seed());
  int n = rand() % 2;
  if (n == 1)
  return "sell";
  else if (n == 0)
  return "buy;";
  
  return "sell";
}
