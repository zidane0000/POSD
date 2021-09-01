#include "terminal.h"

//basic C++ library
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;

int main(int argc, char *argv[]){
  //argv[0]: The path of binary file.
  //argv[1]: The full name of input file.
  //argv[2]: The full name of output file.
  //argv[3]: The feature of shape that sorting basis on.
  //argv[4]: The 'inc' for increasing, 'dec' for decreasing.


  std::fstream in_file;
  in_file.open(argv[1], std::ios::in);
  if(!in_file){
    cout << "Can't Open file" << argv[1] << endl;
    return 0;
  }
  else
    cout << "Open file" << argv[1] << " Success" << endl;

  std::string in_str( (std::istreambuf_iterator<char>(in_file) ),
                     (std::istreambuf_iterator<char>()    ) );
  in_file.close();

  while ( in_str.find ("\r\n") != string::npos )
    in_str.erase ( in_str.find ("\r\n"), 2 );

  for(int i = 0; i < in_str.size(); i++){
    if(in_str[i] == ')') {
      i++;
      in_str.insert(i," ");
    }
  }
  in_str = in_str + argv[3] + " " + argv[4];

  cout << "input : " << in_str << endl;

  try{
    Terminal m_terminal(in_str);
    std::fstream out_file(argv[2], std::ios::out);
    std::string showres = m_terminal.showResult();
    cout << "showResult : " << showres << endl;
    out_file << showres;
    out_file.close();
  }
  catch(string e) {
      std::cout << e << std::endl;
  }

  return 0;
}
