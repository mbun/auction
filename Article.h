/*
 * Article.h
 *
 *  Created on: May 7, 2015
 *      Author: Yi-Hsiu
 */

#ifndef ARTICLE_H_
#define ARTICLE_H_

#include <string>
#include <iostream>
using namespace std;

class Article
{
private:
	string description;

public:
    Article(string s);
    string getDescription();
    friend ostream& operator<<(ostream& os, const Article& article);
};


#endif /* ARTICLE_H_ */
