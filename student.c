#include <stdlib.h>
#include <string.h>
#include "student.h"
#include "tools.h"
#include "sys.h"

Student* stu;	//	学生结构体定义
	
int Std_i;		//	学生总数
int Std_num;	//	登录成功的学生
int Ch;			//	输入账号、密码时接收的键盘键值
int Len;		//	输入账号、密码时的位数
static char id[20];	//	用于存储用户本次输入的学号
static char key[16];	//	用于存储用户本次输入的密码
static int inschool_stu;	//	在校学生人数

void student_view(void)	//	学生端
{	
	Std_i = 0;	//	每次进入学生端，将学生总个数赋初值0，以免对后续不同学生读取文件信息产生影响
	//	打开学生信息文件并读取数据
	FILE* stdfile = fopen("student_inf.txt","r");	
	if(NULL == stdfile)
	{
		printf("数据打开错误!\n");	//	若路径中不存在学生信息文件，向用户提示错误信息并退出学生端
		return;
	}
	while((-1 != fscanf(stdfile,"%s %c %s %s %hhd %d %lf %lf %lf %hhd ",stu[Std_i].name,&stu[Std_i].sex,stu[Std_i].id,stu[Std_i].key,&stu[Std_i].cnt,&stu[Std_i].flag,&stu[Std_i].chi,&stu[Std_i].math,&stu[Std_i].eng,&stu[Std_i].is_school)))	
	{
		Std_i++;	//	每完成一次学生信息的读取，学生总数加一	
	}
	fclose(stdfile);
	//	所有学生信息读取到结构体中后，解密密码
	for(int k=0; k<Std_i; k++)
	{
		for(int l=0; l<strlen(stu[k].key); l++)
		{
			if(0 == l%2)	stu[k].key[l] -= 10;
			else	stu[k].key[l] += 10;
		}
	}
	system("clear");
	//	用户输入学号和密码
	stu_login();
	for(;;)
	{
		system("clear");
		Std_num = 0;	//	默认学生信息文件中第1位进入登录界面，方便后续程序执行判断账号密码时不会遗漏判断
		//	当当前学生编号不超过学生总个数的时候，进入判断判断学号密码循环
		while(Std_num<Std_i)	
		{
			//	当前编号学生的学号与用户输入的学号相同，进入if语句判断密码
			if(0 == strcmp(id,stu[Std_num].id))
			{
				//	判断用户输入的学号是否处于离校状态
				if(1 == stu[Std_num].is_school)	
				{
					printf("你已离校,无法进入系统\n");
					anykey_continue();
					system("clear");
					return;
				}
				//	判断用户输入的学号是否处于锁定状态
				if(0 == stu[Std_num].flag)	
				{
					printf("学号已被锁定,请联系老师解锁\n");
					anykey_continue();
					system("clear");
					return;
				}
				//	用户输入的密码与该学号在学生信息文件中的密码相同，进入if语句块判断密码的状态
				if(0 == strcmp(key,stu[Std_num].key))	
				{
				//	该学号在学生信息文件中的密码为123456，代表该学生第一次登录，强制进行修改密码
					if(0 == strcmp(stu[Std_num].key,"123456"))	
					{
				//	密码修改完成后，跳出while循环，重新进入for死循环，重新输入账号密码
						stu_cg_pas(stu[Std_num].key);
						stu[Std_num].cnt = 0;
						system("clear");
						break;	
					}
			//	登录成功，将该学生的登录次数置为-1,方便后续判断，并用break跳出while判断学号密码循环
					system("clear");
					stu[Std_num].cnt = -1;	
					msg_show("登录成功\n",1.5); 
					break;
				}
			//	用户输入的密码与该学号在学生信息文件中的密码不同，进入else语句块判断并修改该学号的状态
				else
				{
					stu[Std_num].cnt += 1;
			//	该学号的输入次数未到达3次，提示用户错误信息，break跳出while循环判断后续条件
					if(3 != stu[Std_num].cnt)	
					{
						printf("学号或密码错误,请检查\n");	
						anykey_continue();
					}
			//	判断该学号输入次数达到3次，直接break跳出while循环进入后续判断
					system("clear");
					break;
				}
			}
			Std_num++;
		}
		if(Std_num == Std_i)	//	while循环结束后，如果当前学生的编号与学生总数相同，证明while循环是在条件不满足时自动退出，也就是说输入的用户不在后台信息中
		{
			printf("学号或密码错误,请检查\n");
			anykey_continue();
			system("clear");
		}
		//	while循环人为break退出时
		else
		{
			if(-1 == stu[Std_num].cnt)	//	当该学生的登录次数为-1时，即登录成功
			{
				stu[Std_num].cnt = 0;	//	登录成功后，将该学生的登录次数置为0，并跳出登录死循环
				break;
			}
			else if(3 == stu[Std_num].cnt) //	当该账号的登录次数为3时
			{
				stu[Std_num].flag = 0;	//	锁定账号
				printf("学号已被锁定,请联系老师解锁\n");
				anykey_continue();
				system("clear");
				return;
			}
		}
		//	帐号或密码错误并且该学号没有被锁定时，再次执行输入学号密码函数
		stu_login();		
	}
	//学生功能界面
	for(;;)
	{
		switch(show_student_view()) 
		{
			case '1':	stu_find_score();	break;			//	查询成绩功能	
			case '2':	stu_cg_pas(stu[Std_num].key);break;	//	修改密码功能(传入的参数为该学号学生的密码)
			case '3':	stu_find_inf();		break;			//	查询个人信息功能
			case '4':	return;								//	退出学生端
		}
	}
}

