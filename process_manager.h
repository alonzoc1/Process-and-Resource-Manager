#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include <iostream>
#include <queue>
#include <set>
#include "process.h"
#include "resources.h"

class Process_Manager{
private:
	Process p_list[1024];
	int p_count;
	Resource_Manager r;
	std::queue <char> prio_1;
	std::queue <char> prio_2;
	std::queue <char> R1_queue;
	std::queue <char> R2_queue;
	std::queue <char> R3_queue;
	std::queue <char> R4_queue;
	std::set <char> R1_set;
	std::set <char> R2_set;
	std::set <char> R3_set;
	std::set <char> R4_set;
	int exists(char name){
		int i;
		for (i = 0; i<p_count; i++){
			if (p_list[i].get_name() == name)
				return 1;
		}
		return 0;
	}
	
	int get_index(char name){
		int success = 0;
		int i;
		for (i = 0; i<p_count; i++){
			if (p_list[i].get_name() == name){
				success = 1;
				break;
			}
		}
		if (success)
			return i;
		else
			return 0;
	}
		
	char running;
	int current_priority;
	int running_index;
public:
	void init(){
		p_count = 1;
		r.initR();
		running = '\0';
		current_priority = 0;
		running_index = 0;
		Process p('\0', 0, '\0');
		p_list[0] = p;
		p_list[0].change_state(1);
		while (!prio_1.empty()){
			prio_1.pop();
		}
		while (!prio_2.empty()){
			prio_2.pop();
		}
		while (!R1_queue.empty()){
			R1_queue.pop();
		}
		while (!R2_queue.empty()){
			R2_queue.pop();
		}
		while (!R3_queue.empty()){
			R3_queue.pop();
		}
		while (!R4_queue.empty()){
			R4_queue.pop();
		}
		R1_set.clear();
		R2_set.clear();
		R3_set.clear();
		R4_set.clear();

	}
	
	char get_running(){
		return running;
	}
	
	int create(char name, int priority){
		if ((priority==0)+(priority > 2))
			return 0;//fail
		if (exists(name))
			return 0;//fail
		Process p(name, priority, running);
		p_list[p_count] = p;
		p_list[running_index].add_child(name);
		if (priority == 1){
			prio_1.push(name);
		}
		if (priority == 2){
			prio_2.push(name);
		}
		//remove when implemented scheduler

		//end remove
		p_count++;
		//~ if (blacklist.count(name))
			//~ blacklist.erase(name);
		//std::cout << "Created without incident, running scheduler()\n";///debug
		scheduler();
		return 1;
	}
	
	int destroy_ready(char name, int first){//recursive deletion mark
		int target = get_index(name);
		if (target == 0)
			return 0;//fail
		p_list[target].change_state(3);
		//blacklist.insert(name);
		//remove_blocked(name, p_list[target].get_prio());
		int i = 0;
		while (i < (p_list[target].c_count) ){
			//std::cout << "running destroy ready on: " << p_list[target].children[i] << std::endl;//debug
			destroy_ready(p_list[target].children[i], 0);
			i++;
		}
		if (name == running){
			running = '\0';
			running_index = 0;
			current_priority = 0;
			//std::cout << "in destroy ready, temporary init switch" << std::endl;//debug
		}//temporary switch to init, then run scheduler again
		if (prio_1.empty() == 0){
			char holder = prio_1.front();
			if (holder == name){
				prio_1.pop();
			}
			else{
				prio_1.push(holder);
				prio_1.pop();
				char iter = prio_1.front();
				while (iter != holder){
					if (iter == name){
						prio_1.pop();
						iter = prio_1.front();
					}
					else{
						prio_1.pop();
						prio_1.push(iter);
						iter = prio_1.front();
					}
				}
			}
		}
		if (prio_2.empty() == 0){
			char holder = prio_2.front();
			if (holder == name){
				prio_2.pop();
			}
			else{
				prio_2.push(holder);
				prio_2.pop();
				char iter = prio_2.front();
				while (iter != holder){
					if (iter == name){
						prio_2.pop();
						iter = prio_2.front();
					}
					else{
						prio_2.pop();
						prio_2.push(iter);
						iter = prio_2.front();
					}
				}
			}
		}
		int j = 1;
		while (j < 5){
			int usage = p_list[target].get_usage(j);
			r.release(j, usage);
			p_list[target].sub_usage(j, usage);
			switch(j){
				case 1:
					if (R1_set.count(name) == 1){
						R1_set.erase(name);
						char temp = R1_queue.front();
						char first = temp;
						if (first == name){
							R1_queue.pop();
						}
						else{
							do{
								if (temp != name)
									R1_queue.push(temp);
								temp = R1_queue.front();
								R1_queue.pop();
							} while(temp != first);
						}
					}
					break;
				case 2:
					if (R2_set.count(name) == 1){
						R2_set.erase(name);
						char temp = R2_queue.front();
						char first = temp;
						if (first == name){
							R2_queue.pop();
						}
						else{
							do{
								if (temp != name)
									R2_queue.push(temp);
								temp = R2_queue.front();
								R2_queue.pop();
							} while(temp != first);
						}
					}
					break;
				case 3:
					if (R3_set.count(name) == 1){
						R3_set.erase(name);
						char temp = R3_queue.front();
						char first = temp;
						if (first == name){
							R3_queue.pop();
						}
						else{
							do{
								if (temp != name)
									R3_queue.push(temp);
								temp = R3_queue.front();
								R3_queue.pop();
							} while(temp != first);
						}
					}
					break;
				case 4:
					if (R4_set.count(name) == 1){
						R4_set.erase(name);
						char temp = R4_queue.front();
						char first = temp;
						if (first == name){
							R4_queue.pop();
						}
						else{
							do{
								if (temp != name)
									R4_queue.push(temp);
								temp = R4_queue.front();
								R4_queue.pop();
							} while(temp != first);
						}
					}
					break;
			}
			j++;
		}
		
		if (first){
			int parent = get_index(p_list[target].get_parent());
			//std::cout << "Parent is: " << p_list[parent].get_name() << std::endl;//debug
			p_list[parent].kill_child(name);
		}
		return 1;
	}
	
