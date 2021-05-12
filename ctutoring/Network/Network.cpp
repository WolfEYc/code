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
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Network.h"

using std::string;
using std::vector;

Network::Network() {
  // empty containers of vectors already created
  // no implementation is needed here
}

void Network::loadFromFile(string fileName) {
  // TODO(student): load user and post information from file
    std::ifstream name(fileName);
    if (!name.is_open()) {
      throw std::invalid_argument("File could not be opened");
    }
    try{
      string line;

      while (getline(name, line)) {
        string type;
        string username;
        unsigned int PostId;
        string PostText;
        string new_word;
        
        std::stringstream word;
        word << line; 
        word >> type;
        
        if (type == "User") {
          word >> username;          
          addUser(username);          
        }
        if (type == "Post") {
          word >> PostId;
          word >> username;
          while (word >> new_word) {
            
            PostText = PostText + " " + new_word;
          }
          addPost(PostId, username, PostText);
        }

      } 
    } catch (...){
      throw std::runtime_error("runtime error");
    }

}

void Network::addUser(string userName) {
  // TODO(student): create user and add it to network
  for (int i=0; i<userName.length(); i++) {
      userName[i] = tolower(userName[i]);
  }
  for (int i=0; i<users.size(); i++) {
      if (users[i]->getUserName() == userName) {
          throw std::invalid_argument("user constructor: name already exists");
      }
  }
  User* new_user = new User(userName);
  users.push_back(new_user);
  std::cout << "Added User " << userName << std::endl;
}

void Network::addPost(unsigned int postId, string userName, string postText) {
  // TODO(student): create post and add it to network
  bool found_name = false;
  User* found_user;
  for (int i=0; i<users.size(); i++) {
      if (users[i]->getUserName() == userName) {
          found_name = true;
          found_user = users[i];
      }
  }
  if (found_name = false) {
      throw std::invalid_argument("addPost constructor: name doesn't exist");
  }
  for (int i=0; i<posts.size(); i++) {
      if (posts[i]->getPostId() == postId) {
          throw std::invalid_argument("addPost: Id already exists");
      }
  }

  Post* new_post = new Post(postId, userName, postText);
  posts.push_back(new_post);
  found_user->addUserPost(new_post);
  vector<string> new_tags = new_post->findTags();   

  for (int i=0; i<new_tags.size(); i++) {
      bool found_tag = false;

      for (int j=0; j<tags.size(); j++) {

        if (new_tags[i] == tags[j]->getTagName()) {
          found_tag = true;
          tags[j]->addTagPost(new_post);
        }

      }
      try {
        if (found_tag == false) {
            Tag* new_tag = new Tag(new_tags[i]);
            tags.push_back(new_tag);
            tags.back()->addTagPost(new_post);
        }
      }
      catch (...) {
          std::cout << "Error caught";
      }
  }
  std::cout << "Added Post " << postId << " by " << userName << std::endl;
}

vector<Post*> Network::getPostsByUser(string userName) {
  // TODO(student): return posts created by the given user
  if (userName.length() == 0) {
    throw std::invalid_argument("username is empty");
  }

  for (int i=0; i<users.size(); i++) {
    if (users[i]->getUserName() == userName) {
      return users[i]->getUserPosts();      
    }
  }
  
  throw std::invalid_argument("username not found");
  
}

vector<Post*> Network::getPostsWithTag(string tagName) {
  // TODO(student): return posts containing the given tag
  vector<Post*> post_with_tag;
  bool found = false;
  if (tagName.length() == 0) {
    throw std::invalid_argument("tagName is empty");
  }
  for (int i=0; i<tags.size(); i++) {
    if (tags[i]->getTagName() == tagName) {
      return tags[i]->getTagPosts();
    }
  }
  if (!found) {
    throw std::invalid_argument("tagName not found");
  }
}

vector<string> Network::getMostPopularHashtag() {
  // TODO(student): return the tag occurring in most posts
  int max = 0;
  int count = 0;
  vector<string> MP_Hashtag;

  for(int i = 0; i<tags.size(); i++){
    if(tags[i]->getTagPosts().size() > max){
      max = tags[i]->getTagPosts().size();
    }
  }

  for(int i = 0; i < tags.size();i++){
    if(tags[i]->getTagPosts().size() == max){
      MP_Hashtag.push_back(tags[i]->getTagName());
    }
  }

  return MP_Hashtag;
}

/**
  * Destructor
  * Do not change; already implemented.
  */
Network::~Network() {
  for (unsigned int i = 0; i < users.size(); ++i) {
    delete users.at(i);
  }
  for (unsigned int i = 0; i < tags.size(); ++i) {
    delete tags.at(i);
  }
  for (unsigned int i = 0; i < posts.size(); ++i) {
    delete posts.at(i);
  }
}
