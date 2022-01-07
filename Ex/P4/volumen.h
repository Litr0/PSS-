double volumenSec(double (*f)(double x, double y),
    double xi, double xf, double yi, double yf,
    int n, int p);
double volumen(double (*f)(double x, double y),
    double xi, double xf, double yi, double yf,
    int n, int p);
int leer(int fd, void *vbuf, int n);
double double_random(double a, double b);
long long getUSecsOfDay();
