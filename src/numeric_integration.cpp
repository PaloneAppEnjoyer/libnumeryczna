//ca³kowanie nuemryczne L6, L7
#include "../pch.h"
#include "../include/numeric_integration.h"

double Integration::integrate(std::function<double(double)> func, double a, double b, int n, Types type)
{
	if (n <= 0)
	{
		throw std::invalid_argument("Liczba podzia³ów musi byæ dodatnia.");
	}
	switch (type)
	{
	case Types::SIMPSON:
		return simpson(func, a, b, n);
	case Types::TRAPEZOID:
		return trapezoid(func, a, b, n);
	case Types::RECTANGLE:
		return rectangle(func, a, b, n);
	case Types::GAUSS_LEGENDRE:{
        double sum = 0.0;
        for (int i = 0; i < n; ++i)
        {
            double sub_a = a + i * (b - a) / n;
            double sub_b = a + (i + 1) * (b - a) / n;
            sum += gaussLegendreIntegrate(func, sub_a, sub_b, 4);
        }
        return sum;
        }
	default:
		throw std::invalid_argument("Nieobs³ugiwany typ ca³kowania.");
	}
    return 0.0;
}

std::vector<Integration::GaussPoint> Integration::getGaussPoints(int n)
{
    switch (n)
    {
    case 2:
        return { {-1.0 / std::sqrt(3), 1.0}, {1.0 / std::sqrt(3), 1.0} };
    case 3:
        return {
            {-std::sqrt(3.0 / 5.0), 5.0 / 9.0},
            {0.0, 8.0 / 9.0},
            {std::sqrt(3.0 / 5.0), 5.0 / 9.0} };
    case 4:
        return {
            {-sqrt(3.0 / 7.0 + (2.0 / 7.0) * sqrt(6.0 / 5.0)), (18 - sqrt(30.0)) / 36},
            {-sqrt(3.0 / 7.0 - (2.0 / 7.0) * sqrt(6.0 / 5.0)), (18 + sqrt(30.0)) / 36},
            {sqrt(3.0 / 7.0 - (2.0 / 7.0) * sqrt(6.0 / 5.0)), (18 + sqrt(30.0)) / 36},
            {sqrt(3.0 / 7.0 + (2.0 / 7.0) * sqrt(6.0 / 5.0)), (18 - sqrt(30.0)) / 36} };
    default:
        throw std::invalid_argument("Nieobs³ugiwana liczba wêz³ów");
    }
}

double Integration::gaussLegendreIntegrate(std::function<double(double)> f, double a, double b, int n)
{
    auto points = getGaussPoints(n);
    double result = 0.0;
    for (auto& pt : points)
    {
        double xi = ((b - a) / 2.0) * pt.x + (a + b) / 2.0;
        result += pt.w * f(xi);
    }
    return result * (b - a) / 2.0;
}

double Integration::rectangle(std::function<double(double)> func, double a, double b, int n)
{
    double h = (b - a) / n;
    double sum = 0.0;
    for (int i = 0; i < n; i++)
    {
        double xi = a + i * h;
        sum += func(xi);
    }
    return h * sum;
}

double Integration::trapezoid(std::function<double(double)> func, double a, double b, int n)
{
    double h = (b - a) / n;
    double sum = 0.5 * (func(a) + func(b));
    for (int i = 1; i < n; i++)
    {
        sum += func(a + i * h);
    }
    return h * sum;
}

double Integration::simpson(std::function<double(double)> fun, double a, double b, int n)
{
    if (n % 2 != 0)
        n++;
    double h = (b - a) / n;
    double sum = fun(a) + fun(b);

    for (int i = 1; i < n; i++)
    {
        double xi = a + i * h;
        sum += (i % 2 == 0 ? 2 : 4) * fun(xi);
    }
    return h / 3 * sum;
}