void stu_cg_pas(char* s) // 学生修改密码
{
	char str[20] = {};	//	用户输入的新密码
	char confirm_str[16] = {};	//	用户输入的确认密码
	//	修改密码
	for(;;)
	{
		system("clear");
		printf("请修改密码\n");
		hide_input(str);	//	用户不显示输入
		if(16 >= strlen(str) && 8 <= strlen(str) && 0 != strcmp(s,str))	//	输入的密码在8-16位
		{
			printf("请确认密码\n");
			hide_input(confirm_str);	//	用户不显示输入
			if(0 == strcmp(str,confirm_str))
			{
				strcpy(stu[Std_num].key,str); 	//	新密码覆盖旧密码
				system("clear");
				printf("修改密码成功!\n");	//	修改密码成功后，提示信息并跳出密码修改函数
				anykey_continue();
				return;
			}
			else
			{	
				printf("两次输入的密码不相同，请重新输入\n");	//	两次输入的密码位数不相同
				anykey_continue();
				continue;
			}
		}
		strcpy(stu[Std_num].key,s);		// 密码不满足8-16位，不合法，重新循环
		msg_show("密码不合法，请重新输入(密码位数需要在8-16位之间)\n",1.5);
	}
}

int show_student_view(void) //	学生端功能显示界面
{
	system("clear");
	puts("****欢迎使用学生端教务管理系统****");
	puts("1.       查询成绩");
	puts("2.       修改密码");
	puts("3.       查看个人信息");
	puts("4.       退出学生端");
	puts("**********************************");
	printf("请输入:");
	
	char cmd = getch();
	printf("%c\n",cmd);		//	回显
	return cmd;
}

void stu_find_score(void)	//	学生查询成绩
{	
	system("clear");
	double chi_arr[Std_i];	//	语文成绩数组
	double math_arr[Std_i]; //	数学成绩数组
	double eng_arr[Std_i];	//	英语成绩数组
	double chi_sum = 0,math_sum = 0,eng_sum = 0;
	inschool_stu = 0;		//	在校学生数量
	for(int k=0; k<Std_i; k++)
	{
		if(0 == stu[k].is_school)
		{
			chi_arr[inschool_stu] = stu[k].chi;	//存储语文成绩	
			math_arr[inschool_stu] = stu[k].math;	//存储数学成绩
			eng_arr[inschool_stu] = stu[k].eng;	//存储英语成绩
			inschool_stu++;
		}
	}
	for(int k=0; k<inschool_stu; k++)	//	计算语文总成绩
	{
		chi_sum += chi_arr[k];
	}
	printf("语文平均成绩为: %.2lf\n",chi_sum/inschool_stu);	//	计算并输出语文平均成绩
	for(int k=0; k<inschool_stu; k++)	//	计算数学总成绩
	{
		math_sum += math_arr[k];
	}
	printf("数学平均成绩为: %.2lf\n",math_sum/inschool_stu);	//	计算数学平均成绩
	for(int k=0; k<inschool_stu; k++)	//	计算英语总成绩
	{
		eng_sum += eng_arr[k];
	}
	printf("英语平均成绩为: %.2lf\n",eng_sum/inschool_stu);	//	计算英语平均成绩
	printf("您语文成绩的排名是: %d\n",sort_rank(chi_arr,stu[Std_num].chi));	//	排序+排名
	printf("您数学成绩的排名是: %d\n",sort_rank(math_arr,stu[Std_num].math));	//	排序+排名
	printf("您英语成绩的排名是: %d\n",sort_rank(eng_arr,stu[Std_num].eng));	//	排序+排名
	printf("  语文成绩   数学成绩   英语成绩\n");
	for(int k=0; k<inschool_stu; k++)
	{
		printf("   %.2lf      %.2lf       %.2lf\n",chi_arr[k],math_arr[k],eng_arr[k]);
	}
	printf("语文最低成绩为: %.2lf,数学最低成绩为: %.2lf,英语最低成绩为: %.2lf\n",chi_arr[inschool_stu-1],math_arr[inschool_stu-1],eng_arr[inschool_stu-1]);
	printf("语文最高成绩为: %.2lf,数学最高成绩为: %.2lf,英语最高成绩为: %.2lf\n",chi_arr[0],math_arr[0],eng_arr[0]);
	anykey_continue();
}

void stu_find_inf(void)	//	学生个人信息显示
{
	system("clear");
	printf("学生姓名为:%s \n学生学号为:%s \n学生语文成绩为:%.2lf \n学生数学成绩为:%.2lf \n学生英语成绩为:%.2lf\n",stu[Std_num].name,stu[Std_num].id,stu[Std_num].chi,stu[Std_num].math,stu[Std_num].eng); //	显示学生的姓名、性别、学号、语文成绩、数学成绩、英语成绩
	anykey_continue();
}

void swap(double* s1, double* s2)	//	成绩交换函数
{
	double temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

void stu_login(void)	//	学生登录输入学号、密码函数
{
	printf("请输入学号\n");
	display_input(id);	//	用户显示输入
	printf("请选择本次密码是否可见(Yes:Y \\ No:其他):");
	char choice = getch();
	printf("%c\n",choice);
	if('Y' == choice)
	{
		printf("请输入密码\n");
		display_input(key);	//	用户显示输入
	}
	else
	{
		printf("请输入密码\n");
		hide_input(key);	//	用户不显示输入
	}
}

int sort_rank(double* arr, double grade)	//	成绩排序、排名
{
	int rank = 0;
	for(int k=0; k<inschool_stu-1; k++)
	{
	   	for(int j=k+1; j<inschool_stu; j++)
	   	{	
			if(arr[k] < arr[j])	
			{
				swap(&arr[k],&arr[j]);
			}
	   	}
	}
	for(rank=0; rank<inschool_stu; rank++)
	{
		if(grade == arr[rank])
		{
			return rank+1;
		}
	}
	return -1;
}
