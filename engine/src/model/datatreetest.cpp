#ifdef WIN32
#pragma warning( disable : 4786 )  
#endif 

#include <iostream>

#include "datatreetest.h"

//#include "model/debugpersistor.h"

#include "datatree.h"

#include "standardinode.h"


DataTreeTest::DataTreeTest():  EasyTest("DataTreeTest","")
{}

DataTreeTest::~DataTreeTest()
{}

void DataTreeTest::pre() throw(std::runtime_error)
{}

void DataTreeTest::run() throw(std::runtime_error)
{
  //DebugPersistor dbg(std::cout);
  
  DataTree tree;
  
  StandardINode* firstNode = new StandardINode(100);
  DataTreeTypes::INodeNumber first = tree.createObject(DataTree::ROOT,
						       firstNode);
  
  DataTreeTypes::INodeType second = tree.createObject(first,
						      new StandardINode(20));
  DataTreeTypes::INodeType third = tree.createObject(DataTree::ROOT,
						     new StandardINode(40));
  
  std::cout << tree;
  
  tree.deleteObject(first);
  
  std::cout << tree;
  
  first = tree.createObject(DataTree::ROOT, new StandardINode(111));

  std::cout << tree;

  utils::Buffer buf((const unsigned char*)"Hallo",5);

  tree.setData(first,buf);
  
  std::cout << tree;

  tree.deleteObject(first);

  std::cout << tree;
}

void DataTreeTest::post() throw(std::runtime_error)
{}
