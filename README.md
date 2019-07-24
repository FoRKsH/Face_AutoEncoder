# Face_autoEncoder
A simple face autoencoder neural network using c++.
This project is fully written in C++ without any external libraries.
Works best on codeblocks with c11 compiler.
You can simply create a Trainset object and call loadtrain to load the trainset Data. // please note input is 10K pixel , same as output
Create Network object passing number of layers including the output layers
Don't forget to initialize  each layer with number of neurons , Alpha.
Create trainer object and call Train function giving the number of cycles.
thats all 
