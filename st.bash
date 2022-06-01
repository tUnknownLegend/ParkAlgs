rm -r ./build/*
cd build
scan-build cmake ..
scan-build make
printf "main:\n--------------\n"
valgrind --tool=memcheck --leak-check=yes --error-exitcode=1 ./1
printf "\n--------------\nTests:\n"
valgrind --tool=memcheck --leak-check=yes --error-exitcode=1 ./Tests