	int destroy_execute(){//removes state 3 processes
		int iter = 0;
		
		while (iter < p_count){
			if (p_list[iter].get_state() == 3){//shift
				//std::cout << "deleting: " << p_list[iter].get_name() << std::endl;//debug
				int iter2 = iter;
				p_count--;
				while (iter2 < p_count){
					p_list[iter2] = p_list[iter2+1];
					iter2++;
				}
			}
			else
				iter++;
		}
		return 1;
	}
	
	int destroy(char name){
		int success = 0;
		//std::cout << "running destroy ready" << std::endl;//debug
		success += destroy_ready(name, 1);
		//std::cout << "running destroy execute"<< std::endl;//debug
		success += destroy_execute();
		//std::cout << "running scheduler" << std::endl;//debug
		scheduler();
		//std::cout <<"finished running destroy" << std::endl;//debug
		if (success == 2)
			return 1;
		else
			return 0;
	}
	
	void free_blocked(){
		//std::cout << "free_blocked is starting...\n";///debug
		char contender;
		int target;
		int skip = 0;
		if (R1_queue.empty() == 0)
			skip = 1;
		//std::cout << "R1 queue status (1 is empty)"<<skip<<std::endl;//debug
		while (skip){
			contender = R1_queue.front();
			target = get_index(contender);
			if (p_list[target].desire_count <= r.check(1)){
				//std::cout << "Contender desires: "<< p_list[target].desire_count << std::endl;//debug
				//std::cout << "r.check(1) is : " << r.check(1) << std::endl;//debug
				p_list[target].add_usage(1, p_list[target].desire_count);
				r.request(1, p_list[target].desire_count);
				p_list[target].desire_count = 0;
				p_list[target].desire_type = 0;
				R1_queue.pop();
				if (p_list[target].get_prio() == 2)
					prio_2.push(contender);
				else
					prio_1.push(contender);
				skip = 0;
			}
			else{
				break;
			}
		}
		skip = 0;
		if (R2_queue.empty() == 0)
			skip = 1;
		while (skip){
			contender = R2_queue.front();
			target = get_index(contender);
			if (p_list[target].desire_count <= r.check(2)){
				p_list[target].add_usage(2, p_list[target].desire_count);
				r.request(2, p_list[target].desire_count);
				p_list[target].desire_count = 0;
				p_list[target].desire_type = 0;
				R2_queue.pop();
				if (p_list[target].get_prio() == 2)
					prio_2.push(contender);
				else
					prio_1.push(contender);
				skip = 0;
			}
			else{
				break;
			}
		}
		skip = 0;
		if (R3_queue.empty() == 0)
			skip = 1;
		while (skip){
			contender = R3_queue.front();
			target = get_index(contender);
			if (p_list[target].desire_count <= r.check(3)){
				p_list[target].add_usage(3, p_list[target].desire_count);
				r.request(3, p_list[target].desire_count);
				p_list[target].desire_count = 0;
				p_list[target].desire_type = 0;
				R3_queue.pop();
				if (p_list[target].get_prio() == 2)
					prio_2.push(contender);
				else
					prio_1.push(contender);
				skip = 0;
			}
			else{
				break;
			}
		}
		skip = 0;
		if (R4_queue.empty() == 0)
			skip = 1;
		while (skip){
			contender = R4_queue.front();
			target = get_index(contender);
			if (p_list[target].desire_count <= r.check(4)){
				p_list[target].add_usage(4, p_list[target].desire_count);
				r.request(4, p_list[target].desire_count);
				p_list[target].desire_count = 0;
				p_list[target].desire_type = 0;
				R4_queue.pop();
				if (p_list[target].get_prio() == 2)
					prio_2.push(contender);
				else
					prio_1.push(contender);
				skip = 0;
			}
			else{
				break;
			}
		}
	}
		
	
	void scheduler(){
		//std::cout << "Scheduler is starting free_blocked()" << std::endl;///debug
		free_blocked();
		//std::cout << "free_blocked completed" << std::endl;///debug
		int target;
		int finished = 0;
		if (current_priority == 0){
			if (prio_2.empty() == 0){
				p_list[0].change_state(0);
				running = prio_2.front();
				target = get_index(running);
				current_priority = p_list[target].get_prio();
				running_index = target;
				finished = 1;
				p_list[running_index].change_state(1);
				prio_2.pop();
			}
			if ( (finished == 0) && (prio_1.empty() == 0) ){
				p_list[0].change_state(0);
				running = prio_1.front();
				target = get_index(running);
				current_priority = p_list[target].get_prio();
				running_index = target;
				p_list[running_index].change_state(1);
				finished = 1;
				prio_1.pop();
			}
			if (finished == 0){
				running = '\0';
				running_index = 0;
				finished = 1;
			}
		}
		
		if ((current_priority == 1) && (finished == 0)){
			if (prio_2.empty() == 0){
				if (p_list[running_index].get_state() == 1){
					prio_1.push(running);//get back in line
					p_list[running_index].change_state(0);
				}
				running = prio_2.front();
				target = get_index(running);
				current_priority = p_list[target].get_prio();
				running_index = target;
				p_list[running_index].change_state(1);
				finished = 1;
				prio_2.pop();
			}
			if ( (finished == 0) && (p_list[running_index].get_state() == 2) ){
				if (prio_1.empty() == 0){
					running = prio_1.front();
					target = get_index(running);
					current_priority = p_list[target].get_prio();
					running_index = target;
					p_list[running_index].change_state(1);
					prio_1.pop();
					finished = 1;
				}
				else{
					running = '\0';
					current_priority = 0;
					running_index = 0;
					p_list[0].change_state(1);
					finished = 1;
				}
			}
		}
		
		if ((current_priority == 2) && (finished == 0) && (p_list[running_index].get_state() == 2) ){
			if (prio_2.empty() == 0){
				running = prio_2.front();
				running_index = get_index(running);
				current_priority = 2;
				p_list[running_index].change_state(1);
				finished = 1;
				prio_2.pop();
			}
			else if (prio_1.empty() == 0){
				running = prio_1.front();
				running_index = get_index(running);
				current_priority = 1;
				p_list[running_index].change_state(1);
				finished = 1;
				prio_1.pop();
			}
			else{
				running = '\0';
				running_index = 0;
				current_priority = 0;
				p_list[0].change_state(0);
				finished = 1;
			}
		}
	}
	

	
	int request(int type, int amount){//0=error,1=success,2=block
		int success = 0;
		if ((p_list[running_index].get_usage(type)+amount) > type){//impossible
			return 0;
		}
		success = r.request(type, amount);
		if (success == 1){
			p_list[running_index].add_usage(type,amount);
			return 1;
		}
		else if (success == 2){
			p_list[running_index].change_state(2);
			p_list[running_index].add_desire(type,amount);
			switch(type){
				case 1:
					R1_queue.push(running);
					R1_set.insert(running);
					break;
				case 2:
					R2_queue.push(running);
					R2_set.insert(running);
					break;
				case 3:
					R3_queue.push(running);
					R3_set.insert(running);
					break;
				case 4:
					R4_queue.push(running);
					R4_set.insert(running);
					break;
			}
			running_index = 0;
			running = '\0';
			current_priority = 0;//temporary init
			scheduler();
			return 2;
		}
		else{ return 0;}
	}
	
