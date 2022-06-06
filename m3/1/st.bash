rm -r ./build/*
cd build
scan-build cmake ..
scan-build make
printf "main:\n--------------\n"
./1
printf "\n--------------\nTests:\n"
./Tests