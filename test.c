#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"test.h"
void menu()
{
    printf("欢迎使用函数管理系统\n");
    printf("1.添加函数信息\n");
    printf("2.删除函数信息\n");
    printf("3.修改函数信息\n");
    printf("4.查询函数信息\n");
    printf("5.显示函数信息\n");
    printf("6.退出系统\n");
    printf("请选择你要进行的操作：\n");
}
void del_all()
{
    FILE *tempFile = fopen("function1.txt", "w");
    remove("function.txt");
    fclose(tempFile);
    rename("function1.txt", "function.txt");   
}
void del() {
    int id;
    int new_id = 1; // 用于重新分配编号
    int found = 0;  // 标记是否找到要删除的记录
    function temp_function; // 用于存储当前读取的函数信息
    char a [999] = "\0";

    remake:
    printf("请输入要删除的函数编号：\n");
    scanf("%s", &a);
    for (int i = 0; i < 999; i++)
    {
        if (a[i] == '\0')
        {
            break;
        }
        if (num(&a[i]) == 1)
        {
            printf("输入错误，请重新输入\n");
            goto remake;
        }
    }
    id = atoi(a);//处理非法输入



    FILE *file = fopen("function.txt", "r");
    FILE *tempFile = fopen("function1.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf("无法打开文件\n");
        if (file != NULL) fclose(file);
        if (tempFile != NULL) fclose(tempFile);
        return;
    }

    while (fscanf(file, "%d %s %s %s %s %s", 
                  &temp_function.id, 
                  temp_function.easy_name, 
                  temp_function.name, 
                  temp_function.function, 
                  temp_function.my_return, 
                  temp_function.illustrate) != EOF) 
    {
        if (temp_function.id == id) {
            found = 1; // 找到匹配的记录
            continue;  // 跳过当前记录（不写入临时文件）
        }
        // 更新编号并写入临时文件
        fprintf(tempFile, "%d %s %s %s %s %s\n", 
                new_id++, 
                temp_function.easy_name, 
                temp_function.name, 
                temp_function.function, 
                temp_function.my_return, 
                temp_function.illustrate);
    }

    fclose(file);
    fclose(tempFile);

    // 用临时文件替换原始文件
    if (remove("function.txt") != 0) {
        printf("删除原始文件失败\n");
        return;
    }
    if (rename("function1.txt", "function.txt") != 0) {
        printf("重命名临时文件失败\n");
        return;
    }

    if (found) {
        printf("编号为 %d 的函数信息已删除，其他编号已重新更新。\n", id);
    } else {
        printf("未找到编号为 %d 的函数信息。\n", id);
    }
}
void find_id() {
    int id;
    char a [999] = "\0";
    int found = 0; // 用于标记是否找到函数
    function temp_function; // 临时变量，用于存储当前读取的函数信息
    
    remake:
    printf("请输入要查找的函数编号：\n");
    scanf("%s", &a);
    for (int i = 0; i < 999; i++)
    {
        if (a[i] == '\0')
        {
            break;
        }
        if (num(&a[i]) == 1)
        {
            printf("输入错误，请重新输入\n");
            goto remake;
        }
    }
    id = atoi(a);//处理非法输入
    

    FILE *file = fopen("function.txt", "r");
    if (file == NULL) {
        printf("无法打开文件\n");
        return;
    }

    // 遍历文件中的每条记录
    while (fscanf(file, "%d %s %s %s %s %s",
                  &temp_function.id,
                  temp_function.easy_name,
                  temp_function.name,
                  temp_function.function,
                  temp_function.my_return,
                  temp_function.illustrate) != EOF) 
    {
        if (temp_function.id == id) {
            // 找到匹配的记录，打印信息
            printf("函数编号：%d\n", temp_function.id);
            printf("函数名：%s\n", temp_function.easy_name);
            printf("函数原型：%s\n", temp_function.name);
            printf("函数功能：%s\n", temp_function.function);
            printf("返回值：%s\n", temp_function.my_return);
            printf("说明：%s\n", temp_function.illustrate);
            found = 1; // 设置标记为已找到
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("未找到编号为 %d 的函数信息。\n", id);
    }
}

void find_prototype() {
    char prototype[50];
    int found = 0; // 标志是否找到匹配的函数
    function temp_function; // 用于存储当前读取的函数信息

    printf("请输入要查找的函数原型（支持部分匹配）：\n");
    scanf("%s", prototype);

    FILE *file = fopen("function.txt", "r");
    if (file == NULL) {
        printf("无法打开文件\n");
        return;
    }

    // 遍历文件中的每条记录
    while (fscanf(file, "%d %s %s %s %s %s", 
                  &temp_function.id, 
                  temp_function.easy_name, 
                  temp_function.name, 
                  temp_function.function, 
                  temp_function.my_return, 
                  temp_function.illustrate) != EOF) 
    {
        // 使用 strstr 进行部分匹配
        if (strstr(temp_function.name, prototype) != NULL) {
            // 找到匹配的记录，打印信息
            printf("函数编号：%d\n", temp_function.id);
            printf("函数名：%s\n", temp_function.easy_name);
            printf("函数原型：%s\n", temp_function.name);
            printf("函数功能：%s\n", temp_function.function);
            printf("返回值：%s\n", temp_function.my_return);
            printf("说明：%s\n", temp_function.illustrate);
            printf("-----------------------------\n");
            found = 1; // 设置标记为已找到
        }
    }

    fclose(file);

    // 如果未找到任何匹配的记录
    if (found == 0) {
        printf("未找到包含 \"%s\" 的函数原型。\n", prototype);
    }
}
int num(char *str)//判断是否为数字
{
    int i = 0;
    while (str[i] != '\0')
    {
       if (str[i] > '9' || str[i] < '0')
       {
           
           return 1;
       }
       i++;
    }
    return 0;
    
}
void add()
{
    function Function[999];
    int count = 0;
    // 读取文件中的函数编号到多少了
    FILE *file1 = fopen("function.txt", "r");
     while (fscanf(file1, "%d", &count) != EOF)
     {
      while (fgetc(file1) != '\n' && !feof(file1)) {
        
    }
     }
    fclose(file1);
    count++;

   
    
    FILE *file = fopen("function.txt", "a"); // 以追加模式打开文件
    if (file == NULL) {
        printf("无法打开文件\n");
        return;
    }
    printf("当前编号为：%d\n", count);
    Function[count].id = count;
    printf("请输入函数名：\n");
    scanf("%s", Function[count].easy_name);
    printf("请输入函数原型：\n");
    scanf("%s", Function[count].name);
    printf("请输入函数功能：\n");
    scanf("%s", Function[count].function);
    printf("请输入返回值：\n");
    scanf("%s", Function[count].my_return);
    printf("请输入说明：\n");
    scanf("%s", Function[count].illustrate);
    fprintf(file, "%d %s %s %s %s %s\n", Function[count].id,Function[count].easy_name, Function[count].name, Function[count].function, Function[count].my_return, Function[count].illustrate);
    fclose(file);
    printf("函数信息已保存到文件。\n");
    fclose(file);
    
}
void id_revise() 
{
    int id;
    char a [999] = "\0";
    int found = 0; // 0_未找到匹配记录，1_找到匹配记录
    function temp_function; // 临时变量
  
    remake:
    printf("请输入要修改的函数编号：\n");
    scanf("%s", &a);
    for (int i = 0; i < 999; i++)
    {
        if (a[i] == '\0')
        {
            break;
        }
        if (num(&a[i]) == 1)
        {
            printf("输入错误，请重新输入\n");
            goto remake;
        }
    }
    id = atoi(a);//处理非法输入

    FILE *file = fopen("function.txt", "r");
    FILE *tempFile = fopen("function1.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf("无法打开文件\n");
        if (file !=NULL) fclose(file);
        if (tempFile !=NULL) fclose(tempFile);
        return;
    }

    // 遍历文件
    while (fscanf(file, "%d %s %s %s %s %s", 
                  &temp_function.id, 
                  temp_function.easy_name, 
                  temp_function.name, 
                  temp_function.function, 
                  temp_function.my_return, 
                  temp_function.illustrate) != EOF) 
    {
        if (temp_function.id == id) {
            found = 1; // 找到匹配的记录,置标志位为1
            printf("找到编号为 %d 的函数信息，开始修改。\n", id);

            printf("请输入新的函数名：\n");
            scanf("%s", temp_function.easy_name);
            printf("请输入新的函数原型：\n");
            scanf("%s", temp_function.name);
            printf("请输入新的函数功能：\n");
            scanf("%s", temp_function.function);
            printf("请输入新的返回值：\n");
            scanf("%s", temp_function.my_return);
            printf("请输入新的说明：\n");
            scanf("%s", temp_function.illustrate);
        }
        // 无论是否修改，都重新写入到新文件中
        fprintf(tempFile, "%d %s %s %s %s %s\n", 
                temp_function.id, 
                temp_function.easy_name, 
                temp_function.name, 
                temp_function.function, 
                temp_function.my_return, 
                temp_function.illustrate);
    }

    fclose(file);
    fclose(tempFile);

    // 如果未找到匹配记录
    if (!found) {
        printf("未找到编号为 %d 的函数信息。\n", id);
        remove("function1.txt");
        return;
    }

    // 处理异常情况
    if (remove("function.txt") != 0) {
        printf("删除原始文件失败\n");
        return;
    }
    if (rename("function1.txt", "function.txt") != 0) {
        printf("重命名临时文件失败\n");
        return;
    }

    printf("函数信息已成功修改。\n");
}
void name_revise() {
    char prototype[50];
    int found_count = 0; // 记录匹配的函数个数
    function temp_function; // 临时变量，用于存储当前读取的函数信息
    function matches[50];   // 用于存储所有匹配的函数记录
    int match_ids[50];      // 用于存储匹配记录的原始编号

    printf("请输入要查找的函数原型（支持部分匹配）：\n");
    scanf("%s", prototype);

    FILE *file = fopen("function.txt", "r");
    if (file == NULL) {
        printf("无法打开文件\n");
        return;
    }

    // 遍历文件，查找所有匹配的记录
    while (fscanf(file, "%d %s %s %s %s %s", 
                  &temp_function.id, 
                  temp_function.easy_name, 
                  temp_function.name, 
                  temp_function.function, 
                  temp_function.my_return, 
                  temp_function.illustrate) != EOF) 
    {
        if (strstr(temp_function.name, prototype) != NULL) {
            matches[found_count] = temp_function;
            match_ids[found_count] = temp_function.id;
            found_count++;
        }
    }
    fclose(file);

    // 如果没有找到匹配记录，提示用户
    if (found_count == 0) {
        printf("未找到包含 \"%s\" 的函数原型。\n", prototype);
        return;
    }

    // 显示所有匹配的记录
    printf("找到以下匹配的函数记录：\n");
    for (int i = 0; i < found_count; i++) {
        printf("%d. 函数编号：%d\n", i + 1, matches[i].id);
        printf("    函数原型：%s\n", matches[i].name);
        printf("    函数名：%s\n", matches[i].easy_name);
        printf("    函数功能：%s\n", matches[i].function);
        printf("    返回值：%s\n", matches[i].my_return);
        printf("    说明：%s\n", matches[i].illustrate);
        printf("-----------------------------\n");
    }

    // 用户选择要修改的记录
    int choice;
    printf("请输入要修改的函数序号（1-%d）：\n", found_count);
    scanf("%d", &choice);

    if (choice < 1 || choice > found_count) {
        printf("输入序号无效。\n");
        return;
    }

    // 修改用户选择的函数
    int selected_id = match_ids[choice - 1]; // 获取所选记录的原始编号
    printf("请输入新的函数名：\n");
    scanf("%s", matches[choice - 1].easy_name);
    printf("请输入新的函数原型：\n");
    scanf("%s", matches[choice - 1].name);
    printf("请输入新的函数功能：\n");
    scanf("%s", matches[choice - 1].function);
    printf("请输入新的返回值：\n");
    scanf("%s", matches[choice - 1].my_return);
    printf("请输入新的说明：\n");
    scanf("%s", matches[choice - 1].illustrate);

    // 将修改后的记录写回文件
    file = fopen("function.txt", "r");
    FILE *tempFile = fopen("function1.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf("无法打开文件\n");
        if (file !=NULL) fclose(file);
        if (tempFile !=NULL) fclose(tempFile);
        return;
    }

    // 遍历文件，将所有记录复制到临时文件中，同时更新修改的记录
    while (fscanf(file, "%d %s %s %s %s %s", 
                  &temp_function.id, 
                  temp_function.easy_name, 
                  temp_function.name, 
                  temp_function.function, 
                  temp_function.my_return, 
                  temp_function.illustrate) != EOF) 
    {
        if (temp_function.id == selected_id) {
            // 写入修改后的记录
            fprintf(tempFile, "%d %s %s %s %s %s\n", 
                    temp_function.id, 
                    matches[choice - 1].easy_name, 
                    matches[choice - 1].name, 
                    matches[choice - 1].function, 
                    matches[choice - 1].my_return, 
                    matches[choice - 1].illustrate);
        } else {
            // 保留未修改的记录
            fprintf(tempFile, "%d %s %s %s %s %s\n", 
                    temp_function.id, 
                    temp_function.easy_name, 
                    temp_function.name, 
                    temp_function.function, 
                    temp_function.my_return, 
                    temp_function.illustrate);
        }
    }

    fclose(file);
    fclose(tempFile);

    // 替换原文件
    if (remove("function.txt") != 0) {
        printf("删除原始文件失败\n");
        return;
    }
    if (rename("function1.txt", "function.txt") != 0) {
        printf("重命名临时文件失败\n");
        return;
    }

    printf("函数信息已成功修改。\n");
}
void display()
{
    FILE *file = fopen("function.txt", "r");
    if (file == NULL) {
        printf("无法打开文件\n");
        return;
    }

    function temp_function;
    while (fscanf(file, "%d %s %s %s %s %s", 
                  &temp_function.id, 
                  temp_function.easy_name, 
                  temp_function.name, 
                  temp_function.function, 
                  temp_function.my_return, 
                  temp_function.illustrate) != EOF) 
    {
        printf("函数编号：%d\n", temp_function.id);
        printf("函数名：%s\n", temp_function.easy_name);
        printf("函数原型：%s\n", temp_function.name);
        printf("函数功能：%s\n", temp_function.function);
        printf("返回值：%s\n", temp_function.my_return);
        printf("说明：%s\n", temp_function.illustrate);
        printf("-----------------------------\n");
    }

    fclose(file);
}
