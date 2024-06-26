/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "xform.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QTimer>
#include "lispthread.h"

int main(int argc, char **argv)
{
    /*
     * First of all, we have to initialize the ECL environment.
     * This should be done from the main thread.
     */
    cl_boot(argc, argv);

    Q_INIT_RESOURCE(affine);
#ifdef Q_OS_ANDROID
    qputenv("QT_SCALE_FACTOR", "2");
#endif
    QApplication app(argc, argv);

    XFormWidget xformWidget(nullptr);
    QStyle *arthurStyle = new ArthurStyle;
    xformWidget.setStyle(arthurStyle);

    const QList<QWidget *> widgets = xformWidget.findChildren<QWidget *>();
    for (QWidget *w : widgets) {
        w->setStyle(arthurStyle);
        w->setAttribute(Qt::WA_AcceptTouchEvents);
    }

    xformWidget.show();

    QCommandLineParser *parser = new QCommandLineParser();
    parser->addHelpOption();
    parser->addOption({{"e", "eval"}, "Evaluate a Lisp expression.", "expression"});
    parser->process(app);

    //
    // By default, swank listens on localhost.
    // start-swank.lisp can be modified to make it listen on another
    // address by getting the address from the enviroment variable
    //        ...
    //   ---->:interface (my-getenv "SWANK_HOST" "localhost")
    //        :port (parse-integer (my-getenv "SWANK_PORT" "4005"))
    //        ...
    qputenv("SWANK_HOST", "192.168.26.131");

    //
    // The LispThread will be created and started in the event loop
    //
    QTimer::singleShot(100, [parser](){(new LispThread(parser->values("eval")))->start();delete parser;});

    return app.exec();
}
