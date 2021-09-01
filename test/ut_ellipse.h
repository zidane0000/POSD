#include "../src/ellipse.h"

TEST(shape, ellipse_area_info_perimeter){
  Ellipse e1(2, 1.4);
  ASSERT_EQ(8.796, e1.area());
  ASSERT_EQ("Ellipse (2.000, 1.400)", e1.info());
  EXPECT_NEAR(11.196, e1.perimeter(), 0.001);
}

TEST(shape, ellipse_exception){
  try {
    Ellipse(-2.3, 1);
    FAIL();
  }catch(std::string e) {
        ASSERT_EQ("This is not an ellipse!", e);
  }

  try {
    Ellipse(-2.4, -10);
    FAIL();
  }catch(std::string e) {
        ASSERT_EQ("This is not an ellipse!", e);
  }

  ASSERT_NO_THROW(Ellipse(1, 1));
}
