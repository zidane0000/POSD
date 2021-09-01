#include "../src/terminal.h"

TEST(terminal_test, terminalInit){
  Terminal t("Rectangle (3.7, 4.2) Ellipse (3, 4) Triangle ([0,-3], [-3,0], [0,-4]) perimeter inc");
}

TEST(terminal_test, terminalInitExpect){
  try {
      Terminal("Rectangle (0, 0) Ellipse (-1, -1) area inc");
      FAIL();
  }catch(string e) {
      EXPECT_EQ("invalid input", e);
  }
}

TEST(terminal_test, InvalidInputShapeNoSpace){
  try {
      Terminal t("Rectangle(3.7, 4.2) Ellipse(3, 4) Triangle([0,-3], [-3,0], [0,-4]) perimeter inc");
      FAIL();
  }catch(string e) {
      EXPECT_EQ("invalid input", e);
  }
}

TEST(terminal_test, PerimeterIncreasing ){
  Terminal terminal("Rectangle (3.7, 4.2) Ellipse (4, 3) Triangle ([0,0], [-3,0], [0,-4]) perimeter inc");
  EXPECT_EQ("12.000\n15.800\n22.850", terminal.showResult());
}

TEST(terminal_test, terminalResult){
  Terminal terminal("Rectangle (2, 2) Rectangle (1, 1) Ellipse$%^&(1, 1) area inc");
  EXPECT_EQ("1.000\n4.000", terminal.showResult());
}
