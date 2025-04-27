#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <string>

using namespace std;


class Shape {
public:
    virtual double area() const = 0;
    virtual ~Shape() {}
};

class Circle : public Shape {
    double radius;
public:
    Circle(double r) : radius(r) {
        if (r < 0) {
            throw invalid_argument("Ошибка: радиус не может быть отрицательным");
        }
    }
    double area() const override {
        return 3.14159 * radius * radius;
    }
};

class Rectangle : public Shape {
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {
        if (w < 0 || h < 0) {
            throw invalid_argument("Ошибка: стороны прямоугольника не могут быть отрицательными");
        }
    }
    double area() const override {
        return width * height;
    }
};


class Animal {
    string name;
public:
    Animal(const string& n) : name(n) {
        if (n.empty()) {
            throw invalid_argument("Ошибка: имя животного не может быть пустым");
        }
    }
    virtual string speak() const = 0;
    virtual ~Animal() {}
};

class Dog : public Animal {
public:
    Dog(const string& n) : Animal(n) {}
    string speak() const override {
        return "Гав!";
    }
};

class Cat : public Animal {
public:
    Cat(const string& n) : Animal(n) {}
    string speak() const override {
        return "Мяу!";
    }
};


class BankAccount {
protected:
    double balance;
public:
    BankAccount(double b) : balance(b) {}
    virtual void withdraw(double amount) {
        if (amount > balance) {
            throw runtime_error("Ошибка: недостаточно средств на счете");
        }
        balance -= amount;
    }
    virtual ~BankAccount() {}
};

class SavingsAccount : public BankAccount {
public:
    SavingsAccount(double b) : BankAccount(b) {}
    void withdraw(double amount) override {
        if (amount > balance - 100) { 
            throw runtime_error("Ошибка: нельзя снять средства, минимальный баланс 100");
        }
        balance -= amount;
    }
};

class CheckingAccount : public BankAccount {
public:
    CheckingAccount(double b) : BankAccount(b) {}
    void withdraw(double amount) override {
        if (amount > balance) {
            throw runtime_error("Ошибка: недостаточно средств на расчетном счете");
        }
        balance -= amount;
    }
};

class FileHandler {
public:
    virtual void open(const string& filename) = 0;
    virtual ~FileHandler() {}
};

class TextFileHandler : public FileHandler {
public:
    void open(const string& filename) override {
        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Ошибка: текстовый файл с таким именем не найден");
        }
        cout << "Текстовый файл " << filename << " успешно открыт" << endl;
    }
};

class BinaryFileHandler : public FileHandler {
public:
    void open(const string& filename) override {
        ifstream file(filename, ios::binary);
        if (!file.is_open()) {
            throw runtime_error("Ошибка: бинарный файл с таким именем не найден");
        }
        cout << "Бинарный файл " << filename << " успешно открыт" << endl;
    }
};

class DrawableShape {
public:
    virtual void draw() const = 0;
    virtual ~DrawableShape() {}
};

class Triangle : public DrawableShape {
    double a, b, c;
public:
    Triangle(double a1, double b1, double c1) : a(a1), b(b1), c(c1) {
        if (a <= 0 || b <= 0 || c <= 0 || a + b <= c || a + c <= b || b + c <= a) {
            throw invalid_argument("Ошибка: некорректные параметры треугольника");
        }
    }
    void draw() const override {
        cout << "Рисуем треугольник со сторонами " << a << ", " << b << ", " << c << endl;
    }
};

class Square : public DrawableShape {
    double side;
public:
    Square(double s) : side(s) {
        if (s <= 0) {
            throw invalid_argument("Ошибка: сторона квадрата должна быть положительной");
        }
    }
    void draw() const override {
        cout << "Рисуем квадрат со стороной " << side << endl;
    }
};


class Person {
protected:
    string name;
    int age;
public:
    Person(const string& n, int a) : name(n), age(a) {
        if (n.empty()) {
            throw invalid_argument("Ошибка: имя не может быть пустым");
        }
        if (a < 0 || a > 120) {
            throw invalid_argument("Ошибка: некорректный возраст");
        }
    }
    virtual void display() const {
        cout << "Имя: " << name << ", Возраст: " << age << endl;
    }
    virtual ~Person() {}
};

class Student : public Person {
    string university;
public:
    Student(const string& n, int a, const string& u) : Person(n, a), university(u) {}
    void display() const override {
        Person::display();
        cout << "Университет: " << university << endl;
    }
};

class Teacher : public Person {
    string subject;
public:
    Teacher(const string& n, int a, const string& s) : Person(n, a), subject(s) {}
    void display() const override {
        Person::display();
        cout << "Предмет: " << subject << endl;
    }
};


class Calculator {
public:
    virtual double calculate(double a, double b) const = 0;
    virtual ~Calculator() {}
};

class Addition : public Calculator {
public:
    double calculate(double a, double b) const override {
        return a + b;
    }
};

class Division : public Calculator {
public:
    double calculate(double a, double b) const override {
        if (b == 0) {
            throw runtime_error("Ошибка: деление на ноль");
        }
        return a / b;
    }
};


class Game {
public:
    virtual void start() = 0;
    virtual ~Game() {}
};

class Chess : public Game {
public:
    void start() override {
        cout << "Шахматная игра началась" << endl;
    }
};

class Tennis : public Game {
    int players;
public:
    Tennis(int p) : players(p) {
        if (p != 2 && p != 4) {
            throw invalid_argument("Ошибка: для тенниса нужно 2 или 4 игрока");
        }
    }
    void start() override {
        cout << "Теннисный матч начался с " << players << " игроками" << endl;
    }
};

class Document {
public:
    virtual void save(const string& filename) = 0;
    virtual ~Document() {}
};

class PDFDocument : public Document {
public:
    void save(const string& filename) override {
        if (filename.empty()) {
            throw runtime_error("Ошибка: имя файла не может быть пустым");
        }
        cout << "PDF документ сохранен как " << filename << endl;
    }
};

class WordDocument : public Document {
public:
    void save(const string& filename) override {
        if (filename.find(".docx") == string::npos) {
            throw runtime_error("Ошибка: файл должен иметь расширение .docx");
        }
        cout << "Word документ сохранен как " << filename << endl;
    }
};


class Matrix {
protected:
    int rows, cols;
public:
    Matrix(int r, int c) : rows(r), cols(c) {}
    virtual double getElement(int r, int c) const = 0;
    virtual ~Matrix() {}
};

class IntMatrix : public Matrix {
    vector<vector<int>> data;
public:
    IntMatrix(int r, int c) : Matrix(r, c), data(r, vector<int>(c)) {}
    double getElement(int r, int c) const override {
        if (r < 0 || r >= rows || c < 0 || c >= cols) {
            throw out_of_range("Ошибка: выход за пределы матрицы");
        }
        return data[r][c];
    }
};

class FloatMatrix : public Matrix {
    vector<vector<float>> data;
public:
    FloatMatrix(int r, int c) : Matrix(r, c), data(r, vector<float>(c)) {}
    double getElement(int r, int c) const override {
        if (r < 0 || r >= rows || c < 0 || c >= cols) {
            throw out_of_range("Ошибка: выход за пределы матрицы");
        }
        return data[r][c];
    }
};


