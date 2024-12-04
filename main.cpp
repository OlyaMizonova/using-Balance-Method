#include"NamesOfFunctions.h"

void main() {
	setlocale(LC_ALL, "RUS");
	double left_boarder = 0, right_boarder = 1;
	double h;
	int n;
	double breaking_point=0.25, mu1=0,mu2 = 1;
	vector<vector<double>> result;
	int is_test_task = 0;
	double maxDiffX, maxDifference;
	cout << "\nКакую задачу вы хотите решить? Если тестовую - введите 0, иначе - 1: \n";
	cin >> is_test_task;
	is_test_task = (1-is_test_task);
	cout << "\nВведите количество узлов: \n";
	cin >> n;
	h = 1. / n;
	result = differenceScheme(n, mu1, mu2, breaking_point, is_test_task, &maxDifference,&maxDiffX);

	if (is_test_task) {
		cout << "i   xi   vi      ui      vi-ui\n";
	}
	else {
		cout << "i   xi   vi     v2i     vi-v2i\n";
	}
	for (int i = 0; i < n + 1; i++) {
		cout << i << "    ";
		for (int j = 0; j < result[i].size(); j++) {
			cout << result[i][j] << "    ";
		}
		cout << "\n";
	}

	cout << "\nдля вешения задачи использована равномерная сетка с числом разбиений n = " << n <<
		"\nзадача должна быть решена с заданной точностью e = 0,5*10^-6 \nзадача решена с точностью e2 = " << maxDifference <<
		"\nмаксимальное отклонение аналитического и численного решений наблюдается в точке x = " <<maxDiffX;
	cout << "\nВведите 5 разных значений n: \n";
	vector<int> ns(5);
	for (int i = 0; i < 5; i++) {
		cin >> ns[i];
	}
	if (is_test_task) {
		cout << "\nn     max|vi-ui|        e1i-1/e1i";
	}
	else {
		cout << "\nn     max|vi-v2i|        e2i-1/e2i";
	}
	double previousEps = 1;
	for (int i = 0; i < 5; i++) {
		double maxDiffXX, maxDifferencee;
		result = differenceScheme(ns[i], mu1, mu2, breaking_point, is_test_task, &maxDifferencee,&maxDiffXX);
		cout << "\n" << ns[i];
		cout << "     " << maxDifferencee << "       ";
		if (!i) {
			cout << 0 << "\n";
		}
		else {
			cout << previousEps / maxDifferencee << "\n";
		}
		previousEps = maxDifferencee;
	}
	ns = { 10,20,50,80,100,200,500,800,1000,2000,5000,8000,10000,20000,50000,80000,100000,200000,500000,800000,1000000 };
	cout << "n       max|vi-ui|         max|vi-v2i|        lg(n)      -lg(e1)       -lg(e2)\n";
	for (int i = 0; i < size(ns); i++) {
		double maxDiffXTest, maxDifferenceTest;
		double maxDiffXMain, maxDifferenceMain;
		vector<vector<double>>resultTest = differenceScheme(ns[i], mu1, mu2, breaking_point, 1, &maxDifferenceTest, &maxDiffXTest);
		vector<vector<double>>resultMain = differenceScheme(ns[i], mu1, mu2, breaking_point, 0, &maxDifferenceMain, &maxDiffXMain);
		cout << ns[i] << "        " << maxDifferenceTest << "         " << maxDifferenceMain<<"     " << log10(ns[i]) << "       "
			<< -log10(maxDifferenceTest) << "       " << -log10(maxDifferenceMain) << "\n";

	}
}