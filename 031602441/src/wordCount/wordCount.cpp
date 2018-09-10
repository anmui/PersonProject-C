#include"pch.h"
#include<iostream> 
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<fstream>
#include"readchars.h"
#include"readlines.h"
#include"readword.h"
#include"sort.h"
using namespace std;
/***********************单词结构体***********************/
struct word {
	char name[30];
	int num;
	struct word *next;
};


/*****************************主函数****************************/
int main()
{
	char filename[30];
	struct word *head;
	head = new word;
	head->next = NULL;
	int file_lines = 0;
	int file_chars = 0;
	int word_num = 0;
	cin >> filename;
	FILE *file = _fsopen(filename, "r", _SH_DENYNO);
	if (!file)
	{
		cout << "打开文件错误！" << endl;
		return 0;
	}
	else
	{
		readchars(head, filename, file_chars);
		readword(head, filename, word_num);
		readlines(head, filename, file_lines);
		sort(head);
	}

}
