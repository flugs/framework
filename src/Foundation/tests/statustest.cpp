#include <QtTest>
#include <QtCore>
#include <Flugs/Foundation/Status>

FLUGS_USE_NAMESPACE

class StatusTest : public QObject
{
    Q_OBJECT

    struct Stat {
        Status status;
        int value;
        Status::Code code;
        Status::Family family;
        QString reasonPhrase;
    };

private slots:
    // cppcheck-suppress unusedFunction
    void test()
    {
        // clang-format off
        QList<Stat> list = {
            Stat { Status(),                               0, Status::Code::Other,           Status::Family::Other,         QStringLiteral("")                 },
            Stat { Status(Status::Code::Other),            0, Status::Code::Other,           Status::Family::Other,         QStringLiteral("")                 },
            Stat { Status(Status::Code::Continue),       100, Status::Code::Continue,        Status::Family::Informational, QStringLiteral("Continue")         },
            Stat { Status(Status::Code::Accepted),       202, Status::Code::Accepted,        Status::Family::Successful,    QStringLiteral("Accepted")         },
            Stat { Status(Status::Code::MultipleChoice), 300, Status::Code::MultipleChoice,  Status::Family::Redirection,   QStringLiteral("Multiple Choices") },
            Stat { Status(Status::Code::ImATeapot),      418, Status::Code::ImATeapot,       Status::Family::ClientError,   QStringLiteral("I'm a teapot")     },
            Stat { Status(Status::Code::NotImplemented), 501, Status::Code::NotImplemented,  Status::Family::ServerError,   QStringLiteral("Not Implemented")  },
            Stat { Status(402),                          402, Status::Code::PaymentRequired, Status::Family::ClientError,   QStringLiteral("Payment Required") },
            Stat { Status(333),                          333, Status::Code::Other,           Status::Family::Redirection,   QStringLiteral("")                 },
            Stat { Status(783),                          783, Status::Code::Other,           Status::Family::Other,         QStringLiteral("")                 },
        };
        // clang-format on

        foreach(const Stat &s, list) {
            QCOMPARE(s.status, s.status);
            QCOMPARE(s.status, Status(s.value));
            QCOMPARE(s.status.code(), s.code);
            QCOMPARE(s.status.number(), s.value);
            QCOMPARE(s.status.family(), s.family);
            QCOMPARE(s.status.reasonPhrase(), s.reasonPhrase);
            QVERIFY(s.status == s.value);
            QVERIFY(s.value == s.status);
            QVERIFY(s.status == Status(s.value));
        }
    }
};

QTEST_GUILESS_MAIN(StatusTest)

#include "statustest.moc"
