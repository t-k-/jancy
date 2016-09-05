# This file is part of AXL (R) library
# Tibbo Technology Inc (C) 2004-2013. All rights reserved
# Author: Vladimir Gladkov

#..............................................................................

set (DOC_NAME "Jancy Standard Library Reference")

set (XML_DIR  ${CMAKE_CURRENT_BINARY_DIR}/xml)
set (RST_DIR  ${CMAKE_CURRENT_BINARY_DIR}/rst)
set (HTML_DIR ${CMAKE_CURRENT_BINARY_DIR}/html)
set (TEX_DIR  ${CMAKE_CURRENT_BINARY_DIR}/tex)
set (PDF_DIR  ${CMAKE_CURRENT_BINARY_DIR}/pdf)
set (TMP_DIR  ${CMAKE_CURRENT_BINARY_DIR}/tmp)

# . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

set (
	JANCY_CMD_LINE
	-d 
	--std-lib-doc
	--no-doxy-comment ///
	-O ${XML_DIR}
	${JANCY_SRC_DIR}/jnc_ct/jnc/jnc_StdTypedefs.jnc
	${JANCY_SRC_DIR}/jnc_ct/jnc/jnc_DynamicLib.jnc
	${JANCY_SRC_DIR}/jnc_ct/jnc/jnc_Recognizer.jnc
	${JANCY_SRC_DIR}/jnc_ct/jnc/jnc_Scheduler.jnc
	-S ${JANCY_SRC_DIR}/jnc_std/jnc
	-S ${JANCY_SRC_DIR}/jnc_sys/jnc
	-I ${JANCY_SRC_DIR}/jnc_io_base/jnc
	-S ${JANCY_SRC_DIR}/jnc_io_base/jnc
	-S ${JANCY_SRC_DIR}/jnc_io_ssh/jnc
	-S ${JANCY_SRC_DIR}/jnc_io_pcap/jnc
	)

set (
	DOXYREST_CMD_LINE
	${XML_DIR}/index.xml
	-o ${RST_DIR}/global.rst
	-F ${DOXYREST_FRAME_DIR}
	-f c_global.rst.in
	)

set (
	SPHINX_HTML_CMD_LINE
	-b html
	-d ${TMP_DIR}/sphinx-doctrees
	-c ${CMAKE_CURRENT_BINARY_DIR}
	${RST_DIR}
	${HTML_DIR}
	)

set (
	SPHINX_TEX_CMD_LINE
	-b latex
	-d ${TMP_DIR}/sphinx-doctrees
	-c ${CMAKE_CURRENT_BINARY_DIR}
	${RST_DIR}
	${TEX_DIR}
	)

set (
	LATEX_CMD_LINE
	-quiet
	-output-directory=${PDF_DIR}
	-aux-directory=${TMP_DIR}
	jancy_stdlib.tex
	)

string (
	REPLACE  
	";" " "
	JANCY_CMD_LINE
	"${JANCY_CMD_LINE}"
	)

string (
	REPLACE  
	";" " "
	DOXYREST_CMD_LINE
	"${DOXYREST_CMD_LINE}"
	)

string (
	REPLACE  
	";" " "
	SPHINX_HTML_CMD_LINE
	"${SPHINX_HTML_CMD_LINE}"
	)

string (
	REPLACE  
	";" " "
	SPHINX_TEX_CMD_LINE
	"${SPHINX_TEX_CMD_LINE}"
	)

string (
	REPLACE  
	";" " "
	LATEX_CMD_LINE
	"${LATEX_CMD_LINE}"
	)

# . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

configure_file (
	conf.py.in
	conf.py
	)

if (WIN32)	
	string (REPLACE "$(Configuration)" "%1" JANCY_EXE ${JANCY_EXE})
	string (REPLACE "$(Configuration)" "%1" DOXYREST_EXE ${DOXYREST_EXE})

	configure_file (
		build-rst.bat.in
		build-rst.bat
		)

	configure_file (
		build-html.bat.in
		build-html.bat
		)

	configure_file (
		build-pdf.bat.in
		build-pdf.bat
		)		
else ()
	axl_configure_file_w_permissions (
		build-rst.sh.in
		build-rst.sh
		OWNER_READ OWNER_WRITE OWNER_EXECUTE
		GROUP_READ GROUP_WRITE GROUP_EXECUTE
		WORLD_READ WORLD_WRITE WORLD_EXECUTE
		)

	axl_configure_file_w_permissions (
		build-html.sh.in
		build-html.sh
		OWNER_READ OWNER_WRITE OWNER_EXECUTE
		GROUP_READ GROUP_WRITE GROUP_EXECUTE
		WORLD_READ WORLD_WRITE WORLD_EXECUTE
		)

	axl_configure_file_w_permissions (
		build-pdf.sh.in
		build-pdf.sh
		OWNER_READ OWNER_WRITE OWNER_EXECUTE
		GROUP_READ GROUP_WRITE GROUP_EXECUTE
		WORLD_READ WORLD_WRITE WORLD_EXECUTE
		)
endif ()
	
#..............................................................................