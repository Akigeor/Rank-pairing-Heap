#include<cstdio>
#include<algorithm>
#include<queue>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<cassert>
#include "rpheap.hpp"

void test1(){
	std :: priority_queue<int, std::vector<int>, std::greater<int> > Q1;
	sjtu :: rpheap<int> Q2;
	const int mod = 999983;
	const int number = 100000;
	for (int i = 0;i < number;i ++){
		int x = rand() % mod;
		Q1.push(x);
		Q2.push(x);
	}
	for (int i = 0;i < number / 2;i ++){
		assert(Q1.top() == Q2.top());
		Q1.pop();
		Q2.pop();
	}
}
void test2(){
	sjtu :: rpheap<int> Q1,Q2;
	std :: priority_queue<int, std::vector<int>, std::greater<int> > Q3;
	const int mod = 87546875;
	const int number = 100000;
	for (int i = 0;i < number;i ++){
		int x = rand() % mod;
		int choice = rand() % 2;
		if (choice) Q1.push(x); else Q2.push(x);
		Q3.push(x);
	}
	Q1.merge(Q2);
	for (int i = 0;i < number / 2;i ++){
		assert(Q1.top() == Q3.top());
		Q1.pop();
		Q3.pop();
	}
}
int a[100000];
void test3(){
	const int number = 100000;
	const int mod = 52454787;
	sjtu :: rpheap<int> Q;
	sjtu :: rpheap<int> :: iterator p[100000];
	for (int i = 0;i < number;i ++){
		p[i] = Q.push(i);
		a[i] = i;
	}
	for (int i = 0;i < 10;i ++) Q.pop();
	for (int i = 0;i < number;i ++){
		int x = rand() % mod;
		int id = rand() % (number - 10) + 10;
		a[id] -= x;
		p[id].decrease_key(a[id]);
	}
	for (int i = 0;i < 10;i ++) Q.pop();
	std :: sort(a + 10,a + number);
	for (int i = 20;i < number;i ++){
		assert(a[i] == Q.top());
		Q.pop();
	}
}
int main(){
	srand(time(0));
	test1();
	test2();
	test3();
	return 0;
}
