#ifndef TOOLS_H
#define TOOLS_H
#include "sys.h"
#include <stdlib.h>
#include <getch.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include "teacher.h"
#include "admin.h"
extern int Ch;	//	输入账号、密码时接收的键盘键值
extern int Len;	//	输入账号、密码时的位数
int sys_show(void);   //展示主界面
bool tch_login(void);	//教师登录系统
void anykey_continue(void);	//按任意键继续
void msg_show(const char* msg,float sec); //延时展示信息
char *int_to_string(int num);	//将int型转换成字符串
void hchange_password_t(char* s);	//教师登录密码判断系统
void op_stufile(char* s);		//打开学生文件读取本地学生数量
void wr_stufile(char* s);		//将内存所有学生信息写入本地学生记录文件
void my_secret(char* s);		//将普通密码加密
void op_teafile(char* s);		//打开教师文件读取本地学生数量
void hide_input(char* s);     	 //用户不显示输入
void display_input(char* s);	 //	用户显示输入
int limit_len(int len,char* string);   //限制文件名长度
//void is_dispaly_login(void);    //教师登录时是否显示密码
#endif//TOOLS_H
