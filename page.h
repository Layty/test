//
// Created by vmuser on 11/19/20.
//

#ifndef LVGL_PAGE_H
#define LVGL_PAGE_H
#include "lvglBase.h"


class page {

public:
    lv_obj_t *win;
    std::vector<lv_obj_t * >objGroup;

public:
    page(lv_obj_t* parent);
    virtual ~page();

    void setGroups(std::vector<lv_obj_t* >&v){objGroup=v;}
    void addGroup(lv_obj_t *v){objGroup.push_back(v);}
    lv_obj_t *getWin() const;

    virtual void close();
    virtual void open(void);


};


#endif //LVGL_PAGE_H
