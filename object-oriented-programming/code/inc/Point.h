#ifndef _POINT_H_
#define _POINT_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "Common.h"

typedef enum { PointX, PointY, PointZ } Point_Coordinate_Enum;

typedef struct Point_t Point_t;

// ? Constructor
// 1. Create object body. (try to ask memorys)
// 2. Initialize all members in the object.
Point_t * Point_Constructor(double x, double y, double z);

// ? Destructor
// 1. Release object to avoid memory leaks.
// 2. Return a result that can be inspected by the user \
//    is a better habit for declaring setter functions.
task_t Point_Destructor(Point_t * const self);

// ? setters
// 1. Will update or change data value in object.
// 2. Changing more than 1 member in 1 call should be avoided.
// 3. Return a result that can be inspected by the user \
//    is a better habit for declaring setter functions.
task_t Point_set_Coordinate(Point_t * const self, Point_Coordinate_Enum coordinate, double value);

// ? getters 
// 1. Should not overwrite any data in object.
// 2. The only way to access the members in object.
// 3. Don't try to ask multiple members in 1 call.
double Point_get_Coordinate(Point_t const * const self, Point_Coordinate_Enum coordinate);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _POINT_H_
