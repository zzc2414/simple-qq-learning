#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTimer>
#include <QDebug>

int main(int argc, char *argv[])
{
    int errorCount = 0;
    int remainingSeconds = 0;
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("My First Qt");
    window.resize(400, 250);

    QLabel *userLabel = new QLabel("Username:", &window);
    userLabel->setGeometry(70, 50, 80, 30);

    QLineEdit *userEdit = new QLineEdit(&window);
    userEdit->setGeometry(150, 50, 170, 30);

    QLabel *passwordLabel = new QLabel("Password:", &window);
    passwordLabel->setGeometry(70, 90, 80, 30);

    QLineEdit *passwordEdit = new QLineEdit(&window);
    passwordEdit->setGeometry(150, 90, 170, 30);


    QPushButton *button = new QPushButton("Login", &window);
    button->setGeometry(150, 150, 100, 40);

    QLabel *messageLabel = new QLabel("", &window);
    messageLabel->setGeometry(70, 200, 260, 30);

    QTimer *lockTimer = new QTimer(&window);
    lockTimer->setInterval(1000);

    QObject::connect(
        lockTimer,
        &QTimer::timeout,
        &window,
        [button, messageLabel, lockTimer, &errorCount, &remainingSeconds]()
        {
            remainingSeconds--;

            if (remainingSeconds <= 0)
            {
                lockTimer->stop();
                button->setEnabled(true);
                errorCount = 0;
                messageLabel->setText("Login unlocked. Please try again");
            }
            else
            {
                messageLabel->setText(
                    QString("Locked: %1 seconds remaining").arg(remainingSeconds)
                );
            }
        }
    );

    QObject::connect(
        button,
        &QPushButton::clicked,
        &window,
        [userEdit, passwordEdit, button, messageLabel, lockTimer,
         &errorCount, &remainingSeconds]()
        {
            QString username = userEdit->text();
            QString password = passwordEdit->text();

            if (username.isEmpty() || password.isEmpty())
            {
                messageLabel->setText("Please enter username and password");
            }
            else if (username != "admin")
            {
                messageLabel->setText("Account does not exist");
            }
            else if (password != "123456")
            {
                errorCount++;

                messageLabel->setText(
                    "Wrong password. Error count: "
                    + QString::number(errorCount)
                );

                if (errorCount >= 3)
                {
                    remainingSeconds = 60;
                    button->setEnabled(false);
                    messageLabel->setText("Locked: 60 seconds remaining");
                    lockTimer->start();
                }
            }
            else
            {
                messageLabel->setText("Login success");
                errorCount = 0;
            }
        }
    );


    window.show();

    return app.exec();
}
