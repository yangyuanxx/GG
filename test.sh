rm -rf bin bin-int
rm -rf GG/vendor/GLFW/bin GG/vendor/GLFW/bin-int
./GenerateProject.sh
make clean
make