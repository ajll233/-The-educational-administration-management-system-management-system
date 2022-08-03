# -The-educational-administration-management-system-management-system
校长和教师和学生三端口功能实现
使用sch_man_sys.conf可以一键打开文件
makefile脚本文件使用make指令可以一键打开


具体项目：
学生：
	姓名 性别 学号 密码 语文 数学 英语
    1、第一次登录强制修改密码。
    2、查询成绩
        排名 不显示姓名和学号。
        平均分
        最高分
        最低分
    3、修改密码
    4、查看个人信息
    5、三次密码错误锁定帐号，由教师解锁
    
教师：
	姓名 性别 工号 密码
    1、第一次登录强制修改密码。
    2、添加学生（学生的学号自动生成）
        单个添加
        批量导入
    3、删除学生
    	输入两次学号确定
        删除的学生要记录保存在已退学的文件中
    4、查找学生
        按姓名查找
        按学号查找
    5、修改学生信息
        修改学生基础信息
        修改学生成绩
    6、录入学生成绩
        单个录入
        批量导入
    7、重置学生密码
    8、显示所有在校学生信息
    9、显示所有退出学生信息
    10、三次密码错误锁定帐号，由校长解锁
    
校长：
	admin 
    1、第一次登录强制修改密码。
    2、能重置自己的密码
    3、能重置教师密码
    4、添加教师
    5、删除教师
    6、显示所有在职教师
    7、显示所有离职教师
    8、解锁教师帐号
    
设计文档
	文件 结构 成员 全局变量 函数名
	
分配任务
	教师
	学生
	校长
	
构建编译，测试
