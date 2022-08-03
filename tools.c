#include "tools.h"

//按任意键继续
void anykey_continue(void)
{
	puts("按任意键继续...");
    stdin->_IO_read_ptr =stdin->_IO_read_end;
    getch();
}

//打印提示信息
void msg_show(const char* msg,float sec)
{   
	printf("%s",msg);
    fflush(stdout);
    usleep(sec*1000000);
}

//将整数转换成字符串
char *int_to_string(int num)
{
	int i=0,j=0;
	char temp[10];
	while(num)
	{
    	temp[i++]=num%10+'0';  
    	num/=10;        
	}
    temp[i]='\0';
 	i=i-1;
 	while(i>=0)
    Str[j++]=temp[i--];   
	Str[j]='\0';              
	return Str;
}

//展示主界面
int sys_show(void)
{
	system("clear");
	puts("****欢迎使用鼠人教务管理系统****");
	puts("1.            学生");
	puts("2.            老师");
	puts("3.           管理员");
	puts("4.          退出系统");
	puts("********************************");
	printf("请输入:");
	
	char cmd = getch();		//接收输入的单个字符值
	printf("%c\n",cmd);		//将	回显
	return cmd;				//将得到的值
}


void hchange_password_t(char* s) // 教师修改密码 
{
 	char str[16] = {};
 	char ag_str[16]={};
 	for(;;)
 	{
  		system("clear");
  		printf("请修改密码:\n");
  		hide_input(str);	//	用户不显示输入
  		my_secret(str);     //加密密码
  		if(16 >= strlen(str) && 8 <= strlen(str) && 0 != strcmp(s,str))
  		{	
	   		printf("请再次输入确认密码：\n");
			hide_input(ag_str);   //隐藏显示
			my_secret(ag_str);		//加密密码
			if(strcmp(ag_str,str)==0)
			{
	   			strcpy(tea[Tch_n].key,str);
		   		FILE* fwp = fopen("teacher_inf.txt","w");
		   		if(NULL == fwp)
		   		{
					printf("系统出错\n");
					return;
		   		}
			   for(int k=0; k<Tch_i; k++)
			   {
				fprintf(fwp,"%s %c %s %s %d %hhd ",tea[k].name,tea[k].sex,tea[k].id,tea[k].key,tea[k].flag,tea[k].is_school);
			   }
			   fclose(fwp);
			   system("clear");
			   printf("修改密码成功!\n");
			   anykey_continue();
			   return;
		   }
	  }
	  strcpy(tea[Tch_n].key,s);
	  msg_show("密码不合法，请重新输入\n",1.5);
 	}
}


//教师登录系统
bool tch_login(void)
{
	char id[20] = {};
 	char key[16] = {};
 	FILE* frp = fopen("teacher_inf.txt","r");
 	if(NULL == frp)
 	{
  		printf("数据打开错误!\n");
  		return false;
 	}
 	while((-1 != fscanf(frp,"%s %c %s %s %hhd %d %hhd",tea[Tch_i].name,&tea[Tch_i].sex,tea[Tch_i].id,tea[Tch_i].key,&tea[Tch_i].cnt,&tea[Tch_i].flag,&tea[Tch_i].is_school)))
 	{
  		Tch_i++;
 	}
 	All_tch=Tch_i;
 	fclose(frp);          
 	system("clear");
    printf("请输入工号\n");
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
 	my_secret(key);
 	for(;;)
 	{
  		system("clear");
  		Tch_n = 0;
  		
  		while(Tch_n<Tch_i)
  		{
   			if(0 == strcmp(id,tea[Tch_n].id))
   			{
    			if(1 == tea[Tch_n].is_school)
    			{
    				printf("您已离职,无法进入系统\n");
     				anykey_continue();
     				system("clear");
     				Tch_i=0;
     				End=1;
     				return false;
    			}
    			if(0 == tea[Tch_n].flag)
    			{
     				printf("工号已被锁定,请联系校长解锁\n");
     				anykey_continue();
     				system("clear");
     				Tch_i=0;
     				End=1;
     				return false;
    			}
    			if(0 == strcmp(key,tea[Tch_n].key))
    			{
     				if(0 == strcmp(tea[Tch_n].key,";(=*?,"))
     				{
      					hchange_password_t(tea[Tch_n].key);
      					system("clear");
      					break;                             
     				}
     				Tch_i=0;
     				tea[Tch_n].cnt=0;
     				msg_show("登录成功\n",1.5);
     				return true;
    			}
				else
				{
		 			tea[Tch_n].cnt += 1;
		 			if(tea[Tch_n].cnt!=3)
		 			{
		 				printf("工号或密码错误,请检查\n");
		 				anykey_continue();
		 			}
		 			system("clear");
		 			break;
				}
   			}
   			Tch_n++;
  		}
  		if(Tch_n == Tch_i)   //循环遍历结束后没找到正确教师
	    {
		  	printf("工号或密码错误,请检查\n");
		  	anykey_continue();
		  	system("clear");
	  	}
		else
		{
			if(3 == tea[Tch_n].cnt)
		    {
				printf("工号已被锁定,请联系校长解锁\n");
				anykey_continue();
				system("clear");
				tea[Tch_n].flag=0;
				Tch_i=0;
				End=1;
				return false;
		    }
        }		
 		//printf("请重新输入工号和密码\n");
  		//scanf("%s %s",id,key);
  		my_secret(key);
  		printf("请输入工号\n");
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
		my_secret(key);
	}
}

