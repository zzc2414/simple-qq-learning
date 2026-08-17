#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QDebug>

int main(int argc, char *argv[])
{
    int errorCount = 0;
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

    QObject::connect(
        button,
        &QPushButton::clicked,
        &window,
        [userEdit, passwordEdit, messageLabel, &errorCount]()
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
                    messageLabel->setText(
                        "Password entered incorrectly 3 times"
                    );
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
