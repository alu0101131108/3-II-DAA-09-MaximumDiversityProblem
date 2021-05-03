#include "./../include/PointSet.hpp"
#include "./../include/Algorithms/ConstructiveGreedy.hpp"
#include "./../include/Algorithms/LocalSearch.hpp"
#include <chrono>

std::string tab(std::string str, int size)
{
  int nSpaces = size - str.size();
  std::string extra(nSpaces, ' ');
  return str + extra;
}

std::string tab(int integer, int size)
{
  std::string str = std::to_string(integer);
  int nSpaces = size - str.size();
  std::string extra(nSpaces, ' ');
  return str + extra;
}

int main(int argc, char** argv) 
{
  if (argc != 2)
  {
    std::cout << "main() - ERROR: 1 arguments expected.\n";
    throw 60;
  }

  PointSet set, subset;
  std::vector<int> nValues = {15, 20, 30};
  std::vector<int> kValues = {2, 3};
  std::vector<int> mValues = {2, 3, 4, 5};
  std::chrono::time_point<std::chrono::system_clock> start, end;
  std::chrono::duration<double> elapsed_seconds;
  std::string diversity, cpu;
  argv[1] == 0 ? set.setMDSubsetGenerator(new ConstructiveGreedy()) : set.setMDSubsetGenerator(new LocalSearch());

  // Table headers.
  std::cout << std::string(140, '=') << std::endl;
  std::cout << tab("n", 5) + tab("K", 5) + tab("m", 5) + tab("z", 15) + tab("S", 100) + tab("CPU (s)", 10) << std::endl;
  std::cout << std::string(140, '=') << std::endl;
  
  // Table values.
  for (int k = 0; k < kValues.size(); k++)
  {
    for (int n = 0; n < nValues.size(); n++)
    {
      set.loadFromFile("./../input-problems/max_div_" + std::to_string(nValues[n]) + "_" + std::to_string(kValues[k]) + ".txt");
      for (int m = 0; m < mValues.size(); m++)
      {
        start = std::chrono::high_resolution_clock::now();
        subset = set.generateMDSubset(mValues[m]);
        end = std::chrono::high_resolution_clock::now();
        elapsed_seconds = end - start;
        cpu = std::to_string(elapsed_seconds.count());
        diversity = std::to_string(subset.getDiversityValue());
        std::cout << tab(nValues[n], 5) + tab(kValues[k], 5) + tab(mValues[m], 5) + tab(diversity, 15);
        std::cout << tab(subset.toString(), 100) + tab(cpu, 10) << std::endl;
      }
      std::cout << std::string(140, '-') << std::endl;
    }
  }

  return 0;
}
  // std::cout << "--------ConstructiveGreedy----------" << std::endl;
  // set.setMDSubsetGenerator(new ConstructiveGreedy());
  // subset = set.generateMDSubset(2);
  // std::cout << "2: Z Value: " << subset.getDiversityValue() << std::endl;
  // subset = set.generateMDSubset(3);
  // std::cout << "3: Z Value: " << subset.getDiversityValue() << std::endl;
  // subset = set.generateMDSubset(4);
  // std::cout << "4: Z Value: " << subset.getDiversityValue() << std::endl;
  // subset = set.generateMDSubset(5);
  // std::cout << "5: Z Value: " << subset.getDiversityValue() << std::endl;
  // std::cout << "\n------------LocalSearch-------------" << std::endl;
  // set.setMDSubsetGenerator(new LocalSearch());
  // subset = set.generateMDSubset(2);
  // std::cout << "2: Z Value: " << subset.getDiversityValue() << std::endl;
  // subset = set.generateMDSubset(3);
  // std::cout << "3: Z Value: " << subset.getDiversityValue() << std::endl;
  // subset = set.generateMDSubset(4);
  // std::cout << "4: Z Value: " << subset.getDiversityValue() << std::endl;
  // subset = set.generateMDSubset(5);
  // std::cout << "5: Z Value: " << subset.getDiversityValue() << std::endl;
  // subset.printPoints();