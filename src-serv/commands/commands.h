#ifndef COMMANDS_COMMANDS_H_
#define COMMANDS_COMMANDS_H_

  enum CommandCode{
        VIEW, EXIT, UNKNOWN
    };

struct Command {
    enum CommandCode cmdCode;
    char** fullCommand;
};

#include "view.h"


#endif
