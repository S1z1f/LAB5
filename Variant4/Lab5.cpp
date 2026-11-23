#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <unordered_set>    // Подключение неупорядоченного множества std::unordered_set
using namespace std;
class Book {    //Объявление класса
    string author;  //ФИО
    string name;    //Название книги
    string publisger;   //Издательство
    int year;   //Год выпуска
    int pages;  //Количество страниц
public:
    Book() {    //Конструктор создаёт пустые поля
        author = ""; name = ""; publisger = ""; year = 0; pages = 0;
    }
    Book(string author, string name, string publisger, int year, int pages) {   //Конструктор с параметрами
        this->author = author; this->name = name; this->publisger = publisger; this->year = year; this->pages = pages;
        // Запись переданных значений в поля объекта
    }
    bool operator<(const Book& b) const {   // Перегрузка оператора "<"
        return author < b.author;   // Сравниваем книги по алфавиту по полю ФИО автора
    }
    string getKey() const { // Геттер, возвращающий ключевое поле (ФИО автора) для вычисления хеша
        return author;
    }
    bool operator ==(const Book & c) const{   // Перегрузка оператора "=="
        return author == c.author;      // Считаем книги одинаковыми, если совпадает ФИО автора
    }
    friend ostream& operator<<(ostream& out, const Book& b);    // Объявление дружественной функции для перегрузки оператора вывода
};
ostream& operator <<(ostream & out, const Book & b) {   // Реализация перегруженного оператора
    out<< "   Автор: " << b.author << "." << endl << "Название книги: " <<  b.name << "." << endl << "Издательство: " << b.publisger << "." << endl << "Год издания: " << b.year << "."<< endl << "Количество страниц: " << b.pages;
    //Записываем значения в файл
    return out;
}
struct BookHash {   // Структура для вычисления хеш-кода объекта Book
    size_t operator()(const Book& b) const {    // Перегрузка оператора вызова функции ()
        return hash<string>()(b.getKey());  // Вычисление стандартного хеша от ФИО автора
    }
};
int main() {
    ifstream fin("input.txt");  //Открываем файл со значениями
    ofstream fout("output.txt");    //Открываем файл для записи результатов
    int n;  //Количество книг
    fin >> n;   //Считаем количество книг из исходного файла
    fin.ignore(2, '\n');    // Очистка буфера от символа переноса строки после числа
    set<Book> s;   // Создание упорядоченного множества
    unordered_set<Book, BookHash> u;    // Создание хеш-множества
    for (int i=0; i < n; i++) {     //Перебираем данные из файла
        string author, name, publisger;
        int year, pages;
        getline(fin, author);   //Построчное чтение данных
        getline(fin, name);
        getline(fin, publisger);
        fin >> year >> pages;
        fin.ignore(2, '\n');
        Book b(author, name, publisger, year, pages);   // Создание объекта книги из прочитанных данных
        s.insert(b);    // Если объект с таким ключом уже есть, второй раз не добавляется
        u.insert(b);    //Если автор уже есть, дубликат также игнорируется
    }
    fout << "Чтение из файла. " << endl << "Количество объектов: " << n << endl << endl; // Вывод в файл исходного количества прочитанных записей
    fout << "Значения отсортированные по автору." << endl << "Количество уникальных элементов: " <<s.size()<< endl; // Вывод количества уникальных элементов, попавших в set
    for (const Book & b : s) fout << b << endl; // Поэлементный вывод содержимого set
    fout << endl << "Неупорядоченное множество." << endl << "Количество объектов: "<< u.size() << endl; // Вывод количества уникальных элементов в unordered_set
    for (const Book & b : u) fout << b << endl;     // Поэлементный вывод содержимого unordered_set
    return 0;
}
