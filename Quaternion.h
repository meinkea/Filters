#ifndef QUATERNION_H
#define QUATERNION_H

#include <stdio.h>
#include <math.h>
#include <string.h>

#define M_PI 3.14159265358979323846

const static int QUAT_SIZE = 4*sizeof(float);
typedef float quat[4]; // [w, i, j, k]
typedef float euler[3]; // [R, P. Y]


// Predefining basic Quaternions
quat Qzero = {  0.00,  0.00,  0.00,  0.00};

quat Qw = {  1.00,  0.00,  0.00,  0.00};
quat Qi = {  0.00,  1.00,  0.00,  0.00};
quat Qj = {  0.00,  0.00,  1.00,  0.00};
quat Qk = {  0.00,  0.00,  0.00,  1.00};

quat Qwi = {  1.00,  1.00,  0.00,  0.00};
quat Qwj = {  1.00,  0.00,  1.00,  0.00};
quat Qwk = {  1.00,  0.00,  0.00,  1.00};
quat Qij = {  0.00,  1.00,  1.00,  0.00};
quat Qik = {  0.00,  1.00,  0.00,  1.00};
quat Qjk = {  0.00,  0.00,  1.00,  1.00};

quat Qwij = {  1.00,  1.00,  1.00,  0.00};
quat Qwik = {  1.00,  1.00,  0.00,  1.00};
quat Qwjk = {  1.00,  0.00,  1.00,  1.00};
quat Qijk = {  0.00,  1.00,  1.00,  1.00};

quat Qwijk = {  1.00,  1.00,  1.00,  1.00};


// Set Quaternion using another quat
void Qset(quat qres, quat qData) {
  memcpy(qres, qData, QUAT_SIZE);
}
// Set Quaternion using vector
void QsetArray(quat qres, float qData[4]) {
  memcpy(qres, qData, QUAT_SIZE);
}


// Basic mathematic opperations
void Qadd(quat qres, quat qA, quat qB) {
  qres[0] = qA[0] + qB[0];
  qres[1] = qA[1] + qB[1];
  qres[2] = qA[2] + qB[2];
  qres[3] = qA[3] + qB[3];
  return;
}
void Qsub(quat qres, quat qA, quat qB) {
  qres[0] = qA[0] - qB[0];
  qres[1] = qA[1] - qB[1];
  qres[2] = qA[2] - qB[2];
  qres[3] = qA[3] - qB[3];
  return;
}
void Qmul(quat qres, quat qA, quat qB) {
  static quat q = {0.0,0.0,0.0,0.0};

  q[0] =  qA[0]*qB[0] - qA[1]*qB[1] - qA[2]*qB[2] - qA[3]*qB[3];
  q[1] =  qA[0]*qB[1] + qA[1]*qB[0] + qA[2]*qB[3] - qA[3]*qB[2];
  q[2] =  qA[0]*qB[2] - qA[1]*qB[3] + qA[2]*qB[0] + qA[3]*qB[1];
  q[3] =  qA[0]*qB[3] + qA[1]*qB[2] - qA[2]*qB[1] + qA[3]*qB[0];

  memcpy(qres, q, QUAT_SIZE);
  return;
}

//
void QscalarMultiply(quat qres, quat q, float s) {
  qres[0] = s*q[0];
  qres[1] = s*q[1];
  qres[2] = s*q[2];
  qres[3] = s*q[3];
  return;
}
void Qconjugate(quat qres, quat q) {
  qres[0] = 1*q[0];
  qres[1] = -1*q[1];
  qres[2] = -1*q[2];
  qres[3] = -1*q[3];
  return;
}
float Qnorm(quat q) {
  float norm = q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3];
  return norm;
}
void Qnormalize(quat qres, quat q) {
  static double n = 0;
  n = sqrt(Qnorm(q));
  qres[0] /= n;
  qres[1] /= n;
  qres[2] /= n;
  qres[3] /= n;
  return;
}


//Yaw = ψ - Z
//Pitch = θ - Y
//Roll = φ  - X
void Euler_to_Q(quat q, euler a) {

  printf("a(deg) : \t%5.2f \t%5.2f \t%5.2f\n", a[0], a[1], a[2]);

  float b[3] = {0,0,0};
  b[0] = a[0];  b[1] = a[1];  b[2] = a[2];
  for (int I=0; I<3; ++I) {
    b[I] *= M_PI/180;
  }
  printf("a(rad) : \t%5.2f \t%5.2f \t%5.2f\n", b[0], b[1], b[2]);
  
  float cy = cos(a[0]*(M_PI/360));
  float cp = cos(a[1]*(M_PI/360));
  float cr = cos(a[2]*(M_PI/360));
  float sy = sin(a[0]*(M_PI/360));
  float sp = sin(a[1]*(M_PI/360));
  float sr = sin(a[2]*(M_PI/360));

  //printf("cos : \t%5.2f \t%5.2f \t%5.2f\n", cy, cp, cr);
  //printf("sin : \t%5.2f \t%5.2f \t%5.2f\n", sy, sp, sr);

  q[0] = cy*cp*cr + sy*sp*sr;
  q[1] = cy*cp*sr - sy*sp*cr;
  q[2] = cy*sp*cr + sy*cp*sr;
  q[3] = sy*cp*cr - cy*sp*sr;

  printf("res 1 : %5.2f + %5.2fi + %5.2fj + %5.2fk\n", q[0], q[1], q[2], q[3]);
  puts("");

  return;
}

float AngleNorm(euler a) {
  float norm = a[0]*a[0]+a[1]*a[1]+a[2]*a[2];
  return norm;
}

void AngularRate_to_Q(quat qres, euler w, float dt) {
  // w ~ angular rate vecotor [x,y,z] (rad/s) (constant approximation)
  // note: w is in IMU's reference frame, all coords in 
  // dt ~ time interval during which w is a reasonable apporximation

  float l = sqrt(AngleNorm(w));
  float dtlo2 = dt * l / 2; // (dt*|w|)/2
  float c = cos(dtlo2); // cos( dt*|w|)/2 )
  float s = sin(dtlo2); // sin(dt*|w|)/2)

  // [ c, (wx/|w|)*s, (wy/|w|)*s, (wz/|w|)*s ]
  qres[0] = c;
  qres[1] = s * w[0] / l;
  qres[2] = s * w[1] / l;
  qres[3] = s * w[3] / l;

  Qnormalize(qres, qres); // Normalize, to take care of rounding errors

  return;
}


void printqf(char * z, quat qres) {
  printf("%s = %.2fw %.2fi %.2fj %.2fk\n", z, qres[0], qres[1], qres[2], qres[3]);
  return;
}

#endif /* QUATERNION_H */
