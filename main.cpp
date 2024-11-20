#include"NamesOfFunctions.h"

void main() {
	setlocale(LC_ALL, "RUS");
	double left_boarder = 0, right_boarder = 1;
	double h, n;
	double breaking_point=0.25, mu1=0,mu2=1;
	vector<vector<double>> result;
	int is_test_task = 0;
	//cout << "Введите левую и правую границы: \n";
	//cin >> left_boarder >> right_boarder;
	cout << "\nКакую задачу вы хотите решить? Если тестовую - введите 0, иначе - 1: \n";
	cin >> is_test_task;
	is_test_task = (1-is_test_task);
	cout << "\nВведите количество узлов: \n";
	cin >> n;
	h = (right_boarder - left_boarder) / n;
	result = differenceScheme(h, n, mu1, mu2, breaking_point, is_test_task);
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
}