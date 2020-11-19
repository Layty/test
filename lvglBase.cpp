#include "lvglBase.h"


#define IO_KeyOk_Dt 84
#define IO_KeyUp_Dt 80
#define IO_KEY_RIGHT 79
#define IO_KEY_LEFT 77
#define IO_KEY_DOWN 73
#define IO_KeyEsc_Dt 13
#define IO_KeyEn_Ct 64


static void keypad_init(void);
static bool keypad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
static uint32_t keypad_get_key(void);

void initGpio(int n)
{
    FILE * fp =fopen("/sys/class/gpio/export","w");
    if (fp == NULL)
    {
        perror("export open filed");
    }
    else
    {
        fprintf(fp,"%d",n);
        fclose(fp);
    }
}   //create gpio file

void setGpioDirection(int n,const char *direction)
{
    char path[100] = {0};
    sprintf(path,"/sys/class/gpio/gpio%d/direction",n);
    FILE * fp =fopen(path,"w");
    if (fp == NULL)
    {
        perror("direction open filed");
    }
    else
    {
        fprintf(fp,"%s",direction);
        fclose(fp);
    }
}   //set gpio "in" or "out"

void setGpioValue(int n,int val)
{
    char path[100] = {0};
    sprintf(path,"/sys/class/gpio/gpio%d/value",n);
    FILE * fp =fopen(path,"w");
    if (fp == NULL)
    {
        perror("direction open filed");
    }
    else
    {
        fprintf(fp,"%d",val);
        fclose(fp);
    }
}

int getGpioValue(int n)
{
    int ret=-1;
    char path[100] = {0};
    char value_str[3];
    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/value", n);
    FILE * fp =fopen(path,"r");
    if (fp == NULL)
    {
        perror("direction open filed");
    }
    else
    {
        if(fread(value_str, 3, 1, fp)<0)
        {
            perror("Failed to read value!");
        }
        else
        {
            ret=atoi(value_str);
        }
        fclose(fp);
    }
    return ret;
}   //get gpio(n)'s value


/* Initialize your buttons */
static void button_init(void)
{
    /*Your code comes here*/
    initGpio(IO_KeyOk_Dt);
    setGpioDirection(IO_KeyOk_Dt,"in");
    initGpio(IO_KeyOk_Dt);

    initGpio(IO_KeyUp_Dt);
    setGpioDirection(IO_KeyUp_Dt,"in");
    initGpio(IO_KeyUp_Dt);

    initGpio(IO_KEY_RIGHT);
    setGpioDirection(IO_KEY_RIGHT,"in");
    initGpio(IO_KEY_RIGHT);

    initGpio(IO_KEY_LEFT);
    setGpioDirection(IO_KEY_LEFT,"in");
    initGpio(IO_KEY_LEFT);

    initGpio(IO_KEY_DOWN);
    setGpioDirection(IO_KEY_DOWN,"in");
    initGpio(IO_KEY_DOWN);

    initGpio(IO_KeyEsc_Dt);
    setGpioDirection(IO_KeyEsc_Dt,"in");
    initGpio(IO_KeyEsc_Dt);


    initGpio(IO_KeyEn_Ct);
    setGpioDirection(IO_KeyEn_Ct,"out");
    setGpioValue(IO_KeyEn_Ct,1);
}

/* Initialize your keypad */
static void keypad_init(void)
{
    /*Your code comes here*/
    button_init();
}

/* Will be called by the library to read the mouse */
static bool keypad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    static uint32_t last_key = 0;

    /*Get the current x and y coordinates*/
    // mouse_get_xy(&data->point.x, &data->point.y);

    /*Get whether the a key is pressed and save the pressed key*/
    uint32_t act_key = keypad_get_key();
    if(act_key != 0) {
        data->state = LV_INDEV_STATE_PR;

        /*Translate the keys to LVGL control characters according to your key definitions*/
        switch(act_key) {
            case 1:
                act_key = LV_KEY_NEXT;
                break;
            case 2:
                act_key = LV_KEY_PREV;
                break;
            case 3:
                act_key = LV_KEY_LEFT;
                break;
            case 4:
                act_key = LV_KEY_RIGHT;
                break;
            case 5:
                act_key = LV_KEY_ENTER;
                break;
        }

        last_key = act_key;
    } else {
        data->state = LV_INDEV_STATE_REL;
    }

    data->key = last_key;

    /*Return `false` because we are not buffering and no more data to read*/
    return false;
}

/*Get the currently being pressed key.  0 if no key is pressed*/
static uint32_t keypad_get_key(void)
{
    int a =getGpioValue(IO_KeyUp_Dt);
    //  printf("%d\n",a);
    if(a==0)
    {
        return LV_KEY_UP ;
    }

    int b =getGpioValue(IO_KEY_DOWN);
    //  printf("%d\n",a);
    if(b==0)
    {
        return LV_KEY_DOWN ;
    }


    a =getGpioValue(IO_KEY_RIGHT);
    //  printf("%d\n",a);
    if(a==0)
    {
        return LV_KEY_RIGHT ;
    }


    a =getGpioValue(IO_KEY_LEFT);
    //  printf("%d\n",a);
    if(a==0)
    {
        return LV_KEY_LEFT ;
    }


    a =getGpioValue(IO_KeyOk_Dt);
    //  printf("%d\n",a);
    if(a==0)
    {
        return LV_KEY_ENTER ;
    }


    a =getGpioValue(IO_KeyEsc_Dt);
    //  printf("%d\n",a);
    if(a==0)
    {
        return LV_KEY_ESC ;
    }


    return 0;
}


