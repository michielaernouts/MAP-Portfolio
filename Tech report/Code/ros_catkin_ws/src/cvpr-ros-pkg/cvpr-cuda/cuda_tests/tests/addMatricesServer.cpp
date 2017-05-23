#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sys/time.h>

/* call_addMatrix is a host function defined in addMatrix.cu. */
void call_addMatrix( float *C, float *A, float *B, int N);

/* Add two matrices using addMatrix; the result should have 2^20 in each position */
void testAddMatrix (void) {
  float *A, *B, *C;
  int i;

  A = (float*) malloc(1024 * 1024 * sizeof(*A));
  B = (float*) malloc(1024 * 1024 * sizeof(*B));
  C = (float*) malloc(1024 * 1024 * sizeof(*C));

  if (!A || !B || !C) {
    printf("Unable to allocate some of the matrices :'(\n");
    return;
  }

  for (i = 1024 * 1024 - 1; i != 0; --i) {
    A[i] = i;
    B[i] = 1024*1024 - i;
  }

  call_addMatrix((float*) C, (float*) A, (float*) B, 1024);

  for (i = 1024 * 1024 - 1; i != 0; --i) {
    if (C[i] != A[i] + B[i]) {
      printf("Error at position %d! %f + %f != %f\n", i, A[i], B[i], C[i]);
      ros::shutdown();
    }
  }

  printf("All good! :) Now running on CPU ...\n");

  struct timeval time_start;
  gettimeofday(&time_start, NULL);

  for (int i = 1024; i != 0; --i) {
    for (int j = 0; j < 1024 * 1024; ++j) {
      C[j] = A[j] + B[j];
    }
  }
  
  struct timeval time_end;
  gettimeofday(&time_end, NULL);

  double time_float = (time_end.tv_sec - time_start.tv_sec) + (time_end.tv_usec - time_start.tv_usec) * 0.000001;

  printf("CPU completed 1024 runs in %f\n", time_float);

  free(A); free(B); free(C);
}

/* Put up a useless ROS node */
int main (int argc, char **argv) {
  ros::init(argc, argv, "matrix_adder");

  ros::NodeHandle node;

  ros::Publisher pub = node.advertise<std_msgs::String>("addmatrices_status", 1);

  ros::Duration loop_rate(1.0);

  while (ros::ok()) {
    testAddMatrix();
    std_msgs::String str;
    str.data = "Processed.";
    pub.publish(str);
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
