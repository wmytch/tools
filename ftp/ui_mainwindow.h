/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actAppendHost;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *cbRemoteHostIP;
    QSpinBox *sbRemoteHostPort;
    QLabel *label_2;
    QLineEdit *editUser;
    QLabel *label_3;
    QLineEdit *editPassword;
    QPushButton *pbConnect;
    QRadioButton *rbFtp;
    QRadioButton *rbSftp;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QComboBox *cbRemotePath;
    QToolButton *toolButton_2;
    QTreeWidget *remoteFileSystem;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QPushButton *pbDownload;
    QPushButton *pbUpload;
    QSpacerItem *verticalSpacer_2;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_4;
    QComboBox *cbLocalPath;
    QToolButton *tbLocalParentPath;
    QTreeView *localView;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(786, 600);
        actAppendHost = new QAction(MainWindow);
        actAppendHost->setObjectName(QString::fromUtf8("actAppendHost"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        cbRemoteHostIP = new QComboBox(groupBox);
        cbRemoteHostIP->setObjectName(QString::fromUtf8("cbRemoteHostIP"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(cbRemoteHostIP->sizePolicy().hasHeightForWidth());
        cbRemoteHostIP->setSizePolicy(sizePolicy1);
        cbRemoteHostIP->setMinimumSize(QSize(250, 0));
        cbRemoteHostIP->setEditable(true);

        gridLayout->addWidget(cbRemoteHostIP, 0, 1, 1, 2);

        sbRemoteHostPort = new QSpinBox(groupBox);
        sbRemoteHostPort->setObjectName(QString::fromUtf8("sbRemoteHostPort"));
        sizePolicy.setHeightForWidth(sbRemoteHostPort->sizePolicy().hasHeightForWidth());
        sbRemoteHostPort->setSizePolicy(sizePolicy);
        sbRemoteHostPort->setMaximum(65535);
        sbRemoteHostPort->setValue(22);

        gridLayout->addWidget(sbRemoteHostPort, 0, 3, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(label_2, 0, 4, 1, 1);

        editUser = new QLineEdit(groupBox);
        editUser->setObjectName(QString::fromUtf8("editUser"));
        sizePolicy.setHeightForWidth(editUser->sizePolicy().hasHeightForWidth());
        editUser->setSizePolicy(sizePolicy);

        gridLayout->addWidget(editUser, 0, 5, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy2.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(label_3, 0, 6, 1, 1);

        editPassword = new QLineEdit(groupBox);
        editPassword->setObjectName(QString::fromUtf8("editPassword"));
        sizePolicy.setHeightForWidth(editPassword->sizePolicy().hasHeightForWidth());
        editPassword->setSizePolicy(sizePolicy);
        editPassword->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(editPassword, 0, 7, 1, 1);

        pbConnect = new QPushButton(groupBox);
        pbConnect->setObjectName(QString::fromUtf8("pbConnect"));
        sizePolicy.setHeightForWidth(pbConnect->sizePolicy().hasHeightForWidth());
        pbConnect->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pbConnect, 0, 8, 1, 1);

        rbFtp = new QRadioButton(groupBox);
        rbFtp->setObjectName(QString::fromUtf8("rbFtp"));
        rbFtp->setChecked(false);

        gridLayout->addWidget(rbFtp, 1, 1, 1, 1);

        rbSftp = new QRadioButton(groupBox);
        rbSftp->setObjectName(QString::fromUtf8("rbSftp"));
        rbSftp->setChecked(true);

        gridLayout->addWidget(rbSftp, 1, 2, 1, 1);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 3);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy3);
        groupBox_2->setMinimumSize(QSize(300, 0));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
        cbRemotePath = new QComboBox(groupBox_2);
        cbRemotePath->setObjectName(QString::fromUtf8("cbRemotePath"));
        cbRemotePath->setEditable(true);

        gridLayout_3->addWidget(cbRemotePath, 0, 0, 1, 1);

        toolButton_2 = new QToolButton(groupBox_2);
        toolButton_2->setObjectName(QString::fromUtf8("toolButton_2"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/up.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_2->setIcon(icon);

        gridLayout_3->addWidget(toolButton_2, 0, 1, 1, 1);

        remoteFileSystem = new QTreeWidget(groupBox_2);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setTextAlignment(1, Qt::AlignLeading|Qt::AlignVCenter);
        remoteFileSystem->setHeaderItem(__qtreewidgetitem);
        remoteFileSystem->setObjectName(QString::fromUtf8("remoteFileSystem"));
        remoteFileSystem->setEditTriggers(QAbstractItemView::NoEditTriggers);
        remoteFileSystem->setTabKeyNavigation(true);
        remoteFileSystem->setDragEnabled(true);
        remoteFileSystem->setDragDropMode(QAbstractItemView::DragDrop);
        remoteFileSystem->setAlternatingRowColors(true);
        remoteFileSystem->setSelectionMode(QAbstractItemView::ExtendedSelection);

        gridLayout_3->addWidget(remoteFileSystem, 1, 0, 1, 2);


        gridLayout_2->addWidget(groupBox_2, 1, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        pbDownload = new QPushButton(centralwidget);
        pbDownload->setObjectName(QString::fromUtf8("pbDownload"));
        pbDownload->setEnabled(false);
        sizePolicy.setHeightForWidth(pbDownload->sizePolicy().hasHeightForWidth());
        pbDownload->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(pbDownload);

        pbUpload = new QPushButton(centralwidget);
        pbUpload->setObjectName(QString::fromUtf8("pbUpload"));
        pbUpload->setEnabled(false);
        sizePolicy.setHeightForWidth(pbUpload->sizePolicy().hasHeightForWidth());
        pbUpload->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(pbUpload);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        gridLayout_2->addLayout(verticalLayout, 1, 1, 1, 1);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        sizePolicy3.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy3);
        gridLayout_4 = new QGridLayout(groupBox_3);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        cbLocalPath = new QComboBox(groupBox_3);
        cbLocalPath->setObjectName(QString::fromUtf8("cbLocalPath"));
        cbLocalPath->setEditable(true);
        cbLocalPath->setMaxCount(10);

        gridLayout_4->addWidget(cbLocalPath, 0, 0, 1, 1);

        tbLocalParentPath = new QToolButton(groupBox_3);
        tbLocalParentPath->setObjectName(QString::fromUtf8("tbLocalParentPath"));
        tbLocalParentPath->setIcon(icon);

        gridLayout_4->addWidget(tbLocalParentPath, 0, 1, 1, 1);

        localView = new QTreeView(groupBox_3);
        localView->setObjectName(QString::fromUtf8("localView"));
        localView->setMouseTracking(true);
        localView->setAcceptDrops(true);
        localView->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed|QAbstractItemView::SelectedClicked);
        localView->setTabKeyNavigation(true);
        localView->setDragEnabled(true);
        localView->setDragDropOverwriteMode(true);
        localView->setDragDropMode(QAbstractItemView::DragDrop);
        localView->setAlternatingRowColors(true);
        localView->setSelectionMode(QAbstractItemView::ExtendedSelection);
        localView->setSortingEnabled(true);

        gridLayout_4->addWidget(localView, 1, 0, 1, 2);


        gridLayout_2->addWidget(groupBox_3, 1, 2, 1, 1);


        verticalLayout_2->addLayout(gridLayout_2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 786, 21));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menu->menuAction());
        menu->addAction(actAppendHost);
        toolBar->addAction(actAppendHost);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actAppendHost->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\344\270\273\346\234\272", nullptr));
        groupBox->setTitle(QString());
        label->setText(QCoreApplication::translate("MainWindow", "\350\277\234\347\250\213\344\270\273\346\234\272", nullptr));
        cbRemoteHostIP->setCurrentText(QCoreApplication::translate("MainWindow", "192.168.211.103", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267", nullptr));
        editUser->setText(QCoreApplication::translate("MainWindow", "mac", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\345\257\206\347\240\201", nullptr));
        editPassword->setText(QCoreApplication::translate("MainWindow", ":::::::", nullptr));
        pbConnect->setText(QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245", nullptr));
        rbFtp->setText(QCoreApplication::translate("MainWindow", "ftp", nullptr));
        rbSftp->setText(QCoreApplication::translate("MainWindow", "sftp", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\350\277\234\347\250\213\344\270\273\346\234\272", nullptr));
        toolButton_2->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = remoteFileSystem->headerItem();
        ___qtreewidgetitem->setText(3, QCoreApplication::translate("MainWindow", "Date Modified", nullptr));
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("MainWindow", "Type", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("MainWindow", "Size", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("MainWindow", "Name", nullptr));
        pbDownload->setText(QCoreApplication::translate("MainWindow", ">", nullptr));
        pbUpload->setText(QCoreApplication::translate("MainWindow", "<", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "\346\234\254\345\234\260\344\270\273\346\234\272", nullptr));
        tbLocalParentPath->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
