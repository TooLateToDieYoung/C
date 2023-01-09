# Typedef Enums
```C
typedef enum { PointX, PointY, PointZ } Point_Coordinate_Enum;
```

---

# Data Strutcture
```C
/* Public (user visable in the header file) */
typedef struct Point_t Point_t;

/* Private (hide implementation in the source file) */
struct Point_t {
  double x;
  double y;
  double z;
};
```

---

# Reference Object Data Strutcture
```C
/* Public (user visable in the header file) */
typedef struct {
  double x;
  double y;
  double z;
} Point_refs_t;
```

---

# Constructor
  - Create object body. (try to ask memorys)
  - Initialize all members in the object.
  - Two APIs are provided, one of which is constructed via the refs data structure.
```C
/* Declared in the header file */
Point_t * Point_Constructor(double x, double y, double z);
Point_t * Point_Constructor_Refs(Point_refs_t const * const refs);
```

---

# Destructor
  - Release object to avoid memory leaks.
  - Return a result that can be inspected by the user is a better habit for declaring setter functions.
```C
/* Declared in header file */
task_t Point_Destructor(Point_t * const self);
```

---

# Setters
  - Will update or change data value in object.
  - Changing more than 1 member in 1 call should be avoided.
  - Return a result that can be inspected by the user is a better habit for declaring setter functions.
```C
/* Declared in the header file */
task_t Point_set_Coordinate(
  Point_t * const self,             // ? Point to a modifiable object
  Point_Coordinate_Enum coordinate, // ? Specifies the details of variables
  double value                      // ? New value to replace old data
);
```

---

# Getters 
  - Should not overwrite any data in object.
  - The only way to access the members in object.
  - Don't try to ask multiple members in 1 call.
```C
/* Declared in the header file */
double Point_get_Coordinate(
  Point_t const * const self,      // ? Point to a read-only object
  Point_Coordinate_Enum coordinate // ? Specifies the details of variables
);
```

---

# General Class Member Function
- Others class member functions allow users to call.
```C
Point_refs_t Point_Refs(Point_t const * const self);
```

---
