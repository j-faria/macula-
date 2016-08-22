# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <cmath>
#include <random>

using namespace std;

int main ( );
void testmacula();

extern "C" {
  void macula(double t[], int *ndata, int *Nspot, int *mmax, 
               int *derivatives, int *temporal, int *TdeltaV, // Controls
               double Theta_star[], double Theta_spot[], double Theta_inst[], // Star, Spot & Instrument parameters
               double Tstart[], double Tend[], // Times of start/end for each data set
               double Fmod[], double dFmod_star[], double dFmod_spot[], 
               double dFmod_inst[], double dFmoddt[], double deltaratio[]); // Outputs
}


int main ( )
{

  cout << "\n";

  testmacula();

  cout << "  Normal end of execution.\n";

  return 0;
}


void testmacula()
{
  
  random_device rd;
  mt19937 gen(rd());
  uniform_real_distribution<> uniformdist(0, 1);

  int ndata = 1e2; // # of data points
  int Nspot = 5;   // # of star spots
  int mmax = 1;    // # of quarters/instruments
  int derivatives = 0; // Calculate partial derivatives?
  int temporal = 0; // Calculate temporal derivatives?
  int TdeltaV = 0; // Calculate transit depth variations?

  int i, k, l;

  double t[ndata];
  double Theta_star[12];
  double Theta_spot[Nspot*8];
  double Theta_inst[mmax*2];
  double Tstart[mmax], Tend[mmax];
  double Fmod[ndata], deltaratio[ndata];
  double dFmod_star[12*ndata];
  double dFmod_spot[Nspot*8*ndata];
  double dFmod_inst[mmax*2*ndata];
  double dFmoddt[ndata];

  double degs = 0.017453292519943295;
  double Pi = 3.141592653589793;


  // Create some dummy times
  for (i=0; i<ndata; i++)
    t[i] = 55000.0 + 0.1*i;

  // Define start and end time of this dummy data set
  Tstart[0] = t[0] - 0.05;
  Tend[0] = t[ndata-1] + 0.05;

  // Star's parameters
  Theta_star[0]  = uniformdist(gen)*Pi-0.5*Pi; // inclination
  Theta_star[1]  = 0.23333*(Tend[0]-Tstart[0])*uniformdist(gen)+0.1*(Tend[0]-Tstart[0]); //  P_EQ
  Theta_star[2]  = 0.40*uniformdist(gen) - 0.20; //  kappa2
  Theta_star[3]  = 0.40*uniformdist(gen) - 0.20; //  kappa4
  Theta_star[4]  = 0.3999;    // c1
  Theta_star[5]  = 0.4269;    // c2
  Theta_star[6]  =-0.0227;    // c3
  Theta_star[7]  =-0.0839;    // c4
  Theta_star[8]  = 0.3999;    // d1
  Theta_star[9] = 0.4269;    // d2
  Theta_star[10] =-0.0227;    // d3
  Theta_star[11] =-0.0839;    // d4


  // Spot parameters
  for (int k = 0; k < Nspot; k++)
  {
    /* code */
   Theta_spot[Nspot*k] = uniformdist(gen)*2.0*Pi - Pi;      // longitude
   Theta_spot[Nspot*k + 1] = uniformdist(gen)*Pi - 0.5*Pi;      // latitude
   Theta_spot[Nspot*k + 2] = uniformdist(gen)*10.0*degs;      // alpha_max
   Theta_spot[Nspot*k + 3] = uniformdist(gen)*0.5;       // fspot
   Theta_spot[Nspot*k + 4] = uniformdist(gen)*(Tend[mmax-1]-Tstart[0])+Tstart[0]; // tmax
   Theta_spot[Nspot*k + 5] = (Tend[mmax-1]-Tstart[0])*uniformdist(gen);  // lifetime
   Theta_spot[Nspot*k + 6] = (Tend[mmax-1]-Tstart[0])*uniformdist(gen);  // ingress
   Theta_spot[Nspot*k + 7] = (Tend[mmax-1]-Tstart[0])*uniformdist(gen);  // egress    
  }

  // Instrumental parameters
  Theta_inst[0]  = 1.0;  // U(1)
  Theta_inst[1]  = 1.0;  // B(1)

  macula(t, &ndata, &Nspot, &mmax, &derivatives, &temporal, &TdeltaV, // Controls
              Theta_star, Theta_spot, Theta_inst,   // Star, Spot and Instrument parameters
              Tstart, Tend,        // Times of start/end for each data set
              Fmod, dFmod_star, dFmod_spot, dFmod_inst, dFmoddt, deltaratio); // Outputs

  for (int i = 0; i < ndata; i++)
  {
    cout << "  " << t[i]<< "  " <<Fmod[i]<< "  " <<deltaratio[i]<< "  " <<dFmoddt[i] <<"\n";
  }

  return;
}
