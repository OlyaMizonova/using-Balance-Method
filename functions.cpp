#include"NamesOfFunctions.h"

pair<double, double> max(vector <vector <double>> v) {
	pair<double, double> Max(0.0, 0.0);
	for (int i = 0; i < size(v); i++) {
		if (Max.first < v[i][3]) {
			Max.first = v[i][3];
			Max.second = v[i][0];
		}
	}
	return Max;
}

double u_for_test(double x) {
	if (x < 0.25) {
		return 0.587442041369270784325 * exp(sqrt(2) * x) - 1.587442041369270784325 * exp(-sqrt(2) * x)+1;
	}
	else {
		return -16.237319865422281265629536 * exp((1 / (2 * sqrt(5)) * x)) - 23.37825943652863832026 * exp(-(1 / (2 * sqrt(5)) )*x)+40;
	}
}

double d_i(double h, double breaking_point, double x_i_minus_05, double x_i_plus_05, double x_i, int is_test_task) {
	if (is_test_task) { // тестовая задача
		if (x_i_plus_05 <= breaking_point) { // отрезок левее точки разрыва
			return 1.;
		}
		if (x_i_minus_05 >= breaking_point) { // отрезок правее точки разрыва 
			return 0.0625;
		}
		if (x_i_minus_05 <= breaking_point && x_i_plus_05 >= breaking_point) { // точка разрыва принадлежит отрезку
			return (1 / h) * (breaking_point - x_i_minus_05) + (0.0625 / h) * (x_i_plus_05 - breaking_point);
		}
	}
	else { // основная задача
		if (x_i_plus_05 <= breaking_point) {// отрезок левее точки разрыва
			return 1.;
		}
		if (x_i_minus_05 >= breaking_point) { // отрезок правее точки разрыва 
			return pow(x_i, 2);
		}
		if (x_i_minus_05 <= breaking_point && x_i_plus_05 >= breaking_point) { // точка разрыва принадлежит отрезку
			return (1 / h) * (breaking_point - x_i_minus_05) + (1 / h) * pow(((breaking_point + x_i_plus_05) / 2), 2) * (x_i_plus_05 - breaking_point);
		}
	}
}

double a_i(double h, double breaking_point, double x_i_minus_05, double x_i_minus_1, double x_i, int is_test_task) {
	if (is_test_task) { // тестовая задача
		if (x_i <= breaking_point) { // отрезок левее точки разрыва
			return 0.5;
		}
		if (x_i_minus_1 >= breaking_point) { // отрезок правее точки разрыва 
			return 1.25;
		}
		if (x_i_minus_1 <= breaking_point && breaking_point <= x_i) { // точка разрыва принадлежит отрезку
			return pow((2./h)*(breaking_point-x_i_minus_1)+(4/(5*h))*(x_i-breaking_point),-1);
		}
	}
	else { // основная задача
		if (x_i <= breaking_point) { // отрезок левее точки разрыва
			return sqrt(x_i_minus_05);
		}
		if (x_i_minus_1 >= breaking_point) { // отрезок правее точки разрыва 
			return x_i_minus_05 + 1;
		}
		if (x_i_minus_1 <= breaking_point && breaking_point <= x_i) { // точка разрыва принадлежит отрезку
			double first = (breaking_point - x_i_minus_1) / (sqrt((breaking_point + x_i_minus_1) / 2)); // просто по-отдельности считаю слагаемые
			double second = (x_i - breaking_point) / (((breaking_point + x_i) / 2) + 1);
			return pow(((1 / h) * (first + second)), -1);
		}
	}
}

