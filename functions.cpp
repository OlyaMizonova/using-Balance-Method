#include"NamesOfFunctions.h"

double u_for_test(double x) {
	if (x < 0.25) {
		return 0.587442041369270784325 * exp(sqrt(2) * x) - 1.587442041369270784325 * exp(-sqrt(2) * x)+1;
	}
	else {
		return -16.237319865422281265629536 * exp((1 / (2 * sqrt(5)) * x)) - 23.37825943652863832026 * exp(-(1 / (2 * sqrt(5)) )*x)+40;
	}
}

double d_i(double h, double breaking_point, double x_i_minus_05, double x_i_plus_05, double x_i, int is_test_task) {//возможно стоит вычислять иксы внутри функции
	if (is_test_task) {
		if (x_i_plus_05 <= breaking_point) {
			return 1.;
		}
		if (x_i_minus_05 >= breaking_point) {
			return 0.0625;
		}
		if (x_i_minus_05 <= breaking_point && x_i_plus_05 >= breaking_point) {
			return (1 / h) * (breaking_point - x_i_minus_05) + (0.0625 / h) * (x_i_plus_05 - breaking_point);
		}
	}
	else {
		if (x_i_plus_05 <= breaking_point) {
			return 1.;
		}
		if (x_i_minus_05 >= breaking_point) {
			return pow(x_i, 2);
		}
		if (x_i_minus_05 <= breaking_point && x_i_plus_05 >= breaking_point) {
			return (1 / h) * (breaking_point - x_i_minus_05) + (1 / h) * pow(((breaking_point + x_i_plus_05) / 2), 2) * (x_i_plus_05 - breaking_point);
		}
	}
}

double a_i(double h, double breaking_point, double x_i_minus_05, double x_i_minus_1, double x_i, int is_test_task) {
	if (is_test_task) {
		if (x_i <= breaking_point) {
			return 0.5;
		}
		if (x_i_minus_1 >= breaking_point) {
			return 1.25;
		}
		if (x_i_minus_1 <= breaking_point && breaking_point <= x_i) {
			return pow((2./h)*(breaking_point-x_i_minus_1)+(4/(5*h))*(x_i-breaking_point),-1);
		}
	}
	else {
		if (x_i <= breaking_point) {
			return sqrt(x_i_minus_05);
		}
		if (x_i_minus_1 >= breaking_point) {
			return x_i_minus_05 + 1;
		}
		if (x_i_minus_1 <= breaking_point && breaking_point <= x_i) {
			double first = (breaking_point - x_i_minus_1) / (sqrt((breaking_point + x_i_minus_1) / 2));
			double second = (x_i - breaking_point) / (((breaking_point + x_i) / 2) + 1);
			return pow(((1 / h) * (first + second)), -1);
		}
	}
}

double fi_i(double h, double breaking_point, double x_i_minus_05, double x_i_plus_05, double x_i, int is_test_task) {
	if (is_test_task) {
		if (x_i_plus_05 <= breaking_point) {
			return 1;
		}
		if (x_i_minus_05 >= breaking_point) {
			return 2.5;
		}
		if (x_i_minus_05 <= breaking_point && breaking_point <= x_i_plus_05) {
			return (1/h)*(breaking_point-x_i_minus_05)+(2.5/h)*(x_i_plus_05-breaking_point);
		}
	}
	else {
		if (x_i_plus_05 <= breaking_point) {
			return 1;
		}
		if (x_i_minus_05 >= breaking_point) {
			return sqrt(x_i) + 2;
		}
		if (x_i_minus_05 <= breaking_point && breaking_point <= x_i_plus_05) {
			double first = (1 / h) * (breaking_point - x_i_minus_05);
			double second = (1 / h) * (sqrt((breaking_point + x_i_plus_05) / 2) + 2) * (x_i_plus_05 - breaking_point);
			return first + second;
		}
	}
}

double A_i(int i, double h, double breaking_point, int is_test_task) {
	double ai = a_i(h, breaking_point, (i - 0.5) * h, (i - 1) * h, i * h, is_test_task);
	return ai / (pow(h, 2));
}

double B_i(int i, double h, double breaking_point, int is_test_task) {
	int new_i = i + 1;
	double ai_plus_1 = a_i(h, breaking_point, (new_i - 0.5) * h, (new_i - 1) * h, new_i * h, is_test_task);
	return ai_plus_1 / (pow(h, 2));
}

double C_i(int i, double h, double breaking_point, int is_test_task) {
	double ai = a_i(h, breaking_point, (i - 0.5) * h, (i - 1) * h, i * h, is_test_task);
	int new_i = i + 1;
	double ai_plus_1 = a_i(h, breaking_point, (new_i - 0.5) * h, (new_i - 1) * h, new_i * h, is_test_task);
	double di = d_i(h, breaking_point, (i - 0.5) * h, (i + 0.5) * h, i * h, is_test_task);
	return ((1 / pow(h, 2)) * (ai + ai_plus_1) + di);
}

vector<double> sweepMethod(double left_boarder, double h, double n, double mu1, double mu2, double breaking_point, int is_test_task) {
	vector<double> result(n+1);
	result[0]=mu1;
	result[n] = mu2;
	vector<double> alpha(n), beta(n);
	alpha[0] = 0;
	beta[0] = 0;

	//прямой ход прогонки
	for (int i = 1; i < n; i++) {//у альфа и бета (и коэфф АВС) индексы сдвинуты на 1
		double Ai_minus_1 = A_i(i, h, breaking_point, is_test_task);
		double Bi_minus_1 = B_i(i, h, breaking_point, is_test_task);
		double Ci_minus_1 = C_i(i, h, breaking_point, is_test_task);
		double fii_minus_1 = fi_i(h, breaking_point, (i - 0.5) * h, (i+0.5)*h,i*h, is_test_task);
		alpha[i] = Bi_minus_1 / (Ci_minus_1-Ai_minus_1*alpha[i-1]);
		beta[i] = (fii_minus_1 + Ai_minus_1 * beta[i - 1]) / (Ci_minus_1 - Ai_minus_1 * alpha[i - 1]);
	}

	//обратный ход прогонки
	for (int i = n - 1; i > 0; i--) {
		result[i] = alpha[i] * result[i + 1] + beta[i];
	}
	return result;
}

vector<vector<double>> differenceScheme(double left_boarder, double h, double n, double mu1, double mu2, double breaking_point, int is_test_task) {
	vector<vector<double>> result;
	vector<double> v_with_usual_h = sweepMethod(left_boarder, h, n, mu1, mu2, breaking_point, is_test_task);
	if (!is_test_task) {
		vector<double> v_with_half_h = sweepMethod(left_boarder, h / 2, n * 2, mu1, mu2, breaking_point, is_test_task);
		vector<double>v_minus_v_half_h(n + 1);
		for (int i = 0; i < n + 1; i++) {
			v_minus_v_half_h[i] = abs(v_with_usual_h[i] - v_with_half_h[2*i]);
			result.push_back({ i * h,v_with_usual_h[i],v_with_half_h[2 * i],v_minus_v_half_h[i] });
		}
	}
	else {
		vector<double>u_x(n + 1);
		vector<double>u_x_minus_v(n + 1);
		for (int i = 0; i < n + 1; i++) {
			double xi = i * h;
			u_x[i] = u_for_test(xi);
			u_x_minus_v[i] = abs(u_x[i] - v_with_usual_h[i]);
			result.push_back({ i * h,v_with_usual_h[i],u_x[i],u_x_minus_v[i] });
		}
	}
	return result;
}