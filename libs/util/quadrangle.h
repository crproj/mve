#include <vector>

using namespace std;

class Quadrangle {

private:
  unsigned int maxNumberVerts;
  unsigned int numberVerts;
  unsigned int id;

  
public:
  Quadrangle(int id);
  Quadrangle();
  bool isInside( int x, int y );
  void addPoint( int x, int y);
  void setID(int id);
  bool isComplete();
  int getSize();
  int getID();
  vector<int> xCoords;
  vector<int> yCoords;
};
