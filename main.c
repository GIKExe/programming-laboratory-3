#include <math.h>
#include <stdlib.h>
#include <stdio.h>

// Функция для вычисления значения кривой в точке x
double f(double x) {
  return 2 * pow(x, 3) + pow(x, 2) + 1;
}

// Функция вычисления интеграла методом Симпсона
double integral(double a, double b, int n) {
  double h = (b - a) / n;
  double sum = f(a) + f(b);

  for (int i = 1; i < n; i++) {
    double x = a + i * h;
    if (i % 2 == 0)
      sum += 2 * f(x);
    else
      sum += 4 * f(x);
  }
  return sum * h / 3;
}

// Процедура для оценки погрешности методом Рунге
void estimate_error(double a, double b, int n, double* error) {
  double integral_n = integral(a, b, n);
  double integral_2n = integral(a, b, n * 2);
  *error = fabs(integral_2n - integral_n) / 15;
}

void clear_buffer() {
	while (getchar() != '\n');
}

int main() {
  double a = 0, b = 0, result, error;
  int n = 0, choice;
  int limits_set = 0, n_set = 0, integral_set = 0, error_set = 0;

  do {
		printf("\nМеню:");
		printf("\n1. Ввести пределы интегрирования (a, b)");
		if (limits_set) printf(" (%f, %f)", a, b);
    printf("\n2. Ввести количество разбиений n");
    if (n_set) printf(" (%d)", n);
    if (limits_set && n_set) {
      printf("\n3. Вычислить интеграл");
      if (integral_set) printf(" (%.6f)", result);
      printf("\n4. Оценить погрешность");
      if (error_set) printf(" (%.6f)", error);
    } else {
      printf("\n3. [Недоступно - введите данные]");
      printf("\n4. [Недоступно - введите данные]");
    }
		printf("\n5. Выход");
		printf("\nВыберите опцию: ");
    scanf("%d", &choice);
    system("cls");

    switch (choice) {
      case 1:
        printf("Введите пределы интегрирования (a b): ");
        if (scanf("%lf %lf", &a, &b) == 2) {
          limits_set = 1;
        } else {
          printf("Ошибка ввода!\n");
          clear_buffer();
        }
        break;

      case 2:
        printf("Введите количество разбиений n: ");
        if (scanf("%d", &n) == 1 && n > 0) {
          n_set = 1;
        } else {
          printf("Ошибка ввода! n должно быть положительным числом.\n");
          clear_buffer();
        }
        break;

      case 3:
        if (limits_set && n_set) {
          result = integral(a, b, n);
          integral_set = 1;
        } else printf("Сначала введите данные!\n");

        break;

      case 4:
        if (limits_set && n_set) {
          estimate_error(a, b, n, &error);
          error_set = 1;
          n *= 2; // Увеличиваем n для следующего вычисления
        } else printf("Сначала введите данные!\n");
        break;

      case 5:
        printf("Выход...\n");
        break;

      default:
        printf("Неверный ввод! Выберите пункт от 1 до 5.\n");
    }
  } while (choice != 5);

  return 0;
}