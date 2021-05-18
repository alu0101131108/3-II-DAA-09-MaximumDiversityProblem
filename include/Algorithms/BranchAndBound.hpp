#ifndef __BRANCHANDBOUND_H__
#define __BRANCHANDBOUND_H__

#include "./MDAlgorithm.hpp"
#include "./../Node.hpp"
#include <vector>
#include <iostream>

enum Strategy
{
  VALUE,
  DEPTH,
  SECOND_BEST // MODIFICACION
};

class BranchAndBound : public MDAlgorithm
{
private:
  MDAlgorithm* algorithm;
  int strategy;
  int subsetSize;
  int generatedNodes;
  PointSet set;
  PointSet lowerBound;
  Node* root;
  std::vector<Node*> branchables;

public:
  BranchAndBound(int strategy_, MDAlgorithm* algorithm_);
  PointSet run(PointSet set_, int subsetSize_);
  void branchNode(Node *branchable);
  void computeUpperBound(Node* fillable);
  void addToBranchables(Node* addable);
  void trim();
  int getGeneratedNodes();
};


#endif // __BRANCHANDBOUND_H__