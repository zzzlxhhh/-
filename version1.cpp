// 启发式搜索.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include<iostream>
#include<vector>
#include<set>
using namespace std;
int target[9];
struct NODE
{
	int index;//指向父节点
	int arr[9];
	int f;//启发函数的值
	int depth;//结点的深度
};
vector<NODE> open;
vector<NODE> close;
//判断是否到达目标状态
bool equal(int index, int sg[])
{
	int i;
	for (i = 0; i < 9; i++)
	{
		if (open[index].arr[i] != sg[i])
			return false;
	}
	return true;
}
//判断节点是否可拓展
bool expandable(NODE &node)
{
	int i;
	for (i = 0; i<open.size(); i++)
	{
		if (equal(i, node.arr))
			return false;
	}
	return true;
}
//函数h(x) 位置不相符的个数
/*int distance2(int s0[], int sg[])
{
	int i = 0; int count = 0;
	for (i; i < 9; i++)
	{
		if (s0[i] == 0)continue;
		else if (s0[i] != sg[i])
			count++;
	}
	return count;
}*/
//函数h(x)距离
int distance(int s0[], int sg[])
{
	int i = 0;
	int j; int count = 0; int temp;
	int x1, y1,x2,y2;
	for (i; i < 9; i++)
	{
		if (s0[i] == 0)continue;
		else if (s0[i] != sg[i])
		{
			for (j= 0; j < 9; j++)
				if (sg[j] == s0[i]) temp=j;
			y1 = temp % 3;
			x1 = temp / 3;
			y2 = i % 3;
			x2 = i / 3;
			count = abs(x1 - x2) + abs(y1 - y2)+count;
		}
	}
	return count;
}
//比较逆序数
/*int distance1(int a[], int b[])
{
	int i = 0, j = 0,p=0;
	int s0[8],sg[8];
	int m = 0, n = 0;
	int count1 = 0;
	int index;
	for (j; j < 9; j++)//注意此处循环为9
	{//去除零元素
		if (a[j] != 0) s0[m++] = a[j];
		if (b[j] != 0) sg[n++] = b[j];
	}
	set<int> s1;
	set<int> s2;
	for(i=0;i<8;i++)
		{//对sg的每个数建立两个堆分别存储该数前后的数
		index = 0;
		while (s0[i] != sg[index])index++;
		for (j = 0; j < 8; j++)
			if (j < index) s1.insert(sg[j]);
			else if (j > index) s2.insert(sg[j]);
		for (j = 0; j < 8; j++)
			if (j < i) count1 += s2.count(s0[j]);//即本该出现在s0[i]后面的数出现在了前面
			else if (j > i) count1 += s1.count(s0[j]);
		s1.clear();
		s2.clear();
		}
	
	return count1*3;
}*/
//方法四
/*int distance(int a[], int b[])
{
	return distance1(a, b) + distance2(a, b);
}*/

