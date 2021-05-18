#include "./../include/Algorithms/BranchAndBound.hpp"

BranchAndBound::BranchAndBound(int strategy_, MDAlgorithm *algorithm_) : strategy(strategy_), algorithm(algorithm_), root(NULL)
{
  generatedNodes = 0;
}

// MODIFICACION EN ESTA FUNCION.
PointSet BranchAndBound::run(PointSet set_, int subsetSize_)
{
  // Set parameters as attributes in order to make them accesible from other
  // functions.
  set = set_;
  subsetSize = subsetSize_;
  lowerBound = algorithm->run(set, subsetSize);
  generatedNodes = 0;

  // Create and branch root node.
  root = new Node();
  for (int i = 0; i < set.getSize(); i++)
  {
    PointSet tempSet;
    tempSet.insert(set[i]);
    Node *child = new Node(tempSet, 1);
    computeUpperBound(child);
    root->addChild(child);
    addToBranchables(child);
    generatedNodes++;
  }

  // Branch all branchable nodes. Since vector is sorted by given criteria, we will branch
  // the first element and then pull it off the list (already branched).
  ///// MODIFICACION /////////
  // Se cambia para que siempre que sea posible, se coga el segundo mejor valor. Es decir, el
  // segundo elemento de la lista.
  while (!branchables.empty())
  {
    if (branchables.size() > 1)
    {
      Node *bestBranchable = branchables[1];
      branchables.erase(branchables.begin() + 1);
      branchNode(bestBranchable);
    }
    else
    {
      Node *bestBranchable = branchables[0];
      branchables.erase(branchables.begin());
      branchNode(bestBranchable);
    }
  }

  // Result will end up in lowerBound attribute.
  return lowerBound;
}

void BranchAndBound::branchNode(Node* parent) 
{
  // Create childs by appending all possible values among candidates.
  // Candidates will be all points that are not selected in parent yet. 
  PointSet selected = parent->getData();
  PointSet candidates = set.substract(selected);
  for (int i = 0; i < candidates.getSize(); i++)
  {
    PointSet tempSet = selected;
    tempSet.insert(candidates[i]);
    Node *child = new Node(tempSet, parent->getDepth() + 1);
    computeUpperBound(child);
    parent->addChild(child);

    // Childs are leaf nodes.
    if (child->getDepth() == subsetSize)
    {
      // Check if a higher lower bound is found to update it and trim the tree.
      if (child->getUpperBound() > lowerBound.getDiversityValue())
      {
        lowerBound = child->getData();
        trim();
      }
    }
    // Childs are not leaf nodes. Add them to branchables if their upper bound
    // is greater than lower bound's diversity value.
    else if (child->getUpperBound() > lowerBound.getDiversityValue())
    {
      addToBranchables(child);
    }

    generatedNodes++;
  }
}

/**
 * Aproach from https://www.uv.es/rmarti/paper/docs/mdp3.pdf method.
 * Page 5 - 8. Proposition 1 and proposition 2.
 * Any solution's Z can be split in three parts: z1, z2 and z3.
 * z1 is the sum of distances between all selected points.
 * z2 is the sum of distances that start at a selected point and end at an unselected one.
 * z3 is the sum of distances between all unselected points.
 * Upper Bound for Z will be found by computing an upper bound for each part, and then
 * adding those three: UBz = UBz1 + UBz2 + UBz3.
 **/
