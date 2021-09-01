#ifndef _SHAPE_PARSER_
#define _SHAPE_PARSER_

#include "scanner.h"
#include "shape_builder.h"

class ShapeParser {
public:
  ShapeParser(std::string input) {
    // initialize a scanner for handling input.
    // initialize a shape builder for handling building shape.
    m_scanner = new Scanner(input);
    m_shapebuilder = new ShapeBuilder();
  }

  ~ShapeParser() {
    delete m_scanner;
    delete m_shapebuilder;
  }

  void parser() {
    // using Scanner::nextToken() to get all information to determine what to build,
    // and provide the argument the shape needed.
    // use functions in ShapeBuilder to build out the shape.
    // the shape with invalid argument should be ignored (see example bellow).
    bool stop = false;
    std::string get = "";
    while(!stop) {
      try {
        get = m_scanner->nextToken();
        if(get == "Rectangle") {
          parser_rectangle();
        } else if(get == "Ellipse") {
          parser_ellipse();
        } else if(get == "Triangle") {
          parser_triangle();
        } else if(get == "{") {
          m_shapebuilder->buildCompoundShapeBegin();
        } else if(get == "}") {
          m_shapebuilder->buildCompoundShapeEnd();
        } else {
          std::cout << "ignore :" << get << std::endl;
        }
      }
      catch(std::string e) {
        stop = true;
      }
    }
  }

  std::deque<Shape*> getResult() {
    // return result.
    return m_shapebuilder->getResult();
  }
private:
  Scanner * m_scanner = nullptr;
  ShapeBuilder * m_shapebuilder = nullptr;

  void parser_rectangle() {
    std::string get = m_scanner->nextToken();
    std::vector<double> get_doulbe;
    while(get != ")"){
      if(get != "(" && get != ","){
        // number
        try{
          get_doulbe.push_back(std::stod(get));
        }catch(std::string e){
          std::cout << get << std::endl;
        }
      }
      get = m_scanner->nextToken();
    }

    if(get_doulbe.size() == 2)
      m_shapebuilder->buildRectangle(get_doulbe[0], get_doulbe[1]);
  }

  void parser_ellipse() {
    std::string get = m_scanner->nextToken();
    std::vector<double> get_doulbe;
    while(get != ")"){
      if(get != "(" && get != ","){
        // number
        try{
          get_doulbe.push_back(std::stod(get));
        }catch(std::string e){
          std::cout << get << std::endl;
        }
      }
      get = m_scanner->nextToken();
    }

    if(get_doulbe.size() == 2)
      m_shapebuilder->buildEllipse(get_doulbe[0], get_doulbe[1]);
  }

  void parser_triangle() {
    std::string get = m_scanner->nextToken();
    std::vector<double> get_doulbe;
    while(get != ")") {
      if(get != "(" && get != ",") {
        // number
        try{
          get_doulbe.push_back(std::stod(get));
        }catch(std::string e) {
          std::cout << get << std::endl;
        }
      }
      get = m_scanner->nextToken();
    }

    if(get_doulbe.size() == 6)
      m_shapebuilder->buildTriangle(get_doulbe[0], get_doulbe[1], get_doulbe[2], get_doulbe[3], get_doulbe[4], get_doulbe[5]);

  }
};


#endif
