

#########################config ###########################
CC = gcc
STRIP = strip
CFLAGS = -Wall -O2
project_dir = $(shell pwd)
DIR_BUILD = $(shell pwd)/build
DIR_CMD = $(shell pwd)/cmd_bin
SYS_BIT = $(shell getconf LONG_BIT)
#########################config end########################

#########################TARGET ########################
TARGET_CONSOLE_CMD = console_cmd
TARGET_TOOL_CMDLINK = command_link



TARGET = $(TARGET_CONSOLE_CMD) 
TARGET += $(TARGET_TOOL_CMDLINK)



#########################TARGET END########################



#########################include ###########################
INC_PATH += $(shell find $(project_dir)/inc/ -maxdepth 3 -type d)
INC_PATH += $(shell find $(project_dir)/src/ -maxdepth 3 -type d)


CFLAGS += $(addprefix -I, $(INC_PATH))
#########################include end ########################


###########################lib path ########################
LIBS_PATH = -L$(project_dir)/lib

LIBS_PATH += -lpthread -lm -lrt 
###########################lib path END#####################

###########################src #############################
##common
#DIR_COMM = $(shell find $(project_dir)/src/common -maxdepth 2 -type d)
#OBJ_COMM = $(foreach dir_comm, $(DIR_COMM), $(wildcard $(dir_comm)/*.c))

#modules 
DIR_MODS_TEMP = $(shell find $(project_dir)/src/modules -maxdepth 3 -type d)
DIR_MODS_FILTER_OUT = $(project_dir)/src/modules/console_cmd/command_link
DIR_MODS = $(filter-out $(DIR_MODS_FILTER_OUT), $(DIR_MODS_TEMP))
OBJ_MODS = $(foreach dir_mod, $(DIR_MODS), $(wildcard $(dir_mod)/*.c))
###########################src end##########################


###########################target src ##########################
##application
DIR_APP = $(shell find $(project_dir)/src/application -maxdepth 2 -type d)
OBJ_APP = $(foreach dir_app, $(DIR_APP), $(wildcard $(dir_app)/*.c))

#test
TARGET_CONSOLE_CMD_SRC = $(wildcard $(project_dir)/src/test/console_cmd_test/*.c)

all: $(TARGET)

# console is ofen used for debug, so name it	
debug: $(TARGET_CONSOLE_CMD) $(TARGET_TOOL_CMDLINK)	


$(TARGET_CONSOLE_CMD): 
	@echo "\n----compiles $(TARGET_CONSOLE_CMD) ----"
	@#echo $(DIR_MODS)		# 在这里注释有效，但是放在这里一定会被输出到屏幕，除非用@不让其显示输出
	
	@$(CC) -o $@ $(OBJ_COMM) \
				$(OBJ_MODS) \
				$(TARGET_CONSOLE_CMD_SRC) \
				$(CFLAGS) \
				$(LIBS_PATH) 
	$(STRIP) $(TARGET_CONSOLE_CMD)
	mv $(TARGET_CONSOLE_CMD) $(DIR_BUILD)/
	@echo "----compiles $(TARGET_CONSOLE_CMD) ----end\n\n"

$(TARGET_TOOL_CMDLINK):
	@make -C $(project_dir)/src/modules/console_cmd/command_link
	mv $(project_dir)/src/modules/console_cmd/command_link/command_link $(DIR_BUILD)



#debug:
#	$(warning CFLAGS is< $(CFLAGS))
#	$(warning SOURCE is< $(SOURCE))
#	$(warning OBJS is< $(OBJS))
#


.PHONY: sqlite clean

clean:
	rm $(DIR_BUILD)/$(TARGET_CONSOLE_CMD) -rf
	rm $(DIR_BUILD)/$(TARGET_TOOL_CMDLINK)  -rf
	rm $(DIR_CMD) -rf
	
###########################rules end##########################

