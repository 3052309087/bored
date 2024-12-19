#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"test.h"



int main()
{
    
    while (1)
    {
    menu();
    int choice;
    scanf("%d",&choice);
       switch (choice)
    {
    case 1://添加
        add();
        printf("添加成功\n");
        break;
    case 2://删除
        printf("1:全部删除：\n2；按id删除：\n");
        int choice1;
        scanf("%d",&choice1);
        if (choice1 == 1)
        {
            here:
            printf("确认删除全部吗？\n1:确认\n2:取消\n");
            int choice3;
            scanf("%d",&choice3);
            if (choice3 == 1)
            {
                del_all();
                printf("删除成功\n");
            }
            else if (choice3 == 2)
            {
                printf("取消成功\n");
            }
            else
            {
                printf("输入错误，请重新输入\n");
                goto here;
            }
        }
        else if (choice1 == 2)
        {
            del();
        }
        else
        {
            printf("输入错误，请重新输入\n");
        }
        break;
    case 3://修改
        printf("1:按编号修改：\n2；按名称修改：\n");
        int choice2;
        scanf("%d",&choice2);
        if (choice2 == 1)
        {
            id_revise();
        }
        else if (choice2 == 2)
        {
            name_revise();
        }
        else
        {
            printf("输入错误，请重新输入\n");
        }
        break;
    case 4://查找
        printf("1:按编号查找：\n2；按名称查找：\n");
        int choice4;
        scanf("%d",&choice4);
        if (choice4 == 1)
        {
            find_id();
        }
        else if (choice4 == 2)
        {
            find_prototype();
        }
        else
        {
            printf("输入错误，请重新输入\n");
        }
        break;
    case 5://显示全部
        display();
        break;
    case 6:
        printf("谢谢使用，再见\n");
        exit(0);
        
    
    default:
        printf("输入错误，请重新输入\n");
        break;
    }
    }
    
    return 0;
}

