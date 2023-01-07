#include "Vector.h"
#include <stdlib.h> // ? Ask for dynamic memory operations
#include <math.h>

struct Vector_t {
  double x;
  double y;
  double z;
};

// ? Constructor
Vector_t * Vector_Constructor(Point_t const * const begin, Point_t const * const end)
{
  if(!begin || !end) return NULL;

  Vector_t * const obj = (Vector_t*)malloc(sizeof(Vector_t));

  // Check if dynamic memory is successed.
  if(!obj) return NULL;

  // Initialize members
  obj->x = Point_get_Coordinate(end, PointX) - Point_get_Coordinate(begin, PointX);
  obj->y = Point_get_Coordinate(end, PointY) - Point_get_Coordinate(begin, PointY);
  obj->z = Point_get_Coordinate(end, PointZ) - Point_get_Coordinate(begin, PointZ);

  return obj;
}

// ? Destructor
task_t Vector_Destructor(Vector_t * const self)
{
  if(!self) return Fail;

  free(self);

  return Success;
}

// ? setters
task_t Vector_set_Coordinate(Vector_t * const self, Vector_Coordinate_Enum coordinate, double value)
{
  if(!self) return Fail;

  switch(coordinate) {
    case VectorX: { self->x = value; return Success; }
    case VectorY: { self->y = value; return Success; }
    case VectorZ: { self->z = value; return Success; }
    default:      { return Fail; }
  }
}

// ? getters 
double Vector_get_Coordinate(Vector_t const * const self, Vector_Coordinate_Enum coordinate)
{
  if(!self) return 0.0f;

  switch(coordinate) {
    case VectorX: { return self->x; }
    case VectorY: { return self->y; }
    case VectorZ: { return self->z; }
    default:      { return 0.0f;    }
  }
}

// ? general member functions
double Vector_Length(Vector_t const * const self)
{
  return self ? sqrt( self->x * self->x + self->y * self->y + self->z * self->z ) : 0.0f ;
}

double Vector_CoordinateAngle(Vector_t const * const self, Vector_Coordinate_Enum coordinate)
{
  if(!self) return 0.0f;

  switch(coordinate) {
    case VectorX: { return acos( self->x / Vector_Length(self) ); }
    case VectorY: { return acos( self->y / Vector_Length(self) ); }
    case VectorZ: { return acos( self->z / Vector_Length(self) ); }
    default:      { return 0.0f; }
  }
}

double Vector_PlaneAngle(Vector_t const * const self, Vector_Plane_Enum plane)
{
  if(!self) return 0.0f;

  switch(plane) {
    case PlaneXY: { return asin( self->z / Vector_Length(self) ); }
    case PlaneXZ: { return asin( self->y / Vector_Length(self) ); }
    case PlaneYZ: { return asin( self->x / Vector_Length(self) ); }
    default:      { return 0.0f; }
  }
}
