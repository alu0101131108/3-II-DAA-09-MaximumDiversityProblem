#include "./../include/Point.hpp"

Point::Point()
{
  dimension = 0;
  coordinates = {};
}

Point::Point(std::vector<float> coordinates_)
{
  coordinates = coordinates_;
  dimension = coordinates.size();
}

Point::Point(int dimension_, std::string stringCoordinates) 
{
  dimension = dimension_;
  std::istringstream iss(stringCoordinates);
  float coordinate;
  for (int i = 0; i < dimension; i++)
  {
    iss >> coordinate;
    coordinates.push_back(coordinate);
  }
}

Point::~Point()
{
}

std::vector<float> Point::getCoordinates() 
{
  return coordinates;
}

void Point::setCoordinates(std::vector<float> coordinates_) 
{
  coordinates = coordinates_;
}

void Point::printCoordinates() 
{
  for (int i = 0; i < dimension; i++)
  {
    std::cout << coordinates[i] << " ";
  }
  std::cout << std::endl;
}

float Point::getDistanceTo(Point other)
{
  float distance = 0;
  for (int i = 0; i < dimension; i++)
  {
    distance += pow(coordinates[i] - other[i], 2);
  }
  distance = abs(sqrt(distance));
  return distance;
}

bool operator==(Point &left, Point &right)
{
  if (left.coordinates.size() != right.coordinates.size())
  {
    return false;
  }

  for (int i = 0; i < left.coordinates.size(); i++)
  {
    if (left[i] != right[i])
    {
      return false;
    }
  }
  
  return true;
}

float & Point::operator[](int dim) 
{
  if (dim >= dimension)
  {
    std::cout << "Point::operator[] - ERROR: Dimension does not exist.\n";
    throw 50;
  }
  return coordinates[dim];
}

