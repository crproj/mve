#include <vector>

using namespace std;

class Quadrangle {

private:
  unsigned int maxNumberVerts;
  unsigned int numberVerts;
  int id;

  
public:
  Quadrangle(int id);
  Quadrangle();
  bool isInside( float x, float y, float width, float height );
  void addPoint( float x, float y);
  void setID(int id);
  bool isComplete();
  int getSize();
  int getID() const;
  vector<float> xCoords;
  vector<float> yCoords;
};