bool reverse(int a[], int b[])//判断逆序数奇偶是否相同
{
	int i = 0, j = 0;
	int s0[8], sg[8];
	int m = 0, n = 0;
	for (j; j < 9; j++)//注意此处循环为9
	{
		if (a[j] != 0) s0[m++] = a[j];
		if (b[j] != 0) sg[n++] = b[j];
	}
	int count1 = 0, count2 = 0;
	for (i = 0; i < 8; i++)
		for (j = i+1; j < 8; j++)
		{
			if (s0[j] < s0[i])
				count1++;
			if (sg[j] < sg[i])
				count2++;
		}
	if (count1 % 2 == count2 % 2)
		return true;
	else return false;
}
//按启发函数值最小的节点
int min_node()
{
	int min_index = 0;
	int min = open[0].f;
	for (int i = 0; i<open.size(); i++)
	{
		if (open[i].f < min)
		{
			min = open[i].f;
			min_index = i;
		}
	}
	return min_index;
}
//拓展节点
void expand(int index)
{
	int a[9], b[9], c[9], d[9];
	int temp, i, n = index;
	NODE temp_node;
	int switch_index;//记录应该与0交换的位置
	int open_size = open.size();//用于判断是否加入了拓展节点
	int deep = open[index].depth;
	for (i = 0; i < 9; i++)
	{
		a[i] = open[index].arr[i];
	}
	for (i = 0; i < 9; i++)
	{
		b[i] = open[index].arr[i];
	}
	for (i = 0; i < 9; i++)
	{
		c[i] = open[index].arr[i];
	}
	for (i = 0; i < 9; i++)
	{
		d[i] = open[index].arr[i];
	}
	int zero_index = 0;
	
	//空格上下左右移动
	//找到空格零的位置
		for (i = 0; i < 9; i++)
			if (a[i] == 0)
			{
				zero_index = i;
				break;
			}
		//向上
		switch_index = (zero_index / 3 - 1)*3 + zero_index % 3;
		if (switch_index >= 0 && switch_index < 9)
		{
			temp = a[switch_index];
			a[switch_index] = a[zero_index];
			a[zero_index] = temp;
			index = index + 1;
			for (int i = 0; i < 9; i++)
			{				
				temp_node.arr[i] = a[i];				
			}
			temp_node.index = n;
			temp_node.depth = deep + 1;
			temp_node.f = deep + 1 + distance(a, target);
			if (expandable(temp_node))
			open.push_back(temp_node);
		}
		//向右
		switch_index = zero_index + 1;
		if ((zero_index % 3) != 2)
		{
			temp = b[switch_index];
			b[switch_index] = b[zero_index];
			b[zero_index] = temp;
			index = index + 1;
			for (int i = 0; i < 9; i++)
			{
				temp_node.arr[i] = b[i];
			}
			temp_node.index = n;
			temp_node.depth = deep + 1;
			temp_node.f = deep + 1 + distance(b, target);
			if (expandable(temp_node))
			open.push_back(temp_node);
		}
		//向下
		switch_index = (zero_index / 3 + 1)*3 + zero_index % 3;
		if (switch_index >= 0 && switch_index < 9)
		{
			temp = c[switch_index];
			c[switch_index] = c[zero_index];
			c[zero_index] = temp;
			index = index + 1;
			for (int i = 0; i < 9; i++)
			{
				temp_node.arr[i] = c[i];
			}
			temp_node.index = n;
			temp_node.depth = deep + 1;
			temp_node.f = deep + 1 + distance(c, target);
			if (expandable(temp_node))
			open.push_back(temp_node);
		}
		//向左
		switch_index = zero_index - 1;
		if (zero_index % 3 != 0)
		{
			temp = d[switch_index];
			d[switch_index] = d[zero_index];
			d[zero_index] = temp;
			index = index + 1;
			for (int i = 0; i < 9; i++)
			{
				temp_node.arr[i] = d[i];
			}
			temp_node.index = n;
			temp_node.depth = deep + 1;
			temp_node.f = deep + 1 + distance(d, target);
			if (expandable(temp_node))
			open.push_back(temp_node);
		}
	
}
//判断open是否为空，即是否所有的节点都是f值：10000
bool open_empty()
{
	int num = open.size();
	for (int i = 0; i < num; i++)
		if (open[i].f != 10000) return false;
		else continue;//不全为10000
	return true;
}
//将一行形式的数码按照3*3的形式打印输出
void print(int arr[])
{
	for (int i = 0; i < 9; i++)
	{
		cout << arr[i] << " ";
		if (i % 3 == 2) cout << endl;
	}
}
//打印结果
void print_path(int index, vector<NODE>& close)
{   //按index找父节点,并将正确的搜索路径放入close中
	//close.push_back(open[index]);
	//index = open[index].index;
	while (index != 0)
	{
		close.push_back(open[index]);
		index = open[index].index;
	}
	for (int i = close.size() - 1; i >= 0; i--)
	{
		cout << "第" << close.size() - i << "步"<<endl;
		print(close[i].arr);
	}
	cout << "最少移动" << close.size()<<endl;
}
int main()
{
	int s0[9];
	int sg[9]={ 1,2,3,8,0,4,7,6,5 };
	int min;
	while (1) {
		open.clear();
		close.clear();
		cout << "八数码问题求解" << endl;
		cout << "input:" << endl;
		cout << "初始状态：";
		for (int i = 0; i < 9; i++)
			cin >> s0[i];
		//cout << "目标状态：";
		for (int i = 0; i < 9; i++)
		{
			//cin >> sg[i];
			
			target[i] = sg[i];
		}
		NODE root;
		root.depth = 1;//从第一层开始算
		root.f = distance(s0, sg) + root.depth;
		root.index = 0;//第一个结点指向自己
		for (int i = 0; i < 9; i++)
		{
			root.arr[i] = s0[i];
		}
		if (!reverse(root.arr, sg))
		{
			cout << "该状态下无解" << endl;
			break;
		}
		open.push_back(root);
		while (1)
		{
			if (open_empty())
			{
				cout << "该状态下无解" << endl;
				break;
			}
			
			else
			{
				min = min_node();
				open[min].f = 10000;//类似于将节点从open表中去除
				if (equal(min, sg))
				{
					cout << "得到最优解" << endl;
					print_path(min, close);
					break;
				}
				else
				{
					expand(min);
				}

			}

		}
	}
}
