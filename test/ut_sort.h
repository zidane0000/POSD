#include "../src/shape.h"
#include "../src/sort.h"
#include "../src/rectangle.h"
#include "../src/triangle.h"
#include "../src/ellipse.h"

class ShapeInit : public ::testing::Test {
protected:
  void SetUp() override {
    p_triangle = new Triangle({ new TwoDimensionalCoordinate(0.0, 0.0), new TwoDimensionalCoordinate(3.0, 0.0), new TwoDimensionalCoordinate(0.0, 4.0) });
    p_rectangle = new Rectangle(4,5);
    p_ellipse = new Ellipse(3, 1.4);
  }

  void TearDown() override {
      delete p_rectangle;
      delete p_ellipse;
      delete p_triangle;
  }

  Shape* p_rectangle;
  Shape* p_ellipse;
  Shape* p_triangle;
};

TEST_F(ShapeInit, SubtypePolymorphism){
  Shape* shapes[3] = {p_rectangle, p_triangle, p_ellipse};
  EXPECT_EQ(20, shapes[0]->area());
  EXPECT_EQ(6, shapes[1]->area());
  EXPECT_EQ(13.194, shapes[2]->area());

  EXPECT_EQ(18, shapes[0]->perimeter());
  EXPECT_EQ(12, shapes[1]->perimeter());
  EXPECT_NEAR(15.196, shapes[2]->perimeter(), 0.001);
}

TEST_F(ShapeInit, SortByStdAscending) {
  Shape* shapes[3] = {p_rectangle, p_triangle, p_ellipse};

  std::sort(shapes, shapes + 3, AscendingCompare("area"));
  EXPECT_EQ(6, shapes[0]->area());
  EXPECT_EQ(13.194, shapes[1]->area());
  EXPECT_EQ(20, shapes[2]->area());

  std::sort(shapes, shapes + 3, AscendingCompare("perimeter"));
  EXPECT_EQ(12, shapes[0]->perimeter());
  EXPECT_NEAR(15.196, shapes[1]->perimeter(), 0.001);
  EXPECT_EQ(18, shapes[2]->perimeter());
}

TEST_F(ShapeInit, SortByStdDescending) {
  Shape* shapes[3] = {p_rectangle, p_triangle, p_ellipse};

  std::sort(shapes, shapes + 3, DescendingCompare("area"));
  EXPECT_EQ(20, shapes[0]->area());
  EXPECT_EQ(13.194, shapes[1]->area());
  EXPECT_EQ(6, shapes[2]->area());

  std::sort(shapes, shapes + 3, DescendingCompare("perimeter"));
  EXPECT_EQ(18, shapes[0]->perimeter());
  EXPECT_NEAR(15.1965, shapes[1]->perimeter(), 0.001);
  EXPECT_EQ(12, shapes[2]->perimeter());
}

//Lambda Expressions
TEST_F(ShapeInit, DescendingByAreaOnArray) {
  std::array<Shape *, 3> shapes = {p_rectangle, p_triangle, p_ellipse};
  std::sort(shapes.begin(), shapes.end(), [](Shape * a, Shape * b) { return a->area() > b->area(); });
  EXPECT_EQ(20, shapes[0]->area());
  EXPECT_EQ(13.194, shapes[1]->area());
  EXPECT_EQ(6, shapes[2]->area());
}

TEST(QuickSort, SortByQuickSortDescendingByArea) {
  Shape* shapes[8] = { new Rectangle(1,7), new Rectangle(1,3), new Rectangle(1,5), new Rectangle(1,4), new Rectangle(1,1), new Rectangle(1,6), new Rectangle(1,2), new Rectangle(1,8) };
  quickSort(shapes, shapes + 8, DescendingCompare("area"));
  EXPECT_EQ(8, shapes[0]->area());
  EXPECT_EQ(7, shapes[1]->area());
  EXPECT_EQ(6, shapes[2]->area());
  EXPECT_EQ(5, shapes[3]->area());
  EXPECT_EQ(4, shapes[4]->area());
  EXPECT_EQ(3, shapes[5]->area());
  EXPECT_EQ(2, shapes[6]->area());
  EXPECT_EQ(1, shapes[7]->area());
}

TEST(QuickSort, SortByQuickSortAscendingByArea) {
  Shape* shapes[8] = { new Rectangle(1,5), new Rectangle(1,7), new Rectangle(1,3), new Rectangle(1,4), new Rectangle(1,1), new Rectangle(1,6), new Rectangle(1,2), new Rectangle(1,8) };
  quickSort(shapes, shapes + 8, AscendingCompare("area"));
  EXPECT_EQ(1, shapes[0]->area());
  EXPECT_EQ(2, shapes[1]->area());
  EXPECT_EQ(3, shapes[2]->area());
  EXPECT_EQ(4, shapes[3]->area());
  EXPECT_EQ(5, shapes[4]->area());
  EXPECT_EQ(6, shapes[5]->area());
  EXPECT_EQ(7, shapes[6]->area());
  EXPECT_EQ(8, shapes[7]->area());
}
