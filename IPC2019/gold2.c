// Ho Sim Gold2
#include <math.h>
#include <stdio.h>

int main() {
  int x1;
  int y1;
  int x2;
  int y2;

  printf("first line\n");
  scanf_s("%d%d%d%d", &x1, &y1, &x2, &y2);
  printf("x1 %d x2 %d y2 %d\n", x1, x2, y2);
  double slope1 = (double)(y2 - y1) / (double)(x2 - x1);

  printf("second line\n");
  int i1, i2, j1, j2;
  scanf_s("%d%d%d%d", &i1, &j1, &i2, &j2);
  printf("x1 %d x2 %d y2 %d\n", i1, i2, j2);
  double slope2 = (double)(j2 - j1) / (double)(i2 - i1);

  printf("%lf %lf\n", slope1, slope2);
  int slope1IsFinite = isfinite(slope1);
  int slope2IsFinite = isfinite(slope2);
  if (slope1IsFinite && slope2IsFinite) {
    // same slope
    printf("%s", slope1 == slope2? "parallel":"intersecting");
  } else if (!slope1IsFinite) {
    printf("%s", slope2IsFinite ? "intersecting - one vertical"
                                : "parallel - both vertical");
  }

  // intersecting slopes will create a line funtion that equal to one value of x
  // and y if only one is vertical (slope undefined), always intersect if both
  // vertical, parallel slopes are parallel when they are equal

  return 0;
}
