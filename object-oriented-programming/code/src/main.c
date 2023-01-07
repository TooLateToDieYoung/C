#include <stdio.h>
#include "Common.h"
#include "Point.h"
#include "Vector.h"

int main(void)
{
  Point_t * const Pa = Point_Constructor(0, 0, 0);
  Point_t * const Pb = Point_Constructor(1, 1, 1);
  Vector_t * const V = Vector_Constructor(Pa, Pb); // Pb -> Pb
  
  task_t result = Success;

  if(!Pa || !Pb || !V) {
    result = Fail;
    goto __End;
  }

  printf("vector lenght = %.4f\r\n", Vector_Length(V));
  printf("vector angle against to X-Y plane = %.4f deg\r\n", 57.3f * Vector_PlaneAngle(V, PlaneXY));

__End:

  Point_Destructor(Pa);
  Point_Destructor(Pb);
  Vector_Destructor(V);

  return result;
}
