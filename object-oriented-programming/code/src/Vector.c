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
  
  const Point_refs_t B = Point_Refs(begin);
  const Point_refs_t E = Point_Refs(end);

  return Vector_Constructor_Refs(&(Vector_refs_t){
    .x = E.x - B.x,
    .y = E.y - B.y,
    .z = E.z - B.z
  });
}

Vector_t * Vector_Constructor_Refs(Vector_refs_t const * const refs)
{
  if(!refs) return NULL;

  Vector_t * const obj = (Vector_t*)malloc(sizeof(Vector_t));

  // Check if dynamic memory is successed.
  if(!obj) return NULL;

  // Initialize members
  *obj = *(Vector_t*)refs;

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

// ? general member function
Vector_refs_t Vector_Refs(Vector_t const * const self)
{
  return self ? *(Vector_refs_t*)(self) : (Vector_refs_t){ 0 } ;
}
