#include <vector>

using namespace std;

class Quadrangle {

private:
  unsigned int maxNumberVerts;
  unsigned int numberVerts;
  unsigned int id;

  
public:
  Quadrangle(int id);
  bool isInside( int x, int y );
  void addPoint( int x, int y);
  bool isComplete();
  int getSize();
  vector<int> xCoords;
  vector<int> yCoords;
};
