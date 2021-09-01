#include "shape.h"
#include "sort.h"
#include "rectangle.h"
#include "triangle.h"
#include "ellipse.h"

class Terminal {
public:
  Terminal(std::string input) {
    //input string should be {Shape}+{Feature to sort}+{Order}
    //if any of condition missing, the constructure should handle the exception by throwing std::string "invalid input"
    std::regex  m_regex ("(.*) (area|perimeter) (inc|dec)");
    std::cmatch m_cmatch;
    if(std::regex_match(input.c_str(), m_cmatch, m_regex)){
        //Split to each shape
        std::string str_shapes = m_cmatch[1].str() + " ";
        str_feature = m_cmatch[2].str();
        str_order = m_cmatch[3].str();
    		std::string part_str_shapes;
        Shape* res = nullptr;
    		size_t cut_posi = find_cut_point(str_shapes);
    		while (cut_posi != str_shapes.npos){
    			cut_posi++;
    			part_str_shapes = str_shapes.substr(0, cut_posi);
    			str_shapes = str_shapes.substr(cut_posi, str_shapes.size() - (cut_posi));
    			cut_posi = find_cut_point(str_shapes);

          res = Str2Shape(part_str_shapes.c_str());
          if(res)
            m_shapes.push_back(res);
    		}
    }
    else {
      throw (std::string)"invalid input";
    }

    if(m_shapes.size() == 0){
      throw (std::string)"invalid input";
    }
    else{
      //quickSort
      if(str_order == "inc")
        quickSort(m_shapes.begin(), m_shapes.end(), AscendingCompare(str_feature));
      else if(str_order == "dec")
        quickSort(m_shapes.begin(), m_shapes.end(), DescendingCompare(str_feature));
    }
  }

  ~Terminal(){
    for (auto m_shape : m_shapes) {
        delete m_shape;
    }
  }

  std::string info() {
    std::string result = "";
    for (auto m_shape : m_shapes)
      result = result + m_shape->info() + " ";
    return result;
  }

  std::string showResult() {
    std::string result = "";
    char c_res[10];
    for (auto m_shape : m_shapes) {
      if(str_feature == "area")
        sprintf(c_res, "%.3f", m_shape->area());
      else if(str_feature == "perimeter")
        sprintf(c_res, "%.3f", m_shape->perimeter());
      result = result + c_res + "\n";
    }

    if(result != "")
      return result.substr(0, result.size() - 1);
    else
      return "";
  }

private:
  std::string str_feature = ""; //area or perimeter
  std::string str_order = "";
  std::vector<Shape*> m_shapes;

  Shape* Str2Shape(const char* str_shape){
    std::regex Rectangle_regex("\\s*Rectangle \\s*\\(\\s*([0-9]+.?[0-9]*),\\s*([0-9]+.?[0-9]*)\\)");
  	std::regex Ellipse_regex("\\s*Ellipse \\s*\\(\\s*([0-9]+.?[0-9]*),\\s*([0-9]+.?[0-9]*)\\)");
  	std::regex Triangle_regex("\\s*Triangle \\s*\\(\\s*\\[(\\+|-?[0-9]+.?[0-9]*),(\\+|-?[0-9]+.?[0-9]*)\\], \\s*\\[(\\+|-?[0-9]+.?[0-9]*),(\\+|-?[0-9]+.?[0-9]*)\\], \\s*\\[(\\+|-?[0-9]+.?[0-9]*),(\\+|-?[0-9]+.?[0-9]*)\\]\\)");
  	std::cmatch m_shape_cmatch;

    Shape* res = nullptr;
    try {
      if (std::regex_match(str_shape, m_shape_cmatch, Rectangle_regex)) {
        res = new Rectangle(std::stod(m_shape_cmatch[1]), std::stod(m_shape_cmatch[2]));
      }
      else if (std::regex_match(str_shape, m_shape_cmatch, Ellipse_regex)) {
        res = new Ellipse(std::stod(m_shape_cmatch[1]), std::stod(m_shape_cmatch[2]));
      }
      else if (std::regex_match(str_shape, m_shape_cmatch, Triangle_regex)) {
        std::vector<TwoDimensionalCoordinate*> vec = { new TwoDimensionalCoordinate(std::stod(m_shape_cmatch[1]), std::stod(m_shape_cmatch[2])),
                                                       new TwoDimensionalCoordinate(std::stod(m_shape_cmatch[3]), std::stod(m_shape_cmatch[4])),
                                                       new TwoDimensionalCoordinate(std::stod(m_shape_cmatch[5]), std::stod(m_shape_cmatch[6]))};
        res = new Triangle(vec);
      }
    }
    catch(std::string e) {
      res = nullptr;
    }
    return res;
  }

  size_t find_cut_point(std::string& str) {
  	size_t cut_point = str.find_first_of(')');
  	while (cut_point != str.npos && str[cut_point + 1] != ' ')
  		cut_point = str.find_first_of(')', cut_point + 1);
  	return cut_point;
  }
};
