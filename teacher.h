#ifndef TEACHER_H
#define TEACHER_H
#include "sys.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
void teacher_view(void);   	//教师端口登录界面
bool tch_login(void);	   	//教师登录密码判断系统   
void add_stu(void);        	//添加学生基本信息选择函数
void tch_del(void);		   	//删除学生
void tch_find(void);	   	//查找学生
void tch_mod(void);		   	//修改学生信息或者成绩
void tch_input(void);		//录入成绩
void tch_setstupas(void);	//重置学生密码
void tch_show_instu(void);	//显示所有在校学生
void tch_show_dstu(void);	//显示所有退出学生
void tch_unlock(void);		//解锁学生密码
void timport_stu(void);       //单个添加学生
void tbatch_import_stu(void); //批量导入学生
void menu(void);              //教师功能菜单
void tsingle_input(void);	  //单个录入成绩
void tbatch_input(void);	  //批量录入成绩
#endif//TEACHER_H
