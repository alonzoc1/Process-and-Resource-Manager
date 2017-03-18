#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <string>
#include "process_manager.h"

void start_shell();

void init_pm(Process_Manager* pm);

int create_process(Process_Manager * pm, char p, int prio);

int destroy_process(Process_Manager * pm, char p);

int request_resource(Process_Manager * pm, int r, int amount);//1-4

int release_resource(Process_Manager * pm, int r, int a);

int timeout(Process_Manager * pm);

#endif
