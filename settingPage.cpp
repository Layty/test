#include "settingPage.h"

page * newWin;
lv_group_t *g;
lv_obj_t* btnEsc;
lv_obj_t* btnOk;


void esccb(struct _lv_obj_t * obj, lv_event_t e) {

    printf("cbesc\n");
    uint32_t *key = (uint32_t*)lv_event_get_data();
    if(e==LV_EVENT_RELEASED)
    {
        printf("Clicked: %s\n", lv_list_get_btn_text(obj));
        if(obj==btnEsc)
        {
            //删除自身页面
            printf("del page to back\n");
            pangeManage::instance()->delPage();
            lvglBase::instance()->wait();


        }
        else if (obj==btnOk)
        {
            printf("want to enter new page\n");
        }

    }else if (e == LV_EVENT_KEY)
    {
        printf("enter key =%d \n",*key);
        if (*key == LV_KEY_LEFT || *key == LV_KEY_UP || *key == LV_KEY_PREV)
        {
            lv_group_focus_prev(g);

        }
        else if (*key == LV_KEY_RIGHT || *key == LV_KEY_DOWN || *key == LV_KEY_NEXT)
        {
            lv_group_focus_next(g);
        }
        else if (*key == LV_KEY_ESC)
        {
            pangeManage::instance()->delPage();
        }
    }
    else if(e == LV_EVENT_REFRESH)
    {
        pageLists::instance()->back()->open();
    }

}


void openSetting(struct _lv_obj_t  * obj, lv_event_t e){

    if(e==LV_EVENT_RELEASED)
    {
        newWin=pangeManage::instance()->creatPage();
        pageLists::instance()->push_back((page*)newWin);
        g=lvglBase::instance()->getG();

        lv_obj_t * label;
        btnEsc=lv_btn_create(newWin->getWin(),NULL);
        lv_obj_set_event_cb(btnEsc, esccb);
        lv_obj_align(btnEsc, NULL, LV_ALIGN_CENTER, 0, -40);
        label = lv_label_create(btnEsc, NULL);
        lv_label_set_text(label, "Esc");

        newWin->addGroup(btnEsc);



        btnOk=lv_btn_create(newWin->getWin(),NULL);
        lv_obj_set_event_cb(btnOk, esccb);
        lv_obj_align(btnOk, NULL, LV_ALIGN_CENTER, 0, 40);
        label = lv_label_create(btnOk, NULL);
        lv_label_set_text(label, "Ok");

        newWin->addGroup(btnOk);
        newWin->open();


    }

}

