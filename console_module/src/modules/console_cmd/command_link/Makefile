DESTINATION := command_link
LIBS := 
INCLUDES := .


RM := rm -f
#C,CC或CPP文件的后缀
PS=c
# GNU Make的隐含变量定义
CC=gcc
#CC=gcc
CPPFLAGS = -g -Wall -O2
CPPFLAGS += $(addprefix -I,$(INCLUDES))
CPPFLAGS += -MMD

#以下部分无需修改
SOURCE := $(wildcard *.$(PS))
OBJS := $(patsubst %.$(PS),%.o,$(SOURCE))
DEPS := $(patsubst %.o,%.d,$(OBJS))
MISSING_DEPS := $(filter-out $(wildcard $(DEPS)),$(DEPS))
MISSING_DEPS_SOURCES := $(wildcard $(patsubst %.d,%.$(PS),$(MISSING_DEPS)))

# if you build a file named like phony object, 
# then it will ignore this file exist and make it as Makefile
.PHONY : all deps objs clean rebuild

all : $(DESTINATION)

deps : $(DEPS)
	$(CC) -MM -MMD $(SOURCE)


objs : $(OBJS)

clean :
	@$(RM) *.o
	@$(RM) *.d
	@$(RM) $(DESTINATION)

rebuild: clean all 

ifneq ($(MISSING_DEPS),)
$(MISSING_DEPS) :
	@$(RM) $(patsubst %.d,%.o,$@)
endif

-include $(DEPS)

$(DESTINATION) : $(OBJS)
	$(CC) -o $(DESTINATION) $(OBJS) $(addprefix -l,$(LIBS))
