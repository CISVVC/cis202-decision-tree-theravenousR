/*
   File: main.cpp
   Description: Decision Tree
   Author: Ryan Ignasiak
   Email: ignasiakr@student.vvc.edu
*/
/*
   This program will create a decision tree for an animal
   guessing game.
*/

#include <iostream>
#include <fstream>
#include <string>
#include "binary_tree.h"

Binary_tree read(istream& in) {
  std::string data;
  int level;
  in>>level;
  getline(in, data);
  if (level == -1) {
    return Binary_tree();
  }
  Binary_tree left = read(in);
  Binary_tree right = read(in);
  return Binary_tree(data, left, right);
}

void write(ostream& out, const Binary_tree& tree, int level) {
  if (tree.empty()) {
    out<<-1<<"\n";
    return;
  }
  out<<level<<tree.data()<<"\n";
  write (out, tree.left(), level + 1);
  write (out, tree.right(), level + 1);
}

/*
 * helper function that will help with definite or indefinite 
 * articles in a string
 */
std::string article(const std::string& entry) {
    std::string article = "a";
    if (std::string("aeiou").find(entry[0]) != std::string::npos) {
        article =  "an";
    }
    return article;
}

int main(int argc,char **argv) {
    bool done = false;
    std::string temp;
    std::string response;
    std::string answer;
    if(argc > 1) {  
      std::cout << "The first argument is: " << std::endl;
      std::cout << argv[1] << std::endl;
    }
    Binary_tree root;  
    //  get the filename from the command line arguments
    std::ifstream in_file(argv[1]);
    //  open the file stream
    //  initialize the root Binary_tree variable with data from the 
    //  file stream to initialize the decision tree root by calling
    //  the read function
    root = read(in_file);
    Binary_tree question_tree = root;
    Binary_tree extra;

    while(!done) {

      Binary_tree left = question_tree.left();
      Binary_tree right = question_tree.right();

      if (left.empty() && right.empty()) {
        std::cout<<"Is it "<<article(question_tree.data())<<question_tree.data()<<"? (y/n)"<<std::endl;
        std::cin>>response;

        if (response == "y") {
          std::cout<<"I guessed it!"<<std::endl;
        }
        else {
          std::cout<<"I give up. What is it?"<<std::endl;
          std::cin.ignore();
          getline(std::cin, answer);
          std::cout<<"Please give me a question that is true for "<<answer<<" and false for"<<question_tree.data()<<":"<<std::endl;
          getline(std::cin, temp);
          extra = question_tree.data();
          Binary_tree finish(" " + answer);
          question_tree.set(" " + temp, finish, extra);
        }

        std::cout<<"May I try again? (y/n)\n";
        std::cin>>response;

        if (response == "n") {
          done = true;
          std::ofstream out_file("questions.dat");
          write(out_file, root, 0);
        }
        else {
          question_tree = root;
        }

      }
      else {

        do {
          std::cout<<question_tree.data()<<" (y/n)"<<std::endl;
          std::cout<<"   ";
          std::cin>>response;
        }
        while(response != "y" && response != "n");

        if (response == "y") {
          question_tree = left;
        }
        else {
          question_tree = right;
        }

      }

      }
      return 0;
}
