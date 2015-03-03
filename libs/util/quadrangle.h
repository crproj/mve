#include <vector>

using namespace std;

class Quadrangle {

private:
  unsigned int numberVerts;
  int id;
  bool complete;

  
public:
  Quadrangle(int id);
  Quadrangle();
  bool isInside( float x, float y, float width, float height );
  void addPoint( float x, float y);
  void setID(int id);
  void setComplete();
  bool isComplete();
  unsigned int getSize();
  int getID();
  vector<float> xCoords;
  vector<float> yCoords;
};
