By creating a function "multiThread" to calculate colors of pixels 
on certain rows, we are able to divide the entire image into several 
parts and make each thread be responsible for each part. I structed a 
new data type called "imagepixel", which contains the information about 
the scene, the number of threads and the id of the thread responsible 
for certain pixels. Also, I declare a variable scaled_color_entire to 
store 3 parameters for all pixels in the image so that in main function, 
I can print all the pixels' color parameters. In the for loop of 
multiThread, I changed the initial value of py to thread_id and 
incremented py by nthreads. This way, each thread evaluates the 
(thread_id + a * nthreads)th row, where a is an integer. This helps 
make sure that all threads run in parallel. Memory spaces are dynamically 
allocated for the threads of size nthreads and thread_id. This enables 
the function to generate as many threads as needed.

1 thread:
real   0m48.695s
user   0m48.698s
sys    0m0.001s

2 threads:
real	0m24.296s
user	0m48.217s
sys	0m0.001s

4 threads:
real	0m12.705s
user	0m49.573s
sys	0m0.003s

8 threads:
real	0m7.924s
user	0m53.077s
sys	0m0.019s

From the results, we notice that the more threads used, the faster 
the program got executed. This is because multiple threads run at the 
same times and divide the task so that colors of several pixels are 
being calculated simultaneously.With n threads, the program speeds up 
approximately n times.
