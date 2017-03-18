#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
class Process{
private:
	char p_name;
	int priority;
	
	
	int state; //0: ready || 1: running || 2: blocked ||
	//note, there are two more states for the program:
	//3: marked for deletion
	char parent;
public:
	int r_usage[4];
	int desire_count;
	int desire_type;
	char children[1024];
	int c_count;
	
	Process(){
		p_name = '\0';
		priority = 0;
		c_count = 0;
		int i = 0;
		while (i<4){
			r_usage[i] = 0;
			i++;
		}
		desire_count = 0;
		desire_type = 0;
		state = 0;
		parent = '\0';
	}
	Process(char name, int prio, char parent_t){
		p_name = name;
		priority = prio;
		c_count = 0;
		int i = 0;
		while (i<4){
			r_usage[i] = 0;
			i++;
		}
		state = 0;
		desire_count = 0;
		desire_type = 0;
		parent = parent_t;
	}
	
	char get_name(){
		return p_name;
	}
	int get_prio(){
		return priority;
	}
	void add_usage(int type, int amount){
		int i = (type-1);
		r_usage[i] += amount;
	}
	
	void add_desire(int type, int amount){
		desire_type = type;
		desire_count = amount;
	}
	
	void clear_desire(){
		desire_type = 0;
		desire_count = 0;
	}
	
	int get_d_type(){
		return desire_type;
	}
	
	int get_d_count(){
		return desire_count;
	}
	
	void sub_usage(int type, int amount){
		int i = (type-1);
		r_usage[i] -= amount;
	}
	
	int get_usage(int type){
		return r_usage[type-1];
	}
	
	int get_state(){
		return state;
	}
	
	int change_state(int i){
		if ( (i==0) + (i==1) + (i==2) + (i==3)){
			 state = i;
			 return 1;
		 }
		 else
			return 0;
	}
	
	char get_parent(){
		return parent;
	}
	
	int kill_child(char name){
		int i = 0;
		int success = 0;
		while (i<c_count){
			if (children[i] == name){
				success = 1;
				break;
			}
			i++;
		}
		if (success == 0)
			return 0;
		c_count--;
		while (i < c_count){
			children[i] = children[i+1];
			i++;
		}
		return 1;
	}
	int add_child(char name){
		children[c_count] = name;
		c_count++;
		//std::cout << "Adding child to: " << get_name() << std::endl; //debug
		//std::cout << "Adding: " << name << std::endl;//debug
		return 1;
	}
};
	
#endif
