#include <heat/bmi_heat.h>

#include <stdio.h>
#include <stdlib.h>

void print_var_values (void *self, const char *var_name);

int
main (void)
{
  void *self = NULL;
  double *new_vals = NULL;
  int err = 0;

  err = BMI_HEAT_Initialize (NULL, &self);
  if (err || !self)
    return EXIT_FAILURE;

  {
    char name[BMI_MAX_COMPONENT_NAME];
    BMI_HEAT_Get_component_name (self, name);
  
    fprintf (stdout, "%s\n", name);
  }

  { /* Get grid information */
    int n_dims;
    int *shape;
    int len = 0;
    int i;

    BMI_HEAT_Get_var_rank (self, "plate_surface__temperature", &n_dims);
    shape = (int*) malloc (sizeof (int)*n_dims);

    BMI_HEAT_Get_grid_shape (self, "plate_surface__temperature", shape);
    for (i = 0, len = 1; i < n_dims; i++)
      len *= shape[i];

    new_vals = (double *)malloc (sizeof (double) * len);
    for (i = 0; i < len; i++)
      new_vals[i] = -1;

    free (shape);
  }

  fprintf (stdout, "Values before set\n");
  fprintf (stdout, "=================\n");
  print_var_values (self, "plate_surface__temperature");

  BMI_HEAT_Set_value (self, "plate_surface__temperature", new_vals);

  fprintf (stdout, "Values after set\n");
  fprintf (stdout, "================\n");
  print_var_values (self, "plate_surface__temperature");

  {
    int inds[5] = {1, 2, 4, 8, 16};
    double vals[5] = {11, 22, 44, 88, 1616};
    double *p;
    int i;

    BMI_HEAT_Set_value_at_indices (self, "plate_surface__temperature", inds, 5, vals);
    print_var_values (self, "plate_surface__temperature");

    BMI_HEAT_Get_value_ptr (self, "plate_surface__temperature", (void**)(&p));
    for (i=0; i<5; i++) {
      fprintf (stdout, "Checking %d...", inds[i]);
      if (p[inds[i]] == vals[i])
        fprintf (stdout, "PASS\n");
    }
  }

  free (new_vals);

  BMI_HEAT_Finalize (self);

  return EXIT_SUCCESS;
}

void
print_var_values (void *self, const char *var_name)
{
  double *var = NULL;
  int n_dims = 0;
  int *shape = NULL;

  BMI_HEAT_Get_var_rank (self, var_name, &n_dims);
  shape = (int*) malloc (sizeof (int)*n_dims);

  BMI_HEAT_Get_grid_shape (self, "plate_surface__temperature", shape);
  BMI_HEAT_Get_value_ptr (self, var_name, (void**)(&var));

  fprintf (stdout, "Variable: %s\n", var_name);
  fprintf (stdout, "Number of dimension: %d\n", n_dims);
  fprintf (stdout, "Shape: %d x %d\n", shape[0], shape[1]);
  fprintf (stdout, "================\n");

  {
    int i, j;
    for (i = 0; i < shape[0]; i++) {
      for (j = 0; j < shape[1]; j++)
        fprintf (stdout, "%f ", var[i*shape[1]+j]);
      fprintf (stdout, "\n");
    }
  }

  return;
}
