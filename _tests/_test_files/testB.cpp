#include "gtest/gtest.h"
#include <iostream>
#include <cstring>
#include <vector>
#include <iomanip>
#include "../../includes/queue/MyQueue.h"
#include "../../includes/tokenizer/tokenizer.h"

using namespace std;

bool tokenizer(bool debug = true)
{
  if (debug){
    cout << "testB:: tokenizer() entering tokenizer" << endl;
  }
    string eq = "sin(x)";
    cout << eq << endl;
    Tokenizer token(eq);

    cout << "its built" << endl;

    Queue<Token*> _q = token.tokenize();

    cout << "should be: sin ( x )" << endl;
    _q.print_pointers();
  return true;
}

TEST(TOKENIZER, tokenizer) {
  
  //EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, tokenizer(false));
}




int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running testB.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}

