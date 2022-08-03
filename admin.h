#ifndef ADMIN_H
#define ADMIN_H

#include <string.h>
extern int tea_i;
void admin_view(void);        //校长端口登录界面
void admin_cg_pas(char* s);   //校长个人修改密码
int show_admin_view(void);	  //校长功能界面
void himport_tea(void);		  //添加教师
void hdelete_tea(void);		  //删除教师
void hshow_tea_in(void);	  //显示所有在职教师
void hshow_tea_drop(void);	  //显示所有离校教师
void hadd_account_tea(void);  //解锁教师帐号
void hreset_pas(void);		  //重置教师密码
#endif//ADMIN_H