class Vehicle {
protected:
    double fuel;
public:
    Vehicle(double f) : fuel(f) {
        if (f < 0) {
            throw invalid_argument("Ошибка: количество топлива не может быть отрицательным");
        }
    }
    virtual double fuelEfficiency() const = 0;
    virtual ~Vehicle() {}
};

class Car : public Vehicle {
    double mileage;
public:
    Car(double f, double m) : Vehicle(f), mileage(m) {
        if (m < 0) {
            throw invalid_argument("Ошибка: пробег не может быть отрицательным");
        }
    }
    double fuelEfficiency() const override {
        if (fuel == 0) return 0;
        return mileage / fuel;
    }
};

class Truck : public Vehicle {
    double load;
public:
    Truck(double f, double l) : Vehicle(f), load(l) {
        if (l < 0) {
            throw invalid_argument("Ошибка: груз не может быть отрицательным");
        }
    }
    double fuelEfficiency() const override {
        if (fuel == 0) return 0;
        return (load * 0.1) / fuel; 
    }
};


class User {
protected:
    string username;
    string password;
public:
    User(const string& u, const string& p) : username(u), password(p) {}
    virtual void login(const string& p) const {
        if (p != password) {
            throw runtime_error("Ошибка: неверный пароль");
        }
        cout << "Пользователь " << username << " вошел в систему" << endl;
    }
    virtual ~User() {}
};

class AdminUser : public User {
public:
    AdminUser(const string& u, const string& p) : User(u, p) {}
    void login(const string& p) const override {
        User::login(p);
        cout << "Доступ администратора предоставлен" << endl;
    }
};

class RegularUser : public User {
public:
    RegularUser(const string& u, const string& p) : User(u, p) {}
    void login(const string& p) const override {
        User::login(p);
        cout << "Доступ обычного пользователя предоставлен" << endl;
    }
};


class ScalableShape {
public:
    virtual void scale(double factor) = 0;
    virtual ~ScalableShape() {}
};

class ScalableCircle : public ScalableShape {
    double radius;
public:
    ScalableCircle(double r) : radius(r) {
        if (r <= 0) {
            throw invalid_argument("Ошибка: радиус должен быть положительным");
        }
    }
    void scale(double factor) override {
        if (factor <= 0) {
            throw invalid_argument("Ошибка: коэффициент масштабирования должен быть положительным");
        }
        radius *= factor;
        cout << "Круг масштабирован. Новый радиус: " << radius << endl;
    }
};

class ScalableSquare : public ScalableShape {
    double side;
public:
    ScalableSquare(double s) : side(s) {
        if (s <= 0) {
            throw invalid_argument("Ошибка: сторона квадрата должна быть положительной");
        }
    }
    void scale(double factor) override {
        if (factor <= 0) {
            throw invalid_argument("Ошибка: коэффициент масштабирования должен быть положительным");
        }
        side *= factor;
        cout << "Квадрат масштабирован. Новая сторона: " << side << endl;
    }
};


class Library {
protected:
    vector<string> availableBooks;
public:
    Library(const vector<string>& books) : availableBooks(books) {}
    virtual void borrowBook(const string& book) {
        auto it = find(availableBooks.begin(), availableBooks.end(), book);
        if (it == availableBooks.end()) {
            throw runtime_error("Ошибка: книга '" + book + "' недоступна");
        }
        availableBooks.erase(it);
        cout << "Книга '" << book << "' успешно взята" << endl;
    }
    virtual ~Library() {}
};

class FictionLibrary : public Library {
public:
    FictionLibrary(const vector<string>& books) : Library(books) {}
    void borrowBook(const string& book) override {
        Library::borrowBook(book);
        cout << "Это художественная литература" << endl;
    }
};

class NonFictionLibrary : public Library {
public:
    NonFictionLibrary(const vector<string>& books) : Library(books) {}
    void borrowBook(const string& book) override {
        Library::borrowBook(book);
        cout << "Это научная литература" << endl;
    }
};


class Order {
protected:
    string orderId;
public:
    Order(const string& id) : orderId(id) {
        if (id.empty()) {
            throw invalid_argument("Ошибка: ID заказа не может быть пустым");
        }
    }
    virtual void process() = 0;
    virtual ~Order() {}
};

class OnlineOrder : public Order {
    string address;
public:
    OnlineOrder(const string& id, const string& addr) : Order(id), address(addr) {
        if (addr.empty()) {
            throw invalid_argument("Ошибка: адрес доставки не может быть пустым");
        }
    }
    void process() override {
        cout << "Онлайн заказ #" << orderId << " обработан. Адрес доставки: " << address << endl;
    }
};

class InStoreOrder : public Order {
public:
    InStoreOrder(const string& id) : Order(id) {}
    void process() override {
        cout << "Заказ в магазине #" << orderId << " обработан и готов к выдаче" << endl;
    }
};


class RotatableShape {
public:
    virtual void rotate(double angle) = 0;
    virtual ~RotatableShape() {}
};

class RotatableTriangle : public RotatableShape {
public:
    void rotate(double angle) override {
        if (angle < 0 || angle > 360) {
            throw invalid_argument("Ошибка: угол вращения должен быть между 0 и 360 градусами");
        }
        cout << "Треугольник повернут на " << angle << " градусов" << endl;
    }
};

class RotatableRectangle : public RotatableShape {
public:
    void rotate(double angle) override {
        if (angle < 0 || angle > 360) {
            throw invalid_argument("Ошибка: угол вращения должен быть между 0 и 360 градусами");
        }
        cout << "Прямоугольник повернут на " << angle << " градусов" << endl;
    }
};


class Payment {
protected:
    double amount;
public:
    Payment(double a) : amount(a) {
        if (a <= 0) {
            throw invalid_argument("Ошибка: сумма платежа должна быть положительной");
        }
    }
    virtual void processPayment() = 0;
    virtual ~Payment() {}
};

class CreditCardPayment : public Payment {
    string cardNumber;
public:
    CreditCardPayment(double a, const string& num) : Payment(a), cardNumber(num) {
        if (num.length() != 16) {
            throw invalid_argument("Ошибка: номер карты должен содержать 16 цифр");
        }
    }
    void processPayment() override {
        cout << "Оплата кредитной картой на сумму " << amount << " руб. успешно обработана" << endl;
    }
};

class PayPalPayment : public Payment {
    string email;
public:
    PayPalPayment(double a, const string& e) : Payment(a), email(e) {
        if (e.find('@') == string::npos) {
            throw invalid_argument("Ошибка: некорректный email адрес");
        }
    }
    void processPayment() override {
        cout << "PayPal оплата на сумму " << amount << " руб. для " << email << " успешно обработана" << endl;
    }
};


class ExceptionHandler {
public:
    virtual void handle(const exception& e) = 0;
    virtual ~ExceptionHandler() {}
};

