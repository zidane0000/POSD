#include "../src/triangle.h"

TEST(shape, triangle_area_info_perimeter){
  TwoDimensionalCoordinate point_1(0.0, 0.0);
  TwoDimensionalCoordinate point_2(0.0, 3.0);
  TwoDimensionalCoordinate point_3(4.0, 0.0);
  std::vector<TwoDimensionalCoordinate*> vec = { &point_1, &point_2, &point_3 };

  Triangle t1(vec);
  ASSERT_EQ(6, t1.area());
  ASSERT_EQ("Triangle ([0.000, 0.000], [0.000, 3.000], [4.000, 0.000])", t1.info());
  ASSERT_EQ(12, t1.perimeter());

}

TEST(shape, triangle_exception){
  try {
    std::vector<TwoDimensionalCoordinate*> test;
    Triangle t2(test);
    FAIL();
  }catch(std::string e) {
        ASSERT_EQ("This is not a triangle!", e);
  }
}
