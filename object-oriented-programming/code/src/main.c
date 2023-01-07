#include <stdio.h>
#include "Common.h"
#include "Point.h"
#include "Vector.h"

int main(void)
{
  Point_t * const Pa = Point_Constructor(0, 0, 0);
  Point_t * const Pb = Point_Constructor(1, 1, 1);
  Vector_t * const V = Vector_Constructor(Pa, Pb); // dynamic object: Pb -> Pb
  const Vector_refs_t Vr = Vector_Refs(V); // static object refer to dynamic object.

  task_t result = Success;

  if(!Pa || !Pb || !V) {
    result = Fail;
    goto __End;
  }

  // ? Call class function via dynamic object
  printf("vector lenght = %.4f\r\n", Vector_Length(V));
  printf("vector angle against to X-Y plane = %.4f rad\r\n", Vector_PlaneAngle(V, PlaneXY));

  // ? Call class function via static object (reference)
  printf("vector refs lenght = %.4f\r\n", Vector_Length((Vector_t*)&Vr));
  printf("vector refs angle against to X-Y plane = %.4f rad\r\n", Vector_PlaneAngle((Vector_t*)&Vr, PlaneXY));

__End:

  Point_Destructor(Pa);
  Point_Destructor(Pb);
  Vector_Destructor(V);

  return result;
}