class FileExceptionHandler : public ExceptionHandler {
public:
    void handle(const exception& e) override {
        cerr << "Обработка файловой ошибки: " << e.what() << endl;
    }
};

class NetworkExceptionHandler : public ExceptionHandler {
public:
    void handle(const exception& e) override {
        cerr << "Обработка сетевой ошибки: " << e.what() << endl;
    }
};


class Course {
protected:
    int maxStudents;
    int currentStudents;
public:
    Course(int max) : maxStudents(max), currentStudents(0) {
        if (max <= 0) {
            throw invalid_argument("Ошибка: максимальное количество студентов должно быть положительным");
        }
    }
    virtual void enroll() {
        if (currentStudents >= maxStudents) {
            throw runtime_error("Ошибка: курс переполнен");
        }
        currentStudents++;
        cout << "Студент зачислен. Текущее количество: " << currentStudents << endl;
    }
    virtual ~Course() {}
};

class OnlineCourse : public Course {
public:
    OnlineCourse(int max) : Course(max) {}
    void enroll() override {
        Course::enroll();
        cout << "Это онлайн курс. Ссылка на платформу отправлена" << endl;
    }
};

class OfflineCourse : public Course {
    string location;
public:
    OfflineCourse(int max, const string& loc) : Course(max), location(loc) {
        if (loc.empty()) {
            throw invalid_argument("Ошибка: местоположение не может быть пустым");
        }
    }
    void enroll() override {
        Course::enroll();
        cout << "Это оффлайн курс. Местоположение: " << location << endl;
    }
};


class ShoppingCart {
protected:
    vector<string> items;
public:
    virtual void checkout() {
        if (items.empty()) {
            throw runtime_error("Ошибка: корзина пуста");
        }
        cout << "Оформление заказа. Количество товаров: " << items.size() << endl;
    }
    virtual ~ShoppingCart() {}
};

class RegularCart : public ShoppingCart {
public:
    void checkout() override {
        ShoppingCart::checkout();
        cout << "Обычная корзина. Скидки не применяются." << endl;
    }
};

class DiscountedCart : public ShoppingCart {
    double discount;
public:
    DiscountedCart(double d) : discount(d) {
        if (d <= 0 || d >= 1) {
            throw invalid_argument("Ошибка: скидка должна быть между 0 и 1");
        }
    }
    void checkout() override {
        ShoppingCart::checkout();
        cout << "Корзина со скидкой " << (discount * 100) << "%" << endl;
    }
};

class Shape1 {
public:
    virtual void translate(double dx, double dy) = 0;
    virtual ~Shape1() {}
};

class Circle1 : public Shape1 {
    double x, y, radius;
public:
    Circle1(double x, double y, double r) : x(x), y(y), radius(r) {
        if (r <= 0) throw invalid_argument("Ошибка: радиус должен быть положительным");
    }
    void translate(double dx, double dy) override {
        if (x + dx < 0 || y + dy < 0) {
            throw invalid_argument("Ошибка: нельзя переместить круг в отрицательные координаты");
        }
        x += dx;
        y += dy;
        cout << "Круг перемещен в (" << x << ", " << y << ")" << endl;
    }
};

class Rectangle1 : public Shape1 {
    double x, y, width, height;
public:
    Rectangle1(double x, double y, double w, double h) : x(x), y(y), width(w), height(h) {
        if (w <= 0 || h <= 0) throw invalid_argument("Ошибка: ширина и высота должны быть положительными");
    }
    void translate(double dx, double dy) override {
        if (x + dx < 0 || y + dy < 0) {
            throw invalid_argument("Ошибка: нельзя переместить прямоугольник в отрицательные координаты");
        }
        x += dx;
        y += dy;
        cout << "Прямоугольник перемещен в (" << x << ", " << y << ")" << endl;
    }
};


class Database {
public:
    virtual void connect(const string& connectionString) = 0;
    virtual ~Database() {}
};

class MySQLDatabase : public Database {
public:
    void connect(const string& connectionString) override {
        if (connectionString.empty()) {
            throw runtime_error("Ошибка: строка подключения не может быть пустой");
        }
        if (connectionString.find("mysql://") == string::npos) {
            throw runtime_error("Ошибка: неверный формат строки подключения MySQL");
        }
        cout << "Успешное подключение к MySQL: " << connectionString << endl;
    }
};

class SQLiteDatabase : public Database {
public:
    void connect(const string& connectionString) override {
        if (connectionString.empty()) {
            throw runtime_error("Ошибка: строка подключения не может быть пустой");
        }
        if (connectionString.find(".db") == string::npos) {
            throw runtime_error("Ошибка: неверный формат файла SQLite");
        }
        cout << "Успешное подключение к SQLite: " << connectionString << endl;
    }
};


class Task {
protected:
    bool initialized = false;
public:
    virtual void execute() = 0;
    virtual ~Task() {}
};

class PrintTask : public Task {
    string message;
public:
    PrintTask(const string& msg) : message(msg) {
        if (msg.empty()) throw invalid_argument("Ошибка: сообщение не может быть пустым");
        initialized = true;
    }
    void execute() override {
        if (!initialized) throw runtime_error("Ошибка: задача печати не инициализирована");
        cout << "Печать: " << message << endl;
    }
};

class EmailTask : public Task {
    string recipient, subject, body;
public:
    EmailTask(const string& rec, const string& subj, const string& b) :
        recipient(rec), subject(subj), body(b) {
        if (rec.empty() || subj.empty()) throw invalid_argument("Ошибка: получатель и тема обязательны");
        initialized = true;
    }
    void execute() override {
        if (!initialized) throw runtime_error("Ошибка: задача email не инициализирована");
        cout << "Отправка email " << subject << " для " << recipient << endl;
    }
};


class PerimeterShape {
public:
    virtual double getPerimeter() const = 0;
    virtual ~PerimeterShape() {}
};

class Triangle1 : public PerimeterShape {
    double a, b, c;
public:
    Triangle1(double a, double b, double c) : a(a), b(b), c(c) {
        if (a <= 0 || b <= 0 || c <= 0) throw invalid_argument("Ошибка: стороны должны быть положительными");
        if (a + b <= c || a + c <= b || b + c <= a) throw invalid_argument("Ошибка: недопустимые стороны треугольника");
    }
    double getPerimeter() const override {
        return a + b + c;
    }
};

class Square1 : public PerimeterShape {
    double side;
public:
    Square1(double s) : side(s) {
        if (s <= 0) throw invalid_argument("Ошибка: сторона должна быть положительной");
    }
    double getPerimeter() const override {
        return 4 * side;
    }
};


class WeatherService {
public:
    virtual string getForecast() const = 0;
    virtual ~WeatherService() {}
};

class LocalWeatherService : public WeatherService {
public:
    string getForecast() const override {
        
        bool dataAvailable = rand() % 2;
        if (!dataAvailable) throw runtime_error("Ошибка: локальные данные погоды недоступны");
        return "Местный прогноз: солнечно, 25°C";
    }
};