void menu(void)
{
	system("clear");
	printf("****************************************\n");
	printf("            1.添加学生\n");
	printf("            2.删除学生\n");
	printf("            3.查找学生\n");
	printf("            4.修改学生信息\n");
	printf("            5.录入学生成绩\n");
	printf("            6.重置学生密码\n");
	printf("            7.显示所有在校学生信息\n");
	printf("            8.显示所有退出学生信息\n");
	printf("            9.解锁学生密码\n");
	printf("            q.退出\n");
	printf("***************************************\n");
	printf("请输入你的需求\n");
	stdin->_IO_read_ptr =stdin->_IO_read_end;    //不清除缓冲区会导致输入的回车被getch吃掉
	char cmd = getch();
	printf("%c\n",cmd);		//	回显
	switch (cmd)
		{
			case '1':	add_stu();	break;			
		    case '2':	tch_del();	break;			
		    case '3':	tch_find();	break;	
		    case '4':	tch_mod(); break;
		    case '5':	tch_input();break;
		    case '6':	tch_setstupas();break;
		    case '7':	tch_show_instu();break;
		    case '8':	tch_show_dstu();break;
		    case '9':	tch_unlock();break;
		    case 'q':	End=1;;return;        //End赋1不会进入菜单
		}
}

void op_stufile(char* s)  //用于读取学生指定文件
{
	FILE* frp=fopen(s,"r");
	if(NULL==frp)
    {
         perror("fopen");
         return;
    }
    
    while(-1!=fscanf(frp,"%s %c %s %s %hhd %d %lf %lf %lf %hhd ",stu[Tch_i].name,&stu[Tch_i].sex,stu[Tch_i].id,stu[Tch_i].key,&stu[Tch_i].cnt,&stu[Tch_i].flag,&stu[Tch_i].chi,&stu[Tch_i].math,&stu[Tch_i].eng,&stu[Tch_i].is_school))
    {
    	Tch_i++;
    }
    fclose(frp);
    frp=NULL;
}

void wr_stufile(char* s) //用于写入学生指定文件
{
	FILE* fwp=fopen(s,"w");
	if(NULL==fwp)
    {
         perror("fopen");
         return;
    }
    for(int j=0;j<Tch_i;j++)
    {
	fprintf(fwp,"%s %c %s %s %hhd %d %lf %lf %lf %hhd ",stu[j].name,stu[j].sex,stu[j].id,stu[j].key,stu[j].cnt,stu[j].flag,stu[j].chi,stu[j].math,stu[j].eng,stu[j].is_school);
	}
	fclose(fwp);
	fwp=NULL;
	Tch_i=0;
}

void op_teafile(char* s)  //用于读取教师指定文件
{
	tea_i = 0;
	FILE* frp = fopen(s,"r");	//	打开教师信息文件
	if(NULL == frp)
	{
		printf("数据打开错误!\n");
		return;
	}
	while(-1 != fscanf(frp,"%s %c %s %s %hhd %d %hhd ",tea[tea_i].name,&tea[tea_i].sex,tea[tea_i].id,tea[tea_i].key,&tea[tea_i].cnt,&tea[tea_i].flag,&tea[tea_i].is_school))	//	读取教师总个数
	{
		tea_i++;
	}
	fclose(frp);	//	关闭教师文件
	frp=NULL;
}
void my_secret(char* s) //加密
{
	for(int l=0; l<strlen(s); l++)
	{
		if(0 == l%2)	s[l] += 10;
		else	s[l] -= 10;
	}
}

void hide_input(char* s)	//	用户不显示输入
{
	while((Ch = getch()))
	{
		if(10 == Ch)
		{
			printf("\n");
			break;
		}
		else if(127 == Ch)
		{
			if(0 != Len)
			{
				putchar('\b');
				putchar(' ');
				putchar('\b');
				s[Len--] = '\0';
			}
		}
		else if(Len < 16)
		{
			s[Len++] = Ch;
			printf("*");
		}
	}
	s[Len] = '\0';
	Ch = 0;
	Len = 0;
}

void display_input(char* s)	//	用户显示输入
{
	while((Ch = getch()))
	{
		if(10 == Ch)
		{
			printf("\n");
			break;
		}
		else if(127 == Ch)
		{
			if(0 != Len)
			{
				putchar('\b');
				putchar(' ');
				putchar('\b');
				s[Len--] = '\0';
			}
		}
		else if(Len < 16)
		{
			s[Len++] = Ch;
			printf("%c",Ch);
		}
	}
	s[Len] = '\0';
	Ch = 0;
	Len = 0;
}

int limit_len(int len,char* string)   //限制文件名长度
{
	int j=0;
	for(j=0;j<len;j++)
	{
		string[j]=getchar();
		if(string[j]==' ' || string[j]=='\n')
		{
			string[j]='\0';
			break;
		}
	}
	if(len==j)
	{
		return 100;
	}
	else
	return 1;
	
}

