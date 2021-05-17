#include "./../include/PointSet.hpp"
#include "./../include/Algorithms/ConstructiveGreedy.hpp"
#include "./../include/Algorithms/LocalSearch.hpp"
#include "./../include/Algorithms/Grasp.hpp"
#include "./../include/Algorithms/BranchAndBound.hpp"
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
  srand(time(NULL));
  PointSet set, subset;
  BranchAndBound *branchAndBound;

  std::vector<int> nValues = {15, 20, 30};
  std::vector<int> kValues = {2, 3};
  std::vector<int> mValues = {2, 3, 4, 5};
  std::vector<MDAlgorithm*> algorithms = {new ConstructiveGreedy(), new Grasp(10, 2, ALL)};
  std::vector<int> strategys {VALUE, DEPTH};

  std::chrono::time_point<std::chrono::system_clock> start, end;
  std::chrono::duration<double> elapsed_seconds;
  std::string diversity, cpu, nodes;
  std::string path = "/home/sebas/ULL/3º/cuatri2/daa/08-MaximumDiversityProblem/input-problems/";


  for (int a = 0; a < algorithms.size(); a++)
  {
    for (int s = 0; s < strategys.size(); s++)
    {
      // Table headers.
      std::cout << std::endl << std::endl;
      std::cout << "a: " << a << "    s: " << s << std::endl;
      std::cout << std::string(150, '=') << std::endl;
      std::cout << tab("n", 5) + tab("K", 5) + tab("m", 5) + tab("z", 15) + tab("S", 100) + tab("CPU (s)", 10) + tab("Nodes", 10) << std::endl;
      std::cout << std::string(150, '=') << std::endl;

      for (int k = 0; k < kValues.size(); k++)
      {
        for (int n = 0; n < nValues.size(); n++)
        {
          set.loadFromFile(path + "max_div_" + std::to_string(nValues[n]) + "_" + std::to_string(kValues[k]) + ".txt");
          for (int m = 0; m < mValues.size(); m++)
          {
            // Table values.
            branchAndBound = new BranchAndBound(strategys[s], algorithms[a]);
            set.setMDSubsetGenerator(branchAndBound);
            start = std::chrono::high_resolution_clock::now();
            subset = set.generateMDSubset(mValues[m]);
            end = std::chrono::high_resolution_clock::now();
            elapsed_seconds = end - start;
            cpu = std::to_string(elapsed_seconds.count());
            nodes = std::to_string(branchAndBound->getGeneratedNodes());
            diversity = std::to_string(subset.getDiversityValue());
            std::cout << tab(nValues[n], 5) + tab(kValues[k], 5) + tab(mValues[m], 5) + tab(diversity, 15);
            std::cout << tab(subset.toString(), 100) + tab(cpu, 10) + tab(nodes, 10) << std::endl;
          }
          std::cout << std::string(150, '-') << std::endl;
        }
      }
    }
  }

  return 0;
}

//////////////////////////////////////////////////////////
// Table for Constructive Greedy and Local Search.
//////////////////////////////////////////////////////////
// int main(int argc, char **argv)
// {
//   srand(time(NULL));

//   if (argc != 2)
//   {
//     std::cout << "main() - ERROR: 1 arguments expected.\n";
//     throw 60;
//   }

//   PointSet set, subset;
//   std::vector<int> nValues = {15, 20, 30};
//   std::vector<int> kValues = {2, 3};
//   std::vector<int> mValues = {2, 3, 4, 5};
//   std::chrono::time_point<std::chrono::system_clock> start, end;
//   std::chrono::duration<double> elapsed_seconds;
//   std::string diversity, cpu;
//   argv[1] == 0 ? set.setMDSubsetGenerator(new ConstructiveGreedy()) : set.setMDSubsetGenerator(new LocalSearch());

//   // Table headers.
//   std::cout << std::string(140, '=') << std::endl;
//   std::cout << tab("n", 5) + tab("K", 5) + tab("m", 5) + tab("z", 15) + tab("S", 100) + tab("CPU (s)", 10) << std::endl;
//   std::cout << std::string(140, '=') << std::endl;

//   // Table values.
//   for (int k = 0; k < kValues.size(); k++)
//   {
//     for (int n = 0; n < nValues.size(); n++)
//     {
//       set.loadFromFile("./../input-problems/max_div_" + std::to_string(nValues[n]) + "_" + std::to_string(kValues[k]) + ".txt");
//       for (int m = 0; m < mValues.size(); m++)
//       {
//         start = std::chrono::high_resolution_clock::now();
//         subset = set.generateMDSubset(mValues[m]);
//         end = std::chrono::high_resolution_clock::now();
//         elapsed_seconds = end - start;
//         cpu = std::to_string(elapsed_seconds.count());
//         diversity = std::to_string(subset.getDiversityValue());
//         std::cout << tab(nValues[n], 5) + tab(kValues[k], 5) + tab(mValues[m], 5) + tab(diversity, 15);
//         std::cout << tab(subset.toString(), 100) + tab(cpu, 10) << std::endl;
//       }
//       std::cout << std::string(140, '-') << std::endl;
//     }
//   }

