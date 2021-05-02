#include "./../include/PointSet.hpp"
#include "./../include/Algorithms/ConstructiveGreedy.hpp"

int main() 
{
  PointSet set, subset;
  set.loadFromFile("./../input-problems/max_div_30_3.txt");
  set.setMDSubsetGenerator(new ConstructiveGreedy());
  subset = set.generateMDSubset(2);
  subset.printPoints();
  // std::cout << "2: Z Value: " << subset.getDiversityValue() << std::endl;
  // subset = set.generateMDSubset(3);
  // std::cout << "3: Z Value: " << subset.getDiversityValue() << std::endl;
  // subset = set.generateMDSubset(4);
  // std::cout << "4: Z Value: " << subset.getDiversityValue() << std::endl;
  // subset = set.generateMDSubset(5);
  // std::cout << "5: Z Value: " << subset.getDiversityValue() << std::endl;
  return 0;
}