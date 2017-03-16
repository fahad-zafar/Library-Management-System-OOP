#-------------------------------------------------
#
# Project created by QtCreator 2016-10-10T18:33:30
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 14-4048
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    book.cpp \
    borrower.cpp \
    loan.cpp \
    user.cpp \
    libitem.cpp \
    lms.cpp \
    lms_singleton.cpp \
    clerk.cpp \
    librarian.cpp \
    dvd.cpp \
    borrowerdata.cpp \
    itemdata.cpp \
    clerkdata.cpp \
    changeborrowerinfo.cpp \
    addborrower.cpp \
    borrowerinfo.cpp \
    checkoutitem.cpp \
    returnitemwindow.cpp \
    returnitem.cpp \
    holdrequestswindow.cpp \
    librariandata.cpp \
    additem.cpp \
    delitem.cpp \
    changeiteminfo.cpp \
    available.cpp \
    onloan.cpp \
    itemstate.cpp \
    renewitems.cpp

HEADERS  += mainwindow.h \
    book.h \
    borrower.h \
    loan.h \
    user.h \
    libitem.h \
    lms.h \
    lms_singleton.h \
    clerk.h \
    librarian.h \
    dvd.h \
    borrowerdata.h \
    itemdata.h \
    clerkdata.h \
    changeborrowerinfo.h \
    addborrower.h \
    borrowerinfo.h \
    checkoutitem.h \
    returnitemwindow.h \
    returnitem.h \
    holdrequestswindow.h \
    librariandata.h \
    additem.h \
    delitem.h \
    changeiteminfo.h \
    bookstate.h \
    available.h \
    onloan.h \
    itemstate.h \
    renewitems.h

FORMS    += mainwindow.ui \
    borrowerdata.ui \
    itemdata.ui \
    clerkdata.ui \
    changeborrowerinfo.ui \
    addborrower.ui \
    borrowerinfo.ui \
    checkoutitem.ui \
    returnitemwindow.ui \
    returnitem.ui \
    holdrequestswindow.ui \
    librariandata.ui \
    additem.ui \
    delitem.ui \
    changeiteminfo.ui \
    renewitems.ui
