########################################################################
#
# Copyright (C) 2006 ESOC, ESA (www.esa.int)
#
# Description: 
#	Makefile for the Mdk package of the SMP2 Adapter
#
# History:
#	See bottom of the file
#
########################################################################

Files = \
Aggregate \
Component \
Composite \
Model \
Object \
Request \
SimpleTypes

export
BinDir = $(PWD)/bin

include ../../Makefile.top

# Create target directory
$(BinDir) :
	$(MakeDir) $@

all: $(BinDir) $(BIN_OBJECTS) 
	cd Management; make all
	ar -cru $(ParentBinDir)/libMdk.a $(BinDir)/*.o

clean:
	rm -rf $(BinDir)

###########
# History #
###########

# $Log: Makefile,v $
# Revision 1.1  2006/05/05 23:22:27  nin
# Released
#