class RemoteWeatherService : public WeatherService {
public:
    string getForecast() const override {
       
        bool serviceAvailable = rand() % 2;
        if (!serviceAvailable) throw runtime_error("Ошибка: удаленный сервис погоды недоступен");
        return "Удаленный прогноз: облачно, 20°C";
    }
};


class Transaction {
public:
    virtual void commit() = 0;
    virtual ~Transaction() {}
};

class BankTransaction : public Transaction {
    string accountFrom, accountTo;
    double amount;
public:
    BankTransaction(const string& from, const string& to, double amt) :
        accountFrom(from), accountTo(to), amount(amt) {
        if (from.empty() || to.empty()) throw invalid_argument("Ошибка: счета не могут быть пустыми");
        if (amt <= 0) throw invalid_argument("Ошибка: сумма должна быть положительной");
    }
    void commit() override {
       
        bool success = rand() % 2;
        if (!success) throw runtime_error("Ошибка: банковская транзакция не выполнена");
        cout << "Банковская транзакция " << amount << " от " << accountFrom << " к " << accountTo << endl;
    }
};

class CryptoTransaction : public Transaction {
    string walletFrom, walletTo;
    double amount;
public:
    CryptoTransaction(const string& from, const string& to, double amt) :
        walletFrom(from), walletTo(to), amount(amt) {
        if (from.length() < 20 || to.length() < 20) throw invalid_argument("Ошибка: неверный формат криптокошелька");
        if (amt <= 0) throw invalid_argument("Ошибка: сумма должна быть положительной");
    }
    void commit() override {
        
        bool success = rand() % 2;
        if (!success) throw runtime_error("Ошибка: криптотранзакция не выполнена");
        cout << "Криптотранзакция " << amount << " от " << walletFrom.substr(0, 5) << "... к " << walletTo.substr(0, 5) << "..." << endl;
    }
};


class Notification1 {
public:
    virtual void send(const string& recipient, const string& message) = 0;
    virtual ~Notification1() {}
};

class EmailNotification1 : public Notification1 {
public:
    void send(const string& recipient, const string& message) override {
        if (recipient.empty() || recipient.find('@') == string::npos) {
            throw invalid_argument("Ошибка: неверный email адрес");
        }
        if (message.empty()) {
            throw invalid_argument("Ошибка: сообщение не может быть пустым");
        }
        cout << "Email отправлен на " << recipient << ": " << message.substr(0, 20) << "..." << endl;
    }
};

class SMSNotification1 : public Notification1 {
public:
    void send(const string& recipient, const string& message) override {
        if (recipient.empty() || recipient.length() < 10) {
            throw invalid_argument("Ошибка: неверный номер телефона");
        }
        if (message.empty()) {
            throw invalid_argument("Ошибка: сообщение не может быть пустым");
        }
        cout << "SMS отправлено на " << recipient << ": " << message.substr(0, 20) << "..." << endl;
    }
};


class BoundingBoxShape {
public:
    virtual void getBoundingBox(double& x1, double& y1, double& x2, double& y2) const = 0;
    virtual ~BoundingBoxShape() {}
};

class BoundingCircle : public BoundingBoxShape {
    double x, y, radius;
public:
    BoundingCircle(double x, double y, double r) : x(x), y(y), radius(r) {
        if (r <= 0) throw invalid_argument("Ошибка: радиус должен быть положительным");
    }
    void getBoundingBox(double& x1, double& y1, double& x2, double& y2) const override {
        x1 = x - radius;
        y1 = y - radius;
        x2 = x + radius;
        y2 = y + radius;
        cout << "Ограничивающий прямоугольник круга: (" << x1 << "," << y1 << ") (" << x2 << "," << y2 << ")" << endl;
    }
};

class Polygon : public BoundingBoxShape {
    vector<pair<double, double>> points;
public:
    Polygon(const vector<pair<double, double>>& pts) : points(pts) {
        if (pts.size() < 3) throw invalid_argument("Ошибка: полигон должен иметь минимум 3 точки");
    }
    void getBoundingBox(double& x1, double& y1, double& x2, double& y2) const override {
        if (points.empty()) throw runtime_error("Ошибка: полигон не имеет точек");
        x1 = x2 = points[0].first;
        y1 = y2 = points[0].second;

        for (const auto& p : points) {
            if (p.first < x1) x1 = p.first;
            if (p.first > x2) x2 = p.first;
            if (p.second < y1) y1 = p.second;
            if (p.second > y2) y2 = p.second;
        }
        cout << "Ограничивающий прямоугольник полигона: (" << x1 << "," << y1 << ") (" << x2 << "," << y2 << ")" << endl;
    }
};


class UserProfile {
protected:
    string username;
    int age;
public:
    UserProfile(const string& name, int age) : username(name), age(age) {
        if (name.empty()) throw invalid_argument("Ошибка: имя пользователя не может быть пустым");
        if (age < 0 || age > 120) throw invalid_argument("Ошибка: некорректный возраст");
    }
    virtual void updateProfile(const string& newName, int newAge) {
        if (newName.empty()) throw invalid_argument("Ошибка: имя пользователя не может быть пустым");
        if (newAge < 0 || newAge > 120) throw invalid_argument("Ошибка: некорректный возраст");
        username = newName;
        age = newAge;
        cout << "Профиль обновлен: " << username << ", " << age << " лет" << endl;
    }
    virtual ~UserProfile() {}
};

class AdminProfile : public UserProfile {
    int accessLevel;
public:
    AdminProfile(const string& name, int age, int level) : UserProfile(name, age), accessLevel(level) {
        if (level < 1 || level > 10) throw invalid_argument("Ошибка: уровень доступа должен быть 1-10");
    }
    void updateProfile(const string& newName, int newAge) override {
        UserProfile::updateProfile(newName, newAge);
        cout << "Уровень доступа администратора: " << accessLevel << endl;
    }
};

class GuestProfile : public UserProfile {
public:
    GuestProfile(const string& name, int age) : UserProfile(name, age) {}
    void updateProfile(const string& newName, int newAge) override {
        UserProfile::updateProfile(newName, newAge);
        cout << "Гостевой профиль имеет ограниченные права" << endl;
    }
};


class PaymentProcessor {
public:
    virtual void processPayment(double amount) = 0;
    virtual ~PaymentProcessor() {}
};

class CreditCardProcessor : public PaymentProcessor {
    string cardNumber;
    double balance;
public:
    CreditCardProcessor(const string& num, double bal) : cardNumber(num), balance(bal) {
        if (num.length() != 16) throw invalid_argument("Ошибка: номер карты должен содержать 16 цифр");
        if (bal < 0) throw invalid_argument("Ошибка: баланс не может быть отрицательным");
    }
    void processPayment(double amount) override {
        if (amount <= 0) throw invalid_argument("Ошибка: сумма платежа должна быть положительной");
        if (amount > balance) throw runtime_error("Ошибка: недостаточно средств на кредитной карте");
        balance -= amount;
        cout << "Кредитная карта: оплачено " << amount << ", остаток: " << balance << endl;
    }
};

