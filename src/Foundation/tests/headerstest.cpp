#include <QtTest>
#include <Flugs/Foundation/Headers>

FLUGS_USE_NAMESPACE

class HeadersTest : public QObject
{
    Q_OBJECT

private slots:
#if 0
    void testHeaderClass() {
        Header h1("foo", "bar");

        QCOMPARE(h1.name(), QByteArray("foo"));
        QCOMPARE(h1.value(), QByteArray("bar"));
        QVERIFY(!h1.values().isEmpty());
        QCOMPARE(h1.values().size(), 1);

        Header h2("foo", "bar");
        Header h3("FOO", "bar");

        QCOMPARE(h1, h2);
        QCOMPARE(h1, h3);
        QCOMPARE(h2, h1);
        QCOMPARE(h2, h3);
        QCOMPARE(h3, h1);
        QCOMPARE(h3, h2);
    }

    // cppcheck-suppress unusedFunction
    void testEmpty()
    {
        Headers h;
        QVERIFY(h.isEmpty());
        QCOMPARE(h.size(), 0);
        QCOMPARE(h.value("foo"), QByteArray());
        QCOMPARE(h.value("foo", "foobar"), QByteArray("foobar"));
        QCOMPARE(h.value("", "foobar"), QByteArray("foobar"));
        QVERIFY(h.toMultiHash().isEmpty());
    }

    // cppcheck-suppress unusedFunction
    void testValue()
    {
        Headers h;
        QCOMPARE(h.value("foo"), QByteArray());
        QCOMPARE(h.value("FOO"), QByteArray());
        QCOMPARE(h.value("foo", "foobar"), QByteArray("foobar"));
        QCOMPARE(h.value("FOO", "foobar"), QByteArray("foobar"));

        h.insert("foo", "bar");
        QCOMPARE(h.value("foo"), QByteArray("bar"));
        QCOMPARE(h.value("FOO"), QByteArray("bar"));
        QCOMPARE(h.value("foo", "foobar"), QByteArray("bar"));
        QCOMPARE(h.value("FOO", "foobar"), QByteArray("bar"));
        QVERIFY(h.contains("foo"));
        QVERIFY(h.contains("FOO"));
        QVERIFY(!h.contains("foobar"));
        QVERIFY(!h.contains("bar"));
        QVERIFY(!h.isEmpty());
        QCOMPARE(h.size(), 1);

        h.insert("FOO", "bar");
        QCOMPARE(h.value("foo"), QByteArray("bar"));
        QCOMPARE(h.value("FOO"), QByteArray("bar"));
        QCOMPARE(h.value("foo", "foobar"), QByteArray("bar"));
        QCOMPARE(h.value("FOO", "foobar"), QByteArray("bar"));
        QVERIFY(h.contains("foo"));
        QVERIFY(h.contains("FOO"));
        QVERIFY(!h.contains("foobar"));
        QVERIFY(!h.contains("bar"));
        QVERIFY(!h.isEmpty());
    }
#endif
};

QTEST_GUILESS_MAIN(HeadersTest)

#include "headerstest.moc"
