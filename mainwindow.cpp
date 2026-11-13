#include "mainwindow.h"
#include <QFont>
#include <QPalette>
#include <QIcon>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(500, 450);
    this->setWindowTitle("Калькулятор ИМТ");
    this->setWindowIcon(QIcon(""));

    titleLabel = new QLabel("Калькулятор ИМТ", this);
    titleLabel->setGeometry(0, 15, 500, 30);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = titleLabel->font();
    titleFont.setBold(true);
    titleFont.setPointSize(14);
    titleLabel->setFont(titleFont);

    QPalette pal = this->palette();
    pal.setColor(QPalette::PlaceholderText, Qt::gray);

    nameLabel = new QLabel("Ваше имя:", this);
    nameLabel->setGeometry(50, 60, 100, 30);

    nameEdit = new QLineEdit(this);
    nameEdit->setGeometry(150, 60, 300, 30);
    nameEdit->setPlaceholderText("Введите ваше имя");
    nameEdit->setPalette(pal);

    heightLabel = new QLabel("Рост (в метрах):", this);
    heightLabel->setGeometry(50, 100, 100, 30);

    heightSpinBox = new QDoubleSpinBox(this);
    heightSpinBox->setGeometry(150, 100, 100, 30);
    heightSpinBox->setDecimals(2);
    heightSpinBox->setRange(0.50, 2.50);
    heightSpinBox->setValue(1.70);
    heightSpinBox->setSingleStep(0.01);

    weightSliderLabel = new QLabel("Вес (кг):", this);
    weightSliderLabel->setGeometry(50, 140, 100, 30);

    weightSlider = new QSlider(Qt::Horizontal, this);
    weightSlider->setGeometry(150, 140, 200, 30);
    weightSlider->setRange(20, 200);
    weightSlider->setValue(70);

    weightSpinBox = new QSpinBox(this);
    weightSpinBox->setGeometry(360, 140, 90, 30);
    weightSpinBox->setRange(20, 200);
    weightSpinBox->setValue(70);
    weightSpinBox->setReadOnly(true);

    connect(weightSlider, &QSlider::valueChanged, this, &MainWindow::updateWeight);

    helpCheckBox = new QCheckBox("Показать справку", this);
    helpCheckBox->setGeometry(50, 190, 200, 30);

    helpLabel = new QLabel("Недостаток веса — меньше 18,5; норма — 18,5–24,9; избыток — 25–29,9; ожирение — 30 и больше", this);
    helpLabel->setGeometry(50, 220, 400, 40);
    helpLabel->setWordWrap(true);
    helpLabel->setVisible(false);

    connect(helpCheckBox, &QCheckBox::toggled, this, &MainWindow::toggleHelp);

    calcButton = new QPushButton("Рассчитать", this);
    calcButton->setGeometry(200, 280, 100, 30);
    connect(calcButton, &QPushButton::clicked, this, &MainWindow::calculateIMT);

    resultLabel = new QLabel("", this);
    resultLabel->setGeometry(50, 330, 400, 60);
    resultLabel->setAlignment(Qt::AlignCenter);
    resultLabel->setWordWrap(true);
}

MainWindow::~MainWindow()
{
}

void MainWindow::updateWeight(int value)
{
    weightSpinBox->setValue(value);
}

void MainWindow::toggleHelp(bool checked)
{
    helpLabel->setVisible(checked);
}

void MainWindow::calculateIMT()
{
    double height = heightSpinBox->value();
    double weight = weightSlider->value();
    QString name = nameEdit->text();

    if (name.isEmpty()) {
        name = "Гражданин";
    }

    double imt = weight / (height * height);
    QString category;

    if (imt < 18.5) {
        category = "недостаток веса";
    } else if (imt >= 18.5 && imt <= 24.9) {
        category = "норма";
    } else if (imt >= 25.0 && imt <= 29.9) {
        category = "избыток";
    } else {
        category = "ожирение";
    }

    QString resultText = QString("%1, ваш ИМТ: %2 (%3)").arg(name).arg(imt, 0, 'f', 1).arg(category);
    resultLabel->setText(resultText);
}