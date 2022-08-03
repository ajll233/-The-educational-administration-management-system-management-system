#ifndef STUDENT_H
#define STUDENT_H

#include <stdbool.h>

void student_view(void); 	  //	学生端
int show_student_view(void);  //	学生端功能显示界面
void stu_cg_pas(char* s);     // 	学生修改密码
void stu_find_score(void);    //	学生查询成绩
void stu_find_inf(void);      //	学生个人信息显示
void swap(double* s1, double* s2);//	成绩交换函数
void stu_login(void);	//	学生登录输入学号、密码函数
int sort_rank(double* arr, double grade);	//	成绩排序、排名	

#endif//STUDENT_H
