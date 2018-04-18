#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <typeinfo>
#include <map>
#include <vector>
#include <algorithm>

#define CAPACITY 10
#define UNITLENGTH 2

using namespace std;

struct range{
	int left;
	int right;
};
class Predicate{
public:
	Predicate(){};
	void set(int *preTmp);
	int ID;
	int valueNum;
	int dimensionID;
	int opreator;
	struct range range;
	int indicadulValue;
}; 
void Predicate::set(int *preTmp){
	ID = preTmp[0];
	valueNum = preTmp[1];
	dimensionID = preTmp[2];
	opreator = preTmp[3];
	range.left = preTmp[4];
	range.right = preTmp[5];
	indicadulValue = preTmp[6];

	cout<<"{"<<endl;
 	cout<<"tmpPredicate.ID:"<<ID<<endl;
 	cout<<"tmpPredicate.valueNum:"<<valueNum<<endl;
 	cout<<"tmpPredicate.dimensionID:"<<dimensionID<<endl;
 	cout<<"tmpPredicate.range.left:"<<range.left<<endl;
 	cout<<"tmpPredicate.range.right:"<<range.right<<endl;
 	cout<<"tmpPredicate.indicadulValue:"<<indicadulValue<<endl;
 	cout<<"}"<<endl;
}
class Event{
public:
	Event(int id, int preNum, int EquPreNum);
	Event(){};
	int ID;
	int predicateNum;
	int EquPredicateNum;
	int typicalDimId;
	map<int, Predicate>predicates;
};
Event::Event(int id, int preNum, int EquPreNum){
	ID = id;
	cout<<"id:" <<id<<"  preNum: "<<preNum<<endl;
	EquPredicateNum = EquPreNum;
	predicateNum = preNum;
};
void cleanTmp(char *tmp){
	for(int i=0; i<7; i++){
		tmp[i] = ' ';
	}
}
void print(int num){
	printf("%d\n", num);
}
void printHead(Event &eventHead){
	printf("eventHead.ID:%d\n",eventHead.ID);
	printf("eventHead.predicateNum:%d\n",eventHead.predicateNum);
	printf("eventHead.EquPredicateNum:%d\n", eventHead.EquPredicateNum);
}
void print(Event *events){
	map<int, Predicate>::iterator iter;
	iter = events[0].predicates.find(0);
	cout<<(iter->second).ID<<endl;
}
void parseObjNum(int &objNum){
	FILE *fp = NULL;
	fp = fopen("D:/BE-Tree/project/parseData/source/event.out", "rb");
	char result = fgetc(fp);
	char tmp[7] = {' ',' ',' ',' ',' ',' ',' '};
	int count = 0, i = 0, start = 0;
	while(EOF!=result){
		if(result == '\n'){
			count++;
			printf("count = %d\n", count);
			result = fgetc(fp);
		}
		if(count==3){
			if(result == ' '){
				start = 1;
				goto next;
			}else if(result == '$'){
				start = 0;
				objNum = atoi(tmp);
				cleanTmp(tmp);
				goto next;
			}
			if(start == 1){
				tmp[i] = result;
				i++;
			}
		}
		if(count>3){
			break;
		}
		next: result = fgetc(fp);
	}
}
void parseData(Event *events, int &systemDim, int &preMaxNum, int &preMinNum){
	FILE *fp = NULL;
	fp = fopen("D:/BE-Tree/project/parseData/source/event.out", "rb");
	char result = fgetc(fp);
		 printf("Parse Result\n");
	//字符串寄存
	char tmp[7] = {' ',' ',' ',' ',' ',' ',' '};
	int  temp[3] = {0};
	int  preTmp[7] = {0};
	int  i, num, j, predicateNum, k, preNumber;
		 i = 0;
		 j = 0;
		 k = 0;
		 predicateNum = -1;
		 preNumber = 0;//predicate解析计数
	Event tmpEvent;
	int eventNum = 0;
	int  count,start;
	 	 count = 0;
		 start = 0;
	while(EOF!=result){
		if(count==0){
			if(result == ' '){
				start = 1;
				goto next;
			}else if(result == '$'){
				start = 0;
				systemDim = atoi(tmp);
				cleanTmp(tmp);
				i = 0;
				j = 0;
				goto next;
			}
			if(start == 1){
				tmp[i] = result;
				i++;
			}
		}
		if(count==4){
			if(result == ' '){
				start = 1;
				goto next;
			}else if(result == '$'){
				start = 0;
				preMaxNum = atoi(tmp);
				cleanTmp(tmp);
				i = 0;
				j = 0;
				goto next;
			}
			if(start == 1){
				tmp[i] = result;
				i++;
			}
		}
		if(count==5){
			if(result == ' '){
				start = 1;
				goto next;
			}else if(result == '$'){
				start = 0;
				preMinNum = atoi(tmp);
				cleanTmp(tmp);
				i = 0;
				j = 0;
				goto next;
			}
			if(start == 1){
				tmp[i] = result;
				i++;
			}
		}
		//events在第十个\n后
		if(result == '\n'){
			putchar('\n');
			count++;
			printf("count = %d\n", count);
			result = fgetc(fp);
			j = 0;
			//解析出一个完整的event
			if(count>10){
				events[eventNum] = tmpEvent;
				preNumber = 0;
				eventNum++;
				cout<<"eventNum"<<eventNum<<endl;
			}
		}
		if(count>9&&count<12){
			if(result == '['){
				start = 1;
				goto next;
			}else if(result == ']'){
				start = 0;
				num = atoi(tmp);
				temp[j] = num;
				cleanTmp(tmp);
				Event tmp(temp[0], temp[1], temp[2]);
				tmpEvent = tmp;
				printHead(tmpEvent);
				predicateNum = tmpEvent.predicateNum;
				i = 0;
				j = 0;
				goto next;
			} 
			if(start == 1){
				if(result == ','){
					num = atoi(tmp);
					temp[j] = num;
					cleanTmp(tmp);
					result = fgetc(fp);
					i = 0;
					j++;
					goto next;
				}
				tmp[i] = result;
				i++;
			}
			if(result == '|'){
				j++;
				goto next;
			}
			if(j == predicateNum){
				if(result == ' '){
					num = atoi(tmp);
					cleanTmp(tmp);
					i = 0;
					preTmp[k] = num;
					k++;
					if(k > 6){
						//k循环解析字符串
						k = 0;
						tmpEvent.predicates[preTmp[2]].set(preTmp);
						preNumber++;
					}
					goto next;
				}else if(result == ','){
					goto next;
				}
				
				//putchar(result);
				i++;
				tmp[i] = result;
			}
		}else if(count>13){
			break;		
		}
		next: result = fgetc(fp);	
		
	}
	cout<<"end testing"<<events[0].predicates[395].ID<<endl;
	cout<<"end testing"<<events[0].predicates[808].ID<<endl;
	cout<<"********"<<endl;
	cout<<"systemDim"<<systemDim<<endl;
	cout<<"preMinNum"<<preMinNum<<endl;
	cout<<"preMaxNum"<<preMaxNum<<endl;
}

void main()
{	
	int  systemDim, preMaxNum, preMinNum, objNum;
	Event *events;
	parseObjNum(objNum);
	cout<<objNum;
	events = new Event[objNum];
	parseData(events, systemDim, preMaxNum, preMinNum);
	cout<<"end testing"<<events[0].predicates[395].ID<<endl;
	cout<<"end testing"<<events[0].predicates[808].ID<<endl;
	cout<<"********"<<endl;
	cout<<"systemDim"<<systemDim<<endl;
	cout<<"preMinNum"<<preMinNum<<endl;
	cout<<"preMaxNum"<<preMaxNum<<endl;
	cout<<objNum<<endl;
}