#include "../src/compound_shape.h"
#include "../src/rectangle.h"
#include "../src/triangle.h"
#include "../src/ellipse.h"

class CompoundShapeInit : public ::testing::Test {
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

TEST_F(CompoundShapeInit, CompoundShapeTest){
  EXPECT_NEAR(32.132, p_compound_shape->area(), 0.001);
  EXPECT_NEAR(36.5664, p_compound_shape->perimeter(), 0.001);
  EXPECT_EQ("Compound Shape {Triangle ([0.000, 0.000], [3.000, 0.000], [0.000, 4.000]), Ellipse (4.000, 2.000), Rectangle (1.000, 1.000)}", p_compound_shape->info());
}

TEST_F(CompoundShapeInit, CompoundShapeAddAndDeleteException){
  try{
    p_compound_shape->getShapeById("?");
    FAIL();
  }
  catch(std::string e){
    EXPECT_EQ("Expected get shape but shape not found", e);
  }

  try{
    p_compound_shape->deleteShapeById("?");
    FAIL();
  }
  catch(std::string e){
    EXPECT_EQ("Expected delete shape but shape not found", e);
  }

  try{
    std::list<Shape*> t;
    CompoundShape("0", t);
  }
  catch(std::string e){
    EXPECT_EQ("This is not a compound shape!", e);
  }
}

TEST(CompoundShape, CompoundShapeAddAndDelete){
  std::list<Shape*> shapes({new Rectangle("1", 1, 1)});
  CompoundShape p_compound_shape = CompoundShape("0", shapes);

  Shape* p_rec = new Rectangle ("2", 2.000, 2.000);
  p_compound_shape.addShape(p_rec);
  EXPECT_EQ("Compound Shape {Rectangle (1.000, 1.000), Rectangle (2.000, 2.000)}", p_compound_shape.info());

  p_compound_shape.deleteShapeById("2");
  EXPECT_EQ("Compound Shape {Rectangle (1.000, 1.000)}", p_compound_shape.info());
}

TEST(CompoundShape, TestShapeById_Lv3TreeStruct){
  Shape* p_compound_shape_level3 = new CompoundShape("2", {new Rectangle("1", 1, 2), new Rectangle("0", 1, 1)});
  Shape* p_compound_shape_level2 = new CompoundShape("4", {new Rectangle("3", 1, 3), p_compound_shape_level3 });
  Shape* p_compound_shape_level1 = new CompoundShape("5", { p_compound_shape_level2 });

  EXPECT_EQ("Compound Shape {Compound Shape {Rectangle (1.000, 3.000), Compound Shape {Rectangle (1.000, 2.000), Rectangle (1.000, 1.000)}}}", p_compound_shape_level1->info());
  p_compound_shape_level1->deleteShapeById("0");
  EXPECT_EQ("Compound Shape {Compound Shape {Rectangle (1.000, 3.000), Compound Shape {Rectangle (1.000, 2.000)}}}", p_compound_shape_level1->info());

  Shape* get_shape = p_compound_shape_level1->getShapeById("1");
  EXPECT_EQ("Rectangle (1.000, 2.000)", get_shape->info());

  try{
    //exception_for_get_shape_by_id_tree_structure
    p_compound_shape_level1->getShapeById("a");
    FAIL();
  }
  catch(std::string e){
    EXPECT_EQ("Expected get shape but shape not found", e);
  }

  try{
    //exception_for_delete_shape_by_id_tree_structure
    p_compound_shape_level1->deleteShapeById("a");
    FAIL();
  }
  catch(std::string e){
    EXPECT_EQ("Expected delete shape but shape not found", e);
  }
}

// TEST_F(CompoundShapeInit, Shape_Type_And_CreateIterator_Test){
//   //type
//   EXPECT_EQ("Triangle", p_triangle->type());
//   EXPECT_EQ("Ellipse", p_ellipse->type());
//   EXPECT_EQ("Rectangle", p_rectangle->type());
//   EXPECT_EQ("Compound Shape", p_compound_shape->type());
//
//   //createIterator
//   try{
//     p_triangle->createIterator()->first();
//     FAIL();
//   }
//   catch(std::string e){
//     EXPECT_EQ("No child member!", e); //
//   }
// }
//
// TEST_F(CompoundShapeInit, CompoundShape_CreateIterator_Test){
//   EXPECT_FALSE(p_compound_shape->createIterator()->isDone());
// }