class DebitCardProcessor : public PaymentProcessor {
    string cardNumber;
    double balance;
public:
    DebitCardProcessor(const string& num, double bal) : cardNumber(num), balance(bal) {
        if (num.length() != 16) throw invalid_argument("Ошибка: номер карты должен содержать 16 цифр");
        if (bal < 0) throw invalid_argument("Ошибка: баланс не может быть отрицательным");
    }
    void processPayment(double amount) override {
        if (amount <= 0) throw invalid_argument("Ошибка: сумма платежа должна быть положительной");
        if (amount > balance) throw runtime_error("Ошибка: недостаточно средств на дебетовой карте");
        balance -= amount;
        cout << "Дебетовая карта: оплачено " << amount << ", остаток: " << balance << endl;
    }
};

class Shape4 {
public:
    virtual void reflect(char axis) = 0;
    virtual ~Shape4() {}
};

class Circle4 : public Shape4 {
    double x, y, radius;
public:
    Circle4(double x, double y, double r) : x(x), y(y), radius(r) {
        if (r <= 0) throw invalid_argument("Радиус должен быть положительным");
    }
    void reflect(char axis) override {
        if (axis != 'x' && axis != 'y')
            throw invalid_argument("Недопустимая ось отражения. Используйте 'x' или 'y'");

        if (axis == 'x') y = -y;
        else x = -x;
        cout << "Круг отражен по оси " << axis << ". Новые координаты: (" << x << "," << y << ")" << endl;
    }
};

class Rectangle4 : public Shape4 {
    double x1, y1, x2, y2;
public:
    Rectangle4(double x1, double y1, double x2, double y2) : x1(x1), y1(y1), x2(x2), y2(y2) {
        if (x1 == x2 || y1 == y2) throw invalid_argument("Прямоугольник не может быть вырожденным");
    }
    void reflect(char axis) override {
        if (axis != 'x' && axis != 'y')
            throw invalid_argument("Недопустимая ось отражения. Используйте 'x' или 'y'");

        if (axis == 'x') { y1 = -y1; y2 = -y2; }
        else { x1 = -x1; x2 = -x2; }
        cout << "Прямоугольник отражен по оси " << axis << ". Новые координаты: ("
            << x1 << "," << y1 << "), (" << x2 << "," << y2 << ")" << endl;
    }
};


class FileReader {
public:
    virtual void read(const string& filename) = 0;
    virtual ~FileReader() {}
};

class TextFileReader : public FileReader {
public:
    void read(const string& filename) override {
        if (filename.empty()) throw invalid_argument("Имя файла не может быть пустым");
        if (filename.find(".txt") == string::npos)
            throw runtime_error("Файл " + filename + " не является текстовым (.txt)");

        cout << "Текстовый файл " << filename << " успешно прочитан" << endl;
    }
};

class BinaryFileReader : public FileReader {
public:
    void read(const string& filename) override {
        if (filename.empty()) throw invalid_argument("Имя файла не может быть пустым");
        if (filename.find(".bin") == string::npos)
            throw runtime_error("Файл " + filename + " не является бинарным (.bin)");

        cout << "Бинарный файл " << filename << " успешно прочитан" << endl;
    }
};


class AreaShape {
public:
    virtual double getArea() const = 0;
    virtual ~AreaShape() {}
};

class Ellipse : public AreaShape {
    double a, b;
public:
    Ellipse(double a, double b) : a(a), b(b) {
        if (a <= 0 || b <= 0) throw invalid_argument("Оси эллипса должны быть положительными");
    }
    double getArea() const override {
        return 3.14159 * a * b;
    }
};

class Square4 : public AreaShape {
    double side;
public:
    Square4(double s) : side(s) {
        if (s <= 0) throw invalid_argument("Сторона квадрата должна быть положительной");
    }
    double getArea() const override {
        return side * side;
    }
};


class EmailService {
public:
    virtual void sendEmail(const string& to, const string& subject, const string& body) = 0;
    virtual ~EmailService() {}
};

class SMTPService : public EmailService {
public:
    void sendEmail(const string& to, const string& subject, const string& body) override {
        if (to.empty() || to.find('@') == string::npos)
            throw invalid_argument("Некорректный email адрес получателя");
        if (subject.empty()) throw invalid_argument("Тема письма не может быть пустой");

        cout << "SMTP: Письмо '" << subject << "' отправлено на " << to << endl;
    }
};

class APIService : public EmailService {
public:
    void sendEmail(const string& to, const string& subject, const string& body) override {
        if (to.empty() || to.find('@') == string::npos)
            throw invalid_argument("Некорректный email адрес получателя");
        if (body.empty()) throw invalid_argument("Тело письма не может быть пустым");

        cout << "API: Письмо '" << subject << "' отправлено на " << to << endl;
    }
};


class Game4 {
protected:
    bool isActive = false;
public:
    virtual void endGame() = 0;
    virtual ~Game4() {}
};

class ChessGame4 : public Game4 {
public:
    void endGame() override {
        if (!isActive) throw runtime_error("Нельзя завершить неактивную шахматную игру");
        cout << "Шахматная игра завершена" << endl;
        isActive = false;
    }
};

class FootballGame4 : public Game4 {
public:
    void endGame() override {
        if (!isActive) throw runtime_error("Нельзя завершить неактивный футбольный матч");
        cout << "Футбольный матч завершен" << endl;
        isActive = false;
    }
};


class VertexShape {
public:
    virtual vector<pair<double, double>> getVertices() const = 0;
    virtual ~VertexShape() {}
};

class Triangle4 : public VertexShape {
    vector<pair<double, double>> vertices;
public:
    Triangle4(const vector<pair<double, double>>& v) : vertices(v) {
        if (v.size() != 3) throw invalid_argument("Треугольник должен иметь 3 вершины");
        if (v[0] == v[1] || v[1] == v[2] || v[0] == v[2])
            throw invalid_argument("Вершины треугольника не должны совпадать");
    }
    vector<pair<double, double>> getVertices() const override {
        return vertices;
    }
};

class Pentagon : public VertexShape {
    vector<pair<double, double>> vertices;
public:
    Pentagon(const vector<pair<double, double>>& v) : vertices(v) {
        if (v.size() != 5) throw invalid_argument("Пятиугольник должен иметь 5 вершин");
        for (size_t i = 0; i < v.size(); i++) {
            for (size_t j = i + 1; j < v.size(); j++) {
                if (v[i] == v[j]) throw invalid_argument("Вершины пятиугольника не должны совпадать");
            }
        }
    }
    vector<pair<double, double>> getVertices() const override {
        return vertices;
    }
};

class Session5 {
protected:
    bool isActive = false;
public:
    virtual void startSession5() = 0;
    virtual ~Session5() {}
};

class UserSession5 : public Session5 {
public:
    void startSession5() override {
        if (isActive) throw runtime_error("Пользовательская сессия уже активна");
        isActive = true;
        cout << "Пользовательская сессия начата" << endl;
    }
};

class AdminSession6 : public Session5 {
public:
    void startSession5() override {
        if (isActive) throw runtime_error("Административная сессия уже активна");
        isActive = true;
        cout << "Административная сессия начата" << endl;
    }
};


