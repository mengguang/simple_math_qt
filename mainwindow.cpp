#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(exam_timer_timeout()));
  prepare_new_exam();
  connect(ui->answer_button_1,SIGNAL(clicked()),this,SLOT(general_answer_clicked()));
  connect(ui->answer_button_2,SIGNAL(clicked()),this,SLOT(general_answer_clicked()));
  connect(ui->answer_button_3,SIGNAL(clicked()),this,SLOT(general_answer_clicked()));
  connect(ui->answer_button_4,SIGNAL(clicked()),this,SLOT(general_answer_clicked()));
  connect(ui->answer_button_5,SIGNAL(clicked()),this,SLOT(general_answer_clicked()));
  connect(ui->answer_button_6,SIGNAL(clicked()),this,SLOT(general_answer_clicked()));
  connect(ui->answer_button_7,SIGNAL(clicked()),this,SLOT(general_answer_clicked()));
  connect(ui->answer_button_8,SIGNAL(clicked()),this,SLOT(general_answer_clicked()));
  connect(ui->answer_button_9,SIGNAL(clicked()),this,SLOT(general_answer_clicked()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_restartButton_clicked() {
  if (started == true) {
    prepare_new_exam();
  } else {
    questions = 0;
    score = total_questions;
    start_time = time(nullptr);
    started = true;
    ui->restartButton->setText("Stop");
    ui->notifyText->setText("");
    timer->start(1000);
    new_question();
  }
}

void MainWindow::on_userAnswerText_returnPressed() {
  if (started == false) {
    return;
  }
  auto user_answer = QString("");
  if (user_answer.length() == 0) {
    return;
  }
  auto user_answer_valid = false;
  long user_answer_l = user_answer.toLong(&user_answer_valid, 10);
  if (!user_answer_valid) {
    return;
  } else {
    if (user_answer_l == answer) {
      ui->notifyText->setStyleSheet("QLabel {color : green; }");
      ui->notifyText->setText("Right!");
    } else {
      score--;
      ui->notifyText->setStyleSheet("QLabel {color : red; }");
      ui->notifyText->setText("Wrong!");
      return;
    }
  }
  questions++;
  if (questions >= total_questions) {
    stop_exam();
  } else {
    new_question();
  }
}

void MainWindow::exam_timer_timeout() {
  auto now = time(nullptr);
  ui->timeUsedLCD->display(static_cast<int>((now - start_time)));
}

void MainWindow::new_question() {
  ui->questionNumberLCD->display(questions + 1);
  const auto op = rand() % 2;

  auto x = 0;
  auto y = 0;

  if (op == sum) {
    const auto sum_result = rand() % (op_sum_max_result - op_sum_min_result) +
                            op_sum_min_result + 1;
    x = rand() % (sum_result - 1) + 1;
    y = sum_result - x;
  }
  if (op == sub) {
    x = rand() % (op_sub_max_number_first - op_sub_min_number_first) +
        op_sub_min_number_first;
    y = rand() % (x - 1) + 1;
  }

  if (op == sum) {
    auto question = QString("%1 + %2 = ").arg(x).arg(y);
    ui->questionText->setText(question);
    answer = x + y;
  }
  if (op == sub) {
    auto question = QString("%1 - %2 = ").arg(x).arg(y);
    ui->questionText->setText(question);
    answer = x - y;
  }
  init_answer_button(answer);
}

void MainWindow::prepare_new_exam() {
  started = false;
  timer->stop();
  const auto seed = static_cast<unsigned int>(time(nullptr));
  srand(seed);
  ui->restartButton->setText("Start");
  ui->questionText->setText("");
  ui->notifyText->setText("");
  ui->timeUsedLCD->display(0);
  ui->questionNumberLCD->display(0);
  init_answer_button(0);
}

void MainWindow::stop_exam() {
  started = false;
  timer->stop();
  ui->notifyText->setStyleSheet("QLabel {color : blue; }");
  ui->notifyText->setText(QString("Final Score: %1").arg(score));
  ui->restartButton->setText("Start");
}

void MainWindow::init_answer_button(int answer) {
  int answers[9];
  for (int i = 0; i < 100; i++) {
    answers[i % 9] = rand() % 20;
  }
  int ax = rand() % 9;
  answers[ax] = answer;
  ui->answer_button_1->setText(QString("%1").arg(answers[0]));
  ui->answer_button_2->setText(QString("%1").arg(answers[1]));
  ui->answer_button_3->setText(QString("%1").arg(answers[2]));
  ui->answer_button_4->setText(QString("%1").arg(answers[3]));
  ui->answer_button_5->setText(QString("%1").arg(answers[4]));
  ui->answer_button_6->setText(QString("%1").arg(answers[5]));
  ui->answer_button_7->setText(QString("%1").arg(answers[6]));
  ui->answer_button_8->setText(QString("%1").arg(answers[7]));
  ui->answer_button_9->setText(QString("%1").arg(answers[8]));
}

void MainWindow::check_answer(int x) {
  if (started == false) {
    return;
  }
  if (x == answer) {
    ui->notifyText->setStyleSheet("QLabel {color : green; }");
    ui->notifyText->setText("You Are Right!");
  } else {
    score--;
    ui->notifyText->setStyleSheet("QLabel {color : red; }");
    ui->notifyText->setText("You Are Wrong!");
    return;
  }
  questions++;
  if (questions >= total_questions) {
    stop_exam();
  } else {
    new_question();
  }
}

void MainWindow::general_answer_clicked() {
  auto ok = false;
  auto x = static_cast<QPushButton *>(sender())->text().toInt(&ok, 10);
  if (!ok) {
    return;
  }
  check_answer(x);
}
