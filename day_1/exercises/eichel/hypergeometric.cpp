#define ACP_TEST_CPP
#include <iostream>
#include <numeric>
#include <cmath>
#include <vector>

// file to serve as a starting point

void hypergeometric(std::vector<double>& dist, int n, int a, int b, int q){
  using namespace std;

  int i, m, l, j, mab, mmax, mmin, lmax, lmin;
  double qs;
  float prog;

  mab = min(a,b);

  int size = mab+1;

  if(dist.size() != size)
    dist.resize(mab+1);

  for(i = 0; i < (mab+1); i++){

    qs = 0;
    mmin = max((a-i-n+q),0);
    mmax = min((a-i),q);

    for(m = mmin; m <= mmax; m++){

      lmin = max((a-n+q-m),0);
      lmax = min(i,(q-m));

      for(l = lmin; l <= lmax; l++){

	for(j = 0; j <= l; j++){

	  qs = qs + exp( (lgamma(n-q+1) - lgamma(n-q-i+l+1) - lgamma(i-l+1) + lgamma(q+1) - lgamma(l-j+1) - lgamma(j+1) - lgamma(q-l-m+1) - lgamma(m+1) + lgamma(n-i-q+l+1) - lgamma(n-q+l-a+m+1) - lgamma(a-i-m+1) + lgamma(n+q-a-m-j+1) - lgamma(n+q-a-m-j-b+i+1) - lgamma(b-i+1) - lgamma(n+1) + lgamma(n-a+1) + lgamma(a+1) - lgamma(n+q+1) + lgamma(n+q-b+1) + lgamma(b+1)) );

	}
      }
    }

    dist.at(i) = qs;
  }

}

int main(int argc, char *argv[])
{
  int n = 100, a = 35, b = 41, q = 76;

  std::vector<double> dist;

  hypergeometric(dist,n,a,b,q);

  double sum = std::accumulate(dist.begin(), dist.end(), 0.);
  
  std::cout << "1] sum = " << sum << "\n";

  hypergeometric(dist,500,250,350,102);

  sum = std::accumulate(dist.begin(), dist.end(), 0.);
  std::cout << "2] sum = " << sum << "\n";


  return 0;
}
