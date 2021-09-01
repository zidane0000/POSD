#include "../src/rectangle.h"
#include "../src/filter.h"
#include "../src/shape_filter.h"
#include "../src/shape_setter.h"

class FilterInit : public ::testing::Test {
protected:
  void SetUp() override {
    data.push_back(new Rectangle("0", 1, 1, "black"));
    data.push_back(new Rectangle("1", 2, 1, "black"));
    data.push_back(new Rectangle("2", 4, 1, "black"));
    data.push_back(new Rectangle("3", 8, 1, "white"));
    data.push_back(new Rectangle("4", 16, 1, "black"));
    data.push_back(new Rectangle("5", 32, 1, "black"));
    data.push_back(new Rectangle("6", 64, 1, "black"));
    data.push_back(new Rectangle("7", 128, 1, "black"));
    data.push_back(new Rectangle("8", 256, 1, "black"));
  }

  void TearDown() override {
    for(Shape * in_data : data)
      delete in_data;
    data.clear();
  }

  std::list<Shape *> data;
};

TEST_F(FilterInit, FilterTest_Area_Perimeter_Color) {
  Filter * areaFilter = new ShapeFilter([](Shape* shape) {return shape->area() <= 40;});
  Filter * perimeterilter = new ShapeFilter([](Shape* shape) {return shape->perimeter() >= 5;});
  Filter * colorFilter = new ShapeFilter([](Shape* shape) {return shape->color() == "black";});

  areaFilter->setNext(perimeterilter)->setNext(colorFilter);
  std::list<Shape*> results = areaFilter->push(data);

  //Area res = 0 - 5
  //Perimeter res = 1 - 5
  //Colr res = 1, 2, 4, 5
  EXPECT_EQ(4, results.size());
}

TEST_F(FilterInit, SetterTest_Area_Perimeter_ColorSet) {
  Filter * areaFilter = new ShapeFilter([](Shape* shape) {return shape->area() <= 40;});
  Filter * perimeterilter = new ShapeFilter([](Shape* shape) {return shape->perimeter() >= 5;});
  Filter* colorSetter = new ShapeSetter([](Shape* shape) {shape->setColor("black");});

  areaFilter->setNext(perimeterilter)->setNext(colorSetter);
  std::list<Shape*> results = areaFilter->push(data);

  //Area res = 0 - 5
  //Perimeter res = 1 - 5
  EXPECT_EQ(5, results.size());
}

TEST_F(FilterInit, filter_by_area) {
  Filter * areaFilter = new ShapeFilter([](Shape* shape) {return shape->area() <= 40;});
  std::list<Shape*> results = areaFilter->push(data);

  //Area res = 0 - 5
  EXPECT_EQ(6, results.size());
}

TEST_F(FilterInit, filter_by_perimeter) {
  Filter * perimeterilter = new ShapeFilter([](Shape* shape) {return shape->perimeter() >= 5;});
  std::list<Shape*> results = perimeterilter->push(data);

  //Area res = 0 - 5
  EXPECT_EQ(8, results.size());
}

TEST_F(FilterInit, filter_by_area_perimeter) {
  Filter * areaFilter = new ShapeFilter([](Shape* shape) {return shape->area() <= 40;});
  Filter * perimeterilter = new ShapeFilter([](Shape* shape) {return shape->perimeter() >= 5;});

  areaFilter->setNext(perimeterilter);

  std::list<Shape*> results = areaFilter->push(data);

  //Area res = 0 - 5
  EXPECT_EQ(5, results.size());
}

TEST_F(FilterInit, filter_when_no_result) {
  Filter * areaFilter = new ShapeFilter([](Shape* shape) {return shape->area() == 0;});
  std::list<Shape*> results = areaFilter->push(data);
  EXPECT_EQ(0, results.size());
}
