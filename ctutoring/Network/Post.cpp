/*
 *
 * This code is copyrighted (c) 2021 by
 * Texas A&M Computer Science
 *
 *	There will be RIGOROUS cheat checking on your exams!!
 *	DON'T POST ANYWHERE!! such as CHEGG, public Github, etc
 *  You will be legally responsible.
 */

#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>
#include "Post.h"

using std::string;
using std::vector;

Post::Post(unsigned int postId, string userName, string postText)
  : postId(postId), userName(userName), postText(postText) {
  if (postId == 0 || userName == "" || postText == "") {
    throw std::invalid_argument("post constructor: invalid parameter values");
  }
}

unsigned int Post::getPostId() {
  return postId;
}

string Post::getPostUser() {
  return userName;
}

string Post::getPostText() {
  return postText;
}

vector<string> Post::findTags() {
  // TODO(student): extracts candidate tags based on occurrences of # in the post
  string post_text = getPostText();
  std::stringstream mystring;
  mystring.str(post_text);
  string test = "";
  vector<string> tags;
  while (mystring >> test) {
      
      if (test[0] == '#') {
          while (test.back() == '!' || test.back() == ',' || test.back() == '.' || test.back() == '?') {
              test.pop_back();
          }
          for (int i=1; i<test.length(); i++) {
              test[i] = tolower(test[i]);
          }
          tags.push_back(test);
      }
  }
  return tags;
}
