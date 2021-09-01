#ifndef _SCANNER_
#define _SCANNER_

class Scanner {
public:
  Scanner(std::string input): m_input(input) {
    std::cout << "Scanner: " << input << std::endl;
  }

  std::string nextToken() {
    // DO NOT use regular expression to implement.
    // return next token.
    // throw exception std::string "next char doesn't exist." if next token not found.
    if(m_input.empty()) {
      throw std::string("next char doesn't exist.");
    }
    else {
      //Ellipse (%.3f, %.3f)
      //Rectangle (%.3f, %.3f)
      //Triangle (%.3f, %.3f, %.3f, %.3f, %.3f, %.3f)
      //CompoundShape { ... }
      while(m_input[0] == ' ')
        m_input = m_input.substr(1, m_input.size() - 1);

      if((m_input[0] < 48 || m_input[0] > 122) && (m_input[0] != '-')) {  //非0(48)-9、a(97)-z(122)、A(65)-Z(90)
        char symbol_only = m_input[0];
        m_input = m_input.substr(1, m_input.size() - 1);
        return string(1, symbol_only);
      }
      else if((m_input[0] >= 65 && m_input[0] <= 122) && (m_input[0] != '-')) {  //英文字母
        int cut_posi = m_input.find_first_of(' ');
        std::string cut = m_input.substr(0, cut_posi);
        m_input = m_input.substr(cut_posi + 1, m_input.size() - cut_posi);
        return cut;
      }
      else { //數字
        int comma_posi = m_input.find_first_of(',');
        int brackets_posi = m_input.find_first_of(')');
        int cut_posi;
        if(comma_posi < 0)
          cut_posi = brackets_posi;
        else if(brackets_posi < 0)
          cut_posi = comma_posi;
        else
          cut_posi = comma_posi < brackets_posi ? comma_posi : brackets_posi;
        std::string cut = m_input.substr(0, cut_posi);
        //std::cout << m_input << "-" << cut_posi << "-" << cut << std::endl;
        m_input = m_input.substr(cut_posi, m_input.size() - cut_posi);
        //std::cout << "after:" << m_input << std::endl;
        return cut;
      }
    }
  }

private:
  std::string m_input;
};

#endif
