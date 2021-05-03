#include "./../include/PointSet.hpp"

PointSet::PointSet()
{
  dimension = 0;
  points = {};
  MDSubsetGenerator = NULL;
}

PointSet::PointSet(int dimension_, std::vector<Point> points_) 
{
  dimension = dimension_;
  points = points_;
  MDSubsetGenerator = NULL;
}

PointSet::~PointSet()
{
}

Point &PointSet::operator[](int index)
{
  if (index >= points.size() || index < 0)
  {
    std::cout << "PointSet::operator[] - ERROR: Out of range index.\n";
    throw 50;
  }
  return points[index];
}

void PointSet::loadFromFile(std::string filename) 
{
  std::ifstream ifs(filename);
  int pointsNumber;
  std::string line;
  if(!ifs.is_open())
  {
    std::cout << "PointSet::loadFromFile - ERROR: Unable to open file.\n";
    throw 10;
  }
  ifs >> pointsNumber;
  ifs >> dimension;
  std::getline(ifs, line); // Jumps to next line to avoid empty line read.
  for (int i = 0; i < pointsNumber; i++) 
  {
    std::getline(ifs, line);
    replace(line.begin(), line.end(), ',', '.');
    points.push_back(Point(dimension, line));
  }
}

void PointSet::printPoints() 
{
  int numberOfPoints = points.size();
  std::cout << "Number of points: " << numberOfPoints << std::endl;
  std::cout << "Dimension: " << dimension << std::endl;
  for (int i = 0; i < numberOfPoints; i++) 
  {
    points[i].printCoordinates();
  }
}

void PointSet::setMDSubsetGenerator(MDAlgorithm* MDSubsetGenerator_)
{
  if (MDSubsetGenerator != NULL)
  {
    delete MDSubsetGenerator;
  }
  MDSubsetGenerator = MDSubsetGenerator_;
}

PointSet PointSet::generateMDSubset(int subsetSize) 
{
  if (MDSubsetGenerator == NULL)
  {
    std::cout << "PointSet::generateMDSubset - ERROR: MDSubsetGenerator not set\n";
    throw 20;
  }
  else if (subsetSize >= points.size())
  {
    std::cout << "PointSet::generateMDSubset - ERROR: Size of subset is not valid.\n";
    throw 30;
  }
  else
  {
    return MDSubsetGenerator -> run(*this, subsetSize);
  }
}

Point PointSet::getGravityCenter() 
{
  int pointsNumber = points.size();
  std::vector<float> gravityCenterCoordinates(dimension, 0);
  // Add all corresponding point coordinates.
  for (int i = 0; i < pointsNumber; i++) 
  {
    for (int j = 0; j < dimension; j++)
    {
      gravityCenterCoordinates[j] += points[i][j];
    }
  }
  // Divide them by the total of points.
  for (int i = 0; i < dimension; i++)
  {
    gravityCenterCoordinates[i] = gravityCenterCoordinates[i] / pointsNumber;
  }

  return Point(gravityCenterCoordinates);
}

float PointSet::getDiversityValue() 
{
  float diversity = 0;
  int pointsNumber = points.size();
  // Sum of all (unique) distances.
  for (int i = 0; i < pointsNumber; i++)
  {
    for (int j = i + 1; j < pointsNumber; j++) 
    {
      diversity += points[i].getDistanceTo(points[j]);
    }
  } 
  return diversity;
}

int PointSet::getDimension()
{
  return dimension;
}

int PointSet::getSize()
{
  return points.size();
}

Point PointSet::getFarthestPointTo(Point selected)
{
  Point farthest;
  int pointsNumber = points.size();
  float distance, maxDistance = LOWER_DISTANCE_LIMIT;
  for (int i = 0; i < pointsNumber; i++)
  {
    distance = selected.getDistanceTo(points[i]);
    if (distance > maxDistance)
    {
      farthest = points[i];
      maxDistance = distance;
    }
  }
  return farthest;
}

void PointSet::insert(Point toInsert)
{
  points.push_back(toInsert);
}

void PointSet::pop() 
{
  if (points.empty())
  {
    std::cout << "PointSet::pop - ERROR: Points container is empty already.\n";
    throw 60;
  }
  extract(points[0]);
}

void PointSet::extract(Point toExtract)
{
  bool existed = false;
  int pointsNumber = points.size();
  for (int i = 0; i < pointsNumber; i++)
  {
    if (points[i] == toExtract)
    {
      points.erase(points.begin() + i);
      existed = true;
    }
  }
  if (!existed)
  {
    std::cout << "PointSet::extract - WARNING: Extracted element was not found.\n";
  }
}

bool PointSet::belongs(Point possible)
{
  int pointsNumber = points.size();
  for (int i = 0; i < pointsNumber; i++)
  {
    if (points[i] == possible)
    {
      return true;
    }
  }
  return false;
}
