# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aattali <aattali@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/22 11:07:12 by aattali           #+#    #+#              #
#    Updated: 2024/05/14 13:41:35 by aattali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#* ************************************************************************** *#
#* *                            GENERAL INFO                                * *#
#* ************************************************************************** *#

TARGET := ircserv

#* ************************************************************************** *#
#* *                             COMPILATION                                * *#
#* ************************************************************************** *#

CC := c++
CPPFLAGS += -Wall -Werror -Wextra -g3
STD := -std=c++98

#* ************************************************************************** *#
#* *                              INCLUDES                                  * *#
#* ************************************************************************** *#

INCLUDES := includes
INCLUDES_FLAGS += $(addprefix -I, $(INCLUDES))

#* ************************************************************************** *#
#* *                               SOURCES                                  * *#
#* ************************************************************************** *#

-include make/sources.mk
SRCDIR := src

#* ************************************************************************** *#
#* *                              OBJECTS                                   * *#
#* ************************************************************************** *#

OBJDIR := obj
OBJECTS := ${SOURCES:%.cpp=${OBJDIR}/%.o}

#* ************************************************************************** *#
#* *                            DEPENDENCIES                                * *#
#* ************************************************************************** *#

DEPENDENCIES := $(OBJECTS:.o=.d)

#* ************************************************************************** *#
#* *                          TEXT CONSTANTS                                * *#
#* ************************************************************************** *#

BLACK = \033[30m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
BOLD = \033[1m
THIN = \033[2m
ITALIC = \033[3m
UNDERLINE = \033[4m
RESET_COLOR = \033[0m
NEW			:= \r\033[K

#* ************************************************************************** *#
#* *                           PRESENTATION                                 * *#
#* ************************************************************************** *#

define success_message
	@printf "✨ $(NEW)$(GREEN)$(BOLD)COMPILATION SUCCESSFUL$(RESET_COLOR) ✨\n"
endef

define linking_message
	@printf "$(YELLOW)Linking $(BOLD)$(CYAN)$@ $(RESET_COLOR)$(YELLOW)...$(RESET_COLOR)\n"
endef

LAST_DIR = ""
FIRST_COMPILE_MESSAGE = true
define compile_message
	@if [ "$(FIRST_COMPILE_MESSAGE)" = "true" ]; then \
		printf "\n"; \
		FIRST_COMPILE_MESSAGE=false; \
	fi
	@if [ "$(dir $<)" != "$(LAST_DIR)" ]; then \
		printf "$(BOLD)$(YELLOW)Compiling files in directory $(RESET_COLOR)$(BOLD)$(CYAN)$(dir $<)$(RESET_COLOR)\n"; \
		LAST_DIR="$(dir $<)"; \
	fi
	printf "$(CYAN)    • $(notdir $<)";
	@$(eval LAST_DIR := $(dir $<))
endef


#* ************************************************************************** *#
#* *                          MAKEFILE RULES                                * *#
#* ************************************************************************** *#

all: $(TARGET)

# -------------------- #
# Create object files. #
# -------------------- #

$(OBJECTS): $(OBJDIR)/%.o: %.cpp
	@mkdir -p $(@D)
	@$(call compile_message)
	@$(CC) $(CPPFLAGS) $(STD) -MMD -MF $(@:.o=.d) $(INCLUDES_FLAGS) -c $< -o $@

# ---------------------------------------- #
# Link the files after compiling them all. #
# ---------------------------------------- #

-include $(DEPENDENCIES)
$(TARGET): $(OBJECTS)
	@echo ""
	@$(call linking_message)
	@$(CC) $(CPPFLAGS) $(STD) $(INCLUDES_FLAGS) -o $@ $(OBJECTS)
	@echo ""
	@$(call success_message)

# --------------------- #
# Delete compiled data. #
# --------------------- #

clean:
	@rm -rf $(OBJDIR)
	@printf "$(YELLOW)Deleting $(CYAN)$(OBJECTS_PATH) $(YELLOW)...$(RESET_COLOR)\n"

fclean: clean
	@rm -rf $(TARGET)
	@printf "$(YELLOW)Deleting $(CYAN)$(NAME) executable $(YELLOW)...$(RESET_COLOR)\n"

# ------------------------------- #
# Create the list of all sources. #
# ------------------------------- #

gmk:
	if [ -d make ];then echo ok;else mkdir make;fi
	@find -name '*.cpp' -printf "%d%p\n" | sort -n | sed 's/^[[:digit:]]/SOURCES += /' > make/sources.mk

# --------------------- #
#      Recompile.       #
# --------------------- #

re: fclean all

.PHONY: clean fclean gmk re