class ColoredShape {
protected:
    string color;
public:
    ColoredShape(const string& c) : color(c) {
        if (c.empty()) throw invalid_argument("Цвет не может быть пустым");
    }
    virtual string getColor() const = 0;
    virtual ~ColoredShape() {}
};

class ColoredCircle : public ColoredShape {
public:
    ColoredCircle(const string& c) : ColoredShape(c) {}
    string getColor() const override {
        if (color == "transparent") throw runtime_error("Круг не может быть прозрачным");
        return color;
    }
};

class ColoredSquare : public ColoredShape {
public:
    ColoredSquare(const string& c) : ColoredShape(c) {}
    string getColor() const override {
        if (color == "invisible") throw runtime_error("Квадрат не может быть невидимым");
        return color;
    }
};


class Logger {
public:
    virtual void log(const string& message) = 0;
    virtual ~Logger() {}
};

class FileLogger : public Logger {
public:
    void log(const string& message) override {
        if (message.empty()) throw invalid_argument("Сообщение для лога не может быть пустым");
        cout << "Лог записан в файл: " << message << endl;
    }
};

class ConsoleLogger : public Logger {
public:
    void log(const string& message) override {
        if (message.empty()) throw invalid_argument("Сообщение для лога не может быть пустым");
        cout << "Лог выведен в консоль: " << message << endl;
    }
};


class DataProcessor5 {
public:
    virtual void processData5(const string& data) = 0;
    virtual ~DataProcessor5() {}
};

class CSVProcessor5 : public DataProcessor5 {
public:
    void processData5(const string& data) override {
        if (data.empty()) throw invalid_argument("CSV данные не могут быть пустыми");
        if (data.find(',') == string::npos)
            throw runtime_error("Некорректный CSV формат: отсутствуют разделители");

        cout << "CSV данные успешно обработаны" << endl;
    }
};
class JSONProcessor5 : public DataProcessor5 {
public:
    void processData5(const string& data) override {
        if (data.empty()) throw invalid_argument("JSON данные не могут быть пустыми");
        if (data.find('{') == string::npos || data.find('}') == string::npos)
            throw runtime_error("Некорректный JSON формат: отсутствуют фигурные скобки");

        cout << "JSON данные успешно обработаны" << endl;
    }
};
class Notification {
public:
    virtual void send(const string& recipient, const string& message) = 0;
    virtual ~Notification() {}
};

class EmailNotification : public Notification {
public:
    void send(const string& recipient, const string& message) override {
        if (recipient.empty() || recipient.find('@') == string::npos)
            throw invalid_argument("Некорректный email адрес");
        if (message.empty())
            throw invalid_argument("Сообщение не может быть пустым");

        cout << "Email отправлен на " << recipient << ": " << message << endl;
    }
};

class SMSNotification : public Notification {
public:
    void send(const string& recipient, const string& message) override {
        if (recipient.length() < 10)
            throw invalid_argument("Некорректный номер телефона");
        if (message.empty())
            throw invalid_argument("Сообщение не может быть пустым");

        cout << "SMS отправлено на " << recipient << ": " << message << endl;
    }
};

class PushNotification : public Notification {
public:
    void send(const string& recipient, const string& message) override {
        if (recipient.empty())
            throw invalid_argument("ID устройства не может быть пустым");
        if (message.empty())
            throw invalid_argument("Сообщение не может быть пустым");

        cout << "Push-уведомление отправлено на устройство " << recipient << ": " << message << endl;
    }
};

class PerimeterShape1 {
public:
    virtual double getPerimeter() const = 0;
    virtual ~PerimeterShape1() {}
};

class Circle5: public PerimeterShape1 {
    double radius;
public:
    Circle5(double r) : radius(r) {
        if (r <= 0) throw invalid_argument("Радиус должен быть положительным");
    }
    double getPerimeter() const override {
        return 2 * 3.14159 * radius;
    }
};

class Rectangle5 : public PerimeterShape1 {
    double width, height;
public:
    Rectangle5(double w, double h) : width(w), height(h) {
        if (w <= 0 || h <= 0) throw invalid_argument("Стороны должны быть положительными");
    }
    double getPerimeter() const override {
        return 2 * (width + height);
    }
};

class Triangle5 : public PerimeterShape1 {
    double a, b, c;
public:
    Triangle5(double a, double b, double c) : a(a), b(b), c(c) {
        if (a <= 0 || b <= 0 || c <= 0) throw invalid_argument("Стороны должны быть положительными");
        if (a + b <= c || a + c <= b || b + c <= a) throw invalid_argument("Некорректные стороны треугольника");
    }
    double getPerimeter() const override {
        return a + b + c;
    }
};

class Session {
protected:
    bool isActive = false;
public:
    virtual void start() = 0;
    virtual ~Session() {}
};

class UserSession : public Session {
public:
    void start() override {
        if (isActive) throw runtime_error("Пользовательская сессия уже активна");
        isActive = true;
        cout << "Пользовательская сессия начата" << endl;
    }
};

class AdminSession : public Session {
public:
    void start() override {
        if (isActive) throw runtime_error("Административная сессия уже активна");
        isActive = true;
        cout << "Административная сессия начата" << endl;
    }
};


class DataProcessor {
public:
    virtual void process(const string& data) = 0;
    virtual ~DataProcessor() {}
};

class CSVProcessor : public DataProcessor {
public:
    void process(const string& data) override {
        if (data.empty()) throw invalid_argument("CSV данные не могут быть пустыми");
        if (data.find(',') == string::npos)
            throw runtime_error("Некорректный CSV формат");

        cout << "CSV данные успешно обработаны" << endl;
    }
};

class JSONProcessor : public DataProcessor {
public:
    void process(const string& data) override {
        if (data.empty()) throw invalid_argument("JSON данные не могут быть пустыми");
        if (data.find('{') == string::npos || data.find('}') == string::npos)
            throw runtime_error("Некорректный JSON формат");

        cout << "JSON данные успешно обработаны" << endl;
    }
};

class XMLProcessor : public DataProcessor {
public:
    void process(const string& data) override {
        if (data.empty()) throw invalid_argument("XML данные не могут быть пустыми");
        if (data.find('<') == string::npos || data.find('>') == string::npos)
            throw runtime_error("Некорректный XML формат");

        cout << "XML данные успешно обработаны" << endl;
    }
};


class TransformableShape {
public:
    virtual void transform(double factor) = 0;
    virtual ~TransformableShape() {}
};

class TransformableCircle : public TransformableShape {
    double radius;
public:
    TransformableCircle(double r) : radius(r) {
        if (r <= 0) throw invalid_argument("Радиус должен быть положительным");
    }
    void transform(double factor) override {
        if (factor <= 0) throw invalid_argument("Коэффициент трансформации должен быть положительным");
        radius *= factor;
        cout << "Круг трансформирован. Новый радиус: " << radius << endl;
    }
};

