#include "sys.h"
#include "student.h"
#include "teacher.h"
#include "admin.h"
#include "tools.h"

Student *stu=NULL;
Teacher *tea=NULL;
Extra *ext=NULL;
Other *oth=NULL;
int Tch_i=0;//文件中读取总学生数量
char Str[10]={};
int Tch_n;
int All_tch;
int End=0;

void init_sys(void)
{
	stu=calloc(sizeof(Student),STU_MAX);
	tea=calloc(sizeof(Teacher),TEA_MAX);
	ext=calloc(sizeof(Extra),STU_MAX);
	oth=calloc(sizeof(Other),STU_MAX);
}

void run_sys(void)
{
	for(;;)
	{
		switch(sys_show())
		{
			case '1':	
			{
				//	以只写的方式打开文件
				student_view();	
				FILE* stdwfile = fopen("student_inf.txt","w");
				if(NULL == stdwfile)
				{
					printf("系统出错\n");
					return;
				}
				
				
				//	加密密码
				for(int k=0; k<Std_i; k++)
				{
					for(int l=0; l<strlen(stu[k].key); l++)
					{
						if(0 == l%2)	stu[k].key[l] += 10;
						else	stu[k].key[l] -= 10;
					}
				}
				
				//	将所有数据依次写入文件并关闭文件
				for(int k=0; k<Std_i; k++)
				{
					fprintf(stdwfile,"%s %c %s %s %hhd %d %lf %lf %lf %hhd ",stu[k].name,stu[k].sex,stu[k].id,stu[k].key,stu[k].cnt,stu[k].flag,stu[k].chi,stu[k].math,stu[k].eng,stu[k].is_school);
				}
				fclose(stdwfile);
				break;	
			}				
			case '2':	teacher_view();	break;			
			case '3':	admin_view();	break;	
			case '4':	return;
		}
	}
}

void end_sys(void)  //释放内存
{
	free(stu);      
	free(tea);
	free(oth);
	free(ext);
}
