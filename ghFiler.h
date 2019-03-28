#include "support.h"

#ifndef gh_H
#define gh_H

  // fgFilter Beliefs
  struct ghFilter {
    float g;  // Position Scaler (belief)
    float h;  // Velocity Scaler (belief)
  };

  // State variables
  struct ghSystem {
    float x;  // State position
    float dx; // State velocity
  };

  // Measurement and time-step
  struct ghMeasurement {
    float z;  // Observation
    float dt; // Time Interval (since last measurement)
  };

  // Prediction (prior)
  // System/Plant model (change to describe plant)
  void ghProcessModel(struct ghSystem * pEstSys, struct ghSystem * pPredictSys, float dt) {
    pPredictSys->x = pEstSys->x + (pEstSys->dx)*(dt); // Xp = Xe + DXe * DTe
    pPredictSys->dx = pEstSys->dx; // DXp = DXe
    return;
  }

  // Update step of filter
  void ghUpdate(struct ghFilter filter, struct ghSystem * pEstSys, struct ghMeasurement meas) {
    // Prior
    static struct ghSystem PredictSys = {.x=0, .dx=0}, * pPredictSys = &PredictSys;

    // Prediction Step
    ghProcessModel(pEstSys, pPredictSys, meas.dt);

    // Update Step
    float residual = meas.z - PredictSys.x;
    pEstSys->dx = PredictSys.dx + filter.h * (residual/meas.dt);
    pEstSys->x = PredictSys.x + filter.g * residual;
  }

  // Same as ghUpdate, but provided formated text output (to terminal) for troubleshooting
  void ghUpdate_verbose(struct ghFilter filter, struct ghSystem * pEstSys, struct ghMeasurement meas) {
    static struct ghSystem PredictSys = {.x=0, .dx=0}, * pPredictSys = &PredictSys;
    printf("previous: %6.2f, ", pEstSys->x);

    // Prediction Step
    ghProcessModel(pEstSys, pPredictSys, meas.dt);
    printf("Xp: %6.2f, ", pPredictSys->x);

    // Update Step
    float residual = meas.z - PredictSys.x;
    printf("Xz: %6.2f, ", meas.z);
    printf("res: %6.2f, ", residual);
    pEstSys->dx = PredictSys.dx + filter.h * (residual/meas.dt);
    pEstSys->x = PredictSys.x + filter.g * residual;
    printf("Xe: %6.2f\n", pEstSys->x);
  }

  void ghUpdate_verbose2(struct ghFilter filter, struct ghSystem * pEstSys, struct ghMeasurement meas) {
    static struct ghSystem PredictSys = {.x=0, .dx=0}, * pPredictSys = &PredictSys;
    printf("%8.2f\t", pEstSys->x);

    // Prediction Step
    ghProcessModel(pEstSys, pPredictSys, meas.dt);
    printf("%8.2f\t", pPredictSys->x);

    // Update Step
    float residual = meas.z - PredictSys.x;
    printf("%8.2f\t", meas.z);
    printf("%8.2f\t", residual);
    pEstSys->dx = PredictSys.dx + filter.h * (residual/meas.dt);
    pEstSys->x = PredictSys.x + filter.g * residual;
    printf("%8.2f\n", pEstSys->x);
  }

  // Print ghFilter's members
  void print_ghFilter(struct ghFilter filter) {
    puts("g-h Filter Properties");
    printDashLine(30);
    printf("  g : %f", filter.g);
    printf("  h : %f", filter.h);
    puts("\n");
    return;
  }

  // Print ghSystem's members
  void print_ghSystem(struct ghSystem sys) {
    puts("System Properties");
    printDashLine(30);
    printf("  x  : %f", sys.x);
    printf("  dx : %f", sys.dx);
    puts("\n");
    return;
  }

  // Print ghMeasurement's members
  void print_ghMeasurement(struct ghMeasurement meas) {
    puts("Measurement Properties");
    printDashLine(30);
    printf("  z  : %f", meas.z);
    printf("  dt : %f", meas.dt);
    puts("\n");
    return;
  }

  // not implemented
  void print_ghUpdate() {
    return;
  }


#endif /* bayes_H */
