#include <QtTest>
#include <QHttpServer/Header>

QHTTPSERVER_USE_NAMESPACE

class HeaderTest : public QObject
{
    Q_OBJECT

private slots:
    void testHeader()
    {
        Header h1;
        Header h2;
        QVERIFY(!h1.isValid());
        QVERIFY(!h2.isValid());
        QVERIFY(h1.name().isEmpty());
        QVERIFY(h1.value().isEmpty());
        QVERIFY(h1.values().isEmpty());
        QCOMPARE(h1, h2);

        h1 = Header("foo", "");
        h2 = Header("FOO", "");
        QVERIFY(h1.isValid());
        QVERIFY(h2.isValid());
        QCOMPARE(h1.name(), QByteArray("foo"));
        QCOMPARE(h2.name(), QByteArray("FOO"));
        QCOMPARE(h1, h2);
    }
};

QTEST_GUILESS_MAIN(HeaderTest)

#include "headertest.moc"
