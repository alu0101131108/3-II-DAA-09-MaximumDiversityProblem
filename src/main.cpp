#include "./../include/PointSet.hpp"
#include "./../include/Algorithms/ConstructiveGreedy.hpp"
#include "./../include/Algorithms/LocalSearch.hpp"

std::string tab(std::string str, int size)
{
  int nSpaces = size - str.size();
  std::string extra(nSpaces, ' ');
  return str + extra;
}

int main() 
{
  PointSet set, subset;
  set.loadFromFile("./../input-problems/max_div_15_2.txt");

  std::cout << "--------ConstructiveGreedy----------" << std::endl;
  set.setMDSubsetGenerator(new ConstructiveGreedy());
  subset = set.generateMDSubset(2);
  std::cout << "2: Z Value: " << subset.getDiversityValue() << std::endl;
  subset = set.generateMDSubset(3);
  std::cout << "3: Z Value: " << subset.getDiversityValue() << std::endl;
  subset = set.generateMDSubset(4);
  std::cout << "4: Z Value: " << subset.getDiversityValue() << std::endl;
  subset = set.generateMDSubset(5);
  std::cout << "5: Z Value: " << subset.getDiversityValue() << std::endl;

  std::cout << "\n------------LocalSearch-------------" << std::endl;
  set.setMDSubsetGenerator(new LocalSearch());
  subset = set.generateMDSubset(2);
  std::cout << "2: Z Value: " << subset.getDiversityValue() << std::endl;
  subset = set.generateMDSubset(3);
  std::cout << "3: Z Value: " << subset.getDiversityValue() << std::endl;
  subset = set.generateMDSubset(4);
  std::cout << "4: Z Value: " << subset.getDiversityValue() << std::endl;
  subset = set.generateMDSubset(5);
  std::cout << "5: Z Value: " << subset.getDiversityValue() << std::endl;

  // subset.printPoints();
  return 0;
}