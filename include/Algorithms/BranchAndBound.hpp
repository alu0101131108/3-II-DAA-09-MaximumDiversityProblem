#ifndef __BRANCHANDBOUND_H__
#define __BRANCHANDBOUND_H__

#include "./MDAlgorithm.hpp"
#include "./../Node.hpp"
#include <vector>
#include <iostream>

enum Strategy
{
  VALUE,
  DEPTH
};

class BranchAndBound : public MDAlgorithm
{
private:
  int strategy;
  MDAlgorithm* algorithm;
  std::vector<Node*> branchables;
  PointSet set;
  int subsetSize;
  PointSet lowerBound;
  Node* root;

public:
  BranchAndBound(int strategy_, MDAlgorithm* algorithm_);
  PointSet run(PointSet set_, int subsetSize_);
  void branchNode(Node *branchable);
  void fillNode(Node* fillable);
  void addToBranchables(Node* addable);
  void trim();
};


#endif // __BRANCHANDBOUND_H__