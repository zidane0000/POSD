#include "../src/shape_builder.h"

TEST(ShapeBuilderTest, build_rectangle) {
  ShapeBuilder sb;
  sb.buildRectangle(2, 2);
  std::deque<Shape*> results = sb.getResult();

  EXPECT_EQ(1, results.size());
  EXPECT_EQ("Rectangle (2.000, 2.000)", results[0]->info());
}

TEST(ShapeBuilderTest, build_ellipse) {
  ShapeBuilder sb;
  sb.buildEllipse(5, 2);
  std::deque<Shape*> results = sb.getResult();

  EXPECT_EQ(1, results.size());
  EXPECT_EQ("Ellipse (5.000, 2.000)", results[0]->info());
}

TEST(ShapeBuilderTest, build_triangle) {
  ShapeBuilder sb;
  sb.buildTriangle(0, 0, 0, -3, -4, 0);
  std::deque<Shape*> results = sb.getResult();

  EXPECT_EQ(1, results.size());
  EXPECT_EQ("Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])", results[0]->info());
}

TEST(ShapeBuilderTest, build_multi_simple_shapes) {
  ShapeBuilder sb;
  sb.buildRectangle(3, 4);
  sb.buildRectangle(3, 4);
  sb.buildEllipse(4.200, 3.700);
  sb.buildTriangle(0, 0, 0, -3, -4, 0);
  std::deque<Shape*> results = sb.getResult();

  EXPECT_EQ(4, results.size());
  EXPECT_EQ("Rectangle (3.000, 4.000)", results[0]->info());
  EXPECT_EQ("Rectangle (3.000, 4.000)", results[1]->info());
  EXPECT_EQ("Ellipse (4.200, 3.700)", results[2]->info());
  EXPECT_EQ("Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])", results[3]->info());
}

TEST(ShapeBuilderTest, build_empty_compoundShape ) {
  ShapeBuilder sb;
  sb.buildCompoundShapeBegin();
  sb.buildCompoundShapeEnd();
  std::deque<Shape*> results = sb.getResult();

  EXPECT_EQ(1, results.size());
  EXPECT_EQ("Compound Shape {}", results[0]->info());
}

TEST(ShapeBuilderTest, build_Tree_Level3_CompoundShape) {
  ShapeBuilder sb;
  sb.buildCompoundShapeBegin();

  sb.buildCompoundShapeBegin();
  sb.buildRectangle(1.000, 3.000);

  sb.buildCompoundShapeBegin();
  sb.buildRectangle(1.000, 2.000);
  sb.buildRectangle(1.000, 1.000);
  sb.buildCompoundShapeEnd();

  sb.buildCompoundShapeEnd();

  sb.buildCompoundShapeEnd();
  std::deque<Shape*> results = sb.getResult();
  EXPECT_EQ(1, results.size());
  EXPECT_EQ("Compound Shape {Compound Shape {Rectangle (1.000, 3.000), Compound Shape {Rectangle (1.000, 2.000), Rectangle (1.000, 1.000)}}}", results[0]->info());
}

TEST(ShapeBuilderTest, build_compoundShape_that_contains_a_empty_compoundShape ) {
  ShapeBuilder sb;
  sb.buildCompoundShapeBegin();
  sb.buildCompoundShapeBegin();
  sb.buildCompoundShapeEnd();
  sb.buildCompoundShapeEnd();
  std::deque<Shape*> results = sb.getResult();

  EXPECT_EQ(1, results.size());
  EXPECT_EQ("Compound Shape {Compound Shape {}}", results[0]->info());
}
