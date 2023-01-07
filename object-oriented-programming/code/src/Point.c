#include "Point.h"
#include <stdlib.h> // ? Ask for dynamic memory operations

struct Point_t {
  double x;
  double y;
  double z;
};

// ? Constructor
Point_t * Point_Constructor(double x, double y, double z)
{
  Point_t * const obj = (Point_t*)malloc(sizeof(Point_t));

  // Check if dynamic memory is successed.
  if(!obj) return NULL;

  // Initialize members
  obj->x = x;
  obj->y = y;
  obj->z = z;

  return obj;
}

// ? Destructor
task_t Point_Destructor(Point_t * const self)
{
  if(!self) return Fail;

  free(self);

  return Success;
}

// ? setters
task_t Point_set_Coordinate(Point_t * const self, Point_Coordinate_Enum coordinate, double value)
{
  if(!self) return Fail;

  switch(coordinate) {
    case PointX: { self->x = value; return Success; }
    case PointY: { self->y = value; return Success; }
    case PointZ: { self->z = value; return Success; }
    default:     { return Fail; }
  }
}

// ? getters 
double Point_get_Coordinate(Point_t const * const self, Point_Coordinate_Enum coordinate)
{
  if(!self) return 0.0f;

  switch(coordinate) {
    case PointX:  { return self->x; }
    case PointY:  { return self->y; }
    case PointZ:  { return self->z; }
    default:      { return 0.0f;    }
  }
}