void BranchAndBound::computeUpperBound(Node *nodePointer)
{
  PointSet selected = nodePointer->getData();
  PointSet unselected = set.substract(selected);
  int remainers = subsetSize - selected.getSize();

  //// Z1 will be constant, then its own value will be its upper bound.
  float z1 = selected.getDiversityValue();

  //// Z2 will contain the biggest contributions (respect to the selected ones)
  //// possible from unselected nodes when added to the partial solution.
  float z2 = 0; 
  std::vector<float> zSel;
  bool inserted;

  // Fill zSet values ordering by max to min.
  for (int u = 0; u < unselected.getSize(); u++)
  {
    // zSelValue for unselected[u] will be the sum of distances
    // between him and all selected points.
    float zSelValue = 0;
    for (int s = 0; s < selected.getSize(); s++)
    {
      zSelValue += selected[s].getDistanceTo(unselected[u]);
    }
    // Insert it considering vector must be sorted from high to low.
    inserted = false;
    for (int z = 0; z < zSel.size(); z++)
    {
      if (zSel[z] < zSelValue)
      {
        zSel.insert(zSel.begin() + z, zSelValue);
        inserted = true;
        break;
      }
    }
    if (!inserted)
    {
      zSel.push_back(zSelValue);
    }
  }
  // Fill z2 with most significant contributions.
  for (int r = 0; r < remainers; r++)
  {
    z2 += zSel[r];
  }

  //// Z3 will contain the biggest contributions (respect to the unselected ones)
  //// possible from unselected nodes when added to the partial solution.
  float z3 = 0;
  std::vector<float> zUnsel;  // All possible contributions in z3 context. (sorted high to low)
  std::vector<float> dUnsel;  // There will be one dUnsel vector for each point v of unselected.
                              // It will contain all distances from it to other unselected points. (sorted)

  // Given a point v in unselected.
  for (int u = 0; u < unselected.getSize(); u++)
  {
    dUnsel.clear();
    float dUnselValue;
    inserted = false;

    // Find given v's dUnsel values, and insert them sorted.
    for (int u2 = 0; u2 < unselected.getSize(); u2++)
    {
      if (u != u2)
      {
        dUnselValue = unselected[u].getDistanceTo(unselected[u2]);
        for (int d = 0; d < dUnsel.size(); d++)
        {
          if (dUnsel[d] < dUnselValue)
          {
            dUnsel.insert(dUnsel.begin() + d, dUnselValue);
            inserted = true;
            break;
          }
        }
        if (!inserted)
        {
          dUnsel.push_back(dUnselValue);
        }
      }
    }
    // Now v's zUnselValue is filled by most significant distances.
    float zUnselValue = 0;
    for (int r = 0; r < remainers - 1; r++)
    {
      zUnselValue += dUnsel[r];
    }
    zUnselValue /= 2;

    // Insert zUnselValue considering vector must be sorted from high to low.
    inserted = false;
    for (int z = 0; z < zUnsel.size(); z++)
    {
      if (zUnsel[z] < zUnselValue)
      {
        zUnsel.insert(zUnsel.begin() + z, zUnselValue);
        inserted = true;
        break;
      }
    }
    if (!inserted)
    {
      zUnsel.push_back(zUnselValue);
    }
  }
  // We end up with zUnsel filled with every zUnselValue for every v in unselected.
  // It is also sorted from high to low. So in order to get its most significant 
  // potential contribution, we will add up its most significant potential values.
  for (int r = 0; r < remainers; r++)
  {
    z3 += zUnsel[r];
  }
  
  // Finally we compute Upper Bound of Z by adding its 3 components upper bounds.
  nodePointer->setUpperBound(z1 + z2 + z3);
}

// MODIFICACION EN ESTA FUNCION.
void BranchAndBound::addToBranchables(Node *addable)
{
  bool inserted = false;
  float upperBoundValue;
  int depth;
  switch (strategy)
  {
  // It will insert elements, so they are sorted (min to max) 
  // by their upper bound value.
  case VALUE:
    upperBoundValue = addable->getUpperBound();
    for (int i = 0; i < branchables.size(); i++)
    {
      if (upperBoundValue < branchables[i]->getUpperBound())
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

  // It will insert elements, so they are sorted (min to max)
  // by their depth.
  case DEPTH:
    depth = addable->getDepth();
    for (int i = 0; i < branchables.size(); i++)
    {
      if (depth < branchables[i]->getDepth())
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

  ////// MODIFICACION //////
  // En este caso el vector de nodos a expandir se ordena de mayor a menor cota superior.
  case SECOND_BEST:
    upperBoundValue = addable->getUpperBound();
    for (int i = 0; i < branchables.size(); i++)
    {
      if (upperBoundValue > branchables[i]->getUpperBound())
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

  default:
    std::cout << "BranchAndBound::addToBranchables - ERROR: undefined strategy\n";
    throw 64;
    break;
  }
}

void BranchAndBound::trim()
{
  float lowerBoundValue = lowerBound.getDiversityValue();
  int firstNotToTrim = -1;
  for (int i = 0; i < branchables.size(); i++)
  {
    if (branchables[i]->getUpperBound() <= lowerBoundValue)
    {
      branchables[i]->setTrimmed(true);
    }
    else
    {
      firstNotToTrim = i;
      break;
    }
  }

  // Trim only the ones that are lower than lowerBound.
  if (firstNotToTrim > 0)
  {
    branchables.erase(branchables.begin(), branchables.begin() + firstNotToTrim);
  }
  // Trim all since they are all lower than lowerBound.
  else if (firstNotToTrim < 0)
  {
    branchables.clear();
  }
  // else -> Dont trim any, since firstNotToTrim == 0.
}

int BranchAndBound::getGeneratedNodes()
{
  return generatedNodes;
}