//   return 0;
// }
//////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////
// Table for Grasp Search.
/////////////////////////////////////////////////////////////
// int main(int argc, char **argv)
// {
//   srand(time(NULL));

//   PointSet set, subset;

//   std::vector<int> nValues = {15, 20, 30};
//   std::vector<int> kValues = {2, 3};
//   std::vector<int> mValues = {2, 3, 4, 5};
//   std::vector<int> iterations = {10, 20};
//   std::vector<int> lrcSizes = {2, 3};

//   std::chrono::time_point<std::chrono::system_clock> start, end;
//   std::chrono::duration<double> elapsed_seconds;
//   std::string diversity, cpu;

//   // Table.
//   for (int k = 0; k < kValues.size(); k++)
//   {
//     // Table headers.
//     std::cout << std::endl
//               << std::endl;
//     std::cout << std::string(150, '=') << std::endl;
//     std::cout << tab("n", 5) + tab("K", 5) + tab("m", 5) + tab("It", 5) + tab("LRC", 5) + tab("z", 15) + tab("S", 100) + tab("CPU (s)", 10) << std::endl;
//     std::cout << std::string(150, '=') << std::endl;
//     for (int n = 0; n < nValues.size(); n++)
//     {
//       set.loadFromFile("./../input-problems/max_div_" + std::to_string(nValues[n]) + "_" + std::to_string(kValues[k]) + ".txt");
//       for (int m = 0; m < mValues.size(); m++)
//       {
//         for (int it = 0; it < iterations.size(); it++)
//         {
//           for (int lrc = 0; lrc < lrcSizes.size(); lrc++)
//           {
//             // Table values.
//             set.setMDSubsetGenerator(new Grasp(iterations[it], lrcSizes[lrc], NO_PROGRESS));
//             start = std::chrono::high_resolution_clock::now();
//             subset = set.generateMDSubset(mValues[m]);
//             end = std::chrono::high_resolution_clock::now();
//             elapsed_seconds = end - start;
//             cpu = std::to_string(elapsed_seconds.count());
//             diversity = std::to_string(subset.getDiversityValue());
//             std::cout << tab(nValues[n], 5) + tab(kValues[k], 5) + tab(mValues[m], 5) + tab(iterations[it], 5) + tab(lrcSizes[lrc], 5);
//             std::cout << tab(diversity, 15) + tab(subset.toString(), 100) + tab(cpu, 10) << std::endl;
//           }
//         }
//       }
//       std::cout << std::string(150, '-') << std::endl;
//     }
//   }

//   return 0;
// }
/////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////
// Concrete execution of branch and bound.
/////////////////////////////////////////////////////////////
// int main(int argc, char **argv)
// {
//   srand(time(NULL));
//   PointSet set, subset;
//   std::chrono::time_point<std::chrono::system_clock> start, end;
//   std::chrono::duration<double> elapsed_seconds;
//   std::string diversity, cpu;

//   // Values.
//   int n = 30, k = 3, it = 20, lrc = 2, m = 5;

//   // Table headers.
//   // std::cout << std::endl << std::endl;
//   // std::cout << std::string(150, '=') << std::endl;
//   // std::cout << tab("n", 5) + tab("K", 5) + tab("m", 5) + tab("It", 5) + tab("LRC", 5) + tab("z", 15) + tab("S", 100) + tab("CPU (s)", 10) << std::endl;
//   // std::cout << std::string(150, '=') << std::endl;

//   // Execution.
//   set.loadFromFile("/home/sebas/ULL/3º/cuatri2/daa/08-MaximumDiversityProblem/input-problems/max_div_30_3.txt");
//   set.setMDSubsetGenerator(new BranchAndBound(VALUE, new ConstructiveGreedy())); // new Grasp(it, lrc, ALL)
//   start = std::chrono::high_resolution_clock::now();
//   subset = set.generateMDSubset(m);
//   end = std::chrono::high_resolution_clock::now();
//   elapsed_seconds = end - start;
//   cpu = std::to_string(elapsed_seconds.count());
//   diversity = std::to_string(subset.getDiversityValue());
//   std::cout << tab(n, 5) + tab(k, 5) + tab(m, 5) + tab(it, 5) + tab(lrc, 5);
//   std::cout << tab(diversity, 15) + tab(subset.toString(), 100) + tab(cpu, 10) << std::endl;

//   return 0;
// }
////////////////////////////////////////////////////////////