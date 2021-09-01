#include "../src/scanner.h"

TEST(Scanner, ellipse) {
  Scanner scanner("Ellipse (4.000, 3.000)");

  EXPECT_EQ("Ellipse", scanner.nextToken());
  EXPECT_EQ("(", scanner.nextToken());
  EXPECT_EQ("4.000", scanner.nextToken());
  EXPECT_EQ(",", scanner.nextToken());
  EXPECT_EQ("3.000", scanner.nextToken());
  EXPECT_EQ(")", scanner.nextToken());

  try {
      scanner.nextToken();
      FAIL();
  }catch(std::string e) {
      EXPECT_EQ("next char doesn't exist.", e);
  }
}

TEST(Scanner, rectangle) {
  Scanner scanner("Rectangle (3.000, 4.000)");

  EXPECT_EQ("Rectangle", scanner.nextToken());
  EXPECT_EQ("(", scanner.nextToken());
  EXPECT_EQ("3.000", scanner.nextToken());
  EXPECT_EQ(",", scanner.nextToken());
  EXPECT_EQ("4.000", scanner.nextToken());
  EXPECT_EQ(")", scanner.nextToken());

  try {
      scanner.nextToken();
      FAIL();
  }catch(std::string e) {
      EXPECT_EQ("next char doesn't exist.", e);
  }
}

TEST(Scanner, triangle) {
  Scanner scanner("Triangle (1.000, 2.000, 3.000, 4.000, 5.000, 6.000)");

  EXPECT_EQ("Triangle", scanner.nextToken());
  EXPECT_EQ("(", scanner.nextToken());
  EXPECT_EQ("1.000", scanner.nextToken());
  EXPECT_EQ(",", scanner.nextToken());
  EXPECT_EQ("2.000", scanner.nextToken());
  EXPECT_EQ(",", scanner.nextToken());
  EXPECT_EQ("3.000", scanner.nextToken());
  EXPECT_EQ(",", scanner.nextToken());
  EXPECT_EQ("4.000", scanner.nextToken());
  EXPECT_EQ(",", scanner.nextToken());
  EXPECT_EQ("5.000", scanner.nextToken());
  EXPECT_EQ(",", scanner.nextToken());
  EXPECT_EQ("6.000", scanner.nextToken());
  EXPECT_EQ(")", scanner.nextToken());

  try {
      scanner.nextToken();
      FAIL();
  }catch(std::string e) {
      EXPECT_EQ("next char doesn't exist.", e);
  }
}

TEST(Scanner, compoundshape) {
  Scanner scanner("CompoundShape {Rectangle (3.000, 4.000), CompoundShape {Ellipse (4.000, 3.000), Rectangle (3.000, 4.000), Triangle (0.000, 0.000, 3.000, 0.000, 0.000, 4.000)}}");

  EXPECT_EQ("CompoundShape", scanner.nextToken());
  EXPECT_EQ("{", scanner.nextToken());
  EXPECT_EQ("Rectangle", scanner.nextToken());
  EXPECT_EQ("(", scanner.nextToken());
  EXPECT_EQ("3.000", scanner.nextToken());
  EXPECT_EQ(",", scanner.nextToken());
  EXPECT_EQ("4.000", scanner.nextToken());
  EXPECT_EQ(")", scanner.nextToken());
  EXPECT_EQ(",", scanner.nextToken());
  EXPECT_EQ("CompoundShape", scanner.nextToken());
  EXPECT_EQ("{", scanner.nextToken());
  EXPECT_EQ("Ellipse", scanner.nextToken());
  EXPECT_EQ("(", scanner.nextToken());
  EXPECT_EQ("4.000", scanner.nextToken());
  EXPECT_EQ(",", scanner.nextToken());
  EXPECT_EQ("3.000", scanner.nextToken());
  EXPECT_EQ(")", scanner.nextToken());
  EXPECT_EQ(",", scanner.nextToken());
  EXPECT_EQ("Rectangle", scanner.nextToken());
  EXPECT_EQ("(", scanner.nextToken());
  EXPECT_EQ("3.000", scanner.nextToken());
  EXPECT_EQ(",", scanner.nextToken());
  EXPECT_EQ("4.000", scanner.nextToken());
  EXPECT_EQ(")", scanner.nextToken());
  EXPECT_EQ(",", scanner.nextToken());
  EXPECT_EQ("Triangle", scanner.nextToken());
  EXPECT_EQ("(", scanner.nextToken());
  EXPECT_EQ("0.000", scanner.nextToken());
  EXPECT_EQ(",", scanner.nextToken());
  EXPECT_EQ("0.000", scanner.nextToken());
  EXPECT_EQ(",", scanner.nextToken());
  EXPECT_EQ("3.000", scanner.nextToken());
  EXPECT_EQ(",", scanner.nextToken());
  EXPECT_EQ("0.000", scanner.nextToken());
  EXPECT_EQ(",", scanner.nextToken());
  EXPECT_EQ("0.000", scanner.nextToken());
  EXPECT_EQ(",", scanner.nextToken());
  EXPECT_EQ("4.000", scanner.nextToken());
  EXPECT_EQ(")", scanner.nextToken());
  EXPECT_EQ("}", scanner.nextToken());
  EXPECT_EQ("}", scanner.nextToken());

  try {
      scanner.nextToken();
      FAIL();
  }catch(std::string e) {
      EXPECT_EQ("next char doesn't exist.", e);
  }
}
