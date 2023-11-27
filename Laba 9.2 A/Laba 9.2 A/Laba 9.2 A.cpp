#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;

enum Spec {
	RI = 1, 
	KN,
	VP,
	PZ
};

struct Student {
	int id;
	string surname;
	int course;
	Spec spec;
	int physics;
	int math;
	int it;
};

void Create(Student* students, int N) {
    int spec;

    for (int i = 0; i < N; i++) {
        students[i].id = i + 1;
     
        cin.get(); 
        cin.sync();

     cout << "Прізвище: "; cin >> students[i].surname;
     cout << "Курс: "; cin >> students[i].course;
     cout << "Спеціальність (" <<
            "РІ: " << RI << ", " <<
            "КІ: " << KN << ", " <<
            "ВП: " << VP << ", " <<
            "ПЗ: " << PZ << "):" << endl;

        cin >> spec;
        students[i].spec = (Spec)spec;

        cout << "Фізика: "; cin >> students[i].physics;
        cout << "Математика: "; cin >> students[i].math;
        cout << "Інформатика: "; cin >> students[i].it;
        cout << endl;

    }
}

string getSpecStr(Spec s) {
    switch (s) {
    case RI:
        return "РІ";
    case KN:
        return "КН";
    case VP:
        return "ВП";
    case PZ:
        return "ПЗ";
    default:
        return "Невідома";
    }
}

void PrintHeader() {
    cout << "============================================================================"
        << endl;
    cout << "| №  | Прізвище | Спеціальність | Курс | Фізика | Математика | Інформатика |"
        << endl;
    cout << "============================================================================"
        << endl;
}

void Print(const Student* p, int N) {
    PrintHeader();

    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(2) << right << i + 1 << " ";
        cout
            << "| " << setw(8) << right << p[i].surname << " "
            << "| " << setw(14) << left << getSpecStr(p[i].spec)
            << "| " << setw(5) << left << p[i].course
            << "| " << setw(7) << right << p[i].physics
            << "| " << setw(11) << right << p[i].math
            << "| " << setw(12) << right << p[i].it << "|" << endl;
        cout << "----------------------------------------------------------------------------";
        cout << endl;
    }
    cout << endl;
}

void Sort(Student* s, const int N) {
    Student tmp;
    for (int i0 = 0; i0 < N - 1; i0++) {
        for (int i1 = 0; i1 < N - i0; i1++) {
            if ((s[i1].spec < s[i1 + 1].spec)
                || (s[i1].spec == s[i1 + 1].spec && s[i1].course < s[i1 + 1].course)
                || (s[i1].spec == s[i1 + 1].spec && s[i1].course == s[i1].course && s[i1].surname > s[i1 + 1].surname)) {
                tmp = s[i1];
                s[i1] = s[i1 + 1];
                s[i1 + 1] = tmp;
            }
        }
    }
}

int* IndexSort(Student* s, const int N){
    int* I = new int[N];
    for (int i = 0; i < N; i++)
        I[i] = i;

    int i, j, value;
    for (i = 1; i < N; i++){
        value = I[i];
        for (
            j = i - 1;j >= 0 &&
            ((s[I[j]].spec < s[value].spec)
            || (s[I[j]].spec == s[value].spec && s[I[j]].course < s[value].course)
            || (s[I[j]].spec == s[value].spec && s[I[j]].course == s[value].course && s[I[j]].surname < s[value].surname));
            j--
            ){
            I[j + 1] = I[j];
        }

        I[j + 1] = value;
    }
    return I;
}

void PrintIndexSorted(Student* p, int* I, const int N){

    cout << "============================================================================"
        << endl;
    cout << "| №  | Прізвище | Спеціальність | Курс | Фізика | Математика | Інформатика |"
        << endl;
    cout << "============================================================================"
        << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(2) << i + 1 << " ";
        cout << "| " << setw(8) << p[I[i]].surname << " ";
        cout << "| " << setw(14) << getSpecStr(p[I[i]].spec);
        cout << "| " << setw(5) << p[I[i]].course;
        cout << "| " << setw(7) << p[I[i]].physics;
        cout << "| " << setw(11) << p[I[i]].math;
        cout << "| " << setw(12) << p[I[i]].it << "|" << endl;
        cout << "----------------------------------------------------------------------------";
        cout << endl;
    }
    cout << endl;
}

int BinSearch(Student* p, const int N, const int course, const Spec spec, const string surname)
{
    int L = 0, R = N - 1, m;
    do {
        m = (L + R) / 2;
        if (p[m].surname == surname && p[m].course == course && p[m].spec == spec)
            return m;
        if ((p[m].surname < surname)
            || (p[m].surname == surname && p[m].spec < spec)
            || (p[m].surname == surname && p[m].spec == spec) && p[m].course < course)
        {
            L = m + 1;
        }
        else
        {
            R = m - 1;
        }
    } while (L <= R);

    return -1;
}

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Vvedit N: "; cin >> N;
    cout << endl;

    int menu;
    int find;
    string surname;
    unsigned course;
    int ispec;

    Spec spec{};

    Student* a = new Student[N];

    Create(a, N);
    Print(a, N);

    do {
        cout << endl << endl;
        cout << "Виберіть дію: " << endl;
        cout << " [1] - Вивід даних на екран" << endl;
        cout << " [2] - Фізичне впорядкування масиву" << endl;
        cout << " [3] - Індексне впорядкування масиву" << endl;
        cout << " [4] - Бінарний пошук" << endl;
        cout << " [0] - Вихід з програми" << endl;
        cout << " Введіть значення команди: "; cin >> menu;
        cout << endl << endl;
        switch (menu) {
        case 1:
            Print(a, N);
            break;
        case 2:
            Sort(a, N);
            break;
        case 3:
            IndexSort(a, N);
            PrintIndexSorted(a, IndexSort(a, N), N);
            break;
        case 4:
            cin.get(); 
            cin.sync();
            cout << "Введіть прізвище студента: "; cin >> surname;
            cout << "Введіть спеціальність (1 - RI, 2 - KN, 3 - VP, 4 - PZ): ";
            cin >> ispec;
            spec = (Spec)ispec;
            cin.get();
            cin.sync();
            cout << "Введіть курс: "; cin >> course;

            find = BinSearch(a, N, course, spec, surname);
            if (find != -1) {
                cout << "Студент " << surname << " навчається на спеціальності: " << spec << endl;
            }
            else
                cout << "Студент " << surname << " не навчається на спеціальності: " << spec << endl;
            break;
        case 0:
            break;

        }
    } while (menu != 0);

    delete[] a;
	return 0;
}