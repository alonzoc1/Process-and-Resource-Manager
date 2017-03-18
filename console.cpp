#include "console.h"

void start_shell(){
	Process_Manager pm;
	pm.init();
	std::string buff;
	int first = 1;
	std::cout << "init ";
	while (std::getline(std::cin,buff)){
		if (buff == ""){
			std::cout << '\n';
			first = 1;
		}
		
		else if (buff == "init"){
			//std::cout << "its init" << std::endl;//debug
			init_pm(&pm);
			if (first == 1){
				//std::cout << "first" << std::endl;//debug
				first = 0;
				char running = pm.get_running();
				if (running == '\0'){
					//std::cout << "running is nullchar" << std::endl;//debug
					std::cout << "init";
				}
				else{
					//std::cout << "running isn't nullchar" << std::endl;//debug
					std::cout << running;
				}
			}
			else{
				char running1 = pm.get_running();
				if (running1 == '\0'){
					std::cout << " " << "init";
				}
				else{
					std::cout << " " << running1;
				}
			}
		}
		
		else if ( (buff[0] == 'c') && (buff[1] == 'r') ){
			int prio = (buff[5]) - '0';
			char name = buff[3];
			//std::cout << "name is: " << name << "prio is: " << prio << std::endl;//debug
			int success = create_process(&pm, name, prio);
			//std::cout << "success is: " << success << std::endl;//debug
			if (first == 1){
				first = 0;
				if (success == 0){
					std::cout << "error";
				}
				if (success == 1){
					if (pm.get_running() == '\0')
						std::cout << "init";
					else
						std::cout << pm.get_running();
				}
			}
			else{
				if (success == 0){
					std::cout << " error";
				}
				else{
					if (pm.get_running() == '\0')
						std::cout << " init";
					else
						std::cout << " " << pm.get_running();
				}
			}
		}
		
		else if (buff == "to"){
			timeout(&pm);
			if (first){
				first = 0;
				if (pm.get_running() == '\0')
					std::cout << "init";
				else
					std::cout << pm.get_running();
			}
			else{
				if (pm.get_running() == '\0')
					std::cout << " init";
				else
					std::cout << " " << pm.get_running();
			}
		}
		
		else if ( (buff[0] == 'd') && (buff[1] == 'e') ){
			//std::cout << "destroying: " << buff[3] << std::endl;//debug
			int success = destroy_process(&pm, buff[3]);
			//std::cout << "success is: " << success << std::endl;//debug
			if(first){
				first = 0;
				if (success){
					if (pm.get_running() == '\0')
						std::cout << "init";
					else
						std::cout << pm.get_running();
				}
				else{
					std::cout << "error";
				}
			}
			else{
				if (success){
					if (pm.get_running() == '\0')
						std::cout << " init";
					else
						std::cout << " " << pm.get_running();
				}
				else{
					std::cout << " error";
				}
			}
		}
		
		else if ( (buff[0] == 'r') && (buff[1] == 'e') && (buff[2] == 'q') ){
			int name = buff[5]-'0';
			int amount = buff[7] - '0';
			int success = request_resource(&pm, name, amount);
			if (first){
				first =0;
				if (success){
					if (pm.get_running() == '\0')
						std::cout << "init";
					else
						std::cout << pm.get_running();
				}
				else{
					std::cout << "error";
				}
			}
			else{
				if (success){
					if (pm.get_running() == '\0')
						std::cout << " init";
					else
						std::cout << " " << pm.get_running();
				}
				else{
					std::cout << " error";
				}
			}
		}
		
		else if ( (buff[0] == 'r') && (buff[1] == 'e') && (buff[2] == 'l') ){
			int name = buff[5]-'0';
			int amount = buff[7] - '0';
			int success = release_resource(&pm, name, amount);
			if (first){
				first =0;
				if (success){
					if (pm.get_running() == '\0')
						std::cout << "init";
					else
						std::cout << pm.get_running();
				}
				else{
					std::cout << "error";
				}
			}
			else{
				if (success){
					if (pm.get_running() == '\0')
						std::cout << " init";
					else
						std::cout << " " << pm.get_running();
				}
				else{
					std::cout << " error";
				}
			}
		}
	}
}

void init_pm(Process_Manager * pm){
	(*pm).init();
}

int create_process(Process_Manager * pm, char p, int prio){
	return (*pm).create(p,prio);
}

int destroy_process(Process_Manager * pm, char p){
	return (*pm).destroy(p);
}

int timeout(Process_Manager * pm){
	return (*pm).timeout();
}

int request_resource(Process_Manager * pm, int r, int amount){
	return (*pm).request(r,amount);
}

int release_resource(Process_Manager * pm, int type, int amount){
	return (*pm).release(type,amount);
}
