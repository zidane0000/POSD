#include "../src/utility.h"

class utilityInit : public ::testing::Test {
protected:
  void SetUp() override {
    p_triangle = new Triangle("2", { new TwoDimensionalCoordinate(0.0, 0.0), new TwoDimensionalCoordinate(3.0, 0.0), new TwoDimensionalCoordinate(0.0, 4.0) });
    p_ellipse = new Ellipse("3", 4, 2);
    p_rectangle = new Rectangle("4", 1, 1);

    list<Shape*> list_shape_1{p_triangle};
    p_compound_shape_1 = new CompoundShape("1", list_shape_1);

    list<Shape*> list_shape_2{p_compound_shape_1, p_ellipse, p_rectangle};
    p_compound_shape_0 = new CompoundShape("0", list_shape_2);
  }

  void TearDown() override {
    delete p_triangle;
    delete p_ellipse;
    delete p_rectangle;
    delete p_compound_shape_0;
    delete p_compound_shape_1;
  }

  Shape* p_triangle;
  Shape* p_ellipse;
  Shape* p_rectangle;
  Shape* p_compound_shape_0;
  Shape* p_compound_shape_1;
};

TEST_F(utilityInit, exception_for_get_shape_by_id){
  try{
    //exception_for_rectangle_get_shape_by_id
    getShapeById(p_rectangle, "0");
    FAIL();
  }
  catch(std::string e){
    EXPECT_EQ("Only compound shape can get shape!", e);
  }

  try{
    //exception_for_rectangle_filter_shape
    filterShape(p_rectangle, AreaFilter(10, 5));
    FAIL();
  }
  catch(std::string e){
    EXPECT_EQ("Only compound shape can filter shape!", e);
  }

  try{
    //exception_for_rectangle_get_shape_by_id
    getShapeById(p_triangle, "0");
    FAIL();
  }
  catch(std::string e){
    EXPECT_EQ("Only compound shape can get shape!", e);
  }

  try{
    //exception_for_rectangle_filter_shape
    filterShape(p_triangle, AreaFilter(10, 5));
    FAIL();
  }
  catch(std::string e){
    EXPECT_EQ("Only compound shape can filter shape!", e);
  }

  try{
    //exception_for_rectangle_get_shape_by_id
    getShapeById(p_ellipse, "0");
    FAIL();
  }
  catch(std::string e){
    EXPECT_EQ("Only compound shape can get shape!", e);
  }

  try{
    //exception_for_rectangle_filter_shape
    filterShape(p_ellipse, AreaFilter(10, 5));
    FAIL();
  }
  catch(std::string e){
    EXPECT_EQ("Only compound shape can filter shape!", e);
  }
}

TEST_F(utilityInit, getShapeById_Test){
  try{
    getShapeById(p_triangle, "0");
    FAIL();
  }
  catch(std::string e){
    EXPECT_EQ("Only compound shape can get shape!", e);
  }

  EXPECT_EQ(p_triangle, getShapeById(p_compound_shape_0, "2"));

  try{
    getShapeById(p_compound_shape_0, "0");
    FAIL();
  }
  catch(std::string e){
    EXPECT_EQ("Expected get shape but shape not found", e);
  }
}

TEST_F(utilityInit, filterShape_Test){
  //                    area   perimeter   color        type
  //p_triangle          6      12          white        triangle
  //p_ellipse           25.132 20.5664     white        ellipse
  //p_rectangle         1      4           red          rectangle
  //p_compound_shape_1  6      12          transparent  compound_shape
  // cout << "area->" << endl;
  // cout << p_triangle->area() << endl;
  // cout << p_ellipse->area() << endl;
  // cout << p_rectangle->area() << endl;
  // cout << p_compound_shape_1->area() << endl;
  // cout << "perimeter->" << endl;
  // cout << p_triangle->perimeter() << endl;
  // cout << p_ellipse->perimeter() << endl;
  // cout << p_rectangle->perimeter() << endl;
  // cout << p_compound_shape_1->perimeter() << endl;
  // cout << "color->" << endl;
  // cout << p_triangle->color() << endl;
  // cout << p_ellipse->color() << endl;
  // cout << p_rectangle->color() << endl;
  // cout << p_compound_shape_1->color() << endl;

  std::deque<Shape*> deq_area = filterShape(p_compound_shape_0, AreaFilter(10, 5));
  EXPECT_EQ( 2, deq_area.size());
  // retrun shapes that area in range of 10 >= && 5 <=, but don't include compoundShape_0 itself.

  std::deque<Shape*> deq_perimeter = filterShape(p_compound_shape_0, PerimeterFilter(10, 5));
  EXPECT_EQ( 0, deq_perimeter.size());
  // retrun shapes that perimeter in range 10 >= && 5 <=, but don't include compoundShape_0 itself.

  std::deque<Shape*> deq_color = filterShape(p_compound_shape_0, ColorFilter("white"));
  EXPECT_EQ( 3, deq_color.size());
  // retrun shapes that color match "white", but don't include compoundShape_0 itself.

  std::deque<Shape*> deq_type = filterShape(p_compound_shape_0, TypeFilter("Compound Shape"));
  EXPECT_EQ( 1, deq_type.size());
  // retrun shapes that type match "Compound Shape", but don't include compoundShape_0 itself.
}
