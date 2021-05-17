#include "./../include/Node.hpp"

Node::Node()
{
  depth = 0;
  data = PointSet();
  trimmed = false;
  upperBound = -1;
}

Node::Node(PointSet data_, int depth_) : data(data_), depth(depth_)
{
  trimmed = false;
  upperBound = -1;
}

Node::~Node()
{
}

void Node::addChild(Node *child)
{
  childs.push_back(child);
}

std::vector<Node*> Node::getChilds()
{
  return childs;
}

float Node::getDiversityValue() 
{
  return data.getDiversityValue();
}

int Node::getDepth()
{
  return depth;
}

void Node::setDepth(int newDepth)
{
  depth = newDepth;
}

PointSet Node::getData()
{
  return data;
}

void Node::setData(PointSet data_)
{
  data = data_;
}

void Node::draw()
{
  std::string tab = std::string(depth * 2, ' ');
  std::string stringData = data.toString();
  std::string trimmedStr = trimmed ? "TRIMMED -" : "";
  std::cout << tab << trimmedStr << "Node (" << depth << ") - " << childs.size() << " - " << upperBound << std::endl;
  std::cout << tab << stringData << std::endl;
  for (int i = 0; i < childs.size(); i++)
  {
    childs[i]->draw();
  }
}

void Node::setTrimmed(bool state)
{
  trimmed = state;
}

float Node::getUpperBound() 
{
  return upperBound;
}

void Node::setUpperBound(float upperBound_) 
{
  upperBound = upperBound_;
}

