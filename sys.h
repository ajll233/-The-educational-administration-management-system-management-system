#ifndef SYS_H
#define SYS_H

void init_sys(void);  //初始化系统
void run_sys(void);	  //运行系统
void end_sys(void);	 //释放系统内存

typedef struct Student
{
    char name[20];	//学生姓名
    char sex;		//学生性别
    char id[12];	//学生学号
    char key[16];	//学生密码
    char cnt;		//输入密码次数
    int flag;		//学生密码是否被锁定
    double chi;		//学生语文成绩
    double math;	//学生数学成绩
    double eng;		//学生英语成绩
    char is_school;	//0在校，1离校
}Student;
#define STU_MAX 1000 //定义宏学生最大数量

//学生
extern Student *stu;	//声明学生结构体变量
extern int Std_num;		//登录成功学生
extern int Std_i;		//学生个数

//老师
typedef struct Teacher
{
    char name[20];  //教师姓名
    char sex;       //教师性别
    char id[6];     //教师工号
    char key[16];   //教师密码
    char cnt;		//输入密码次数
    int flag;       //教师密码是否被锁定
    char is_school;	//教师是否在校
}Teacher;
extern Teacher *tea;

#define TEA_MAX 100	 //定义教职工最大数量
extern int Tch_n;          
extern int Tch_i;
extern int End;
extern int All_tch;
extern char Str[10];


typedef struct Extra  //接收一次学生成绩
{
	char id[12];
	double chi;		//学生语文成绩
    double math;	//学生数学成绩
    double eng;		//学生英语成绩
}Extra;
extern Extra *ext;
typedef struct Other  //接收一次学生基本信息
{
	char name[20];	//学生姓名
    char sex;		//学生性别
}Other;
extern Other *oth;
#endif//SYS_H