double fi_i(double h, double breaking_point, double x_i_minus_05, double x_i_plus_05, double x_i, int is_test_task) {
	if (is_test_task) { // тестовая задача
		if (x_i_plus_05 <= breaking_point) { // отрезок левее точки разрыва
			return 1;
		}
		if (x_i_minus_05 >= breaking_point) { // отрезок правее точки разрыва 
			return 2.5;
		}
		if (x_i_minus_05 <= breaking_point && breaking_point <= x_i_plus_05) { // точка разрыва принадлежит отрезку
			return (1/h)*(breaking_point-x_i_minus_05)+(2.5/h)*(x_i_plus_05-breaking_point);
		}
	}
	else { // основная задача
		if (x_i_plus_05 <= breaking_point) { // отрезок левее точки разрыва
			return 1;
		}
		if (x_i_minus_05 >= breaking_point) { // отрезок правее точки разрыва 
			return sqrt(x_i) + 2;
		}
		if (x_i_minus_05 <= breaking_point && breaking_point <= x_i_plus_05) { // точка разрыва принадлежит отрезку
			double first = (1 / h) * (breaking_point - x_i_minus_05); // просто по-отдельности считаю слагаемые
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
	double di = d_i(h, breaking_point, (i - 0.5) * h, (i + 0.5) * h, i * h, is_test_task);
	int new_i = i + 1;
	double ai_plus_1 = a_i(h, breaking_point, (new_i - 0.5) * h, (new_i - 1) * h, new_i * h, is_test_task);
	return ((1 / pow(h, 2)) * (ai + ai_plus_1) + di);
}

vector<double> sweepMethod(double h, int n, double mu1, double mu2, double breaking_point, int is_test_task) {
	vector<double> result(n+1); // вектор для записи результата
	result[0]=mu1; // левое граничное условие
	result[n] = mu2; //правое граничное условие
	vector<double> alpha(n), beta(n); //векторы для хранения коэффициентов альфа и бета
	alpha[0] = 0;
	beta[0] = 0;

	//прямой ход прогонки
	for (int i = 1; i < n; i++) {//у альфа и бета индексы сдвинуты на 1
		double Ai = A_i(i, h, breaking_point, is_test_task); // коэффициент Ai из метода прогонки
		double Bi = B_i(i, h, breaking_point, is_test_task); // коэффициент Вi из метода прогонки
		double Ci = C_i(i, h, breaking_point, is_test_task); // коэффициент Сi из метода прогонки
		double fii = fi_i(h, breaking_point, (i - 0.5) * h, (i+0.5)*h,i*h, is_test_task); // коэффициент fi_i из разностной схемы
		alpha[i] = Bi / (Ci - Ai * alpha[i - 1]);
		beta[i] = (fii + Ai * beta[i - 1]) / (Ci - Ai * alpha[i - 1]);
	}

	//обратный ход прогонки
	for (int i = n - 1; i > 0; i--) {
		result[i] = alpha[i] * result[i + 1] + beta[i];
	}
	return result;
}

vector<vector<double>> differenceScheme(double h, int n, double mu1, double mu2, double breaking_point, int is_test_task) {
	vector<vector<double>> result; //итоговая "таблица"
	vector<double> v_with_usual_h = sweepMethod( h, n, mu1, mu2, breaking_point, is_test_task); //решение разностной схемы с обычным шагом
	if (!is_test_task) {
		vector<double> v_with_half_h = sweepMethod(h / 2, n * 2, mu1, mu2, breaking_point, is_test_task); 
																								//решение разностной схемы с половинным шагом
		vector<double>v_minus_v_half_h(n + 1); // модуль разности решений разностной схемы с обычным шагом и с половинным шагом
		for (int i = 0; i < n + 1; i++) {
			cout << "x[i]h = " << v_with_usual_h[i] << " x[i]2h = " << v_with_half_h[i] << '\n';
			v_minus_v_half_h[i] = abs(v_with_usual_h[i] - v_with_half_h[2*i]);
			result.push_back({ i * h,v_with_usual_h[i],v_with_half_h[2 * i],v_minus_v_half_h[i] });
		}
	}
	else {
		vector<double>u_x(n + 1); //аналитическое решение
		vector<double>u_x_minus_v(n + 1); // модуль разности аналитического решения и решения с обычным шагом
		for (int i = 0; i < n + 1; i++) {
			double xi = i * h;
			u_x[i] = u_for_test(xi);
			u_x_minus_v[i] = abs(u_x[i] - v_with_usual_h[i]);
			result.push_back({ i * h,v_with_usual_h[i],u_x[i],u_x_minus_v[i] });
		}
	}
	return result;
}