#include "../src/info_visitor.h"
#include "../src/area_visitor.h"

class VisitorInit : public ::testing::Test {
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

TEST_F(VisitorInit, InfoVisitorTest) {
  InfoVisitor m_visitor;
  p_triangle->accept(&m_visitor);
  EXPECT_EQ(p_triangle->info(), m_visitor.info());

  p_ellipse->accept(&m_visitor);
  EXPECT_EQ(p_ellipse->info(), m_visitor.info());

  p_rectangle->accept(&m_visitor);
  EXPECT_EQ(p_rectangle->info(), m_visitor.info());

  p_compound_shape_0->accept(&m_visitor);
  EXPECT_EQ(p_compound_shape_0->info(), m_visitor.info());
}

TEST_F(VisitorInit, AreaVisitorTest) {
  AreaVisitor m_visitor;
  p_triangle->accept(&m_visitor);
  EXPECT_EQ(p_triangle->area(), m_visitor.area());

  p_ellipse->accept(&m_visitor);
  EXPECT_EQ(p_ellipse->area(), m_visitor.area());

  p_rectangle->accept(&m_visitor);
  EXPECT_EQ(p_rectangle->area(), m_visitor.area());

  p_compound_shape_0->accept(&m_visitor);
  EXPECT_EQ(p_compound_shape_0->area(), m_visitor.area());
}
