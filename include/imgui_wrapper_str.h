typedef struct f_slider {
  const char *label;
  float *val;
  float lower;
  float upper;
} F_SLIDER;

typedef struct i_slider {
  const char *label;
  int *val;
  int lower;
  int upper;
} I_SLIDER;
