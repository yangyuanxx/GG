rm -rf bin bin-int
rm -rf GG/vendor/GLFW/bin GG/vendor/GLFW/bin-int
rm -rf GG/vendor/Glad/bin GG/vendor/Glad/bin-int
rm -rf GG/vendor/imgui/bin GG/vendor/imgui/bin-int
./GenerateProject.sh
make clean
make