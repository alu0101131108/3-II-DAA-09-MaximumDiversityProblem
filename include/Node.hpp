#ifndef __NODE_H__
#define __NODE_H__

#include <vector>
#include "./PointSet.hpp"

class Node
{
private:
  PointSet data;
  std::vector<Node*> childs;
  int depth;
  bool trimmed;
  float upperBound;
  
  
public:
  Node();
  Node(PointSet data_, int depth_);
  ~Node();
  void addChild(Node* child);
  std::vector<Node*> getChilds();
  float getDiversityValue();
  int getDepth();
  void setDepth(int newDepth);
  PointSet getData();
  void setData(PointSet data_);
  void draw();
  void setTrimmed(bool state);
  float getUpperBound();
  void setUpperBound(float upperBound_);
};



#endif // __NODE_H__