class TransformableSquare : public TransformableShape {
    double side;
public:
    TransformableSquare(double s) : side(s) {
        if (s <= 0) throw invalid_argument("Сторона должна быть положительной");
    }
    void transform(double factor) override {
        if (factor <= 0) throw invalid_argument("Коэффициент трансформации должен быть положительным");
        side *= factor;
        cout << "Квадрат трансформирован. Новая сторона: " << side << endl;
    }
};

class Polygon1 : public TransformableShape {
    vector<double> sides;
public:
    Polygon1(const vector<double>& s) : sides(s) {
        if (s.size() < 3) throw invalid_argument("Полигон должен иметь минимум 3 стороны");
        for (double side : s) {
            if (side <= 0) throw invalid_argument("Стороны должны быть положительными");
        }
    }
    void transform(double factor) override {
        if (factor <= 0) throw invalid_argument("Коэффициент трансформации должен быть положительным");
        for (double& side : sides) {
            side *= factor;
        }
        cout << "Полигон трансформирован" << endl;
    }
};


class User5 {
protected:
    string username;
    int age;
public:
    User5(const string& name, int age) : username(name), age(age) {
        if (name.empty()) throw invalid_argument("Имя пользователя не может быть пустым");
        if (age < 0 || age > 120) throw invalid_argument("Некорректный возраст");
    }
    virtual void updateProfile5(const string& newName, int newAge) {
        if (newName.empty()) throw invalid_argument("Имя пользователя не может быть пустым");
        if (newAge < 0 || newAge > 120) throw invalid_argument("Некорректный возраст");
        username = newName;
        age = newAge;
        cout << "Профиль обновлен: " << username << ", " << age << " лет" << endl;
    }
    virtual ~User5() {}
};

class AdminUser5 : public User5 {
    string department;
public:
    AdminUser5(const string& name, int age, const string& dept) : User5(name, age), department(dept) {
        if (dept.empty()) throw invalid_argument("Отдел не может быть пустым");
    }
    void updateProfile5(const string& newName, int newAge) override {
        User5::updateProfile5(newName, newAge);
        cout << "Отдел администратора: " << department << endl;
    }
};

class RegularUser5 : public User5 {
    string address;
public:
    RegularUser5(const string& name, int age, const string& addr) : User5(name, age), address(addr) {
        if (addr.empty()) throw invalid_argument("Адрес не может быть пустым");
    }
    void updateProfile5(const string& newName, int newAge) override {
        User5::updateProfile5(newName, newAge);
        cout << "Адрес пользователя: " << address << endl;
    }
};
class Shape7 {
public:
    virtual string getDescription() const = 0;
    virtual ~Shape7() {}
};

class Circle7 : public Shape7 {
    double radius;
public:
    Circle7(double r) : radius(r) {
        if (r <= 0) throw invalid_argument("Радиус должен быть положительным");
    }
    string getDescription() const override {
        return "Круг с радиусом " + to_string(radius);
    }
};

class Square7 : public Shape7 {
    double side;
public:
    Square7(double s) : side(s) {
        if (s <= 0) throw invalid_argument("Сторона должна быть положительной");
    }
    string getDescription() const override {
        return "Квадрат со стороной " + to_string(side);
    }
};

class Triangle7 : public Shape7 {
    double a, b, c;
public:
    Triangle7(double a, double b, double c) : a(a), b(b), c(c) {
        if (a <= 0 || b <= 0 || c <= 0)
            throw invalid_argument("Стороны должны быть положительными");
        if (a + b <= c || a + c <= b || b + c <= a)
            throw invalid_argument("Некорректные стороны треугольника");
    }
    string getDescription() const override {
        return "Треугольник со сторонами " + to_string(a) + ", " + to_string(b) + ", " + to_string(c);
    }
};

class EmailService1 {
public:
    virtual void sendEmail(const string& to, const string& subject, const string& body) = 0;
    virtual ~EmailService1() {}
};

class SMTPService1 : public EmailService1 {
public:
    void sendEmail(const string& to, const string& subject, const string& body) override {
        if (to.empty() || to.find('@') == string::npos)
            throw invalid_argument("Некорректный email адрес");
        if (subject.empty())
            throw invalid_argument("Тема не может быть пустой");

        cout << "SMTP: Отправлено письмо '" << subject << "' на " << to << endl;
    }
};

class APIService1 : public EmailService1 {
public:
    void sendEmail(const string& to, const string& subject, const string& body) override {
        if (to.empty() || to.find('@') == string::npos)
            throw invalid_argument("Некорректный email адрес");
        if (body.empty())
            throw invalid_argument("Тело письма не может быть пустым");

        cout << "API: Отправлено письмо '" << subject << "' на " << to << endl;
    }
};

class MockEmailService : public EmailService {
public:
    void sendEmail(const string& to, const string& subject, const string& body) override {
        cout << "MOCK: Тестовая отправка письма '" << subject << "' на " << to << endl;
    }
};


class DataValidator {
public:
    virtual void validate(const string& data) const = 0;
    virtual ~DataValidator() {}
};

class EmailValidator : public DataValidator {
public:
    void validate(const string& email) const override {
        if (email.empty() || email.find('@') == string::npos || email.find('.') == string::npos)
            throw invalid_argument("Некорректный email адрес");
    }
};

class PhoneValidator : public DataValidator {
public:
    void validate(const string& phone) const override {
        if (phone.length() < 10 || phone.find_first_not_of("0123456789") != string::npos)
            throw invalid_argument("Некорректный номер телефона");
    }
};

class AgeValidator : public DataValidator {
public:
    void validate(const string& ageStr) const override {
        try {
            int age = stoi(ageStr);
            if (age < 0 || age > 120)
                throw invalid_argument("Некорректный возраст");
        }
        catch (...) {
            throw invalid_argument("Возраст должен быть числом");
        }
    }
};


class DimensionalShape {
public:
    virtual vector<double> getDimensions() const = 0;
    virtual ~DimensionalShape() {}
};

class DimensionalCircle : public DimensionalShape {
    double radius;
public:
    DimensionalCircle(double r) : radius(r) {
        if (r <= 0) throw invalid_argument("Радиус должен быть положительным");
    }
    vector<double> getDimensions() const override {
        return { radius };
    }
};

class DimensionalRectangle : public DimensionalShape {
    double width, height;
public:
    DimensionalRectangle(double w, double h) : width(w), height(h) {
        if (w <= 0 || h <= 0) throw invalid_argument("Стороны должны быть положительными");
    }
    vector<double> getDimensions() const override {
        return { width, height };
    }
};

class DimensionalTriangle : public DimensionalShape {
    double a, b, c;
public:
    DimensionalTriangle(double a, double b, double c) : a(a), b(b), c(c) {
        if (a <= 0 || b <= 0 || c <= 0)
            throw invalid_argument("Стороны должны быть положительными");
        if (a + b <= c || a + c <= b || b + c <= a)
            throw invalid_argument("Некорректные стороны треугольника");
    }
    vector<double> getDimensions() const override {
        return { a, b, c };
    }
};

class Transaction7 {
protected:
    double amount;
public:
    Transaction7(double amt) : amount(amt) {
        if (amt <= 0) throw invalid_argument("Сумма должна быть положительной");
    }
    virtual void execute(double& balance) = 0;
    virtual ~Transaction7() {}
};

