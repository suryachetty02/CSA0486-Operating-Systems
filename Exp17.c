#include <stdio.h>

int main() {

  int n = 5;
  int m = 3; 
  int available[m]; 
  int max[n][m]; 
  int allocation[n][m];
  int need[n][m]; 

  available[0] = 5;
  available[1] = 10;
  available[2] = 15;


  max[0][0] = 2;
  max[0][1] = 3;
  max[0][2] = 4;
  max[1][0] = 3;
  max[1][1] = 5;
  max[1][2] = 6;
  max[2][0] = 4;
  max[2][1] = 6;
  max[2][2] = 8;


  allocation[0][0] = 1;
  allocation[0][1] = 2;
  allocation[0][2] = 3;
  allocation[1][0] = 0;
  allocation[1][1] = 1;
  allocation[1][2] = 2;
  allocation[2][0] = 3;
  allocation[2][1] = 4;
  allocation[2][2] = 5;


  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      need[i][j] = max[i][j] - allocation[i][j];
    }
  }

  int isSafe = 1;
  for (int i = 0; i < n; i++) {
    int k = 0;
    while (k < m) {
      if (need[i][k] > available[k]) {
        isSafe = 0;
        break;
      }
      k++;
    }
    if (!isSafe) {
      break;
    }
  }


  if (isSafe) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        allocation[i][j] += need[i][j];
        available[j] -= need[i][j];
      }
    }
  } else {

    printf("The system is in a deadlock state.\n");
  }

  return 0;
}
