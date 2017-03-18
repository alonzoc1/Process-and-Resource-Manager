#ifndef RESOURCES_H
#define RESOURCES_H

class Resource_Manager{
	
public:
	int resources[4];
	//set all resources to a value (no error checking)
	void set_all(int one, int two, int three, int four);
		
	//check a resource (returns number of resources available)
	int check(int type);
		
	//allocates resources away, if possible. Return true if success
	int request(int type, int amount);
		
	//returns resources to manager, if possible
	int release(int type, int amount);
	
	//returns to standard position
	void initR();
};
		
	
#endif
