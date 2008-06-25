/*
FatRat download manager
http://fatrat.dolezel.info

Copyright (C) 2006-2008 Lubos Dolezel <lubos a dolezel.info>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
version 2 as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifndef GENERALDONWLOADFORMS_H
#define GENERALDONWLOADFORMS_H
#include "ui_HttpOptsWidget.h"
#include "ui_HttpUrlOptsDlg.h"
#include "WidgetHostChild.h"
#include <QDialog>
#include "GeneralDownload.h"

class HttpUrlOptsDlg : public QDialog, Ui_HttpUrlOptsDlg
{
Q_OBJECT
public:
	HttpUrlOptsDlg(QWidget* parent, QList<Transfer*>* multi = 0);
	void init();
	int exec();
	void runMultiUpdate();
	virtual void accept();

	QString m_strURL, m_strReferrer, m_strUser, m_strPassword, m_strBindAddress;
	FtpMode m_ftpMode;
	QUuid m_proxy;
	QList<Transfer*>* m_multi;
};

class HttpOptsWidget : public QObject, public WidgetHostChild, Ui_HttpOptsWidget
{
Q_OBJECT
public:
	HttpOptsWidget(QWidget* me,GeneralDownload* myobj);
	virtual void load();
	virtual void accepted();
	virtual bool accept();
public slots:
	void addUrl();
	void editUrl();
	void deleteUrl();
private:
	GeneralDownload* m_download;
	QList<GeneralDownload::UrlObject> m_urls;
};

#endif