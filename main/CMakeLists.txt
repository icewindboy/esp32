set(SOURCES 
  "blufi_example_main.c"
  "app/app.c"
  "pages/calibration.c"
  "blufi/blufi_init.c"
  "blufi/blufi_security.c"
  "blufi/blufi_server.c"

  )

set(include_dirs 
  app
  pages
  blufi  
)

idf_component_register(SRCS  
          ${SOURCES} 
          INCLUDE_DIRS ${include_dirs})

# idf_component_register(SRCS "main.cpp"
#         INCLUDE_DIRS ".")
