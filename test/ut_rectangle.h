#include "../src/rectangle.h"

TEST(shape, rectangle_area_info_perimeter){
  Rectangle r1(1.4, 2);
  ASSERT_EQ("Rectangle (1.400, 2.000)", r1.info());
  ASSERT_EQ(2.8, r1.area());
  ASSERT_EQ(6.8, r1.perimeter());
}

TEST(shape, rectangle_exception){
  try {
    Rectangle(-2.3, 1);
    FAIL();
  }catch(std::string e) {
        ASSERT_EQ("This is not a rectangle!", e);
  }

  ASSERT_NO_THROW(Rectangle(1, 1));
}
