SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

ADD_LIBRARY(kvbf SHARED kvbf.cpp kvbf_block.cpp kvbf_cell.cpp kvbf_layer.cpp )
