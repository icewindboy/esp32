file(GLOB SOURCES 
  main.c
  app/*.c
  blufi/*.c
  pages/*.c
  pages/temperature/*.c
  pages/gadget/*.c
  mqtt/*.c
  box/*.c
  )

# set(include_dirs 
#   app
#   pages
#   pages/temperature
#   pages/gadget
#   blufi  
#   driver
# )

idf_component_register(SRCS  
          ${SOURCES} 
          INCLUDE_DIRS ${include_dirs})

# idf_component_register(SRCS "main.cpp"
#         INCLUDE_DIRS ".")
