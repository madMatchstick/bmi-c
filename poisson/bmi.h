#ifndef BMI_H_INCLUDED
#define BMI_H_INCLUDED

#if defined(__cplusplus)
extern "C" {
#endif

typedef enum {
  BMI_GRID_TYPE_UNKNOWN = 0,
  BMI_GRID_TYPE_UNIFORM,
  BMI_GRID_TYPE_RECTILINEAR,
  BMI_GRID_TYPE_STRUCTURED,
  BMI_GRID_TYPE_UNSTRUCTURED,
  BMI_GRID_TYPE_NUMBER
}
BMI_Grid_type;

typedef enum {
  BMI_VAR_TYPE_UNKNOWN = 0,
  BMI_VAR_TYPE_CHAR,
  BMI_VAR_TYPE_UNSIGNED_CHAR,
  BMI_VAR_TYPE_INT,
  BMI_VAR_TYPE_LONG,
  BMI_VAR_TYPE_UNSIGNED_INT,
  BMI_VAR_TYPE_UNSIGNED_LONG,
  BMI_VAR_TYPE_FLOAT,
  BMI_VAR_TYPE_DOUBLE,
  BMI_VAR_TYPE_NUMBER
}
BMI_Var_type;

#define BMI_SUCCESS (0)
#define BMI_FAILURE (1)

#define BMI_MAX_UNITS_NAME 2048
#define BMI_MAX_COMPONENT_NAME 2048
#define BMI_MAX_VAR_NAME 2048

#if defined(__cplusplus)
}
#endif

#endif
