#include <vector>
#include <cmath>
#include <iomanip>
#include <functional>
class Integration {
public:

	enum class Types
	{
		SIMPSON, TRAPEZOID, RECTANGLE, GAUSS_LEGENDRE
	};

	Integration() = default;
	double integrate(std::function<double(double)> func,double a, double b, int n = 1000, Types type = Types::SIMPSON);

private:
	double a, b; // granice ca³kowania
	struct GaussPoint
	{
		double x, w;
	};
	std::vector<Integration::GaussPoint> getGaussPoints(int n);
	double rectangle(std::function<double(double)> func, double a, double b, int n);
	double trapezoid(std::function<double(double)> func, double a, double b, int n);
	double simpson(std::function<double(double)> fun, double a, double b, int n);
	double gaussLegendreIntegrate(std::function<double(double)> f, double a, double b, int n);

};
