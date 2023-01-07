#ifndef _VECTOR_H_
#define _VECTOR_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "Common.h"
#include "Point.h"

typedef enum { VectorX, VectorY, VectorZ } Vector_Coordinate_Enum;
typedef enum { PlaneXY, PlaneXZ, PlaneYZ } Vector_Plane_Enum;

typedef struct Vector_t Vector_t;

// ? Constructor
Vector_t * Vector_Constructor(Point_t const * const begin, Point_t const * const end);

// ? Destructor
task_t Vector_Destructor(Vector_t * const self);

// ? setters
task_t Vector_set_Coordinate(Vector_t * const self, Vector_Coordinate_Enum coordinate, double value);

// ? getters 
double Vector_get_Coordinate(Vector_t const * const self, Vector_Coordinate_Enum coordinate);

// ? general member functions
double Vector_Length(Vector_t const * const self);
double Vector_CoordinateAngle(Vector_t const * const self, Vector_Coordinate_Enum coordinate); // rad
double Vector_PlaneAngle(Vector_t const * const self, Vector_Plane_Enum plane); // rad


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _VECTOR_H_