class DepositTransaction7 : public Transaction7 {
public:
    DepositTransaction7(double amt) : Transaction7(amt) {}
    void execute(double& balance) override {
        balance += amount;
        cout << "Депозит на " << amount << " выполнен. Новый баланс: " << balance << endl;
    }
};

class WithdrawalTransaction7 : public Transaction7 {
public:
    WithdrawalTransaction7(double amt) : Transaction7(amt) {}
    void execute(double& balance) override {
        if (amount > balance)
            throw runtime_error("Недостаточно средств для снятия");
        balance -= amount;
        cout << "Снятие " << amount << " выполнено. Новый баланс: " << balance << endl;
    }
};


class IntersectableShape {
public:
    virtual bool getIntersection(const IntersectableShape& other) const = 0;
    virtual ~IntersectableShape() {}
};

class IntersectableCircle : public IntersectableShape {
    double x, y, radius;
public:
    IntersectableCircle(double x, double y, double r) : x(x), y(y), radius(r) {
        if (r <= 0) throw invalid_argument("Радиус должен быть положительным");
    }
    bool getIntersection(const IntersectableShape& other) const override {
        throw runtime_error("Реализация пересечения для круга не выполнена");
    }
};


class User8 {
protected:
    string username;
    string password;
public:
    User8(const string& user, const string& pass) : username(user), password(pass) {
        if (user.empty() || pass.empty())
            throw invalid_argument("Имя пользователя и пароль не могут быть пустыми");
    }
    virtual void authenticate(const string& inputPass) const = 0;
    virtual ~User8() {}
};

class AdminUser8 : public User8 {
public:
    AdminUser8(const string& user, const string& pass) : User8(user, pass) {}
    void authenticate(const string& inputPass) const override {
        if (inputPass != password)
            throw runtime_error("Неверные учетные данные администратора");
        cout << "Администратор " << username << " аутентифицирован" << endl;
    }
};

class RegularUser8 : public User8 {
public:
    RegularUser8(const string& user, const string& pass) : User8(user, pass) {}
    void authenticate(const string& inputPass) const override {
        if (inputPass != password)
            throw runtime_error("Неверные учетные данные пользователя");
        cout << "Пользователь " << username << " аутентифицирован" << endl;
    }
};





int main() {
    setlocale(LC_ALL, "Ru");
    try {
  
        Circle c(5);
        cout << "Площадь круга: " << c.area() << endl;

        Dog d("Шарик");
        cout << d.speak() << endl;


        SavingsAccount sa(500);
        sa.withdraw(300);

        TextFileHandler tfh;
        try {
            tfh.open("nonexistent.txt");
        }
        catch (const exception& e) {
            cerr << e.what() << endl;
        }


        Triangle t(3, 4, 5);
        t.draw();

     
        Student s("Иван", 20, "МГУ");
        s.display();


        Division div;
        cout << "10 / 2 = " << div.calculate(10, 2) << endl;

        Tennis tennis(2);
        tennis.start();


        PDFDocument pdf;
        pdf.save("document.pdf");


        IntMatrix im(3, 3);
        try {
            im.getElement(5, 5);
        }
        catch (const exception& e) {
            cerr << e.what() << endl;
        }

   
        Car car(50, 500);
        cout << "Расход топлива автомобиля: " << car.fuelEfficiency() << endl;

    
        AdminUser admin51("admin", "password");
        try {
            admin51.login("wrong");
        }
        catch (const exception& e) {
            cerr << e.what() << endl;
        }

  
        ScalableSquare sq(10);
        sq.scale(1.5);


        FictionLibrary flib({ "Война и мир", "Преступление и наказание" });
        flib.borrowBook("Война и мир");

  
        OnlineOrder oo("12345", "ул. Ленина, 10");
        oo.process();

       
        RotatableRectangle rr;
        rr.rotate(45);

    
        PayPalPayment pp(1000, "user@example.com");
        pp.processPayment();

        FileExceptionHandler feh;
        try {
            throw runtime_error("Файл не найден");
        }
        catch (const exception& e) {
            feh.handle(e);
        }


        OnlineCourse oc(50);
        oc.enroll();


        DiscountedCart dc(0.1);
        dc.checkout();
      
        Circle1 circle(10, -10, 5);
        circle.translate(2, 3);

     
        MySQLDatabase mysql;
        mysql.connect("");

        PrintTask printTask("Важное сообщение для печати");
        printTask.execute();


        Triangle1 triangle(3, 4, 5);
        cout << "Периметр треугольника: " << triangle.getPerimeter() << endl;


        RemoteWeatherService remoteWeather;
        cout << remoteWeather.getForecast() << endl;

 
        BankTransaction bankTrans("ACC123", "ACC456", 1000);
        bankTrans.commit();


       

        BoundingCircle boundingCircle(0, 0, 10);
        double x1, y1, x2, y2;
        boundingCircle.getBoundingBox(x1, y1, x2, y2);

        AdminProfile admin1("admin", 35, 5);
        admin1.updateProfile("superadmin", 36);

     
        CreditCardProcessor creditCard("1234567812345678", -5000);
        creditCard.processPayment(-1000);

        Circle4 circle4(5, 5, 10);
        circle4.reflect('x');


        TextFileReader textReader;
        textReader.read("document.txt");

        Square4 square4(5);
        cout << "Площадь квадрата: " << square4.getArea() << endl;

     

       
        ChessGame4 chess;
        

       
        Triangle4 triangle4({ {0,0}, {1,0}, {0.5,1} });
        auto vertices = triangle4.getVertices();

     
        AdminSession6 admin4;
        admin4.startSession5();

        
        ColoredSquare redSquare("red");
        cout << "Цвет квадрата: " << redSquare.getColor() << endl;

        ConsoleLogger console;
        console.log("Тестовое сообщение");

       
        JSONProcessor5 json;
        json.processData5("{\"key\":\"value\"}");
     

       
        Triangle1 triangle23(3, 4, 5);
        cout << "Периметр треугольника: " << triangle23.getPerimeter() << endl;

      

       
        JSONProcessor json1;
        json1.process("{\"key\":\"value\"}");

       
        TransformableCircle circle1(5);
        circle1.transform(1.5);

      
        RegularUser5 user12("Иван", 30, "ул. Примерная, 10");
        user12.updateProfile5("Иван Иванов", 31);
        
        Circle7 circle7(5);
        cout << circle7.getDescription() << endl;

     
      


        EmailValidator emailValidator;
        emailValidator.validate("test@example.com");

      
        DimensionalRectangle rect(10, 20);
        auto dims = rect.getDimensions();
        cout << "Размеры прямоугольника: " << dims[0] << " x " << dims[1] << endl;

        
        double balance = 1000;
        DepositTransaction7 deposit(500);
        deposit.execute(balance);

     
        RegularUser8 user7("user1", "password123");
        user7.authenticate("password123");

    }
    catch (const exception& e) {
        cerr  << e.what() << endl;
    }
}