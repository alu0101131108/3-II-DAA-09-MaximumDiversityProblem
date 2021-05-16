#include "./../include/Algorithms/BranchAndBound.hpp"

BranchAndBound::BranchAndBound(int strategy_, MDAlgorithm *algorithm_) : strategy(strategy_), algorithm(algorithm_), root(NULL)
{}

PointSet BranchAndBound::run(PointSet set_, int subsetSize_)
{
  // Set parameters as attributes in order to make them accesible from other
  // functions.
  set = set_;
  subsetSize = subsetSize_;
  lowerBound = algorithm->run(set, subsetSize);
  std::cout << "first lower bound: " << lowerBound.getDiversityValue() << std::endl;

  // Create and branch root node.
  root = new Node();
  for (int i = 0; i < set.getSize(); i++)
  {
    PointSet tempSet;
    tempSet.insert(set[i]);
    Node *child = new Node(tempSet, 1);
    fillNode(child);
    root->addChild(child);
    addToBranchables(child);
  }

  // Branch any nodes created. Every time a leaf node is reached, lowerBound
  // will get updated and non usefull branches will be trimmed.
  int count = 0;
  while (!branchables.empty())
  {
    // std::cout << "lower bound value: " << lowerBound.getDiversityValue() << std::endl;
    for (int i = 0; i < branchables.size(); i++)
    {
      std::cout << "[" << branchables[i]->getDiversityValue() << "]";
    }
    std::cout << std::endl;
    
    count++;
    Node* bestBranchable = branchables[0];
    branchables.erase(branchables.begin());
    branchNode(bestBranchable);
  }
  //std::cout << "Branches: " << count << std::endl;
  //root->draw();

  // Result will end up in lowerBound attribute.
  return lowerBound;
}

void BranchAndBound::branchNode(Node* parent) 
{
  // Make a copy of the parent and unfill non locked points.
  PointSet nodeSet = parent->getData();
  int depth = parent->getDepth();
  int fillersNumber = subsetSize - depth;
  nodeSet.popBack(fillersNumber);

  // Create childs by appending all possible values among candidates.
  // Candidates will be all points that are not locked in parent yet. 
  PointSet candidates = set.substract(nodeSet);
  for (int i = 0; i < candidates.getSize(); i++)
  {
    PointSet tempSet = nodeSet;
    tempSet.insert(candidates[i]);
    Node* child = new Node(tempSet, depth + 1);
    fillNode(child);
    parent->addChild(child);

    // Childs are leaf nodes.
    if (child->getDepth() == subsetSize)
    {
      // Check if a higher lower bound is found to update it and trim the tree.
      if (child->getDiversityValue() > lowerBound.getDiversityValue())
      {
        lowerBound = child->getData();
        trim();
      }
    }
    // Childs are not leaf nodes. Add them to branchables if they have greater z value than lower bound.
    else if (child->getDiversityValue() > lowerBound.getDiversityValue())
    {
      std::cout << "added-> " << child->getDiversityValue() << " > " << lowerBound.getDiversityValue() << std::endl;
      addToBranchables(child);
    }
  }
}

void BranchAndBound::fillNode(Node *fillable)
{
  PointSet nodeSet = fillable->getData();
  PointSet candidates = set.substract(nodeSet);
  Point gravityCenter, farthest;
  int pointsToFill = subsetSize - nodeSet.getSize();
  for (int i = 0; i < pointsToFill; i++)
  {
    gravityCenter = nodeSet.getGravityCenter();
    farthest = candidates.getFarthestPointTo(gravityCenter);
    nodeSet.insert(farthest);
  }
  fillable->setData(nodeSet);
}

void BranchAndBound::addToBranchables(Node *addable)
{
  int diversity = addable->getDiversityValue();
  bool inserted = false;
  switch (strategy)
  {
  case VALUE:
    for (int i = 0; i < branchables.size(); i++)
    {
      if (diversity < branchables[i]->getDiversityValue())
      {
        branchables.insert(branchables.begin() + i, addable);
        inserted = true;
        break;
      }   
    }
    if (!inserted)
    {
      branchables.push_back(addable);
    }
    break;

  case DEPTH:
    std::cout << "BranchAndBound::addToBranchables - Not implemented\n";
    throw 98;
    break;

  default:
    std::cout << "BranchAndBound::addToBranchables - ERROR: undefined strategy\n";
    throw 64;
    break;
  }
}

// Can be updated, if vector is sorted no need to iterate over all values.
void BranchAndBound::trim()
{
  float lowerBoundValue = lowerBound.getDiversityValue();
  for (int i = 0; i < branchables.size(); i++)
  {
    if (lowerBoundValue >= branchables[i]->getDiversityValue())
    {
      branchables[i]->setTrimmed(true);
      branchables.erase(branchables.begin() + i);
      // std::cout << "Node trimmed" << std::endl;
    }
  }
}