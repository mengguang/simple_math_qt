#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(exam_timer_timeout()));
  prepare_new_exam();
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
    ui->userAnswerText->setFocus();
    new_question();
  }
}

void MainWindow::on_userAnswerText_returnPressed() {
  if (started == false) {
    return;
  }
  auto user_answer = ui->userAnswerText->text();
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
  ui->userAnswerText->clear();
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
  ui->userAnswerText->setText("");
}

void MainWindow::stop_exam() {
  ui->notifyText->setText(QString("Score: %1").arg(score));
  started = false;
  // m_eximTimer.Stop();
  ui->restartButton->setText("Start");
}
