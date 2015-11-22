/*
 * Article.cpp
 *
 *  Created on: May 7, 2015
 *      Author: Yi-Hsiu
 */

#include "Article.h"

Article::Article(string s) {
    description = s;
}

string Article::getDescription() {
    return description;
}

ostream& operator<<(ostream& os, const Article& article)
{
    os << article.description << " (" << &article << ")";
    return os;
}