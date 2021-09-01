#include "../src/compound_shape.h"
#include "../src/rectangle.h"
#include "../src/triangle.h"
#include "../src/ellipse.h"

class IteratorInit : public ::testing::Test {
protected:
  void SetUp() override {
    p_triangle = new Triangle("0", { new TwoDimensionalCoordinate(0.0, 0.0), new TwoDimensionalCoordinate(3.0, 0.0), new TwoDimensionalCoordinate(0.0, 4.0) });
    p_ellipse = new Ellipse("1", 4, 2);
    p_rectangle = new Rectangle("2", 1, 1);

    std::list<Shape*> shapes{p_triangle, p_ellipse, p_rectangle};
    p_compound_shape = new CompoundShape("3", shapes);
  }

  void TearDown() override {
    delete p_triangle;
    delete p_ellipse;
    delete p_rectangle;
    delete p_compound_shape;
  }

  Shape* p_triangle;
  Shape* p_ellipse;
  Shape* p_rectangle;
  Shape* p_compound_shape;
};

TEST_F(IteratorInit, Shape_Type_And_NullIterator_Test){
  //type
  EXPECT_EQ("Triangle", p_triangle->type());
  EXPECT_EQ("Ellipse", p_ellipse->type());
  EXPECT_EQ("Rectangle", p_rectangle->type());
  EXPECT_EQ("Compound Shape", p_compound_shape->type());

  //isDone
  EXPECT_TRUE(p_triangle->createIterator()->isDone());
  EXPECT_TRUE(p_ellipse->createIterator()->isDone());
  EXPECT_TRUE(p_rectangle->createIterator()->isDone());

  try{
    //exception_for_ellipse_iterate_first
    p_triangle->createIterator()->first();
    FAIL();
  }
  catch(std::string e){
    EXPECT_EQ("No child member!", e); //
  }

  try{
    //exception_for_ellipse_iterate_current_item
    p_triangle->createIterator()->currentItem();
    FAIL();
  }
  catch(std::string e){
    EXPECT_EQ("No child member!", e); //
  }

  try{
    //exception_for_ellipse_iterate_next
    p_triangle->createIterator()->next();
    FAIL();
  }
  catch(std::string e){
    EXPECT_EQ("No child member!", e); //
  }
}

TEST_F(IteratorInit, ShapeIterator_Test){
  Iterator* it = p_compound_shape->createIterator();
  EXPECT_FALSE(it->isDone());

  EXPECT_NO_THROW(it->first());

  //compound_shape_iterate_current_item
  Shape* cur = it->currentItem();
  EXPECT_EQ(p_triangle, cur);

  //compound_shape_iterate_current_next
  EXPECT_NO_THROW(it->next());

  try{
    //exception_for_compound_shape_iterate_next_out_of_range
    while(!it->isDone())
      it->next();
    it->next();
    FAIL();
  }
  catch(std::string e){
    EXPECT_EQ("Moving past the end!", e); //
  }
}

TEST(RectangleTestSuite, id_default_color){
  Rectangle rect("0", 2.3, 1);
  EXPECT_EQ("0", rect.id());
  EXPECT_EQ("white", rect.color());
  EXPECT_EQ("Rectangle (2.300, 1.000)", rect.info());
  EXPECT_EQ("Rectangle", rect.type());
}

TEST(RectangleTestSuite, Exception_for){
  Rectangle rect("0", 2.3, 1);
  try{
    //exception_for_add_shape
    rect.addShape(&rect);
    FAIL();
  }
  catch(std::string e){
    EXPECT_EQ("Only compound shape can add shape!", e);
  }

  try{
    //exception_for_delete_shape
    rect.deleteShapeById("0");
    FAIL();
  }
  catch(std::string e){
    EXPECT_EQ("Only compound shape can delete shape!", e);
  }

  try{
    //exception_for_get_shape_by_id
    rect.getShapeById("0");
    FAIL();
  }
  catch(std::string e){
    EXPECT_EQ("Only compound shape can get shape!", e);
  }
}

TEST(EllipseTestSuite, id_color){
  Ellipse m_ell("0", 5, 2);
  EXPECT_EQ("white", m_ell.color());
  EXPECT_EQ("0", m_ell.id());

  try{
    //exception_for_semi_major_axis_is_zero
    Ellipse t_ell("0", 0, 1);
    FAIL();
  }
  catch(std::string e){
    EXPECT_EQ("This is not an ellipse!", e);
  }

  try{
    //exception_for_semi_minor_axis_is_zero
    Ellipse t_ell("0", 1, 0);
    FAIL();
  }
  catch(std::string e){
    EXPECT_EQ("This is not an ellipse!", e);
  }

  try{
    //exception_for_semi_major_axis_less_than_zero
    Ellipse t_ell("0", 1, 2);
    FAIL();
  }
  catch(std::string e){
    EXPECT_EQ("This is not an ellipse!", e);
  }

  try{
    //exception_for_add_shape
    m_ell.addShape(&m_ell);
    FAIL();
  }
  catch(std::string e){
    EXPECT_EQ("Only compound shape can add shape!", e);
  }

  try{
    //exception_for_add_shape
    m_ell.deleteShapeById("0");
    FAIL();
  }
  catch(std::string e){
    EXPECT_EQ("Only compound shape can delete shape!", e);
  }

  try{
    //exception_for_get_shape_by_id
    m_ell.getShapeById("0");
    FAIL();
  }
  catch(std::string e){
    EXPECT_EQ("Only compound shape can get shape!", e);
  }
}
