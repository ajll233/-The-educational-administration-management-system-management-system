#include "admin.h"
#include "tools.h"
#include "sys.h"

char admin_key[] = "123456";
int tea_i;		//	教师总数

void admin_view(void)
{
	
	char id[20] = {}; //申请char类型变量id用于帐号接收
	char key[16] = {};//申请char类型变量key用于密码接收
	
	FILE* adminfile = fopen("admin_key.txt","r");	//	打开校长密码文件
	if(NULL == adminfile) //文件打开失败
	{
		printf("数据打开错误!\n");
		anykey_continue();
		return;
	}
	fscanf(adminfile,"%s",admin_key); //导出校长密码数据用于对比
	fclose(adminfile);	//	关闭校长文件
	system("clear");  //清屏
	printf("请输入管理员帐号\n");
	display_input(id);	//	用户显示输入
	printf("请选择本次密码是否可见(Yes:Y \\ No:其他):");
	char choice = getch(); //接收选择
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
	my_secret(key); //密码加密
	for(;;)
	{
		system("clear");
		if(0 == strcmp("admin",id))
		{
			if(0 == strcmp(key,admin_key))
			{
				if(0 == strcmp(";(=*?,",admin_key))
				{
					admin_cg_pas(admin_key);
					system("clear");
				}
				else
				{
					msg_show("登录成功\n",1.5);
					break;
				}
			}
			else
			{
				printf("管理员账号或密码错误,请检查\n");
				anykey_continue();
				system("clear");
			}
		}
		else
		{
			printf("管理员账号或密码错误,请检查\n");
			anykey_continue();
			system("clear");
		}
		printf("请输入管理员帐号\n");
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
	op_teafile("teacher_inf.txt"); //读取教师人数
	for(;;)
	{
		switch(show_admin_view()) //校长功能界面
		{
			case '1':	admin_cg_pas(admin_key);	break;			
			case '2':	hreset_pas(); break;			
			case '3':	himport_tea();break;	
			case '4':	hdelete_tea();break;	
			case '5':	hshow_tea_in();break;	
			case '6':	hshow_tea_drop();break;	
			case '7':	hadd_account_tea();break;	
			case '8':	return ;
			
		}
	}
}

void admin_cg_pas(char* s) // 校长个人修改密码
{
	char str[16] = {};      //定义局部变量str接收校长密码
	char ag_str[16]={};     //定义局部变量ag_str接收第二次输入密码
	for(;;)
	{
		system("clear");
		printf("请修改密码:\n");
		hide_input(str);   //用户不显示输入
		my_secret(str);    //密码加密
		if(16 >= strlen(str) && 8 <= strlen(str) && 0 != strcmp(s,str))  //判断是否和原密码相同和判断密码是否是大于等于8位小于等于16位
		{
			printf("请再次输入确认密码：\n");
			hide_input(ag_str);         //隐藏密码显示
			my_secret(ag_str);			//加密
			if(strcmp(ag_str,str)==0)	//原密码和现修改的密码相等才能执行
			{
				strcpy(admin_key,str);	//赋值
				FILE* adminfile = fopen("admin_key.txt","w");
				if(NULL == adminfile)
				{
					printf("系统出错\n");
					return;
				}
				fprintf(adminfile,"%s",admin_key);
				fclose(adminfile);
				system("clear");
				printf("修改密码成功!\n");
				anykey_continue();
				return;
			}
		}
		strcpy(admin_key,s);
		msg_show("密码不合法，请重新输入\n",1.5);
	}
}

int show_admin_view(void) //	校长端功能显示界面
{
	system("clear");
	puts("****欢迎使用校长端教务管理系统****");
	puts("1.       修改密码");
	puts("2.       重置教师密码");
	puts("3.       添加教师");
	puts("4.       删除教师");
	puts("5.       显示所有在职教师");
	puts("6.       显示所有离职教师");
	puts("7.       解锁教师账号");
	puts("8.       退出校长端");
	puts("**********************************");
	printf("请输入:");
	
	char cmd = getch();
	printf("%c\n",cmd);		//	回显
	return cmd;
}


void himport_tea(void) //添加教师
{
	char secret_key[7]="123456";
	my_secret(secret_key);  //加密密码
	op_teafile("teacher_inf.txt"); //读取教师人数
    printf("请输入要添加的教师信息\n");
    for(;;)
    {
    	 printf("请输入姓名:");
    	stdin->_IO_read_ptr =stdin->_IO_read_end; //吃掉回车
		if(limit_len(20,tea[tea_i].name)==100)        
    	{
    		printf("姓名不合法。请重新输入！\n");
    		continue;
    	}
    	else
    	break;
	}
    printf("请输入性别:");
    stdin->_IO_read_ptr =stdin->_IO_read_end;
    display_input(&tea[tea_i].sex);
    FILE* fwp=fopen("teacher_inf.txt","w");
    for(int j=0;j<=tea_i;j++)
    {
    	if(strcmp(tea[j].id,"")==0 && j==0 && tea[j].is_school==0)//如果本地文件中没有任何教师
    	{
    		strcpy(tea[j].id,"101");//给内存中对应的教师工号赋值101
    		strcpy(tea[j].key,secret_key);
    		tea[j].flag=1;//判断是否帐号锁定赋值1,代表帐号可用
    	}
    	else if(j>0)	//除第一个教师以外所有教师
    	{
    		strcpy(tea[j].id,int_to_string(atoi(tea[j-1].id)+1));//在之前的教师的工号上加1,往后递增，其中用到atoi将字符串转换成转型后加1,再用自己写的函数将int转换成字符串型，最后用strcpy赋值给内存中教师的id
    		strcpy(tea[j].key,secret_key);//将初始化的加密密码赋值给内存中的教师
    		tea[j].flag=1;  //判断是否帐号锁定赋值1,代表帐号可用
    	}
    	fprintf(fwp,"%s %c %s %s %hhd %d %hhd ",tea[j].name,tea[j].sex,tea[j].id,tea[j].key,tea[j].cnt,tea[j].flag,tea[j].is_school);
     }
    tea_i=0;
    fclose(fwp);
    msg_show("添加成功！\n",1.5);
}

void hdelete_tea(void) //删除教师
{
	int j=0,tea_i=0;
	Teacher teadel1={};   //定义一个变量
	Teacher teadel2={};
	FILE* frp=fopen("teacher_inf.txt","r");
	if(NULL==frp)
    {
         perror("fopen");
         return;
    }
    while(-1!=fscanf(frp,"%s %c %s %s %hhd %d %hhd ",tea[tea_i].name,&tea[tea_i].sex,tea[tea_i].id,tea[tea_i].key,&tea[tea_i].cnt,&tea[tea_i].flag,&tea[tea_i].is_school))
    {
    	tea_i++;
    }
    fclose(frp);
    frp=NULL; 
	printf("请输入要删除人的工号：\n");
	display_input(teadel1.id);   //接收第一次的工号
	for(;j<tea_i;j++)
	{
		if(strcmp(teadel1.id,tea[j].id)==0 && tea[j].is_school==0)
		{
			printf("请再次输入以确认删除：\n");
			scanf("%s",teadel2.id); //接收第二次工号
			if(strcmp(teadel1.id,teadel2.id)==0)//如果第一次和第二次相等才执行
			{
				tea[j].is_school=1;
				msg_show("删除成功！\n",1.5);
				break;
			}
		}	
	}
	if(j==tea_i)
	msg_show("查无此人！请重新查询\n",1.5);	
	FILE* fwp=fopen("teacher_inf.txt","w");
	if(NULL==fwp)
    {
         perror("fopen");
         return;
    }
    for(int j=0;j<tea_i;j++)
    {
	fprintf(fwp,"%s %c %s %s %hhd %d %hhd ",tea[j].name,tea[j].sex,tea[j].id,tea[j].key,tea[j].cnt,tea[j].flag,tea[j].is_school);
	}
	fclose(fwp);
	fwp=NULL;
	tea_i=0;
}

void hshow_tea_in(void) //显示所有在职教师
{
	op_teafile("teacher_inf.txt"); //读取教师人数
	for(int j=0;j<tea_i;j++)
	{
		if(tea[j].is_school==0)
		{
		printf("姓名：%s 性别：%s 工号：%s \n",tea[j].name,'w'==tea[j].sex?"女":"男",tea[j].id);
		}
	}
	anykey_continue();
}
void hshow_tea_drop(void) //显示所有离校教师
{
	op_teafile("teacher_inf.txt"); //读取教师人数
	for(int j=0;j<tea_i;j++)
	{
		if(tea[j].is_school==1)
		{
		printf("姓名：%s 性别：%s 工号：%s \n",tea[j].name,'w'==tea[j].sex?"女":"男",tea[j].id);
		}
	}
	anykey_continue();
}

void hadd_account_tea(void) //解锁教师帐号
{
	int j=0,tea_i=0;
	Teacher teazz={};
	FILE* frp=fopen("teacher_inf.txt","r");
	if(NULL==frp)
    {
         perror("fopen");
         return;
    }
    while(-1!=fscanf(frp,"%s %c %s %s %hhd %d %hhd ",tea[tea_i].name,&tea[tea_i].sex,tea[tea_i].id,tea[tea_i].key,&tea[tea_i].cnt,&tea[tea_i].flag,&tea[tea_i].is_school))
    {
    	tea_i++;
    }
    fclose(frp);
    frp=NULL; 
	printf("请输入要解锁的教师工号\n");
	display_input(teazz.id);
	for(;j<tea_i;j++)
	{
		if(strcmp(teazz.id,tea[j].id)==0 && tea[j].is_school==0)
		{
			tea[j].flag=1;
			tea[j].cnt=0;
			msg_show("解锁成功！\n",1.5);
			break;
		}
	}
	if(tea_i==j)
	msg_show("查无此人！请重新查询\n",1.5);
	FILE* fwp=fopen("teacher_inf.txt","w");
	if(NULL==fwp)
    {
         perror("fopen");
         return;
    }
    for(int j=0;j<tea_i;j++)
    {
	fprintf(fwp,"%s %c %s %s %hhd %d %hhd ",tea[j].name,tea[j].sex,tea[j].id,tea[j].key,tea[j].cnt,tea[j].flag,tea[j].is_school);
	}
	fclose(fwp);
	fwp=NULL;
	tea_i=0;
}

void hreset_pas(void)    //重置教师密码
{
	char secret_key[7]="123456";
	my_secret(secret_key);  //加密密码
	int j=0,tea_i=0;
	Teacher teazz={};
	FILE* frp=fopen("teacher_inf.txt","r");
	if(NULL==frp)
    {
         perror("fopen");
         return;
    }
    while(-1!=fscanf(frp,"%s %c %s %s %hhd %d %hhd ",tea[tea_i].name,&tea[tea_i].sex,tea[tea_i].id,tea[tea_i].key,&tea[tea_i].cnt,&tea[tea_i].flag,&tea[tea_i].is_school))
    {
    	tea_i++;
    }
    fclose(frp);
    frp=NULL; 
	printf("请输入要重置的教师的工号\n");
	display_input(teazz.id);
	for(;j<tea_i;j++)
	{
		if(strcmp(teazz.id,tea[j].id)==0 && tea[j].is_school==0)
		{
			strcpy(tea[j].key,secret_key);
			tea[j].cnt=0;
			msg_show("重置成功！\n",1.5);
			break;
		}
	}
	if(tea_i==j)
	msg_show("查无此人！请重新查询\n",1.5);
	FILE* fwp=fopen("teacher_inf.txt","w");
	if(NULL==fwp)
    {
         perror("fopen");
         return;
    }
    for(int j=0;j<tea_i;j++)
    {
	fprintf(fwp,"%s %c %s %s %hhd %d %hhd ",tea[j].name,tea[j].sex,tea[j].id,tea[j].key,tea[j].cnt,tea[j].flag,tea[j].is_school);
	}
	fclose(fwp);
	fwp=NULL;
	tea_i=0;
}
