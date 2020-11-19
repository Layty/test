#ifndef LVGL_BASE_H
#define LVGL_BASE_H

#ifdef LV_CONF_INCLUDE_SIMPLE
#include "lvgl.h"
#include "lv_ex_conf.h"
#else
#include "../lvgl/lvgl.h"
#include "../lv_ex_conf.h"
#endif


#include <vector>
#include <string>

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#include "lv_lib_freetype/lv_freetype.h"
#include "lvgl/lvgl.h"
#include "lv_drivers/display/fbdev.h"
#include "lv_examples/lv_examples.h"

class page;


typedef struct
{
    lv_obj_t * obj;
    bool group;
}myLvObj_t;




/**
 * @brief 单例模式,只允许存在一个lvgl_base 控制交互,其他类去操作这个类
 * 
 */
class lvglBase
{
public:
    int lv_hor;
    int lv_ver;
    lv_group_t * g;
    lv_indev_t * input;
    lv_obj_t * scr;             //top scr,init and const





    static lvglBase *instance();



    lvglBase(/* args */);

    lv_obj_t *getScr() const;
    lv_group_t *getG() const;
    int getLvHor() const;
    void setLvHor(int lvHor);
    int getLvVer() const;
    void setLvVer(int lvVer);


    void inputInit();
    void wait();
    void clearGroup();
    void addGroup(std::vector<lv_obj_t*>&v);
    void addGroup(lv_obj_t* v);


    static void defaultPrintEv(struct _lv_obj_t  * obj, lv_event_t e);



};





#endif // !LVGL_BASE_H