#define DISP_BUF_SIZE (80 * LV_HOR_RES_MAX)
lvglBase::lvglBase(/* args */):lv_hor(LV_HOR_RES_MAX),lv_ver(LV_VER_RES_MAX)
{

    printf("Init\n");
    /*LittlevGL init*/
    lv_init();

    /*Linux frame buffer device init*/
    fbdev_init();

    /*A small buffer for LittlevGL to draw the screen's content*/
    static lv_color_t buf[DISP_BUF_SIZE];

    /*Initialize a descriptor for the buffer*/
    static lv_disp_buf_t disp_buf;
    lv_disp_buf_init(&disp_buf, buf, NULL, DISP_BUF_SIZE);
    /*Initialize and register a display driver*/
    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.buffer   = &disp_buf;
    disp_drv.flush_cb = fbdev_flush;
    lv_disp_drv_register(&disp_drv);


    inputInit();
    g = lv_group_create();
    lv_indev_set_group(input, g);
    scr=lv_scr_act();

//    base=lv_obj_create(scr,NULL);

}

void lvglBase::inputInit() {
    keypad_init();
    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv); /*Basic initialization*/
    indev_drv.type =LV_INDEV_TYPE_KEYPAD;
    indev_drv.read_cb =keypad_read; /*See below.*/
    /*Register the driver in LVGL and save the created input device object*/
    input = lv_indev_drv_register(&indev_drv);
}


int lvglBase::getLvHor() const {
    return lv_hor;
}

void lvglBase::setLvHor(int lvHor) {
    lv_hor = lvHor;
}

int lvglBase::getLvVer() const {
    return lv_ver;
}

void lvglBase::setLvVer(int lvVer) {
    lv_ver = lvVer;
}



void lvglBase::clearGroup() {
    lv_group_remove_all_objs(g);
    lv_group_set_wrap(g, true);
}


void lvglBase::addGroup(std::vector<lv_obj_t *> &v) {
    for (auto ch : v)
    {
        lv_group_add_obj(g,ch);
    }
}

void lvglBase::addGroup(lv_obj_t *v) {
    lv_group_add_obj(g, v);
    wait();
//    lv_indev_wait_release(input);
}


void lvglBase::defaultPrintEv( struct _lv_obj_t * obj, lv_event_t e) {
    const char echoEvent[][100]=
            {
                    "LV_EVENT_PRESSED",             /**< The object has been pressed*/
                    "LV_EVENT_PRESSING",            /**< The object is being pressed (called continuously while pressing)*/
                    "LV_EVENT_PRESS_LOST",          /**< User is still pressing but slid cursor/finger off of the object */
                    "LV_EVENT_SHORT_CLICKED",       /**< User pressed object for a short period of time, then released it. Not called if dragged. */
                    "LV_EVENT_LONG_PRESSED",        /**< Object has been pressed for at least `LV_INDEV_LONG_PRESS_TIME`.  Not called if dragged.*/
                    "LV_EVENT_LONG_PRESSED_REPEAT", /**< Called after `LV_INDEV_LONG_PRESS_TIME` in every
                               `LV_INDEV_LONG_PRESS_REP_TIME` ms.  Not called if dragged.*/
                    "LV_EVENT_CLICKED",             /**< Called on release if not dragged (regardless to long press)*/
                    "LV_EVENT_RELEASED",            /**< Called in every cases when the object has been released*/
                    "LV_EVENT_DRAG_BEGIN",
                    "LV_EVENT_DRAG_END",
                    "LV_EVENT_DRAG_THROW_BEGIN",
                    "LV_EVENT_GESTURE",           /**< The object has been gesture*/
                    "LV_EVENT_KEY",
                    "LV_EVENT_FOCUSED",
                    "LV_EVENT_DEFOCUSED",
                    "LV_EVENT_LEAVE",
                    "LV_EVENT_VALUE_CHANGED",      /**< The object's value has changed (i.e. slider moved) */
                    "LV_EVENT_INSERT",
                    "LV_EVENT_REFRESH",
                    "LV_EVENT_APPLY",  /**< "Ok", "Apply" or similar specific button has clicked*/
                    "LV_EVENT_CANCEL", /**< "Close", "Cancel" or similar specific button has clicked*/
                    "LV_EVENT_DELETE", /**< Object is being deleted */
                    "_LV_EVENT_LAST" /** Number of events*/

            };



    printf("%s\n",echoEvent[e]);
    fflush(stdout);
}

lv_obj_t *lvglBase::getScr() const {
    return scr;
}

lvglBase *lvglBase::instance() {
    static lvglBase me;

    return &me;
}

lv_group_t *lvglBase::getG() const {
    return g;
}

void lvglBase::wait() {
//    lv_indev_wait_release(input);

}



