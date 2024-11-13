#############################################################################
# Makefile for building: appweat.app/Contents/MacOS/appweat
# Generated by qmake (3.1) (Qt 6.7.1)
# Project:  ../../appweat.pro
# Template: app
# Command: /Users/hikipau/Qt/6.7.1/macos/bin/qmake6 -o appweat.xcodeproj/project.pbxproj ../../appweat.pro -spec macx-xcode -qtconf /Users/hikipau/Qt/6.7.1/ios/bin/target_qt.conf CONFIG+=debug CONFIG+=iphonesimulator CONFIG+=simulator CONFIG+=qml_debug
#############################################################################

MAKEFILE      = project.pbxproj

EQ            = =

MOC       = /Users/hikipau/Qt/6.7.1/macos/libexec/moc
UIC       = /Users/hikipau/Qt/6.7.1/macos/libexec/uic
LEX       = flex
LEXFLAGS  = 
YACC      = yacc
YACCFLAGS = -d
DEFINES       = -DQT_QML_DEBUG -DQT_MULTIMEDIAWIDGETS_LIB -DQT_WIDGETS_LIB -DQT_MULTIMEDIA_LIB -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_SQL_LIB -DQT_CORE_LIB
INCPATH       = -I../../../appweat -I. -I../../../../Qt/6.7.1/ios/mkspecs/common/uikit -I../../../../Qt/6.7.1/ios/include -I../../../../Qt/6.7.1/ios/include/QtMultimediaWidgets -I../../../../Qt/6.7.1/ios/include/QtWidgets -I../../../../Qt/6.7.1/ios/include/QtMultimedia -I../../../../Qt/6.7.1/ios/include/QtGui -I../../../../Qt/6.7.1/ios/include/QtNetwork -I../../../../Qt/6.7.1/ios/include/QtSql -I../../../../Qt/6.7.1/ios/include/QtCore -I. -I. -I../../../../Qt/6.7.1/ios/mkspecs/macx-ios-clang
DEL_FILE  = rm -f
MOVE      = mv -f

preprocess: compilers
clean preprocess_clean: compiler_clean

mocclean: compiler_moc_header_clean compiler_moc_objc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_objc_header_make_all compiler_moc_source_make_all

check: first

benchmark: first

compilers: qrc_resources.cpp moc_mainwindow.cpp ui_mainwindow.h
compiler_rcc_make_all: qrc_resources.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_resources.cpp
qrc_resources.cpp: ../../resources.qrc \
		../../../../Qt/6.7.1/macos/libexec/rcc \
		../../Resources/videos/фон.mp4 \
		../../Resources/photo/фон.png
	/Users/hikipau/Qt/6.7.1/macos/libexec/rcc -name resources --no-zstd ../../resources.qrc -o qrc_resources.cpp

compiler_moc_header_make_all: moc_mainwindow.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_mainwindow.cpp
moc_mainwindow.cpp: ../../mainwindow.h \
		../../../../Qt/6.7.1/ios/include/QtWidgets/QMainWindow \
		../../../../Qt/6.7.1/ios/include/QtCore/QDebug \
		../../../../Qt/6.7.1/ios/include/QtNetwork/QNetworkAccessManager \
		../../../../Qt/6.7.1/ios/include/QtNetwork/QNetworkRequest \
		../../../../Qt/6.7.1/ios/include/QtNetwork/QNetworkReply \
		../../../../Qt/6.7.1/ios/include/QtCore/QByteArray \
		../../../../Qt/6.7.1/ios/include/QtGui/QPixmap \
		../../../../Qt/6.7.1/ios/include/QtMultimedia/QMediaPlayer \
		../../../../Qt/6.7.1/ios/include/QtMultimediaWidgets/QVideoWidget \
		../../../../Qt/6.7.1/ios/include/QtWidgets/QVBoxLayout \
		../../../../Qt/6.7.1/ios/include/QtSql/QSqlQuery \
		../../../../Qt/6.7.1/macos/libexec/moc
	/Users/hikipau/Qt/6.7.1/macos/libexec/moc $(DEFINES) -D__APPLE__ -D__GNUC__=4 -D__APPLE_CC__ -D__cplusplus=199711L -D__APPLE_CC__=6000 -D__clang__ -D__clang_major__=16 -D__clang_minor__=0 -D__clang_patchlevel__=0 -D__GNUC__=4 -D__GNUC_MINOR__=2 -D__GNUC_PATCHLEVEL__=1 -I/Users/hikipau/Qt/6.7.1/ios/mkspecs/macx-ios-clang -I/Users/hikipau/QtProjects/appweat -I/Users/hikipau/Qt/6.7.1/ios/mkspecs/common/uikit -I/Users/hikipau/Qt/6.7.1/ios/include -I/Users/hikipau/Qt/6.7.1/ios/include/QtMultimediaWidgets -I/Users/hikipau/Qt/6.7.1/ios/include/QtWidgets -I/Users/hikipau/Qt/6.7.1/ios/include/QtMultimedia -I/Users/hikipau/Qt/6.7.1/ios/include/QtGui -I/Users/hikipau/Qt/6.7.1/ios/include/QtNetwork -I/Users/hikipau/Qt/6.7.1/ios/include/QtSql -I/Users/hikipau/Qt/6.7.1/ios/include/QtCore -I. -I/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS18.0.sdk/usr/include/c++/v1 -I/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/clang/16/include -I/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS18.0.sdk/usr/include -I/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include ../../mainwindow.h -o moc_mainwindow.cpp

compiler_moc_objc_header_make_all:
compiler_moc_objc_header_clean:
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_mainwindow.h
compiler_uic_clean:
	-$(DEL_FILE) ui_mainwindow.h
ui_mainwindow.h: ../../mainwindow.ui \
		../../../../Qt/6.7.1/macos/libexec/uic
	/Users/hikipau/Qt/6.7.1/macos/libexec/uic ../../mainwindow.ui -o ui_mainwindow.h

compiler_rez_source_make_all:
compiler_rez_source_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_rcc_clean compiler_moc_header_clean compiler_uic_clean 
