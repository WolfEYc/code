/*
 *
 * This code is copyrighted (c) 2021 by
 * Texas A&M Computer Science
 *
 *	There will be RIGOROUS cheat checking on your exams!!
 *	DON'T POST ANYWHERE!! such as CHEGG, public Github, etc
 *  You will be legally responsible.
 */

#include <string>
#include <stdexcept>
#include "Tag.h"

using std::string;
using std::vector;

Tag::Tag(string tagName) /* TODO(student): initialize */ : tagName(tagName) {
  // TODO(student): implement constructor checks
  if (tagName.length() < 2 || tagName[0] != '#' || !islower(tagName[1]) || tagName[-1] == '!' || tagName[-1] == ',' || tagName[-1] == '.' || tagName[-1] == '?') {
      throw std::invalid_argument("Tag constructor: invalid parameter values");
  }
  for (int i=2; i<tagName.length(); i++) {
      if (!islower(tagName[i])) {
          throw std::invalid_argument("Tag constructor: invalid parameter values");
      }
  }
}

string Tag::getTagName() {
  // TODO(student): implement getter
  return tagName;
}

vector<Post*>& Tag::getTagPosts() {
  // TODO(student): implement getter
  return tagPosts;
}

void Tag::addTagPost(Post* post) {
  // TODO(student): add post to tag posts
  if (post == nullptr) {
      throw std::invalid_argument("addUserPost: post is nullptr");
  }
  tagPosts.push_back(post);
}
