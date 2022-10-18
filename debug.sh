idf.py build
cd build
/opt/esp/idf/components/esptool_py/esptool/esptool.py --chip esp32 merge_bin --fill-flash-size 4MB -o flash_image.bin @flash_args
cd ..

qemu-system-xtensa -nographic -s -S -machine esp32  -drive file=flash_image.bin,if=mtd,format=raw
