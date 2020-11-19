//
// Created by vmuser on 11/19/20.
//

#ifndef LVGL_PAGELISTS_H
#define LVGL_PAGELISTS_H

#include "page.h"

class pageLists {
public:
    std::vector<page*> listPage;
    static pageLists *instance()
    {
        static pageLists me;
        return &me;
    }

    bool empty()
    {
        return listPage.empty();
    }

    void push_back(page* p)
    {
        listPage.push_back(p);
    }

    void pop_back()
    {
        listPage.pop_back();
    }

    page* back(){return listPage.back();}

};


#endif //LVGL_PAGELISTS_H