	int release(int type, int amount){
		int count = p_list[running_index].get_usage(type);
		if (count < amount){
			return 0;
		}
		p_list[running_index].sub_usage(type,amount);
		if (r.release(type, amount) == 0){
			return 0;
		}
		scheduler();
		return 1;
	}
	
	int timeout(){
		if (current_priority == 2){
			p_list[running_index].change_state(0);
			prio_2.push(running);
			current_priority = 0;
			running = '\0';
			running_index = 0;
			scheduler();
		}
		if (current_priority == 1){
			p_list[running_index].change_state(0);
			prio_1.push(running);
			current_priority = 0;
			running = '\0';
			running_index = 0;
			scheduler();
		}
		return 1;
	}
		
	//debug
	void list_processes(){
		for (int i = 0; i < p_count; i++){
			if (p_list[i].get_name() == '\0')
				std::cout << "init: ";
			else
				std::cout << p_list[i].get_name() << ": ";
			switch(p_list[i].get_state()){
				case 0: std::cout << "Ready";
						break;
				case 1: std::cout << "Running";
						break;
				case 2: std::cout << "Blocked";
						break;
			}
			std::cout << std::endl;
		}
		if (running != '\0')
			std::cout << "Running: " << running << std::endl;
		else
			std::cout << "Running: init" << std::endl;
	}
	
	
};

#endif
