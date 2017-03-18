#include "resources.h"

void Resource_Manager::set_all(int one, int two, int three, int four){
	resources[0] = one;
	resources[1] = two;
	resources[2] = three;
	resources[3] = four;
}

int Resource_Manager::check(int type){
	int j = (type-1);
	return resources[j];
}

int Resource_Manager::request(int type, int amount){
	//check for negative, input error
	if (amount < 0){
		return 0;//fail
	}
	if ( (type < 1) || (type > 4) ){
		return 0;//fail
	}
	int current = check(type);
	if (amount > type){
		return 0;
	}
	
	if (current < amount){ //not enough resources
		return 2;//fail
	}

	
	current -= amount;
	resources[(type-1)] = current;
	return 1;//success
}

int Resource_Manager::release(int type, int amount){
	//check for negative, input error
	if (amount < 0){
		return 0;//fail
	}
	if ( (type < 1) || (type > 4) )
		return 0;
	int current = check(type);
	current+= amount;
	
	if ( (current) > (type) ){//more resources than possible
		return 0;//fail
	}
	
	resources[(type-1)] = current;
	return 1;//success
}

void Resource_Manager::initR(){
	set_all(1,2,3,4);
}
