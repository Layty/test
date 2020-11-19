//
// Created by vmuser on 11/19/20.
//

#ifndef LVGL_PANGEMANAGE_H
#define LVGL_PANGEMANAGE_H

#include "page.h"
#include "pageLists.h"

class pangeManage {
public:
    static pangeManage *instance()
    {
        static pangeManage me;
        return &me;
    }

    page * creatPage();
    void delPage();


};


#endif //LVGL_PANGEMANAGE_H
